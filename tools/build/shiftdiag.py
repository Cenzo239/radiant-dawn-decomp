#!/usr/bin/env python3
"""After a failed link: where do symbols of build/RFEE01/main.elf sit differently from symbols.txt?
Prints, per section, the first symbols whose offset changes (shift runs) and the lib unit owning that address."""
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, "tools/lib"))
sys.path.insert(0, os.path.join(ROOT, "tools/build"))
import place as PL  # noqa: E402

secs, syms, _r = PL.CF.parse_elf(os.path.join(ROOT, "build/RFEE01/main.elf"))
exp = {}
for l in open(os.path.join(ROOT, "config/RFEE01/symbols.txt")):
    m = re.match(r"(\S+) = \.(\w+):(0x\w+);", l)
    if m:
        exp[m[1]] = (m[2], int(m[3], 16))
units = json.load(open(os.path.join(ROOT, "config/RFEE01/units.json")))["units"]


def owner(sec, a):
    for u in units:
        r = u["ranges"].get("." + sec)
        if r and int(r[0], 16) <= a < int(r[1], 16):
            return u["name"]
    return "-"


for sec in ("text", "data", "rodata", "bss", "sdata", "sbss", "sdata2", "extab", "extabindex", "ctors", "dtors"):
    rows = sorted((exp[s["name"]][1], s["value"] - exp[s["name"]][1], s["name"]) for s in syms
                  if s["name"] in exp and s["shndx"] and exp[s["name"]][0] == sec)
    prev, n = None, 0
    for a, d, nm in rows:
        if d != prev:
            if n < 8:
                print(sec, hex(a), hex(d), nm[:60], owner(sec, a))
            n += 1
            prev = d
    if n:
        print(sec, "changes", n)
