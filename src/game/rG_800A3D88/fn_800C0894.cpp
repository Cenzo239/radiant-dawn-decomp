/* Attached effect: detach (names guessed). */
#include "game/rG_800A3D88/types.h"

extern "C" {
struct EData { u8 p[0x21]; u8 m21; };
struct Mdl { u32 flags; };
struct EOwn { u8 p[0x30]; Mdl* mdl; };
struct Eff {
    u8 p[0x34];
    void* m34;
    EData* m38;
    EOwn* m3c;
    void* m40;
    u8 p44[2];
    u16 m46;
};
extern u8 lbl_803825A8[];
void fn_800829CC(void*, void*);
void fn_800C1064(Eff*, int);
void fn_801780B0(void*);

static inline int EffHas(const Eff* e, int m) { return e->m46 & m; }
void fn_800C0894(Eff* e) {
    Mdl* m;
    if (e->m34 != NULL) {
        if (EffHas(e, 2) && e->m38 != NULL) {
            if (EffHas(e, 8)) {
                e->m46 &= ~0xC;
            } else {
                e->m46 |= 4;
            }
            e->m46 &= ~2;
            if (e->m38->m21 & 4) {
                e->m46 &= ~0x10;
                fn_800C1064(e, 0);
                fn_800829CC(e, lbl_803825A8);
            }
            if (e->m40 != NULL) {
                fn_801780B0(e->m40);
                e->m40 = NULL;
            }
            e->m46 &= ~0x40;
            m = e->m3c->mdl;
            if (m != NULL) {
                m->flags &= ~8;
            }
        }
    }
}
}
