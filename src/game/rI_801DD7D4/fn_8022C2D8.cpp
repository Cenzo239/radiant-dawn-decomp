/* fn_8022C2D8 (round 24): destructor of a 0x80-byte window object (vtable lbl_80390540) holding one
 * reference-counted child at +0x7C; the base part is destroyed by fn_8021696C, and del > 0 frees it.
 * The original keeps the null it stores into the child slot in a saved register (li r31,0 before the
 * vtable store). That is a loop-hoisted constant: the release is written as a loop over a one-element
 * array of child pointers (probably a member array or a generic release loop in the original). */
#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/rlist.h"

extern "C" {
void* fn_8021696C(void*, int);
extern void* lbl_80390540[];
}

struct S80 {
    void* vt;
    u8 p[0x78];
    RObj* a7c[1];
};

extern "C" S80* fn_8022C2D8(S80* o, int del) {
    if (o != NULL) {
        o->vt = lbl_80390540;
        for (int i = 0; i < 1; i++) {
            RObj* p = o->a7c[i];
            if (p != NULL) {
                if (--p->rc == 0) {
                    if (p != NULL) {
                        p->destroy(1);
                    }
                }
                o->a7c[i] = NULL;
            }
        }
        fn_8021696C(o, 0);
        if (del > 0) {
            fn_80079210(o);
        }
    }
    return o;
}
