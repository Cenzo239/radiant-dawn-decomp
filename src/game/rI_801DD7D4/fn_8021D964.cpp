#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
int fn_80120378(void*);
f32 fn_80120524(void*, int);
f32 fn_80062850(void*);
extern u8 lbl_803CAB38[];
struct S4C2 { u8 p[0x40]; void* a40; u8 p44[4]; int a48; };
static inline f32 cost(void* u, int k) {
    f32 r;
    if (k == 0) {
        r = 0.0f;
    } else {
        f32 v = fn_80120524(u, k);
        if (v < 1.0f) v = 1.0f;
        r = v;
    }
    return r;
}
bool fn_8021D964(const S4C2* o) {
    int n = o->a48;
    bool r = fn_80120378(o->a40) - n > 0;
    if (r) {
        r = fn_80062850(lbl_803CAB38) >= cost(o->a40, o->a48 + 1);
    }
    return r;
}
}
