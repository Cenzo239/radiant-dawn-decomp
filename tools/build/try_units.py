#!/usr/bin/env python3
"""For every link unit of the TU map (build/tmp/buildtree/tu_units.json) whose functions are all
exact: generate its source with gen_tu.py, compile it and run place.py. Records the result per
unit in build/tmp/buildtree/try_units.json (and the generated sources in build/tmp/buildtree/tu/).

A unit that passes can be linked as Matching right now (gen_units.py picks them up).
Usage: python3 -I tools/build/try_units.py [-j 12] [--units 12,13]
"""
import argparse
import bisect
import collections
import re
import concurrent.futures as cf
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, HERE)
import gen_tu as G  # noqa: E402
import place as PL  # noqa: E402

OUT = os.path.join(ROOT, "build/tmp/buildtree/try_units.json")
TU_DIR = os.path.join(ROOT, "build/tmp/buildtree/tu")


def classify(errors):
    for key, cls in (("no exact", "inexact"), ("(static initialiser)", "ctors"), ("(exception table)", "extab"),
                     ("MWLD would dead-strip", "dead-strip"), ("compile failed", "compile"), ("chunker", "chunker"),
                     ("contiguity", "codegen"), ("size 0x", "codegen"), ("words differ", "codegen"),
                     ("referenced from outside", "shared-data"), ("not aligned", "align"),
                     ("cannot derive", "data-base"), ("not in symbols.txt", "extra-symbol")):
        if any(key in e for e in errors):
            return cls
    return "other"


ASM = {"on": False, "rounds": 32, "shrink": True, "shrink_budget": 3000, "shrink_seconds": 1500, "lit": True,
       "loop_seconds": 600, "max_group": 600, "v2": True}

# Worker processes (fork: they inherit every cache the main process warmed up). Generation and
# placement are Python, so threads were bound by the GIL; processes use all cores.
_WORK = {}


def _run_unit(u):
    return run(u, _WORK["ok_files"])


def pmap(fn, items, j, weight=None):
    """fn over items in worker processes, results in input order; heaviest items first."""
    import multiprocessing
    order = sorted(range(len(items)), key=lambda k: -weight(items[k])) if weight else list(range(len(items)))
    if j <= 1 or len(items) <= 1:
        return [fn(x) for x in items]
    with cf.ProcessPoolExecutor(j, mp_context=multiprocessing.get_context("fork")) as ex:
        futs = {k: ex.submit(fn, items[k]) for k in order}
        return [futs[k].result() for k in range(len(items))]


def fn_at(addr):
    S = G._dol()[1]
    k = bisect.bisect_right(FN_STARTS[0], addr) - 1
    return FN_STARTS[1][k] if k >= 0 else None


FN_STARTS = [[], []]


def init_fn_starts():
    S = G._dol()[1]
    fs = sorted((s.addr, s.name) for s in S.values() if s.sec == ".text" and s.type == "function")
    FN_STARTS[0][:] = [a for a, _ in fs]
    FN_STARTS[1][:] = [n for _, n in fs]


def blamed_functions(errors, unit_fns, text_start):
    """Functions that a placement error points at (their code differs from the DOL)."""
    out = set()
    sized = any(re.match(r"function (\S+) size 0x", e) for e in errors)
    contig = False
    for e in errors:
        m = re.match(r"function (\S+) size 0x", e)
        if m:
            out.add(m.group(1))
        m = re.match(r"\.text: \d+ words differ from the DOL \(first at 0x([0-9A-F]{8})\)", e)
        if m:
            out.add(fn_at(int(m.group(1), 16)))
        m = re.match(r"function (\S+) at 0x([0-9A-F]{8}) breaks contiguity", e)
        if m and not sized and not contig:
            # the function before it (in the DOL) went missing or is extra; a size error
            # explains every later break by itself, and only the first break is informative
            contig = True
            out.add(m.group(1))
            out.add(fn_at(int(m.group(2), 16) - 4))
        m = re.match(r"(\S+) \(0x[0-9A-F]{8}\) is referenced from outside the unit", e)
        if m:   # data the C object keeps local although other code needs it by name: its users
            o = PL.dolmodel()[0].get(m.group(1))   # in the unit become asm
            if o is not None:
                out |= set(o.refby)
        m = re.match(r"\.text\+0x([0-9A-F]+): ", e)   # a relocation in the code points elsewhere
        if m:
            out.add(fn_at(text_start + int(m.group(1), 16)))
    return {f for f in out if f in unit_fns}


def header_conflict(r):
    """(hoisted header, "name"|"macro", identifier) for a compile error located in a header
    included by the generated TU (two region headers declare one name differently)."""
    out = r.get("compile_out", "")
    src = r.get("source")
    if not out or not src or not os.path.exists(os.path.join(ROOT, src)):
        return None
    incs = re.findall(r'(?m)^#\s*include\s*[<"]([^>"]+)[>"]', open(os.path.join(ROOT, src)).read())
    chain = [p.strip().replace("\\", "/") for p in re.findall(r"#\s+(?:In|From): (.*)", out)]
    hdr = None
    for p in chain:
        for i in incs:
            if p.endswith("/" + i) or p == i:
                hdr = i
                break
        if hdr:
            break
    if hdr is None:
        # "(included from: ..." chains, paths wrapped over several "#   " lines: the first
        # hoisted header named in the message
        first = out.split("Error:", 1)[0] + out.split("Error:", 1)[-1].split("Error:", 1)[0]
        flat = re.sub(r"\n#\s*", "", first).replace("\\", "/")
        hits = [(flat.find("/" + i + ":"), i) for i in incs if ("/" + i + ":") in flat]
        if hits:
            hdr = max(hits)[1]   # the outermost: the hoisted include the chain enters by
    if hdr is None:
        return None
    m = re.search(r"macro '(\w+)' redefined", out)
    if m:
        return hdr, "macro", m.group(1)
    if src.endswith(".cpp") and re.search(r"illegal implicit conversion from 'void \*'", out):
        return hdr, "macro", "NULL0"    # a C header's NULL ((void*)0) read as C++: NULL 0 before it
    m = re.search(r"(?:identifier|class|object|illegal overloading) '(?:struct |class )?([A-Za-z_]\w*)[^']*' (?:redeclared|redefined|\n)", out) \
        or re.search(r"illegal overloading '([A-Za-z_]\w*)", out)
    if m:
        return hdr, "name", m.group(1)
    if "illegal function overloading" in out:
        m = re.search(r"#\s+\d+: ([^\n]*)", out)
        n = re.findall(r"([A-Za-z_]\w*)\s*\(", m.group(1)) if m else []
        if n:
            return hdr, "name", n[0]
    return None


def blamed_files(r, unit_fns, ok_files, force):
    """Per-function files that make a merged unit fail as a whole: the file at the line a
    compile error points to, or the file that defines a function placement does not know
    (pool-order helpers such as StringPool). All their unit functions become asm."""
    files = set()
    src = r.get("source")
    text = open(os.path.join(ROOT, src)).read().split("\n") if src and os.path.exists(os.path.join(ROOT, src)) else []
    for e in r["errors"]:
        for ln in re.findall(r"#\s+(\d+): ", e):
            k = int(ln) - 1
            while 0 <= k < len(text):
                m = re.match(r"/\* ---- \S+ from (\S+) \*/", text[k])
                if m:
                    files.add(m.group(1))
                    break
                k -= 1
        m = re.match(r"function (\S+) not in symbols.txt", e)
        if m:
            for k, line in enumerate(text):
                if re.search(r"\b%s\s*\(" % re.escape(m.group(1).split("__")[0]), line):
                    j = k
                    while j >= 0:
                        mm = re.match(r"/\* ---- \S+ from (\S+) \*/", text[j])
                        if mm:
                            files.add(mm.group(1))
                            break
                        j -= 1
                    break
    out = {f for f in unit_fns if f in ok_files and ok_files[f][0] in files}
    return out - set(force)


def c_bytes(r):
    return (int(r["text"][1], 16) - int(r["text"][0], 16) - r.get("asm_bytes", 0)) if r["ok"] else -1


def run(u, ok_files):
    r = run_main(u, ok_files)
    if ASM["on"] and ASM["shrink"] and r["ok"] and r.get("asm"):
        r = shrink(u, ok_files, r)
    if ASM["on"] and r.get("fallback") != "previous selection":
        # the previous selection's line, if it still places and links more C (the repair loop
        # can take a worse path), shrunk in turn (variant v2 may free more of it)
        p = prev_result(u, ok_files)
        if p is not None and c_bytes(p) > c_bytes(r):
            if ASM["shrink"] and p.get("asm"):
                p = shrink(u, ok_files, p)
            p["fallback"] = "previous selection"
            r = p
    return r


def prev_result(u, ok_files):
    prev = PREV.get(tuple(u["text"]))
    if prev is None:
        return None
    missing = [f for f in u["functions"] if f not in ok_files]
    asm, opts = prev
    res = {"unit": u["unit"], "text": u["text"], "n": len(u["functions"])}
    hf = next((G.parse_hdr_fix(o[5:]) for o in opts if o.startswith("hfix=")), {})
    ld = next((o[5:].split(",") for o in opts if o.startswith("lead=")), ())
    dd = next((o[4:].split(",") for o in opts if o.startswith("def=")), ())
    rw = next((o[3:].split(",") for o in opts if o.startswith("rw=")), ())
    r = run_once(u, ok_files, set(asm) - set(missing), dict(res, c_native="cnative" in opts, hdr_fix=hf,
                                                             prune_data="prune" in opts, lead_data=ld, def_data=dd,
                                                             lit_rw=rw, lit_order="order" in opts,
                                                             cpp_redir=next((o[7:].split(",") for o in opts if o.startswith("credir=")), ()),
                                                             pp_hoist="hoist" in opts, inline_copies=next((o[4:].split(",") if o[4:] else [] for o in opts if o == "inl" or o.startswith("inl=")), False)),
                 asm_data="lit" if "asmlit" in opts else "asmdata" in opts)
    if not r["ok"]:
        return None
    r["why"] = {f: "kept from the previous selection" for f in r.get("asm", ())}
    return r


def shrink(u, ok_files, r):
    """The repair loop over-blames (a size or pool error makes neighbours and pool sharers asm
    as well, a file fallback takes whole files): give each exact function it made asm back to
    C, file by file and then one by one in address order, and keep every step that still
    places."""
    S = G._dol()[1]
    missing = {f for f in u["functions"] if f not in ok_files}
    force = set(r["asm"]) - missing
    if not force:
        return r
    base = {k: r[k] for k in ("unit", "text", "n", "why") if k in r}
    base.update(c_native=r.get("c_native", False), hdr_fix=r.get("hdr_fix") or {}, prune_data=r.get("prune_data", False),
                lead_data=r.get("lead_data", ()), def_data=r.get("def_data", ()), lit_rw=r.get("lit_rw", ()),
                lit_order=r.get("lit_order", False), cpp_redir=r.get("cpp_redir", ()),
                pp_hoist=r.get("pp_hoist", False), inline_copies=r.get("inline_copies", False))
    budget = [ASM["shrink_budget"]]
    best = r
    import time
    deadline = time.time() + ASM["shrink_seconds"]

    def attempt(drop):
        nonlocal best
        if budget[0] <= 0 or time.time() > deadline:
            return False
        budget[0] -= 1
        f2 = force - drop
        cur = best.get("asm_data", False)
        for ad in ((cur,) if not missing and not f2 else [cur] + [m for m in (("lit", True, False) if ASM["lit"] else (True, False)) if m != cur]):
            x = run_once(u, ok_files, f2, dict(base), asm_data=ad)
            for _k in range(4):
                # a give-back that meets an extern "C" declaration conflict: redirect the name
                # (credir=) as the repair loop would, and retry
                m = re.search(r"identifier '((?:fn|lbl)_[0-9A-F]{8})\b[^']*'\s*(?:\n#\s*)?redeclared", x.get("compile_out", ""))
                if x["ok"] or not m or m.group(1) in base.get("cpp_redir", ()):
                    break
                base["cpp_redir"] = list(base.get("cpp_redir", ())) + [m.group(1)]
                x = run_once(u, ok_files, f2, dict(base), asm_data=ad)
            inside = inside_names(x, base)
            if not x["ok"] and inside:
                x = run_once(u, ok_files, f2, dict(base, def_data=list(base.get("def_data", ())) + inside), asm_data=ad)
            if not x["ok"] and drop and base.get("def_data") and ASM["v2"]:
                # a label defined in the unit (def=) changes the code of `lbl + const` in the
                # functions given back: without the labels their files name
                named = set()
                for p in {ok_files[f][0] for f in drop if f in ok_files}:
                    named |= _NAMED.get(p) or set(re.findall(r"\blbl_[0-9A-F]{8}\b", G.strip_comments(G.read_source(p))))
                keep = [n for n in base["def_data"] if n not in named]
                if len(keep) < len(base["def_data"]):
                    x = run_once(u, ok_files, f2, dict(base, def_data=keep), asm_data=ad)
            if x["ok"]:
                best = x
                base["def_data"] = x.get("def_data", ())
                return True
        return False
    exts = {os.path.splitext(ok_files[f][0])[1] for f in u["functions"] if f in ok_files}
    if ASM["v2"] and exts == {".c", ".cpp"} and not base.get("c_native"):
        # C files compiled as C (cnative) on the placed asm list: with the phase-5 C-mode
        # fixes it compiles more often, and the give-back below avoids the cr6 calls
        base["c_native"] = True
        if not attempt(set()):
            base["c_native"] = False
    if ASM["v2"] and base.get("inline_copies") in (None, False):
        # functions of the unit before that a file defines ahead of its unit functions: inlinable
        base["inline_copies"] = []
        if not attempt(set()):
            base["inline_copies"] = False
        else:
            base["inline_copies"] = best.get("inline_copies", [])
    if ASM["v2"] and not base.get("pp_hoist"):
        # files chunked after preprocessing: their own lines only, headers hoisted
        base["pp_hoist"] = True
        if not attempt(set()):
            base["pp_hoist"] = False
    if ASM["v2"]:
        # variant v2 on the placed asm list: if it still places, the give-back below runs with it
        v2 = variant_v2(u, ok_files)
        if v2["lit_rw"] or v2["def_data"] or force:
            # all of it, else its parts (one bad rewrite or definition must not cost the rest)
            for parts in (("rw", "order", "def"), ("rw", "order"), ("order", "def"), ("def",), ("order",), ("rw",)):
                if "rw" in parts and not v2["lit_rw"] or "def" in parts and not v2["def_data"]:
                    continue
                old = dict(base)
                if "rw" in parts:
                    base["lit_rw"] = v2["lit_rw"]
                if "order" in parts:
                    base["lit_order"] = True
                if "def" in parts:
                    base["def_data"] = sorted(set(base.get("def_data", ())) | set(v2["def_data"]))
                if attempt(set()):
                    break
                base.clear()
                base.update(old)
    files = {}
    for f in sorted(force, key=lambda f: S[f].addr):
        files.setdefault(ok_files[f][0], set()).add(f)
    for fs in list(files.values()):
        if len(fs) > 1 and fs <= force and attempt(fs):
            force -= fs
    for f in sorted(force, key=lambda f: S[f].addr):
        if f in force and attempt({f}):
            force.discard(f)
    if best is not r:
        best["shrunk"] = len(set(r["asm"])) - len(best.get("asm", []))
        best["why"] = {k: v for k, v in r.get("why", {}).items() if k in set(best.get("asm", []))}
        best["units"] = r.get("units")
        for k in ("fallback",):
            if k in r:
                best[k] = r[k]
    return best


def inside_names(r, res):
    """symbols.txt items the C code names (extern lbl_...) that lie inside the unit's own ranges
    (placement: "... lies inside the unit's own ranges but the object does not define it")."""
    return sorted({m.group(1) for e in r.get("errors", ())
                   for m in [re.search(r": (\w+) lies inside the unit's own ranges but the object does not define it", e)]
                   if m and m.group(1) not in res.get("def_data", ())})


def variant_v2(u, ok_files):
    """Variant v2 (phase 5): labels the C code names that are the unit's own data.
    lit_rw: .sdata2 literals only unit functions use (rewritten into literals, gen_tu
    literal_rewrites), lit_order: each C function's first-used literals made in DOL order,
    def_data: other named items inside the unit's data ranges (tu_analyze), defined at their
    first C user where the declaration allows it."""
    S = G._dol()[1]
    unit = set(u["functions"])
    data = u.get("data") or {}
    names = set()
    for p in {ok_files[f][0] for f in u["functions"] if f in ok_files}:
        if p not in _NAMED:
            try:
                _NAMED[p] = set(re.findall(r"\blbl_[0-9A-F]{8}\b", G.strip_comments(G.read_source(p))))
            except OSError:
                _NAMED[p] = set()
        names |= _NAMED[p]
    names = {n for n in names if n in S and n not in RENAMES}
    M_ = PL.dolmodel()[0]
    rw = sorted(n for n in names if S[n].sec == ".sdata2" and S[n].size in (4, 8) and n in M_
                and M_[n].refby and M_[n].refby <= unit)
    inside = []
    for n in sorted(names - set(rw)):
        o = S[n]
        if o.sec in data:
            a, b = (int(x, 16) for x in data[o.sec])
            if a <= o.addr < b:
                inside.append(n)
    return {"lit_rw": rw, "lit_order": True, "def_data": inside}


_NAMED = {}


def run_main(u, ok_files, v2=None):
    res = {"unit": u["unit"], "text": u["text"], "n": len(u["functions"])}
    if v2:
        res.update(v2)
    missing = [f for f in u["functions"] if f not in ok_files]
    if missing and (not ASM["on"] or len(missing) == len(u["functions"])):
        res.update(ok=False, cls="inexact", errors=[f"{len(missing)} functions without an exact definition"])
        return res
    r = run_loop(u, ok_files, missing, res, False)
    if r["ok"] and not r.get("asm"):
        return r
    exts = {os.path.splitext(ok_files[f][0])[1] for f in u["functions"] if f in ok_files}
    if ASM["on"] and exts == {".c", ".cpp"} and (r.get("compile_seen") or not r["ok"] or r.get("asm")):
        # (also for code differences: a C file's unprototyped `T f();` becomes `T f(...)` in C++,
        # and calls of a variadic function set cr6, 4 bytes per call)
        # C files of a C++ unit compiled as C (#pragma cplusplus off) instead of as C++
        r2 = run_loop(u, ok_files, missing, res, True)
        if r2["ok"] and (not r["ok"] or r2.get("asm_bytes", 0) < r.get("asm_bytes", 0)):
            r = r2
    if ASM["on"] and not r["ok"] and r.get("why"):
        # last resort: every per-function file the loop blamed goes asm as a whole (its pools,
        # statics and pool-order helpers leave the object together)
        files = {ok_files[f][0] for f in r["why"] if f in ok_files}
        start = {f for f in u["functions"] if f in ok_files and ok_files[f][0] in files}
        if len(start) + len(missing) < len(u["functions"]):
            r3 = run_loop(u, ok_files, missing, res, r.get("c_native", False), start)
            if r3["ok"]:
                r3["fallback"] = "files"
                return r3
    if ASM["on"] and not r["ok"] and any("no references from code" in e or "not aligned" in e for e in r["errors"]):
        # file statics that only asm functions use: leave them out of the object
        r5 = run_loop(u, ok_files, missing, res, r.get("c_native", False), prune=True)
        if r5["ok"]:
            return r5
        lead = lead_items(r["errors"] + r5["errors"])
        if lead:
            # the pool starts mid-way into its alignment: the items before it (same original TU)
            # are defined at the top of the unit under their names
            for pr in (False, True):
                r6 = run_loop(u, ok_files, missing, res, r.get("c_native", False), prune=pr, lead=lead)
                if r6["ok"]:
                    return r6
    if ASM["on"] and ASM["v2"] and not r["ok"]:
        r7 = run_loop(u, ok_files, missing, dict(res, pp_hoist=True), r.get("c_native", False))
        if r7["ok"]:
            return r7
    prev = PREV.get(tuple(u["text"]))
    if ASM["on"] and not r["ok"] and prev is not None:
        # the asm list of the previous selection (link_select.txt before this run) still places:
        # keep it, so a unit never drops out because the repair loop took another path
        asm, opts = prev
        hf = next((G.parse_hdr_fix(o[5:]) for o in opts if o.startswith("hfix=")), {})
        ld = next((o[5:].split(",") for o in opts if o.startswith("lead=")), ())
        dd = next((o[4:].split(",") for o in opts if o.startswith("def=")), ())
        rw = next((o[3:].split(",") for o in opts if o.startswith("rw=")), ())
        r4 = run_once(u, ok_files, set(asm) - set(missing), dict(res, c_native="cnative" in opts, hdr_fix=hf,
                                                                  prune_data="prune" in opts, lead_data=ld,
                                                                  def_data=dd, lit_rw=rw, lit_order="order" in opts,
                                                                  cpp_redir=next((o[7:].split(",") for o in opts if o.startswith("credir=")), ()),
                                                             pp_hoist="hoist" in opts, inline_copies=next((o[4:].split(",") if o[4:] else [] for o in opts if o == "inl" or o.startswith("inl=")), False)),
                      asm_data="lit" if "asmlit" in opts else "asmdata" in opts)
        if r4["ok"]:
            r4["fallback"] = "previous selection"
            return r4
    return r


PREV = {}


def lead_items(errors):
    """symbols.txt items between the aligned boundary and a misaligned section base."""
    S = G._dol()[1]
    out = []
    for e in errors:
        m = re.match(r"(\.\w+): base 0x([0-9A-F]{8}) not aligned to (\d+)", e)
        if not m:
            continue
        sec, b, al = m.group(1), int(m.group(2), 16), int(m.group(3))
        lo = b - b % al
        items = sorted((o for o in S.values() if o.sec == sec and lo <= o.addr < b), key=lambda o: o.addr)
        if not items or items[0].addr != lo or any(o.type == "function" or not o.size for o in items):
            continue
        out += [o.name for o in items if o.name not in out]
    return out


def load_prev(path):
    """game lines of a previous link_select.txt: (start, end) -> (asm list, options)."""
    if not os.path.exists(path):
        return
    for line in open(path):
        parts = line.split("#", 1)[0].split()
        if len(parts) >= 2 and parts[0] == "game":
            a, b = parts[1].split("-")
            asm = next((o[4:].split(",") for o in parts[2:] if o.startswith("asm=")), [])
            PREV[(a, b)] = (asm, set(parts[2:]))


def run_loop(u, ok_files, missing, res, c_native, start_force=(), prune=False, lead=()):
    res = dict(res)
    res["c_native"] = c_native
    if prune:
        res["prune_data"] = True
    if lead:
        res["lead_data"] = list(lead)
    force = set(start_force)
    res["hdr_fix"] = {}
    why = {f: "fallback: whole file" for f in start_force}
    res["why"] = why
    compile_seen = False

    def note(fns, reason):
        for f in fns:
            why.setdefault(f, reason)
    rounds = ASM["rounds"] if ASM["on"] else 1
    import time
    deadline = time.time() + ASM["loop_seconds"]   # (a 1,000-function file closure takes ~70 s a round)
    hfix_rounds = 32
    def_rounds = 4
    def_added = []
    r_last = None
    while rounds > 0:
        rounds -= 1
        if time.time() > deadline and r_last is not None:
            return r_last
        r = run_once(u, ok_files, force, dict(res))
        r_last = r
        r["compile_seen"] = compile_seen or r["cls"] == "compile"
        if r["ok"] or not ASM["on"] or r["cls"] in ("generator", "chunker"):
            return r
        if r["cls"] == "compile" and def_added:
            # the definitions just added do not compile (type not in scope): without them
            res["def_data"] = [n for n in res.get("def_data", ()) if n not in def_added]
            def_added, def_rounds = [], 0
            rounds += 1
            continue
        def_added = []
        if r["cls"] == "compile":
            compile_seen = True
            hc = header_conflict(r)
            if hc and hc[2] not in res["hdr_fix"].get(hc[0], ([], []))[0 if hc[1] == "name" else 1]:
                # a conflict between two hoisted headers: rename / undefine it around the later one
                names, macros = res["hdr_fix"].setdefault(hc[0], ([], []))
                (names if hc[1] == "name" else macros).append(hc[2])
                if hfix_rounds > 0:
                    hfix_rounds -= 1
                    rounds += 1
                continue
            m = re.search(r"identifier '((?:fn|lbl)_[0-9A-F]{8})\b[^']*'\s*(?:\n#\s*)?redeclared", r.get("compile_out", ""))
            if m and m.group(1) not in res.get("cpp_redir", ()) and hfix_rounds > 0:
                # two files declare one extern "C" name differently: the later one is redirected
                res["cpp_redir"] = list(res.get("cpp_redir", ())) + [m.group(1)]
                hfix_rounds -= 1
                rounds += 1
                continue
            # a declaration conflict between merged files: the offending file's functions go asm
            more = blamed_files(r, u["functions"], ok_files, force)
            if not more:
                return r
            note(more, "compile: " + (r["errors"][0] if r["errors"] else "")[-160:])
            force |= more
            if len(force) + len(missing) >= len(u["functions"]):
                return r
            continue
        errors = list(r["errors"])
        inside = inside_names(r, res)
        if inside and def_rounds > 0:
            # data the C code names that lies inside the unit's own pool: define it at its first user
            def_rounds -= 1
            res["def_data"] = list(res.get("def_data", ())) + inside
            def_added = inside
            rounds += 1
            continue
        if missing or force:
            # the asm functions' own data (literals, strings, tables) defined in the TU as bytes;
            # "lit": literals they share with later C functions made by the compiler in place
            for mode in (("lit", True) if ASM["lit"] else (True,)):
                r2 = run_once(u, ok_files, force, dict(res), asm_data=mode)
                if r2["ok"]:
                    return r2
                errors += r2["errors"]
        more = blamed_functions(errors, u["functions"], int(u["text"][0], 16)) - force - set(missing)
        note(more, "place: " + "; ".join(errors[:2])[:200])
        if not more:
            more = set(r.get("minority", []) + (r2.get("minority", []) if (missing or force) else [])) \
                & set(u["functions"]) - force - set(missing)
            note(more, "minority: " + "; ".join(errors[:2])[:200])
        bf = blamed_files(r, u["functions"], ok_files, force)
        note(bf - more, "file: " + "; ".join(r["errors"][:2])[:200])
        more |= bf
        if not more:
            return r
        force |= more
        if len(force) + len(missing) >= len(u["functions"]):
            return r
    return r


def run_once(u, ok_files, force, res, asm_data=False):
    try:
        if ASM["on"]:
            skipped = []
            text, lang, problems, asm_fns, data_names = G.generate(u["functions"], ok_files, f"unit {u['unit']}",
                                                                   fallback=True, force_asm=force, asm_data=asm_data,
                                                                   c_native=res.get("c_native", False),
                                                                   hdr_fix=res.get("hdr_fix"),
                                                                   prune_data=res.get("prune_data", False),
                                                                   lead_data=res.get("lead_data", ()),
                                                                   def_data=res.get("def_data", ()),
                                                                   def_skipped=skipped,
                                                                   lit_rw=res.get("lit_rw", ()),
                                                                   lit_order=res.get("lit_order", False),
                                                                   cpp_redir=res.get("cpp_redir", ()),
                                                                   pp_hoist=res.get("pp_hoist", False),
                                                                   inline_copies=res.get("inline_copies", False))
            if skipped:   # definitions it cannot write are left out (the line lists the rest)
                res["def_data"] = [n for n in res["def_data"] if n not in skipped]
        else:
            (text, lang, problems), asm_fns = G.generate(u["functions"], ok_files, f"unit {u['unit']}"), []
    except Exception as e:  # noqa: BLE001
        res.update(ok=False, cls="generator", errors=[str(e)[:300]])
        return res
    if asm_fns:
        S = G._dol()[1]
        res["asm"] = asm_fns
        res["asm_bytes"] = sum(S[f].size for f in asm_fns)
        res["asm_data"] = asm_data
    path = os.path.join(TU_DIR, f"u{u['unit']:04d}_{u['text'][0]}{lang}")
    res["files"] = sorted({ok_files[f][0] for f in u["functions"] if f in ok_files and f not in asm_fns})
    smaps = G.symbol_map_renames(res["files"])
    bad = [o for o, n in smaps.items() if RENAMES.get(o, n) != n and RENAMES.get(o) in BASE_RENAMES.values()]
    if bad:
        problems = problems + [f"symbol map renames {bad[0]}, which a library source names {RENAMES[bad[0]]}"]
    if smaps:
        res["renames"] = smaps
    # the same prelude as gen_units.py: library names through lib_aliases.h, nothing dead-stripped
    body = text

    def prelude(undefs):
        return "#pragma force_active on\n" + ('#include "tu/lib_aliases.h"\n' if RENAMES else "") + \
            "".join(f"#undef {o}\n" for o in sorted(undefs) if o not in BASE_RENAMES) + body
    undefs = set(smaps)
    text = prelude(undefs)
    open(path, "w").write(text)
    res["source"] = os.path.relpath(path, ROOT)
    if problems:
        res.update(ok=False, cls=classify(problems), errors=problems[:5])
        return res
    try:
        obj = PL.compile_src(os.path.relpath(path, ROOT))
        for _k in range(4):
            # inline copies the compiler did not inline everywhere stay out (prototype again)
            if res.get("inline_copies") in (None, False):
                break
            _rel = PL.parse_elf(obj)[2]
            left = sorted({r[2][:-len("__tu_inl")] for lst in _rel.values() for r in lst
                           if r[2].endswith("__tu_inl")} - set(res["inline_copies"]))
            if not left:
                break
            os.unlink(obj)
            res["inline_copies"] = sorted(set(res["inline_copies"]) | set(left))
            gen = G.generate(u["functions"], ok_files, f"unit {u['unit']}", fallback=True, force_asm=force,
                             asm_data=asm_data, c_native=res.get("c_native", False), hdr_fix=res.get("hdr_fix"),
                             prune_data=res.get("prune_data", False), lead_data=res.get("lead_data", ()),
                             def_data=res.get("def_data", ()), def_skipped=[], lit_rw=res.get("lit_rw", ()),
                             lit_order=res.get("lit_order", False), cpp_redir=res.get("cpp_redir", ()),
                             pp_hoist=res.get("pp_hoist", False), inline_copies=res["inline_copies"])
            body = gen[0]
            open(path, "w").write(prelude(undefs))
            obj = PL.compile_src(os.path.relpath(path, ROOT))
        if smaps:
            ren, defd = PL.settle_renames(obj, smaps)
            if {o for o in undefs if o not in BASE_RENAMES} != {o for o in defd if o not in BASE_RENAMES}:
                # labels this unit does not define go through lib_aliases.h (no #undef)
                os.unlink(obj)
                undefs = defd
                open(path, "w").write(prelude(undefs))
                obj = PL.compile_src(os.path.relpath(path, ROOT))
                ren, defd = PL.settle_renames(obj, smaps)
    except RuntimeError as e:
        res.update(ok=False, cls="compile", errors=[str(e)[-400:]], compile_out=str(e)[:3000])
        return res
    try:
        if smaps:
            smaps = PL.object_renames(obj, smaps)
            res["renames"] = smaps
        P, dropped = PL.place_game(obj, {**{new: old for old, new in RENAMES.items()},
                                         **{n: o for o, n in smaps.items()}})
        if dropped:
            res["dead_stripped"] = dropped
    finally:
        os.unlink(obj)
    if not P.ok:
        # code whose data references imply a minority base: those functions pool their data
        # differently (their literals sit elsewhere in the original pool)
        votes = []
        for sec, bv in P.base_votes.items():
            if len(bv) > 1:
                best = max(bv, key=lambda b: len(bv[b]))
                votes += [a for b, L in bv.items() if b != best for a in L]
        res["minority"] = sorted({fn_at(a) for a in votes} - {None})
    res.update(ok=P.ok, cls=("ok+asm" if asm_fns else "ok") if P.ok else classify(P.errors), errors=P.errors[:8],
               ranges={k: ["%08X" % a, "%08X" % b] for k, (a, b) in P.ranges.items()})
    return res


RENAMES = {}
BASE_RENAMES = {}


def lib_candidates():
    """Library sources whose functions are all verified (lib/verified.json, lib/map.json status ok)
    and that have recorded flags (lib/manifest.json)."""
    m = json.load(open(os.path.join(ROOT, "lib/map.json")))
    mf = json.load(open(os.path.join(ROOT, "lib/manifest.json")))
    v = json.load(open(os.path.join(ROOT, "lib/verified.json")))
    return [k for k in v if k in mf and k in m["sources"]
            and all(x[2] == "ok" for x in m["sources"][k]["functions"].values())]


def try_libs(j):
    """Place every candidate library source the way gen_units.py does (names by address)."""
    import gen_units as GU
    lib_map = json.load(open(os.path.join(ROOT, "lib/map.json")))
    manifest = json.load(open(os.path.join(ROOT, "lib/manifest.json")))
    GU.GLOBAL_RENAMES.update(RENAMES)

    _WORK.update(lib_map=lib_map, manifest=manifest)
    res = pmap(_lib_one, lib_candidates(), j)
    # two sources of the same code (different repos): keep the first that places
    import gen_config as GC
    taken = [(a, b) for a, b, _n in GC.base_ranges()]
    names = {}
    for o, n in RENAMES.items():
        names.setdefault(n, o)
    for r in res:
        if not r["ok"]:
            continue
        rng = [(int(a, 16), int(b, 16)) for a, b in r["ranges"].values()]
        if any(a < y and x < b for a, b in rng for x, y in taken):
            r.update(ok=False, cls="duplicate", errors=["overlaps another library source that places"])
            continue
        dup = next((n for o, n in r["renames"].items() if names.get(n, o) != o), None)
        if dup:   # the game links two copies of some SDK files (MEM): one name per symbol
            r.update(ok=False, cls="duplicate", errors=[f"renames a symbol to {dup}, which another symbol already has"])
            continue
        taken += rng
        for o, n in r["renames"].items():
            names.setdefault(n, o)
    return res


def _lib_one(key):
    import gen_units as GU
    try:
        unit, errors = GU.lib_unit(key, _WORK["lib_map"], _WORK["manifest"])
    except Exception as e:  # noqa: BLE001
        return {"lib": key, "ok": False, "cls": "compile", "errors": [str(e)[-300:]]}
    r = {"lib": key, "ok": not errors, "cls": "ok" if not errors else lib_class(errors),
         "errors": errors[:8], "functions": unit.get("functions", 0), "ranges": unit.get("ranges", {})}
    r["renames"] = unit.get("renames", {})
    if unit.get("extra_cflags"):
        r["extra_cflags"] = unit["extra_cflags"]
    return r


def lib_class(errors):
    if any("not in symbols.txt" in e and e.startswith("function") for e in errors):
        return "stripped"     # the source has functions the original link dead-stripped
    return classify(errors)


def write_select(results, libs, path=None):
    """config/RFEE01/link_select.txt: every library source and game unit that places."""
    path = path or os.path.join(ROOT, "config/RFEE01/link_select.txt")
    lines = ["# Generated by tools/build/try_units.py --write-select: every unit that places (see docs/BUILD.md).\n",
             "# Use: python3 -I tools/build/gen_units.py -j 14\n"]
    excl = os.path.join(ROOT, "config/RFEE01/lib_exclude.txt")
    excluded = {l.strip() for l in open(excl) if l.strip() and not l.startswith("#")} if os.path.exists(excl) else set()
    lines += [f"lib {r['lib']}\n" for r in libs if r["ok"] and r["lib"] not in excluded]
    lines += [f"game {r['text'][0]}-{r['text'][1]}" + (f" asm={','.join(r['asm'])}" if r.get("asm") else "") + (" asmlit" if r.get("asm_data") == "lit" else " asmdata" if r.get("asm_data") else "") + (" cnative" if r.get("c_native") else "") + (" hfix=" + G.format_hdr_fix(r["hdr_fix"]) if r.get("hdr_fix") else "") + (" prune" if r.get("prune_data") else "") + (" lead=" + ",".join(r["lead_data"]) if r.get("lead_data") else "") + (" def=" + ",".join(r["def_data"]) if r.get("def_data") else "") + (" rw=" + ",".join(r["lit_rw"]) if r.get("lit_rw") else "") + (" order" if r.get("lit_order") else "") + (" credir=" + ",".join(r["cpp_redir"]) if r.get("cpp_redir") else "") + (" hoist" if r.get("pp_hoist") else "") + ((" inl=" + ",".join(r["inline_copies"]) if r["inline_copies"] else " inl") if r.get("inline_copies") not in (None, False) else "") + "\n"
              for r in results if r["ok"]]
    open(path, "w").write("".join(lines))
    print(f"{path}: {sum(r['ok'] for r in libs)} library sources, {sum(r['ok'] for r in results)} game units")


def write_lib_tsv(libs):
    with open(os.path.join(ROOT, "docs/tu_libs.tsv"), "w") as f:
        f.write("# lib_source\tstatus\tfunctions\tsections\tfirst_problem\n")
        for r in sorted(libs, key=lambda r: r["lib"]):
            secs = " ".join(f"{k}:{a[2:]}-{b[2:]}" for k, (a, b) in r.get("ranges", {}).items()) if r["ok"] else ""
            f.write("\t".join([r["lib"], r["cls"], str(r.get("functions", "")), secs,
                                "" if r["ok"] else (r["errors"][0] if r["errors"] else "").replace("\t", " ")[:160]]) + "\n")


def catalog_files():
    out = {}
    for line in open(os.path.join(ROOT, "docs/signatures/CATALOG.tsv")):
        if line.startswith("#"):
            continue
        parts = line.rstrip("\n").split("\t")
        if len(parts) > 3:
            out[parts[0]] = parts[3]
    return out


def link_units(units, ok_files):
    """Merge TU-map units so that no source file is split between two link units: MWCC inlines
    functions defined earlier in the same file (-inline auto), so a file's functions must be
    compiled together. The result is a list of contiguous unit runs."""
    cat = catalog_files()
    file_units = {}
    for k, u in enumerate(units):
        for f in u["functions"]:
            src = ok_files[f][0] if f in ok_files else cat.get(f)
            if src:
                file_units.setdefault(src, []).append(k)
    # interval closure
    end = list(range(len(units)))   # end[k]: last unit index that must be merged with k
    for ks in file_units.values():
        a, b = min(ks), max(ks)
        if b > end[a]:
            end[a] = b
    merged = []
    k = 0
    while k < len(units):
        e = end[k]
        j = k
        while j <= e:
            e = max(e, end[j])
            j += 1
        group = units[k:e + 1]
        data = {}
        for g in group:
            for sec, (x, y) in (g.get("data") or {}).items():
                if x == y:
                    continue
                if sec in data:
                    data[sec] = [min(data[sec][0], x), max(data[sec][1], y)]
                else:
                    data[sec] = [x, y]
        merged.append({"unit": group[0]["unit"], "units": [g["unit"] for g in group],
                       "text": [group[0]["text"][0], group[-1]["text"][1]],
                       "functions": [f for g in group for f in g["functions"]], "data": data})
        k = e + 1
    return merged


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("-j", type=int, default=12)
    ap.add_argument("--units")
    ap.add_argument("--asm", action="store_true", help="emit functions that are not exact (or differ when merged) as asm")
    ap.add_argument("--libs", action="store_true", help="also place every candidate library source (docs/tu_libs.tsv)")
    ap.add_argument("--write-select", action="store_true", help="write config/RFEE01/link_select.txt (implies --libs)")
    ap.add_argument("--prev", default=os.path.join(ROOT, "config/RFEE01/link_select.txt"),
                    help="previous selection: a unit that no longer places tries its old asm list")
    ap.add_argument("--no-shrink", action="store_true", help="skip the pass that gives asm functions back to C")
    ap.add_argument("--no-lit", action="store_true", help="skip the asmlit variant (shared literals made in place)")
    ap.add_argument("--no-v2", action="store_true", help="skip variant v2 (named literals rewritten, literal order, named data defined)")
    a = ap.parse_args()
    ASM["on"] = a.asm
    ASM["lit"] = not a.no_lit
    ASM["shrink"] = not a.no_shrink
    ASM["v2"] = not a.no_v2
    load_prev(a.prev)
    init_fn_starts()
    if a.asm:
        G.asm_lines()
        G.nonmatching_files()
    import gen_config as GC
    RENAMES.update(GC.lib_renames())
    BASE_RENAMES.update(RENAMES)
    # names the per-function symbol maps give to original labels (vtables, ...): other units
    # reach them through lib_aliases.h like library names
    for o, n in G.symbol_map_renames(sorted({p for ps in G.load_ok_files().values() for p in ps[:1]})).items():
        RENAMES.setdefault(o, n)
    import gen_units as GU
    # the generated TUs include src/tu/lib_aliases.h: during the run it holds every rename (all
    # exact files' symbol maps); the build's own copy (written by gen_units.py for the linked
    # units) is put back at exit, so a try_units run alone never breaks `ninja`
    alias_path = os.path.join(ROOT, "src/tu/lib_aliases.h")
    saved = open(alias_path).read() if os.path.exists(alias_path) else None
    import atexit
    atexit.register(lambda: saved is not None and open(alias_path, "w").write(saved))
    GU.write_aliases(RENAMES)   # gen_units.py adds the renames of the library units it links
    os.makedirs(TU_DIR, exist_ok=True)
    units = json.load(open(os.path.join(ROOT, "build/tmp/buildtree/tu_units.json")))
    ok_files = G.load_ok_files()
    if a.units:
        want = {int(x) for x in a.units.split(",")}
        units = [u for u in units if u["unit"] in want]
    PL.dolmodel()
    PL.eh_entries()
    G._dol()
    _WORK["ok_files"] = ok_files
    fine = pmap(_run_unit, units, a.j, weight=lambda u: len(u["functions"]))
    # second pass: where a fine unit fails although all its functions are exact, try the run
    # of units that keeps every source file whole (inlining across functions of one file)
    byid = {r["unit"]: r for r in fine}
    groups = [g for g in link_units(units, ok_files) if len(g["units"]) > 1
              and any(byid[k]["cls"] not in ("ok", "ok+asm", "inexact") for k in g["units"])
              and len(g["functions"]) <= ASM["max_group"]]
    coarse = pmap(_run_unit, groups, a.j, weight=lambda u: len(u["functions"]))
    results = []
    replaced = set()
    def c_bytes(r):
        return (int(r["text"][1], 16) - int(r["text"][0], 16) - r.get("asm_bytes", 0)) if r["ok"] else 0
    for g, r in zip(groups, coarse):
        # the file closure replaces its units only if it links more C than they do on their own
        if r["ok"] and c_bytes(r) > sum(c_bytes(byid[k]) for k in g["units"]):
            r["units"] = g["units"]
            r["level"] = "file-closure"
            results.append(r)
            replaced |= set(g["units"])
    for r in fine:
        if r["unit"] not in replaced:
            r["units"] = [r["unit"]]
            r["level"] = "unit"
            results.append(r)
    results.sort(key=lambda r: r["text"][0])
    results = lead_merges(results, units, ok_files, a.j)
    if not a.units:
        json.dump(results, open(OUT, "w"), indent=0)
        write_tsv(results)
    if a.libs or a.write_select:
        libs = try_libs(a.j)
        json.dump(libs, open(OUT.replace(".json", "_libs.json"), "w"), indent=0)
        write_lib_tsv(libs)
        lc = collections.Counter(r["cls"] for r in libs)
        print("libraries:", ", ".join(f"{k} {v}" for k, v in lc.most_common()))
        if a.write_select and not a.units:
            write_select(results, libs)
    c = collections.Counter(r["cls"] for r in results)
    nb = collections.Counter()
    for r in results:
        nb[r["cls"]] += int(r["text"][1], 16) - int(r["text"][0], 16)
    for k, v in c.most_common():
        print(f"{k:13} {v:5} units  0x{nb[k]:06X} bytes")
    if a.units:
        for r in results:
            print(json.dumps(r, indent=1)[:3000])


def lead_merges(results, units, ok_files, j):
    """A unit that places only with `lead=` items owned by the unit before it overlaps that
    unit's pool (gen_units.py drops it): try the run of units from the owner to it as one unit,
    which then holds the pool from its aligned start; it replaces them if it links more C."""
    S = PL.dolmodel()[0]
    idx = {u["unit"]: k for k, u in enumerate(units)}
    fn_unit = {f: k for k, u in enumerate(units) for f in u["functions"]}
    by_unit = {k: r for r in results for k in r.get("units", [r["unit"]])}
    groups = []
    for r in results:
        if not r["ok"] or not r.get("lead_data") or r.get("level") != "unit":
            continue
        owners = {fn_unit[f] for n in r["lead_data"] if n in S for f in S[n].refby if f in fn_unit}
        k1 = idx[r["unit"]]
        if not owners or min(owners) >= k1 or k1 - min(owners) > 4:
            continue
        g = units[min(owners):k1 + 1]
        if any(by_unit.get(x["unit"], {}).get("level") == "file-closure" for x in g):
            continue
        data = {}
        for x in g:
            for sec, (lo, hi) in (x.get("data") or {}).items():
                if lo != hi:
                    data[sec] = [min(data[sec][0], lo), max(data[sec][1], hi)] if sec in data else [lo, hi]
        groups.append({"unit": g[0]["unit"], "units": [x["unit"] for x in g], "text": [g[0]["text"][0], g[-1]["text"][1]],
                       "functions": [f for x in g for f in x["functions"]], "data": data, "lead_unit": r["unit"]})
    if not groups:
        return results
    merged = pmap(_run_unit, groups, j, weight=lambda u: len(u["functions"]))
    drop = set()
    add = []
    for g, r in zip(groups, merged):
        # (the unit with lead= does not link next to its owner: gen_units.py drops it)
        old = [by_unit.get(k) for k in g["units"] if k != g["lead_unit"]]
        if r["ok"] and not drop & set(g["units"]) and c_bytes(r) > sum(max(c_bytes(o), 0) for o in old if o):
            r["units"] = g["units"]
            r["level"] = "lead-merge"
            add.append(r)
            drop |= set(g["units"])
    out = [r for r in results if not set(r.get("units", [r["unit"]])) & drop] + add
    out.sort(key=lambda r: r["text"][0])
    print(f"lead merges: {len(add)} of {len(groups)}")
    return out


def write_tsv(results=None):
    """docs/tu_units.tsv: one row per link unit with its build status."""
    results = results or json.load(open(OUT))
    tus = [l.rstrip("\n").split("\t") for l in open(os.path.join(ROOT, "docs/tu_map.tsv")) if not l.startswith("#")]

    def tu_of(addr):
        for r in tus:
            if int(r[1], 16) <= addr < int(r[2], 16):
                return r[0]
        return ""
    with open(os.path.join(ROOT, "docs/tu_units.tsv"), "w") as f:
        f.write("# units\ttext_start\ttext_end\tfunctions\ttu\tlevel\tstatus\tsections\tfirst_problem\tasm_functions\tasm_bytes\n")
        for r in results:
            secs = " ".join(f"{k}:{a}-{b}" for k, (a, b) in r.get("ranges", {}).items()) if r["ok"] else ""
            f.write("\t".join([",".join(map(str, r.get("units", [r["unit"]]))), r["text"][0], r["text"][1], str(r["n"]),
                               tu_of(int(r["text"][0], 16)), r.get("level", "unit"), r["cls"], secs,
                               ("" if r["ok"] else (r["errors"][0] if r["errors"] else "")).replace("\t", " ").replace("\n", " ")[:160],
                               ",".join(r.get("asm", [])), "0x%X" % r["asm_bytes"] if r.get("asm_bytes") else ""]) + "\n")


if __name__ == "__main__":
    if "--tsv" in sys.argv:
        write_tsv()
    else:
        main()
