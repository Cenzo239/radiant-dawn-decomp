/* Near misses for region rC2_8005259C. Not part of the matched build.
 * Each block says how close it got; compile against ../decls.h. */
#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

/* fn_8005B508 and 14 copies with the same instructions (B6E4, B8C0, BACC, BCD8, BEB4, C090, C26C, C448, C624,
 * C800, C9DC, CBB0, CD8C, CF68): 25 of 98 words off. Only the temporaries' registers differ:
 * the original loads 0x190 into r0, -1 into r5 and 0 into r11; ours uses -1 in r0, 0x190 in r11, 0 in r12.
 * fn_8005D474 inlines the same constructor and has the same problem.
 * Stores come out in source order, so their order is fixed. These make no difference (all still 25 words):
 * base/derived inline nesting, real C++ classes with inline constructors and operator new, inline helpers with
 * constant parameters (int or s16) over any run of fields, helpers writing through a struct at &p->fN (every range),
 * and a neighbouring function before it in the file. Moving one store does flip the registers (swapping fa and fc,
 * or moving f50 after the second vtable store, gives r5 for -1 and r0 for 0x190), but then the store order is wrong. */
static inline void sprBaseInit(Spr* p) {
        p->f4 = 0;
        p->vt = lbl_8038CB1C;
        p->f8 = -1;
        p->fa = 0;
        p->fc = 0x190;
        p->fe = 0x260;
        p->f10 = 0x1c0;
        p->f12 = 0;
        p->f14 = 0;
        p->f16 = 0x260;
        p->f18 = 0x30;
        p->f1a = 0;
        p->f1c = 0;
        p->f1e = 0;
        p->f20 = 0;
        p->f22 = 0xff;
        p->f23 = 0xff;
        p->f24 = 0xff;
        p->f25 = 0xff;
        p->f26 = 0x316;
        p->f28 = 0;
        p->f2c = 1.0f;
        p->f30 = 1.0f;
        p->f34 = 1.0f;
        p->f38 = 0x10;
        p->f3c = 0;
        p->f40 = 0;
        p->f44 = 0;
        p->f48 = 0;
        p->f4c = 0;
        p->f50 = 1;
        p->f5a = 0;
        p->f5e = 0;
}
static inline void sprInit(Spr* p) {
        sprBaseInit(p);
        p->vt = lbl_8038C1C0;
        p->f60 = 0;
        p->f64 = 0;
        p->f58 = 0x30;
        p->f5c = 0x30;
        p->f54 = 0.75f;
}
static inline Spr* newSpr(void) {
    Spr* p = (Spr*)fn_80079150(0x68);
    if (p) {
        sprInit(p);
    }
    return p;
}

extern "C" void fn_8005B508(void* proc) {
    Spr* p = newSpr();
    Spr* q;
    p->f8 = -0x1000;
    p->f4c = 1;
    p->f64 = lbl_80361F9C + 0x6f;
    p->f38 |= 0x10;
    p->f60 = 0;
    p->f28 = 8;
    fn_801E5448(proc, p);
    q = fn_801E5640(proc, -0x1000, 0);
    if (q) {
        q->f60 = 1;
    }
    fn_80083B78(proc);
}

/* fn_8005260C: 38 words and one instruction too long. The original materialises &lbl_803CAB38 before the 0x33 test (same issue as rC fn_80051FF4), which shifts most of the diff. */
extern "C" void fn_8005260C(Cmd0* c) {
    u8* q;
    GameData* g = &lbl_803CAB38;
    u32 k = 3;
    if (lbl_804CB3F8 == 0x33) {
        k = 0;
    }
    q = (u8*)fn_80062A9C(g, k);
    if (q) {
        u8 b = q[4];
        if (b == (u8)c->v58()) {
            int n = 6;
            Color4 col;
            if (lbl_804CB3F8 == 0x33) {
                n = 7;
            }
            col = *fn_800CD204(n);
            fn_80080508(&col);
        }
    }
}

