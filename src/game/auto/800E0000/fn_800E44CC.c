#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_800893E4(void *, void *(*)(void *, void *), void *);
#else
s32 fn_800893E4();
#endif
extern u8 fn_800E44B4[0x18];
extern u8 lbl_80384278[0x50];

s32 fn_800E44CC(void) {
    return fn_800893E4(lbl_80384278, fn_800E44B4, 0) != 0;
}
