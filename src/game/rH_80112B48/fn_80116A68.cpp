/* Map path helpers, 80116A68, 80116BD0. */
#include "game/rH_80112B48/map.h"
#pragma auto_inline off

extern "C" {
#define ABS(a) ((a) < 0 ? -(a) : (a))

int fn_80116A68(Map* m, s8* ox, s8* oy, int f, u8* path) {
    s8 lx, ly;
    u8* cut;
    if (path == 0) {
        path = m->buf;
    }
    lx = *ox;
    cut = path;
    ly = *oy;
    for (;;) {
        Map* q;
        s8 x, y;
        u8 fl;
        switch (*path++) {
        case 1:
            (*ox)--;
            break;
        case 2:
            (*ox)++;
            break;
        case 4:
            (*oy)++;
            break;
        case 8:
            (*oy)--;
            break;
        case 0x40:
            goto none;
        }
        x = *ox;
        y = *oy;
        q = (Map*)((u8*)m + x + y * 0x40);
        fl = q->ter[3][0];
        if (fl & 1) {
            goto stop;
        }
        if (q->ter[0][0] == 0 && *(s8*)q->g5 == 0) {
            lx = x;
            ly = y;
            cut = path;
        }
        if ((fl & 2) && f == 0 && lx == x) {
            if (ly != y) {
                continue;
            }
            goto end;
        }
    }
none:
    return 0;
stop:
    *ox = lx;
    *oy = ly;
    *cut = 0x40;
    return 1;
end:
    *cut = 0x40;
    return 2;
}

#pragma push
#pragma use_lmw_stmw on
void fn_80116BD0(Map* m, s8 x, s8 y, s8 r, s16 v) {
        s8 x0 = x - r;
    s8 y0;
    s8 x1;
    s8 y1;
    int j;
    int i;
    if (x0 < 0) {
        x0 = 0;
    }
    y0 = y - r;
    if (y0 < 0) {
        y0 = 0;
    }
    x1 = x + r;
    if (x1 > m->w - 1) {
        x1 = m->w - 1;
    }
    y1 = y + r;
    if (y1 > m->h - 1) {
        y1 = m->h - 1;
    }
    {
        for (j = y0; (s8)j <= y1; j++) {
            for (i = x0; (s8)i <= x1; i++) {
                if (ABS((s8)i - x) + ABS((s8)j - y) <= r) {
                    Map* q = (Map*)((u8*)m + j * 0x40 + i);
                    if (*(s8*)q->g5 == 0) {
                        ((s16*)m->cur)[i + j * 0x40] = v + ((s16*)m->cur)[i + j * 0x40];
                    }
                }
            }
        }
    }
}
#pragma pop

}
