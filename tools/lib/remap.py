#!/usr/bin/env python3
"""Re-place the functions of one lib source after editing it.

Usage: tools/lib/remap.py KEY [KEY ...]       (KEY like ogws/src/nw4r/snd/snd_Voice.cpp)
Compiles the source, then within the address span lib/map.json already has for it:
exact (reloc-masked) matches become "ok", the best opcode-shape match (> 0.75) becomes "diff"
at that address with the original's size. Rewrites that source's entry in lib/map.json.
"""
import difflib, json, os, shlex, subprocess, struct, sys, tempfile
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path[:0] = [HERE, os.path.join(HERE, "..")]
ROOT = os.path.dirname(os.path.dirname(HERE))
import check_func as cf
from libscan import apply
from fuzzy import shape


def compile_obj(key, man):
    tmp = tempfile.mkdtemp(dir=os.path.join(ROOT, "build/tmp") if os.path.isdir(os.path.join(ROOT, "build/tmp")) else None)
    obj = os.path.join(tmp, "o.o")
    cc = os.path.join(ROOT, "build/compilers", man["cc"], "mwcceppc.exe")
    cmd = [cf.WIBO, cc] + [x for f in man["flags"] for x in shlex.split(f)] + ["-c", "lib/" + key, "-o", obj]
    r = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True)
    if not os.path.exists(obj):
        print((r.stdout + r.stderr)[:800])
        return None
    return obj


def main():
    mp = os.path.join(ROOT, "lib/map.json")
    M = json.load(open(mp))
    MAN = json.load(open(os.path.join(ROOT, "lib/manifest.json")))
    syms = cf.load_symbols()
    read = cf.dol_reader()
    addr_size = {a: s for n, (a, s) in syms.items() if 0x8028BC54 <= a < 0x80360900}
    for key in sys.argv[1:]:
        ent = M["sources"][key]
        obj = compile_obj(key, MAN[key])
        if obj is None:
            continue
        secs, esyms, relocs = cf.parse_elf(obj)
        addrs = [f[0] for f in ent["functions"].values()]
        lo, hi = min(addrs) - 0x2000, max(addrs) + 0x2000
        cands = sorted(a for a in addr_size if lo <= a <= hi)
        cshape = {}
        new, used = {}, set()
        fl = []
        for s in esyms:
            if s["type"] == 2 and s["shndx"] and s["shndx"] < 0xFF00 and s["size"] >= 4 and secs[s["shndx"]]["name"].startswith(".text"):
                fl.append(s)
        rest = []
        for s in fl:
            sec = secs[s["shndx"]]
            fb = bytes(sec["data"][s["value"]:s["value"] + s["size"]])
            fm = {}
            for off, rtype, *_ in relocs.get(s["shndx"], []):
                if s["value"] <= off < s["value"] + s["size"]:
                    wo = off - 2 if rtype in (4, 5, 6) else off & ~3
                    fm[wo - s["value"]] = fm.get(wo - s["value"], 0) | cf.RELOC_MASK.get(rtype, 0xFFFFFFFF)
            mb = apply(fb, fm)
            hit = None
            for a in cands:
                if a in used or addr_size[a] != len(fb):
                    continue
                if apply(read(a, len(fb)), fm) == mb:
                    hit = a
                    # prefer a candidate near the old entry for this name
                    old = ent["functions"].get(s["name"])
                    if old is None or abs(old[0] - a) < 0x4000:
                        break
            if hit is not None:
                used.add(hit)
                new[s["name"]] = [hit, len(fb), "ok"]
            else:
                rest.append((s, fb, fm))
        for s, fb, fm in rest:
            sh = shape(fb, fm)
            best = None
            for a in cands:
                if a in used or not (0.6 * len(fb) <= addr_size[a] <= 1.7 * len(fb)):
                    continue
                if a not in cshape:
                    cshape[a] = shape(read(a, addr_size[a]), {})
                r = difflib.SequenceMatcher(None, sh, cshape[a], autojunk=False).ratio()
                if best is None or r > best[0]:
                    best = (r, a)
            if best and best[0] > 0.75:
                used.add(best[1])
                new[s["name"]] = [best[1], addr_size[best[1]], "diff"]
        import fcntl
        with open(mp + ".lock", "w") as lk:
            fcntl.flock(lk, fcntl.LOCK_EX)
            M2 = json.load(open(mp))
            M2["sources"][key]["functions"] = new
            json.dump(M2, open(mp, "w"), indent=0)
            fcntl.flock(lk, fcntl.LOCK_UN)
        ok = sum(1 for f in new.values() if f[2] == "ok")
        print(f"{key}: {ok} ok, {len(new) - ok} diff, {len(fl) - len(new)} unplaced")


if __name__ == "__main__":
    main()
