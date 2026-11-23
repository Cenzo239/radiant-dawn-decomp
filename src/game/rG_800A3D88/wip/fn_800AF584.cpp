// WIP, does not match: 36 lines in the first attempt with the F584 layout; i/j3 ranks swapped and one cmpwi scheduled early. Uses efflookup.h.
#include "game/rG_800A3D88/efflookup.h"

// Fade process on a battle character's tint.
extern "C" {
void fn_80008F10(Mdl*, u8, u8, u8);
void fn_80008F20(Mdl*, u8);
union ColW { Col c; u32 w; };
void fn_800C11B8(Eff*, ColW*);
struct TintP {
    u8 pad[0x30];
    ChrE* chr;
    Col a;
    Col b;
    int mode;
    int total;
    int t;
};
#define SET_TINT(c, v, t, q, i, x, y, j3, q3, j2, q2, j1, q1, j0, k3, r3, k2, r2, k1, r1, k0) \
    if (m != NULL) { \
        fn_80008F10(m, v.c.r, v.c.g, v.c.b); \
        fn_80008F20(c->mdl, v.c.a); \
        for (q = c, i = 0; i < 2; i++, ADV(q)) { \
            x = E4(c, i, q, j3, q3, j2, q2, j1, q1, j0, x); \
            if (x != NULL) { \
                y = E4(c, i, q, k3, r3, k2, r2, k1, r1, k0, y); \
                t.w = v.w; \
                fn_800C11B8(y, &t); \
            } \
        } \
    }
struct F584 { ColW v1, v2, t1, t2; };
#pragma use_lmw_stmw on
void fn_800AF584(TintP* p) {
/*P*/
int b_i;
ChrE* a_q3;
int b_j0;
int b_k3;
ChrE* a_q2;
int b_j1;
ChrE* b_r3;
ChrE* a_q1;
int b_j3;
int b_k0;
ChrE* c;
int a_j0;
Eff* b_x;
int b_k1;
ChrE* q;
int a_i;
int b_j2;
int b_k2;
int a_j3;
int a_j1;
ChrE* b_q1;
Eff* b_y;
int a_j2;
ChrE* b_q2;
ChrE* b_r2;
Eff* a_x;
ChrE* b_q3;
ChrE* b_r1;
/*E*/
    F584 f;
    Mdl* m;
    switch (p->mode) {
    case 1:
        c = p->chr;
        m = c->mdl;
        f.v1.c = p->a;
        SET_TINT(c, f.v1, f.t1, q, a_i, a_x, a_x, a_j3, a_q3, a_j2, a_q2, a_j1, a_q1, a_j0, a_j3, a_q3, a_j2, a_q2, a_j1, a_q1, a_j0)
        break;
    default:
        c = p->chr;
        m = c->mdl;
        f.v2.c = p->b;
        SET_TINT(c, f.v2, f.t2, q, b_i, b_x, b_y, b_j3, b_q3, b_j2, b_q2, b_j1, b_q1, b_j0, b_k3, b_r3, b_k2, b_r2, b_k1, b_r1, b_k0)
        break;
    }
}
}
