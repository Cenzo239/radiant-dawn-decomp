/* r20: `sched` (check_regs.py). Staff roll draw. Changes against the wip draft:
   - in the banner branch `xa = 0` comes first and ONE zero colour word `W z` (declared right after it) is shared by
     both gradient calls; the compiler then keeps a single zero register for xa and the colour words, as the original
     does (the draft had two block-scoped zeros and one `li` too many);
   - the second line of a two-line left column is `(s16)(y + 0x14)`, the centred one `(s16)y + 0x14` (the draft had
     the two casts the other way round).
   k0/k1/k2 hold the bytes of lbl_804D0B20+0/+4/+8 (000000FF, 000000FF, FFFFFFFF).
   Moved instruction (dd.py -u): one `extsh r5,r0` of the y argument against one `lfs f2` before fn_800CB520. */
/* Staff roll: draw */
#pragma inline_max_size(4000)
#pragma inline_max_total_size(30000)
#include "game/rN_8025EEF0/prim2d.h"

struct C4 { u8 r, g, b, a; };

extern "C" {

extern char lbl_80373ECC[];
extern char lbl_80392EBC[];
extern char lbl_80392EA4[];
void fn_800804D4(int r, int g, int b, int a);
void fn_80080330(f32 x, f32 y);
void fn_80080388(f32 a, f32 b, f32 c, f32 d);
void fn_80080508(C4* c);
void fn_80080940(C4* a, C4* b, C4* c, C4* d);
void fn_80080A94(f32 s);
void fn_80080C24(const char* s);
C4* fn_800CD204(int i);
int fn_800CA3DC(const char* s, int a, f32 v);
int fn_800CA7A4(const char* s, int a, f32 v);
void fn_800CB520(int a, int x, int y, int b, int c, int d, f32 s, f32 t, const char* f, ...);
void* memcpy(void* a, const void* b, u32 n);

struct Roll {
    u8 pad[0x30];
    u8 m30;
    u8 pad31[3];
    f32 m34;
    u8 pad38[0x1C];
    void* tex;
    s16 m58;
    u8 m5A;
    u8 pad5B;
    f32 m5C;
    u8 pad60[4];
    f32 m64;
    u8 pad68[0x14];
    s16 m7C, m7E, m80, m82;
    u8 pad84[0x14];
    u16 m98;
    u8 pad9A[2];
    u32* m9C;
};

static C4 k0 = {0, 0, 0, 0xFF};
static C4 k1 = {0, 0, 0, 0xFF};
static C4 k2 = {0xFF, 0xFF, 0xFF, 0xFF};

static inline void grad(C4 a, C4 b, C4 c, C4 d) { fn_80080940(&a, &b, &c, &d); }
static inline C4 mk0() { C4 r = k0; return r; }
static inline C4 mk1() { C4 r = k1; return r; }
static inline C4 mk2() { C4 r = k2; return r; }
struct W { u32 v; };
static inline void gradA(W a, W b, C4 c, C4 d) { fn_80080940((C4*)&a, (C4*)&b, &c, &d); }
static inline void gradB(C4 a, C4 b, W c, W d) { fn_80080940(&a, &b, (C4*)&c, (C4*)&d); }
static inline void setc(C4 c) { fn_80080508(&c); }
#define CENTER(str, sc, d) { \
    const char* s = fn_800D0864(str); \
    s16 w = fn_800CA3DC(s, 4, sc); \
    s16 h = fn_800CA7A4(s, 4, sc); \
    int x = 0x130 - (w >> 1); \
    int y0 = 0xE0 - (h >> 1); \
    int y = y0 d; \
    f32 fx = x; \
    f32 fy = y; \
    fn_800800D4(8); \
    fn_80080330(fx, fy); \
    setc(*fn_800CD204(1)); \
    fn_80080A94(sc); \
    fn_80080C24(s); \
    fn_80080308(); }
static inline BOOL hasNL(const char* s) {
    int k;
    for (k = 0; s[k] != 0; k++) {
        if (s[k] == '\n') return 1;
    }
    return 0;
}
static inline int findNL(const char* s) {
    int r = -1;
    int i = 0;
    for (; *s != 0; s++) {
        if (*s == '\n') {
            r = i;
            break;
        }
        i++;
    }
    return r;
}
#define TXT8(x, y, sc, s) { \
    fn_800800D4(8); \
    fn_80080330(x, y); \
    setc(*fn_800CD204(1)); \
    fn_80080A94(sc); \
    fn_80080C24(s); \
    fn_80080308(); }
static inline BOOL vis(s16 y) {
    BOOL b = 0;
    if ((f32)y < 448.0f && (f32)y + 50.0f > 0.0f) b = 1;
    return b;
}

void fn_80289214(Roll* o) {
    char buf[0x100];
/*P*/
    int xb;
    int i;
    const char* a;
    const char* b;
    const char* c;
    int n;
    int xa;
    int y;
    const char* S;
    int six;
/*E*/
    o->m34 += 16.666666f;
    if (o->m5A != 0) o->m5C -= o->m64;
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 300.0f, 1.0f);
    fn_8007E7DC(0xFF);
    fn_8007E174(0, 0x12);
    fn_8007E164();
    fn_800800D4(3);
    {
        C4 k = mk0();
        fn_80080388(0.0f, 0.0f, 608.0f, 448.0f);
        grad(k, k, k, k);
    }
    fn_80080578(0);
    fn_80080308();
    if (o->m7C != 0) {
        fn_8007E154();
        fn_8007E4E4(0.0f, 0.0f, 200.0f, 1.0f);
        fn_8007E7DC((u8)o->m7C);
        fn_8007E174(0, 0x13);
        fn_8007E164();
        CENTER(lbl_80373ECC + 0x1BF, 1.5f, )
    }
    if (o->m7E != 0 && o->m30 == 1 && *o->m9C != 999) {
        if ((s8)fn_8024BC94()[0x1BC8] == 0) {
            xa = 0x21A;
            xb = 0;
        } else {
            C4 k = mk1();
            xa = 0; W z; z.v = 0;
            xb = 400;
            fn_8007E154();
            fn_8007E4E4(0.0f, 400.0f, 150.0f, 1.0f);
            fn_8007E7DC((u8)o->m7E);
            fn_8007E174(0, 0x12);
            fn_8007E164();
            fn_800800D4(3);
            six = 6;
            fn_80080388(0.0f, 0.0f, 608.0f, six);
            gradA(z, z, k, k);
            fn_80080578(0);
            fn_80080308();
            fn_800800D4(3);
            { int h = 0x14; fn_80080388(0.0f, six, 608.0f, h); }
            grad(k, k, k, k);
            fn_80080578(0);
            fn_80080308();
            fn_800800D4(3);
            { int y2 = 0x1A; fn_80080388(0.0f, y2, 608.0f, six); }
            gradB(k, k, z, z);
            fn_80080578(0);
            fn_80080308();
        }
        fn_8007E154();
        fn_8007E4E4(xa, xb, 100.0f, 1.0f);
        fn_8007E374(o->tex, *o->m9C, 0x21);
        fn_8007E7DC((u8)o->m7E);
        fn_8007E164();
        fn_800800D4(3);
        {
            C4 k = mk2();
            fn_80080430(0.0f, 0.0f, 0.0f, 0.0f, 608.0f, 448.0f);
            grad(k, k, k, k);
        }
        fn_80080578(0);
        fn_80080308();
    }
    fn_8007E154();
    fn_8007E4E4(o->m58, 0.0f, 200.0f, 1.0f);
    fn_8007E7DC((u8)o->m80);
    fn_8007E174(0, 0x13);
    fn_8007E164();
    i = 0;
    y = (int)o->m5C;
    if ((int)o->m98 > 0) {
        S = lbl_80373ECC;
        for (; i < o->m98; i++) {
            if (i != 0) {
                fn_80290DDC(lbl_80392EBC, lbl_80392EA4, i - 1);
                if (hasNL(fn_800D0864(lbl_80392EBC))) {
                    y = (s16)(y + 0x2A);
                } else {
                    y = (s16)(y + 0x20);
                }
            }
            if (vis((s16)y)) {
                char* q = (char*)S + 0x1D3;
                fn_80290DDC(q, S + 0x1E8, i);
                a = fn_800D0864(q);
                fn_80290DDC(q, S + 0x1FE, i);
                b = fn_800D0864(q);
                fn_80290DDC(q, S + 0x214, i);
                c = fn_800D0864(q);
                if (a != 0) {
                    memcpy(buf, a, 0x100);
                    n = findNL(buf);
                    if (n == -1) {
                        s16 w = fn_800CA3DC(a, 4, 1.0f);
                        fn_800CB520(8, (s16)(int)(f32)(0x120 - w), (s16)y, 1, 0, 0, 1.0f, 0.0f, a);
                    } else {
                        const char* a2 = a + n + 1;
                        s16 w = fn_800CA3DC(a2, 4, 1.0f);
                        fn_800CB520(8, (s16)(int)(f32)(0x120 - w), (s16)(y + 0x14), 1, 0, 0, 1.0f, 0.0f, a2);
                        buf[n] = 0;
                        w = fn_800CA3DC(buf, 4, 1.0f);
                        fn_800CB520(8, (s16)(int)(f32)(0x120 - w), (s16)y, 1, 0, 0, 1.0f, 0.0f, buf);
                    }
                }
                if (b != 0) {
                    s16 w = fn_800CA3DC(b, 4, 1.0f);
                    fn_800CB520(8, (s16)(int)(f32)(0x130 - (w >> 1)), (s16)y, 1, 0, 0, 1.0f, 0.0f, b);
                }
                if (c != 0) {
                    memcpy(buf, c, 0x100);
                    n = findNL(buf);
                    if (n == -1) {
                        if (*c == '[') {
                            TXT8(320.0f, (s16)y, 0.8f, c)
                        } else {
                            fn_800CB520(8, 0x140, (s16)y, 1, 0, 0, 1.0f, 0.0f, c);
                        }
                    } else {
                        TXT8(320.0f, (s16)y + 0x14, 0.8f, c + n + 1)
                        buf[n] = 0;
                        fn_800CB520(8, 0x140, (s16)y, 1, 0, 0, 1.0f, 0.0f, buf);
                    }
                }
            }
        }
    }
    if (o->m82 != 0) {
        fn_8007E154();
        fn_8007E4E4(0.0f, 0.0f, 200.0f, 1.0f);
        fn_8007E7DC((u8)o->m82);
        fn_8007E174(0, 0x13);
        fn_8007E164();
        CENTER(lbl_80373ECC + 0x22A, 1.0f, - 0x48)
        CENTER(lbl_80373ECC + 0x23E, 1.0f, - 0x24)
        CENTER(lbl_80373ECC + 0x252, 1.0f, )
        CENTER(lbl_80373ECC + 0x266, 1.0f, + 0x24)
        CENTER(lbl_80373ECC + 0x27A, 1.0f, + 0x48)
    }
}

}
