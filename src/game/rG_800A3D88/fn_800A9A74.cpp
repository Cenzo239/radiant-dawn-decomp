#include "game/rG_800A3D88/types.h"

// Battle scene frame: update both characters, keeping the slower one in step.
extern "C" {
struct Vec { f32 x, y, z; };
struct W3 { u32 a, b, c; };
struct ChI { u8 p[0x50]; u32 m50; };
struct Ev { u8 p[0x33]; u8 m33; };
struct Bat {
    u8 p[0x30];
    Ev* m30;
    void* m34;
    void* m38;
    ChI* e[2];
    u8 p44[8];
    u8 m4c;
};
void fn_800BE3B4(ChI*);
void fn_800B93F8(ChI*, Vec*, Vec*);
void fn_800BE940(ChI*);
static inline ChI* At(Bat* b, int i) { if (i < 0) return NULL; return b->e[i]; }
static inline ChI* At2(Bat* q, int i) { if (i < 0) return NULL; return q->e[0]; }
#define ADV(q) (q = (Bat*)((u8*)q + 4))
static inline void MkA(Vec* out, f32 x) {
    Vec t = {0.0f, 0.0f, -30.0f};
    t.x = x;
    *out = t;
}
static inline void MkA2(Vec* out, f32 x) { MkA(out, x); }
static inline void MkB(Vec* out, f32 x) {
    Vec t = {0.0f, 100.0f, 30.0f};
    t.x = x;
    *out = t;
}
static inline void Upd1(Bat* b) {
    int i;
    Bat* q;
    for (q = b, i = 0; i < 2; i++, ADV(q)) {
        if (At2(q, i)->m50 & 0x800000) fn_800BE3B4(At2(q, i));
    }
}
static inline void Upd0(Bat* b) {
    int i;
    Bat* q;
    for (q = b, i = 0; i < 2; i++, ADV(q)) {
        if (!(At2(q, i)->m50 & 0x800000)) fn_800BE3B4(At2(q, i));
    }
}
static inline void Upd5(Bat* b) {
    int i;
    Bat* q;
    for (q = b, i = 0; i < 2; i++, ADV(q)) fn_800BE940(At2(q, i));
}
void fn_800A9A74(Bat* b) {
    Vec v0, v1, a1, b1, a2, b2;
Vec* pb;
Vec* pa;
Bat* q3;
int i3;
Vec* pb2;
Vec* pa2;
Bat* q4;
int i4;
int i;
int m;
    for (i = 0; i < 2; i++) At(b, i)->m50 &= ~0x20;
    Upd1(b);
    Upd0(b);
    m = b->m30->m33;
    MkA2(&v0, -m);
    MkB(&v1, m);
    pb = &b1;
    pa = &a1;
    for (q3 = b, i3 = 0; i3 < 2; i3++, ADV(q3)) {
        if (!(At2(q3, i3)->m50 & 0x800000)) {
            *(W3*)&b1 = *(W3*)&v1;
            *(W3*)&a1 = *(W3*)&v0;
            fn_800B93F8(At2(q3, i3), pa, pb);
        }
    }
    pb2 = &b2;
    pa2 = &a2;
    for (q4 = b, i4 = 0; i4 < 2; i4++, ADV(q4)) {
        if (At2(q4, i4)->m50 & 0x800000) {
            *(W3*)&b2 = *(W3*)&v1;
            *(W3*)&a2 = *(W3*)&v0;
            fn_800B93F8(At2(q4, i4), pa2, pb2);
        }
    }
    Upd5(b);
    if (b->m4c != 0) {
        for (i = 0; i < 2; i++) {
            if (At(b, i)->m50 & 0x10) {
                for (int j = 0; j < 2; j++) At(b, j)->m50 |= 0x20;
                break;
            }
        }
    }
    for (i = 0; i < 2; i++) At(b, i)->m50 &= ~0x10;
}
}
