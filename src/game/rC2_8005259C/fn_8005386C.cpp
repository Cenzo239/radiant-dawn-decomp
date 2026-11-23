#include "game/rC2_8005259C/base.h"
struct MU { u8 pad[0x102]; s8 x; s8 y; u8 p104[0x28]; u8 a12c[1]; };
struct GD { u8 pad[0x92c]; u8 b92c; };
extern "C" {
extern MU* lbl_803CA870[];
extern GD lbl_803CAB38;
extern u8 lbl_803EC898[];
extern void* lbl_804CA500;
extern void* lbl_804CA520;
u8* fn_80116A4C(void*);
#if TARGET_PC
FE10_PROTO void fn_8014089C(ptr32<const void>);
#else
void fn_8014089C(u8* grid);
#endif
int fn_8011B77C(void*, void*);
#if TARGET_PC
FE10_PROTO u8 fn_80116A68(void*, s8*, s8*, int, p32arg);
#else
u8 fn_80116A68(void*, s8*, s8*, int, int);
#endif
void fn_800620A8(GD*, f32, f32);
void fn_800453B4(void*, int);
#if TARGET_PC
FE10_PROTO void fn_80103CE4(MU*, int, p32arg, p32arg, void*);
#else
void fn_80103CE4(MU*, int, int, int, void*);
#endif
void fn_801034B4(MU*, void*);
}

extern "C" void fn_8005386C(void* p) {
    MU* u;
    s8 x, y;
    lbl_803CAB38.b92c = 0;
    u = lbl_803CA870[0];
    u8* grid = fn_80116A4C(lbl_803EC898);
    fn_8014089C(grid);
    {
    int r = fn_8011B77C(u->a12c, lbl_804CA500);
    x = u->x;
    y = u->y;
    switch (fn_80116A68(lbl_803EC898, &x, &y, r, 0)) {
    case 1:
        fn_800620A8(&lbl_803CAB38, x, y);
        fn_800453B4(lbl_803CA870, 0x25);
        break;
    case 2:
        fn_800620A8(&lbl_803CAB38, x, y);
        fn_800453B4(lbl_803CA870, 0x2e);
        break;
    }
    }
    if (fn_8011B77C(u->a12c, lbl_804CA520)) {
        fn_80103CE4(u, 0, x, y, p);
    } else {
        fn_801034B4(u, p);
    }
}
