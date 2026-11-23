"""Reader for the FE10 "pack" archive (usually stored LZ10-compressed as *.cmp,
uncompressed as *.pak).

All integers big-endian.
  0x00 char[4] "pack"
  0x04 u16 file_count
  0x06 u16 reserved (0)
  0x08 entry[file_count], 16 bytes each:
         u32 reserved (0)  (runtime slot: the game stores a pointer here)
         u32 name_offset   absolute offset of NUL-terminated ASCII name
         u32 data_offset   absolute offset of file data (32-byte aligned)
         u32 size          file size in bytes
  ...  name strings, then file data
"""
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from lz10 import load  # noqa: E402


class Pack:
    def __init__(self, raw: bytes):
        if raw[:4] != b"pack":
            raise ValueError("not a pack archive")
        count, = struct.unpack_from(">H", raw, 4)
        self.raw = raw
        self.entries = []  # (name, offset, size)
        for i in range(count):
            _, noff, doff, size = struct.unpack_from(">4I", raw, 8 + 16 * i)
            name = raw[noff:raw.index(b"\0", noff)].decode("ascii", "replace")
            self.entries.append((name, doff, size))

    def names(self):
        return [e[0] for e in self.entries]

    def get(self, name) -> bytes:
        for n, off, size in self.entries:
            if n == name:
                return self.raw[off:off + size]
        raise KeyError(name)

    def items(self):
        for n, off, size in self.entries:
            yield n, self.raw[off:off + size]


def open_file(path):
    return Pack(load(path))


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit("usage: pack.py FILE.cmp|.pak [OUTDIR]")
    p = open_file(sys.argv[1])
    for n, off, size in p.entries:
        print("%08x %8d  %s" % (off, size, n))
    if len(sys.argv) > 2:
        os.makedirs(sys.argv[2], exist_ok=True)
        for n, data in p.items():
            with open(os.path.join(sys.argv[2], os.path.basename(n)), "wb") as f:
                f.write(data)
