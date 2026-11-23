#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off
typedef GXColor C4;
typedef struct Pn { u8 pad[0x34]; C4* pal; int x, y, w, h; } Pn;
extern "C" {
extern void fn_8007E154(void);
extern void fn_8007E164(void);
#if TARGET_PC
extern FE10_PROTO void fn_8007E174(p32arg, int);
#else
extern void fn_8007E174(int, int);
#endif
extern void fn_8007E4E4(f32, f32, f32, f32);
extern int fn_8028DB44(int);
extern void fn_800800D4(int);
extern void fn_80080388(f32, f32, f32, f32);
extern void fn_80080578(int);
extern void fn_80080308(void);
extern void fn_80080508(C4*);
extern void fn_80080940(C4*, C4*, C4*, C4*);
extern u32 fn_8017FA1C(void);
static inline C4 Col(const C4& s) { C4 c; c.r = s.r; c.g = s.g; c.b = s.b; c.a = s.a; return c; }
static inline C4 Col1(const C4& s) { return Col(s); }
static inline C4 Col2(const C4& s) { return Col1(s); }
static inline C4 Col3(const C4& s) { return Col2(s); }
static inline C4 Col4(const C4& s) { return Col3(s); }
#define IDX(k) p->pal[((k) - fn_8017FA1C()) & 0x1F]
static inline C4 Fz(Pn* p, int k) { return Col4(IDX(k)); }
#define GD(name,C,a1,a2,a3,a4) static inline void name(Pn* p, int c) { C4 d = C(IDX(a1)); C4 k = C(IDX(a2)); C4 b = C(IDX(a3)); C4 a = C(IDX(a4)); fn_80080940(&a, &b, &k, &d); }
GD(G0101,Col3,c,c + 1,c,c + 1)
GD(H10101,Col2,c,c + 1,c,c + 1)
GD(H20101,Col1,c,c + 1,c,c + 1)
GD(H30101,Col,c,c + 1,c,c + 1)
static inline void W10101(Pn* p, int c) { H10101(p, c); }
static inline void Y10101(Pn* p, int c) { H20101(p, c); }
static inline void W20101(Pn* p, int c) { Y10101(p, c); }
static inline void Z10101(Pn* p, int c) { H30101(p, c); }
static inline void Z20101(Pn* p, int c) { Z10101(p, c); }
static inline void W30101(Pn* p, int c) { Z20101(p, c); }
GD(G1010,Col3,c + 1,c,c + 1,c)
GD(H11010,Col2,c + 1,c,c + 1,c)
GD(H21010,Col1,c + 1,c,c + 1,c)
GD(H31010,Col,c + 1,c,c + 1,c)
static inline void W11010(Pn* p, int c) { H11010(p, c); }
static inline void Y11010(Pn* p, int c) { H21010(p, c); }
static inline void W21010(Pn* p, int c) { Y11010(p, c); }
static inline void Z11010(Pn* p, int c) { H31010(p, c); }
static inline void Z21010(Pn* p, int c) { Z11010(p, c); }
static inline void W31010(Pn* p, int c) { Z21010(p, c); }
GD(G0011,Col3,c,c,c + 1,c + 1)
GD(H10011,Col2,c,c,c + 1,c + 1)
GD(H20011,Col1,c,c,c + 1,c + 1)
GD(H30011,Col,c,c,c + 1,c + 1)
static inline void W10011(Pn* p, int c) { H10011(p, c); }
static inline void Y10011(Pn* p, int c) { H20011(p, c); }
static inline void W20011(Pn* p, int c) { Y10011(p, c); }
static inline void Z10011(Pn* p, int c) { H30011(p, c); }
static inline void Z20011(Pn* p, int c) { Z10011(p, c); }
static inline void W30011(Pn* p, int c) { Z20011(p, c); }
GD(G1100,Col3,c + 1,c + 1,c,c)
GD(H11100,Col2,c + 1,c + 1,c,c)
GD(H21100,Col1,c + 1,c + 1,c,c)
GD(H31100,Col,c + 1,c + 1,c,c)
static inline void W11100(Pn* p, int c) { H11100(p, c); }
static inline void Y11100(Pn* p, int c) { H21100(p, c); }
static inline void W21100(Pn* p, int c) { Y11100(p, c); }
static inline void Z11100(Pn* p, int c) { H31100(p, c); }
static inline void Z21100(Pn* p, int c) { Z11100(p, c); }
static inline void W31100(Pn* p, int c) { Z21100(p, c); }
static inline int RN(void) { return fn_8028DB44(15); }
#pragma inline_max_size(4000)
static inline void body(Pn* p) {
    /*P*/
    int y;
    f32 x0;
    f32 y0;
    f32 x1;
    f32 pos1;
    f32 pos2;
    f32 pos4;
    f32 step1;
    f32 step2;
    f32 step3;
    f32 step4;
    f32 pos3;
    int x;
    f32 y1;
    int n;
    int i1;
    int i2;
    int i3;
    int c4;
    int i4;
    int c1;
    int c2;
    int c3;
/*E*/
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 20.0f, 1.0f);
    fn_8007E174(0, 0);
    fn_8007E164();
    x = p->x;
    y = p->y;
    x0 = x;
    y0 = y;
    x1 = x + p->w;
    y1 = y + p->h;
    pos1 = 2.0f + x0;
    n = RN();
    step1 = (x1 - pos1) / (f32)n;
    for (i1 = 0; i1 < n; i1++) {
        c1 = i1 + 1;
        fn_800800D4(3);
        if (step1 >= 0.0f) {
            fn_80080388(pos1, y0, step1, 2.0f);
            W31010(p, c1);
        } else {
            fn_80080388(pos1 + step1, y0, -step1, 2.0f);
            W30101(p, c1);
        }
        fn_80080578(0);
        fn_80080308();
        pos1 += step1;
    }
    pos2 = 2.0f + y0;
    step2 = (y1 - pos2) / (f32)n;
    for (i2 = 0; i2 < n; i2++) {
        c2 = i2 + 0x11;
        fn_800800D4(3);
        if (step2 >= 0.0f) {
            fn_80080388(x1, pos2, 2.0f, step2);
            W21100(p, c2);
        } else {
            fn_80080388(x1, pos2 + step2, 2.0f, -step2);
            W20011(p, c2);
        }
        fn_80080578(0);
        fn_80080308();
        pos2 += step2;
    }
    pos3 = x1;
    step3 = ((2.0f + x0) - pos3) / (f32)n;
    for (i3 = 0; i3 < n; i3++) {
        c3 = i3 + 1;
        fn_800800D4(3);
        if (step3 >= 0.0f) {
            fn_80080388(pos3, y1, step3, 2.0f);
            W11010(p, c3);
        } else {
            fn_80080388(pos3 + step3, y1, -step3, 2.0f);
            W10101(p, c3);
        }
        fn_80080578(0);
        fn_80080308();
        pos3 += step3;
    }
    pos4 = y1;
    step4 = ((2.0f + y0) - pos4) / (f32)n;
    for (i4 = 0; i4 < n; i4++) {
        c4 = i4 + 0x11;
        fn_800800D4(3);
        if (step4 >= 0.0f) {
            fn_80080388(x0, pos4, 2.0f, step4);
            G1100(p, c4);
        } else {
            fn_80080388(x0, pos4 + step4, 2.0f, -step4);
            G0011(p, c4);
        }
        fn_80080578(0);
        fn_80080308();
        pos4 += step4;
    }
    fn_800800D4(1);
    fn_80080388(1.0f + x0, 1.0f + y0, 2.0f, 2.0f);
    { C4 a = Fz(p, 0); fn_80080508(&a); }
    fn_80080308();
    fn_800800D4(1);
    fn_80080388(x1 - 1.0f, 1.0f + y0, 2.0f, 2.0f);
    { C4 a = Fz(p, 0x10); fn_80080508(&a); }
    fn_80080308();
    fn_800800D4(1);
    fn_80080388(x1 - 1.0f, y1 - 1.0f, 2.0f, 2.0f);
    { C4 a = Fz(p, 0); fn_80080508(&a); }
    fn_80080308();
    fn_800800D4(1);
    fn_80080388(1.0f + x0, y1 - 1.0f, 2.0f, 2.0f);
    { C4 a = Fz(p, 0x10); fn_80080508(&a); }
    fn_80080308();
}
void fn_80035604(Pn* p) { body(p); }
}
