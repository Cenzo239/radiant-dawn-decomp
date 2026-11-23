"""Reader for FE10's NW4R sound archive (Sound/sound.brsar, sound_us.brsar),
RSAR version 1.4. See docs/formats/sound.md.

Layout (all offsets in INFO are relative to the INFO payload = block + 8,
string offsets in SYMB relative to the SYMB payload):
  header: u32 symb_off, symb_size, info_off, info_size, file_off, file_size
  SYMB:   u32 string_table, sound_tree, player_tree, group_tree, bank_tree
          string table = u32 n, u32 offset[n]; trees are Patricia tries
  INFO:   DataRef sounds, banks, players, files, groups, player_info
  FILE:   the sub-files, stored inside group images (group.offset is absolute
          in the .brsar; item.offset relative to it; wave data at
          group.wave_offset + item.wave_offset; this is a raw DSP-ADPCM
          sample pool, not an RWAR file)

CLI:
  brsar.py ARCHIVE summary
  brsar.py ARCHIVE sounds [--type seq|strm|wave]      # JSON lines
  brsar.py ARCHIVE banks|players|groups|files          # JSON lines
  brsar.py ARCHIVE extract OUTDIR      # sub-files (.brseq/.brwsd/.brbnk + .wavedata pools)
  brsar.py ARCHIVE wav OUTDIR [--sound LABEL_OR_ID ...] # wave sounds -> .wav
"""
import json
import signal
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
signal.signal(signal.SIGPIPE, signal.SIG_DFL)
from nwsnd import (NwFile, Rwsd, dataref, u16, u32, s32, cstr,  # noqa: E402
                   decode_wave, write_wav)

SOUND_TYPES = {1: "seq", 2: "strm", 3: "wave"}
SUFFIX = {b"RSEQ": "brseq", b"RWSD": "brwsd", b"RBNK": "brbnk", b"RSTM": "brstm",
          b"RWAR": "brwar", b"RWAV": "brwav"}


class Rsar(NwFile):
    def __init__(self, raw):
        super().__init__(raw, b"RSAR")
        (self.symb_off, self.symb_size, self.info_off, self.info_size,
         self.file_off, self.file_size) = struct.unpack_from(">6I", raw, 0x10)
        self._read_symb()
        self._read_info()

    # ---- SYMB
    def _read_symb(self):
        raw = self.raw
        s = self.symb_off + 8
        self._sbase = s
        tab = s + u32(raw, s)
        n = u32(raw, tab)
        self.strings = [cstr(raw, s + u32(raw, tab + 4 + 4 * i)) for i in range(n)]

    def string(self, idx):
        if idx == 0xFFFFFFFF or idx >= len(self.strings):
            return None
        return self.strings[idx]

    # ---- INFO
    def _table(self, off):
        """Table<DataRef<T>> at INFO-relative off -> list of INFO-relative offsets."""
        raw, b = self.raw, self._ibase
        o = b + off
        return [dataref(raw, o + 4 + 8 * i) for i in range(u32(raw, o))]

    def _read_info(self):
        raw = self.raw
        b = self._ibase = self.info_off + 8
        refs = [dataref(raw, b + 8 * i)[1] for i in range(6)]
        sound_t, bank_t, player_t, file_t, group_t, pinfo = refs

        self.sounds = []
        for i, (_, off) in enumerate(self._table(sound_t)):
            o = b + off
            sid, fid, pid = struct.unpack_from(">3I", raw, o)
            _, p3d = dataref(raw, o + 0xC)
            vol, prio, stype, remote = raw[o + 0x14:o + 0x18]
            dtype, sub = dataref(raw, o + 0x18)
            up0, up1 = struct.unpack_from(">2I", raw, o + 0x20)
            pan_mode, pan_curve, actor = raw[o + 0x28:o + 0x2B]
            s = {"id": i, "label": self.string(sid), "file": fid, "player": pid,
                 "volume": vol, "player_priority": prio,
                 "type": SOUND_TYPES.get(stype, stype), "remote_filter": remote,
                 "user_param": [up0, up1], "pan_mode": pan_mode,
                 "pan_curve": pan_curve, "actor_player": actor}
            if p3d:
                q = b + p3d
                s["3d"] = {"flags": u32(raw, q), "decay_curve": raw[q + 4],
                           "decay_ratio": raw[q + 5], "doppler": raw[q + 6]}
            q = b + sub
            if stype == 1:
                s["seq"] = {"data_offset": u32(raw, q), "bank": u32(raw, q + 4),
                            "alloc_track": u32(raw, q + 8),
                            "channel_priority": raw[q + 0xC],
                            "release_priority_fix": raw[q + 0xD]}
            elif stype == 2:
                s["strm"] = {"start_position": u32(raw, q),
                             "alloc_channels": u16(raw, q + 4),
                             "alloc_track_flag": u16(raw, q + 6)}
            elif stype == 3:
                s["wave"] = {"index": s32(raw, q), "alloc_track": u32(raw, q + 4),
                             "channel_priority": raw[q + 8],
                             "release_priority_fix": raw[q + 9]}
            self.sounds.append(s)

        self.banks = []
        for i, (_, off) in enumerate(self._table(bank_t)):
            sid, fid = struct.unpack_from(">2I", raw, b + off)
            self.banks.append({"id": i, "label": self.string(sid), "file": fid})

        self.players = []
        for i, (_, off) in enumerate(self._table(player_t)):
            o = b + off
            self.players.append({"id": i, "label": self.string(u32(raw, o)),
                                 "max_sounds": raw[o + 4], "heap_size": u32(raw, o + 8)})

        self.files = []
        for i, (_, off) in enumerate(self._table(file_t)):
            o = b + off
            size, wsize, entry = struct.unpack_from(">IIi", raw, o)
            _, path = dataref(raw, o + 0xC)
            _, pos_t = dataref(raw, o + 0x14)
            positions = []
            if pos_t:
                for _, po in self._table(pos_t):
                    positions.append(struct.unpack_from(">2I", raw, b + po))
            self.files.append({"id": i, "size": size, "wave_size": wsize,
                               "entry": entry,
                               "external": cstr(raw, b + path) if path else None,
                               "positions": positions})  # (group, index)

        self.groups = []
        for i, (_, off) in enumerate(self._table(group_t)):
            o = b + off
            sid, entry = struct.unpack_from(">Ii", raw, o)
            _, path = dataref(raw, o + 8)
            goff, gsize, woff, wsize = struct.unpack_from(">4I", raw, o + 0x10)
            _, items_t = dataref(raw, o + 0x20)
            items = []
            for _, io in self._table(items_t):
                fid, ioff, isize, iwoff, iwsize = struct.unpack_from(">5I", raw, b + io)
                items.append({"file": fid, "offset": ioff, "size": isize,
                              "wave_offset": iwoff, "wave_size": iwsize})
            self.groups.append({"id": i, "label": self.string(sid), "entry": entry,
                                "external": cstr(raw, b + path) if path else None,
                                "offset": goff, "size": gsize,
                                "wave_offset": woff, "wave_size": wsize,
                                "items": items})

        o = b + pinfo
        keys = ("seq_sounds", "seq_tracks", "strm_sounds", "strm_tracks",
                "strm_channels", "wave_sounds", "wave_tracks")
        self.player_info = dict(zip(keys, struct.unpack_from(">7H", raw, o)))

        # file id -> label of sounds/banks using it (for naming)
        self.file_names = {}
        for s in self.sounds:
            self.file_names.setdefault(s["file"], s["label"])
        for bk in self.banks:
            self.file_names.setdefault(bk["file"], bk["label"])

    # ---- data access
    def file_data(self, fid):
        """Return (main bytes, wave bytes or None) for file fid, taken from the
        first group that contains it. External files return (None, None)."""
        f = self.files[fid]
        if f["external"] or not f["positions"]:
            return None, None
        gid, idx = f["positions"][0]
        g = self.groups[gid]
        it = g["items"][idx]
        main = self.raw[g["offset"] + it["offset"]:g["offset"] + it["offset"] + it["size"]]
        wav = None
        if it["wave_size"]:
            w = g["wave_offset"] + it["wave_offset"]
            wav = self.raw[w:w + it["wave_size"]]
        return main, wav

    def sound(self, key):
        if isinstance(key, int) or key.isdigit():
            return self.sounds[int(key)]
        for s in self.sounds:
            if s["label"] == key:
                return s
        raise KeyError(key)

    def decode_wave_sound(self, s):
        """Decode a wave sound (type 'wave'): returns (channels, rate) or None."""
        main, wav = self.file_data(s["file"])
        if main is None or wav is None:
            return None
        rwsd = Rwsd(main)
        sub = rwsd.sounds[s["wave"]["index"]]
        if not sub["notes"]:
            return None
        widx = sub["notes"][0]["wave"]
        info = rwsd.waves[widx]
        # WaveInfo.dataOffset (+ channel offset) is relative to the file's
        # sample pool (the pWaveAddr nw4r passes to ReadWaveParam).
        return decode_wave(info, wav), info["rate"]


def summary(r):
    from collections import Counter
    types = Counter(s["type"] for s in r.sounds)
    kinds = Counter()
    for f in r.files:
        if f["external"]:
            kinds["external"] += 1
            continue
        main, _ = r.file_data(f["id"])
        kinds[main[:4].decode() if main else "none"] += 1
    return {"version": r.version_str, "size": r.size, "strings": len(r.strings),
            "sounds": len(r.sounds), "sound_types": dict(types),
            "banks": len(r.banks), "players": len(r.players),
            "files": len(r.files), "file_kinds": dict(kinds),
            "groups": len(r.groups), "player_info": r.player_info}


def main(argv):
    if len(argv) < 3:
        print(__doc__)
        return 1
    with open(argv[1], "rb") as fh:
        r = Rsar(fh.read())
    cmd = argv[2]
    if cmd == "summary":
        print(json.dumps(summary(r), indent=1))
    elif cmd == "sounds":
        want = argv[argv.index("--type") + 1] if "--type" in argv else None
        for s in r.sounds:
            if want is None or s["type"] == want:
                print(json.dumps(s))
    elif cmd in ("banks", "players", "files"):
        for x in getattr(r, cmd):
            print(json.dumps(x))
    elif cmd == "groups":
        for g in r.groups:
            g = dict(g)
            g["items"] = len(g["items"])
            print(json.dumps(g))
    elif cmd == "extract":
        out = argv[3]
        os.makedirs(out, exist_ok=True)
        n = 0
        for f in r.files:
            main_b, wav = r.file_data(f["id"])
            if main_b is None:
                continue
            name = "%04d_%s" % (f["id"], r.file_names.get(f["id"]) or "file")
            ext = SUFFIX.get(main_b[:4], "bin")
            with open(os.path.join(out, "%s.%s" % (name, ext)), "wb") as fh:
                fh.write(main_b)
            if wav:
                with open(os.path.join(out, "%s.wavedata" % name), "wb") as fh:
                    fh.write(wav)
            n += 1
        print("extracted %d files to %s" % (n, out))
    elif cmd == "wav":
        out = argv[3]
        os.makedirs(out, exist_ok=True)
        keys = []
        if "--sound" in argv:
            keys = argv[argv.index("--sound") + 1:]
        sel = [r.sound(k) for k in keys] if keys else [s for s in r.sounds if s["type"] == "wave"]
        n = 0
        for s in sel:
            if s["type"] != "wave":
                print("skip %s (%s sound; see docs)" % (s["label"], s["type"]), file=sys.stderr)
                continue
            res = r.decode_wave_sound(s)
            if not res:
                continue
            chans, rate = res
            write_wav(os.path.join(out, "%s.wav" % (s["label"] or s["id"])), chans, rate)
            n += 1
        print("wrote %d wav files to %s" % (n, out))
    else:
        print(__doc__)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
