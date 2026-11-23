#!/usr/bin/env python3
"""Local permuter for library sources (no tokens, plain hill climbing).

Usage: tools/lib/lperm.py <template> <key> <function> [--jobs N] [--iters N] [--name NAME]
                          [--decls] [--seed S] [--worse P] [--nice N] [--verbose] [--scan]

<template>  full copy of lib/<key> with markers (see below); it is compiled in place of the
            original with the compiler and flags of <key> (lib/manifest.json) plus `-i lib/<dir of key>`.
<key>       source key as in lib/map.json / lib/manifest.json (path below lib/).
<function>  mangled name or unique substring of a function of <key> in lib/map.json.

Markers:
  /*P*/ ... /*E*/            the units inside are reordered. A unit is a line; a line whose (), {}, []
                             are not balanced continues into the next lines (so a whole `if (...) {...}`
                             is one unit). Empty lines are dropped.
  /*A*/ v1 /*|*/ v2 /*Z*/    one alternative is chosen (any number of /*|*/, may span lines, may contain
                             /*P*/ blocks and further /*A*/ groups). Inside a /*P*/ block a group is part of
                             its unit.
  //LPERM-BEGIN ... //LPERM-END   with --decls, every run of 2+ consecutive declaration lines in this region
                             (outside of blocks) becomes an implicit /*P*/ block.

Score: words of the function that differ from main.dol at its map address (relocated fields masked
as in libcheck.py), plus 2 per word of size difference. Score 0 is confirmed with the real checker
(libcheck.py, all references); only then it prints FOUND and stops.
Output: build/lperm/<name>.best.cpp (best variant), <name>.score, <name>.log; compiles in build/tmp.
"""
import argparse, hashlib, json, os, random, re, shlex, shutil, struct, subprocess, sys, tempfile, time
from multiprocessing import Pool

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
sys.path[:0] = [HERE, os.path.join(HERE, "..")]
import check_func as cf

TMPROOT = os.path.join(ROOT, "build/tmp")
OUTDIR = os.path.join(ROOT, "build/lperm")
BAD = 9999

# ---------------------------------------------------------------- template parsing
TOK = re.compile(r"/\*P\*/|/\*E\*/|/\*A\*/|/\*\|\*/|/\*Z\*/")


class Perm:
    def __init__(self, units):
        self.units = units  # list of node lists
        self.id = None


class Alt:
    def __init__(self, alts):
        self.alts = alts  # list of node lists
        self.id = None


def parse(text):
    toks = []
    pos = 0
    for m in TOK.finditer(text):
        toks.append(text[pos:m.start()])
        toks.append(m.group(0))
        pos = m.end()
    toks.append(text[pos:])
    toks = [t for t in toks if t != ""]
    i = [0]

    def seq(stop):
        out = []
        while i[0] < len(toks):
            t = toks[i[0]]
            if t in stop:
                return out, t
            i[0] += 1
            if t == "/*P*/":
                body, end = seq({"/*E*/"})
                if end != "/*E*/":
                    raise SystemExit("unterminated /*P*/")
                i[0] += 1
                out.append(Perm(split_units(body)))
            elif t == "/*A*/":
                alts = []
                while True:
                    body, end = seq({"/*|*/", "/*Z*/"})
                    if end is None:
                        raise SystemExit("unterminated /*A*/")
                    i[0] += 1
                    alts.append(body)
                    if end == "/*Z*/":
                        break
                out.append(Alt(alts))
            elif t in ("/*E*/", "/*|*/", "/*Z*/"):
                raise SystemExit("stray marker %s" % t)
            else:
                out.append(t)
        return out, None

    nodes, end = seq(set())
    return nodes


def depth_of(s):
    s = re.sub(r"//[^\n]*|/\*.*?\*/|\"(\\.|[^\"\\])*\"|'(\\.|[^'\\])*'", "", s, flags=re.S)
    return sum(s.count(c) for c in "({[") - sum(s.count(c) for c in ")}]")


def split_units(nodes):
    units, cur, dep = [], [], 0
    for n in nodes:
        if isinstance(n, str):
            parts = n.split("\n")
            for k, p in enumerate(parts):
                if p:
                    cur.append(p)
                    dep += depth_of(p)
                if k < len(parts) - 1 and dep <= 0:
                    units.append(cur)
                    cur, dep = [], 0
                elif k < len(parts) - 1:
                    cur.append("\n")
        else:
            cur.append(n)
    units.append(cur)
    return [u for u in units if any(not isinstance(x, str) or x.strip() for x in u)]


DECL = re.compile(r"^\s*(const\s+|static\s+|register\s+|volatile\s+)*[A-Za-z_][\w:<>,\s]*?[\s\*&]+[A-Za-z_]\w*(\[[^\]]*\])?(\s*=[^;]*|\([^;]*\))?;\s*(//.*)?$")
KW = re.compile(r"^\s*(return|if|else|for|while|do|switch|case|goto|break|continue|delete)\b")


def add_decl_blocks(text):
    b = text.find("//LPERM-BEGIN")
    e = text.find("//LPERM-END")
    if b < 0 or e < b:
        raise SystemExit("--decls needs //LPERM-BEGIN ... //LPERM-END in the template")
    region = text[b:e].split("\n")
    out, run, depth_blk = [], [], 0

    def flush():
        if len(run) >= 2:
            out.append("/*P*/" + run[0])
            out.extend(run[1:-1])
            out.append(run[-1] + "\n/*E*/")
        else:
            out.extend(run)
        run.clear()

    for line in region:
        inblk = depth_blk > 0
        depth_blk += line.count("/*P*/") + line.count("/*A*/") - line.count("/*E*/") - line.count("/*Z*/")
        if not inblk and depth_blk == 0 and DECL.match(line) and not KW.match(line) and "/*" not in line:
            run.append(line)
        else:
            flush()
            out.append(line)
    flush()
    return text[:b] + "\n".join(out).replace("\n/*E*/\n", "\n/*E*/") + text[e:]


def collect(nodes, perms, alts):
    for n in nodes:
        if isinstance(n, Perm):
            n.id = len(perms)
            perms.append(n)
            for u in n.units:
                collect(u, perms, alts)
        elif isinstance(n, Alt):
            n.id = len(alts)
            alts.append(n)
            for a in n.alts:
                collect(a, perms, alts)


def render(nodes, st):
    order, choice = st
    out = []
    for n in nodes:
        if isinstance(n, str):
            out.append(n)
        elif isinstance(n, Perm):
            for k in order[n.id]:
                out.append(render(n.units[k], st).strip("\n") + "\n")
        else:
            out.append(render(n.alts[choice[n.id]], st))
    return "".join(out)


def used(nodes, st, perms, alts):
    """ids of the blocks that the current choices actually render"""
    for n in nodes:
        if isinstance(n, Perm):
            perms.add(n.id)
            for u in n.units:
                used(u, st, perms, alts)
        elif isinstance(n, Alt):
            alts.add(n.id)
            used(n.alts[st[1][n.id]], st, perms, alts)


# ---------------------------------------------------------------- compile and score
G = {}


def init_worker(cfg, nice):
    G.update(cfg)
    if nice:
        try:
            os.nice(nice)
        except OSError:
            pass


def load_cfg(key, fn):
    MAP = json.load(open(os.path.join(ROOT, "lib/map.json")))
    MAN = json.load(open(os.path.join(ROOT, "lib/manifest.json")))
    if key not in MAP["sources"] or key not in MAN:
        raise SystemExit("unknown key %s" % key)
    funcs = MAP["sources"][key]["functions"]
    if fn in funcs:
        name = fn
    else:
        c = [n for n in funcs if fn in n]
        if len(c) != 1:
            raise SystemExit("function %r: %d matches in map: %s" % (fn, len(c), c[:8]))
        name = c[0]
    addr, size = funcs[name][0], funcs[name][1]
    man = MAN[key]
    flags = [x for f in man["flags"] for x in shlex.split(f)]
    flags += ["-i", os.path.dirname("lib/" + key)]
    orig = bytes(cf.dol_reader()(addr, size))
    return {"key": key, "name": name, "addr": addr, "size": size, "cc": man["cc"],
            "flags": flags, "orig": orig}


def compile_obj(text, tmp):
    src = os.path.join(tmp, "t.cpp" if not G["key"].endswith(".c") else "t.c")
    with open(src, "w") as f:
        f.write(text)
    obj = os.path.join(tmp, "t.o")
    cc = os.path.join(ROOT, "build/compilers", G["cc"], "mwcceppc.exe")
    r = subprocess.run([cf.WIBO, cc, *G["flags"], "-c", src, "-o", obj], cwd=ROOT, capture_output=True,
                       text=True, stdin=subprocess.DEVNULL)
    if r.returncode != 0 or not os.path.exists(obj):
        return None, r.stdout + r.stderr
    return obj, None


def score_obj(obj):
    secs, syms, relocs = cf.parse_elf(obj)
    F = next((s for s in syms if s["name"] == G["name"] and s["type"] == 2 and 0 < s["shndx"] < 0xFF00), None)
    if F is None:
        return BAD
    ours = bytearray(secs[F["shndx"]]["data"][F["value"]:F["value"] + F["size"]])
    theirs = bytearray(G["orig"])
    for off, rtype, _t, _a, _s in relocs.get(F["shndx"], []):
        rel = off - F["value"]
        if 0 <= rel < len(ours):
            wo = rel - 2 if rtype in (4, 5, 6) else rel & ~3
            mask = cf.RELOC_MASK.get(rtype, 0xFFFFFFFF)
            for buf in (ours, theirs):
                if 0 <= wo and wo + 4 <= len(buf):
                    w, = struct.unpack(">I", buf[wo:wo + 4])
                    struct.pack_into(">I", buf, wo, w & ~mask)
    n = min(len(ours), len(theirs)) // 4
    d = sum(1 for i in range(n) if ours[i * 4:i * 4 + 4] != theirs[i * 4:i * 4 + 4])
    return d + 2 * abs(len(ours) - len(theirs)) // 4


def evaluate(text):
    tmp = tempfile.mkdtemp(prefix="lperm_", dir=TMPROOT)
    try:
        obj, err = compile_obj(text, tmp)
        if obj is None:
            return BAD, (err or "")[-400:]
        return score_obj(obj), None
    except Exception as e:  # broken object etc.
        return BAD, repr(e)
    finally:
        shutil.rmtree(tmp, ignore_errors=True)


def real_check(text, path):
    """Full libcheck.py run on the variant (as check_lib.py does); True if the function is OK."""
    import check_lib
    key = G["key"]
    ent = check_lib.MAP["sources"][key]
    man = check_lib.MAN[key]
    base_syms = cf.load_symbols()
    all_addrs = dict(cf.load_all_symbol_addresses())
    all_addrs.update(check_lib.MAP["symbols"])
    all_addrs.update(ent.get("syms", {}))
    for n, (a, s, st) in ent["functions"].items():
        all_addrs[n] = a
    alt = {}
    for n, ad in list(cf.load_all_symbol_addresses().items()) + list(check_lib.MAP["symbols"].items()) + \
            [(n, ad) for e in check_lib.MAP["sources"].values() for n, ad in e.get("syms", {}).items()]:
        if 0x80000000 <= ad < 0x81800000:
            alt.setdefault(n, set()).add(ad)
    alt = {n: sorted(v) for n, v in alt.items()}
    fstart = {a: s for n, (a, s) in base_syms.items()}
    with open(path, "w") as f:
        f.write(text)
    flags = list(man["flags"]) + ["-i " + os.path.dirname("lib/" + key)]
    with tempfile.NamedTemporaryFile("w", suffix=".json", delete=False, dir=TMPROOT) as tf:
        json.dump({"source": os.path.abspath(path), "cc": man["cc"], "flags": flags, "verbose": False,
                   "entry": ent, "all": all_addrs, "fstart": fstart, "alt": alt}, tf)
    r = subprocess.run([sys.executable, os.path.join(HERE, "libcheck.py"), tf.name], cwd=ROOT,
                       capture_output=True, text=True)
    os.unlink(tf.name)
    out = r.stdout + r.stderr
    ok = any(l.startswith("  OK   %s " % G["name"]) for l in out.splitlines())
    return ok, out


# ---------------------------------------------------------------- search
def mutate(st, perms, alts, nodes, rng):
    order = [list(o) for o in st[0]]
    choice = list(st[1])
    st2 = (order, choice)
    up, ua = set(), set()
    used(nodes, st2, up, ua)
    movable = [p for p in up if len(perms[p].units) > 1]
    switch = [a for a in ua if len(alts[a].alts) > 1]
    for _ in range(rng.choice([1, 1, 1, 2, 2, 3])):
        if not movable and not switch:
            break
        if switch and (not movable or rng.random() < len(switch) / (len(switch) + 2.0 * len(movable))):
            a = rng.choice(switch)
            choice[a] = rng.choice([k for k in range(len(alts[a].alts)) if k != choice[a]])
        else:
            L = order[rng.choice(movable)]
            r = rng.random()
            if r < 0.4 and len(L) > 1:  # swap neighbours
                k = rng.randrange(len(L) - 1)
                L[k], L[k + 1] = L[k + 1], L[k]
            elif r < 0.6:  # swap any two
                x, y = rng.sample(range(len(L)), 2)
                L[x], L[y] = L[y], L[x]
            else:  # move one unit
                x = L.pop(rng.randrange(len(L)))
                L.insert(rng.randrange(len(L) + 1), x)
    return st2


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("template")
    ap.add_argument("key")
    ap.add_argument("function")
    ap.add_argument("--jobs", type=int, default=3)
    ap.add_argument("--iters", type=int, default=1000, help="number of candidate compiles")
    ap.add_argument("--name", default=None, help="output name (default: template file name without extension)")
    ap.add_argument("--decls", action="store_true", help="also reorder declaration runs between //LPERM-BEGIN/END")
    ap.add_argument("--seed", type=int, default=None)
    ap.add_argument("--worse", type=float, default=0.02,
                    help="probability to continue from a slightly worse candidate (best+1..2) to leave plateaus")
    ap.add_argument("--nice", type=int, default=0, help="extra niceness of the worker processes")
    ap.add_argument("--verbose", action="store_true")
    ap.add_argument("--scan", action="store_true",
                    help="only compile the start state and each single alternative of every /*A*/ group, print the scores")
    a = ap.parse_args()

    os.makedirs(TMPROOT, exist_ok=True)
    os.makedirs(OUTDIR, exist_ok=True)
    text = open(a.template).read()
    if a.decls:
        text = add_decl_blocks(text)
    nodes = parse(text)
    perms, alts = [], []
    collect(nodes, perms, alts)
    st0 = ([list(range(len(p.units))) for p in perms], [0] * len(alts))
    name = a.name or os.path.splitext(os.path.basename(a.template))[0]
    bestp = os.path.join(OUTDIR, name + ".best.cpp")
    scorep = os.path.join(OUTDIR, name + ".score")
    logf = open(os.path.join(OUTDIR, name + ".log"), "a")
    rng = random.Random(a.seed)

    def log(msg):
        line = time.strftime("%H:%M:%S ") + msg
        print(line, flush=True)
        logf.write(line + "\n")
        logf.flush()

    cfg = load_cfg(a.key, a.function)
    init_worker(cfg, 0)
    log("start %s %s (0x%08X, 0x%X bytes); %d perm blocks (%d units), %d alt groups; jobs %d iters %d"
        % (name, cfg["name"][:60], cfg["addr"], cfg["size"], len(perms), sum(len(p.units) for p in perms),
           len(alts), a.jobs, a.iters))

    if a.scan:
        print("start", evaluate(render(nodes, st0))[0])
        for g in range(len(alts)):
            for k in range(1, len(alts[g].alts)):
                c = list(st0[1]); c[g] = k
                sc, err = evaluate(render(nodes, (st0[0], c)))
                first = render(alts[g].alts[k], st0).strip().split("\n")[0][:70]
                print("alt %d.%d %5d  %s" % (g, k, sc, first))
        return 0
    cache = {}
    t0 = render(nodes, st0)
    s0, err = evaluate(t0)
    if s0 >= BAD:
        log("template does not compile / function missing:\n" + (err or ""))
        return 2
    log("start score %d" % s0)
    best, bs = st0, s0
    cur, cs = st0, s0
    cache[hashlib.md5(t0.encode()).hexdigest()] = s0
    open(bestp, "w").write(t0)
    open(scorep, "w").write("%d\n" % bs)
    failed_zero = set()

    def confirm(t):
        ok, out = real_check(t, os.path.join(OUTDIR, name + ".found.cpp"))
        if ok:
            log("FOUND: %s is OK in libcheck; source in build/lperm/%s.found.cpp" % (cfg["name"], name))
        else:
            log("score 0 but libcheck does not accept it (references?):\n" +
                "\n".join(l for l in out.splitlines() if cfg["name"] in l or l.startswith("       ")))
        return ok

    if s0 == 0 and confirm(t0):
        open(scorep, "w").write("0 FOUND\n")
        print("FOUND")
        return 0
    done = 0
    batch = max(a.jobs * 2, 2)
    stale = 0
    with Pool(a.jobs, initializer=init_worker, initargs=(cfg, a.nice)) as pool:
        while done < a.iters:
            cands, texts = [], []
            tries = 0
            while len(cands) < batch and tries < batch * 50:
                tries += 1
                st = mutate(cur, perms, alts, nodes, rng)
                t = render(nodes, st)
                h = hashlib.md5(t.encode()).hexdigest()
                if h in cache or h in (x[2] for x in cands):
                    continue
                cands.append((st, t, h))
            if not cands:
                stale += 1
                if stale > 20:
                    log("search space exhausted around the current state")
                    break
                cur, cs = best, bs
                continue
            res = pool.map(evaluate, [c[1] for c in cands])
            done += len(cands)
            order = sorted(range(len(cands)), key=lambda k: res[k][0])
            for k in order:
                cache[cands[k][2]] = res[k][0]
            k = order[0]
            sc = res[k][0]
            st, t, h = cands[k]
            if sc == 0 and h not in failed_zero:
                if confirm(t):
                    open(bestp, "w").write(t)
                    open(scorep, "w").write("0 FOUND\n")
                    print("FOUND")
                    return 0
                failed_zero.add(h)
                sc = 1
            if sc < bs:
                best, bs = st, sc
                open(bestp, "w").write(t)
                open(scorep, "w").write("%d\n" % bs)
                log("iter %d: new best %d" % (done, bs))
            if sc <= cs:
                cur, cs = st, sc
            elif sc <= bs + 2 and rng.random() < a.worse:
                cur, cs = st, sc
                if a.verbose:
                    log("iter %d: wander to %d" % (done, sc))
            if cs > bs + 2:
                cur, cs = best, bs
            if a.verbose and done % (batch * 25) < batch:
                log("iter %d: best %d current %d cache %d" % (done, bs, cs, len(cache)))
    log("end after %d compiles: best %d (build/lperm/%s.best.cpp)" % (done, bs, name))
    return 0 if bs == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
