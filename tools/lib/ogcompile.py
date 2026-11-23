#!/usr/bin/env python3
"""Compile a public decomp's sources (default: ogws) with the local MWCC into
object files, using the per-object compiler flags found in its configure.py
(parsed as text, never executed).

Usage: tools/lib/ogcompile.py REPO OUTDIR [--version RSPE01_01] [-j 6] [--filter substr]
"""
import argparse, ast, os, re, shlex, subprocess, sys
from concurrent.futures import ThreadPoolExecutor

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
WIBO = os.path.join(ROOT, "tools/wibo_guard")


def parse_lists(text, version):
    """Evaluate the cflags_* = [...] definitions without executing code."""
    defs = {}
    for m in re.finditer(r"^(cflags_\w+) = \[\n(.*?)^\]", text, re.S | re.M):
        name, body = m.groups()
        items = []
        for line in body.splitlines():
            line = line.split("#")[0].strip().rstrip(",")
            if not line or line.startswith("if ") or line.startswith("else"):
                continue
            if line.startswith("*"):
                items.append(("spread", line[1:]))
            else:
                items.append(("lit", line))
        defs[name] = items

    def expand(name):
        out = []
        for kind, v in defs[name]:
            if kind == "spread":
                out += expand(v)
            else:
                v = v.replace("{config.version}", version).replace("{version_num}", "1")
                if v.startswith("f"):
                    v = v[1:]
                try:
                    out.append(ast.literal_eval(v))
                except Exception:
                    pass
        return out
    return {n: expand(n) for n in defs}


def objects(text, version):
    """Yield (path, cflags_name, mw_version, objname_overrides)."""
    res = []
    libs = re.split(r"\n    \{\n        \"lib\":", text)[1:]
    for blk in libs:
        mw = re.search(r'"mw_version": ([^\n]+),', blk)
        cf = re.search(r'"cflags": (cflags_\w+)', blk)
        mwv = mw.group(1).strip() if mw else "config.linker_version"
        for om in re.finditer(r'Object\(([^,]+), "([^"]+)"([^\n]*)\)', blk):
            extra = om.group(3)
            ocf = re.search(r"cflags ?= ?(cflags_\w+)", extra)
            omw = re.search(r'mw_version ?= ?"([^"]+)"', extra)
            res.append((om.group(2), (ocf.group(1) if ocf else (cf.group(1) if cf else None)),
                        omw.group(1) if omw else mwv, om.group(1)))
    return res


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("repo")
    ap.add_argument("out")
    ap.add_argument("--version", default="RSPE01_01")
    ap.add_argument("-j", type=int, default=6)
    ap.add_argument("--filter", default="")
    ap.add_argument("--cc", default="")
    a = ap.parse_args()
    text = open(os.path.join(a.repo, "configure.py")).read()
    lists = parse_lists(text, a.version)
    objs = objects(text, a.version)
    ver = {"config.linker_version": "GC/3.0a5.2"}
    os.makedirs(a.out, exist_ok=True)
    jobs = []
    for path, cfn, mwv, _st in objs:
        if a.filter not in path:
            continue
        src = os.path.join("src", path)
        if not os.path.exists(os.path.join(a.repo, src)) or cfn not in lists:
            continue
        mwv = a.cc or ver.get(mwv, mwv.strip('"'))
        flags = [f for f in lists[cfn]] + ["-DNDEBUG=1", "-DBUILD_VERSION=1", f"-DVERSION_{a.version}"]
        jobs.append((src, mwv, flags, path))

    import json
    man = {}
    for src, mwv, flags, path in jobs:
        fl = []
        for f in flags:
            f = re.sub(r"^(-ir?) (include\S*)$", r"\1 lib/ogws/\2", f)
            f = re.sub(r"^-i build/\S+$", "", f)
            if f:
                fl.append(f)
        man["ogws/src/" + path] = {"unit": "ogws__src__" + path.replace("/", "__") + ".o", "cc": mwv, "flags": fl}
    mp = os.path.join(a.out, "manifest.json")
    allman = json.load(open(mp)) if os.path.exists(mp) else {}
    allman.update(man)
    json.dump(allman, open(mp, "w"), indent=1)

    def run(j):
        src, mwv, flags, path = j
        outp = os.path.join(a.out, "ogws__src__" + path.replace("/", "__") + ".o")
        cc = os.path.join(ROOT, "build/compilers", mwv, "mwcceppc.exe")
        if not os.path.exists(cc):
            return path, "nocompiler " + mwv
        cmd = [WIBO, cc] + [x for f in flags for x in shlex.split(f)] + ["-c", src, "-o", outp]
        r = subprocess.run(cmd, cwd=a.repo, capture_output=True, text=True)
        return path, ("ok" if r.returncode == 0 and os.path.exists(outp) else "FAIL " + (r.stdout + r.stderr)[:300].replace("\n", " | "))

    with ThreadPoolExecutor(a.j) as ex:
        for path, st in ex.map(run, jobs):
            print(path, st, flush=True)


if __name__ == "__main__":
    main()
