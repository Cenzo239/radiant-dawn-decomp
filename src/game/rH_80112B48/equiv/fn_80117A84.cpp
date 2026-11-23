/* EQUIVALENT (sched, round 19b): fn_80117A84. Only difference (checked with dd.py): in the second grid loop the x counter is decremented after the three row pointers instead of before them.
 * Caveat: the byte grid at Map+0xF18E is read as `((s8*)m + 0xF18E)[y*0x40 + x]`; map.h declares that area as `u16 g5[0x1000]`, so the first 0x1000 bytes are really an s8 grid (a port should fix the Map layout). */
#include "game/rH_80112B48/unit.h"
#include "game/rH_80112B48/map.h"
#pragma auto_inline off
extern "C" {
extern u32 OSGetTick(void);
extern void fn_80114B44(Map*, int, int);
extern void fn_8010E41C(u8*, int);
extern void fn_80067168(Unit*);
extern u8 lbl_804CB830;
static inline u8 IC(u16 v) { return (v & 0x2000) ? 0 : 1; }
void fn_80117A84(Map* m) {
    u8 tbl[0x18];
    int i;
    OSGetTick();
    fn_80114B44(m, 10, 0);
    fn_8010E41C(tbl, 1);
    for (i = 1; i <= 0xfe; i++) {
        Unit* v = UnitGet(i);
        if (v->person && tbl[v->team[8]] && (v->flags10C & 0x800) && !(v->flags10C & 0x10000dc)) {
            int y;
            fn_80067168(v);
            for (y = (s8)(m->h - 1); (s8)y >= 0; y--) {
                int x;
                for (x = (s8)(m->w - 1); x >= 0; x--) {
                    if (((s8*)m + 0xF18E)[y*0x40 + x] == 0 && m->g4[x + y * 0x40] != 0) {
                        m->g7[x + y * 0x40] |= 0x2000;
                    }
                }
            }
        }
    }
    {
        int y;
        for (y = (s8)(m->h - 1); (s8)y >= 0; y--) {
            int x;
            for (x = (s8)(m->w - 1); x >= 0; x--) {
                u16 f = m->g7[x + y * 0x40];
                if (f) {
                    u16 v = (f >> 13) & 1;
                    int hi = v;
                    u8 a = (s8)y == 0 ? 0 : IC(m->g7[x + (s8)(y - 1) * 0x40]);
                    u8 b = (s8)y == m->h - 1 ? 0 : IC(m->g7[x + (s8)(y + 1) * 0x40]);
                    u8 c = (s8)x == 0 ? 0 : IC(m->g7[(s8)(x - 1) + y * 0x40]);
                    u8 d = (s8)x == m->w - 1 ? 0 : IC(m->g7[(s8)(x + 1) + y * 0x40]);
                    v <<= 5;
                    if (hi) {
                        v <<= 1; v |= a;
                        v <<= 1; v |= b;
                        v <<= 1; v |= d;
                        v <<= 1; v |= c;
                    } else {
                        v <<= 4;
                    }
                    m->g7[x + y * 0x40] = v << 4;
                }
            }
        }
    }
    {
        BOOL ok = 1;
        if (lbl_804CB830 != 1 && lbl_804CB830 != 2) ok = 0;
        if (ok) {
            int y;
            for (y = (s8)(m->h - 1); (s8)y >= 0; y--) {
                int x;
                for (x = (s8)(m->w - 1); x >= 0; x--) {
                    if (m->ter[2][x + y * 0x40] == 0) {
                        m->g7[x + y * 0x40] = 0;
                    }
                }
            }
        }
    }
    OSGetTick();
}
}
