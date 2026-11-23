#!/usr/bin/env python3
"""Form a translation-unit source from the per-function files.

Input: a list of game functions (one link unit, address order). For each function the exact
definition is taken from its per-function file (build/tmp/buildtree/survey.json says which file
reports it OK). Each file is split into top-level chunks (preprocessor lines, declarations,
function definitions); the TU is then emitted in address order:

  - #include lines are hoisted to the top (deduplicated).
  - For C++ TUs every source file gets its own namespace (tu_f<N>), so the file-local types
    of different files (each file defines its own Vec, structs with padding, ...) cannot clash.
    The fn_/lbl_ names are extern "C", so namespaces do not change any symbol. C files in a
    C++ TU are wrapped in extern "C" and their unprototyped declarations `T f();` become
    `T f(...)` (same calling convention for MWCC: arguments as passed, CR6 set).
  - Before a function, the not yet emitted chunks of its file that precede it are emitted
    (types, externs, statics, pragmas) in file order, so each file keeps its own declaration
    order (C++ file statics are laid out in declaration order).
  - Pragmas are scoped per file with #pragma push/pop, re-emitting the file's earlier pragmas.
  - Definitions of fn_ functions that are not part of the unit become prototypes.
  - Pure-C TUs are emitted without namespaces; identical chunks are deduplicated and a
    conflicting redefinition is reported (the TU then needs a shared header first).

Usage: python3 -I tools/build/gen_tu.py OUT.cpp fn_A fn_B ... | --range 0x800CF95C 0x800CFAD4
"""
import argparse
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, HERE)
import dolmodel as M  # noqa: E402

SURVEY = os.path.join(ROOT, "build/tmp/buildtree/survey.json")
FN_RE = re.compile(r"^fn_[0-9A-F]{8}$")


class Chunk:
    __slots__ = ("kind", "text", "name", "extc", "file", "idx")

    def __init__(self, kind, text, name=None, extc=False):
        self.kind, self.text, self.name, self.extc = kind, text, name, extc
        self.file = None
        self.idx = 0

    def __repr__(self):
        return f"<{self.kind} {self.name or self.text[:30]!r}>"


def split_chunks(src):
    """Split C/C++ source into top-level chunks."""
    chunks = []
    i, n = 0, len(src)
    cur = []
    depth = 0
    extc_depth = []  # depth at which an extern "C" { block was opened
    pending_comment = []

    def flush(kind="decl", name=None):
        text = "".join(cur).strip()
        if text:
            chunks.append(Chunk(kind, text, name, bool(extc_depth)))
        cur.clear()

    at_line_start = True
    while i < n:
        c = src[i]
        if c == "\n":
            cur.append(c)
            i += 1
            at_line_start = True
            continue
        if at_line_start and depth == 0 and c in " \t":
            cur.append(c)
            i += 1
            continue
        if at_line_start and depth == 0 and c == "#":
            # preprocessor line (with continuations)
            j = i
            while True:
                k = src.find("\n", j)
                if k < 0:
                    k = n
                if src[k - 1:k] == "\\":
                    j = k + 1
                    continue
                break
            line = src[i:k]
            if strip_comments("".join(cur)).strip():
                # a directive inside a declaration: keep it inline
                cur.append(line + "\n")
            else:
                flush()   # a leading comment becomes its own chunk
                chunks.append(Chunk("pp", line.strip(), None, bool(extc_depth)))
            i = k + 1
            at_line_start = True
            continue
        at_line_start = False
        if src.startswith("//", i):
            k = src.find("\n", i)
            k = n if k < 0 else k
            cur.append(src[i:k])
            i = k
            continue
        if src.startswith("/*", i):
            k = src.find("*/", i + 2)
            k = n if k < 0 else k + 2
            cur.append(src[i:k])
            i = k
            continue
        if c in "\"'":
            j = i + 1
            while j < n and src[j] != c:
                j += 2 if src[j] == "\\" else 1
            cur.append(src[i:j + 1])
            i = j + 1
            continue
        if c == "{":
            head = strip_comments("".join(cur)).strip()
            if depth == 0 and re.fullmatch(r'extern\s+"C"', head):
                cur.clear()
                extc_depth.append(depth)
                i += 1
                continue
            depth += 1
            cur.append(c)
            i += 1
            continue
        if c == "}":
            if depth == 0 and extc_depth:
                flush()
                extc_depth.pop()
                i += 1
                continue
            depth -= 1
            cur.append(c)
            i += 1
            if depth == 0:
                head = strip_comments("".join(cur))
                pre = head[:head.index("{")]
                if is_function_head(pre):
                    flush("func", function_name(pre))
            continue
        if c == ";" and depth == 0:
            cur.append(c)
            i += 1
            flush()
            continue
        cur.append(c)
        i += 1
    flush()
    return chunks


def strip_comments(s):
    s = re.sub(r"/\*.*?\*/", " ", s, flags=re.S)
    return re.sub(r"//[^\n]*", " ", s)


def is_function_head(pre):
    p = pre.strip()
    if not p.endswith(")") and not re.search(r"\)\s*(const)?\s*$", p) and ":" not in p:
        return False
    if re.match(r"^(typedef|struct|union|enum|class|namespace)\b", p) and "(" not in p.split("{")[0]:
        return False
    if re.match(r"^(typedef)\b", p):
        return False
    if "=" in p.split("(")[0]:
        return False
    return "(" in p


def function_name(pre):
    p = strip_comments(pre)
    # name before the first '(' that opens the parameter list
    m = re.search(r"([A-Za-z_~][\w:~]*)\s*\(", p)
    return m.group(1).split("::")[-1] if m else None


def needs_c_linkage(text):
    t = strip_comments(text).strip()
    if re.match(r"^(typedef|struct|class|union|enum|template|using|namespace|static|inline|friend)\b", t):
        return False
    if re.match(r"^(const\s+)?(struct|class|union|enum)\s+\w+\s*(:[^{]*)?\{", t):
        return False
    return True


_STR_RE = re.compile(r'"(?:[^"\\\n]|\\.)*"|\'(?:[^\'\\\n]|\\.)*\'')
_CALL_RE = re.compile(r"(?<![\w.>:])(fn_[0-9A-F]{8})(\s*\()")


def no_adl_calls(text):
    """C++ units: write calls of fn_ functions in a body as (fn_X)(...). A file may declare
    fn_X inside its namespace while a hoisted header declares it globally; with an argument of
    a global class type, argument-dependent lookup finds both and MWCC calls the call ambiguous.
    A parenthesised name disables ADL (same function, same code)."""
    k = text.find("{")
    if k < 0:
        return text
    body = text[k:]
    parts = []
    pos = 0
    for m in _STR_RE.finditer(body):
        parts.append(_CALL_RE.sub(r"(\1)\2", body[pos:m.start()]))
        parts.append(m.group(0))
        pos = m.end()
    parts.append(_CALL_RE.sub(r"(\1)\2", body[pos:]))
    return text[:k] + "".join(parts)


def prototype_of(text):
    """Turn a function definition into a declaration."""
    body = strip_comments(text)
    k = body.index("{")
    return body[:k].rstrip() + ";"


_TPC_DIRECTIVE = re.compile(r"^\s*#\s*(if|ifdef|ifndef|elif|else|endif)\b(.*)$")


def _tpc_value(kw, expr):
    """Value of a conditional that only tests TARGET_PC, with TARGET_PC undefined (False /
    True), or None for any other condition."""
    e = re.sub(r"/\*.*?\*/|//.*$", "", expr).strip()
    e = re.sub(r"\s+", "", e)
    while e.startswith("(") and e.endswith(")") and e.count("(") == 1:
        e = e[1:-1]
    if kw == "ifdef":
        return False if e == "TARGET_PC" else None
    if kw == "ifndef":
        return True if e == "TARGET_PC" else None
    neg = e.startswith("!")
    if neg:
        e = e[1:]
    if e in ("TARGET_PC", "defined(TARGET_PC)", "definedTARGET_PC"):
        return neg
    return None


def strip_target_pc(text):
    """Resolve `#if TARGET_PC` / `#ifdef TARGET_PC` / `#if defined(TARGET_PC)` (and their
    negations, with #elif/#else and nesting) as if TARGET_PC were undefined, like unifdef
    -UTARGET_PC: the host branches of the port go, the original code stays; every other
    conditional is left as it is. Without TARGET_PC the preprocessor sees the same code, but the
    textual chunker would otherwise read both branches."""
    if "TARGET_PC" not in text:
        return text
    out = []
    stack = []    # {"known": bool, "cur": bool, "taken": bool, "rest": bool}

    def active(frames):
        return all(f["cur"] for f in frames)
    for line in text.split("\n"):
        m = _TPC_DIRECTIVE.match(line)
        if not m:
            if active(stack):
                out.append(line)
            continue
        kw, expr = m.group(1), m.group(2)
        parent = active(stack[:-1]) if kw in ("elif", "else", "endif") else active(stack)
        if kw in ("if", "ifdef", "ifndef"):
            v = _tpc_value(kw, expr)
            if v is None:
                stack.append({"known": False, "cur": True, "taken": False, "rest": False})
                if parent:
                    out.append(line)
            else:
                stack.append({"known": True, "cur": v, "taken": v, "rest": False})
            continue
        if not stack:     # unbalanced: leave it
            out.append(line)
            continue
        f = stack[-1]
        if kw == "elif":
            v = _tpc_value("if", expr)
            if f["known"]:
                if f["taken"]:
                    f["cur"] = False
                elif v is None:     # the first real branch: it becomes the #if
                    f.update(known=False, cur=True)
                    if parent:
                        out.append(re.sub(r"#\s*elif", "#if", line, count=1))
                else:
                    f["cur"] = f["taken"] = v
            else:
                if f["rest"] or v is False:
                    f["cur"] = False
                elif v is True:     # always taken: the remaining branches are dead
                    f["cur"], f["rest"] = True, True
                    if parent:
                        out.append(re.sub(r"#\s*elif.*$", "#else", line))
                else:
                    f["cur"] = True
                    if parent:
                        out.append(line)
        elif kw == "else":
            if f["known"]:
                f["cur"] = not f["taken"]
                f["taken"] = True
            elif f["rest"]:
                f["cur"] = False
            else:
                f["cur"] = True
                if parent:
                    out.append(line)
        else:   # endif
            stack.pop()
            if not f["known"] and parent:
                out.append(line)
    return "\n".join(out)


def read_source(p):
    """A per-function source file as the generator reads it (TARGET_PC branches resolved)."""
    return strip_target_pc(open(os.path.join(ROOT, p), encoding="utf-8", errors="replace").read())


def _self_test_target_pc():
    src = "\n".join([
        "int a;",
        "#if TARGET_PC",
        "int host1(void) { return 1; }",
        "#else",
        "int orig1(void) { return 1; }",
        "#endif",
        "#ifdef TARGET_PC",
        "#if X",
        "int host2;",
        "#endif",
        "#endif",
        "#if !defined(TARGET_PC)",
        "int orig2;",
        "#else",
        "int host3;",
        "#endif",
        "#if X",
        "int x1;",
        "#elif defined(TARGET_PC)",
        "int host4;",
        "#else",
        "int x2;",
        "#endif",
        "#if defined(TARGET_PC)",
        "int host5;",
        "#elif Y",
        "int y1;",
        "#else",
        "int y2;",
        "#endif",
        "#ifndef TARGET_PC",
        "#ifdef Z",
        "int z1;",
        "#endif",
        "#endif",
        "#if X",
        "int x3;",
        "#elif !TARGET_PC",
        "int orig3;",
        "#else",
        "int host6;",
        "#endif",
    ])
    want = "\n".join([
        "int a;",
        "int orig1(void) { return 1; }",
        "int orig2;",
        "#if X", "int x1;", "#else", "int x2;", "#endif",
        "#if Y", "int y1;", "#else", "int y2;", "#endif",
        "#ifdef Z", "int z1;", "#endif",
        "#if X", "int x3;", "#else", "int orig3;", "#endif",
    ])
    got = strip_target_pc(src)
    assert got == want, "strip_target_pc self-test failed:\n" + got
    assert strip_target_pc("#if X\nint a;\n#endif") == "#if X\nint a;\n#endif"
    print("strip_target_pc: ok")


def preprocess(path):
    import shlex
    import subprocess
    sys.path.insert(0, os.path.join(ROOT, "tools"))
    import check_func as CF
    cc = os.path.join(ROOT, "build/compilers/GC/3.0a5.2/mwcceppc.exe")
    flags = [f for f in shlex.split(CF.DEFAULT_FLAGS)]
    r = subprocess.run([CF.WIBO, cc, *flags, "-E", "-ppopt", "pragma", path], cwd=ROOT, capture_output=True, text=True,
                       errors="replace")
    if r.returncode != 0:
        raise RuntimeError(f"preprocess {path}: {r.stdout[-300:]}{r.stderr[-300:]}")
    out = r.stdout
    # the compiler prints option warnings into the same stream
    out = "\n".join(l for l in out.splitlines() if not l.startswith(("###", "#   ")))
    return out


def preprocessed_own(text):
    """The lines of a preprocessed file that come from the file itself (stack depth 0 of the
    compiler's `#line` markers), not from its headers."""
    out, depth = [], 0
    for line in text.split("\n"):
        m = re.search(r"/\* stack depth (\d+) \*/", line)
        if m and line.lstrip().startswith("/* #line"):
            depth = int(m.group(1))
            continue
        if depth == 0:
            out.append(line)
    return "\n".join(out)


def load_ok_files():
    sv = json.load(open(SURVEY))
    ok = {}
    for r in sv:
        if "/equiv/" in r["file"] or r.get("check_rc") is None:
            continue
        for f, st in r.get("funcs", {}).items():
            if st == "OK":
                ok.setdefault(f, []).append(r["file"])
    # prefer region files over auto/ files, then files where every function matches
    # a file another worker moved or deleted since survey.py ran: its functions count as not exact
    for f in list(ok):
        ok[f] = [p for p in ok[f] if os.path.exists(os.path.join(ROOT, p))]
        if not ok[f]:
            del ok[f]
    rc = {r["file"]: r.get("check_rc") for r in sv}
    for f in ok:
        ok[f].sort(key=lambda p: ("/auto/" in p, rc.get(p) != 0, p))
    return ok


ASM_DIR = os.path.join(ROOT, "build/RFEE01/asm")
_asm = {}


def asm_lines():
    """address -> (label lines before it, instruction text) from dtk's disassembly
    (build/RFEE01/asm, every split object has its asm there, C units included)."""
    with _lock:
        return _asm_lines()


def _asm_lines():
    if "idx" not in _asm:
        idx = {}
        line_re = re.compile(r"^/\* ([0-9A-F]{8}) [0-9A-F]{8}  (?:[0-9A-F]{2} ){4}\*/\t(.*)$")
        for dp, _dn, fns in os.walk(ASM_DIR):
            for fn in fns:
                if not fn.endswith(".s"):
                    continue
                labels = []
                for line in open(os.path.join(dp, fn), errors="replace"):
                    if line.startswith(".L_") or line.startswith("lbl_"):
                        labels.append(line.strip())
                        continue
                    m = line_re.match(line)
                    if m:
                        idx[int(m.group(1), 16)] = (labels, m.group(2).strip())
                        labels = []
                    elif not line.startswith("/*"):
                        labels = [] if line.startswith(".fn") or line.startswith(".endfn") else labels
        _asm["idx"] = idx
    return _asm["idx"]


import threading  # noqa: E402
_lock = threading.Lock()


def _dol():
    with _lock:
        if "syms" not in _asm:
            dol, syms = M.Dol(), M.load_symbols()
            _asm["dol"], _asm["syms"] = dol, syms
    return _asm["dol"], _asm["syms"]


def nonmatching_files():
    """function -> per-function files that define it without matching (survey DIFF), best first."""
    with _lock:
        return _nonmatching_files()


def _nonmatching_files():
    if "nm" not in _asm:
        nm = {}
        for r in json.load(open(SURVEY)):
            if "/equiv/" in r["file"] or not r.get("compiled"):
                continue
            for f, st in r.get("funcs", {}).items():
                if st == "DIFF":
                    nm.setdefault(f, []).append(r["file"])
        for f in nm:
            nm[f].sort(key=lambda p: ("/auto/" in p, p))
        _asm["nm"] = nm
    return _asm["nm"]


def asm_body(name):
    """The function's original instructions as MWCC asm (one opword per instruction, so no
    relocation is needed: the unit is linked at the original address, every branch
    displacement, @ha/@l pair and r2/r13 offset is already right). dtk's disassembly is kept
    as a comment on each word."""
    dol, S = _dol()
    o = S[name]
    idx = asm_lines()
    data = dol.read(o.addr, o.size)
    out = []
    for k in range(0, o.size, 4):
        a = o.addr + k
        labels, ins = idx.get(a, ([], ""))
        for lab in labels:
            if k:
                out.append(f"    /* {lab} */\n")
        w = int.from_bytes(data[k:k + 4], "big")
        out.append(f"    opword 0x{w:08X} /* {a:08X}  {ins.replace('*/', '* /')} */\n")
    return "".join(out)


def c_version_block(f, lang):
    """The non-matching C definition of f (src/game file that check_func reports DIFF), with
    the declarations of its file, for the port: compiled only with -DFE10_NONMATCHING."""
    files = nonmatching_files().get(f)
    if not files:
        return f"/* no C version of {f} yet */\n", None
    p = files[0]
    chunks = split_chunks(read_source(p))
    target = next((ch for ch in chunks if ch.kind == "func" and ch.name == f), None)
    if target is None:
        return f"/* C version of {f}: {p} (made by macros, see the file) */\n", p
    cfile = p.endswith(".c")
    out = [f"#ifdef FE10_NONMATCHING /* C version of {f}, not matching yet: {p} */\n"]
    body = []
    for ch in chunks[:chunks.index(target) + 1]:
        if ch.kind == "pp":
            if ch.text.startswith("#include"):
                out.append(ch.text + "\n")
            else:
                body.append((ch.text, ch.extc))
            continue
        text = ch.text
        if ch.kind == "func" and ch is not target:
            text = prototype_of(text)
        extc = ch.extc or (lang == ".cpp" and cfile) or (lang == ".cpp" and ch.kind == "decl" and needs_c_linkage(text))
        body.append((text, extc))
    if lang == ".cpp":
        out.append(f"namespace tu_nm_{f} {{\n")
    for text, extc in body:
        out.append('extern "C" {\n' + text + '\n}\n' if extc and lang == ".cpp" else text + "\n")
    if lang == ".cpp":
        out.append(f"}} /* namespace tu_nm_{f} */\n")
    out.append("#else\n")
    return "".join(out), p


def ctor_entry(f):
    """A static initialiser's .ctors slot: MWCC emits it for a real C++ __sinit; the per-function
    files write the __sinit as a plain function, so the TU adds the pointer (dtk assigns the
    slot to the unit that owns the function)."""
    import place as PL
    PL.dolmodel()
    o = _dol()[1].get(f)
    if o is None or not any(sec == ".ctors" and w == o.addr for sec, _x, w in PL.eh_entries()):
        return ""
    return (f'__declspec(section ".ctors") static void (* const tu_ctor_{f})(void) = (void (*)(void)){f};\n')


DATA_SECS = (".sdata2", ".rodata", ".data", ".sdata")


def asm_private_data(f, asm_fns, done, shared=False, lang=".c", named=(), decl_text=""):
    """Data only the asm functions of the unit reference (literals, strings, jump tables, ...):
    in the original TU the compiler emitted it at the function's position, so the TU defines
    it there as bytes (static, unnamed for the linker: the opwords need no relocation).

    shared (variant `asmlit`): a float/double literal of .sdata2 whose first user is this asm
    function but which later C functions of the unit also use. Bytes would give the pool a
    second copy (the C code makes its own literal), so the literal is made by the compiler at
    this position instead: a helper function (force_active off, so MWLD dead-strips it; place.py
    models that) uses the same constants; the C functions' literals then pool into the same
    entry, at the original position."""
    import place as PL
    import struct as _st
    S = PL.dolmodel()[0]
    dol = _dol()[0]
    out = []
    for t, _add in S[f].refs:
        o = S.get(t)
        if o is None or o.sec not in DATA_SECS or t in done or not o.size:
            continue
        if not o.refby:
            continue
        if not o.refby <= set(asm_fns):
            if not shared:
                continue
            first = min(o.refby, key=lambda n: S[n].addr if n in S else 1 << 32)
            if first not in asm_fns:
                continue
            if t in named:
                # the C functions reference it by its label (extern lbl_...): define the label here
                try:
                    d = lead_block([t], lang, decl_text).split("\n", 1)[1]
                except (ValueError, KeyError):
                    continue
                done.add(t)
                out.append((o.addr, o, "@@DEF" + d))
                continue
            if o.sec != ".sdata2" or o.size not in (4, 8):
                continue
            stmt = _lit_stmt(dol.read(o.addr, o.size))
            if stmt is None:
                continue
            done.add(t)
            out.append((o.addr, o, stmt))
            continue
        done.add(t)
        if o.sec == ".sdata2" and o.size in (4, 8) and not any(dol.read(o.addr, o.size)):
            # all-zero constant bytes would go to .sbss2: a 0.0 literal pools in .sdata2
            out.append((o.addr, o, "tu_f = 0.0f;" if o.size == 4 else "tu_d = 0.0;"))
            continue
        kind = o.attrs.get("data", "")
        al = int(o.attrs.get("align", "0"), 0) or {"double": 8, "float": 4, "4byte": 4, "2byte": 2, "byte": 1,
                                                  "string": 1, "wstring": 2}.get(kind) or (4 if o.addr % 4 == 0 else 1)
        out.append((o.addr, o, al))
    lines = []
    group = []

    def flush():
        if group:
            body = " ".join(group)
            fn = (f"void tu_lit_{f}_{len(lines)}(void) {{ volatile float tu_f; volatile double tu_d; "
                  f"volatile int tu_i = 0; volatile unsigned int tu_u = 0; {body} }}")
            if lang == ".cpp":
                fn = 'extern "C" { ' + fn + " }"
            lines.append("#pragma push\n#pragma force_active off\n" + fn + "\n#pragma pop\n")
            group.clear()
    names = []
    for addr, o, al in sorted(out, key=lambda x: x[0]):
        if isinstance(al, str) and al.startswith("@@DEF"):
            flush()
            d = al[5:]
            if lang == ".cpp" and not d.startswith('extern "C"'):
                d = 'extern "C" { ' + d.rstrip("\n") + " }\n"
            lines.append(d)
            continue
        if isinstance(al, str):
            group.append(al)
            continue
        flush()
        names.append(o.name)
        b = dol.read(o.addr, o.size)
        const = "const " if o.sec in (".sdata2", ".rodata") else ""
        lines.append(f'__declspec(section "{o.sec}") static {const}unsigned char tu_d_{o.addr:08X}[{o.size}] '
                     f'__attribute__((aligned({al}))) = {{{", ".join("0x%02X" % x for x in b)}}}; /* {o.name} */\n')
    flush()
    return "".join(lines), names


_FLOAT_DECL = r"(?m)^[ \t]*extern\s+(?:const\s+|volatile\s+)*(f32|float|f64|double)\s+%s\s*;"


def literal_rewrites(names, parsed, files, decl_text):
    """Labels of .sdata2 float/double literals that C code reads by name (m2c style,
    `extern f32 lbl_804CCC18;`) -> the C literal of their value (variant `rw=`). In the original
    the compiler made them as literals: written as literals, the compiler pools them again, at
    the first user, and merges them with the same constant used by other functions of the unit
    (a defined variable would be a second entry). Only labels declared as float/double scalars
    whose size matches and whose address is never taken."""
    import math
    import struct as _st
    S = _dol()[1]
    dol = _dol()[0]
    funcs = "".join(strip_comments(ch.text) for p in files for ch in parsed[p] if ch.kind == "func")
    out = {}
    for n in names:
        o = S.get(n)
        if o is None or o.sec != ".sdata2" or o.size not in (4, 8):
            continue
        m = re.search(_FLOAT_DECL % n, decl_text)
        if not m or {"f32": 4, "float": 4, "f64": 8, "double": 8}[m.group(1)] != o.size:
            continue
        if re.search(r"&\s*%s\b" % n, funcs) or re.search(r"\b%s\s*(?:\[|=[^=]|\+\+|--|\+=|-=|\*=|/=)" % n, funcs):
            continue
        v = _st.unpack(">f" if o.size == 4 else ">d", dol.read(o.addr, o.size))[0]
        if not math.isfinite(v):
            continue
        txt = repr(v)
        if "e" not in txt and "." not in txt:
            txt += ".0"
        out[n] = f"({txt}f)" if o.size == 4 else f"({txt})"
    return out


def apply_rewrites(text, rw):
    pat = re.compile(r"\b(%s)\b" % "|".join(map(re.escape, rw)))
    parts, pos = [], 0
    for m in _STR_RE.finditer(text):
        parts.append(pat.sub(lambda x: rw[x.group(1)], text[pos:m.start()]))
        parts.append(m.group(0))
        pos = m.end()
    parts.append(pat.sub(lambda x: rw[x.group(1)], text[pos:]))
    return "".join(parts)


def order_helper(f, unit, named, done, lang):
    """Variant `order`: the .sdata2 float/double literals whose first user in main.dol is the C
    function f, made in their original order by a helper right before it (force_active off,
    dead-stripped like the asmlit helpers). MWCC pools a function's literals in the order its
    code generator meets them, which a matching source need not reproduce (check_func compares
    by symbol); the function's own literals then pool into these entries."""
    import place as PL
    S = PL.dolmodel()[0]
    dol = _dol()[0]
    if f not in S:
        return ""
    stmts = []
    for t, _a in sorted(S[f].refs, key=lambda x: S[x[0]].addr if x[0] in S else 0):
        o = S.get(t)
        if o is None or o.sec != ".sdata2" or o.size not in (4, 8) or t in done or t in named or not o.refby:
            continue
        if not o.refby <= unit:
            continue
        first = min(o.refby, key=lambda n: S[n].addr if n in S else 1 << 32)
        if first != f:
            continue
        st = _lit_stmt(dol.read(o.addr, o.size))
        if st is None:
            continue
        done.add(t)
        stmts.append(st)
    if len(stmts) < 2:
        return ""      # a single literal cannot be out of order
    fn = (f"void tu_ord_{f}(void) {{ volatile float tu_f; volatile double tu_d; "
          f"volatile int tu_i = 0; volatile unsigned int tu_u = 0; {' '.join(stmts)} }}")
    if lang == ".cpp":
        fn = 'extern "C" { ' + fn + " }"
    return "#pragma push\n#pragma force_active off\n" + fn + "\n#pragma pop"


def _lit_stmt(b):
    """A statement that makes MWCC pool the constant with these bytes (float, double, or the
    int/unsigned to floating conversion constant)."""
    import math
    import struct as _st
    if len(b) == 8 and b[:4] == bytes.fromhex("43300000"):
        if b[4:] == bytes.fromhex("80000000"):
            return "tu_d = tu_i;"
        if b[4:] == bytes(4):
            return "tu_d = tu_u;"
    v = _st.unpack(">f" if len(b) == 4 else ">d", b)[0]
    if not math.isfinite(v) or (v != 0 and abs(v) < (1.1754943508222875e-38 if len(b) == 4 else 2.2250738585072014e-308)):
        return None     # (denormals: not a literal of this type, and MWCC rejects them)
    txt = repr(v)
    if "e" not in txt and "." not in txt:
        txt += ".0"
    return f"tu_f = {txt}f;" if len(b) == 4 else f"tu_d = {txt};"


def asm_function(f, lang, data=""):
    """Placeholder text for f as an asm function (the C-unit signature is filled in by
    fix_asm_signatures once the whole TU text is known)."""
    cv, p = c_version_block(f, lang)
    head = f"\n/* ---- {f}: not matching yet, assembled from the original instructions */\n"
    if lang == ".cpp":
        fn = (f'namespace tu_asm {{\n{data}extern "C" {{\nasm void {f}(void) {{\n    nofralloc\n' + asm_body(f) +
              "}\n}\n" + ctor_entry(f) + "} /* namespace tu_asm */\n")
    else:
        fn = data + f"@@ASMSIG {f}@@ {{\n    nofralloc\n" + asm_body(f) + "}\n" + ctor_entry(f)
    tail = "#endif /* FE10_NONMATCHING */\n" if cv.startswith("#ifdef") else ""
    return head + cv + fn + tail


_PP_CACHE = {}


def includes_text(includes):
    return [i + "\n" for i in includes]


def preprocessed_includes(text):
    """The hoisted #include lines of a generated C unit, preprocessed (declarations the
    headers make)."""
    incs = "".join(l + "\n" for l in re.findall(r'(?m)^#\s*include\s*[<"][^>"]+[>"].*$', text))
    if not incs:
        return ""
    with _lock:
        if incs in _PP_CACHE:
            return _PP_CACHE[incs]
    import tempfile
    d = os.path.join(ROOT, "build/tmp/buildtree")
    os.makedirs(d, exist_ok=True)
    fd, path = tempfile.mkstemp(suffix=".c", dir=d)
    try:
        os.write(fd, incs.encode())
        os.close(fd)
        try:
            out = preprocess(os.path.relpath(path, ROOT))
        except RuntimeError:
            out = ""
    finally:
        os.unlink(path)
    with _lock:
        _PP_CACHE[incs] = out
    return out


def fix_asm_signatures(text):
    """C units: an asm definition must repeat the TU's prototype of the function (C forbids a
    conflicting redeclaration); without one it is void f(void). The prototype may also come
    from a header (searched in the preprocessed includes)."""
    body = re.sub(r"#ifdef FE10_NONMATCHING.*?#else", "", text, flags=re.S)

    def find(f, t):
        return re.search(r"(?m)^[ \t]*(?!return\b|else\b|case\b|goto\b)(?:extern[ \t]+)?([A-Za-z_][^;{}()#=]*?)\b" + f + r"\s*\(([^;{}()]*(?:\([^;{}()]*\)[^;{}()]*)*)\)\s*;", t)

    def sig(m):
        f = m.group(1)
        decl = find(f, body) or (find(f, preprocessed_includes(text)) if re.search(r"(?m)^#\s*include", text) else None)
        if not decl:
            return f"asm void {f}(void)"
        ret = re.sub(r"\b(extern|static|inline)\b", "", decl.group(1)).strip()
        return f"asm {ret} {f}({decl.group(2).strip() or 'void'})"
    return re.sub(r"@@ASMSIG (\w+)@@", sig, text)


def parse_hdr_fix(token):
    """link_select.txt token hfix=<header>|<name>|-<macro>;<header>|... -> {header: ([names], [macros])}"""
    out = {}
    for part in token.split(";"):
        if not part:
            continue
        h, *items = part.split("|")
        out[h] = ([x for x in items if not x.startswith("-")], [x[1:] for x in items if x.startswith("-")])
    return out


def format_hdr_fix(fix):
    return ";".join(h + "".join("|" + n for n in names) + "".join("|-" + m for m in macros)
                    for h, (names, macros) in sorted(fix.items()))


def symbol_map_renames(files):
    """Global names the per-function files' symbol maps (<file>.symbols.json, as check_func.py
    --symbol-map reads them) give to original labels: {original label: object name}. Only
    names a linker can see (C identifiers: compiler-generated vtables such as __vt__8HbWidget,
    runtime helpers); local statics ("...bss.0", "sa$42", "@GUARD@...") need no rename, their
    unit places them from the code that references them."""
    S = _dol()[1]
    out = {}
    for p in files:
        mp = os.path.join(ROOT, os.path.splitext(p)[0] + ".symbols.json")
        if not os.path.exists(mp):
            continue
        try:
            m = json.load(open(mp))
        except ValueError:
            continue
        for local, orig in m.items():
            if re.fullmatch(r"[A-Za-z_]\w*", local) and orig in S and local not in S and local != orig:
                out[orig] = local
    return out


_ALIASES = {}


def lib_aliases():
    """fn_ name -> library name (#defines of src/tu/lib_aliases.h)."""
    with _lock:
        if not _ALIASES:
            p = os.path.join(ROOT, "src/tu/lib_aliases.h")
            for line in open(p) if os.path.exists(p) else []:
                m = re.match(r"#define (\w+) (\w+)", line)
                if m:
                    _ALIASES[m.group(1)] = m.group(2)
            _ALIASES.setdefault("", "")
    return _ALIASES


def include_block(includes, fix, lang, c_only=()):
    """The hoisted #includes. Headers of different regions disagree on some declarations
    (s32 as long or int, NULL, one fn_ with different parameter types, two structs of one name).
    For a header listed in fix, the conflicting names are renamed while it is included (the
    files that use it then see the first header's declaration; same size, same code, which
    placement checks) and the conflicting macros are undefined before it (its definition wins)."""
    # definitions in headers (pool-order scaffolding such as StringPool) are not force_active:
    # MWLD dead-strips them (place.py models it), the real functions stay force_active
    out = ["#pragma force_active off\n"] if includes else []
    any_null = False
    for inc in includes:
        m = re.match(r'#\s*include\s*[<"]([^>"]+)[>"]', inc)
        h = m.group(1) if m else None
        names, macros = fix.get(h, ([], []))
        any_null |= "NULL" in macros
        names = [lib_aliases().get(x, x) for x in names]   # a renamed library function: its real name
        out += ["#undef NULL\n#define NULL 0\n" if x == "NULL0" else f"#undef {x}\n" for x in macros]
        if inc in c_only:
            out.append("#pragma cplusplus off\n")
        out += [f"#define {x} {x}__tu_alt{len(out)}\n" for x in names]
        out.append(inc + "\n")
        out += [f"#undef {x}\n" for x in names]
        if inc in c_only:
            out.append("#pragma cplusplus on\n")
    if includes:
        out.append("#pragma force_active on\n")
    if any_null and lang == ".cpp":
        out.append("#undef NULL\n#define NULL 0\n")
    if any_null:
        # a header fix undefined NULL before a header whose include guard then skipped it
        out.append("#ifndef NULL\n#define NULL 0\n#endif\n")
    return out


def lead_block(lead_data, lang, decl_text=""):
    """Data items just before the unit's own pool start in some section (lead_data: symbols.txt
    names), defined at the top of the TU under their names: the object's section then starts
    on the boundary its alignment needs (a pool that holds a double is 8-aligned, but the
    unit's first literal sits at 4 mod 8 because the item before it belongs to the same
    original TU). The items keep their global names, so code elsewhere still finds them.
    When the TU (or a header) already declares the item, the definition repeats that type
    (float, double and integer scalars)."""
    import struct as _st
    S = _dol()[1]
    dol = _dol()[0]
    out = []
    for name in lead_data:
        o = S[name]
        b = dol.read(o.addr, o.size) if o.sec not in (".bss", ".sbss") else None
        m = re.search(r"\bextern\s+((?:const\s+|volatile\s+)*[A-Za-z_]\w*(?:\s+[A-Za-z_]\w*)?)\s+%s\s*;" % name, decl_text)
        sec = f'__declspec(section "{o.sec}") '
        if m:
            t = m.group(1).strip()
            base = re.sub(r"\b(const|volatile)\b", "", t).strip()
            fl = {"f32": ("f", 4), "float": ("f", 4), "f64": ("d", 8), "double": ("d", 8)}.get(base)
            ints = {"s32": ">i", "int": ">i", "u32": ">I", "s16": ">h", "u16": ">H", "s8": ">b", "u8": ">B",
                    "long": ">i", "BOOL": ">i"}
            if fl and b is not None and o.size == fl[1]:
                v = _st.unpack(">" + fl[0], b)[0]
                init = repr(v) + ("f" if fl[0] == "f" else "")
            elif base in ints and b is not None and _st.calcsize(ints[base]) == o.size:
                init = str(_st.unpack(ints[base], b)[0])
            else:
                raise ValueError(f"lead data {name}: declared as {t}, cannot define it")
            d = f"{sec}{t} {name} = {init};"
        else:
            const = "const " if o.sec in (".sdata2", ".rodata") else ""
            init = (" = {" + ", ".join("0x%02X" % x for x in b) + "}") if b is not None else ""
            d = f"{sec}{const}unsigned char {name}[{o.size}]{init};"
        out.append(('extern "C" { extern ' + d + " }\n") if lang == ".cpp" and not m else d + "\n")
    return "/* data of the original TU before the unit's own pool (alignment) */\n" + "".join(out)


def define_item(name, lang, decl_text):
    """A definition of the symbols.txt item `name` with the type the TU declares it with:
    zero-initialised data (.bss/.sbss) from any declaration (the `extern` dropped), float and
    integer scalars with their value, undeclared items as bytes; None if it cannot be written."""
    S = _dol()[1]
    o = S[name]
    m = re.search(r"(?m)^[ \t]*extern\s+(?!\"C\")([^;{}()=]*?\b%s\b[^;{}()=]*);" % re.escape(name), decl_text)
    arr = re.search(r"(?m)^[ \t]*extern\s+((?:const\s+|volatile\s+)*)(u8|s8|char|unsigned char|signed char|u16|s16|u32|s32|int|f32|float)\s+%s\s*\[\s*(0x[0-9A-Fa-f]+|\d*)\s*\]\s*;" % re.escape(name), decl_text)
    if o.sec in (".bss", ".sbss") and m:
        d = re.sub(r"\bconst\b", "", m.group(1)).strip() + ";"
    elif arr and o.sec not in (".bss", ".sbss"):
        # an array declared with an element type: defined with that type, from the DOL bytes
        import struct as _st
        fmt = {"u8": "B", "s8": "b", "char": "b", "unsigned char": "B", "signed char": "b", "u16": "H", "s16": "h",
               "u32": "I", "s32": "i", "int": "i", "f32": "f", "float": "f"}[arr.group(2)]
        n = _st.calcsize(fmt)
        cnt = int(arr.group(3), 0) if arr.group(3) else o.size // n
        if cnt * n != o.size:
            return None
        vals = _st.unpack(">%d%s" % (cnt, fmt), _dol()[0].read(o.addr, o.size))
        if fmt == "f" and not all(v == v and abs(v) != float("inf") for v in vals):
            return None
        body = ", ".join((repr(v) + "f") if fmt == "f" else str(v) for v in vals)
        d = f'__declspec(section "{o.sec}") {arr.group(1)}{arr.group(2)} {name}[{arr.group(3) or cnt}] = {{{body}}};'
    else:
        try:
            d = lead_block([name], lang, decl_text).split("\n", 1)[1].rstrip("\n")
        except (ValueError, KeyError):
            return None
        if o.sec in (".bss", ".sbss"):
            d = re.sub(r"^__declspec\(section \"[^\"]*\"\) ", "", d)
    if lang == ".cpp" and not d.startswith('extern "C"'):
        d = 'extern "C" { ' + d + " }"
    return f"/* {name}: named by the C code, defined at its first user */\n" + d + "\n"


_STATIC_DATA_RE = re.compile(r"static\s+(?!inline\b)[^(){};=]*?\b([A-Za-z_]\w*)\s*(?:\[[^\]]*\]\s*)*(?:=|;)", re.S)


_IDENT_RE = re.compile(r"[A-Za-z_]\w*")


def _reach(marks, rest):
    """Names of the marked definitions (match groups 1: name, 2: text) that the rest of the
    text uses, directly or through other used marked definitions."""
    used = set(_IDENT_RE.findall(rest))
    body = {}
    for m in marks:
        ids = set(_IDENT_RE.findall(m.group(2)))
        ids.discard(m.group(1))
        body.setdefault(m.group(1), set()).update(ids)
    keep = set()
    todo = [n for n in body if n in used]
    while todo:
        n = todo.pop()
        if n in keep:
            continue
        keep.add(n)
        todo += [x for x in body[n] if x in body and x not in keep]
    return keep


def drop_helpers(text):
    """Remove helper functions nobody in the TU references (pool-order dummies of the
    per-function files: in the merged TU the real functions order the pool themselves, and a
    dummy would add code main.dol does not have)."""
    pat = re.compile(r"@@HELPER (\w+)@@(.*?)@@ENDHELPER@@", re.S)
    marks = list(pat.finditer(text))
    if not marks:
        return text
    keep = _reach(marks, pat.sub("", text))
    return pat.sub(lambda m: m.group(2) if m.group(1) in keep else f"/* {m.group(1)}: pool-order helper, not needed in the TU */", text)


def prune_statics(text):
    """Drop file-static data that no C code of the TU uses any more (its users became asm
    functions): it would otherwise sit in the object with nothing to place it by."""
    marks = list(re.finditer(r"@@STATIC (\w+)@@(.*?)@@ENDSTATIC@@", text, flags=re.S))
    rest = re.sub(r"@@STATIC (\w+)@@(.*?)@@ENDSTATIC@@", "", text, flags=re.S)
    rest = re.sub(r"#ifdef FE10_NONMATCHING.*?#else", "", rest, flags=re.S)
    rest = re.sub(r"(?m)^\s*opword .*$", "", rest)
    keep = _reach(marks, rest)

    def sub(m):
        return m.group(2) if m.group(1) in keep else f"/* {m.group(1)}: only used by asm functions */"
    return re.sub(r"@@STATIC (\w+)@@(.*?)@@ENDSTATIC@@", sub, text, flags=re.S)


_TAG_DEF = re.compile(r"^(?:typedef\s+)?(?:const\s+)?(?:struct|union|enum)\s+([A-Za-z_]\w*)\s*(?::[^{]*)?\{")
_C_BASIC = {"void", "char", "short", "int", "long", "float", "double", "signed", "unsigned", "const", "volatile",
            "struct", "union", "enum", "s8", "u8", "s16", "u16", "s32", "u32", "s64", "u64", "f32", "f64", "BOOL",
            "bool", "size_t", "vu8", "vu16", "vu32", "vs32", "M2C_UNK"}


_HLN = {}


def header_local_names(incs):
    """c_local_names of the preprocessed hoisted includes (cached per include list)."""
    with _lock:
        if incs in _HLN:
            return _HLN[incs]
    v = c_local_names(split_chunks(preprocessed_includes(incs)))
    with _lock:
        _HLN[incs] = v
    return v


def c_local_names(chunks):
    """Names a C file defines that have no linkage or that only the file sees: struct/union/
    enum tags, typedef names, static functions and static data -> normalised definition."""
    out = {}
    for ch in chunks:
        if ch.kind == "pp":
            continue
        t = re.sub(r"\s+", " ", strip_comments(ch.text)).strip()
        if ch.kind == "func":
            if ch.name and not FN_RE.match(ch.name) and re.match(r"^(static|inline)\b", t):
                out.setdefault(ch.name, t)
            continue
        m = _TAG_DEF.match(t)
        if m:
            out.setdefault(m.group(1), t)
        if t.startswith("typedef"):
            body = re.sub(r"\{.*\}", "{}", t)
            m = re.search(r"\(\s*\*\s*([A-Za-z_]\w*)\s*\)\s*\(", body)     # function pointer typedef
            names = [m.group(1)] if m else re.findall(r"([A-Za-z_]\w*)\s*(?:\[[^\]]*\]\s*)*[,;]", body)
            for n in names:
                if n not in ("typedef",):
                    out.setdefault(n, t)
            continue
        m = _STATIC_DATA_RE.match(t)
        if m and not FN_RE.match(m.group(1)):
            out.setdefault(m.group(1), t)
    return out


def rename_idents(text, mp):
    """Identifiers of mp renamed outside strings (members after . / -> are left alone)."""
    if not mp:
        return text
    pat = re.compile(r"(?<![.\w])(?<!->)(%s)\b" % "|".join(map(re.escape, mp)))
    parts, pos = [], 0
    for m in _STR_RE.finditer(text):
        parts.append(pat.sub(lambda x: mp[x.group(1)], text[pos:m.start()]))
        parts.append(m.group(0))
        pos = m.end()
    parts.append(pat.sub(lambda x: mp[x.group(1)], text[pos:]))
    return "".join(parts)


_ONE_DECL = re.compile(r"^(?:extern\s+)?(?!typedef\b|static\b)([^;{}=#]*?)\b((?:fn|lbl)_[0-9A-F]{8})\b([^;{}=#]*);$", re.S)


def c_decl_parse(text):
    """(name, key, typedef text maker) of a declaration chunk that declares exactly one fn_/lbl_
    name (C mode), else None."""
    t = re.sub(r"\s+", " ", strip_comments(text)).strip()
    m = _ONE_DECL.match(t)
    if not m:
        return None
    pre, name, post = m.group(1), m.group(2), m.group(3)
    if len(re.findall(r"\b(?:fn|lbl)_[0-9A-F]{8}\b", t)) != 1:
        return None
    depth = 0
    for c in pre + post:     # a single declarator: no comma outside parentheses
        depth += c == "("
        depth -= c == ")"
        if c == "," and depth == 0:
            return None
    key = re.sub(r"^extern\s+", "", t)
    if post.startswith(" (") or post.startswith("("):
        # parameter names do not matter
        def strip_param(pm):
            q = pm.strip()
            m2 = re.match(r"^(.*?[\w\*\s\)])\s*\b([A-Za-z_]\w*)\s*((?:\[[^\]]*\])*)$", q)
            if m2 and re.search(r"[A-Za-z_*]", m2.group(1)) and m2.group(2) not in _C_BASIC \
                    and m2.group(1).strip() not in ("struct", "union", "enum"):
                return m2.group(1).strip() + m2.group(3)
            return q
        k = post.find("(")
        j = post.rfind(")")
        params = post[k + 1:j]
        if "(" not in params:
            key = re.sub(r"^extern\s+", "", (pre + name + post[:k + 1] + ",".join(strip_param(x) for x in params.split(",")) + post[j:]))
    key = re.sub(r"\s*([*(),\[\]])\s*", r"\1", key)
    tdef = "typedef " + pre + "@@T@@" + post + ";"
    return name, key, tdef


def erased_proto(text):
    """A C prototype of a fn_ declaration with every non-basic type that is a pointer written
    as void * (return type and parameters), or None."""
    t = re.sub(r"\s+", " ", strip_comments(text)).strip()
    m = re.match(r"^(?:extern\s+)?([^()]*?)\b(fn_[0-9A-F]{8})\s*\((.*)\)\s*;$", t)
    if not m:
        return None

    def one(ty, allow_void=False):
        ty = ty.strip()
        ids = [i for i in re.findall(r"[A-Za-z_]\w*", ty) if i not in ("const", "volatile")]
        if "*" in ty:
            return "void *"
        if all(i in _C_BASIC for i in ids) and ids:
            return " ".join(ids)
        return None
    ret = one(m.group(1))
    if ret is None:
        return None
    params = m.group(3).strip()
    if params in ("", "void", "..."):
        return f"{ret} {m.group(2)}({params});"
    out = []
    for prm in params.split(","):
        prm = prm.strip()
        if prm == "..." or "(" in prm or "[" in prm:
            if prm == "...":
                out.append(prm)
                continue
            return None
        ids = re.findall(r"[A-Za-z_]\w*", prm)
        if len(ids) > 1 and ids[-1] not in _C_BASIC:
            prm = prm[:prm.rfind(ids[-1])]      # the parameter name
        e = one(prm)
        if e is None:
            return None
        out.append(e)
    return f"{ret} {m.group(2)}({', '.join(out)});"


def c_simple_proto(text):
    """A prototype that only uses basic types and struct tags (forward-declarable), with the
    tag forward declarations, else None."""
    t = re.sub(r"\s+", " ", strip_comments(text)).strip()
    tags = re.findall(r"\b(?:struct|union)\s+([A-Za-z_]\w*)", t)
    rest = re.sub(r"\b(?:struct|union)\s+[A-Za-z_]\w*", "", t)
    m = re.match(r"^(?:extern\s+)?([^()]*?)\b(fn_[0-9A-F]{8})\s*\((.*)\)\s*;$", rest)
    if not m:
        return None
    for ident in re.findall(r"[A-Za-z_]\w*", m.group(1)):
        if ident not in _C_BASIC:
            return None
    for prm in m.group(3).split(","):
        ids = re.findall(r"[A-Za-z_]\w*", prm)
        if "(" in prm or "[" in prm:
            return None
        if ids and ids[-1] not in _C_BASIC and len(ids) > 1:
            ids = ids[:-1]      # the parameter name
        if any(i not in _C_BASIC for i in ids):
            return None
    tagkw = re.findall(r"\b(struct|union)\s+([A-Za-z_]\w*)", t)
    return "".join(f"{k} {n};\n" for k, n in dict.fromkeys(tagkw)) + t


_HDR_CACHE = {}


def _resolve_include(name, from_dir):
    for d in (from_dir, os.path.join(ROOT, "include"), os.path.join(ROOT, "src")):
        q = os.path.normpath(os.path.join(d, name))
        if os.path.isfile(q):
            return q
    return None


def header_closure(path):
    """(set of headers a file includes, transitively; {macro: #define text} those headers
    define), by a textual scan (include paths: the file's directory, include/, src/)."""
    if path in _HDR_CACHE:
        return _HDR_CACHE[path]
    _HDR_CACHE[path] = (set(), {})      # (cycles)
    seen, macs = set(), {}
    try:
        text = strip_target_pc(open(path, encoding="utf-8", errors="replace").read())
    except OSError:
        return _HDR_CACHE[path]
    for line in re.finditer(r'(?m)^[ \t]*#[ \t]*include[ \t]*[<"]([^>"]+)[>"]', text):
        q = _resolve_include(line.group(1), os.path.dirname(path))
        if q:
            seen.add(q)
            h, m = header_closure(q)
            seen |= h
            for k, v in m.items():
                macs.setdefault(k, v)
    if path.endswith(".h"):
        for m in re.finditer(r"(?m)^[ \t]*#[ \t]*define[ \t]+(\w+)((?:[^\n]*\\\n)*[^\n]*)", text):
            macs.setdefault(m.group(1), (m.group(0).strip(), path))
    _HDR_CACHE[path] = (seen, macs)
    return _HDR_CACHE[path]


_HDR_FUNCS = {}


def header_global_functions(path):
    """Names of non-static, non-inline functions a header defines (pool-order scaffolding such
    as strpool.h's StringPool): two units including the header would both define them."""
    if path not in _HDR_FUNCS:
        names = set()
        try:
            for ch in split_chunks(strip_target_pc(open(path, encoding="utf-8", errors="replace").read())):
                if ch.kind == "func" and ch.name and not FN_RE.match(ch.name) and "::" not in ch.text.split("(")[0] \
                        and not re.match(r"^\s*(static|inline)\b", strip_comments(ch.text)):
                    names.add(ch.name)
        except OSError:
            pass
        _HDR_FUNCS[path] = names
    return _HDR_FUNCS[path]


def generate(functions, ok_files, header_note="", fallback=False, force_asm=(), asm_data=False, c_native=False,
             hdr_fix=None, prune_data=False, lead_data=(), def_data=(), def_skipped=None, lit_rw=(),
             lit_order=False, cpp_redir=(), pp_hoist=False, inline_copies=False):
    """Return (text, lang, problems). def_skipped: a list; def_data names that cannot be defined
    are appended to it and left out instead of being reported as problems."""
    problems = []
    files = []
    origin = {}
    asm_fns = []
    for f in functions:
        if f not in ok_files or f in force_asm:
            if fallback and re.fullmatch(r"[A-Za-z_]\w*", f) and f in _dol()[1]:
                asm_fns.append(f)
            else:
                problems.append(f"{f}: no exact definition")
            continue
        origin[f] = ok_files[f][0]
        if origin[f] not in files:
            files.append(origin[f])
    langs = {os.path.splitext(p)[1] for p in files}
    lang = ".cpp" if ".cpp" in langs else ".c"
    parsed = {}
    for k, p in enumerate(files):
        chunks = split_chunks(read_source(p))
        found = {ch.name for ch in chunks if ch.kind == "func"}
        fmacros = {m.group(1) for ch in chunks if ch.kind == "pp"
                   for m in [re.match(r"#\s*define\s+(\w+)\(", ch.text)] if m}
        by_macro = bool(fmacros) and any(
            ch.kind != "pp" and m.group(1) in fmacros for ch in chunks
            for m in re.finditer(r"(?m)^\s*(\w+)\s*\(\s*fn_[0-9A-F]{8}\b", strip_comments(ch.text)))
        if by_macro or any(origin.get(f) == p and f not in found for f in functions):
            # functions made by macros: chunk the preprocessed file (pragmas kept)
            if pp_hoist:
                # (variant `hoist`) only the file's own lines; its #includes are hoisted like
                # those of the other files, so header classes are not copied into its namespace
                incs = [Chunk("pp", m.group(0).strip()) for m in
                        re.finditer(r'(?m)^[ \t]*#[ \t]*include[ \t]*[<"][^>"]+[>"]', strip_comments(read_source(p)))]
                chunks = incs + split_chunks(preprocessed_own(preprocess(p)))
            else:
                chunks = split_chunks(preprocess(p))
        for j, ch in enumerate(chunks):
            ch.file, ch.idx = p, j
        parsed[p] = chunks
    unit = set(functions)
    out = [f"/* Generated by tools/build/gen_tu.py from the per-function sources; do not edit.\n"
           f" * {header_note}\n * Sources:\n" + "".join(f" *   {p}\n" for p in files) + " */\n"]
    includes = []
    for p in files:
        for ch in parsed[p]:
            if ch.kind == "pp" and ch.text.startswith("#include") and ch.text not in includes:
                includes.append(ch.text)
    # C files compiled at one global scope (pure C units, cnative): names without linkage that
    # two files define differently (struct tags, typedefs, statics) are renamed in the later
    # file; fn_/lbl_ declarations that differ are redirected (see c_redirect below)
    # macros of hoisted headers that a file does not include: hidden from that file's blocks
    # where it uses the name itself (more.h's `#define GD ((GD3*)&lbl_803CAB38)` and another
    # file's own `struct GD`), restored after the block
    hdr_all = {}
    file_hdrs = {}
    if len(files) > 1:
        for p in files:
            hs, ms = header_closure(os.path.join(ROOT, p))
            file_hdrs[p] = hs
            for k, v in ms.items():
                hdr_all.setdefault(k, v)
    cmode_files = [p for p in files if p.endswith(".c") and (lang == ".c" or c_native)]
    ren = {p: {} for p in files}
    if len(cmode_files) > 1:
        first_def = {}
        if includes:
            # types the hoisted headers define: a file's own different definition is renamed
            first_def.update(header_local_names("".join(includes_text(includes))))
        for k, p in enumerate(cmode_files):
            for n, t in c_local_names(parsed[p]).items():
                if n in first_def and first_def[n] != t:
                    ren[p][n] = f"{n}__tu_c{files.index(p)}"
                else:
                    first_def.setdefault(n, t)
    cdecl = {}           # fn_/lbl_ name -> (key, file) of the declaration in force (C mode)
    cpp_first = {}       # fn_/lbl_ name of cpp_redir -> scope of its first declaration ("" = global)
    redirects = {p: {} for p in files}
    defkeys = {}
    for p in cmode_files:
        for ch in parsed[p]:
            if ch.kind == "func" and ch.name in unit and origin.get(ch.name) == p:
                d = c_decl_parse(rename_idents(prototype_of(ch.text), ren[p]))
                if d:
                    defkeys[ch.name] = (d[1], rename_idents(prototype_of(ch.text), ren[p]), p)


    def cpp_redirect(text, p):
        """C++ (variant `credir=`): two files declare one extern "C" fn_/lbl_ name with types MWCC
        calls different ("identifier ... redeclared"). The later file's declaration becomes a
        typedef and `#define n (*(T*)&tu_fK::n)` (the first declaration, in its namespace)."""
        d = c_decl_parse(text)
        if not d or d[0] not in cpp_redir:
            return text
        name, key, tdef = d
        if name in redirects[p]:
            return ""
        if name not in cpp_first:
            hdr = preprocessed_includes("".join(includes_text(includes))) if includes else ""
            cpp_first[name] = "" if re.search(r"\b%s\b" % name, hdr) else ns[p]
            if cpp_first[name]:
                return text
        if cpp_first[name] == ns[p]:
            return text
        tn = f"tu_T_{name}_{files.index(p)}"
        mac = f"#define {name} (*({tn}*)&{cpp_first[name]}::{name})"
        redirects[p][name] = mac
        return tdef.replace("@@T@@", tn) + "\n" + mac

    def c_redirect(text, p):
        """C mode: a declaration of a fn_/lbl_ name that another file declared differently
        becomes a typedef of this file's type and a macro `#define n (*(T*)&n)` in force in this
        file's blocks (calls and accesses compile with this file's types, same code)."""
        d = c_decl_parse(text)
        if not d:
            return text
        name, key, tdef = d
        if name in redirects[p]:
            return ""
        pre = ""
        if name not in cdecl and name in defkeys and defkeys[name][2] != p and defkeys[name][0] != key:
            sp = c_simple_proto(defkeys[name][1])
            if sp is None:
                return text
            cdecl[name] = (defkeys[name][0], defkeys[name][2])
            pre = sp + "\n"
        if name not in cdecl:
            cdecl[name] = (key, p)
            cpp_first.setdefault(name, "")
            return text
        if cdecl[name][0] == key or cdecl[name][1] == p or defkeys.get(name, ("", "", None))[2] == p:
            return pre + text     # (a file's own definition cannot be redirected)
        tn = f"tu_T_{name}_{files.index(p)}"
        mac = f"#define {name} (*({tn}*)&{name})"
        redirects[p][name] = mac
        return pre + tdef.replace("@@T@@", tn) + "\n" + mac
    c_only = set()
    if c_native and lang == ".cpp":
        # headers that only C files include are read in C mode too
        users = {}
        for p in files:
            for ch in parsed[p]:
                if ch.kind == "pp" and ch.text.startswith("#include"):
                    users.setdefault(ch.text, set()).add(p.endswith(".c"))
        c_only = {i for i, u in users.items() if u == {True}}
    # functions hoisted headers define (StringPool scaffolding): a name of this unit's own, or
    # two units that include the header define one global twice (MWLD "multiply-defined")
    hfuncs = set()
    for p in files:
        for h in header_closure(os.path.join(ROOT, p))[0]:
            hfuncs |= {n for n in header_global_functions(h) if n not in _dol()[1]}
    out += [f"#define {n} {n}__tu_{functions[0]}\n" for n in sorted(hfuncs)]
    out += include_block(includes, hdr_fix or {}, lang, c_only)
    if cpp_redir and c_native and lang == ".cpp":
        # a name of cpp_redir that a C file (compiled as C) declares too: C cannot reach the
        # C++ file's namespace, so one declaration with the pointer types erased to void* is
        # made at global scope first; the C file's own declaration and the C++ files' are then
        # redirected to it (same calling convention, same code)
        hoisted = []
        for p in cmode_files:
            for ch in parsed[p]:
                if ch.kind not in ("decl", "func"):
                    continue
                t = prototype_of(ch.text) if ch.kind == "func" else ch.text
                d = c_decl_parse(rename_idents(t, ren[p]))
                if not d or d[0] not in cpp_redir or d[0] in cdecl or not d[0].startswith("fn_") \
                        or d[0] in unit:    # (a unit function's definition cannot be redirected)
                    continue
                e = erased_proto(rename_idents(t, ren[p]))
                if e is None:
                    continue
                ed = c_decl_parse(e)
                cdecl[d[0]] = (ed[1], "@hoisted")
                cpp_first[d[0]] = ""
                hoisted.append(e)
        if hoisted:
            out.append("#pragma cplusplus off\n" + "\n".join(hoisted) + "\n#pragma cplusplus on\n")
    if lead_data:
        out.append(lead_block(lead_data, lang, preprocessed_includes("".join(includes_text(includes))) +
                              "".join(ch.text + "\n" for p in files for ch in parsed[p] if ch.kind == "decl")))
    emitted = {p: set() for p in files}   # chunk indices already in the TU (files may define
    # their functions out of address order: every chunk is emitted once, before the first
    # function that follows it in its file)
    pragmas = {p: [] for p in files}
    protos = {p: set() for p in files}
    macros = {p: {} for p in files}
    macro_now = {}
    owner_macro = {}    # macro -> the file whose #define is in force
    ns = {p: f"tu_f{k}" for k, p in enumerate(files)}
    seen_c = set()
    global_ops = set()
    data_done, data_names = set(), []
    named, decl_text = set(), ""
    def_at = {}
    if def_data:
        # data the C code names (extern lbl_...) that lies inside the unit's own pool: defined
        # under its name right before its first user, where the original compiler emitted it
        import place as PL
        S_ = PL.dolmodel()[0]
        order = {f: k for k, f in enumerate(functions)}
        mapped = set()
        for p in files:
            mp = os.path.join(ROOT, os.path.splitext(p)[0] + ".symbols.json")
            if os.path.exists(mp):
                try:
                    mapped |= set(json.load(open(mp)).values())
                except ValueError:
                    pass
        for name in def_data:
            users = [f for f in S_[name].refby if f in order] if name in S_ else []
            # a label a symbol map gives to a file static of the unit is defined by that file
            first = min(S_[name].refby, key=lambda n: S_[n].addr if n in S_ else 1 << 32) if users else None
            if users and name not in mapped and not (asm_data == "lit" and first in asm_fns):
                # at the first C user (its file declares the type); asm users have no types
                # (an asm function that uses it first defines it itself in the asmlit variant,
                # see asm_private_data)
                c_users = [f for f in users if f not in asm_fns]
                if c_users:     # (no C user left: nothing to define it for)
                    def_at.setdefault(min(c_users, key=order.get), []).append(name)
    if asm_data == "lit" or def_data or lit_rw or lit_order:
        # labels the C side names (extern lbl_...): such shared data is defined under its name
        for p in files:
            for ch in parsed[p]:
                named.update(re.findall(r"\blbl_[0-9A-F]{8}\b", strip_comments(ch.text)))
        decl_text = preprocessed_includes("".join(includes_text(includes))) + \
            "".join(ch.text + "\n" for p in files for ch in parsed[p] if ch.kind == "decl")
    rw = literal_rewrites(lit_rw, parsed, files, decl_text) if lit_rw else {}
    named -= set(rw)
    order_done = set()
    for f in functions:
        defs = []
        for name in def_at.get(f, ()):
            dl = lang if f in asm_fns or lang == ".c" else (".c" if c_native and origin.get(f, "").endswith(".c") else ".cpp")
            d = define_item(name, dl, decl_text)
            if d is None:
                if def_skipped is not None:
                    def_skipped.append(name)
                else:
                    problems.append(f"{name}: cannot define it from its declaration")
            else:
                defs.append(d)
        if f in asm_fns:
            out += defs
            data = ""
            if asm_data:
                data, names = asm_private_data(f, asm_fns, data_done, shared=asm_data == "lit", lang=lang,
                                               named=named, decl_text=decl_text)
                data_names.extend(names)
            out.append(asm_function(f, lang, data))
            continue
        if f not in origin:
            continue
        p = origin[f]
        chunks = parsed[p]
        target = next((ch for ch in chunks if ch.kind == "func" and ch.name == f), None)
        if target is None:
            problems.append(f"{f}: definition not found in {p} by the chunker")
            continue
        block = []
        prior = list(pragmas[p])
        if any(k > target.idx for k in emitted[p]):
            # defined earlier in its file than chunks already emitted (out of address order):
            # the pragmas in force at its own place in the file, not those emitted so far (a
            # `#pragma push / inline_depth(3) / pop` around it was consumed by an earlier block)
            prior = [ch.text for ch in chunks[:target.idx]
                     if ch.kind == "pp" and ch.text.startswith("#pragma")]
            depth = 0
            for t in prior:
                if re.match(r"#\s*pragma\s+push\b", t):
                    depth += 1
                elif re.match(r"#\s*pragma\s+pop\b", t):
                    depth = max(0, depth - 1)
            late_pops = depth
        else:
            late_pops = 0
        cfile = p.endswith(".c")
        # c_native: a C file of a C++ unit is compiled as C (#pragma cplusplus off), at global
        # scope like a pure C unit, instead of as C++ inside its namespace
        cmode = lang == ".cpp" and cfile and c_native
        L = ".c" if cmode else lang
        start_redirects = dict(redirects[p])    # (those this block adds are defined in place)
        if L == ".c" and f not in cdecl and f in defkeys:
            cdecl[f] = (defkeys[f][0], p)     # its own definition is the declaration in force
        for ch in chunks[:target.idx + 1]:
            if ch.idx in emitted[p]:
                continue
            if ch.kind == "pp":
                emitted[p].add(ch.idx)
                if ch.text.startswith("#include"):
                    continue
                if ch.text.startswith("#pragma"):
                    pragmas[p].append(ch.text)
                text = rename_idents(ch.text, ren[p]) if L == ".c" else ch.text
                m = re.match(r"#\s*define\s+\w+(\([^)]*\))?", text)
                if m and L == ".cpp":
                    text = text[:m.end()] + no_adl_calls("{" + text[m.end():])[1:]
                md = re.match(r"#\s*(define|undef)\s+(\w+)", text)
                if md and len(files) > 1:
                    # macros are not scoped by the file namespaces: each file sees its own
                    # definition (re-asserted when its next block starts, see below)
                    if md.group(1) == "define":
                        macros[p][md.group(2)] = text
                        owner_macro[md.group(2)] = p
                        if macro_now.get(md.group(2)) != text:   # (a header may define it too)
                            text = f"#undef {md.group(2)}\n" + text
                        macro_now[md.group(2)] = text.split("\n", 1)[-1] if text.startswith("#undef") else text
                    else:
                        macros[p].pop(md.group(2), None)
                        macro_now.pop(md.group(2), None)
                block.append((text, ch.extc))
                continue
            if ch.kind == "func" and ch is not target:
                if ch.name and FN_RE.match(ch.name):
                    if ch.name in unit and origin.get(ch.name) == p:
                        # a later unit function of this file (defined earlier in the file):
                        # emitted at its own position, declared here
                        if ch.name not in protos[p]:
                            protos[p].add(ch.name)
                            pt = prototype_of(ch.text)
                            if L == ".c":
                                pt = c_redirect(rename_idents(pt, ren[p]), p)
                            elif cpp_redir:
                                pt = cpp_redirect(pt, p)
                            block.append((pt, ch.extc or (L == ".cpp" and cfile)))
                        continue
                    emitted[p].add(ch.idx)
                    if inline_copies is not False and inline_copies is not None and ch.name not in unit \
                            and ch.name not in inline_copies:
                        # (variant `inl`) a function of another unit that this file defines
                        # before a unit function: in the original TU the compiler could inline
                        # it here (-inline auto). A static copy under another name, not
                        # force_active: inlined calls leave nothing, the copy is dead-stripped
                        nm = ch.name
                        mac = f"#define {nm} {nm}__tu_inl"
                        macros[p][nm] = mac
                        owner_macro[nm] = p
                        macro_now[nm] = mac
                        body = ch.text if L != ".cpp" else no_adl_calls(ch.text)
                        if L == ".c":
                            body = rename_idents(body, ren[p])
                        if not re.match(r"^\s*(static|inline)\b", strip_comments(body)):
                            body = "static " + body.lstrip()
                        block.append((f"#undef {nm}\n{mac}\n#pragma push\n#pragma force_active off\n{body}\n#pragma pop",
                                      ch.extc or (L == ".cpp" and cfile)))
                        continue
                    pt = prototype_of(ch.text)
                    if L == ".c":
                        pt = c_redirect(rename_idents(pt, ren[p]), p)
                    elif cpp_redir:
                        pt = cpp_redirect(pt, p)
                    block.append((pt, ch.extc or (L == ".cpp" and cfile)))
                    continue
            emitted[p].add(ch.idx)
            text = ch.text
            if L == ".cpp" and cfile:
                text = re.sub(r"\b((?:fn|func)_[0-9A-Fa-f]{8}|[A-Za-z_]\w*)\s*\(\s*\)\s*;", r"\1(...);", text) \
                    if ch.kind != "func" else text
            if L == ".c":
                text = rename_idents(text, ren[p])
                if ch.kind == "decl":
                    text = c_redirect(text, p)
                    if not text:
                        continue
                key = re.sub(r"\s+", " ", strip_comments(text)).strip()
                if ch.kind != "func" and key in seen_c:
                    continue
                if ch.kind == "func" and ch is not target and key in seen_c and ch.name and not FN_RE.match(ch.name):
                    continue    # the same static helper in two C files
                seen_c.add(key)
            if L == ".cpp" and cpp_redir and ch.kind == "decl":
                text = cpp_redirect(text, p)
                if not text:
                    continue
            extc = ch.extc or (L == ".cpp" and cfile)
            if L == ".cpp" and not extc and ch.kind == "decl" and needs_c_linkage(text):
                # global objects/functions declared at file scope of a .cpp file: unmangled
                # at global scope, so keep them unmangled inside the file's namespace
                extc = True
            if ch.kind == "func" and ch is not target and ch.name and not FN_RE.match(ch.name) \
                    and "::" not in strip_comments(text).split("(")[0] and ch.name not in _dol()[1]:
                # a helper that is not a game function (pool-order dummies such as StringPool,
                # poolOrder): dropped below when nothing in the TU calls it
                text = f"@@HELPER {ch.name}@@" + text + "@@ENDHELPER@@"
            if rw and ch.kind == "func":
                text = apply_rewrites(text, rw)
            if L == ".cpp" and ch.kind == "func":
                text = no_adl_calls(text)
            if L == ".cpp" and ch.kind == "decl" and re.match(r"^(?:typedef\s+)?(?:struct|class|union)\b[^;{]*\{", strip_comments(text).strip()) \
                    and re.search(r"\)\s*(?:const\s*)?\{", strip_comments(text)):
                # a class with inline member functions (files chunked after preprocessing carry
                # their headers' classes): an out-of-line copy MWCC emits (weak) must not be
                # force_active, MWLD dead-strips it like in the original link
                text = "#pragma push\n#pragma force_active off\n" + text + "\n#pragma pop"
            if prune_data and ch.kind == "decl":
                m = _STATIC_DATA_RE.match(strip_comments(text).strip())
                if m:   # kept only if a C function of the TU still uses it (see prune_statics)
                    text = f"@@STATIC {m.group(1)}@@" + text + "@@ENDSTATIC@@"
            block.append((text, extc))
        if lit_order:
            h = order_helper(f, unit, named, order_done, L)
            if h:
                defs = defs + [h]
        if defs:
            # after the file's declarations (the item's type), right before the function
            block[-1:-1] = [(d, False) for d in defs]
        # emit
        out.append(f"\n/* ---- {f} from {p} */\n")
        if L == ".cpp":
            out.append(f"namespace {ns[p]} {{\n")
        out.append("#pragma push\n")
        for name in [n for n in macro_now if n not in macros[p] and n in owner_macro and owner_macro[n] != p]:
            # a macro another file defined: this file does not see it (its own functions or
            # parameters may use the name, e.g. a `vtx` macro of one file and an inline `vtx`
            # of another); the other file re-asserts it when its next block starts
            if name in ("NULL", "TRUE", "FALSE"):
                continue    # (also defined by headers the other files rely on)
            out.append(f"#undef {name}\n")
            if name in hdr_all:     # the hoisted header's definition again
                out.append(hdr_all[name][0] + "\n")
            macro_now.pop(name)
        for name, d in macros[p].items():
            if macro_now.get(name) != d:
                out.append(f"#undef {name}\n{d}\n")
                macro_now[name] = d
                owner_macro[name] = p
        if cmode:
            out.append("#pragma cplusplus off\n")
        for name, mac in start_redirects.items():
            out.append(mac + "\n")
        for pr in prior:
            out.append(pr + "\n")
        hidden = []
        if hdr_all:
            btxt = strip_comments("".join(t for t, _e in block))
            used = set(_IDENT_RE.findall(btxt))
            # only names the file defines itself (a tag or typedef of its own)
            own = set(re.findall(r"\b(?:struct|class|union|enum)\s+([A-Za-z_]\w*)", btxt)) | \
                set(re.findall(r"\}\s*([A-Za-z_]\w*)\s*;", btxt)) | \
                set(re.findall(r"\btypedef\b[^;{}]*?\b([A-Za-z_]\w*)\s*;", btxt))
            hidden = [n for n, (d, h) in hdr_all.items() if n in used and n in own and h not in file_hdrs[p]
                      and n not in macros[p] and n not in macro_now]
            out += [f"#undef {n}\n" for n in hidden]
        for text, extc in block:
            if L == ".cpp" and re.search(r"\boperator\s*(?:new|delete)\b", strip_comments(text).split("{")[0]):
                # allocation functions must be declared at global scope (C++): outside the
                # file's namespace, once
                k = re.sub(r"\s+", " ", strip_comments(text)).strip()
                if k not in global_ops:
                    global_ops.add(k)
                    out.append(f"}} /* namespace {ns[p]} */\n" + text + f"\nnamespace {ns[p]} {{\n")
                continue
            if extc and L == ".cpp":
                out.append('extern "C" {\n' + text + '\n}\n')
            else:
                out.append(text + "\n")
        out.append(ctor_entry(f))
        out += [f"#undef {name}\n" for name in redirects[p]]
        out += [hdr_all[n][0] + "\n" for n in hidden]
        out.append("#pragma pop\n" * late_pops)
        out.append("#pragma pop\n")
        if cmode:   # after the pop: a file's own unbalanced push would otherwise restore C mode
            out.append("#pragma cplusplus on\n")
        if L == ".cpp":
            out.append(f"}} /* namespace {ns[p]} */\n")
    # what MWCC emits at the end of the TU (weak vtables of header classes, out-of-line inline
    # copies) takes the pragma state in force there: not force_active, so MWLD (and place.py's
    # model) dead-strip what nothing references, as in the original link
    out.append("\n#pragma force_active off\n")
    text = "".join(out)
    text = drop_helpers(text)
    if prune_data:
        text = prune_statics(text)
    if asm_fns:
        text = fix_asm_signatures(text) if lang == ".c" else text
        text = text.replace(" * Sources:\n", f" * {len(asm_fns)} function(s) not matching yet are asm (original instructions);\n"
                            f" * compile with -DFE10_NONMATCHING for their C versions.\n * Sources:\n", 1)
    if fallback:
        return text, lang, problems, asm_fns, data_names
    return text, lang, problems


def functions_in(a, b):
    S = M.load_symbols()
    return [s.name for s in sorted(S.values(), key=lambda s: s.addr)
            if s.sec == ".text" and s.type == "function" and a <= s.addr < b]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("out")
    ap.add_argument("functions", nargs="*")
    ap.add_argument("--range", nargs=2)
    a = ap.parse_args()
    fns = a.functions or functions_in(int(a.range[0], 16), int(a.range[1], 16))
    text, lang, problems = generate(fns, load_ok_files(), f"{fns[0]}..{fns[-1]}")
    out = a.out
    if not out.endswith(lang):
        out = os.path.splitext(out)[0] + lang
    os.makedirs(os.path.dirname(out), exist_ok=True)
    open(out, "w").write(text)
    print(out)
    for p in problems:
        print("PROBLEM", p)
    return 1 if problems else 0


if __name__ == "__main__":
    if sys.argv[1:] == ["--self-test"]:
        _self_test_target_pc()
        sys.exit(0)
    sys.exit(main())
