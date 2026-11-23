/* fn_80136E74: functionally equal (regs level per tools/check_regs.py; registers differ from the original). From wip/near4.cpp. */
/* ===== fn_80136E74 (0x8B0): masked diff is 0, 100 lines of register ranks. The parameter must rank near the bottom (r22, wanted) but always takes r31 here, and hoisted 0, 6 and the map pointer must then move up. Wrappers, inlines and named copies do not move it. ===== */
/* Builds the display list of the terrain outline from the tile heights. */
#include "game/rL_80133EB4/types.h"
#pragma use_lmw_stmw off

struct TileDef { u8 pad0[7]; u8 x7; u8 pad8[0x14 - 8]; s8 x14[23]; };
struct Tile { u8 pad0[8]; TileDef* def; };
struct Map {
    u8 pad0[8];
    s8 x0, y0, x1, y1;
    u8 padc[0x100 - 0xC];
};
struct Obj {
    u8 pad0[0xBC];
    void* dl;
    u32 dlSize;
};
extern "C" {
extern Map lbl_803EC898;
extern char lbl_803694D4[];
extern void* fn_80078D9C(int, char*, int);
extern void* fn_80078CCC(u32, char*, int);
extern void fn_80078E24(void*);
extern Tile* fn_801181E8(Map*, int, int);
extern f32 fn_801146A8(Map*, int, int, int);
extern void DCInvalidateRange(void*, u32);
extern void DCFlushRange(void*, u32);
extern void fn_803079FC(void*, u32);
extern u32 fn_80307AAC(void);
extern void fn_80304314(int, int, int);
extern void* memcpy(void*, const void*, u32);

static inline void V(int x, int y, f32 h) {
    volatile f32* fifo = (volatile f32*)0xCC008000;
    *fifo = (f32)x;
    *fifo = (f32)y;
    *fifo = h;
}
static inline s16 Lv(TileDef* d, int j) {
    s8 v = d->x14[j];
    return v < 0 ? 0x7FFF : v;
}

void fn_80136E74(Obj* o) {
    /*P*/
    int k2;
    int xx;
    int yy;
    u8* b;
    u8* q;
    int x;
    u8* p;
    int ky;
    u8* d;
    int y;
    Map* m2;
    Map* map;
/*E*/
    b = (u8*)fn_80078D9C(-0x4000, lbl_803694D4 + 0x103, 0);
    map = &lbl_803EC898;
    f32 lim = 0.01f;
    y = map->y0;
    ky = y * 0x80;
    for (; y < map->y1; y++) {
        x = map->x0;
        p = x + (b + ky);
        for (; x < map->x1; x++) {
            *p = 0;
            TileDef* t = fn_801181E8(&lbl_803EC898, (s8)x, (s8)y)->def;
            if ((t->x7 & 1) == 0) {
                for (int j = 0; j < 23; j++) {
                    if (Lv(t, j) != 0x7FFF) goto F;
                }
                goto N;
                F:
                    {
                        *p = 6;
                        if (x == map->x0) {
                            *p |= 1;
                        } else if (p[-1] == 0) {
                            *p |= 1;
                        } else {
                            f32 a = fn_801146A8(map, (s8)(x - 1), (s8)y, 1);
                            f32 dx = fn_801146A8(map, (s8)x, (s8)y, 0) - a;
                            a = fn_801146A8(map, (s8)(x - 1), (s8)y, 3);
                            f32 dy = fn_801146A8(map, (s8)x, (s8)y, 2) - a;
                            if (dx * dx + dy * dy >= lim) *p |= 1;
                        }
                        if (y == map->y0) {
                            *p |= 8;
                        } else if (p[-0x80] == 0) {
                            *p |= 8;
                        } else {
                            f32 a = fn_801146A8(map, (s8)x, (s8)(y - 1), 2);
                            f32 dx = fn_801146A8(map, (s8)x, (s8)y, 0) - a;
                            a = fn_801146A8(map, (s8)x, (s8)(y - 1), 3);
                            f32 dy = fn_801146A8(map, (s8)x, (s8)y, 1) - a;
                            if (dx * dx + dy * dy >= lim) *p |= 8;
                        }
                    }
                N: ;
            }
            p++;
        }
        ky += 0x80;
    }
    d = (u8*)fn_80078D9C(-0x40000, lbl_803694D4 + 0x103, 0);
    DCInvalidateRange(d, 0x40000);
    fn_803079FC(d, 0x40000);
    {
    yy = map->y0;
    m2 = &lbl_803EC898;
    k2 = yy * 0x80;
    for (; yy < m2->y1; yy++) {
        xx = m2->x0;
        q = xx + (b + k2);
        for (; xx < m2->x1; xx++) {
            if (*q) switch (*q) {
            case 6:
                fn_80304314(0xB0, 0, 3);
                V(xx + 1, yy, fn_801146A8(&lbl_803EC898, (s8)xx, (s8)yy, 1));
                V(xx + 1, yy + 1, fn_801146A8(&lbl_803EC898, (s8)xx, (s8)yy, 3));
                V(xx, yy + 1, fn_801146A8(&lbl_803EC898, (s8)xx, (s8)yy, 2));
                break;
            case 7:
                fn_80304314(0xB0, 0, 4);
                V(xx + 1, yy, fn_801146A8(&lbl_803EC898, (s8)xx, (s8)yy, 1));
                V(xx + 1, yy + 1, fn_801146A8(&lbl_803EC898, (s8)xx, (s8)yy, 3));
                V(xx, yy + 1, fn_801146A8(&lbl_803EC898, (s8)xx, (s8)yy, 2));
                V(xx, yy, fn_801146A8(&lbl_803EC898, (s8)xx, (s8)yy, 0));
                break;
            case 14:
                fn_80304314(0xB0, 0, 4);
                V(xx, yy, fn_801146A8(&lbl_803EC898, (s8)xx, (s8)yy, 0));
                V(xx + 1, yy, fn_801146A8(&lbl_803EC898, (s8)xx, (s8)yy, 1));
                V(xx + 1, yy + 1, fn_801146A8(&lbl_803EC898, (s8)xx, (s8)yy, 3));
                V(xx, yy + 1, fn_801146A8(&lbl_803EC898, (s8)xx, (s8)yy, 2));
                break;
            case 15:
                fn_80304314(0xB0, 0, 5);
                V(xx, yy, fn_801146A8(&lbl_803EC898, (s8)xx, (s8)yy, 0));
                V(xx + 1, yy, fn_801146A8(&lbl_803EC898, (s8)xx, (s8)yy, 1));
                V(xx + 1, yy + 1, fn_801146A8(&lbl_803EC898, (s8)xx, (s8)yy, 3));
                V(xx, yy + 1, fn_801146A8(&lbl_803EC898, (s8)xx, (s8)yy, 2));
                V(xx, yy, fn_801146A8(&lbl_803EC898, (s8)xx, (s8)yy, 0));
                break;
            }
            q++;
        }
        k2 += 0x80;
    }
    }
    u32 n = fn_80307AAC();
    if (o->dl) {
        fn_80078E24(o->dl);
        o->dl = 0;
    }
    o->dl = fn_80078CCC(n, lbl_803694D4 + 0x103, 0);
    o->dlSize = n;
    DCFlushRange(o->dl, n);
    memcpy(o->dl, d, n);
    DCFlushRange(o->dl, n);
    fn_80078E24(d);
    fn_80078E24(b);
}
}

