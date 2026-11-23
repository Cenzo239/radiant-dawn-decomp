/* fn_80174CAC: near miss, 172 scorer lines; &lbl_803CA870 gets CSE'd into a saved register (orig rematerialises lis/addi at each call), and y/x1 swap. */
/* AI: pick the best-scoring tile in move range for a unit with no target (names guessed). */
#include "game/rQ_80163178/common.h"
#define ABS(a) ((a) < 0 ? -(a) : (a))
#define B116(u) (*((u8*)(u) + 0x116))
#define B3BB(u) (*((u8*)(u) + 0x3BB))
extern "C" {
void fn_80163010(AiCfg*, Unit*);
void* memset(void*, int, u32);
void fn_800453CC(AiAct*);
void fn_800453FC(AiAct*);
void fn_80171188(Unit*);
void fn_80166720(Unit*);
void fn_80165F94(Unit*, int, int);
s8 fn_8012408C(Unit*);
int fn_801658E4(Unit*, s8, s8);
int fn_8015804C(Unit*, int, int);
void fn_80160610(u8, int, int, Unit*, int, int, int, int, int);
void fn_8004559C(AiAct*, int);

u8 fn_80174CAC(void) {
    /*P*/
    int y1;
    int d;
    int v;
    Map* m;
    int best;
    int bx;
    int by;
    int ux;
    int uy;
    int rng;
    int x0;
    int y;
    int x1;
    Unit* u;
    int x;
/*E*/
    m = &lbl_803EC898;
    best = 0x80000000;
    u = lbl_803CA870.unit;
    u->m3D0[0] = 0x40;
    u->b3BC = 0;
    fn_80163010(&lbl_804183F0, u);
    lbl_804183F0.done = 0;
    memset(lbl_804183F0.res, 0, 0x14);
    fn_800453CC(&lbl_803CA870);
    fn_800453FC(&lbl_803CA870);
    fn_80171188(u);
    fn_80166720(u);
    v = *((u8*)&lbl_803CA870 + 0x15);
    d = v - fn_8012408C(u);
    B116(u) += d;
    B3BB(u) = d;
    fn_80165F94(u, 6, -1);
    ux = u->x;
    uy = u->y;
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
                    u8 t = m->ter[0][(s8)x + (s8)y * 0x40];
                    if (t == 0 || t == u->tid) {
                        int s = fn_8015804C(u, x, y);
                        if (s > best) {
                            best = s;
                            bx = x;
                            by = y;
                        }
                    }
                }
            }
        }
    }
    B116(u) -= d;
    B3BB(u) = 0;
    if (best > (int)0x80000000) {
        fn_80160610(1, (s8)bx, (s8)by, 0, (s8)bx, (s8)by, -1, 0, 0);
    } else {
        fn_8004559C(&lbl_803CA870, 0);
    }
    return lbl_804183F0.done;
}
}
