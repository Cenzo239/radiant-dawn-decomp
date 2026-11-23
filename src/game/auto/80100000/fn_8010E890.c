#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8008A5AC(char *, char);
#else
M2C_UNK fn_8008A5AC();
#endif

void fn_8010E890(s8 *arg0, s32 arg1) {
    u8 var_r4;
    s8 *temp_r5;

    temp_r5 = M2C_FIELD(arg0, s8 **, 0);
    if (temp_r5 != NULL) {
        var_r4 = M2C_FIELD(temp_r5, u8 *, 0xFC);
    } else {
        var_r4 = 0;
    }
    fn_8008A5AC(arg1, var_r4);
    fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 4));
    fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 5));
    fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 6));
    fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 7));
}
