#include "game/auto/m2c_prelude.h"
extern u8 lbl_8037F7E0[0x10];
extern u8 lbl_8037F7F0[0x10];
extern u8 lbl_803CAB38[0x988];

void fn_80063BB8(void) {
    M2C_FIELD(lbl_803CAB38, M2C_UNK **, 0xD8) = lbl_8037F7E0;
    M2C_FIELD(lbl_803CAB38, M2C_UNK **, 0xEC) = lbl_8037F7E0;
    M2C_FIELD(lbl_803CAB38, M2C_UNK **, 0x100) = lbl_8037F7F0;
}
