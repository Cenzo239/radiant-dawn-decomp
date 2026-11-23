#!/usr/bin/env python3
"""Place reference objects' text sections into main.dol by voting on function matches.

Usage: tools/lib/place.py OBJDIR --out placement.json
For each text section of each object, every function votes (address - offset) for
the section base; the base covering the most matched bytes wins.
"""
import argparse, glob, json, os, struct, sys
sys.path[:0] = [os.path.dirname(os.path.abspath(__file__)), os.path.join(os.path.dirname(os.path.abspath(__file__)), "..")]
import check_func as cf
from libscan import apply

LO, HI = 0x8028BC54, 0x80360900


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("objdir")
    ap.add_argument("--out", required=True)
    a = ap.parse_args()
    read = cf.dol_reader()
    text = read(LO, HI - LO)
    words = {}
    for i in range(0, len(text), 4):
        words.setdefault(text[i:i + 4], []).append(i)
    res = []
    for p in sorted(glob.glob(os.path.join(a.objdir, "*.o"))):
        try:
            secs, syms, relocs = cf.parse_elf(p)
        except Exception:
            continue
        unit = os.path.basename(p)[:-2]
        for si, sec in enumerate(secs):
            if not sec["name"].startswith(".text") or sec["size"] < 4:
                continue
            buf = sec["data"]
            fns = [s for s in syms if s["shndx"] == si and s["type"] == 2 and s["size"] >= 4]
            if not fns:
                continue
            masks_all = {}
            for off, rtype, *_ in relocs.get(si, []):
                wo = off - 2 if rtype in (4, 5, 6) else off & ~3
                if 0 <= wo and wo + 4 <= len(buf):
                    masks_all[wo] = masks_all.get(wo, 0) | cf.RELOC_MASK.get(rtype, 0xFFFFFFFF)
            votes = {}
            fmatch = []
            for f in fns:
                fb = buf[f["value"]:f["value"] + f["size"]]
                fm = {wo - f["value"]: m for wo, m in masks_all.items() if f["value"] <= wo < f["value"] + f["size"]}
                mb = apply(fb, fm)
                # anchor: first unmasked word that exists
                anchors = [i for i in range(0, len(fb), 4) if i not in fm and fb[i:i + 4] in words]
                if not anchors:
                    continue
                ai = min(anchors, key=lambda i: len(words[fb[i:i + 4]]))
                hits = []
                for pos in words[fb[ai:ai + 4]]:
                    st = pos - ai
                    if st < 0 or st + len(fb) > len(text):
                        continue
                    if apply(text[st:st + len(fb)], fm) == mb:
                        hits.append(LO + st)
                for h in hits:
                    votes[h - f["value"]] = votes.get(h - f["value"], 0) + f["size"]
                fmatch.append((f, hits))
            if not votes:
                continue
            base, score = max(votes.items(), key=lambda kv: kv[1])
            placed = []
            for f, hits in fmatch:
                if base + f["value"] in hits:
                    placed.append([f["name"], base + f["value"], f["size"]])
            total = sum(f["size"] for f in fns)
            res.append({"unit": unit, "sec": si, "secname": sec["name"], "secsize": len(buf), "base": base,
                        "score": score, "total": total, "nfn": len(fns), "nplaced": len(placed), "placed": placed})
    json.dump(res, open(a.out, "w"), indent=0)
    good = [r for r in res if r["score"] * 2 >= r["total"] and r["score"] >= 8]
    print(f"{len(res)} sections placed-or-voted; {len(good)} with >=50% coverage; bytes {sum(r['score'] for r in good)}", file=sys.stderr)


if __name__ == "__main__":
    main()
