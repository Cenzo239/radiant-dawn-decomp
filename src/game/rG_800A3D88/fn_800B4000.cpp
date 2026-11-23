#include "game/rG_800A3D88/chr.h"

// Battle character: world position of a model node, optionally at a given frame.
extern "C" {
struct Mtx34 { f32 m[3][4]; };
struct ChP { u8 p[0x30]; Mdl* mdl; };
struct Anim { u8 p[0x18]; int m18; };
void fn_80312344(void*, void*);
void fn_80312318(void*);
Anim* fn_80007F10(Mdl*);
Vec fn_800076E8(Mdl*, int);
void* fn_800078E4(Mdl*, int);
void fn_80007A00(Mdl*, int);
void fn_8000F3E4(void*, int);
void fn_80007DE8(Mdl*);
void fn_80007A5C(Mdl*, int);
int fn_800B4000(ChP* c, int k, Vec* out, int fr, int raw) {
    Mtx34 save;
    if (k < 0) return 0;
    if (raw) {
        fn_80312344((u8*)c->mdl + 0x10, &save);
        fn_80312318((u8*)c->mdl + 0x10);
    }
    Anim* a = fn_80007F10(c->mdl);
    if (a != NULL) {
        if (fr > a->m18) fr = a->m18;
        if (c->mdl->frame == (f32)fr) fr = -1;
    }
    if (fr < 0) {
        *out = fn_800076E8(c->mdl, k);
    } else {
        void* n = fn_800078E4(c->mdl, k);
        fn_80007A00(c->mdl, 0x10000000);
        fn_8000F3E4(n, 0x10000000);
        f32 old = c->mdl->frame;
        c->mdl->frame = fr;
        fn_80007DE8(c->mdl);
        *out = fn_800076E8(c->mdl, k);
        c->mdl->frame = old;
        fn_80007DE8(c->mdl);
        fn_80007A5C(c->mdl, 0x10000000);
    }
    if (raw) fn_80312344(&save, (u8*)c->mdl + 0x10);
    return 1;
}
}
