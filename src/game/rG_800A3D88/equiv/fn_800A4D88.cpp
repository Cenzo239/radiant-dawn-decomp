/* fn_800A4D88: battle camera target position by camera mode. Level: regs (in
   the two-target loop the counter and the two walking pointers sit in each
   other's saved registers; 7 words). Rewritten from wip/fn_800A4D88.cpp: the
   function and fn_800B3A1C return Vec by value (hidden pointer in r3), and
   the two-point cases write `r[n++] = ...`. */
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
Vec fn_800B3A1C(Tgt*, int, int);
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
Vec fn_800A4D88(Body* b) {
    Vec r[2];
    Vec sum = { 0.0f, 0.0f, 0.0f };
    int n = 0;
    Tgt* t;
    int i;
    Vec* p;
    t = Target(b);
    switch (b->m72 & 0xE000) {
    case 0:
    case 0x2000:
        if (t != NULL && fn_800BD280(t)) {
            return fn_800B3A1C(t, (b->m72 >> 10) & 1, -1);
        }
        break;
    case 0x4000:
    case 0x6000:
        for (p = r, i = 0; i < 2; i++, p++) {
            if (fn_800BD280(b->mA0[i])) {
                r[i] = fn_800B3A1C(b->mA0[i], (b->m72 >> 10) & 1, -1);
                fn_80313460(&sum, p, &sum);
                n++;
            }
        }
        sum.z = 0.0f;
        if (n > 0) fn_803134A8(&sum, &sum, 1.0f / (f32)n);
        return sum;
    case 0xA000:
        if (t != NULL && fn_800BD280(t)) t = t->m80;
    case 0x8000:
        if (t != NULL && fn_800BD280(t)) {
            r[n++] = fn_800B3A1C(t, (b->m72 >> 10) & 1, -1);
            t = t->m80;
        }
        if (t != NULL && fn_800BD280(t)) {
            r[n++] = fn_800B3A1C(t, (b->m72 >> 10) & 1, -1);
        }
        if (n == 2) {
            f32 w = fn_800A84A4(lbl_80365064 + 0x9B);
            sum.x = fn_8001EF30(r[1].x, r[0].x, 1.0f, w);
            sum.y = fn_8001EF30(r[1].y, r[0].y, 1.0f, w);
            sum.z = 0.0f;
        }
        return sum;
    }
    return b->m30;
}
}
