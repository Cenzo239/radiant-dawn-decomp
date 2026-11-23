/* Flood fill step in one direction, 801161B0. */
#include "game/rH_80112B48/map.h"
#pragma auto_inline off
extern "C" {
void fn_801161B0(Map* m, u32 dir, int dx, int dy) {
    int nx;
    MapNode* n;
    u8 y0;
    u8 x0;
    int ny;
    int t;
    int i;
    u16 f;
    u16 c;
    int j;
    t = (dir & 0xf) << 4;
    n = m->head;
    y0 = n->y;
    x0 = n->x;
    ny = dy + y0;
    nx = dx + x0;
    i = (s8)x0 + ((s8)y0 << 6);
    f = m->flags[i];
    if (t & f) {
        return;
    }
    if (!(dir & f)) {
        return;
    }
    j = (s8)nx + ((s8)ny << 6);
    c = *(s16*)&m->cur[i] + 1;
    if (c >= m->cur[j]) {
        return;
    }
    if (c > m->limit) {
        return;
    }
    m->tail->x = nx;
    m->tail->y = ny;
    m->tail->dir = dir;
    m->tail->cost = c;
    m->tail++;
    m->count++;
    m->cur[j] = c;
    if (c >= m->unk2623C) {
        m->g4[j] = 1;
    }
}
}
