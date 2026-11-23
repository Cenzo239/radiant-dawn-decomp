#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800444F4(int);
FE10_PROTO void fn_80084F0C(char *);
#else
M2C_UNK fn_800444F4();
M2C_UNK fn_80084F0C();
#endif
M2C_UNK fn_800C4348();
#if TARGET_PC
FE10_PROTO void fn_800CD4A4(int);
#else
M2C_UNK fn_800CD4A4();
#endif
M2C_UNK fn_800CDE60();
s8 * fn_8024BCA0();
extern u8 lbl_80379288[0xb];

s32 fn_80025B0C(void) {
    s8 *temp_r3;

    temp_r3 = fn_8024BCA0();
    M2C_FIELD(temp_r3, s32 *, 0x40) = (s32) (M2C_FIELD(temp_r3, s32 *, 0x40) & 0xFFFFFFC7);
    fn_800CDE60();
    fn_800C4348();
    fn_800CD4A4(5);
    fn_800444F4(6);
    fn_80084F0C(lbl_80379288);
    return 5;
}
