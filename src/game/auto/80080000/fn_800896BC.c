#include "game/auto/m2c_prelude.h"
M2C_UNK fn_800787E4();

s32 fn_800896BC(s8 *arg0) {
    fn_800787E4();
    M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) + 4);
    return 1;
}
