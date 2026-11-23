#include "game/rG_800A3D88/types.h"

// Face object idle timing, chosen by its animation flags.
extern "C" {
struct FO { u8 p[0x48]; u32 m48; };
struct FP { u8 p[0x18]; FO* m18; u8 p1c[0x30 - 0x1C]; FO* m30; s16 m34; s16 m36; int m38; u8 p3c[2]; s16 m3e; u8 p40[2]; s16 m42; };
u32 fn_80089ED0();
void fn_80083DC4(void*, int);
static inline int Wait(FP* p) {
    int r = fn_80089ED0() >> 16;
    switch (p->m34) {
    case 3:
        r = (r >> 7) + 0x12C;
        break;
    case 1:
        r = (r >> 7) + 0x3C;
        break;
    case 2:
        r = (r >> 10) + 1;
        break;
    case 4:
        r = 1;
        break;
    case 5:
        r = 0x7FFFFFFF;
        break;
    default:
        r = 1;
        break;
    }
    return r;
}
static inline void Arm(FP* p, s16 a, s16 b, s16 c, int st) {
    p->m34 = a;
    p->m36 = b;
    p->m42 = c;
    p->m3e = c;
    p->m38 = Wait(p);
    fn_80083DC4(p, st);
}
void fn_800C67F8(FP* p) {
    p->m30 = p->m18;
    switch (p->m18->m48 & 6) {
    case 2:
        Arm(p, 1, 3, 5, 3);
        break;
    case 4:
        Arm(p, 1, 4, 2, 4);
        break;
    case 6:
        Arm(p, 1, 5, 0, 5);
        break;
    default:
        Arm(p, 1, 1, 0, 1);
        break;
    }
}
}
