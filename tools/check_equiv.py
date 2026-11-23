#!/usr/bin/env python3
"""Check that C is functionally plausible against the original, without matching bytes.

Compiles one file and compares each function with the original disassembly:
  - calls: same targets, same counts
  - indirect calls (bctrl): same count
  - global data: same .data/.bss/.sdata symbols referenced
  - memory offsets not on the stack, and compare/immediate constants: mostly the same
  - size: within --size-tolerance of the original

This catches wrong calls, wrong fields and wrong constants. It's evidence, not proof:
a swapped branch or a wrong comparison direction can still pass.

Usage: tools/check_equiv.py file.c [-v]
Exit code is 0 only when every function that exists in the original passes.
"""
import argparse
import collections
import glob
import os
import re
import shlex
import shutil
import subprocess
import sys
import tempfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import check_func as cf  # noqa: E402

ASM_GLOB = os.path.join(cf.ROOT, "build/RFEE01/asm/*.s")
DTK = os.path.join(cf.ROOT, "build/tools/dtk")
_INDEX = None

CALL_RE = re.compile(r"\b(bl|b)\s+([A-Za-z_@][\w@$.]*)")
SYM_RE = re.compile(r"\b(lbl_[0-9A-F]+)")
OFFSET_RE = re.compile(r"\s(-?0x[0-9a-fA-F]+|\d+)\((r\d+)\)")
CMP_RE = re.compile(r"\b(cmpwi|cmplwi|li|lis|subic|mulli|andi\.|ori|oris|xori)\b[^#\n]*?,\s*(-?0x[0-9a-fA-F]+|-?\d+)\s*$", re.M)
STRIP_RE = re.compile(r"/\*.*?\*/")


def asm_index():
    global _INDEX
    if _INDEX is None:
        _INDEX = {}
        for path in glob.glob(ASM_GLOB):
            text = open(path).read()
            for m in re.finditer(r"^\.fn (\S+?), \w+\n(.*?)^\.endfn \1$", text, re.M | re.S):
                _INDEX[m.group(1)] = m.group(2)
    return _INDEX


def data_sections():
    """symbol -> section, for telling mutable globals from pooled constants."""
    out = {}
    for line in open(cf.SYMBOLS):
        m = re.match(r"^(\S+) = (\S+):0x", line)
        if m:
            out[m.group(1)] = m.group(2)
    return out


def features(body, sections):
    lines = [STRIP_RE.sub("", ln).strip() for ln in body.split("\n")]
    insns = [ln for ln in lines if ln and not ln.startswith((".", "#")) and not ln.endswith(":")]
    calls = collections.Counter()
    data = set()
    offsets = collections.Counter()
    imms = collections.Counter()
    bctrl = 0
    for ln in insns:
        op = ln.split()[0]
        if op == "bctrl":
            bctrl += 1
        m = CALL_RE.match(ln)
        if m and not m.group(2).startswith(".L") and not m.group(2).startswith("lbl_"):
            calls[m.group(2)] += 1
        for sym in SYM_RE.findall(ln):
            if sections.get(sym) in (".data", ".bss", ".sdata", ".sbss", ".sbss2"):
                data.add(sym)
        m = OFFSET_RE.search(ln)
        if m and m.group(2) not in ("r1", "r2", "r13", "r0") and "@" not in ln:
            offsets[int(m.group(1), 0)] += 1
        m = CMP_RE.search(ln)
        if m and "@" not in ln and op != "subic":
            imms[int(m.group(2), 0) & 0xFFFF] += 1
    return {"size": len(insns), "calls": calls, "data": data, "offsets": offsets, "imms": imms, "bctrl": bctrl}


def similarity(a, b):
    total = sum((a | b).values())
    return 1.0 if not total else sum((a & b).values()) / total


def compare(name, ours, orig, size_tol):
    problems = []
    if ours["calls"] != orig["calls"]:
        missing = orig["calls"] - ours["calls"]
        extra = ours["calls"] - orig["calls"]
        if missing or extra:
            problems.append(f"calls: missing {dict(missing)} extra {dict(extra)}")
    if ours["bctrl"] != orig["bctrl"]:
        problems.append(f"indirect calls: {ours['bctrl']} vs {orig['bctrl']}")
    if ours["data"] != orig["data"]:
        problems.append(f"data: missing {sorted(orig['data'] - ours['data'])[:5]} extra {sorted(ours['data'] - ours['data'] & orig['data'])[:5]}")
    # Register allocation and inlining shift these a little, so small differences are fine.
    if sum(orig["offsets"].values()) >= 4 and similarity(ours["offsets"], orig["offsets"]) < 0.7:
        problems.append(f"field offsets differ: missing {dict(orig['offsets'] - ours['offsets'])} extra {dict(ours['offsets'] - orig['offsets'])}")
    elif sum(orig["offsets"].values()) < 4 and set(orig["offsets"]) - set(ours["offsets"]):
        problems.append(f"field offsets missing: {sorted(set(orig['offsets']) - set(ours['offsets']))}")
    if sum(orig["imms"].values()) >= 4 and similarity(ours["imms"], orig["imms"]) < 0.6:
        problems.append(f"constants differ: missing {dict(orig['imms'] - ours['imms'])} extra {dict(ours['imms'] - orig['imms'])}")
    elif sum(orig["imms"].values()) < 4 and set(orig["imms"]) - set(ours["imms"]):
        problems.append(f"constants missing: {sorted(set(orig['imms']) - set(ours['imms']))}")
    ratio = ours["size"] / max(1, orig["size"])
    if abs(ratio - 1) > size_tol and abs(ours["size"] - orig["size"]) > 6:
        problems.append(f"size: {ours['size']} instructions vs {orig['size']}")
    return problems


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("source")
    ap.add_argument("--cc", default="GC/3.0a5.2")
    ap.add_argument("--size-tolerance", type=float, default=0.35)
    ap.add_argument("-v", "--verbose", action="store_true")
    args = ap.parse_args()

    cc = os.path.join(cf.ROOT, "build/compilers", args.cc, "mwcceppc.exe")
    tmp = tempfile.mkdtemp(prefix="equiv_")
    try:
        obj = os.path.join(tmp, "out.o")
        r = subprocess.run([cf.WIBO, cc, *shlex.split(cf.DEFAULT_FLAGS), "-c", args.source, "-o", obj],
                           cwd=cf.ROOT, capture_output=True, text=True)
        if r.returncode != 0 or not os.path.exists(obj):
            print(r.stdout + r.stderr)
            print("COMPILE FAILED")
            return 2
        dis = os.path.join(tmp, "out.s")
        d = subprocess.run([DTK, "elf", "disasm", obj, dis], capture_output=True, text=True)
        if not os.path.exists(dis):
            print(d.stdout + d.stderr)
            print("DISASM FAILED")
            return 2
        text = open(dis).read()
    finally:
        pass
    sections = data_sections()
    index = asm_index()
    all_ok = True
    checked = 0
    for m in re.finditer(r"^\.fn (\S+?), \w+\n(.*?)^\.endfn \1$", text, re.M | re.S):
        name = m.group(1)
        if name not in index:
            continue
        checked += 1
        problems = compare(name, features(m.group(2), sections), features(index[name], sections), args.size_tolerance)
        if problems:
            all_ok = False
            print(f"  FAIL {name}")
            for p in problems:
                print(f"       {p}")
        else:
            print(f"  PASS {name}")
    shutil.rmtree(tmp, ignore_errors=True)
    if not checked:
        print("no functions from the original found in this file")
        return 1
    print("EQUIV" if all_ok else "NOT EQUIV")
    return 0 if all_ok else 1


if __name__ == "__main__":
    sys.exit(main())
