#include "game/rG_800A3D88/types.h"
// Title slide 2, second layout: score panels drawn with the Prim2D helpers.
extern "C" {
struct Col { u8 r, g, b, a; };
struct Title2 {
    u8 pad[0x30];
    s16 m30;
    u8 m32, m33;
    void* m34;
    void* m38;
    s8 m3c, m3d;
    s16 m3e, m40, m42, m44, m46, m48, m4a, m4c;
    u8 pad4e[2];
    void* m50;
};
extern char lbl_80365D94[];
extern int lbl_804CA468;
extern int lbl_804CA46C;
extern int lbl_804CA470;
extern int lbl_804CA474;
void fn_8007E154();
void fn_8007E164();
#if TARGET_PC
FE10_PROTO void fn_8007E174(p32arg, int);
#else
void fn_8007E174(int, int);
#endif
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
void fn_80080494();
void fn_80080508(Col*);
void fn_80080578(int);
int fn_800CB0FC(int, f32);
void fn_80176B54(int, int, int, const Col*, int, int, int, int, int, int);
void fn_80176EA8(int, int, int, const char*);
static inline const int& Max(const int& a, const int& b) { return a < b ? b : a; }
static inline void Cp(Col* d, Col s) { *d = s; }
static const Col K0 = {0x7D, 0x85, 0x8A, 0xFF};
static inline void Pan(Title2* t, Col c, int m3e, int m42, int m40, int m44, int m46, int m48, int m4a, int m4c) {
    Col x6, x5, x4; int d2; Col x3, x2, x1; int d1;
    fn_8007E154();
    fn_8007E4E4(0.0f, 102.0f, t->m30, 1.0f);
    fn_8007E7DC(t->m32);
    fn_8007E164();
    fn_8007E154();
    fn_8007E374(t->m50, 0x1D, 0x11);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080430(0.0f, 0.0f, 0.0f, 0.0f, 240.0f, 64.0f);
    fn_80080578(0);
    fn_80080494();
    fn_80080308();
    fn_8007E154();
    fn_8007E374(t->m50, 0x1C, 0x11);
    fn_8007E720(-1.0f);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080430(32.0f, 4.0f, 0.0f, 0.0f, 40.0f, 64.0f);
    fn_80080578(0);
    fn_80080308();
    if (t->m3c > 0) {
        fn_8007E154();
        fn_8007E374(t->m50, 0x19, 0x11);
        fn_8007E164();
        int k = 10;
        fn_80176B54(0x59, 3, 2, &c, 0, 0, 0xB, 0x10, k, m46);
        d1 = m3e - m44;
        fn_80176B54(0x59, 0x17, 2, &c, 0, 0, 0xB, 0x10, k, Max(lbl_804CA470, d1));
        fn_80176B54(0x59, 0x2B, 2, &c, 0, 0, 0xB, 0x10, 10, m4a);
    } else {
        fn_8007E154();
        fn_8007E174(0, 0x13);
        fn_8007E164();
        fn_800800D4(5);
        *(u32*)&x1 = *(u32*)&c;
        fn_80080508(&x1);
        fn_80176EA8(0x59, 0, 2, lbl_80365D94);
        fn_80080308();
        fn_800800D4(5);
        *(u32*)&x2 = *(u32*)&c;
        fn_80080508(&x2);
        fn_80176EA8(0x59, 0x14, 2, lbl_80365D94);
        fn_80080308();
        fn_800800D4(5);
        *(u32*)&x3 = *(u32*)&c;
        fn_80080508(&x3);
        fn_80176EA8(0x59, 0x29, 2, lbl_80365D94);
        fn_80080308();
    }
    fn_8007E154();
    fn_8007E4E4(368.0f, 258.0f, t->m30, 1.0f);
    fn_8007E7DC(t->m32);
    fn_8007E164();
    fn_8007E154();
    fn_8007E374(t->m50, 0x1D, 0x11);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080430(0.0f, 0.0f, 0.0f, 0.0f, 240.0f, 64.0f);
    fn_80080578(0);
    fn_80080308();
    fn_8007E154();
    fn_8007E374(t->m50, 0x1C, 0x11);
    fn_8007E720(-1.0f);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080430(141.0f, 3.0f, 0.0f, 0.0f, 40.0f, 64.0f);
    fn_80080578(0);
    fn_80080308();
    if (t->m3d > 0) {
        fn_8007E154();
        fn_8007E374(t->m50, 0x19, 0x11);
        fn_8007E164();
        int k = 10;
        fn_80176B54(0xC6, 3, 2, &c, 0, 0, 0xB, 0x10, k, m48);
        d2 = m40 - m42;
        fn_80176B54(0xC6, 0x17, 2, &c, 0, 0, 0xB, 0x10, k, Max(lbl_804CA474, d2));
        fn_80176B54(0xC6, 0x2B, 2, &c, 0, 0, 0xB, 0x10, 10, m4c);
    } else {
        fn_8007E154();
        fn_8007E174(0, 0x13);
        fn_8007E164();
        fn_800800D4(5);
        *(u32*)&x4 = *(u32*)&c;
        fn_80080508(&x4);
        fn_80176EA8(0xC6, 0, 2, lbl_80365D94);
        fn_80080308();
        fn_800800D4(5);
        *(u32*)&x5 = *(u32*)&c;
        fn_80080508(&x5);
        fn_80176EA8(0xC6, 0x14, 2, lbl_80365D94);
        fn_80080308();
        fn_800800D4(5);
        *(u32*)&x6 = *(u32*)&c;
        fn_80080508(&x6);
        fn_80176EA8(0xC6, 0x29, 2, lbl_80365D94);
        fn_80080308();
    }
}
void fn_800C283C(Title2* t) {
    int m3e, m42, m40, m44, m46, m48, m4a, m4c;
    m3e = t->m3e;
    m42 = t->m42;
    m40 = t->m40;
    m44 = t->m44;
    m46 = t->m46;
    m48 = t->m48;
    m4a = t->m4a;
    m4c = t->m4c;
    Pan(t, K0, m3e, m42, m40, m44, m46, m48, m4a, m4c);
}
}
