#include "game/rB_8002E1C4/types.h"

/* Functor runners over the map. The functor's vtable is at +0: slot +8 visits a
 * unit, slot +0xC visits a tile. Direction flags are 8 up, 2 right, 4 down, 1 left. */
struct MapUnit;
class RangeFunctor {
public:
    virtual void visitUnit(MapUnit* u);
    virtual void visitTile(s8 x, s8 y);
};
struct MapState {
    int w;
    int h;
    u8 pad8[5];
    u8 grid[64 * 64];
    u8 pad100d[0x508e - 0x100d];
    u16 dir[64 * 64];
    u8 pad[0x15190 - 0x508e - 0x2000];
    s16* dist;
};
extern "C" {
extern MapState lbl_803EC898;
extern u8* lbl_804CB810;

static inline MapUnit* byId(u8 id) {
    return id ? (MapUnit*)(lbl_804CB810 + (id - 1) * 0x3f0) : 0;
}
static inline MapUnit* unitAt(s8 x, s8 y) {
    return byId(lbl_803EC898.grid[x + y * 64]);
}

#pragma use_lmw_stmw on
void fn_800392FC(RangeFunctor* f, s8 x, s8 y) {
    u16* d = &lbl_803EC898.dir[x + y * 64];
    if (*d & 8) {
        MapUnit* u = unitAt(x, y - 1);
        if (u) f->visitUnit(u);
    }
    if (*d & 2) {
        MapUnit* u = unitAt(x + 1, y);
        if (u) f->visitUnit(u);
    }
    if (*d & 4) {
        MapUnit* u = unitAt(x, y + 1);
        if (u) f->visitUnit(u);
    }
    if (*d & 1) {
        MapUnit* u = unitAt(x - 1, y);
        if (u) f->visitUnit(u);
    }
}

#pragma use_lmw_stmw reset
void fn_800394E0(RangeFunctor* f, s8 x, s8 y) {
    u16* d = &lbl_803EC898.dir[x + y * 64];
    if (*d & 8) f->visitTile(x, y - 1);
    if (*d & 2) f->visitTile(x + 1, y);
    if (*d & 4) f->visitTile(x, y + 1);
    if (*d & 1) f->visitTile(x - 1, y);
}

void fn_800395F4(RangeFunctor* f, s8 x, s8 y) {
    u16* d = &lbl_803EC898.dir[x + y * 64];
    if (*d & 0x808) f->visitTile(x, y - 1);
    if (*d & 0x202) f->visitTile(x + 1, y);
    if (*d & 0x404) f->visitTile(x, y + 1);
    if (*d & 0x101) f->visitTile(x - 1, y);
}

void fn_80039708(RangeFunctor* f, s8 x, s8 y) {
    if (y - 1 >= 0) f->visitTile(x, y - 1);
    if (x + 1 < lbl_803EC898.w) f->visitTile(x + 1, y);
    if (y + 1 < lbl_803EC898.h) f->visitTile(x, y + 1);
    if (x - 1 >= 0) f->visitTile(x - 1, y);
}

#pragma use_lmw_stmw on
void fn_80039800(RangeFunctor* f, s8 v) {
    s8 y;
    for (y = 0; y < lbl_803EC898.h; y++) {
        s8 x;
        for (x = 0; x < lbl_803EC898.w; x++) {
            if (lbl_803EC898.dist[x + y * 64] >= v) {
                u8 id = lbl_803EC898.grid[x + y * 64];
                if (id) f->visitUnit(byId(id));
            }
        }
    }
}

void fn_800398E0(RangeFunctor* f, s8 v) {
    s8 y;
    for (y = 0; y < lbl_803EC898.h; y++) {
        s8 x;
        for (x = 0; x < lbl_803EC898.w; x++) {
            if (lbl_803EC898.dist[x + y * 64] >= v) f->visitTile(x, y);
        }
    }
}
#pragma use_lmw_stmw reset
}
