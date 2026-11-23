/* fn_801CCA38: model bounding box: transform the 8 corners of the def box (optionally squashed in y) and take min/max. */
#include "game/rF_8017F400/types.h"
extern "C" {
typedef struct Vec3 { f32 x, y, z; } Vec3;
typedef struct BDef { u8 pad[0xa0]; Vec3 lo; Vec3 hi; u32 fl; } BDef;
typedef struct BObj { u8 pad[0x10]; BDef* def; u8 pad14[0x24 - 0x14]; f32 mtx[3][4]; u8 pad54[0xb0 - 0x54]; Vec3 mn; Vec3 mx; } BObj;
extern Vec3 lbl_8036E994;
extern Vec3 lbl_8036E9A0;
extern void fn_80312DB4(void*, Vec3*, Vec3*);
void fn_801CCA38(BObj* o, f32 t) {
    BDef* d = o->def;
    Vec3 a = d->lo;
    Vec3 b = d->hi;
    Vec3 c[8];
    Vec3* p;
    int i;
    if (d->fl & 0x08000000) a.y = a.y - t * (b.y - a.y);
    c[0].x = a.x; c[0].y = a.y; c[0].z = a.z;
    c[1].x = b.x; c[1].y = a.y; c[1].z = a.z;
    c[2].x = a.x; c[2].y = b.y; c[2].z = a.z;
    c[3].x = b.x; c[3].y = b.y; c[3].z = a.z;
    c[4].x = a.x; c[4].y = a.y; c[4].z = b.z;
    c[5].x = b.x; c[5].y = a.y; c[5].z = b.z;
    c[6].x = a.x; c[6].y = b.y; c[6].z = b.z;
    c[7].x = b.x; c[7].y = b.y; c[7].z = b.z;
    { Vec3 k = lbl_8036E994; o->mn = k; }
    { Vec3 k = lbl_8036E9A0; o->mx = k; }
    for (i = 0, p = c; i < 8; i++, p++) {
        Vec3 r;
        fn_80312DB4(o->mtx, p, &r);
        if (o->mn.x > r.x) o->mn.x = r.x;
        if (o->mn.y > r.y) o->mn.y = r.y;
        if (o->mn.z > r.z) o->mn.z = r.z;
        if (o->mx.x < r.x) o->mx.x = r.x;
        if (o->mx.y < r.y) o->mx.y = r.y;
        if (o->mx.z < r.z) o->mx.z = r.z;
    }
}
}
