/* Body in a one-line wrapper: this puts the parameter below the unit in register order. */
#include "game/rC2_8005259C/base.h"
struct MU { u8 pad[0x102]; s8 x; s8 y; };
struct Ctx { MU* p0; u8 pad4[0xd]; s8 b11; s8 b12; };
struct GD { u8 pad[0x934]; f32 x; f32 y; };
extern "C" {
extern Ctx lbl_803CA870;
extern GD lbl_803CAB38;
int fn_800A1954(int, int);
void fn_800A1848(void*, int, int);
void fn_80083DC4(void*, int);
}

static inline void body(void* p) {
    MU* u = lbl_803CA870.p0;
    if (u->x != (s8)lbl_803CAB38.x || u->y != (s8)lbl_803CAB38.y) {
        GD* g = &lbl_803CAB38;
        s8 fx;
        s8 fy;
        fy = g->y;
        fx = g->x;
        if (fn_800A1954(fx, fy)) {
            s8 ax;
            s8 ay;
            ay = g->y;
            ax = g->x;
            fn_800A1848(p, ax, ay);
            {
                s8 by = u->y;
                s8 bx = u->x;
                lbl_803CA870.b11 = bx;
                lbl_803CA870.b12 = by;
            }
            {
                f32 ny = u->y;
                f32 nx = u->x;
                g->y = ny;
                g->x = nx;
            }
            fn_80083DC4(p, 7);
        }
    }
}
extern "C" void fn_80053704(void* q) {
    body(q);
}
