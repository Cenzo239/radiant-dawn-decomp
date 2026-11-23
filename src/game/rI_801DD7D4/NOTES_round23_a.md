# Round 23 (agent r23a): equivalent to exact

Exact (new files in this folder; the equiv/ files are left as they were):
- fn_80201110 (0x21C) -> fn_80201110.cpp. `dy` and `fw` declared `s16` instead of `int` (both only feed s16 sums); found by a type grid over the /*P*/ block after declaration orders had been exhausted in earlier rounds.
- fn_801E31D4 (0xF4) -> fn_801E31D4.cpp and fn_801E5640 (0xF4) -> fn_801E5640.cpp. The parameter is `const W* wc` with `W* w = (W*)wc;` as the first statement: the `lwz r31,0x48(r3)` list load moves up between the prologue saves (7 words each, "reverse iterator" puzzle of rounds 13-20).
- fn_801ECF94, fn_801EDF9C, fn_801EEFA4, fn_801FE8BC (0x7C each) -> fn_801ECF94.cpp (the POS macro). const LV* parameter fixes the load order (11 -> 5 words), ty/cu/tp s16 locals assigned in the order ty, tp, cu fix the registers (-> 1), and `int d = (s16)(cu - tp) * 0x1c; in.y = d + ty; in.x = o->tx;` (int local for the row offset, y stored before x) gives `add r0,r0,r6`; through setP every operand order gives `add r0,r6,r0`. Same shape as rS fn_80240814.

- fn_8022A7CC (0xB0) -> fn_8022A7CC.cpp. `const GD* o` parameter (field load scheduled between the prologue saves).

Tried, still not exact:
- fn_802225E8 (2 words, `mr r5,r4` vs `li r6,0`): nth with s16/int/const parameters, casts of n at the call.
- fn_8023DC38 (2 words): not retried beyond reading (earlier rounds: store order of the volatile flags).
- fn_80205E50 family (fn_801F17C4, fn_802020AC, fn_8020B408, fn_80213B4C, fn_8021F5C4, fn_80221050, fn_8022516C, fn_8022DFE0, rS fn_80241BF0, rF fn_801D2744: 25 words each, the zero/-1/400 constants of the inlined wfInit get r12/r0/r11, original r11/r5/r0). A local wfInit copy: s16/int for each of the 7 parameters (128 cells, no change), the first four statements in all orders (only orders that move the rc store change the colours). Not solved; one fix would close eleven functions.
