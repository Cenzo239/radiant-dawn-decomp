/* NOT MATCHING, not compiled. fn_80116294: first draft, right size within 4 words, heavy colouring left (15 saved registers). */
/* Trace a move path back through the cost grid, 80116294. */
#include "game/rH_80112B48/map.h"
#pragma auto_inline off
extern "C" {
extern u8 lbl_804CA4CC[4];
static inline u16 CR(Map* m, int x, int y, int mask, int want) {
    int i;
    if ((s8)x >= m->w) return 0xffff;
    i = (s8)(x + 1) + ((s8)y << 6);
    if ((m->flags[i] & mask) != want) return 0xffff;
    return m->cur[i];
}
static inline u16 CL(Map* m, int x, int y, int mask, int want) {
    int i;
    if ((s8)x <= 0) return 0xffff;
    i = (s8)(x - 1) + ((s8)y << 6);
    if ((m->flags[i] & mask) != want) return 0xffff;
    return m->cur[i];
}
static inline u16 CD(Map* m, int x, int y, int mask, int want) {
    int i;
    if ((s8)y >= m->h) return 0xffff;
    i = (s8)x + ((s8)(y + 1) << 6);
    if ((m->flags[i] & mask) != want) return 0xffff;
    return m->cur[i];
}
static inline u16 CU(Map* m, int x, int y, int mask, int want) {
    int i;
    if ((s8)y <= 0) return 0xffff;
    i = (s8)x + ((s8)(y - 1) << 6);
    if ((m->flags[i] & mask) != want) return 0xffff;
    return m->cur[i];
}
#pragma push
#pragma use_lmw_stmw on
u8* fn_80116294(Map* m, u8* p, int x, int y) {
    /*P*/
    int d;
    int z1;
    int z2;
    int z3;
    int z4;
    int m1;
    int m2;
    int m3;
    int m4;
    u16 c3;
    u16 c1;
    u16 c0;
    int mn;
    int n;
    u16 c2;
/*E*/
    u8 cand[8];
    u8 tmp[0x100];
    u8* path = p;
    z1 = 1; z2 = 2; z3 = 8; z4 = 4;
    m1 = 1; m2 = 2; m3 = 8; m4 = 4;
    if (m->unk2623D) {
        m1 = 0x10; m2 = 0x20; m3 = 0x80; m4 = 0x40;
        z1 = 0; z2 = 0; z3 = 0; z4 = 0;
    }
    while (m->cur[(s8)x + ((s8)y << 6)] != 0) {
        c0 = CR(m, x, y, m1, z1);
        c1 = CL(m, x, y, m2, z2);
        c2 = CD(m, x, y, m3, z3);
        c3 = CU(m, x, y, m4, z4);
        mn = 0xffff;
        n = 0;
        if ((u16)mn > c0) mn = c0;
        if ((u16)mn > c1) mn = c1;
        if ((u16)mn > c3) mn = c3;
        if ((u16)mn > c2) mn = c2;
        {
        u16 mv = mn;
        if (mv == c0) { cand[0] = lbl_804CA4CC[0]; n = 1; }
        if (mv == c1) { cand[n] = lbl_804CA4CC[1]; n++; }
        if (mv == c3) { cand[(u8)n] = lbl_804CA4CC[2]; n++; }
        if (mv == c2) { cand[(u8)n] = lbl_804CA4CC[3]; n++; }
        }
        switch ((u8)n) {
        case 1:
            d = cand[0];
            break;
        case 2:
        case 3:
        case 4:
            d = cand[0];
            break;
        }
        *p = d;
        p++;
        switch (d) {
        case 4: y--; break;
        case 2: x--; break;
        case 1: x++; break;
        case 8: y++; break;
        }
    }
    {
        u8* t = tmp;
        u8* q = path;
        for (; p > path; t++) {
            *t = *--p;
        }
        *t = 0x40;
        t = tmp;
        while (*t != 0x40) {
            *q = *t;
            t++;
            q++;
        }
        *q = 0x40;
    }
    return path;
}
#pragma pop
}
