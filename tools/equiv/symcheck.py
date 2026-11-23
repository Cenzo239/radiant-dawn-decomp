#!/usr/bin/env python3
"""symcheck.py FILE fn REGION [-v] [-x] [--anon] [--strbase=lbl_X] [--args=fn_Y=nInt,nFloat]
Per-basic-block symbolic comparison of our compile against the original, for `sched`/`regs` drafts.
For every block (cut at labels, branches, calls) both sides are executed symbolically; compared are:
  - the set of non-stack stores (address expression, value expression),
  - the final contents of every r1 stack byte written in the block,
  - the final value of every register that is defined in the block and live out of it,
  - the condition the terminating branch tests.
Register copies are transparent. Values that enter a block are ("in", reg) (strict) or ("in", class) (--anon,
for drafts whose saved registers are renamed). Non-stack loads carry the set of non-stack stores that precede
them in the block (except stores through the same unchanged base register at a non-overlapping constant offset, which can't be
the same memory), so a load moved across a store that may alias is reported. Not a proof across blocks.
-x prints, for each flagged block, the stores / stack bytes / call arguments / live-out values only one side has.
Object-local data names ("@stringBase0", "...data.0", local statics) are renamed to the original's lbl_X when used
consistently and, where known, the bytes are equal (see auto_locals; each renaming is printed as a "note:" line);
the MWCC runtime helpers in HELPERS are aliased to their fn_ names.
At a direct call only the argument registers the original callee can read before writing (callee_args, worked out
from the original's code, through its own callees) are compared, so a temporary left in an unused argument register
is not reported; --assoc compares nested integer `add`s as one sum (use it to confirm that association is the only
difference in a block, the default keeps reporting it); --allargs compares every argument register set in the block as before. --args still overrides.
--eqsym ignores the operand order of a register-register compare that is only tested by the block's own beq/bne
(flags dead afterwards); like --assoc it is off by default so that the difference stays visible.
--xargs adds a cross-block check: an argument register that a later direct call's callee reads (worked out as with
--virt-this) and that the calling block doesn't set itself must be set to the same value, by register name, in the
block that prepares it. Catches a missing argument whose register happens to hold another value (fn_8027247C).
--virt-this assumes that indirect calls made inside a callee read r3 only when callee_args is worked out (an
assumption, so off by default; the call sites of the function under test are still compared in full).
--ret=none|r3|f1 says which return register is live at blr (default both; r4 of a 64-bit result is never counted).
A FILE.symbols.json next to the source (the name map check_regs.py uses) is applied to our side's names and printed as "note:" lines."""
import sys, os, re, subprocess, glob, shlex, tempfile, shutil, struct
OURC = {}
DOLR = None
from collections import Counter
ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
os.chdir(ROOT)
sys.path.insert(0, ROOT + "/tools")
import check_func as c

STRBASE = None
AUTOARGS = "--allargs" not in sys.argv
SIGS = {}
for _a in sys.argv:
    if _a.startswith('--args='):
        _n, _v = _a[7:].split('='); SIGS[_n] = tuple(int(x) for x in _v.split(','))
for _a in sys.argv:
    if _a.startswith('--strbase='): STRBASE = _a.split('=')[1]
# MWCC runtime helpers our object names but symbols.txt doesn't (sizes and bodies checked against the original).
HELPERS = {"__ptmf_scall": "fn_8028C178", "__div2i": "fn_8028C418", "__mod2i": "fn_8028C634", "__cvt_sll_flt": "fn_8028C764",
           "__cvt_dbl_usll": "fn_8028C818"}
def norm_sym(n):
    if LOCALS:
        m = re.match(r'"?((?:@\d+|\.\.\.[A-Za-z0-9_.]+|[A-Za-z_][\w$]*))"?(.*)$', n)
        if m and m.group(1) in LOCALS: n = LOCALS[m.group(1)] + m.group(2)
    n = re.sub(r'"?@\d+"?', '@K', n)
    n = re.sub(r'"?@stringBase0"?', '@S', n)
    n = re.sub(r'(lbl_804C[C-F][0-9A-F]+|lbl_804D[0-9A-F]+)(\+0x[0-9A-Fa-f]+)?(?=@sda21)', '@K', n)
    n = re.sub(r'jumptable_[0-9A-F]+', '@K', n)
    n = re.sub(r'@K\+0x[0-9A-Fa-f]+', '@K', n)
    n = re.sub(r'\b(k[0-9]\w*)(\+0x[0-9A-Fa-f]+)?(?=@sda21)', '@K', n)
    if STRBASE: n = n.replace(STRBASE, '@S')
    return n

def parse(txt):
    out = []
    for l in txt.splitlines():
        l = l.rstrip()
        m = re.match(r"\s*(\.L_[0-9A-Fa-f]+):", l)
        if m:
            out.append(("label", m.group(1))); continue
        m = re.match(r"\s*/\*.*?\*/\s*(.*)", l)
        n = (m.group(1) if m else l).strip()
        if not n or n.startswith('.'): continue
        n = re.sub(r"\s+", " ", n)
        parts = n.split(" ", 1)
        mn = parts[0]
        ops = [o.strip() for o in parts[1].split(",")] if len(parts) > 1 else []
        out.append(("ins", mn, ops))
    return out

ASM = None
def orig(fn):
    global ASM
    if ASM is None: ASM = [open(f).read() for f in sorted(glob.glob(ROOT + "/build/RFEE01/asm/auto_*.s"))]
    for t in ASM:
        if ".fn %s," % fn not in t: continue
        m = re.search(r"\.fn %s, .*?\n(.*?)\.endfn %s\b" % (re.escape(fn), re.escape(fn)), t, re.S)
        if m: return parse(m.group(1))

def ours(src, fn, R):
    tmp = tempfile.mkdtemp(dir=ROOT + "/build/tmp")
    obj = tmp + "/o.o"
    r = subprocess.run([c.WIBO, ROOT + "/build/compilers/GC/3.0a5.2/mwcceppc.exe", *shlex.split(c.DEFAULT_FLAGS),
                        "-i", f"src/game/{R}", "-i", f"src/game/{R}/wip", "-c", src, "-o", obj],
                       cwd=ROOT, capture_output=True, text=True, stdin=subprocess.DEVNULL)
    if not os.path.exists(obj):
        print(r.stdout[-1500:]); shutil.rmtree(tmp); sys.exit(1)
    subprocess.run([ROOT + "/build/tools/dtk", "elf", "disasm", obj, tmp + "/o.s"], capture_output=True, text=True,
                   stdin=subprocess.DEVNULL)
    s = open(tmp + "/o.s").read()
    shutil.rmtree(tmp)
    for mo in re.finditer(r'\.obj ("?)([^",\s]+)\1, \w+\n(.*?)\.endobj', s, re.S):
        bs = b""
        ok = True
        for l in mo.group(3).splitlines():
            l = l.strip()
            mm = re.match(r"\.(4byte|2byte|byte|float|double) (.*)", l)
            if not mm:
                if l and not l.startswith("#") and not l.startswith(".balign"): ok = False
                continue
            try:
                k = mm.group(1)
                for v in mm.group(2).split("#")[0].split(","):   # ".byte 0x4C, 0x45, 0x00" lists
                    v = v.strip()
                    ms = re.match(r"(?:lbl|fn)_([0-9A-F]{8})(?:\+0x([0-9A-Fa-f]+))?$", v) if k == "4byte" else None
                    if ms: bs += struct.pack(">I", (int(ms.group(1), 16) + int(ms.group(2) or "0", 16)) & 0xFFFFFFFF)  # pointer to a named original address
                    elif k == "4byte": bs += struct.pack(">I", int(v, 0) & 0xFFFFFFFF)
                    elif k == "2byte": bs += struct.pack(">H", int(v, 0) & 0xFFFF)
                    elif k == "byte": bs += struct.pack(">B", int(v, 0) & 0xFF)
                    elif k == "float": bs += struct.pack(">f", float(v))
                    elif k == "double": bs += struct.pack(">d", float(v))
            except Exception:
                ok = False
        if ok: OURC[mo.group(2)] = bs
    m = re.search(r"\.fn %s, .*?\n(.*?)\.endfn %s\b" % (fn, fn), s, re.S)
    return parse(m.group(1))

REG = re.compile(r"^(r|f)([0-9]|[12][0-9]|3[01])$")
CRR = re.compile(r"^cr([0-7])$")
MEM = re.compile(r"^(.*)\((r[0-9]+)\)$")
# psq_st/psq_l are a store and a load of the first operand (they used to fall into the generic path, where the
# stored register counted as defined); the W/qr operands are not modelled, both sides must agree on them textually
STORES = {"stb": 1, "sth": 2, "stw": 4, "stfs": 4, "stfd": 8, "psq_st": 8}
LOADS = {"lbz": 1, "lhz": 2, "lha": 2, "lwz": 4, "lfs": 4, "lfd": 8, "psq_l": 8}
CMPS = {"cmpw", "cmpwi", "cmplw", "cmplwi", "fcmpu", "fcmpo"}
CA_DEF = {"addic", "subfic", "addc", "subfc", "srawi", "sraw", "subic"}
CA_USE = {"adde", "addze", "subfe", "subfze", "addme"}
VOL = ["r0"] + ["r%d" % i for i in range(3, 13)] + ["f%d" % i for i in range(0, 14)] + ["cr%d" % i for i in range(8)] + ["ctr", "lr", "ca"]
ARGS = ["r%d" % i for i in range(3, 11)] + ["f%d" % i for i in range(1, 14)] + ["r1", "r2", "r13"]
SAVED = ["r%d" % i for i in range(14, 32)] + ["f%d" % i for i in range(14, 32)] + ["r1", "r2", "r13", "r3", "f1", "lr"]

# what the function returns, when known from the source: --ret=none (void), --ret=r3 or --ret=f1. Default: both r3 and
# f1 count as live at blr, so a dead temporary left in the other one (or in either, for a void function) is reported.
for _a in sys.argv:
    if _a.startswith("--ret="):
        _keep = _a[6:]
        if _keep not in ("none", "r3", "f1"): sys.exit("--ret=none|r3|f1")
        SAVED = [r_ for r_ in SAVED if r_ not in ("r3", "f1") or r_ == _keep]

def is_branch(mn):
    return mn in ("b", "bl", "blr", "bctr", "bctrl", "blrl", "bdnz") or (mn.startswith("b") and mn.rstrip("+-")[1:] in
        ("eq", "ne", "lt", "gt", "le", "ge", "eqlr", "nelr", "ltlr", "gtlr", "lelr", "gelr", "so", "ns"))

def decode(mn, ops):
    """returns dict: defs(list), uses(list), kind, plus fields"""
    rec = mn.endswith(".")
    base = mn[:-1] if rec else mn
    d = {"mn": mn, "base": base, "defs": [], "uses": [], "kind": "gen", "imm": []}
    if is_branch(mn):
        d["kind"] = "br"
        b = mn.rstrip("+-")
        cond = b not in ("b", "bl", "blr", "bctr", "bctrl", "blrl")
        tgt = None
        o = list(ops)
        if o and o[-1].startswith(".L"): tgt = o.pop()
        elif o and not CRR.match(o[-1]) and b in ("b", "bl"): tgt = o.pop()
        d["target"] = HELPERS.get(tgt, tgt)
        if b == "bdnz": d["uses"].append("ctr"); d["defs"].append("ctr")
        elif cond:
            d["uses"].append(o[0] if o and CRR.match(o[0]) else "cr0")
        if b in ("bl", "bctrl", "blrl"):
            d["uses"] += ARGS
            if b == "bctrl": d["uses"].append("ctr")
            d["defs"] += VOL
            d["call"] = True
            # the epilogue helpers reload the saved registers N..31 (without this a dead temporary left in a saved
            # register counted as live at the blr)
            mr_ = re.match(r"_rest([gf])pr_(\d+)$", d["target"] or "")
            if mr_: d["defs"] += [("r" if mr_.group(1) == "g" else "f") + str(i_) for i_ in range(int(mr_.group(2)), 32)]
        if b.endswith("lr") and b != "blrl":
            d["uses"] += SAVED
            d["ret"] = True
        if b == "bctr": d["uses"].append("ctr"); d["jt"] = True
        d["cond"] = cond
        return d
    if base == "nop": return d
    if base in ("mflr",): d["defs"] = [ops[0]]; d["uses"] = ["lr"]; return d
    if base in ("mtlr",): d["defs"] = ["lr"]; d["uses"] = [ops[0]]; return d
    if base in ("mtctr",): d["defs"] = ["ctr"]; d["uses"] = [ops[0]]; return d
    if base in ("mfctr",): d["defs"] = [ops[0]]; d["uses"] = ["ctr"]; return d
    if base in ("crset", "crclr", "cror"):
        d["defs"] = [re.match(r"cr\d", ops[0]).group(0)] if re.match(r"cr\d", ops[0]) else ["cr0"]
        d["imm"] = list(ops); return d
    if base in CMPS:
        o = list(ops); cr = "cr0"
        if CRR.match(o[0]): cr = o.pop(0)
        d["defs"] = [cr]
        for x in o:
            (d["uses"] if REG.match(x) else d["imm"]).append(x)
        d["kind"] = "cmp"; d["srcs"] = o
        return d
    # stores
    sb = base
    upd = False; idx = False
    for nm in sorted(STORES, key=len, reverse=True):
        if base.startswith(nm) and base[len(nm):] in ("", "x", "u", "ux"):
            sfx = base[len(nm):]
            d["kind"] = "store"; d["size"] = STORES[nm]; d["snm"] = nm + ("" if len(ops) <= 2 or "x" in sfx else ":" + ",".join(ops[2:]))
            if "x" in sfx:
                d["uses"] = [ops[0], ops[1], ops[2]]; d["addr"] = ("x", ops[1], ops[2])
                if "u" in sfx: d["defs"] = [ops[1]]
            else:
                m = MEM.match(ops[1])
                d["uses"] = [ops[0]] + ([m.group(2)] if m.group(2) != "r0" else []); d["addr"] = ("d", m.group(2), norm_sym(m.group(1)))
                if "u" in sfx and m.group(2) != "r1": d["defs"] = [m.group(2)]
                if "u" in sfx and m.group(2) == "r1": d["kind"] = "frame"
            d["val"] = ops[0]
            return d
    for nm in sorted(LOADS, key=len, reverse=True):
        if base.startswith(nm) and base[len(nm):] in ("", "x", "u", "ux"):
            sfx = base[len(nm):]
            d["kind"] = "load"; d["size"] = LOADS[nm]; d["lnm"] = nm + ("" if len(ops) <= 2 or "x" in sfx else ":" + ",".join(ops[2:]))
            d["defs"] = [ops[0]]
            if "x" in sfx:
                d["uses"] = [ops[1], ops[2]]; d["addr"] = ("x", ops[1], ops[2])
                if "u" in sfx: d["defs"].append(ops[1])
            else:
                m = MEM.match(ops[1])
                d["uses"] = [m.group(2)] if m.group(2) != "r0" else []; d["addr"] = ("d", m.group(2), norm_sym(m.group(1)))
                if "u" in sfx: d["defs"].append(m.group(2)); d["upd"] = True
                d["rawoff"] = m.group(1)
            return d
    if base in ("stmw", "lmw"):
        d["kind"] = "multi"; d["imm"] = list(ops); return d
    if base in ("mr", "fmr"):
        d["kind"] = "copy"; d["defs"] = [ops[0]]; d["uses"] = [ops[1]]
        if rec: d["defs"].append("cr0")
        return d
    # generic: first operand dest
    if not ops: return d
    d["defs"] = [ops[0]]
    srcs = ops[1:]
    if base in ("xor", "subf", "subfc") and len(srcs) == 2 and srcs[0] == srcs[1] and REG.match(srcs[0]):
        srcs = []            # the zero idiom: the result doesn't depend on the register
    if base in ("rlwimi",): srcs = [ops[0]] + srcs
    d["srcs"] = srcs
    for x in srcs:
        mm = MEM.match(x)
        if REG.match(x): d["uses"].append(x)
        elif mm: d["uses"].append(mm.group(2)); d["imm"].append(norm_sym(mm.group(1)))
        else: d["imm"].append(norm_sym(x))
    if base in CA_DEF: d["defs"].append("ca")
    if base in CA_USE: d["uses"].append("ca")
    if rec: d["defs"].append("cr0")
    return d

def blocks(items):
    """split into blocks; returns list of dict(label=set, ins=[decoded])"""
    bl = []; cur = {"labels": [], "ins": []}
    for it in items:
        if it[0] == "label":
            if cur["ins"]:
                bl.append(cur); cur = {"labels": [], "ins": []}
            cur["labels"].append(it[1])
        else:
            dd = decode(it[1], it[2]); dd["text"] = it[1] + " " + ", ".join(it[2])
            cur["ins"].append(dd)
            if dd["kind"] == "br":
                bl.append(cur); cur = {"labels": [], "ins": []}
    if cur["ins"] or cur["labels"]: bl.append(cur)
    return bl

def liveness(bl):
    lab = {}
    for i, b in enumerate(bl):
        for l in b["labels"]: lab[l] = i
    succ = []
    for i, b in enumerate(bl):
        s = []
        t = b["ins"][-1] if b["ins"] else None
        if t is None or t["kind"] != "br":
            if i + 1 < len(bl): s.append(i + 1)
        else:
            if t.get("jt"): s = list(range(len(bl)))
            elif t.get("ret") and not t["cond"]: s = []
            else:
                if t.get("target") in lab and not t.get("call"): s.append(lab[t["target"]])
                if (t["cond"] or t.get("call") or t["mn"].rstrip("+-") == "bdnz") and i + 1 < len(bl): s.append(i + 1)
        succ.append(s)
    use = []; dfs = []
    for b in bl:
        u = set(); dset = set()
        for ins in b["ins"]:
            for x in ins["uses"]:
                if ins.get("call") and x in ARGS and x not in dset: continue  # args set in other blocks: unknown
                if x not in dset: u.add(x)
            for x in ins["defs"]: dset.add(x)
        use.append(u); dfs.append(dset)
    lin = [set() for _ in bl]; lout = [set() for _ in bl]
    ch = True
    while ch:
        ch = False
        for i in range(len(bl) - 1, -1, -1):
            o = set()
            for s in succ[i]: o |= lin[s]
            n = use[i] | (o - dfs[i])
            if o != lout[i] or n != lin[i]:
                lout[i] = o; lin[i] = n; ch = True
    return lout, dfs

# Mnemonics whose first operand is only written. Anything else in the generic path counts every register operand
# as read when a callee's argument registers are worked out (over-approximation: more registers get compared).
PUREDEF = set("""li lis addi addis add addc adde addze addme addic subf subfc subfe subfic subfze subi subis subic neg
mullw mulli mulhw mulhwu divw divwu and andi andis andc or ori oris orc xor xori xoris nor nand eqv not slw srw sraw
srawi slwi srwi rlwinm rlwnm clrlwi clrrwi clrlslwi extsb extsh cntlzw rotlwi rotrwi extrwi extlwi fadd fadds fsub fsubs fmul
fmuls fdiv fdivs fmadd fmadds fmsub fmsubs fnmadd fnmadds fnmsub fnmsubs fneg fabs fnabs frsp fctiwz fctiw fsel
frsqrte fres mfcr mftb mfmsr mfspr la psq_l psq_lx ps_add ps_sub ps_mul ps_div ps_madd ps_msub ps_nmadd ps_nmsub ps_muls0 ps_muls1
ps_madds0 ps_madds1 ps_sum0 ps_sum1 ps_merge00 ps_merge01 ps_merge10 ps_merge11 ps_neg ps_abs ps_nabs ps_mr ps_res
ps_rsqrte ps_sel""".split())
ARGREGS = ["r%d" % i for i in range(3, 11)] + ["f%d" % i for i in range(1, 14)]
# opt-in assumption for "stale register" checks: a virtual call inside a callee reads `this` (r3) only. Without it any
# callee that makes an indirect call counts as reading every argument register it hasn't written yet.
VIRTTHIS = "--virt-this" in sys.argv
CALLEE = {}
def callee_args(fn, depth=0):
    """Argument registers the original function fn can read before writing them (on any path, through the functions it
    calls). Returns None when unknown (not in the asm, indirect, too deep, recursive): then all are compared."""
    if fn in CALLEE: return CALLEE[fn]
    if fn is None or depth > 6: return None
    if re.match(r"_(save|rest)[gf]pr_\d+$", fn): return set()
    CALLEE[fn] = None            # recursion guard: unknown while in progress
    items = orig(fn)
    if items is None: return None
    try: bl = blocks(items)
    except Exception: return None
    lab = {}
    for i, b in enumerate(bl):
        for l in b["labels"]: lab[l] = i
    use = []; dfs = []; succ = []
    for i, b in enumerate(bl):
        u = set(); dset = set(); s_ = []; ended = False
        for ins in b["ins"]:
            uu = list(ins["uses"]); dd = list(ins["defs"])
            if ins["kind"] == "br":
                tg = ins.get("target"); base = ins["mn"].rstrip("+-")
                # --xargs only: an argument that merely survives to blr in r3/f1 is not counted as read (a callee
                # that never touches f1 would otherwise "read" it); the default comparison keeps counting it
                if XMODE and ins.get("ret"): uu = [x for x in uu if x not in ("r3", "f1")]
                if tg and re.match(r"_(save|rest)[gf]pr_\d+$", tg):
                    uu = []; dd = []          # prologue/epilogue helpers neither read nor clobber argument registers
                elif ins.get("call") or (base == "b" and tg not in lab):
                    # a direct call to itself reads nothing new (least fixed point); other cycles stay unknown
                    ca = set() if tg == fn else (callee_args(tg, depth + 1) if tg and not tg.startswith(".L") else
                                                 ({"r3"} if VIRTTHIS and base == "bctrl" else None))
                    uu = [x for x in uu if x not in ARGREGS] + (ARGREGS if ca is None else sorted(ca))
                # indirect tail call: assume everything is read. A switch (the block loads from a jumptable_) reads nothing.
                if ins.get("jt") and not any("jumptable_" in j["text"] for j in b["ins"]): uu = uu + ARGREGS
            elif ins["kind"] == "gen" and ins["base"] not in PUREDEF:
                uu = uu + [x for x in dd if x in ARGREGS]
            for x in uu:
                if x not in dset: u.add(x)
            for x in dd: dset.add(x)
        t = b["ins"][-1] if b["ins"] else None
        if t is None or t["kind"] != "br":
            if i + 1 < len(bl): s_.append(i + 1)
        else:
            base = t["mn"].rstrip("+-")
            if t.get("jt"): s_ = list(range(len(bl)))
            elif t.get("ret") and not t["cond"]: s_ = []
            else:
                if t.get("target") in lab and not t.get("call"): s_.append(lab[t["target"]])
                if (t["cond"] or t.get("call") or base == "bdnz") and i + 1 < len(bl): s_.append(i + 1)
        use.append(u); dfs.append(dset); succ.append(s_)
    lin = [set() for _ in bl]
    ch = True
    while ch:
        ch = False
        for i in range(len(bl) - 1, -1, -1):
            o = set()
            for s_ in succ[i]: o |= lin[s_]
            n = use[i] | (o - dfs[i])
            if n != lin[i]: lin[i] = n; ch = True
    res = set(x for x in (lin[0] if bl else ()) if x in ARGREGS)
    CALLEE[fn] = res
    return res

XARGS = "--xargs" in sys.argv
XMODE = False
XCACHE = {}
def xcallee(fn):
    """callee_args under the --virt-this assumption, in its own cache (used by --xargs only, to ADD comparisons)"""
    global VIRTTHIS, CALLEE
    global XMODE
    sv = (VIRTTHIS, CALLEE); VIRTTHIS = True; CALLEE = XCACHE; XMODE = True
    try: return callee_args(fn)
    finally: VIRTTHIS, CALLEE = sv; XMODE = False

def argflow(bl):
    """--xargs: for every block, the argument registers that are live out of it only because a later direct call's
    callee reads them without the calling block setting them (an argument prepared in an earlier block)."""
    lab = {}
    for i, b in enumerate(bl):
        for l in b["labels"]: lab[l] = i
    use = []; dfs = []; succ = []
    for i, b in enumerate(bl):
        u = set(); dset = set()
        for ins in b["ins"]:
            if ins.get("call") and ins["mn"] == "bl" and not re.match(r"_(save|rest)[gf]pr_\d+$", ins.get("target") or ""):
                ca = xcallee(ins.get("target"))
                for x in (ca or ()):
                    if x in ARGREGS and x not in dset: u.add(x)
            for x in ins["defs"]: dset.add(x)
        t = b["ins"][-1] if b["ins"] else None
        s = []
        if t is None or t["kind"] != "br":
            if i + 1 < len(bl): s.append(i + 1)
        elif t.get("jt"): s = list(range(len(bl)))
        elif t.get("ret") and not t["cond"]: s = []
        else:
            if t.get("target") in lab and not t.get("call"): s.append(lab[t["target"]])
            if (t["cond"] or t.get("call") or t["mn"].rstrip("+-") == "bdnz") and i + 1 < len(bl): s.append(i + 1)
        use.append(u); dfs.append(dset); succ.append(s)
    lin = [set() for _ in bl]; lout = [set() for _ in bl]
    ch = True
    while ch:
        ch = False
        for i in range(len(bl) - 1, -1, -1):
            o = set()
            for s in succ[i]: o |= lin[s]
            n = use[i] | (o - dfs[i])
            if o != lout[i] or n != lin[i]: lout[i] = o; lin[i] = n; ch = True
    return lout

def constval(ins):
    global DOLR
    ro = ins.get("rawoff")
    if not ro or not ro.endswith("@sda21") or ins["addr"][1] != "r0": return None
    mm = re.match(r'"?([^"+]+)"?(?:\+0x([0-9A-Fa-f]+))?@sda21$', ro)
    if not mm: return None
    name, off = mm.group(1), int(mm.group(2) or "0", 16)
    n = ins["size"]
    if name in OURC:
        b = OURC[name][off:off + n]
        return b.hex() if len(b) == n else None
    ml = re.match(r"lbl_([0-9A-F]{8})$", name)
    if ml:
        a = int(ml.group(1), 16) + off
        if 0x804CCA60 <= a < 0x804D1840:
            if DOLR is None: DOLR = c.dol_reader()
            return DOLR(a, n).hex()
    return None

COMM = {"add", "fadd", "fadds", "fmul", "fmuls", "mullw", "and", "or", "xor", "addc", "mulhw", "mulhwu", "fmadd", "fmadds", "fmsub", "fmsubs", "fnmadd", "fnmadds", "fnmsub", "fnmsubs", "lhax", "lwzx", "lbzx", "lhzx", "lfsx", "lfdx"}
INTERN = {}
REV = {}
ASSOC = "--assoc" in sys.argv   # opt-in: integer `add` trees compared as sums (exact mod 2^32); default stays strict
def I(t):
    v = INTERN.get(t)
    if v is None:
        v = len(INTERN) + 1; INTERN[t] = v; REV[v] = t
    return v

def run(b, anon):
    regs = {}
    def val(r):
        if r in regs: return regs[r]
        if anon and r not in ("r1", "r2", "r13") :
            return I(("in", r[0] if r[0] in "rf" else r))
        return I(("in", r))
    stack = {}      # byte offset -> expr
    stores = Counter(); nstores = []; per_addr = Counter()
    def numoff(a):
        if a[0] != "d": return None
        try: return int(a[2], 16)
        except ValueError: return None
    term = None
    ver = Counter()      # definitions of each register so far: (name, ver) identifies a base value even under --anon
    for ins in b["ins"]:
        k = ins["kind"]
        bkey = (ins["addr"][1], ver[ins["addr"][1]]) if k in ("store", "load") and ins["addr"][0] == "d" else None
        for d_ in ins["defs"]: ver[d_] += 1
        if k == "br":
            cv = tuple(val(u) for u in ins["uses"][:1]) if ins["cond"] else ()
            term = (ins["mn"].rstrip("+-"), cv)
            if ins.get("call"):
                AR = ARGS
                if ins.get("target") in SIGS:
                    ni, nf = SIGS[ins.get("target")]
                    AR = ["r%d" % i for i in range(3, 3 + ni)] + ["f%d" % i for i in range(1, 1 + nf)]
                elif AUTOARGS and ins["mn"] == "bl":
                    ca = callee_args(ins.get("target"))
                    if ca is not None: AR = [r_ for r_ in ARGS if r_ in ca or r_ in ("r1", "r2", "r13")]
                # argument registers are fixed by the ABI, so they are compared by register in --anon mode too
                # (a sorted multiset would accept two swapped arguments)
                av = tuple((r_, regs[r_]) for r_ in AR if r_ in regs)
                term = ("bl", ins.get("target"), av)
                for r_ in VOL: regs[r_] = I(("clob", r_))
                for r_ in ins["defs"]:
                    if r_ not in VOL: regs[r_] = I(("restored", r_))
            continue
        if k in ("frame", "multi"):
            continue
        if k == "copy":
            v = val(ins["uses"][0]); regs[ins["defs"][0]] = v
            if len(ins["defs"]) > 1: regs["cr0"] = I(("rec", v))
            continue
        if k == "cmp":
            regs[ins["defs"][0]] = I((ins["base"],) + tuple(val(x) if REG.match(x) else x for x in ins["srcs"]))
            continue
        if k in ("store", "load"):
            a = ins["addr"]
            if a[0] == "d":
                # base r0 in a D-form load/store is the literal 0 (the @sda21 placeholder), not the register's value
                basev = I(("zero",)) if a[1] == "r0" else val(a[1]); isstack = (a[1] == "r1")
                addr = I(("d", basev, a[2]))
            else:
                isstack = False; addr = I(("x",) + tuple(sorted((val(a[1]), val(a[2])))))
            if k == "store":
                v = val(ins["val"])
                if isstack:
                    off = int(a[2], 16)
                    for j in range(ins["size"]): stack[off + j] = I(("sb", ins["snm"], v, j))
                else:
                    rec = (ins["snm"], addr, v, per_addr[addr]); per_addr[addr] += 1
                    stores[rec] += 1; nstores.append((rec, bkey, numoff(a), ins["size"]))
                if ins["defs"]: regs[ins["defs"][0]] = addr
            else:
                if isstack:
                    off = int(a[2], 16)
                    e = I(("ld", ins["lnm"]) + tuple(stack.get(off + j, I(("inmem", off + j))) for j in range(ins["size"])))
                else:
                    # earlier stores the load may depend on; a store through the same base value at a constant
                    # offset range that doesn't overlap the load's can't be the same memory and is left out
                    lo = numoff(a)
                    dep = frozenset(rec for rec, b_, o_, sz_ in nstores
                                    if not (lo is not None and o_ is not None and bkey is not None and b_ == bkey
                                            and (o_ + sz_ <= lo or lo + ins["size"] <= o_)))
                    e = I(("ld", ins["lnm"], addr, I(dep)))
                cv = constval(ins)
                if cv is not None: e = I(("const", ins["lnm"], cv))
                dreg = ins["defs"][0]
                if len(ins["defs"]) > 1: regs[ins["defs"][1]] = addr
                regs[dreg] = e
            continue
        # generic
        srcs = []
        for x in ins.get("srcs", []):
            mm = MEM.match(x)
            if REG.match(x): srcs.append(val(x))
            elif mm: srcs.append(("m", norm_sym(mm.group(1)), val(mm.group(2))))
            else: srcs.append(norm_sym(x))
        if ins["base"] in COMM and len(srcs) >= 2 and all(isinstance(x, int) for x in srcs[:2]):
            srcs[:2] = sorted(srcs[:2])
        extra = (val("ca"),) if "ca" in ins["uses"] else ()
        if ASSOC and ins["base"] == "add" and len(srcs) == 2 and all(isinstance(x, int) for x in srcs):
            terms = []
            for x in srcs:
                t_ = REV.get(x)
                if isinstance(t_, tuple) and t_ and t_[0] == "add+": terms += list(t_[1:])
                else: terms.append(x)
            e = I(("add+",) + tuple(sorted(terms)))
        else:
            e = I((ins["base"],) + tuple(srcs) + extra + tuple(ins["imm"] if not ins.get("srcs") else ()))
        for dreg in ins["defs"]:
            if dreg == "ca": regs["ca"] = I(("ca", e))
            elif dreg == "cr0" and dreg != ins["defs"][0]: regs["cr0"] = I(("rec", e))
            else: regs[dreg] = e
    return regs, stack, stores, term

EQSYM = "--eqsym" in sys.argv   # opt-in: beq/bne on a compare whose flags die at the branch: operand order ignored
def eqsym(term):
    if term and term[0] in ("beq", "bne") and len(term[1]) == 1:
        t = REV.get(term[1][0])
        if isinstance(t, tuple) and len(t) == 3 and t[0] in ("cmpw", "cmplw", "fcmpu", "fcmpo") and all(isinstance(z, int) for z in t[1:]):
            return (term[0], (I((t[0],) + tuple(sorted(t[1:]))),))
    return term

LOCALS = {}
OPSYM = re.compile(r'^"?((?:@\d+|@stringBase0|\.\.\.[A-Za-z0-9_.]+|[A-Za-z_][\w$]*))"?((?:\+0x[0-9A-Fa-f]+)?(?:@ha|@l|@h|@sda21)?(?:\(r\d+\))?)$')
def auto_locals(ia, ib):
    """Object-local data names on our side ("@stringBase0", "@123" reached by lis/addi, "...data.0", local statics)
    are renamed to the original's lbl_X when instructions at the same position use them in the same operand shape,
    the mapping is one-to-one over the whole function, and (where our object's bytes are known and relocation-free)
    the original's bytes at lbl_X are equal. It is only a renaming of our side: a use that doesn't fit still differs.
    @sda21 literals are left to the by-value comparison in constval."""
    global STRBASE, DOLR
    xa = [i for i in ia if i[0] == "ins"]; xb = [i for i in ib if i[0] == "ins"]
    if len(xa) != len(xb): return
    cand = {}
    for p, q in zip(xa, xb):
        if p[1] != q[1] or len(p[2]) != len(q[2]): continue
        for o1, o2 in zip(p[2], q[2]):
            m1 = OPSYM.match(o1); m2 = OPSYM.match(o2)
            if not m1 or not m2 or REG.match(o1) or CRR.match(o1): continue
            n1, n2 = m1.group(1), m2.group(1)
            if n1 == n2 or re.match(r"(lbl|fn|jumptable)_[0-9A-F]{8}$", n1) or o1.startswith(".L"): continue
            if "@sda21" in m1.group(2) and n1 != "@stringBase0": continue
            if re.sub(r"\(r\d+\)", "", m1.group(2)) != re.sub(r"\(r\d+\)", "", m2.group(2)): continue
            if re.match(r"lbl_[0-9A-F]{8}$", n2): cand.setdefault(n1, set()).add(n2)
    used = Counter(l for v in cand.values() if len(v) == 1 for l in v)
    for n1, v in sorted(cand.items()):
        if len(v) != 1: continue
        lbl = next(iter(v))
        if used[lbl] != 1: continue
        if STRBASE and (n1 == "@stringBase0" or lbl == STRBASE): continue
        how = "contents not compared"
        if n1 in OURC:
            if DOLR is None: DOLR = c.dol_reader()
            try: same = DOLR(int(lbl[4:], 16), len(OURC[n1])) == OURC[n1]
            except KeyError: same = False
            if not same:
                print("note: %s has other bytes than the original's %s; not aliased" % (n1, lbl)); continue
            how = "%d bytes equal" % len(OURC[n1])
        if n1 == "@stringBase0": STRBASE = lbl
        else: LOCALS[n1] = lbl
        print("note: %s taken as %s (%s)" % (n1, lbl, how))

RINT = None
def show(e, depth=6):
    """expression id -> readable text (for -x)"""
    global RINT
    if RINT is None or len(RINT) != len(INTERN): RINT = {v: k for k, v in INTERN.items()}
    if not isinstance(e, int) or e not in RINT: return str(e)
    t = RINT[e]
    if isinstance(t, frozenset): return "{%d stores}" % len(t) if t else "{}"
    if depth == 0: return "#%d" % e
    if t[0] == "in": return "in:" + t[1]
    if t[0] == "inmem": return "stk[%s]" % hex(t[1])
    if t[0] == "const": return "const:%s:%s" % (t[1], t[2])
    return "(" + " ".join(str(x) if i == 0 or not isinstance(x, (int, tuple)) else
                          (show(x, depth - 1) if isinstance(x, int) else "(" + " ".join(show(y, depth - 1) if isinstance(y, int) else str(y) for y in x) + ")")
                          for i, x in enumerate(t)) + ")"

def main():
    src, fn, R = sys.argv[1:4]
    v = "-v" in sys.argv; anon = "--anon" in sys.argv; expl = "-x" in sys.argv
    ia = ours(src, fn, R); ib = orig(fn)
    # the same per-file name map check_regs.py passes to check_func.py (object-local name -> symbols.txt name)
    sm = os.path.splitext(src)[0] + ".symbols.json"
    if os.path.exists(sm):
        import json
        for k_, v_ in json.load(open(sm)).items():
            if isinstance(v_, str) and re.match(r"(lbl|fn)_[0-9A-F]{8}$", v_):
                LOCALS[k_] = v_; print("note: %s taken as %s (%s)" % (k_, v_, os.path.basename(sm)))
    auto_locals(ia, ib)
    A = blocks(ia); B = blocks(ib)
    if len(A) != len(B):
        print("block count differs", len(A), len(B)); sys.exit(2)
    la, da = liveness(A); lb, db = liveness(B)
    xla = argflow(A) if XARGS else None; xlb = argflow(B) if XARGS else None
    bad = 0; pos = 0
    for i, (x, y) in enumerate(zip(A, B)):
        n = len(x["ins"])
        if len(x["ins"]) != len(y["ins"]):
            print("block %d (ins %d): length differs %d %d" % (i, pos, len(x["ins"]), len(y["ins"]))); bad += 1; pos += n; continue
        ra, sa, ta, ea = run(x, anon); rb, sb, tb, eb = run(y, anon)
        if EQSYM and "cr0" not in la[i] and "cr0" not in lb[i]: ea = eqsym(ea); eb = eqsym(eb)
        msgs = []
        if ta != tb: msgs.append("non-stack stores differ")
        if sa != sb:
            ks = sorted(k for k in set(sa) | set(sb) if sa.get(k) != sb.get(k))
            msgs.append("stack bytes differ at " + ",".join(hex(k) for k in ks))
        if ea != eb: msgs.append("terminator differs %s %s" % (ea, eb))
        if XARGS:
            # an argument register this block sets for a call in a later block must hold the same value by name
            xa = dict((r, ra[r]) for r in xla[i] if r in ra); xb = dict((r, rb[r]) for r in xlb[i] if r in rb)
            for r in sorted(set(xa) | set(xb)):
                if xa.get(r) != xb.get(r):
                    msgs.append("argument %s for a later call differs (ours %s, orig %s)" % (r, show(xa.get(r), 3) if r in xa else "not set here", show(xb.get(r), 3) if r in xb else "not set here"))
        if anon:
            CL = set(I(("clob", r_)) for r_ in VOL)
            fa = Counter(ra[r] for r in ra if r in la[i] and ra[r] not in CL); fb = Counter(rb[r] for r in rb if r in lb[i] and rb[r] not in CL)
            if fa != fb: msgs.append("live-out value multiset differs (%d vs %d values)" % (sum(fa.values()), sum(fb.values())))
        else:
            for r in sorted(set(ra) | set(rb)):
                if (r in la[i] or r in lb[i]) and ra.get(r) != rb.get(r):
                    msgs.append("live-out %s differs" % r)
        if msgs:
            bad += 1
            print("block %d (ins %d..%d): %s" % (i, pos, pos + n - 1, "; ".join(msgs)))
            if expl:
                def side(tag, only):
                    for it in only: print("    %s only: %s" % (tag, it))
                ca = Counter(); cb = Counter()
                for (nm, ad, vl, k_), n_ in ta.items(): ca["store %s [%s] = %s (#%d at this address)" % (nm, show(ad), show(vl), k_)] += n_
                for (nm, ad, vl, k_), n_ in tb.items(): cb["store %s [%s] = %s (#%d at this address)" % (nm, show(ad), show(vl), k_)] += n_
                for k_ in set(sa) | set(sb):
                    if sa.get(k_) != sb.get(k_):
                        ca["stack %s = %s" % (hex(k_), show(sa.get(k_)))] += 1; cb["stack %s = %s" % (hex(k_), show(sb.get(k_)))] += 1
                if ea != eb:
                    if ea and eb and ea[0] == "bl" and eb[0] == "bl":
                        if ea[1] != eb[1]: ca["call target %s" % ea[1]] += 1; cb["call target %s" % eb[1]] += 1
                        for a_ in ea[2]: ca["arg %s = %s" % (a_[0], show(a_[1]))] += 1
                        for a_ in eb[2]: cb["arg %s = %s" % (a_[0], show(a_[1]))] += 1
                    else:
                        ca["branch %s %s" % (ea[0], " ".join(show(z) for z in ea[1]))] += 1 if ea else 0
                        cb["branch %s %s" % (eb[0], " ".join(show(z) for z in eb[1]))] += 1 if eb else 0
                if anon:
                    for z, n_ in fa.items(): ca["live-out " + show(z)] += n_
                    for z, n_ in fb.items(): cb["live-out " + show(z)] += n_
                side("ours", sorted((ca - cb).elements())); side("orig", sorted((cb - ca).elements()))
            if v:
                for p, q in zip(x["ins"], y["ins"]):
                    print("    %-38s %-38s %s" % (p["text"], q["text"], "" if p["text"] == q["text"] else "*"))
        pos += n
    print("%s: %d blocks, %d differ (%s)" % (fn, len(A), bad, "anon" if anon else "strict"))
    sys.exit(1 if bad else 0)

if __name__ == "__main__":
    main()
