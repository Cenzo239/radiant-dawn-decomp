"""Reader for FE10 unit placement files zmap/<map>/dispos_{n,h,c}.bin.

See docs/formats/maps_events.md, section "Unit placement (dispos)".

The file is an IS binary container (isbin.py). Every label except
"<map>_date_<x>" names one placement group ("<map>_mikata_h", "<map>_teki_h",
"<map>_z01_h", "<map>_ev00_c", ...); scripts load groups by that name without
the suffix (DisposRank/InstantDispos("bmap0101_teki")), the engine appends
"_n"/"_h"/"_c" itself (fn_8010DE10).

  <map>_date_x : u32 ptr -> build date string "2007/06/05 0:00:00"

  group (label offset):
    u8 count, u8 version (always 7), u8 gtype, u8 group_param
      gtype 0..2 (1 almost always); loader maps 1->flag 2, 2->flag 4, 3->flag 8
      group_param is copied into every unit (runtime +0x0D / +0x67), meaning unknown
    unit[count], 0x68 bytes each:
      0x00 u16 unit serial (2000+ c, 4000+ n, 6000+ h; unique per file)
      0x02 u16 flags (bit 0x0008, 0x0800 tested by the loader)
      0x04 ptr PID_*            0x08 ptr JID_*
      0x0C u8  x, y             start position
      0x0E u8  x, y             end position (unit walks/warps start -> end)
      0x10 u8  level
      0x11 u8  army / allegiance (0 player, 1 enemy, 2 ally, 3 other; + bits?)
      0x12 u8  initial laguz gauge (0-30)
      0x13 u8  AI group / team id (guess)
      0x14 s8[8] stat modifiers (guess: HP Str Mag Skl Spd Lck Def Res)
      0x1C u8  unknown (small integer)
      0x1D u8  facing at start (8-direction bitmask 1/2/4/8 + combos, guess)
      0x1E u8  facing at end   (guess)
      0x1F u8  unused (read and discarded)
      0x20 ptr affinity name ("invalid", "fire", "thunder", ... -> fn_801194FC)
      0x24 ptr IID_*[7]         inventory (null = empty)
      0x40 ptr SID_*[5]         extra skills
      0x54 ptr AI sequences [5] (attack AI, move AI, heal/misc AI,
                                 MTYPE_*, retreat AI; null -> SEQ_SAFETYMOVE)

Loader: fn_8010BED8 (group) / fn_8010BCBC (unit record, version 7 only).
"""
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from isbin import open_file as _open_isbin  # noqa: E402

UNIT_SIZE = 0x68
DIFFICULTY_FILES = {"n": "normal (JP Normal = US Easy?)",
                    "h": "hard (JP Hard = US Normal/Hard?)",
                    "c": "common (event/cutscene units, difficulty independent)"}
AI_SLOTS = ("attack", "move", "heal", "movetype", "retreat")
STAT_NAMES = ("hp", "str", "mag", "skl", "spd", "lck", "def", "res")


def _ptr_str(b, o):
    return b.str_at_ptr(o)


def parse_unit(b, o):
    d = b.data
    serial, flags = struct.unpack_from(">HH", d, o)
    u = {
        "offset": o,
        "serial": serial,
        "flags": flags,
        "pid": _ptr_str(b, o + 0x04),
        "jid": _ptr_str(b, o + 0x08),
        "start": (d[o + 0x0C], d[o + 0x0D]),
        "end": (d[o + 0x0E], d[o + 0x0F]),
        "level": d[o + 0x10],
        "army": d[o + 0x11],
        "laguz_gauge": d[o + 0x12],
        "team": d[o + 0x13],
        "stat_mod": dict(zip(STAT_NAMES, struct.unpack_from(">8b", d, o + 0x14))),
        "unk_1c": d[o + 0x1C],
        "dir_start": d[o + 0x1D],
        "dir_end": d[o + 0x1E],
        "affinity": _ptr_str(b, o + 0x20),
        "items": [x for x in (_ptr_str(b, o + 0x24 + 4 * i) for i in range(7)) if x],
        "skills": [x for x in (_ptr_str(b, o + 0x40 + 4 * i) for i in range(5)) if x],
        "ai": dict(zip(AI_SLOTS, (_ptr_str(b, o + 0x54 + 4 * i) for i in range(5)))),
    }
    return u


def parse(path_or_isbin):
    b = path_or_isbin if hasattr(path_or_isbin, "labels") else _open_isbin(path_or_isbin)
    d = b.data
    out = {"date": None, "groups": []}
    for off, name in sorted(b.label_list):
        if "_date_" in name:
            out["date"] = b.str_at_ptr(off)
            continue
        count, version, gtype, gparam = d[off:off + 4]
        g = {"name": name, "offset": off, "count": count, "version": version,
             "gtype": gtype, "param": gparam, "units": []}
        if version != 7:
            g["error"] = "unsupported version %d" % version
        else:
            p = off + 4
            for _ in range(count):
                g["units"].append(parse_unit(b, p))
                p += UNIT_SIZE
        out["groups"].append(g)
    return out


def format_text(info):
    lines = ["date: %s" % info["date"]]
    for g in info["groups"]:
        lines.append("")
        lines.append("[%s] %d unit(s)  gtype=%d param=%d" %
                     (g["name"], g["count"], g["gtype"], g["param"]))
        for u in g["units"]:
            mods = " ".join("%s%+d" % (k, v) for k, v in u["stat_mod"].items() if v)
            extra = []
            if u["laguz_gauge"]:
                extra.append("gauge=%d" % u["laguz_gauge"])
            if u["team"]:
                extra.append("team=%d" % u["team"])
            if mods:
                extra.append("mods(" + mods + ")")
            if u["affinity"] and u["affinity"] != "invalid":
                extra.append("affinity=" + u["affinity"])
            lines.append("  #%d %-22s %-18s Lv%-2d army=%d (%2d,%2d)->(%2d,%2d) dir=%d/%d flags=%04x %s" % (
                u["serial"], u["pid"], u["jid"], u["level"], u["army"],
                u["start"][0], u["start"][1], u["end"][0], u["end"][1],
                u["dir_start"], u["dir_end"], u["flags"], " ".join(extra)))
            if u["items"] or u["skills"]:
                lines.append("      items: %s%s" % (", ".join(u["items"]) or "-",
                                                   ("   skills: " + ", ".join(u["skills"])) if u["skills"] else ""))
            ai = u["ai"]
            lines.append("      ai: %s / %s / %s / %s / %s" % tuple(ai[k] for k in AI_SLOTS))
    return "\n".join(lines)


if __name__ == "__main__":
    import argparse
    import json
    ap = argparse.ArgumentParser(description="FE10 dispos_*.bin unit placement dump")
    ap.add_argument("file")
    ap.add_argument("--json", action="store_true")
    a = ap.parse_args()
    info = parse(a.file)
    if a.json:
        print(json.dumps(info, ensure_ascii=False, indent=1))
    else:
        print(format_text(info))
