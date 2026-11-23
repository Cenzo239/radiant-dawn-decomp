#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80021860(int, int, unsigned char);
FE10_PROTO void fn_80021B2C(unsigned char);
FE10_PROTO void fn_80021BA4(int, int, int, int);
FE10_PROTO void fn_80021BF4(int);
FE10_PROTO void fn_80021C34(int);
FE10_PROTO void fn_80021CB4(int, int, int, int);
#else
M2C_UNK fn_80021860();
M2C_UNK fn_80021B2C();
M2C_UNK fn_80021BA4();
M2C_UNK fn_80021BF4();
M2C_UNK fn_80021C34();
M2C_UNK fn_80021CB4();
#endif
M2C_UNK fn_80021EF8();
#if TARGET_PC
FE10_PROTO void fn_80022158(int, int, int);
#else
M2C_UNK fn_80022158();
#endif
M2C_UNK fn_80306FD8();

void fn_80235A00(void) {
    fn_80021860(1, 7, 0);
    fn_80021BA4(0, 1, 0, 0xF);
    fn_80021C34(1);
    fn_80021B2C(0);
    fn_80021BF4(1);
    fn_80021CB4(0, 0, 0, 0xFF);
    fn_80021EF8(0, 3);
    fn_80022158(0, 0, 0);
    fn_80022158(1, 0, 0);
    fn_80022158(2, 0, 0);
    fn_80022158(3, 0, 0);
    fn_80306FD8(0, 0, 1, 2, 3);
    fn_80306FD8(1, 0, 0, 0, 3);
    fn_80306FD8(2, 1, 1, 1, 3);
    fn_80306FD8(3, 2, 2, 2, 3);
}
