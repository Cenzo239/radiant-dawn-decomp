/* Flood fill step, 80115AC8. */
#include "game/rH_80112B48/unit.h"
#include "game/rH_80112B48/map.h"
#pragma auto_inline off

extern "C" {
extern u8 lbl_804CB84C;
extern s8 lbl_804CB84D;
extern s8 lbl_804CB84E;
extern u8 lbl_803CB770[];
#if TARGET_PC
extern FE10_PROTO struct Trap * fn_80066130(u8*, int, int, int);
#else
extern int fn_80066130(u8*, int, int, int);
#endif

static inline u16 CostAt(Map* m, int x, int y) {
    u8 t;
    if ((s8)x < 0 || m->w <= (s8)x || (s8)y < 0 || m->h <= (s8)y) {
        t = 0;
    } else {
        if (lbl_804CB84C) {
            s8 a = (lbl_804CB84D + (s8)x + m->w) % m->w;
            s8 b = (lbl_804CB84E + (s8)y + m->h) % m->h;
            x = a;
            y = b;
        }
        t = m->ter[1][(s8)x + ((s8)y << 6)];
    }
    return m->costTbl[t];
}
#pragma push
#pragma use_lmw_stmw on
void fn_80115AC8(Map* m, u8 d, int dx, int dy) {
        u16 c0;
    int y;
    int x;
MapNode* h = m->head; u16* cur = m->cur;u8 y0 = h->y; u8 x0 = h->x;c0 = cur[(s8)x0 + (s8)y0 * 0x40]; y = dy + y0; x = dx + x0;
    {
        u16 c;
        if (fn_80066130(lbl_803CB770, (s8)x, (s8)y, 0xc)) {
            c = 0x7fff;
        } else {
            c = CostAt(m, x, y);
        }
        c = c0 + c;
        {
            int idx = (s8)x + (s8)y * 0x40;
            u8 id = m->ter[0][idx];
            if (id && m->team[UnitGet(id)->team[8]] && m->unk2623E == 0) {
                return;
            }
            if (c < m->cur[idx] && c <= m->limit) {
                m->tail->x = x;
                m->tail->y = y;
                m->tail->dir = d;
                m->tail->cost = c;
                m->tail++;
                m->count++;
                m->cur[idx] = c;
            }
        }
    }
}
#pragma pop

}
