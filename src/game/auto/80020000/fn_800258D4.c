#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800444F4(int);
FE10_PROTO void fn_80084F0C(char *);
FE10_PROTO void fn_800CD4A4(int);
#else
M2C_UNK fn_800444F4();
M2C_UNK fn_80084F0C();
M2C_UNK fn_800CD4A4();
#endif
M2C_UNK fn_800CDE60();
M2C_UNK fn_80283A58();
extern u8 lbl_80361260[0xa8];

void fn_800258D4(void) {
    fn_800CDE60();
    fn_800CD4A4(5);
    fn_800444F4(6);
    fn_80084F0C(lbl_80361260 + 0x86);
    fn_80283A58();
}
