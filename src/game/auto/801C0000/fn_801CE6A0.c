#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO short fn_801237EC(void *);
#else
s16 fn_801237EC();
#endif

void fn_801CE6A0(s8 *arg0, s8 *arg1) {
    M2C_FIELD(arg0, s8 **, 0) = arg1;
    if (arg1 != NULL) {
        if ((s32) M2C_FIELD(arg1, s32 *, 0x3F0) != 0) {
            M2C_FIELD(arg0, s16 *, 6) = (s16) (s8) M2C_FIELD(arg1, u8 *, 0x114);
            M2C_FIELD(arg0, s16 *, 8) = (s16) (s8) M2C_FIELD(arg1, u8 *, 0x114);
            M2C_FIELD(arg0, s16 *, 0xA) = (s16) (s8) M2C_FIELD(arg1, u8 *, 0x114);
            M2C_FIELD(arg0, s16 *, 0xC) = fn_801237EC(arg1);
            M2C_FIELD(arg0, s16 *, 0xE) = 0;
        } else {
            M2C_FIELD(arg0, s16 *, 6) = 0;
            M2C_FIELD(arg0, s16 *, 8) = 0;
            M2C_FIELD(arg0, s16 *, 0xA) = 0;
            M2C_FIELD(arg0, s16 *, 0xC) = 0;
            M2C_FIELD(arg0, s16 *, 0xE) = 0;
        }
        M2C_FIELD(arg0, s16 *, 0x10) = (s16) M2C_FIELD(arg1, s16 *, 0x448);
        M2C_FIELD(arg0, s16 *, 0x12) = (s16) M2C_FIELD(arg1, s16 *, 0x44A);
        M2C_FIELD(arg0, s16 *, 0x14) = (s16) M2C_FIELD(arg1, s16 *, 0x44E);
        M2C_FIELD(arg0, s16 *, 0x16) = (s16) M2C_FIELD(arg1, s16 *, 0x458);
    }
}
