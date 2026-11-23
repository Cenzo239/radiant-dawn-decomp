#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off
#pragma inline_depth(30)
#pragma inline_max_size(8000)
#pragma inline_max_total_size(100000)
typedef GXColor C4;
typedef struct Pn { u8 pad[0x34]; C4* pal; int x, y, w1, w2, h1, h2; u8 mode; } Pn;
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
extern void fn_80080940(C4*, C4*, C4*, C4*);
extern u32 fn_8017FA1C(void);
static inline C4 Col0(const C4& s) { C4 c; c.r = s.r; c.g = s.g; c.b = s.b; c.a = s.a; return c; }
#define IDX(k) p->pal[((k) - fn_8017FA1C()) & 0x1F]
#define WRAP(a, b) static inline void a(Pn* p, int c) { b(p, c); }
#define GD(name, C, a1, a2, a3, a4) static inline void name(Pn* p, int c) { C4 d = C(IDX(a1)); C4 k = C(IDX(a2)); C4 b = C(IDX(a3)); C4 a = C(IDX(a4)); fn_80080940(&a, &b, &k, &d); }
static inline C4 Col1(const C4& s) { return Col0(s); }
static inline C4 Col2(const C4& s) { return Col1(s); }
static inline C4 Col3(const C4& s) { return Col2(s); }
static inline C4 Col4(const C4& s) { return Col3(s); }
static inline C4 Col5(const C4& s) { return Col4(s); }
static inline C4 Col6(const C4& s) { return Col5(s); }
static inline C4 Col7(const C4& s) { return Col6(s); }
static inline C4 Col8(const C4& s) { return Col7(s); }
static inline C4 Col9(const C4& s) { return Col8(s); }
static inline C4 Col10(const C4& s) { return Col9(s); }
static inline C4 Col11(const C4& s) { return Col10(s); }
GD(H0_1, Col0, c + 1, c, c + 1, c)
WRAP(H0_1_1, H0_1)
WRAP(H0_1_2, H0_1_1)
WRAP(H0_1_3, H0_1_2)
WRAP(H0_1_4, H0_1_3)
WRAP(H0_1_5, H0_1_4)
WRAP(H0_1_6, H0_1_5)
WRAP(H0_1_7, H0_1_6)
WRAP(H0_1_8, H0_1_7)
WRAP(H0_1_9, H0_1_8)
WRAP(H0_1_10, H0_1_9)
WRAP(H0_1_11, H0_1_10)
GD(H1_1, Col0, c, c + 1, c, c + 1)
WRAP(H1_1_1, H1_1)
WRAP(H1_1_2, H1_1_1)
WRAP(H1_1_3, H1_1_2)
WRAP(H1_1_4, H1_1_3)
WRAP(H1_1_5, H1_1_4)
WRAP(H1_1_6, H1_1_5)
WRAP(H1_1_7, H1_1_6)
WRAP(H1_1_8, H1_1_7)
WRAP(H1_1_9, H1_1_8)
WRAP(H1_1_10, H1_1_9)
WRAP(H1_1_11, H1_1_10)
GD(V0_2, Col1, c + 1, c + 1, c, c)
WRAP(V0_2_1, V0_2)
WRAP(V0_2_2, V0_2_1)
WRAP(V0_2_3, V0_2_2)
WRAP(V0_2_4, V0_2_3)
WRAP(V0_2_5, V0_2_4)
WRAP(V0_2_6, V0_2_5)
WRAP(V0_2_7, V0_2_6)
WRAP(V0_2_8, V0_2_7)
WRAP(V0_2_9, V0_2_8)
WRAP(V0_2_10, V0_2_9)
GD(V1_2, Col1, c, c, c + 1, c + 1)
WRAP(V1_2_1, V1_2)
WRAP(V1_2_2, V1_2_1)
WRAP(V1_2_3, V1_2_2)
WRAP(V1_2_4, V1_2_3)
WRAP(V1_2_5, V1_2_4)
WRAP(V1_2_6, V1_2_5)
WRAP(V1_2_7, V1_2_6)
WRAP(V1_2_8, V1_2_7)
WRAP(V1_2_9, V1_2_8)
WRAP(V1_2_10, V1_2_9)
GD(H0_3, Col2, c + 1, c, c + 1, c)
WRAP(H0_3_1, H0_3)
WRAP(H0_3_2, H0_3_1)
WRAP(H0_3_3, H0_3_2)
WRAP(H0_3_4, H0_3_3)
WRAP(H0_3_5, H0_3_4)
WRAP(H0_3_6, H0_3_5)
WRAP(H0_3_7, H0_3_6)
WRAP(H0_3_8, H0_3_7)
WRAP(H0_3_9, H0_3_8)
GD(H1_3, Col2, c, c + 1, c, c + 1)
WRAP(H1_3_1, H1_3)
WRAP(H1_3_2, H1_3_1)
WRAP(H1_3_3, H1_3_2)
WRAP(H1_3_4, H1_3_3)
WRAP(H1_3_5, H1_3_4)
WRAP(H1_3_6, H1_3_5)
WRAP(H1_3_7, H1_3_6)
WRAP(H1_3_8, H1_3_7)
WRAP(H1_3_9, H1_3_8)
GD(V0_4, Col3, c + 1, c + 1, c, c)
WRAP(V0_4_1, V0_4)
WRAP(V0_4_2, V0_4_1)
WRAP(V0_4_3, V0_4_2)
WRAP(V0_4_4, V0_4_3)
WRAP(V0_4_5, V0_4_4)
WRAP(V0_4_6, V0_4_5)
WRAP(V0_4_7, V0_4_6)
WRAP(V0_4_8, V0_4_7)
GD(V1_4, Col3, c, c, c + 1, c + 1)
WRAP(V1_4_1, V1_4)
WRAP(V1_4_2, V1_4_1)
WRAP(V1_4_3, V1_4_2)
WRAP(V1_4_4, V1_4_3)
WRAP(V1_4_5, V1_4_4)
WRAP(V1_4_6, V1_4_5)
WRAP(V1_4_7, V1_4_6)
WRAP(V1_4_8, V1_4_7)
GD(H0_5, Col4, c + 1, c, c + 1, c)
WRAP(H0_5_1, H0_5)
WRAP(H0_5_2, H0_5_1)
WRAP(H0_5_3, H0_5_2)
WRAP(H0_5_4, H0_5_3)
WRAP(H0_5_5, H0_5_4)
WRAP(H0_5_6, H0_5_5)
WRAP(H0_5_7, H0_5_6)
GD(H1_5, Col4, c, c + 1, c, c + 1)
WRAP(H1_5_1, H1_5)
WRAP(H1_5_2, H1_5_1)
WRAP(H1_5_3, H1_5_2)
WRAP(H1_5_4, H1_5_3)
WRAP(H1_5_5, H1_5_4)
WRAP(H1_5_6, H1_5_5)
WRAP(H1_5_7, H1_5_6)
GD(V0_6, Col5, c + 1, c + 1, c, c)
WRAP(V0_6_1, V0_6)
WRAP(V0_6_2, V0_6_1)
WRAP(V0_6_3, V0_6_2)
WRAP(V0_6_4, V0_6_3)
WRAP(V0_6_5, V0_6_4)
WRAP(V0_6_6, V0_6_5)
GD(V1_6, Col5, c, c, c + 1, c + 1)
WRAP(V1_6_1, V1_6)
WRAP(V1_6_2, V1_6_1)
WRAP(V1_6_3, V1_6_2)
WRAP(V1_6_4, V1_6_3)
WRAP(V1_6_5, V1_6_4)
WRAP(V1_6_6, V1_6_5)
GD(H0_7, Col6, c + 1, c, c + 1, c)
WRAP(H0_7_1, H0_7)
WRAP(H0_7_2, H0_7_1)
WRAP(H0_7_3, H0_7_2)
WRAP(H0_7_4, H0_7_3)
WRAP(H0_7_5, H0_7_4)
GD(H1_7, Col6, c, c + 1, c, c + 1)
WRAP(H1_7_1, H1_7)
WRAP(H1_7_2, H1_7_1)
WRAP(H1_7_3, H1_7_2)
WRAP(H1_7_4, H1_7_3)
WRAP(H1_7_5, H1_7_4)
GD(V0_8, Col7, c + 1, c + 1, c, c)
WRAP(V0_8_1, V0_8)
WRAP(V0_8_2, V0_8_1)
WRAP(V0_8_3, V0_8_2)
WRAP(V0_8_4, V0_8_3)
GD(V1_8, Col7, c, c, c + 1, c + 1)
WRAP(V1_8_1, V1_8)
WRAP(V1_8_2, V1_8_1)
WRAP(V1_8_3, V1_8_2)
WRAP(V1_8_4, V1_8_3)
GD(H0_9, Col8, c + 1, c, c + 1, c)
WRAP(H0_9_1, H0_9)
WRAP(H0_9_2, H0_9_1)
WRAP(H0_9_3, H0_9_2)
GD(H1_9, Col8, c, c + 1, c, c + 1)
WRAP(H1_9_1, H1_9)
WRAP(H1_9_2, H1_9_1)
WRAP(H1_9_3, H1_9_2)
GD(V0_10, Col9, c + 1, c + 1, c, c)
WRAP(V0_10_1, V0_10)
WRAP(V0_10_2, V0_10_1)
GD(V1_10, Col9, c, c, c + 1, c + 1)
WRAP(V1_10_1, V1_10)
WRAP(V1_10_2, V1_10_1)
GD(H0_11, Col10, c + 1, c, c + 1, c)
WRAP(H0_11_1, H0_11)
GD(H1_11, Col10, c, c + 1, c, c + 1)
WRAP(H1_11_1, H1_11)
GD(V0_12, Col11, c + 1, c + 1, c, c)
GD(V1_12, Col11, c, c, c + 1, c + 1)
#pragma inline_max_size(8000)
static inline void body(Pn* p) {
    /*P*/
    f32 end1;
    f32 end2;
    f32 end3;
    f32 end4;
    f32 end5;
    f32 end6;
    f32 end7;
    f32 end8;
    f32 end9;
    f32 end10;
    f32 end11;
    f32 end12;
    f32 pos12;
    f32 step1;
    f32 step2;
    f32 step3;
    f32 step4;
    f32 step5;
    f32 step6;
    f32 step7;
    f32 step8;
    f32 step9;
    f32 step10;
    f32 step11;
    f32 fix1;
    f32 fix2;
    f32 fix3;
    f32 fix4;
    f32 fix5;
    f32 fix6;
    f32 fix7;
    f32 fix8;
    f32 fix9;
    f32 fix10;
    f32 fix11;
    f32 fix12;
    f32 step12;
    f32 pos1;
    f32 pos2;
    f32 pos3;
    f32 pos4;
    f32 pos5;
    f32 pos6;
    f32 pos7;
    f32 pos8;
    f32 pos9;
    f32 pos10;
    f32 pos11;
    int c11;
    int i1;
    int i2;
    int i3;
    int i4;
    int i5;
    int i6;
    int i7;
    int i8;
    int i9;
    int i10;
    int i12;
    int c12;
    int i11;
    int c2;
    int c3;
    int c4;
    int c6;
    int c8;
    int c10;
    int n1;
    int n2;
    int n3;
    int n4;
    int n5;
    int n6;
/*E*/
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 20.0f, 1.0f);
    fn_8007E174(0, 0);
    fn_8007E164();
    if (p->mode) {
    fix1 = p->y;
    end1 = p->x + p->w1;
    pos1 = p->x;
    n1 = fn_8028DB44(5);
    step1 = (end1 - pos1) / (f32)n1;
    for (i1 = 0; i1 < n1; i1++) {
        fn_800800D4(3);
        if (step1 >= 0.0f) {
            fn_80080388(pos1, fix1, step1, 2.0f);
            H0_1_11(p, i1);
        } else {
            fn_80080388(pos1 + step1, fix1, -step1, 2.0f);
            H1_1_11(p, i1);
        }
        fn_80080578(0);
        fn_80080308();
        pos1 += step1;
    }
    fix2 = p->x + p->w1;
    end2 = p->y + p->h1;
    pos2 = p->y;
    n2 = fn_8028DB44(0xb);
    step2 = (end2 - pos2) / (f32)n2;
    for (i2 = 0; i2 < n2; i2++) {
        c2 = i2 + 5;
        fn_800800D4(3);
        if (step2 >= 0.0f) {
            fn_80080388(fix2, pos2, 2.0f, step2);
            V0_2_10(p, c2);
        } else {
            fn_80080388(fix2, pos2 + step2, 2.0f, -step2);
            V1_2_10(p, c2);
        }
        fn_80080578(0);
        fn_80080308();
        pos2 += step2;
    }
    fix3 = p->y + p->h1;
    end3 = p->w2 + (p->x + p->w1);
    pos3 = p->x + p->w1;
    step3 = (end3 - pos3) / (f32)n2;
    for (i3 = 0; i3 < n2; i3++) {
        c3 = i3 + 16;
        fn_800800D4(3);
        if (step3 >= 0.0f) {
            fn_80080388(pos3, fix3, step3, 2.0f);
            H0_3_9(p, c3);
        } else {
            fn_80080388(pos3 + step3, fix3, -step3, 2.0f);
            H1_3_9(p, c3);
        }
        fn_80080578(0);
        fn_80080308();
        pos3 += step3;
    }
    fix4 = p->w2 + (p->x + p->w1);
    end4 = p->h2 + (p->y + p->h1);
    pos4 = p->y + p->h1;
    step4 = (end4 - pos4) / (f32)n1;
    for (i4 = 0; i4 < n1; i4++) {
        c4 = i4 + 27;
        fn_800800D4(3);
        if (step4 >= 0.0f) {
            fn_80080388(fix4, pos4, 2.0f, step4);
            V0_4_8(p, c4);
        } else {
            fn_80080388(fix4, pos4 + step4, 2.0f, -step4);
            V1_4_8(p, c4);
        }
        fn_80080578(0);
        fn_80080308();
        pos4 += step4;
    }
    fix5 = p->h2 + (p->y + p->h1);
    end5 = p->x;
    pos5 = p->w2 + (p->x + p->w1);
    n3 = fn_8028DB44(0x10);
    step5 = (end5 - pos5) / (f32)n3;
    for (i5 = 0; i5 < n3; i5++) {
        fn_800800D4(3);
        if (step5 >= 0.0f) {
            fn_80080388(pos5, fix5, step5, 2.0f);
            H0_5_7(p, i5);
        } else {
            fn_80080388(pos5 + step5, fix5, -step5, 2.0f);
            H1_5_7(p, i5);
        }
        fn_80080578(0);
        fn_80080308();
        pos5 += step5;
    }
    fix6 = p->x;
    end6 = p->y;
    pos6 = p->h2 + (p->y + p->h1);
    step6 = (end6 - pos6) / (f32)n3;
    for (i6 = 0; i6 < n3; i6++) {
        c6 = i6 + 16;
        fn_800800D4(3);
        if (step6 >= 0.0f) {
            fn_80080388(fix6, pos6, 2.0f, step6);
            V0_6_6(p, c6);
        } else {
            fn_80080388(fix6, pos6 + step6, 2.0f, -step6);
            V1_6_6(p, c6);
        }
        fn_80080578(0);
        fn_80080308();
        pos6 += step6;
    }
    } else {
    fix7 = p->y;
    end7 = p->w2 + (p->x + p->w1);
    pos7 = p->x;
    n4 = fn_8028DB44(0x10);
    step7 = (end7 - pos7) / (f32)n4;
    for (i7 = 0; i7 < n4; i7++) {
        fn_800800D4(3);
        if (step7 >= 0.0f) {
            fn_80080388(pos7, fix7, step7, 2.0f);
            H0_7_5(p, i7);
        } else {
            fn_80080388(pos7 + step7, fix7, -step7, 2.0f);
            H1_7_5(p, i7);
        }
        fn_80080578(0);
        fn_80080308();
        pos7 += step7;
    }
    fix8 = p->w2 + (p->x + p->w1);
    end8 = p->h2 + (p->y + p->h1);
    pos8 = p->y;
    step8 = (end8 - pos8) / (f32)n4;
    for (i8 = 0; i8 < n4; i8++) {
        c8 = i8 + 16;
        fn_800800D4(3);
        if (step8 >= 0.0f) {
            fn_80080388(fix8, pos8, 2.0f, step8);
            V0_8_4(p, c8);
        } else {
            fn_80080388(fix8, pos8 + step8, 2.0f, -step8);
            V1_8_4(p, c8);
        }
        fn_80080578(0);
        fn_80080308();
        pos8 += step8;
    }
    fix9 = p->h2 + (p->y + p->h1);
    end9 = p->x + p->w1;
    pos9 = p->w2 + (p->x + p->w1);
    n5 = fn_8028DB44(5);
    step9 = (end9 - pos9) / (f32)n5;
    for (i9 = 0; i9 < n5; i9++) {
        fn_800800D4(3);
        if (step9 >= 0.0f) {
            fn_80080388(pos9, fix9, step9, 2.0f);
            H0_9_3(p, i9);
        } else {
            fn_80080388(pos9 + step9, fix9, -step9, 2.0f);
            H1_9_3(p, i9);
        }
        fn_80080578(0);
        fn_80080308();
        pos9 += step9;
    }
    fix10 = p->x + p->w1;
    end10 = p->y + p->h1;
    pos10 = p->h2 + (p->y + p->h1);
    n6 = fn_8028DB44(0xb);
    step10 = (end10 - pos10) / (f32)n6;
    for (i10 = 0; i10 < n6; i10++) {
        c10 = i10 + 5;
        fn_800800D4(3);
        if (step10 >= 0.0f) {
            fn_80080388(fix10, pos10, 2.0f, step10);
            V0_10_2(p, c10);
        } else {
            fn_80080388(fix10, pos10 + step10, 2.0f, -step10);
            V1_10_2(p, c10);
        }
        fn_80080578(0);
        fn_80080308();
        pos10 += step10;
    }
    fix11 = p->y + p->h1;
    end11 = p->x;
    pos11 = p->x + p->w1;
    step11 = (end11 - pos11) / (f32)n6;
    for (i11 = 0; i11 < n6; i11++) {
        c11 = i11 + 16;
        fn_800800D4(3);
        if (step11 >= 0.0f) {
            fn_80080388(pos11, fix11, step11, 2.0f);
            H0_11_1(p, c11);
        } else {
            fn_80080388(pos11 + step11, fix11, -step11, 2.0f);
            H1_11_1(p, c11);
        }
        fn_80080578(0);
        fn_80080308();
        pos11 += step11;
    }
    fix12 = p->x;
    end12 = p->y;
    pos12 = p->y + p->h1;
    step12 = (end12 - pos12) / (f32)n5;
    for (i12 = 0; i12 < n5; i12++) {
        c12 = i12 + 27;
        fn_800800D4(3);
        if (step12 >= 0.0f) {
            fn_80080388(fix12, pos12, 2.0f, step12);
            V0_12(p, c12);
        } else {
            fn_80080388(fix12, pos12 + step12, 2.0f, -step12);
            V1_12(p, c12);
        }
        fn_80080578(0);
        fn_80080308();
        pos12 += step12;
    }
    }
}
void fn_80036914(Pn* p) { body(p); }
}
