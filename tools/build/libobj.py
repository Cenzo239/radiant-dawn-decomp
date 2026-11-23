#!/usr/bin/env python3
"""List the function symbols of a library source's compiled object next to the DOL addresses
lib/map.json gives them: object order, size, binding (1 global, 0 local, 2 weak) and address ('-' =
no DOL address, i.e. the DOL has no function of that name from this source).
Usage: python3 -I tools/build/libobj.py <lib source key>    (e.g. ogws/src/nw4r/snd/snd_BasicSound.cpp)
Compare with `awk '/0x802A2[D-F]/' config/RFEE01/symbols.txt` to see which DOL functions the object
lacks, emits in another order, or emits in addition (weak/inline copies)."""
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, "tools/build"))
import gen_units as GU  # noqa: E402
import place as PL  # noqa: E402

key = sys.argv[1]
m = json.load(open(os.path.join(ROOT, "lib/manifest.json")))[key]
obj = PL.compile_src(os.path.join("lib", key), m["cc"], GU.flat_flags(m["flags"]))
try:
    secs, syms, _rel = PL.parse_elf(obj)
finally:
    os.unlink(obj)
mp = json.load(open(os.path.join(ROOT, "lib/map.json")))["sources"][key]["functions"]
for s in sorted([s for s in syms if s["type"] == 2 and s["shndx"]], key=lambda s: (s["shndx"], s["value"])):
    a = mp.get(s["name"])
    print(secs[s["shndx"]]["name"], hex(s["value"]), hex(s["size"]), s.get("bind"), s["name"], hex(a[0]) if a else "-")
