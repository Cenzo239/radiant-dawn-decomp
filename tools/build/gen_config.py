#!/usr/bin/env python3
"""Generate config/RFEE01/splits.txt (and symbol renames in symbols.txt) from the link-unit list.

Inputs
  config/RFEE01/units.json        the link units (written by tools/build/gen_units.py, reviewable)
  config/RFEE01/splits.base.txt   the hand-kept part of splits.txt (header + runtime objects)
  config/RFEE01/symbols.base.txt  symbols.txt before library renames (kept by this script)
Outputs
  config/RFEE01/splits.txt        base + one entry per unit, in address order
  config/RFEE01/symbols.txt       base with the renames of linked library units applied
configure.py reads units.json itself (tools/build/units_config.py) for the Object() entries.

Usage: python3 -I tools/build/gen_config.py [--check]
"""
import argparse
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
CFG = os.path.join(ROOT, "config/RFEE01")
UNITS = os.path.join(CFG, "units.json")
SPLITS_BASE = os.path.join(CFG, "splits.base.txt")
SYMBOLS_BASE = os.path.join(CFG, "symbols.base.txt")
SPLITS = os.path.join(CFG, "splits.txt")
SYMBOLS = os.path.join(CFG, "symbols.txt")
ORDER = [".init", "extab", "extabindex", ".text", ".ctors", ".dtors", ".rodata", ".data", ".bss",
         ".sdata", ".sbss", ".sdata2", ".sbss2"]


def load_units():
    if not os.path.exists(UNITS):
        return []
    return json.load(open(UNITS))["units"]


def parse_splits(text):
    """-> (header, [(name, [section lines])])"""
    lines = text.splitlines()
    k = next(i for i, l in enumerate(lines) if l and not l[0].isspace() and l != "Sections:")
    header = "\n".join(lines[:k]).rstrip() + "\n"
    entries, cur = [], None
    for l in lines[k:]:
        if not l.strip():
            continue
        if not l[0].isspace():
            cur = (l.rstrip(":").split(":")[0] if l.endswith(":") else l, [l], [])
            entries.append(cur)
        else:
            cur[2].append(l)
    return header, entries


def gen_splits(units):
    header, base = parse_splits(open(SPLITS_BASE).read())
    items = []
    for name, head, secs in base:
        start = min((int(m.group(1), 16) for m in (re.search(r"\.text\s+start:0x([0-9A-Fa-f]+)", l) for l in secs) if m),
                    default=0)
        items.append((start, head[0], secs))
    claimed = []
    for u in units:
        secs = []
        for sec in ORDER:
            if sec in u["ranges"]:
                a, b = (int(x, 16) for x in u["ranges"][sec])
                secs.append(f"\t{sec:<11} start:0x{a:08X} end:0x{b:08X}")
                claimed.append((a, b, sec, u["name"]))
        start = int(u["ranges"][".text"][0], 16) if ".text" in u["ranges"] else 0
        items.append((start, u["name"] + ":", secs))
    claimed.sort()
    for x, y in zip(claimed, claimed[1:]):
        if y[0] < x[1]:
            sys.exit(f"overlapping units: {x} and {y}")
    # dtk keeps (and rewrites) splits.txt in address order
    out = [header]
    for start, head, secs in sorted(items, key=lambda t: t[0]):
        out.append("\n" + head + "\n" + "".join(l + "\n" for l in secs))
    return "".join(out)


def base_ranges():
    """[(start, end, object)] of the hand-kept splits (splits.base.txt): no unit may overlap them."""
    _header, base = parse_splits(open(SPLITS_BASE).read())
    out = []
    for name, head, secs in base:
        for l in secs:
            m = re.search(r"start:0x([0-9A-Fa-f]+) end:0x([0-9A-Fa-f]+)", l)
            if m:
                out.append((int(m.group(1), 16), int(m.group(2), 16), name))
    return out


SYM_RE = re.compile(r"^(\S+)( = .*)$")
BASE_RE = re.compile(r"^(\S+) = (\S+):0x([0-9A-Fa-f]+);")


def lib_renames():
    """symbols.txt name -> library name, for every library function/global of lib/map.json whose
    name is unique and whose address starts a symbol (the asm then uses the real names, and
    library objects can be linked against it). Static functions that share a name with another
    (OnReset, ...) keep their fn_ name."""
    m = json.load(open(os.path.join(ROOT, "lib/map.json")))
    by_name = {}
    repos = {}
    for key, src in m["sources"].items():
        for fn, (addr, size, st) in src["functions"].items():
            if st == "ok":
                by_name.setdefault(fn, set()).add(addr)
                repos.setdefault((fn, addr), set()).add(key.split("/")[0])
    for fn, addrs in by_name.items():
        # nw4r/EGG functions the game links twice (the Home Button menu has its own copy of
        # parts of nw4r, wii-ipl/libs/NW4R): the name belongs to the copy of the nw4r library
        # itself (ogws), which the other nw4r objects reference
        if len(addrs) > 1 and re.search(r"Q\d+nw4r|Q\d+3EGG", fn):
            own = [a for a in addrs if "ogws" in repos.get((fn, a), ())]
            if len(own) == 1:
                by_name[fn] = set(own)
    for name, addr in m["symbols"].items():
        by_name.setdefault(name, set()).add(addr)
    base = {}
    names_in_base = {}
    for line in open(SYMBOLS_BASE):
        mm = BASE_RE.match(line)
        if mm:
            a = int(mm.group(3), 16)
            base.setdefault(a, mm.group(1))
            names_in_base.setdefault(mm.group(1), set()).add(a)
    by_addr = {}
    for name, addrs in by_name.items():
        if len(addrs) != 1 or not re.fullmatch(r"[A-Za-z_@$][\w@$<>,:~*&.-]*", name):
            continue
        a = next(iter(addrs))
        by_addr.setdefault(a, set()).add(name)
    out = {}
    for a, names in by_addr.items():
        if len(names) != 1 or a not in base:
            continue
        new = next(iter(names))
        old = base[a]
        if old == new or (new in names_in_base and names_in_base[new] != {a}):
            continue
        if not re.match(r"^(fn|lbl|func)_[0-9A-F]{8}$", old):
            continue
        if 0x800068A0 <= a < 0x8028BCD4 and not re.fullmatch(r"[A-Za-z_]\w*", new):
            # library code inside the game range (e.g. a nw4r thunk at 0x8025F238): game TUs
            # define it under its fn_ name and reach renamed names only through
            # src/tu/lib_aliases.h, which needs a C identifier
            continue
        out[old] = new
    return out


def gen_symbols(units):
    renames = dict(lib_renames())
    for u in units:
        for old, new in u.get("renames", {}).items():
            if old in renames and renames[old] != new and False:
                sys.exit(f"conflicting rename for {old}: {renames[old]} / {new}")
            renames[old] = new
    # MWLD dead-strips functions nothing references; dtk's asm objects keep them, a C object
    # does not. Mark unreferenced functions inside linked units force_active (-> FORCEACTIVE).
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    import dolmodel
    model = dolmodel.model()
    ranges = [tuple(int(x, 16) for x in u["ranges"][".text"]) for u in units if ".text" in u["ranges"]]
    ranges.sort()
    import bisect
    starts = [r[0] for r in ranges]
    force = set()
    for sym in model.values():
        if sym.sec == ".text" and sym.type == "function" and not sym.refby:
            k = bisect.bisect_right(starts, sym.addr) - 1
            if k >= 0 and ranges[k][0] <= sym.addr < ranges[k][1]:
                force.add(sym.name)
    sizes = {}
    for u in units:
        sizes.update(u.get("symbol_sizes", {}))
    taken = set()
    out = []
    for line in open(SYMBOLS_BASE):
        m = SYM_RE.match(line.rstrip("\n"))
        if m and m.group(1) in sizes:
            line = re.sub(r"size:0x[0-9A-Fa-f]+", "size:" + sizes[m.group(1)], line)
            m = SYM_RE.match(line.rstrip("\n"))
        if m and m.group(1) in force and "force_active" not in line:
            line = line.rstrip("\n") + " force_active\n"
        if m and m.group(1) in renames:
            new = renames[m.group(1)]
            line = new + m.group(2) + "\n"
            if new in taken:
                sys.exit(f"duplicate symbol name after renames: {new}")
            taken.add(new)
        out.append(line)
    return "".join(out)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--check", action="store_true", help="only report whether the outputs are up to date")
    a = ap.parse_args()
    for base, cur in ((SPLITS_BASE, SPLITS), (SYMBOLS_BASE, SYMBOLS)):
        if not os.path.exists(base):
            # first run: the current file is the base
            open(base, "w").write(open(cur).read())
    units = load_units()
    splits = gen_splits(units)
    symbols = gen_symbols(units)
    if a.check:
        ok = open(SPLITS).read() == splits and open(SYMBOLS).read() == symbols
        print("up to date" if ok else "outdated")
        return 0 if ok else 1
    open(SPLITS, "w").write(splits)
    open(SYMBOLS, "w").write(symbols)
    print(f"{len(units)} units -> {os.path.relpath(SPLITS, ROOT)}, {os.path.relpath(SYMBOLS, ROOT)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
