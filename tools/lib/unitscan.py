#!/usr/bin/env python3
"""Locate whole compiled .text sections of reference objects inside main.dol.

Usage: tools/lib/unitscan.py OBJDIR [--out units.tsv]
"""
import argparse, glob, os, struct, sys
sys.path[:0] = [os.path.dirname(os.path.abspath(__file__)), os.path.join(os.path.dirname(os.path.abspath(__file__)), "..")]
import check_func as cf
from libscan import apply

LO, HI = 0x8028BC54, 0x80360900


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("objdir")
    ap.add_argument("--out", default="")
    a = ap.parse_args()
    read = cf.dol_reader()
    text = read(LO, HI - LO)
    words = {}
    for i in range(0, len(text), 4):
        words.setdefault(text[i:i + 4], []).append(i)
    rows = []
    for p in sorted(glob.glob(os.path.join(a.objdir, "*.o"))):
        try:
            secs, syms, relocs = cf.parse_elf(p)
        except Exception:
            continue
        unit = os.path.basename(p)[:-2]
        for si, sec in enumerate(secs):
            if not sec["name"].startswith(".text") or sec["size"] < 8:
                continue
            buf = sec["data"]
            masks = {}
            for off, rtype, *_ in relocs.get(si, []):
                wo = off - 2 if rtype in (4, 5, 6) else off & ~3
                if 0 <= wo and wo + 4 <= len(buf):
                    masks[wo] = masks.get(wo, 0) | cf.RELOC_MASK.get(rtype, 0xFFFFFFFF)
            mb = apply(buf, masks)
            # anchor on the rarest fully-unmasked word
            cand = [(len(words.get(buf[i:i + 4], [])), i) for i in range(0, len(buf), 4) if i not in masks]
            cand = [c for c in cand if c[0] > 0]
            if not cand:
                rows.append((unit, si, len(buf), "-", len(buf) // 4, "no-anchor"))
                continue
            _, ai = min(cand)
            best = None
            for pos in words[buf[ai:ai + 4]]:
                start = pos - ai
                if start < 0 or start + len(buf) > len(text):
                    continue
                other = apply(text[start:start + len(buf)], masks)
                d = sum(1 for i in range(0, len(buf), 4) if other[i:i + 4] != mb[i:i + 4])
                if best is None or d < best[0]:
                    best = (d, start)
                    if d == 0:
                        break
            if best is None:
                rows.append((unit, si, len(buf), "-", len(buf) // 4, "nopos"))
            else:
                rows.append((unit, si, len(buf), f"{LO + best[1]:08X}", best[0], "EXACT" if best[0] == 0 else "PART"))
    with open(a.out or "/dev/stdout", "w") as f:
        for r in rows:
            f.write("\t".join(map(str, r)) + "\n")
    ex = [r for r in rows if r[5] == "EXACT" and r[2] >= 8]
    print(f"sections {len(rows)}, exact {len(ex)} ({sum(r[2] for r in ex)} bytes)", file=sys.stderr)


if __name__ == "__main__":
    main()
