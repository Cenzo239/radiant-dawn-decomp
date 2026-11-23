#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8008A5AC(char *, char);
FE10_PROTO void fn_8008A5C0(void *, unsigned short);
FE10_PROTO void fn_8008A5E4(void *, unsigned int);
FE10_PROTO void fn_8008A71C(char *, char *);
#else
M2C_UNK fn_8008A5AC();
M2C_UNK fn_8008A5C0();
M2C_UNK fn_8008A5E4();
M2C_UNK fn_8008A71C();
#endif

void fn_80111D68(
#if TARGET_PC
s8 *arg0, s8 *arg1
#else
s8 *arg0, s32 arg1
#endif
) {
    s8 *temp_r5;

    temp_r5 = M2C_FIELD(arg0, s8 **, 0);
    if (temp_r5 == NULL) {
        fn_8008A5E4(arg1, 0);
        return;
    }
    fn_8008A5C0(arg1, M2C_FIELD(temp_r5, u16 *, 0xE));
    fn_8008A5C0(arg1, M2C_FIELD(arg0, u16 *, 4));
    if (((u8) M2C_FIELD(arg0, u8 *, 5) >> 5U) & 1) {
        fn_8008A71C(arg1, arg0 + 6);
        fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 0x1E));
        fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 0x1F));
        fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 0x20));
        fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 0x21));
        fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 0x22));
        fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 0x23));
        fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 0x24));
        fn_8008A5AC(arg1, M2C_FIELD(arg0, u8 *, 0x25));
    }
}
