#include "game/auto/m2c_prelude.h"
extern s8 *lbl_804CB598;

u16 fn_80077BE0(void) {
    return M2C_FIELD(M2C_FIELD(lbl_804CB598, s8 **, 4), u16 *, 0xC);
}
