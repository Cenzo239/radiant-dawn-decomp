/* wip near misses for fn_801DD7D4.cpp (whole file kept so declarations stay together):
   fn_801DE6E0: size 0x170, want 0x17C; 1 wrong reference(s); 61 of 92 words differ
*/
#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#pragma auto_inline off

extern "C" {

extern char lbl_8036ED48[];
void* fn_800E4060(const char*, int);
void fn_800E48AC(void*, f32, f32, f32);
void fn_800E4AD4(void*, f32);
void fn_800E4A40(void*, f32);
void fn_800E515C(void*);
void fn_800E56B8(void*);
void fn_80081A90(void*);
void fn_80079210(void*);
void fn_800453B4(void*, int);
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E7E8(int);
void fn_8007E174(int, int);
void fn_801D7560(int, int, int, int, int);
void fn_801D7988(int, int, int);
extern char lbl_803CA870[];
extern char lbl_8038C294[];

typedef struct GXColor { u8 r, g, b, a; } GXColor;

typedef struct Mdl { u8 pad0[8]; s16 x8; u8 pada[0x18-0xa]; u32 x18; u8 pad1c[0x64-0x1c]; GXColor col; } Mdl;
typedef struct Pfx { u8 pad0[0x30]; Mdl* x30; } Pfx;

class EffObj {
public:
    virtual void v08();
    virtual void v0C();
    virtual void init();
    virtual f32 scale();
    virtual int v18();
    virtual int v1C();
    Pfx* x4;
    int x8;
    u8 padc[0x18-0xc];
    f32 x18;
    u8 pad1c[0x20-0x1c];
    GXColor x20;
    f32 x24;
};

void fn_801DD7D4(EffObj* e) {
    e->init();
    e->x4 = (Pfx*)fn_800E4060(lbl_8036ED48, 4);
    e->x4->x30->x18 |= 0x101c;
}

void fn_801DD830(EffObj* e) {
    if (e->x4 != NULL) {
        fn_80081A90(e->x4);
    }
}

static inline void mdlSetColor(Mdl* m, GXColor c) {
    m->col = c;
}

void fn_801DDA8C(EffObj* e, f32 a, f32 b, f32 c) {
    f32 z = e->x24 + c;
    fn_800E48AC(e->x4, a, b, 0.0f);
    e->x4->x30->x8 = z;
    {
        f32 s = e->x18;
        f32 t = e->scale();
        fn_800E4AD4(e->x4, t * s);
    }
    mdlSetColor(e->x4->x30, e->x20);
    switch (e->x8) {
    case 3:
        break;
    case 0:
        fn_800E4A40(e->x4, 90.0f);
        break;
    case 2:
        fn_800E4A40(e->x4, 180.0f);
        break;
    case 1:
        fn_800E4A40(e->x4, 270.0f);
        break;
    }
    fn_800E515C(e->x4);
    fn_800E56B8(e->x4);
}

void fn_801DDBAC(EffObj* e) {
    e->init();
    e->x4 = (Pfx*)fn_800E4060(lbl_8036ED48 + 0xb, 4);
    e->x4->x30->x18 |= 0x101c;
}

int fn_801DDC0C(EffObj* e) { return 10; }
f32 fn_801DDC14(void) { return 0.05f; }
int fn_801DDCBC(EffObj* e) { return 0x10; }
int fn_801DDCC4(EffObj* e) { return 0x20; }
int fn_801DDD6C(EffObj* e) { return 0x16; }
int fn_801DDD74(EffObj* e) { return 0x16; }

void* fn_801DDD7C(void* p, int del) {
    if (p != NULL) {
        if (p != NULL) {
            *(void**)p = lbl_8038C294;
            ((VO0*)p)->v10();
        }
        if (del > 0) {
            fn_80079210(p);
        }
    }
    return p;
}

void fn_801DDDE8(void) { fn_800453B4(lbl_803CA870, 0); }

void fn_801DDDF8(VO4* p) {
    if (p != NULL) {
        p->v90(1);
    }
}

void* fn_80085EF8(int);
typedef struct Pos { u8 pad[0x30]; s16 x; s16 y; } Pos;
typedef struct LL { u8 pad[0x3c]; VO4* x3c; u8 ids[0x64]; s8 n; } LL;

void fn_801DDE18(VO4* o, LL* l) {
    int i;
    Pos* p;
    for (i = 0; i < l->n; i++) {
        p = (Pos*)fn_80085EF8(l->ids[i]);
        p->x += o->v98();
        p->y += o->v9C();
    }
}

void fn_801DE060(VO4* o, void* a) {

    int h;
    int m;
    o->v94();
    h = o->v54();
    if ((s16)h == 0) {
        {
        int n = o->vA0(a);
        m = o->v5C();
        h = m * n;
        }
        m = (s16)o->v4C() * 2;
        h = (s16)(m + h);
    }
    fn_801D7560(0, 0, (s16)o->v50(), (s16)h, 0x10);
    fn_8007E154();
    fn_8007E7E8(0x80);
    fn_8007E164();
}

typedef struct St { u8 pad[0x2d]; u8 x2d; u8 x2e; } St;

void fn_801DE348(void* o, St* s) {
    int b;
    fn_8007E154();
    fn_8007E174(0, 0x13);
    b = 0;
    if (s->x2d != 0 || s->x2e != 0) b = 1;
    fn_8007E7E8(!b ? 0x80 : 0x40);
    fn_8007E164();
}

void fn_801DEDCC(VO4* o) {
    o->v94();
    fn_801D7988(0, 0, 0x10);
    fn_8007E154();
    fn_8007E7E8(0x80);
    fn_8007E164();
}

void fn_801DEE18(void) {}

typedef struct St2 { u8 pad[0x38]; u8 x38; u8 x39; u8 pad3a[2]; VO4* x3c; } St2;

void fn_801DEE1C(void* o, void* a, St2* s) {
    fn_8007E154();
    fn_8007E174(0, 0x13);
    fn_8007E7E8(s->x38 != 0 ? 0x80 : 0x40);
    fn_8007E164();
}

void fn_80253EE4(int, f32);

int fn_801DF0D8(void* o, St2* a, St2* s) {
    if (s->x39 == 2) return 0x10;
    fn_800453B4(lbl_803CA870, 0x81);
    if (a->x3c->vA8() != 0) {
        fn_80253EE4(a->x3c->vA8(), 0.0f);
    }
    return 5;
}

int fn_801DF160(void* o, St2* a, St2* s) {
    if (s->x39 == 2) return 0x10;
    fn_800453B4(lbl_803CA870, 0x80);
    if (a->x3c->vAC() != 0) {
        fn_80253EE4(a->x3c->vAC(), 0.0f);
    }
    return 1;
}

void fn_801DF1E8(void) { fn_800453B4(lbl_803CA870, 0x80); }

void fn_8007E5C0(f32, f32, f32, f32, f32, f32, f32, f32);
void fn_8007E7DC(u8);
f32 fn_800D58FC(void*);
f32 fn_8017F68C(int, f32, f32, f32, f32);
void fn_801D7C18(int, int, int);
GXColor* fn_800CD204(int);
void fn_80080508(GXColor*);
void fn_80080ABC(int, f32);

void fn_801DDEC8(VO4* o, St* a) {
    f32 y, z, t, s;
    t = fn_800D58FC(a);
    s = fn_8017F68C(5, 0.0f, 1.0f, t, 1.0f);
    fn_8007E154();
    z = o->v70();
    y = (s16)o->v64();
    fn_8007E5C0((s16)o->v60(), y, z, 0.0f, 0.0f, s, s, 0.0f);
    fn_8007E7DC(255.99f * t);
    {
        int b = 0;
        if (a->x2d != 0 || a->x2e != 0) b = 1;
        fn_8007E7E8(!b ? 0x80 : 0x40);
    }
    fn_8007E164();
}

void fn_801DE3B8(void* o, void* a, St2* s) {
    if (s->x39 == 2) {
        GXColor c = *fn_800CD204(0);
        fn_80080508(&c);
    } else {
        GXColor c = *fn_800CD204(0x1d);
        fn_80080508(&c);
        fn_80080ABC(1, 2.0f);
    }
}

void fn_801DEC74(VO4* o, void* a) {
    f32 y, z, t, s;
    t = fn_800D58FC(a);
    s = fn_8017F68C(5, 0.0f, 1.0f, t, 1.0f);
    fn_8007E154();
    z = o->v70();
    y = (s16)o->v64();
    fn_8007E5C0((s16)o->v60(), y, z, 0.0f, 0.0f, s, s, 0.0f);
    fn_8007E7DC(255.99f * t);
    fn_8007E164();
}

void fn_801DF2D4(VO4* o, St* a) {
    f32 y, z, ay, ax, t, s;
    t = fn_800D58FC(a);
    s = fn_8017F68C(5, 0.0f, 1.0f, t, 1.0f);
    fn_8007E154();
    ax = (s16)o->v54() / 2;
    ay = (s16)o->v50() / 2;
    z = o->v70();
    y = (s16)o->v64();
    fn_8007E5C0((s16)o->v60(), y, z, ay, ax, s, s, 0.0f);
    fn_8007E7DC(255.99f * t);
    {
        int b = 0;
        if (a->x2d != 0 || a->x2e != 0) b = 1;
        fn_8007E7E8(!b ? 0x80 : 0x40);
    }
    fn_8007E164();
}

void fn_801DF4F4(VO4* o) {
    o->v94();
    fn_801D7C18(0, 0, 0x10);
}

#pragma use_lmw_stmw on
static inline void layoutGrid(LL* l, s16 x, s16 y, s16 w, s16 c, s16 h, s16 rr) {
    int r, n;
    int yo, xo, ry, i;
    n = 0;
    r = 0;
    yo = 0;
    for (; r < rr && n < l->n; r++) {
        ry = y + yo;
        i = 0;
        xo = 0;
        for (; i < c && n < l->n; i++, n++) {
            Pos* p = (Pos*)fn_80085EF8(l->ids[n]);
            p->x = x + xo;
            xo += w;
            p->y = ry;
        }
        yo += h;
    }
}

void fn_801DE6E0(VO4* o, LL* l) {
    int a, b, t;
    s16 x, y;
    int rows;
    a = o->v58();
    b = o->v5C();
    t = o->v98();
    x = o->v48() + t;
    t = o->v9C();
    y = o->v4C() + t;
    rows = o->vA0(l);
    layoutGrid(l, x, y, a, o->vA4(), b, rows);
}
#pragma use_lmw_stmw off

#pragma use_lmw_stmw on
void fn_801DF1F8(VO4* o, LL* l) {
    int i;
    Pos* p;
    s16 d;
    int t;
    s8 n;
    for (i = 0; i < l->n; i++) {
        p = (Pos*)fn_80085EF8(l->ids[i]);
        n = l->n;
        d = (s16)l->x3c->v50() / (n + 1);
        p->x = (i + 1) * d + l->x3c->v48();
        t = o->vC8();
        p->y = t - o->vCC();
    }
}
#pragma use_lmw_stmw off

}
