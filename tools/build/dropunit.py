#!/usr/bin/env python3
"""Remove library units from config/RFEE01/units.json and link_select.txt without re-running gen_units
(for bisecting a failing link: then gen_config.py, configure.py, ninja). Usage: dropunit.py <suffix> ..."""
import json
import sys

suf = tuple(sys.argv[1:])
p = "config/RFEE01/units.json"
d = json.load(open(p))
n0 = len(d["units"])
d["units"] = [u for u in d["units"] if not (u["kind"] == "lib" and u["lib_source"].endswith(suf))]
json.dump(d, open(p, "w"), indent=1)
q = "config/RFEE01/link_select.txt"
L = [x for x in open(q) if not x.rstrip().endswith(suf)]
open(q, "w").writelines(L)
print(n0 - len(d["units"]), "units removed")
