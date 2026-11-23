/* EQUIVALENT (sched, round 19b): fn_80114D00. Moved instructions (checked with dd.py): two independent byte loads (0x102/0x103) and their extsb/slwi/add are in another order. From wip/r10_fn_80114D00.cpp. */
/* NOT MATCHING, not compiled. fn_80114D00: 47 words of colouring around the third and second loops; the diamond loop is solved by the ABS macro. */
#include "game/rH_80112B48/unit.h"
#include "game/rH_80112B48/map.h"
#pragma auto_inline off
extern "C" {
extern u8 lbl_804CB830;
extern u32 lbl_804CA4C8;
extern u8 lbl_803CAB38[];
extern void fn_80114B44(Map*, int, int);
extern void fn_80066C48(void);
extern void* memset(void*, int, u32);
extern s8 fn_801241F4(Unit*);
extern void fn_80117A84(Map*);
static inline void SideSet(u8* tbl, const u8* a) {
    for (; *a != 0xff; a++) {
        tbl[*a] = 1;
    }
}
#pragma use_lmw_stmw on
#define ABS(a) ((a) < 0 ? -(a) : (a))
static inline void Rng(Map* m, s8 cx, s8 cy, s8 r) {
    int y; int x;
    for (y = 0; (s8)y < m->h; y++) {
        for (x = 0; (s8)x < m->w; x++) {
            if (ABS((s8)x - cx) + ABS((s8)y - cy) <= r) {
                m->ter[2][x + (y << 6)] = 1;
            }
        }
    }
}
static inline Map* QQ(Map* m, s8 x, s8 y) { return (Map*)((u8*)m + x + y * 0x40); }
void fn_80114D00(Map* m) {
    /*P*/
    Unit* v2;
    int i2;
    int i3;
    Map* q2;
    Map* q3;
    u64 fa;
    u64 fb;
    u64 fc;
    Unit* v3;
    BOOL ok;
    Unit* v;
    int i;
    int j;
/*E*/
    ok = 1;
    if (lbl_804CB830 != 1 && lbl_804CB830 != 2) ok = 0;
    fn_80114B44(m, 0, 0);
    fn_80114B44(m, 3, 0);
    fn_80114B44(m, 4, 0);
    if (ok) {
        fn_80114B44(m, 2, 0);
    } else {
        fn_80114B44(m, 2, -1);
    }
    fn_80066C48();
    {
        u8 a[] = {0, 2, 3, 0xff};
        u8 tbl[0xb];
        memset(tbl, (u8)lbl_804CA4C8, 0xb);
        SideSet(tbl, a);
        for (i = 0xfe; i >= 1; i--) {
            { int z = (u8)i; if (z) v = &lbl_804CB810[z - 1]; else v = 0; }
            if (v->person && tbl[v->team[8]] && !(v->flags10C & 0x10000dc)) {
                m->ter[0][v->x + v->y * 0x40] = v->padFC;
                if (ok && !(v->flags108 & 0x40)) {
                    Rng(m, v->x, v->y, fn_801241F4(v));
                }
            }
        }
    }
    if (lbl_803CAB38[0x11] != 1) {
        u8 a[] = {1, 0xff};
        u8 tbl[0xb];
        memset(tbl, (u8)lbl_804CA4C8, 0xb);
        SideSet(tbl, a);
        for (i2 = 0xfe; i2 >= 1; i2--) {
            { int z = (u8)i2; if (z) v2 = &lbl_804CB810[z - 1]; else v2 = 0; }
            if (v2->person && tbl[v2->team[8]] && !(v2->flags10C & 0x100009c)) {
                q2 = (Map*)(((u8*)m + v2->x) + v2->y * 0x40);
                if (q2->ter[2][0] != 0) {
                    q2->ter[0][0] = v2->padFC;
                    fa = v2->flags;
                    if (fa & 0x40) {
                        v2->flags = (fa & ~(u64)0x40) | 0x200;
                    }
                } else {
                    q2->ter[3][0] |= 1;
                    fb = v2->flags;
                    if (!(fb & 0x40)) {
                        v2->flags = fb | 0x240;
                    }
                }
            }
        }
    } else {
        u8 a[] = {1, 0xff};
        u8 tbl[0xb];
        memset(tbl, (u8)lbl_804CA4C8, 0xb);
        SideSet(tbl, a);
        for (i3 = 0xfe; i3 >= 1; i3--) {
            { int z = (u8)i3; if (z) v3 = &lbl_804CB810[z - 1]; else v3 = 0; }
            if (v3->person && tbl[v3->team[8]]) {
                fc = v3->flags;
                if (!(fc & 4)) {
                    q3 = (Map*)((u8*)m + v3->x + v3->y * 0x40);
                    if (q3->ter[2][0] != 0) {
                        v3->flags = fc & ~(u64)0x40;
                    } else {
                        v3->flags = fc | 0x40;
                    }
                    m->ter[0][v3->x + v3->y * 0x40] = v3->padFC;
                }
            }
        }
    }
    fn_80117A84(m);
}
}