#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8008A5AC(char *, char);
FE10_PROTO void fn_8008A5C0(void *, unsigned short);
FE10_PROTO void fn_8008A5E4(void *, unsigned int);
FE10_PROTO void fn_8008A780(char *, int, void *);
#else
M2C_UNK fn_8008A5AC();
M2C_UNK fn_8008A5C0();
M2C_UNK fn_8008A5E4();
M2C_UNK fn_8008A780();
#endif

void fn_8010940C(
#if TARGET_PC
s8 *arg0, s8 *arg1
#else
s8 *arg0, s32 arg1
#endif
) {
    fn_8008A780(arg1, 8, arg0);
    fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 8));
    fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 9));
    fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 0xA));
    fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 0xB));
    fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 0xC));
    fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 0xD));
    fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 0xE));
    fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 0xF));
    fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 0x10));
    fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 0x11));
    fn_8008A5C0(arg1, M2C_FIELD(arg0, u16 *, 0x12));
    fn_8008A5E4(arg1, M2C_FIELD(arg0, s32 *, 0x14));
    fn_8008A5E4(arg1, M2C_FIELD(arg0, s32 *, 0x18));
    fn_8008A5E4(arg1, M2C_FIELD(arg0, s32 *, 0x1C));
}
