"""Reader for NW4R streams (Sound/strm/*.brstm, RSTM 1.0) and the single-file
NW4R sound formats extracted from the archive (.brwav, .brwar, .brwsd,
.brbnk, .brseq). See docs/formats/sound.md.

CLI:
  brstm.py info FILE [FILE...]          # JSON summary per file
  brstm.py wav FILE.brstm OUT.wav       # decode a stream (all channels)
  brstm.py wav FILE.brstm OUTDIR --tracks   # one stereo/mono wav per track
  brstm.py waves FILE.brwar OUTDIR      # every RWAV in a wave archive -> wav
  brstm.py dump FILE.brwsd|.brbnk|.brseq    # structure as JSON
  brstm.py scan DIR                     # summary table of all .brstm in DIR
"""
import json
import os
import signal
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from nwsnd import Rstm, Rwar, Rwav, Rwsd, Rbnk, Rseq, write_wav  # noqa: E402

signal.signal(signal.SIGPIPE, signal.SIG_DFL)


def load(path):
    with open(path, "rb") as fh:
        raw = fh.read()
    cls = {b"RSTM": Rstm, b"RWAR": Rwar, b"RWAV": Rwav, b"RWSD": Rwsd,
           b"RBNK": Rbnk, b"RSEQ": Rseq}.get(raw[:4])
    if cls is None:
        raise ValueError("%s: unknown magic %r" % (path, raw[:4]))
    return cls(raw)


def main(argv):
    if len(argv) < 3:
        print(__doc__)
        return 1
    cmd = argv[1]
    if cmd == "info":
        for p in argv[2:]:
            f = load(p)
            d = {"file": os.path.basename(p), "magic": f.magic, "version": f.version_str}
            if isinstance(f, Rstm):
                d.update(f.summary())
            elif isinstance(f, Rwav):
                d.update({k: v for k, v in f.info.items() if k != "chan"})
            elif isinstance(f, Rwar):
                d["waves"] = len(f)
            print(json.dumps(d))
    elif cmd == "wav":
        f = load(argv[2])
        chans = f.decode()
        if "--tracks" in argv:
            os.makedirs(argv[3], exist_ok=True)
            base = os.path.splitext(os.path.basename(argv[2]))[0]
            for i, t in enumerate(f.tracks):
                write_wav(os.path.join(argv[3], "%s_track%d.wav" % (base, i)),
                          [chans[c] for c in t["channels"]], f.rate)
        else:
            write_wav(argv[3], chans, f.rate)
    elif cmd == "waves":
        f = load(argv[2])
        os.makedirs(argv[3], exist_ok=True)
        for i in range(len(f)):
            w = f.wave(i)
            write_wav(os.path.join(argv[3], "%03d.wav" % i), w.decode(), w.info["rate"])
        print("wrote %d waves" % len(f))
    elif cmd == "dump":
        f = load(argv[2])
        if isinstance(f, Rwsd):
            out = {"sounds": f.sounds,
                   "waves": [{k: v for k, v in w.items() if k != "chan"} for w in f.waves]}
        elif isinstance(f, Rbnk):
            out = {"programs": f.programs,
                   "waves": [{k: v for k, v in w.items() if k != "chan"} for w in f.waves]}
        elif isinstance(f, Rseq):
            out = {"labels": f.labels, "code_size": len(f.code)}
        else:
            out = {"magic": f.magic}
        print(json.dumps(out, indent=1))
    elif cmd == "scan":
        d = argv[2]
        for name in sorted(os.listdir(d)):
            if not name.endswith(".brstm"):
                continue
            f = load(os.path.join(d, name))
            print("%-48s %-5s ch=%d tr=%d %5d Hz %8.2f s loop=%s" % (
                name, f.version_str, f.nch, len(f.tracks), f.rate,
                f.nsamples / f.rate, f.loop_start if f.loop else "-"))
    else:
        print(__doc__)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
