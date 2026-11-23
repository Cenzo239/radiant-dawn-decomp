#!/usr/bin/env python3
"""Side-by-side disassembly of one lib function: compiled source vs the game (build/RFEE01/asm).

Usage: tools/lib/fdiff.py <key> <function substring> [-a] [-D define ...] [--src file]
  -a     print all lines (default: only differing lines with 2 lines of context)
  --src  compile another file with the flags of <key> (for experiments)
  --cc GC/3.0a5 | --flag "-schedule off" | --noflag "-ipa file"   compiler / flag experiments
"""
import glob, json, os, re, shlex, subprocess, sys, tempfile
HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
sys.path[:0] = [HERE, os.path.join(HERE, "..")]
import check_func as cf


def norm(l):
    l = re.sub(r"/\*.*?\*/", "", l).strip()
    l = re.sub(r"\.L_[0-9A-Fa-f]+", ".L", l)
    l = re.sub(r"\"[^\"]*\"(@sda21|@ha|@l|@h)?|\b(lbl|fn|jumptable)_[0-9A-Za-z_]+(@sda21|@ha|@l|@h)?", "SYM", l)
    l = re.sub(r"^(bl|b) (?!\.L)\S+", r"\1 SYM", l)
    l = re.sub(r"\b[A-Za-z_]\w*(@sda21|@ha|@l|@h)", "SYM", l)
    return re.sub(r"\s+", " ", l)


def target(addr):
    pat = "/* %08X " % addr
    for f in sorted(glob.glob(os.path.join(ROOT, "build/RFEE01/asm/*.s"))):
        s = open(f).read()
        i = s.find(pat)
        if i < 0:
            continue
        j = s.find(".endfn", i)
        return [l for l in s[i:j].split("\n") if l.strip().startswith("/*")]
    return []


def main():
    args = sys.argv[1:]
    allv = "-a" in args
    if allv: args.remove("-a")
    src = None
    if "--src" in args:
        i = args.index("--src"); src = args[i + 1]; del args[i:i + 2]
    extra = []
    ccov = None
    if "--cc" in args:
        i = args.index("--cc"); ccov = args[i + 1]; del args[i:i + 2]
    drop = []
    while "--noflag" in args:
        i = args.index("--noflag"); drop.append(args[i + 1]); del args[i:i + 2]
    while "--flag" in args:
        i = args.index("--flag"); extra += shlex.split(args[i + 1]); del args[i:i + 2]
    while "-D" in args:
        i = args.index("-D"); extra += ["-D" + args[i + 1]]; del args[i:i + 2]
    key, sub = args[0], args[1]
    MAP = json.load(open(os.path.join(ROOT, "lib/map.json")))
    MAN = json.load(open(os.path.join(ROOT, "lib/manifest.json")))
    man = MAN[key]
    ent = MAP["sources"][key]
    names = [n for n in ent["functions"] if sub in n]
    cc = os.path.join(ROOT, "build/compilers", ccov or man["cc"], "mwcceppc.exe")
    man = dict(man); man["flags"] = [f for f in man["flags"] if f not in drop]
    with tempfile.TemporaryDirectory() as tmp:
        objp = os.path.join(tmp, "out.o")
        cmd = [cf.WIBO, cc, *[x for f in man["flags"] for x in shlex.split(f)], *extra, "-c", src or ("lib/" + key), "-o", objp]
        r = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True)
        if r.returncode != 0 or not os.path.exists(objp):
            print(r.stdout + r.stderr); print("COMPILE FAILED"); return 2
        asmp = os.path.join(tmp, "out.s")
        subprocess.run([os.path.join(ROOT, "build/tools/dtk"), "elf", "disasm", objp, asmp], cwd=ROOT, capture_output=True)
        asm = open(asmp).read()
    for n in names:
        addr = ent["functions"][n][0]
        m = re.search(r"\.fn %s,.*?\n(.*?)\.endfn" % re.escape('"%s"' % n if not re.match(r"^[\w$.]+$", n) else n), asm, re.S)
        if not m:
            m = re.search(r"\.fn \"?%s\"?,.*?\n(.*?)\.endfn" % re.escape(n), asm, re.S)
        if not m:
            print("not found in object:", n); continue
        ours = [l for l in m.group(1).split("\n") if l.strip().startswith("/*")]
        want = target(addr)
        print("== %s at 0x%08X: ours %d, want %d instructions" % (n, addr, len(ours), len(want)))
        import difflib
        A = [norm(l) for l in ours]; B = [norm(l) for l in want]
        rows = []
        for tag, i1, i2, j1, j2 in difflib.SequenceMatcher(None, A, B, autojunk=False).get_opcodes():
            if tag == "equal":
                rows += [(i1 + k, j1 + k, A[i1 + k], B[j1 + k], False) for k in range(i2 - i1)]
            else:
                n = max(i2 - i1, j2 - j1)
                for k in range(n):
                    a = A[i1 + k] if i1 + k < i2 else ""
                    b = B[j1 + k] if j1 + k < j2 else ""
                    rows.append((i1 + k if a else -1, j1 + k if b else -1, a, b, True))
        N = len(rows)
        show = set()
        for x, r in enumerate(rows):
            if r[4] or allv:
                show.update(range(max(0, x - 2), min(N, x + 3)))
        last = -1
        for x, (i, j, a, b, d) in enumerate(rows):
            if x in show:
                if x != last + 1: print("   ...")
                print("%s%4s %4s  %-42s %s" % ("!" if d else " ", "%X" % (i * 4) if i >= 0 else "", "%X" % (j * 4) if j >= 0 else "", a, b)); last = x
    return 0


if __name__ == "__main__":
    sys.exit(main())
