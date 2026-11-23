// fn_800C5A34 (round m4, m4-b): exact. From wip/fn_800C5A34.cpp: `bx += ...` compound adds keep x/y above bx/by,
// and reading the sheet size through `Dim** t` (one load, two derefs) puts t in r3 and w/h in r4/r5.
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
void fn_8007E41C(void*, int, int, int);
void fn_800800D4(int);
void fn_80080388(f32, f32, f32, f32);
void fn_80080410(f32, f32, f32, f32);
void fn_800804D4(u8, u8, u8, u8);
void fn_80080308();

void fn_800C5A34(Face* f, int x, int y, int a, int mode, int kind, int flag, f32 z) {
    FaceD* d = f->m34;
    u8 g = f->m41;
int tw;
int th;
s16 bx;
s16 by;
int n;
int w;
int h;
    if (x < 0 || x > 0x260) return;
    if (f->m30 == NULL) return;
    if (mode == 0 && (u16)d->m10 == (u16)d->m14) return;
    if (mode == 0) {
        bx = d->m10;
        n = 8;
        by = d->m12;
    } else {
        bx = d->m14;
        n = 0xB;
        by = d->m16;
    }
    int big = (f->m48 >> 12) & 1;
    if (big == 0) {
        bx = (s16)(bx - d->m1c);
        by = (s16)(by - d->m1e);
    }
    if (bx == -1) return;
    if (!(d->m20 & 2)) n -= 6;
    switch (kind) {
    case 1:
        n += 1;
        break;
    case 2:
        n += 2;
        break;
    case 0:
        break;
    }
    if (big == 0) {
        w = 0xC0;
        h = 0x80;
    } else {
        Dim** t = fn_80006A0C(f->m30, 1);
        w = (*t)->m2;
        h = (*t)->m0;
    }
    if (f->m48 & 1) bx = w - bx;
    bx += x - (w >> 1);
    by += y - h;
    Dim* t2 = *fn_80006A0C(f->m30, n);
    tw = t2->m2;
    th = t2->m0;
    if (f->m48 & 1) bx = bx - tw;
    fn_8007E154();
    if (flag != 0) fn_8007E4E4(0.0f, 0.0f, 96.0f + z, 1.0f);
    fn_8007E41C(f->m30, n, f->m40, 0x11);
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
