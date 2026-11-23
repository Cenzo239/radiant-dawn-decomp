#!/usr/bin/env python3
"""Remove function definitions from an MWCC ELF object (big-endian ELF32 relocatable).

Used for weak/inline functions (implicit destructors, template ctors, ...) whose single copy in the
original link lives in another object: the original linker kept one definition, but the compiled
object of this source still emits its own copy, which MWLD would keep first (the DOL would then
differ). The function's bytes are cut out of .text, the symbol becomes undefined (so every call in
the object binds to the copy that exists elsewhere in the link), later functions move up and
relocation offsets/addends follow.

Usage: dropfn.py <in.o> <out.o> name [name ...]     (in and out may be the same file)
Exit status 1 (and the file untouched) when a name is not a function of .text, a relocation
targets the middle of a dropped span, or the object has exception tables.
"""
import struct
import sys


def rd(fmt, d, o):
    return struct.unpack_from(">" + fmt, d, o)


def main(argv):
    src, dst, names = argv[1], argv[2], set(argv[3:])
    d = open(src, "rb").read()
    if d[:4] != b"\x7fELF" or d[4] != 1 or d[5] != 2:
        sys.exit("dropfn: not a big-endian ELF32 object")
    (shoff,) = rd("I", d, 0x20)
    shentsize, shnum, shstrndx = rd("HHH", d, 0x2E)
    secs = []
    for i in range(shnum):
        n, ty, fl, ad, off, sz, lk, inf, al, es = rd("10I", d, shoff + i * shentsize)
        secs.append(dict(name_off=n, type=ty, flags=fl, addr=ad, off=off, size=sz, link=lk, info=inf,
                         align=al, entsize=es))
    shstr = d[secs[shstrndx]["off"]:secs[shstrndx]["off"] + secs[shstrndx]["size"]]
    for s in secs:
        e = shstr.index(b"\0", s["name_off"])
        s["name"] = shstr[s["name_off"]:e].decode()
        s["data"] = bytearray(d[s["off"]:s["off"] + s["size"]]) if s["type"] != 8 else bytearray()
    if any(s["name"] in ("extab", "extabindex") for s in secs):
        sys.exit("dropfn: object has exception tables")
    ti = next(i for i, s in enumerate(secs) if s["name"] == ".text")
    si = next(i for i, s in enumerate(secs) if s["type"] == 2)
    st, strtab = secs[si], secs[secs[si]["link"]]["data"]
    nsym = st["size"] // 16
    syms = []
    for i in range(nsym):
        n, v, sz, info, oth, shn = rd("IIIBBH", st["data"], i * 16)
        e = strtab.index(b"\0", n)
        syms.append(dict(name=bytes(strtab[n:e]).decode(), n=n, value=v, size=sz, info=info, other=oth, shndx=shn))
    drop = []
    for nm in names:
        c = [s for s in syms if s["name"] == nm and 0 < s["shndx"] < 0xFF00 and s["info"] & 0xF in (1, 2)
             and secs[s["shndx"]]["type"] == 1]
        if len(c) != 1:
            sys.exit(f"dropfn: {nm} is not a (unique) function or data object of a PROGBITS section")
        drop.append(c[0])
    # span of a dropped symbol: up to the next symbol start of its section (padding belongs to its predecessor)
    spans = {}
    for sec_i in {s["shndx"] for s in drop}:
        starts = sorted({s["value"] for s in syms if s["shndx"] == sec_i and s["info"] & 0xF in (0, 1, 2) and s["name"]})
        sp = []
        for s in drop:
            if s["shndx"] == sec_i:
                sp.append((s["value"], next((x for x in starts if x > s["value"]), len(secs[sec_i]["data"]))))
        sp.sort()
        for (a0, b0), (a1, b1) in zip(sp, sp[1:]):
            if a1 < b0:
                sys.exit("dropfn: overlapping spans")
        spans[sec_i] = sp

    def new_off(sec_i, o, what):
        shift = 0
        for a, b in spans.get(sec_i, ()):
            if o >= b:
                shift += b - a
            elif o >= a:
                sys.exit(f"dropfn: {what} points into a dropped symbol (section {secs[sec_i]['name']}, offset 0x{o:X})")
        return o - shift

    for sec_i, sp in spans.items():
        out = bytearray()
        pos = 0
        for a, b in sp:
            out += secs[sec_i]["data"][pos:a]
            pos = b
        out += secs[sec_i]["data"][pos:]
        secs[sec_i]["newdata"] = out
    # symbols
    dropped_idx = {id(s) for s in drop}
    undef_info = next((s["info"] for s in syms if s["shndx"] == 0 and s["name"] and s["info"] & 0xF == 2), 0x12)
    for s in syms:
        if id(s) in dropped_idx:
            ty = s["info"] & 0xF
            s["shndx"], s["value"], s["size"], s["info"] = 0, 0, 0, 0x10 | (undef_info & 0xF if ty == 2 else ty)
        elif s["shndx"] in spans:
            s["value"] = new_off(s["shndx"], s["value"], s["name"] or "symbol")
    sec_sym = {i: s["shndx"] for i, s in enumerate(syms) if s["shndx"] in spans and s["info"] & 0xF == 3}
    # relocations
    for i, s in enumerate(secs):
        if s["type"] != 4:      # SHT_RELA
            continue
        tgt = s["info"]
        newd = bytearray()
        for k in range(s["size"] // 12):
            off, info, add = struct.unpack_from(">IIi", s["data"], k * 12)
            symi = info >> 8
            if tgt in spans:
                if any(a <= off < b for a, b in spans[tgt]):
                    continue
                off = new_off(tgt, off, "relocation")
            if symi in sec_sym:
                add = new_off(sec_sym[symi], add, "section-relative reference")
            newd += struct.pack(">IIi", off, info, add)
        s["data"] = newd
    for sec_i in spans:
        secs[sec_i]["data"] = secs[sec_i].pop("newdata")
    st["data"] = bytearray()
    for s in syms:
        st["data"] += struct.pack(">IIIBBH", s["n"], s["value"], s["size"], s["info"], s["other"], s["shndx"])
    # layout
    buf = bytearray(d[:0x34])
    for i, s in enumerate(secs):
        if i == 0 or s["type"] == 0:
            s["new_off"], s["new_size"] = 0, 0
            continue
        al = max(s["align"], 1)
        while len(buf) % al:
            buf.append(0)
        s["new_off"] = len(buf)
        if s["type"] == 8:      # NOBITS keeps its size
            s["new_size"] = s["size"]
        else:
            buf += s["data"]
            s["new_size"] = len(s["data"])
    while len(buf) % 4:
        buf.append(0)
    new_shoff = len(buf)
    for s in secs:
        buf += struct.pack(">10I", s["name_off"], s["type"], s["flags"], s["addr"], s["new_off"], s["new_size"],
                           s["link"], s["info"], s["align"], s["entsize"])
    struct.pack_into(">I", buf, 0x20, new_shoff)
    open(dst, "wb").write(buf)


if __name__ == "__main__":
    main(sys.argv)
