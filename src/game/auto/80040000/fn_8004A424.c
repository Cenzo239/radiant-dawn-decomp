#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8008A5AC(char *, char);
FE10_PROTO void fn_8008A780(char *, int, void *);
#else
M2C_UNK fn_8008A5AC();
M2C_UNK fn_8008A780();
#endif

void fn_8004A424(s8 *arg0, s32 arg1) {
    s8 *temp_r3;
    s8 *temp_r5;

    temp_r5 = M2C_FIELD(arg0, s8 **, 0);
    if (temp_r5 != NULL) {
        fn_8008A5AC(arg1, M2C_FIELD(temp_r5, u8 *, 0xFC));
    } else {
        fn_8008A5AC(arg1, 0U);
    }
    temp_r3 = M2C_FIELD(arg0, s8 **, 4);
    if (temp_r3 != NULL) {
        fn_8008A5AC(arg1, M2C_FIELD(temp_r3, u8 *, 0xFC));
    } else {
        fn_8008A5AC(arg1, 0U);
    }
    fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 0xC));
    fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 0xD));
    fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 0xE));
    fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 0xF));
    fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 0x10));
    fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 0x11));
    fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 0x12));
    fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 0x13));
    fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 0x14));
    fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 0x15));
    fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 0x16));
    fn_8008A780(arg1, 1, arg0 + 0x17);
    fn_8008A780(arg1, 0x10, arg0 + 0x18);
    fn_8008A780(arg1, 1, arg0 + 0x28);
}
