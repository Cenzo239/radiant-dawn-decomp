#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_80083CB4(void *);
#else
M2C_UNK fn_80083CB4();
#endif
extern u8 lbl_80384278[0x50];

#if TARGET_PC
s32 fn_800E4588(void) {
    return fn_80083CB4(lbl_80384278);
}
#else
void fn_800E4588(void) {
    fn_80083CB4(lbl_80384278);
}
#endif
