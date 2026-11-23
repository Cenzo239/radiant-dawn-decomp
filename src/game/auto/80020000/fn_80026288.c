#include "game/auto/m2c_prelude.h"
void fn_80026288(s8 *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x800), s16 *, 2) = (s16) (M2C_FIELD(arg0, s16 *, 0) - M2C_FIELD(arg0, s16 *, 2));
    M2C_FIELD(arg0, s8 **, 0x800) = NULL;
}
