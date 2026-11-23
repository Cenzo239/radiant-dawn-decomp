"""Shared model of main.dol for the build-tree tools: symbols, sections and references.

Reads config/RFEE01/symbols.txt and the dtk disassembly in build/RFEE01/asm (run `ninja` once
so it exists). Every function and data object gets the list of symbols it references
(calls, @ha/@l/@sda21 operands, .4byte pointers in data).
"""
import os
import re
import struct

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
SYMBOLS = os.path.join(ROOT, "config/RFEE01/symbols.txt")
# The analysis uses the names before library renames (gen_config.py keeps them in symbols.base.txt)
if os.path.exists(os.path.join(ROOT, "config/RFEE01/symbols.base.txt")):
    SYMBOLS = os.path.join(ROOT, "config/RFEE01/symbols.base.txt")
ASM_DIR = os.path.join(ROOT, "build/RFEE01/asm")
DOL = os.path.join(ROOT, "orig/RFEE01/sys/main.dol")

GAME_TEXT = (0x800068A0, 0x8028BCD4)   # game code (fn_8028BC54 is the last game __sinit); library from 0x8028BCD4

SECTIONS = {  # name: (start, end)
    ".init": (0x80004000, 0x800064C4), "extab": (0x800064E0, 0x80006658),
    "extabindex": (0x80006660, 0x80006884), ".text": (0x800068A0, 0x803609A0),
    ".ctors": (0x803609A0, 0x80360A80), ".dtors": (0x80360A80, 0x80360A8C),
    ".rodata": (0x80360AA0, 0x80378714), ".data": (0x80378720, 0x803B66F0),
    ".bss": (0x803B6700, 0x804CA024), ".sdata": (0x804CA040, 0x804CB070),
    ".sbss": (0x804CB080, 0x804CCA54), ".sdata2": (0x804CCA60, 0x804D1830),
    ".sbss2": (0x804D1840, 0x804D1858),
}

SYM_RE = re.compile(r"^(\S+) = (\S+):0x([0-9A-Fa-f]+); // (.*)$")


class Sym:
    __slots__ = ("name", "sec", "addr", "size", "type", "attrs", "refs", "refby")

    def __init__(self, name, sec, addr, size, typ, attrs):
        self.name, self.sec, self.addr, self.size, self.type, self.attrs = name, sec, addr, size, typ, attrs
        self.refs = []      # (target name, addend)
        self.refby = set()  # names

    def __repr__(self):
        return f"{self.name}@{self.addr:08X}"


def load_symbols(path=SYMBOLS):
    syms = {}
    for line in open(path):
        m = SYM_RE.match(line.strip())
        if not m:
            continue
        name, sec, addr, rest = m.group(1), m.group(2), int(m.group(3), 16), m.group(4)
        attrs = dict(kv.split(":", 1) for kv in rest.split() if ":" in kv)
        flags = [kv for kv in rest.split() if ":" not in kv]
        size = int(attrs.get("size", "0"), 16)
        s = Sym(name, sec, addr, size, attrs.get("type", "?"), attrs)
        s.attrs["_flags"] = flags
        old = syms.get(name)
        if old is not None and old.addr != addr:
            # same name at two addresses (local symbols of different objects): dtk names the asm symbols
            # Name_<ADDR>; the later one keeps the plain name, the earlier is kept under the dtk name
            old.name = "%s_%08X" % (name, old.addr)
            syms[old.name] = old
        syms[name] = s
    return syms


TOKEN = re.compile(r"[A-Za-z_@.$?][\w@.$?<>:,~*&\-]*")
OPERAND_SYM = re.compile(r"((?:[A-Za-z_@$?][\w@$?.]*))(?:\+(0x[0-9A-Fa-f]+|\d+))?(?:@(?:ha|h|l|sda21))?")


def current_aliases(syms):
    """The dtk asm uses the names of the current symbols.txt (library renames applied);
    map them back to the base names used here."""
    cur = os.path.join(ROOT, "config/RFEE01/symbols.txt")
    if cur == SYMBOLS or not os.path.exists(cur):
        return {}
    by_addr = {}
    for s in syms.values():
        by_addr.setdefault((s.sec, s.addr), s.name)
    out = {}
    for line in open(cur):
        m = SYM_RE.match(line.strip())
        if m and m.group(1) not in syms:
            n = by_addr.get((m.group(2), int(m.group(3), 16)))
            if n:
                out[m.group(1)] = n
    return out


def load_refs(syms, asm_dir=ASM_DIR):
    """Fill .refs/.refby from the dtk asm."""
    alias = current_aliases(syms)
    # dtk appends _<ADDR> to local symbols whose name is not unique (PlayRecordCallback_803213C4)
    _suffix = re.compile(r"^(.*)_([0-9A-F]{8})$")

    def _norm(n):
        n = alias.get(n, n)
        if n not in syms:
            m = _suffix.match(n)
            if m:
                for s_ in (syms.get(m.group(1)),):
                    if s_ is not None and s_.addr == int(m.group(2), 16):
                        return s_.name
        return n
    files = []
    for dp, _dn, fn in os.walk(asm_dir):
        files += [os.path.join(dp, f) for f in fn if f.endswith(".s")]
    for path in files:
        cur = None
        for line in open(path, errors="replace"):
            if line.startswith(".fn ") or line.startswith(".obj "):
                nm = (re.match(r'^\.\w+ ("[^"]*"|[^,\s]+)', line).group(1)).strip('"')
                cur = syms.get(_norm(nm))
                continue
            if line.startswith(".endfn") or line.startswith(".endobj"):
                cur = None
                continue
            if cur is None:
                continue
            if "*/" in line:
                body = line.split("*/", 1)[1]
            else:
                body = line
            body = body.split("#", 1)[0].strip()
            if not body:
                continue
            parts = body.split(None, 1)
            if len(parts) < 2:
                continue
            for tok in re.findall(r'"[^"]*"(?:\+\w+)?(?:@\w+)?|[^,\s()]+', parts[1]):
                tok = tok.replace('"', '')
                if not tok or tok.startswith(".L_") or tok.startswith("0x") or tok[0].isdigit() or tok[0] == "-":
                    continue
                m = re.match(r"^(@?[^+@]+(?:@[^+@]+)*?)(?:\+(0x[0-9A-Fa-f]+|\d+))?(?:@(ha|h|l|sda21))?$", tok)
                if not m:
                    continue
                tname = _norm(m.group(1))
                if tname in syms:
                    add = int(m.group(2), 0) if m.group(2) else 0
                    cur.refs.append((tname, add))
                    syms[tname].refby.add(cur.name)
    return syms


class Dol:
    def __init__(self, path=DOL):
        data = open(path, "rb").read()
        self.data = data
        offs = struct.unpack(">18I", data[0:72])
        addrs = struct.unpack(">18I", data[72:144])
        sizes = struct.unpack(">18I", data[144:216])
        self.segs = [(a, s, o) for o, a, s in zip(offs, addrs, sizes) if s]

    def read(self, addr, size):
        for a, s, o in self.segs:
            if a <= addr and addr + size <= a + s:
                return self.data[o + addr - a:o + addr - a + size]
        if SECTIONS[".bss"][0] <= addr < SECTIONS[".sbss2"][1]:
            return b"\0" * size
        raise KeyError(hex(addr))


def section_of(addr):
    for n, (a, b) in SECTIONS.items():
        if a <= addr < b:
            return n
    return None


def model():
    syms = load_symbols()
    load_refs(syms)
    return syms
