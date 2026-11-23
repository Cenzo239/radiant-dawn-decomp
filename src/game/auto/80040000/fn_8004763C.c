#include "game/auto/m2c_prelude.h"
s8 ** fn_80030CF4();
#if TARGET_PC
FE10_PROTO void fn_80031D8C(char, void *, char, char, char);
FE10_PROTO int fn_8011B77C(void *, void *);
FE10_PROTO void fn_80128D70(void *);
#else
M2C_UNK fn_80031D8C();
s32 fn_8011B77C();
M2C_UNK fn_80128D70();
#endif
extern u8 lbl_803C8E80[0x1648];
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA4E8;
#else
extern s32 lbl_804CA4E8;
#endif

s32 fn_8004763C(s32 arg0) {
    M2C_UNK *temp_r5;
    M2C_UNK *var_r30;
    u8 var_r0;
    s8 *temp_r3;

    temp_r5 = lbl_803C8E80 + 0x4A0;
    var_r30 = NULL;
    if (((s32) M2C_FIELD(M2C_FIELD(lbl_803C8E80, s8 **, 0xF4), u8 *, 8) == 0) && ((s32) M2C_FIELD(lbl_803C8E80, u8 *, 0x47A) != 0)) {
        var_r30 = lbl_803C8E80;
    }
    if (!(M2C_FIELD(lbl_803C8E80, s32 *, 0x15EC) & 1) && ((s32) M2C_FIELD(M2C_FIELD(temp_r5, s8 **, 0xF4), u8 *, 8) == 0) && ((s32) M2C_FIELD(temp_r5, u8 *, 0x47A) != 0)) {
        var_r30 = temp_r5;
    }
    if (var_r30 == NULL) {
        return 0;
    }
    if ((s8) M2C_FIELD(var_r30, u8 *, 0x114) == 0) {
        return 0;
    }
    if (fn_8011B77C(M2C_FIELD(var_r30, s32 *, 0x3F0) + 0x12C, lbl_804CA4E8) != 0) {
        fn_80128D70(M2C_FIELD(var_r30, s32 *, 0x3F0));
    }
    temp_r3 = *fn_80030CF4(var_r30);
    if (temp_r3 != NULL) {
        var_r0 = M2C_FIELD(temp_r3, u8 *, 0x12);
    } else {
        var_r0 = 0x13;
    }
    fn_80031D8C((s8) var_r0, arg0, -1, -1, -1);
    return 1;
}
