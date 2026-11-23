/* fn_80020354: exact. fn_80020764: functionally equal (check_regs: sched, 2 of 223 words differ; symcheck: the FIFO write
   sequence is equal, the one flagged block is a float temporary left in f1 before fn_803077C4(int), which reads r3 only).
   Corrected copy of wip/fn_80020354.cpp (round 21 regs review). THE WIP VERSION IS WRONG: it sends the corners of the
   GXBegin(0x98 triangle strip, 0, 4) in perimeter order (x,y) (x2,y) (x2,y2) (x,y2); the original sends strip order
   (x,y) (x2,y) (x,y2) (x2,y2). fn_80020354 passed as `regs` with that bug because the corner is chosen only by which
   register is stored. Don't port from the wip file. */
#include "game/rA_800068A0/types.h"

/* Full-screen / rectangle fills drawn directly through the GX FIFO. The state
 * setup inlines the cached setters of fn_80021754.c with constant arguments. */

typedef struct GColor { u8 r, g, b, a; } GColor;

extern "C" {

#define GXFIFO_F32 (*(volatile f32*)0xCC008000)
#define GXFIFO_U8 (*(volatile u8*)0xCC008000)

extern void fn_803031CC(void);
extern void fn_80302B80(int, int);
extern void fn_80303200(int, int, int, int, int);
extern void fn_80305794(int);
extern void fn_80021A08(int, int, int, int, int, int, int);
extern void fn_8030385C(int);
extern void fn_80307274(int);
extern void fn_80306C18(int, int);
extern void fn_80307118(int, int, int, int);
extern void fn_80307748(int, int, int, int);
extern void fn_803077F0(int, int, int);
extern void fn_80307054(int, int, int, int, int);
extern void fn_803045DC(int);
extern void fn_80304314(int, int, int);
extern void fn_80011838(int);
extern void fn_80307798(int);
extern void fn_803077C4(int);
extern u8 lbl_804CB0D8;
extern u8 lbl_804CB0E5;
extern u8 lbl_804CB0E4;
extern u32 lbl_803BF8B8[16];
extern u32 lbl_803BF8F8[16];
extern u32 lbl_803BF938[16];
extern u32 lbl_803BF978[16];
extern u32 lbl_803BF9B8[16];
extern u32 lbl_803BF878[16];
extern u32 lbl_804CB0E0;
extern u32 lbl_804CB0C4;
extern u32 lbl_804CB0C0;
extern u32 lbl_804CB0DC;

static inline void gxE4(int v) {
    if (lbl_804CB0E4 != v) {
        fn_80307274(v);
        lbl_804CB0E4 = v;
    }
}

static inline void gxState1(void) {
    fn_803031CC();
    fn_80302B80(9, 1);
    fn_80302B80(0xB, 1);
    fn_80303200(0, 9, 1, 4, 0);
    fn_80303200(0, 0xB, 1, 5, 0);
    if (lbl_804CB0D8 != 1) {
        fn_80305794(1);
        lbl_804CB0D8 = 1;
    }
    fn_80021A08(4, 0, 1, 1, 0, 0, 2);
    if (lbl_804CB0E5 != 0) {
        fn_8030385C(0);
        lbl_804CB0E5 = 0;
    }
    gxE4(1);
    if (lbl_803BF8B8[0] != 4) {
        lbl_803BF8F8[0] = -1;
        lbl_803BF938[0] = -1;
        lbl_803BF978[0] = -1;
        lbl_803BF9B8[0] = -1;
        fn_80306C18(0, 4);
        lbl_803BF8B8[0] = 4;
    }
    if (lbl_803BF878[0] != 0x4FFFF) {
        fn_80307118(0, 0xFF, 0xFF, 4);
        lbl_803BF878[0] = 0x4FFFF;
    }
}

static inline void gxState2(void) {
    if (lbl_804CB0C4 != 0x300) {
        fn_803077F0(0, 3, 0);
        lbl_804CB0C4 = 0x300;
    }
    if (lbl_804CB0C0 != 0x7100) {
        fn_80307054(0, 0, 1, 7, 0);
        lbl_804CB0C0 = 0x7100;
    }
    if (lbl_804CB0DC != 0) {
        fn_803045DC(0);
        lbl_804CB0DC = 0;
    }
}

static inline void gxPos3(f32 x, f32 y, f32 z) {
    GXFIFO_F32 = x;
    GXFIFO_F32 = y;
    GXFIFO_F32 = z;
}
static inline void gxCol4(u8 r, u8 g, u8 b, u8 a) {
    GXFIFO_U8 = r;
    GXFIFO_U8 = g;
    GXFIFO_U8 = b;
    GXFIFO_U8 = a;
}

void fn_80020354(int x, int y, int w, int h, const GColor* col, f32 z) {
    GColor def[4] = {{0, 0, 0, 0xFF}, {0, 0, 0, 0xFF}, {0, 0, 0, 0xFF}, {0, 0, 0, 0xFF}};
    if (col == 0) {
        col = def;
    }
    gxState1();
    if (lbl_804CB0E0 != 0x50401) {
        fn_80307748(1, 4, 5, 0);
        lbl_804CB0E0 = 0x50401;
    }
    gxState2();
    fn_80304314(0x98, 0, 4);
    int x2 = x + w;
    int y2 = y + h;
    gxPos3(x, y, z);
    gxCol4(col->r, col->g, col->b, col->a);
    gxPos3(x2, y, z);
    gxCol4(col->r, col->g, col->b, col->a);
    gxPos3(x, y2, z);
    gxCol4(col->r, col->g, col->b, col->a);
    gxPos3(x2, y2, z);
    gxCol4(col->r, col->g, col->b, col->a);
    fn_80011838(-1);
}

void fn_80020764(int x, int y, int w, int h, const GColor* col) {
    GColor def = {0, 0, 0, 0};
    if (col == 0) {
        col = &def;
    }
    gxState1();
    if (lbl_804CB0E0 != 0) {
        fn_80307748(0, 0, 0, 0);
        lbl_804CB0E0 = 0;
    }
    gxState2();
    fn_80307798(0);
    fn_803077C4(1);
    fn_80304314(0x98, 0, 4);
    int x2 = x + w;
    int y2 = y + h;
    gxPos3(x, y, 0.0f);
    gxCol4(0, 0, 0, ((u8*)col)[0]);
    gxPos3(x2, y, 0.0f);
    gxCol4(0, 0, 0, ((u8*)col)[1]);
    gxPos3(x, y2, 0.0f);
    gxCol4(0, 0, 0, ((u8*)col)[2]);
    gxPos3(x2, y2, 0.0f);
    gxCol4(0, 0, 0, ((u8*)col)[3]);
    fn_803077C4(0);
    fn_80307798(1);
    fn_80011838(-1);
}

} /* extern "C" */
