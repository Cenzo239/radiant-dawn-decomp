/* Weapon triangle and frame icon draw with animated arrows, split from fn_8006E610.cpp's helpers. */
#include "game/rO_80065D64/types.h"
#pragma auto_inline off
struct Tex {
    u32 d[8];
    u16 w;
    u16 h;
};
extern "C" {
extern void* lbl_804CB58C;
extern void fn_80006A64(void*, Tex*, u16);
extern u16 fn_80305DF8(Tex*);
extern u16 fn_80305E0C(Tex*);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E174(Tex*, int);
extern void fn_8007E720(f32);
extern void fn_8007E4E4(f32, f32, f32, f32);
extern void fn_8007E7DC(int);
extern void fn_800800D4(int);
extern void fn_80080330(f32, f32);
extern void fn_80080388(f32, f32, f32, f32);
extern void fn_80080410(f32, f32, f32, f32);
extern void fn_800804D4(int, int, int, int);
#if TARGET_PC
extern FE10_PROTO void fn_80080C24(p32arg);
#else
extern void fn_80080C24(int);
#endif
extern void fn_80080308(void);
extern Tex fn_8006E098(int x, int y, int w, int h, int u0, int v0, int u1, int v1, int color, u8 alpha, u16 id, int flags);

static inline void TexLoad(Tex* t, u16 id) {
    fn_80006A64(lbl_804CB58C, t, id);
    t->w = fn_80305DF8(t);
    t->h = fn_80305E0C(t);
}

static inline Tex Spr(int x, int y, int w, int h, int color, u8 alpha, u16 id, int flags) {
    Tex t;
    TexLoad(&t, id);
    fn_8007E154();
    fn_8007E174(&t, 0x11);
    fn_8007E164();
    if (w == -1) {
        w = t.w;
    }
    if (h == -1) {
        h = t.h;
    }
    return fn_8006E098(x, y, w, h, 0, 0, t.w, t.h, color, alpha, id, flags);
}

static inline Tex Spr3(int x, int y, int color, u8 alpha, u16 id, int flags) {
    Tex t0;
    TexLoad(&t0, id);
    int w = t0.w;
    int h = t0.h;
    Tex t;
    TexLoad(&t, id);
    fn_8007E154();
    fn_8007E174(&t, 0x11);
    fn_8007E164();
    if (w == -1) {
        w = t.w;
    }
    if (h == -1) {
        h = t.h;
    }
    return fn_8006E098(x, y, w, h, 0, 0, t.w, t.h, color, alpha, id, flags);
}

void fn_8006E610(int x, int y, int w, int h, int color, int f);

static inline Tex Spr3R(int x, int y, u16 id, int& w, int& h) {
    Tex t0;
    TexLoad(&t0, id);
    w = t0.w;
    h = t0.h;
    Tex t;
    TexLoad(&t, id);
    fn_8007E154();
    fn_8007E174(&t, 0x11);
    fn_8007E164();
    if (w == -1) {
        w = t.w;
    }
    if (h == -1) {
        h = t.h;
    }
    return fn_8006E098(x, y, w, h, 0, 0, t.w, t.h, 1, 0xFF, id, 0);
}
struct T9 { int v[3][3]; };
static const T9 sIc = {{{9, 11, 10}, {16, 17, 18}, {22, 19, 20}}};
static const T9 sOx = {{{32, 30, 28}, {9, 10, 11}, {55, 56, 57}}};
static const T9 sOy = {{{58, 58, 58}, {20, 19, 18}, {18, 19, 20}}};
extern u8 lbl_803CAB38[];
extern u8* fn_80060728(u8*);
extern int lbl_804CB590;
extern int fn_801D09F0(void);
class DB { u8 pad[0x44]; };
class Drawer : public DB {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18(int, int, int);
};
extern u8 lbl_803E7290[];
extern void fn_801BCA5C(f32);
void fn_800739A4(int k, f32 x, f32 y) {
    /*P*/
    int i;
    int px3;
    int py3;
    int h4;
    int h1;
    int w4;
    int b0;
    int a0;
    int b1;
    int a1;
    int b2;
    int px1;
    int py1;
    int h2;
    int px2;
    int py2;
    int h3;
    int px4;
    int py4;
    int px5;
    int py5;
    int px6;
    int py6;
    int h7;
    int w2;
    int w3;
    int h5;
    int a2;
    int w5;
    int row;
    int h8;
    int h6;
    int col;
    int w7;
    int w1;
    int w8;
    int w6;
/*E*/
    if (fn_80060728(lbl_803CAB38)[0x11] == 2) {
        return;
    }
    T9 ic = sIc;
    T9 ox = sOx;
    T9 oy = sOy;
    if (fn_801D09F0()) {
        ox.v[0][0] -= 2;
        ox.v[0][1] -= 2;
        ox.v[0][2] -= 2;
        ox.v[1][0] += 3;
        ox.v[1][1] += 3;
        ox.v[1][2] += 3;
        ox.v[2][0] -= 4;
        ox.v[2][1] -= 4;
        ox.v[2][2] -= 4;
    }
    switch (k) {
    case 0:
        row = 0;
        col = 0;
        break;
    case 2:
        row = 0;
        col = 1;
        break;
    case 1:
        row = 0;
        col = 2;
        break;
    case 6:
        row = 1;
        col = 0;
        break;
    case 8:
        row = 1;
        col = 1;
        break;
    case 7:
        row = 1;
        col = 2;
        break;
    case 9:
        row = 2;
        col = 1;
        break;
    case 10:
        row = 2;
        col = 2;
        break;
    case 3:
    case 4:
    case 5:
    default:
        return;
    }
    Spr3R(x, y, 0x1C, w1, h1);
    fn_801BCA5C(-1.0f);
    lbl_804CB590 = (lbl_804CB590 + 1) % 0x18;
    i = lbl_804CB590 / 8;
    b0 = oy.v[0][i];
    a0 = ox.v[0][i];
    py1 = y + b0;
    px1 = x + a0;
    Spr3R(px1, py1, 0x1D, w2, h2);
    b1 = oy.v[1][i];
    a1 = ox.v[1][i];
    py2 = y + b1;
    px2 = x + a1;
    Spr3R(px2, py2, 0x1E, w3, h3);
    b2 = oy.v[2][i];
    a2 = ox.v[2][i];
    py3 = y + b2;
    px3 = x + a2;
    Spr3R(px3, py3, 0x1F, w4, h4);
    ((Drawer*)lbl_803E7290)->v18(15.0f + (15.0f + x), 13.0f + (y - 9.0f), ic.v[row][col]);
    ((Drawer*)lbl_803E7290)->v18(15.0f + (38.0f + x), 13.0f + (30.0f + y), ic.v[row][(col + 1) % 3]);
    ((Drawer*)lbl_803E7290)->v18(15.0f + (x - 7.0f), 13.0f + (30.0f + y), ic.v[row][(col + 2) % 3]);
    fn_801BCA5C(1.0f);
    switch (k) {
    case 6:
    case 7:
    case 8:
        x -= 80.0f;
        Spr3R(x, y, 0x1C, w5, h5);
        fn_801BCA5C(-1.0f);
        py4 = y + b0;
        px4 = x + a0;
        Spr3R(px4, py4, 0x1D, w6, h6);
        py5 = y + b1;
        px5 = x + a1;
        Spr3R(px5, py5, 0x1E, w7, h7);
        py6 = y + b2;
        px6 = x + a2;
        Spr3R(px6, py6, 0x1F, w8, h8);
        ((Drawer*)lbl_803E7290)->v18(15.0f + (15.0f + x), 13.0f + (y - 9.0f), ic.v[2][0]);
        ((Drawer*)lbl_803E7290)->v18(15.0f + (38.0f + x), 13.0f + (30.0f + y), ic.v[2][1]);
        ((Drawer*)lbl_803E7290)->v18(15.0f + (x - 7.0f), 13.0f + (30.0f + y), ic.v[2][2]);
        fn_801BCA5C(1.0f);
    }
}
}
