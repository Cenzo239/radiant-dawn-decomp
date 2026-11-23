/* NOT MATCHING, not compiled. fn_80116680: about 120 words. The whole body in an inline gives the parameter order; the cur reload and the u16 temporaries are still wrong. fn_80116294 is the sibling. */
/* NOT MATCHING, not compiled. fn_80116680: wrong parameter registers and 8 words short; fn_80116294 is the sibling, not attempted. */
/* Walk the flood-fill cost grid back to a move path, 80116294, 80116680. */
#include "game/rH_80112B48/unit.h"
#include "game/rH_80112B48/map.h"
#pragma auto_inline off
extern "C" {
extern u8 lbl_804CA4D0[4];
extern u8 lbl_804CA4CC[4];
extern int fn_80089C88(int);
static inline int Max() { return 0xffff; }
#define Lo(mn,a) { u16 z = a; if ((u16)mn > z) mn = z; }

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
static inline u16 CE(Map* m, int x, int y) { if ((s8)x < m->x1 - 1 && !(m->flags[(s8)(x + 1) + (s8)y * 0x40] & 0x10)) return m->cur[(s8)(x + 1) + (s8)y * 0x40]; return 0xffff; }
static inline int CW(Map* m, int x, int y) { if ((s8)x > m->x0 && !(m->flags[(s8)(x - 1) + (s8)y * 0x40] & 0x20)) return m->cur[(s8)(x - 1) + (s8)y * 0x40]; return 0xffff; }
static inline u16 CS(Map* m, int x, int y) { if ((s8)y < m->y1 - 1 && !(m->flags[(s8)x + (s8)(y + 1) * 0x40] & 0x80)) return m->cur[(s8)x + (s8)(y + 1) * 0x40]; return 0xffff; }
static inline u16 CN(Map* m, int x, int y) { if ((s8)y > m->y0 && !(m->flags[(s8)x + (s8)(y - 1) * 0x40] & 0x40)) return m->cur[(s8)x + (s8)(y - 1) * 0x40]; return 0xffff; }
static inline u8* Walk(Map* m, u8* out, int x, int y) {
    u8* p = out;
    u8* out2 = out;
    u8 tmp[8];
    int mv;
    while ((s16)m->cur[(s8)x + (s8)y * 0x40] != 0) {
        int a = CE(m,x,y);
        int b = CW(m,x,y);
        int d = CS(m,x,y);
        int c = CN(m,x,y);
        int mn = 0xffff;
        int n = 0;
        Lo(mn,a);Lo(mn,b);Lo(mn,c);Lo(mn,d);
        {
        u16 q = mn;
        if (q == (u16)a) {
            tmp[0] = lbl_804CA4D0[0];
            n = 1;
        }
        if (q == (u16)b) {
            tmp[n] = lbl_804CA4D0[1];
            n++;
        }
        if (q == (u16)c) {
            tmp[(u8)n++] = lbl_804CA4D0[2];
        }
        if (q == (u16)d) {
            tmp[(u8)n++] = lbl_804CA4D0[3];
        }
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
u8* fn_80116680(Map* m, u8* out, int x, int y) {
    return Walk(m, out, x, y);
}
#pragma pop
}
