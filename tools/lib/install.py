#!/usr/bin/env python3
"""Copy reference sources named in a map.json (plus the header trees they need) into lib/.

Usage: tools/lib/install.py MAP.json OBJDIR NAME=REPO [NAME=REPO ...]
Writes lib/<key> for each source key "NAME/<repo-relative path>", lib/NAME/<include dirs>,
lib/map.json and lib/manifest.json (merged with what is already there).
"""
import json, os, re, shutil, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
L = os.path.join(ROOT, "lib")


def main():
    mp, objdir = sys.argv[1:3]
    repos = dict(a.split("=", 1) for a in sys.argv[3:])
    m = json.load(open(mp))
    man = json.load(open(os.path.join(objdir, "manifest.json")))
    mpath = os.path.join(L, "manifest.json")
    old = json.load(open(mpath)) if os.path.exists(mpath) else {}
    incs = {}
    for key in m["sources"]:
        name, rel = key.split("/", 1)
        dst = os.path.join(L, key)
        os.makedirs(os.path.dirname(dst), exist_ok=True)
        if not os.path.exists(dst):  # never overwrite edited lib sources
            shutil.copy(os.path.join(repos[name], rel), dst)
        old[key] = {"cc": man[key]["cc"], "flags": man[key]["flags"]}
        for f in man[key]["flags"]:
            mm = re.match(r"^-ir? lib/([^/]+)/(\S+)$", f)
            if mm:
                incs.setdefault(mm.group(1), set()).add(mm.group(2))
    for name, dirs in incs.items():
        dirs = sorted(dirs, key=len)
        done = []
        for d in dirs:
            if any(d.startswith(o + "/") for o in done):
                continue
            src = os.path.join(repos[name], d)
            if os.path.isdir(src):
                shutil.copytree(src, os.path.join(L, name, d), dirs_exist_ok=True, copy_function=lambda a, b: None if os.path.exists(b) else shutil.copy2(a, b))
                done.append(d)
    json.dump(old, open(mpath, "w"), indent=1, sort_keys=True)
    shutil.copy(mp, os.path.join(L, "map.json"))
    print(len(m["sources"]), "sources installed")


if __name__ == "__main__":
    main()
