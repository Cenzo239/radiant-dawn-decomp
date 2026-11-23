#include "game/auto/m2c_prelude.h"
M2C_UNK __register_global_object();
#if TARGET_PC
FE10_PROTO void fn_80110D38(void *);
#else
M2C_UNK fn_80110D38();
#endif
extern u8 fn_80111C24[0x54];
extern u8 lbl_803EC358[0x10];
extern u8 lbl_803EC368[0x28];

void fn_80112B00(void) {
    fn_80110D38(lbl_803EC368);
    __register_global_object(lbl_803EC368, fn_80111C24, lbl_803EC358);
}
