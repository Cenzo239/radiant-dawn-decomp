// WIP, does not match: 7 lines: one float register in the x/y/z store after fn_8001EF30 (y in f3, then f3 reloaded with the 1.0f argument).
#include "game/rG_800A3D88/chr.h"

// Battle camera: recompute the target position and view flags.
extern "C" {
struct Tgt { u8 p[0x54]; s8 m54; u8 p55[0x78 - 0x55]; void* m78; u8 p7c[4]; Tgt* m80; };
struct Body {
    u8 p[0x30];
    Vec m30;
    u8 p3c[0x60 - 0x3C];
    f32 m60, m64, m68;
    u8 p6c[3];
    u8 m6f;
    u8 p70[2];
    u16 m72;
    u8 p74[0x94 - 0x74];
    Tgt* m94;
    Tgt* m98;
    Tgt* m9c;
    Tgt* mA0[2];
};
extern char lbl_80365064[];
struct W3 { u32 a, b, c; };
void* fn_800A7460(void*, const char*);
void fn_800A4D88(W3*, Body*);
f32 fn_800A5120(Body*);
f32 fn_8001EF30(f32, f32, f32, f32);
f32 fn_800A526C(Body*);
int fn_800BD280(Tgt*);
void fn_800B056C(Tgt*);
void fn_800B08B0(Tgt*);
static inline Tgt* Target(Body* b) {
    Tgt* t = b->m98;
    if (t == NULL) return NULL;
    switch (b->m72 & 0xE000) {
    case 0:
    case 0x4000:
    case 0x8000:
    case 0xA000:
        return t;
    case 0x2000:
        return t->m80;
    case 0x6000:
        return b->m94;
    }
    return NULL;
}
static inline void Set(Vec* d, f32 x, f32 y, f32 z) { d->x = x; d->y = y; d->z = z; }
static inline void Set2(Body* d, f32 x, f32 y, f32 z) { d->m30.x = x; d->m30.y = y; d->m30.z = z; }
static inline void Set3(Body* d, f32 x, const Vec& v) { d->m30.x = x; d->m30.y = v.y; d->m30.z = v.z; }
static inline void Slide(Body* b, const Vec& a, f32 v) { b->m30.x = fn_8001EF30(b->m30.x, a.x, 1.0f, 0.125f); b->m30.y = a.y; b->m30.z = a.z; b->m60 = fn_8001EF30(b->m60, v, 1.0f, 0.125f); }
static inline void Ap(f32& x, f32 t) { x = fn_8001EF30(x, t, 1.0f, 0.125f); }
static inline void Ap2(f32* x, f32 t) { *x = fn_8001EF30(*x, t, 1.0f, 0.125f); }
static inline f32 Ap3(f32 x, f32 t) { return fn_8001EF30(x, t, 1.0f, 0.125f); }
struct F47AC { Vec r0; Vec r1; Vec a1; };
void fn_800A47AC(Body* b, int mode) {
    F47AC f;
/*P*/
Tgt* t;
Tgt* u;
Body* q2;
Body* q;
bool side;
int i;
int i2;
/*E*/
    side = 0;
    t = Target(b);
    if (t != NULL) {
        if (t->m54 == 1) side = 1;
        if (t->m78 != NULL && fn_800A7460(t->m78, lbl_80365064 + 0xF) != NULL) {
            side = side == 0;
        }
    }
    b->m6f = side;
    if (mode != 0) {
        fn_800A4D88((W3*)&f.r1, b);
        *(W3*)&f.a1 = *(W3*)&f.r1;
        f32 v = fn_800A5120(b);
        f32 nx, z, y;
        nx = fn_8001EF30(b->m30.x, f.a1.x, 1.0f, 0.125f);
        y = f.a1.y;
        z = f.a1.z;
        b->m30.x = nx;
        b->m30.y = y;
        b->m30.z = z;
        b->m60 = fn_8001EF30(b->m60, v, 1.0f, 0.125f);
    } else {
        fn_800A4D88((W3*)&f.r0, b);
        b->m30 = f.r0;
        b->m60 = fn_800A5120(b);
    }
    b->m64 = 1.0f;
    b->m68 = fn_800A526C(b);
    if (b->m72 & 0x100) {
        for (q = b, i = 0; i < 2; i++, q = (Body*)((u8*)q + 4)) {
            u = q->mA0[0];
            if (fn_800BD280(u)) {
                if (u == Target(b)) fn_800B056C(u);
                else fn_800B08B0(u);
            }
        }
    } else {
        for (q2 = b, i2 = 0; i2 < 2; i2++, q2 = (Body*)((u8*)q2 + 4)) {
            if (fn_800BD280(q2->mA0[0])) fn_800B056C(q2->mA0[0]);
        }
    }
    b->m9c = t;
}
}
