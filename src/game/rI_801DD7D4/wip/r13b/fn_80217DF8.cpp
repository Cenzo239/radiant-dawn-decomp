#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#include "game/rI_801DD7D4/rlist.h"
#pragma auto_inline off
extern "C" {
struct C4 { u8 r, g, b, a; };
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E174(int, u32);
void fn_8007E720(f32);
void fn_8007E7E8(int);
void fn_8007E7DC(int);
void fn_8007E7B4(void);
int fn_800CB0FC(f32, int);
const char* fn_800D0864(const char*);
int fn_800CA3DC(f32, const char*, int);
void fn_800CB278(int, int, int, const char*, ...);
void fn_800800D4(int);
void fn_80080ABC(int, f32);
void fn_80080308(void);
void fn_80080330(f32, f32);
void fn_80080508(C4);
void fn_80080C24(const char*);
void fn_80080910(void*, void*);
u8 fn_80110DA8(void*);
u8 fn_80110E00(void*);
u8 fn_80110E58(void*);
u8 fn_80110EB0(void*);
u32* fn_801E2204(void*, s16*, s16*);
void fn_8031292C(void*, f32, f32, f32);
void fn_803128E0(void*, void*, f32, f32, f32);
void fn_80008F10(void*, int, int, int);
void fn_80008F20(void*, int);
void fn_80007C58(void*);
f32 fn_801E33B4(void*);
f32 fn_801E3468(void*);
void fn_802170E8(void* p);
extern char lbl_80371974[];
typedef void (RObj::*MF)(int);
struct FnT { MF f; int arg; };
extern MF lbl_8038F77C;
struct Slot { int a0; int a4; int a8; };
struct Sci { s16 x, y, w, h; void* a8; };
struct N3 { u8 p[0x30]; f32 sy, sz; u8 p38[4]; N3* parent; };
class MV { public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(void*); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); virtual int v38(); virtual int v3C();
    virtual int v40(); virtual int v44(); virtual int v48(); virtual int v4C(); virtual int v50(); virtual int v54(); virtual int v58(); virtual int v5C(); virtual int v60(int, int, const char*, int);
    int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26, a28; u8 p2a[2]; f32 sx, sy, sz; u32 flags; N3* parent; int a40; LNode* a44; LNode* a48; u8 p4c[8]; s16 a54; u8 p56[2]; s16 a58, a5a, a5c, a5e; Sci* a60; u8* a64; u8 p68[4]; u8* a6c; u8 a70[0x28]; int a98;
};
static inline FnT forEach(LNode* n, LNode* e, FnT f) {
    while (n != e) {
        (n->val->*f.f)(f.arg);
        n = n->next;
    }
    return f;
}
#define CHAIN(o, fld, fn, v0, v1, v2, v3) { \
    N3* p; N3* q; N3* r; N3* t; \
    v0 = (o)->fld; p = (o)->parent; \
    if (p) { v1 = p->fld; q = p->parent; if (q) { v2 = q->fld; r = q->parent; if (r) { v3 = r->fld; t = r->parent; if (t) { v3 *= fn(t); } v2 *= v3; } v1 *= v2; } v0 *= v1; } \
}
static inline void setR(MV* o, s16 a, s16 b, s16 c, s16 d) { o->a58 = a; o->a5a = b; o->a5c = c; o->a5e = d; }
void fn_80217DF8(MV* o, void* c) {
    f32 e, d, b, a;
/*P*/
    int col;
    s16 x;
    u16 sel;
    int y;
    int k;
    const char* base;
    LNode* sent;
    int rh;
    int yo;
    Slot* s;
    s16 yy;
    s16 w;
    int off;
    int i;
    const char* str;
    s16 sw;
    const char* s2;
/*E*/
    o->v5C();
    o->v18(c);
    yo = (0x20 - fn_800CB0FC(1.0f, -1)) >> 1;
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E174(0, (u16)(o->flags | 3));
    fn_8007E164();
    s = (Slot*)(o->a6c + o->a98 * 0x78);
    sel = o->v34();
    y = yo + 0xc;
    k = 0;
    base = lbl_80371974;
    for (i = 0; i < 10; i++, s++) {
        if (s->a8 != 0) {
            col = 0;
            if ((s16)k++ == (s16)sel) col = 0x1d;
            str = fn_800D0864((const char*)s->a4);
            fn_800CB278((0x5f - (s16)fn_800CA3DC(1.0f, str, -1)) >> 1, (s16)y, col, base + 0x93, str);
            y += 0x1c;
        }
    }
    x = o->tx + 0x65;
    yy = o->ty + 0x3a;
    w = (s16)(o->ix1 - o->ix0) - 0x65 - o->tx * 2;
    rh = o->a54;
    off = (rh - fn_800CB0FC(1.0f, -1)) >> 1;
    s2 = fn_800D0864(lbl_80371974 + 0x98);
    sw = fn_800CA3DC(1.0f, s2, -1);
    fn_800800D4(5);
    fn_80080330((f32)(x + ((w - sw) >> 1)), (f32)(yy + off));
    {
        C4 col = {0xa2, 0x7a, 0x5c, 0xff};
        fn_80080508(col);
    }
    fn_80080ABC(1, 2.0f);
    fn_80080C24(s2);
    fn_80080308();
    yy += o->a54;
    o->v60(x, yy, lbl_80371974 + 0xb1, fn_80110DA8(o->a70));
    yy += o->a54;
    o->v60(x, yy, lbl_80371974 + 0xb8, fn_80110E00(o->a70));
    yy += o->a54;
    o->v60(x, yy, lbl_80371974 + 0xbf, fn_80110E58(o->a70));
    yy += o->a54;
    o->v60(x, yy, lbl_80371974 + 0xc7, fn_80110EB0(o->a70));
    setR(o, 0x65, 0, o->ix1 - o->ix0, o->ty + 0x3a);
    fn_801E2204(o, &o->a58, &o->a58);
    fn_801E2204(o, &o->a5c, &o->a5c);
    fn_8007E154();
    fn_8007E164();
    o->a60->x = o->x0 + o->ix0 + 0x65;
    o->a60->y = o->y0 + o->iy0;
    o->a60->w = (s16)(o->ix1 - o->ix0) - 0x65;
    o->a60->h = o->ty + 0x3a;
    o->a60->a8 = o->a64;
    {
        f32 m[12];
        fn_8031292C(m, 1.0f, 1.0f, 1.0f);
        fn_803128E0(m, o->a64 + 0x10, 0.0f, 0.0f, -10.0f);
    }
    fn_80008F10(o->a64, 0x80, 0x80, 0x80);
    CHAIN(o, sy, fn_801E33B4, a, b, d, e)
    fn_80008F20(o->a64, (u8)(255.99f * a));
    fn_80007C58(o->a64);
    fn_8007E154();
    fn_8007E174(0, (u16)(o->flags | 0x410));
    CHAIN(o, sy, fn_801E33B4, e, d, b, a)
    fn_8007E7DC((u8)(255.99f * e));
    CHAIN(o, sz, fn_801E3468, e, d, b, a)
    fn_8007E7E8((u8)(128.99f * e));
    fn_8007E164();
    fn_800800D4(0xb);
    fn_80080910(fn_802170E8, o->a60);
    fn_80080308();
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
    {
        FnT g;
        g.f = lbl_8038F77C;
        g.arg = (int)c;
        sent = (LNode*)&o->a44;
        forEach(o->a48, sent, g);
    }
}
}
