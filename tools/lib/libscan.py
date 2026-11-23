#!/usr/bin/env python3
"""Find FE10 library functions among compiled functions of reference objects.

Usage: tools/lib/libscan.py OBJDIR [--out results.tsv] [--near N]
Exact: same size and same bytes after masking relocated fields (using the
reference object's relocations on both sides). Near: same size, <= N words differ.
"""
import argparse, glob, os, re, struct, sys
sys.path[:0] = [os.path.dirname(os.path.abspath(__file__)), os.path.join(os.path.dirname(os.path.abspath(__file__)), "..")]
import check_func as cf

LO, HI = 0x8028BC54, 0x80360900


def ref_funcs(objdir):
    out = []
    for p in sorted(glob.glob(os.path.join(objdir, "*.o"))):
        try:
            secs, syms, relocs = cf.parse_elf(p)
        except Exception:
            continue
        for s in syms:
            if s["type"] != 2 or s["shndx"] == 0 or s["shndx"] >= 0xFF00 or s["size"] < 4:
                continue
            sec = secs[s["shndx"]]
            if not sec["name"].startswith(".text"):
                continue
            buf = bytearray(sec["data"][s["value"]:s["value"] + s["size"]])
            masks = {}
            for off, rtype, *_ in relocs.get(s["shndx"], []):
                rel = off - s["value"]
                if 0 <= rel < len(buf):
                    wo = rel - 2 if rtype in (4, 5, 6) else rel & ~3
                    if wo >= 0 and wo + 4 <= len(buf):
                        masks[wo] = masks.get(wo, 0) | cf.RELOC_MASK.get(rtype, 0xFFFFFFFF)
            out.append((os.path.basename(p)[:-2], s["name"], bytes(buf), masks))
    return out


def apply(b, masks):
    b = bytearray(b)
    for wo, m in masks.items():
        w, = struct.unpack(">I", b[wo:wo + 4])
        struct.pack_into(">I", b, wo, w & ~m)
    return bytes(b)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("objdir")
    ap.add_argument("--out", default="")
    ap.add_argument("--near", type=int, default=0)
    a = ap.parse_args()
    syms = cf.load_symbols()
    read = cf.dol_reader()
    targets = [(n, ad, sz, read(ad, sz)) for n, (ad, sz) in syms.items() if LO <= ad < HI and n.startswith("fn_")]
    refs = ref_funcs(a.objdir)
    bysize = {}
    for r in refs:
        bysize.setdefault(len(r[2]), []).append(r)
    rows, found = [], set()
    for n, ad, sz, data in sorted(targets, key=lambda t: t[1]):
        for unit, name, rb, masks in bysize.get(sz, []):
            if apply(rb, masks) == apply(data, masks):
                rows.append((n, ad, sz, "EXACT", 0, unit, name))
                found.add(n)
        if n in found or not a.near:
            continue
        best = None
        for unit, name, rb, masks in bysize.get(sz, []):
            x, y = apply(rb, masks), apply(data, masks)
            d = sum(1 for i in range(0, sz, 4) if x[i:i + 4] != y[i:i + 4])
            if d <= max(a.near, sz // 4 * 0.3) and (best is None or d < best[0]):
                best = (d, unit, name)
        if best:
            rows.append((n, ad, sz, "NEAR", best[0], best[1], best[2]))
    with open(a.out or "/dev/stdout", "w") as f:
        for r in rows:
            f.write("\t".join(map(str, (r[0], f"{r[1]:08X}", r[2], r[3], r[4], r[5], r[6]))) + "\n")
    ex = {r[0] for r in rows if r[3] == "EXACT"}
    print(f"targets {len(targets)}, refs {len(refs)}, exact {len(ex)} functions ({sum(t[2] for t in targets if t[0] in ex)} of {sum(t[2] for t in targets)} bytes)", file=sys.stderr)


if __name__ == "__main__":
    main()
