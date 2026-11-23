#!/usr/bin/env python3
"""Build lib/map.json from a placement (tools/lib/place.py) of compiled reference objects.

Usage: tools/lib/mkmap.py OBJDIR PLACE.json --out lib/map.json [--min-score 24]

map.json:
  sources[path] = {unit, functions: {name: [addr, size, "ok"|"diff"]}}
  symbols[name] = addr          (learned from relocations of matched functions)
  conflicts[name] = [addrs]
"""
import argparse, json, os, struct, sys
sys.path[:0] = [os.path.dirname(os.path.abspath(__file__)), os.path.join(os.path.dirname(os.path.abspath(__file__)), "..")]
import check_func as cf

SDA, SDA2 = 0x804CA040 + 0x8000, 0x804CCA60 + 0x8000


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("objdir")
    ap.add_argument("place")
    ap.add_argument("--out", required=True)
    ap.add_argument("--min-score", type=int, default=24)
    ap.add_argument("--min-big", type=int, default=256)
    a = ap.parse_args()
    man = json.load(open(os.path.join(a.objdir, "manifest.json")))
    unit2path = {v["unit"][:-2]: k for k, v in man.items()}
    place = json.load(open(a.place))
    read = cf.dol_reader()
    cand = [p for p in place if p["score"] >= a.min_score and (p["score"] * 2 >= p["total"] or p["score"] >= a.min_big)]
    cand.sort(key=lambda p: -p["score"])
    claimed = []  # (start, end)

    def free(s, e):
        return all(e <= cs or s >= ce for cs, ce in claimed)

    sources = {}
    symbols, conflicts = {}, {}
    for p in cand:
        path = unit2path.get(p["unit"])
        if path is None:
            continue
        ok = []
        for name, addr, size in p["placed"]:
            if free(addr, addr + size):
                ok.append((name, addr, size))
        if (sum(s for _, _, s in ok) * 2 < p["total"] and sum(s for _, _, s in ok) < a.min_big) or sum(s for _, _, s in ok) < a.min_score:
            continue
        for _, ad, sz in ok:
            claimed.append((ad, ad + sz))
        ent = sources.setdefault(path, {"unit": p["unit"], "functions": {}})
        for name, ad, sz in ok:
            ent["functions"][name] = [ad, sz, "ok"]
        ent.setdefault("sections", []).append({"base": p["base"], "size": p["secsize"], "name": p["secname"], "idx": p["sec"]})

    # exact matches elsewhere near a claimed section (functions that shifted)
    import glob
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    from libscan import apply
    LO, HI = 0x8028BC54, 0x80360900
    text = read(LO, HI - LO)
    words = {}
    for i in range(0, len(text), 4):
        words.setdefault(text[i:i + 4], []).append(i)
    order = {"ogws": 0, "wii-ipl": 1, "petari": 2}
    for path in sorted(unit2path.values(), key=lambda k: (order.get(k.split("/")[0], 9), k)):
        unit = man[path]["unit"][:-2]
        if not os.path.exists(os.path.join(a.objdir, unit + ".o")):
            continue
        ent = sources.get(path) or {"unit": unit, "functions": {}, "sections": []}
        try:
            secs, syms, relocs = cf.parse_elf(os.path.join(a.objdir, unit + ".o"))
        except Exception:
            continue
        lo, hi = 0, 1 << 32
        nb = len(ent["functions"])
        for si, sec in enumerate(secs):
            if not sec["name"].startswith(".text"):
                continue
            for s_ in syms:
                if s_["shndx"] != si or s_["type"] != 2 or s_["size"] < 12 or s_["name"] in ent["functions"]:
                    continue
                fb = bytes(sec["data"][s_["value"]:s_["value"] + s_["size"]])
                fm = {}
                for off, rtype, *_ in relocs.get(si, []):
                    if s_["value"] <= off < s_["value"] + s_["size"]:
                        wo = off - 2 if rtype in (4, 5, 6) else off & ~3
                        fm[wo - s_["value"]] = fm.get(wo - s_["value"], 0) | cf.RELOC_MASK.get(rtype, 0xFFFFFFFF)
                mb = apply(fb, fm)
                anchors = [i for i in range(0, len(fb), 4) if i not in fm and fb[i:i + 4] in words]
                if not anchors:
                    continue
                ai = min(anchors, key=lambda i: len(words[fb[i:i + 4]]))
                hits = []
                for pos in words[fb[ai:ai + 4]]:
                    st = pos - ai
                    ad = LO + st
                    if st < 0 or st + len(fb) > len(text) or not (lo - 0x1000 <= ad <= hi + 0x1000):
                        continue
                    if apply(text[st:st + len(fb)], fm) == mb and free(ad, ad + len(fb)):
                        hits.append(ad)
                if len(hits) == 1:
                    ent["functions"][s_["name"]] = [hits[0], s_["size"], "ok"]
                    claimed.append((hits[0], hits[0] + s_["size"]))
                    sources[path] = ent

    # expected addresses of unmatched functions inside claimed sections
    for path, ent in sources.items():
        secs, syms, relocs = cf.parse_elf(os.path.join(a.objdir, ent["unit"] + ".o"))
        for sc in ent["sections"]:
            si = sc["idx"]
            fl = sorted((s_ for s_ in syms if s_["shndx"] == si and s_["type"] == 2 and s_["size"] >= 4), key=lambda s_: s_["value"])
            i = 0
            while i < len(fl):
                if fl[i]["name"] in ent["functions"]:
                    i += 1
                    continue
                j = i
                while j < len(fl) and fl[j]["name"] not in ent["functions"]:
                    j += 1
                run = fl[i:j]
                prev = ent["functions"].get(fl[i - 1]["name"]) if i > 0 else None
                nxt = ent["functions"].get(fl[j]["name"]) if j < len(fl) else None
                if prev is not None and prev[2] == "ok":
                    cur = prev[0] + prev[1]
                    gap = (nxt[0] - cur) if nxt is not None else None
                    if len(run) == 1 and gap is not None and gap > 0:
                        ent["functions"][run[0]["name"]] = [cur, gap, "diff"]
                    else:
                        for r_ in run:
                            ent["functions"][r_["name"]] = [cur, r_["size"], "diff"]
                            cur += r_["size"]
                elif nxt is not None and nxt[2] == "ok":
                    cur = nxt[0]
                    for r_ in reversed(run):
                        cur -= r_["size"]
                        ent["functions"][r_["name"]] = [cur, r_["size"], "diff"]
                else:
                    for r_ in run:
                        ent["functions"][r_["name"]] = [sc["base"] + r_["value"], r_["size"], "diff"]
                i = j
        # learn symbol addresses from relocations of matched functions
        fsym = {}
        for s_ in syms:
            if s_["type"] == 2 and s_["shndx"] and s_["shndx"] < 0xFF00:
                fsym.setdefault(s_["name"], s_)
        for fname, (faddr, fsize, fst) in ent["functions"].items():
            if fst != "ok" or fname not in fsym:
                continue
            fs = fsym[fname]
            si = fs["shndx"]
            for off, rtype, target, addend, tsym in relocs.get(si, []):
                if not (fs["value"] <= off < fs["value"] + fs["size"]):
                    continue
                at = faddr + (off - fs["value"])
                if rtype in (4, 5, 6):
                    w = 0
                else:
                    w, = struct.unpack(">I", read(at & ~3, 4))
                want = None
                if rtype == 10:
                    disp = w & 0x03FFFFFC
                    if disp & 0x02000000:
                        disp -= 0x04000000
                    want = at + disp
                elif rtype == 109:
                    ra, simm = (w >> 16) & 0x1F, w & 0xFFFF
                    if simm & 0x8000:
                        simm -= 0x10000
                    base = {13: SDA, 2: SDA2}.get(ra)
                    if base is not None:
                        want = base + simm
                elif rtype == 4:  # LO: find matching HA just before
                    lo, = struct.unpack(">h", read(at, 2))
                    for off2, rt2, tg2, ad2, _ in relocs.get(si, []):
                        if rt2 == 6 and tg2 == target and ad2 == addend and 0 < off - off2 <= 64:
                            hi, = struct.unpack(">H", read(faddr + (off2 - fs["value"]), 2))
                            want = ((hi << 16) + lo) & 0xFFFFFFFF
                            break
                if want is None:
                    continue
                if tsym["name"].startswith("@") or tsym["name"] == "" or tsym["name"].startswith("...") or (0 < tsym["shndx"] < 0xFF00 and tsym["type"] == 3):
                    continue
                addr = want - addend
                if not 0x80000000 <= addr < 0x81800000:
                    continue  # HA/LO pair not found correctly; never learn a non-address
                if tsym["shndx"] != 0 and tsym["type"] == 2 and target in ent["functions"]:
                    continue
                ps = ent.setdefault("syms", {})
                if target in ps and ps[target] != addr:
                    conflicts.setdefault(path + ":" + target, {ps[target]}).add(addr)
                else:
                    ps[target] = addr
    seen = {}
    for ent in sources.values():
        for t, ad in ent.get("syms", {}).items():
            seen.setdefault(t, set()).add(ad)
    symbols = {t: next(iter(v)) for t, v in seen.items() if len(v) == 1}
    for ent in sources.values():
        ent["syms"] = {t: ad for t, ad in ent.get("syms", {}).items() if t not in symbols}
    out = {"sources": sources, "symbols": symbols, "conflicts": {k: sorted(v) for k, v in conflicts.items()}}
    json.dump(out, open(a.out, "w"), indent=0)
    nf = sum(1 for e in sources.values() for f in e["functions"].values() if f[2] == "ok")
    nd = sum(1 for e in sources.values() for f in e["functions"].values() if f[2] == "diff")
    nb = sum(f[1] for e in sources.values() for f in e["functions"].values() if f[2] == "ok")
    print(f"{len(sources)} sources, {nf} ok funcs ({nb} bytes), {nd} diff funcs, {len(symbols)} symbols, {len(conflicts)} conflicts", file=sys.stderr)


if __name__ == "__main__":
    main()
