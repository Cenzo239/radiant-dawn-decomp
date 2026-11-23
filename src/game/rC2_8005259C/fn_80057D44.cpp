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
void fn_80057D44(Bez* b) {
    f32 k;f32 u;f32 t;f32 uu;f32 tt;f32 ax;f32 ay;f32 az;f32 bx;f32 by;f32 bz;f32 cx;f32 cy;f32 cz;f32 x;f32 y;f32 z;
    
    bx=b->b.x; by=b->b.y; t = (f32)b->t / (f32)b->end;
    ax=b->a.x; bz=b->b.z; ay=b->a.y; cx=b->c.x; az=b->a.z; cy=b->c.y; cz=b->c.z;
    u = 1.0f - t;
    tt = t * t; k = 2.0f * u * t; uu = u * u;
x = cx * tt + (ax * uu + bx * k); y = cy * tt + (ay * uu + by * k); z = cz * tt + (az * uu + bz * k);
    Node* n = b->n;
    n->pos.x = x;
    n->pos.y = y;
    n->pos.z = z;
    if (b->t++ == b->end) {
        fn_80083B78(b);
    }
}
}
