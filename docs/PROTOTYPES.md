# Prototype audit

Each source file declares the functions it calls with its own stand-in types. A declaration that passes fewer arguments than the callee reads still compiles to the original's instructions whenever the right value happens to sit in the register, so the matching checks can't see it; the equivalence review (docs/SCHED_REVIEW.md) found eight real bugs of this kind. For the port every function needs one correct declaration.

`tools/protos.py --tsv docs/PROTOTYPES_CONFLICTS.tsv --asm docs/PROTOTYPES_SHORT.tsv` writes two reports:

- `PROTOTYPES_SHORT.tsv`: definitions and declarations that pass fewer argument registers than the original code of the function certainly reads before writing (directly or through known direct callees; indirect and unknown callees count as reading nothing). Shapes are `return(params)` with I = integer/pointer register, F = float register, S = named type by value, V = void. "reads 8 int" usually means a variadic function. The last two columns say which files really call the function with that declaration (the others only take its address). This is the list to fix; first scan: 155 functions called through a short declaration in about 490 exact or equiv files, and 141 definitions that take fewer parameters than their code reads.
- `PROTOTYPES_CONFLICTS.tsv`: functions whose declarations disagree in shape with the definition (`hard`: other registers used; `soft`: only the return kind). Wider and noisier: an integer parameter declared before or after the floats uses the same registers.

Fixing rule: correct the declaration, pass the missing argument at each call (the value the original caller has in that register), and re-run the file's check. An exact file must stay exact and an equiv file must keep its class with `symcheck.py --anon --xargs` clean. Where no spelling keeps the class, leave the code and record the function in `docs/signatures/`. Verified signatures are collected in `docs/signatures/*.tsv` (function, shape, variadic, evidence) for the later shared header.

## Result of the first pass (2026-11-13)

Three agents settled every row of the first report. `docs/signatures/proto{1,2,3}.tsv` record each function (true shape, fixed / false positive, evidence, files changed); about 520 functions were fixed in about 500 files, the rest were false positives of the tool. Every edited file was re-checked: no exact file lost its MATCH, no equivalent file lost its class or gained a flagged block, and three drafts became exact because the missing argument had been their only difference (fn_80106190, fn_8028B84C, fn_80232334, now promoted).

Among the fixed calls are real port bugs, for example the biorhythm float never passed to the hit/avoid/crit bonus functions (fn_80107864, fn_801278B8), VIConfigure called without the render mode, a rotation with a garbage angle (fn_80312830), skill checks on a garbage unit pointer, and save-header checks on a garbage buffer. The agents' reports list them per region.

The tool learned from the false positives: `clrlslwi` only writes, `xor rX,rY,rY` reads nothing, a 64-bit integer takes an aligned register pair, the unused half operand of `ps_sum0/ps_sum1` doesn't count, a switch reaches no particular case in "certainly reads" mode, local float typedefs are recognised, `case X:` lines aren't declarations, calls through a header's declaration count as calls, and unprototyped C declarations are now checked against the argument counts of the actual calls (`unprototyped call` rows).

Left after the pass: `PROTOTYPES_SHORT.tsv` now holds 63 `unprototyped call` rows (m2c-written files in src/game/auto that call through `()` declarations with too few arguments: to be checked) and 11 known false positives (register hand-over in hand-written asm around fn_8001D2FC; uninitialised locals read on a switch default path; OSTime typedefs).

`tools/protos.py --catalog docs/signatures/CATALOG.tsv` lists every game function once: the shape and text of its best definition (exact file first, then equiv, then wip), the audited shape and status where the audit settled it, and any other declaration shapes still in use. This is the reference for the shared header of the port.

## Second pass: unprototyped calls (2026-11-13)

All 63 `unprototyped call` rows in src/game/auto were real: the m2c-written callers dropped arguments the original passes (the caller's own parameter still in the register, the result of the call just before, or a value just loaded and tested). Fixed in 80 files, all still exact; records in `docs/signatures/proto4.tsv`. Among them 13 deleting destructors that called operator delete without the object, the GX state-cache wrappers (cull mode, TEV swap modes), a command iterator without its cursor, and DVDClose without its file. fn_8010B1D8 returns its tail-callee's pointer (I(I), corrected in proto1.tsv). What remains in PROTOTYPES_SHORT.tsv are the known false positives listed above.
