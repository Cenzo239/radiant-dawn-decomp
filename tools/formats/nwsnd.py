"""Shared readers for the NintendoWare for Revolution (NW4R) sound formats used
by FE10: RSAR (sound archive), RSTM (stream), RWSD (wave sound data), RBNK
(instrument bank), RSEQ (MML sequence), RWAR (wave archive), RWAV (wave), and
a DSP-ADPCM decoder plus a WAV writer. Python 3.9 standard library only.

All integers are big-endian. Every NW4R file starts with the common header
  0x00 char[4] magic, 0x04 u16 BOM 0xFEFF, 0x06 u16 version (major<<8|minor),
  0x08 u32 file size, 0x0C u16 header size, 0x0E u16 block count,
followed by (u32 offset, u32 size) per block. Every block starts with
char[4] magic + u32 size. A "DataRef" is 8 bytes {u8 refType (0 = address,
1 = offset), u8 dataType, u16 pad, u32 value}; offsets are relative to the
start of the block's payload (block start + 8) unless noted.

Layouts follow the FE10 versions of the nw4r snd headers in
lib/ogws/include/nw4r/snd. Versions on the FE10 disc: RSAR 1.4, RSTM 1.0,
RWSD 1.2, RBNK 1.1, RSEQ 1.0. RWAR/RWAV readers are included for completeness
(other NW4R games, modding); FE10's archive stores raw sample pools instead.
"""
import struct
import wave

FMT_PCM8, FMT_PCM16, FMT_ADPCM = 0, 1, 2
FMT_NAMES = {0: "pcm8", 1: "pcm16", 2: "adpcm"}


def u8(b, o):
    return b[o]


def u16(b, o):
    return struct.unpack_from(">H", b, o)[0]


def u32(b, o):
    return struct.unpack_from(">I", b, o)[0]


def s32(b, o):
    return struct.unpack_from(">i", b, o)[0]


def cstr(b, o):
    e = b.index(b"\0", o)
    return b[o:e].decode("ascii", "replace")


def dataref(b, o):
    """Return (dataType, value) of the DataRef at o; value is an offset."""
    ref_type, data_type = b[o], b[o + 1]
    return data_type, u32(b, o + 4)


class NwFile:
    """Common header + block list."""

    def __init__(self, raw, magic=None):
        if magic and raw[:4] != magic:
            raise ValueError("not a %s file (magic %r)" % (magic.decode(), raw[:4]))
        if u16(raw, 4) != 0xFEFF:
            raise ValueError("bad BOM")
        self.raw = raw
        self.magic = raw[:4].decode("ascii")
        self.version = u16(raw, 6)
        self.size = u32(raw, 8)
        self.header_size = u16(raw, 0xC)
        self.nblocks_field = u16(raw, 0xE)
        # The block-count field is not reliable (RSTM says 2 but has HEAD,
        # ADPC, DATA), so read (offset, size) pairs up to the header size.
        self.blocks = {}
        for i in range((self.header_size - 0x10) // 8):
            off, size = struct.unpack_from(">2I", raw, 0x10 + 8 * i)
            if off == 0 or off + 8 > len(raw):
                continue
            tag = raw[off:off + 4].decode("ascii", "replace")
            self.blocks[tag] = (off, size)

    def block(self, tag):
        off, size = self.blocks[tag]
        return off + 8, off + size  # payload start, end

    @property
    def version_str(self):
        return "%d.%d" % (self.version >> 8, self.version & 0xFF)


# --------------------------------------------------------------------------
# DSP-ADPCM

def read_adpcm_info(b, o):
    """AdpcmInfo (0x30 bytes): s16 coef[16], u16 gain, u16 pred_scale,
    s16 yn1, s16 yn2, u16 loop_pred_scale, s16 loop_yn1, s16 loop_yn2, u16 pad."""
    coef = struct.unpack_from(">16h", b, o)
    gain, ps, yn1, yn2, lps, lyn1, lyn2 = struct.unpack_from(">HHhhHhh", b, o + 0x20)
    return {"coef": coef, "gain": gain, "pred_scale": ps, "yn1": yn1, "yn2": yn2,
            "loop_pred_scale": lps, "loop_yn1": lyn1, "loop_yn2": lyn2}


def decode_adpcm(data, nsamples, coef, hist1=0, hist2=0):
    """Decode Nintendo DSP-ADPCM (8-byte frames, 14 samples each).
    Returns (list of int16, hist1, hist2)."""
    out = []
    append = out.append
    pos = 0
    n = len(data)
    while len(out) < nsamples and pos < n:
        ps = data[pos]
        c1 = coef[(ps >> 4) * 2]
        c2 = coef[(ps >> 4) * 2 + 1]
        scale = 1 << (ps & 0xF)
        for i in range(14):
            byte = data[pos + 1 + (i >> 1)] if pos + 1 + (i >> 1) < n else 0
            nib = (byte >> 4) if (i & 1) == 0 else (byte & 0xF)
            if nib >= 8:
                nib -= 16
            s = ((nib * scale) << 11) + 1024 + c1 * hist1 + c2 * hist2
            s >>= 11
            if s > 32767:
                s = 32767
            elif s < -32768:
                s = -32768
            hist2 = hist1
            hist1 = s
            append(s)
            if len(out) >= nsamples:
                break
        pos += 8
    return out, hist1, hist2


def decode_pcm(data, fmt, nsamples):
    if fmt == FMT_PCM16:
        n = min(nsamples, len(data) // 2)
        return list(struct.unpack_from(">%dh" % n, data, 0))
    if fmt == FMT_PCM8:
        n = min(nsamples, len(data))
        return [((x - 256) if x >= 128 else x) << 8 for x in data[:n]]
    raise ValueError("format %d" % fmt)


def dsp_addr_to_sample(addr, fmt):
    """nw4r AxVoice::GetSampleByDspAddress with base 0."""
    if fmt == FMT_ADPCM:
        return (addr // 16) * 14 + (addr % 16) - 2
    return addr  # PCM8/PCM16 loop fields are already sample counts


def adpcm_bytes_for(nsamples):
    frames = (nsamples + 13) // 14
    return frames * 8


def write_wav(path, channels, rate):
    """channels: list of equal-length int16 sample lists."""
    nch = len(channels)
    n = min(len(c) for c in channels) if channels else 0
    inter = []
    for i in range(n):
        for c in channels:
            inter.append(c[i])
    w = wave.open(path, "wb")
    w.setnchannels(nch)
    w.setsampwidth(2)
    w.setframerate(rate)
    w.writeframes(struct.pack("<%dh" % len(inter), *inter))
    w.close()


# --------------------------------------------------------------------------
# WaveInfo (shared by RWAV, RWSD WAVE block, RBNK WAVE block)

def read_wave_info(b, o):
    """WaveInfo at o (offsets inside are relative to o). Returns a dict."""
    fmt, loop, nch, rate24 = b[o], b[o + 1], b[o + 2], b[o + 3]
    rate = (rate24 << 16) + u16(b, o + 4)
    loop_start, loop_end, ch_tab, data_off = struct.unpack_from(">4I", b, o + 8)
    chans = []
    for i in range(nch):
        co = o + u32(b, o + ch_tab + 4 * i)
        cdata, cadpcm, vfl, vfr, vrl, vrr = struct.unpack_from(">6I", b, co)
        chans.append({
            "data_offset": cdata,
            "adpcm": read_adpcm_info(b, o + cadpcm) if cadpcm else None,
            "volume": (vfl, vfr, vrl, vrr),
        })
    return {
        "format": fmt, "loop": loop, "channels": nch, "rate": rate,
        "loop_start_addr": loop_start, "loop_end_addr": loop_end,
        "loop_start": dsp_addr_to_sample(loop_start, fmt),
        "nsamples": dsp_addr_to_sample(loop_end, fmt) + 1,
        "data_offset": data_off, "chan": chans,
    }


def decode_wave(info, wave_base):
    """Decode all channels of a WaveInfo whose sample data lives in the bytes
    object wave_base (sample offset = info.data_offset + channel.data_offset)."""
    out = []
    n = info["nsamples"]
    for ch in info["chan"]:
        start = info["data_offset"] + ch["data_offset"]
        if info["format"] == FMT_ADPCM:
            raw = wave_base[start:start + adpcm_bytes_for(n)]
            a = ch["adpcm"]
            pcm, _, _ = decode_adpcm(raw, n, a["coef"], a["yn1"], a["yn2"])
        else:
            width = 2 if info["format"] == FMT_PCM16 else 1
            pcm = decode_pcm(wave_base[start:start + n * width], info["format"], n)
        out.append(pcm)
    return out


# --------------------------------------------------------------------------
# RWAV / RWAR

class Rwav(NwFile):
    """RWAV: INFO block = WaveInfo; DATA block = samples. WaveInfo.dataOffset
    is relative to the start of the RWAV file (points at DATA payload)."""

    def __init__(self, raw):
        super().__init__(raw, b"RWAV")
        start, _ = self.block("INFO")
        self.info = read_wave_info(raw, start)

    def decode(self):
        return decode_wave(self.info, self.raw)


class Rwar(NwFile):
    """RWAR: TABL block {u32 count; {u8 refType, pad[3], u32 offset, u32 size}[]}
    with offsets relative to the DATA block start; DATA holds RWAV files."""

    def __init__(self, raw):
        super().__init__(raw, b"RWAR")
        t, _ = self.block("TABL")
        d_off, _ = self.blocks["DATA"]
        count = u32(raw, t)
        self.entries = []
        for i in range(count):
            off, size = struct.unpack_from(">2I", raw, t + 4 + 12 * i + 4)
            self.entries.append((d_off + off, size))

    def __len__(self):
        return len(self.entries)

    def wave(self, i):
        off, size = self.entries[i]
        return Rwav(self.raw[off:off + size])


# --------------------------------------------------------------------------
# RSTM

class Rstm(NwFile):
    def __init__(self, raw):
        super().__init__(raw, b"RSTM")
        h, _ = self.block("HEAD")
        _, info_off = dataref(raw, h)
        tt_type, tt_off = dataref(raw, h + 8)
        _, ct_off = dataref(raw, h + 16)
        o = h + info_off
        (self.format, self.loop, self.nch, rate24, rate, self.block_header_offset,
         self.loop_start, self.nsamples, self.data_offset, self.nblocks,
         self.block_size, self.block_samples, self.last_block_size,
         self.last_block_samples, self.last_block_padded, self.adpcm_interval,
         self.adpcm_size) = struct.unpack_from(">4BHH11I", raw, o)
        self.rate = (rate24 << 16) + rate
        # tracks
        o = h + tt_off
        ntracks, ttype = raw[o], raw[o + 1]
        self.track_type = ttype
        self.tracks = []
        for i in range(ntracks):
            _, toff = dataref(raw, o + 4 + 8 * i)
            t = h + toff
            if ttype == 1:
                vol, pan = raw[t], raw[t + 1]
                cnt = raw[t + 8]
                idx = list(raw[t + 9:t + 9 + cnt])
            else:
                vol, pan = 127, 64
                cnt = raw[t]
                idx = list(raw[t + 1:t + 1 + cnt])
            self.tracks.append({"volume": vol, "pan": pan, "channels": idx})
        # channels
        o = h + ct_off
        cnt = raw[o]
        self.adpcm = []
        for i in range(cnt):
            _, coff = dataref(raw, o + 4 + 8 * i)
            _, aoff = dataref(raw, h + coff)
            self.adpcm.append(read_adpcm_info(raw, h + aoff) if self.format == FMT_ADPCM else None)

    def summary(self):
        return {
            "format": FMT_NAMES.get(self.format, self.format), "channels": self.nch,
            "rate": self.rate, "samples": self.nsamples,
            "seconds": round(self.nsamples / self.rate, 3) if self.rate else 0,
            "loop": bool(self.loop), "loop_start": self.loop_start,
            "blocks": self.nblocks, "block_size": self.block_size,
            "tracks": self.tracks,
        }

    def decode(self):
        """Return per-channel int16 lists. Blocks are interleaved by channel:
        block b of channel c is at DATA payload + data_offset-relative start.
        The ADPC block stores {s16 yn1, s16 yn2} per block per channel; the
        decoder state carries over naturally, so it is only needed for seeking."""
        d, _ = self.block("DATA")
        base = d + u32(self.raw, d)  # first u32 of DATA payload = sample start offset
        chans = [[] for _ in range(self.nch)]
        hist = [(a["yn1"], a["yn2"]) if a else (0, 0) for a in self.adpcm] or [(0, 0)] * self.nch
        pos = base
        for b in range(self.nblocks):
            last = b == self.nblocks - 1
            bsize = self.last_block_padded if last else self.block_size
            bsamp = self.last_block_samples if last else self.block_samples
            for c in range(self.nch):
                chunk = self.raw[pos:pos + bsize]
                if self.format == FMT_ADPCM:
                    a = self.adpcm[c]
                    pcm, h1, h2 = decode_adpcm(chunk, bsamp, a["coef"], *hist[c])
                    hist[c] = (h1, h2)
                else:
                    pcm = decode_pcm(chunk, self.format, bsamp)
                chans[c].extend(pcm)
                pos += bsize
        return [c[:self.nsamples] for c in chans]


# --------------------------------------------------------------------------
# RWSD / RBNK / RSEQ

class Rwsd(NwFile):
    """DATA: u32 count, DataRef<Wsd>[]; Wsd = {WsdInfo, TrackTable, NoteTable}.
    WAVE: u32 count, u32 offset[] (relative to WAVE block start) -> WaveInfo."""

    def __init__(self, raw):
        super().__init__(raw, b"RWSD")
        d, _ = self.block("DATA")
        self.sounds = []
        for i in range(u32(raw, d)):
            _, wo = dataref(raw, d + 4 + 8 * i)
            w = d + wo
            _, info_o = dataref(raw, w)
            _, track_o = dataref(raw, w + 8)
            _, note_o = dataref(raw, w + 16)
            io = d + info_o
            pitch, = struct.unpack_from(">f", raw, io)
            snd = {"pitch": pitch, "pan": raw[io + 4], "surround_pan": raw[io + 5],
                   "fx_send": [raw[io + 6], raw[io + 7], raw[io + 8]],
                   "main_send": raw[io + 9], "notes": [], "tracks": []}
            no = d + note_o
            for j in range(u32(raw, no)):
                _, nref = dataref(raw, no + 4 + 8 * j)
                n = d + nref
                snd["notes"].append({
                    "wave": s32(raw, n), "attack": raw[n + 4], "decay": raw[n + 5],
                    "sustain": raw[n + 6], "release": raw[n + 7], "hold": raw[n + 8],
                    "key": raw[n + 0xC], "volume": raw[n + 0xD], "pan": raw[n + 0xE],
                    "pitch": struct.unpack_from(">f", raw, n + 0x10)[0]})
            to = d + track_o
            for j in range(u32(raw, to)):
                _, tref = dataref(raw, to + 4 + 8 * j)
                t = d + tref
                _, nt_o = dataref(raw, t)  # NoteEventTable
                events = []
                if nt_o:
                    e = d + nt_o
                    for k in range(u32(raw, e)):
                        _, eref = dataref(raw, e + 4 + 8 * k)
                        ev = d + eref
                        pos, length = struct.unpack_from(">2f", raw, ev)
                        events.append({"pos": pos, "length": length, "note": u32(raw, ev + 8)})
                snd["tracks"].append(events)
            self.sounds.append(snd)
        self.waves = []
        if "WAVE" in self.blocks:
            wo, _ = self.blocks["WAVE"]
            cnt = u32(raw, wo + 8)
            for i in range(cnt):
                self.waves.append(read_wave_info(raw, wo + u32(raw, wo + 12 + 4 * i)))


class Rbnk(NwFile):
    """DATA: Table<DataRegion> (one per program). A region is InstParam
    (dataType 1), RangeTable (2: u8 n, u8 key[n], then DataRegion[n] at
    4-aligned offset) or IndexTable (3: u8 min, u8 max, pad, DataRegion[]).
    WAVE: Table<DataRef<WaveInfo>> (offsets relative to WAVE payload)."""

    def __init__(self, raw):
        super().__init__(raw, b"RBNK")
        d, _ = self.block("DATA")
        self._d = d
        self.programs = []
        for i in range(u32(raw, d)):
            self.programs.append(self._region(d + 4 + 8 * i))
        self.waves = []
        if "WAVE" in self.blocks:
            w, _ = self.block("WAVE")
            for i in range(u32(raw, w)):
                _, o = dataref(raw, w + 4 + 8 * i)
                self.waves.append(read_wave_info(raw, w + o))

    def _region(self, ref_off, depth=0):
        raw, d = self.raw, self._d
        dtype, off = dataref(raw, ref_off)
        if off == 0 and dtype == 0:
            return None
        o = d + off
        if dtype == 1:
            return {"wave": s32(raw, o), "attack": raw[o + 4], "decay": raw[o + 5],
                    "sustain": raw[o + 6], "release": raw[o + 7], "hold": raw[o + 8],
                    "note_off_type": raw[o + 0xA], "alt_assign": raw[o + 0xB],
                    "key": raw[o + 0xC], "volume": raw[o + 0xD], "pan": raw[o + 0xE],
                    "pitch": struct.unpack_from(">f", raw, o + 0x10)[0]}
        if dtype == 2:
            n = raw[o]
            keys = list(raw[o + 1:o + 1 + n])
            base = o + ((1 + n + 3) & ~3)
            return {"range": [(k, self._region(base + 8 * j, depth + 1)) for j, k in enumerate(keys)]}
        if dtype == 3:
            lo, hi = raw[o], raw[o + 1]
            return {"index": lo, "to": hi,
                    "regions": [self._region(o + 4 + 8 * j, depth + 1) for j in range(hi - lo + 1)]}
        return {"unknown_type": dtype, "offset": off}


class Rseq(NwFile):
    """DATA: u32 offset (relative to DATA block start) of the MML byte code.
    LABL: u32 count, u32 offset[] (relative to LABL payload) -> {u32 data
    offset, u32 name length, char name[]}."""

    def __init__(self, raw):
        super().__init__(raw, b"RSEQ")
        do, dsize = self.blocks["DATA"]
        self.code_offset = do + u32(raw, do + 8)
        self.code = raw[self.code_offset:do + dsize]
        self.labels = []
        if "LABL" in self.blocks:
            l, _ = self.block("LABL")
            for i in range(u32(raw, l)):
                e = l + u32(raw, l + 4 + 4 * i)
                off, ln = u32(raw, e), u32(raw, e + 4)
                self.labels.append((raw[e + 8:e + 8 + ln].decode("ascii", "replace"), off))
