#include "game/auto/m2c_prelude.h"
void fn_800263A0(s8 *arg0, s32 arg1) {
    s8 *temp_r3;
    s8 *temp_r5;
    s8 *temp_r5_2;
    s8 *temp_r5_3;
    s8 *temp_r5_4;

    temp_r5 = arg0 + ((M2C_FIELD(arg0, u8 *, 0xA0) + arg1) * 2);
    M2C_FIELD(temp_r5, u16 *, 0x20) = (u16) (M2C_FIELD(temp_r5, u16 *, 0x20) | 1);
    temp_r5_2 = arg0 + ((arg1 + M2C_FIELD(arg0, u8 *, 0xA0) + 1) * 2);
    M2C_FIELD(temp_r5_2, u16 *, 0x20) = (u16) (M2C_FIELD(temp_r5_2, u16 *, 0x20) | 1);
    temp_r5_3 = arg0 + ((arg1 + M2C_FIELD(arg0, u8 *, 0xA0) + 2) * 2);
    M2C_FIELD(temp_r5_3, u16 *, 0x20) = (u16) (M2C_FIELD(temp_r5_3, u16 *, 0x20) | 1);
    temp_r5_4 = arg0 + ((arg1 + M2C_FIELD(arg0, u8 *, 0xA0) + 3) * 2);
    M2C_FIELD(temp_r5_4, u16 *, 0x20) = (u16) (M2C_FIELD(temp_r5_4, u16 *, 0x20) | 1);
    temp_r3 = arg0 + ((arg1 + M2C_FIELD(arg0, u8 *, 0xA0) + 4) * 2);
    M2C_FIELD(temp_r3, u16 *, 0x20) = (u16) (M2C_FIELD(temp_r3, u16 *, 0x20) | 1);
}
