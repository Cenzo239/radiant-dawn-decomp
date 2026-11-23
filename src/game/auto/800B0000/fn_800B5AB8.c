#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80007F10(void *);
FE10_PROTO int fn_80009FD0(void *, int, unsigned int);
FE10_PROTO float fn_800A7370(void *, char *);
#else
s8 * fn_80007F10();
s32 fn_80009FD0();
f32 fn_800A7370();
#endif
f32 fn_800A84A4();
extern u8 lbl_803657E8[0x360];

s32 fn_800B5AB8(s8 *arg0) {
    s32 temp_r3_2;
    s32 temp_r3_3;
    s32 temp_r4;
    s32 var_r31;
    s32 var_r31_2;
    s8 *temp_r3;

    if ((s32) M2C_FIELD(arg0, s32 *, 0x78) == 0) {
        return 0;
    }
    temp_r4 = M2C_FIELD(arg0, s32 *, 0x30);
    if (temp_r4 == 0) {
        return 0;
    }
    if ((s8 *) M2C_FIELD(arg0, s8 **, 0x7C) == NULL) {
        return 0;
    }
    temp_r3 = fn_80007F10(temp_r4);
    if (temp_r3 == NULL) {
        return 0;
    }
    if (M2C_FIELD(arg0, s32 *, 0x50) & 0x01000000) {
        var_r31_2 = (s32) ((f32) M2C_FIELD(temp_r3, s32 *, 0x18) - fn_800A84A4(lbl_803657E8 + 0x1C1));
        temp_r3_2 = fn_80009FD0(temp_r3, 0, 0x18);
        if ((temp_r3_2 >= 0) && (var_r31_2 > temp_r3_2)) {
            var_r31_2 = temp_r3_2;
        }
        return var_r31_2;
    }
    if (M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x7C), u16 *, 8) & 0x800) {
        var_r31 = (s32) ((f32) M2C_FIELD(temp_r3, s32 *, 0x18) - fn_800A7370(M2C_FIELD(arg0, s32 *, 0x78), lbl_803657E8 + 0x1C1));
        temp_r3_3 = fn_80009FD0(temp_r3, 0, 0x18);
        if ((temp_r3_3 >= 0) && (var_r31 > temp_r3_3)) {
            var_r31 = temp_r3_3;
        }
        return var_r31;
    }
    return M2C_FIELD(temp_r3, s32 *, 0x18);
}
