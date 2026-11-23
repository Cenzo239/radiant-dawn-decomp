#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
#if TARGET_PC
FE10_PROTO void* fn_80081194(void*, p32arg);
FE10_PROTO void* fn_80081050(void*, p32arg);
#else
void* fn_80081194(void*, int);
void* fn_80081050(void*, int);
#endif
struct A44 { u8 p[0x44]; f32 a44; };
struct S44 { u8 p[0x28]; s16 a28; u8 p2a[6]; s8 a30; int a34; f32 a38, a3c; A44* a40; };
extern void* lbl_8038F7BC[];
void fn_8021C278(u8* t, s8 k, int n, void* par, int mode) {
    S44* o;
    if (mode != 0) {
        o = (S44*)fn_80081194(lbl_8038F7BC, (int)par);
    } else {
        o = (S44*)fn_80081050(lbl_8038F7BC, (int)par);
    }
    o->a30 = k;
    n = n > 0 ? n : *(s16*)(t + 0x28);
    o->a34 = n;
    f32 v; v=*(f32*)(t + 0x44); o->a38=v; v=*(f32*)(t + 0x44); o->a3c=180.0f+v;
    *(u8**)&o->a40 = t;
    o->a28 = n;
}
}
