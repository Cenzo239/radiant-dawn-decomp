/*
 * fn_800620A8 (round 22, exact): put the game-data camera at the centre of map tile (x, y).
 * Same body as the end of fn_80060D68: centre = tile + 0.5, height from fn_801142F0 clamped to the
 * map's limit at lbl_803EC898+0x1D428. Not paired-single code: the psq_st/psq_l only save f30/f31.
 */
#include "game/rC2_8005259C/base.h"
struct Map;
struct Big { u8 pad[0x1d428]; f32 lim; };
struct GD {
    u8 pad[0x934];
    f32 x934, y938, x93c, y940, x944, y948, z94c;
};
extern "C" {
extern Big lbl_803EC898;
f32 fn_801142F0(Map* m, f32 fx, f32 fy);
void fn_800620A8(GD* g, f32 x, f32 y)
{
    f32 z;
    x += 0.5f;
    y += 0.5f;
    g->x934 = x;
    g->y938 = y;
    z = fn_801142F0((Map*)&lbl_803EC898, x, y);
    if (z > lbl_803EC898.lim) {
        z = lbl_803EC898.lim;
    }
    g->x93c = x;
    g->y940 = y;
    g->z94c = z;
    g->x944 = x;
    g->y948 = y;
}
}
