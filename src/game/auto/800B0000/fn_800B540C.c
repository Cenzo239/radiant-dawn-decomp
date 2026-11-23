#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_801092C4(unsigned short *);
FE10_PROTO int fn_8011B77C(void *, void *);
#else
s32 fn_801092C4();
s32 fn_8011B77C();
#endif
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA5A8;
#else
extern s32 lbl_804CA5A8;
#endif

void fn_800B540C(s8 *arg0, s8 *arg1) {
    s32 var_r3;
    u8 temp_r0;
    s8 *temp_r31;

    if (arg1 != NULL) {
        temp_r31 = M2C_FIELD(arg1, s8 **, 0x3F0);
        if (temp_r31 != NULL) {
            if (fn_8011B77C(temp_r31 + 0x12C, lbl_804CA5A8) != 0) {
                M2C_FIELD(arg0, s32 *, 0x50) = (s32) (M2C_FIELD(arg0, s32 *, 0x50) | 0x20000);
            }
            if (fn_801092C4(temp_r31 + 0x110) != 0) {
                M2C_FIELD(arg0, s32 *, 0x50) = (s32) (M2C_FIELD(arg0, s32 *, 0x50) | 0x40000);
            }
            temp_r0 = M2C_FIELD(temp_r31, u8 *, 0xFE);
            var_r3 = 0;
            if (((s8) temp_r0 >= 0xF) && ((s8) temp_r0 < 0x1E)) {
                var_r3 = 1;
            }
            if (var_r3 != 0) {
                M2C_FIELD(arg0, s32 *, 0x50) = (s32) (M2C_FIELD(arg0, s32 *, 0x50) | 0x10000);
            }
            if ((s8) M2C_FIELD(temp_r31, u8 *, 0xFE) >= 0x1E) {
                M2C_FIELD(arg0, s32 *, 0x50) = (s32) (M2C_FIELD(arg0, s32 *, 0x50) | 0x10000);
            }
        }
    }
}
