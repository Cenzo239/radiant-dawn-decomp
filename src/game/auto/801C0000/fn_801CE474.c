#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80030CF4(void *);
FE10_PROTO int fn_8011B77C(void *, void *);
#else
s8 ** fn_80030CF4();
s32 fn_8011B77C();
#endif
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA4E8;
FE10_PROTO extern void *lbl_804CA4EC;
#else
extern s32 lbl_804CA4E8;
extern s32 lbl_804CA4EC;
#endif

s8 **fn_801CE474(s8 **arg0) {
    s32 var_r31;
    u8 var_r0;
    s8 **temp_r30;
    s8 **temp_r3;
    s8 *temp_r0;
    s8 *temp_r3_2;
    s8 *temp_r4;

    temp_r0 = *arg0;
    if (temp_r0 != NULL) {
        temp_r3 = fn_80030CF4(temp_r0);
        temp_r4 = *arg0;
        temp_r30 = temp_r3;
        if (temp_r4 != NULL) {
            var_r31 = M2C_FIELD(temp_r4, s32 *, 0x3F0);
        } else {
            var_r31 = 0;
        }
        if ((temp_r3 != NULL) && (var_r31 != 0) && (fn_8011B77C(var_r31 + 0x12C, lbl_804CA4E8) != 0) && (fn_8011B77C(var_r31 + 0x12C, lbl_804CA4EC) == 0)) {
            temp_r3_2 = *temp_r30;
            if (temp_r3_2 != NULL) {
                var_r0 = M2C_FIELD(temp_r3_2, u8 *, 0x12);
            } else {
                var_r0 = 0x13;
            }
            if (var_r0 == 5) {
                return NULL;
            }
            goto block_13;
        }
block_13:
        return temp_r30;
    }
    return NULL;
}
