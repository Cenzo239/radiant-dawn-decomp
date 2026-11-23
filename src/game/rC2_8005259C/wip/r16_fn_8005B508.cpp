/* Round 16 one attempt: 36 words (from 52). Storing w->y0 before w->id = -1 in wfInit gives the original li order (0x190 in r0 before -1). Store order and the shared 0 for b->a60 / third argument remain. Size still 0x18C vs 0x188. */
/* NEAR MISS: fn_8005B508 family (15 copies), 36 of 98 words here because the string base is a label; 25 with the real "" literal under pool_strings. Size now matches via the third argument of fn_801E5448 (b->a60). Only the registers of -1 and 0x190 are left: want 0x190 in r0, -1 in r5, 0 in r11. No effect at all (IR stays identical): int/s16/const-ref parameters, -1 and 0x190 as locals, inline results, computing 0x190 as 0x1C0-0x30, rect structs by value, returning this, local copies of vtables and floats, chained stores. Redundant if (w) guards around any run of stores: none help. rA fn_80023360 has the same ctor and is unmatched too (mnuAdd in rA is unused). */
/* The fn_8005B508 family: fifteen identical functions that add one screen object, then end the proc.
 * Constructor written as in rA_800068A0/fn_800235B8.cpp. The base's values arrive as s16 inline parameters,
 * and a60 is passed on as a third argument, which the old near miss lacked. */
#ifndef RC2_WB_H
#define RC2_WB_H
/* Widget base (see rI_801DD7D4/fn_wf.h) and the 0x68-byte derived object made by the fn_8005B508 family.
 * Standalone from decls.h, whose fn_801E5448 prototype has only two parameters. */
#include "game/rC2_8005259C/types.h"
extern "C" {
extern char lbl_8038CB1C[];
extern char lbl_8038C1C0[];
extern char lbl_80361F9C[];
void* fn_80079150(u32);
void fn_801E5448(void*, void*, int);
void* fn_801E5640(void*, int, int);
void fn_80083B78(void*);
}
struct WF {
    void* vt; int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1;
    s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26, a28; f32 sx, sy, sz; u32 flags; void* a3c;
};
struct WB { WF w; int a40, a44, a48, a4c; u8 a50; f32 a54; s16 a58, a5a, a5c, a5e; int a60; const char* a64; };
static inline void wfInit(WF* w, s16 x0, s16 y0, s16 x1, s16 y1, s16 ix1, s16 iy1, s16 a26, int fl) {
    w->rc = 0;
    w->vt = lbl_8038CB1C;
    w->y0 = y0;
    w->id = -1;
    w->x0 = x0; w->x1 = x1; w->y1 = y1;
    w->ix0 = 0; w->iy0 = 0; w->ix1 = ix1; w->iy1 = iy1;
    w->a1a = 0; w->a1c = 0; w->tx = 0; w->ty = 0;
    w->c[0] = 0xff; w->c[1] = 0xff; w->c[2] = 0xff; w->c[3] = 0xff;
    w->a26 = a26; w->a28 = 0;
    w->sx = 1.0f; w->sy = 1.0f; w->sz = 1.0f;
    w->flags = fl; w->a3c = 0;
}
static inline void wbInit(WB* b, s16 x0, s16 y0, s16 x1, s16 y1, s16 ix1, s16 iy1, s16 a26, int fl) {
    wfInit(&b->w, x0, y0, x1, y1, ix1, iy1, a26, fl);
    b->a40 = 0; b->a44 = 0; b->a48 = 0; b->a4c = 0;
    b->a50 = 1;
    b->a5a = 0; b->a5e = 0;
    b->w.vt = lbl_8038C1C0;
    b->a60 = 0; b->a64 = 0;
    b->a58 = iy1; b->a5c = iy1;
    b->a54 = 0.75f;
}
static inline void wbAdd(void* p) {
    WB* b = (WB*)fn_80079150(0x68);
    WB* x;
    if (b != 0) {
        wbInit(b, 0, 0x190, 0x260, 0x1C0, 0x260, 0x30, 0x316, 0x10);
    }
    b->w.id = -0x1000;
    b->a4c = 1;
    b->a64 = lbl_80361F9C + 0x6f;
    b->w.flags |= 0x10;
    b->a60 = 0;
    b->w.a28 = 8;
    fn_801E5448(p, b, b->a60);
    x = (WB*)fn_801E5640(p, -0x1000, 0);
    if (x != 0) {
        x->a60 = 1;
    }
}
#endif

#pragma use_lmw_stmw on

#define ADD_ITEM_FN(name) \
    extern "C" void name(void* proc) { \
        wbAdd(proc); \
        fn_80083B78(proc); \
    }

ADD_ITEM_FN(fn_8005B508)
