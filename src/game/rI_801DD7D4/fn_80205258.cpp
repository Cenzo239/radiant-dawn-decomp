#include "game/rI_801DD7D4/types.h"
extern "C" {
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E720(f32);
#if TARGET_PC
FE10_PROTO void fn_8007E174(p32arg, u16);
#else
void fn_8007E174(int, u16);
#endif
void fn_801D820C(s16, s16, int, int, int, int);
int fn_800CB0FC(f32, int);
int fn_800CA3DC(f32, const char*, int);
const char* fn_80110F08(void*);
void fn_801E6DA0(s16, s16, int, const char*, ...);
const char* fn_800D0864(void*);
void fn_800CB278(s16, s16, int, const char*, ...);
void fn_800800D4(int);
typedef struct C4 { u8 r, g, b, a; } C4;
const C4* fn_800CD204(int);
void fn_80080508(C4*);
void fn_80080B00(int, const C4*, f32);
void fn_80176F7C(int, int, int, int, int);
void fn_80080308(void);
extern u8 lbl_8036F328[];
struct Ctx { u8 p[0x2d]; u8 x2d, x2e; u8 p2[5]; int x34; struct { u8 p[8]; void* x8; }* x38; };
struct VD { virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18(void*); };
struct T5 { u8 p[0x3c]; void* x3c; u32 x40; };
void fn_80205258(T5* o, Ctx* a) {
    int i;
    f32 x, step, y;
    ((VD*)o)->v18(a);
    x = 0.0f;
    y = x;
    step = 20.0f;
    for (i = 0; i < 8; i++) {
        int k;
        fn_8007E154();
        fn_8007E720(0.01f);
        fn_8007E164();
        switch (i) {
        case 0: k = 0xb; break;
        case 1: k = 0xc; break;
        case 2: k = 0xd; break;
        case 3: k = 0xe; break;
        case 4: k = 0xf; break;
        case 5: k = 0x10; break;
        case 6: k = 0x16; break;
        case 7: k = 0x17; break;
        default: k = 0xb; break;
        }
        int hl = 0;
        int b = 0;
        if (!a->x2d && !a->x2e && o->x3c) b = 1;
        if (b) {
            void* t;
            void* c = o->x3c;
            if (a->x34) t = a->x38->x8; else t = 0;
            if (t == c) hl = 1;
        }
        fn_801D820C((s16)x, (s16)y, k, (u32)i == o->x40, hl, 0x10);
        x += step;
    }
}
}
