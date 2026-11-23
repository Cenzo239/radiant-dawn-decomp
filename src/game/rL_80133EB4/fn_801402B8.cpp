#include "game/rL_80133EB4/types.h"
struct Path { s8 x[0x40]; s8 y[0x40]; u8 pad80[0x40]; s8 s[0x40]; s8 n; };
struct Map { u8 p[0x20000]; };
#define FIFO (*(volatile f32*)0xCC008000)
extern "C" {
extern Map lbl_803EC898;
extern void* lbl_804CB580;
extern void fn_80006A64(void*, void*, int);
extern void fn_80022254(void*, int);
extern void fn_803031CC(void);
extern void fn_80302B80(int, int);
extern void fn_80303200(int, int, int, int, int);
extern void fn_80021C34(int);
extern void fn_80021F7C(int, int, int, int);
extern void fn_80021B2C(int);
extern void fn_80021A08(int, int, int, int, int, int, int);
extern void fn_80021BF4(int);
extern void fn_80021CB4(int, int, int, int);
extern void fn_80021EF8(int, int);
extern void fn_80021BA4(int, int, int, int);
extern void fn_80021B68(int);
extern void* fn_8000FB88(void);
extern void fn_80312378(void*, void*, void*);
extern void fn_80307E48(void*, int);
extern void fn_80307F10(void*, int, int);
extern void fn_80021784(int);
extern void fn_803128AC(void*, f32, f32, f32);
extern void fn_8031292C(void*, f32, f32, f32);
extern u8 fn_801147E4(Map*, int, int);
extern void fn_80304314(int, int, int);
extern f32 fn_801146A8(Map*, int, int, int);
extern f32 fn_80114728(Map*, int, int);
extern void fn_80011838(int);

void fn_801402B8(Path* p) {
    u8 tex[0x20];
    u8 m2[0x30];
    u8 m1[0x30];
    fn_80006A64(lbl_804CB580, tex, 0);
    fn_803031CC();
    fn_80302B80(9, 1);
    fn_80302B80(0xD, 1);
    fn_80303200(0, 9, 1, 4, 0);
    fn_80303200(0, 0xD, 1, 4, 0);
    fn_80021B2C(1);
    fn_80021A08(4, 0, 0, 0, 0, 0, 2);
    fn_80021BF4(1);
    fn_80021EF8(0, 3);
    fn_80021CB4(0, 0, 0, 0xFF);
    fn_80021C34(1);
    fn_80021F7C(0, 1, 4, 0x1E);
    fn_8031292C(m2, 0.04761905f, 1.0f, 1.0f);
    fn_80307F10(m2, 0x1E, 1);
    fn_80021B68(0);
    fn_80022254(tex, 0);
    fn_803128AC(m1, 0.0f, 0.0f, -0.03f);
    fn_80312378(fn_8000FB88(), m1, m1);
    fn_80307E48(m1, 0);
    fn_80021784(0);
    fn_80021BA4(1, 4, 5, 0);
/*P*/
    s8 x;
    s8 y;
    int i;
/*E*/
    f32 x0;
    f32 y0;
    f32 x1;
    f32 y1;
    f32 e = 0.025f;
    for (i = 0; i <= p->n; i++) {
        x = p->x[i];
        y = p->y[i];
        x0 = x;
        y0 = y;
        x1 = 1.0f + x0;
        y1 = 1.0f + y0;
        if (fn_801147E4(&lbl_803EC898, x, y)) {
            fn_80304314(0x98, 0, 4);
            f32 z = fn_801146A8(&lbl_803EC898, x, y, 0);
            FIFO = x0; FIFO = y0; FIFO = z; FIFO = e + p->s[i]; FIFO = e;
            z = fn_801146A8(&lbl_803EC898, x, y, 1);
            FIFO = x1; FIFO = y0; FIFO = z; FIFO = (p->s[i] + 1) - e; FIFO = e;
            z = fn_801146A8(&lbl_803EC898, x, y, 2);
            FIFO = x0; FIFO = y1; FIFO = z; FIFO = e + p->s[i]; FIFO = 1.0f - e;
            z = fn_801146A8(&lbl_803EC898, x, y, 3);
            FIFO = x1; FIFO = y1; FIFO = z; FIFO = (p->s[i] + 1) - e; FIFO = 1.0f - e;
        } else {
            fn_80304314(0xA0, 0, 6);
            f32 z = fn_80114728(&lbl_803EC898, x, y);
            FIFO = 0.5f + x0; FIFO = 0.5f + y0; FIFO = z; FIFO = 0.5f + p->s[i]; FIFO = 0.5f;
            z = fn_801146A8(&lbl_803EC898, x, y, 0);
            FIFO = x0; FIFO = y0; FIFO = z; FIFO = e + p->s[i]; FIFO = e;
            z = fn_801146A8(&lbl_803EC898, x, y, 1);
            FIFO = x1; FIFO = y0; FIFO = z; FIFO = (p->s[i] + 1) - e; FIFO = e;
            z = fn_801146A8(&lbl_803EC898, x, y, 3);
            FIFO = x1; FIFO = y1; FIFO = z; FIFO = (p->s[i] + 1) - e; FIFO = 1.0f - e;
            z = fn_801146A8(&lbl_803EC898, x, y, 2);
            FIFO = x0; FIFO = y1; FIFO = z; FIFO = e + p->s[i]; FIFO = 1.0f - e;
            z = fn_801146A8(&lbl_803EC898, x, y, 0);
            FIFO = x0; FIFO = y0; FIFO = z; FIFO = e + p->s[i]; FIFO = e;
        }
    }
    fn_80011838(-1);
}
}
