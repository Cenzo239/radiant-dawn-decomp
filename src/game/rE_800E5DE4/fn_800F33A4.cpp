#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off
typedef struct W2 { u32 a, b; } W2;
typedef struct W3 { W2 ab; u32 c; } W3;
extern "C" {
extern W3 lbl_80367AD0;
extern W3 lbl_80367AA0;
extern void fn_80312654(f32 (*)[4], int, f32);
extern void fn_80312AC0(f32 (*)[4], const Vec*, const Vec*, const Vec*);
extern void fn_80312D2C(f32 (*)[4], f32, f32, f32, f32, f32, f32, f32, f32);
extern void fn_80312378(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
extern void fn_803128AC(f32 (*)[4], f32, f32, f32);
extern void fn_80312DB4(f32 (*)[4], const Vec*, Vec*);
void fn_800F33A4(int i, f32 (*out)[4], f32 x, f32 y, f32 w, f32 h, f32 ang) {
    Vec e0;
    Vec t0 = {0.0f, 0.0f, 0.0f};
    Vec up;
    Vec eye;
    Vec tgt;
    f32 q[3][4];
    f32 r[3][4];
    f32 l[3][4];
    f32 o[3][4];
    t0.x = x;
    t0.y = y;
    *(W3*)&tgt = *(W3*)&t0;
    *(W3*)&e0 = lbl_80367AA0;
    e0.x = x;
    e0.y = y;
    *(W3*)&eye = *(W3*)&e0;
    *(W3*)&up = lbl_80367AD0;
    if (0.0f != ang) {
        fn_80312654(r, 0x5A, 0.017453292f * ang);
        if (i == 0) fn_80312DB4(r, &up, &up);
        fn_80312AC0(l, &eye, &up, &tgt);
        fn_80312D2C(o, -w, w, -h, h, 0.5f, 0.5f, 0.5f, 0.5f);
        fn_80312378(o, l, out);
        fn_803128AC(q, -0.5f, -0.5f, 0.0f);
        fn_80312378(r, q, r);
        fn_803128AC(q, 0.5f, 0.5f, 0.0f);
        fn_80312378(q, r, r);
        fn_80312378(r, out, out);
    } else {
        fn_80312AC0(l, &eye, &up, &tgt);
        fn_80312D2C(o, -w, w, -h, h, 0.5f, 0.5f, 0.5f, 0.5f);
        fn_80312378(o, l, out);
    }
}
}
