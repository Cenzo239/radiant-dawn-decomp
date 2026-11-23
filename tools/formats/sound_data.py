"""Reader for FE10's sound tables: Sound/sound_data*.cms (LZ10 + IS binary
container) and soundroom.bin. See docs/formats/sound.md, section
"Game sound tables".

The game never plays a .brsar sound id directly. Code asks for a game label
(e.g. "SFX_BTL_SWORD_HIT1", "BGM_PHASE_PL1"); fn_80076F54 finds that label in
the loaded IS tables and returns its 0x24-byte record, whose field +0x04 is the
.brsar sound label (resolved by nw4r ConvertLabelStringToSoundId,
fn_802AD3B0). Several game labels may share one archive sound.

CLI:
  sound_data.py FILE.cms tables                      # table names + counts
  sound_data.py FILE.cms dump TABLE                  # JSON lines
      TABLE: bgm sfx voice groups map_bgm battle_bgm chapter_group env map maya
  sound_data.py FILE.cms resolve LABEL [--brsar sound_us.brsar]
  sound_data.py soundroom soundroom.bin              # sound-room track list
"""
import json
import os
import signal
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from isbin import open_file  # noqa: E402

signal.signal(signal.SIGPIPE, signal.SIG_DFL)

TABLES = {
    "bgm": "SND_BGM_DATA", "sfx": "SND_SFX_DATA", "voice": "SND_VOICE_DATA",
    "groups": "SND_GROUP_DATA", "map_bgm": "SND_MAP_BGM_DATA",
    "battle_bgm": "SND_BATTLE_BGM_DATA", "chapter_group": "SND_CHAPTER_GROUP_DATA",
    "env": "SND_ENV_DATA", "map": "SND_MAP_DATA", "maya": "SND_SFX_MAYA_DATA",
}
KINDS = {0: "seq", 1: "strm", 2: "wave"}


class SoundData:
    def __init__(self, path):
        self.b = open_file(path)

    def s(self, o):
        """String behind the pointer field at data offset o (None if null)."""
        b = self.b
        if o not in b.pointer_set:
            return None
        return b.cstr(b.u32(o))

    def table(self, name):
        o = self.b.labels[TABLES.get(name, name)]
        return o + 4, self.b.u32(o)

    # ---- 0x24-byte sound records (BGM / SFX / VOICE)
    def record(self, o):
        d = self.b.data
        (kind, vol, pitch, prange, pan, b0e, prio, b10, b11, b12, b13, b14,
         limit, rmin, rmax, rv0, rv1, w1c, w1e, w20, room) = struct.unpack_from(
            ">BBhBBBBBBBBBbhhbbHHhh", d, o + 8)
        return {
            "label": self.s(o), "sound": self.s(o + 4),
            "kind": KINDS.get(kind, kind), "volume": vol, "pitch": pitch,
            "pitch_range": prange, "pan": pan, "b0e": b0e, "priority": prio,
            "b10_13": [b10, b11, b12, b13], "b14": b14, "max_instances": limit,
            "rand_pitch": [rmin, rmax], "rand_volume": [rv0, rv1],
            "w1c": w1c, "w1e": w1e, "w20": w20, "room_index": room,
        }

    def records(self, name):
        o, n = self.table(name)
        return [self.record(o + 0x24 * i) for i in range(n)]

    def lookup(self, label):
        """Like fn_80076F54: label -> record (searched in BGM/SFX/VOICE)."""
        o = self.b.labels.get(label)
        if o is None:
            return None
        return self.record(o)

    # ---- other tables
    def dump(self, name):
        b, s = self.b, self.s
        if name in ("bgm", "sfx", "voice"):
            return self.records(name)
        if name == "groups":
            n = b.u32(0)
            return [{"label": s(4 + 8 * i), "group": s(8 + 8 * i)} for i in range(n)]
        o, n = self.table(name)
        out = []
        if name == "map_bgm":  # 13 words, fn_80068398 .. fn_800685B0
            for i in range(n):
                r = o + 52 * i
                out.append({"chapter": s(r), "condition": b.u8(r + 4),
                            "map": [s(r + 8 + 4 * k) for k in range(4)],
                            "phase": [s(r + 24 + 4 * k) for k in range(4)],
                            "prologue": s(r + 40), "base": s(r + 44),
                            "preparation": s(r + 48)})
        elif name == "battle_bgm":  # 7 words, matched by fn_80068638
            for i in range(n):
                r = o + 28 * i
                out.append({"bgm": s(r), "chapter": s(r + 4), "unit_a": s(r + 8),
                            "unit_b": s(r + 12), "flag": s(r + 16),
                            "a_14": struct.unpack_from(">b", b.data, r + 0x14)[0],
                            "b_15": struct.unpack_from(">b", b.data, r + 0x15)[0],
                            "a_16": struct.unpack_from(">b", b.data, r + 0x16)[0],
                            "b_17": struct.unpack_from(">b", b.data, r + 0x17)[0],
                            "flag_value": b.u8(r + 0x18), "symmetric": b.u8(r + 0x19)})
        elif name == "chapter_group":  # 4 words, fn_800680D0
            for i in range(n):
                r = o + 16 * i
                out.append({"chapter": s(r), "flag": s(r + 4),
                            "flag_value": b.u8(r + 8), "group": s(r + 12)})
        elif name == "env":  # 6 words
            for i in range(n):
                r = o + 24 * i
                out.append({"map": s(r), "sfx": s(r + 4), "type": b.u8(r + 8),
                            "b9": b.u8(r + 9),
                            "pos": list(struct.unpack_from(">3f", b.data, r + 12))})
        elif name == "map":  # 5 words
            for i in range(n):
                r = o + 20 * i
                out.append({"map": s(r), "b4": b.u8(r + 4), "b5": b.u8(r + 5),
                            "floats": list(struct.unpack_from(">3f", b.data, r + 8))})
        elif name == "maya":  # {u32 id, char* label}
            for i in range(n):
                r = o + 8 * i
                out.append({"id": b.u32(r), "sfx": s(r + 4)})
        else:
            raise KeyError(name)
        return out


def soundroom(path):
    """soundroom.bin: u32 n; {char* RID image, s16 x, s16 y, s16 scale%, pad}[n];
    u32 m; {char* BGM label, u32 display number}[m]."""
    b = open_file(path)
    n = b.u32(0)
    images = []
    for i in range(n):
        r = 4 + 12 * i
        x, y, sc = struct.unpack_from(">hhh", b.data, r + 4)
        images.append({"image": b.cstr(b.u32(r)), "x": x, "y": y, "scale": sc})
    o = 4 + 12 * n
    tracks = [{"bgm": b.cstr(b.u32(o + 4 + 8 * i)), "number": b.u32(o + 8 + 8 * i)}
              for i in range(b.u32(o))]
    return images, tracks


def main(argv):
    if len(argv) < 3:
        print(__doc__)
        return 1
    if argv[1] == "soundroom":
        images, tracks = soundroom(argv[2])
        for t in tracks:
            print(json.dumps(t, ensure_ascii=False))
        print("# %d background images" % len(images), file=sys.stderr)
        return 0
    sd = SoundData(argv[1])
    cmd = argv[2]
    if cmd == "tables":
        for k, v in TABLES.items():
            n = sd.b.u32(0) if k == "groups" else sd.table(k)[1]
            print("%-14s %-24s %5d" % (k, v, n))
    elif cmd == "dump":
        for x in sd.dump(argv[3]):
            print(json.dumps(x, ensure_ascii=False))
    elif cmd == "resolve":
        rec = sd.lookup(argv[3])
        if rec is None:
            print("label not found", file=sys.stderr)
            return 1
        out = {"record": rec}
        if "--brsar" in argv:
            from brsar import Rsar
            with open(argv[argv.index("--brsar") + 1], "rb") as fh:
                r = Rsar(fh.read())
            snd = next((x for x in r.sounds if x["label"] == rec["sound"]), None)
            out["brsar_sound"] = snd
            if snd:
                f = r.files[snd["file"]]
                out["file"] = f["external"] or ("archive file %d" % f["id"])
        print(json.dumps(out, indent=1, ensure_ascii=False))
    else:
        print(__doc__)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
