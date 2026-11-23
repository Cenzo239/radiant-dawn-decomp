#include "game/rL_80133EB4/talk.h"
#pragma auto_inline off
#pragma use_lmw_stmw on
extern "C" {
struct SB { u8 l : 1; u8 n : 7; };
static inline void F18(Talk* t) { if (t->x18) { fn_800D42A0(t->x18); t->x18 = 0; } }
static inline void F14(Talk* t) { if (t->x14) { fn_80081A90(t->x14); t->x14 = 0; } }
extern u8 lbl_80413F10[];
extern void fn_8014B244(Talk*);

struct TF { u32 f; u16 ctr; };
#define CUR (*(u8**)&lbl_804181AC.cur)
static inline BOOL IsSjisB(u8 c, const u8* p) {
    if ((c >= 0x81 && c <= 0x9F) || (c >= 0xE0 && c <= 0xFC)) {
        c = p[1];
        if ((c >= 0x40 && c <= 0x7E) || (c >= 0x80 && c <= 0xFC)) return 1;
    }
    return 0;
}
extern u8 lbl_80386B70[], lbl_80386B64[];
extern int fn_80149434(Talk*, char**);
#if TARGET_PC
extern FE10_PROTO struct Proc * fn_80085708(void*);
#else
extern int fn_80085708(void*);
#endif
extern int fn_801513E4(void*);
extern void fn_80151818(void*, void*);
extern void fn_80151CC4(void*, void*);
extern int fn_800CAB40(u8*);
extern void fn_8014EE28(void*, int);
extern void fn_80151360(void*, int);
extern void fn_8014EF58(void*);
static inline u8* CurP(Talk* t) {
    u8* r;
    if (t->x1e8) return (u8*)t->x21c[0];
    r = (u8*)t->x240;
    if (r == 0) r = (u8*)t->x21c[0];
    return r;
}
void fn_8014B650(void* proc) {
    /*P*/
    Talk* t1;
    Talk* t2;
    int i;
    int i3;
    Talk* t3;
    int i2;
    int i1;
    Talk* t;
    int n;
/*E*/
    u32 f;
    u32 a;
    while (a = *(volatile u32*)&lbl_804CB878, f = lbl_804CB878, !(a & 0x20)) {
    retry:
        { TF* f = (TF*)&lbl_804CB878; f->ctr = f->ctr + 1; }
        switch (fn_80149434(&lbl_804181AC, &lbl_804181AC.cur)) {
        case 2:
        case 0:
            continue;
        case 1:
            goto retry;
        case 4:
        default:
            break;
        }
        if (fn_80085708(lbl_80386B70) || fn_80085708(lbl_80386B64)) continue;
        if (fn_801513E4(CurP(&lbl_804181AC))) {
            fn_80151818(CurP(&lbl_804181AC), lbl_804181AC.proc);
            continue;
        }
        if (!(lbl_804CB700 & 3) && CurP(&lbl_804181AC)[0x80] == 0) {
            fn_80151CC4(CurP(&lbl_804181AC), lbl_804181AC.proc);
            continue;
        }
        fn_8014B244(&lbl_804181AC);
        {
            u8 c = *CUR;
            if ((s32)c == 0x23) {
                n = fn_800CAB40(CUR);
                for (i = 0; i < n; i++) {
                    fn_8014EE28(lbl_80413F10, (s8)*CUR);
                    fn_80151360(CurP(&lbl_804181AC), (s8)*CUR++);
                }
                goto retry;
            } else {
                if (!IsSjisB(c, CUR)) {
                    fn_80151360(CurP(&lbl_804181AC), (s8)c);
                    fn_8014EE28(lbl_80413F10, (s8)*CUR++);
                } else {
                    fn_80151360(CurP(&lbl_804181AC), (s8)c);
                    fn_8014EE28(lbl_80413F10, (s8)*CUR++);
                    fn_80151360(CurP(&lbl_804181AC), (s8)*CUR);
                    fn_8014EE28(lbl_80413F10, (s8)*CUR++);
                }
                *(u16*)&lbl_804181AC.x1ec = *(u16*)&lbl_804181AC.x1f0;
            }
        }
    }
    if (f & 0x10) {
        fn_80083DC4(proc, 3);
        return;
    }
    fn_8014EF58(lbl_80413F10);
    {
        a = *(volatile u32*)&lbl_804CB700;
        f = lbl_804CB700;
        if ((a & 2) && ((f & 0x8000) || lbl_804181AC.x1e9)) fn_800C900C(2, 0x85);
    }
    if (lbl_804CB700 & 3) {
        if (lbl_804181AC.x1e9) fn_800C835C(0, 0);
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
        fn_80081A90(proc);
    } else if (lbl_804181AC.x1e9) {
        fn_80083DC4(proc, 2);
    } else {
        fn_8014CF98();
        {
            Talk* q = &lbl_804181AC;
            int i;
            for (i = 0; i < 9; i++, q = (Talk*)((u8*)q + 4)) {
                if (q->x21c[0]) fn_80151D28(q->x21c[0], proc);
            }
        }
        {
            Talk* q = &lbl_804181AC;
            int i;
            for (i = 0; i < 5; i++, q = (Talk*)((u8*)q + 4)) {
                if (q->actor[0]) {
                    if (lbl_804CB700 & 3) {
                        fn_800C4240(q->actor[0]);
                    } else {
                        fn_800C71CC(q->actor[0], proc);
                    }
                    q->actor[0] = 0;
                }
            }
        }
        if (lbl_804181AC.x18) fn_800D3C90(fn_800D4228(lbl_804181AC.x18), (u8)(lbl_804181AC.x204 * 0x3C / 1000));
    }
}
}
