#!/usr/bin/env python3
"""Rank near-miss reference functions for unverified library functions.

Usage: tools/lib/fuzzy.py OBJDIR [--min-size 32] [--out fuzzy.tsv] [--lo ADDR --hi ADDR]
Similarity is difflib's ratio over instruction words with relocated fields masked and
registers ignored (opcode + low-level shape), so version differences show as ~0.8-0.99.
"""
import argparse, difflib, glob, json, os, struct, sys
sys.path[:0] = [os.path.dirname(os.path.abspath(__file__)), os.path.join(os.path.dirname(os.path.abspath(__file__)), "..")]
import check_func as cf
from libscan import ref_funcs, apply

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))


def shape(b, masks):
    b = apply(b, masks)
    out = []
    for i in range(0, len(b), 4):
        w, = struct.unpack(">I", b[i:i + 4])
        op = w >> 26
        # keep opcode and (for opcode 31/19/63/59) the extended opcode; drop register fields
        if op in (31, 19, 63, 59, 4):
            out.append((op, (w >> 1) & 0x3FF))
        elif op in (14, 15, 24, 25, 26, 27, 28, 29):
            out.append((op, w & 0xFFFF if (w >> 21) & 0x1F == 0 else 0))
        else:
            out.append((op, 0))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("objdir")
    ap.add_argument("--min-size", type=int, default=32)
    ap.add_argument("--out", default="")
    ap.add_argument("--lo", type=lambda x: int(x, 16), default=0x8028BC54)
    ap.add_argument("--hi", type=lambda x: int(x, 16), default=0x80360900)
    a = ap.parse_args()
    v = json.load(open(os.path.join(ROOT, "lib/verified.json")))
    have = {x for d in v.values() for x in d.values()}
    syms = cf.load_symbols()
    read = cf.dol_reader()
    targets = [(n, ad, sz) for n, (ad, sz) in syms.items()
               if a.lo <= ad < a.hi and n.startswith("fn_") and ad not in have and sz >= a.min_size]
    refs = [(u, n, shape(b, m), len(b)) for u, n, b, m in ref_funcs(a.objdir) if len(b) >= a.min_size]
    byop = []
    from collections import Counter
    for u, n, sh, sz in refs:
        byop.append(Counter(o for o, _ in sh))
    rows = []
    for n, ad, sz in sorted(targets, key=lambda t: -t[2]):
        sh = shape(read(ad, sz), {})
        c = Counter(o for o, _ in sh)
        cands = []
        for i, (u, rn, rsh, rsz) in enumerate(refs):
            if not (0.6 * sz <= rsz <= 1.7 * sz):
                continue
            ov = sum((c & byop[i]).values()) / max(len(sh), len(rsh))
            if ov > 0.75:
                cands.append((ov, i))
        cands.sort(reverse=True)
        best = None
        for _, i in cands[:25]:
            u, rn, rsh, rsz = refs[i]
            r = difflib.SequenceMatcher(None, sh, rsh, autojunk=False).ratio()
            if best is None or r > best[0]:
                best = (r, u, rn, rsz)
        if best and best[0] > 0.6:
            rows.append((n, f"{ad:08X}", sz, f"{best[0]:.3f}", best[1], best[2], best[3]))
    with open(a.out or "/dev/stdout", "w") as f:
        for r in rows:
            f.write("\t".join(map(str, r)) + "\n")
    print(f"{len(targets)} unverified targets, {len(rows)} with a >0.6 candidate", file=sys.stderr)


if __name__ == "__main__":
    main()
