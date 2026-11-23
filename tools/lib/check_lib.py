#!/usr/bin/env python3
"""Compile a library source from lib/src and compare every mapped function with main.dol.

Usage: tools/lib/check_lib.py ogws/src/revolution/OS/OSAlarm.c [-v]      (path relative to lib/src)
       tools/lib/check_lib.py --all [-j N]                       summary of every mapped source

Functions and symbols come from lib/map.json. Functions with status "diff" are
expected at an address inferred from the object layout and are compared too.
"""
import argparse, json, os, shlex, subprocess, sys
from concurrent.futures import ThreadPoolExecutor
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path[:0] = [HERE, os.path.join(HERE, "..")]
ROOT = os.path.dirname(os.path.dirname(HERE))
import check_func as cf

MAP = json.load(open(os.path.join(ROOT, "lib/map.json")))
MAN = json.load(open(os.path.join(ROOT, "lib/manifest.json")))
ALT = {}


def run_one(path, verbose):
    ent = MAP["sources"][path]
    man = MAN[path]
    base_syms = cf.load_symbols()
    all_addrs = dict(cf.load_all_symbol_addresses())
    all_addrs.update(MAP["symbols"])
    all_addrs.update(ent.get("syms", {}))
    for n, (a, s, st) in ent["functions"].items():
        all_addrs[n] = a
    alt = ALT.get("v")
    if alt is None:
        alt = {}
        def put(n, ad):
            if 0x80000000 <= ad < 0x81800000:
                alt.setdefault(n, set()).add(ad)
        for n, ad in cf.load_all_symbol_addresses().items():
            put(n, ad)
        for n, ad in MAP["symbols"].items():
            put(n, ad)
        for e in MAP["sources"].values():
            for n, ad in e.get("syms", {}).items():
                put(n, ad)
        alt = ALT["v"] = {n: sorted(v) for n, v in alt.items()}
    fstart = {}
    for n, (a, s) in base_syms.items():
        fstart[a] = s
    import tempfile
    tmpdir = os.path.join(ROOT, "build/tmp") if os.path.isdir(os.path.join(ROOT, "build/tmp")) else None
    with tempfile.NamedTemporaryFile("w", suffix=".json", delete=False, dir=tmpdir) as tf:
        json.dump({"source": "lib/" + path, "cc": man["cc"], "flags": man["flags"], "verbose": verbose,
                   "entry": ent, "all": all_addrs, "fstart": fstart, "alt": alt}, tf)
    r = subprocess.run([sys.executable, os.path.join(HERE, "libcheck.py"), tf.name], cwd=ROOT, capture_output=True, text=True)
    os.unlink(tf.name)
    return r.returncode, r.stdout + r.stderr


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("path", nargs="?")
    ap.add_argument("--all", action="store_true")
    ap.add_argument("-j", type=int, default=4)
    ap.add_argument("-v", action="store_true")
    a = ap.parse_args()
    if a.all:
        paths = sorted(MAP["sources"])
        with ThreadPoolExecutor(a.j) as ex:
            res = list(ex.map(lambda p: (p, run_one(p, False)), paths))
        tot_ok = tot = 0
        spans = []
        verified = {}
        lines = []
        for p, (rc, out) in res:
            oks = {l.split()[1]: int(l.split(" at ")[1].split()[0], 16) for l in out.splitlines() if l.startswith("  OK   ")}
            for l in out.splitlines():
                if l.startswith("  OK   ") and "(0x" in l:
                    spans.append((int(l.split(" at ")[1].split()[0], 16), int(l.split("(0x")[1].split()[0], 16)))
            ok = len(oks)
            n = ok + out.count("  DIFF ") + out.count("  SKIP ")
            tot_ok += ok
            tot += n
            verified[p] = oks
            lines.append(f"{'MATCH ' if rc == 0 else 'DIFF  '} {ok:3}/{n:<3} {p}")
        print("\n".join(lines))
        syms = cf.load_symbols()
        lo, hi = 0x8028BC54, 0x80360900
        tgt = {a: s for n, (a, s) in syms.items() if lo <= a < hi and n.startswith("fn_")}
        got = {}
        for p, d in verified.items():
            for nm, ad in d.items():
                if ad in tgt:
                    got[ad] = tgt[ad]
        # a symbol that dtk split off inside a verified function (e.g. the `blr` after a tail `bctr`,
        # 0x802A3220) is covered by that function's verified bytes
        for ad, sz in spans:
            for a2 in range(ad + 4, ad + sz, 4):
                if a2 in tgt and a2 not in got and a2 + tgt[a2] <= ad + sz:
                    got[a2] = tgt[a2]
        print(f"functions ok {tot_ok}/{tot}; library range: {len(got)} of {len(tgt)} functions, {sum(got.values())} of {sum(tgt.values())} bytes verified")
        json.dump(verified, open(os.path.join(ROOT, "lib/verified.json"), "w"), indent=0, sort_keys=True)
        open(os.path.join(ROOT, "lib/status.txt"), "w").write("\n".join(lines) + "\n")
        return
    rc, out = run_one(a.path, a.v)
    print(out)
    sys.exit(rc)


if __name__ == "__main__":
    main()
