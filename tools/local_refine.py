#!/usr/bin/env python3
"""Let a local Ollama model repair m2c drafts that don't match yet.

Takes functions from build/m2c/results.tsv that failed to compile or missed by
a few words, and asks the model to fix each draft, up to --tries times. Nothing
is kept unless tools/check_func.py confirms an exact match.

Usage:
  tools/local_refine.py [--model qwen3.6:27b-q4_K_M] [--limit N] [--tries 3]
      [--max-words 5] [--write]
"""
import argparse
import json
import os
import re
import shutil
import subprocess
import sys
import tempfile
import time
import urllib.request

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import m2c_pipeline as p  # noqa: E402

PROMPT = """You are fixing C code so that it compiles with Metrowerks CodeWarrior for PowerPC \
to exactly the assembly below. Keep the function name and every external symbol name. \
Keep the extern declarations. Types s8 u8 s16 u16 s32 u32 s64 u64 f32 f64 and macros such as M2C_FIELD \
already exist; don't redefine them. Don't add #include lines.

Assembly:
{asm}

Current C:
{code}

Problem:
{problem}

Reply with the complete corrected C in one ```c block and nothing else."""


def ask(model, prompt):
    req = urllib.request.Request(
        "http://localhost:11434/api/generate",
        data=json.dumps({
            "model": model, "prompt": prompt, "stream": False, "think": False,
            "keep_alive": "2m", "options": {"temperature": 0.2, "num_ctx": 8192},
        }).encode(),
        headers={"Content-Type": "application/json"},
    )
    with urllib.request.urlopen(req, timeout=300) as r:
        return json.load(r)["response"]


def check(name, code, tmp):
    src = os.path.join(tmp, f"{name}.c")
    open(src, "w").write('#include "game/auto/m2c_prelude.h"\n' + code)
    c = subprocess.run([sys.executable, "-I", os.path.join(p.ROOT, "tools/check_func.py"), src, "-v"],
                       capture_output=True, text=True, cwd=p.ROOT, timeout=120)
    ok = c.returncode == 0 and f"OK   {name}" in c.stdout
    return ok, c.stdout[-1200:]


def draft(name, body, tmp):
    asm = os.path.join(tmp, "f.s")
    open(asm, "w").write(".text\n" + body)
    r = subprocess.run([p.PY, p.M2C, "-t", "ppc-mwcc-c", "--valid-syntax", "--globals=used", "-f", name, asm],
                       capture_output=True, text=True, timeout=120)
    return p.fix_draft(r.stdout)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--model", default="qwen3.6:27b-q4_K_M")
    ap.add_argument("--limit", type=int, default=20)
    ap.add_argument("--tries", type=int, default=3)
    ap.add_argument("--max-words", type=int, default=5)
    ap.add_argument("--max-size", type=int, default=120, help="skip functions longer than this many instructions")
    ap.add_argument("--names", default="", help="comma-separated functions, instead of picking from results.tsv")
    ap.add_argument("--write", action="store_true")
    args = ap.parse_args()

    funcs = p.load_functions()
    todo = []
    for line in open(os.path.join(p.OUT, "results.tsv")):
        name, status, note = (line.rstrip("\n").split("\t") + [""])[:3]
        if name not in funcs or funcs[name][1].count("\n/* ") > args.max_size:
            continue
        near = status == "mismatch" and "/" in note and "size" not in note and int(note.split("/")[0]) <= args.max_words
        if status == "compile_failed" or near:
            todo.append((name, status))
    todo = todo[:args.limit]
    if args.names:
        todo = [(n, "named") for n in args.names.split(",")]
    print(f"{len(todo)} functions, model {args.model}", flush=True)

    matched = 0
    start = time.time()
    log = open(os.path.join(p.OUT, "refine.tsv"), "a")
    for name, status in todo:
        tmp = tempfile.mkdtemp(prefix="refine_")
        addr, body = funcs[name]
        code = draft(name, body, tmp)
        ok, out = check(name, code, tmp)
        result = "miss"
        t0 = time.time()
        for attempt in range(1, args.tries + 1):
            problem = re.sub(r"Z:\\[^\n]*", "", out)
            reply = ask(args.model, PROMPT.format(asm=body, code=code, problem=problem))
            m = re.search(r"```(?:c|C)?\n(.*?)```", reply, re.S)
            if not m:
                continue
            code = m.group(1)
            ok, out = check(name, code, tmp)
            if ok:
                result = f"match@{attempt}"
                matched += 1
                if args.write:
                    d = os.path.join(p.ROOT, "src/game/auto", f"{addr & ~0xFFFF:08X}")
                    os.makedirs(d, exist_ok=True)
                    open(os.path.join(d, f"{name}.c"), "w").write('#include "game/auto/m2c_prelude.h"\n' + code)
                break
        log.write(f"{name}\t{status}\t{result}\t{time.time() - t0:.0f}s\n")
        log.flush()
        print(name, status, result, f"{time.time() - t0:.0f}s", flush=True)
        shutil.rmtree(tmp, ignore_errors=True)
    print(f"done: {matched}/{len(todo)} matched in {time.time() - start:.0f}s")


if __name__ == "__main__":
    main()
