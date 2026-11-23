#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
extern "C" {
#pragma auto_inline off
struct E { E() {} char c; };
void fn_802248B4(void*, E);
u32* fn_801E2204(void*, s16*, s16*);
void fn_802236D8(u8* o) { fn_802248B4(o + 0x74, E()); }

u32 fn_8012B120(void*, void*);
u8 fn_801F28C0(void*** a, void* b) { return fn_8012B120(b, **a); }

typedef struct LMenu { u8 p[0x1e]; s16 x1e, x20; u8 p2[0x2e]; s16 x50; u8 p3[6]; s16 x58; } LMenu;
u32 fn_802228B8(const LMenu* o) {
    s16 q[2];
    s16 p[2];
    int s = o->x50;
    int y;
    if (s < 0) {
        y = 0;
        s = 0;
    } else {
        int t = s * o->x58;
        y = (s16)(t + o->x20);
        s = o->x1e;
    }
    p[0] = s;
    p[1] = y;
    return *fn_801E2204((void*)o, q, p);
}

struct RowM { virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); virtual int v30(); virtual int v34(); virtual int v38(); };
static inline s16 rowD(int a, int b) { return a - b; }
typedef struct R1 { u8 p[0x1e]; s16 x1e, x20; u8 p2[0x36]; s16 x58[8]; s16 x68[4]; s16 x70[4]; } R1;
typedef struct R2 { u8 p[0x1e]; s16 x1e, x20; u8 p2[0x34]; s16 x56; u8 p3[6]; s16 x5e, x60, x62; } R2;
struct RV { virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c(); virtual void v40(); virtual int v44(); };
void fn_802124D8(s16* o) {
    s16 w = o[7] - o[5];
    s16 h = o[8] - o[6];
    s16 a = w - 2;
    o[9] = 2;
    o[10] = 5;
    o[11] = a;
    o[12] = h - 5;
    o[15] = 0x18;
    o[16] = 7;
    o[0x29] = (s16)((s16)(a - 2) - 0x30) + 0x20;
    o[0x2a] = 0x11;
    o[0x2b] = 0;
}
void fn_80213310(s16* o) {
    s16 w = o[7] - o[5];
    s16 h = o[8] - o[6];
    s16 a = w - 2;
    o[9] = 2;
    o[10] = 5;
    o[11] = a;
    o[12] = h - 5;
    o[15] = 0x18;
    o[16] = 0x9a;
    o[0x29] = (s16)((s16)(a - 2) - 0x30) + 0x20;
    o[0x2a] = 0xa4;
    o[0x2b] = 0;
}
}
