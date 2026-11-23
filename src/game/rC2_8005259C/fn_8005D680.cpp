#include "game/rC2_8005259C/base.h"
struct MU { u8 pad[0xc4]; s16 hc4; u8 p[0x108 - 0xc6]; u64 flags; };
struct Tile { s8 x; u8 y; };
struct Map { u8 pad[0xd]; u8 id[1]; };
extern "C" {
extern Map lbl_803EC898;
extern int lbl_803E7320[];
void fn_80114D00(Map*);
#if TARGET_PC
FE10_PROTO void fn_801484B4(p32arg);
#else
void fn_801484B4(int);
#endif
Tile* fn_800CFD18(void*, int);
MU* fn_80127B68(MU*);
void fn_80126EB0(MU*, int, int);
void fn_800F39DC(MU*);
}

extern "C" int fn_8005D680(void* a, MU* u) {
    Tile* t;
    int r = 0;
    if (!(u->flags & 0x10000dcULL)) {
        if (u->flags & 0x10000ULL) {
            return 0;
        }
        u->flags |= 0x10000dcULL;
        fn_80114D00(&lbl_803EC898);
        fn_801484B4(0);
        r = 1;
    } else {
        int i;
        if (u->flags & 0x200000ULL) {
            return 0;
        }
        for (i = 0; i < lbl_803E7320[0]; i++) {
            t = fn_800CFD18(lbl_803E7320, i);
            if (lbl_803EC898.id[t->x + (s8)t->y * 0x40] == 0) {
                MU* o;
                u->flags &= ~0x10000dcULL;
                o = fn_80127B68(u);
                fn_80126EB0(u, t->x, (s8)t->y);
                if (o) {
                    u->hc4 = 64.0f * (0.015625f * o->hc4);
                }
                fn_800F39DC(u);
                fn_80114D00(&lbl_803EC898);
                fn_801484B4(0);
                r = 1;
                break;
            }
        }
    }
    return r;
}
