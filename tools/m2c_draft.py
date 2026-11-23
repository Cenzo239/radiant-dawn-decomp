#!/usr/bin/env python3
"""Print the m2c draft of a function, ready to save as a .c file for check_func.py.

Usage: tools/m2c_draft.py fn_80012345 > draft.c
"""
import os
import subprocess
import sys
import tempfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import m2c_pipeline as p  # noqa: E402

name = sys.argv[1]
body = p.load_functions()[name][1]
tmp = tempfile.mkdtemp()
asm = os.path.join(tmp, "f.s")
open(asm, "w").write(".text\n" + body)
r = subprocess.run([p.PY, p.M2C, "-t", "ppc-mwcc-c", "--valid-syntax", "--globals=used", "-f", name, asm],
                   capture_output=True, text=True)
print('#include "game/auto/m2c_prelude.h"\n#pragma use_lmw_stmw on\n' + p.fix_draft(r.stdout))
