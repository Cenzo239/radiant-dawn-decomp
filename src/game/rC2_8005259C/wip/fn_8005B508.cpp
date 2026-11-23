/* NEAR MISS: fn_8005B508 family (15 copies), 36 of 98 words here because the string base is a label; 25 with the real "" literal under pool_strings. Size now matches via the third argument of fn_801E5448 (b->a60). Only the registers of -1 and 0x190 are left: want 0x190 in r0, -1 in r5, 0 in r11. No effect at all (IR stays identical): int/s16/const-ref parameters, -1 and 0x190 as locals, inline results, computing 0x190 as 0x1C0-0x30, rect structs by value, returning this, local copies of vtables and floats, chained stores. Redundant if (w) guards around any run of stores: none help. rA fn_80023360 has the same ctor and is unmatched too (mnuAdd in rA is unused). */
/* The fn_8005B508 family: fifteen identical functions that add one screen object, then end the proc.
 * Constructor written as in rA_800068A0/fn_800235B8.cpp. The base's values arrive as s16 inline parameters,
 * and a60 is passed on as a third argument, which the old near miss lacked. */
#include "game/rC2_8005259C/wip/wb.h"
#pragma use_lmw_stmw on

#define ADD_ITEM_FN(name) \
    extern "C" void name(void* proc) { \
        wbAdd(proc); \
        fn_80083B78(proc); \
    }

ADD_ITEM_FN(fn_8005B508)
ADD_ITEM_FN(fn_8005B6E4)
ADD_ITEM_FN(fn_8005B8C0)
ADD_ITEM_FN(fn_8005BACC)
ADD_ITEM_FN(fn_8005BCD8)
ADD_ITEM_FN(fn_8005BEB4)
ADD_ITEM_FN(fn_8005C090)
ADD_ITEM_FN(fn_8005C26C)
ADD_ITEM_FN(fn_8005C448)
ADD_ITEM_FN(fn_8005C624)
ADD_ITEM_FN(fn_8005C800)
ADD_ITEM_FN(fn_8005C9DC)
ADD_ITEM_FN(fn_8005CBB0)
ADD_ITEM_FN(fn_8005CD8C)
ADD_ITEM_FN(fn_8005CF68)
