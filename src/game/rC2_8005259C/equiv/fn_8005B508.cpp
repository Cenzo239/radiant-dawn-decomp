/* EQUIVALENT (sched, round 19b): the fn_8005B508 family, fifteen identical functions (392 bytes each) that add one
 * screen object to a proc and then end the proc. Same instructions per basic block as the original; three constant
 * loads (li 0x190, li -1, the second vtable addi) are scheduled a slot apart because the temporaries get other
 * registers (checked with dd.py: only li/addi of constants move relative to independent stores).
 * Note: fn_801E5448 may take a third argument (see wip/wb.h); here the `li r5,0` of `p->f60 = 0` doubles as it. */
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

#define ADD_ITEM_FN(name) \
    extern "C" void name(void* proc) { \
        sprAdd(proc); \
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
