#include "game/auto/m2c_prelude.h"
void fn_800E48AC(s8 *arg0, f32 farg0, f32 farg1, f32 farg2) {
    M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x30), f32 *, 0x1C) = farg0;
    M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x30), f32 *, 0x20) = farg1;
    M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x30), f32 *, 0x24) = farg2;
}
