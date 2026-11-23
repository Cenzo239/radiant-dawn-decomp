#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" Vec3 fn_800622B8(GameData* g) {
    Vec3 v;
    v.x = g->f944;
    v.y = g->f948;
    v.z = fn_801142F0(lbl_803EC898, v.x, v.y);
    return v;
}

extern "C" void fn_80062318(NameTable* t, int i, const char* s) {
    if (s) {
        fn_802910CC(t->a30[i], s, 0xc);
    }
}

extern "C" const char* fn_8006233C(NameTable* t, int i) {
    return fn_800D0864(t->a30[i]);
}

extern "C" void fn_8006234C(NameTable* t, int i, const char* s) {
    if (s) {
        fn_802910CC(t->a54[i], s, 0xc);
    }
}

extern "C" const char* fn_80062370(NameTable* t, int i) {
    return fn_800D0864(t->a54[i]);
}
