/* symcheck: r21 review, flag was an artefact. fn_8026D73C: (a) 3 blocks: stale r8 before fn_801BC88C (reads r3-r7,
   f1-f8). See docs/SCHED_REVIEW.md. */
/* r20: `sched` (check_regs.py). Wip draft with three real fixes:
   - fn_80179888 takes an int and fn_80179A7C a u8 (the draft had them the other way round, so the scroll position
     28.0f * m148 was cut to 8 bits and the alpha was not);
   - the eight gradient colours were placeholders (all FFFFFFFF); they now hold the bytes of lbl_804D04E8+8..+0x27
     (k23 +8 3C3C3CFF, k22 +0xC 000000FF, k21 +0x10 3C3C3CFF, k20 +0x14 000000FF, k33..k30 +0x18..+0x24 000000FF);
     k1a/k1b are +0 FFFFFFFF and +4 FFFFFF00.
   Moved instructions (dd.py -u): in the song row loop, `mr r5`, two `addi` and one `lha` before the first text call;
   in the cursor sprite block before fn_801BC88C, `lfs`/`fmr` of 0.0f, `li r4/r6/r7`, `addi r5`, two `xoris` and one
   `subi`. The conversion slots 0x100..0x10C are written and read in the same order in both versions. */
/* Random-order list (lbl_804CC044): draw */
#pragma inline_max_size(4000)
#pragma inline_max_total_size(30000)
#include "game/rN_8025EEF0/prim2d.h"

struct GXC { u8 r, g, b, a; };


struct ListSt {
    void* tex;
    void* tex2;
    u8 pad8[8];
    int n;
    u8 pad14[4];
    u8* items;
    u8 pad1C[0xC];
    int cur;
    u8 pad2C[0x14];
    s16 alpha;
    u8 pad42[2];
    void* bar;
    char txt1[0x80];
    char txt2[0x80];
    f32 m148;
    u8 pad14C[8];
    s16 cx, cy;
    u8 pad158[0xA];
    s16 x, y, w, h;
    s16 tx, ty;
    s16 m16E;
};
struct Rect16 { s16 x, y, w, h; };

extern "C" {

extern ListSt* lbl_804CC044;
extern s8 lbl_804CC048;
extern s8 lbl_804CC058;
extern Rect16 lbl_804CC050;
extern Rect16 lbl_804CC060;
extern char lbl_8037340C[];
void fn_8026D458(void* p, void* arg);
void fn_8007E7E8(int a);
void fn_8007E720(f32 v);
void fn_8007E74C(void* f, void* a);
void fn_8007E7B4(void);
u16** fn_80006A0C(void* tex, int i);
u8* fn_800CD204(int i);
void fn_801BC88C(f32 x, f32 y, f32 x2, f32 y2, f32 a, f32 b, f32 w, f32 h, void* tex, int i, GXC* c, int d, int e);
void fn_801BCA5C(f32 v);
void fn_801BCA94(void);
void fn_80080388(f32 a, f32 b, f32 c, f32 d);
void fn_800803C8(f32 a, f32 b, f32 c, f32 d);
void fn_80080348(f32 a, f32 b, f32 c, f32 d);
void fn_80080368(f32 a, f32 b, f32 c, f32 d);
void fn_80080494(void);
void fn_80080940(GXC* a, GXC* b, GXC* c, GXC* d);
int fn_800CA3DC(const char* s, int a, f32 v);
void fn_800CB3A8(int x, int y, int a, int b, int c, f32 s, f32 t, const char* f, ...);
char* strcpy(char* a, const char* b);
char* fn_80291110(char* a, const char* b);
void fn_80070688(f32 a, f32 b, f32 c, f32 d);
s16 fn_8024F3C8(const char* s);
int fn_802454C8(void* s, int a);
void fn_80072ACC(int a, int b, int c, int d, int e, int f, int g);
void fn_800712E8(int x, int y, int a);
const char* fn_800CECFC(void);
const char* fn_800CF05C(void);
const char* fn_800CEB4C(void);
const char* fn_800CEC24(void);
const char* fn_800CF53C(void);
void fn_801C6D9C(const char* s, int a, int b, int c);
void fn_8017980C(void* p, int a, int b, int c);
void fn_80179888(void* p, int a);
void fn_80179A7C(void* p, u8 a);
void fn_80179A84(void* p);

static GXC k1a = {0xFF, 0xFF, 0xFF, 0xFF};
static GXC k1b = {0xFF, 0xFF, 0xFF, 0x00};
static const GXC k20 = {0x00, 0x00, 0x00, 0xFF};
static const GXC k21 = {0x3C, 0x3C, 0x3C, 0xFF};
static const GXC k22 = {0x00, 0x00, 0x00, 0xFF};
static const GXC k23 = {0x3C, 0x3C, 0x3C, 0xFF};
static const GXC k30 = {0x00, 0x00, 0x00, 0xFF};
static const GXC k31 = {0x00, 0x00, 0x00, 0xFF};
static const GXC k32 = {0x00, 0x00, 0x00, 0xFF};
static const GXC k33 = {0x00, 0x00, 0x00, 0xFF};

static inline GXC rc(const GXC& s) { GXC r = s; return r; }
static inline void spr1(int i, f32 x, f32 y, f32 w, f32 h, const char* mode) {
    GXC a; GXC t;
    const u8* p = fn_800CD204(1);
    u16* d;
    t.r = p[0]; t.g = p[1]; t.b = p[2]; t.a = 0xFF;
    d = *fn_80006A0C(lbl_804CC044->tex, i);
    {
        f32 tw = d[1];
        f32 th = d[0];
        *(u32*)&a = *(u32*)&t;
        fn_801BC88C(x, y, x + w, y + h, 0.0f, 0.0f, tw, th, lbl_804CC044->tex, i, &a, 0x11, 0);
    }
}
static inline void spr2(int i, f32 x, f32 y, f32 w, f32 h, const char* mode) {
    GXC t; GXC a;
    const u8* p = fn_800CD204(1);
    u16* d;
    t.r = p[0]; t.g = p[1]; t.b = p[2]; t.a = 0xFF;
    d = *fn_80006A0C(lbl_804CC044->tex, i);
    {
        f32 tw = d[1];
        f32 th = d[0];
        *(u32*)&a = *(u32*)&t;
        fn_801BC88C(x, y, x + w, y + h, 0.0f, 0.0f, tw, th, lbl_804CC044->tex, i, &a, 0x11, 0);
    }
}
static inline void sprA(int i, f32 x, f32 y) {
    u16* d = *fn_80006A0C(lbl_804CC044->tex, i);
    f32 w = d[1];
    f32 h = d[0];
    spr1(i, x, y, w, h, 0);
}
static inline void spr3(int i, int x, int y, f32 w, f32 h) {
    GXC a; GXC t;
    const u8* p = fn_800CD204(1);
    u16* d;
    t.r = p[0]; t.g = p[1]; t.b = p[2]; t.a = 0xFF;
    d = *fn_80006A0C(lbl_804CC044->tex, i);
    {
        f32 tw = d[1]; f32 th = d[0];
        *(u32*)&a = *(u32*)&t;
        fn_801BC88C(x, y, (f32)x + w, (f32)y + h, 0.0f, 0.0f, tw, th, lbl_804CC044->tex, i, &a, 0x11, 0);
    }
}
static inline void spr4(int i, int x, int y, f32 w, f32 h) {
    GXC t; GXC a;
    const u8* p = fn_800CD204(1);
    u16* d;
    t.r = p[0]; t.g = p[1]; t.b = p[2]; t.a = 0xFF;
    d = *fn_80006A0C(lbl_804CC044->tex, i);
    {
        f32 tw = d[1]; f32 th = d[0];
        *(u32*)&a = *(u32*)&t;
        fn_801BC88C(x, y, (f32)x + w, (f32)y + h, 0.0f, 0.0f, tw, th, lbl_804CC044->tex, i, &a, 0x11, 0);
    }
}
static inline void sprI(int i, int x, int y) {
    u16* d = *fn_80006A0C(lbl_804CC044->tex, i);
    f32 w = d[1];
    f32 h = d[0];
    spr3(i, x, y, w, h);
}
static inline void sprJ(int i, int x, int y, f32 w, f32 h) { spr4(i, x, y, w, h); }
static inline void sprW(int i, f32 x, f32 y, f32 w, f32 h) { spr2(i, x, y, w, h, 0); }
static inline void rset(Rect16* r, s16 x, s16 y, s16 w, s16 h) { r->x = x; r->y = y; r->w = w; r->h = h; }
static inline void dep(f32 v) {
    fn_8007E154();
    fn_8007E720(v);
    fn_8007E164();
}
static inline void grad(GXC d, GXC c, GXC b, GXC a) { fn_80080940(&d, &c, &b, &a); }

static inline void sprB(int i, f32 x, f32 y) {
    sprA(i, x, y);
}

void fn_8026D73C(void) {
    char buf[0x60];
/*P*/
    const char* S2;
    const char* S;
    const char* a1;
    const char* a2;
    const char* b1;
    const char* b2;
    const char* c1;
    const char* c2;
    const char* d1;
    const char* d2;
    const char* e1;
    const char* e2;
    const char* f1;
    const char* f2;
    const char* g1;
    const char* g2;
    const char* h1;
    const char* h2;
    const char* k1;
    const char* k2;
    int i;
    int bx;
    void* save;
    int fl;
    int idx;
    const char* m0;
    int q;
    int yy;
/*E*/
    if (lbl_804CC048 == 0) lbl_804CC048 = 1;
    if (lbl_804CC058 == 0) lbl_804CC058 = 1;
    save = fn_8024BC94();
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 950.0f, 1.0f);
    fn_8007E7DC(0xFF);
    fn_8007E7E8(0x50);
    fn_8007E164();
    sprA(0, 0.0f, 0.0f);
    if (lbl_804CC044->tex2 != 0) {
        GXC ca = rc(k1a);
        GXC cb = rc(k1b);
        fn_8007E154();
        fn_8007E4E4(0.0f, 0.0f, 200.0f, 1.0f);
        fn_8007E7DC(0xFF);
        fn_8007E374(lbl_804CC044->tex2, 0, 0x11);
        fn_8007E164();
        fn_800800D4(1);
        fn_80080388(0.0f, 0.0f, 72.0f, 448.0f);
        fn_800803C8(0.0f, 0.0f, 72.0f, 448.0f);
        fn_80080308();
        fn_800800D4(3);
        fn_80080388(72.0f, 0.0f, 20.0f, 448.0f);
        fn_800803C8(72.0f, 0.0f, 20.0f, 448.0f);
        fn_80080578(0);
        grad(ca, cb, ca, cb);
        fn_80080308();
        fn_800800D4(3);
        fn_80080388(516.0f, 0.0f, 20.0f, 448.0f);
        fn_800803C8(72.0f, 0.0f, 20.0f, 448.0f);
        fn_80080494();
        fn_80080578(0);
        grad(cb, ca, cb, ca);
        fn_80080308();
        fn_800800D4(1);
        fn_80080388(536.0f, 0.0f, 72.0f, 448.0f);
        fn_800803C8(0.0f, 0.0f, 72.0f, 448.0f);
        fn_80080494();
        fn_80080308();
    }
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 100.0f, 1.0f);
    fn_8007E7DC((u8)lbl_804CC044->alpha);
    fn_8007E7E8(0x80);
    fn_8007E164();
    fn_8007E154();
    fn_8007E174(0, 0x12);
    fn_8007E164();
    fn_800800D4(3);
    fn_80080348(0.0f, 0.0f, 0.0f, 0.0f);
    fn_80080368(608.0f, 62.0f, 0.0f, 0.0f);
    grad(k23, k22, k21, k20);
    fn_80080578(0);
    fn_80080308();
    fn_800800D4(3);
    fn_80080348(0.0f, 388.0f, 0.0f, 0.0f);
    fn_80080368(608.0f, 448.0f, 0.0f, 0.0f);
    grad(k33, k32, k31, k30);
    fn_80080578(0);
    fn_80080308();
    fn_801BCA5C(-1.0f);
    sprA(2, 0.0f, 62.0f);
    fn_801BCA5C(-1.0f);
    {
        m0 = fn_800D0864(lbl_8037340C);
        fn_801BCA94();
        fn_800CB3A8((s16)(0x130 - fn_800CA3DC(m0, -1, 0.8f) / 2), 0x43, 0x3E, 0, 0, 0.8f, 0.0f, m0);
    }
    sprA(1, 17.0f, 14.0f);
    fn_801BCA5C(2.0f);
    fn_801BCA5C(-2.0f);
    fn_8007E154();
    fn_8007E7DC((u8)(lbl_804CC044->alpha * lbl_804CC044->m16E / 0xFF));
    fn_8007E164();
    rset(&lbl_804CC050, lbl_804CC044->tx, lbl_804CC044->ty, 0x170, lbl_804CC044->y - lbl_804CC044->ty);
    fn_8007E154();
    fn_8007E74C(fn_8026D458, &lbl_804CC050);
    fn_8007E164();
    {
        f32 y0 = lbl_804CC044->ty;
        f32 x0 = lbl_804CC044->tx;
        sprA(3, x0, y0);
    }
    if (lbl_804CC044->cur != -1) {
        s16 x;
        s16 y;
        fn_801BCA5C(-1.0f);
        strcpy(buf, lbl_8037340C + 0x10);
        fn_80291110(buf, *(const char**)(lbl_804CC044->items + lbl_804CC044->cur * 8));
        fn_801BCA94();
        x = lbl_804CC044->tx + 0x16;
        y = lbl_804CC044->ty + 4;
        fn_800CB3A8(x, y, 1, 1, 0, 1.0f, 0.0f, lbl_8037340C + 0x15, lbl_804CC044->cur + 1);
        fn_800CB3A8((s16)(x + 0x24), y, 1, 1, 0, 1.0f, 0.0f, fn_800D0864(buf));
        fn_801BCA5C(1.0f);
    }
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
    fn_801BCA5C(2.0f);
    fn_8007E154();
    fn_8007E7DC((u8)lbl_804CC044->alpha);
    fn_8007E164();
    {
        f32 h1 = lbl_804CC044->h - 6;
        f32 w1 = lbl_804CC044->w - 6;
        f32 y1 = lbl_804CC044->y + 3;
        f32 x1 = lbl_804CC044->x + 3;
        sprW(4, x1, y1, w1, h1);
    }
    fn_801BCA5C(-1.0f);
    fn_80070688(lbl_804CC044->x, lbl_804CC044->y, lbl_804CC044->w, lbl_804CC044->h);
    fn_801BCA5C(-1.0f);
    rset(&lbl_804CC060, lbl_804CC044->x + 8, lbl_804CC044->y + 0xE, lbl_804CC044->w - 0x28, lbl_804CC044->h - 0x1C);
    fn_8007E154();
    fn_8007E74C(fn_8026D458, &lbl_804CC060);
    fn_8007E164();
    fn_801BCA94();
    S2 = lbl_8037340C;
    for (i = 0; i < 9; i++) {
        idx = i + (int)lbl_804CC044->m148 - 1;
        if (idx >= 0 && idx < lbl_804CC044->n) {
            f32 fr = lbl_804CC044->m148 - (f32)(int)lbl_804CC044->m148;
            q = idx * 8;
            if (fn_802454C8(save, fn_8024F3C8(*(const char**)(lbl_804CC044->items + q)))) {
                fl = 1;
                strcpy(buf, S2 + 0x10);
                fn_80291110(buf, *(const char**)(lbl_804CC044->items + q));
            } else {
                fl = 0;
                strcpy(buf, S2 + 0x1A);
            }
            bx = (s16)(lbl_804CC044->x + 0x1C);
            yy = (int)(28.0f * ((f32)i - fr) + (f32)(lbl_804CC044->y - 0xE));
            fn_800CB3A8(bx, (s16)yy, fl, 1, 0, 1.0f, 0.0f, S2 + 0x15, idx + 1);
            fn_800CB3A8((s16)(bx + 0x24), (s16)yy, fl, 1, 0, 1.0f, 0.0f, fn_800D0864(buf));
            fn_801BCA5C(1.0f);
            sprI(5, bx - 8, (s16)yy + 0x14);
            sprJ(6, bx - 5, (s16)yy + 0x14, 330.0f, 8.0f);
            sprI(7, bx + 0x145, (s16)yy + 0x14);
            fn_801BCA5C(-1.0f);
        }
    }
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
    fn_801BCA5C(2.0f);
    fn_801BCA5C(-1.0f);
    fn_80072ACC(lbl_804CC044->cx + 0xA8, lbl_804CC044->cy + 0xC, 0x164, 0x17, 0x19, 100, 1);
    fn_801BCA5C(-4.0f);
    fn_800712E8(lbl_804CC044->cx, lbl_804CC044->cy, 1);
    fn_801BCA5C(5.0f);
    S = lbl_8037340C;
    {
        a1 = fn_800D0864(S + 0x5F);
        b1 = fn_800CECFC();
        c1 = fn_800D0864(S + 0x57);
        d1 = fn_800CF05C();
        e1 = fn_800D0864(S + 0x4E);
        f1 = fn_800CEB4C();
        g1 = fn_800D0864(S + 0x46);
        h1 = fn_800CEC24();
        k1 = fn_800D0864(S + 0x3B);
        fn_80290DDC(lbl_804CC044->txt1, S + 0x22, fn_800CF53C(), k1, h1, g1, f1, e1, d1, c1, b1, a1);
    }
    {
        a2 = fn_800D0864(S + 0x5F);
        b2 = fn_800CECFC();
        c2 = fn_800D0864(S + 0x57);
        d2 = fn_800CF05C();
        e2 = fn_800D0864(S + 0x4E);
        f2 = fn_800CEB4C();
        g2 = fn_800D0864(S + 0x68);
        h2 = fn_800CEC24();
        k2 = fn_800D0864(S + 0x3B);
        fn_80290DDC(lbl_804CC044->txt2, S + 0x22, fn_800CF53C(), k2, h2, g2, f2, e2, d2, c2, b2, a2);
    }
    if (lbl_804CC044->cur == -1) {
        fn_801C6D9C(lbl_804CC044->txt1, 0xFF, 0, 0);
    } else {
        fn_801C6D9C(lbl_804CC044->txt2, 0xFF, 0, 0);
    }
    fn_8017980C(lbl_804CC044->bar, lbl_804CC044->x + lbl_804CC044->w - 0x1E, lbl_804CC044->y + 0xC, lbl_804CC044->h - 0x18);
    fn_80179888(lbl_804CC044->bar, 28.0f * lbl_804CC044->m148);
    fn_80179A7C(lbl_804CC044->bar, lbl_804CC044->alpha);
    fn_80179A84(lbl_804CC044->bar);
    fn_8007E154();
    fn_8007E7DC(0xFF);
    fn_8007E164();
}

}
