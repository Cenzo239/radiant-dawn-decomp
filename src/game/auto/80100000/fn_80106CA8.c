#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8008A5AC(char *, char);
FE10_PROTO void fn_8008A5C0(void *, unsigned short);
#else
M2C_UNK fn_8008A5AC();
M2C_UNK fn_8008A5C0();
#endif

void fn_80106CA8(s8 *arg0, s32 arg1) {
    fn_8008A5C0(arg1, M2C_FIELD(arg0, u16 *, 0));
    fn_8008A5C0(arg1, M2C_FIELD(arg0, u16 *, 2));
    fn_8008A5C0(arg1, M2C_FIELD(arg0, u16 *, 4));
    fn_8008A5C0(arg1, M2C_FIELD(arg0, u16 *, 6));
    fn_8008A5C0(arg1, M2C_FIELD(arg0, u16 *, 8));
    fn_8008A5C0(arg1, M2C_FIELD(arg0, u16 *, 0xA));
    fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 0xC));
    fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 0xD));
}
