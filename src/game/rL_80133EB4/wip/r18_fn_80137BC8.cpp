/* fn_80137BC8 (round 18): other. From wip/near3.cpp with the eight corner-height stores written back in and the real .rodata values in front (the six Vecs of fn_80134F90). Same size; 20 masked lines differ: scheduling of the address temporaries in the tile copy (volatile register dependent) and one li/addi swap. */
/* ===== fn_80137BC8: 23 words: volatile registers in the tile copy ===== */
#include "game/rL_80133EB4/types.h"
struct MM { u8 pad[0x4C]; u8 x4c, x4d; u8 pad4e[0x8A - 0x4E]; char name[1]; };
struct N { s16 v[4]; void* x8; };
struct Map { u8 p[0x20000]; };
extern "C" {
extern const char lbl_803694D4[];
extern u8 lbl_803EC898[];
extern void fn_80290DDC(char*, const char*, ...);
extern int fn_80076F54(char*);
extern void* fn_80077064(char*);
extern u8 fn_8011D1E4(void*);
extern f32 fn_801146A8(void*, int, int, int);
extern void fn_80114818(void*, int, int);
extern void fn_80114850(void*, int, int);
extern void fn_8031356C(Vec*, Vec*, Vec*);
extern void fn_803134C4(Vec*, Vec*);
extern f32 fn_8031354C(Vec*, Vec*);
/* The six Vecs used by fn_80134F90 come first in this file's .rodata (real values). */
static const Vec sF0 = {10000.0f, 10000.0f, 10000.0f};
static const Vec sF1 = {-10000.0f, -10000.0f, -10000.0f};
static const Vec sF2 = {-0.25f, -0.25f, 0.0f};
static const Vec sF3 = {0.25f, 0.25f, 0.0f};
static const Vec sF4 = {-1.0f, -1.0f, 0.0f};
static const Vec sF5 = {1.0f, 1.0f, 0.0f};
static const Vec sA = {1.0f, 0.0f, 0.0f};
static const Vec sB = {0.0f, 1.0f, 0.0f};
static const Vec sC = {-1.0f, 0.0f, 0.0f};
static const Vec sD = {0.0f, -1.0f, 0.0f};
struct Mp { u8 p[0x15422]; s16 h[0x4005]; s16 l[1]; };
static inline void Put(Mp* g, int idx, s16 a, s16 b) {
    u8* p = (u8*)g + idx * 2;
    *(s16*)(p + 0x15422) = a;
    *(s16*)(p + 0x1D42C) = b;
}
void fn_80137BC8(MM* mm) {
    char path[0x40];
/*P*/
    Mp* g;
    int ofs;
    int y2;
    u8* row;
    int x2;
    N* base;
    N* extra;
    u16* a;
    u16* bb;
    int x;
    int y;
    N* n1;
    N* n2;
    const char* s;
    u16* b;
/*E*/
    base = 0;
    a = 0;
    fn_80290DDC(path, lbl_803694D4 + 0x104, mm->name);
    if (fn_80076F54(path)) base = (N*)fn_80077064(path);
    fn_80290DDC(path, lbl_803694D4 + 0x113, mm->name);
    if (fn_80076F54(path)) a = (u16*)fn_80077064(path);
    s = lbl_803694D4;
    fn_80290DDC(path, s + 0x121, mm->name);
    if (fn_80076F54(path)) {
        extra = (N*)fn_80077064(path);
        fn_80290DDC(path, s + 0x12E, mm->name);
        b = (u16*)fn_80077064(path);
    } else {
        extra = base;
        b = a;
    }
    if (base) {
        bb = b;
        y = 0;
        g = (Mp*)lbl_803EC898;
        for (; y < mm->x4d; y++) {
            ofs = (s8)y * 0x40;
            row = (u8*)g + ofs;
            for (x = 0; x < mm->x4c; x++) {
                n1 = &base[*a++];
                n2 = &extra[*bb++];
                u8 m = fn_8011D1E4(n1->x8);
                int xx = (s8)x;
                int i;
                u8* rr;
                rr = row + xx;
                i = xx + ofs;
                rr[0x100D] = m;
#define H(e) (*(s16*)((u8*)g + (e) * 2 + 0x15422))
#define L(e) (*(s16*)((u8*)g + (e) * 2 + 0x1D42C))
                H(i * 4 + 0) = n1->v[0];
                L(i * 4 + 0) = n2->v[0];
                H(i * 4 + 1) = n1->v[1];
                L(i * 4 + 1) = n2->v[1];
                H(i * 4 + 2) = n1->v[2];
                L(i * 4 + 2) = n2->v[2];
                H(i * 4 + 3) = n1->v[3];
                L(i * 4 + 3) = n2->v[3];
            }
        }
        for (y2 = 0; y2 < mm->x4d; y2++) {
            for (x2 = 0; x2 < mm->x4c; x2++) {
                f32 h[4];
                h[0] = fn_801146A8(lbl_803EC898, (s8)x2, (s8)y2, 0);
                h[1] = fn_801146A8(lbl_803EC898, (s8)x2, (s8)y2, 1);
                h[2] = fn_801146A8(lbl_803EC898, (s8)x2, (s8)y2, 2);
                h[3] = fn_801146A8(lbl_803EC898, (s8)x2, (s8)y2, 3);
                if (h[0] == h[1] && h[1] == h[2] && h[2] == (f32)(f64)h[3]) {
                    fn_80114818(lbl_803EC898, (s8)x2, (s8)y2);
                } else {
                    Vec p0 = *(Vec*)&sA; p0.z = h[1] - h[0];
                    Vec p1 = *(Vec*)&sB; p1.z = h[2] - h[0];
                    Vec n0;
                    Vec q0 = *(Vec*)&sC; q0.z = h[2] - h[3];
                    Vec q1 = *(Vec*)&sD; q1.z = h[1] - h[3];
                    Vec nn;
                    fn_8031356C(&p0, &p1, &n0);
                    fn_8031356C(&q0, &q1, &nn);
                    fn_803134C4(&n0, &n0);
                    fn_803134C4(&nn, &nn);
                    f32 d = fn_8031354C(&n0, &nn);
                    if (d < 1.001f && d > 0.999f) {
                        fn_80114818(lbl_803EC898, (s8)x2, (s8)y2);
                    } else {
                        fn_80114850(lbl_803EC898, (s8)x2, (s8)y2);
                    }
                }
            }
        }
    }
}
}

