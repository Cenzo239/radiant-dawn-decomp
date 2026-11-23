#include "game/rC2_8005259C/base.h"
/* Camera path step (quadratic bezier) and map cursor helpers. */
struct Pt3 { f32 x, y, z; };
struct Node { u8 p[4]; Pt3 pos; };
struct Bez { u8 p[0x30]; Node* n; Pt3 a; Pt3 b; Pt3 c; u8 p58[2]; s16 t; s16 end; };
struct Vs { u8 pad[0x24]; f32 a, b, c; };
struct Job { u8 pad[0x89]; u8 kind; };
struct Cam {
    u8 pad[0x934];
    f32 x, y;
    f32 x2, y2, x3, y3;
    u8 p[0x94C - 0x94C + 0];
    f32 h;
};
struct Unit102 { u8 p[0x102]; s8 x, y; };
extern "C" {
extern u8 lbl_803EC898[];
void fn_80083B78(Bez*);
Job* fn_8010B094(u8);
f32 fn_801142F0(void*, f32, f32);
u32 fn_8028C418(u32, u32, u32, u32);
void fn_8006214C(Cam* c, Unit102* u) {
    f32 x; f32 y; y = u->y; x = u->x; y += 0.5f; x += 0.5f;
    c->y = y;
    c->x = x;
    f32 h = fn_801142F0(lbl_803EC898, x, y);
    f32 m = *(f32*)(lbl_803EC898 + 0x1D428);
    if (h > m) h = m;
    c->x2 = x;
    c->y2 = y;
    c->h = h;
    c->x3 = x;
    c->y3 = y;
}
void fn_80061808(Vs* v, f32 x) {
    Job* j = fn_8010B094(*((u8*)v + 0x10));
    switch (j->kind) {
    case 0: {
        f32 m = 999999.0f - v->b - v->c;
        if (x > m) x = m;
        if (x < 0.0f) x = 0.0f;
        v->a = x;
        break;
    }
    case 1: {
        f32 m = 999999.0f - v->a - v->c;
        if (x > m) x = m;
        if (x < 0.0f) x = 0.0f;
        v->b = x;
        break;
    }
    case 2: {
        f32 m = 999999.0f - v->a - v->b;
        if (x > m) x = m;
        if (x < 0.0f) x = 0.0f;
        v->c = x;
        break;
    }
    case 3: {
        f32 m = 999999.0f - v->a;
        if (x > m) x = m;
        if (x < 0.0f) x = 0.0f;
        v->c = x;
        v->b = 0.0f;
        break;
    }
    case 4:
        if (x > 999999.0f) x = 999999.0f;
        if (x < 0.0f) x = 0.0f;
        v->c = x;
        v->a = 0.0f;
        v->b = 0.0f;
        break;
    }
}
}
