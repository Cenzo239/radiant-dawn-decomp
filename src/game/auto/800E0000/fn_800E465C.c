#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_800893E4(void *, void *(*)(void *, void *), void *);
#else
M2C_UNK fn_800893E4();
#endif
extern u8 lbl_80384278[0x50];

void fn_800E465C(
#if TARGET_PC
void *arg0, void *arg1
#else
s32 arg0, s32 arg1
#endif
) {
    fn_800893E4(lbl_80384278, arg0, arg1);
}
