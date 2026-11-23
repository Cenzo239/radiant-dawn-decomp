"""Reader for Intelligent Systems' generic relocatable binary container.

Used (after optional LZ10 decompression) by FE10Data.cms, FE10Anim.cms,
FE10Battle.cms, Mess/*.m, zmap/*/dispos_*.bin, Shop/*.bin, gmap/rect/*.bin, ...
See docs/FORMATS.md, section "IS binary container".

All integers are big-endian.

  0x00 u32 file_size
  0x04 u32 data_size          data region is file[0x20 : 0x20 + data_size]
  0x08 u32 pointer_count      pointer (relocation) table entries
  0x0C u32 label_count        symbol table A entries (the named tables)
  0x10 u32 label2_count       symbol table B entries; 0 in all data files,
                              1 in 56 particle .gs files. The model loader
                              fn_80075874 treats A as imports and B as exports
                              (see docs/formats/graphics.md); data tables are
                              looked up by name in A.
  0x14 u8[12] reserved (zero; the runtime writes a magic into 0x18..0x1E)
  0x20 data[data_size]
  ...  u32 pointer_offsets[pointer_count]   offsets (into data) of u32 fields
                                            that hold data-relative pointers
  ...  {u32 data_offset, u32 name_offset}[label_count + label2_count]
  ...  char names[]           NUL-terminated, name_offset relative to here

At load time the game adds the data base address to every pointer field and
looks labels up by name (e.g. "PersonData", "MESS_..." ...).
"""
import struct
import sys

HEADER_SIZE = 0x20


class ISBin:
    def __init__(self, raw: bytes):
        if len(raw) < HEADER_SIZE:
            raise ValueError("too small")
        (self.file_size, self.data_size, self.pointer_count,
         self.label_count, self.label2_count) = struct.unpack_from(">5I", raw, 0)
        if self.file_size != len(raw) or HEADER_SIZE + self.data_size > len(raw):
            raise ValueError("not an IS binary container (size mismatch)")
        self.raw = raw
        self.data = raw[HEADER_SIZE:HEADER_SIZE + self.data_size]
        p = HEADER_SIZE + self.data_size
        self.pointers = list(struct.unpack_from(">%dI" % self.pointer_count, raw, p))
        p += 4 * self.pointer_count
        nlab = self.label_count + self.label2_count
        lab = [struct.unpack_from(">2I", raw, p + 8 * i) for i in range(nlab)]
        strtab = p + 8 * nlab
        self.labels = {}           # name -> data offset
        self.label_list = []       # [(offset, name)] in file order
        for off, noff in lab:
            name = self._cstr(strtab + noff, raw)
            self.labels[name] = off
            self.label_list.append((off, name))
        self.pointer_set = set(self.pointers)

    @staticmethod
    def _cstr(pos, buf, enc="shift_jis"):
        end = buf.index(b"\0", pos)
        return buf[pos:end].decode(enc, "replace")

    @staticmethod
    def check(raw: bytes) -> bool:
        if len(raw) < HEADER_SIZE:
            return False
        fs, ds, pc, lc, lc2 = struct.unpack_from(">5I", raw, 0)
        return (fs == len(raw) and HEADER_SIZE + ds + 4 * pc + 8 * (lc + lc2) <= fs
                and raw[0x14:0x18] == bytes(4))

    # helpers working on data-relative offsets
    def u8(self, o): return self.data[o]
    def u16(self, o): return struct.unpack_from(">H", self.data, o)[0]
    def s8(self, o): return struct.unpack_from(">b", self.data, o)[0]
    def u32(self, o): return struct.unpack_from(">I", self.data, o)[0]

    def ptr(self, o):
        """Return the target offset of the pointer field at o, or None if null."""
        if o not in self.pointer_set:
            v = self.u32(o)
            if v != 0:
                raise ValueError("field 0x%x is not a relocated pointer" % o)
            return None
        return self.u32(o)

    def cstr(self, o, enc="shift_jis"):
        return self._cstr(o, self.data, enc)

    def str_at_ptr(self, o, enc="shift_jis"):
        t = self.ptr(o)
        return None if t is None else self.cstr(t, enc)


def open_file(path):
    from lz10 import load
    return ISBin(load(path))


if __name__ == "__main__":
    b = open_file(sys.argv[1])
    print("file_size=0x%x data_size=0x%x pointers=%d labels=%d" %
          (b.file_size, b.data_size, b.pointer_count, b.label_count))
    for off, name in b.label_list:
        print("  %08x  %s" % (off, name))
