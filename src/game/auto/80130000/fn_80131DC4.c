#include "game/auto/m2c_prelude.h"
extern u8 lbl_80413510[0x6d8];

u8 fn_80131DC4(void) {
    return M2C_FIELD(lbl_80413510, u8 *, 0x6D4);
}
