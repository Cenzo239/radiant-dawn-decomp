// WIP, does not match: 72 lines: t/qb must outrank both parameters; b r29, out r28. Everything else is right.
#include "game/rG_800A3D88/chr.h"

// Battle camera: target position by camera mode.
extern "C" {
struct Tgt { u8 p[0x80]; Tgt* m80; };
struct Body {
    u8 p[0x30];
    Vec m30;
    u8 p3c[0x72 - 0x3C];
    u16 m72;
    u8 p74[0x94 - 0x74];
    Tgt* m94;
    Tgt* m98;
    u8 p9c[4];
    Tgt* mA0[2];
};
extern char lbl_80365064[];
int fn_800BD280(Tgt*);
void fn_800B3A1C(Vec*, Tgt*, int, int);
void fn_80313460(Vec*, Vec*, Vec*);
void fn_803134A8(Vec*, Vec*, f32);
f32 fn_800A84A4(const char*);
f32 fn_8001EF30(f32, f32, f32, f32);
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
struct W3 { u32 a, b, c; };
union VU { Vec v; W3 w; };
struct F4D88 { Vec v3, v2, v1; VU sum; Vec r[2]; };
void fn_800A4D88(Vec* out, Body* b) {
    F4D88 f;
/*P*/
int n;
Tgt* t;
Body* qb;
Vec* p;
Vec* q;
int i;
/*E*/
    f.sum.w.a = 0;
    n = 0;
    f.sum.w.b = 0;
    f.sum.w.c = 0;
    t = Target(b);
    switch (b->m72 & 0xE000) {
    case 0:
    case 0x2000:
        if (t != NULL && fn_800BD280(t)) {
            fn_800B3A1C(out, t, (b->m72 >> 10) & 1, -1);
            return;
        }
        break;
    case 0x4000:
    case 0x6000:
        for (q = p = f.r, qb = b, i = 0; i < 2; i++, q++, p++, qb = (Body*)((u8*)qb + 4)) {
            if (fn_800BD280(qb->mA0[0])) {
                fn_800B3A1C(&f.v1, qb->mA0[0], (b->m72 >> 10) & 1, -1);
                *p = f.v1;
                fn_80313460(&f.sum.v, q, &f.sum.v);
                n++;
            }
        }
        f.sum.v.z = 0.0f;
        if (n > 0) fn_803134A8(&f.sum.v, &f.sum.v, 1.0f / (f32)n);
        *(W3*)out = f.sum.w;
        return;
    case 0xA000:
        if (t != NULL && fn_800BD280(t)) t = t->m80;
    case 0x8000:
        if (t != NULL && fn_800BD280(t)) {
            fn_800B3A1C(&f.v2, t, (b->m72 >> 10) & 1, -1);
            n = 1;
            f.r[0] = f.v2;
            t = t->m80;
        }
        if (t != NULL && fn_800BD280(t)) {
            fn_800B3A1C(&f.v3, t, (b->m72 >> 10) & 1, -1);
            f.r[n].x = f.v3.x;
            f.r[n].y = f.v3.y;
            f.r[n].z = f.v3.z;
            n++;
        }
        if (n == 2) {
            f32 w = fn_800A84A4(lbl_80365064 + 0x9B);
            f.sum.v.x = fn_8001EF30(f.r[1].x, f.r[0].x, 1.0f, w);
            f.sum.v.y = fn_8001EF30(f.r[1].y, f.r[0].y, 1.0f, w);
            f.sum.v.z = 0.0f;
        }
        *(W3*)out = f.sum.w;
        return;
    }
    *out = b->m30;
}
}
