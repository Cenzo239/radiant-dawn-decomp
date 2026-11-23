/* 800F199C: registers only, m and q swapped (m r30, q r29 in the original). Everything else matches. */
#include "game/rE_800E5DE4/types.h"
typedef struct CC { u8 pad[0x25]; u8 b25; u8 pad26[2]; u16 h28; } CC;
typedef struct Obj { u8 pad[0x30]; CC* ctl; } Obj;
extern "C" {
extern u16 fn_80008D48(void*, const u16*);
extern void* fn_8017C288(void*);
extern u32 fn_80008CF0(void*, u16);
extern void fn_8017C1AC(void*, u16);
extern Obj* fn_8017C218(int, void*);
extern void fn_8017C1E0(Obj*, u16);
#pragma use_lmw_stmw on
Obj* fn_800F199C(void* m0, void* q0) {
/*P*/
    Obj* o;
    void* mm;
    void* qq;
    u16 k;
/*E*/
    mm = m0;
    qq = q0;
    if (mm == 0) return 0;
    const u16 t[] = {0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0xA0, 0xA1, 0xFFFF};
    k = fn_80008D48(mm, t);
    if (k == 0xFFFF) return 0;
    o = 0;
    if (k == 0x96) {
        void* x = fn_8017C288(qq);
        if (x) {
            fn_8017C1AC(x, ((fn_80008CF0(mm, k) >> 10) & 0x3F) * 10);
        }
        return 0;
    }
    switch (k) {
    case 0x97: o = fn_8017C218(0, qq); break;
    case 0x98: o = fn_8017C218(1, qq); break;
    case 0x99: o = fn_8017C218(2, qq); break;
    case 0x9A: o = fn_8017C218(3, qq); break;
    case 0x9B: o = fn_8017C218(4, qq); break;
    case 0x9C: o = fn_8017C218(5, qq); break;
    case 0x9D: o = fn_8017C218(6, qq); break;
    case 0x9E: o = fn_8017C218(7, qq); break;
    case 0x9F: o = fn_8017C218(8, qq); break;
    case 0xA0: o = fn_8017C218(9, qq); break;
    case 0xA1: o = fn_8017C218(10, qq); break;
    }
    if (o) {
        u32 v = fn_80008CF0(mm, k);
        u8 a = (int)(v & 0x7F) * 255 / 100;
        int h = (v >> 7) & 7;
        u16 d = (int)((v >> 10) & 0x3F) * 10;
        if ((u16)v) {
            if (a) o->ctl->b25 = a;
            if (h) o->ctl->h28 = h;
            if (d) fn_8017C1E0(o, d);
        }
    }
    return o;
}
}
