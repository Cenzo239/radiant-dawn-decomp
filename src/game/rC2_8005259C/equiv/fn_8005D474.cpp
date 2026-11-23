/* EQUIVALENT (sched, round 19b): fn_8005D474. Adds the same screen object as the fn_8005B508 family unless the command context byte +0xC is 0x81.
 * Moved instructions (checked with dd.py): the same three constant loads in the inlined sprite constructor as in equiv/fn_8005B508.cpp (copy of that constructor below). */
#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

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

static inline void sprAdd(void* proc) {
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
}

extern "C" void fn_80058094(void);
extern "C" void fn_8005D474(void* proc) {
    switch (((u8*)&lbl_803CA870)[0xc]) {
    case 0x81:
        fn_80083DC4(proc, 0x27);
        break;
    default:
        sprAdd(proc);
        fn_80058094();
        fn_80083B78(proc);
        break;
    }
}
