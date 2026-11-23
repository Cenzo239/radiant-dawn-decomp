# Round 23 (agent r23a): equivalent to exact

Exact (new files in this folder; the equiv/ and wip/ files are left as they were):
- fn_80240814 (0x54) -> fn_80240814.cpp. Three steps: `const ListWin*` parameter (loads move between the prologue stores), the fields read into s16 locals in the order v20, top, cursor, and the row offset in an `int d` local with `p.y = d + y;` stored before `p.x` (operand order of the add). Same recipe fixed the rI POS family (fn_801ECF94 and three siblings).

Tried, still not exact:
- fn_80241BF0 (sched): `const void*` parameter (cast back inside) takes it from 51 to 25 words; what is left is the wfInit constant colouring shared with the rI fn_80205E50 family (see rI NOTES_round23_a.md). A real WF/WB class pair with constructors and `new WBc(...)` instead of the wbInit inline gives the same 25 words.
