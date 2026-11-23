#include "game/rC2_8005259C/base.h"
struct C4 { u8 r, g, b, a; };
struct MU { u8 pad[0x10c]; u32 f10c; u8 p[0x3f0 - 0x110]; };
struct Tile { s8 x; s8 y; };
struct Ctx { u8 pad[0x11]; s8 x; s8 y; };
struct Map { u8 pad[0xd]; u8 id[1]; };
extern "C" {
extern Ctx lbl_803CA870;
extern Map lbl_803EC898;
extern int lbl_803E7320[];
extern MU* lbl_804CB810;
void fn_8013E7FC(void);
Tile* fn_800CFD18(void*, int);
void fn_8013EE5C(int, int, C4);
void fn_80021BA4(int, int, int, int);
}
static C4 colA = {0x00, 0x40, 0xa0, 0xff};
static C4 colB = {0xa0, 0x40, 0x00, 0xff};
static inline MU* unitAt(int id) {
    if (id) {
        return &lbl_804CB810[id - 1];
    }
    return 0;
}

#pragma use_lmw_stmw on
extern "C" void fn_800599C4(void) {
    s8 tx;
    int x;
    int y;
    int i;
    s8 ty;
    u8 id;
    fn_8013E7FC();
    i = 0;
    x = lbl_803CA870.x;
    y = lbl_803CA870.y;
    for (; i < lbl_803E7320[0]; i++) {
        tx = fn_800CFD18(lbl_803E7320, i)->x;
        ty = fn_800CFD18(lbl_803E7320, i)->y;
        id = lbl_803EC898.id[tx + ty * 0x40];
        if (id != 0 && (unitAt(id)->f10c & 0x20000)) {
            continue;
        }
        if (tx != x || ty != y) {
            fn_8013EE5C(tx, ty, colA);
        } else {
            fn_8013EE5C(tx, ty, colB);
        }
    }
    fn_80021BA4(1, 4, 5, 0);
}
