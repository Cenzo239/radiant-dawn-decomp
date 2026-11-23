# Building main.dol from source

Goal: `ninja` links C/C++ objects wherever they reproduce the original bytes and dtk's asm for
everything else, and still produces main.dol with SHA1 `d1b8deabfec5a96bf38945665ffe203867612c1c`.
Every further exact function (or fixed library source) should be able to replace asm without
touching anything by hand. The per-function files under `src/game/` stay the source of truth; all
build config is generated.

## Pipeline

```
src/game/**/fn_*.c(pp)  --survey.py-->  build/tmp/buildtree/survey.json   (what each file emits, which functions are exact)
main.dol + dtk asm      --tu_analyze.py--> docs/tu_map.tsv, docs/TU_MAP.md, tu_units.json (units = minimal linkable pieces)
units + survey          --try_units.py-->  docs/tu_units.tsv, docs/tu_libs.tsv, config/RFEE01/link_select.txt
                                           (generate + compile + place every unit and library source)
config/RFEE01/link_select.txt --gen_units.py--> src/tu/**  (generated TU sources)
                                              src/tu/lib_aliases.h, config/RFEE01/units.json
units.json              --gen_config.py--> config/RFEE01/splits.txt, symbols.txt
units.json              --configure.py (tools/build/units_config.py)--> build.ninja Objects
```

Commands (all from the project root):

```
python3 -I tools/build/survey.py -j 14        # 1.5 min: compile every per-function file once
python3 -I tools/build/tu_analyze.py          # 5 s: TU map + units
python3 -I tools/build/try_units.py -j 14 --asm --write-select
                                              # ~10 min (process pool): which units link today, writes link_select.txt
                                              # (a unit that no longer places falls back to its line
                                              # in the previous link_select.txt, see phase 3)
python3 -I tools/build/gen_units.py -j 14     # ~2 min: sources + units.json for link_select.txt
python3 -I tools/build/gen_config.py          # splits.txt / symbols.txt
python3 configure.py && ninja                 # 5 min: build + SHA1 check (prints "main.dol: OK")
```

No step needs a hand edit: `try_units.py --write-select` writes `config/RFEE01/link_select.txt` from
every game unit and library source that places (`--libs` probes the library sources without writing
the selection; without `--asm` only all-exact units are tried). gen_units.py re-checks every unit
and skips what no longer places, so a stale selection never breaks the build. Always finish with
`ninja` and keep only a selection that prints `main.dol: OK`.

### 1. Units, TUs and why units are the link granularity

`tu_analyze.py` (see `docs/TU_MAP.md`) finds the clean cuts: positions where no TU-private data
(literals, jump tables, string pools) is shared across the cut and the data order of every
section can be split consistently. A unit between two clean cuts can be compiled separately:
its literals are pooled exactly as in the original TU (MWCC pools per object, and nothing on the
other side of the cut uses them). So a link unit need not be a whole original TU; the TU map only
says how units group into the original files (for naming and for later merging into real source
files). Two refinements:

- **File closure**: MWCC inlines functions defined earlier in the same file (`-inline auto`). If a
  unit cut separates such functions, the unit compiled alone differs. `try_units.py` first tries
  each unit alone, then, for failures, the smallest run of units that keeps each source file whole.
- **Alignment**: a unit whose `.sdata2` holds a double must start 8-aligned (handled in the cuts).

### 2. Forming a TU source (tools/build/gen_tu.py)

Input: the unit's function list in address order. For each function the exact definition comes
from the file in which `check_func.py` reports it OK (region files before `auto/` files).

1. Each file is split into top-level chunks (preprocessor lines, declarations, function bodies,
   `extern "C"` blocks flattened with a flag). Files whose functions come from macros are chunked
   after preprocessing (`-E -ppopt pragma`, so pragmas survive).
2. `#include`s are hoisted (deduplicated); `src/tu/lib_aliases.h` comes first when library
   symbols are renamed (see 5).
3. Functions are emitted in address order. Before each function, the not yet emitted chunks of its
   file that precede it are emitted, so every file keeps its own order of types, externs, statics
   and pragmas (C++ file statics are laid out in declaration order, C in first-use order).
4. Isolation: in a C++ unit each file goes into `namespace tu_fN { ... }`, so each file's private
   `Vec`/padding structs cannot clash. Everything that is not a type or a static is wrapped in
   `extern "C"` there, so `fn_`/`lbl_` names stay unmangled (global variables are not mangled at
   global scope either). C files in a C++ unit are wrapped in `extern "C"` and their `T f();`
   declarations become `T f(...)`. Pure C units are concatenated with identical chunks removed.
5. Pragmas are scoped per file: `#pragma push`, the file's earlier pragmas, the block, `#pragma pop`.
6. `fn_` definitions that are not part of the unit become prototypes.

The generated file says which per-function files it came from; it is never edited by hand. When a
function in `src/game` changes, rerunning gen_units regenerates the TU.

Per-function pools merge naturally: each file emits only the literals and strings its own
functions use; in the TU the compiler pools them once, in first-use (C) or declaration (C++) order.
The `pool_N`/`StringPool` dummy functions some files use to force a pool order are **not** unit
functions; since phase 3 the generator drops such helpers when nothing in the TU calls them, and
headers are compiled with `force_active off` so scaffolding defined in a header is dead-stripped
(see "Generator phase 3").

### 2b. asm fallback (gen_tu.py `fallback=True`, try_units.py `--asm`)

A unit that contains functions without an exact definition still links from source: those
functions are emitted as MWCC `asm` functions made of the original instruction words,

```
namespace tu_asm { extern "C" {                 /* C units: same, without namespace */
asm void fn_80032560(void) {
    nofralloc
    opword 0x9421FFE0 /* 80032560  stwu r1, -0x20(r1) */
    opword 0x480695CD /* 80032564  bl fn_8008BDDC */
    ...
}
} }
```

- One `opword` per instruction, no relocations: the unit is linked at the original address, so
  branch displacements, `@ha/@l` pairs and r2/r13 offsets in the words are already right. That also
  removes every symbol-level problem (literal pools shared with the C functions, jump tables (dtk
  writes their entries as `fn+0x...`), local labels, renamed library names). dtk's disassembly is
  kept as a comment on each word (taken from build/RFEE01/asm, which has every function, C units
  included).
- C++ units put it in `namespace tu_asm` (MWCC accepts an `extern "C"` definition next to other
  declarations of the same name in other namespaces); C units repeat the TU's own prototype of the
  function (`asm T fn(params)`), as C forbids conflicting redeclarations.
- The C version stays next to it: if `survey.json` has a per-function file that defines the
  function without matching (check_func DIFF), that definition and its file's declarations are
  emitted under `#ifdef FE10_NONMATCHING ... #else <asm> #endif` (in `namespace tu_nm_<fn>` for
  C++). The DOL build never sees it; the port defines FE10_NONMATCHING (and resolves whatever
  conflicts the non-matching versions bring). Functions with no C file yet get a comment.
- Variant `asmdata` (a token on the link_select.txt line): data that only the unit's asm functions
  reference (literals, strings, tables) is defined at the function's position as
  `__declspec(section "...") static const unsigned char tu_d_<addr>[n] __attribute__((aligned(a)))`,
  so it lands inside the C pool where the original compiler put it. try_units tries both variants.
- Repair loop (try_units, up to 16 rounds, plus up to 32 header fixes): when a unit with asm fallback does not place, the
  functions the errors point at also become asm: size or byte differences in `.text`, relocation
  targets, contiguity breaks (the function before), code whose data references imply a minority
  data base (their literals sit elsewhere in the original pool), references to a symbol inside the
  unit's own ranges that the object does not define, and for compile errors or unknown functions
  (`StringPool`, `poolOrder`) every function of the offending per-function file. A unit whose
  functions would all be asm is not linked from source. The final asm list is written on the
  link_select.txt line (`game A-B asm=fn_1,fn_2 [asmdata]`), so gen_units.py reproduces exactly
  what was checked.
- Libraries: an opword carries no relocation, so a library function referenced only from asm
  functions would be dead-stripped by MWLD; gen_units.py compiles such library objects with
  `force_active on` (NOTE lines in its output).

### 2c. Static initialisers

The per-function files write a `__sinit` as a plain function. When the DOL has a `.ctors` slot that
points at a unit function, the TU adds the pointer right after the function:
`__declspec(section ".ctors") static void (* const tu_ctor_fn_X)(void) = (void (*)(void))fn_X;`
(the slot's base is found by place.py from the slot that holds the function's address).

### 3. When is a unit Matching? (tools/build/place.py)

A unit is linked from source iff `place.py` accepts its compiled object:
- `.text`: the object's functions exist in symbols.txt with the same sizes and are contiguous
  (the object occupies exactly `[first, last+size)`);
- every other section (`.rodata .data .bss .sdata .sbss .sdata2 .ctors`...) gets its base from the
  original instructions that reference the object's own data symbols (one consistent base per
  section, inside that section, aligned to the object's section alignment);
- bytes of every section equal main.dol with relocated fields masked, and every relocation (code
  and data, e.g. jump tables and vtables) points at the original target;
- every symbols.txt symbol that starts inside an owned range is defined by the object under the
  same global name, or referenced only from inside the unit (otherwise the rest of the link would
  miss it); no range edge may fall inside a symbols.txt symbol (dtk refuses such splits).

Added in the generator phase 2:
- `.ctors`/`.dtors`/`extabindex` entries in the DOL that point at the unit's functions must be
  emitted by the object (dtk assigns them to the unit; slots owned by splits.base.txt are exempt).
  Their base is the DOL slot holding the function's address; `extab` follows from `extabindex`
  (bases are derived iteratively, data referenced from data included);
- dead-strip: every function/object the object defines must be referenced in the DOL or marked
  force_active (read from MWCC's `.comment` section), else MWLD would drop it;
- a symbol the object references (`extern lbl_...`) but whose address lies inside the object's own
  ranges is an error (it would be undefined at link time);
- sections that no code references get their base from data symbols named as in symbols.txt;
- padding-aware edges: a range that ends inside its own last symbol (symbols.txt size includes
  padding) takes the padding when the next symbol sits on the next 4/8 boundary, otherwise the
  symbol's size is corrected; a range that starts inside the previous object's last symbol shrinks
  that symbol. Corrections go to `units.json` (`symbol_sizes`) and gen_config.py writes them into
  symbols.txt (symbols.base.txt stays as is).

The unit then owns exactly the ranges its object emits (`units.json` → splits.txt). Data that the C
code reaches through `extern lbl_...` stays in dtk's auto-split asm objects around it, which is fine
for a byte-identical link (data can move into C later, unit by unit, with the same check). Anything
that fails is simply not listed and stays asm; nothing else has to change.

"Matching" in configure.py is the dtk-template flag: the C object is linked. A unit that is not
Matching is not added at all (dtk's auto split covers its range), so a partially matched TU never
breaks the build.

### 4. splits.txt, symbols.txt, configure.py

- `config/RFEE01/splits.base.txt` / `symbols.base.txt`: the hand-kept inputs (copies of the files
  as they were before this phase, plus later hand edits such as symbol sizes). `gen_config.py`
  writes splits.txt = base entries + one entry per unit, in address order (the order dtk writes
  back), and symbols.txt = base + renames. `gen_config.py --check` reports whether they are current.
  Note: dtk writes back to symbols.txt during a build (it currently re-labels four strings and one
  `.sbss` word in library data as locals); such write-backs should be folded into symbols.base.txt
  if they are wanted, the generator otherwise overwrites them.
- `configure.py` calls `tools/build/units_config.py`, which turns `units.json` into libraries:
  `game` (compiler GC/3.0a5.2, the exact flags of `tools/check_func.py` + `-i src`, `-lang` by
  extension, no Shift-JIS conversion) and one library per lib repo (`ogws`, `petari`, `wii-ipl`, ...)
  with the compiler and flags recorded per source in `lib/manifest.json`, `src_dir="."`, object
  name `lib/<key>`.
- `config/RFEE01/link_select.txt` is the list of units to build (reviewable, one line each:
  `game <start>-<end> [asm=fn_a,fn_b] [asmdata] [cnative] [hfix=...] [prune] [lead=...]` or
  `lib <source key>`; the options are described under "Generator phase 3"). It is generated by
  `try_units.py --write-select` (status `ok`/`ok+asm` in docs/tu_units.tsv, `ok` in docs/tu_libs.tsv).

### 5. Library code (lib/)

- Splits: one unit per lib source (`lib/<repo>/...`), placed by `place.py` with a name map from
  `lib/map.json` (object name → symbols.txt name by address).
- Names: `gen_config.lib_renames()` renames every library function/global of `lib/map.json` whose
  name is unique and whose address starts a symbol (3,566 renames, e.g. `fn_80317BD4` →
  `OSSetAlarm`) in symbols.txt, so the asm and the library objects use the same names. Static
  functions that share a name across files (`OnReset`, ...) keep their `fn_` name.
- Game sources keep calling `fn_` names; `src/tu/lib_aliases.h` (`#define fn_80317BD4 OSSetAlarm`)
  is included by every generated game TU. `tools/check_func.py` and the analysis read
  `symbols.base.txt`, so the per-function workflow is unchanged.
- Flags per source come from `lib/manifest.json` (cc GC/3.0a3 for MSL math, 3.0a5 for some SDK
  files, `-ipa file`, `-fp_contract off`, Shift-JIS, defines), exactly as `check_lib.py` used them.
- The two register-only SoundArchivePlayer functions: their sources are not listed (their range
  stays asm, as decided).
- Library sources whose object has functions the DOL lacks (dead-stripped by the original link)
  cannot be placed as a whole yet; see the plan.
- Candidates (try_units.py `--libs`): lib/verified.json sources with lib/manifest.json flags whose
  functions are all `ok` in lib/map.json (493). Retries with flags the manifest lacks:
  `-pragma "force_active on"` (functions the original kept though nothing references them; only
  `.comment` changes) and `-Cpp_exceptions on` (the original had extab/extabindex entries, MSL).
  Recorded as `extra_cflags` in units.json, used by units_config.py.
- Excluded automatically: sources overlapping splits.base.txt (`__init_cpp_exceptions.cpp`), a
  second copy of the same SDK file (the game links MEM twice: one name per symbol), objects that
  reference a name the final symbols.txt does not have (a rename skipped because two names share
  an address), and renames that would give a symbol a name another symbol already has. When a
  function and a label share an address (`OSDisableInterrupts` / `__RAS_OSDisableInterrupts_begin`)
  the function name wins.

## Prototype result (first phase)

`config/RFEE01/link_select.txt` links 5 game TUs and 5 library objects from source:

| unit | functions | sections owned |
|---|---:|---|
| game TU0044 `src/tu/game/rG_800A3D88/tu_800A8B80.cpp` | 7 | .text 800A8B80-800A91C4, .rodata 80365348-80365354, .sdata2 804CD2E0-804CD318 |
| game TU0046 `src/tu/game/rG_800A3D88/tu_800AA444.cpp` | 23 | .text 800AA444-800AAD44, .sdata2 804CD340-804CD348 |
| game TU0127 `src/tu/game/rF_8017F400/tu_801AB68C.cpp` | 5 | .text 801AB68C-801ABC34, .sdata2 804CEFD8-804CF000 |
| game TU0132 `src/tu/game/rF_8017F400/tu_801B486C.cpp` | 23 | .text 801B486C-801B5EB4, .sdata2 804CF248-804CF2A8 |
| game TU0165 `src/tu/game/rI_801DD7D4/tu_802291A8.cpp` | 2 | .text 802291A8-8022A5F8, .data 80390238-80390258, .sdata2 804CFD30-804CFD48 |
| lib `ogws/src/MSL/k_rem_pio2.c` | 1 | .text, .rodata, .sdata2 |
| lib `ogws/src/MSL/e_fmod.c` | 1 | .text, .rodata |
| lib `ogws/src/revolution/OS/OSAlarm.c` | 12 | .text, .data, .sbss |
| lib `ogws/src/revolution/OS/OSMutex.c` | 5 | .text |
| lib `ogws/src/revolution/NdevExi2AD/exi2.c` | 6 | .text |

`ninja` prints `build/RFEE01/main.dol: OK` (SHA1 d1b8deabfec5a96bf38945665ffe203867612c1c).

Commands: `python3 -I tools/build/gen_units.py && python3 -I tools/build/gen_config.py &&
python3 configure.py && ninja`.

### Full-scale check (first phase; the filters described here now live in place.py/gen_units.py)

`config/RFEE01/link_select.all.txt` lists every unit that passed and linked: **2,134 game units
(2,290 functions, 0x5D514 bytes = 14.5% of the game code, 2,676 data bytes) and 112 library
objects (428 functions, 0x177EC bytes of code, 62.6 KB of data)**. Generating and building it
(`gen_units.py --select config/RFEE01/link_select.all.txt -j 14`, ~10 min, then ~5 min ninja)
gives `build/RFEE01/main.dol: OK`. It is not the default yet (the phase asked for a small
sample); switching is a matter of passing that file to gen_units.py. Four link-level problems
showed up only at this scale and are now handled:

- MWLD dead-strips functions nothing references (dtk's asm objects keep them): generated game TUs
  start with `#pragma force_active on`; library objects with unreferenced functions are left out
  (dtk drops the `force_active` attribute from symbols.txt on write-back, so that route failed).
- A unit containing a `__sinit` (its `.ctors` entry) or a function with `extab`/`extabindex`
  entries makes dtk assign those entries to the unit; the C object (compiled with
  `-Cpp_exceptions off`, `__sinit` written as a plain function) does not emit them, so `.ctors`
  and `extab` shrink. Such units (31) are excluded until the sinit files emit their `.ctors`
  pointer and the C++ library sources are compiled with exceptions on.
- Alignment padding at the end of a range belongs to the unit only if the next symbol sits on the
  next 4/8-byte boundary (dvdqueue.c's 0x10-byte gap was a missing static, not padding).
- Library renames: names must be unique (two `MEMInitList`), the base `Runtime.PPCEABI.H` split
  must not be duplicated by a library unit, library code inside the game range keeps a C-identifier
  name only (game TUs reach it through `lib_aliases.h`), and `dolmodel.py` maps the renamed names of
  the regenerated asm back to the base names.

## Status after the generator phase 2 (2026-11-13)

Build: `config/RFEE01/link_select.txt` (generated) links **1,971 game units and 149 library
objects** from source (2,120 units), and `ninja` reproduces main.dol (SHA1
d1b8deabfec5a96bf38945665ffe203867612c1c). Coverage of the game code (0x800068A0..0x8028BCD4):

| | before (c6b0198) | step 1 (filters in the tools) | step 2/3/4 (asm fallback, sinit, libs) |
|---|---:|---:|---:|
| game units from source | 2,134 | 2,178 | 1,971 (98 with asm; merged units are larger) |
| game code from source | 14.5% (0x5D514) | 15.0% (0x60918) | **56.9% (0x16EE84)** |
| of which real C | 14.5% | 15.0% | **23.9% (0x9A0E4, 3,334 functions)** |
| of which asm fallback | - | - | 33.0% (0xD4DA0, 1,763 functions) |
| library objects | 112 (0x177EC code) | 144 | 149 (0x29AC0 code) |

docs/tu_units.tsv (try_units.py --asm; columns `asm_functions`, `asm_bytes` added):

| status | units | functions | text | share |
|---|---:|---:|---:|---:|
| ok (all C) | 1,876 | 2,042 | 0x4FF38 | 12.4% |
| ok+asm | 98 | 3,060 | 0x11F4CC | 44.5% |
| compile (merged source does not compile, error not in a file block) | 29 | 1,867 | 0x67A70 | 16.1% |
| align (pool section base not aligned) | 20 | 814 | 0x35E7C | 8.4% |
| data-base | 56 | 376 | 0x24288 | 5.6% |
| codegen | 98 | 556 | 0x200C4 | 5.0% |
| ctors (sinit units failing for another reason) | 2 | 317 | 0x1B720 | 4.3% |
| inexact (no exact function at all) | 85 | 88 | 0x10018 | 2.5% |
| shared-data / other / chunker | 38 | 67 | 0x8CC0 | 1.4% |

docs/tu_libs.tsv: 149 of 493 candidate library sources place (+37 over the earlier 112); 290 fail
because the source has functions the original link dead-stripped (`stripped`).

Notes:
- `symbols.base.txt`: fn_8012E888 and fn_80118008 (the dead trailing `blr` of fn_8012E854 and
  fn_80117F74, split off as 4-byte functions) are merged back (sizes 0x38 and 0x98), so the real
  sources of those two functions can match. Re-run check_func on them.
- tools/transform_dep.py escapes spaces in dependency paths: with the project under
  "RD decomp" ninja treated every object as dirty and rebuilt all of them on every run.
- dtk write-back into symbols.txt is still overwritten by gen_config.py (see the obstacles below).

## Generator phase 3 (2026-11-13)

Why exact functions ended up as asm (analysis of the phase-2 selection: 1,763 asm functions,
of which only ~230 had no exact definition): almost all were demoted by the repair loop, mostly
because merged sources did not compile. The causes and what the tools do now:

1. **Files that define their functions out of address order** (147 per-function files, 2,117
   functions). gen_tu.py kept one cursor per file and moved it backwards, so a function defined
   earlier in its file than an already emitted one was silently dropped and the file's statics
   and inline helpers were emitted twice (`class 'tu_f14::Fn3x' redefined`, `object
   'tu_f0::WinClear' redefined`). Now every chunk is emitted once (set per file), and a unit
   function the file defines earlier is declared at that point and defined at its own position.
2. **Argument-dependent lookup**: a file declares `fn_X` in its namespace, a hoisted header
   declares it globally; with an argument of a global class type MWCC calls the call ambiguous.
   Calls of `fn_` names in C++ bodies (and in `#define` bodies) are written `(fn_X)(...)`.
3. **C files in C++ units** (`illegal implicit conversion from 'void *'`): variant `cnative`
   compiles them as C inside the C++ unit (`#pragma cplusplus off` ... `on`, at global scope,
   deduplicated like a C unit; headers only C files include are read in C mode too).
4. **Header conflicts** (`s32` as long vs int, `NULL`, one fn_ with two prototypes, two structs
   of one name): the compile error names the header (`In:`/`From:`), and try_units records a
   fix for that hoisted include (token `hfix=` on the link_select line): the conflicting name is
   renamed while the later header is included (`#define s32 s32__tu_altN` / `#undef`; a renamed
   library function through its lib_aliases.h target), a redefined macro is undefined before it,
   and a C header whose `NULL` is `((void*)0)` gets `NULL 0` in a C++ unit. Each file's own
   `#define`s are re-asserted when its next block starts (macros are not namespaced).
5. **Macro-made functions** (`HLP2(fn_80228BB8, 0x24)`): a file with function-like macro
   invocations that define fn_ functions is chunked after preprocessing, so non-unit functions
   it makes become prototypes instead of extra code.
6. **asm signatures in C units** are also looked up in the preprocessed hoisted headers.
7. **Over-blaming**: a size error no longer also blames every later function (contiguity), data
   the C object keeps local although other units reference it by name blames its users
   (`shared-data`), and after a unit places, `shrink` gives every exact function the loop made asm
   back to C, file by file and then one by one, keeping each step that still places (budget 400
   attempts / 7 minutes per unit). Last resorts when a unit fails: all blamed files as asm, then
   the previous selection's asm list (`--prev`, default the current link_select.txt), so a unit
   never drops out because the loop took another path.

Pools, data bases (task step 3):
- `prune`: file statics that only asm functions still use are left out of the object (they had no
  reference left to place them by: `data-base ... no references from code`).
- `lead=`: a pool whose base is 4 mod 8 although the object holds a double starts after items of
  the same original TU that belong to the unit before; those items are defined at the top of
  the TU under their symbols.txt names (with the declared type if a header declares them), so the
  section starts aligned. Conflicts with a neighbouring unit that owns the item are caught by
  gen_units.py (`overlaps`).
- `asmdata` (phase 2) still covers data only asm functions use. Literals shared between an asm
  function and a later C function remain the main limit (`minority .sdata2`, see obstacles).
- gen_units.py drops a game unit that would leave a data gap of less than 8 bytes starting at 4
  mod 8 between two splits (dtk: `Unsplit data in .sdata2 ... to next split`), and deletes the
  generated TU sources of units that are no longer selected.

Library dead-stripping (task step 4): `place.strip_object` models MWLD's dead-stripping of one
object: the object's own functions are those the DOL has in object order (longest increasing run
of DOL addresses; a mapped function whose DOL copy lies elsewhere is a weak copy linked from
another object), a function without a known name is kept when the DOL has a function of the same
size and bytes (relocations masked) where it would go (its name then joins the rename map),
force_active symbols are kept, and everything they reference, transitively; the rest is dropped
and the gaps closed (each symbol keeps the alignment of its old offset). place.py then places the
stripped object; the real link strips the same symbols because nothing references them.
gen_units.py records `dead_stripped` in units.json and never adds force_active to such an object;
a dead-stripped library object whose kept function only asm-fallback code references is skipped.

Pool helpers (task step 5): helper functions that are not game functions and that nothing in the
TU calls (`StringPool`, `poolOrder`, `dummy1` in per-function files) are dropped from the TU;
hoisted headers are compiled with `force_active off`, so scaffolding defined in a header
(`strpool.h`) is dead-stripped at link time, and `place.place_game` places such an object
stripped (`dead_stripped` in units.json).

link_select.txt line tokens: `game A-B [asm=...] [asmdata] [cnative] [hfix=hdr|name|-macro;...]
[prune] [lead=lbl_a,lbl_b]`. Timing: try_units.py ~15 min with the shrink pass (`--no-shrink`
to skip it), gen_units.py ~6 min.

Symbol maps (`<file>.symbols.json`, object-local name -> original label, the `--symbol-map` of
tools/check_func.py): survey.py passes the file's map to check_func, so functions that are exact
only with their map (fn_8006BDCC, the `...bss.0` / `sa$42` statics) count as exact. Local names
(statics, guards) need nothing else: the unit places them from the code that references them.
A map entry whose local name a linker sees (a C identifier, e.g. a compiler-generated vtable
`__vt__8HbWidget -> lbl_8038CB1C`) becomes a rename like the library ones: the unit records
`renames` in units.json, gen_config.py writes the local name into symbols.txt (dtk's asm then
uses it), place.py gets the map as name map, and lib_aliases.h gets `#define lbl_8038CB1C
__vt__8HbWidget` (computed by gen_units.py from the selected lines before any game unit is
generated, and by try_units.py from all exact files) so other game units' `extern lbl_...`
references still link; the defining unit `#undef`s its own labels after the include. Two units
mapping one label cannot both link (their ranges overlap; gen_units.py keeps the first), and a
map that names a label differently from a library rename is refused.

## Status after the generator phase 3 (2026-11-13)

Build: `config/RFEE01/link_select.txt` links **2,061 game units and 214 library objects** from
source, and `ninja` reproduces main.dol (SHA1 d1b8deabfec5a96bf38945665ffe203867612c1c).
Coverage of the game code (0x800068A0..0x8028BCD4), measured on units.json after each landed step:

| | phase 2 | step 1 (rerun) | 2a (order, ADL, cnative, fallbacks) | 2b (header fixes) | 3a (shrink, prune, lead, lib strip) | final |
|---|---:|---:|---:|---:|---:|---:|
| game units | 1,971 | 1,978 | 1,987 | 1,994 | 2,041 | **2,061** |
| game code from source | 56.9% | 56.9% | 67.0% | 80.1% | 81.4% | **82.5% (0x2149C0)** |
| of which real C | 23.9% | 24.0% | 31.9% | 36.6% | 42.9% | **43.4% (0x117E1C, 6,270 functions)** |
| of which asm | 33.0% | 33.0% | 35.1% | 43.5% | 38.5% | 39.2% (0xFCBA4, 1,592 functions) |
| library objects | 149 (0x29AC0) | 149 | 149 | 149 | 210 (0x4190C) | **214 (0x43464 code)** |

(The asm share rose at first because units that did not compile at all now link with part of
their functions as asm; the shrink pass then turned 657 of them back into C.)

docs/tu_units.tsv (try_units.py --asm, before gen_units.py's overlap/gap filters):

| status | units | functions | text | share |
|---|---:|---:|---:|---:|
| ok (all C) | 1,928 | 2,392 | 0x5B8C4 | 14.2% |
| ok+asm | 138 | 5,554 | 0x1BC48C | 68.9% |
| ctors (sinit units failing for another reason) | 2 | 317 | 0x1B720 | 4.3% |
| data-base | 22 | 248 | 0x196A8 | 3.9% |
| align | 10 | 253 | 0x1551C | 3.3% |
| inexact (no exact function at all) | 88 | 91 | 0xF200 | 2.3% |
| codegen | 20 | 89 | 0x8FFC | 1.4% |
| compile | 3 | 208 | 0x8AB4 | 1.3% |
| shared-data / other / chunker | 31 | 35 | 0x2750 | 0.4% |

Why the 1,601 asm functions of the selection are asm (`why` in build/tmp/buildtree/try_units.json):

| reason | functions | bytes |
|---|---:|---:|
| no exact definition yet | 340 | 0x6914C |
| whole-file fallback (the shrink budget ran out on the largest units) | 360 | 0x1FAEC |
| literal pool shared with an asm function (`minority .sdata2/.data/.rodata`) | 486 | 0x4B4A0 |
| code differs once merged (size, relocation, contiguity: cross-file inlining) | 209 | 0x15A34 |
| compile conflicts the loop could only resolve by asm | 116 | 0x8970 |
| kept from the previous selection | 67 | 0x5D4C |
| other (shared data, files) | 23 | 0x4974 |

docs/tu_libs.tsv: 215 of 493 candidate sources place (214 link; ogws VI/vi.c is refused because
its dead-stripped model takes over AI functions of identical code). Of the 290 former `stripped`
sources, 67 now place dead-stripped; the rest fail for source-level reasons (a function the
DOL has that the source lacks, weak copies, data-size edges, names the rename pass cannot give).


## Phase 4 (2026-11-13/14)

Landed (each step ends with `ninja` printing `main.dol: OK`, SHA1 d1b8deabfec5a96bf38945665ffe203867612c1c;
snapshots in build/tmp/buildtree4/good_<step>):

| | phase 3 | step 1 (process pool) | step 2 (rerun) | step 3 (literals, pragmas, cnative) | step 4 (def=, guards) | step 5 (library proposals) |
|---|---:|---:|---:|---:|---:|---:|
| game units linked | 2,061 | 2,061 | 2,060 | 2,065 | 2,117 | **2,117** |
| game code from source | 82.5% | 82.5% | 82.2% (0x2122EC) | 83.4% (0x21A3C8) | 83.7% (0x21BE30) | **83.7% (0x21BE30)** |
| of which real C | 43.4% | 43.4% | 44.0% (6,265 fns) | 46.0% (0x128A94, 6,402 fns) | 46.0% (0x128B64, 6,436 fns) | **46.0% (0x128B64, 6,436 fns)** |
| of which asm | 39.2% (1,592 fns) | 39.2% | 38.2% (1,553 fns) | 37.4% (0xF1934, 1,515 fns) | 37.7% (0xF32CC, 1,509 fns) | **37.7% (1,509 fns)** |
| library objects | 214 | 214 | 214 | 214 (0x43464 code) | 211 (0x42C2C) | **266 (0x6AFB4 code)** |

(Step 2 lost one unit, 0x800A64AC-0x800A8B80: its fn_800A6DE4 moved to equiv/ after the survey;
the next try_units run gives it an asm fallback.)

1. **Processes instead of threads.** try_units.py and gen_units.py run units in a fork-based
   `ProcessPoolExecutor` (workers inherit the warmed caches; heaviest units are submitted
   first). try_units: 15 min -> 7.5-9.5 min, gen_units: 6 min -> ~2 min. The shrink budget is now
   3,000 attempts / 1,500 s per unit, but that freed nothing: the budget was not the limit. The
   360 whole-file fallbacks fail to shrink because giving back single functions of those files
   breaks the literal pool or the code (e.g. unit 0x80093328: fn_80092D04.cpp, 108 macro-made
   functions; one function back already shifts a .sdata2 word). Guards: a repair loop stops after
   600 s (`loop_seconds`) and file closures of more than 600 functions are not tried
   (`max_group`; the 1,133-function closure at 0x801DD7D4 takes ~70 s per compile); a file
   closure replaces its units only if it links more C bytes than they do alone.
2. **Rerun** (31 new exact functions). The help-bar family (`.symbols.json` mapping
   `__vt__8HbWidget` / `__vt__9HbHelpBar` / `__nw__FUl`): no two units link the same label (the
   files' units either make those functions asm or fail: 0x80057D44 on a header conflict, see
   below; 0x802020AC on `__vt__Q25tu_f011HbInfoPanel`, a vtable the namespacing mangles). The
   only symbol-map rename in the selection is `fn_8028C818 -> __cvt_dbl_usll`.
   gen_tu/gen_units tolerate per-function files that another worker moved or deleted after
   survey.py (their functions count as not exact; a unit that fails is skipped, not fatal).
3. **Shared literals and more** (selection tokens `asmlit`, `def=`):
   - `asmlit`: a .sdata2 float/double literal whose first user is an asm function and that later
     C functions also use is made by the compiler at the asm function's position: a helper
     `tu_lit_<fn>_N` (force_active off, dead-stripped by MWLD and by place.py's model) uses the
     same constants (`tu_f = 0.5f;`, int/unsigned conversion constants through `tu_d = tu_i;`);
     the C functions' literals pool into the same entry. Shared items that the C code names
     (`extern f32 lbl_...`) are defined under their label instead, with the declared type.
     Unit 0x8006DECC: 20 -> 1 asm functions; 17 units use it.
   - `def=`: data the C code names that lies inside the unit's own pool (placement: "lies inside
     the unit's own ranges but the object does not define it") is defined under its name right
     before its first user (bss from the declaration, scalars with their value, bytes otherwise).
   - Pragmas of functions emitted out of file order: a function defined earlier in its file than
     chunks already emitted now gets the pragmas in force at its own place (fn_80008A38's
     `#pragma push / inline_depth(3) / pop` was consumed by an earlier block: 0x204 vs 0x118 bytes).
   - `cnative` is also tried when a mixed C/C++ unit only places with asm: C files compiled as C++
     turn `T f();` into `T f(...)`, and every call of a variadic function sets cr6 (+4 bytes per
     call: most "size +4/+8" codegen failures of auto/ files).
   - Header conflicts reported as `(included from: ...)` chains with wrapped paths are parsed
     (the outermost hoisted header gets the `hfix`); compile errors keep the first 2,000
     characters. Repair rounds 16 -> 32.
4. **Step 4 (rerun with the repair additions)** landed (snapshot good_step4): 2,117 game units
   (136 with asm), **83.7% of the game code from source (0x21BE30), real C 46.0% (0x128B64,
   6,436 functions), asm 37.7% (0xF32CC, 1,509 functions)**, 211 library objects. It adds:
   - `def=` (link_select token): data the C code names that lies inside the unit's own pool
     ("... lies inside the unit's own ranges but the object does not define it") is defined
     under its name right before its first C user (bss from the declaration, scalars with
     their value, bytes otherwise); labels a symbol map gives to a file static are left alone,
     and definitions that do not compile are dropped again.
   - repair rounds 16 -> 32, a 600 s limit per repair loop, no file closures above 600
     functions, and a file closure replaces its units only if it links more C than they do
     (otherwise 0x80009CD0..0x80023170 replaced 94 good units by one with 150 asm functions).
   - try_units.py restores the build's src/tu/lib_aliases.h at exit (it writes every rename while
     it runs; left behind, `ninja` failed on `__vt__8HbWidget`).
   - place.py: a library object that keeps a symbol static which outside code references is
     recorded (`static_outside`), and gen_units.py drops it when that code stays asm (GXFifo.c's
     `__GXCurrentThread`, link error "undefined"); OSMemory.c, CARDBlock.c and SIBios.c are
     dropped by this rule too (3 objects fewer than step 3; their references may be harmless,
     not checked yet). Ranges that do not start/end 4-aligned are refused (dtk "Invalid alignment
     for split" after fs.c's .data).
   Cross-file inlining proper (region .cpp files whose merged code differs by a few words) is not
   handled; the pragma and cnative fixes of step 3 covered the systematic part.
5. **Library sources** (moved to a separate agent; its tools/build proposals, see
   build/tmp/buildlibs/proposals.md). With its lib/ fixes and P2-P4 try_units places 279
   sources; 266 link with the SHA1 (snapshot good_step5libs). The rest are refused by the checks
   below or listed in config/RFEE01/lib_exclude.txt (sources place.py accepts but whose real link
   differs: ogws dvd.c, found by build/tmp/buildtree4/libloop.sh, which drops the library unit in
   front of the first moved symbol until `main.dol: OK`).
   - gen_config.py: an nw4r/EGG name the game links twice (the Home Button menu's own nw4r copy)
     goes to the ogws copy (+5 renames, e.g. `__dt__Q44nw4r2ut6detail12LinkListImplFv`).
   - P3: in `lib_unit` a function symbol wins over a label at the same address, and a reference
     to a label symbols.txt has at the referenced function's address is accepted.
   - P4: only global object symbols are renamed (statics keep their symbols.txt name: no
     clashes between `Callback`/`OnShutdown` statics of several objects).
   - P2: when the dead-stripped model fails, it is retried keeping unreferenced .bss/.sbss
     objects, then all data objects (`keep_data` in units.json) — MWLD keeps such data in some
     objects (dvd.c's TmdBuffer).
   - P1 (strip also on size/contiguity errors) is **not** taken: the weak copy the model drops can
     be the one MWLD links (first in link order). The strip model now drops a weak copy only if
     its DOL twin lies before the object's own functions, and never a global (non-weak)
     definition (scsystem.c's `__SCGetConfBuf` was multiply defined).
6. tu_analyze.py: statics named by a symbol map can be witnesses (`--map-statics-near`: users
   within 0x2000 bytes; `--map-statics`: all). Off by default: fn_8006BDCC's static is a
   function-local static that fn_8006C19C names as `extern lbl_803CB7B8`, so merging the two
   units leaves the reference undefined and the merged unit (0x80068EC4..0x8006C17C, 0x32B8
   bytes) is lost.

TARGET_PC (the port branch): gen_tu.py reads per-function files through `read_source()`, which
resolves `#if TARGET_PC` / `#ifdef TARGET_PC` / `#if defined(TARGET_PC)` and their negations
(`#ifndef`, `!defined(...)`, `!TARGET_PC`), with `#elif`/`#else` and nesting, as if TARGET_PC
were undefined (unifdef -UTARGET_PC; every other conditional stays). Self-test:
`python3 -I tools/build/gen_tu.py --self-test`. The other textual parsers in tools/build read
generated TUs or compiler output (survey.py compiles; macro files are chunked after the
compiler's preprocessing), so they see the original branch already.

## Phase 5 — status and next steps (2026-11-14)

Landed (each with `ninja` printing `main.dol: OK`, SHA1 d1b8deabfec5a96bf38945665ffe203867612c1c;
snapshots build/tmp/buildtree5/good_<step>, each with `build/` = the exact tools/build code
gen_units.py ran, `RFEE01/`, `src_tu.tar`, docs tsv, try_units.json):

| | phase 4 end | step s1 | step s2 | step s3 | step s4 | step s6 | step s7 | step s8 | step s9 (final) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| game units linked | 2,118 (136 with asm) | 2,119 (136) | 2,031 (140; more file closures) | 2,031 (139) | 2,031 (139) | 2,035 (141) | 2,033 (141) | 2,033 (140) | **2,022 (140)** |
| game code from source | 83.7% (0x21BEEC) | 84.1% (0x21EB70) | 86.9% (0x230FE4) | 86.9% (0x230FE4) | 86.9% (0x230FE4) | 88.7% (0x23C264) | 89.2% (0x23F530) | 89.2% (0x23F530) | **89.1% (0x23F1E4)** |
| of which real C | 46.0% (0x128CC4, 6,444 fns) | 46.8% (0x12E0C4, 6,502 fns) | 49.3% (0x13E3E8, 6,874 fns) | 49.4% (0x13EBB8, 6,876 fns) | 49.4% (0x13EC40, 6,889 fns) | 52.3% (0x1512AC, 7,204 fns) | 52.7% (0x154578, 7,286 fns) | 52.8% (0x154E44, 7,290 fns) | **53.1% (0x1567B0, 7,300 fns)** |
| of which asm | 37.7% (0xF3228, 1,502 fns) | 37.3% (0xF0AAC, 1,460 fns) | 37.6% (0xF2BFC, 1,376 fns) | 37.5% (0xF242C, 1,374 fns) | 37.5% (0xF23A4, 1,361 fns) | 36.4% (0xEAFB8, 1,275 fns) | 36.4% (0xEAFB8, 1,275 fns) | 36.3% (0xEA6EC, 1,271 fns) | **36.1% (0xE8A34, 1,250 fns)** |
| library objects | 266 (0x6AFB4 code) | 266 | 267 (0x6C5B8 code) | 267 | 267 (0x6C5B8 code) | 267 (0x6C5B8 code) | 267 (0x6C5B8 code) | 267 (0x6C5B8 code) | **267 (0x6C5B8 code)** |

Why the selected functions are asm (try_units.json `why`), phase 4 -> s2: literal pool / minority
441 -> 455 (but in more code: two new units), compile conflicts 189 -> 116, whole-file fallbacks
278 -> 172 (unit 0x80093328: 121 -> 10 asm), no exact definition 426 -> 362, kept from the previous
selection 0 -> 83, code differences (size/reloc/contiguity) ~170 -> ~180.
New units: 0x80106F98..0x80112B00 (file closure, 222 functions, 22 asm), the sinit unit
0x80175E7C (36 asm), 0x801C875C and 0x801C9FC4 (were data-base).

### s1 (tools/build)

- **Variant v2** (try_units `variant_v2`, applied in `shrink` on the placed asm list, all of it or
  its parts): `rw=lbl_...` (gen_tu `literal_rewrites`: .sdata2 float/double literals that C
  code reads by label, m2c style `extern f32 lbl_804CCC18;`, and that only unit functions use,
  are rewritten into the literal, so the compiler pools them once with the same constant of
  other functions), `order` (gen_tu `order_helper`: a dead-stripped helper before each C
  function makes its first-used .sdata2 literals in DOL order; MWCC's in-function literal order
  need not match the per-function source), and `def=` for other named items inside the unit's
  data ranges (tu_units.json `data`). Undefinable `def=` items are left out (`def_skipped`).
- **C files at one global scope** (pure C units, `cnative`): struct/union/enum tags, typedefs
  and statics two files (or a hoisted header and a file) define differently are renamed in the
  later file (`c_local_names`, `rename_idents`); a fn_/lbl_ declaration that differs from the one
  in force becomes `typedef ... tu_T_<name>_<k>; #define name (*(tu_T*)&name)` for that file's
  blocks (`c_redirect`; MWCC still emits a direct `bl`); a later file's declaration of a unit
  function another file defines gets the definer's prototype first when it only uses basic types
  and struct tags (`c_simple_proto`). Identical static helpers and identical declarations with
  a leading comment are deduplicated.
- **Macro scoping**: a file's `#define` is #undef'd in other files' blocks; a hoisted header's
  macro is hidden in the blocks of a file that does not include that header and defines the
  name itself (`header_closure`: rC2 more.h `#define GD ...` vs a file's `struct GD`).
- `operator new/delete` are emitted at global scope once; C++ classes with inline members in
  files chunked after preprocessing are compiled with `force_active off` (their weak
  out-of-line copies are dead-stripped as in the original link).
- place.py `place_game`: when the dead-stripped model still fails, its errors are returned (the
  helpers' "not in symbols.txt" and their contiguity breaks blamed innocent neighbours).

### s2

- try_units: after shrink, the previous selection's line is re-placed and kept (and shrunk) when
  it links more C (`prev_result`); shrink also tries `cnative` on the placed asm list for mixed
  C/C++ units (this freed 0x80093328: fn_80092D04.cpp's functions were asm because C files read
  as C++ turn `T f()` into `f(...)`, +4 bytes of cr6 per call).
- gen_tu `define_item`: arrays declared with an element type (`extern u8 lbl_X[0x2c8];`) are
  defined with that type; definitions in cnative C files use the C form.
- place.py: a code reference into a data section that no DOL reference places ("no references
  from code") is reported as `.text+0x..`, so the function is blamed instead of the whole unit.
- `credir=` (C++ units): an extern "C" fn_/lbl_ name two files declare differently ("identifier
  ... redeclared") is redirected in the later file to `tu_fK::name` of the first declarer
  (repair loop, generator, gen_units token).

### s3 (landed)

- `_lit_stmt` refuses denormal values (an 8-byte .sdata2 item that is not a double: MWCC
  "number is out of range"); all-zero .sdata2 items of asm functions are made as 0.0 literals
  (bytes went to .sbss2); the hoisted headers' local names are cached per include list.

### s4 (landed)

- variant `hoist` (token on the link_select line): a file chunked after preprocessing keeps only
  its own lines (`preprocessed_own`: stack depth 0 of the compiler's `#line` markers) and its
  #includes are hoisted like the other files'; its header classes are then no longer copied into
  its namespace (unit 0x80057D44: the namespaced vtable `__vt__Q26tu_f218HbWidget` disappears and
  the unit gets to ordinary pool errors). Tried in shrink and for units that do not place.
  Effect: +13 functions in C; 0x80057D44 and 0x802020AC still do not place (the repair loop
  without hoist ends on the namespaced vtable, with hoist on pool bases).

### s5 (link failed, not kept) and s6 (landed)

- **Namespaced class names** (place.py `strip_tu_ns`, `lookup_name`, `object_renames`): a class a
  per-function file defines lives in `namespace tu_fN`, so its vtable is
  `__vt__Q25tu_f011HbInfoPanel` where the file's symbol map says `__vt__11HbInfoPanel`.
  Placement looks such names up without the namespace, and the unit's renames (symbols.txt,
  lib_aliases.h) use the name the object really has.
- **End of the TU not force_active**: what MWCC emits at the end of a TU (weak vtables of
  header classes such as `__vt__4HbRc`, out-of-line inline copies) took the TU's
  `force_active on` and could not be dead-stripped; the generated TU now ends with
  `#pragma force_active off`, and place.py's strip model also runs on "no references from code"
  errors. Units 0x80057D44 (194 functions, 3 asm) and 0x802020AC (33 functions, 11 asm) link.
- **Macro isolation fix**: s1's isolation #undef'd `NULL` in other files' blocks when one file
  defined it itself (0x801F17C4 went 58 -> 72 asm in s1, now 57 before shrink); NULL/TRUE/FALSE
  are never isolated, and a macro a hoisted header also defines gets the header's definition
  back. `#ifndef NULL / #define NULL 0` after the includes when a header fix undefined NULL.
- **C file vs C++ file conflicts** (`credir=` names that a cnative C file declares too): one
  prototype with pointer types erased to `void *` is declared at global scope first
  (`erased_proto`), the C file's declaration and the C++ files' are redirected to it. Not for
  unit functions defined in C (their definition cannot be redirected).
- **Symbol-map labels and `#undef`**: only the unit whose object defines a symbol-map name
  #undefs the label's alias (`settle_renames`); the others reach it through lib_aliases.h (s5
  failed to link: tu_8022DFE0 referenced `lbl_8038CB1C` raw while symbols.txt had
  `__vt__8HbWidget`).
- **Header-defined helpers** (`header_global_functions`): non-static functions a hoisted header
  defines (strpool.h's `StringPool`) get a unit-unique name (`StringPool__tu_<first fn>`); two
  units including strpool.h failed with "multiply-defined: StringPool" in s5.
- try_units `lead_merges`: a unit that needs `lead=` items of the unit before it is tried merged
  with that unit (gen_units would drop it for the overlap); in s6 the comparison still counted
  the dropped unit, so 0x8002545C stayed out.

### s7 (landed)

- `lead_merges` no longer counts the unit that gen_units.py drops: 0x80025388..0x80025A74 and
  0x8007DF48..0x80080C24 (or their neighbours) now link as one unit each (2 of 2 merges).

### s8 (landed)

- variant `inl` / `inl=fn_a,..` (cross-unit inlining, step 5): a function of another unit that a
  per-function file defines ahead of a unit function was emitted as a prototype, so calls the
  original compiler inlined (-inline auto) became `bl`. Now it is emitted as a `static` copy
  under the name `<fn>__tu_inl` (`#define` in force in that file's blocks, force_active off):
  inlined calls leave nothing and the unreferenced copy is dead-stripped; copies that the
  object still calls are listed after `inl=` and stay prototypes (try_units.run_once repeats
  the compile until none is left). Unit 0x80193590: fn_80193A2C (0x3AC, fn_80193404 inlined)
  places in C. Tried in shrink. Effect over the whole build: 88 units take `inl`, +4 functions
  in C; most remaining "size" differences are not cross-unit inlining.
- What the remaining code differences look like (build/tmp/buildtree5/t_fdiff.py <unit> <fn>
  gives one function back and diffs it against the DOL): e.g. fn_8022B07C (-4 bytes): the
  original reads `lbl_80371F70 + 9` with a separate `addi`, the merged unit folds the offset
  into the relocation because the label is now defined in the TU (`def=`); a `def=` item can
  so block the give-back of its users. Other -4/+4 cases are the cr6 set of calls through
  unprototyped / variadic declarations that differ between the merged unit and the file.

### s9 (landed; the final tree of the build phase, snapshot good_s9)

- Literal-pool round. Finding: the odd-sized .sdata2 items (7/9-byte splits) are only ~42 of the
  ~440 "minority" functions; most minority functions are given back by shrink together with a
  C file whose declaration conflicts with a C++ file (e.g. 0x801BC88C:
  `M2C_UNK fn_8007E154();` vs `int fn_8007E154(...)`). Shrink now resolves such conflicts in
  the give-back attempt (adds the name to `credir=`, `M2C_UNK` counts as a basic type for the
  erased global prototype), and when a give-back fails it retries without the `def=` labels the
  given-back files name (a label defined in the TU changes the code of `lbl + const`).
- The new src/game sources for 0x8024CF54 (sndmgr.h) made that unit place in try_units (70 of
  197 functions asm), but the linked DOL differed (SHA1 b7d41aa8...): its object's .bss is
  0x2F50 bytes, place.py's dead-strip model placed only 0x330 of it (804303B8..804306E8), and
  the real link moved everything after it by -0x190 (MWLD keeps different statics than the
  model). The unit was removed from link_select.txt by hand for s9 (it stays asm); dropping it
  gave `main.dol: OK`. The 0x8003CD54 change was not in the s9 survey yet (it landed while
  try_units ran); the next round picks it up.
- Net: +10 functions in C, -21 asm; the game code from source is 0.1% lower than s8 (the asm
  of a few units whose shrink took a different path is now in dtk's asm instead of the units).

### Open (and why)

- **0x8003CD54..0x80042AC4: bss block now one model (done in src/game).** The state objects of
  fn_8003CD54 .. fn_8003DCAC (lbl_803CA720 .. lbl_803CA7B0, 0xA0 bytes) are defined once, in
  function order, as file statics in src/game/rB_8002E1C4/statefn_bss.h, included by
  fn_8003CA20.c, fn_8003CFD4.c, fn_8003D6D4.c and the sinit fn_8004288C.cpp (which dropped
  `sHead`). Not function-local statics as first planned: without the 0xA0 bytes in front, the
  sinit alone addresses its objects as block + 0x00.. instead of + 0xA0.. and is no longer exact.
  Each file stays exact (symbol maps `sState_<fn>` -> label; sinit keeps "...bss.0" =
  lbl_803CA720). try_units on unit 313 no longer reports the bss block; what keeps ~46 functions
  asm there is .sdata2 ("cannot derive a single base"), fn_800429EC's size and the MapUnit/Unit
  conflict in fn_80042914/fn_800429F8.
- **0x8024CF54..0x8025F3B8: the sound manager's statics are defined once (done in src/game).**
  src/game/rS_8023FD30/sndmgr.h is the only definition of the block at lbl_8042E798, without
  constructors: the locks are POD storage (`SndLockRaw sMutexRaw / sCmdMutexRaw`) seen through
  the virtual classes by `#define sMutex (*(SndLockable*)&sMutexRaw)` (keeps the original
  virtual-call code), the sinit's chain records/heap/effect blocks are members of the layout, and
  `rS_sndKeep` is gone. fn_8025EBF0.cpp includes sndmgr.h. All six files exact, offsets checked
  through symbol maps ("...bss.0" = lbl_8042E798). try_units on unit 2682 no longer reports
  __sinit/.ctors; the next blocker is "minority: .bss: cannot derive a single base (0x8042e798,
  0x8042e878, 0x804303a0)" (files of the unit that address the block through other labels).
- C-mode / C++ conflicts on unit functions defined in a C file (MWCC compares the C
  definition with the C++ files' extern "C" declarations) are still blamed (asm).
- 4 library objects are skipped because only asm references their kept function.
- Cross-file inlining (step 5): most "size" differences seen were the cr6 calls of C files read
  as C++ (now tried with cnative); not otherwise started.
- OSMemory.c, CARDBlock.c, SIBios.c: linked since phase 4 step 5 with the SHA1, so their
  kept-static references are harmless.

### Closing state of the build phase (s9)

`ninja` reproduces main.dol (SHA1 d1b8deabfec5a96bf38945665ffe203867612c1c) with 2,022 game units
and 267 library objects linked from generated sources: 89.1% of the game code comes from source,
53.1% as real C (7,300 functions) and 36.1% as MWCC asm functions (1,250). Everything is
regenerated by the pipeline under "Commands" (no hand edits except the one link_select line of
s9, documented above); phase 5 moved real C from 46.0% to 53.1% and asm from 1,502 to 1,250
functions.

### Next steps

1. Shrink: when a give-back fails, retry it without the `def=` items its function names (they
   change codegen of `lbl + const`), and with the file's own declarations of unprototyped
   callees in force (cr6).
0. Unit 0x8024CF54: model MWLD's dead-stripping of local .bss statics like the real link (the
   s9 link moved .bss by -0x190), or keep the unit out (gen_units cannot tell yet).
2. Remaining classes (s8): shared literal pools / minority ~440 functions (mostly units with odd
   dtk splits of .sdata2 items, e.g. 0x801D60D0's 7- and 9-byte items), no exact C ~380,
   whole-file fallbacks ~160, codegen differences (reloc/size/other) ~170, compile conflicts
   ~56 (mostly C files whose unit function a C++ file declares differently); the two src/game
   bss items above are done, their units now stop at other blockers.

### Commands

```
python3 -I tools/build/survey.py -j 8
python3 -I tools/build/tu_analyze.py
python3 -I tools/build/try_units.py -j 8 --asm --write-select --prev build/tmp/buildtree5/good_s9/RFEE01/link_select.txt
sh build/tmp/buildtree5/build.sh <tag>   # gen_units -j 8, gen_config, configure, ninja -j 8, coverage
```
(build/tmp/buildtree5/round.sh <tag> <prev link_select> runs all of it.) Keep a result only with
`main.dol: OK`; otherwise restore the last good_<step> (RFEE01/ -> config/RFEE01, src_tu.tar,
build/ -> tools/build, docs tsv). Test helpers in build/tmp/buildtree5: t_v2once.py (one unit,
v2 parts, give back by `why:` prefix, CN=1 for cnative), t_hf.py, t_place.py, pool.py,
objpool.py, whocalls.py, why.py (asm reasons).

## Main obstacles

1. **Literal pools shared between asm and C functions** (486 functions, 0x4B4A0): when a function
   that stays asm is the first user of a literal a later C function also uses, the C object pools
   that literal at the C function's position and the pool shifts. The repair loop makes the C
   users asm too. Ways out: the asm function's matching C version (each one that becomes exact
   frees its sharers), or a rewrite that makes C functions reference such literals by name.
2. **Units too large for the shrink budget** (360 functions in whole-file fallbacks): raise
   `ASM["shrink_budget"/"shrink_seconds"]` in try_units.py, or run try_units with a process pool
   (threads are bound by the GIL: generation and placement are Python).
3. **Cross-file inlining** (codegen, ~200 functions): a function inlined from another file in the
   original TU; per-function files need static-inline copies that match when merged.
4. **Library sources**: 278 candidates still fail (codegen 93, dead-strip 57, extra-symbol 27,
   data-base 21, duplicate 18, ...): mostly source differences or names; per-source work.
5. **TU cuts through file statics**: fn_8006BDCC's static (lbl_803CB7B8) is also used by
   fn_8006C19C in the next unit; `tu_analyze.py --map-statics` closes such cuts but makes larger
   units that do not place yet, so it is off.
6. **dtk write-back** into symbols.txt is still overwritten by gen_config.py.

## Plan for the rest

1. After each matching round: `survey.py`, `tu_analyze.py`, `try_units.py --asm --write-select`,
   `gen_units.py`, `gen_config.py`, `configure.py && ninja`; keep the selection only with
   `main.dol: OK` (the last good state is kept in build/tmp/buildtree3/good_final).
2. Obstacle 1 (named shared literals), then obstacle 2 (process pool, larger shrink budget).
3. Static-inline copies for cross-file inlining (codegen class).
4. Library sources one by one from docs/tu_libs.tsv.
5. TU map refinement and real source files; data into C (unchanged from the earlier plan).
