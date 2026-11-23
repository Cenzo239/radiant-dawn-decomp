#include "game/auto/m2c_prelude.h"
M2C_UNK __register_global_object();
#if TARGET_PC
FE10_PROTO void fn_8025F41C(void *);
#else
M2C_UNK fn_8025F41C();
#endif
extern u8 fn_8025F43C[0xa4];
extern u8 lbl_8041ED10[0xc];
extern u8 lbl_8041ED1C[0xcc];

void fn_801D09F8(void) {
    fn_8025F41C(lbl_8041ED1C);
    __register_global_object(lbl_8041ED1C, fn_8025F43C, lbl_8041ED10);
}
