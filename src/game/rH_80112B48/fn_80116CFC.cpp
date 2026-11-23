/* Map: terrain lookup with wrap-around, ranges and move strings, 80115CD8..80118280. */
#include "game/rH_80112B48/map.h"
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off

extern "C" {

extern u8 lbl_804CB84C;
extern s8 lbl_804CB84D;
extern s8 lbl_804CB84E;
extern u32 lbl_804CB700;
extern int fn_8011D260(int);
extern void* fn_8010B240(int);
extern BOOL fn_8011F5B4(Unit*);

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

s16 fn_80115CD8(Map* m, s8 x, s8 y) {
    s16 c = m->costTbl[MapTer(m, x, y)];
    u8 id = m->ter[0][x + (y << 6)];
    if (id) {
        Unit* v = UnitGet(id);
        if (m->team[v->team[8]]) {
            return 0x7fff;
        }
    }
    return c;
}

int fn_8011800C(u8* s, u8* d) {
    int n;
    if (d == 0) {
        return 0;
    }
    if (s == 0) {
        *d = 0x40;
        return 0;
    }
    n = 0;
    while (*s != 0x40) {
        n++;
        *d++ = *s++;
    }
    *d = 0x40;
    return n;
}

int fn_8011806C(u8* s) {
    int n = 0;
    if (s) {
        while (*s != 0x40) {
            n++;
            s++;
        }
    }
    return n;
}

u8 fn_80118098(Map* m, s8 x, s8 y) {
    return MapTer(m, x, y);
}

u8 fn_80118130(Map* m, s8 x, s8 y) {
    return fn_8011D260(MapTer(m, x, y));
}

void* fn_801181E8(Map* m, s8 x, s8 y) {
    return fn_8010B240(MapTer(m, x, y));
}

void* fn_80118280(Map* m, Unit* u) {
    if (lbl_804CB700 & 0x80000) {
        return 0;
    }
    if (!fn_8011F5B4(u)) {
        return 0;
    }
    s8 y = u->y; s8 x = u->x; return fn_8010B240(MapTer(m, x, y));
}

}
