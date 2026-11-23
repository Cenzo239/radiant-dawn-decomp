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
int fn_800F1E9C(void* m, void* q) {
    if (m == 0) return 0;
    if (fn_80008C98(m, 0x49)) {
        u32 v = fn_80008CF0(m, 0x49);
        u16 a = v & 0x3FF;
        int b = (v >> 10) & 0x3F;
        fn_8017EA78(0, a, a, b, 0, q);
        fn_8017EA78(1, a, a, b, 0, q);
        fn_8017EA78(2, a, a, b, 0, q);
        fn_8017EA78(3, a, a, b, 0, q);
        return 1;
    }
    return 0;
}
}
