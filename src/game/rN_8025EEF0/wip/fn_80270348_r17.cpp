/* NEAR MISS (round 17): 26 positional lines. Statement order of l/tt fixed the tt sum; l still loads x18 before x14, and two loop blocks keep register ranks. */
/* Soundroom/dialog screen draw: two sides of portraits and text boxes */
#include "game/rN_8025EEF0/calls.h"

struct C4 { u8 r, g, b, a; };
extern "C" {
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E4E4(f32 x, f32 y, f32 z, f32 s);
void fn_8007E7DC(u8 a);
void fn_8007E720(f32 v);
void fn_8007E174(int a, int b);
void fn_8007E74C(void* f, void* a);
void fn_8007E7B4(void);
u8* fn_800CD204(int i);
u16** fn_80006A0C(void* tex, int i);
void fn_801BC88C(f32 x, f32 y, f32 x2, f32 y2, f32 a, f32 b, f32 w, f32 h, void* tex, int i, C4* c, int d, int e);
void fn_8026FC38(void*, void*);
void* fn_8012486C(void* p);
void* fn_80118F8C(void* p);
u8* fn_800C6210(void* p, int a);
void fn_800C4DDC(int x, int y, int a, void* o);
void fn_800C429C(void* o);
int fn_800CB0FC(int a, f32 s);
const char* fn_80118C44(void* u);
const char* fn_80118CA4(void* u);
int fn_80290D04(char* b, int n, const char* f, ...);
void fn_800800D4(int t);
void fn_80080508(C4* c);
void fn_80080ABC(int a, f32 s);
void fn_80176EA8(int x, int y, int a, const char* s);
void fn_80080308(void);
void fn_80080330(f32 x, f32 y);
void fn_80080C24(const char* s);
void fn_800804F4(u8 a);
char* fn_802910CC(char* d, const char* s, int n);
f32 fn_8017F68C(f32 a, f32 b, f32 c, f32 d, int e);
int fn_800CA3DC(const char* s, int a, f32 v);
extern char lbl_804CAB18[8];

struct Icon { u8 pad0[4]; int x4; void* x8; s16 xC; s16 xE; };
struct Pt { u8 pad0[4]; int x4; void* x8; void* xC; void* x10; s16 x14; s16 x16; s16 x18; s16 x1A; f32 x1C; s16 x20; s16 x22; s16 x24; s16 x26; };
struct TB {
    u8 pad0[0x28];
    int x28;
    char buf[3][0x40];
    char* w;
    char* last;
    s16 line;
    u8 padF6[2];
    u8* xF8;
    void* xFC;
    s16 x100;
    s16 x102;
    f32 x104;
};
struct Scr {
    u8 pad0[0x38];
    void* x38;
    u8 pad3C[0xC];
    Icon* x48;
    u8 pad4C[4];
    Pt* x50;
    u8 pad54[4];
    Pt* x58;
    u8 pad5C[4];
    TB* x60;
    u8 pad64[4];
    TB* x68;
};
}

static inline C4 mk(const u8* p) { C4 c; c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = 0xFF; return c; }
static inline void spr(void* tex, int i, f32 x, f32 y, f32 s, int fl, C4& c, C4& a) {
    const u8* p = fn_800CD204(1);
    c.r = p[0];
    c.g = p[1];
    c.b = p[2];
    c.a = 0xFF;
    u16* d = *fn_80006A0C(tex, i);
    f32 w = d[1];
    f32 h = d[0];
    *(u32*)&a = *(u32*)&c;
    fn_801BC88C(x, y, w * s + x, h * s + y, 0.0f, 0.0f, w, h, tex, i, &a, 0x11, fl);
}
static inline void col(C4& c, int i) {
    const u8* p = fn_800CD204(i);
    c.r = p[0];
    c.g = p[1];
    c.b = p[2];
    c.a = p[3];
    fn_80080508(&c);
}
static inline void xf(int x, int y, f32 z, f32 s) {
    fn_8007E4E4(x, y, z, s);
}
static inline BOOL hasP(Pt* p) { return p->xC || p->x10; }
static inline BOOL hasT(TB* t) { return t->xF8 || t->xFC; }

static inline int sx(int v) { return (s16)v; }
static inline int rd4(u8* d) { return *(s16*)d; }
static inline void drawP(Pt* p, u8*& o, int& ox, int& oy) {
    fn_8007E154();
    xf(p->x14, p->x16, 500.0f, 1.0f);
    fn_8007E7DC(255.9f * p->x1C);
    fn_8007E164();
    fn_8007E154();
    fn_8007E720(-1.1f);
    fn_8007E164();
    o = fn_800C6210(p->xC ? fn_8012486C(p->xC) : fn_80118F8C(p->x10), 0x200);
    u8* d = *(u8**)(o + 0x34);
    ox = rd4(d + 0x28);
    oy = *(s16*)(d + 0x2A);
    s16 tt = p->x16 + p->x1A - 0x20;
    s16 l = p->x18 + (ox + p->x14);
    p->x20 = l;
    p->x22 = tt;
    p->x24 = l + 0xEC;
    p->x26 = tt + 0xC1;
    fn_8007E154();
    fn_8007E74C((void*)fn_8026FC38, &p->x20);
    fn_8007E164();
    *(u32*)(o + 0x48) &= ~1;
    if (p->x4) {
        *(u32*)(o + 0x48) |= 1;
        ox = (s16)-ox;
    }
    fn_800C4DDC((s16)ox + p->x18 + 0x76, oy + p->x1A + 0xA1, 0xFF, o);
    fn_800C429C(o);
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
}
static inline void drawT(TB* t, char* tmp, char* hd, int& z, void*& u, int& y0, const char*& a, int& y, char*& s, char*& q, int& j, int& al, int& x, C4& k0, C4& k1, C4& k2, C4& k3) {
    fn_8007E154();
    xf(t->x100, t->x102, 499.0f, 1.0f);
    fn_8007E7DC(255.9f * t->x104);
    fn_8007E164();
    fn_8007E154();
    fn_8007E720(-0.2f);
    fn_8007E164();
    fn_8007E154();
    fn_8007E174(0, 0x13);
    fn_8007E164();
    y0 = (0x20 - fn_800CB0FC(-1, 1.0f)) >> 1;
    u = t->xF8 ? *(void**)(t->xF8 + 0xEC) : t->xFC;
    hd[0x7F] = 0;
    a = fn_80118C44(u);
    fn_80290D04(hd, 0x7F, lbl_804CAB18, fn_80118CA4(u), a);
    fn_800800D4(5);
    col(k0, 0x38);
    fn_80080ABC(1, 2.0f);
    fn_80176EA8(0xC4, y0 + 0x1A, 2, hd);
    fn_80080308();
    fn_8007E154();
    if (fn_801D09F0()) {
        xf(t->x100 + 0x40, t->x102 + 0x40, 498.8f, 0.9f);
    } else {
        xf(t->x100 + 0x20, t->x102 + 0x40, 498.8f, 0.9f);
    }
    fn_8007E7DC(255.9f * t->x104);
    fn_8007E164();
    y = (0x20 - fn_800CB0FC(2, 1.0f)) >> 1;
    s = t->buf[0];
    q = s;
    for (j = 0; j <= t->line; j++) {
        if (j < t->line || t->x28 <= 0) {
            fn_800800D4(6);
            fn_80080330(z, y);
            col(k1, 1);
            fn_80080ABC(1, 2.0f);
            fn_80080C24(s);
            fn_80080308();
        } else {
            tmp[0] = z;
            int n = t->last - q;
            if (n > 0) {
                fn_802910CC(tmp, s, n);
                tmp[t->last - q] = z;
                fn_800800D4(6);
                fn_80080330(z, y);
                col(k2, 1);
                fn_80080ABC(1, 2.0f);
                fn_80080C24(tmp);
                fn_80080308();
            }
            t->x28 = t->x28 - 1;
            al = fn_8017F68C(255.0f, 0.0f, t->x28, 8.0f, 0);
            x = (s16)fn_800CA3DC(tmp, 2, 1.0f);
            fn_800800D4(6);
            fn_80080330(x, y);
            col(k3, 1);
            fn_800804F4(al);
            fn_80080ABC(1, 2.0f);
            fn_80080C24(t->last);
            fn_80080308();
        }
        s += 0x40;
        q += 0x40;
        y += 0x20;
    }
}

extern "C" void fn_80270348(Scr* o) {
    char hd2[0x80];
    char hd1[0x80];
    char tmp2[0x40];
    char tmp1[0x40];
    C4 c4C, c48, c44, c40, c3C, c38, c34, c30;
    C4 a2C, c28, a24, c20, a1C, c18, a14, c10, c0C, a08;
/*P*/
    Scr* self;
    int z;
    Pt* p2;
    u8* o2;
    int i;
    u8* o3;
    int ox2;
    int oy2;
    int ox3;
    int oy3;
    const char* a1;
    const char* a2;
    int yd;
    char* s2;
    int al2;
    int j2;
    int al1;
    char* s1;
    char* q1;
    int j1;
    char* q2;
    Pt* p1;
    int yb;
    TB* t2;
    int ya;
    int yc;
    TB* t1;
    Pt* p3;
    int fl1;
    int fl2;
    int k1;
    int k2;
    void* u1;
    void* u2;
    int x1;
    int x2;
    Icon* c0;
/*E*/
    self = o;
    z = 0;
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 800.0f, 1.0f);
    fn_8007E7DC(0xFF);
    fn_8007E164();
    spr(self->x38, 0, 0.0f, 0.0f, 1.0f, 0, c0C, a08);
    for (i = 0; i < 2; i++, self = (Scr*)((u8*)self + 4)) {
        c0 = self->x48;
        if (c0) {
            fn_8007E154();
            xf(c0->xC, c0->xE, 499.0f, 1.0f);
            fn_8007E7DC(0xFF);
            fn_8007E164();
            k1 = 2;
            if (c0->x4 == 0) k1 = 1;
            spr(c0->x8, k1, 0.0f, 0.0f, 1.0f, 0, c10, a14);
        }
        p1 = self->x50;
        if (p1) {
            fn_8007E154();
            xf(p1->x14, p1->x16, 500.0f, 1.0f);
            fn_8007E7DC(0xFF);
            fn_8007E164();
            if (p1->x4 == 0) {
                fl1 = p1->x4 ? 1 : 0;
                spr(p1->x8, 5, 44.0f, 10.0f, 1.0f, fl1, c28, a2C);
            } else {
                fl2 = p1->x4 ? 1 : 0;
                spr(p1->x8, 5, 0.0f, 10.0f, 1.0f, fl2, c20, a24);
            }
            fn_8007E154();
            fn_8007E720(-1.5f);
            fn_8007E164();
            k2 = 4;
            if (p1->x4 == 0) k2 = 3;
            spr(p1->x8, k2, 0.0f, 0.0f, 1.0f, 0, c18, a1C);
            p2 = self->x50;
            if (hasP(p2)) drawP(p2, o2, ox2, oy2);
        }
        t1 = self->x60;
        if (t1 && hasT(t1)) drawT(t1, tmp1, hd1, z, u1, ya, a1, yb, s1, q1, j1, al1, x1, c3C, c38, c34, c30);
        p3 = self->x58;
        if (p3 && hasP(p3)) drawP(p3, o3, ox3, oy3);
        t2 = self->x68;
        if (t2 && hasT(t2)) drawT(t2, tmp2, hd2, z, u2, yc, a2, yd, s2, q2, j2, al2, x2, c4C, c48, c44, c40);
    }
}
