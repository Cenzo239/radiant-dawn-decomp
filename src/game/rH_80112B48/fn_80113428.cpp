/* Map setup and flood fill, 80113428, 8011398C, 80115AC8, 80115DEC. */
#include "game/rH_80112B48/unit.h"
#include "game/rH_80112B48/map.h"
#pragma auto_inline off

extern "C" {
extern Map lbl_803EC898;
extern u8 lbl_804CB84C;
extern s8 lbl_804CB84D;
extern s8 lbl_804CB84E;
extern u8 lbl_803CB770[];
struct TileT {
    u8 pad0[8];
    u8* p8;
    u8 padC[4];
};
extern TileT* fn_8010B240(int);
extern u8* fn_8013B9A8(Map*);
extern u8 fn_8013554C(u8*);
extern void fn_80113BB4(Map*);
extern void fn_80113C74(Map*);
extern void fn_80113794(Map*, int, int, int);
extern void fn_80113890(Map*, int, int, int);
#if TARGET_PC
extern FE10_PROTO struct Trap * fn_80066130(u8*, int, int, int);
#else
extern int fn_80066130(u8*, int, int, int);
#endif
extern void fn_80114B44(Map*, int, int);
extern void fn_801161B0(Map*, int, int, int);

static inline u8 MapTer(Map* m, s8 x, s8 y) {
    if (x < 0 || m->w <= x || y < 0 || m->h <= y) {
        return 0;
    }
    if (lbl_804CB84C) {
        x = (lbl_804CB84D + x + m->w) % m->w;
        y = (lbl_804CB84E + y + m->h) % m->h;
    }
    return m->ter[1][x + (y << 6)];
}

#pragma push
#pragma use_lmw_stmw on
void fn_80113428(Map* m) {
        Map* g;
    u8 v;
    u8* row;
    int y;
    int x;
    u8* d;
    d = fn_8013B9A8(m);
    m->w = d[0x4c];
    m->h = d[0x4d];
    m->x0 = fn_8013554C(d);
    m->x1 = m->w - fn_8013554C(d);
    m->y0 = fn_8013554C(d);
    m->y1 = m->h - fn_8013554C(d);
    fn_80113BB4(m);
    fn_80113C74(m);
    g = &lbl_803EC898;
    for (y = g->y0; y <= g->y1 - 1; y++) {
        x = g->x0;
        row = (u8*)m + (s8)y * 0x40;
        for (; x <= g->x1 - 1; x++) {
            v = fn_8010B240(MapTer(m, x, y))->p8[7] & 1;
            row[(s8)x + 0xF18E] = v;
        }
    }
}
#pragma pop

void fn_8011398C(Map* m) {
    int x;
    int y;
    for (y = m->y0; y < m->y1; y++) {
        for (x = m->x0; x < m->x1; x++) {
            if (fn_8010B240(MapTer(m, x, y))->p8[7] & 2) {
                fn_80113794(m, (s8)x, (s8)y, 0xf00);
            }
        }
    }
    for (y = m->y0; y < m->y1; y++) {
        for (x = m->x0; x < m->x1; x++) {
            if (fn_8010B240(MapTer(m, x, y))->p8[7] & 4) {
                fn_80113890(m, (s8)x, (s8)y, 0xf0f);
            }
        }
    }
}


extern void fn_80115AC8(Map*, int, int, int);
static inline u16 Fl2(Map* m, MapNode* h) { s8 y = h->y; s8 x = h->x; return m->flags[x + y * 0x40]; }
#pragma push
#pragma use_lmw_stmw on
void fn_80115764(Map* m, s8 x, s8 y, u16 lim) {
    m->pad26234 = 0;
    m->limit = lim;
    m->head = (MapNode*)m->pad2562C;
    m->tail = (MapNode*)(m->pad2562C + 0x600);
    m->tail->x = x;
    m->tail->y = y;
    m->tail->dir = 0x20;
    m->tail->cost = 0;
    m->tail++;
    m->tail->dir = 0x40;
    fn_80114B44(m, 0xc, -1);
    m->padC = 0;
    m->cur[x + y * 0x40] = 0;
    for (;;) {
        u8 b = m->pad26234;
        m->count = 0;
        m->pad26234 = b ^ 1;
        m->tail = (MapNode*)(m->pad2562C + b * 0x600);
        m->head = (MapNode*)(m->pad2562C + m->pad26234 * 0x600);
        if (m->head->dir == 0x40) {
            break;
        }
        while (m->head->dir != 0x40) {
            u16 w = Fl2(m, m->head);
            if (m->unk2623D) {
                w = (u16)(w ^ 0xf0) >> 4;
            }
            switch (m->head->dir) {
            case 0x20:
                if (w & 8) {
                    fn_80115AC8(m, 8, 0, -1);
                }
                if (w & 4) {
                    fn_80115AC8(m, 4, 0, 1);
                }
                if (w & 1) {
                    fn_80115AC8(m, 1, -1, 0);
                }
                if (w & 2) {
                    fn_80115AC8(m, 2, 1, 0);
                }
                break;
            case 8:
                if (w & 8) {
                    fn_80115AC8(m, 8, 0, -1);
                }
                if (w & 1) {
                    fn_80115AC8(m, 1, -1, 0);
                }
                if (w & 2) {
                    fn_80115AC8(m, 2, 1, 0);
                }
                break;
            case 4:
                if (w & 4) {
                    fn_80115AC8(m, 4, 0, 1);
                }
                if (w & 1) {
                    fn_80115AC8(m, 1, -1, 0);
                }
                if (w & 2) {
                    fn_80115AC8(m, 2, 1, 0);
                }
                break;
            case 1:
                if (w & 8) {
                    fn_80115AC8(m, 8, 0, -1);
                }
                if (w & 4) {
                    fn_80115AC8(m, 4, 0, 1);
                }
                if (w & 1) {
                    fn_80115AC8(m, 1, -1, 0);
                }
                break;
            case 2:
                if (w & 8) {
                    fn_80115AC8(m, 8, 0, -1);
                }
                if (w & 4) {
                    fn_80115AC8(m, 4, 0, 1);
                }
                if (w & 2) {
                    fn_80115AC8(m, 2, 1, 0);
                }
                break;
            }
            m->tail->dir = 0x40;
            m->head++;
        }
    }
}
#pragma pop

#pragma push
#pragma use_lmw_stmw on
void fn_80115DEC(Map* m, s8 x, s8 y, u8 t, u16 lim) {
    m->pad26234 = 0;
    m->limit = lim;
    m->head = (MapNode*)m->pad2562C;
    m->tail = (MapNode*)(m->pad2562C + 0x600);
    m->unk2623C = t;
    m->tail->x = x;
    m->tail->y = y;
    m->tail->dir = 0x20;
    m->tail->cost = 0;
    m->tail++;
    m->tail->dir = 0x40;
    fn_80114B44(m, 0xc, -1);
    m->cur[x + y * 0x40] = 0;
    for (;;) {
        u8 b = m->pad26234;
        m->count = 0;
        m->pad26234 = b ^ 1;
        m->tail = (MapNode*)(m->pad2562C + b * 0x600);
        m->head = (MapNode*)(m->pad2562C + m->pad26234 * 0x600);
        if (m->head->dir == 0x40) {
            break;
        }
        while (m->head->dir != 0x40) {
            switch (m->head->dir) {
            case 0x20:
                fn_801161B0(m, 0x808, 0, -1);
                fn_801161B0(m, 0x404, 0, 1);
                fn_801161B0(m, 0x101, -1, 0);
                fn_801161B0(m, 0x202, 1, 0);
                break;
            case 8:
                fn_801161B0(m, 0x808, 0, -1);
                fn_801161B0(m, 0x101, -1, 0);
                fn_801161B0(m, 0x202, 1, 0);
                break;
            case 4:
                fn_801161B0(m, 0x404, 0, 1);
                fn_801161B0(m, 0x101, -1, 0);
                fn_801161B0(m, 0x202, 1, 0);
                break;
            case 1:
                fn_801161B0(m, 0x808, 0, -1);
                fn_801161B0(m, 0x404, 0, 1);
                fn_801161B0(m, 0x101, -1, 0);
                break;
            case 2:
                fn_801161B0(m, 0x808, 0, -1);
                fn_801161B0(m, 0x404, 0, 1);
                fn_801161B0(m, 0x202, 1, 0);
                break;
            }
            m->tail->dir = 0x40;
            m->head++;
        }
    }
}
#pragma pop

}
