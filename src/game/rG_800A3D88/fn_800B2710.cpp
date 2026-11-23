#include "game/rG_800A3D88/chr.h"

// Battle character: release the model, sounds and effects.
extern "C" {
extern u8 lbl_80382550[];
void fn_80006EE0(void*);
void fn_8023F1A8(void*);
void fn_80011CBC(void (*)(void*), void*);
void fn_80081A90(void*);
void fn_800829CC(Chr*, void*);
void fn_800B2710(Chr* c) {
    if (c->mdl != NULL) {
        fn_80011CBC(fn_80006EE0, c->mdl);
        if (c->m34 != NULL) {
            fn_80011CBC(fn_8023F1A8, c->m34);
        }
        if (c->m38 != NULL) {
            fn_80011CBC(fn_8023F1A8, c->m38);
            c->m38 = NULL;
        }
        c->mdl = NULL;
        c->m7c = NULL;
        c->m34 = NULL;
        for (int i = 0; i < 2; i++) {
            if (c->m3c[i] != NULL) {
                fn_80081A90(c->m3c[i]);
                c->m3c[i] = NULL;
            }
        }
        fn_800829CC(c, lbl_80382550);
        if (c->m98 != NULL) {
            fn_80081A90(c->m98);
            c->m98 = NULL;
        }
        c->flags = 0;
        c->flags |= 0x204C;
    }
}
}
