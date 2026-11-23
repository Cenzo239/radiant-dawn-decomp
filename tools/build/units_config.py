"""configure.py hook: turn config/RFEE01/units.json into dtk-template library entries.

Each unit carries its status ("Matching" links the C object, anything else links dtk's asm
for the same ranges), compiler and flag set. Flag sets:
  game : the flags of tools/check_func.py (the ones every game function was matched with) + -i src
  lib  : the per-source flags recorded in lib/manifest.json (cc and flags exactly as checked)
"""
import json
import shlex
from pathlib import Path
from typing import Any, Dict, List

ROOT = Path(__file__).resolve().parents[2]


def game_cflags() -> List[str]:
    import sys
    sys.path.insert(0, str(ROOT / "tools"))
    import check_func  # noqa: E402
    toks, out = shlex.split(check_func.DEFAULT_FLAGS), []
    i = 0
    while i < len(toks):
        if toks[i] in ("-pragma", "-i", "-I") and i + 1 < len(toks):
            v = toks[i + 1]
            out.append(f'{toks[i]} "{v}"' if toks[i] == "-pragma" else f"{toks[i]} {v}")
            i += 2
        else:
            out.append(toks[i])
            i += 1
    return out


def unit_libs(Object, version: str) -> List[Dict[str, Any]]:
    path = ROOT / "config" / version / "units.json"
    if not path.exists():
        return []
    units = json.loads(path.read_text())["units"]
    manifest = json.loads((ROOT / "lib" / "manifest.json").read_text())
    gflags = game_cflags()
    game_objs, lib_groups = [], {}
    for u in units:
        done = u.get("status") == "Matching"
        if u["kind"] == "game":
            game_objs.append(Object(done, u["name"], mw_version=u.get("cc", "GC/3.0a5.2"),
                                    cflags=gflags + u.get("extra_cflags", []), shift_jis=False))
        else:
            m = manifest[u["lib_source"]]
            flags = [f for f in m["flags"]] + u.get("extra_cflags", [])
            obj = Object(done, u["name"], mw_version=m["cc"], cflags=flags, shift_jis=False, src_dir=".",
                         drop_functions=u.get("drop_functions") or None)
            lib_groups.setdefault(u.get("group", "lib"), []).append(obj)
    libs = []
    if game_objs:
        libs.append({"lib": "game", "mw_version": "GC/3.0a5.2", "cflags": gflags,
                     "progress_category": "game", "objects": game_objs})
    for g, objs in lib_groups.items():
        libs.append({"lib": g, "mw_version": "GC/3.0a5.2", "cflags": [], "progress_category": "sdk",
                     "objects": objs})
    return libs
