/* AI: walk to a trap target from a list or the move range, fn_80154C44. */
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

extern u8 lbl_80386EA0[];
extern int fn_8011EF78(Unit*);
extern void* fn_80065E10(void*);
extern void fn_801662AC(int, int, void*, int, int);
extern Unit* fn_800CFB0C(u8*);
extern u8 fn_8010E398(void*, void*);
extern u8* fn_800CFD18(void*, int);
extern int fn_80157548(Unit*, AiBest*, TF*);


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


static inline void Ls(s16* list, Unit* u, Map* m, int& best, int& bx, int& by, int& py, int& cost) {
    
    s16 px;

    for (; (px = list[0]) >= 0; list += 2) {
        py = list[1];
        if (fn_80066130(lbl_803CB770, (s8)px, (s8)py, 10)) {
            if (((Map*)&lbl_803EC898)->costS[(s8)px + (s8)py * 0x40] >= 0) {
                if (fn_8016D11C(u) >= (int)fn_801676D8((s8)px, (s8)py)) {
                    bx = (s8)px;
                    by = (s8)py;
                    best = (s16)m->cur[(s8)px + (s8)py * 0x40];
                    break;
                }
            }
        }
    }
}
static inline void Sq(Unit* u, Map* m, int& best, int& bx, int& by, int& ux, int& rng, int& x1, int& y, int& x) {
    
    int y1;
    int x0;
    s16 uy;

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
                            if (fn_8016D11C(u) >= cost) {
                                if (((Map*)&lbl_803EC898)->costS[(s8)x + (s8)y * 0x40] < best) {
                                    bx = (s8)x;
                                    by = (s8)y;
                                    best = (s16)m->cur[(s8)x + (s8)y * 0x40];
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
#pragma use_lmw_stmw on
u8 fn_80154C44(s16* list, int act) {
    
    Map* m;
    int cost;
    int bx;
    int best;
    int by;
    int ux;
    int rng;
    int x1;
    int y;
    int x;
    Unit* u;
    int py;

    m = &lbl_803EC898;
    u = lbl_803CA870.unit;
    if (fn_8011EF78(u) == 0) {
        return lbl_804183F0.done;
    }
    fn_800453B4(&lbl_803CA870, act);
    if ((lbl_804183F0.flags & 2) || (u->w3B4 & 0x7000000)) {
        fn_80114B44(m, 6, -1);
        fn_80114888(m, 6);
        m->cur[u->x + u->y * 0x40] = 0;
    } else {
        fn_80165F94(u, 6, -1);
    }
    best = 0x7FFF;
    if (list) {
        Ls(list, u, m, best, bx, by, py, cost);
    } else {
        Sq(u, m, best, bx, by, ux, rng, x1, y, x);
    }
    if (best != 0x7FFF) {
        u8 d = fn_80066130(lbl_803CB770, (s8)bx, (s8)by, 10)[3];
        int ax = DirX(d);
        int ay = DirY(d);
        fn_80160610(lbl_803CA870.action, (s8)bx, (s8)by, 0, (s8)(bx + ax), (s8)(by + ay), -1, 0, 0);
    }
    return lbl_804183F0.done;
}
}
