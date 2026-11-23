# Round 23 (agent r23a): equivalent to exact

Exact (new files in this folder; the equiv/ and wip/ files are left as they were):
- fn_8026806C (0x90) -> fn_8026806C.cpp. The `lha` above `stwu` came from the parameter: `const SlotMenu* m` (the round 22 lesson on const parameters moving the first field load).
- fn_8025F068 (0x30) -> fn_8025F068.cpp (alone; fn_8025F0E8 stays in equiv/fn_8025F068.cpp). Same const trick: `const u8* p` puts the `lbz` above the `lfd`.
- fn_80283528 (0x144) and fn_802836C0 (0x26C) -> fn_80283528.cpp. The setPos(c, y, d, x) arguments become `{ int y = c.m22; int x = c.m20; setPos(&c, y, d, x); }`: named locals in a block fix the load order of inline arguments (4 and 12 words).
- fn_80280F1C (0x2CC) -> fn_80280F1C.cpp. The equiv file declared fn_8017F68C float-first `(f32, f32, f32, f32, int)`; with the real `(int mode, f32 from, f32 to, f32 t, f32 d)` and the call written in that order (same registers, so not a behaviour bug), plus `o->m4C = k;` before `o->from = o->cur;` in go(), it is exact. symcheck flags only the fn_80295CF0/sqrt alias blocks (the equiv file had three more).
- fn_80263D18 (0xC8) and fn_80263DE0 (0x7C) -> fn_80263D18_x.cpp (fn_80263D18.cpp is an older file of this TU). Exhaustive grid of the five declarations x three initialisations (720 cells): `int ofs; int c; int n; int col; char* l;` gives the original's descending volatile registers in both line splitters; the earlier sw.py runs had stopped in a local minimum.
- fn_8026AB7C (0xA4) -> fn_8026AB7C.cpp. introFind's count and row offset become by-reference parameters declared in the caller (`int id; s16 n; int i; int ofs;`, grid over 72 declaration orders and types; `s16 n` was the last step, 15 -> 7 -> 0 words).

Tried, still not exact:
- fn_8025F0E8 (11 words, registers of the conversion temporaries): declaration orders, `f->t++`, a const parameter, direct field reads.
- fn_8027C5CC (2 words, count-1 value wants r27): cntm1() inline, no d2 local, block-scoped local, separate `n2--`.
- fn_802732FC (4 words, case 5 m42/row registers swapped): operand orders of the y sum, accessors M42()/M2C(), a RowT(j) inline.
- fn_80265574 (4 words, final text call x/y conversion registers): DrawA/DrawB wrappers, s16 and int locals. Note: the file declares fn_800CB3A8 as (int x, int y, int, int, int, f32, f32, fmt, ...); the definition is (f32 a, f32 b, int x, int y, int col, int k1, int k2, fmt, ...). Same registers, so no behaviour change, but the port should call it with the floats first; doing so still gives 4 words.
- fn_8026A864 (renamed, v and obj swap r30/r31): 480 declaration orders x types of v, four unitOf() spellings.
- fn_8026A9D4 (8 -> 5 words with the same by-reference introFind0R as fn_8026AB7C; id and n stay swapped r29/r30): 240 declaration orders x n type, id/n types, id by reference.
