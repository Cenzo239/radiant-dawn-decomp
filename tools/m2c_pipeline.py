#!/usr/bin/env python3
"""Draft unmatched functions with m2c, compile them and keep the exact matches.

No LLM involved. Each function gets its own source file, so -inline auto can't
pull one draft into another.

Usage:
  tools/m2c_pipeline.py --matched oks.txt [--start 0x8014C9F8 --end 0x80163164]
      [--limit N] [--jobs N] [--write]

--matched is a file of `OK fn_X` lines from check_func.py runs (or plain names).
--write copies matches into src/game/auto/. Without it the run only reports.
A summary of every function's outcome goes to build/m2c/results.tsv.
"""
import argparse
import glob
import multiprocessing
import os
import re
import shutil
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
M2C = os.path.join(ROOT, "..", "tools", "m2c", "repo", "m2c.py")
PY = os.environ.get("M2C_PYTHON", sys.executable)
ASM = os.path.join(ROOT, "build/RFEE01/asm")
OUT = os.path.join(ROOT, "build/m2c")

HEADER = """#pragma mpwc_relax on
#define NULL 0
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;
"""

# Flag variants tried in order. Later ones only run if the earlier ones miss.
VARIANTS = [
    ("plain", ""),
    ("lmw", "#pragma use_lmw_stmw on\n"),
]

M2C_FLAGS = [
    [],
    ["--no-andor"],
    ["--gotos-only"],
]

FN_RE = re.compile(r"^\.fn (\S+?), \w+", re.M)


def load_functions():
    """name -> (address, asm text) for every function in the auto-split asm."""
    funcs = {}
    for path in sorted(glob.glob(os.path.join(ASM, "*.s"))):
        text = open(path).read()
        for m in FN_RE.finditer(text):
            name = m.group(1)
            end = text.find(f".endfn {name}\n", m.end())
            if end < 0:
                continue
            body = text[m.start():end + len(f".endfn {name}\n")]
            addr = re.search(r"/\* ([0-9A-F]{8}) ", body)
            if addr:
                funcs[name] = (int(addr.group(1), 16), body)
    return funcs


def load_sizes():
    """Global data sizes from symbols.txt, so arrays address like the original."""
    sizes = {}
    pat = re.compile(r"^(\S+) = (\S+):0x[0-9A-Fa-f]+; // .*?size:0x([0-9A-Fa-f]+)")
    for line in open(os.path.join(ROOT, "config/RFEE01/symbols.txt")):
        m = pat.match(line)
        if m:
            sizes[m.group(1)] = int(m.group(3), 16)
    return sizes


SIZES = load_sizes()
MACROS = open(os.path.join(os.path.dirname(M2C), "m2c_macros.h")).read()


def fix_draft(draft):
    """Make m2c's output acceptable to MWCC in C mode."""
    # m2c infers prototypes per call site, and they can disagree. Unprototyped
    # declarations accept any arguments.
    def fix_decl(m):
        return f"{m.group(1)} {m.group(2)}();"
    draft = re.sub(r"^([\w ]+?\s\**)\s*(fn_[0-9A-F]+|\w+)\([^;{]*\);\s*/\* extern \*/$",
                   lambda m: f"{m.group(1).rstrip()} {m.group(2)}();", draft, flags=re.M)
    # Globals of unknown type become byte arrays of their real size, so offsets
    # are in bytes and small or large addressing comes out right.
    unk = re.findall(r"^extern M2C_UNK (\w+);$", draft, flags=re.M)
    for name in unk:
        size = SIZES.get(name, 0x1000)
        draft = draft.replace(f"extern M2C_UNK {name};", f"extern u8 {name}[{size:#x}];")
        draft = re.sub(rf"&{name}\b", name, draft)
    # void* arithmetic isn't allowed; byte pointers behave the way m2c assumes.
    draft = re.sub(r"\bvoid \*", "s8 *", draft)
    return draft


def load_matched(path):
    names = set()
    for line in open(path):
        m = re.search(r"(?:OK\s+)?(\S+)", line.strip())
        if m:
            parts = line.split()
            names.add(parts[1] if parts and parts[0] == "OK" else parts[0])
    return names


def add_passthrough(draft, name, count):
    """Add leading parameters the draft dropped and pass them to the first call."""
    params = ", ".join(f"s32 p{i}" for i in range(count))
    args = ", ".join(f"p{i}" for i in range(count))
    new, n = re.subn(rf"\b{name}\(void\)", f"{name}({params})", draft, count=1)
    if not n:
        new, n = re.subn(rf"\b{name}\(([^)]*)\) \{{", lambda m: f"{name}({params}, {m.group(1)}) {{", draft, count=1)
    if not n:
        return None
    head, sep, body = new.partition(f"{name}(")
    body, n = re.subn(r"\b(fn_[0-9A-F]+)\(\)", rf"\1({args})", body, count=1)
    if not n:
        body, n = re.subn(r"\b(fn_[0-9A-F]+)\(", rf"\1({args}, ", body, count=1)
    return head + sep + body if n else None


def chain_calls(draft):
    """`g(x); f(y);` with r3 untouched between them becomes `f(g(x), y);`."""
    def join(m):
        inner = m.group(4)
        return f"{m.group(1)}{m.group(3)}({m.group(2)}{', ' + inner if inner else ''});"
    new, n = re.subn(r"^(\s*)(fn_[0-9A-F]+\([^;\n]*\));\n\s*(fn_[0-9A-F]+)\(([^;\n]*)\);$", join, draft, flags=re.M)
    return new if n else None


def repair_casts(code, out):
    """Cast assignments the compiler rejects for int-to-pointer conversion."""
    m = re.search(r"#\s+(\d+):[^\n]*\n#\s+Error:[^\n]*\n#\s+\(10209\) illegal implicit conversion from '[^']*' to", out)
    if not m:
        return None
    lines = code.split("\n")
    i = int(m.group(1)) - 1
    if i >= len(lines):
        return None
    fixed = re.sub(r"^(\s*[^=;]+?)\s=\s(.+);$", r"\1 = (void *)(\2);", lines[i])
    if fixed == lines[i]:
        return None
    lines[i] = fixed
    return "\n".join(lines)


def try_draft(name, draft, tmp):
    """Compile a draft with each pragma variant. Returns (status, code, note)."""
    last, note = "compile_failed", ""
    for label, prefix in VARIANTS:
        src = os.path.join(tmp, f"{name}.c")
        code = HEADER + MACROS + "\n" + prefix + draft
        for _ in range(8):
            open(src, "w").write(code)
            c = subprocess.run(
                [sys.executable, "-I", os.path.join(ROOT, "tools/check_func.py"), src],
                capture_output=True, text=True, cwd=ROOT, timeout=120,
            )
            out = c.stdout
            if "COMPILE FAILED" not in out:
                break
            fixed = repair_casts(code, out)
            if fixed is None:
                break
            code = fixed
        if "COMPILE FAILED" in out:
            err = re.search(r"\((\d{5})\) ([^\n]*)", out)
            if last == "compile_failed":
                note = (err.group(1) + " " + err.group(2)[:50]) if err else "?"
            continue
        if c.returncode == 0 and f"OK   {name}" in out:
            return "match", code, label
        last = "mismatch"
        d = re.search(r"(\d+) of (\d+) words differ", out)
        size = re.search(r"size 0x", out)
        note = (f"{d.group(1)}/{d.group(2)}" + (" size" if size else "")) if d else "?"
    return last, None, note


def run_one(item):
    name, body = item
    tmp = tempfile.mkdtemp(prefix="m2c_")
    best = ("m2c_failed", None, "")
    rank = {"m2c_failed": 0, "m2c_incomplete": 1, "compile_failed": 2, "mismatch": 3}
    try:
        asm = os.path.join(tmp, "f.s")
        open(asm, "w").write(".text\n" + body)
        for flags in M2C_FLAGS:
            r = subprocess.run(
                [PY, M2C, "-t", "ppc-mwcc-c", "--valid-syntax", "--globals=used", *flags, "-f", name, asm],
                capture_output=True, text=True, timeout=120,
            )
            if r.returncode != 0 or not r.stdout.strip():
                continue
            draft = fix_draft(r.stdout)
            if "M2C_ERROR" in draft or "M2C_BSTR" in draft:
                if rank[best[0]] < 1:
                    best = ("m2c_incomplete", None, "")
                continue
            candidates = [draft]
            for transform in (lambda d: add_passthrough(d, name, 1), lambda d: add_passthrough(d, name, 2), chain_calls):
                extra = transform(draft)
                if extra:
                    candidates.append(extra)
            status, note = "compile_failed", ""
            for candidate in candidates:
                st, code, nt = try_draft(name, candidate, tmp)
                if st == "match":
                    return name, st, code, " ".join(flags) + " " + nt
                if candidate is draft:
                    status, note = st, nt
            if rank[status] > rank[best[0]]:
                best = (status, None, note)
        return name, best[0], None, best[2]
    except subprocess.TimeoutExpired:
        return name, "timeout", None, ""
    finally:
        shutil.rmtree(tmp, ignore_errors=True)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--matched", required=True)
    ap.add_argument("--start", type=lambda s: int(s, 16), default=0x800068A0)
    ap.add_argument("--end", type=lambda s: int(s, 16), default=0x8028BCD4,
                    help="exclusive end address (default: start of the runtime library)")
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--jobs", type=int, default=max(1, (os.cpu_count() or 4) - 2))
    ap.add_argument("--write", action="store_true")
    args = ap.parse_args()

    funcs = load_functions()
    matched = load_matched(args.matched)
    todo = sorted((a, n, b) for n, (a, b) in funcs.items()
                  if n not in matched and args.start <= a < args.end)
    if args.limit:
        todo = todo[:args.limit]
    print(f"{len(funcs)} functions, {len(matched)} already matched, {len(todo)} to try", flush=True)

    os.makedirs(OUT, exist_ok=True)
    counts = {}
    size_matched = 0
    with multiprocessing.Pool(args.jobs) as pool, open(os.path.join(OUT, "results.tsv"), "w") as res:
        items = [(n, b) for _a, n, b in todo]
        for i, (name, status, code, note) in enumerate(pool.imap_unordered(run_one, items, chunksize=4)):
            counts[status] = counts.get(status, 0) + 1
            res.write(f"{name}\t{status}\t{note}\n")
            if code:
                size_matched += funcs[name][1].count("\n/* ") * 4
                if args.write:
                    addr = funcs[name][0]
                    d = os.path.join(ROOT, "src/game/auto", f"{addr & ~0xFFFF:08X}")
                    os.makedirs(d, exist_ok=True)
                    open(os.path.join(d, f"{name}.c"), "w").write(code.replace(HEADER + MACROS + "\n", '#include "game/auto/m2c_prelude.h"\n'))
            if (i + 1) % 200 == 0:
                print(i + 1, counts, flush=True)
    print("done", counts, f"matched about {size_matched} bytes")


if __name__ == "__main__":
    main()
