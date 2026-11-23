/* fn_801813D0: world map x to widescreen x; fn_80183944: map country label. */
#include "game/rF_8017F400/types.h"
extern "C" {
typedef struct GMap { u8 pad[0x10]; f32 x10, x14, x18, x1c, x20; u8 pad24[0x34-0x24]; struct { u8 a, b; u8 pad[2]; void* obj; } lab[1]; u8 pad3c[0x248-0x3c]; void* x248; } GMap;
typedef struct Gfx { u8 pad[8]; u16 x8; u8 pada[0x18-0xa]; u32 x18; u8 pad1c[0x64-0x1c]; u8 x64, x65, x66, x67; } Gfx;
typedef struct Spr { u8 pad[0x30]; Gfx* g; } Spr;
extern int fn_801D09F0(void);
extern Spr* fn_800E3C04(const char*, void*);
extern void fn_800E48AC(Spr*, f32, f32, f32);
extern void fn_800E4AD4(Spr*, f32);
extern char lbl_8036BA4C[];
static inline f32 Wide(GMap* m, f32 x) {
    f32 lo, w, c, hi, off;
    if (fn_801D09F0() == 0) return x;
    c = (304.0f - m->x10) / m->x18;
    w = 608.0 / m->x18;
    lo = c - 0.5f * w;
    hi = c + 0.5f * w;
    off = 608.0f * ((0.5f * m->x20 - lo) / (hi - lo));
    return 0.7638191f * (x - off) + off;
}
f32 fn_801813D0(GMap* m, f32 x) {
    f32 w, lo, c, hi, off;
    if (fn_801D09F0() == 0) return x;
    c = (304.0f - m->x10) / m->x18;
    w = 608.0 / m->x18;
    lo = c - 0.5f * w;
    hi = c + 0.5f * w;
    off = 608.0f * ((0.5f * m->x20 - lo) / (hi - lo));
    return 0.7638191f * (x - off) + off;
}
}
