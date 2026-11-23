#include "game/rG_800A3D88/efflookup.h"

// Fade process on a battle character's tint (colour blend, step counter).
// The blend returns a 4-byte colour struct by value (stored byte-wise with r0);
// returning u32 and splitting it by hand gives the wrong registers.
// Local order from a hill climb; the effect lookup is the hand-unfolded E4 (see NOTES.md).
extern "C" {
struct Rgba { u8 r, g, b, a; };
f32 fn_8001EF44(f32, f32, int, int);
f32 fn_8001EBC8(f32, f32, f32, f32, int);
Rgba fn_80175E7C(Rgba*, Rgba*, f32);
void fn_80008F10(Mdl*, u8, u8, u8);
void fn_80008F20(Mdl*, u8);
void fn_800C11B8(Eff*, Col*);
void fn_80083B78(void*);
struct TintP {
    u8 pad[0x30];
    ChrE* chr;
    Rgba a;
    Rgba b;
    int mode;
    int total;
    int t;
};
static inline void MdlTint(ChrE* c, Col* v) {
    fn_80008F10(c->mdl, v->r, v->g, v->b);
    fn_80008F20(c->mdl, v->a);
}
void fn_800AF12C(TintP* p) {
    Col t1; Col t2; Rgba tb; Rgba ta;
    int i;
    int j0;
    int j1;
    Eff* y;
    int j2;
    int k2;
    int k3;
    Eff* x;
    ChrE* c;
    int k1;
    int j3;
    int k0;
    ChrE* q1;
    ChrE* r3;
    ChrE* q;
    ChrE* q2;
    ChrE* r2;
    ChrE* q3;
    ChrE* r1;
    f32 f;
    p->t++;
    switch (p->mode) {
    case 1:
        f = fn_8001EF44(0.0f, 1.0f, p->total, p->t);
        break;
    default:
        f = fn_8001EBC8(0.0f, 1.0f, p->total, p->t, 2);
        break;
    }
    tb = p->b;
    ta = p->a;
    Rgba col = fn_80175E7C(&ta, &tb, f);
    c = p->chr;
    *(u32*)&t2 = *(u32*)&col;
    if (c->mdl != NULL) {
        MdlTint(c, &t2);
        for (q = c, i = 0; i < 2; i++, ADV(q)) {
            x = E4(c, i, q, j3, q3, j2, q2, j1, q1, j0, x);
            if (x != NULL) {
                y = E4(c, i, q, k3, r3, k2, r2, k1, r1, k0, y);
                *(u32*)&t1 = *(u32*)&col;
                fn_800C11B8(y, &t1);
            }
        }
    }
    if (p->t >= p->total) fn_80083B78(p);
}
}
