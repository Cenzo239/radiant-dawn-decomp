# Round 15 a: 0x801DD7D4..0x80213000

16 new matches, 0x36C0 bytes (14,016). The 25 KB aim was not reached. One file per function. Each prints MATCH from `python3 -I tools/check_func.py --strict-references <file>`.

| file | bytes | notes |
|---|---|---|
| fn_801F5A44.cpp | 0xA4C | list-cursor menu, `curVal`/`adv` family |
| fn_80202FF4.cpp | 0x844 | same family |
| fn_801F99A0.cpp | 0x7C0 | same family |
| fn_8020291C.cpp | 0x6D8 | `wfInit` constructor plus the family; matched on the first compile |
| fn_801F243C.cpp | 0x484 | scale chain, 16 lazy statics, `new` of a 0x24 effect |
| fn_801DD844.cpp | 0x248 | |
| fn_801E9F38.cpp | 0x244 | old near miss, now solved |
| fn_801E2204.cpp | 0x220 | also holds a copy of fn_801E32C8 (already matched in fn_801E32C8.cpp), which is needed for the inline |
| fn_801E7A28.cpp | 0x198 | |
| fn_801E84FC.cpp | 0x184 | |
| fn_801DE6E0.cpp | 0x17C | |
| fn_801E733C.cpp | 0x154 | |
| fn_801E77E8.cpp | 0x150 | |
| fn_801F977C.cpp | 0x124 | |
| fn_801E7218.cpp | 0x124 | |
| fn_801F15A4.cpp | 0xE4 | |

## Near misses (in wip/r15a/)

| function | words | state |
|---|---|---|
| fn_801EA17C | 1 | Needs `lha` for `cur` with a kept `extsh` at the final compare. `u16 cur` gives the `extsh` but turns `lha` into `lhz`. |
| fn_80202344 | about 200 | The constructor and the loops are right. Blocked by the `mr r31,r28` zero idiom before the `fn_802044F4` loop. The frame is also 0x10 too big. |
| fn_802020AC | 17 | Only the `lbl_8038C1C0` constructor's -1/0x190 registers are wrong (the known dead end). |
| fn_801E2424 (and fn_801E2924) | about 100 | Hand-written levels get every register right, but the 17 stack slots come out in the wrong order (see below). |
| fn_801FE8BC family | 9 | Volatile registers around `(b - a) * 0x1c + y`. The file in wip/r15a was later changed by another session (there is also a `_codex` copy), so it isn't mine any more. |
| fn_80201110 | 9 | `fw` and `dy` swap (r25, r27). |
| fn_802007E4 | 18 | `w1` and `xr` swap (r29, r26). Use `int y2 = y + 0x1c`. |
| fn_801E7990 | 8 | Only `top`, `q` and `h` volatile registers are wrong. Same body as fn_801E84FC. |
| fn_801E1D0C | 7 | Only the `x88 = x44 > x40 - x42` flag's volatile registers are wrong. |

## Skipped

- Zero-idiom functions (`mr rZ,rI`) as asked: fn_801F9030, fn_801F8798, fn_801F2954, fn_801F4850, and the others listed in round 13. fn_80202344 turned out to be one of them.
- `lbl_8038C1C0` constructor users: fn_80205E50, fn_8020B408, fn_802020AC.
- The retry-loop family, the fn_801EBF00 family, and the fn_801DFF2C lazy-static family.
- fn_801E10E4: std::string with SSO; not attempted.

## Caveats on matches

- Struct, field, class and helper names are guesses. Virtual slots are declared with whatever signature that one caller needs.
- **fn_801F5A44 and fn_80202FF4:** the `isOk` / `act` inlines exist to give `id` the lower register. The original may have shaped this differently.
- **fn_80202FF4 and fn_801F99A0:** `getPr` (`Ps r = w->v48(); return r;`) and the doubled `setX2`/`mv2` nesting exist only to get the stack slot order.
- **fn_801F99A0 and fn_801F5A44:** `setI3` re-reads `h->x44` after storing it. That re-read is what keeps the dead store `x40 = 0` alive in the else path.
- **fn_801DD844:** the first test reads `((const Sl*)o)->x14`, so the decrement reloads the field (const and non-const reads are not CSE'd). The original probably had neither.
- **fn_801E9F38:** `x` is an `int` assigned through `gx()`, an accessor returning `int`, so that the late `extsh` is kept.
- **fn_801E7218:** the parameter is reassigned (`id = fn_80105328(...)`), so the index shares its register.
- **fn_801E733C:** the explicit `k += 0x28` offset exists for register rank.
- **fn_801E2204.cpp** redefines fn_801E32C8, which is also matched in fn_801E32C8.cpp. If both files are linked, one copy has to go.
- All declaration orders came from `sw.py`, `rr.py` or `tys.py` and say nothing about the source.

## Lessons not in MATCHING.md

- **List-cursor menu family:** `curVal(b)` (a v34 index, then a size test, then `adv(next, cur)`) plus `getPr` and the pad-button `if/else if` chain gave 4 matches worth 8.5 KB, all on the first or second compile. Check other regions for `cmpwi cr1,r4,0; blt cr1` advance blocks.
- **`std::advance` with `extsh rX,rN` before the 8x unroll:** the inline's count parameter is `int`, not `s16` (fn_801E7A28).
- **Self-recursion at the right depth:** `#pragma inline_depth(3)` around fn_801E2204 gave exactly 3 inlined levels, with the deepest `operator+` as real calls. Callers in other functions never inline it, whatever pragmas or `inline` are used. Hand-written levels are needed there, and even then the slot order differs.
- **Dead store kept on one path:** `h->x40 = 0; h->x44 = 0; h->x40 = 0;` in the else arm only comes from an inline setter that re-reads the field it just stored (`h->x44 = t; if (h->x44 == 0) h->x40 = 0;`).
- **Products become induction variables:** `s->x = x0 + c * cw` gives the kept `add r0,x0,iv` with `iv += cw`. Writing `xo += cw` by hand lets the compiler fold `x0` into the IV.
- **`int fh = call(); yy = ...; s16 d = (h - fh) >> 1;`:** computing the next value between a call and its use fixed the last volatile register in fn_801E84FC.
- **A free `r4` at a virtual call with no `mr r4`** means the function has a second parameter that it passes straight through (fn_801E1D0C, `o->v18(a)`).
- **`int m = w * k; x = m + base;`** gives the product-first `add`, where `k * w + base` puts the field first.
