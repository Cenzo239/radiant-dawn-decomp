#include "game/rG_800A3D88/types.h"

// Finds a record in table lbl_804CB654 by its name, or by its two secondary names.
extern "C" {
struct Rec { const char* m0; const char* m4; const char* m8; u8 pc[8]; };
extern u8* lbl_804CB654;
u32 fn_80109A2C(u8**);
int fn_80291188(const char*, const char*);
#pragma use_lmw_stmw on
Rec* fn_800A7770(const char* a, const char* b, const char* c) {
    u8* r;
int j;
int n;
Rec* base;
int j2;
const char* k;
int i2;
Rec* p;
int i;
const char* s;
    r = lbl_804CB654;
    n = (u16)fn_80109A2C(&r);
    fn_80109A2C(&r);
    base = (Rec*)r;
    p = base;
    if (c != NULL && *c != 0) {
        for (i = 0; i < n; i++, p++) {
            if (p->m0 != NULL && fn_80291188(p->m0, c) == 0) return p;
        }
        p = base;
    }
    if (a != NULL && b != NULL && *a != 0 && *b != 0) {
        for (i2 = 0; i2 < n; i2++, p++) {
            s = p->m4;
            if (s != NULL) {
                k = p->m8;
                if (k != NULL && fn_80291188(s, b) == 0 && fn_80291188(k, a) == 0) return p;
            }
        }
        p = base;
    }
    if (b != NULL && *b != 0) {
        for (j = 0; j < n; j++, p++) {
            if (p->m4 != NULL && fn_80291188(p->m4, b) == 0) return p;
        }
        p = base;
    }
    if (a != NULL && *a != 0) {
        for (j2 = 0; j2 < n; j2++, p++) {
            if (p->m8 != NULL && fn_80291188(p->m8, a) == 0) return p;
        }
    }
    return NULL;
}
#pragma use_lmw_stmw off
}
