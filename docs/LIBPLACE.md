# Library placement: making library sources link as whole objects

Goal: every library function (SDK, MSL, NW4R snd/lyt/ut, HBM, BTE, ...) that `lib/verified.json` already
lists as byte-exact should be *linked from source*, so that the real `ninja` link uses the compiled
object instead of dtk's asm. `docs/BUILD.md` section 3 says when `tools/build/place.py` accepts an object;
`docs/tu_libs.tsv` lists each library source with a status and the first problem.

Measured on 2026-11-16: 267 library objects (1,810 functions) are linked from source; 1,776 functions of
the library range 0x8028BC54-0x80360900 are not, and 1,770 of those are already verified byte-exact by
`tools/lib/check_lib.py` (only per function, with relocations masked). What is missing is the *object
model*: the source must emit exactly the functions of its DOL range, in the DOL order, with the same
sizes, and its data/bss/sdata must start where the DOL has them.

## Fast loop (seconds)

```
python3 -I tools/build/libdrv.py -v <key>            # place one source: class + first errors (about 4 s)
python3 -I tools/build/libdrv.py --all -j 2          # every candidate (about 1-2 min); classes summary on the last line
python3 -I tools/build/libobj.py <key>               # functions of the compiled object (order, size, bind, DOL address)
python3 -I tools/lib/check_lib.py <key> -v           # byte/reference check of the source against main.dol (verified.json)
python3 -I tools/lib/remap.py <key>                  # re-place the functions of an edited source into lib/map.json
python3 -I tools/lib/fdiff.py <key> <function> [-a]  # side-by-side disassembly vs the game
```
`<key>` is the path below `lib/` (for example `ogws/src/nw4r/snd/snd_BasicSound.cpp`). `libdrv.py` writes
nothing outside `build/tmp/libplace/` (it uses `place.py` and `gen_units.lib_unit` exactly as the real
generator does). The generator (`gen_units.py`) and the full link are run by the integrator, not by you.

## What a failure means and how to fix it

- `function X at 0x.. breaks contiguity (expected 0x..)` / `size 0x.. , DOL has 0x..`: the object's
  function sequence differs from the DOL range. Run `libobj.py` and compare with the symbols of the range
  (`config/RFEE01/symbols.txt`). Usual causes:
  1. functions emitted in another order: reorder the definitions in the source file (member functions are
     emitted in definition order; inline class-body functions are emitted when first used);
  2. the object emits an inline/implicit function the DOL range lacks (`-` in the address column): make it
     inline-only (the DOL inlined it), or define/declare it so that it is not emitted;
  3. the DOL range has a function the object lacks: add it (it must come from a verified source or be
     written; see docs/LIB.md for how earlier rounds added missing functions);
  4. a weak function (bind 2: implicit dtors, `LinkList<T>` ctors/dtors, `NonCopyable` dtor, template
     copies) whose DOL copy sits in *another* object: the placement model drops such a copy (MWLD keeps one
     definition; the model assumes it is the one in the DOL). This is not an error by itself.
- `function X not in symbols.txt`: the original link dead-stripped it. `lib_unit` then retries with the
  dead-strip model; if that still fails read the errors after `(dead-stripped model)`.
- `.sdata2: cannot derive a single base`, `.data: cannot derive...`: the object's data sections do not map to
  one consistent base in the DOL (order of statics, literals pooled differently, a static the original has
  but the source lacks, string/float literal order). Compare with `datadiag`-style reasoning: which code
  references the data and at which DOL offsets.
- `reference to X: not in symbols.txt` / `lbl_... is referenced from outside the unit`: a global/static
  naming problem; usually the object must define (or not define) a symbol the DOL names differently. Names
  come from `lib/map.json` (`symbols`) and `symbols.txt`; fix the map entry or the source linkage
  (`static` vs global).
- `overlaps another library source that places` (status `duplicate`): another source already covers the
  range; nothing to do (unless it is the better source).
- `MWLD would dead-strip it`: the object defines something nothing references; `-pragma "force_active on"`
  retries are automatic. If the object really needs it, it must be referenced from the DOL.

Typical per-source fixes live in the source file under `lib/<repo>/src/...` and the headers under
`lib/<repo>/include/...` (shared by many sources: change headers only with `check_lib.py --all` afterwards,
it must stay >= 3,273 of 3,277). Compiler flags per source are in `lib/manifest.json`.

## Rules

- Never commit game data (nothing under `orig/`, no dol/wbfs). The repo is private but still: no extracted assets.
- All MWCC runs go through `tools/wibo_guard` (already done by the tools). The Mac is busy: use `-j 1`/`-j 2`.
  No `pkill`, no broad process commands, never touch other worktrees (`fe10-m13`, `fe10-m16`, ...).
- Source credits: the sources are CC0/public decomp code (ogws, wii-ipl, Petari, xenoblade, wiiplay-pc, xd-decomp,
  mhtri); keep the headers/LICENSE files that come with them and keep notes of where a body comes from.
- A change must not lower the number of placed sources (`libdrv.py --all`, compare with the baseline in the
  hand-over note) and must keep `check_lib.py <key>` verified for the functions that were verified before.
- Do not run `ninja`, `gen_units.py`, `gen_config.py` or `configure.py` (the integrator does).
- Commit your work in small commits on your own branch; list each placed source in
  `docs/libplace/<your group>.md` with the cause and the fix (or, for sources you gave up, the cause).
