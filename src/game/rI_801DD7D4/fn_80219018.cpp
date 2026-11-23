#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/rlist.h"
#pragma auto_inline off
#pragma pool_strings on
extern "C" {
struct C4 { u8 r, g, b, a; };
void fn_8007E154(void);
void fn_8007E164(void);
#if TARGET_PC
FE10_PROTO void fn_8007E174(p32arg, u32);
#else
void fn_8007E174(int, u32);
#endif
void fn_8007E720(f32);
void fn_8007E7E8(int);
void fn_8007E7DC(int);
int fn_800CB0FC(f32, int);
const char* fn_800D0864(const char*);
int fn_800CA3DC(f32, const char*, int);
void fn_800800D4(int);
void fn_80080308(void);
void fn_80080330(f32, f32);
void fn_80080508(C4);
#if TARGET_PC
FE10_PROTO void fn_80080910(ptr32<const void>, ptr32<const void>);
#else
void fn_80080910(void*, void*);
#endif
void fn_80080ABC(int, f32);
void fn_80080C24(const char*);
C4* fn_800CD204(int);
void fn_80176EA8(int, int, int, const char*);
void fn_8031292C(void*, f32, f32, f32);
void fn_803128E0(void*, void*, f32, f32, f32);
void fn_80008F10(void*, int, int, int);
void fn_80008F20(void*, u8);
void fn_80007C58(void*);
f32 fn_801E33B4(void*);
f32 fn_801E3468(void*);
void fn_802170E8(void* p);
int fn_801120C0(void*, int);
int fn_8011215C(void*, int);
int fn_80112214(void*, int);
int fn_801122C8(void*, int);
void fn_801DA184(s16, s16, s16, int);
void fn_801DA230(int, int, int);
void fn_801DA2C0(int, int, int);
void fn_801DBA68(s16, s16, s16, s16, u8, int);
extern f32 lbl_804CBF00;
typedef void (RObj::*MF)(void*);
struct FnT { MF f; void* arg; };
extern MF lbl_8038F7A4;
struct Sci { s16 x, y, w, h; void* a8; };
struct N3 { u8 p[0x30]; f32 sy, sz; u8 p38[4]; N3* parent; };
struct Sb { u8 p[0x1c]; u8 a1c, a1d, a1e, a1f; };
struct It { Sb* s; u8 p4; u8 b0 : 2; u8 fl : 1; u8 b3 : 5; u8 p6[0x18]; s8 a1e, a1f, a20, a21; };
class EV { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(u32); void* a4; u8 p8[0x20]; };
class MV { public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(void*); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); virtual int v38(); virtual int v3C();
    virtual int v40(); virtual int v44(); virtual int v48(); virtual int v4C(); virtual int v50(); virtual int v54(); virtual int v58(); virtual int v5C(void*); virtual int v60(); virtual int v64(); virtual void v68(int, int, int, const char*, int, int, int);
    int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26, a28; u8 p2a[2]; f32 sx, sy, sz; u32 flags; N3* parent; int a40; LNode a44; u8 p50[4]; s16 a54; u8 p56[0xa]; Sci* a60; u8* a64; u8 p68[8]; It* a70; u8 p74[4]; EV e[4];
};
static inline FnT forEach(LNode*& n, LNode* e, FnT f) {
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
#define GET(p, f) ((p)->fl ? (p)->f : 0)
#define SCALE(k) fn_8007E154(); fn_8007E720(k); fn_8007E164();
#define FLAGS(o, m) fn_8007E154(); fn_8007E174(0, (u16)(o->flags | m)); fn_8007E164();
static const C4 kCol = {0x60, 0x64, 0x6b, 0xff};
void dummy1(const char** p) {
    *p = "FSHOP_ITEMS_%s";
    *p = "xwp/";
    *p = "forge/";
    *p = "_b.cmp";
    *p = "_b.g";
    *p = "_b.gs";
    *p = "_b.tpl";
    *p = "SFX_SYS_CURSOR_WINDOW_MOVE1";
    *p = "MESS_FORGE_KIND";
    *p = "MESS_FORGE_POINT";
    *p = "MESS_FORGE_ABLE";
    *p = "MESS_SHOPINFO_NUM";
    *p = "#E%s";
    *p = "MESS_FORGE_INITIAL_PARAM";
    *p = "MP_POW";
    *p = "MP_HIT";
    *p = "MP_CRIT";
    *p = "MP_WGT";
    *p = "MESS_SHOPINFO_GOLD";
    *p = "MESS_FORGE_COLOR";
    *p = "MMM_DECIDE";
    *p = "MMM_GOBACK";
}
void fn_80219018(MV* o, void* a) {
    f32 c, b, d, e;
/*P*/
    int v1;
    int b2;
    int b3;
    int ty;
    int x;
    int h;
    It* u;
    int y;
    int t1;
    int v2;
    LNode* n;
    int v3;
    int v4;
    int b1;
    int b4;
    int x2;
    LNode* sent;
/*E*/
    o->v5C(a);
    o->v18(a);
    x = o->tx;
    y = o->ty;
    h = o->a54;
    ty = (h - fn_800CB0FC(1.0f, -1)) >> 1;
    fn_800CA3DC(1.0f, fn_800D0864("MESS_SHOPINFO_GOLD"), -1);
    u = o->a70;
    if (u->fl) v1 = u->a1e; else v1 = 0;
    b1 = u->s->a1c;
    o->v68(x, y, 0, "MP_POW", b1, v1, (s16)fn_801120C0(u, -1));
    y += o->a54;
    if (u->fl) v2 = u->a1f; else v2 = 0;
    b2 = u->s->a1d;
    o->v68(x, (s16)y, 1, "MP_HIT", b2, v2, (s16)fn_8011215C(u, -1));
    y += o->a54;
    if (u->fl) v3 = u->a20; else v3 = 0;
    b3 = u->s->a1f;
    o->v68(x, (s16)y, 2, "MP_CRIT", b3, v3, (s16)fn_80112214(u, -1));
    y += o->a54;
    if (u->fl) v4 = u->a21; else v4 = 0;
    b4 = u->s->a1e;
    o->v68(x, (s16)y, 3, "MP_WGT", b4, v4, (s16)fn_801122C8(u, -1));
    FLAGS(o, 3)
    fn_800800D4(5);
    fn_80080330(x, ty + 0x98);
    fn_80080508(kCol);
    fn_80080ABC(1, 2.0f);
    fn_80080C24(fn_800D0864("MESS_FORGE_COLOR"));
    fn_80080308();
    {int v = o->v64(); fn_801DA184(x + 0x48, ((h - 0x13) >> 1) + 0x98, v, 0x10);}
    SCALE(-1.0f)
    t1 = (0x20 - fn_800CB0FC(1.0f, -1)) >> 1;
    fn_801DA2C0(x, 0xc4, 0x10);
    FLAGS(o, 3)
    SCALE(-0.5f)
    fn_800800D4(5);
    fn_80080508(*fn_800CD204(6));
    fn_80080ABC(1, 2.0f);
    x2 = x + 0x33;
    fn_80176EA8(x2, t1 + 0xc4, 2, fn_800D0864("MMM_DECIDE"));
    fn_80080308();
    SCALE(0.5f)
    t1 = (0x20 - fn_800CB0FC(1.0f, -1)) >> 1;
    fn_801DA230(x, 0xe5, 0x10);
    FLAGS(o, 3)
    SCALE(-0.5f)
    fn_800800D4(5);
    fn_80080508(*fn_800CD204(1));
    fn_80080ABC(1, 2.0f);
    fn_80176EA8(x2, t1 + 0xe5, 2, fn_800D0864("MMM_GOBACK"));
    fn_80080308();
    SCALE(0.5f)
    o->e[0].v2C(o->flags);
    o->e[1].v2C(o->flags);
    o->e[2].v2C(o->flags);
    o->e[3].v2C(o->flags);
    if ((s16)o->v34() == 4) {
        lbl_804CBF00 += 0.1f;
        if (lbl_804CBF00 > 1.0f) lbl_804CBF00 = 1.0f;
    } else {
        lbl_804CBF00 -= 0.1f;
        if (lbl_804CBF00 < 0.0f) lbl_804CBF00 = 0.0f;
    }
    if (u != NULL) {
        SCALE(-5.0f)
        o->a60->x = o->x0 + o->ix0;
        o->a60->y = o->y0 + o->iy0;
        o->a60->w = (s16)(o->ix1 - o->ix0) - 0x58;
        o->a60->h = 0x98;
        o->a60->a8 = o->a64;
        {
            f32 m[12];
            fn_8031292C(m, 1.0f, 1.0f, 1.0f);
            fn_803128E0(m, o->a64 + 0x10, 0.0f, 0.0f, -18.0f);
        }
        fn_80008F10(o->a64, 0x80, 0x80, 0x80);
        CHAIN(o, sy, fn_801E33B4, c, b, d, e)
        fn_80008F20(o->a64, 255.9f * lbl_804CBF00 * c);
        fn_80007C58(o->a64);
        fn_8007E154();
        fn_8007E174(0, (u16)(o->flags | 0x410));
        CHAIN(o, sy, fn_801E33B4, e, d, b, c)
        fn_8007E7DC((u8)(255.99f * e));
        CHAIN(o, sz, fn_801E3468, e, d, b, c)
        fn_8007E7E8((u8)(128.99f * e));
        fn_8007E164();
        fn_800800D4(0xb);
        fn_80080910(fn_802170E8, o->a60);
        fn_80080308();
        SCALE(5.0f)
    }
    SCALE(-2.0f)
    fn_801DBA68(o->tx >> 1, o->ty >> 1, (s16)(o->ix1 - o->ix0) - 0x58 - o->tx, 0x98 - o->ty, 255.9f * lbl_804CBF00, 0x10);
    SCALE(2.0f)
    {
        FnT ft;
        ft.f = lbl_8038F7A4;
        ft.arg = a;
        sent = &o->a44;
        forEach((n = o->a44.next), sent, ft);
    }
}
}
