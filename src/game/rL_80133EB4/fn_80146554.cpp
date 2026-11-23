/* Weather particles: scatter new ones over the current view and queue the draw callback. */
#include "game/rL_80133EB4/types.h"
#pragma use_lmw_stmw off

struct Pt { s16 x, y, z; };
struct Ang { f32 a, r; };
struct Wx {
    u8 pad0[0x30];
    u8 x30;
    u8 pad31;
    u8 x32;
    u8 pad33;
    u16 x34;
    u8 pad36[0x40 - 0x36];
    Pt* x40;
    u8 pad44[4];
    Ang* x48;
};
struct Proc {
    u8 pad0[0x30];
    u8 x30;
    u8 pad31;
    u8 x32;
    u8 pad33[0x54 - 0x33];
    f32 x54;
    u8 pad58[4];
    f32 x5c;
    f32 x60;
    u8 pad64[4];
    f32 x68;
};
extern "C" {
extern u8 lbl_80386540[];
extern u8 lbl_803EC898[];
extern Proc* fn_80083B84(void*);
extern int fn_80068D74(void);
extern u32 fn_8017FA1C(void);
extern u32 fn_80089ED0(void);
extern f32 fn_801141D4(void*, int, int, int);
extern void fn_80145980(Wx*);
extern void fn_80010788(int, int, void (*)(Wx*), Wx*);

void fn_80146554(Wx* o) {
    /*P*/
    int i;
    int x0;
    int z0;
    int w;
    int d;
    Pt* q;
/*E*/
    Proc* pr = fn_80083B84(lbl_80386540);
    if (pr->x30 == 0) return;
    if (pr->x32 == 0 && fn_80068D74() == 0) return;
    x0 = 256.0f * pr->x54;
    z0 = 256.0f * pr->x5c;
    w = 256.0f * (pr->x60 - pr->x54);
    d = 256.0f * (pr->x68 - pr->x5c);
    { int idx = o->x34 * (fn_8017FA1C() & 7); q = &o->x40[idx]; }
    switch (pr->x32) {
    case 0: {
        f32 k = 256.0f;
        for (i = 0; i < o->x34; i++) {
            q->x = fn_80089ED0() % w;
            q->z = fn_80089ED0() % d;
            q->y = k * fn_801141D4(lbl_803EC898, (x0 + q->x) >> 8, (z0 + q->z) >> 8, 0);
            q++;
        }
        break;
    }
    case 1:
    case 2:
    case 3: {
        int zero = 0;
        for (i = 0; i < o->x34; i++) {
            q->x = fn_80089ED0() % w;
            q->z = fn_80089ED0() % d;
            q->y = zero;
            q++;
        }
        break;
    }
    case 4: {
        int zero = 0;
        for (i = 0; i < o->x34; i++) {
            q->x = fn_80089ED0() % w;
            q->z = fn_80089ED0() % d;
            q->y = zero;
            q++;
        }
        break;
    }
    }
    if (o->x30) {
        for (i = 0; i < o->x32; i++) {
            Ang* e = &o->x48[i];
            if (e->r >= 0.0f) continue;
            e->r = (i * 40) / o->x32;
            o->x48[i].a = fn_80089ED0() % 360;
        }
        o->x30 = 0;
    } else if ((fn_8017FA1C() & 3) == 0) {
        for (i = 0; i < o->x32; i++) {
            if (o->x48[i].r >= 0.0f) continue;
            {
                Ang* e = &o->x48[i];
                e->r = 40.0f;
                o->x48[i].a = fn_80089ED0() % 360;
                break;
            }
        }
    }
    fn_80010788(3, 0x9A, fn_80145980, o);
}
}
