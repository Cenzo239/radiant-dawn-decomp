/* 800F1C30: registers only, m/v/j rotated (m r28, v r27, j r26 in the original), plus 800F1E9C was split out and matched. */
#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off
typedef struct Mm { u8 pad[0xC]; f32 x; f32 y; f32 z; u8 rest[0x94]; } Mm;
typedef struct Obj { u8 pad[0x30]; f32 x; f32 y; f32 z; f32 s; u8 pad40[0x10]; void* v50; u8 pad54; u8 c[4]; } Obj;
extern "C" {
extern u8 lbl_803674B4[];
extern u16 fn_80008D48(void*, const u16*);
extern u32 fn_80008CF0(void*, u16);
extern int fn_80008C98(void*, int);
extern int fn_80007630(void*, const char*);
extern Vec fn_800076E8(void*, int);
extern f32 fn_8000793C(void*, int);
extern void* fn_800078E4(void*, int);
extern void fn_8000DD0C(void*, void*, Mm*, f32);
extern Obj* fn_8017E3B4(void*);
extern Obj* fn_8017E460(void*);
extern void fn_8017E218(Obj*, int);
extern void fn_8017E22C(Obj*, int);
extern void fn_8017E244(Obj*, int);
extern void fn_8017EA78(int, int, int, int, int, void*);
static inline void Set(Obj* o, void* a, Vec p, f32 s, GXColor c) {
    o->x = p.x;
    o->y = p.y;
    o->z = p.z;
    o->s = s;
    o->c[0] = c.r;
    o->c[1] = c.g;
    o->c[2] = c.b;
    o->c[3] = c.a;
    o->v50 = a;
}
int fn_800F1C30(void* m, void* a, void* q) {
/*P*/
    int j;
    s16 v;
    u16 k;
    Obj* o;
/*E*/
    if (m == 0) return 0;
    const u16 t[] = {0x28, 0x29, 0x2A, 0xFFFF};
    k = fn_80008D48(m, t);
    if (k == 0xFFFF) return 0;
    v = fn_80008CF0(m, k);
    if (v == 0) v = 8;
    j = fn_80007630(m, (char*)lbl_803674B4 + 0x59E);
    if (j < 0) return 0;
    Vec p = fn_800076E8(m, j);
    f32 s = fn_8000793C(m, j);
    Mm mm;
    fn_8000DD0C(m, fn_800078E4(m, j), &mm, -1.0f);
    GXColor c = {(u8)(int)mm.x, (u8)(int)mm.y, (u8)(int)mm.z, 0xFF};
    o = 0;
    switch (k) {
    case 0x28:
        o = fn_8017E3B4(q);
        if (o) fn_8017E218(o, v);
        break;
    case 0x29:
        o = fn_8017E3B4(q);
        if (o) fn_8017E22C(o, v);
        break;
    case 0x2A:
        o = fn_8017E460(q);
        if (o) fn_8017E244(o, v);
        break;
    }
    if (o) {
        Set(o, a, p, s, c);
        return 1;
    }
    return 0;
}
}
