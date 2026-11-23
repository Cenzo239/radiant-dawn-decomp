#!/usr/bin/env python3
"""Classify near misses that differ from the original only in register choice.

A function that isn't byte-exact can still be the same code with different
registers. This tool compiles a source file like check_func.py does and puts
each function into one of these classes:

  exact      byte for byte, references right (what check_func.py calls OK)
  renamed    same instructions in the same order, references right, and the
             registers differ by one consistent renaming of callee-saved
             registers (r14-r31, f14-f31). This is the same program: only the
             names of the saved registers changed.
  regs       same instructions in the same order, references right, but the
             register differences aren't one consistent renaming (live ranges
             were split differently). Very likely equivalent, not proven.
  slots      like `regs`, and in addition some locals sit in other stack
             slots: r1-relative offsets differ by one consistent one-to-one
             mapping. Same strength of evidence as `regs`.
  sched      same size and block structure, and every basic block holds the
             same instructions as the original's block (registers aside) in a
             different order. Typical when a different register choice made
             the scheduler move one or two instructions. Likely equivalent,
             weaker evidence than `regs`: dependencies between the moved
             instructions aren't checked.
  other      anything else (different size, constants, references or blocks)

Only `exact` counts as a match. `renamed` and `regs` are for the port, where
register choice doesn't matter.

Usage:
  tools/check_regs.py FILE [FILE...] [--extra "-i dir"] [--tsv out.tsv]
"""
import argparse
import os
import re
import shlex
import struct
import subprocess
import sys
import tempfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import check_func as c  # noqa: E402

G, F = "g", "f"
FLOAT_X = {535, 567, 599, 631, 663, 695, 727, 759, 983}


def fields(w):
    """Register fields of one instruction: list of (class, shift)."""
    op = w >> 26
    d, a, b, cc = 21, 16, 11, 6
    if op in (16, 17, 18, 19):
        return []
    if op in (10, 11):
        return [(G, a)]
    if op in (46, 47):  # lmw/stmw: the first field is a count, not a name
        return [(G, a)]
    if op in (7, 8, 12, 13, 14, 15, 24, 25, 26, 27, 28, 29, 20, 21) or 32 <= op <= 45:
        return [(G, d), (G, a)]
    if op == 23:
        return [(G, d), (G, a), (G, b)]
    if 48 <= op <= 55:
        return [(F, d), (G, a)]
    if op in (56, 57, 60, 61):
        return [(F, d), (G, a)]
    if op == 31:
        xo = (w >> 1) & 0x3FF
        if xo in (339, 467, 19, 144, 83, 146):
            return [(G, d)]
        if xo in (0, 32):
            return [(G, a), (G, b)]
        if xo == 824:
            return [(G, d), (G, a)]
        if xo in FLOAT_X:
            return [(F, d), (G, a), (G, b)]
        return [(G, d), (G, a), (G, b)]
    if op in (59, 63, 4):
        xo5 = (w >> 1) & 0x1F
        if op != 4 and xo5 >= 16:
            return [(F, d), (F, a), (F, b), (F, cc)]
        xo = (w >> 1) & 0x3FF
        if op == 63 and xo in (0, 32):
            return [(F, a), (F, b)]
        if op == 4:
            return [(F, d), (F, a), (F, b), (F, cc)]
        return [(F, d), (F, a), (F, b)]
    return None  # unknown: compare the whole word


def split(w):
    """(skeleton, [(class, number)])."""
    fs = fields(w)
    if fs is None:
        return w, []
    regs = []
    for cls, sh in fs:
        regs.append((cls, (w >> sh) & 0x1F))
        w &= ~(0x1F << sh)
    return w, regs


def zero_base(w):
    """True when the instruction reads rA as the constant 0 if rA is r0."""
    op = w >> 26
    return op in (14, 15) or 32 <= op <= 55


def classify(ours, theirs):
    if len(ours) != len(theirs):
        return "other", 0
    n = len(ours) // 4
    mapping, used, renamed, diff = {}, {}, True, 0
    slot_fwd, slot_back, slots = {}, {}, False
    for i in range(n):
        wo, = struct.unpack(">I", ours[i * 4:i * 4 + 4])
        wt, = struct.unpack(">I", theirs[i * 4:i * 4 + 4])
        if wo != wt:
            diff += 1
        so, ro = split(wo)
        st, rt = split(wt)
        if so != st:
            # The same access to another stack slot: op rX,off(r1) or addi rX,r1,off.
            op = wo >> 26
            on_stack = (op == 14 or 32 <= op <= 55) and op == wt >> 26 and \
                ((wo >> 16) & 0x1F) == 1 == ((wt >> 16) & 0x1F) and \
                ((wo >> 21) & 0x1F) == ((wt >> 21) & 0x1F)  # same register, or it is a reorder
            if not on_stack or (so & ~0xFFFF) != (st & ~0xFFFF):
                return "other", diff
            a, b = wt & 0xFFFF, wo & 0xFFFF
            if slot_fwd.setdefault(a, b) != b or slot_back.setdefault(b, a) != a:
                return "other", diff
            slots = True
        if zero_base(wo) and (((wo >> 16) & 0x1F) == 0) != (((wt >> 16) & 0x1F) == 0):
            return "other", diff
        for (cls, mine), (_c, orig) in zip(ro, rt):
            if (mine < 14) != (orig < 14) or (mine < 14 and mine != orig):
                # A volatile register changed: not a saved-register renaming.
                renamed = False
                continue
            if mapping.setdefault((cls, orig), mine) != mine or used.setdefault((cls, mine), orig) != orig:
                renamed = False
    if diff == 0:
        return "exact", 0
    if slots:
        return "slots", diff
    return ("renamed" if renamed else "regs"), diff


SDA_BASE, SDA2_BASE = 0x804CA040 + 0x8000, 0x804CCA60 + 0x8000


def _is_ctl(w):
    op = w >> 26
    return op in (16, 18) or (op == 19 and ((w >> 1) & 0x3FF) in (16, 528))


def _branch_target(w, pc):
    op = w >> 26
    if op == 18:
        d = w & 0x03FFFFFC
        return pc + (d - 0x04000000 if d & 0x02000000 else d)
    if op == 16:
        d = w & 0xFFFC
        return pc + (d - 0x10000 if d & 0x8000 else d)
    return None


def _key(w, pc):
    """Register-masked form of a word, with branches made position independent."""
    op = w >> 26
    if op == 18:
        return ("b", w & 3, _branch_target(w, pc))
    if op == 16:
        return ("bc", w & 0xFFFF0003, _branch_target(w, pc))
    return split(w)[0]


def _sections():
    out = {}
    pat = re.compile(r"^(\S+) = (\.\w+):0x")
    for line in open(c.SYMBOLS):
        m = pat.match(line)
        if m:
            out[m.group(1)] = m.group(2)
    return out


def sched_equal(ours, theirs, relocs, addr, all_addrs, sections=None, read=None):
    """True when each basic block has the original's instructions in some order.

    ours/theirs are the raw function bytes; relocs is [(offset in function,
    type, symbol, addend)]. Our words are linked against symbols.txt first, so
    reference targets take part in the comparison. Words that refer to symbols
    without an original name (literals, strings) match on everything but the
    relocated field.
    """
    n = len(theirs) // 4
    tw = [struct.unpack(">I", theirs[i * 4:i * 4 + 4])[0] for i in range(n)]
    ow = [struct.unpack(">I", ours[i * 4:i * 4 + 4])[0] for i in range(n)]
    wild = [0] * n
    forced = {}
    sections = sections or {}
    local = {}
    for off, rtype, sym, addend, data in relocs:
        i = (off - 2 if rtype in (4, 5, 6) else off) // 4
        if not 0 <= i < n:
            continue
        mask = c.RELOC_MASK.get(rtype, 0xFFFFFFFF)
        a = all_addrs.get(sym)
        if a is None or sym.startswith(("@", ".")):
            # Compiler-local names (literals, string bases, pooled statics)
            # can collide with unrelated entries in symbols.txt.
            if rtype == 10:
                # A call to a helper without an original name (__ptmf_scall):
                # matches any call that leaves the function.
                forced[i] = ("b?", ow[i] & 3)
                continue
            wild[i] = mask
            ow[i] &= ~mask
            if rtype == 109 and data is not None:
                local[i] = data
            continue
        a += addend
        w = ow[i] & ~mask
        if rtype == 10:
            forced[i] = ("b", ow[i] & 3, a)
            continue
        if rtype == 11:
            forced[i] = ("bc", ow[i] & 0xFFFF0003, a)
            continue
        if rtype == 4:
            w |= a & 0xFFFF
        elif rtype == 5:
            w |= (a >> 16) & 0xFFFF
        elif rtype == 6:
            w |= ((a + 0x8000) >> 16) & 0xFFFF
        elif rtype == 109:
            if sections.get(sym, "").startswith((".sdata2", ".sbss2")):
                w |= (2 << 16) | ((a - SDA2_BASE) & 0xFFFF)
            elif sections.get(sym, "").startswith((".sdata", ".sbss")):
                w |= (13 << 16) | ((a - SDA_BASE) & 0xFFFF)
            else:
                w |= a & 0xFFFF
        else:
            return False
        ow[i] = w
    starts = {0}
    for i, w in enumerate(tw):
        if _is_ctl(w):
            starts.add(i)
            starts.add(i + 1)
            t = _branch_target(w, addr + i * 4)
            if t is not None and addr <= t < addr + n * 4 and not (w & 1):
                starts.add((t - addr) // 4)
    cuts = sorted(s for s in starts if s <= n) + [n]
    for lo, hi in zip(cuts, cuts[1:]):
        if lo == hi:
            continue
        want = [_key(tw[i], addr + i * 4) for i in range(lo, hi)]
        exact, loose = [], []
        for i in range(lo, hi):
            if i in forced:
                exact.append(forced[i])
            elif wild[i]:
                loose.append((split(ow[i])[0], wild[i], local.get(i)))
            else:
                exact.append(_key(ow[i], addr + i * 4))
        for k in exact:
            if isinstance(k, tuple) and k[0] == "b?":
                k = next((x for x in want if isinstance(x, tuple) and x[0] == "b" and x[1] == k[1]
                          and not addr <= x[2] < addr + n * 4), None)
            if k not in want:
                return False
            want.remove(k)
        # Original words of this block, kept beside their masked keys so a
        # literal's value can be compared with the one the original loads.
        raw = {}
        for i in range(lo, hi):
            raw.setdefault(_key(tw[i], addr + i * 4), []).append(tw[i])

        def same_value(key, data):
            if data is None or read is None:
                return True
            for w in raw.get(key, []):
                base = {13: SDA_BASE, 2: SDA2_BASE}.get((w >> 16) & 0x1F)
                if base is None:
                    continue
                simm = w & 0xFFFF
                try:
                    if read(base + (simm - 0x10000 if simm & 0x8000 else simm), len(data)) == data:
                        return True
                except KeyError:
                    pass
            return False

        for k, mask, data in loose:
            # The original word with the same field cleared, registers masked.
            hit = next((x for x in want if isinstance(x, int) and (x & ~mask & 0xFFFFFFFF) == k & ~mask
                        and same_value(x, data)), None)
            if hit is None:
                return False
            want.remove(hit)
        if want:
            return False
    return True


def check_file(source, extra, cc="GC/3.0a5.2"):
    """{function: (class, differing words, size)} for one source file."""
    cmd = [sys.executable, "-I", os.path.join(c.ROOT, "tools/check_func.py"), source, "--extra", extra]
    symmap = os.path.splitext(source)[0] + ".symbols.json"
    if os.path.exists(os.path.join(c.ROOT, symmap) if not os.path.isabs(symmap) else symmap):
        cmd += ["--symbol-map", symmap]
    r = subprocess.run(cmd, capture_output=True, text=True, cwd=c.ROOT)
    if "COMPILE FAILED" in r.stdout:
        return None
    bad_refs = set(re.findall(r"DIFF (\S+): \d+ wrong reference", r.stdout))
    compiler = os.path.join(c.ROOT, "build/compilers", cc, "mwcceppc.exe")
    os.makedirs(os.path.join(c.ROOT, "build/tmp"), exist_ok=True)
    with tempfile.TemporaryDirectory(dir=os.path.join(c.ROOT, "build/tmp")) as tmp:
        obj = os.path.join(tmp, "out.o")
        r = subprocess.run([c.WIBO, compiler, *shlex.split(c.DEFAULT_FLAGS), *shlex.split(extra),
                            "-c", source, "-o", obj], cwd=c.ROOT, capture_output=True, text=True)
        if r.returncode != 0 or not os.path.exists(obj):
            return None
        secs, syms, relocs = c.parse_elf(obj)
    orig_syms = c.load_symbols()
    all_addrs = c.load_all_symbol_addresses()
    sections = _sections()
    read = c.dol_reader()
    out = {}
    for s in syms:
        if s["type"] != 2 or s["shndx"] == 0 or s["shndx"] >= 0xFF00:
            continue
        sec = secs[s["shndx"]]
        if not sec["name"].startswith(".text") or s["name"] not in orig_syms:
            continue
        addr, osize = orig_syms[s["name"]]
        ours = bytearray(sec["data"][s["value"]:s["value"] + s["size"]])
        theirs = bytearray(read(addr, osize))
        raw_ours, raw_theirs = bytes(ours), bytes(theirs)
        fn_relocs = []
        for off, rtype, t, a, ts in relocs.get(s["shndx"], []):
            if not 0 <= off - s["value"] < len(ours):
                continue
            data = None
            tsec = secs[ts["shndx"]] if 0 < ts["shndx"] < len(secs) else None
            if tsec is not None and tsec["type"] != 8 and not tsec["name"].startswith(".text") and ts["size"] > a >= 0:
                data = bytes(tsec["data"][ts["value"] + a:ts["value"] + ts["size"]])
            fn_relocs.append((off - s["value"], rtype, t, a, data))
        for off, rtype, _t, _a, _s in relocs.get(s["shndx"], []):
            rel = off - s["value"]
            if 0 <= rel < len(ours):
                word_off = rel - 2 if rtype in (4, 5, 6) else rel & ~3
                mask = c.RELOC_MASK.get(rtype, 0xFFFFFFFF)
                for buf in (ours, theirs):
                    if word_off + 4 <= len(buf):
                        w, = struct.unpack(">I", buf[word_off:word_off + 4])
                        struct.pack_into(">I", buf, word_off, w & ~mask)
        cls, diff = classify(ours, theirs)
        if s["name"] in bad_refs:
            cls = "other"
        if cls == "other" and len(raw_ours) == len(raw_theirs) and \
                sched_equal(raw_ours, raw_theirs, fn_relocs, addr, all_addrs, sections, read):
            cls = "sched"
        out[s["name"]] = (cls, diff, osize)
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("sources", nargs="+")
    ap.add_argument("--extra", default="")
    ap.add_argument("--tsv")
    args = ap.parse_args()
    rows = []
    for src in args.sources:
        d = os.path.dirname(src)
        extra = args.extra or f"-i {shlex.quote(d)}"
        res = check_file(src, extra)
        if res is None:
            print(f"{src}: COMPILE FAILED")
            continue
        for name, (cls, diff, size) in sorted(res.items()):
            print(f"  {cls:8} {name} (0x{size:X} bytes, {diff} words differ)")
            rows.append((name, cls, diff, size, src))
    if args.tsv:
        with open(args.tsv, "w") as f:
            for row in rows:
                f.write("\t".join(str(x) for x in row) + "\n")


if __name__ == "__main__":
    main()
