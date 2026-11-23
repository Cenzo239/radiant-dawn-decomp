#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off
typedef struct G { u8 pad[0x30]; f32 x; f32 y; Handle* h; void* font; u8 alpha; u8 t; u8 dur; u8 amp; u8 side; u8 t2; u8 dur2; u8 b47; } G;
extern "C" {
extern u8 lbl_80367458[];
extern u8 lbl_803C8E80[];
extern void* fn_801CE670(Handle*);
extern int fn_801CE620(Handle*);
extern void* fn_800D0864(const char*);
extern f32 fn_8001EF30(f32, f32, f32, f32);
extern f32 fn_8001EF44(int, int, f32, f32);
extern double fn_80295940(f32);
extern double fn_80295534(f32);
extern void fn_800EF0D8(f32, f32, G*, int, int);
extern void fn_800EE798(G*, int, int, void*, f32, f32);
extern void fn_800EEB3C(G*, int, int, int, int, f32, f32);
extern void fn_800EE910(G*, int, int, int, int, f32, f32, f32, f32);
extern void fn_800EEEC4(G*, int, int, int, f32, f32);
void fn_800EF25C(G* p) {
    if (p->h && p->font && p->alpha) {
/*P*/
        s16 hp;
        s16 max;
        void* name;
        int lv;
        int ix;
        int iy;
/*E*/
        f32 a = 0.0f;
        f32 b = a;
        f32 c = a;
        f32 d = a;
        name = fn_801CE670(p->h);
        lv = fn_801CE620(p->h);
        hp = p->h->unk6;
        max = *(s16*)((u8*)p->h + 0xC);
        if (name == 0) {
            lv = 4;
            switch (*(u32*)(lbl_803C8E80 + 0x15EC) & 0x180000) {
            case 0x80000:
                name = fn_800D0864((char*)lbl_80367458 + 0x14);
                break;
            case 0x100000:
                name = fn_800D0864((char*)lbl_80367458 + 0x1A);
                break;
            case 0x180000:
                name = fn_800D0864((char*)lbl_80367458 + 0x20);
                break;
            }
        }
        if (p->dur) {
            f32 s = fn_8001EF30(0.0f, 20.0f * p->dur / 10.0f, p->dur, ++p->t);
            if (p->side == 0) {
                { f32 t0 = fn_80295940(s); a = p->amp * (3.0f * t0); }
                { f32 t0 = fn_80295534(s); b = p->amp * (2.0f * t0); }
            } else {
                { f32 t0 = fn_80295940(s); c = p->amp * (3.0f * t0); }
                { f32 t0 = fn_80295534(s); d = p->amp * (2.0f * t0); }
            }
            if (p->t >= p->dur) p->dur = 0;
        }
        ix = p->x + a;
        iy = p->y + b;
        if (p->dur2) {
            f32 f = fn_8001EF44(p->dur2, ++p->t2, 0.0f, 255.0f);
            if (p->t2 >= p->dur2) {
                p->dur2 = 0;
            } else {
                fn_800EF0D8(ix, iy, p, p->alpha * f / 255.0f, 1);
            }
        }
        fn_800EE798(p, p->alpha, lv, name, ix, iy);
        fn_800EEB3C(p, p->alpha, hp, max, 0, ix, iy);
        fn_800EE910(p, p->alpha, hp, max, 0, ix, iy, c, d);
        fn_800EEEC4(p, p->alpha, lv, 0, ix, iy);
        fn_800EF0D8(ix, iy, p, p->alpha, 0);
    }
}
}
