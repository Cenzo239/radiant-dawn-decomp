#include "game/rG_800A3D88/types.h"

// Title slide 1: shaking logo plate, cursor arrow and counters, drawn with the Prim2D helpers.
extern "C" {
struct TtlS { u8 p[0x446]; u8 m446; u8 p447[0x476 - 0x447]; s16 m476; };
struct Title {
    u8 pad[0x30];
    s16 x, y, m34;
    u8 m36, m37, m38, m39;
    s16 m3a, m3c;
    u8 pad3e[2];
    f32 m40;
    u8 m44;
    u8 pad45[3];
    TtlS* m48;
    s8 m4c;
    u8 pad4d[3];
    s16 m50, m52;
    u32 m54;
    u32 m58;
    s16 m5c;
    u8 pad5e[2];
    void* m60;
    void* m64;
};
void fn_8007E154();
void fn_8007E164();
#if TARGET_PC
FE10_PROTO void fn_8007E374(void*, p32arg, int);
#else
void fn_8007E374(void*, int, int);
#endif
void fn_8007E4E4(f32, f32, f32, f32);
void fn_8007E720(f32);
void fn_8007E7DC(int);
void fn_80080308();
void fn_800800D4(int);
void fn_80080430(f32, f32, f32, f32, f32, f32);
void fn_800804F4(int);
void fn_80080578(int);
int fn_800CB0FC(int, f32);
void* fn_800CD204(int);
void fn_80176B54(int, int, int, void*, int, int, int, int, int, int);
f32 fn_8017F68C(int, f32, f32, f32, f32);
double fn_80295940(double);
double fn_80295534(double);
void fn_80108080(void*, int, int, int);
void fn_80108064(void*, int, int, int);
void fn_800C14F0(Title*, s16, s16);
long long OSGetTime();
#define BUS (*(u32*)0x800000F8)
void fn_800C18A4(Title* t) {
s16 a2;
int a1;
f32 w;
s16 a4;
int fr;
int b2;
int ay;
int ax;
int b4;
s16 h;
int c4;
s16 ox;
int e2;
s16 oy;
int e3;
int c1;
int c2;
u32 tk;
int d4;
int e1;
s16 e4;
int f5;
int c3;
f32 sx;
f32 sy;
f32 bx;
f32 by;
    fr = t->m38;
    h = fn_800CB0FC(-1, 1.0f);
    sx = 0.0f; sy = sx; bx = sx; by = sx;
    if (t->m3c > 0) {
        f32 a = fn_8017F68C(0, 0.0f, 2.0f * t->m3c, ++t->m3a, t->m3c);
        if (t->m44 == 0) {
            sx = t->m40 * (3.0f * (f32)fn_80295940(a));
            sy = t->m40 * (2.0f * (f32)fn_80295534(a));
        } else {
            bx = t->m40 * (3.0f * (f32)fn_80295940(a));
            by = t->m40 * (2.0f * (f32)fn_80295534(a));
        }
        if (t->m3c <= t->m3a) t->m3c = 0;
    }
    fn_8007E154();
    fn_8007E4E4(t->x + sx, t->y + sy, t->m34, 1.0f);
    fn_8007E164();
    ox = (s16)(t->m39 == 0 ? 0 : 0x1A);
    oy = (s16)(t->m39 == 0 ? 0 : 0x2E);
    e1 = t->m39 == 0 ? 0x40 : 0x60;
    e2 = t->m39 == 0 ? 0x50 : 0x90;
    a1 = t->m39 == 0 ? 0xB : 6;
    c1 = t->m39 == 0 ? 0xF : 8;
    fn_8007E154();
    fn_8007E374(t->m64, a1 + fr, 0x11);
    fn_8007E7DC(t->m36);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080430(0.0f, 0.0f, 0.0f, 0.0f, e1, e2);
    fn_80080578(0);
    fn_80080308();
    fn_8007E154();
    fn_8007E720(-0.1f);
    fn_8007E374(t->m64, c1 + fr, 0x11);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080430(0.0f, 0.0f, 0.0f, 0.0f, e1, e2);
    fn_80080578(0);
    fn_80080308();
    a2 = t->m39 == 0 ? 0xA : 5;
    b2 = t->m39 == 0 ? 0xE8 : 0x130;
    c2 = t->m39 == 0 ? 0x50 : 0xA0;
    fn_8007E154();
    fn_8007E720(-0.1f);
    fn_8007E374(t->m64, a2, 0x11);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080430(0.0f, 0.0f, 0.0f, 0.0f, b2, c2);
    fn_80080578(0);
    fn_80080308();
    fn_8007E154();
    fn_8007E720(-0.1f);
    fn_8007E164();
    if (t->m60 != NULL) {
        int px = t->m39 == 0 ? 0x42 : 0x48;
        int py = t->m39 == 0 ? 0x42 : 0x44;
        int fl = 0;
        if (t->m48->m446 != 0 && t->m4c > 0) fl = 1;
        ay = py + oy;
        ax = px + ox;
        e3 = ay - h;
        fn_80108080(t->m60, ax, e3, fl);
        fn_80108064(t->m60, 1, ax, e3);
        tk = OSGetTime() / (BUS / 4 / 1000) % 500;
        if (tk <= 200) {
            w = fn_8017F68C(4, 0.0f, 4.0f, tk, 200.0f);
            c3 = (int)fn_8017F68C(4, 128.0f, 255.0f, tk, 200.0f);
        } else {
            w = fn_8017F68C(4, 4.0f, 0.0f, tk - 200, 300.0f);
            c3 = (int)fn_8017F68C(4, 255.0f, 128.0f, tk - 200, 300.0f);
        }
        s16 dir = t->m48->m476;
        e4 = (s16)((h - 0x10 >> 1) + 0x10);
        if (dir > 0) {
            fn_8007E154();
            fn_8007E374(t->m64, 0x1A, 0x11);
            fn_8007E164();
            fn_8007E154();
            fn_8007E720(-0.1f);
            fn_8007E164();
            fn_800800D4(1);
            fn_80080430((s16)(ax + 10), (s16)(int)((f32)(ay - e4) - w - 2.0f), 0.0f, 0.0f, 16.0f, 16.0f);
            fn_800804F4((u8)c3);
            fn_80080578(0);
            fn_80080308();
            fn_8007E154();
            fn_8007E720(0.1f);
            fn_8007E164();
        } else if (dir < 0) {
            fn_8007E154();
            fn_8007E720(-0.1f);
            fn_8007E164();
            fn_8007E154();
            fn_8007E374(t->m64, 0x1B, 0x11);
            fn_8007E164();
            fn_800800D4(1);
            fn_80080430((s16)(ax + 10), (s16)(int)(2.0f + (w + (f32)(ay - e4))), 0.0f, 0.0f, 16.0f, 16.0f);
            fn_800804F4((u8)c3);
            fn_80080578(0);
            fn_80080308();
            fn_8007E154();
            fn_8007E720(0.1f);
            fn_8007E164();
        }
    }
    c4 = t->m39 == 0 ? 0x1F : 0x26;
    d4 = t->m39 == 0 ? 0x1A : 0x42;
    b4 = t->m39 == 0 ? 0x33 : 0x45;
    a4 = t->m39 == 0 ? 0x2E : 0x5E;
    if (++t->m54 > t->m58) t->m54 = t->m58;
    if (t->m54 == 0) f5 = t->m50;
    else if (t->m54 == t->m58) f5 = t->m52;
    else f5 = (int)fn_8017F68C(0, t->m50, t->m52, t->m54, t->m58);
    fn_800C14F0(t, ox + 0x36, oy + 0x29);
    fn_8007E154();
    fn_8007E374(t->m64, 0x17, 0x11);
    fn_8007E164();
    fn_80176B54((int)(c4 + bx), (int)(d4 + by), 2, fn_800CD204(1), 0, 0, 0x11, 0x17, 0xF, (s16)f5);
    fn_8007E154();
    fn_8007E374(t->m64, 0x18, 0x11);
    fn_8007E164();
    fn_80176B54(b4, a4, 2, fn_800CD204(4), 0, 0, 0xB, 0xF, 8, t->m5c);
}
}
