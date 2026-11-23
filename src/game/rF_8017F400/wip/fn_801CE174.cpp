/* near miss (round 17): fn_801CE174, 21 lines: stack slots (want v 0x8, t1 0x14, t2 0x20, arg copy 0x2c) and the lim/v-load registers. */
/* fn_801CE174: name label update: pick the anchor offset by screen half, then clamp the label y to the row. */
#include "game/rF_8017F400/types.h"
extern "C" {
typedef struct Vec3 { f32 x, y, z; } Vec3;
typedef struct LObj { u8 pad[0x1c]; Vec3 v; u8 pad28[0x4c - 0x28]; Vec3 off; } LObj;
typedef struct LLab { u8 pad[0x30]; LObj* o; u8 pad34[2]; s16 row; u8 pad38[2]; s16 x3a; s16 x3c; u8 pad3e[2]; s8 x40; } LLab;
extern Vec3 lbl_8036E9E8;
extern Vec3 lbl_8036E9F4;
extern void fn_800106AC(int, void*, void*);
extern void fn_801CDD5C(void*);
extern void fn_800E48C8(void*, Vec3);
static inline void SetOff(LLab* p, const Vec3& k) { Vec3 t = k; p->o->off = t; }
static inline void Clamp(LLab* p) {
    Vec3 v = p->o->v;
    int lim = p->x3c + p->row * 0x24;
    if (v.y < lim) v.y += 6.0f;
    if (v.y > lim) v.y -= 6.0f;
    fn_800E48C8(p, v);
}
void fn_801CE174(LLab* p) {
    if (p->x3a > 0x130) { Vec3 t = lbl_8036E9E8; p->o->off = t; } else { Vec3 t = lbl_8036E9F4; p->o->off = t; }
    if (p->x40) fn_800106AC(0, (void*)fn_801CDD5C, p);
    Clamp(p);
}
}
