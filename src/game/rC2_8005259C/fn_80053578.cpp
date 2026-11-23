#include "game/rC2_8005259C/base.h"
struct Sub { u8 pad[8]; u8 b8; };
struct MU { u8 pad[0xf4]; Sub* f4; u8 p[0x102 - 0xf8]; u8 x; u8 y; u8 p2[8]; u32 f10c; };
struct Ctx { MU* p0; u8 pad4[8]; u8 bc; u8 p[8]; u8 b15; u8 p16[0x12]; u8 b28; };
extern "C" {
extern Ctx lbl_803CA870;
extern u8 lbl_803CAB38[];
void fn_80045548(Ctx*);
void fn_80113370(void);
#if TARGET_PC
FE10_PROTO void fn_801484B4(p32arg);
#else
void fn_801484B4(int);
#endif
void fn_80083DC4(void*, int);
void fn_800679EC(MU*);
void fn_8004564C(Ctx*, void*);
void fn_800453B4(Ctx*, int);
int fn_80045274(Ctx*);
void fn_800453CC(Ctx*);
void fn_8006214C(void*, MU*);
void fn_8014083C(int, int, int);
}

extern "C" void fn_80053578(void* p) {
    MU* u = lbl_803CA870.p0;
    if (u->f10c & 1) {
        return;
    }
    switch (lbl_803CA870.bc) {
    case 7:
    case 0x4e:
        if (u->f4->b8 != 0) {
            fn_800453B4(&lbl_803CA870, 1);
            break;
        }
    case 6:
    case 0x29:
    case 0x1c:
    case 0x1d:
    case 0x3d:
    case 0x3e:
    case 0x3f:
        fn_80083DC4(p, 8);
        return;
    }
    if (fn_80045274(&lbl_803CA870)) {
        fn_800453CC(&lbl_803CA870);
        u = lbl_803CA870.p0;
        fn_800679EC(u);
        fn_8006214C(lbl_803CAB38, u);
        fn_8014083C((s8)u->x, (s8)u->y, (s8)lbl_803CA870.b15);
        fn_80083DC4(p, 3);
    }
}
