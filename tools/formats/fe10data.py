#!/usr/bin/env python3
"""Decoder for Fire Emblem: Radiant Dawn (RFEE01) game databases.

Handles
  * FE10Data.cms      main database (persons, classes, items, skills, ...)
  * FE10Growth.cms    per-character per-level stat tables (FE10PersonGrowth)
  * Shop/shopitem_*.bin   shop inventories (n/h/m = difficulty)

All three are (optionally LZ10-compressed) IS relocatable containers, see
isbin.py.  Field layouts are documented in docs/formats/fe10data.md.

Library use (Python 3.9, stdlib only):

    import fe10data
    db = fe10data.load("FE10Data.cms")          # ISBin
    persons = fe10data.parse_persons(db)          # list of dicts
    everything = fe10data.parse_all(db)           # {table_name: data}

CLI:
    python3 fe10data.py FE10Data.cms                       # summary
    python3 fe10data.py FE10Data.cms --table persons       # text dump
    python3 fe10data.py FE10Data.cms --json out.json       # all tables
    python3 fe10data.py FE10Growth.cms --json growth.json
    python3 fe10data.py Shop/shopitem_n.bin --table shops

Unknown fields are kept as unk_XX (XX = hex offset inside the record or
inside the named byte block).  Signed bytes are decoded as signed where the
game treats them as such (personal stat modifiers, con modifiers, ...).
"""
import argparse
import json
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from isbin import ISBin  # noqa: E402
from lz10 import load as _lz_load  # noqa: E402

# --------------------------------------------------------------------------
# constants recovered from main.dol string tables

STATS8 = ("hp", "str", "mag", "skl", "spd", "lck", "def", "res")
STATS10 = STATS8 + ("mov", "con")

# 12-char weapon rank strings, one char per weapon type (fn_801115A8)
RANK_TYPES = ("sword", "lance", "axe", "bow", "knife", "strike",
              "fire", "thunder", "wind", "light", "dark", "staff")
# rank letter -> weapon experience threshold (fn_801115A8 / fn_801112A8)
RANK_WEXP = {"-": 0, "E": 1, "D": 31, "C": 71, "B": 121, "A": 181,
             "S": 251, "SS": 331, "*": 331, "N": 0}

# item weapon-type strings -> runtime index (fn_8010F73C)
WEAPON_TYPE_INDEX = {"sword": 0, "lance": 1, "axe": 2, "bow": 3, "knife": 4,
                     "blow": 5, "fang": 5, "flame": 6, "thunder": 7,
                     "wind": 8, "light": 9, "dark": 10, "rod": 11,
                     "ballista": 13, "item": 14, "acc": 15, "card": 16,
                     "elemental": 17, "neutral": 18}

# affinity strings -> runtime index (fn_801194FC)
AFFINITY_INDEX = {"invalid": -1, "fire": 1, "thunder": 2, "wind": 3,
                  "water": 4, "dark": 5, "light": 6, "heaven": 7,
                  "telius": 8}  # telius == "Earth" in the US release


# --------------------------------------------------------------------------
# helpers

def load(path):
    """Read a (possibly LZ10-compressed) IS container and return an ISBin."""
    return ISBin(_lz_load(path))


def _s8(v):
    return v - 256 if v >= 128 else v


def _ptrstr(b, off):
    """String at the pointer field off (None if null)."""
    if off in b.pointer_set:
        return b.cstr(b.u32(off))
    if b.u32(off) != 0:
        raise ValueError("field 0x%x is not a relocated pointer" % off)
    return None


def _ptrlist(b, off, n):
    return [_ptrstr(b, off + 4 * i) for i in range(n)]


def _stats(raw, names=STATS8, signed=False):
    return {k: (_s8(v) if signed else v) for k, v in zip(names, raw)}


def _ranks(s):
    """Decode a 12-char weapon-rank string into {type: letter}."""
    if not s:
        return {}
    return {t: c for t, c in zip(RANK_TYPES, s) if c != "-"}


def _unk(raw, idxs):
    return {"unk_%02x" % i: raw[i] for i in idxs}


# --------------------------------------------------------------------------
# FE10Data.cms tables

def parse_persons(b):
    """PersonData: u32 count + variable-length records (fn_80109DF8)."""
    base = b.labels["PersonData"]
    n = b.u32(base)
    p = base + 4
    out = []
    for i in range(n):
        hdr = b.data[p:p + 4]
        nskill = hdr[0]
        f = _ptrlist(b, p + 4, 7)
        q = p + 0x20
        skills = _ptrlist(b, q, nskill)
        q += 4 * nskill
        extra_skill = _ptrstr(b, q)
        q += 4
        anims = _ptrlist(b, q, 4)
        q += 16
        blk = b.data[q:q + 27]
        rec = {
            "index": i + 1,              # runtime ids are 1-based
            "offset": p,
            "pid": f[0],
            "name_msg": f[1],            # MPID_*
            "help_msg": f[2],            # MNPID_*
            "face": f[3],                # FID_*
            "job": f[4],                 # JID_* default class
            "affinity": f[5],
            "weapon_ranks_str": f[6],
            "weapon_ranks": _ranks(f[6]),
            "level": hdr[2],
            "unk_hdr1": hdr[1],
            "female": hdr[3],             # !=0 -> loader adds SID_FEMALE
            "skills": skills,
            "extra_skill": extra_skill,
            "anims": anims,              # AID_* x4
            "biorhythm": blk[0],
            "unk_b1": blk[1],            # 0xff for generics (bio-related?)
            "unk_b2": blk[2],            # 0xff for generics (bio-related?)
            "unk_b3": blk[3],            # bitmask 0/3/7/15/31
            "authority": blk[4],
            "laguz_gauge": {             # signed per-turn/per-battle deltas
                "turn_gain": _s8(blk[5]), "battle_gain": _s8(blk[6]),
                "turn_loss": _s8(blk[7]), "battle_loss": _s8(blk[8])},
            "bases": _stats(blk[9:17], signed=True),  # added to class bases
            "con": _s8(blk[17]),          # added to class con
            "unk_b18": _s8(blk[18]),
            "growths": _stats(blk[19:27]),
        }
        out.append(rec)
        p = (q + 0x1e) & ~3
    return out


def parse_jobs(b):
    """JobData: u32 count + variable-length records (fn_8010A2FC)."""
    base = b.labels["JobData"]
    n = b.u32(base)
    p = base + 4
    out = []
    for i in range(n):
        f = _ptrlist(b, p, 11)
        q = p + 0x2c
        blk = b.data[q:q + 13]
        nskill, nsfxc = blk[5], blk[6]
        q += 16
        skills = _ptrlist(b, q, nskill)
        q += 4 * nskill
        extra = _ptrstr(b, q)
        q += 4
        sfxc = _ptrlist(b, q, nsfxc)
        q += 4 * nsfxc
        st = b.data[q:q + 32]
        rec = {
            "index": i + 1,
            "offset": p,
            "jid": f[0],
            "name_msg": f[1],            # MJID_*
            "name_jp": f[2],             # half-width katakana internal name
            "help_msg": f[3],            # MH_J_*
            "prev_job": f[4],            # class this one promotes from
            "next_job": f[5],            # promotion
            "alt_job": f[6],             # transformed/untransformed counterpart
            "natural_weapon": f[7],     # IID_* laguz claw/fang/breath
            "anim": f[8],                # AID_*
            "base_ranks_str": f[9],
            "base_ranks": _ranks(f[9]),
            "max_ranks_str": f[10],
            "max_ranks": _ranks(f[10]),
            "con": blk[0],
            "unk_b1": blk[1], "unk_b2": _s8(blk[2]),
            "unk_b3": blk[3], "unk_b4": _s8(blk[4]),
            "unk_b7": blk[7],
            "unk_b8": blk[8],
            "move": blk[9],
            "skill_capacity": blk[10],
            "unk_b11": blk[11],
            "unk_b12": blk[12],
            "skills": skills,
            "extra_skill": extra,
            "class_types": sfxc,          # SFXC_* (effectiveness classes)
            "caps": _stats(st[0:8]),
            "bases": _stats(st[8:16], signed=True),
            "growths": _stats(st[16:24]),
            "promo_gains": _stats(st[24:32], signed=True),
        }
        out.append(rec)
        p = (q + 0x23) & ~3
    return out


def parse_items(b):
    """ItemData: u32 count + variable-length records (fn_8010A958)."""
    base = b.labels["ItemData"]
    n = b.u32(base)
    p = base + 4
    out = []
    for i in range(n):
        f = _ptrlist(b, p, 9)
        q = p + 0x24
        blk = b.data[q:q + 13]
        q += 16
        x = b.data[q:q + 4]
        q += 4
        attrs = _ptrlist(b, q, x[1])
        q += 4 * x[1]
        eff = _ptrlist(b, q, x[2])
        q += 4 * x[2]
        bonus = growth = None
        if x[3] & 1:
            bonus = _stats(b.data[q:q + 10], STATS10, signed=True)
            q += 10
        if x[3] & 2:
            growth = _stats(b.data[q:q + 8], signed=True)
            q += 8
        rec = {
            "index": i + 1,
            "offset": p,
            "iid": f[0],
            "name_msg": f[1],            # MIID_*
            "help_msg": f[2],            # MH_I_*
            "type": f[3],
            "type2": f[4],
            "rank": f[5],
            "effect1": f[6],             # EID_*
            "effect2": f[7],
            "effect3": f[8],
            "icon": struct.unpack_from(">H", blk, 0)[0],
            "price_per_use": struct.unpack_from(">H", blk, 2)[0],
            "might": blk[4],
            "hit": blk[5],
            "crit": blk[6],
            "weight": blk[7],
            "uses": blk[8],
            "wexp": blk[9],
            "range_min": blk[10],
            "range_max": blk[11],
            "unk_b12": blk[12],
            "unk_x0": x[0],
            "attributes": attrs,
            "effective_vs": eff,          # SFXC_*
            "stat_bonus": bonus,
            "growth_bonus": growth,
        }
        out.append(rec)
        p = (q + 3) & ~3
    return out


def _skill_list(b, off, n):
    if n == 0 or off not in b.pointer_set:
        return []
    t = b.u32(off)
    return [{"flag": b.u8(t + 8 * k), "id": _ptrstr(b, t + 8 * k + 4)}
            for k in range(n)]


def parse_skills(b):
    """SkillData: u32 count + 0x2c-byte records (fn_8010B22C)."""
    base = b.labels["SkillData"]
    n = b.u32(base)
    out = []
    for i in range(n):
        o = base + 4 + i * 0x2c
        f = _ptrlist(b, o, 7)
        d = b.data[o + 0x1c:o + 0x24]
        out.append({
            "index": i,
            "offset": o,
            "sid": f[0],
            "name_msg": f[1],            # MSID_*
            "help_msg": f[2],            # MH_SKILL_*
            "help2_msg": f[3],           # MH2_SKILL_*
            "effect1": f[4],             # EID_*
            "effect2": f[5],
            "item": f[6],                # IID_* (skill scroll / icon item)
            "id": d[0],
            "unk_1d": d[1],
            "capacity": d[2],
            "icon": d[3],
            "unk_22": d[6], "unk_23": d[7],
            "list_a": _skill_list(b, o + 0x24, d[4]),
            "list_b": _skill_list(b, o + 0x28, d[5]),
        })
    return out


def parse_terrain(b):
    """TerrainData: u32 0 + 199 x 0x10 records (fn_8010B240, fn_8011D17C)."""
    base = b.labels["TerrainData"] + 4
    out = []
    for i in range(199):
        o = base + i * 0x10
        t = b.u32(o + 8)
        s = b.data[t:t + 0x2c]
        out.append({
            "index": i,
            "name_jp": _ptrstr(b, o),
            "name_msg": _ptrstr(b, o + 4),
            "id": b.u8(o + 12),
            "unk_0d": b.data[o + 13:o + 16].hex(),
            "params_offset": t,
            "bonus_a": {"avoid": s[0], "def": s[1], "res": s[2]},
            "bonus_b": {"avoid": s[3], "def": s[4], "res": s[5]},
            "heal": s[6],
            "flags": s[7],
            "effect": _ptrstr(b, t + 8),
            "sound1": _ptrstr(b, t + 12),
            "sound2": _ptrstr(b, t + 16),
            "move_cost": [None if c == 0xff else c for c in s[20:43]],
        })
    return out


def parse_battle_terrain(b):
    """BattleTerrIndex / BattleTerrName."""
    o = b.labels["BattleTerrIndex"]
    nterr, nmap = b.u16(o), b.u16(o + 2)
    stride = (4 + 2 * nterr + 3) & ~3
    maps = []
    for i in range(nmap):
        r = o + 4 + i * stride
        idx = struct.unpack_from(">%dH" % nterr, b.data, r + 4)
        maps.append({"map": _ptrstr(b, r),
                     "bg_index": [None if v == 0xffff else v for v in idx]})
    o = b.labels["BattleTerrName"]
    names = []
    while o in b.pointer_set:
        names.append(b.cstr(b.u32(o)))
        o += 4
    return {"maps": maps, "names": names}


def parse_divine(b):
    """DivineData: affinity bonuses, u32 count + 0xc records."""
    o = b.labels["DivineData"]
    out = []
    for i in range(b.u32(o)):
        r = o + 4 + i * 0xc
        d = b.data[r + 4:r + 12]
        out.append({"affinity": _ptrstr(b, r), "atk": d[0], "def": d[1],
                    "hit": d[2], "avoid": d[3],
                    "unk": d[4:].hex()})
    return out


def parse_divine_param(b):
    o = b.labels["DivineParam"]
    out = []
    for i in range(b.u32(o)):
        r = o + 4 + i * 0xc
        out.append({"affinity_a": _ptrstr(b, r), "affinity_b": _ptrstr(b, r + 4),
                    "unk_08": b.u8(r + 8), "unk_09": b.u8(r + 9),
                    "unk_0a": b.u16(r + 10)})
    return out


def parse_reliance(b):
    """RelianceData (supports): fn_801198C8."""
    o = b.labels["RelianceData"]
    n = b.u32(o)
    p = o + 4
    out = []
    for i in range(n):
        k = b.u32(p + 4)
        partners = []
        for j in range(k):
            e = p + 8 + 8 * j
            partners.append({"pid": _ptrstr(b, e), "unk_4": _s8(b.u8(e + 4)),
                             "unk_5": b.u8(e + 5), "unk_6": b.u16(e + 6)})
        out.append({"pid": _ptrstr(b, p), "partners": partners})
        p += 8 + 8 * k
    return out


def parse_reliance_param(b):
    o = b.labels["RelianceParam"]
    return {"raw": list(b.data[o:o + 16])}


def parse_groups(b):
    o = b.labels["GroupData"]
    return [{"id": b.u32(o + 4 + i * 0xc),
             "name_jp": _ptrstr(b, o + 8 + i * 0xc),
             "name_msg": _ptrstr(b, o + 12 + i * 0xc)}
            for i in range(b.u32(o))]


def parse_kizna(b):
    """KiznaData (bonds): iterated until a null PID (fn_80110000 area)."""
    o = b.labels["KiznaData"]
    out = []
    p = o + 4
    for i in range(b.u32(o)):
        if b.u32(p) == 0:
            break
        out.append({"pid_a": _ptrstr(b, p), "pid_b": _ptrstr(b, p + 4),
                    "unk_8": b.u8(p + 8), "value": b.u8(p + 9),
                    "unk_a": b.u16(p + 10)})
        p += 0xc
    return out


def parse_sukumi(b):
    """3SukumiData: weapon triangle, u32 count + 0xc records."""
    o = b.labels["3SukumiData"]
    out = []
    for i in range(b.u32(o)):
        r = o + 4 + i * 0xc
        out.append({"attacker": _ptrstr(b, r), "defender": _ptrstr(b, r + 4),
                    "damage": _s8(b.u8(r + 8)), "hit": _s8(b.u8(r + 9)),
                    "unk_0a": b.u16(r + 10)})
    return out


def parse_chapters(b):
    """ChapterData: u32 count + 0xb4-byte records, copied 1:1 into RAM
    (fn_80109B18, fn_8010B094 looks up by the byte at +0x84)."""
    o = b.labels["ChapterData"]
    out = []
    for i in range(b.u32(o)):
        r = o + 4 + i * 0xb4
        diff = []
        for d in range(3):
            q = r + 0x24 + d * 0x20
            diff.append({"win": [x for x in _ptrlist(b, q, 3) if x],
                         "lose": [x for x in _ptrlist(b, q + 12, 5) if x]})
        raw = b.data[r + 0x84:r + 0x90]
        out.append({
            "index": i,
            "cid": _ptrstr(b, r),
            "name_msg": _ptrstr(b, r + 4),          # MCT*
            "map": _ptrstr(b, r + 8),
            "script": _ptrstr(b, r + 0xc),
            "message_file": _ptrstr(b, r + 0x10),
            "conditions": diff,                    # 3 difficulty blocks
            "chapter_no": raw[0],
            "unk_85": raw[1:4].hex(),
            "unk_88": raw[4], "unk_89": raw[5], "unk_8a": raw[6],
            "unk_8b": _s8(raw[7]),
            "unk_8c": raw[8:12].hex(),
            "affinity": _ptrstr(b, r + 0x90),
            "base_room": _ptrstr(b, r + 0x94),     # RID_*
            "battle_bg": _ptrstr(b, r + 0x98),
            "weather": _ptrstr(b, r + 0x9c),
            "room2": _ptrstr(b, r + 0xa0),         # RID_*
            "leader": _ptrstr(b, r + 0xa4),        # PID_*
            "unk_a8": b.data[r + 0xa8:r + 0xb4].hex(),
        })
    return out


def parse_game_data(b):
    o = b.labels["GameData"]
    return {"u16": list(struct.unpack_from(">68H", b.data, o))}


def parse_bio(b):
    o = b.labels["BioData"]
    rows = [list(struct.unpack_from(">4f", b.data, o + 16 * i)) for i in range(10)]
    o = b.labels["BioParam"]
    params = []
    for i in range(5):
        r = o + 12 * i
        params.append({"mult": struct.unpack_from(">f", b.data, r)[0],
                       "bytes": [_s8(v) for v in b.data[r + 4:r + 12]]})
    return {"bio": rows, "params": params}


def parse_nobtl(b):
    """NOBTL_<NAME> lists (no-battle pairs, read via strcpy "NOBTL_"+name)."""
    out = {}
    for name, o in sorted(b.labels.items()):
        if not name.startswith("NOBTL_") or name == "NOBTL_TABLE":
            continue
        owner = _ptrstr(b, o)
        partners = []
        p = o + 4
        while b.u32(p) != 0:
            partners.append(_ptrstr(b, p))
            p += 8
        out[name] = {"owner": owner, "partners": partners}
    return out


TABLES = {
    "persons": parse_persons,
    "jobs": parse_jobs,
    "items": parse_items,
    "skills": parse_skills,
    "terrain": parse_terrain,
    "battle_terrain": parse_battle_terrain,
    "chapters": parse_chapters,
    "affinity": parse_divine,
    "affinity_pairs": parse_divine_param,
    "supports": parse_reliance,
    "support_param": parse_reliance_param,
    "groups": parse_groups,
    "bonds": parse_kizna,
    "triangle": parse_sukumi,
    "game_data": parse_game_data,
    "biorhythm": parse_bio,
    "nobattle": parse_nobtl,
}


def parse_all(b):
    return {k: f(b) for k, f in TABLES.items()}


# --------------------------------------------------------------------------
# FE10Growth.cms

def parse_growth(b):
    """FE10PersonGrowth: u16 count, u16 0 + {ptr PID, u8 lv_first, u8 lv_last,
    u16 pad, ptr rows}; rows = (lv_last-lv_first+1) x 8 stat bytes, indexed
    by absolute level (tier*20+level) - lv_first (fn_8011F9xx)."""
    o = b.labels["FE10PersonGrowth"]
    out = []
    for i in range(b.u16(o)):          # u16 count, u16 unused
        r = o + 4 + i * 0xc
        lo, hi = b.u8(r + 4), b.u8(r + 5)
        t = b.u32(r + 8)
        rows = [_stats(b.data[t + 8 * k:t + 8 * k + 8])
                for k in range(hi - lo + 1)]
        out.append({"pid": _ptrstr(b, r), "abs_level_first": lo,
                    "abs_level_last": hi, "unk_6": b.u16(r + 6),
                    "rows": rows})
    return out


# --------------------------------------------------------------------------
# Shop/shopitem_*.bin

def parse_shop(b):
    labels = sorted(b.label_list)
    ends = {}
    for (off, name), nxt in zip(labels, labels[1:] + [(b.data_size, None)]):
        ends[name] = nxt[0]
    res = {"person": {}, "weapons": {}, "items": {}, "forge": {}, "cards": []}
    for name, o in b.labels.items():
        if name.startswith("SHOP_PERSON_"):
            res["person"][name[12:]] = list(b.data[o:o + 4])
        elif name.startswith(("WSHOP_ITEMS_", "ISHOP_ITEMS_")):
            lst = []
            p = o
            while p < ends[name] and b.u32(p) != 0:
                lst.append({"iid": _ptrstr(b, p), "unk_4": b.u32(p + 4)})
                p += 8
            key = "weapons" if name[0] == "W" else "items"
            res[key][name[12:]] = lst
        elif name.startswith("FSHOP_ITEMS_"):
            lst = []
            for p in range(o, ends[name], 12):
                lst.append({"kind": _ptrstr(b, p), "material": _ptrstr(b, p + 4),
                            "unk_8": _ptrstr(b, p + 8)})
            res["forge"][name[12:]] = lst
        elif name == "FSHOP_CARD_DATA":
            for k in range(b.u32(o)):
                p = o + 4 + 12 * k
                res["cards"].append({"msg": _ptrstr(b, p),
                                     "unk_4": b.data[p + 4:p + 12].hex()})
    return res


# --------------------------------------------------------------------------
# CLI

def _kind(b):
    if "PersonData" in b.labels:
        return "data"
    if "FE10PersonGrowth" in b.labels:
        return "growth"
    if any(n.endswith("SHOP_ITEMS_C0000") for n in b.labels):
        return "shop"
    raise SystemExit("unrecognised file (no known labels)")


def _text(name, data):
    if isinstance(data, list):
        for r in data:
            print(json.dumps(r, ensure_ascii=False))
    else:
        print(json.dumps(data, ensure_ascii=False, indent=1))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("file")
    ap.add_argument("--table", help="one of: " + ", ".join(TABLES) +
                    " (FE10Data); growth; shops")
    ap.add_argument("--json", metavar="OUT", help="write JSON to OUT")
    a = ap.parse_args(argv)
    b = load(a.file)
    kind = _kind(b)
    if kind == "data":
        if a.table:
            if a.table not in TABLES:
                ap.error("unknown table %r" % a.table)
            res = {a.table: TABLES[a.table](b)}
        else:
            res = parse_all(b)
    elif kind == "growth":
        res = {"growth": parse_growth(b)}
    else:
        res = {"shops": parse_shop(b)}
    if a.json:
        with open(a.json, "w", encoding="utf-8") as f:
            json.dump(res, f, ensure_ascii=False, indent=1)
        print("wrote %s (%s)" % (a.json, ", ".join(
            "%s:%d" % (k, len(v)) for k, v in res.items())))
    elif a.table:
        for k, v in res.items():
            _text(k, v)
    else:
        for k, v in res.items():
            print("%-15s %d" % (k, len(v)))
    return 0


if __name__ == "__main__":
    sys.exit(main())
