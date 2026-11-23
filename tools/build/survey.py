#!/usr/bin/env python3
"""Compile every per-function source file once and record what it emits.

For each file under src/game (main, equiv/ and auto/ files; wip/ is skipped):
  - check_func.py result per function (OK / DIFF) and overall exit code
  - the object's sections other than .text (name, size) and their symbols
Writes build/tmp/buildtree/survey.json (input of tu_status.py / gen_tu.py).

Usage: python3 -I tools/build/survey.py [-j 8] [files...]
"""
import argparse
import concurrent.futures as cf
import json
import os
import re
import shlex
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import check_func as CF  # noqa: E402

OUT = os.path.join(ROOT, "build/tmp/buildtree/survey.json")
OBJ_DIR = os.path.join(ROOT, "build/tmp/buildtree/survey_obj")


def sources():
    out = []
    for dp, dn, fn in os.walk(os.path.join(ROOT, "src/game")):
        if "/wip" in dp.replace(os.sep, "/"):
            continue
        for f in fn:
            if f.endswith((".c", ".cpp")):
                out.append(os.path.relpath(os.path.join(dp, f), ROOT))
    return sorted(out)


def one(src):
    obj = os.path.join(OBJ_DIR, src.replace("/", "__") + ".o")
    cc = os.path.join(ROOT, "build/compilers/GC/3.0a5.2/mwcceppc.exe")
    cmd = [CF.WIBO, cc, *shlex.split(CF.DEFAULT_FLAGS), "-c", src, "-o", obj]
    r = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True)
    res = {"file": src, "compiled": r.returncode == 0 and os.path.exists(obj)}
    if not res["compiled"]:
        res["error"] = (r.stdout + r.stderr)[-400:]
        return res
    secs, syms, relocs = CF.parse_elf(obj)
    res["sections"] = [{"name": s["name"], "size": s["size"]} for s in secs
                       if s["name"] and not s["name"].startswith((".rela", ".symtab", ".strtab", ".shstrtab", ".comment", ".mwcats", ".debug", ".line"))
                       and s["type"] in (1, 8)]
    res["symbols"] = [{"name": s["name"], "sec": secs[s["shndx"]]["name"] if 0 < s["shndx"] < len(secs) else None,
                       "size": s["size"], "type": s["type"], "value": s["value"]}
                      for s in syms if s["name"] and 0 < s["shndx"] < len(secs)]
    smap = os.path.splitext(src)[0] + ".symbols.json"   # object-local name -> original label
    extra = ["--symbol-map", smap] if os.path.exists(os.path.join(ROOT, smap)) else []
    if extra:
        res["symbol_map"] = smap
    c = subprocess.run([sys.executable, "-I", os.path.join(ROOT, "tools/check_func.py"), src, *extra],
                       cwd=ROOT, capture_output=True, text=True)
    res["check_rc"] = c.returncode
    res["funcs"] = {}
    for line in c.stdout.splitlines():
        m = re.match(r"\s+(OK|DIFF|SKIP)\s+(\S+?):?\s", line + " ")
        if m:
            name = m.group(2).rstrip(":")
            if m.group(1) == "OK" or name not in res["funcs"]:
                res["funcs"][name] = m.group(1)
            if m.group(1) == "DIFF":
                res["funcs"][name] = "DIFF"
    return res


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("-j", type=int, default=8)
    ap.add_argument("files", nargs="*")
    a = ap.parse_args()
    os.makedirs(OBJ_DIR, exist_ok=True)
    files = a.files or sources()
    old = {}
    if a.files and os.path.exists(OUT):
        old = {r["file"]: r for r in json.load(open(OUT))}
    out = dict(old)
    with cf.ThreadPoolExecutor(a.j) as ex:
        for i, r in enumerate(ex.map(one, files)):
            out[r["file"]] = r
            if i % 200 == 0:
                print(i, len(files), flush=True)
    json.dump(sorted(out.values(), key=lambda r: r["file"]), open(OUT, "w"), indent=0)
    bad = [r["file"] for r in out.values() if not r.get("compiled")]
    print("files", len(out), "compile failures", len(bad), bad[:10])


if __name__ == "__main__":
    main()
