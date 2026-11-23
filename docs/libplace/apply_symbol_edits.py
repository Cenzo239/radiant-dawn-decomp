#!/usr/bin/env python3
"""Apply docs/libplace/*_symbols.tsv to config/RFEE01/symbols.base.txt and symbols.txt (idempotent).
Lines: `merge <addr-of-function> <new size>`  (the trailing 4-byte blr symbol that follows is removed)
       `rename <addr> <new name>`
       `split <addr> <first size> <new name>`  (cut the function at addr after first size bytes; the rest becomes <new name>)
Run from the repository root:  python3 -I docs/libplace/apply_symbol_edits.py
"""
import re, sys, os
root = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
edits = []
import glob
for tsv in sorted(glob.glob(os.path.join(root, 'docs/libplace/*_symbols.tsv'))):
  for l in open(tsv):
    l = l.split('#')[0].split()
    if l: edits.append(l)
pat = re.compile(r'^(\S+) = (\.\w+):0x([0-9A-Fa-f]+);(.*)$')
for fn in ('symbols.base.txt', 'symbols.txt'):
    p = os.path.join(root, 'config/RFEE01', fn)
    lines = open(p).read().split('\n')
    for e in edits:
        addr = int(e[1], 16)
        for i, l in enumerate(lines):
            m = pat.match(l)
            if not m or int(m.group(3), 16) != addr or (m.group(2) != '.text' and e[0] != 'rename'):
                continue
            if e[0] == 'rename':
                lines[i] = '%s = %s:0x%s;%s' % (e[2], m.group(2), m.group(3), m.group(4))
            elif e[0] == 'split':
                first = int(e[2], 0)
                sz = re.search(r'size:0x([0-9A-Fa-f]+)', m.group(4))
                old = int(sz.group(1), 16)
                if old == first:
                    break
                lines[i] = '%s = .text:0x%s;%s' % (m.group(1), m.group(3), m.group(4).replace(sz.group(0), 'size:0x%X' % first))
                lines.insert(i + 1, '%s = .text:0x%08X; // type:function size:0x%X' % (e[3], addr + first, old - first))
            elif e[0] == 'merge':
                new = int(e[2], 0)
                sz = re.search(r'size:0x([0-9A-Fa-f]+)', m.group(4))
                old = int(sz.group(1), 16)
                if old == new:
                    break
                lines[i] = '%s = .text:0x%s;%s' % (m.group(1), m.group(3), m.group(4).replace(sz.group(0), 'size:0x%X' % new))
                nxt = addr + old
                for j, l2 in enumerate(lines):
                    m2 = pat.match(l2)
                    if m2 and m2.group(2) == '.text' and int(m2.group(3), 16) == nxt:
                        assert nxt + 4 == addr + new and 'size:0x4' in m2.group(4), e
                        del lines[j]
                        break
            break
    open(p, 'w').write('\n'.join(lines))
