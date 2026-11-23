#include "game/rG_800A3D88/types.h"

// Font: draw glyph idx from a sheet as one quad.
extern "C" {
extern const f32 lbl_804CD630;
extern const f64 lbl_804CD620, lbl_804CD628;
double fn_80295AA4(double, double);
void fn_80304314(int, int, int);
struct Font {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual int v11(); virtual void v12(); virtual int v13(); virtual int v14(); virtual int v15(); virtual int v16();
};
static inline f32 Round(f32 v) {
    f32 d = fn_80295AA4(lbl_804CD620, lbl_804CD628);
    return (f32)(int)(d * (v + lbl_804CD630 / d)) / d;
}
static inline void pos3(f32 x, f32 y, f32 z) { *(volatile f32*)0xCC008000 = x; *(volatile f32*)0xCC008000 = y; *(volatile f32*)0xCC008000 = z; }
static inline void col4(u8 r, u8 g, u8 b, u8 a) { *(volatile u8*)0xCC008000 = r; *(volatile u8*)0xCC008000 = g; *(volatile u8*)0xCC008000 = b; *(volatile u8*)0xCC008000 = a; }
static inline void tex2(f32 u, f32 v) { *(volatile f32*)0xCC008000 = u; *(volatile f32*)0xCC008000 = v; }
void fn_800C99DC(Font* r, int i, const u8* c, f32 x, f32 y, f32 z) {
    if (i >= 0) {
        x = Round(x);
        y = Round(y);
        f32 u = (i % r->v11()) * r->v13();
        f32 v = (i / r->v11()) * r->v14();
        f32 tw = r->v13();
        f32 th = r->v14();
        f32 w = r->v15();
        f32 h = r->v16();
        fn_80304314(0x80, 0, 4);
        pos3(x, y, z);
        col4(c[0], c[1], c[2], c[3]);
        tex2(u, v);
        pos3(x + w, y, z);
        col4(c[0], c[1], c[2], c[3]);
        tex2(u + tw, v);
        pos3(x + w, y + h, z);
        col4(c[0], c[1], c[2], c[3]);
        tex2(u + tw, v + th);
        pos3(x, y + h, z);
        col4(c[0], c[1], c[2], c[3]);
        tex2(u, v + th);
    }
}
}
