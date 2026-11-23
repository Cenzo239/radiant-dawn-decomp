/* fn_80148D44: functionally equal (regs level per tools/check_regs.py; registers differ from the original). Talk per-frame step. From wip/near3.cpp with the counter increment through a block-local pointer (fixes the hoist order). */
/* ===== fn_80148D44: 12 words: li r28 must be hoisted last, and t must take r23/r24 ===== */
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
extern int fn_80085708(void*);
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

struct SF { u32 a : 3; u32 b : 2; u32 c : 21; u32 d : 1; u32 e : 5; };
extern u8 lbl_803CAB38[];
extern u8 lbl_80386B30[];
extern u8 lbl_80386C3C[], lbl_80386C4C[], lbl_80386C5C[], lbl_80386C6C[];
extern u32 lbl_804CA738;
extern u32 fn_80331194(void);
extern SF* fn_80060728(void*);
extern int fn_800C7F90(void);
extern int fn_80148634(void);
extern void fn_8014D220(u32*);
extern u8* fn_80081194(void*, void*);
extern void fn_80253EE4(void*, f32);
extern void fn_800C642C(void*);
extern void fn_800C63F0(void*, int);
#define U1EC (*(u16*)&t->x1ec)
#define U1EE (*(u16*)&t->x1ee)
#define U1F0 (*(u16*)&t->x1f0)
static inline void Inc() { ((TF*)&lbl_804CB878)->ctr = ((TF*)&lbl_804CB878)->ctr + 1; }
static inline void Inc3(TF* f) { f->ctr = f->ctr + 1; }
static inline int Step(void) {
    int n;
    int i;
retry:
    { TF* f = (TF*)&lbl_804CB878; f->ctr = f->ctr + 1; }
    switch (fn_80149434(&lbl_804181AC, &lbl_804181AC.cur)) {
    case 0:
        return 0;
    case 2:
        return 2;
    case 1:
        goto retry;
    case 4:
    default:
        break;
    }
    if (fn_80085708(lbl_80386B70) || fn_80085708(lbl_80386B64)) return 2;
    if (fn_801513E4(CurP(&lbl_804181AC))) {
        fn_80151818(CurP(&lbl_804181AC), lbl_804181AC.proc);
        return 2;
    }
    if (!(lbl_804CB700 & 3) && CurP(&lbl_804181AC)[0x80] == 0) {
        fn_80151CC4(CurP(&lbl_804181AC), lbl_804181AC.proc);
        return 2;
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
    return 3;
}
static inline u8* CurActor(Talk* t) {
    int c = t->cur200;
    if (c < 0) return 0;
    c = t->x19c[c];
    if (c < 0) return 0;
    return t->actor[c];
}
static inline void Run(int limit) {
    int i;
    for (i = 0; i < limit; i++) {
        int r = Step();
        if (r == 0) {
            fn_80083B78(lbl_804181AC.proc);
            break;
        }
        if (r != 3) break;
    }
}
void fn_80148D44(void) {
/*P*/
    int limit;
    Talk* t1;
    Talk* t2;
    Talk* t3;
/*E*/
    fn_8014D220(&lbl_804CB878);
    t1 = &lbl_804181AC;
    if (t1->x1ea) {
        if (fn_800C7F90()) return;
        t1->x1ea = 0;
    }
    {
        Talk* t = &lbl_804181AC;
        if (t->x1e9 && fn_800C7F90()) return;
    }
    {
        Talk* t = &lbl_804181AC;
        u32 a = *(volatile u32*)&lbl_804CB878;
        u32 f = lbl_804CB878;
        t->x1f4--;
        if (a & 0x20000) {
            limit = 0xFFFF;
        } else if (f & 0x40000) {
            limit = 1;
        } else {
            SF* q = fn_80060728(lbl_803CAB38);
            limit = 1;
            if (q->b == 3) limit = 0xFFFF;
        }
    }
    if ((lbl_804CB878 & 4) && !(lbl_804CB700 & 3)) {
        u8* r = fn_80081194(lbl_80386B30, lbl_804181AC.proc);
        *(Talk**)(r + 0x30) = &lbl_804181AC;
        *(int*)(r + 0x34) = 0;
        return;
    }
    if (fn_80148634()) {
        Talk* t = &lbl_804181AC;
        int z = 0;
        limit = 0xFFFF;
        t->x1f4 = z;
    }
    if (lbl_804CB700 & 3) {
        fn_80083B78(lbl_804181AC.proc);
        return;
    }
    {
        Talk* t = &lbl_804181AC;
        if (t->x1f4 != 0) return;
    }
    {
        int d;
        if (lbl_804CB878 & 0x40000) {
            d = 6;
        } else {
            switch (fn_80060728(lbl_803CAB38)->b) {
            case 0: d = 10; break;
            case 1: d = 4; break;
            case 2: d = 1; break;
            case 3: d = 1; break;
            default: d = 4; break;
            }
        }
        lbl_804181AC.x1f4 = d;
    }
    Run(limit);
    {
#define t t2
        t2 = &lbl_804181AC;
        if (U1EC == 0 && !(lbl_804CB878 & 0x10000) && lbl_804CA738 != fn_80331194() - 1) {
            lbl_804CA738 = fn_80331194();
            if (fn_80060728(lbl_803CAB38)->d == 0) {
                switch (t->x1f3) {
                case 0: break;
                case 1: fn_80253EE4(lbl_80386C6C, 0.0f); break;
                case 2: fn_80253EE4(lbl_80386C5C, 0.0f); break;
                case 3: fn_80253EE4(lbl_80386C4C, 0.0f); break;
                case 4: fn_80253EE4(lbl_80386C3C, 0.0f); break;
                }
            }
        }
#undef t
    }
    {
        u8* a = CurActor(&lbl_804181AC);
        if (a) {
            Talk* t = &lbl_804181AC;
            u16 c = U1EC;
            if (c != U1EE) {
                switch (c) {
                case 0: fn_800C642C(a); break;
                case 0x20: fn_800C642C(a); fn_800C63F0(a, 0x20); break;
                case 8: fn_800C642C(a); fn_800C63F0(a, 8); break;
                }
            }
        }
    }
    {
        Talk* t = &lbl_804181AC;
        U1EE = U1EC;
    }
}
}

