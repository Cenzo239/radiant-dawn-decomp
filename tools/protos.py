#!/usr/bin/env python3
"""Compare every declaration of a game function with its definition.

Each source file declares the functions it calls with its own stand-in types,
so types can't be compared by name. What decides the call ABI is the shape:
how many parameters, and for each whether it travels in an integer or a float
register (or is a struct by value / reference), plus the kind of return value.
This tool reduces every definition and prototype of fn_XXXXXXXX to that shape
and reports the functions whose declarations disagree with the definition.

Usage:
  tools/protos.py [--tsv out.tsv] [--all]
Definitions are taken from exact files first, then equiv/, then wip/.
"""
import argparse
import collections
import glob
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
FLOAT = {"f32", "f64", "float", "double"}
INT = {"int", "s8", "u8", "s16", "u16", "s32", "u32", "s64", "u64", "char", "short", "long", "unsigned",
       "signed", "BOOL", "bool", "size_t", "wchar_t", "uint", "u_int"}
SIG = re.compile(r"(?:^|[;{}\n])\s*((?:static\s+|inline\s+|extern\s+|const\s+|unsigned\s+|signed\s+|struct\s+|class\s+|volatile\s+)*"
                 r"[A-Za-z_][\w:<>]*(?:\s+const)?[\s*&]*?)\s*\b(fn_[0-9A-F]{8})\s*\(([^(){};]*)\)\s*(const\s*)?([;{])")


def strip(text):
    text = re.sub(r"/\*.*?\*/", " ", text, flags=re.S)
    text = re.sub(r"//[^\n]*", " ", text)
    return re.sub(r'"(?:\\.|[^"\\])*"', '""', text)


def kind(decl, is_ret=False):
    """I integer/pointer register, F float register, S struct by value, V void, ? unknown, ... varargs."""
    d = decl.strip()
    if d == "...":
        return "..."
    d = re.sub(r"=.*$", "", d)
    d = re.sub(r"\b(static|inline|extern|register)\b", " ", d).strip()
    if not d or d == "void":
        return "V"
    if "*" in d or "&" in d or "[" in d:
        return "I"
    words = [w for w in re.split(r"\s+", d) if w not in ("const", "volatile", "register", "struct", "class", "enum", "static", "inline", "extern")]
    if not words:
        return "?"
    # The last word is the parameter name unless the declaration is a bare type.
    types = words[:-1] if len(words) > 1 and not is_ret else words
    if not types:
        types = words
    if any(w in FLOAT for w in types):
        return "F"
    if any(w in ("u64", "s64") for w in types) or types.count("long") == 2:
        return "L"   # a 64-bit integer takes an aligned register pair (r3:r4, r5:r6, ...)
    if all(w in INT for w in types):
        return "I"
    return "S"   # a named type by value: struct, class, enum or typedef


def shape(ret, params):
    ps = [p for p in params.split(",")] if params.strip() else []
    if len(ps) == 1 and ps[0].strip() == "void":
        ps = []
    return kind(ret, True) + "(" + "".join(kind(p) for p in ps) + ")"


def params_of(sh):
    return sh[sh.index("(") + 1:-1].replace("S", "I")


def severity(defn, decl, path):
    """hard: a caller using this declaration passes arguments in other registers.
    soft: only the declared return kind differs. none: unprototyped C declaration."""
    a, b = params_of(defn), params_of(decl)
    if b == "" and path.endswith((".c", ".h")) and a != "":
        return "none"
    if a != b and not (b.endswith("...") or a.endswith("...")):
        return "hard"
    ra, rb = defn[0], decl[0]
    if ra != rb and "F" in (ra, rb):
        return "hard"
    if ra != rb and "S" in (ra, rb) and "V" in (ra, rb):
        return "soft"   # struct return uses a hidden pointer: check by hand
    return "none" if ra == rb or {ra, rb} <= {"I", "S", "V"} else "soft"


def needed(name, sym):
    """(integer registers, float registers) the original code of name reads before writing, or None."""
    try:
        regs = sym.sure_args(name)
    except Exception:
        return None
    if regs is None:
        return None
    ni = max([int(r[1:]) - 2 for r in regs if r[0] == "r"], default=0)
    nf = max([int(r[1:]) for r in regs if r[0] == "f" and int(r[1:]) <= 8], default=0)
    return ni, nf


def passed(sh):
    """(highest integer register used, counted from r3, float registers, hidden struct pointer, variadic)."""
    ps = sh[sh.index("(") + 1:-1]
    hidden = 1 if sh[0] == "S" else 0   # a struct result may travel through a hidden pointer in r3
    ni = 0
    for k in ps.replace("...", ""):
        if k == "L":
            ni += ni % 2 + 2      # register pairs start at r3, r5, r7 or r9
        elif k in "IS":
            ni += 1
    return ni, ps.count("F"), hidden, ps.endswith("...")


def rank(path):
    return 2 if "/wip/" in path else 1 if "/equiv/" in path else 0


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--tsv")
    ap.add_argument("--all", action="store_true", help="also list functions that agree")
    ap.add_argument("--catalog", help="write one line per function: shape, definition text and file, "
                                      "and the audited status from docs/signatures")
    ap.add_argument("--asm", help="write a second report: declarations and definitions that pass fewer "
                                  "argument registers than the original code reads")
    args = ap.parse_args()
    defs, protos = {}, collections.defaultdict(lambda: collections.defaultdict(list))
    calls = collections.defaultdict(set)   # function -> files that call it (not just declare it)
    argcs = collections.defaultdict(lambda: collections.defaultdict(list))  # function -> file -> argument counts
    files = [f for f in glob.glob(os.path.join(ROOT, "src/game/**/*"), recursive=True)
             if f.endswith((".c", ".cpp", ".h", ".hpp"))]
    for path in files:
        for base, alias in re.findall(r"typedef\s+((?:unsigned\s+|signed\s+)?[A-Za-z_]\w*)\s+([A-Za-z_]\w*)\s*;",
                                      open(path, errors="replace").read()):
            b = base.split()[-1]
            if b in FLOAT:
                FLOAT.add(alias)
            elif b in INT and b not in ("u64", "s64"):
                INT.add(alias)
    includers = collections.defaultdict(set)   # header basename -> files that include it
    for path in files:
        rel = os.path.relpath(path, ROOT)
        try:
            text = strip(open(path, errors="replace").read())
        except OSError:
            continue
        for h in re.findall(r'#\s*include\s+"([^"]+)"', open(path, errors="replace").read()):
            includers[os.path.basename(h)].add(rel)
        decl_at = {m.start(2) for m in SIG.finditer(text)}
        for m in re.finditer(r"\b(fn_[0-9A-F]{8})\s*\(", text):
            if m.start(1) in decl_at:
                continue
            # argument counts of real calls, for unprototyped C declarations
            depth, i, argc, empty = 1, m.end(), 1, True
            while i < len(text) and depth:
                ch = text[i]
                if ch in "([{":
                    depth += 1
                elif ch in ")]}":
                    depth -= 1
                elif ch == "," and depth == 1:
                    argc += 1
                if depth and not ch.isspace():
                    empty = False
                i += 1
            argcs[m.group(1)][rel].append(0 if empty else argc)
        uses = collections.Counter(re.findall(r"\b(fn_[0-9A-F]{8})\s*\(", text))
        for m in SIG.finditer(text):
            uses[m.group(2)] -= 1
        for n, k in uses.items():
            if k > 0:
                calls[n].add(rel)
        for m in SIG.finditer(text):
            ret, name, params, _c, end = m.groups()
            if re.search(r"\b(return|else|case|default|goto|new|delete|sizeof)\b", ret) or re.search(r"(?<!:):(?!:)", ret):
                continue
            sh = shape(ret, params)
            if end == "{":
                if "inline" in ret:
                    continue
                if name not in defs or rank(rel) < rank(defs[name][1]):
                    defs[name] = (sh, rel, f"{ret.strip()} {name}({params.strip()})")
            else:
                protos[name][sh].append(rel)
    rows = []
    for name in sorted(set(defs) | set(protos)):
        d = defs.get(name)
        shapes = protos.get(name, {})
        if d:
            sev = {s: max((severity(d[0], s, f) for f in fs), key=["none", "soft", "hard"].index) for s, fs in shapes.items()}
            bad = {s: fs for s, fs in shapes.items() if sev[s] != "none"}
            status = "hard" if "hard" in sev.values() else "soft" if "soft" in sev.values() else "ok"
        else:
            ref = max(shapes, key=lambda s: len(shapes[s])) if shapes else ""
            sev = {s: max((severity(ref, s, f) for f in fs), key=["none", "soft", "hard"].index) for s, fs in shapes.items()}
            bad = {s: fs for s, fs in shapes.items() if sev[s] == "hard"}
            bad = shapes if bad else {}
            status = "no definition, declarations disagree" if bad else "no definition"
        if status in ("ok", "no definition") and not args.all:
            continue
        rows.append((name, status, d[0] if d else "", d[1] if d else "",
                     "; ".join(f"{s} x{len(fs)} ({fs[0]})" for s, fs in sorted(bad.items(), key=lambda kv: -len(kv[1])))))
    if args.asm:
        import sys
        sys.argv = sys.argv[:1] + ["--xargs"]
        sys.path.insert(0, os.path.join(ROOT, "tools/equiv"))
        import inspect
        import symcheck as sym
        os.chdir(ROOT)
        # symcheck's callee_args answers "may read" (unknown callees read everything). Here we want
        # "certainly reads": unknown, indirect and too-deep callees count as reading nothing.
        src = inspect.getsource(sym.callee_args)
        assert "ARGREGS if ca is None else sorted(ca)" in src and "uu = uu + ARGREGS" in src
        src = src.replace("def callee_args(", "def sure_args(").replace("callee_args(tg, depth + 1)", "sure_callee(tg, depth + 1)")
        src = src.replace("ARGREGS if ca is None else sorted(ca)", "[] if ca is None else sorted(ca)")
        src = src.replace("uu = uu + ARGREGS", "uu = uu").replace("CALLEE", "SURE")
        assert "if t.get(\"jt\"): s_ = list(range(len(bl)))" in src
        src = src.replace("if t.get(\"jt\"): s_ = list(range(len(bl)))", "if t.get(\"jt\"): s_ = []")
        # ps_sum0/ps_sum1 read their third/second operand for one half only; PSMTXMultVec names an
        # unused register there. Don't count it as a certain read.
        real_decode = sym.decode

        def sure_decode(mn, ops):
            d = real_decode(mn, ops)
            if d["base"] in ("ps_sum0", "ps_sum1") and len(ops) == 4:
                drop = ops[2] if d["base"] == "ps_sum0" else ops[3]
                if drop not in (ops[1], ops[3] if d["base"] == "ps_sum0" else ops[2]):
                    d["uses"] = [u for u in d["uses"] if u != drop]
            return d
        sym.SURE = {}
        sym.VIRTTHIS = False
        sym.XMODE = True
        exec(src, sym.__dict__)
        sym.decode = sure_decode

        def sure_callee(fn, depth):
            # A callee that reads (nearly) every argument register is variadic: what it really
            # receives depends on the call, so it says nothing about its caller's parameters.
            r = sym.sure_args(fn, depth)
            return set() if r and sum(x[0] == "r" for x in r) >= 7 else r
        sym.sure_callee = sure_callee
        short = []
        for name in sorted(set(defs) | set(protos)):
            need = needed(name, sym)
            if not need or need == (0, 0):
                continue
            cands = [("definition", defs[name][0], [defs[name][1]])] if name in defs else []
            cands += [("declaration", s, fs) for s, fs in protos.get(name, {}).items()]
            for what, sh, fs in cands:
                ni, nf, hidden, var = passed(sh)
                if var:
                    continue
                if sh.endswith("()") and all(f.endswith((".c", ".h")) for f in fs) and what == "declaration":
                    # unprototyped: look at the argument counts of the actual calls
                    low = [f for f in set(fs) for n in argcs[name].get(f, []) if n < max(need)]
                    if low:
                        short.append((name, "unprototyped call", sh, f"reads {need[0]} int, {need[1]} float", "check",
                                      str(len(set(low))), "; ".join(sorted(set(low))), str(len(set(low))),
                                      "; ".join(sorted(set(low)))))
                    continue
                if ni + hidden < need[0] or nf < need[1]:
                    sure = "yes" if ni + hidden < need[0] and not hidden or nf < need[1] else "check"
                    via = {f for f in fs if f.endswith((".h", ".hpp"))
                           for g in includers.get(os.path.basename(f), ()) if g in calls[name]}
                    called = sorted((set(fs) & calls[name]) | via) if what == "declaration" else []
                    short.append((name, what, sh, f"reads {need[0]} int, {need[1]} float", sure, str(len(set(fs))),
                                  "; ".join(sorted(set(fs))), str(len(called)), "; ".join(called)))
        with open(args.asm, "w") as f:
            f.write("# function\twhat\tshape\toriginal code\tcertain\tfiles\tfile list\tfiles that call it with this declaration\tthose files\n")
            for r in short:
                f.write("\t".join(r) + "\n")
        c2 = collections.Counter((r[1]) for r in short)
        print(f"too few argument registers: {dict(c2)} in {len(set(r[0] for r in short))} functions")
    if args.catalog:
        audited = {}
        for sig in glob.glob(os.path.join(ROOT, "docs/signatures/*.tsv")):
            for line in open(sig):
                cols = line.rstrip("\n").split("\t")
                if len(cols) >= 3 and cols[0].startswith("fn_"):
                    audited[cols[0]] = (cols[1], cols[2])
        with open(args.catalog, "w") as f:
            f.write("# function\tshape\tdefinition\tdefinition file\taudited shape\taudit status\tdeclaration shapes elsewhere\n")
            for name in sorted(set(defs) | set(protos)):
                d = defs.get(name, ("", "", ""))
                a = audited.get(name, ("", ""))
                others = ", ".join(f"{s} x{len(fs)}" for s, fs in sorted(protos.get(name, {}).items()) if s != d[0])
                f.write("\t".join([name, d[0], d[2], d[1], a[0], a[1], others]) + "\n")
        print(f"catalog: {len(set(defs) | set(protos))} functions")
    total = len(set(defs) | set(protos))
    print(f"{total} functions seen, {len(defs)} with a definition")
    c = collections.Counter(r[1] for r in rows)
    for k, v in c.items():
        print(f"  {k}: {v}")
    if args.tsv:
        with open(args.tsv, "w") as f:
            f.write("# function\tstatus\tshape of definition\tdefinition file\tdisagreeing declarations\n")
            for r in rows:
                f.write("\t".join(r) + "\n")


if __name__ == "__main__":
    main()
