#include "game/rG_800A3D88/types.h"

// Face portrait: draw one sprite from the face sheet, flipped if needed.
extern "C" {
struct Dim { u16 m0, m2; };
struct FaceD { u8 p[0x10]; s16 m10, m12, m14, m16; u16 m18, m1a, m1c, m1e, m20; };
struct Face { u8 p[0x30]; void* m30; FaceD* m34; u8 p38[8]; u8 m40, m41; u8 p42[6]; u32 m48; };
Dim** fn_80006A0C(void*, int);
void fn_8007E154();
void fn_8007E164();
void fn_8007E4E4(f32, f32, f32, f32);
#if TARGET_PC
FE10_PROTO void fn_8007E41C(void*, p32arg, int, int);
#else
void fn_8007E41C(void*, int, int, int);
#endif
void fn_800800D4(int);
void fn_80080388(f32, f32, f32, f32);
void fn_80080410(f32, f32, f32, f32);
void fn_800804D4(u8, u8, u8, u8);
void fn_80080308();

void fn_800C57B0(Face* f, int x, int y, int a, int k, int flag, f32 z) {
    FaceD* d = f->m34;
    u8 g = f->m41;
    int tw, th;
    int bx, by;
    int w, h;
    if (x < 0 || x > 0x260) return;
    if (f->m30 == NULL) return;
    if (!(f->m48 & 0x1000)) {
        w = 0xC0;
        h = 0x80;
        bx = d->m18 - d->m1c;
        by = d->m1a - d->m1e;
    } else {
        Dim* t = *fn_80006A0C(f->m30, 1);
        FaceD* e = f->m34;
        w = t->m2;
        h = t->m0;
        bx = e->m18;
        by = e->m1a;
    }
    if (f->m48 & 1) bx = w - bx;
    bx += x - (w >> 1);
    by += y - h;
    Dim* t2 = *fn_80006A0C(f->m30, k);
    tw = t2->m2;
    th = t2->m0;
    if (f->m48 & 1) bx = bx - tw;
    fn_8007E154();
    if (flag != 0) fn_8007E4E4(0.0f, 0.0f, 96.0f + z, 1.0f);
    fn_8007E41C(f->m30, k, f->m40, 0x11);
    fn_8007E164();
    z = tw;
    fn_800800D4(1);
    if (f->m48 & 1) {
        fn_80080388(bx, by, z, th);
        fn_80080410(tw, 0.0f, 0.0f, th);
    } else {
        fn_80080388(bx, by, z, th);
        fn_80080410(0.0f, 0.0f, tw, th);
    }
    fn_800804D4(g, g, g, a);
    fn_80080308();
}
}
