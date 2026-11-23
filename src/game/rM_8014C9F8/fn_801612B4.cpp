/* AI: lowest-HP target search by name, fn_801612B4 and fn_80161684. */
#include "game/rM_8014C9F8/ai.h"
#define ABS(a) ((a) < 0 ? -(a) : (a))
struct Cmd { int op, a, b, c, d; u32 fl; u32 x; const char* y; u32 z; };
extern "C" {
#if TARGET_PC
extern FE10_PROTO u8* fn_8010B228(p32arg);
#else
extern u8* fn_8010B228(u32);
#endif
extern u8 fn_801107B8(u8*, Unit*);
extern u8 fn_80110880(u8*, Unit*);
extern u8 fn_8010E398(void*, void*);
extern int fn_80291188(const char*, const char*);
extern int fn_8016D11C(Unit*);
extern s16 fn_801237EC(Unit*);
extern BOOL fn_801610E8(Unit*, Unit*, u32, u8, u8, s16*, s16*);


static inline u32 IsFoeT(Unit* a, Unit* b) { return (u8)fn_8010E398(a->team, b->team) == 1; }
int fn_801612B4(Unit* u, Cmd* c) {
    
    u8 mx;
    u8 mn;
    Unit* v;
    int bp;
    Unit* bv;
    int ux;
    int rng;
    int x1;
    int y;
    int x;
    u8* it;
    s16 bx;
    int uy;
    int x0;
    int y1;

    s16 ox, oy;
    s16 by;
    Map* m = &lbl_803EC898;
    if ((lbl_804183F0.flags & 2) || (u->w3B4 & 0x7000000)) {
        fn_80114B44(m, 6, -1);
        fn_80114888(m, 6);
        m->cur[u->x + u->y * 0x40] = 0;
    } else {
        fn_80165F94(u, 6, -1);
    }
    bp = 100;
    bv = 0;
    it = fn_8010B228(c->z);
    mn = fn_801107B8(it, u);
    mx = fn_80110880(it, u);
    uy = u->y;
    ux = u->x;
    rng = mx + fn_8012408C(u);
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
                int t = ((Map*)&lbl_803EC898)->ter[0][(s8)x + (s8)y * 0x40];
                if (t) {
                    v = UnitGet(t);
                    if (v != u) {
                        if ((lbl_804183F0.flags & 4) || !IsFoeT(u, v)) {
                            if (fn_80291188(*(const char**)v->person, c->y) == 0) {
                                if (fn_801610E8(u, v, (u16)fn_8016D11C(u), mn, mx, &ox, &oy)) {
                                    s16 mh = fn_801237EC(v);
                                    int pct = 100.0f * (f32)(s8)v->hp / (f32)mh;
                                    if ((u8)pct < 100 && (u8)pct <= (u8)bp) {
                                        bp = pct;
                                        bx = ox;
                                        by = oy;
                                        bv = v;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (bv) {
        fn_80160610(0x57, (s8)bx, (s8)by, bv, bv->x, (s8)*(u8*)&bv->y, -1, 0, 0);
    }
    return 0;
}
int fn_80161684(Unit* u, Cmd* c) {
    
    u8 mx;
    u8 mn;
    Unit* v;
    int bp;
    Unit* bv;
    int ux;
    int rng;
    int x1;
    int y;
    int x;
    u8* it;
    s16 bx;
    int uy;
    int x0;
    int y1;

    s16 ox, oy;
    s16 by;
    Map* m = &lbl_803EC898;
    if ((lbl_804183F0.flags & 2) || (u->w3B4 & 0x7000000)) {
        fn_80114B44(m, 6, -1);
        fn_80114888(m, 6);
        m->cur[u->x + u->y * 0x40] = 0;
    } else {
        fn_80165F94(u, 6, -1);
    }
    bp = 100;
    bv = 0;
    it = fn_8010B228(c->z);
    mn = fn_801107B8(it, u);
    mx = fn_80110880(it, u);
    uy = u->y;
    ux = u->x;
    rng = mx + fn_8012408C(u);
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
                int t = ((Map*)&lbl_803EC898)->ter[0][(s8)x + (s8)y * 0x40];
                if (t) {
                    v = UnitGet(t);
                    if (v != u) {
                        if ((lbl_804183F0.flags & 4) || !IsFoeT(u, v)) {
                            if (fn_80291188(*(const char**)v->person, c->y) == 0) {
                                if (fn_801610E8(u, v, (u16)fn_8016D11C(u), mn, mx, &ox, &oy)) {
                                    s16 mh = fn_801237EC(v);
                                    int pct = 100.0f * (f32)(s8)v->hp / (f32)mh;
                                    if ((u8)pct <= 50 && (u8)pct <= (u8)bp) {
                                        bp = pct;
                                        bx = ox;
                                        by = oy;
                                        bv = v;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (bv) {
        fn_80160610(0x58, (s8)bx, (s8)by, bv, bv->x, (s8)*(u8*)&bv->y, -1, 0, 0);
    }
    return 0;
}
}
