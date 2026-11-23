#include "game/auto/m2c_prelude.h"
M2C_UNK fn_80031490();
M2C_UNK fn_80039030();
#if TARGET_PC
FE10_PROTO void fn_80084F0C(char *);
#else
M2C_UNK fn_80084F0C();
#endif
M2C_UNK fn_8012D78C();
M2C_UNK fn_8013F204();
extern u8 lbl_80364C1C[0x424];

void fn_800A248C(void) {
    fn_80084F0C(lbl_80364C1C + 0x14);
    fn_80084F0C(lbl_80364C1C + 0x1B);
    fn_80084F0C(lbl_80364C1C + 0x22);
    fn_80084F0C(lbl_80364C1C + 0x2D);
    fn_80084F0C(lbl_80364C1C + 5);
    fn_80084F0C(lbl_80364C1C + 0x38);
    fn_80039030();
    fn_8013F204();
    fn_80031490();
    fn_8012D78C();
}
