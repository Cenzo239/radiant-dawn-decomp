/* fn_80183944 (map country label): exact (round m6). fn_801813D0 (same Wide() body) is in its own file.
   Lever: the halved red byte is a named int computed BEFORE the zero-initialised colour temp
   (`int r = col[0] >> 1; LCol c = {0,0,0,0}; c.r = r; c.g = col[1] >> 1; ...`), so it gets r5 and the zero r4,
   with the byte stores in r,g,b order. */
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
typedef struct LCol { u8 r, g, b, a; } LCol;
static inline void SetC(Gfx* g, LCol c) { g->x64 = c.r; g->x65 = c.g; g->x66 = c.b; g->x67 = c.a; }
static inline void Half(Spr* s, u8* col) {
    int r = col[0] >> 1;
    LCol c = { 0, 0, 0, 0 };
    c.r = r; c.g = col[1] >> 1; c.b = col[2] >> 1;
    SetC(s->g, c);
}
void fn_80183944(
#if TARGET_PC
GMap* m, int idx, int x, int y, fe10_rgba colv, f32 sc
#else
GMap* m, int idx, int x, int y, u8* col, f32 sc
#endif
) {
#if TARGET_PC
    u8* col = (u8*)&colv;
#endif
    /*P*/
    Spr* s;
    GMap* e;
/*E*/
    e = (GMap*)((u8*)m + idx * 8);
    e->lab[0].a = 1;
    e->lab[0].b = 0;
    e->lab[0].obj = fn_800E3C04(lbl_8036BA4C + 0x8d, m->x248);
    s = (Spr*)e->lab[0].obj;
    fn_800E48AC(s, Wide(m, x), y, 0.0f);
    s->g->x8 = 0x3a7;
    fn_800E4AD4(s, 0.2f * sc);
    Half(s, col);
    s->g->x18 |= 0x08001004;
}
}
