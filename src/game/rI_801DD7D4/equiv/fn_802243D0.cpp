/* fn_802243D0: draws the selection cursor of a scrolling grid when the selected cell is visible. */
#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E720(f32);
void fn_8007E7B4(void);
void fn_8007E7E8(int);
int fn_800CB0FC(f32, int);
void fn_800712E8(int, int, int);
}
class Grid { public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(void*); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); virtual int v38(); virtual int v3C();
    virtual int v40(); virtual int v44(); virtual int v48(); virtual int v4C(); virtual int v50(); virtual int v54(); virtual int v58(int, int, int, int, int);
    int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26, a28; u8 p2a[2];
    f32 sx, sy, sz; u32 flags; void* parent; u8 p40[0x15]; u8 a55; u8 p56[2]; s16 cur; u8 p5a[4]; s16 top; s16 cols; s16 rowH; u8 p64[4]; s16 scroll;
};
extern "C" void fn_802243D0(Grid* o, void* c) {
    if (o->a55) {
        int colW;
        s16 rowH, col, row, x, y;
        int d, yy, cy;
        o->v18(c);
        fn_8007E154();
        fn_8007E720(-0.5f);
        fn_8007E164();
        colW = o->v44();
        {
            int q = o->cur / o->cols;
            col = o->cur - q * o->cols;
            row = (s16)q - o->top;
        }
        rowH = o->rowH;
        x = colW * col + o->tx;
        y = rowH * row + o->ty;
        d = (rowH - fn_800CB0FC(1.0f, -1)) >> 1;
        yy = o->scroll + y;
        cy = d + yy;
        if (cy >= o->ty && (s16)(o->iy1 - o->iy0) - o->ty >= rowH + yy - d) {
            fn_8007E154();
            fn_8007E7E8(0x40);
            fn_8007E164();
            fn_800712E8(x, cy, 0);
            fn_8007E154();
            fn_8007E720(2.0f);
            fn_8007E164();
            o->v58((s16)(x - o->tx), (s16)yy, (s16)colW, rowH, 0);
        }
    }
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E7E8(0x80);
    fn_8007E164();
}
