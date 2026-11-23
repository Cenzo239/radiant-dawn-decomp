#!/usr/bin/env python3
"""Random search on hand-written near misses in src/game/*/wip/. No LLM involved.

For each function in a wip file that compiles and misses by a few words, cuts
the other functions out of the file, then keeps moving local declarations and
widening small integer types while the function gets closer. An exact match is
written as src/game/<region>/fn_X_search.cpp and is never written over a file.

Usage:
  tools/wip_search.py [--max-words 30] [--tries 300] [--jobs 12]
      [--skip-region rG_800A3D88 ...] [--limit N]
"""
import argparse
import glob
import multiprocessing
import os
import random
import re
import shlex
import shutil
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CHECK = os.path.join(ROOT, "tools/check_func.py")
TMP = os.path.join(ROOT, "build/tmp")
WIDEN = {"s8": "s32", "s16": "s32", "u8": "u32", "u16": "u32", "s32": "u32", "u32": "s32", "int": "u32"}
DECL = re.compile(r"^\s+(?:const\s+)?[A-Za-z_][\w:<>]*(?:\s+const)?[\s*&]+\w+(?:\[[^\]]*\])?(?:\s*,\s*\**\w+)*\s*;\s*(?://.*)?$")


def run_check(src, region_dir):
    rel = os.path.relpath(region_dir, ROOT)
    extra = f"-i {shlex.quote(rel)} -i {shlex.quote(rel + '/wip')}"
    c = subprocess.run([sys.executable, "-I", CHECK, src, "--extra", extra],
                       capture_output=True, text=True, cwd=ROOT, timeout=300)
    return c.returncode, c.stdout


def score(out, name):
    if "COMPILE FAILED" in out:
        return None
    if re.search(rf"OK\s+{name}\b", out):
        return 0
    if re.search(rf"DIFF {name}: size", out):
        return 10 ** 6
    m = re.search(rf"DIFF {name}: (\d+) of \d+ words differ", out)
    if not m:
        return None
    wrong = re.search(rf"DIFF {name}: (\d+) wrong reference", out)
    return int(m.group(1)) + (int(wrong.group(1)) if wrong else 0) + 1


def find_function(text, name):
    """(start, body_start, end) of a definition of name, or None."""
    m = re.search(rf"^[^\n;{{}}]*\b{name}\s*\([^;{{]*\)\s*\{{", text, re.M)
    if not m:
        return None
    depth, i = 1, m.end()
    while i < len(text) and depth:
        depth += {"{": 1, "}": -1}.get(text[i], 0)
        i += 1
    return (m.start(), m.end(), i) if depth == 0 else None


def strip_others(text, keep):
    """Cut the bodies of all other fn_ definitions down to prototypes."""
    names = set(re.findall(r"\b(fn_[0-9A-F]{8})\s*\(", text)) - {keep}
    for name in names:
        f = find_function(text, name)
        if f:
            text = text[:f[1] - 1].rstrip() + ";" + text[f[2]:]
    return text


def run_one(item):
    path, name, region_dir, tries, ext = item
    rng = random.Random()
    tmp = tempfile.mkdtemp(dir=TMP, prefix="wip_")
    src = os.path.join(tmp, name + ext)
    try:
        base = strip_others(open(path).read(), name)
        open(src, "w").write(base)
        _rc, out = run_check(src, region_dir)
        best = score(out, name)
        if best is None:
            return name, "no_compile", None
        f = find_function(base, name)
        if not f:
            return name, "not_found", best
        head, rest = base[:f[1]], base[f[1]:]
        lines = rest.split("\n")
        i = 1 if not lines[0].strip() else 0
        start = i
        while i < len(lines) and (DECL.match(lines[i]) or lines[i].strip() in ("/*P*/", "/*E*/", "/*PERM*/", "/*ENDPERM*/")):
            i += 1
        decls = [ln for ln in lines[start:i] if DECL.match(ln)]
        tail = lines[i:]
        code = base
        if best == 0:
            pass
        elif len(decls) < 2:
            return name, "few_decls", best
        else:
            for _ in range(tries):
                cand = list(decls)
                if rng.random() < 0.75:
                    a, b = rng.sample(range(len(cand)), 2)
                    cand.insert(b, cand.pop(a))
                else:
                    a = rng.randrange(len(cand))
                    m = re.match(r"(\s+)(\w+)(\s.*)", cand[a])
                    if m and m.group(2) in WIDEN:
                        cand[a] = m.group(1) + WIDEN[m.group(2)] + m.group(3)
                text = head + "\n" + "\n".join(cand + tail)
                open(src, "w").write(text)
                _rc, out = run_check(src, region_dir)
                s = score(out, name)
                if s is None:
                    continue
                if s <= best:
                    best, decls, code = s, cand, text
                if best == 0:
                    break
        if best != 0:
            return name, "miss", best
        dest = os.path.join(region_dir, f"{name}_search{ext}")
        if os.path.exists(dest):
            return name, "exists", 0
        open(dest, "x").write(code)
        rc, out = run_check(dest, region_dir)
        if rc != 0:
            os.remove(dest)
            return name, "whole_file_mismatch", 0
        return name, "match", 0
    except subprocess.TimeoutExpired:
        return name, "timeout", None
    finally:
        shutil.rmtree(tmp, ignore_errors=True)


def scan(item):
    """Which functions in one wip file are close enough to be worth searching."""
    path, region_dir, max_words, done = item
    rc, out = run_check(path, region_dir)
    found = []
    for m in re.finditer(r"DIFF (fn_[0-9A-F]{8}): (\d+) of \d+ words differ", out):
        if m.group(1) not in done and int(m.group(2)) <= max_words:
            found.append((path, m.group(1), int(m.group(2))))
    return found


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--max-words", type=int, default=30)
    ap.add_argument("--tries", type=int, default=300)
    ap.add_argument("--jobs", type=int, default=12)
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--skip-region", nargs="*", default=[])
    args = ap.parse_args()
    os.makedirs(TMP, exist_ok=True)
    done = set(open(os.path.join(ROOT, "build/m2c/matched_names.txt")).read().split())

    items = []
    for path in glob.glob(os.path.join(ROOT, "src/game/*/wip/*.c*")):
        if not path.endswith((".c", ".cpp")):
            continue
        region_dir = os.path.dirname(os.path.dirname(path))
        if os.path.basename(region_dir) in args.skip_region:
            continue
        items.append((path, region_dir, args.max_words, done))
    with multiprocessing.Pool(args.jobs) as pool:
        found = {}
        for res in pool.imap_unordered(scan, items):
            for path, name, words in res:
                if name not in found or words < found[name][1]:
                    found[name] = (path, words)
        todo = sorted(found.items(), key=lambda kv: kv[1][1])
        if args.limit:
            todo = todo[:args.limit]
        print(f"{len(items)} wip files, {len(todo)} functions within {args.max_words} words", flush=True)
        work = [(p, n, os.path.dirname(os.path.dirname(p)), args.tries, os.path.splitext(p)[1]) for n, (p, _w) in todo]
        counts = {}
        with open(os.path.join(ROOT, "build/m2c/wip_search.tsv"), "w") as log:
            for name, status, best in pool.imap_unordered(run_one, work):
                counts[status] = counts.get(status, 0) + 1
                log.write(f"{name}\t{status}\t{best}\n")
                log.flush()
                if status == "match":
                    print("match", name, flush=True)
    print("done", counts)


if __name__ == "__main__":
    main()
