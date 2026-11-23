#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800846BC(void *);
FE10_PROTO void * fn_800893E4(void *, void *(*)(void *, void *), void *);
#else
M2C_UNK fn_800846BC();
M2C_UNK fn_800893E4();
#endif
extern u8 fn_800E450C[0x3c];
extern u8 lbl_80384218[0x24];
extern u8 lbl_80384278[0x50];

void fn_800E4548(void) {
    fn_800893E4(lbl_80384278, fn_800E450C, 0);
    fn_800846BC(lbl_80384218);
}
