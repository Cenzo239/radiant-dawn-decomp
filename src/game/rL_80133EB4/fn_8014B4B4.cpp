#include "game/rL_80133EB4/talk.h"
#pragma auto_inline off
extern "C" {
static inline void B4(Talk* t) {
    t->x1f2 = 2;
    if (fn_800C7FE8() & 4) {
        t->x1f2 = 2;
    } else if (fn_800C7FE8() & 8) {
        t->x1f2 = 5;
    } else {
        if (!(lbl_804CB878 & 0x80)) t->x1f2 = 0;
        fn_800C835C(3, lbl_804181AC.x204);
    }
}
void fn_8014B4B4(void) { B4(&lbl_804181AC); }
static inline void Adv(Talk* t) { lbl_804CB878 &= ~0x30; t->cur = t->cur + 2; }
static inline void Adv2(Talk* t) { char* c = t->cur; lbl_804CB878 &= ~0x30; t->cur = c + 2; }
void fn_8014C59C(void) {
    if (lbl_804181AC.proc == 0 || fn_80083B84(lbl_80386A98) == 0) return;
    fn_8014D350(&lbl_804CB878);
    fn_80083174(lbl_804181AC.proc);
    {
        Talk* t = &lbl_804181AC;
        t->cur += 2; lbl_804CB878 &= ~0x30;
        fn_80083DC4(lbl_804181AC.proc, 0);
    }
    fn_8014D220(&lbl_804CB878);
    if (lbl_804CB700 & 1) {
        fn_8014B650(lbl_804181AC.proc);
    } else {
        u8* q = fn_800C3558();
        q[0x1C] = 1;
    }
}
void fn_8014C8AC(PT* p) {
/*P*/
    Talk* q1;
    Talk* t;
    Talk* q2;
    int i1;
    int i2;
/*E*/
    t = p->t;
    if (t->x1e9 != 0 || (lbl_804CB878 & 0x8000)) {
        fn_800C900C(3, 0x85);
        fn_80083B78(p);
    } else {
        {
            q1=t;
            for (i1 = 0; i1 < 5; i1++, q1=(Talk*)((u8*)q1+4)) {
                if (q1->actor[0]) fn_800C7114(q1->actor[0], p);
            }
        }
        {
            q2=t;
            for (i2 = 0; i2 < 9; i2++, q2=(Talk*)((u8*)q2+4)) {
                if (q2->x21c[0]) fn_80151D28(q2->x21c[0], p);
            }
        }
        fn_8014CF98();
        if (t->x18) fn_800D3C90(fn_800D4228(t->x18), 8);
        fn_80083B78(p);
    }
}

}
