#include "game/rA_800068A0/types.h"
extern "C" {
typedef f32 Mtx[3][4];
typedef struct Vec { f32 x, y, z; } Vec;
typedef struct GXf { int mode; Vec pos; Vec rot; Vec scale; } GXf;
extern void fn_80312654(void* m, int axis, f32 a);
extern void fn_80312378(const void* a, const void* b, void* c);
extern void fn_80312344(const void* a, void* b);
extern void fn_8031292C(void* m, f32 x, f32 y, f32 z);
extern void fn_803128AC(void* m, f32 x, f32 y, f32 z);
extern void fn_803135A8(const void* q, void* m);
void fn_8001D44C(GXf* k, Mtx out) {
    Mtx sc, tr, rx, ry, rz;
    switch (k->mode) {
    case 1:
        fn_80312654(rx, 0x58, 0.017453292f * k->rot.x);
        fn_80312654(ry, 0x59, 0.017453292f * k->rot.y);
        fn_80312654(rz, 0x5A, 0.017453292f * k->rot.z);
        break;
    case 2:
        fn_80312654(rx, 0x59, 0.017453292f * k->rot.y);
        fn_80312654(ry, 0x5A, 0.017453292f * k->rot.z);
        fn_80312654(rz, 0x58, 0.017453292f * k->rot.x);
        break;
    case 3:
        fn_80312654(rx, 0x5A, 0.017453292f * k->rot.z);
        fn_80312654(ry, 0x58, 0.017453292f * k->rot.x);
        fn_80312654(rz, 0x59, 0.017453292f * k->rot.y);
        break;
    case 4:
        fn_80312654(rx, 0x58, 0.017453292f * k->rot.x);
        fn_80312654(ry, 0x5A, 0.017453292f * k->rot.z);
        fn_80312654(rz, 0x59, 0.017453292f * k->rot.y);
        break;
    case 5:
        fn_80312654(rx, 0x59, 0.017453292f * k->rot.y);
        fn_80312654(ry, 0x58, 0.017453292f * k->rot.x);
        fn_80312654(rz, 0x5A, 0.017453292f * k->rot.z);
        break;
    case 6:
        fn_80312654(rx, 0x5A, 0.017453292f * k->rot.z);
        fn_80312654(ry, 0x59, 0.017453292f * k->rot.y);
        fn_80312654(rz, 0x58, 0.017453292f * k->rot.x);
        break;
    case 8:
        fn_8031292C(sc, k->scale.x, k->scale.y, k->scale.z);
        fn_803128AC(tr, k->pos.x, k->pos.y, k->pos.z);
        fn_803135A8(&k->pos, rx);
        fn_80312378(rx, sc, out);
        fn_80312378(rx, out, out);
        fn_80312378(tr, out, out);
        return;
    case 7:
        fn_80312344(&k->pos, out);
        return;
    }
    fn_8031292C(sc, k->scale.x, k->scale.y, k->scale.z);
    fn_803128AC(tr, k->pos.x, k->pos.y, k->pos.z);
    fn_80312378(rx, sc, out);
    fn_80312378(ry, out, out);
    fn_80312378(rz, out, out);
    fn_80312378(tr, out, out);
}

extern s16 lbl_803B7878[];
extern void fn_803126D0(void* m, int axis, f32 s, f32 c);
extern void fn_80312318(void* m);
extern u32 fn_8028C1A0(f32 v);

#define ROT(v, ax) \
    if (0.0f != v) { \
        if (made) { \
            fn_80312654(t, ax, 0.017453292f * v); \
            fn_80312378(t, m, m); \
        } else { \
            fn_80312654(m, ax, 0.017453292f * v); \
            made = 1; \
        } \
    }
#define ROT0(v, ax) \
    if (0.0f != v) { \
        fn_80312654(m, ax, 0.017453292f * v); \
        made = 1; \
    }
#define WRAP(v) \
    if (v < 0.0f) { \
        v += (f32)(((int)v / 360 + 1) * 360); \
    }
#define SC(k, mm, ax) \
    { \
        fn_803126D0(mm, ax, 0.000061035156f * lbl_803B7878[k & 0x3FFF], 0.000061035156f * lbl_803B7878[(k + 0x1000) & 0x3FFF]); \
    }
#define ROTB(v, ax) \
    if (0.0f != v) { \
        u32 k; \
        WRAP(v); \
        k = fn_8028C1A0(2607.5945f * (0.017453292f * v)); \
        if (made) { \
            SC(k, t, ax); \
            fn_80312378(t, m, m); \
        } else { \
            SC(k, m, ax); \
            made = 1; \
        } \
    }
void fn_8001D748(Mtx m, int mode, f32 x, f32 y, f32 z) {
    BOOL made;
    Mtx t;
    made = 0;
    switch (mode) {
    case 1:
        ROT0(x, 0x58);
        ROT(y, 0x59);
        ROT(z, 0x5A);
        break;
    case 2:
    case 8:
        ROT0(y, 0x59);
        ROT(z, 0x5A);
        ROT(x, 0x58);
        break;
    case 3:
    case 9:
        ROT0(z, 0x5A);
        ROT(x, 0x58);
        ROT(y, 0x59);
        break;
    case 4:
    case 10:
        ROT0(x, 0x58);
        ROT(z, 0x5A);
        ROT(y, 0x59);
        break;
    case 5:
    case 11:
        ROT0(y, 0x59);
        ROT(x, 0x58);
        ROT(z, 0x5A);
        break;
    case 6:
    case 12:
        ROT0(z, 0x5A);
        ROT(y, 0x59);
        ROT(x, 0x58);
        break;
    case 7:
        if (0.0f != x) {
            u32 k;
            WRAP(x);
            k = fn_8028C1A0(2607.5945f * (0.017453292f * x));
            SC(k, m, 0x58);
            made = 1;
        }
        ROTB(y, 0x59);
        ROTB(z, 0x5A);
        break;
    }
    if (!made) {
        fn_80312318(m);
    }
}
}
