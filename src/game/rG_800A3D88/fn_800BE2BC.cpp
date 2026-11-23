#include "game/rG_800A3D88/chr.h"
extern "C" {
struct ChrE2 { u8 pad[0x30]; Mdl* mdl; u8 p34[8]; void* e[2]; u8 p44[0xC]; u32 flags; };
void fn_8001A954(Mdl*);
void fn_800C0EFC(void*);
void fn_800BE2BC(ChrE2* c) {
    int i;
    if (c->mdl != NULL) {
        u32 f = c->flags;
        if (!(f & 1) && (f & 0x2000) && !(f & 0x8000)) {
            fn_8001A954(c->mdl);
            for (i = 0; i < 2; i++, c = (ChrE2*)((u8*)c + 4)) {
                if (c->e[0] != NULL) fn_800C0EFC(c->e[0]);
            }
        }
    }
}
}
