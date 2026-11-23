/* NOT MATCHING, not compiled. fn_80116680: wrong parameter registers and 8 words short; fn_80116294 is the sibling, not attempted. */
/* Walk the flood-fill cost grid back to a move path, 80116294, 80116680. */
#include "game/rH_80112B48/unit.h"
#include "game/rH_80112B48/map.h"
#pragma auto_inline off
extern "C" {
extern u8 lbl_804CA4D0[4];
extern u8 lbl_804CA4CC[4];
extern int fn_80089C88(int);

static inline void PathEnd(u8* e, u8* start) {
    u8 buf[0x100];
    u8* q = buf;
    u8* w = start;
    u8* t;
    while (e > start) {
        *q++ = *--e;
    }
    *q = 0x40;
    t = buf;
    while (*t != 0x40) {
        *w++ = *t++;
    }
    *w = 0x40;
}

#pragma push
#pragma use_lmw_stmw on
u8* fn_80116680(Map* m, u8* out, int x, int y) {
    u8* p = out;
    u8 tmp[8];
    int mv;
    u8* out2 = out;
    while (m->cur[(s8)x + (s8)y * 0x40] != 0) {
        int yo = (s8)y * 0x40;
        int a, b, c, d;
        int mn;
        int n;
        if ((s8)x < m->x1 - 1 && !(m->flags[(s8)(x + 1) + yo] & 0x10)) {
            a = m->cur[(s8)(x + 1) + yo];
        } else {
            a = (u16)0xffff;
        }
        if ((s8)x > m->x0 && !(m->flags[(s8)(x - 1) + yo] & 0x20)) {
            b = m->cur[(s8)(x - 1) + yo];
        } else {
            b = (u16)0xffff;
        }
        if ((s8)y < m->y1 - 1 && !(m->flags[(s8)x + (s8)(y + 1) * 0x40] & 0x80)) {
            d = m->cur[(s8)x + (s8)(y + 1) * 0x40];
        } else {
            d = (u16)0xffff;
        }
        if ((s8)y > m->y0 && !(m->flags[(s8)x + (s8)(y - 1) * 0x40] & 0x40)) {
            c = m->cur[(s8)x + (s8)(y - 1) * 0x40];
        } else {
            c = (u16)0xffff;
        }
        mn = 0xffff;
        n = 0;
        if ((u16)mn > (u16)a) {
            mn = a;
        }
        if ((u16)mn > (u16)b) {
            mn = b;
        }
        if ((u16)mn > (u16)c) {
            mn = c;
        }
        if ((u16)mn > (u16)d) {
            mn = d;
        }
        if ((u16)mn == (u16)a) {
            tmp[0] = lbl_804CA4D0[0];
            n = 1;
        }
        if ((u16)mn == (u16)b) {
            tmp[n] = lbl_804CA4D0[1];
            n++;
        }
        if ((u16)mn == (u16)c) {
            tmp[(u8)n++] = lbl_804CA4D0[2];
        }
        if ((u16)mn == (u16)d) {
            tmp[(u8)n++] = lbl_804CA4D0[3];
        }
        switch ((u8)n) {
        case 1:
            mv = tmp[0];
            break;
        case 2:
        case 3:
        case 4:
            mv = tmp[fn_80089C88((u8)n)];
            break;
        }
        *p++ = mv;
        switch (mv) {
        case 1:
            x++;
            break;
        case 2:
            x--;
            break;
        case 8:
            y++;
            break;
        case 4:
            y--;
            break;
        }
    }
    PathEnd(p, out2);
    return out2;
}
#pragma pop
}
