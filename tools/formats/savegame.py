#!/usr/bin/env python3
"""Reader for Fire Emblem: Radiant Dawn (RFEE01) Wii save data.

The game keeps two files in its NAND data directory
(Dolphin: Wii/title/00010000/52464545/data/):

  banner.bin    0xF0A0 bytes, standard Wii save banner (magic WIBN)
  FE10_US.dat   0x124000 bytes:
                  0x000000  system block "FE10ASYS"  0x4000
                  0x004000  6 save slots "FE10ADAT"  0x18000 each
                  0x094000  6 suspend slots "FE10ADAT" 0x18000 each

Every block carries a CRC-32 (zlib polynomial, init/xorout 0xFFFFFFFF) at
+0x18, computed over the whole block with the CRC field set to zero.  The
system block also stores the CRC-32 of banner.bin.  Everything is big-endian.
The slot body is a tagged stream (ITBL BMST MDST UNIP SOKO FGPT "T  T" RELD
KZND DEBUG); see docs/formats/save.md for the field list and the evidence.

Library use (Python 3.9, stdlib only):

    import savegame
    data = open("FE10_US.dat", "rb").read()
    info = savegame.parse_file(data)               # dict, JSON-serialisable
    fixed = savegame.fix_checksums(data)           # bytes with CRCs recomputed

CLI:
    python3 savegame.py FE10_US.dat                       # JSON to stdout
    python3 savegame.py FE10_US.dat --headers-only        # skip slot bodies
    python3 savegame.py FE10_US.dat --banner banner.bin   # also check banner CRC
    python3 savegame.py FE10_US.dat --fe10data FE10Data.cms   # exact unit parsing
    python3 savegame.py FE10_US.dat --fix-checksum out.dat
    python3 savegame.py banner.bin
    python3 savegame.py --selftest

Unit records contain an optional support block whose presence depends on the
character's RelianceData entry in FE10Data (not on anything in the save).
With --fe10data the reader decides exactly like the game; without it, it
tries both variants and keeps the one that parses consistently up to the
SOKO marker (reported as "support_mode": "heuristic").
"""
import argparse
import json
import os
import struct
import sys
import zlib

# --------------------------------------------------------------------------
# constants (all from fn_80246E68 / fn_80248154 / fn_802488B8 / fn_80249FF4)

FILE_NAME = "FE10_US.dat"          # lbl_804CAAB8
BANNER_NAME = "banner.bin"         # lbl_804CAAB4
FILE_SIZE = 0x124000
SYS_SIZE = 0x4000
SLOT_SIZE = 0x18000
SLOT_BASE = 0x4000
SUSPEND_BASE = 0x94000
NUM_SLOTS = 6
BANNER_SIZE = 0xF0A0
CRC_OFF = 0x18

SYS_MAGIC = (b"FE10", b"ASYS", 0x20061002)
DAT_MAGIC = (b"FE10", b"ADAT", 0x20060920)
SYS_REV = 7
DAT_REV = 0x11

TIMEBASE_HZ = 243000000 // 4       # OSGetTime ticks per second on Wii
NUM_UNITS = 0xFE                   # fn_8012D38C
CONVOY_SLOTS = 300                 # lbl_804CB750 (fn_801059EC)
PENDING_SLOTS = 0x10               # lbl_803E9000
SECTION_TAGS = [b"ITBL", b"BMST", b"MDST", b"UNIP", b"SOKO", b"FGPT",
                b"T  T", b"RELD", b"KZND", b"DEBUG"[:4]]
WEAPON_TYPES = ["sword", "lance", "axe", "bow", "knife", "strike", "fire",
                "thunder", "wind", "light", "dark", "staff"]
STATS8 = ["hp", "str", "mag", "skl", "spd", "lck", "def", "res"]
ITBL_NAMES = ["pid", "jid", "iid", "sid", "atkseq", "movseq", "healseq",
              "mtype"]
ITBL_PREFIX = ["PID_", "JID_", "IID_", "SID_", "SEQ_", "SEQ_", "SEQ_",
               "MTYPE_"]


def crc32_block(block):
    """CRC-32 of a system/slot block with the CRC field (+0x18) zeroed."""
    b = bytearray(block)
    b[CRC_OFF:CRC_OFF + 4] = b"\0\0\0\0"
    return zlib.crc32(bytes(b)) & 0xFFFFFFFF


def ticks_to_seconds(t):
    return round(t / TIMEBASE_HZ, 3)


# --------------------------------------------------------------------------
# big-endian stream (mirrors fn_8008A1A0.. / fn_8008A5AC..)

class R:
    def __init__(self, buf, off=0):
        self.b = buf
        self.o = off

    def _take(self, n):
        if self.o + n > len(self.b):
            raise ValueError("read past end at 0x%x" % self.o)
        v = self.b[self.o:self.o + n]
        self.o += n
        return v

    def u8(self):
        return self._take(1)[0]

    def s8(self):
        v = self.u8()
        return v - 256 if v >= 128 else v

    def u16(self):
        return struct.unpack(">H", self._take(2))[0]

    def s16(self):
        return struct.unpack(">h", self._take(2))[0]

    def u32(self):
        return struct.unpack(">I", self._take(4))[0]

    def f32(self):
        return struct.unpack(">f", self._take(4))[0]

    def u64(self):
        return struct.unpack(">Q", self._take(8))[0]

    def raw(self, n):
        return bytes(self._take(n))

    def cstr(self):
        e = self.b.index(b"\0", self.o)
        s = self.b[self.o:e]
        self.o = e + 1
        return s.decode("shift_jis", "replace")

    def tag(self, t):
        got = self.raw(4)
        if got != t:
            raise ValueError("expected tag %r at 0x%x, got %r"
                             % (t, self.o - 4, got))


class W:
    def __init__(self):
        self.b = bytearray()

    def u8(self, v):
        self.b += struct.pack(">B", v & 0xFF)

    s8 = u8

    def u16(self, v):
        self.b += struct.pack(">H", v & 0xFFFF)

    s16 = u16

    def u32(self, v):
        self.b += struct.pack(">I", v & 0xFFFFFFFF)

    def f32(self, v):
        self.b += struct.pack(">f", v)

    def u64(self, v):
        self.b += struct.pack(">Q", v)

    def raw(self, v):
        self.b += bytes(v)

    def cstr(self, s):
        self.b += s.encode("shift_jis") + b"\0"

    def tag(self, t):
        self.b += t


# Field specs: (name, kind[, n]).  kind: u8 s8 u16 s16 u32 u64 raw(n)
# list-u8/u16/u32/s8 (n elements).  Raw fields are hex strings in the output.

def read_spec(r, spec):
    d = {}
    for f in spec:
        name, kind = f[0], f[1]
        if kind == "raw":
            d[name] = r.raw(f[2]).hex()
        elif kind.startswith("list-"):
            k = kind[5:]
            d[name] = [getattr(r, k)() for _ in range(f[2])]
        else:
            d[name] = getattr(r, kind)()
    return d


def write_spec(w, spec, d):
    for f in spec:
        name, kind = f[0], f[1]
        v = d[name]
        if kind == "raw":
            b = bytes.fromhex(v)
            if len(b) != f[2]:
                raise ValueError("%s: need %d bytes" % (name, f[2]))
            w.raw(b)
        elif kind.startswith("list-"):
            k = kind[5:]
            if len(v) != f[2]:
                raise ValueError("%s: need %d values" % (name, f[2]))
            for x in v:
                getattr(w, k)(x)
        else:
            getattr(w, kind)(v)


def spec_size(spec):
    n = 0
    for f in spec:
        k = f[1]
        if k == "raw":
            n += f[2]
        elif k.startswith("list-"):
            n += f[2] * {"u8": 1, "s8": 1, "u16": 2, "s16": 2, "u32": 4}[k[5:]]
        else:
            n += {"u8": 1, "s8": 1, "u16": 2, "s16": 2, "u32": 4, "u64": 8}[k]
    return n


# --------------------------------------------------------------------------
# system block "FE10ASYS" (fn_80245888 write / fn_80245A74 read)

CLEAR_RECORD = [                  # 0x18 bytes, fn_80245614
    ("playthrough_id", "u64"),    # slot header +0x10
    ("difficulty", "s8"),         # slot header +0x35; < 0 = empty record
    ("playthrough_no", "u8"),     # slot header +0x34
    ("pid_index", "u16"),
    ("total_turns", "u32"),
    ("total_seconds", "u64"),
]

SYS_SPEC = [
    ("magic", "raw", 4), ("kind", "raw", 4), ("version", "u32"),
    ("rev", "u32"), ("created_ticks", "u64"), ("crc32", "u32"),
    ("flags_1c", "raw", 8),        # bitset object +0x1c (clear flags at bits 0-4)
    ("bits_24", "raw", 16),        # bitset object +0x28
    ("name_flags", "raw", 0x60),   # 768 named flags (+0x183c)
    ("bits_94", "raw", 16), ("bits_a4", "raw", 16),
    ("bits_b4", "raw", 8), ("bits_bc", "raw", 8), ("bits_c4", "raw", 8),
    ("u16_cc", "list-u16", 8),
]
SYS_SPEC_TAIL = [
    ("u8_3ac", "u8"), ("last_slot", "u8"), ("raw_3ae", "raw", 2),
    ("banner_crc32", "u32"),
]
SYS_DATA_SIZE = spec_size(SYS_SPEC) + 30 * 0x18 + spec_size(SYS_SPEC_TAIL)


def parse_system(block):
    r = R(block)
    d = read_spec(r, SYS_SPEC)
    d["clear_records"] = []
    for i in range(30):
        rec = read_spec(r, CLEAR_RECORD)
        if rec["difficulty"] >= 0:
            rec["index"] = i
            d["clear_records"].append(rec)
    d.update(read_spec(r, SYS_SPEC_TAIL))
    d["magic"] = bytes.fromhex(d["magic"]).decode("latin-1")
    d["kind"] = bytes.fromhex(d["kind"]).decode("latin-1")
    d["valid_magic"] = (d["magic"], d["kind"], d["version"]) == (
        SYS_MAGIC[0].decode(), SYS_MAGIC[1].decode(), SYS_MAGIC[2])
    d["crc32_calc"] = crc32_block(block)
    d["crc_ok"] = d["crc32_calc"] == d["crc32"]
    flags = struct.unpack(">I", bytes.fromhex(d["flags_1c"])[:4])[0]
    d["cleared_difficulty_bits"] = {"diff0": bool(flags & 2),
                                    "diff1": bool(flags & 4),
                                    "diff2": bool(flags & 8),
                                    "diff3": bool(flags & 1)}
    d["por_transfer_flag"] = bool(flags & 0x10)
    return d


def build_system(d):
    w = W()
    dd = dict(d)
    dd["magic"] = SYS_MAGIC[0].hex()
    dd["kind"] = SYS_MAGIC[1].hex()
    write_spec(w, SYS_SPEC, dd)
    recs = {r.get("index", i): r for i, r in enumerate(d["clear_records"])}
    for i in range(30):
        r = recs.get(i)
        if r is None:
            r = {"playthrough_id": 0, "difficulty": -1, "playthrough_no": 0,
                 "pid_index": 0, "total_turns": 0, "total_seconds": 0}
        write_spec(w, CLEAR_RECORD, r)
    write_spec(w, SYS_SPEC_TAIL, d)
    b = bytes(w.b) + b"\xff" * (SYS_SIZE - len(w.b))
    return set_crc(b)


def set_crc(block):
    b = bytearray(block)
    struct.pack_into(">I", b, CRC_OFF, crc32_block(b))
    return bytes(b)


# --------------------------------------------------------------------------
# slot header (fn_80245E44 write / fn_80245F9C read), 0x1060 bytes

OPTIONS_SPEC = [                   # fn_8010940C, defaults fn_801095FC
    ("option_bits", "raw", 8), ("u8_08", "u8"), ("u8_09", "u8"),
    ("u8_0a", "u8"), ("u8_0b", "u8"), ("u8_0c", "u8"),
    ("levels_0d", "list-u8", 4),   # defaults 100 (volumes?)
    ("difficulty", "u8"),          # +0x11, mirror of header +0x35
    ("u16_12", "u16"), ("u32_14", "u32"), ("u32_18", "u32"), ("u32_1c", "u32"),
]

SLOT_HEADER_SPEC = [
    ("magic", "raw", 4), ("kind", "raw", 4), ("version", "u32"),
    ("rev", "u32"),
    ("playthrough_id", "u64"),     # OSGetTime when the game was started
    ("crc32", "u32"),
    ("save_count", "u32"),
    ("saved_ticks", "u64"),        # OSGetTime of this save
    ("playtime_ticks", "u64"),     # game state +0xa0
    ("slot", "u8"), ("is_suspend", "u8"), ("suspend_origin", "u8"),
    ("u8_33", "u8"), ("playthrough_no", "u8"), ("difficulty", "u8"),
    ("chapter", "u8"),             # game state +0x10 (ChapterData index)
    ("mode_37", "u8"),             # game state +0x9c, 8 for suspend saves
    ("turn", "u16"),               # game state +0x12
    ("u16_3a", "u16"),
    ("flags_3c", "u32"),           # bit 0: PoR transfer block present
]


def read_slot_header(r):
    d = read_spec(r, SLOT_HEADER_SPEC)
    d["options"] = read_spec(r, OPTIONS_SPEC)
    blk = r.raw(0x1000)
    d["por_transfer"] = blk.hex() if any(blk) else None
    d["magic"] = bytes.fromhex(d["magic"]).decode("latin-1")
    d["kind"] = bytes.fromhex(d["kind"]).decode("latin-1")
    d["playtime_seconds"] = ticks_to_seconds(d["playtime_ticks"])
    return d


def write_slot_header(w, d):
    dd = dict(d)
    dd["magic"] = DAT_MAGIC[0].hex()
    dd["kind"] = DAT_MAGIC[1].hex()
    write_spec(w, SLOT_HEADER_SPEC, dd)
    write_spec(w, OPTIONS_SPEC, d["options"])
    blk = bytes.fromhex(d["por_transfer"]) if d.get("por_transfer") else b""
    w.raw(blk + b"\0" * (0x1000 - len(blk)))


# --------------------------------------------------------------------------
# ITBL: ID string tables (fn_80242920 write / fn_80242BB0 read)

def read_itbl(r):
    t = {}
    for name in ITBL_NAMES:
        n = r.u32()
        if n > 0x4000:
            raise ValueError("ITBL %s count %d implausible" % (name, n))
        t[name] = [r.cstr() for _ in range(n)]
    return t


def write_itbl(w, t):
    for name in ITBL_NAMES:
        w.u32(len(t[name]))
        for s in t[name]:
            w.cstr(s)


def _name(itbl, table, idx, one_based):
    lst = itbl.get(table, []) if itbl else []
    i = idx - 1 if one_based else idx
    if 0 <= i < len(lst):
        return ITBL_PREFIX[ITBL_NAMES.index(table)] + lst[i]
    return None


# --------------------------------------------------------------------------
# BMST: global game state lbl_803CAB38 (fn_80062AE8 / fn_80062DE0)

CHAPTER_RECORD = [                 # 0x10 bytes, fn_80060580
    ("chapter", "u8"), ("kind", "u8"), ("turns", "u16"),
    ("seconds", "u32"), ("pid_index", "u16"), ("u16_0a", "u16"),
    ("value_0c", "u32"),           # game state +0xbc at chapter end
]

BMST_SPEC_A = [
    ("raw_00", "raw", 16), ("chapter", "u8"), ("u8_11", "u8"),
    ("turn", "u16"), ("bytes_14", "list-u8", 4),
    # per army (index = chapter record +0x89: 0, 1, 2): gold, capped at
    # 9,999,999 (fn_800615DC set / fn_800626E0 get), and bonus EXP as f32
    # (fn_80062780 / fn_80062850 get). Confirmed with real saves.
    ("gold", "list-u32", 3), ("bonus_exp", "list-f32", 3),
    ("raw_30", "raw", 0x24), ("raw_54", "raw", 0x3c),
    ("u8_90", "u8"), ("u8_91", "u8"), ("u8_92", "u8"),
    ("raw_94", "raw", 6),
    ("u8_9a", "u8"), ("u8_9b", "u8"),   # written from floats +0x934/+0x938
    ("u8_9c", "u8"), ("u8_9d", "u8"), ("u8_9e", "u8"),
    ("playthrough_no", "u8"),       # +0x9f
    ("playtime_ticks", "u64"),      # +0xa0
    ("chapter_ticks", "u64"),       # +0xa8
    ("gold_gained_total", "u32"), ("gold_spent_total", "u32"),  # fn_800615DC
    ("u16_b8", "u16"), ("u16_ba", "u16"),
    ("u32_bc", "u32"),
    # units defeated per force (0 player .. 3), this chapter / whole game
    # (incremented at unit death, 0x80028000 battle code)
    ("defeated_chapter", "list-u16", 4), ("defeated_total", "list-u32", 4),
    ("flags_d8", "raw", 16), ("flags_ec", "raw", 16),
]
UNITREF = [("unit", "u8"), ("b1", "u8"), ("b2", "u8"), ("b3", "u8"),
           ("b4", "u8")]               # fn_8010E890


def read_bmst(r):
    d = read_spec(r, BMST_SPEC_A)
    d["unitref_134"] = read_spec(r, UNITREF)
    d["unitref_13c"] = read_spec(r, UNITREF)
    d["bits_544"] = r.raw(16).hex()
    d["chapter_history"] = [read_spec(r, CHAPTER_RECORD) for _ in range(60)]
    d["raw_914"] = r.raw(0x18).hex()
    n = r.u8()
    d["pairs_955"] = [[r.u8(), r.u8()] for _ in range(n)]
    d["flags_100"] = r.raw(0x30).hex()
    return d


def write_bmst(w, d):
    write_spec(w, BMST_SPEC_A, d)
    write_spec(w, UNITREF, d["unitref_134"])
    write_spec(w, UNITREF, d["unitref_13c"])
    w.raw(bytes.fromhex(d["bits_544"]))
    for rec in d["chapter_history"]:
        write_spec(w, CHAPTER_RECORD, rec)
    w.raw(bytes.fromhex(d["raw_914"]))
    w.u8(len(d["pairs_955"]))
    for a, b in d["pairs_955"]:
        w.u8(a)
        w.u8(b)
    w.raw(bytes.fromhex(d["flags_100"]))


# --------------------------------------------------------------------------
# MDST (fn_8013498C / fn_80134B80), sub-version byte 4

MDST_SPEC = [
    ("version", "u8"), ("phase_830", "u8"), ("bytes_839", "list-u8", 6),
    ("bytes_834", "list-u8", 4), ("triples", "list-u8", 24),
    ("u16_840", "list-u16", 3), ("s8_846", "s8"),
    ("u16_848", "u16"), ("u16_84a", "u16"), ("u8_838", "u8"),
    ("bytes_84c", "list-u8", 3),
]


# --------------------------------------------------------------------------
# items (fn_80111D68 write / fn_80111E48 read)

def read_item(r, itbl=None, strict=False):
    iid = r.u16()
    w2 = r.u16()
    if iid == 0:
        return None
    if strict and itbl and iid > len(itbl["iid"]):
        raise ValueError("item index %d" % iid)
    it = {"iid_index": iid, "uses": w2 >> 8, "flags": w2 & 0xFF}
    n = _name(itbl, "iid", iid, True)
    if n:
        it["iid"] = n
    if w2 & 0x20:                  # forged weapon
        s = r.cstr()
        if strict and len(s.encode("shift_jis")) > 0x17:
            raise ValueError("forge name too long")
        it["forge_name"] = s
        it["forge"] = {"mt": r.s8(), "hit": r.s8(), "crit": r.s8(),
                       "wt": r.s8()}
        it["forge_color"] = r.raw(4).hex()
    return it


def write_item(w, it):
    if it is None:
        w.u32(0)
        return
    w.u16(it["iid_index"])
    w.u16((it["uses"] << 8) | it["flags"])
    if it["flags"] & 0x20:
        w.cstr(it["forge_name"])
        for k in ("mt", "hit", "crit", "wt"):
            w.s8(it["forge"][k])
        w.raw(bytes.fromhex(it["forge_color"]))


# --------------------------------------------------------------------------
# UNIP: 254 unit records (fn_8012D38C / fn_80121700 write,
# fn_8012D3EC / fn_80121A28 read)

UNIT_A = [
    ("force", "u8"),               # index into the 11 force lists (0 = player?)
    ("rescue_e4", "u8"), ("link_e8", "u8"), ("link_f8", "u8"),  # unit no.
    ("group_fd", "u8"),            # GroupData index (fn_8010B180)
    ("level", "s8"),               # +0xfe
    ("exp", "u8"),                 # +0xff, 0..99, 0xff = none
    ("u8_100", "u8"), ("u8_101", "u8"),
    ("x", "u8"), ("y", "u8"),      # +0x102/+0x103
    ("flags_108", "u32"), ("flags_10c", "u32"),
    ("raw_110", "raw", 4),
    ("hp", "u8"),                  # +0x114 current HP
    ("u8_115", "u8"),
    ("move_bonus", "s8"),          # +0x116
    ("stat_gain", "list-s8", 8),   # +0x119, added to class + personal base
    ("raw_121", "raw", 8),
]
UNIT_B = [("u8_378", "u8"), ("u8_379", "u8"), ("u16_37a", "u16"),
          ("u16_37c", "u16")]
UNIT_AI = [                        # fn_80129650 / fn_8012978C
    ("atkseq", "u8"), ("movseq1", "u8"), ("movseq2", "u8"),
    ("healseq", "u8"), ("mtype", "u8"), ("ai_flags_3b0", "list-u8", 4),
    ("ai_u32_3b4", "u32"), ("ai_u16_3b8", "u16"), ("ai_u8_3ba", "u8"),
    ("ai_u8_3bc", "u8"), ("ai_u8_3a8", "u8"), ("ai_u16_3be", "u16"),
    ("ai_pad", "u16"),
]
UNIT_C = [("u16_c4", "u16"), ("pad_c4", "u16"),     # fn_800FB2B8
          ("u8_117", "u8"), ("u8_118", "u8"), ("u16_37e", "u16"),
          ("u8_380", "u8")]
BATTLE_REC = [("u16_382", "list-u16", 6), ("u8_38e", "u8"),
              ("u8_38f", "u8")]   # fn_80106CA8


def read_unit(r, itbl=None, support=False, strict=False):
    pid = r.u16()
    if pid == 0:
        return None
    if strict and itbl and pid > len(itbl["pid"]):
        raise ValueError("pid index %d" % pid)
    u = {"pid_index": pid}
    n = _name(itbl, "pid", pid, True)
    if n:
        u["pid"] = n
    u["jid_index"] = r.u16()
    if strict and itbl and not 0 < u["jid_index"] <= len(itbl["jid"]):
        raise ValueError("jid index %d" % u["jid_index"])
    n = _name(itbl, "jid", u["jid_index"], True)
    if n:
        u["jid"] = n
    u.update(read_spec(r, UNIT_A))
    if strict and (u["force"] > 10 or max(u["rescue_e4"], u["link_e8"],
                                          u["link_f8"]) > NUM_UNITS):
        raise ValueError("bad force/link")
    u["stats_relative"] = dict(zip(STATS8, u.pop("stat_gain")))
    cnt = r.u8()
    if strict and cnt > 18:
        raise ValueError("skill count %d" % cnt)
    skills = []
    for _ in range(cnt):
        sid = r.u16()
        s = {"sid_index": sid, "b4": r.u8(), "b5": r.u8()}
        if strict and itbl and sid != 0xFFFF and sid >= len(itbl["sid"]):
            raise ValueError("sid index %d" % sid)
        n = _name(itbl, "sid", sid, False)
        if n:
            s["sid"] = n
        skills.append(s)
    u["skills"] = skills
    u["items"] = [read_item(r, itbl, strict) for _ in range(7)]
    u["weapon_exp"] = dict(zip(WEAPON_TYPES, [r.u16() for _ in range(12)]))
    u["battle_rec"] = read_spec(r, BATTLE_REC)
    if support:
        sp = {"bits_2ec": r.raw(12).hex(), "partner_pid_index": r.u16()}
        k = r.u8()
        if strict and not 0 < k <= 0x48:
            raise ValueError("support count %d" % k)
        sp["points"] = list(r.raw(k))
        sp["bits_348"] = r.raw(12).hex()
        sp["bits_358"] = r.raw(12).hex()
        sp["bits_368"] = r.raw(12).hex()
        n = _name(itbl, "pid", sp["partner_pid_index"], True)
        if n:
            sp["partner_pid"] = n
        u["support"] = sp
    else:
        u["support"] = None
    u.update(read_spec(r, UNIT_B))
    ai = read_spec(r, UNIT_AI)
    if strict and itbl:
        for key, tab in (("atkseq", "atkseq"), ("movseq1", "movseq"),
                         ("movseq2", "movseq"), ("healseq", "healseq"),
                         ("mtype", "mtype")):
            if itbl[tab] and ai[key] >= len(itbl[tab]):
                raise ValueError("ai index")
        if ai["ai_pad"] != 0:
            raise ValueError("ai pad")
    u["ai"] = ai
    u.update(read_spec(r, UNIT_C))
    if strict and u["pad_c4"] != 0:
        raise ValueError("pad")
    return u


def write_unit(w, u):
    if u is None:
        w.u16(0)
        return
    w.u16(u["pid_index"])
    w.u16(u["jid_index"])
    d = dict(u)
    d["stat_gain"] = [u["stats_relative"][k] for k in STATS8]
    write_spec(w, UNIT_A, d)
    w.u8(len(u["skills"]))
    for s in u["skills"]:
        w.u16(s["sid_index"])
        w.u8(s["b4"])
        w.u8(s["b5"])
    for it in u["items"]:
        write_item(w, it)
    for k in WEAPON_TYPES:
        w.u16(u["weapon_exp"][k])
    write_spec(w, BATTLE_REC, u["battle_rec"])
    sp = u["support"]
    if sp is not None:
        w.raw(bytes.fromhex(sp["bits_2ec"]))
        w.u16(sp["partner_pid_index"])
        w.u8(len(sp["points"]))
        w.raw(bytes(sp["points"]))
        for k in ("bits_348", "bits_358", "bits_368"):
            w.raw(bytes.fromhex(sp[k]))
    write_spec(w, UNIT_B, u)
    write_spec(w, UNIT_AI, u["ai"])
    write_spec(w, UNIT_C, u)


def read_units(r, itbl, reliance=None):
    """Return (units, mode).  reliance: set of PID strings with supports."""
    if reliance is not None:
        units = []
        for i in range(NUM_UNITS):
            o = r.o
            pid = struct.unpack_from(">H", r.b, o)[0]
            name = _name(itbl, "pid", pid, True)
            units.append(read_unit(r, itbl, name in reliance))
        return units, "fe10data"
    # heuristic: depth-first over both variants, memoised on offset
    sys.setrecursionlimit(max(4000, sys.getrecursionlimit()))
    dead = set()

    def go(i, off):
        if i == NUM_UNITS:
            return [] if r.b[off:off + 4] == b"SOKO" else None
        if (i, off) in dead:
            return None
        pid = struct.unpack_from(">H", r.b, off)[0]
        variants = (False,) if pid == 0 else (False, True)
        for sup in variants:
            rr = R(r.b, off)
            try:
                u = read_unit(rr, itbl, sup, strict=True)
            except (ValueError, IndexError, UnicodeError):
                continue
            rest = go(i + 1, rr.o)
            if rest is not None:
                return [(u, rr.o)] + rest
        dead.add((i, off))
        return None

    res = go(0, r.o)
    if res is None:
        raise ValueError("could not parse UNIP (try --fe10data)")
    r.o = res[-1][1] if res else r.o
    return [u for u, _ in res], "heuristic"


# --------------------------------------------------------------------------
# remaining sections

TT_ENTRY = [("x", "u8"), ("y", "u8"), ("kind", "u8"), ("b3", "u8"),
            ("bytes_4", "list-u8", 4)]


def read_slot_body(r, reliance=None):
    out = {}
    r.tag(b"ITBL")
    itbl = read_itbl(r)
    out["itbl_counts"] = {k: len(v) for k, v in itbl.items()}
    out["itbl"] = itbl
    r.tag(b"BMST")
    out["game"] = read_bmst(r)
    r.tag(b"MDST")
    out["mdst"] = read_spec(r, MDST_SPEC)
    r.tag(b"UNIP")
    units, mode = read_units(r, itbl, reliance)
    out["support_mode"] = mode
    out["units"] = [dict(u, unit_no=i + 1) for i, u in enumerate(units)
                    if u is not None]
    r.tag(b"SOKO")
    conv = [read_item(r, itbl) for _ in range(CONVOY_SLOTS)]
    out["convoy"] = [dict(it, slot=i) for i, it in enumerate(conv) if it]
    pend = [read_item(r, itbl) for _ in range(PENDING_SLOTS)]
    out["pending_items"] = [dict(it, slot=i) for i, it in enumerate(pend)
                            if it]
    r.tag(b"FGPT")
    out["fgpt"] = [r.s16() for _ in range(6)]
    r.tag(b"T  T")
    ents = [read_spec(r, TT_ENTRY) for _ in range(0x80)]
    cnt = r.u32()
    out["tile_table"] = {"count": cnt, "entries": ents[:min(cnt, 0x80)],
                         "raw_200": r.raw(0x200).hex(), "u32_tail": r.u32()}
    r.tag(b"RELD")
    n = r.u32()
    out["supports"] = [{"a": r.u16(), "b": r.u16(), "level": r.u8()}
                       for _ in range(n)]
    for s in out["supports"]:
        s["a_pid"] = _name(itbl, "pid", s["a"], True)
        s["b_pid"] = _name(itbl, "pid", s["b"], True)
    r.tag(b"KZND")
    n = r.u32()
    out["bonds"] = [{"a": r.u16(), "b": r.u16(), "v0": r.u8(), "v1": r.u8()}
                    for _ in range(n)]
    r.tag(b"DEBU")                 # "DEBUG" string, only 4 bytes written
    out["debug"] = r.raw(8).hex()
    out["body_end"] = r.o
    return out


def write_slot_body(w, d):
    w.tag(b"ITBL")
    write_itbl(w, d["itbl"])
    w.tag(b"BMST")
    write_bmst(w, d["game"])
    w.tag(b"MDST")
    write_spec(w, MDST_SPEC, d["mdst"])
    w.tag(b"UNIP")
    byno = {u["unit_no"]: u for u in d["units"]}
    for i in range(NUM_UNITS):
        write_unit(w, byno.get(i + 1))
    w.tag(b"SOKO")
    conv = {it["slot"]: it for it in d["convoy"]}
    for i in range(CONVOY_SLOTS):
        write_item(w, conv.get(i))
    pend = {it["slot"]: it for it in d["pending_items"]}
    for i in range(PENDING_SLOTS):
        write_item(w, pend.get(i))
    w.tag(b"FGPT")
    for v in d["fgpt"]:
        w.s16(v)
    w.tag(b"T  T")
    t = d["tile_table"]
    for i in range(0x80):
        e = t["entries"][i] if i < len(t["entries"]) else {
            "x": 0, "y": 0, "kind": 0, "b3": 0, "bytes_4": [0, 0, 0, 0]}
        write_spec(w, TT_ENTRY, e)
    w.u32(t["count"])
    w.raw(bytes.fromhex(t["raw_200"]))
    w.u32(t["u32_tail"])
    w.tag(b"RELD")
    w.u32(len(d["supports"]))
    for s in d["supports"]:
        w.u16(s["a"])
        w.u16(s["b"])
        w.u8(s["level"])
    w.tag(b"KZND")
    w.u32(len(d["bonds"]))
    for s in d["bonds"]:
        w.u16(s["a"])
        w.u16(s["b"])
        w.u8(s["v0"])
        w.u8(s["v1"])
    w.tag(b"DEBU")                 # fn_8008A820 copies 4 bytes of "DEBUG"
    w.raw(bytes.fromhex(d["debug"]))


# --------------------------------------------------------------------------
# slots and whole file

def is_empty(block):
    return block[:8] != b"FE10ADAT"


def parse_slot(block, headers_only=False, reliance=None):
    r = R(block)
    h = read_slot_header(r)
    h["crc32_calc"] = crc32_block(block)
    h["crc_ok"] = h["crc32_calc"] == h["crc32"]
    h["valid_magic"] = (h["kind"] == "ADAT" and h["version"] == DAT_MAGIC[2])
    out = {"header": h}
    if headers_only:
        return out
    if h["rev"] != DAT_REV:
        out["body_error"] = "rev %d not supported (only 0x11)" % h["rev"]
        return out
    try:
        out.update(read_slot_body(r, reliance))
        rest = block[out["body_end"]:]
        out["tail_is_ff"] = all(c == 0xFF for c in rest)
    except (ValueError, IndexError) as e:
        out["body_error"] = str(e)
    return out


def build_slot(d):
    w = W()
    write_slot_header(w, d["header"])
    write_slot_body(w, d)
    if len(w.b) > SLOT_SIZE:
        raise ValueError("slot body too large (0x%x)" % len(w.b))
    return set_crc(bytes(w.b) + b"\xff" * (SLOT_SIZE - len(w.b)))


def parse_banner(b):
    if len(b) < 0xA0 or b[:4] != b"WIBN":
        raise ValueError("not a Wii banner (WIBN)")
    flags, speed = struct.unpack_from(">IH", b, 4)
    title = b[0x20:0x60].decode("utf-16-be").split("\0")[0]
    sub = b[0x60:0xA0].decode("utf-16-be").split("\0")[0]
    return {"size": len(b), "flags": flags,
            "icon_speed": [(speed >> (2 * i)) & 3 for i in range(8)],
            "title": title, "subtitle": sub,
            "crc32": zlib.crc32(bytes(b)) & 0xFFFFFFFF}


def parse_file(data, headers_only=False, reliance=None, banner=None):
    if data[:4] == b"WIBN":
        return {"banner": parse_banner(data)}
    if data[:8] == b"FE10ADAT":          # single slot dump
        return {"slot": parse_slot(data[:SLOT_SIZE], headers_only, reliance)}
    if len(data) != FILE_SIZE:
        raise ValueError("size 0x%x, expected 0x%x" % (len(data), FILE_SIZE))
    out = {"file": FILE_NAME, "size": len(data),
           "system": parse_system(data[:SYS_SIZE])}
    if banner is not None:
        bi = parse_banner(banner)
        bi["matches_system"] = bi["crc32"] == out["system"]["banner_crc32"]
        out["banner"] = bi
    for kind, base in (("saves", SLOT_BASE), ("suspends", SUSPEND_BASE)):
        lst = []
        for i in range(NUM_SLOTS):
            blk = data[base + i * SLOT_SIZE:base + (i + 1) * SLOT_SIZE]
            if is_empty(blk):
                lst.append({"index": i, "empty": True})
            else:
                s = parse_slot(blk, headers_only, reliance)
                s["index"] = i
                lst.append(s)
        out[kind] = lst
    return out


def fix_checksums(data):
    """Recompute the CRC of the system block and of every used slot."""
    b = bytearray(data)
    if b[:4] == b"WIBN":
        return bytes(b)
    if b[:8] == b"FE10ADAT":
        b[:SLOT_SIZE] = set_crc(b[:SLOT_SIZE])
        return bytes(b)
    if b[:8] == b"FE10ASYS":
        b[:SYS_SIZE] = set_crc(b[:SYS_SIZE])
    for base in (SLOT_BASE, SUSPEND_BASE):
        for i in range(NUM_SLOTS):
            o = base + i * SLOT_SIZE
            if not is_empty(b[o:o + SLOT_SIZE]):
                b[o:o + SLOT_SIZE] = set_crc(b[o:o + SLOT_SIZE])
    return bytes(b)


def load_reliance(path):
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    import fe10data
    db = fe10data.load(path)
    return {rec["pid"] for rec in fe10data.parse_reliance(db)}


# --------------------------------------------------------------------------
# self test

def _sample_unit(no, pid, jid, sup):
    return {
        "unit_no": no, "pid_index": pid, "jid_index": jid,
        "force": 0, "rescue_e4": 0, "link_e8": 0, "link_f8": 0,
        "group_fd": 1, "level": 11, "exp": 42, "u8_100": 30, "u8_101": 0,
        "x": 5, "y": 7, "flags_108": 0x10, "flags_10c": 0,
        "raw_110": "00000000", "hp": 44, "u8_115": 0, "move_bonus": 0,
        "stats_relative": dict(zip(STATS8, [3, 2, 0, 1, 4, -1, 2, 0])),
        "raw_121": "00" * 8,
        "skills": [{"sid_index": 2, "b4": 1, "b5": 0}],
        "items": [{"iid_index": 1, "uses": 40, "flags": 0},
                  {"iid_index": 2, "uses": 30, "flags": 0x20,
                   "forge_name": "Test Blade",
                   "forge": {"mt": 3, "hit": 10, "crit": 5, "wt": -1},
                   "forge_color": "808080ff"},
                  None, None, None, None, None],
        "weapon_exp": dict(zip(WEAPON_TYPES, [181] + [0] * 11)),
        "battle_rec": {"u16_382": [1, 2, 3, 4, 5, 6], "u8_38e": 0,
                       "u8_38f": 0},
        "support": ({"bits_2ec": "00" * 12, "partner_pid_index": 2,
                     "points": [0, 55, 12], "bits_348": "00" * 12,
                     "bits_358": "00" * 12, "bits_368": "00" * 12}
                    if sup else None),
        "u8_378": 0xFF, "u8_379": 0xFF, "u16_37a": 0xFFFF, "u16_37c": 0,
        "ai": {"atkseq": 0, "movseq1": 0, "movseq2": 1, "healseq": 0,
               "mtype": 0, "ai_flags_3b0": [0, 0, 0, 0], "ai_u32_3b4": 0,
               "ai_u16_3b8": 0, "ai_u8_3ba": 0, "ai_u8_3bc": 0,
               "ai_u8_3a8": 0, "ai_u16_3be": 0, "ai_pad": 0},
        "u16_c4": 0, "pad_c4": 0, "u8_117": 0, "u8_118": 0xFF,
        "u16_37e": 0, "u8_380": 0xFF,
    }


def _sample_slot(i, suspend=False):
    itbl = {"pid": ["IKE", "MICAIAH", "SOLDIER"], "jid": ["BRAVE", "LIGHT"],
            "iid": ["IRONSWORD", "RAGNELL"], "sid": ["HERO", "FEMALE",
                                                     "AETHER"],
            "atkseq": ["ATK_A"], "movseq": ["MOV_A", "MOV_B"],
            "healseq": ["HEAL_A"], "mtype": ["M_A"]}
    units = [_sample_unit(1, 1, 1, True), _sample_unit(2, 2, 2, True),
             _sample_unit(5, 3, 1, False)]
    hist = [{"chapter": c, "kind": 1, "turns": 7, "seconds": 900,
             "pid_index": 1, "u16_0a": 0, "value_0c": 12}
            for c in range(1, 4)]
    hist += [{"chapter": 0, "kind": 0, "turns": 0, "seconds": 0,
              "pid_index": 0, "u16_0a": 0, "value_0c": 0}] * 57
    game = {k: 0 for k, *_ in BMST_SPEC_A}
    game.update({"raw_00": "00" * 16, "bytes_14": [0] * 4,
                 "gold": [0, 0, 0], "bonus_exp": [0.0, 0.0, 0.0],
                 "raw_30": "00" * 0x24, "raw_54": "00" * 0x3c,
                 "raw_94": "00" * 6, "defeated_chapter": [0] * 4, "defeated_total": [0] * 4,
                 "flags_d8": "00" * 16, "flags_ec": "00" * 16,
                 "chapter": 4, "turn": 3, "playthrough_no": 1,
                 "playtime_ticks": 3600 * TIMEBASE_HZ,
                 "unitref_134": {"unit": 0, "b1": 0, "b2": 0, "b3": 0,
                                 "b4": 0},
                 "unitref_13c": {"unit": 1, "b1": 0, "b2": 0, "b3": 0,
                                 "b4": 0},
                 "bits_544": "00" * 16, "chapter_history": hist,
                 "raw_914": "00" * 0x18, "pairs_955": [[1, 2]],
                 "flags_100": "00" * 0x30})
    hdr = {"magic": "FE10", "kind": "ADAT", "version": DAT_MAGIC[2],
           "rev": DAT_REV, "playthrough_id": 0x1234, "crc32": 0,
           "save_count": 3, "saved_ticks": 0x5678,
           "playtime_ticks": game["playtime_ticks"], "slot": i,
           "is_suspend": int(suspend), "suspend_origin": i if suspend else 0xFF,
           "u8_33": 0, "playthrough_no": 1, "difficulty": 1, "chapter": 4,
           "mode_37": 8 if suspend else 3, "turn": 3, "u16_3a": 0,
           "flags_3c": 0,
           "options": {"option_bits": "00" * 8, "u8_08": 1, "u8_09": 20,
                       "u8_0a": 0x40, "u8_0b": 0, "u8_0c": 0,
                       "levels_0d": [100] * 4, "difficulty": 1,
                       "u16_12": 0, "u32_14": 0, "u32_18": 0, "u32_1c": 0},
           "por_transfer": None}
    return {"header": hdr, "itbl": itbl, "game": game,
            "mdst": {"version": 4, "phase_830": 0, "bytes_839": [0] * 6,
                     "bytes_834": [0] * 4, "triples": [0] * 24,
                     "u16_840": [0] * 3, "s8_846": -1, "u16_848": 0,
                     "u16_84a": 0, "u8_838": 0, "bytes_84c": [0] * 3},
            "units": units,
            "convoy": [{"iid_index": 1, "uses": 46, "flags": 0, "slot": 0}],
            "pending_items": [],
            "fgpt": [50, 0, 0, 0, 0, 0],
            "tile_table": {"count": 1, "entries": [{"x": 3, "y": 4, "kind": 7,
                                                     "b3": 0,
                                                     "bytes_4": [0] * 4}],
                           "raw_200": "00" * 0x200, "u32_tail": 0},
            "supports": [{"a": 1, "b": 2, "level": 1}],
            "bonds": [{"a": 1, "b": 2, "v0": 1, "v1": 10}],
            "debug": "00" * 8}


def _strip(o):
    """Drop derived keys so parsed output can be compared with the input."""
    if isinstance(o, dict):
        drop = {"pid", "jid", "iid", "sid", "partner_pid", "a_pid", "b_pid"}
        return {k: _strip(v) for k, v in o.items() if k not in drop}
    if isinstance(o, list):
        return [_strip(v) for v in o]
    return o


def selftest():
    sysd = {"magic": "", "kind": "", "version": SYS_MAGIC[2], "rev": SYS_REV,
            "created_ticks": 1, "crc32": 0, "flags_1c": "00000006" + "00" * 4,
            "bits_24": "00" * 16, "name_flags": "00" * 0x60,
            "bits_94": "00" * 16, "bits_a4": "00" * 16, "bits_b4": "00" * 8,
            "bits_bc": "00" * 8, "bits_c4": "00" * 8,
            "u16_cc": [0xFFFF] * 3 + [0] * 4 + [0xFFFF],
            "clear_records": [{"playthrough_id": 7, "difficulty": 1,
                               "playthrough_no": 1, "pid_index": 1,
                               "total_turns": 300, "total_seconds": 90000,
                               "index": 0}],
            "u8_3ac": 1, "last_slot": 0, "raw_3ae": "ffff",
            "banner_crc32": 0}
    banner = bytearray(BANNER_SIZE)
    banner[:4] = b"WIBN"
    t = "Fire Emblem: Radiant Dawn".encode("utf-16-be")
    banner[0x20:0x20 + len(t)] = t
    banner[0x60:0x62] = " ".encode("utf-16-be")
    sysd["banner_crc32"] = zlib.crc32(bytes(banner)) & 0xFFFFFFFF
    img = bytearray(b"\xff" * FILE_SIZE)
    img[:SYS_SIZE] = build_system(sysd)
    s0 = _sample_slot(0)
    s1 = _sample_slot(0, suspend=True)
    img[SLOT_BASE:SLOT_BASE + SLOT_SIZE] = build_slot(s0)
    img[SUSPEND_BASE:SUSPEND_BASE + SLOT_SIZE] = build_slot(s1)
    img = bytes(img)
    p = parse_file(img, banner=bytes(banner))
    ok = True

    def check(cond, msg):
        nonlocal ok
        print(("ok   " if cond else "FAIL ") + msg)
        ok = ok and cond

    check(p["system"]["valid_magic"] and p["system"]["crc_ok"], "system CRC")
    check(p["banner"]["matches_system"], "banner CRC stored in system")
    check(p["system"]["cleared_difficulty_bits"]["diff0"], "clear flag bits")
    sv = p["saves"][0]
    check(sv["header"]["crc_ok"], "slot CRC")
    check("body_error" not in sv, "slot body parses: %s"
          % sv.get("body_error", ""))
    check(sv.get("support_mode") == "heuristic", "heuristic support detection")
    for key in ("units", "convoy", "supports", "bonds", "fgpt"):
        check(_strip(sv.get(key)) == _strip(s0[key]), "round trip " + key)
    check(_strip(sv["game"]) == _strip(s0["game"]), "round trip game state")
    check(sv["units"][0]["pid"] == "PID_IKE", "ITBL name lookup")
    check(sv["tail_is_ff"], "slot padding")
    check(p["suspends"][0]["header"]["is_suspend"] == 1, "suspend slot")
    rebuilt = build_slot(dict(sv, header=sv["header"]))
    check(rebuilt == img[SLOT_BASE:SLOT_BASE + SLOT_SIZE], "byte-exact rebuild")
    bad = bytearray(img)
    bad[SLOT_BASE + 0x2000] ^= 1
    check(not parse_file(bytes(bad), True)["saves"][0]["header"]["crc_ok"],
          "corruption detected")
    check(fix_checksums(bytes(bad))[SLOT_BASE + 0x18:SLOT_BASE + 0x1c] !=
          img[SLOT_BASE + 0x18:SLOT_BASE + 0x1c], "fix-checksum rewrites CRC")
    fixed = parse_file(fix_checksums(bytes(bad)), True)
    check(fixed["saves"][0]["header"]["crc_ok"], "fix-checksum result valid")
    rel = {"PID_IKE", "PID_MICAIAH"}
    pe = parse_file(img, reliance=rel)
    check(pe["saves"][0].get("support_mode") == "fe10data" and
          _strip(pe["saves"][0]["units"]) == _strip(s0["units"]),
          "exact support detection with reliance set")
    print("selftest", "passed" if ok else "FAILED")
    return 0 if ok else 1


# --------------------------------------------------------------------------

def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("file", nargs="?", help="FE10_US.dat, banner.bin or a "
                    "single 0x18000-byte slot")
    ap.add_argument("--headers-only", action="store_true",
                    help="do not parse slot bodies")
    ap.add_argument("--banner", help="banner.bin to check against the "
                    "CRC stored in the system block")
    ap.add_argument("--fe10data", help="FE10Data.cms, used to decide which "
                    "unit records carry a support block")
    ap.add_argument("--fix-checksum", metavar="OUT",
                    help="write a copy with all CRCs recomputed")
    ap.add_argument("--json", metavar="OUT", help="write JSON to OUT")
    ap.add_argument("--selftest", action="store_true")
    a = ap.parse_args(argv)
    if a.selftest:
        return selftest()
    if not a.file:
        ap.error("file required")
    data = open(a.file, "rb").read()
    if a.fix_checksum:
        with open(a.fix_checksum, "wb") as f:
            f.write(fix_checksums(data))
        print("wrote %s" % a.fix_checksum, file=sys.stderr)
    rel = load_reliance(a.fe10data) if a.fe10data else None
    ban = open(a.banner, "rb").read() if a.banner else None
    res = parse_file(data, a.headers_only, rel, ban)
    txt = json.dumps(res, ensure_ascii=False, indent=1)
    if a.json:
        with open(a.json, "w", encoding="utf-8") as f:
            f.write(txt)
    else:
        print(txt)
    return 0


if __name__ == "__main__":
    sys.exit(main())
