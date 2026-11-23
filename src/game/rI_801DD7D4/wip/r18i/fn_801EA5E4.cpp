/* WIP (round 18): class `other`, 418 of 418 instructions, 10 masked diff lines, all in the third
   colour clamp before fn_80008F10: the original keeps the min/max pointer in r3 and loads o->a4c
   after the last dereference; ours puts the pointer in r6 and loads o->a4c one instruction early
   (and so swaps the lo/hi stores). Everything else, including stack slots, is identical. */
/* fn_801EA5E4: draw of the unit summary box (name, class, level/exp, HP) with the 3-D unit
   portrait model placed and tinted by the widget's inherited scale/alpha chain. */
#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
void fn_801D8CB4(int, int, int);
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E174(int, u32);
void fn_8007E720(f32);
void fn_8007E7B4(void);
void fn_8007E7DC(int);
const char* fn_80118C44(void*);
const char* fn_80118F48(void*);
const char* fn_80118F00(void*);
int fn_800CA3DC(f32, const char*, int);
void fn_801E6DA0(int, int, int, const char*, ...);
void fn_801E6EE8(int, int, int, int, const char*, ...);
u8* fn_8024BC94(void);
int fn_80126B0C(void*);
int fn_801237EC(void*);
void fn_80312654(f32*, int, f32);
void fn_80312378(f32*, f32*, f32*);
void fn_80312954(f32*, f32*, f32, f32, f32);
void fn_803128E0(f32*, void*, f32, f32, f32);
f32 fn_801E33B4(void*);
f32 fn_801E3468(void*);
void fn_80008F10(void*, int, int, int);
void fn_80008F20(void*, int);
void fn_80008F64(void*, int);
void fn_800081D4(void*);
void fn_80007C58(void*);
void fn_800F629C(void*, void*);
void fn_800F7E40(int);
void fn_800800D4(int);
void fn_80080910(void*, void*);
void fn_80080308(void);
void fn_8001A4DC(void* p);
void fn_801E6D88(void);
extern char lbl_8036EF28[];
}
struct Vec { f32 x, y, z; };
struct Unit { u8 p[0xec]; void* xec; void* xf0; u8 pf4[0xa]; s8 xfe; u8 pff[0x15]; s8 x114; };
extern "C" Vec fn_800FB178(Unit*, f32);
struct N3 { u8 p[0x30]; f32 sy, sz; u8 p38[4]; N3* parent; };
class MV { public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(void*);
    int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26, a28; u8 p2a[2];
    f32 sx, sy, sz; u32 flags; N3* parent; Unit* a40; u8 p44[8]; u8* a4c;
};
#define CHAIN(o, fld, fn, v0, v1, v2, v3) { \
    N3* p; N3* q; N3* r; N3* t; \
    v0 = (o)->fld; p = (o)->parent; \
    if (p) { v1 = p->fld; q = p->parent; if (q) { v2 = q->fld; r = q->parent; if (r) { v3 = r->fld; t = r->parent; if (t) { v3 *= fn(t); } v2 *= v3; } v1 *= v2; } v0 *= v1; } \
}
static inline const int& Max(const int& a, const int& b) { return a < b ? b : a; }
static inline const int& Min(const int& a, const int& b) { return a < b ? a : b; }
static inline int clampC(u8 c, f32 k) {
    int v = (int)(c * k);
    int hi = 0xff;
    int lo = 0;
    return Min(Max(lo, v), hi);
}
struct C3 { u8 r, g, b; C3(u8 r_, u8 g_, u8 b_) : r(r_), g(g_), b(b_) {} };
extern "C" void fn_801EA5E4(MV* o, void* c) {
    f32 a, b, d, e;
    Unit* u;
    const char* s;
    f32 x, y;
    o->v14();
    fn_801D8CB4(0, 0, 0x10);
    o->v18(c);
    u = o->a40;
    if (u == NULL) return;
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E174(0, (u16)(o->flags | 3));
    fn_8007E164();
    s = fn_80118C44(u->xec);
    fn_801E6DA0((0xbc - (s16)fn_800CA3DC(1.0f, s, -1)) >> 1, -0x14, 0x1f, s);
    if ((s8)fn_8024BC94()[0x1bc8] == 0) {
        s = fn_80118F48(u->xf0);
        if (s != NULL) {
            fn_801E6EE8(9, (s16)(0xc0 - ((s16)fn_800CA3DC(1.0f, s, 5) >> 1)), 4, 0x1f, s);
        }
    }
    s = fn_80118F00(u->xf0);
    fn_801E6DA0((s16)(0xc0 - ((s16)fn_800CA3DC(1.0f, s, -1) >> 1)), 0x18, 0x1f, s);
    fn_801E6DA0(0x9c, 0x36, 0x1f, lbl_8036EF28 + 5, u->xfe);
    if ((u8)fn_80126B0C(u) != 0xff) {
        fn_801E6DA0(0xea, 0x36, 0x1f, lbl_8036EF28 + 5, (u8)fn_80126B0C(u));
    } else {
        fn_801E6DA0(0xea, 0x36, 0x1f, lbl_8036EF28 + 9);
    }
    fn_801E6DA0(0x9c, 0x52, 0x1f, lbl_8036EF28 + 0xe, u->x114);
    fn_801E6DA0(0xd6, 0x52, 0xc, lbl_8036EF28 + 0x14, (s16)fn_801237EC(u));
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
    {
        f32 m1[12];
        f32 m2[12];
        x = 64.0f + o->x0;
        y = 70.0f + o->y0;
        Vec v = fn_800FB178(u, 1.0f);
        x += v.x;
        y += v.y;
        fn_80312654(m1, 'y', -0.5235988f);
        fn_80312654(m2, 'x', 3.6651914f);
        fn_80312378(m2, m1, m2);
        fn_80312954(m2, m2, 3.5f, 3.5f, 3.5f);
        fn_803128E0(m2, o->a4c + 0x10, x, y, o->a26);
    }
    CHAIN(o, sz, fn_801E3468, a, b, d, e)
    {
        C3 k(0x80, 0x80, 0x80);
        u8 cr = clampC(k.r, a);
        u8 cg = clampC(k.g, a);
        int cb = clampC(k.b, a);
        fn_80008F10(o->a4c, cr, cg, (u8)cb);
    }
    CHAIN(o, sy, fn_801E33B4, a, b, d, e)
    fn_80008F20(o->a4c, (u8)(255.99f * a));
    fn_80008F64(o->a4c, 0xff);
    fn_800081D4(o->a4c);
    fn_80007C58(o->a4c);
    fn_800F629C(u, o->a4c);
    fn_800F7E40(o->a26 - 2);
    fn_8007E154();
    fn_8007E174(0, (u16)(o->flags | 0x400));
    fn_8007E720(1.0f);
    CHAIN(o, sy, fn_801E33B4, a, b, d, e)
    fn_8007E7DC((u8)(255.99f * a));
    fn_8007E164();
    fn_800800D4(0xb);
    fn_80080910(fn_8001A4DC, o->a4c);
    fn_80080308();
    fn_8007E154();
    fn_8007E720(1.0f);
    fn_8007E164();
    fn_800800D4(0xb);
    fn_80080910(fn_801E6D88, 0);
    fn_80080308();
}
