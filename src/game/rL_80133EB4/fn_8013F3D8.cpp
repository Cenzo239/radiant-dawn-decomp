#include "game/rL_80133EB4/types.h"
struct Map { s32 w, h; u8 pad8[0x1318E - 8]; u16 tile[64][64]; };
#define FIFO (*(volatile f32*)0xCC008000)
extern "C" {
extern Map lbl_803EC898;
extern u32 lbl_804CB700;
extern void* lbl_804CB580;
extern int fn_80068D74(void);
extern void fn_8013F238(void);
extern void fn_80006A64(void*, void*, int);
extern void fn_80022254(void*, int);
extern u8 fn_801147E4(Map*, int, int);
extern void fn_80304314(int, int, int);
extern f32 fn_801146A8(Map*, int, int, int);
extern f32 fn_80114728(Map*, int, int);
extern void fn_80022158(int, int, int);
extern void fn_80306FD8(int, int, int, int, int);
extern void fn_80011838(int);

static inline void DrawAll(Map* m, u8* tex) {
/*P*/
    s8 x;
    s8 y;
    f32 fy1;
    u16* p;
    f32 fx1;
    f32 fy;
    f32 fx;
/*E*/
    for (y = m->h - 1; y >= 0; y--) {
        x = lbl_803EC898.w - 1;
        p = (u16*)(x * 2 + ((u8*)m + y * 0x80));
        for (; x >= 0; p--, x--) {
            u16 v = *(u16*)((u8*)p + 0x1318E);
            if (!(v & 0x2000)) continue;
            fn_80022254(tex + (v << 1 & 0x1E0), 0);
            fx = x;
            fy = y;
            fx1 = 1.0f + fx;
            fy1 = 1.0f + fy;
            if (fn_801147E4(&lbl_803EC898, x, y)) {
                fn_80304314(0x98, 0, 4);
                f32 z = fn_801146A8(&lbl_803EC898, x, y, 0);
                FIFO = fx; FIFO = fy; FIFO = z; FIFO = 0.0f; FIFO = 0.0f;
                z = fn_801146A8(&lbl_803EC898, x, y, 1);
                FIFO = fx1; FIFO = fy; FIFO = z; FIFO = 1.0f; FIFO = 0.0f;
                z = fn_801146A8(&lbl_803EC898, x, y, 2);
                FIFO = fx; FIFO = fy1; FIFO = z; FIFO = 0.0f; FIFO = 1.0f;
                z = fn_801146A8(&lbl_803EC898, x, y, 3);
                FIFO = fx1; FIFO = fy1; FIFO = z; FIFO = 1.0f; FIFO = 1.0f;
            } else {
                f32 cy;
                f32 cx = 0.5f * (fx + fx1);
                cy = 0.5f * (fy + fy1);
                f32 cz = fn_80114728(&lbl_803EC898, x, y);
                fn_80304314(0xA0, 0, 6);
                FIFO = cx; FIFO = cy; FIFO = cz; FIFO = 0.5f; FIFO = 0.5f;
                f32 z = fn_801146A8(&lbl_803EC898, x, y, 0);
                FIFO = fx; FIFO = fy; FIFO = z; FIFO = 0.0f; FIFO = 0.0f;
                z = fn_801146A8(&lbl_803EC898, x, y, 1);
                FIFO = fx1; FIFO = fy; FIFO = z; FIFO = 1.0f; FIFO = 0.0f;
                z = fn_801146A8(&lbl_803EC898, x, y, 3);
                FIFO = fx1; FIFO = fy1; FIFO = z; FIFO = 1.0f; FIFO = 1.0f;
                z = fn_801146A8(&lbl_803EC898, x, y, 2);
                FIFO = fx; FIFO = fy1; FIFO = z; FIFO = 0.0f; FIFO = 1.0f;
                z = fn_801146A8(&lbl_803EC898, x, y, 0);
                FIFO = fx; FIFO = fy; FIFO = z; FIFO = 0.0f; FIFO = 0.0f;
            }
        }
    }
}
void fn_8013F3D8(void) {
    if (fn_80068D74() == 0) return;
    if (lbl_804CB700 & 0x1000) return;
    u8 tex[0x200];
    u8* t;
    void* src;
    int i;
    fn_8013F238();
    {
        src = lbl_804CB580;
        t = tex;
        for (i = 0; i < 16; i++, t += 0x20) fn_80006A64(src, t, i + 1);
    }
    DrawAll(&lbl_803EC898, tex);
    fn_80022158(0, 0, 0);
    fn_80306FD8(3, 0, 1, 2, 3);
    fn_80011838(-1);
}
}
