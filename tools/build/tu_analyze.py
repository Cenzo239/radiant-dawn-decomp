#!/usr/bin/env python3
"""Reconstruct translation-unit (TU) boundaries of the game range of main.dol.

Model: the game was linked from objects in one link order; every object contributes one
contiguous range to each section, in the same order in every section. Data that only its own
TU references (compiler float/double literals in .sdata2, switch jump tables, .data string
pools) therefore pins TU membership:

 1. Local items ("witnesses"): .sdata2 literals (not strings), jump tables, .data strings whose
    referencing functions span < 128 KB (longer spans are global char arrays). Their owners are
    the game functions that reference them, directly or through a .data/.rodata table that is
    referenced by at most four places (never through .sdata pointers: those are globals).
 2. Cost of a cut before function c: witnesses straddling c, plus, per section, the minimum
    number of witnesses out of order for the best data cut (segment tree sweep). A cut with
    cost 0 is "clean": no witness contradicts a TU boundary there. Units = runs between clean
    cuts. Any original TU boundary is a clean cut (up to mis-classified global witnesses),
    and a unit is the smallest piece that can be linked on its own without splitting a pool.
 3. Boundary evidence:
      sinit   first clean cut at/after a __sinit (.ctors entry); MWCC emits __sinit after the
              TU's functions and only weak (inline/template) functions after it
      dup     a float/double literal or .data string occurs in two places: they are in two TUs
              (MWCC pools identical literals per TU), so a boundary lies between the two units;
              "dup1" when only one clean cut is possible in between
      inferred  greedy minimal set of cuts that satisfies the remaining dup intervals (the cut is
              placed at the latest clean cut of the interval; the true position is anywhere in
              the window reported)
      range   start/end of the game code
 4. TUs = runs between boundaries. Confidence: high = both ends sinit/dup1/range; medium = an
    inferred end with a window of at most 2 clean cuts; low = otherwise. A TU may still hold
    several original TUs (no duplicate literal tells them apart); the number of clean cuts
    inside is reported.

Outputs: docs/tu_map.tsv, docs/TU_MAP.md, build/tmp/buildtree/tu_units.json (units for gen_units.py)
"""
import bisect
import collections
import json
import os
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, HERE)
import dolmodel as M  # noqa: E402

DATA_SECS = [".rodata", ".data", ".bss", ".sdata", ".sbss", ".sdata2"]
GAME_DATA_START = {".rodata": 0x80360AA0, ".data": 0x80378720, ".bss": 0x803B6700,
                   ".sdata": 0x804CA040, ".sbss": 0x804CB080, ".sdata2": 0x804CCA60}
# First library-owned item of each section: every item before it is referenced only by game
# code, every item from it on only by library code (checked by check_lib_split()).
GAME_DATA_END = {".rodata": 0x803741B8, ".data": 0x80393450, ".bss": 0x80432F20,
                 ".sdata": 0x804CAB90, ".sbss": 0x804CC110, ".sdata2": 0x804D0BE0}
GLOBAL_SPAN = 0x20000
WITNESS_RODATA = True


def build():
    S = M.model()
    dol = M.Dol()
    g0, g1 = M.GAME_TEXT
    fns = sorted((s for s in S.values() if s.sec == ".text" and s.type == "function" and g0 <= s.addr < g1),
                 key=lambda s: s.addr)
    idx = {f.name: i for i, f in enumerate(fns)}
    items = {sec: sorted((s for s in S.values() if s.sec == sec and s.type == "object"
                          and GAME_DATA_START[sec] <= s.addr < GAME_DATA_END[sec]), key=lambda s: s.addr)
             for sec in DATA_SECS}

    def owners(s, depth=0):
        out = set()
        for r in s.refby:
            t = S[r]
            if t.name in idx:
                out.add(idx[t.name])
            elif t.sec in (".data", ".rodata") and t.type == "object" and depth < 2 and len(t.refby) <= 4:
                out |= owners(t, depth + 1)
        return out

    for sec in DATA_SECS:
        for s in items[sec]:
            s.attrs["_own"] = sorted(owners(s))
            s.attrs["_bytes"] = dol.read(s.addr, s.size) if s.size and sec not in (".bss", ".sbss") else b""
    ctors = []
    for a in range(M.SECTIONS[".ctors"][0], M.SECTIONS[".ctors"][1], 4):
        v, = struct.unpack(">I", dol.read(a, 4))
        if g0 <= v < g1:
            ctors.append((a, v))
    return S, dol, fns, idx, items, ctors


def span(fns, s):
    o = s.attrs["_own"]
    return fns[o[-1]].addr - fns[o[0]].addr


_STATICS = []
# File-local statics named by a per-function symbol map are witnesses (no cut between their
# users) when their users lie close together (MAP_STATIC_SPAN): fn_8006BDCC's static
# lbl_803CB7B8 (users 0x111C apart) keeps fn_8006C19C in its unit. Statics whose users spread
# over large ranges (lbl_80425478 around 0x802383F4, 0x7730; the sound manager's lbl_8042E798)
# would merge units that no longer place (with every map static: net -0.8%).
# Off by default as well: fn_8006BDCC's static is a function-local static ("...bss.0") that
# fn_8006C19C names as extern lbl_803CB7B8; in one unit the reference stays undefined (a
# function-local static cannot be named from another function), and the merged unit is lost
# (-0x32B8 bytes). --map-statics-near enables the near statics, --map-statics all of them.
MAP_STATICS = "--map-statics" in sys.argv or "--map-statics-near" in sys.argv
MAP_STATIC_SPAN = 1 << 40 if "--map-statics" in sys.argv else 0x2000


def map_statics():
    """Labels that a per-function symbol map (<file>.symbols.json) names as a file-local
    static ("...bss.0", "sa$42", guards): only their own TU can reference them."""
    if not _STATICS:
        out = set()
        for dp, _dn, fns in os.walk(os.path.join(ROOT, "src/game")):
            if "/wip" in dp.replace(os.sep, "/"):
                continue
            for fn in fns:
                if fn.endswith(".symbols.json"):
                    try:
                        m = json.load(open(os.path.join(dp, fn)))
                    except ValueError:
                        continue
                    out |= {v for k, v in m.items() if not k.replace("_", "a").isalnum()}
        _STATICS.append(out)
    return _STATICS[0]


def witness(fns, sec, s):
    if not s.attrs["_own"]:
        return False
    if MAP_STATICS and s.name in map_statics() and span(fns, s) < MAP_STATIC_SPAN:
        return span(fns, s) < GLOBAL_SPAN
    if sec == ".sdata2":
        return s.attrs.get("data") != "string"
    if s.name.startswith("jumptable_"):
        return True
    if sec == ".data" and s.attrs.get("data") == "string":
        return span(fns, s) < GLOBAL_SPAN
    if sec == ".rodata" and WITNESS_RODATA and looks_like_strings(s.attrs["_bytes"]):
        # pooled read-only string literals (e.g. "GActor.c\0...") referenced from code
        return span(fns, s) < GLOBAL_SPAN
    return False


def looks_like_strings(b):
    if len(b) < 4 or not b.rstrip(b"\0") or b"\0" not in b:
        return False
    body = b.rstrip(b"\0")
    text = sum(1 for x in body if 0x20 <= x < 0x7F or x >= 0x81 or x in (0, 9, 10))
    return text == len(body) and body.count(b"\0") * 3 < len(body)


class MinSeg:
    """Range add, global min."""
    def __init__(self, vals):
        self.N = 1
        while self.N < len(vals):
            self.N *= 2
        self.mn = [10 ** 9] * (2 * self.N)
        self.lz = [0] * (2 * self.N)
        for i, v in enumerate(vals):
            self.mn[self.N + i] = v
        for i in range(self.N - 1, 0, -1):
            self.mn[i] = min(self.mn[2 * i], self.mn[2 * i + 1])

    def add(self, l, r, v, node=1, nl=0, nr=None):
        if nr is None:
            nr = self.N
        if r <= nl or nr <= l:
            return
        if l <= nl and nr <= r:
            self.mn[node] += v
            self.lz[node] += v
            return
        m = (nl + nr) // 2
        self.add(l, r, v, 2 * node, nl, m)
        self.add(l, r, v, 2 * node + 1, m, nr)
        self.mn[node] = min(self.mn[2 * node], self.mn[2 * node + 1]) + self.lz[node]


def cut_costs(fns, items):
    n = len(fns)
    total = [0] * (n + 1)
    for sec in DATA_SECS:
        L = [s for s in items[sec] if witness(fns, sec, s)]
        m = len(L)
        if not m:
            continue
        st = MinSeg(list(range(m + 1)))
        ev = collections.defaultdict(list)
        for i, s in enumerate(L):
            o = s.attrs["_own"]
            ev[o[0] + 1].append((0, i))
            ev[o[-1] + 1].append((1, i))
        X = 0
        for c in range(1, n + 1):
            for t, i in ev.get(c, ()):
                if t == 0:
                    st.add(i + 1, m + 1, -1)
                    X += 1
                else:
                    st.add(0, i + 1, 1)
                    X -= 1
            total[c] += X + st.mn[1]
    return total


def analyze():
    S, dol, fns, idx, items, ctors = build()
    n = len(fns)
    cost = cut_costs(fns, items)
    clean = [c for c in range(1, n) if cost[c] == 0]
    # Alignment: an object whose .sdata2 holds a double is 8-aligned, so a cut whose .sdata2
    # data cut is not 8-aligned cannot start an object that has a double (iterate: dropping a
    # cut merges units).
    sd2 = [s for s in items[".sdata2"] if witness(fns, ".sdata2", s)]
    first_own = sorted((s.attrs["_own"][0], s.addr, s.size) for s in sd2)
    dropped = []
    while True:
        cuts = [0] + clean + [n]
        bad = set()
        for c, nxt in zip(cuts[1:-1], cuts[2:]):
            right = [(a, z) for o, a, z in first_own if c <= o < nxt]
            if not right:
                continue
            d = min(a for a, z in right)
            if d % 8 and any(z == 8 for a, z in right):
                bad.add(c)
        if not bad:
            break
        dropped += sorted(bad)
        clean = [c for c in clean if c not in bad]
    cuts = [0] + clean + [n]
    units = list(zip(cuts, cuts[1:]))
    uid = [0] * n
    for k, (a, b) in enumerate(units):
        for i in range(a, b):
            uid[i] = k
    nu = len(units)

    def unit_of(s):
        return uid[s.attrs["_own"][0]]

    # boundaries are identified by the unit index they start (1..nu-1)
    evidence = collections.defaultdict(set)
    fa = {f.addr: i for i, f in enumerate(fns)}
    sinits = {}
    for a, v in ctors:
        c = fa[v] + 1
        k = uid[c] if c < n else nu
        # first clean cut at/after c: unit containing c starts at or before c
        tail = False
        if c < n and units[k][0] < c:
            k += 1
        if k < nu and units[k][0] != c:
            tail = True   # weak (inline/template) functions follow the __sinit
        if k < nu:
            evidence[k].add("sinit+tail" if tail else "sinit")
        sinits[k] = fns[fa[v]].name
    occ = collections.defaultdict(list)
    for s in items[".sdata2"]:
        if witness(fns, ".sdata2", s) and s.attrs.get("data") in ("float", "double"):
            occ[("f", s.attrs["_bytes"])].append(unit_of(s))
    for s in items[".data"]:
        if witness(fns, ".data", s) and s.attrs.get("data") == "string":
            occ[("s", s.attrs["_bytes"])].append(unit_of(s))
    intervals = []
    for key, L in occ.items():
        L = sorted(set(L))
        for a, b in zip(L, L[1:]):
            intervals.append((a + 1, b, key))
    # file-name strings (assert/__FILE__) referenced from code
    names = collections.defaultdict(set)
    for sec in (".rodata", ".data", ".sdata"):
        for s in items[sec]:
            b = s.attrs["_bytes"]
            for part in b.split(b"\0"):
                t = part.decode("latin-1")
                if len(t) > 2 and t.endswith((".c", ".cpp")) and t.replace("_", "a").replace(".", "a").isalnum():
                    for o in s.attrs["_own"]:
                        names[uid[o]].add(t)
    # different source-file names (assert strings) in two units: a boundary lies between them
    named = sorted((k, nm) for k, v in names.items() for nm in v)
    for (k1, n1), (k2, n2) in zip(named, named[1:]):
        if n1 != n2 and k1 < k2:
            intervals.append((k1 + 1, k2, ("n", n1, n2)))
    for a, b, key in intervals:
        if a == b:
            evidence[a].add("dup1")
    strong = {k for k, e in evidence.items() if e & {"sinit", "dup1"}}
    # greedy stabbing of the remaining intervals
    inferred = {}
    for a, b, key in sorted(intervals, key=lambda x: (x[1], x[0])):
        if any(a <= k <= b for k in strong.union(inferred)):
            # already satisfied (strong or inferred cut inside the window)
            continue
        inferred[b] = [a, b]
    # narrow each inferred window to the intersection of the intervals it alone satisfies
    for a, b, key in intervals:
        hits = [k for k in strong.union(inferred) if a <= k <= b]
        if len(hits) == 1 and hits[0] in inferred:
            w = inferred[hits[0]]
            w[0], w[1] = max(w[0], a), min(w[1], b)
    for k in inferred:
        evidence[k].add("inferred")
    for a, b, key in intervals:
        for k in range(a, b + 1):
            if k in evidence:
                evidence[k].add("dup")
    tails = {k for k, e in evidence.items() if "sinit+tail" in e and k not in strong}
    bounds = sorted({0, nu} | strong | set(inferred) | tails)

    # data cut address per unit boundary and section: first witness on the right side
    wit = {sec: [s for s in items[sec] if witness(fns, sec, s)] for sec in DATA_SECS}

    def data_cut(sec, k):
        if k == 0:
            return GAME_DATA_START[sec]
        if k >= nu:
            return GAME_DATA_END[sec]
        c = units[k][0]
        right = [s.addr for s in wit[sec] if s.attrs["_own"][0] >= c]
        return min(right) if right else GAME_DATA_END[sec]

    tus = []
    for t, (ka, kb) in enumerate(zip(bounds, bounds[1:])):
        fa_, fb_ = units[ka][0], units[kb - 1][1]

        def end_kind(k):
            if k in (0, nu):
                return "range"
            e = evidence[k]
            if "sinit" in e:
                return "sinit"
            if "dup1" in e:
                return "dup1"
            if "sinit+tail" in e:
                return "sinit+tail"
            return "inferred"

        def window(k):
            if k in tails and k not in inferred:
                return 2
            if k in inferred:
                return inferred[k][1] - inferred[k][0] + 1
            return 1
        ek = (end_kind(ka), end_kind(kb))
        wins = (window(ka), window(kb))
        if all(e in ("range", "sinit", "dup1") for e in ek):
            conf = "high"
        elif max(wins) <= 2:
            conf = "medium"
        else:
            conf = "low"
        dr = {}
        for sec in DATA_SECS:
            a, b = data_cut(sec, ka), data_cut(sec, kb)
            if b > a:
                dr[sec] = (a, b)
        lab = set()
        for k in range(ka, kb):
            lab |= names.get(k, set())
        tus.append({
            "id": f"TU{t:04d}", "units": (ka, kb), "text": (fns[fa_].addr, fns[fb_ - 1].addr + fns[fb_ - 1].size),
            "nfunc": fb_ - fa_, "start": ek[0], "end": ek[1], "window": wins, "conf": conf,
            "inner_cuts": kb - ka - 1, "data": dr, "names": sorted(lab),
            "sinit": sinits.get(kb) if kb in sinits else None,
        })
    return {"dropped_align": dropped, "S": S, "fns": fns, "units": units, "uid": uid, "tus": tus, "evidence": evidence,
            "intervals": intervals, "cost": cost, "items": items, "ctors": ctors, "data_cut": data_cut,
            "bounds": bounds}


def region_of(addr):
    best = None
    for d in os.listdir(os.path.join(ROOT, "src/game")):
        if d.startswith("r") and "_" in d:
            a = int(d.split("_")[1], 16)
            if a <= addr and (best is None or a > best[0]):
                best = (a, d)
    return best[1] if best else ""


def write(R):
    fns, tus, units = R["fns"], R["tus"], R["units"]
    tsv = os.path.join(ROOT, "docs/tu_map.tsv")
    with open(tsv, "w") as f:
        f.write("# tu\ttext_start\ttext_end\tfunctions\tunits\t" + "\t".join(DATA_SECS) +
                "\tstart_evidence\tend_evidence\tconfidence\tsource_names\tsinit\tregion\n")
        for t in tus:
            ds = ["%08X-%08X" % t["data"][s] if s in t["data"] else "" for s in DATA_SECS]
            f.write("\t".join([t["id"], "%08X" % t["text"][0], "%08X" % t["text"][1], str(t["nfunc"]),
                               str(t["inner_cuts"] + 1), *ds,
                               t["start"] + ("" if t["window"][0] == 1 else f"(window {t['window'][0]})"),
                               t["end"] + ("" if t["window"][1] == 1 else f"(window {t['window'][1]})"),
                               t["conf"], ",".join(t["names"]), t["sinit"] or "", region_of(t["text"][0])]) + "\n")
    # units file for gen_units.py
    uj = [{"unit": k, "text": ["%08X" % fns[a].addr, "%08X" % (fns[b - 1].addr + fns[b - 1].size)],
           "functions": [f.name for f in fns[a:b]],
           "data": {sec: ["%08X" % R["data_cut"](sec, k), "%08X" % R["data_cut"](sec, k + 1)] for sec in DATA_SECS}}
          for k, (a, b) in enumerate(units)]
    json.dump(uj, open(os.path.join(ROOT, "build/tmp/buildtree/tu_units.json"), "w"))
    return tsv


def summary(R):
    fns, tus = R["fns"], R["tus"]
    total = fns[-1].addr + fns[-1].size - fns[0].addr
    by = collections.Counter()
    nb = collections.Counter()
    for t in tus:
        by[t["conf"]] += t["text"][1] - t["text"][0]
        nb[t["conf"]] += 1
    return total, by, nb


if __name__ == "__main__":
    R = analyze()
    path = write(R)
    total, by, nb = summary(R)
    print("functions", len(R["fns"]), "units", len(R["units"]), "TUs", len(R["tus"]), "sinit", len(R["ctors"]))
    for k in ("high", "medium", "low"):
        print(f"  {k:6} {nb[k]:4} TUs  0x{by[k]:06X} bytes  {100 * by[k] / total:5.1f}%")
    print("wrote", os.path.relpath(path, ROOT))
