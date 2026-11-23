#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off
typedef struct GProc { u8 pad[0x3C]; void* font; u8 pad40[7]; u8 b47; } GProc;
extern "C" {
extern int lbl_804CA498;
extern int lbl_804CA49C;
extern int lbl_804CA4A0;
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32, f32, f32, f32);
#if TARGET_PC
extern FE10_PROTO void fn_8007E374(void*, p32arg, int);
#else
extern void fn_8007E374(void*, int, int);
#endif
extern void fn_8007E7DC(u8);
extern void fn_8007E7F4(void);
extern void fn_8007E720(f32);
extern void* fn_800CD204(int);
extern void fn_80176B54(int, int, int, void*, int, int, int, int, int, int);
extern void fn_800800D4(int);
extern void fn_80080430(f32, f32, f32, f32, f32, f32);
extern void fn_80080578(int);
extern void fn_80080308(void);
extern void fn_80080388(f32, f32, f32, f32);
extern void fn_800803C8(f32, f32, f32, f32);
extern void fn_800808F8(f32, f32);
static inline const int& Min(const int& a, const int& b) { return b < a ? b : a; }
void fn_800EEB3C(GProc* p, int alpha, int v1, int v2, int flag, f32 x, f32 y) {
    f32 z = 400.0f;
    if (flag) z -= 1.0f;
    fn_8007E154();
    fn_8007E4E4(x, y, z, 1.0f);
    fn_8007E7DC(alpha);
    fn_8007E164();
    s16 yy = 0x1A;
    s16 n = (v2 - 1) / 30 + 1;
    int ca = 0x3B;
    int cb = 0x3F;
    for (int i = 0; i < n; i++) {
        if (v2 < 0) break;
        fn_8007E154();
        fn_8007E374(p->font, 0x15, 0x11);
        fn_8007E164();
        fn_800800D4(1);
        fn_80080430(ca, yy, 0.0f, 0.0f, 4.0f, 16.0f);
        fn_80080578(0);
        fn_80080308();
        fn_8007E154();
        fn_8007E374(p->font, 0x16, 0x11);
        fn_8007E164();
        fn_800800D4(10);
        fn_80080388(cb, yy + 1, Min(v2, lbl_804CA498) * 5, 16.0f);
        fn_800803C8(0.0f, 0.0f, 5.0f, 16.0f);
        fn_800808F8(0.0f, 0.0f);
        fn_80080308();
        fn_8007E154();
        fn_8007E374(p->font, 0x17, 0x11);
        fn_8007E164();
        fn_800800D4(1);
        fn_80080430(Min(v2, lbl_804CA49C) * 5 + cb, yy, 0.0f, 0.0f, 7.0f, 16.0f);
        fn_80080578(0);
        fn_80080308();
        if (v1 > 0) {
            fn_8007E154();
            fn_8007E720(-0.1f);
            fn_8007E374(p->font, 0x18, 0x11);
            fn_8007E164();
            fn_800800D4(10);
            fn_80080388(cb, yy + 3, Min(v1, lbl_804CA4A0) * 5, 16.0f);
            fn_800803C8(0.0f, 0.0f, 5.0f, 16.0f);
            fn_800808F8(0.0f, 0.0f);
            fn_80080308();
        }
        fn_8007E154();
        fn_8007E720(0.1f);
        fn_8007E164();
        yy += 0xF;
        v1 -= 30;
        v2 -= 30;
    }
    fn_8007E7F4();
}
}
