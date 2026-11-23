"""Nintendo LZ10 ("LZ77 type 0x10") decompressor used by FE10 *.cms / *.cmp files.

Header: u8 0x10, u24 little-endian decompressed size. Then groups of one flag
byte (MSB first) followed by 8 tokens: bit 0 -> literal byte, bit 1 -> 2-byte
back-reference: length = (b0 >> 4) + 3, distance = ((b0 & 0xF) << 8 | b1) + 1.
If the u24 size is 0, a u32 LE size follows (not seen in FE10, supported anyway).
"""
import sys


def decompress(data: bytes) -> bytes:
    if not data or data[0] != 0x10:
        raise ValueError("not LZ10 data (first byte %r)" % (data[:1],))
    size = data[1] | data[2] << 8 | data[3] << 16
    pos = 4
    if size == 0:
        size = int.from_bytes(data[4:8], "little")
        pos = 8
    out = bytearray()
    while len(out) < size:
        flags = data[pos]
        pos += 1
        for bit in range(8):
            if len(out) >= size:
                break
            if flags & (0x80 >> bit):
                b0, b1 = data[pos], data[pos + 1]
                pos += 2
                length = (b0 >> 4) + 3
                dist = ((b0 & 0xF) << 8 | b1) + 1
                start = len(out) - dist
                if start < 0:
                    raise ValueError("back-reference before start of output")
                for i in range(length):
                    out.append(out[start + i])
            else:
                out.append(data[pos])
                pos += 1
    return bytes(out[:size])


def is_lz10(data: bytes) -> bool:
    return len(data) >= 4 and data[0] == 0x10


def load(path: str) -> bytes:
    """Read a file, transparently decompressing LZ10 (.cms/.cmp)."""
    with open(path, "rb") as f:
        data = f.read()
    if path.endswith((".cms", ".cmp")) and is_lz10(data):
        return decompress(data)
    return data


if __name__ == "__main__":
    if len(sys.argv) != 3:
        sys.exit("usage: lz10.py IN.cms OUT")
    with open(sys.argv[1], "rb") as f:
        out = decompress(f.read())
    with open(sys.argv[2], "wb") as f:
        f.write(out)
    print("%d bytes" % len(out))
