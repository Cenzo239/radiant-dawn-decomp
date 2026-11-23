#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#include "game/rI_801DD7D4/rlist.h"
#pragma auto_inline off
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
#if TARGET_PC
FE10_PROTO void fn_8007E74C(ptr32<const void>, ptr32<const void>);
#else
void fn_8007E74C(void*, void*);
#endif
void fn_8007E7E8(int);
void fn_8007E7DC(int);
void fn_8007E7B4(void);
int fn_800CB0FC(f32, int);
const char* fn_800D0864(const char*);
int fn_800CA3DC(f32, const char*, int);
int fn_800CA7A4(f32, const char*, int);
void fn_800CB278(int, int, int, const char*, ...);
void fn_801E6DA0(int, int, int, const char*, ...);
void fn_800800D4(int);
void fn_80080308(void);
void fn_80080508(C4);
#if TARGET_PC
FE10_PROTO void fn_80080910(ptr32<const void>, ptr32<const void>);
#else
void fn_80080910(void*, void*);
#endif
void fn_80080B00(int, void*, f32);
void fn_80080A94(f32);
void fn_800804F4(int);
C4* fn_800CD204(int);
void fn_80176F7C(int, int, int, int, int);
void fn_80176EA8(int, int, int, const char*);
const char* fn_8010F5E0(void*);
#if TARGET_PC
FE10_PROTO int fn_801E733C(ptr32<const void>);
#else
int fn_801E733C(void*);
#endif
void fn_80291CEC(int, char*, int);
int fn_80110DA8(void*);
int fn_80110E00(void*);
int fn_80110E58(void*);
int fn_80110EB0(void*);
u32* fn_801E2204(void*, s16*, s16*);
void fn_801E2104(void* p, void* arg);
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
extern MF lbl_8038F7B0;
struct Sci { s16 x, y, w, h; void* a8; };
struct N3 { u8 p[0x30]; f32 sy, sz; u8 p38[4]; N3* parent; };
struct It { u8 p0[5]; u8 b0 : 2; u8 fl : 1; u8 b3 : 5; u8 p6[0x18]; s8 a1e, a1f, a20, a21; };
class MV { public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(void*); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); virtual int v38(); virtual int v3C();
    virtual int v40(); virtual int v44(); virtual int v48(); virtual int v4C(); virtual int v50(); virtual int v54(); virtual int v58(); virtual int v5C(); virtual int v60(int, s16, s16, const char*, u8, int);
    int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26, a28; u8 p2a[2]; f32 sx, sy, sz; u32 flags; N3* parent; int a40; LNode* a44; LNode* a48; u8 p4c[8]; s16 a54; u8 p56[2]; s16 a58, a5a, a5c, a5e; Sci* a60; u8* a64; u8 p68[8]; It* a70;
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
#define GET(p, f) ((p)->fl ? (p)->f : 0)
static inline void setR(MV* o, s16 a, s16 b, s16 c, s16 d) { o->a58 = a; o->a5a = b; o->a5c = c; o->a5e = d; }
void fn_8021ABE4(MV* o, void* c) {
    f32 e, d, b, a;
/*P*/
    s16 x;
    int y;
    int v;
/*E*/
    ((VO0N*)o)->v5C();
    o->v18(c);
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E174(0, (u16)(o->flags | 3));
    fn_8007E164();
    y = (s16)(o->ty + 0x4e);
    x = o->tx;
    fn_800CB0FC(1.0f, -1);
    fn_8007E154();
    fn_8007E174(0, (u16)(o->flags | 3));
    fn_8007E164();
    v = GET(o->a70, a1e);
    o->v60(0, x, y, lbl_80371974 + 0xb1, (u8)fn_80110DA8(o->a70), v);
    y += o->a54;
    v = GET(o->a70, a1f);
    o->v60(1, x, y, lbl_80371974 + 0xb8, (u8)fn_80110E00(o->a70), v);
    y += o->a54;
    v = GET(o->a70, a20);
    o->v60(2, x, y, lbl_80371974 + 0xbf, (u8)fn_80110E58(o->a70), v);
    y += o->a54;
    v = GET(o->a70, a21);
    o->v60(3, x, y, lbl_80371974 + 0xc7, (u8)fn_80110EB0(o->a70), v);
    setR(o, 0, 0, o->ix1 - o->ix0, o->ty + 0x4e);
    fn_801E2204(o, &o->a58, &o->a58);
    fn_801E2204(o, &o->a5c, &o->a5c);
    fn_8007E154();
    fn_8007E74C(fn_801E2104, &o->a58);
    fn_8007E164();
    o->a60->x = o->x0 + o->ix0;
    o->a60->y = o->y0 + o->iy0;
    o->a60->w = o->ix1 - o->ix0;
    o->a60->h = o->ty + 0x4e;
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
        LNode* sent;
        g.f = lbl_8038F7B0;
        g.arg = (int)c;
        sent = (LNode*)&o->a44;
        forEach(o->a48, sent, g);
    }
}
}
