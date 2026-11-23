/* Talk teardown (restart/close paths). */
#include "game/rL_80133EB4/talk.h"
#pragma auto_inline off
#pragma use_lmw_stmw on
extern "C" {
struct SB { u8 l : 1; u8 n : 7; };
static inline void F18(Talk* t) { if (t->x18) { fn_800D42A0(t->x18); t->x18 = 0; } }
static inline void F14(Talk* t) { if (t->x14) { fn_80081A90(t->x14); t->x14 = 0; } }
void fn_8014C64C(void) {
    Talk* t3;
    int i3;
    int i1;
    Talk* t1;
    void* p;
    Talk* t2;
    int i2;
    p = fn_80083B84(lbl_80386A98);
    if (p) {
    if (lbl_804181AC.proc) {
        {
            t1 = &lbl_804181AC;
            for (i1 = 0; i1 < 9; i1++, t1 = (Talk*)((u8*)t1 + 4)) {
                if (t1->x21c[0]) fn_80150C68(t1->x21c[0]);
                t1->x21c[0] = 0;
            }
        }
        {
            t2 = &lbl_804181AC;
            for (i2 = 0; i2 < 5; i2++, t2 = (Talk*)((u8*)t2 + 4)) {
                if (t2->actor[0]) fn_800C4240(t2->actor[0]);
                t2->actor[0] = 0;
            }
        }
        if (lbl_804CB880) fn_80006A2C(&lbl_804CB880);
        F18(&lbl_804181AC);
        F14(&lbl_804181AC);
        {
            Talk* t = &lbl_804181AC;
            if ((t->str0 >> 31) == 0) {
                ((u8*)&t->str0)[1] = 0;
                ((SB*)&t->str0)->n = 0;
            } else {
                *t->strp = 0;
                t->str1 = 0;
            }
        }
        lbl_804181AC.proc = 0;
        lbl_804181AC.cur = 0;
        fn_8014CFEC();
        if (lbl_804CB878 & 0x80) {
            fn_80068C08();
            lbl_804CB878 &= ~0x80;
        }
        lbl_804CB700 &= ~0x8002;
        fn_8014D364(&lbl_804CB878);
        {
            t3 = &lbl_804181AC;
            for (i3 = 0; i3 < 8; i3++, t3 = (Talk*)((u8*)t3 + 4)) {
                if (t3->x1c4[0]) fn_800DF6C8(t3->x1c4[0]);
            }
        }
    }

        fn_80081A90(p);
    }
}

void fn_8014C2AC(void* a) {
    int i1;
    Talk* t3;
    Talk* t;
    int i3;
    int i;
    Talk* t1;
    Talk* t2;
    int i2;
    void* p;
    const char* s;
    u32 n;
    if (lbl_804CB878 & 0x100) {
        p = fn_80083B84(lbl_80386A98);
        if (p) {
    if (lbl_804181AC.proc) {
        {
            t1 = &lbl_804181AC;
            for (i1 = 0; i1 < 9; i1++, t1 = (Talk*)((u8*)t1 + 4)) {
                if (t1->x21c[0]) fn_80150C68(t1->x21c[0]);
                t1->x21c[0] = 0;
            }
        }
        {
            t2 = &lbl_804181AC;
            for (i2 = 0; i2 < 5; i2++, t2 = (Talk*)((u8*)t2 + 4)) {
                if (t2->actor[0]) fn_800C4240(t2->actor[0]);
                t2->actor[0] = 0;
            }
        }
        if (lbl_804CB880) fn_80006A2C(&lbl_804CB880);
        F18(&lbl_804181AC);
        F14(&lbl_804181AC);
        {
            Talk* t = &lbl_804181AC;
            if ((t->str0 >> 31) == 0) {
                ((u8*)&t->str0)[1] = 0;
                ((SB*)&t->str0)->n = 0;
            } else {
                *t->strp = 0;
                t->str1 = 0;
            }
        }
        lbl_804181AC.proc = 0;
        lbl_804181AC.cur = 0;
        fn_8014CFEC();
        if (lbl_804CB878 & 0x80) {
            fn_80068C08();
            lbl_804CB878 &= ~0x80;
        }
        lbl_804CB700 &= ~0x8002;
        fn_8014D364(&lbl_804CB878);
        {
            t3 = &lbl_804181AC;
            for (i3 = 0; i3 < 8; i3++, t3 = (Talk*)((u8*)t3 + 4)) {
                if (t3->x1c4[0]) fn_800DF6C8(t3->x1c4[0]);
            }
        }
    }


            fn_80081A90(p);
        }
    }
    s = ((const char*(*)(void*))fn_800D0864)(a);
    fn_80083174(lbl_804181AC.proc);
    t = &lbl_804181AC;
    for (i = 0; i < 16; i++) t->x19c[i] = -1;
    if ((t->str0 >> 31) == 0) n = *(u8*)&t->str0 & 0x7F; else n = t->str1;
    fn_800250B0(&lbl_804181AC.str0, 0, n, s, s + strlen(s), Empty());
    lbl_804181AC.cur = (lbl_804181AC.str0 >> 31) == 0 ? (char*)&lbl_804181AC.str0 + 1 : lbl_804181AC.strp;
    lbl_804CB878 &= ~0x30;
    fn_80083DC4(lbl_804181AC.proc, 0);
    fn_8014D220(&lbl_804CB878);
    if (lbl_804CB700 & 1) {
        fn_8014B650(lbl_804181AC.proc);
    } else {
        u8* q = fn_800C3558();
        q[0x1C] = 1;
    }
}
}
