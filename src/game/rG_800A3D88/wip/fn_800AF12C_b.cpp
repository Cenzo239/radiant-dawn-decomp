// WIP, does not match: 7/278 lines, right size. Only the three byte shifts after fn_80175E7C: ours get r5/r4/r0, the original reuses r0 for each store. About 30 spellings of the byte stores did not move it. Replaces wip/fn_800AF12C.cpp.
#include "game/rG_800A3D88/efflookup.h"

// Fade process on a battle character's tint (Col fields, step counter).
extern "C" {
f32 fn_8001EF44(f32, f32, int, int);
f32 fn_8001EBC8(f32, f32, f32, f32, int);
u32 fn_80175E7C(Col*, Col*, f32);
void fn_80008F10(Mdl*, u8, u8, u8);
void fn_80008F20(Mdl*, u8);
void fn_800C11B8(Eff*, Col*);
void fn_80083B78(void*);
struct TintP {
    u8 pad[0x30];
    ChrE* chr;
    Col a;
    Col b;
    int mode;
    int total;
    int t;
};
static inline void ColSet(Col* c, u32 v) {
    c->r = v >> 24;
    c->g = v >> 16;
    c->b = v >> 8;
    c->a = v;
}
static inline void MdlTint(ChrE* c, Col* v) {
    fn_80008F10(c->mdl, v->r, v->g, v->b);
    fn_80008F20(c->mdl, v->a);
}
static inline Col MkC(u32 v) { Col c; c.r = v >> 24; c.g = v >> 16; c.b = v >> 8; c.a = v; return c; }
static inline void ColR(Col& c, u32 v) { c.r = v >> 24; c.g = v >> 16; c.b = v >> 8; c.a = v; }
static inline void ColV(Col* c, const u32& v) { c->r = v >> 24; c->g = v >> 16; c->b = v >> 8; c->a = v; }
static inline void ColB(Col* c, u8 r, u8 g, u8 b, u8 a) { c->r = r; c->g = g; c->b = b; c->a = a; }
static inline u8 R0(u32 v) { return v >> 24; }
static inline u8 R1(u32 v) { return v >> 16; }
static inline u8 R2(u32 v) { return v >> 8; }
static inline u8 R3(u32 v) { return v; }
static inline u32 S0(u32 v) { return v >> 24; }
static inline u32 S1(u32 v) { return v >> 16; }
static inline u32 S2(u32 v) { return v >> 8; }
static inline void SetB(u8& d, u8 v) { d = v; }
static inline void SetI(u8* d, u32 v, int s) { *d = v >> s; }
void fn_800AF12C(TintP* p) {
    Col t1; Col t2; Col tb; Col ta; Col col;
/*P*/
int i;
ChrE* c;
int j0;
int k3;
int j1;
Eff* y;
int j2;
ChrE* q;
int k2;
Eff* x;
int k1;
int j3;
int k0;
ChrE* q1;
ChrE* r3;
ChrE* q2;
ChrE* r2;
ChrE* q3;
ChrE* r1;
/*E*/
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
    u32 v = fn_80175E7C(&ta, &tb, f);
    ColSet(&col, v);
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
