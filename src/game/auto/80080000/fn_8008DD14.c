#include "game/auto/m2c_prelude.h"
extern s8 *lbl_804CB814;

s32 fn_8008DD14(void) {
    return M2C_FIELD(lbl_804CB814, s32 *, 0x48) == 0;
}
