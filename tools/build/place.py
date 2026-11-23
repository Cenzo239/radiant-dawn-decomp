#!/usr/bin/env python3
"""Place a compiled object in main.dol: find the address range each of its sections
must occupy, and check that linking it there reproduces the DOL.

A unit (one compiled source) can replace dtk's asm for exactly the byte ranges it emits.
For every allocated section of the object this tool derives the DOL base address
(text: from the function names; data: from the original instructions that reference
the object's data symbols), then checks
  - the section maps to one contiguous range at one base, aligned to the section alignment,
  - its bytes equal the DOL with relocated fields masked, and every relocation (in code
    and data) points where the original points,
  - every symbols.txt symbol that starts inside an owned range is either defined by the
    object under the same (global) name or referenced only from inside the unit's ranges
    (otherwise the rest of the link would lose a symbol it needs),
  - the text range holds exactly the object's functions.
It prints the splits.txt section lines, or the reasons the object cannot be placed.

Usage: python3 -I tools/build/place.py src/tu/x.c [--cc GC/3.0a5.2] [--flags "..."] [--names map.json]
As a module: place(obj_path, names=None) -> Placement
"""
import argparse
import bisect
import json
import os
import re
import shlex
import struct
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(ROOT, "tools"))
sys.path.insert(0, HERE)
import check_func as CF  # noqa: E402
import dolmodel as M  # noqa: E402

SDA_BASE, SDA2_BASE = 0x804CA040 + 0x8000, 0x804CCA60 + 0x8000
ALLOC_SECS = (".text", ".rodata", ".data", ".bss", ".sdata", ".sbss", ".sdata2", ".sbss2", ".ctors", ".dtors",
              "extab", "extabindex", ".init")

_cache = {}
_THUNK = re.compile(r"@\d+@")   # this-adjust thunks (@208@name) are real functions; plain @N are compiler locals


def dolmodel():
    if "S" not in _cache:
        _cache["S"] = M.model()
        _cache["dol"] = M.Dol()
        _cache["by_addr"] = sorted((s.addr, s.name) for s in _cache["S"].values())
    return _cache["S"], _cache["dol"], _cache["by_addr"]


def compile_src(src, cc="GC/3.0a5.2", flags=CF.DEFAULT_FLAGS, out=None):
    out = out or tempfile.mktemp(suffix=".o", dir=os.path.join(ROOT, "build/tmp/buildtree"))
    ccp = os.path.join(ROOT, "build/compilers", cc, "mwcceppc.exe")
    r = subprocess.run([CF.WIBO, ccp, *(shlex.split(flags) if isinstance(flags, str) else flags), "-c", src, "-o", out],
                       cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0 or not os.path.exists(out):
        o = r.stdout + r.stderr
        raise RuntimeError("compile failed: " + (o if len(o) <= 2600 else o[:2000] + "\n[...]\n" + o[-600:]))
    return out


class Placement:
    def __init__(self):
        self.ranges = {}     # section -> (start, end)
        self.errors = []
        self.notes = []
        self.functions = []  # (name, addr, size)
        self.ref_targets = []   # debugging: (section, target name, addend, DOL address, code address)
        self.base_votes = {}  # data section -> {candidate base: [code addresses that imply it]}
        self.size_fixes = {}  # symbols.txt name -> corrected size (sizes that covered padding)
        self.weak_else = set()  # weak data symbols whose references imply another base than the rest (copy lives elsewhere)
        self.ext_resolved = {}  # referenced name unknown to symbols.txt -> unnamed (fn_/lbl_) DOL symbol at the target address
        self.adopt = {}  # unnamed DOL data label -> name of the object's global definition at that address
        self.static_outside = {}  # symbols.txt name the object defines static -> outside referencers

    @property
    def ok(self):
        return not self.errors

    def split_lines(self):
        order = [".init", "extab", "extabindex", ".text", ".ctors", ".dtors", ".rodata", ".data", ".bss",
                 ".sdata", ".sbss", ".sdata2", ".sbss2"]
        out = []
        for sec in order:
            if sec in self.ranges:
                a, b = self.ranges[sec]
                out.append(f"\t{sec:<11} start:0x{a:08X} end:0x{b:08X}")
        return out


def decode_target(rtype, word_bytes, addr_of_field, pending_ha, key):
    """Address the original instruction/data refers to, as in check_func."""
    if rtype == 10:
        w, = struct.unpack(">I", word_bytes)
        disp = w & 0x03FFFFFC
        if disp & 0x02000000:
            disp -= 0x04000000
        return addr_of_field + disp
    if rtype == 109:
        w, = struct.unpack(">I", word_bytes)
        ra, simm = (w >> 16) & 0x1F, w & 0xFFFF
        if simm & 0x8000:
            simm -= 0x10000
        base = {13: SDA_BASE, 2: SDA2_BASE, 0: 0}.get(ra)
        return None if base is None else base + simm
    return None


def pad_end(sec, end):
    """Extend a range end over zero padding up to the next symbol (at most to 32-byte alignment)."""
    S, dol, by_addr = dolmodel()
    i = bisect.bisect_left(by_addr, (end, ""))
    nxt = next((x for x, n in by_addr[i:i + 50] if S[n].sec == sec), None)
    # only alignment padding: the next symbol must sit at the next 4- or 8-byte boundary
    # (a wider relaxation to 16/32 bytes put padding into .text units that the object does not emit)
    if nxt is None or nxt == end or nxt not in ((end + 3) // 4 * 4, (end + 7) // 8 * 8):
        return end
    if sec not in (".bss", ".sbss", ".sbss2") and any(dol.read(end, nxt - end)):
        return end
    return nxt


def comment_flags(secs):
    """MWCC's .comment section: one 8-byte record per symbol after a 0x2C header; byte 5 of a
    record has bit 0x08 set for force_active symbols."""
    c = next((s["data"] for s in secs if s["name"] == ".comment"), b"")
    out = {}
    for i in range(max(0, (len(c) - 0x2C) // 8)):
        out[i] = c[0x2C + 8 * i + 5]
    return out


def eh_entries():
    """DOL .ctors/.dtors slots and extabindex entries: [(section, slot address, function address)]."""
    if "eh" not in _cache:
        S, dol, _ = dolmodel()
        out = []
        for sec in (".ctors", ".dtors"):
            a, b = M.SECTIONS[sec]
            for x in range(a, b, 4):
                w, = struct.unpack(">I", dol.read(x, 4))
                if w:
                    out.append((sec, x, w))
        a, b = M.SECTIONS["extabindex"]
        for x in range(a, b - 11, 12):
            w, = struct.unpack(">I", dol.read(x, 4))
            if M.SECTIONS[".text"][0] <= w < M.SECTIONS[".text"][1]:
                out.append(("extabindex", x, w))
        # slots that a hand-kept split (splits.base.txt, e.g. __init_cpp_exceptions.cpp) owns
        import re
        owned = []
        base = os.path.join(ROOT, "config/RFEE01/splits.base.txt")
        for line in open(base) if os.path.exists(base) else ():
            m = re.match(r"\s+(\.ctors|\.dtors|extabindex)\s+start:0x([0-9A-Fa-f]+) end:0x([0-9A-Fa-f]+)", line)
            if m:
                owned.append((int(m.group(2), 16), int(m.group(3), 16)))
        _cache["eh"] = [e for e in out if not any(a <= e[1] < b for a, b in owned)]
    return _cache["eh"]


# absolute symbols of the linker script (gen_config ldscript.lcf): _stack_end = end of .sbss2,
# _stack_addr = (_stack_end + 0x10000 + 7) & ~7, _db_stack_addr = _stack_addr + 0x2000,
# _db_stack_end = _stack_addr, __ArenaLo = (_db_stack_addr + 0x1f) & ~0x1f, __ArenaHi = 0x81700000
LD_ABS = {"_stack_end": 0x804D1858, "_stack_addr": 0x804E1858, "_db_stack_addr": 0x804E3858,
          "_db_stack_end": 0x804E1858, "__ArenaLo": 0x804E3860, "__ArenaHi": 0x81700000}


def elf_aligns(obj):
    """Section alignments (sh_addralign) of an ELF object."""
    d = open(obj, "rb").read()
    shoff, = struct.unpack(">I", d[0x20:0x24])
    shentsize, shnum = struct.unpack(">HH", d[0x2E:0x32])
    return [struct.unpack(">10I", d[shoff + i * shentsize:shoff + (i + 1) * shentsize])[8] for i in range(shnum)]


def elf_binds(obj):
    """Symbol bindings (0 local, 1 global, 2 weak) of an ELF object, in symbol table order."""
    d = open(obj, "rb").read()
    shoff, = struct.unpack(">I", d[0x20:0x24])
    shentsize, shnum = struct.unpack(">HH", d[0x2E:0x32])
    for i in range(shnum):
        h = struct.unpack(">10I", d[shoff + i * shentsize:shoff + (i + 1) * shentsize])
        if h[1] == 2:
            return [d[h[4] + k * 16 + 12] >> 4 for k in range(h[5] // 16)]
    return []


def parse_elf(obj):
    """check_func.parse_elf plus each symbol's binding ("bind": 0 local, 1 global, 2 weak)."""
    secs, syms, relocs = CF.parse_elf(obj)
    st = next(x for x in secs if x["type"] == 2)
    for i, sy in enumerate(syms):
        sy["bind"] = st["data"][i * 16 + 12] >> 4
    return secs, syms, relocs


LAST_FORCE = set()  # force_active functions of the last strip_object run that the DOL lacks
LAST_ELSE = set()   # weak functions of the last strip_object run whose DOL copy lies in another object


def strip_object(obj, in_dol, keep_data=(), natural=False, extra_else=()):
    """Model MWLD's dead-stripping of one object: keep every symbol for which in_dol(name)
    gives a DOL address and everything they reference, transitively; drop the rest and close
    the gaps (each kept symbol keeps the alignment its old offset had, up to the section
    alignment). Returns (parsed object, dropped symbol names) for place()."""
    secs, syms, relocs = parse_elf(obj)
    aligns = elf_aligns(obj)
    sid = {id(x): i for i, x in enumerate(syms)}
    alloc = {i for i, s in enumerate(secs) if s["name"] in ALLOC_SECS and s["size"]}
    # symbol ranges per section: every defined function/object; bytes not covered by a
    # symbol belong to the symbol before them
    per = {}
    for k, sy in enumerate(syms):
        if sy["shndx"] in alloc and sy["type"] in (1, 2) and sy["name"]:
            per.setdefault(sy["shndx"], []).append(k)
    owner = {}
    spans = {}
    for si, ks in per.items():
        ks.sort(key=lambda k: (syms[k]["value"], -syms[k]["size"]))
        uniq = []
        for k in ks:
            if uniq and syms[uniq[-1]]["value"] == syms[k]["value"]:
                owner[k] = uniq[-1]
                continue
            uniq.append(k)
        per[si] = uniq
        for j, k in enumerate(uniq):
            end = syms[uniq[j + 1]]["value"] if j + 1 < len(uniq) else secs[si]["size"]
            spans[k] = (si, syms[k]["value"], end)
            owner[k] = k
    # sections with bytes before their first symbol (or no symbol at all): kept whole
    whole = {si for si in alloc if si not in per or syms[per[si][0]]["value"] != 0}

    def sym_at(si, off):
        ks = per.get(si, [])
        lo, hi = 0, len(ks) - 1
        best = None
        while lo <= hi:
            mid = (lo + hi) // 2
            if syms[ks[mid]]["value"] <= off:
                best = ks[mid]
                lo = mid + 1
            else:
                hi = mid - 1
        return best
    refs = {k: set() for k in spans}
    for si, rl in relocs.items():
        if si not in alloc:
            continue
        for off, rtype, tname, addend, tsym in rl:
            src = sym_at(si, off)
            tk = sid.get(id(tsym))
            if tk is None:
                continue
            if syms[tk]["type"] not in (1, 2) and syms[tk]["shndx"] in alloc:   # section-relative
                tk = sym_at(syms[tk]["shndx"], syms[tk]["value"] + addend)
            tk = owner.get(tk, tk)
            if src is not None and tk is not None:
                refs[src].add(tk)
    # text: the object's functions that the DOL has in object order (longest increasing run of
    # DOL addresses) are its own; a mapped function whose DOL copy lies elsewhere is a weak
    # (inline/template) copy that MWLD took from another object. A function without a name in
    # the DOL is kept when the DOL has a function of its size right where it would go.
    S_, _dol, by_addr = dolmodel()
    roots, elsewhere = set(), set()
    matched = {}

    def same_code(si, a0, b0, c):
        mine = bytearray(secs[si]["data"][a0:b0])
        theirs = bytearray(_dol.read(c, b0 - a0))
        for off, rtype, _t, _a, _ts in relocs.get(si, []):
            if a0 <= off < b0:
                w = (off - a0) & ~3 if rtype not in (4, 5, 6) else off - a0 - 2
                mask = CF.RELOC_MASK.get(rtype, 0xFFFFFFFF)
                for buf in (mine, theirs):
                    if 0 <= w and w + 4 <= len(buf):
                        x, = struct.unpack(">I", buf[w:w + 4])
                        struct.pack_into(">I", buf, w, x & ~mask)
        return mine == theirs
    _bysize = {}

    def by_size():
        if not _bysize:
            for n_, o_ in S_.items():
                if o_.sec == ".text" and o_.type == "function" and not n_.startswith("@"):
                    _bysize.setdefault(o_.size, []).append(n_)
        return _bysize
    matched_else = {}

    def own_run(ks):
        mapped = [(k, in_dol(syms[k]["name"])) for k in ks if in_dol(syms[k]["name"]) is not None]
        # heaviest strictly increasing subsequence of addresses (a global definition weighs 2, a
        # weak copy 1: on a tie the weak copy is the one that lies in another object)
        n_ = len(mapped)
        best, prev = [0] * n_, [None] * n_
        for j in range(n_):
            w = 2 if syms[mapped[j][0]].get("bind", 2) != 2 else 1
            best[j] = w
            for i_ in range(j):
                if mapped[i_][1] < mapped[j][1] and best[i_] + w > best[j]:
                    best[j], prev[j] = best[i_] + w, i_
        own_j = set()
        j = max(range(n_), key=lambda x: best[x]) if n_ else None
        while j is not None:
            own_j.add(j)
            j = prev[j]
        # weak (bind 2) copies must not decide the sequence: a weak copy whose DOL twin lies in another
        # object can tie with a real function of this one (BasicSound/Voice: LinkListNode dtor)
        if any(syms[mapped[j][0]].get("bind", 1) == 2 for j in range(len(mapped))):
            nw = [j for j in range(len(mapped)) if syms[mapped[j][0]].get("bind", 1) != 2]
            tails2, prev2 = [], {}
            for jj, j in enumerate(nw):
                ad = mapped[j][1]
                lo_, hi_ = 0, len(tails2)
                while lo_ < hi_:
                    mid = (lo_ + hi_) // 2
                    if mapped[nw[tails2[mid]]][1] < ad:
                        lo_ = mid + 1
                    else:
                        hi_ = mid
                prev2[jj] = tails2[lo_ - 1] if lo_ else None
                if lo_ == len(tails2):
                    tails2.append(jj)
                else:
                    tails2[lo_] = jj
            own2 = []
            jj = tails2[-1] if tails2 else None
            while jj is not None:
                own2.append(nw[jj])
                jj = prev2[jj]
            own2.sort()
            # weak copies that sit between their own neighbours in address order stay in; at either end of
            # the object a weak copy must touch its neighbour (chains of weak copies are followed in order)
            own_j = set(own2)
            for j in range(len(mapped)):
                if j in own_j or syms[mapped[j][0]].get("bind", 1) != 2:
                    continue
                a_j, z_j = mapped[j][1], syms[mapped[j][0]]["size"]
                before = [(mapped[x][1], syms[mapped[x][0]]["size"]) for x in sorted(own_j) if x < j]
                after = [mapped[x][1] for x in own2 if x > j]
                if before and after:
                    fits = before[-1][0] + before[-1][1] <= a_j and a_j + z_j <= after[0]
                elif after:
                    fits = (a_j + z_j + 3) // 4 * 4 == after[0]
                elif before:
                    fits = (before[-1][0] + before[-1][1] + 3) // 4 * 4 == a_j
                else:
                    fits = True
                if fits:
                    own_j.add(j)
        own = {mapped[j][0]: mapped[j][1] for j in own_j}
        # a weak copy of the run that lies farther from its global neighbours than the object's own
        # distance to them (a copy living elsewhere that merely has a lower/higher address)
        gl = sorted((syms[k]["value"], ad) for k, ad in own.items() if syms[k].get("bind", 2) != 2)
        if gl:
            for k, ad in list(own.items()):
                if syms[k].get("bind", 2) != 2:
                    continue
                o_ = syms[k]["value"]
                pre = [g for g in gl if g[0] < o_]
                post = [g for g in gl if g[0] > o_]
                if (post and ad < post[0][1] - (post[0][0] - o_)) or (pre and ad > pre[-1][1] + (o_ - pre[-1][0])):
                    del own[k]
        return mapped, own

    # weak data (vtables, RTTI) whose single DOL copy lies in another object: same model as the
    # weak functions below; dropfn cuts them out of the compiled object
    for si in alloc:
        if secs[si]["name"] == ".text" or si not in per or secs[si]["type"] == 8:
            continue
        mapped_d, own_d = own_run(per[si])
        elsewhere |= {k for k, _a in mapped_d if k not in own_d and syms[k].get("bind", 2) == 2}
    for si in alloc:
        if secs[si]["name"] != ".text" or si not in per:
            continue
        ks = per[si]
        mapped, own = own_run(ks)
        own_addrs = set(own.values())
        own_names = {n for k_, a_ in mapped for n in [syms[k_]["name"]]}
        for a_ in own_addrs:
            i_ = bisect.bisect_left(by_addr, (a_, ""))
            own_names |= {nm for x, nm in by_addr[i_:i_ + 3] if x == a_}
        # a weak copy whose DOL twin lies in another object (before or after this one) is not part
        # of this object's range. MWLD keeps the first definition in link order (the build
        # confirmed it: snd_DisposeCallbackManager.cpp's copy of __dt__Q34nw4r2ut12LinkListNodeFv
        # won over the later DOL copy and shifted everything by 0x40), so gen_units.lib_unit has
        # tools/build/dropfn.py cut such copies out of the compiled object (units.json
        # "drop_functions"); the calls then bind to the DOL's copy.
        # Only a weak copy can be left to another object: a global definition of a name the DOL
        # has elsewhere is a duplicate at link time (scsystem.c's __SCGetConfBuf)
        elsewhere |= {k for k, a_ in mapped if k not in own and syms[k].get("bind", 2) == 2}
        # an unnamed (unmapped) weak function of at least 8 bytes whose code equals exactly one DOL
        # function of that size outside this object's run: its copy lives in another object
        mapped_ks = {k for k, _a in mapped}
        for k in ks:
            if k in mapped_ks or syms[k].get("bind", 2) != 2:
                continue
            _s, a0, b0 = spans[k]
            if b0 - a0 < 8:
                continue
            hits = [n for n in by_size().get(b0 - a0, ()) if same_code(si, a0, b0, S_[n].addr)]
            if len(hits) == 1:
                elsewhere.add(k)
                matched_else[syms[k]["name"]] = hits[0]
        # a global definition of a name the DOL has elsewhere stays (MWLD does not strip a
        # duplicate definition away): the object then does not place
        roots |= {k for k, _a in mapped if k not in own and k not in elsewhere}
        cursor = None
        nxt_own = {}
        nxt = None
        for k in reversed(ks):     # DOL address of the next own function (gap filling only)
            nxt_own[k] = nxt
            if k in own:
                nxt = own[k]
        for k in ks:
            _s, a0, b0 = spans[k]
            if k in own:
                roots.add(k)
                cursor = own[k] + (b0 - a0)
            elif k in elsewhere:
                continue
            elif cursor is not None and nxt_own[k] is not None and \
                    (cursor + 3) // 4 * 4 + (b0 - a0) <= nxt_own[k]:
                c = (cursor + 3) // 4 * 4
                i = bisect.bisect_left(by_addr, (c, ""))
                hit = next((n for x, n in by_addr[i:i + 4] if x == c and S_[n].sec == ".text"
                            and S_[n].type == "function" and S_[n].size == b0 - a0), None)
                if hit and hit not in own_names and same_code(si, a0, b0, c):
                    roots.add(k)
                    matched[syms[k]["name"]] = hit
                    cursor = c + (b0 - a0)
                elif not hit:
                    # inside a larger DOL function (its symbol is too long): same bytes at that place
                    j_ = bisect.bisect_right(by_addr, (c, "\xff")) - 1
                    cov = next((n_ for x_, n_ in reversed(by_addr[max(0, j_ - 3):j_ + 1]) if S_[n_].sec == ".text"
                                and S_[n_].type == "function" and x_ < c < x_ + S_[n_].size), None)
                    if cov is not None and c + (b0 - a0) <= S_[cov].addr + S_[cov].size and same_code(si, a0, b0, c):
                        roots.add(k)
                        cursor = c + (b0 - a0)
    elsewhere |= {k for k in spans if syms[k]["name"] in extra_else}
    global LAST_ELSE
    LAST_ELSE = {syms[k]["name"] for k in elsewhere}
    if __import__('os').environ.get('DBGOWN'):
        print('ELSE', sorted(n[:50] for n in LAST_ELSE))
    if __import__('os').environ.get('DBGOWN'):
        print('ELSE', sorted(n[:40] for n in LAST_ELSE))
    fa = comment_flags(secs)     # force_active symbols are never stripped
    # (a force_active function the DOL does not have was dead-stripped by the original link: it is
    # cut out of the object like a weak copy living elsewhere; LAST_FORCE lists them)
    roots |= {k for k in spans if fa.get(k, 0) & 0x08 and k not in elsewhere
              and (syms[k]["type"] != 2 or in_dol(syms[k]["name"]) is not None)}
    global LAST_FORCE
    LAST_FORCE = {syms[k]["name"] for k in spans if fa.get(k, 0) & 0x08 and k not in elsewhere
                  and syms[k]["type"] == 2 and in_dol(syms[k]["name"]) is None}
    # data objects of these sections are kept although nothing references them (MWLD keeps
    # unreferenced data of some library objects: dvd.c's TmdBuffer, vi.c's format strings)
    kept_data = {k for k in spans if syms[k]["type"] == 1 and secs[spans[k][0]]["name"] in keep_data
                 and syms[k].get("bind", 1) != 2}
    roots |= kept_data
    keep = set()
    todo = [k for k in spans if k in roots or (in_dol(syms[k]["name"]) is not None and k not in elsewhere
                                                and secs[spans[k][0]]["name"] != ".text") or spans[k][0] in whole]

    def weak_elsewhere(k):
        return k in elsewhere
    while todo:
        k = todo.pop()
        if k in keep:
            continue
        keep.add(k)
        todo += [t for t in refs.get(k, ()) if t in spans and t not in keep and not weak_elsewhere(t)]
    dropped = [syms[k]["name"] for k in spans if k not in keep]
    import os as _o
    if _o.environ.get('PLDBG'):
        for k in spans:
            if 'PaneBase' in syms[k]['name']: print('DBG',syms[k]['name'],k in keep,k in elsewhere,'fa',fa.get(k,0),'dol',in_dol(syms[k]['name']),k in roots,[syms[r]['name'] for r,v in refs.items() if k in v and r in keep],file=sys.stderr)
    if not dropped:
        return (secs, syms, relocs, aligns, {syms[k]["name"] for k in kept_data}, matched), []
    # new offsets
    remap = {}     # si -> list of (old_start, old_end, new_start)
    secs2 = [dict(s) for s in secs]
    for si, ks in per.items():
        if si in whole:
            continue
        pos = 0
        m = []
        data = secs[si]["data"]
        out = bytearray()
        for k in ks:
            if k not in keep:
                continue
            _s, a, b = spans[k]
            if natural and secs[si]["name"] != ".text" and 0 < syms[k]["size"] < b - a:
                b = a + syms[k]["size"]     # drop the alignment padding behind the object
            al = min(aligns[si] or 1, a & -a if a else (aligns[si] or 1))
            if natural and al > 4 and 4 <= (syms[k]["size"] or (b - a)) and (syms[k]["size"] or (b - a)) % 8:
                al = 4      # 4-byte pool entries/strings only need 4; the old offset happened to be 8-aligned
            npos = (pos + al - 1) // al * al
            if secs[si]["type"] != 8:
                out += b"\0" * (npos - pos) + data[a:b]
            m.append((a, b, npos))
            pos = npos + (b - a)
        remap[si] = m
        secs2[si]["size"] = pos
        if secs[si]["type"] != 8:
            secs2[si]["data"] = bytes(out)

    starts = {si: [a for a, _b, _n in m] for si, m in remap.items()}

    def new_off(si, off, strict=False):
        if si not in remap:
            return off
        m = remap[si]
        i = bisect.bisect_right(starts[si], off) - 1
        for j in (i, i - 1):
            if 0 <= j < len(m):
                a, b, n = m[j]
                if a <= off < b or (off == b and a < b and not strict):
                    return n + off - a
        return None
    syms2 = []
    for k, sy in enumerate(syms):
        sy2 = dict(sy)
        if sy["shndx"] in remap:
            k0 = owner.get(k, k)
            if k0 in spans and k0 not in keep:
                sy2["shndx"] = 0
                sy2["value"] = 0
            else:
                nv = new_off(sy["shndx"], sy["value"])
                if nv is None:
                    sy2["shndx"] = 0
                else:
                    sy2["value"] = nv
        syms2.append(sy2)
    relocs2 = {}
    for si, rl in relocs.items():
        lst = []
        for off, rtype, tname, addend, tsym in rl:
            tk = sid.get(id(tsym))
            if si in remap:
                no = new_off(si, off, True)   # a relocation of a dropped span is dropped with it
                if no is None:
                    continue
            else:
                no = off
            if si not in alloc and si in remap:
                continue
            ts2 = syms2[tk]
            ad2 = addend
            if syms[tk]["type"] not in (1, 2) and syms[tk]["shndx"] in remap:
                # section-relative (section symbol, ...data.0 labels): remap the target offset
                ad2 = new_off(syms[tk]["shndx"], syms[tk]["value"] + addend)
                if ad2 is None:
                    continue
                ts2 = dict(syms[tk], value=0)
            lst.append((no, rtype, tname, ad2, ts2))
        relocs2[si] = lst
    roots = {syms[k]["name"] for k in keep if in_dol(syms[k]["name"]) is not None}
    return (secs2, syms2, relocs2, aligns, ({syms[k]["name"] for k in keep} - roots) | {syms[k]["name"] for k in kept_data},
            matched), dropped


def strip_tu_ns(n):
    """A mangled name with the generated TU's file namespace removed: a class a per-function
    file defines lives in `namespace tu_fN` of the merged TU, so its vtable is
    `__vt__Q25tu_f011HbInfoPanel` where the file's symbol map names `__vt__11HbInfoPanel`."""
    for m in re.finditer(r"Q(\d)(\d+?)(?=tu_f\d)", n):
        ln = int(m.group(2))
        ns = n[m.end():m.end() + ln]
        if re.fullmatch(r"tu_f\d+", ns):
            k = int(m.group(1))
            return n[:m.start()] + ("" if k == 2 else f"Q{k - 1}") + n[m.end() + ln:]
    return n


def lookup_name(names, n):
    if n in names:
        return names[n]
    s = strip_tu_ns(n)
    return names.get(s, n) if s != n else n


def object_renames(obj, smaps):
    """smaps {label: local name} with each local name the object does not have replaced by its
    namespaced form (see strip_tu_ns), the name the linker will see."""
    secs, syms, relocs = parse_elf(obj)
    have = {sy["name"] for sy in syms if sy["name"]}
    out = dict(smaps)
    for o, l in smaps.items():
        if l in have:
            continue
        c = [x for x in have if x != l and strip_tu_ns(x) == l]
        if len(c) == 1:
            out[o] = c[0]
    return out


def settle_renames(obj, smaps):
    """For the symbol-map labels of a game unit: (renames, defined) where renames are the
    labels whose local name the object defines or references (symbols.txt must carry that name)
    and defined the labels the object itself defines (only those are #undef'd in the TU;
    the others reach the label through lib_aliases.h like any other unit)."""
    smaps = object_renames(obj, smaps)
    secs, syms, relocs = parse_elf(obj)
    defined = {sy["name"] for sy in syms if sy["name"] and sy["shndx"] != 0}
    used = {sy["name"] for sy in syms if sy["name"]}
    return ({o: n for o, n in smaps.items() if n in used},
            {o for o, n in smaps.items() if n in defined})


def place_game(obj, names):
    """place() for a game TU; when the object has functions main.dol does not know (header
    scaffolding compiled without force_active), place it as MWLD will link it: dead-stripped.
    Returns (Placement, dropped symbol names)."""
    P = place(obj, names)
    if P.ok or not any(e.startswith("function ") and "not in symbols.txt" in e or "no references from code" in e
                       for e in P.errors):
        return P, []
    S = dolmodel()[0]

    def in_dol(n):
        t = lookup_name(names, n)
        return S[t].addr if t in S and (not t.startswith("@") or _THUNK.match(t)) else None
    parsed, dropped = strip_object(obj, in_dol)
    if not dropped:
        return P, []
    P2 = place(parsed, names)
    if P2.ok:
        return P2, dropped
    # the errors of the object as MWLD links it: the dropped helpers' own "not in symbols.txt"
    # and the contiguity breaks they cause would only blame innocent neighbours; a helper of a
    # per-function file that is still referenced stays in the stripped object and is reported
    return P2, []


def place(obj, names=None, strip_check=True):
    """names: optional {object symbol name: symbols.txt name} for renamed (library) symbols.
    strip_check: report functions and objects that MWLD would dead-strip (nothing in the DOL
    references them and the object does not mark them force_active)."""
    S, dol, by_addr = dolmodel()
    names = names or {}
    P = Placement()
    exempt = set()
    if isinstance(obj, tuple):     # an already parsed (e.g. dead-stripped) object, see strip_object
        secs, syms, relocs, aligns = obj[:4]
        exempt = obj[4] if len(obj) > 4 else set()
    else:
        secs, syms, relocs = parse_elf(obj)
        aligns = elf_aligns(obj)

    def orig_name(n):
        return lookup_name(names, n)

    # ---- text
    text_idx = [i for i, s in enumerate(secs) if s["name"] == ".text" and s["size"]]
    if len(text_idx) != 1:
        P.errors.append(f"expected one .text section, found {len(text_idx)}")
        return P
    ti = text_idx[0]

    def swallowed(o, size):
        """The DOL's symbols split a trailing `blr` (or another tiny unnamed piece) off the end of
        the function: o plus the unnamed fn_ symbols right after it tile exactly `size` bytes."""
        if size <= o.size or o.sec != ".text":
            return False
        a = o.addr + o.size
        end = o.addr + size
        while a < end:
            i_ = bisect.bisect_left(by_addr, (a, ""))
            n_ = next((n for x_, n in by_addr[i_:i_ + 3] if x_ == a and S[n].sec == ".text" and S[n].type == "function"
                       and re.match(r"fn_[0-9A-Fa-f]+$", n) and S[n].size <= 8), None)
            if n_ is None:
                # a raw `blr` after a function that ends in a branch (unreachable): the DOL symbol
                # excludes it, no symbol covers it. The symbol grows to the object's size.
                nxt = by_addr[bisect.bisect_left(by_addr, (a, ""))][0] if by_addr else 0
                if nxt >= end and all(dol.read(x, 4) == b"\x4e\x80\x00\x20" for x in range(a, end, 4)) and (end - a) % 4 == 0:
                    P.size_fixes[o.name] = size
                    return True
                return False
            a += S[n_].size
        return a == end
    fsyms = sorted((s for s in syms if s["shndx"] == ti and s["type"] == 2), key=lambda s: s["value"])
    base = None
    embed_end = 0     # end of a DOL function that is larger than ours (it also holds our next function)
    for s in fsyms:
        n = orig_name(s["name"])
        o = S.get(n)
        if base is not None and (o is None or o.sec != ".text") and base + s["value"] + s["size"] <= embed_end:
            P.functions.append((n, base + s["value"], s["size"]))
            continue
        if o is None or o.sec != ".text":
            P.errors.append(f"function {s['name']} not in symbols.txt")
            continue
        if o.size > s["size"] and base is not None or (o.size > s["size"] and base is None and len(fsyms) > 1):
            embed_end = o.addr + o.size
        elif o.size != s["size"] and not swallowed(o, s["size"]):
            P.errors.append(f"function {s['name']} size 0x{s['size']:X}, DOL has 0x{o.size:X}")
        b = o.addr - s["value"]
        if base is None:
            base = b
        elif b != base:
            P.errors.append(f"function {s['name']} at 0x{o.addr:08X} breaks contiguity (expected 0x{base + s['value']:08X})")
        P.functions.append((n, o.addr, o.size))
    if base is None:
        return P
    tsize = secs[ti]["size"]
    P.ranges[".text"] = (base, base + tsize)
    secbase = {ti: base}

    # ---- data sections: find the base from references in code (and data); repeated so that
    # sections referenced only from data (extab from extabindex) are found too
    cand = {}
    # .ctors/.dtors/extabindex are referenced by nobody: their base is the DOL slot that holds
    # the address of the function they point to
    for si, s in enumerate(secs):
        if s["name"] not in (".ctors", ".dtors", "extabindex") or not s["size"]:
            continue
        for off, rtype, tname, addend, tsym in relocs.get(si, []):
            if rtype != 1 or tsym["shndx"] != ti:
                continue
            fa = base + tsym["value"] + addend
            slots = {x - off for sec, x, w in eh_entries() if sec == s["name"] and w == fa}
            cand[si] = slots if si not in cand else cand[si] & slots
    dvotes = {}

    def resolve():
        # a section whose references imply several bases: the base most supported by non-weak
        # symbols wins when every reference that disagrees points at a weak symbol (vtable/RTTI
        # copies the original link took from another object)
        for tsh, vl in dvotes.items():
            if len(cand.get(tsh, ())) < 2 or tsh in secbase:
                continue
            score = {}
            for b, ts in vl:
                sc = score.setdefault(b, [0, 0])
                sc[1] += 1
                if ts.get("bind", 2) != 2:
                    sc[0] += 1
            best = max(score, key=lambda b: tuple(score[b]))
            others = [(b, ts) for b, ts in vl if b != best]
            if any(ts.get("bind", 2) != 2 for _b, ts in others):
                continue
            P.weak_else |= {ts["name"] for _b, ts in others}
            cand[tsh] = {best}

    def scan(si):
        sb = secbase[si]
        pending = {}
        for off, rtype, tname, addend, tsym in relocs.get(si, []):
            fa = sb + off
            if rtype == 6:   # HA
                hi, = struct.unpack(">H", dol.read(fa, 2))
                pending[(tname, addend)] = hi
                continue
            want = None
            if rtype == 4:
                lo, = struct.unpack(">h", dol.read(fa, 2))
                hi = pending.get((tname, addend))
                if hi is not None:
                    want = ((hi << 16) + lo) & 0xFFFFFFFF
            elif rtype in (10, 109):
                want = decode_target(rtype, dol.read(fa & ~3, 4), fa & ~3, None, None)
            elif rtype == 1:
                want, = struct.unpack(">I", dol.read(fa, 4))
            if want is None:
                continue
            tsh = tsym["shndx"]
            if 0 < tsh < len(secs) and tsh != ti and secs[tsh]["name"] in ALLOC_SECS:
                b = want - tsym["value"] - addend
                if tsh in secbase and b != secbase[tsh] and tsym.get("bind", 2) == 2:
                    P.weak_else.add(tsym["name"])
                    continue
                if M.section_of(b) == secs[tsh]["name"] or M.section_of(want) == secs[tsh]["name"]:
                    cand.setdefault(tsh, set()).add(b)
                    dvotes.setdefault(tsh, []).append((b, tsym))
                    P.ref_targets.append((secs[tsh]["name"], tname, addend, want, sb + off))
                    if si == ti:
                        P.base_votes.setdefault(secs[tsh]["name"], {}).setdefault(b, []).append(sb + off)
                        import os as _o
                        if _o.environ.get('PLDBG2') and secs[tsh]['name']=='.rodata': print('VOTE',hex(sb+off),tsym['name'],hex(tsym['value']),addend,hex(want),hex(b),file=sys.stderr)

    scan(ti)
    resolve()
    # sections nothing in the C code references (data of functions emitted as asm opwords, or
    # unreferenced statics): the base from data symbols named as in symbols.txt
    for si, s in enumerate(secs):
        if si == ti or s["name"] not in ALLOC_SECS or not s["size"] or cand.get(si):
            continue
        c = set()
        for sy in syms:
            o = S.get(orig_name(sy["name"])) if sy["shndx"] == si and sy["name"] else None
            if o is not None and o.sec == s["name"]:
                c.add(o.addr - sy["value"])
        if c:
            cand[si] = c
    while True:
        nxt = next((si for si, s in enumerate(secs) if si not in secbase and s["name"] in ALLOC_SECS
                    and s["size"] and len(cand.get(si, ())) == 1 and s["name"] != ".text"), None)
        if nxt is None:
            break
        secbase[nxt] = next(iter(cand[nxt]))
        scan(nxt)
        resolve()
    noref = set()     # sections whose references from code all point outside them in the DOL
    for si, s in enumerate(secs):
        if si == ti or s["name"] not in ALLOC_SECS or s["size"] == 0:
            continue
        c = set(cand.get(si, set()))
        if not c:
            noref.add(si)
        if len(c) != 1:
            P.errors.append(f"{s['name']}: cannot derive a single base ({', '.join(hex(x) for x in sorted(c)) or 'no references from code'})")
            continue
        b = c.pop()
        P.ranges[s["name"]] = (b, b + s["size"])
        secbase[si] = b
        if M.section_of(b) != s["name"] and not (s["name"] == ".sbss2" and M.section_of(b) == ".sbss2"):
            P.errors.append(f"{s['name']}: base 0x{b:08X} lies in {M.section_of(b)}")

    # ---- alignment
    for si in secbase:
        al = aligns[si] or 1
        if secs[si]["name"] == ".sbss" and al == 8 and secbase[si] % 4 == 0:
            continue    # MWCC always writes sh_addralign 8 for .sbss, yet the DOL packs the sbss of one object at 4
        if secbase[si] % al:
            P.errors.append(f"{secs[si]['name']}: base 0x{secbase[si]:08X} not aligned to {al}")

    # ---- bytes and relocation targets, for every placed section
    owned = list(P.ranges.values())

    def inside(a):
        return any(x <= a < y for x, y in owned)

    for si, sb in secbase.items():
        s = secs[si]
        if s["type"] == 8:   # NOBITS
            continue
        mine = bytearray(s["data"])
        try:
            theirs = bytearray(dol.read(sb, len(mine)))
        except KeyError:
            P.errors.append(f"{s['name']}: range 0x{sb:08X}+0x{len(mine):X} is outside the DOL")
            continue
        pending = {}
        for off, rtype, tname, addend, tsym in relocs.get(si, []):
            fa = sb + off
            mask = CF.RELOC_MASK.get(rtype, 0xFFFFFFFF)
            word_off = off & ~3
            if rtype in (4, 5, 6):
                word_off = off - 2
            want = None
            if rtype == 6:
                hi, = struct.unpack(">H", dol.read(fa, 2))
                pending[(tname, addend)] = hi
            elif rtype == 4:
                lo, = struct.unpack(">h", dol.read(fa, 2))
                hi = pending.get((tname, addend))
                if hi is not None:
                    want = ((hi << 16) + lo) & 0xFFFFFFFF
            elif rtype in (10, 109):
                want = decode_target(rtype, dol.read(sb + word_off, 4), sb + word_off, None, None)
            elif rtype == 1:
                want, = struct.unpack(">I", dol.read(fa, 4))
            if want is not None:
                tsh = tsym["shndx"]
                if 0 < tsh < len(secs) and tsh in secbase:
                    got = secbase[tsh] + tsym["value"] + addend
                elif 0 < tsh < len(secs):
                    got = None
                    if si == ti and tsh in noref:
                        # the DOL instruction refers to something else entirely: this code differs
                        P.errors.append(f".text+0x{off:X}: reference to {tname} in unplaced section {secs[tsh]['name']} "
                                        f"(DOL has 0x{want:08X})")
                    else:
                        P.errors.append(f"reference to {tname} in unplaced section {secs[tsh]['name']}")
                else:
                    o = S.get(orig_name(tname))
                    got = o.addr + addend if o else None
                    if o is None and tname in LD_ABS:
                        got = LD_ABS[tname] + addend    # linker-script symbol (ldscript.lcf), absolute value
                    elif o is None:
                        i_ = bisect.bisect_left(by_addr, (want - addend, ""))
                        un = next((n_ for x_, n_ in by_addr[i_:i_ + 4] if x_ == want - addend
                                   and re.match(r"(fn|lbl|jumptable)_[0-9A-Fa-f]+$", n_)), None)
                        if un is not None and tname and not tname.startswith("@") and tname not in S:
                            P.ext_resolved[tname] = un
                            got = None
                        else:
                            P.errors.append(f"reference to {tname}: not in symbols.txt")
                if got is not None and got != want:
                    P.errors.append(f"{s['name']}+0x{off:X}: {tname}+0x{addend:X} -> 0x{got:08X}, DOL has 0x{want:08X}")
            for buf in (mine, theirs):
                if word_off + 4 <= len(buf):
                    w, = struct.unpack(">I", buf[word_off:word_off + 4])
                    struct.pack_into(">I", buf, word_off, w & ~mask)
        if mine != theirs:
            bad = [i for i in range(0, len(mine), 4) if mine[i:i + 4] != theirs[i:i + 4]]
            P.errors.append(f"{s['name']}: {len(bad)} words differ from the DOL (first at 0x{sb + bad[0]:08X})")

    # ---- symbols.txt symbols inside the owned ranges
    defined = {orig_name(s["name"]) for s in syms if s["shndx"] and s["shndx"] < 0xFF00 and s["name"]}
    # a local (static) definition does not satisfy references from other objects
    global_defs = {orig_name(s["name"]) for s in syms if s["shndx"] and s["shndx"] < 0xFF00 and s["name"]
                   and s.get("bind", 1) != 0}
    # a global/weak data object the DOL only has as an unnamed label at its placed address is adopted
    # under the object's name (the unit renames the label)
    for s_ in syms:
        sh_ = s_["shndx"]
        if not (s_["name"] and 0 < sh_ < len(secs) and sh_ in secbase and sh_ != ti and s_["type"] == 1
                and s_.get("bind", 1) != 0) or orig_name(s_["name"]) in S:
            continue
        i_ = bisect.bisect_left(by_addr, (secbase[sh_] + s_["value"], ""))
        un_ = next((n_ for x_, n_ in by_addr[i_:i_ + 4] if x_ == secbase[sh_] + s_["value"]
                    and re.match(r"lbl_[0-9A-Fa-f]+$", n_) and S[n_].sec == secs[sh_]["name"]), None)
        if un_ is not None:
            P.adopt[un_] = s_["name"]
            defined.add(un_)
            global_defs.add(un_)
    for sec, (a, b) in P.ranges.items():
        i = bisect.bisect_left(by_addr, (a, ""))
        while i < len(by_addr) and by_addr[i][0] < b:
            n = by_addr[i][1]
            i += 1
            o = S[n]
            if o.sec != sec or o.attrs.get("type") == "label":
                continue
            outside = [r for r in o.refby if not inside(S[r].addr)]
            if n in defined:
                if outside and n not in global_defs and not n.startswith("@"):
                    # the object keeps it static: a reference from code that stays asm would be
                    # undefined at link time (gen_units.py checks that against the final selection)
                    P.static_outside[n] = sorted(outside)
                continue
            if outside:
                P.errors.append(f"{n} (0x{o.addr:08X}) is referenced from outside the unit ({', '.join(sorted(outside)[:3])}) but the object does not define it")
    # .ctors/.dtors and exception-table entries of the unit's functions: dtk assigns them to the
    # unit that owns the function, so the object must emit them (a __sinit written as a plain
    # function, or C++ compiled without exceptions, would make the link drop them)
    if ".text" in P.ranges:
        ta, tb = P.ranges[".text"]
        for sec, slot, fa in eh_entries():
            if ta <= fa < tb and not (sec in P.ranges and P.ranges[sec][0] <= slot < P.ranges[sec][1]):
                fn = next((n for n, a_, z in P.functions if a_ == fa), hex(fa))
                P.errors.append(f"{sec} entry 0x{slot:08X} for {fn} is not emitted by the object"
                                + (" (static initialiser)" if sec == ".ctors" else " (exception table)"))
    # MWLD dead-strips what nothing references; dtk's asm keeps it, so the object must mark
    # such functions/objects force_active (game TUs: #pragma force_active on)
    if strip_check:
        flags = comment_flags(secs)
        for k, sy in enumerate(syms):
            if sy["type"] not in (1, 2) or not (0 < sy["shndx"] < len(secs)) or secs[sy["shndx"]]["name"] not in ALLOC_SECS:
                continue
            if flags.get(k, 0) & 0x08 or sy["name"] in exempt:
                continue
            if sy["name"].startswith("__sinit_"):
                continue   # kept alive by the object's own .ctors entry (checked above)
            o = S.get(orig_name(sy["name"]))
            if o is not None and not (o.refby - {o.name}) and o.name not in ("__start",) \
                    and not (o.sec == ".text" and any(sc == ".ctors" and fa_ == o.addr for sc, _sl, fa_ in eh_entries())):
                P.errors.append(f"{sy['name']} is referenced nowhere in the DOL and not force_active "
                                "(MWLD would dead-strip it)")
    # trailing alignment padding: the next object starts aligned, dtk wants the gap in this unit
    for sec, (a, b) in list(P.ranges.items()):
        P.ranges[sec] = (a, pad_end(sec, b))
    # dtk refuses a split (ours or the auto split after it) that does not start 4-aligned
    for sec, (a, b) in P.ranges.items():
        if a % 4 or b % 4:
            P.errors.append(f"{sec} range 0x{a:08X}-0x{b:08X} is not 4-aligned (dtk cannot split there)")
    # dtk refuses a split that starts or ends inside a symbols.txt symbol (e.g. a literal whose
    # recorded size includes the alignment padding after it)
    # recorded size includes the alignment padding after it). Padding-aware: a range ending inside
    # a symbol of its own whose tail is zero padding takes the padding; a range starting inside
    # the previous object's last symbol (its size covers our first bytes) shrinks that symbol in
    # symbols.txt (Placement.size_fixes, applied by gen_config.py).
    for sec, (a, b) in list(P.ranges.items()):
        for edge in (a, b):
            i = bisect.bisect_left(by_addr, (edge, "")) - 1
            while i >= 0 and by_addr[i][0] >= edge - 0x10000:
                o = S[by_addr[i][1]]
                if o.sec == sec and o.addr < edge < o.addr + o.size and o.attrs.get("type") != "label":
                    tail = o.addr + o.size
                    if edge == b and o.addr >= a and o.type != "function" and (
                            sec in (".bss", ".sbss", ".sbss2") or not any(dol.read(b, tail - b))):
                        if tail in ((b + 3) // 4 * 4, (b + 7) // 8 * 8):
                            # same rule as pad_end: the next object starts at the next boundary
                            P.ranges[sec] = (a, tail)
                        else:
                            # the linker would not recreate a larger gap: the symbol ends with the object
                            P.size_fixes[o.name] = b - o.addr
                        break
                    if edge == a and o.addr < a and o.type != "function" and a < b:
                        P.size_fixes[o.name] = a - o.addr
                        break
                    P.errors.append(f"{sec} split edge 0x{edge:08X} lies inside symbol {o.name} "
                                    f"(0x{o.addr:08X}+0x{o.size:X}); fix its size in symbols.txt")
                    break
                if o.addr < edge - 0x100:
                    break
                i -= 1
    # a symbol the object only references (extern lbl_...) but whose address now lies inside one
    # of the object's own ranges would be undefined at link time (dtk no longer emits it)
    for si, rl in relocs.items():
        if si not in secbase:
            continue
        for off, rtype, tname, addend, tsym in rl:
            if tsym["shndx"] != 0 or not tname:
                continue
            o = S.get(orig_name(tname))
            if o is None or o.name in defined:
                continue
            if any(x <= o.addr < y for x, y in P.ranges.values()):
                P.errors.append(f"{secs[si]['name']}+0x{off:X}: {tname} lies inside the unit's own ranges "
                                "but the object does not define it")
    return P


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("source")
    ap.add_argument("--cc", default="GC/3.0a5.2")
    ap.add_argument("--flags", default=CF.DEFAULT_FLAGS)
    ap.add_argument("--names", help="JSON {object name: symbols.txt name}")
    a = ap.parse_args()
    obj = compile_src(a.source, a.cc, a.flags)
    try:
        P = place(obj, json.load(open(a.names)) if a.names else None)
    finally:
        os.unlink(obj)
    for line in P.split_lines():
        print(line)
    for e in P.errors:
        print("ERROR", e)
    print("PLACEABLE" if P.ok else "NOT PLACEABLE")
    return 0 if P.ok else 1


if __name__ == "__main__":
    sys.exit(main())
