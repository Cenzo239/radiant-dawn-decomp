#include "game/rG_800A3D88/types.h"

// Title slide 1: stacked gauge bars, one row per 30 points.
extern "C" {
struct Title {
    u8 pad[0x50];
    s16 m50, m52;
    u32 m54;
    u32 m58;
    s16 m5c;
    u8 pad5e[6];
    void* m64;
};
extern s16 lbl_804CA460;
extern s16 lbl_804CA462;
extern s16 lbl_804CA464;
void fn_8007E154();
void fn_8007E164();
#if TARGET_PC
FE10_PROTO void fn_8007E374(void*, p32arg, int);
#else
void fn_8007E374(void*, int, int);
#endif
void fn_8007E720(f32);
void fn_80080308();
void fn_800800D4(int);
void fn_80080388(f32, f32, f32, f32);
void fn_800803C8(f32, f32, f32, f32);
void fn_80080430(f32, f32, f32, f32, f32, f32);
void fn_80080578(int);
void fn_800808F8(f32, f32);
f32 fn_8017F68C(int, f32, f32, f32, f32);
static inline int Cur(Title* t) {
    if (t->m54 == 0) return t->m50;
    if (t->m54 == t->m58) return t->m52;
    return (int)fn_8017F68C(0, t->m50, t->m52, t->m54, t->m58);
}
static inline const s16& Min(const s16& a, const s16& b) { return b < a ? b : a; }
void fn_800C14F0(Title* t, s16 x, s16 y) {
int o;
int x2;
s16 y2;
int i;

    s16 a = Cur(t);
    s16 b = t->m5c;
    s16 n = (b - 1) / 30 + 1;
    x2 = x + 4;
    y2 = y - n * 15;
    i = n - 1;
    o = i * 30;
    for (; i >= 0; i--) {
        if (b > o) {
            fn_8007E154();
            fn_8007E374(t->m64, 0x13, 0x11);
            fn_8007E164();
            fn_800800D4(1);
            fn_80080430(x, y2, 0.0f, 0.0f, 4.0f, 16.0f);
            fn_80080578(0);
            fn_80080308();
            fn_8007E154();
            fn_8007E374(t->m64, 0x14, 0x11);
            fn_8007E164();
            fn_800800D4(10);
            fn_80080388(x2, y2 + 1, Min(b, lbl_804CA460) * 5, 14.0f);
            fn_800803C8(0.0f, 0.0f, 5.0f, 14.0f);
            fn_800808F8(0.0f, 0.0f);
            fn_80080308();
            fn_8007E154();
            fn_8007E374(t->m64, 0x15, 0x11);
            fn_8007E164();
            fn_800800D4(1);
            fn_80080430(x2 + Min(b, lbl_804CA462) * 5, y2, 0.0f, 0.0f, 7.0f, 16.0f);
            fn_80080578(0);
            fn_80080308();
            fn_8007E154();
            fn_8007E720(-0.1f);
            fn_8007E374(t->m64, 0x16, 0x11);
            fn_8007E164();
            fn_800800D4(10);
            fn_80080388(x2, y2 + 3, Min(a, lbl_804CA464) * 5, 10.0f);
            fn_800803C8(0.0f, 0.0f, 5.0f, 10.0f);
            fn_800808F8(0.0f, 0.0f);
            fn_80080308();
            fn_8007E154();
            fn_8007E720(0.1f);
            fn_8007E164();
            a -= 30;
            b -= 30;
        }
        y2 += 15;
        o -= 30;
    }
}
}
