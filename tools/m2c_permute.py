#!/usr/bin/env python3
"""Random search on m2c drafts that nearly match. No LLM involved.

For each near miss, shuffles local declarations and widens small integer types,
keeping any change that brings the function closer. Matches go to src/game/auto/.

Usage:
  tools/m2c_permute.py [--max-words 25] [--tries 60] [--jobs 4]
      [--exclude 0xSTART-0xEND ...]
"""
import argparse
import multiprocessing
import os
import random
import re
import shutil
import subprocess
import sys
import tempfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import m2c_pipeline as p  # noqa: E402

PRELUDE = '#include "game/auto/m2c_prelude.h"\n'
WIDEN = {"s8": "s32", "s16": "s32", "u8": "u32", "u16": "u32", "s32": "u32", "u32": "s32"}


def score(name, code, tmp):
    """Differing words, or None if it doesn't compile. 0 means an exact match."""
    src = os.path.join(tmp, f"{name}.c")
    open(src, "w").write(code)
    c = subprocess.run([sys.executable, "-I", os.path.join(p.ROOT, "tools/check_func.py"), src],
                       capture_output=True, text=True, cwd=p.ROOT, timeout=120)
    if "COMPILE FAILED" in c.stdout:
        return None
    if c.returncode == 0 and f"OK   {name}" in c.stdout:
        return 0
    m = re.search(rf"DIFF {name}: (\d+) of \d+ words differ", c.stdout)
    if not m or re.search(rf"DIFF {name}: size", c.stdout):
        return 10 ** 6
    wrong = re.search(rf"DIFF {name}: (\d+) wrong reference", c.stdout)
    return int(m.group(1)) + (int(wrong.group(1)) if wrong else 0) + 1


def split_decls(code, name):
    """(before, declaration lines, after) for the function's local declarations."""
    m = re.search(rf"\b{name}\([^)]*\) \{{\n", code)
    if not m:
        return None
    rest = code[m.end():]
    end = rest.find("\n\n")
    if end < 0:
        return None
    lines = rest[:end].split("\n")
    if not all(re.match(r"\s+[\w ]+\**\s*\w+(\[\w+\])?;$", ln) for ln in lines):
        return None
    return code[:m.end()], lines, rest[end:]


def mutate(before, decls, after, rng):
    decls = list(decls)
    choice = rng.random()
    if choice < 0.7 and len(decls) > 1:
        i, j = rng.sample(range(len(decls)), 2)
        decls.insert(j, decls.pop(i))
    elif decls:
        i = rng.randrange(len(decls))
        m = re.match(r"(\s+)(\w+)(\s.*)", decls[i])
        if m and m.group(2) in WIDEN:
            decls[i] = m.group(1) + WIDEN[m.group(2)] + m.group(3)
    return decls


def run_one(item):
    name, body, tries, addr = item
    tmp = tempfile.mkdtemp(prefix="perm_")
    rng = random.Random(name)
    try:
        asm = os.path.join(tmp, "f.s")
        open(asm, "w").write(".text\n" + body)
        r = subprocess.run([p.PY, p.M2C, "-t", "ppc-mwcc-c", "--valid-syntax", "--globals=used", "-f", name, asm],
                           capture_output=True, text=True, timeout=120)
        if r.returncode != 0:
            return name, "m2c_failed", 0
        draft = p.fix_draft(r.stdout)
        for prefix in ("", "#pragma use_lmw_stmw on\n"):
            base = PRELUDE + prefix + draft
            best = score(name, base, tmp)
            if best == 0:
                write(name, addr, base)
                return name, "match", 0
            if best is None:
                continue
            parts = split_decls(base, name)
            if not parts:
                continue
            before, decls, after = parts
            for _ in range(tries):
                cand = mutate(before, decls, after, rng)
                code = before + "\n".join(cand) + after
                s = score(name, code, tmp)
                if s == 0:
                    write(name, addr, code)
                    return name, "match", 0
                if s is not None and s <= best:
                    best, decls = s, cand
        return name, "miss", best if best else 0
    except subprocess.TimeoutExpired:
        return name, "timeout", 0
    finally:
        shutil.rmtree(tmp, ignore_errors=True)


def write(name, addr, code):
    d = os.path.join(p.ROOT, "src/game/auto", f"{addr & ~0xFFFF:08X}")
    os.makedirs(d, exist_ok=True)
    open(os.path.join(d, f"{name}.c"), "w").write(code)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--max-words", type=int, default=25)
    ap.add_argument("--max-size", type=int, default=150)
    ap.add_argument("--tries", type=int, default=60)
    ap.add_argument("--jobs", type=int, default=4)
    ap.add_argument("--exclude", nargs="*", default=[])
    args = ap.parse_args()

    ranges = [tuple(int(x, 16) for x in e.split("-")) for e in args.exclude]
    done = set(open(os.path.join(p.OUT, "matched_names.txt")).read().split())
    funcs = p.load_functions()
    todo = []
    for line in open(os.path.join(p.OUT, "results.tsv")):
        name, status, note = (line.rstrip("\n").split("\t") + [""])[:3]
        if name in done or name not in funcs or status != "mismatch" or "/" not in note or "size" in note:
            continue
        addr, body = funcs[name]
        if int(note.split("/")[0]) > args.max_words or body.count("\n/* ") > args.max_size:
            continue
        if any(a <= addr < b for a, b in ranges):
            continue
        todo.append((name, body, args.tries, addr))
    print(f"{len(todo)} near misses, {args.tries} tries each, {args.jobs} jobs", flush=True)

    counts = {}
    with multiprocessing.Pool(args.jobs) as pool, open(os.path.join(p.OUT, "permute.tsv"), "w") as log:
        for i, (name, status, best) in enumerate(pool.imap_unordered(run_one, todo)):
            counts[status] = counts.get(status, 0) + 1
            log.write(f"{name}\t{status}\t{best}\n")
            log.flush()
            if status == "match":
                print("match", name, flush=True)
            if (i + 1) % 25 == 0:
                print(i + 1, counts, flush=True)
    print("done", counts)


if __name__ == "__main__":
    main()
