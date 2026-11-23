// WIP, does not match: 13/430 lines, right size. Only a_i (r24 wanted) against a_j1/a_k1 (r26 wanted) in the first case. Named ColW locals fixed the stack and the byte scheduling. Replaces wip/fn_800AF584.cpp.
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
#pragma use_lmw_stmw on
void fn_800AF584(TintP* p) {
/*P*/
ChrE* q;
int a_j3;
int a_k3;
int b_i;
Eff* a_x;
Eff* a_y;
int b_j0;
int b_k3;
int a_j2;
int a_i;
int a_k2;
int b_k2;
Eff* b_y;
int a_j0;
int a_j1;
int a_k1;
int b_j3;
int b_k0;
int a_k0;
Eff* b_x;
int b_k1;
ChrE* c;
int b_j2;
int b_j1;
ChrE* a_q1;
ChrE* a_r1;
ChrE* b_q1;
ChrE* b_r3;
ChrE* a_q2;
ChrE* a_r2;
ChrE* b_q2;
ChrE* b_r2;
ChrE* a_q3;
ChrE* a_r3;
ChrE* b_q3;
ChrE* b_r1;
/*E*/
    ColW t2; ColW t1; ColW v2; ColW v1;
    Mdl* m;
    switch (p->mode) {
    case 1:
        c = p->chr;
        m = c->mdl;
        v1.c = p->a;
        SET_TINT(c, v1, t1, q, a_i, a_x, a_y, a_j3, a_q3, a_j2, a_q2, a_j1, a_q1, a_j0, a_k3, a_r3, a_k2, a_r2, a_k1, a_r1, a_k0)
        break;
    default:
        c = p->chr;
        m = c->mdl;
        v2.c = p->b;
        SET_TINT(c, v2, t2, q, b_i, b_x, b_y, b_j3, b_q3, b_j2, b_q2, b_j1, b_q1, b_j0, b_k3, b_r3, b_k2, b_r2, b_k1, b_r1, b_k0)
        break;
    }
}
}
