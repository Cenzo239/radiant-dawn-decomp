/* AI: best tile by counting units in range of a trap, fn_80154678. */
#include "game/rM_8014C9F8/ai.h"
#define ABS(a) ((a) < 0 ? -(a) : (a))
class TF {
public:
    virtual int check(Unit*);
    virtual int at(Unit*, s16, s16);
};
struct Vis { void* vt; void* arg; };
extern "C" {
extern u8 lbl_803CB770[];
extern u8 lbl_803E7320[];
extern u8 lbl_80386ED0[];
extern void* lbl_804CA510;
extern int fn_8011B77C(void*, void*);
extern int fn_801658E4(Unit*, int, int);
extern u16 fn_801676D8(int, int);
extern int fn_8016D11C(Unit*);
extern u8* fn_80066130(void*, int, int, int);
extern void* fn_80066D18(u8*);
extern u32* fn_801116B8(void*);
extern void fn_800CFB34(void*);
extern u8* fn_8010B204(int);
extern void fn_80117E30(Map*, int, int, int);
extern void fn_80039800(Vis*, int);
extern u8 lbl_80386EA0[];
extern int fn_8011EF78(Unit*);
extern void* fn_80065E10(void*);
extern void fn_801662AC(int, int, void*, int, int);
extern Unit* fn_800CFB0C(u8*);
extern u8 fn_8010E398(void*, void*);
extern u8* fn_800CFD18(void*, int);
extern int fn_80157548(Unit*, AiBest*, TF*);


static inline u32 IsFoeT(Unit* a, Unit* b) { return (u8)fn_8010E398(a->team, b->team) == 1; }
static inline int DirX(u8 d) {
    switch (d) {
    case 1:
        return -1;
    case 2:
        return 1;
    default:
        return 0;
    }
}
static inline int DirY(u8 d) {
    switch (d) {
    case 4:
        return 1;
    case 8:
        return -1;
    default:
        return 0;
    }
}
static inline u8* Tr(s16 x, s16 y) { return fn_80066130(lbl_803CB770, (s8)x, (s8)y, 10); }
static inline void Scan(Unit* u, void* arg, int x, int y, AiBest& cur, AiBest& best) {
    
    u8* t2;
    int k;
    s16 ox;
    int oy;
    int dy;
    int i;
    
    Vis v;
    t2 = Tr(x, y);
    v.vt = lbl_80386EA0;
    v.arg = arg;
    {
        int d = t2[3];
        int t0 = *(s8*)t2;
        oy = *(s8*)(t2 + 1);
        ox = t0 + DirX(d);
        dy = DirY(d);
    }
    fn_800CFB34(lbl_803E7320);
    fn_80114888(&lbl_803EC898, 7);
    fn_80114B44(&lbl_803EC898, 7, -1);
    fn_801662AC(ox, (s16)(oy + dy), fn_80065E10(t2), 7, 0xFF);
    fn_80039800(&v, 0);
    if (*(int*)lbl_803E7320) {
        cur.x = x;
        cur.y = y;
        cur.score = 0;
        for (i = 0; i < *(int*)lbl_803E7320; i++) {
            if (IsFoeT(u, fn_800CFB0C(fn_800CFD18(lbl_803E7320, i)))) {
                cur.score++;
            } else {
                cur.score--;
            }
        }
        if (cur.score > 0 && cur.score > best.score) {
            best = cur;
        }
    }
}

#pragma use_lmw_stmw on
u8 fn_80154678(void* arg, TF* f, int ac) {
    
    Unit* u;
    int ux;
    int rng;
    int x1;
    int y;
    int x;
    Map* m;
    s16 uy;
    int x0;
    int y1;
    
    AiBest cur;
    AiBest best;
    m = &lbl_803EC898;
    u = lbl_803CA870.unit;
    if (fn_8011EF78(u) == 0) {
        return lbl_804183F0.done;
    }
    fn_800453B4(&lbl_803CA870, ac);
    if ((lbl_804183F0.flags & 2) || (u->w3B4 & 0x7000000)) {
        fn_80114B44(m, 6, -1);
        fn_80114888(m, 6);
        m->cur[u->x + u->y * 0x40] = 0;
    } else {
        fn_80165F94(u, 6, -1);
    }
    memset(&cur, 0, 0x10);
    memset(&best, 0, 0x10);
    best.score = 0x80000000;
    best.t = NULL;
    uy = u->y;
    ux = u->x;
    rng = fn_8012408C(u);
    x0 = ux - rng;
    if (x0 < lbl_803EC898.x0) {
        x0 = lbl_803EC898.x0;
    }
    y = uy - rng;
    if (y < lbl_803EC898.y0) {
        y = lbl_803EC898.y0;
    }
    x1 = ux + rng;
    if (x1 > lbl_803EC898.x1 - 1) {
        x1 = lbl_803EC898.x1 - 1;
    }
    y1 = uy + rng;
    if (y1 > lbl_803EC898.y1 - 1) {
        y1 = lbl_803EC898.y1 - 1;
    }
    for (; y <= y1; y++) {
        for (x = x0; x <= x1; x++) {
            if (rng >= ABS(ux - x) + ABS(uy - y)) {
                if (((Map*)&lbl_803EC898)->costS[(s8)x + (s8)y * 0x40] >= 0 && ((Map*)&lbl_803EC898)->b5S[(s8)x + (s8)y * 0x40] == 0 && !fn_801658E4(u, (s8)x, (s8)y)) {
                    if (((Map*)&lbl_803EC898)->ter[0][(s8)x + (s8)y * 0x40] == 0) {
                        if (fn_80066130(lbl_803CB770, (s8)x, (s8)y, 10)) {
                            int cost = fn_801676D8((s8)x, (s8)y);
                            if (fn_8016D11C(u) >= cost && f->at(0, x, y)) {
                                Scan(u, arg, x, y, cur, best);
                            }
                        }
                    }
                }
            }
        }
    }
    if (best.score != 0x80000000) {
        u8 tx = best.x;
        u8 ty = best.y;
        u8 d = fn_80066130(lbl_803CB770, (s8)tx, (s8)ty, 10)[3];
        int ax = DirX(d);
        int ay = DirY(d);
        fn_80160610(lbl_803CA870.action, (s8)tx, (s8)ty, 0, (s8)(tx + ax), (s8)(ty + ay), -1, 0, 0);
        u->b3BC |= best.fl;
        u->h3BE = best.score;
    }
    return lbl_804183F0.done;
}
}
