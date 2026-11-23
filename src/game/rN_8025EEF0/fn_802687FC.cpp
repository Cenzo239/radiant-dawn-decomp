/* Unit slot menu: draw the three groups and the cursors */
#pragma inline_max_size(4000)
#include "game/rN_8025EEF0/prim2d.h"

struct GXC { u8 r, g, b, a; };

extern "C" {

struct Slot { void* unit; s16 a; s16 b; };
extern Slot lbl_80430740[3][20];
extern s8 lbl_804CC031;
struct SlotDraw {
    u8 pad[0x34];
    void* tex;
    void* m38;
    void* m3C;
    u8 pad40[8];
    u8 m48;
    u8 m49;
    u8 m4A;
    u8 pad4B;
    s16 grp;
    s16 idx;
    s16 grp2;
    s16 idx2;
    s16 cx;
    s16 cy;
};
void fn_8007E7E8(int a);
void fn_8007E720(f32 v);
u16** fn_80006A0C(void* tex, int i);
u8* fn_800CD204(int i);
void fn_801BC88C(f32 x, f32 y, f32 x2, f32 y2, f32 a, f32 b, f32 w, f32 h, void* tex, int i, GXC* c, int d, int e);
void fn_800C4C3C(void* a, void* b, int x, int y, int w, int h, int al, int f);
void* fn_801246A4(void* u);
void fn_8017A188(void* p);
void fn_800712E8(int x, int y, int a);
int fn_8028DB44(int v);


static inline void mkc(GXC& t, const u8* p) { t.r = p[0]; t.g = p[1]; t.b = p[2]; t.a = 0xFF; }
static inline void spr(void* tex, int i, f32 x, f32 y, GXC& t, GXC& a, f32 s) {
    u16* d = *fn_80006A0C(tex, i);
    f32 w = d[1];
    f32 h = d[0];
    *(u32*)&a = *(u32*)&t;
    fn_801BC88C(x, y, w * s + x, h * s + y, 0.0f, 0.0f, w, h, tex, i, &a, 0x11, 0);
}

static inline void dep(f32 v) {
    fn_8007E154();
    fn_8007E720(v);
    fn_8007E164();
}

static inline void group1(SlotDraw* o, Slot* s, f32 y0, f32 x0, GXC& t2, GXC& a2, GXC& t1, GXC& a1) {
/*P*/
    f32 yb;
    f32 xb;
    void* u;
    int col;
    int row;
    Slot* q;
    f32 y;
    f32 x;
/*E*/
    xb = x0; yb = y0;
    q = s;
    for (row = 0; row < 5; row++) {
        for (col = 0; col < 4; col++, q++) {
            u = q->unit;
            if (u != 0) {
                y = q->b + (yb + (f32)(row * 0x30));
                x = q->a + (xb + (f32)(col * 0x28));
                dep(-0.1f);
                if (*(u32*)((u8*)u + 0x10C) & 0x10000) {
                    void* tex = o->tex;
                    mkc(t1, fn_800CD204(1));
                    spr(tex, 1, x, y, t1, a1, 1.0f);
                } else {
                    void* tex = o->tex;
                    mkc(t2, fn_800CD204(1));
                    spr(tex, 2, x, y, t2, a2, 1.0f);
                }
                dep(-0.1f);
                fn_800C4C3C(o->m38, fn_801246A4(u), (int)(1.0f + x), (int)(1.0f + y), 0x20, 0x20, 0xFF, 0);
                dep(0.1f);
                dep(0.1f);
            }
        }
    }
}

static inline void group2(SlotDraw* o, Slot* s, f32 y0, f32 x0, GXC& t2, GXC& a2, GXC& t1, GXC& a1) {
/*P*/
    f32 xb;
    f32 yb;
    f32 x;
    Slot* q;
    int row;
    int col;
    f32 y;
    void* u;
/*E*/
    xb = x0; yb = y0;
    q = s;
    for (row = 0; row < 5; row++) {
        for (col = 0; col < 4; col++, q++) {
            u = q->unit;
            if (u != 0) {
                y = q->b + (yb + (f32)(row * 0x30));
                x = q->a + (xb + (f32)(col * 0x28));
                dep(-0.1f);
                if (*(u32*)((u8*)u + 0x10C) & 0x10000) {
                    void* tex = o->tex;
                    mkc(t1, fn_800CD204(1));
                    spr(tex, 1, x, y, t1, a1, 1.0f);
                } else {
                    void* tex = o->tex;
                    mkc(t2, fn_800CD204(1));
                    spr(tex, 2, x, y, t2, a2, 1.0f);
                }
                dep(-0.1f);
                fn_800C4C3C(o->m38, fn_801246A4(u), (int)(1.0f + x), (int)(1.0f + y), 0x20, 0x20, 0xFF, 0);
                dep(0.1f);
                dep(0.1f);
            }
        }
    }
}

static inline void group3(SlotDraw* o, Slot* s, f32 y0, f32 x0, GXC& t2, GXC& a2, GXC& t1, GXC& a1) {
/*P*/
    f32 yb;
    f32 xb;
    void* u;
    int col;
    int row;
    Slot* q;
    f32 y;
    f32 x;
/*E*/
    xb = x0; yb = y0;
    q = s;
    for (row = 0; row < 5; row++) {
        for (col = 0; col < 4; col++, q++) {
            u = q->unit;
            if (u != 0) {
                y = q->b + (yb + (f32)(row * 0x30));
                x = q->a + (xb + (f32)(col * 0x28));
                dep(-0.1f);
                if (*(u32*)((u8*)u + 0x10C) & 0x10000) {
                    void* tex = o->tex;
                    mkc(t1, fn_800CD204(1));
                    spr(tex, 1, x, y, t1, a1, 1.0f);
                } else {
                    void* tex = o->tex;
                    mkc(t2, fn_800CD204(1));
                    spr(tex, 2, x, y, t2, a2, 1.0f);
                }
                dep(-0.1f);
                fn_800C4C3C(o->m38, fn_801246A4(u), (int)(1.0f + x), (int)(1.0f + y), 0x20, 0x20, 0xFF, 0);
                dep(0.1f);
                dep(0.1f);
            }
        }
    }
}

static inline void first2(SlotDraw* o) {
    GXC a; GXC t;
    void* tex = o->tex;
    mkc(t, fn_800CD204(1));
    spr(tex, 0, 0.0f, 0.0f, t, a, 1.0f);
}
static inline void first(SlotDraw* o) { first2(o); }

static inline void hdr(u8 m) {
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 800.0f, 1.0f);
    fn_8007E174(0, 0x12);
    fn_8007E7DC(0xFF);
    fn_8007E7E8(m);
    fn_8007E164();
}

static inline void cursor(SlotDraw* o) {
/*P*/
    s16 ox;
    int cx;
    int cy;
    s16 nx;
    s16 ny;
    s16 k;
/*E*/
    switch (o->grp) {
    case 0: cx = 0x23; cy = 0x4C; break;
    case 1: cx = 0xE3; cy = 0x4C; break;
    case 2: cx = 0x1A3; cy = 0x4C; break;
    }
    {
        ox = o->cx;
        nx = cx + (o->idx % 4) * 0x28;
        ny = cy + (o->idx / 4) * 0x30;
        if ((o->cx == -0x8000 && o->cy == -0x8000) || (fn_8028DB44(o->cx - nx) <= 1 && fn_8028DB44(o->cy - ny) <= 1)) {
            o->cx = nx;
            o->cy = ny;
        } else {
            o->cx = (ox + nx + 1) >> 1;
            o->cy = (ny + o->cy + 1) >> 1;
        }
    }
    if (o->m48) {
        dep(-2.0f);
        fn_800712E8(o->cx, o->cy + 0x10, o->m4A);
    }
    if (o->m49) {
        switch (o->grp2) {
        case 0: cx = 0x23; cy = 0x4C; break;
        case 1: cx = 0xE3; cy = 0x4C; break;
        case 2: cx = 0x1A3; cy = 0x4C; break;
        }
        {
            k = o->idx2;
            fn_8007E154();
            fn_8007E720(1.5f);
            fn_8007E7E8(0x40);
            fn_8007E164();
            fn_800712E8((s16)(cx + (k % 4) * 0x28), (s16)(cy + (k / 4) * 0x30) + 0x10, 0);
        }
    }
    fn_8007E154();
    fn_8007E7E8(0x80);
    fn_8007E164();
}

static inline void body(SlotDraw* o) {
    GXC tA2; GXC aA2; GXC tA1; GXC aA1;
    GXC tB2; GXC aB2; GXC tB1; GXC aB1;
    GXC tC2; GXC aC2; GXC tC1; GXC aC1;
    if (lbl_804CC031 > 0) return;
    hdr(0x80);
    first(o);
    group1(o, lbl_80430740[0], 76.0f, 35.0f, tA2, aA2, tA1, aA1);
    group2(o, lbl_80430740[1], 76.0f, 227.0f, tB2, aB2, tB1, aB1);
    group3(o, lbl_80430740[2], 76.0f, 419.0f, tC2, aC2, tC1, aC1);
    fn_8017A188(o->m3C);
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 800.0f, 1.0f);
    fn_8007E174(0, 0x12);
    fn_8007E7DC(0xFF);
    fn_8007E7E8(o->m4A ? 0x80 : 0x40);
    fn_8007E164();
    cursor(o);
}

#pragma inline_max_size(4000)
void fn_802687FC(SlotDraw* o) { body(o); }

}
