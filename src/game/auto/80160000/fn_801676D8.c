#include "game/auto/m2c_prelude.h"
extern u8 lbl_803EC898[0x15867];

u16 fn_801676D8(s8 arg0, s8 arg1) {
    return M2C_FIELD((lbl_803EC898 + 0x10000 + ((arg0 + (arg1 << 6)) * 2)), u16 *, -0x4E72);
}
