/* fn_80179A84: scroll bar of the text panel: positions and steps the two arrows, then draws the track (top, tiled
 * middle, bottom) and the thumb (one piece when shorter than 16, else cap, tiled body, cap). Names guessed. */
#include "game/rR_80175E5C/types.h"
#pragma use_lmw_stmw off
struct Arrow {
    u8 pad0[0x39];
    u8 x39;         /* alpha */
    u8 pad3A[2];
    f32 x3C;        /* x */
    f32 x40;        /* y */
    f32 x44;        /* z */
    u8 pad48[0x54 - 0x48];
    int x54;        /* extra animation steps */
    int x58;
    u8 x5C;
    u8 x5D;         /* shown */
};
class Bar {
public:
    void* tex;      /* 0x00 */
    f32 x;          /* 0x04 */
    f32 y;          /* 0x08 */
    f32 z;          /* 0x0C */
    s16 len;        /* 0x10 */
    s16 total;      /* 0x12 */
    s16 vis;        /* 0x14 */
    s16 pos;        /* 0x16 */
    s16 prev;       /* 0x18 */
    u8 alpha;       /* 0x1A */
    Color col;        /* 0x1B */
    Arrow* up;      /* 0x20 */
    Arrow* down;    /* 0x24 */
    virtual u8 capTile();   /* vtable +0x8 */
    virtual u8 bodyTile();  /* vtable +0xC */
};
extern "C" {
void fn_80179214(Arrow*);
void fn_8007E7DC(u8);
void fn_8007E4E4(f32, f32, f32, f32);
#if TARGET_PC
FE10_PROTO void fn_8007E374(void*, p32arg, int);
#else
void fn_8007E374(void*, int, int);
#endif
void fn_80080410(f32, f32, f32, f32);

static inline void ArrowPos(Arrow* a, f32 x, f32 y) {
    a->x3C = x;
    a->x40 = y;
}

void fn_80179A84(Bar* b) {
    int x = (int)b->x;
    int y = (int)b->y;
    int h = b->len;
    if (h < 0x10) {
        return;
    }
    if (b->up) {
        y += 8;
        h -= 0x10;
        if (b->pos <= 0) {
            b->up->x5D = 0;
        } else {
            b->up->x5D = 1;
        }
        if (b->pos + b->vis >= b->total) {
            b->down->x5D = 0;
        } else {
            b->down->x5D = 1;
        }
        ArrowPos(b->up, x + 4, y - 8);
        b->up->x44 = b->z;
        b->up->x39 = b->alpha;
        fn_80179214(b->up);
        ArrowPos(b->down, x + 4, y + h + 8);
        b->down->x44 = b->z;
        b->down->x39 = b->alpha;
        fn_80179214(b->down);
        if (b->pos < b->prev) {
            Arrow* a = b->up;
            if (a->x5C) {
                a->x54 = 0x1e;
            } else {
                a->x54 = 1;
            }
        }
        if (b->pos > b->prev) {
            Arrow* a = b->down;
            if (a->x5C) {
                a->x54 = 0x1e;
            } else {
                a->x54 = 1;
            }
        }
    }
    fn_8007E7DC(b->alpha);
    fn_8007E154();
    fn_8007E4E4(x, y, 1.0f + b->z, 1.0f);
    fn_8007E374(b->tex, 2, 0x11);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080430(0.0f, 0.0f, 0.0f, 0.0f, 8.0f, 24.0f);
    fn_80080578(0);
    fn_80080308();
    fn_800800D4(1);
    fn_80080430(0.0f, h - 0x18, 0.0f, 0.0f, 8.0f, 24.0f);
    fn_800804B4();
    fn_80080578(0);
    fn_80080308();
    fn_8007E154();
    fn_8007E4E4(x, y, 1.0f + b->z, 1.0f);
    fn_8007E374(b->tex, 3, 0x11);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080430(-4.0f, 24.0f, 0.0f, 0.0f, 16.0f, h - 0x30);
    fn_80080578(0);
    fn_80080308();
    {
        int off = (h - 0x30) * b->pos / b->total;
        int sz = (h - 0x30) * b->vis / b->total;
        int room = h - 0x30;
        if (off + sz > room) {
            sz = room - sz;
        }
        if (sz < 0x10) {
            if (sz <= 4) {
                sz = 4;
            }
            fn_8007E154();
            fn_8007E4E4(x + 2, y + off + 0x18, b->z, 1.0f);
            fn_8007E374(b->tex, b->bodyTile(), 0x11);
            fn_8007E164();
            fn_800800D4(1);
            fn_800803F0(0.0f, 0.0f, 8.0f, sz);
            fn_80080410(0.0f, 0.0f, 8.0f, 24.0f);
            fn_80080578(0);
            fn_80080508(b->col);
            fn_80080308();
        } else {
            fn_8007E154();
            y = y + off + 0x18;
            fn_8007E4E4(x + 2, y, b->z, 1.0f);
            fn_8007E374(b->tex, b->capTile(), 0x11);
            fn_8007E164();
            fn_800800D4(1);
            fn_80080430(0.0f, 0.0f, 0.0f, 0.0f, 8.0f, 8.0f);
            fn_80080578(0);
            fn_80080508(b->col);
            fn_80080308();
            fn_8007E154();
            fn_8007E4E4(x + 2, y + 8, b->z, 1.0f);
            fn_8007E374(b->tex, b->bodyTile(), 0x11);
            fn_80080508(b->col);
            fn_8007E164();
            fn_800800D4(1);
            fn_800803F0(0.0f, 0.0f, 8.0f, sz - 0x10);
            fn_80080410(0.0f, 0.0f, 8.0f, 24.0f);
            fn_80080578(0);
            fn_80080508(b->col);
            fn_80080308();
            fn_8007E154();
            fn_8007E4E4(x + 2, sz + y - 8, b->z, 1.0f);
            fn_8007E374(b->tex, b->capTile(), 0x11);
            fn_8007E164();
            fn_800800D4(1);
            fn_80080430(0.0f, 0.0f, 0.0f, 0.0f, 8.0f, 8.0f);
            fn_800804B4();
            fn_80080578(0);
            fn_80080508(b->col);
            fn_80080308();
        }
    }
    fn_8007E7DC(0xff);
    b->prev = b->pos;
}
}
