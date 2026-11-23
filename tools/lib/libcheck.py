#!/usr/bin/env python3
"""Compare one compiled library source with main.dol (called by check_lib.py).

Like tools/check_func.py (relocated fields masked, every reference checked), but
references are resolved per object instead of through one global name table:

- Call/branch to a function of the same object (static, weak template copy,
  thunk target, method): accepted when the global/map address agrees, or when
  that function's own code is byte-identical at the address the original
  branches to and its references verify too (greatest fixpoint over the object).
- Pointer tables (vtables, jump tables, pooled `...data.N` statics): every entry
  that points into this object's code is checked the same way (function plus
  offset, so jump-table labels must land at the same offset inside the function
  the original uses); the other bytes of the table are compared. A pooled
  `...data.N` reference covers only up to the next address another relocation
  of the object points to (one object of the pool), not the whole pool.
- Uninitialised statics (.bss/.sbss/common) of this object: learned per object.
  All references from verified functions must give the same address (majority,
  the others fail), two statics may not overlap, and the address must not be in
  code. A global name that the global tables already
  place elsewhere still fails.
- Everything else (externs, initialised data contents) as in check_func.py.

A function counts as OK at its map address or, if it verifies there, at the
address the original references it from (printed as `at 0x...`).

Usage: libcheck.py JSONARGS     (written by check_lib.py: source, cc, flags, map entry, tables)
"""
import json, os, shlex, struct, subprocess, sys, tempfile
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path[:0] = [HERE, os.path.join(HERE, "..")]
ROOT = os.path.dirname(os.path.dirname(HERE))
import check_func as cf

SDA_BASE, SDA2_BASE = 0x804CA040 + 0x8000, 0x804CCA60 + 0x8000
SHN_COMMON = 0xFFF2


def parse_elf(path):
    """check_func.parse_elf plus symbol binding and index."""
    secs, syms, relocs = cf.parse_elf(path)
    d = open(path, "rb").read()
    st = next(s for s in secs if s["type"] == 2)
    for i, s in enumerate(syms):
        info = d[st["off"] + i * 16 + 12]
        s["bind"] = info >> 4
        s["idx"] = i
    return secs, syms, relocs


def dol_text_ranges():
    data = open(cf.DOL, "rb").read(0xD8)
    addrs = struct.unpack(">18I", data[0x48:0x90])
    sizes = struct.unpack(">18I", data[0x90:0xD8])
    return [(a, a + s) for a, s in zip(addrs[:7], sizes[:7]) if s]


class Obj:
    def __init__(self, path):
        self.secs, self.syms, self.relocs = parse_elf(path)
        self.funcs = [s for s in self.syms if s["type"] == 2 and 0 < s["shndx"] < 0xFF00
                      and self.secs[s["shndx"]]["name"].startswith(".text")]
        self.bysec = {}
        for f in self.funcs:
            self.bysec.setdefault(f["shndx"], []).append(f)
        # every in-object address any relocation points to (cuts pooled data)
        self.reftargets = {}
        for si, lst in self.relocs.items():
            for off, rt, tname, add, tsym in lst:
                if 0 < tsym["shndx"] < 0xFF00:
                    self.reftargets.setdefault(tsym["shndx"], set()).add(tsym["value"] + add)

    def func_at(self, shndx, off):
        best = None
        for f in self.bysec.get(shndx, []):
            if f["value"] <= off < f["value"] + max(f["size"], 1):
                if best is None or f["size"] < best["size"]:
                    best = f
        return best


def main():
    a = json.load(open(sys.argv[1]))
    verbose = a["verbose"]
    ent = a["entry"]
    gaddrs = a["all"]
    fstart = {int(k): v for k, v in a["fstart"].items()}   # symbols.txt function start -> size
    cc = os.path.join(ROOT, "build/compilers", a["cc"], "mwcceppc.exe")
    with tempfile.TemporaryDirectory() as tmp:
        objp = os.path.join(tmp, "out.o")
        cmd = [cf.WIBO, cc, *[x for f in a["flags"] for x in shlex.split(f)], "-c", a["source"], "-o", objp]
        r = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True)
        if r.returncode != 0 or not os.path.exists(objp):
            print(r.stdout + r.stderr)
            print("COMPILE FAILED")
            return 2
        o = Obj(objp)
    secs, relocs = o.secs, o.relocs
    read = cf.dol_reader()
    text_ranges = dol_text_ranges()
    mapf = {n: (v[0], v[1], v[2]) for n, v in ent["functions"].items()}
    unverified = set()
    nconst = [0]

    def rd(addr, n):
        try:
            return bytes(read(addr, n))
        except KeyError:
            return None

    alt = {k: set(v) for k, v in a.get("alt", {}).items()}

    def plausible(x):
        return 0x80000000 <= x < 0x81800000

    def known(name):
        return (name in gaddrs and plausible(gaddrs[name])) or bool(alt.get(name))

    def named_ok(name, x):
        """A global name may sit at its table address or at any address that matched
        code of another source references under that name (libraries linked twice,
        e.g. nw4r ut in the main lib and in HBM)."""
        return (name in gaddrs and gaddrs[name] == x) or x in alt.get(name, ())

    def fkey(f):
        return f["idx"]

    def text_target(tsym, add, want, F, addr):
        """Reference to code of this object. Returns (ok, dep or None, msg)."""
        G = o.func_at(tsym["shndx"], tsym["value"] + add)
        if G is None:
            return False, None, "into no function"
        og = tsym["value"] + add - G["value"]
        if fkey(G) == fkey(F):
            return want == addr + og, None, "self"
        if named_ok(tsym["name"], want - add):
            return True, None, ""
        return True, (fkey(G), want - og), ""

    def extent(tsym, addend):
        sh = tsym["shndx"]
        blob = secs[sh]["data"]
        start = tsym["value"] + addend
        if tsym["name"].startswith("...data.") and tsym["size"] == 0:
            later = [x for x in o.reftargets.get(sh, ()) if x > start]
            nxt = min((s2["value"] for s2 in o.syms if s2["shndx"] == sh and s2["name"].startswith("...data.")
                       and s2["value"] > tsym["value"]), default=len(blob))
            return start, min([nxt] + later)
        if tsym["name"].startswith("@stringBase") or secs[sh]["name"].startswith(".rodata") and b"\0" in blob[start:start + 256] and tsym["size"] == 0:
            return start, blob.index(b"\0", start) + 1
        n = (tsym["size"] - addend) if tsym["size"] > addend else 4
        return start, start + n

    def pointee_ok(tsym, addend, want, depth=0):
        """Initialised data of this object at `want`: bytes equal, and pointers in it
        to further data of this object (RTTI names, string tables) followed too."""
        sh = tsym["shndx"]
        start, end = extent(tsym, addend)
        mine = bytearray(secs[sh]["data"][start:end])
        orig = rd(want, len(mine))
        if orig is None:
            return False
        orig = bytearray(orig)
        for roff, rt, rn, radd, rsym in relocs.get(sh, []):
            if start <= roff < end:
                e = roff - start
                if rt != 1 or e + 4 > len(mine):
                    return False
                oe, = struct.unpack(">I", orig[e:e + 4])
                rs = rsym["shndx"]
                if named_ok(rn, oe - radd):
                    pass
                elif 0 < rs < len(secs) and secs[rs]["type"] != 8 and not secs[rs]["name"].startswith(".text"):
                    if depth >= 12 or not pointee_ok(rsym, radd, oe, depth + 1):
                        return False
                else:
                    unverified.add(rn)
                mine[e:e + 4] = orig[e:e + 4] = b"\0" * 4
        return mine == orig

    def evaluate(F, addr, osize):
        res = {"deps": [], "data": [], "bad": [], "words": [], "n": 0, "bytes_ok": False}
        ours = bytearray(secs[F["shndx"]]["data"][F["value"]:F["value"] + F["size"]])
        th = rd(addr, osize)
        if th is None:
            res["bad"].append("original not readable")
            return res
        theirs = bytearray(th)
        if len(ours) != len(theirs):
            res["bad"].append(f"size 0x{len(ours):X}, want 0x{len(theirs):X}")
        pending_ha = {}
        for off, rtype, target, addend, tsym in relocs.get(F["shndx"], []):
            rel = off - F["value"]
            if not (0 <= rel < min(len(theirs), len(ours))):
                continue
            want = None
            if rtype == 10:
                w, = struct.unpack(">I", theirs[rel:rel + 4])
                disp = w & 0x03FFFFFC
                if disp & 0x02000000:
                    disp -= 0x04000000
                want = addr + rel + disp
            elif rtype == 109:
                w, = struct.unpack(">I", theirs[rel:rel + 4])
                ra, simm = (w >> 16) & 0x1F, w & 0xFFFF
                if simm & 0x8000:
                    simm -= 0x10000
                base = {13: SDA_BASE, 2: SDA2_BASE, 0: 0}.get(ra)
                if base is not None:
                    want = base + simm
            elif rtype == 6:
                hi, = struct.unpack(">H", theirs[rel:rel + 2])
                pending_ha[(target, addend)] = hi
                continue
            elif rtype == 4:
                lo, = struct.unpack(">h", theirs[rel:rel + 2])
                hi = pending_ha.get((target, addend))
                if hi is not None:
                    want = ((hi << 16) + lo) & 0xFFFFFFFF
            if want is None:
                continue
            sh = tsym["shndx"]
            tsec = secs[sh] if 0 < sh < len(secs) else None
            if tsec is not None and tsec["name"].startswith(".text"):
                ok, dep, msg = text_target(tsym, addend, want, F, addr)
                if not ok:
                    res["bad"].append(f"+0x{rel:03X} -> {target}+0x{addend:X} but original uses 0x{want:08X} ({msg})")
                elif dep:
                    res["deps"].append(dep)
                continue
            if tsec is not None and tsec["type"] != 8:
                blob = tsec["data"]
                start, end = extent(tsym, addend)
                mine = bytes(blob[start:end])
                trel = [r_ for r_ in relocs.get(sh, []) if start <= r_[0] < end]
                if trel:
                    torig = rd(want, len(mine))
                    ok = torig is not None
                    msgs = []
                    if ok:
                        tm, to = bytearray(mine), bytearray(torig)
                        for roff, rt, rn, radd, rsym in trel:
                            e = roff - start
                            if rt != 1 or e + 4 > len(tm):
                                ok = False
                                msgs.append(f"reloc type {rt} at +0x{e:X}")
                                continue
                            oe, = struct.unpack(">I", to[e:e + 4])
                            rs = rsym["shndx"]
                            if 0 < rs < len(secs) and secs[rs]["name"].startswith(".text"):
                                eok, dep, msg = text_target(rsym, radd, oe, F, addr)
                                if not eok:
                                    ok = False
                                    msgs.append(f"+0x{e:X} {rn}: 0x{oe:08X} ({msg})")
                                elif dep:
                                    res["deps"].append(dep)
                            elif 0 < rs < len(secs) and secs[rs]["type"] != 8:
                                # pointer to initialised data of this object (strings, nested
                                # tables): compare the pointed-to object, its own pointers masked
                                if not pointee_ok(rsym, radd, oe):
                                    ok = False
                                    msgs.append(f"+0x{e:X} {rn}: data at 0x{oe:08X} differs")
                            elif named_ok(rn, oe - radd):
                                pass
                            elif (0 < rs < len(secs) or rs == SHN_COMMON) and (rsym["bind"] == 0 or not known(rn)):
                                res["data"].append((rsym["idx"], oe - radd))
                            elif known(rn):
                                ok = False
                                msgs.append(f"+0x{e:X} {rn}: 0x{oe:08X}")
                            else:
                                unverified.add(rn)
                            tm[e:e + 4] = b"\0" * 4
                            to[e:e + 4] = b"\0" * 4
                        if tm != to:
                            ok = False
                            msgs.append("other bytes differ")
                    if ok:
                        nconst[0] += 1
                    else:
                        res["bad"].append(f"+0x{rel:03X} -> {target}: table entries differ from original at 0x{want:08X}: " + "; ".join(msgs[:4]))
                    continue
                orig = rd(want, len(mine))
                if orig != mine:
                    res["bad"].append(f"+0x{rel:03X} -> {target}+0x{addend:X}: constant {mine.hex()[:64]} but original has {orig.hex()[:64] if orig else '?'} at 0x{want:08X}")
                else:
                    nconst[0] += 1
                continue
            if named_ok(target, want - addend):
                continue
            if (tsec is not None or sh == SHN_COMMON) and (tsym["bind"] == 0 or not known(target)):
                # static of this object (the name tables may hold another source's
                # static of the same name): learned per object, see the fixpoint below
                res["data"].append((tsym["idx"], want - addend))
                continue
            if known(target):
                res["bad"].append(f"+0x{rel:03X} -> {target}+0x{addend:X} but original uses 0x{want:08X}")
                continue
            unverified.add(target)
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
        res["words"] = [i for i in range(n) if ours[i * 4:i * 4 + 4] != theirs[i * 4:i * 4 + 4]]
        res["n"] = n
        res["bytes_ok"] = len(ours) == len(theirs) and not res["words"]
        return res

    byidx = {f["idx"]: f for f in o.funcs}
    evals = {}
    work = []
    for F in o.funcs:
        if F["name"] in mapf:
            ad, sz, _st = mapf[F["name"]]
            work.append((F["idx"], ad, sz))
    while work:
        fi, ad, sz = work.pop()
        if (fi, ad) in evals:
            continue
        r = evaluate(byidx[fi], ad, sz)
        evals[(fi, ad)] = r
        for gi, ga in r["deps"]:
            if (gi, ga) in evals:
                continue
            G = byidx[gi]
            if G["name"] in mapf and mapf[G["name"]][0] == ga:
                work.append((gi, ga, mapf[G["name"]][1]))
            elif ga in fstart and fstart[ga] == G["size"]:
                work.append((gi, ga, fstart[ga]))
            else:
                evals[(gi, ga)] = {"deps": [], "data": [], "bad": ["no function of this size starts there"], "words": [], "n": 0, "bytes_ok": False}

    valid = {k for k, r in evals.items() if r["bytes_ok"] and not r["bad"]}

    def in_text(x):
        return any(lo <= x < hi for lo, hi in text_ranges)

    symby = {s["idx"]: s for s in o.syms}
    why = {}
    changed = True
    while changed:
        changed = False
        for k in list(valid):
            for d in evals[k]["deps"]:
                if d not in valid:
                    valid.discard(k)
                    why[k] = f"needs {byidx[d[0]]['name']} at 0x{d[1]:08X}"
                    changed = True
                    break
        # learned statics: one address per symbol, majority over verified functions
        votes = {}
        for k in valid:
            for si, ad in evals[k]["data"]:
                votes.setdefault(si, {}).setdefault(ad, set()).add(k)
        chosen = {}
        for si, by in votes.items():
            ranked = sorted(by.items(), key=lambda x: -len(x[1]))
            if len(ranked) > 1 and len(ranked[0][1]) == len(ranked[1][1]):
                bad_addrs = [x for x, _ in ranked]
            else:
                chosen[si] = ranked[0][0]
                bad_addrs = [x for x, _ in ranked[1:]]
            if si in chosen and in_text(chosen[si]):
                bad_addrs.append(chosen.pop(si))
            for x in bad_addrs:
                for k in by[x]:
                    if k in valid:
                        valid.discard(k)
                        why[k] = f"static {symby[si]['name']} at 0x{x:08X} disagrees"
                        changed = True
        # two statics of the object never share an address (the declaration order
        # of the reference source may differ from the game's, so order is not checked)
        lst = sorted((ad, si) for si, ad in chosen.items())
        for (a1, s1), (a2, s2) in zip(lst, lst[1:]):
            if a1 + max(symby[s1]["size"], 1) > a2:
                for k in list(valid):
                    if any(si in (s1, s2) for si, _ in evals[k]["data"]):
                        valid.discard(k)
                        why[k] = f"statics {symby[s1]['name']}/{symby[s2]['name']} overlap"
                        changed = True

    all_ok = True
    checked = 0
    for F in sorted(o.funcs, key=lambda f: (f["shndx"], f["value"])):
        name = F["name"]
        mine = [k for k in evals if k[0] == F["idx"]]
        if not mine:
            if name in mapf:
                continue
            print(f"  SKIP {name}: not in map")
            continue
        mk = (F["idx"], mapf[name][0]) if name in mapf else None
        checked += 1
        if mk in valid:
            print(f"  OK   {name} (0x{F['size']:X} bytes) at 0x{mk[1]:08X}")
            continue
        alt = sorted(k for k in mine if k in valid)
        if alt:
            print(f"  OK   {name} (0x{F['size']:X} bytes) at 0x{alt[0][1]:08X} (referenced address; map has 0x{mapf[name][0] if name in mapf else 0:08X})")
            continue
        if mk is None:
            checked -= 1
            print(f"  SKIP {name}: not in map")
            continue
        all_ok = False
        r = evals[mk]
        for b in r["bad"]:
            if b.startswith("size"):
                print(f"  DIFF {name}: {b}")
        refbad = [b for b in r["bad"] if not b.startswith("size")]
        if mk in why:
            refbad.append(why[mk])
        if refbad:
            print(f"  DIFF {name}: {len(refbad)} wrong reference(s)")
            for b in refbad[:20]:
                print(f"       {b}")
        print(f"  DIFF {name}: {len(r['words'] or [])} of {r.get('n', 0)} words differ")
        if verbose and r["words"]:
            ad = mk[1]
            ours = secs[F["shndx"]]["data"][F["value"]:F["value"] + F["size"]]
            th = rd(ad, mapf[name][1]) or b""
            for i in r["words"][:40]:
                print(f"       +0x{i*4:03X} {ad + i*4:08X}: ours {ours[i*4:i*4+4].hex()} want {th[i*4:i*4+4].hex()}")
    if nconst[0]:
        print(f"  constants/strings verified by value: {nconst[0]}")
    if unverified:
        print("  note: references to symbols with no known address were not checked: " + ", ".join(sorted(unverified)))
    if checked == 0:
        print("no mapped functions found in object")
        return 1
    print("MATCH" if all_ok else "MISMATCH")
    return 0 if all_ok else 1


if __name__ == "__main__":
    sys.exit(main())
