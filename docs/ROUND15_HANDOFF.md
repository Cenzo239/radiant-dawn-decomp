# Round 15 handoff — 2026-11-09

## Current verified results

- Claude checkpoint: 27 untracked source files, 32 functions, 40,600 bytes.
- Codex additions: 9 source files, 12 functions, 560 bytes.
- Combined: 36 files, 44 functions, 41,160 bytes pass the strict function checker.
- No cumulative project percentage is claimed. No full DOL rebuild or push was performed. Sources and WIP are included in the local round-15 checkpoint commit.

## New matches

| Source | Functions | Bytes |
| --- | ---: | ---: |
| `src/game/auto/80020000/fn_80025C20.cpp` | fn_80025C20, fn_80025F34, fn_80026324 | 168 |
| `src/game/auto/80020000/fn_80025EA4.cpp` | fn_80025EA4 | 68 |
| `src/game/auto/80020000/fn_80025F88.cpp` | fn_80025F88 | 28 |
| `src/game/auto/80060000/fn_800656A4.cpp` | fn_800656A4 | 24 |
| `src/game/auto/80080000/fn_8008E258.cpp` | fn_8008E258 | 56 |
| `src/game/rE_800E5DE4/fn_80101B50.cpp` | fn_80101B50 | 48 |
| `src/game/rE_800E5DE4/fn_801026F4.cpp` | fn_801026F4 | 32 |
| `src/game/rH_80112B48/fn_801315EC.cpp` | fn_801315EC, fn_801317EC | 120 |
| `src/game/rK_800CF8BC/fn_800E1DDC.cpp` | fn_800E1DDC | 16 |

## Strict reference verification

`tools/check_func.py` now accepts `--strict-references` and an optional `--symbol-map` JSON file mapping compiler-local names to existing original symbols. Maps cannot override original symbols and must name symbols present in the compiled object. Unknown pointer-table references are also reported. Default invocations remain compatible.

Two earlier unchecked references have been resolved without changing Claude's matching sources:

- `fn_801C5874.symbols.json`: `cnt$765` → `lbl_804CB9EC`. The original loads/stores this counter at 0x801C58C4 and 0x801C5904.
- `fn_8028A88C.symbols.json`: `...bss.0` → `lbl_80430CE0`. The original establishes this base at 0x8028A8E0/0x8028A8F4; the cursor-array offset 0x21F0 agrees with the source layout. All referenced offsets are checked, not just the base.

```sh
python3 -I tools/check_func.py src/game/rF_8017F400/fn_801C5874.cpp --symbol-map src/game/rF_8017F400/fn_801C5874.symbols.json --strict-references
python3 -I tools/check_func.py src/game/rN_8025EEF0/fn_8028A88C.cpp --symbol-map src/game/rN_8025EEF0/fn_8028A88C.symbols.json --strict-references
```

All other files in this round pass with `--strict-references` alone. Compiler-only helpers not named in symbols.txt remain outside the function-matching count.

Validated negative cases: missing map, wrong mapped address, unknown original symbol, stale local symbol, attempted original-symbol override, and a non-object JSON map all fail. The original 27 files and all 9 new files were then rechecked with strict references. `git diff --check` passes. The detailed run log is `build/round15_strict_audit.json`; this document and the symbol maps preserve the useful results outside scratch.

## Saved WIP

- `src/game/rF_8017F400/wip/fn_801959A0_codex.cpp`: 5,160-byte menu function improved from 13 differing words plus four incorrect constant references to 8 differing words. Corrected waits: 30→5 at two sites, 40→30, 50→25. Remaining instruction offsets: 0xC80, 0xC84, 0xFF0, 0x1000, 0x1018, 0x1020, 0x1024, 0x1030. Local BSS and `__div2i` references still need explicit verification before promotion.
- `src/game/rI_801DD7D4/wip/r15a/fn_801FE8BC_codex.cpp`: explicit scalar loads improve the point helper from 11 to 9 differing words.
- `src/game/auto/80020000/wip/fn_80025C64.cpp`: four differing words; the compiler folds the final 0/2 branch into arithmetic.
- `src/game/auto/80060000/wip/fn_800642B4.cpp`: six differing words; the enabled boolean and inner-loop counter use exchanged registers. Declaration permutation, by-reference locals, and basic integer-width variants did not finish it.
- `src/game/rK_800CF8BC/wip/fn_800D70F4_standalone.cpp`: self-contained reproduction of the original two-word scheduling miss. The original fragment remains intact.

Other attempted round-15 near misses: `fn_80181470` remains at four words after byte-swap expression permutations; `fn_801EA17C` still lacks a redundant late `extsh`. No speculative source was promoted.

## Continuation

Use the saved WIP files above or continue the uncovered ranges around 0x80025B0C and 0x80063BE0. A conservative m2c scan of 14 functions in these ranges produced no additional matches. Prefer symbol-backed references, preserve original WIP attempts, and only promote code after the full checker succeeds. Existing unrelated changes to `tools/lib/ogcompile.py` and `tools/lib/fuzzy.py` were left untouched.

## Continuation after f9eaaf4

Three additional functions pass strict checking: `fn_80025C64` (100 bytes), `fn_80025CC8` (176 bytes), and `fn_80026778` (288 bytes), totaling 564 bytes. Sources live in `src/game/auto/80020000/`.

- `fn_80025C64`: assign the call result to a local before setting the default return value; this retains the original final branch instead of folding it into arithmetic.
- `fn_80025CC8`: a non-polymorphic base word places the virtual table at +4. Virtual methods return int; explicitly narrow their results to short into int locals. This preserves the original sign extensions and register allocation.
- `fn_80026778`: ordinary 32-element array initialization produces the original compiler-unrolled loop. Keep the initialization helper separate from the final global field resets.

The old WIP for `fn_80025C64` is historical; use the matching source above.

Local batch: `python3 tools/local_wip_batch.py` scanned 328 WIP files and tested 16 conservative candidates, using four workers and up to 250 variants per searchable candidate. No new complete matches resulted. Raw outcomes are in `build/round15_local_batch.json`. Many candidates have too few leading declarations for this search method; those require structural changes, not more declaration permutations.

## Continuation after 6edb87c

`fn_8006556C` now matches all 312 bytes with strict reference checking. Source: `src/game/auto/80060000/fn_8006556C.cpp`. The function applies the two rows of seven item slots, updates the affected units, and clears the temporary slots.

The first and final loops need separate pointer and counter locals for the original register allocation. A local declaration-order search reduced the difference to two instructions; permuting the first loop's pointer increments finished the match. No assembly substitutions or byte patching were used.

## Continuation after e8375f9 (2026-11-10)

`fn_801CADE0` matches all 72 bytes with strict reference checking. Its color
copy constructor uses volatile byte stores to retain the original stack
temporary. This expresses the required code generation; it is not evidence
that the original source used volatile. The source contains no assembly or
byte patches.

Saved near misses (not counted as matches):

- `auto/80060000/wip/fn_800656BC.cpp`: 756 bytes, only six differing words,
  references correct. Separate context-pointer loads and shared locals across
  loops reduced the initial mismatch; the final six exchange the availability
  loop's outer counter and Boolean registers. Declaration search (including
  2,400 randomized variants), loop forms, integer types, scoped Boolean
  variables, and an inline row helper did not finish it.
- `auto/80060000/wip/fn_800649AC.cpp`: 328 bytes, six differing words,
  references correct. Same outer-counter/Boolean allocation issue.

A recursive scan of 381 WIP files included nested round directories and
functions previously skipped because their names occur as call references.
No baseline exact match was newly promoted: apparent hits also occurred in
existing macro-generated definitions. Always search both `fn_ADDRESS` and raw
`ADDRESS`, including macro arguments, before promoting a candidate.

Useful additional candidates already preserved in their existing WIP files:

- `rI_801DD7D4/wip/r13b/fn_80217DF8.cpp`: 1 of 404 words differs
  (`clrlwi r29,r3,16` instead of `mr r29,r3`). Widening `sel` to int
  removes the narrowing but causes six register differences. Virtual return
  widths and basic local-width changes did not solve both simultaneously.
  The generated `__ptmf_scall` call corresponds to `fn_8028C178`: original
  call at 0x802183FC. This needs a symbol-map sidecar for strict checking
  when the function is eventually promoted.
- `rP_80105B04/wip/fn_80109DF8.cpp`: 2 of 321 words differ, pointer and
  counter increments at +0x3D8/+0x3DC are reversed. Loop syntax, increment
  order, and counter-width variants did not finish it.
- `rT_80026898/wip/fn_80042D38.cpp` contains `fn_80044530`: one
  `mr` instead of `addi ...,0` at +0x28. This likely needs the original
  pooled static script tables, not a struct wrapping an extern array.

Scratch scan/search logs are under `build/tmp/`; all improved decompilation
sources above are preserved outside scratch. Unrelated compiler/fuzzy-tool
changes remain untouched.

## Continuation after 616e27a

`rT_80026898/fn_80044530.cpp` now matches all 88 bytes. Reconstructed the
three original script tables as separate file statics, including their opcodes
and symbol-backed pointers (600 data bytes at 0x80379F58–0x8037A1AF). MWCC
pools these statics and emits the original `addi r3,r31,0`; the former struct
wrapper emitted `mr`. The original WIP remains historical.

This exposed two checker gaps, now fixed in `tools/check_func.py`:

- MWCC's `...data.0` pool base has size zero. Previously only its first four
  bytes were checked. The checker now checks through the next pool base or
  section end.
- A mixed table's relocated pointers were checked, but its ordinary opcode
  bytes were skipped. Both are now checked. Unsupported table relocation
  types fail instead of being assumed to be full 32-bit pointers.

`python3 tools/test_check_func_tables.py` passes five integration tests: the
original table, a changed first opcode, a changed interior opcode, a changed
early pointer, and a changed late pointer. Negative cases retain identical
function instructions and must fail specifically on the data comparison.
All 42 files in the extended round-15 strict audit pass; details are recorded
in `build/round15_table_audit.json`.

Additional local searches made no new matches: 4,000 randomized declaration
variants for `fn_80217DF8`, 360 direct-Boolean declaration/type variants for
`fn_800649AC`, and targeted variants for `fn_8018524C`, `fn_8028B84C`,
`fn_800FBC90`, and `fn_801A2268`. Their existing best WIP sources remain intact.

## Continuation after ecf5285

Two new functions match with strict references, totaling 452 code bytes:

- `rE_800E5DE4/fn_800EB410.cpp` (156 bytes): registers 14 event-process
  classes. Reconstructed all 2,104 bytes of initialized descriptors at
  0x80384300–0x80384B37, using original symbol names for every pointer.
  Separate static descriptors reproduce the original pooled addressing.
  The enhanced checker verifies the complete pool's data and relocations.
- `rN_8025EEF0/fn_8028B154.cpp` (296 bytes): screen-buffer setup. Separate
  texture/state statics reproduce the original 0x60-byte BSS layout; the
  symbol-map sidecar maps `...bss.0` to `lbl_80430CE0`. The state area at
  offset 0x4C extends through the end of that block; declaring it as only
  four bytes incorrectly puts it in small BSS and prevents pooling.

Both pass the full checker; an intentionally incorrect BSS-base mapping is
rejected. Results: `build/round15_static_matches.json`. Older WIP copies for
these two functions are historical.

The controller WIPs `fn_8007A528`, `fn_8007B2F4`, and `fn_8007B458` are
already superseded by `rJ_800799AC/fn_8007A868.cpp`; do not count or promote
them again. A scan for remaining short functions consisting only of multiple
`fn_800846BC` calls found no further unimplemented registrations.

## Continuation after 29579c8

Two new functions match with strict references (284 code bytes):

- `rN_8025EEF0/fn_8028BC54.c` (128 bytes): initializes the two screen-state
  blocks. Generated locally with m2c, then rewritten with typed field layouts.
  All float constants still refer to their original symbols.
- `rE_800E5DE4/fn_800FAFF0.cpp` (156 bytes): conditionally updates the map
  position and calls the optional refresh helper. Explicitly load y before x
  into float locals, then convert both for the call. Converting to int at the
  declaration or directly inside the call gives a different instruction order.

The pipeline default upper bound was exclusive but equal to the last game
function's start, 0x8028BC54. Changed it to 0x8028BCD4 (start of `strlen`).
A targeted run starting at 0x8028BC54 now discovers and matches one function.

`auto/80110000/fn_80110D00.c` was already matched. Its slot-clear helper had
an old-style prototype and was invoked without the slot argument, relying on
the register retaining the right value. Added the proper pointer parameter and
explicit argument. All 56 bytes and references remain identical; this is not
counted as a new function.

Local batches checked 50 open functions of 24–128 bytes and the first 100
open functions above 128 bytes (up to 268 bytes in this batch), using four
workers. The small batch found fn_8028BC54; the medium batch found the
four-word near miss fn_800FAFF0 subsequently completed above. Detailed
scratch outcomes: `build/tmp/small_batch_results.json` and
`build/tmp/medium_batch_results.json`.

Candidate discovery must handle definitions on the same line as a preceding
prototype: a line-anchored definition regex missed the existing
fn_80110D00. Check all source mentions before promoting any apparent match.
Additional constructor, return-type, arithmetic, and declaration searches
did not complete fn_8013157C, fn_80079D90, fn_80176B0C, fn_80280CB4, or
fn_8009AB90. Their previous best WIPs remain unchanged.

## Continuation after fc81db8

Four new functions pass strict checking, totaling 248 code bytes:

- `rN_8025EEF0/fn_80282720.cpp` (156 bytes): language-dependent resource
  load/check. Keep the language local as signed char, matching the source byte;
  an int local exchanges its register with the table-base register. The table
  is an array of string pointers, not the byte array inferred by m2c.
- `rM_8014C9F8/fn_8015FAF8.cpp` and `rF_8017F400/fn_801C8300.cpp`
  (24 bytes each): model the unit flags at +0x108 as one unsigned 64-bit field.
  OR-ing bit 0 or bit 32 produces exactly the original single-word update,
  including the unit-pointer register. The context declaration retains the
  original 0x130-byte size so its pointer is not treated as small data.
- `rN_8025EEF0/fn_802889AC.cpp` (44 bytes): a local
  `#pragma optimize_tail_call off` retains the original ordinary call and
  epilogue. The pragma is scoped with push/pop. This is a code-generation
  requirement, not a claim about the original project's compiler settings.

Audit results: `build/round15_type_matches.json`. Existing WIP fragments for
these four are now historical.

The next 100 medium candidates were compiled with four local workers; no
additional exact m2c matches resulted. Results:
`build/tmp/medium_batch2_results.json`. Targeted experiments confirmed:

- `fn_80117F74` still matches its first 148 bytes but has an extra unreachable
  blr. Loop, inline, and optimization-pragma variants did not remove it. Do not
  count it as a match or trim the emitted object bytes.
- Using 64-bit flag views in the slot loops did not change their six remaining
  register mismatches. Widening the Boolean itself to long long triggers an
  internal error in this MWCC version; keep the saved best WIPs.

## Continuation after 14cbaa6: near-match checkpoint

No new exact match in this pass. The standalone WIP
`rM_8014C9F8/wip/fn_80150B20.cpp` improves the earlier five-word color-copy
candidate to three differing words out of eleven (44 bytes). Strict checking
reports only the order of the alpha, green, and blue loads at +8/+12/+16;
registers and stores match. Volatile reads are an experimental scheduling
constraint, not evidence of original source qualifiers. Keep this in WIP.

The final 119 candidates from `actually_open_medium.json` were processed
with four local workers, completing the 319-candidate medium scan. No exact
automatic match resulted in this final batch. Scratch results are in
`build/tmp/medium_batch3_results.json`.

Other experiments, to avoid repeating unsuccessful searches:

- Color copy: 384 load-order/volatile-mask variants, followed by 576
  load-order/store-order and 576 load-order/declaration-order variants;
  the best remains three differing words.
- `fn_800DA430`: flag/duration parameter reuse, flag widths, and reordered
  inline-wrapper arguments did not improve the eight-word WIP.
- `fn_800DF0B8`: explicit unit validity checks reproduce the existing
  19-word WIP; declaration permutations and object-pointer types did not
  resolve the r30/r31 exchange. Beware `wip_search.strip_others`: it can
  mistake a function call inside a macro for a definition and remove the
  macro's conditional return. Inspect extracted helpers against the source.
- The `fn_8005B508` widget family has stale closeness comments. The current
  standalone WIP checks as 0x18C bytes versus 0x188, not an equal-size match.
  Constructor constants, pooled empty strings, and call argument experiments
  did not complete it. Do not promote dummy string-pool forcing functions.
- `fn_80283528`/`fn_802836C0`: 48 helper argument-order/type variants did
  not improve 12/4 differing words. `fn_8002FFDC` flag-width variants remain
  seven words off; `fn_8025F068` byte-to-float variants remain four words off.
- `fn_800FC5AC` still lacks the original unreachable final blr (40 versus
  44 bytes); loop/goto alternatives did not reproduce it.

## Continuation after a3a8e82

One new strict match: `rD_8008E3B4/fn_8008D6E8.cpp`, 104 bytes. This
destructor restores `lbl_8038C294`, invokes its virtual method at vtable
offset 0x10, and optionally frees the object. Modeling the call as a C++
virtual method produces the original r12 dispatch and register scheduling.
The vtable remains an explicit original symbol, so all references are
checked. No generated vtable is substituted. The final formatted source
passes `tools/check_func.py --strict-references -v`.

Further local experiments (no additional exact matches):

- `fn_80150B20`: 192 inline helper, argument-order, aggregate return, and
  volatile-input variants did not improve the saved three-word WIP.
- `fn_800CF890`: 192 typed-object/helper/local-order variants still exchange
  the two object/table register pairs. The apparent two-word difference
  also has four wrong references; it must not be accepted as a near-exact
  reference match.
- `fn_80077D44`: the byte checks match, but the final pointer addition is
  reassociated. Integer-width, inline-return, C++ Boolean, and optimizer
  variants did not complete it. The two-word byte-sized candidate has an
  extra mask and is four bytes too long; the three-word baseline is better.
- `fn_8022C2D8`: modeling the referenced object's virtual destructor
  reproduces the redundant null check through cr1, but the zero still is
  not retained in r31 across the call. No improvement over existing WIP.
