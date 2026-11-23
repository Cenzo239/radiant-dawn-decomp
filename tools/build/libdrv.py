#!/usr/bin/env python3
"""Read-only driver: place library sources the way try_units.py --libs does, without writing
docs/, config/ or src/tu/. Usage: drv.py [-j 6] [--all | key ...] [--out results.json] [-v]"""
import argparse, collections, json, os, sys, tempfile
ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
TMP = os.path.join(ROOT, "build/tmp/libplace/tmp")
os.environ["TMPDIR"] = TMP
tempfile.tempdir = TMP
sys.path.insert(0, os.path.join(ROOT, "tools/build"))
import place as PL
_orig_compile = PL.compile_src
def compile_src(src, cc="GC/3.0a5.2", flags=PL.CF.DEFAULT_FLAGS, out=None):
    out = out or tempfile.mktemp(suffix=".o", dir=TMP)
    return _orig_compile(src, cc, flags, out)
PL.compile_src = compile_src
import gen_units as GU
GU.write_aliases = lambda *a, **k: None   # never write src/tu
import try_units as TU
import gen_tu as G
import gen_config as GC

ap = argparse.ArgumentParser()
ap.add_argument("-j", type=int, default=6)
ap.add_argument("--all", action="store_true", help="all candidates (incl. currently-ok, for duplicate logic)")
ap.add_argument("--any", action="store_true", help="do not require the key to be a candidate")
ap.add_argument("--out")
ap.add_argument("-v", action="store_true")
ap.add_argument("--pstrip", action="store_true", help="PROPOSAL: try the dead-strip model on contiguity/size errors too")
ap.add_argument("--plabel", action="store_true", help="PROPOSAL: function symbols win over labels at one address")
ap.add_argument("--pbss", action="store_true", help="PROPOSAL: the dead-strip model keeps .bss/.sbss objects")
ap.add_argument("--pdata", action="store_true", help="with --pbss: keep every data object, not only .bss/.sbss")
ap.add_argument("keys", nargs="*")
a = ap.parse_args()
if a.pstrip:
    _place = PL.place
    def place2(obj, names=None, strip_check=True):
        P = _place(obj, names, strip_check)
        if isinstance(obj, str) and any("breaks contiguity" in e or ("size 0x" in e and e.startswith("function ")) for e in P.errors):
            P.errors.append("function (pstrip) not in symbols.txt")
        return P
    PL.place = place2
if a.pbss:
    _strip = PL.strip_object
    def strip2(obj, in_dol):
        secs, syms, _r = PL.CF.parse_elf(obj)
        bss = {sy["name"] for sy in syms if sy["shndx"] and sy["shndx"] < len(secs) and sy["type"] == 1
               and (a.pdata or secs[sy["shndx"]]["name"] in (".bss", ".sbss"))}
        return _strip(obj, lambda n: in_dol(n) if n not in bss else (in_dol(n) or 1))
    PL.strip_object = strip2
    _place_b = PL.place
    def place_b(obj, names=None, strip_check=True):
        P = _place_b(obj, names, strip_check)
        secs, syms, _r = obj[:3] if not isinstance(obj, str) else PL.CF.parse_elf(obj)
        bss = {sy["name"] for sy in syms if sy["shndx"] and sy["shndx"] < len(secs) and sy["type"] == 1
               and (a.pdata or secs[sy["shndx"]]["name"] in (".bss", ".sbss"))}
        P.errors = [e for e in P.errors if not ("referenced nowhere" in e and e.split()[0] in bss)]
        return P
    PL.place = place_b
TU.RENAMES.update(GC.lib_renames())
TU.BASE_RENAMES.update(TU.RENAMES)
for o, n in G.symbol_map_renames(sorted({p for ps in G.load_ok_files().values() for p in ps[:1]})).items():
    TU.RENAMES.setdefault(o, n)
GU.GLOBAL_RENAMES.update(TU.RENAMES)
lib_map = json.load(open(os.path.join(ROOT, "lib/map.json")))
manifest = json.load(open(os.path.join(ROOT, "lib/manifest.json")))
TU._WORK.update(lib_map=lib_map, manifest=manifest)
PL.dolmodel()
if a.plabel:
    S0 = PL._cache["S"]
    PL._cache["S"] = dict(sorted(S0.items(), key=lambda kv: kv[1].type != "function"))
cands = TU.lib_candidates()
if a.all:
    keys = cands
else:
    keys = a.keys
    for k in keys:
        if k not in cands:
            print("NOTE: not a candidate (verified/manifest/map ok):", k)
if a.all:
    res = TU.try_libs(a.j)   # includes duplicate logic
else:
    res = TU.pmap(TU._lib_one, keys, a.j)
c = collections.Counter(r["cls"] for r in res)
for r in sorted(res, key=lambda r: r["lib"]):
    if a.v or len(res) < 40:
        print(r["lib"], r["cls"], r.get("functions"), (r["errors"][:3] if a.v else r["errors"][:1]))
print(", ".join(f"{k} {v}" for k, v in c.most_common()))
if a.out:
    json.dump(res, open(a.out, "w"), indent=0)
