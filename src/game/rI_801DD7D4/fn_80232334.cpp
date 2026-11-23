/* WIP (round 19): class `other`, 60 of 61 instructions, complete and believed correct. Left: the
   original keeps the count in r5 and copies it (`mr r4,r5`) for fn_8021B14C because its "nothing left"
   flag lives in r4; ours puts the flag in r5 and the count straight into r4. */
/* fn_80232334: advances a 4-step reveal sequence to the next step that has something to show
   (steps 0..2 animate a row of the stat panel, step 3 the map preview); deletes the process when no
   step is left. */
#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
void fn_8021A47C(void*, int, int);
void fn_8021B14C(void*, int);
void fn_80253EE4(const char*, f32);
void fn_80083DC4(void*, int);
extern char lbl_80390AE8[];
}
struct Ct { u8 p[0x30]; s8 a30; u8 a31, a32, a33, a34; u8 p35[3]; void* a38; void* a3c; };
static inline u8 cnt(Ct* o, int i) {
    u8 v = 0;
    switch (i) {
    case 0: v = o->a31; break;
    case 1: v = o->a32; break;
    case 2: v = o->a33; break;
    case 3: v = o->a34; break;
    }
    return v;
}
extern "C" void fn_80232334(Ct* o) {
    BOOL done = TRUE;
    int i;
    for (i = o->a30; i < 4; i++) {
        s8 n = cnt(o, i);
        if (n > 0) {
            o->a30 = i + 1;
            if (i != 3) {
                fn_8021A47C(o->a38, (u8)i, n);
            } else {
                fn_8021B14C(o->a3c, n);
            }
            fn_80253EE4(lbl_80390AE8, 0.0f);
            done = FALSE;
            break;
        }
    }
    if (done) fn_80083DC4(o, 1);
}
