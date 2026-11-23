#!/usr/bin/env python3
"""Run place.py over every per-function file that check_func reports as fully exact
(survey.json) and summarise which files could be linked as their own unit right now.
Writes build/tmp/buildtree/place_all.json."""
import collections, json, os, sys
HERE = os.path.dirname(os.path.abspath(__file__)); ROOT = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, HERE)
import place as PL
sv = json.load(open(os.path.join(ROOT, "build/tmp/buildtree/survey.json")))
out = []
why = collections.Counter()
for r in sv:
    if r.get("check_rc") != 0 or "/equiv/" in r["file"]:
        continue
    obj = os.path.join(ROOT, "build/tmp/buildtree/survey_obj", r["file"].replace("/", "__") + ".o")
    P = PL.place(obj)
    kinds = sorted({e.split(" ")[0] if not e.startswith("function") else "function:" + e.split()[-1].split("(")[0] for e in P.errors})
    cls = "ok" if P.ok else ("noncontiguous" if any("contiguity" in e for e in P.errors) else
                             "extern-symbol" if all("referenced from outside" in e for e in P.errors) else "other")
    why[cls] += 1
    out.append({"file": r["file"], "ok": P.ok, "class": cls, "ranges": {k: [hex(a), hex(b)] for k, (a, b) in P.ranges.items()},
                "functions": len(P.functions), "errors": P.errors[:6]})
json.dump(out, open(os.path.join(ROOT, "build/tmp/buildtree/place_all.json"), "w"), indent=1)
print(why)
