#include "game/auto/m2c_prelude.h"
extern u8 lbl_803CAB38[0x988];

s32 fn_801D3FFC(void) {
    return M2C_FIELD(lbl_803CAB38, u8 *, 0x9D) != 0;
}
