#!/usr/bin/env python3
"""Convert a DOL plus a dtk symbols.txt/splits.txt into a symbolised ELF for Ghidra.

Usage: dol2elf.py main.dol config/RFEE01/splits.txt config/RFEE01/symbols.txt out.elf
"""
import re
import struct
import sys


def read_dol(path):
    data = open(path, "rb").read()
    offs = struct.unpack(">18I", data[0x00:0x48])
    addrs = struct.unpack(">18I", data[0x48:0x90])
    sizes = struct.unpack(">18I", data[0x90:0xD8])
    bss_addr, bss_size, entry = struct.unpack(">3I", data[0xD8:0xE4])
    segs = []
    for i in range(18):
        if sizes[i]:
            segs.append((addrs[i], data[offs[i]:offs[i] + sizes[i]], i < 7))
    return segs, bss_addr, bss_size, entry


def read_section_names(splits_path, symbols_path):
    """Section names in DOL order, taken from the Sections: block of splits.txt."""
    names, kinds = [], {}
    in_sections = False
    for line in open(splits_path):
        if line.startswith("Sections:"):
            in_sections = True
            continue
        if in_sections:
            m = re.match(r"\s+(\S+)\s+type:(\S+)", line)
            if not m:
                break
            names.append(m.group(1))
            kinds[m.group(1)] = m.group(2)
    # Ranges of each section, from the symbols that live in it.
    return names, kinds


SYM_RE = re.compile(r"^(\S+) = (\S+):0x([0-9A-Fa-f]+); // (.*)$")


def read_symbols(path):
    syms = []
    for line in open(path):
        m = SYM_RE.match(line.strip())
        if not m:
            continue
        name, sect, addr, attrs = m.group(1), m.group(2), int(m.group(3), 16), m.group(4)
        size = 0
        sm = re.search(r"size:0x([0-9A-Fa-f]+)", attrs)
        if sm:
            size = int(sm.group(1), 16)
        is_func = "type:function" in attrs
        is_local = "scope:local" in attrs
        syms.append((name, sect, addr, size, is_func, is_local))
    return syms


def main():
    dol_path, splits_path, symbols_path, out_path = sys.argv[1:5]
    segs, bss_addr, bss_size, entry = read_dol(dol_path)
    names, kinds = read_section_names(splits_path, symbols_path)
    syms = read_symbols(symbols_path)

    # Find each bss-type section's extent from symbol addresses and the DOL bss range.
    loaded = [n for n in names if kinds[n] != "bss"]
    bss_names = [n for n in names if kinds[n] == "bss"]
    assert len(loaded) == len(segs), (loaded, len(segs))
    sections = []  # (name, addr, data or None, size, flags, is_code)
    for name, (addr, blob, is_code) in zip(loaded, sorted(segs, key=lambda s: s[0])):
        sections.append([name, addr, blob, len(blob), is_code])
    # bss sections sit in gaps between loaded sections inside [bss_addr, bss_addr+bss_size).
    bss_end = bss_addr + bss_size
    gaps = []
    cursor = bss_addr
    for s in sorted(sections, key=lambda s: s[1]):
        if s[1] + s[3] <= bss_addr or s[1] >= bss_end:
            continue
        if s[1] > cursor:
            gaps.append((cursor, s[1]))
        cursor = max(cursor, s[1] + s[3])
    if cursor < bss_end:
        gaps.append((cursor, bss_end))
    assert len(gaps) == len(bss_names), (gaps, bss_names)
    for name, (start, end) in zip(bss_names, gaps):
        sections.append([name, start, None, end - start, False])
    sections.sort(key=lambda s: s[1])
    sect_index = {s[0]: i + 1 for i, s in enumerate(sections)}

    # String tables.
    shstr = bytearray(b"\0")
    strtab = bytearray(b"\0")

    def add(tab, s):
        off = len(tab)
        tab += s.encode() + b"\0"
        return off

    # Build symtab: locals first, then globals.
    STT_OBJECT, STT_FUNC = 1, 2
    entries_local, entries_global = [], []
    for name, sect, addr, size, is_func, is_local in syms:
        if sect not in sect_index:
            continue
        info_type = STT_FUNC if is_func else STT_OBJECT
        rec = (add(strtab, name), addr, size, info_type, sect_index[sect])
        (entries_local if is_local else entries_global).append(rec)
    symtab = bytearray(16)  # null symbol
    for bind, recs in ((0, entries_local), (1, entries_global)):
        for name_off, addr, size, typ, shndx in recs:
            symtab += struct.pack(">IIIBBH", name_off, addr, size, (bind << 4) | typ, 0, shndx)
    first_global = 1 + len(entries_local)

    # Layout: ELF header, program headers, section data, shstrtab, symtab, strtab, section headers.
    ehsize, phentsize, shentsize = 52, 32, 40
    progbits = [s for s in sections if s[2] is not None]
    phnum = len(sections)
    off = ehsize + phentsize * phnum
    body = bytearray()
    data_offsets = {}
    for s in progbits:
        pad = (-(off + len(body))) % 32
        body += b"\0" * pad
        data_offsets[s[0]] = off + len(body)
        body += s[2]
    sh_names = {s[0]: add(shstr, s[0]) for s in sections}
    symtab_name = add(shstr, ".symtab")
    strtab_name = add(shstr, ".strtab")
    shstrtab_name = add(shstr, ".shstrtab")
    pad = (-(off + len(body))) % 4
    body += b"\0" * pad
    symtab_off = off + len(body)
    body += symtab
    strtab_off = off + len(body)
    body += strtab
    shstr_off = off + len(body)
    body += shstr
    pad = (-(off + len(body))) % 4
    body += b"\0" * pad
    shoff = off + len(body)
    n_sections = 1 + len(sections) + 3

    out = bytearray()
    out += b"\x7fELF" + bytes([1, 2, 1, 0]) + b"\0" * 8
    out += struct.pack(">HHIIIIIHHHHHH", 2, 20, 1, entry, ehsize, shoff, 0x80000000,
                       ehsize, phentsize, phnum, shentsize, n_sections, n_sections - 1)
    for s in sections:
        name, addr, blob, size, is_code = s
        flags = 5 if is_code else 6  # R+X or R+W
        if blob is None:
            out += struct.pack(">8I", 1, 0, addr, addr, 0, size, flags, 32)
        else:
            out += struct.pack(">8I", 1, data_offsets[name], addr, addr, size, size, flags, 32)
    out += body
    # Section headers.
    out += b"\0" * shentsize
    SHF_WRITE, SHF_ALLOC, SHF_EXEC = 1, 2, 4
    for s in sections:
        name, addr, blob, size, is_code = s
        if blob is None:
            out += struct.pack(">10I", sh_names[name], 8, SHF_ALLOC | SHF_WRITE, addr, 0, size, 0, 0, 32, 0)
        else:
            fl = SHF_ALLOC | (SHF_EXEC if is_code else 0) | (SHF_WRITE if kinds[name] == "data" else 0)
            out += struct.pack(">10I", sh_names[name], 1, fl, addr, data_offsets[name], size, 0, 0, 32, 0)
    strtab_index = 1 + len(sections) + 1
    out += struct.pack(">10I", symtab_name, 2, 0, 0, symtab_off, len(symtab), strtab_index, first_global, 4, 16)
    out += struct.pack(">10I", strtab_name, 3, 0, 0, strtab_off, len(strtab), 0, 0, 1, 0)
    out += struct.pack(">10I", shstrtab_name, 3, 0, 0, shstr_off, len(shstr), 0, 0, 1, 0)
    open(out_path, "wb").write(out)
    print(f"wrote {out_path}: {len(sections)} sections, {len(entries_local) + len(entries_global)} symbols")


if __name__ == "__main__":
    main()
