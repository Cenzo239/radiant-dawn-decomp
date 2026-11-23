#include "game/rG_800A3D88/types.h"

// Anim-set lookup for a unit: by three derived names, then by weapon class.
extern "C" {
struct AnimE { const char* name; void* a; };
struct E154 { u8 p[0x14D]; u8 n; u8 p14e[2]; AnimE* anims; };
struct UnitA { u8 p[0xF4]; struct { u8 p[8]; u8 m8; }* f4; };
extern char lbl_803651B0[];
#define S(a) (lbl_803651B0 + ((a) - 0x803651B0))
int fn_80291188(const char*, const char*);
const char* fn_800F416C(UnitA*);
const char* fn_801283C0(UnitA*);
const char* fn_801283DC(UnitA*);
static inline int FindN(E154* e, const char* name) {
int n;
int k;
const char* nm;
    nm = name;
    if (nm == NULL) return 0;
    n = e->n;
    for (k = 0; k < n; k++) {
        if (fn_80291188(e->anims[k].name, nm) == 0) return k;
    }
    return -1;
}
#pragma use_lmw_stmw on
int fn_800A6F98(E154* e, UnitA* u) {
    int k;
    if (u != NULL) {
        k = FindN(e, fn_800F416C(u));
        if (k >= 0) return k;
        k = FindN(e, fn_801283C0(u));
        if (k >= 0) return k;
        k = FindN(e, fn_801283DC(u));
        if (k >= 0) return k;
        switch (u->f4->m8) {
        case 0: return FindN(e, S(0x803651E1));
        case 1: return FindN(e, S(0x803651E6));
        case 2: return FindN(e, S(0x803651EB));
        case 3: return FindN(e, S(0x803651F0));
        default: return FindN(e, S(0x803651E1));
        }
    }
    return -1;
}
}
