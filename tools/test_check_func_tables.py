#!/usr/bin/env python3
"""Integration regression checks using the original DOL and local MWCC."""
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest


ROOT = Path(__file__).resolve().parent.parent
SOURCE = ROOT / "src/game/rT_80026898/fn_80044530.cpp"


class ScriptTableChecks(unittest.TestCase):
    def check_source(self, source):
        with tempfile.TemporaryDirectory(dir=ROOT / "build/tmp") as tmp:
            path = Path(tmp) / "script.cpp"
            path.write_text(source)
            result = subprocess.run(
                [sys.executable, "-I", str(ROOT / "tools/check_func.py"),
                 str(path), "--strict-references"],
                cwd=ROOT, capture_output=True, text=True, timeout=60,
            )
        self.assertNotIn("COMPILE FAILED", result.stdout)
        self.assertNotIn("Traceback", result.stderr)
        return result

    def test_original_table(self):
        result = self.check_source(SOURCE.read_text())
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)

    def assert_rejected_mutation(self, old, new):
        source = SOURCE.read_text()
        self.assertIn(old, source)
        result = self.check_source(source.replace(old, new, 1))
        self.assertNotEqual(result.returncode, 0, result.stdout)
        self.assertIn("table entries differ", result.stdout)
        # The executable code still matches; the changed data must cause failure.
        self.assertIn("0 of 22 words differ", result.stdout)

    def test_first_opcode(self):
        self.assert_rejected_mutation("(void*)0x2003", "(void*)0x2002")

    def test_interior_opcode(self):
        self.assert_rejected_mutation("(void*)0x5100A", "(void*)0x4100A")

    def test_pointer_target(self):
        self.assert_rejected_mutation("(void*)fn_80044284", "(void*)fn_8004425C")

    def test_late_pointer_target(self):
        self.assert_rejected_mutation("(void*)fn_80044850", "(void*)fn_8004425C")


if __name__ == "__main__":
    unittest.main()
