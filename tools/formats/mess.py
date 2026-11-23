"""Reader for FE10 message files (Mess/*.m).

A .m file is an uncompressed IS binary container (see isbin.py) with no
pointer table: every label is a message ID (MID_*, MS_*, MESS_*, ...) whose
data offset points at a NUL-terminated Shift-JIS string. English files carry
an "e_" prefix (e_c0314.m), other prefixes are other languages (Japanese has
none). Strings mix text with control codes; see docs/formats/text.md.

CLI:
  mess.py FILE.m                  dump all messages with readable control tags
  mess.py FILE.m --raw            keep raw control bytes (escaped)
  mess.py FILE.m --plain          text only, no control tags
  mess.py FILE.m --json OUT.json  {label: string-with-tags}
  mess.py FILE.m --id MS_0314_OP_01
"""
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from isbin import open_file  # noqa: E402

ENC = "shift_jis"


def _is_sjis_lead(b):
    return 0x81 <= b <= 0x9F or 0xE0 <= b <= 0xFC


# ---------------------------------------------------------------------------
# Tokenizer. Argument layout follows the game's own skipper
# (fn_8026FE?? jump table in 8026C000.c) and the conversation interpreter
# fn_80149434:
#   0x01 + 1 char        0x02 + 2 chars       0x03 + 3 chars
#   0x04 + one '|'-terminated field         0x05 + '|' fields until "||"
#   0x07, 0x08, 0x0B, 0x0C, 0x0D, 0x0E + 2 chars
#   0x09, 0x0A('\n'), 0x0F, 0x10, 0x11, 0x12  no arguments
# ---------------------------------------------------------------------------
ARGLEN = {0x01: 1, 0x02: 2, 0x03: 3, 0x07: 2, 0x08: 2, 0x0B: 2, 0x0C: 2,
          0x0D: 2, 0x0E: 2}


def tokenize(raw: bytes):
    """Yield ('text', str) and ('cmd', code:int, args) tokens.

    args is a str for fixed-length commands, a list of str for 0x04/0x05.
    '\\n' (0x0A) is returned as text; '#' inline format codes stay in text.
    """
    i, n = 0, len(raw)
    buf = bytearray()

    def flush():
        if buf:
            t = bytes(buf).decode(ENC, "replace")
            buf.clear()
            return ("text", t)
        return None

    while i < n:
        c = raw[i]
        if c == 0x0A or c >= 0x20:
            if _is_sjis_lead(c) and i + 1 < n:
                buf += raw[i:i + 2]
                i += 2
            else:
                buf.append(c)
                i += 1
            continue
        t = flush()
        if t:
            yield t
        i += 1
        if c in ARGLEN:
            k = ARGLEN[c]
            yield ("cmd", c, raw[i:i + k].decode(ENC, "replace"))
            i += k
        elif c in (0x04, 0x05):
            fields = []
            while i < n:
                j = raw.index(b"|", i)
                fields.append(raw[i:j].decode(ENC, "replace"))
                i = j + 1
                if c == 0x04 or j == i - 1 and fields[-1] == "":
                    break
            if c == 0x05 and fields and fields[-1] == "":
                fields.pop()
            yield ("cmd", c, fields)
        else:
            yield ("cmd", c, "")
    t = flush()
    if t:
        yield t


# Readable names for fixed-argument commands (see docs/formats/text.md).
SIMPLE_NAMES = {
    0x09: "CloseSpeaker",     # remove current speaker's face/window, then wait
    0x0F: "CloseSpeakerNoWait",
    0x10: "NewPage",          # clear the balloon, continue
    0x11: "A",                # wait for button press
    0x12: "Yield",
}


def tag(tok):
    kind = tok[0]
    if kind == "text":
        return tok[1]
    _, c, a = tok
    if c == 0x01:
        return "[F:%s]" % a
    if c == 0x02:
        if a[0] == "w":
            return "[W%s]" % a[1]
        return "[%s]" % a
    if c == 0x03:
        return "[3:%s]" % a
    if c == 0x04:
        return "[%s]" % a[0] if a else "[4]"
    if c == 0x05:
        return "[%s:%s]" % (a[0], ",".join(a[1:])) if a else "[5]"
    if c == 0x07:
        return "[Speaker:%s]" % a
    if c == 0x08:
        return "[Say:%s]" % a
    if c == 0x0E:
        return "[SayNoWait:%s]" % a
    if c == 0x0B:
        return "[B:%s]" % a
    if c == 0x0C:
        return "[Select:%s]" % a
    if c == 0x0D:
        return "[Assign:%s]" % a
    return "[%s]" % SIMPLE_NAMES.get(c, "%02X" % c)


def render(raw: bytes, mode="tags"):
    if mode == "raw":
        return raw.decode(ENC, "backslashreplace")
    out = []
    for tok in tokenize(raw):
        if tok[0] == "text":
            out.append(tok[1])
        elif mode == "tags":
            out.append(tag(tok))
        elif tok[1] in (0x10,):
            out.append("\n")
    return "".join(out)


class MessFile:
    def __init__(self, path):
        self.bin = open_file(path)
        self.messages = {}   # label -> raw bytes
        for off, name in sorted(self.bin.label_list):
            d = self.bin.data
            self.messages[name] = d[off:d.index(b"\0", off)]

    def get(self, label, mode="tags"):
        return render(self.messages[label], mode)

    def items(self, mode="tags"):
        for k, v in self.messages.items():
            yield k, render(v, mode)


if __name__ == "__main__":
    import argparse
    ap = argparse.ArgumentParser()
    ap.add_argument("file")
    g = ap.add_mutually_exclusive_group()
    g.add_argument("--raw", action="store_true")
    g.add_argument("--plain", action="store_true")
    ap.add_argument("--json")
    ap.add_argument("--id")
    a = ap.parse_args()
    mode = "raw" if a.raw else "plain" if a.plain else "tags"
    m = MessFile(a.file)
    if a.json:
        with open(a.json, "w", encoding="utf-8") as f:
            json.dump(dict(m.items(mode)), f, ensure_ascii=False, indent=1)
    else:
        for k, v in m.items(mode):
            if a.id and k != a.id:
                continue
            print("== %s\n%s\n" % (k, v))
