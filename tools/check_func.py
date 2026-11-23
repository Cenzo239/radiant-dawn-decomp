#!/usr/bin/env python3
"""Compile one C/C++ file with MWCC and compare each function against main.dol.

Functions are matched to the original by name through config/RFEE01/symbols.txt,
so name them as in symbols.txt (e.g. fn_800068A0). Bytes covered by relocations
are masked, so calls and data references only need to point at the right symbol.

Usage:
  tools/check_func.py src/foo.c [--cc GC/3.0a5.2] [--flags "-O4,p ..."] [-v]
  tools/check_func.py src/foo.cpp --symbol-map src/foo.symbols.json --strict-references

Exit code is 0 only when every function in the object that exists in
symbols.txt matches under the checks performed. Unknown reference targets are
reported; --strict-references makes them fail the check. A symbol map associates
object-local names with existing symbols.txt names without overriding originals.
"""
import argparse
import json
import os
import re
import shlex
import struct
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DOL = os.path.join(ROOT, "orig/RFEE01/sys/main.dol")
SYMBOLS = os.path.join(ROOT, "config/RFEE01/symbols.txt")
# Library symbols are renamed in symbols.txt by tools/build/gen_config.py; per-function sources
# use the fn_/lbl_ names, which symbols.base.txt keeps.
if os.path.exists(os.path.join(ROOT, "config/RFEE01/symbols.base.txt")):
    SYMBOLS = os.path.join(ROOT, "config/RFEE01/symbols.base.txt")
WIBO = os.path.join(ROOT, "tools/wibo_guard")  # wibo with a machine-wide limit and hang watchdog

DEFAULT_FLAGS = (
    "-nodefaults -proc gekko -align powerpc -enum int -fp hardware "
    "-Cpp_exceptions off -O4,p -inline auto -pragma \"cats off\" "
    "-pragma \"warn_notinlined off\" -maxerrors 1 -nosyspath -RTTI off "
    "-fp_contract on -str reuse -multibyte -i include -i src"
)


def load_all_symbol_addresses():
    addrs = {}
    pat = re.compile(r"^(\S+) = \S+:0x([0-9A-Fa-f]+);")
    for line in open(SYMBOLS):
        m = pat.match(line)
        if m:
            addrs[m.group(1)] = int(m.group(2), 16)
    return addrs


def load_symbols():
    syms = {}
    pat = re.compile(r"^(\S+) = \.text:0x([0-9A-Fa-f]+); // type:function size:0x([0-9A-Fa-f]+)")
    for line in open(SYMBOLS):
        m = pat.match(line)
        if m:
            syms[m.group(1)] = (int(m.group(2), 16), int(m.group(3), 16))
    return syms


def dol_reader():
    data = open(DOL, "rb").read()
    offs = struct.unpack(">18I", data[0:0x48])
    addrs = struct.unpack(">18I", data[0x48:0x90])
    sizes = struct.unpack(">18I", data[0x90:0xD8])

    def read(addr, size):
        for o, a, s in zip(offs, addrs, sizes):
            if s and a <= addr and addr + size <= a + s:
                return data[o + addr - a:o + addr - a + size]
        raise KeyError(hex(addr))
    return read


def parse_elf(path):
    d = open(path, "rb").read()
    shoff, = struct.unpack(">I", d[0x20:0x24])
    shentsize, shnum, shstrndx = struct.unpack(">HHH", d[0x2E:0x34])
    shdrs = [struct.unpack(">10I", d[shoff + i * shentsize:shoff + (i + 1) * shentsize]) for i in range(shnum)]
    strsec = shdrs[shstrndx]

    def cstr(blob, off):
        return blob[off:blob.index(b"\0", off)].decode()
    shstr = d[strsec[4]:strsec[4] + strsec[5]]
    secs = []
    for h in shdrs:
        secs.append({"name": cstr(shstr, h[0]), "type": h[1], "off": h[4], "size": h[5],
                     "link": h[6], "info": h[7], "data": d[h[4]:h[4] + h[5]]})
    symtab = next(s for s in secs if s["type"] == 2)
    strtab = secs[symtab["link"]]["data"]
    syms = []
    for i in range(symtab["size"] // 16):
        name, value, size, info, other, shndx = struct.unpack(">IIIBBH", symtab["data"][i * 16:(i + 1) * 16])
        syms.append({"name": cstr(strtab, name), "value": value, "size": size, "type": info & 0xF, "shndx": shndx})
    relocs = {}  # section index -> list of (offset, type, symbol name)
    for s in secs:
        if s["type"] == 4:
            lst = relocs.setdefault(s["info"], [])
            for i in range(s["size"] // 12):
                off, info, addend = struct.unpack(">IIi", s["data"][i * 12:(i + 1) * 12])
                lst.append((off, info & 0xFF, syms[info >> 8]["name"], addend, syms[info >> 8]))
    return secs, syms, relocs


# Bits of a 32-bit instruction word that each PPC relocation type rewrites.
RELOC_MASK = {
    1: 0xFFFFFFFF,  # ADDR32
    4: 0x0000FFFF, 5: 0x0000FFFF, 6: 0x0000FFFF,  # ADDR16_LO/HI/HA
    10: 0x03FFFFFC,  # REL24
    11: 0x0000FFFC,  # REL14
    109: 0x001FFFFF,  # EMB_SDA21
}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("source")
    ap.add_argument("--cc", default="GC/3.0a5.2")
    ap.add_argument("--flags", default=DEFAULT_FLAGS)
    ap.add_argument("--extra", default="", help="flags appended to --flags")
    ap.add_argument("--symbol-map", help="JSON mapping object-local names to symbols.txt names")
    ap.add_argument("--strict-references", action="store_true",
                    help="fail if any referenced symbol has no verified address")
    ap.add_argument("-v", "--verbose", action="store_true")
    args = ap.parse_args()

    cc = os.path.join(ROOT, "build/compilers", args.cc, "mwcceppc.exe")
    with tempfile.TemporaryDirectory() as tmp:
        obj = os.path.join(tmp, "out.o")
        cmd = [WIBO, cc, *shlex.split(args.flags), *shlex.split(args.extra), "-c", args.source, "-o", obj]
        r = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True)
        if r.returncode != 0 or not os.path.exists(obj):
            print(r.stdout + r.stderr)
            print("COMPILE FAILED")
            return 2
        secs, syms, relocs = parse_elf(obj)

    orig_syms = load_symbols()
    all_addrs = load_all_symbol_addresses()
    if args.symbol_map:
        try:
            with open(args.symbol_map) as f:
                aliases = json.load(f)
            if not isinstance(aliases, dict):
                raise ValueError("expected an object mapping local names to original symbols")
            object_names = {s["name"] for s in syms}
            resolved = {}
            for local, original in aliases.items():
                if local in all_addrs or local not in object_names:
                    raise ValueError(f"{local!r} must be an object-local symbol absent from symbols.txt")
                if not isinstance(original, str) or original not in all_addrs:
                    raise ValueError(f"unknown original symbol for {local!r}: {original!r}")
                resolved[local] = all_addrs[original]
            all_addrs.update(resolved)
        except (OSError, ValueError) as e:
            ap.error(f"invalid symbol map: {e}")
    read = dol_reader()
    SDA_BASE, SDA2_BASE = 0x804CA040 + 0x8000, 0x804CCA60 + 0x8000
    unverified = set()
    constants_checked = [0]
    all_ok = True
    checked = 0
    for s in syms:
        if s["type"] != 2 or s["shndx"] == 0 or s["shndx"] >= 0xFF00:
            continue
        sec = secs[s["shndx"]]
        if not sec["name"].startswith(".text"):
            continue
        name = s["name"]
        if name not in orig_syms:
            print(f"  SKIP {name}: not in symbols.txt")
            continue
        addr, osize = orig_syms[name]
        ours = bytearray(sec["data"][s["value"]:s["value"] + s["size"]])
        theirs = bytearray(read(addr, osize))
        checked += 1
        if len(ours) != len(theirs):
            all_ok = False
            print(f"  DIFF {name}: size 0x{len(ours):X}, want 0x{len(theirs):X}")
        # Check that each relocation points where the original does.
        bad_targets = []
        pending_ha = {}
        for off, rtype, target, addend, tsym in relocs.get(s["shndx"], []):
            rel = off - s["value"]
            if not (0 <= rel < len(theirs)):
                continue
            want_addr = None
            if rtype == 10:  # REL24 branch
                w, = struct.unpack(">I", theirs[rel:rel + 4])
                disp = w & 0x03FFFFFC
                if disp & 0x02000000:
                    disp -= 0x04000000
                want_addr = addr + rel + disp
            elif rtype == 109:  # SDA21
                w, = struct.unpack(">I", theirs[rel:rel + 4])
                ra, simm = (w >> 16) & 0x1F, w & 0xFFFF
                if simm & 0x8000:
                    simm -= 0x10000
                base = {13: SDA_BASE, 2: SDA2_BASE, 0: 0}.get(ra)
                if base is not None:
                    want_addr = base + simm
            elif rtype == 6:  # ADDR16_HA
                hi, = struct.unpack(">H", theirs[rel:rel + 2])
                pending_ha[(target, addend)] = hi
                continue
            elif rtype == 4:  # ADDR16_LO
                lo, = struct.unpack(">h", theirs[rel:rel + 2])
                hi = pending_ha.get((target, addend))
                if hi is not None:
                    want_addr = ((hi << 16) + lo) & 0xFFFFFFFF
            if want_addr is None:
                continue
            tsec = secs[tsym["shndx"]] if 0 < tsym["shndx"] < len(secs) else None
            if tsec is not None and not tsec["name"].startswith(".text") and tsec["type"] != 8:
                # Data defined in this object (float constants, strings, statics):
                # compare the referenced bytes with the original's.
                start = tsym["value"] + addend
                blob = tsec["data"]
                if tsym["name"].startswith("...data.") and tsym["size"] == 0:
                    # MWCC's pooled-static base has no size, although the
                    # individual objects do. Validate its whole pool rather
                    # than just the first word at the base.
                    end = min((other["value"] for other in syms
                               if other["shndx"] == tsym["shndx"]
                               and other["name"].startswith("...data.")
                               and other["value"] > tsym["value"]), default=len(blob))
                elif tsym["name"].startswith("@stringBase") or tsec["name"].startswith(".rodata") and b"\0" in blob[start:start + 256] and tsym["size"] == 0:
                    end = blob.index(b"\0", start) + 1
                else:
                    n = (tsym["size"] - addend) if tsym["size"] > addend else 4
                    end = start + n
                mine = bytes(blob[start:end])
                table_relocs = [r for r in relocs.get(tsym["shndx"], []) if start <= r[0] < end]
                if table_relocs:
                    # Check pointer targets and the ordinary bytes between them
                    # (for example, script opcodes in a mixed command table).
                    try:
                        table_orig = bytearray(read(want_addr, len(mine)))
                    except KeyError:
                        table_orig = None
                    table_mine = bytearray(mine)
                    ok = table_orig is not None
                    for roff, rt, _rn, radd, rsym in table_relocs:
                        entry = roff - start
                        if rt != 1 or entry + 4 > len(table_mine):
                            # These tables use R_PPC_ADDR32. Do not silently
                            # treat an unsupported relocation as a whole pointer.
                            ok = False
                            continue
                        try:
                            orig_entry, = struct.unpack(">I", read(want_addr + roff - start, 4))
                        except KeyError:
                            ok = False
                            break
                        if rsym["name"] in all_addrs:
                            # Named targets (including other functions in this
                            # object, whose jump tables share the data pool).
                            ok &= all_addrs[rsym["name"]] + radd == orig_entry
                        elif rsym["shndx"] == s["shndx"]:
                            ours_off = rsym["value"] + radd - s["value"]
                            ok &= orig_entry - addr == ours_off
                        else:
                            unverified.add(rsym["name"])
                        if table_orig is not None:
                            table_mine[entry:entry + 4] = b"\0" * 4
                            table_orig[entry:entry + 4] = b"\0" * 4
                    ok &= table_orig is not None and table_mine == table_orig
                    if ok:
                        constants_checked[0] += 1
                    else:
                        bad_targets.append(f"+0x{rel:03X} -> {target}: table entries differ from original at 0x{want_addr:08X}")
                    continue
                try:
                    orig = read(want_addr, len(mine))
                except KeyError:
                    orig = None
                if orig != mine:
                    bad_targets.append(f"+0x{rel:03X} -> {target}+0x{addend:X}: constant {mine.hex()} but original has {orig.hex() if orig else '?'} at 0x{want_addr:08X}")
                else:
                    constants_checked[0] += 1
                continue
            if target not in all_addrs:
                unverified.add(target)
                continue
            if all_addrs[target] + addend != want_addr:
                bad_targets.append(f"+0x{rel:03X} -> {target}+0x{addend:X} but original uses 0x{want_addr:08X}")
        if bad_targets:
            all_ok = False
            print(f"  DIFF {name}: {len(bad_targets)} wrong reference(s)")
            for b in bad_targets[:20]:
                print(f"       {b}")
        # Mask relocated fields in both.
        for off, rtype, _target, _addend, _tsym in relocs.get(s["shndx"], []):
            rel = off - s["value"]
            if 0 <= rel < len(ours):
                word_off = rel & ~3
                mask = RELOC_MASK.get(rtype, 0xFFFFFFFF)
                if rtype in (4, 5, 6):  # 16-bit fields point at the halfword
                    word_off = rel - 2
                for buf in (ours, theirs):
                    if word_off + 4 <= len(buf):
                        w, = struct.unpack(">I", buf[word_off:word_off + 4])
                        struct.pack_into(">I", buf, word_off, w & ~mask)
        n = min(len(ours), len(theirs)) // 4
        bad = [i for i in range(n) if ours[i * 4:i * 4 + 4] != theirs[i * 4:i * 4 + 4]]
        if len(ours) == len(theirs) and not bad and not bad_targets:
            print(f"  OK   {name} (0x{osize:X} bytes)")
        else:
            all_ok = False
            print(f"  DIFF {name}: {len(bad)} of {n} words differ")
            if args.verbose:
                for i in bad[:40]:
                    print(f"       +0x{i*4:03X} {addr + i*4:08X}: ours {ours[i*4:i*4+4].hex()} want {theirs[i*4:i*4+4].hex()}")
    if constants_checked[0]:
        print(f"  constants/strings verified by value: {constants_checked[0]}")
    if unverified:
        print("  note: references to symbols not in symbols.txt were not checked: " + ", ".join(sorted(unverified)))
        if args.strict_references:
            all_ok = False
    if checked == 0:
        print("no functions from symbols.txt found in object")
        return 1
    print("MATCH" if all_ok else "MISMATCH")
    return 0 if all_ok else 1


if __name__ == "__main__":
    sys.exit(main())
