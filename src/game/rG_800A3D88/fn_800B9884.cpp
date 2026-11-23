#include "game/rG_800A3D88/types.h"

// Battle character: refresh the skinning matrices of one of two named bones.
extern "C" {
struct ChrU { u8 p[0x30]; void* mdl; u8 p34[0x50 - 0x34]; u32 m50; };
extern char lbl_803657E8[];
#define STR(n) (lbl_803657E8 + (n))
int fn_80007630(void*, const char*);
void* fn_80007EE4(void*);
void* fn_8000F3D4(void*, int);
void* fn_800080B8(void*);
void* fn_800080E4(void*);
void fn_8000EDEC(void*, void*);
void fn_8000F1D4(void*, void*);
void fn_8000EC30(void*, void*, void*);
static inline void* Bone(ChrU* c, const char* n) {
    int k = fn_80007630(c->mdl, n);
    if (k < 0) return NULL;
    return fn_8000F3D4(fn_80007EE4(c->mdl), k);
}
void fn_800B9884(ChrU* c) {
void* b;
void* m1;
void* m2;
void* n1;
void* n2;
    if (c->m50 & 0x20000) {
        b = Bone(c, STR(0x274));
        if (b != NULL) {
            m1 = fn_800080B8(c->mdl);
            m2 = fn_800080E4(c->mdl);
            fn_8000EDEC(b, m1);
            fn_8000F1D4(b, m1);
            fn_8000EC30(b, m1, m2);
        }
    } else {
        b = Bone(c, STR(0x279));
        if (b != NULL) {
            n1 = fn_800080B8(c->mdl);
            n2 = fn_800080E4(c->mdl);
            fn_8000EDEC(b, n1);
            fn_8000F1D4(b, n1);
            fn_8000EC30(b, n1, n2);
        }
    }
}
}
