#include "game/rG_800A3D88/types.h"

// Face portrait: blink timer and sprite choice for the eyes.
extern "C" {
struct FaceD { u8 p[0x25]; u8 m25; };
struct Face { u8 p[0x34]; FaceD* m34; f32 m38, m3c; u8 m40, m41, m42; u8 p43[5]; u32 m48; };
struct Blink { u8 p[0x30]; Face* m30; s16 m34, m36; };
int fn_80089C88(int);
void fn_800C57B0(Face*, int, int, int, int, int, f32);
void fn_800C6468(Blink* b) {
    Face* f = b->m30;
    f32 z = f->m34->m25 / 255.0f;
    u32 fl = f->m48;
    if (fl & 0x80) z += f->m40;
    if (fl & 0x20000) z -= 1.0f;
    if (fl & 0x40000) z += 1.0f;
    if (b->m36 > 0) {
        b->m36--;
        if (b->m36 == 0) {
            b->m36 = fn_80089C88(8) + 1;
            b->m34 = (b->m34 + 1) & 3;
        }
    }
    u32 g = b->m30->m48;
    int k = 2;
    if (g & 0x800) k = 5;
    switch (b->m34) {
    case 0:
        if (g & 0x20) b->m36 = -1;
        break;
    case 1:
    case 3:
        k += 1;
        if (g & 0x10) b->m36 = -1;
        break;
    case 2:
        k += 2;
        if (g & 8) b->m36 = -1;
        break;
    }
    fn_800C57B0(f, (int)f->m38, (int)f->m3c, f->m42, k, 1, z);
}
}
