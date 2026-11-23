/* AI: set the chosen action (fn_80160508, fn_80160610) and best tile search fn_801610E8. */
#include "game/rM_8014C9F8/ai.h"
struct Act2 {
    Unit* unit;  /* 0x00 */
    Unit* t;     /* 0x04 */
    u8 pad8[6];
    u8 itm;      /* 0x0E */
    u8 padF[2];
    s8 x;        /* 0x11 */
    s8 y;        /* 0x12 */
    s8 tx;       /* 0x13 */
    s8 ty;       /* 0x14 */
    u8 pad15[3];
    int a;       /* 0x18 */
    int b;       /* 0x1C */
};
extern "C" {
extern u8 fn_80172664(Unit*, s8*, s8*);
extern int fn_801658E4(Unit*, int, int);
extern u16 fn_801676D8(int, int);
extern int fn_8015814C(Unit*, int, int, int);
extern int fn_80158208(Unit*, int, int, int);

#pragma use_lmw_stmw on
static inline void Tail(Act2* p, u8 fl, s8& x, s8& y) {
    if (fl & 1) {
        fn_800453B4((AiAct*)p, 0x25);
        p->y = y;
        p->x = x;
        lbl_804183F0.res[4] = 0xC;
    } else if (fl & 2) {
        fn_800453B4((AiAct*)p, 0x2E);
        p->y = y;
        p->x = x;
        lbl_804183F0.res[4] = 0xD;
    }
}
void fn_80160508(u8 act, Unit* t, int tx, int ty, int itm, int a, int b) {
    s8 x, y;
    Act2* p = (Act2*)&lbl_803CA870;
    fn_800453B4((AiAct*)p, act);
    p->t = t;
    p->tx = tx;
    p->ty = ty;
    p->itm = itm;
    p->a = a;
    p->b = b;
    lbl_804183F0.res[4] = 0;
    {
        Unit* u = lbl_803CA870.unit;
        x = u->x;
        y = u->y;
        Tail(p, fn_80172664(u, &x, &y), x, y);
    }
    lbl_804183F0.done = 1;
}
void fn_80160610(u8 act, int mx, int my, Unit* t, int tx, int ty, int itm, int a, int b) {
    s8 x, y;
    Act2* p = (Act2*)&lbl_803CA870;
    fn_800453B4((AiAct*)p, act);
    p->x = mx;
    p->y = my;
    p->t = t;
    p->tx = tx;
    p->ty = ty;
    p->itm = itm;
    p->a = a;
    p->b = b;
    lbl_804183F0.res[4] = 0;
    {
        Unit* u = lbl_803CA870.unit;
        x = u->x;
        y = u->y;
        Tail(p, fn_80172664(u, &x, &y), x, y);
    }
    lbl_804183F0.done = 1;
}
BOOL fn_801610E8(Unit* u, Unit* v, u32 lim, u8 a, u8 b, s16* ox, s16* oy) {
    
    Map* m;
    int best;
    int d;
    int low;
    int y;
    int x;

    m = &lbl_803EC898;
    fn_801663E0(v->x, v->y, a, b, 7);
    best = 0x80000000;
    low = 0x7FFFFFFF;
    for (y = m->y0; y <= m->y1 - 1; y++) {
        for (x = m->x0; x <= m->x1 - 1; x++) {
            if (m->costS[(s8)x + (s8)y * 0x40] < 0) continue;
            if (lbl_803EC898.b5S[(s8)x + (s8)y * 0x40]) continue;
            if (fn_801658E4(u, (s8)x, (s8)y)) continue;
            if (lbl_803EC898.g4[(s8)x + (s8)y * 0x40] == 0) continue;
            {
                u32 t = m->ter[0][(s8)x + (s8)y * 0x40];
                if (t && t != u->padFC[0]) continue;
            }
            if (lim < fn_801676D8((s8)x, (s8)y)) continue;
            if (low < (s16)lbl_803EC898.cost2[(s8)x + (s8)y * 0x40]) continue;
            d = fn_8015814C(u, x, y, 0);
            d += fn_80158208(u, x, y, 0);
            d -= fn_801676D8((s8)x, (s8)y) >> 4;
            if (best < d) {
                *ox = x;
                best = d;
                *oy = y;
                low = (s16)lbl_803EC898.cost2[(s8)x + (s8)y * 0x40];
            }
        }
    }
    return best != 0x80000000;
}
}
