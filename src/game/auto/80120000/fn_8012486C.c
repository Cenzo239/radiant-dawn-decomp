#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_8010B1D8(char *);
FE10_PROTO void * fn_80118F8C(void *);
FE10_PROTO int fn_8011B77C(void *, void *);
#else
u32 fn_8010B1D8();
s8 * fn_80118F8C();
s32 fn_8011B77C();
#endif
extern u8 lbl_80369088[0xe8];
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA4E0;
FE10_PROTO extern void *lbl_804CA4E4;
FE10_PROTO extern void *lbl_804CA5A8;
#else
extern s32 lbl_804CA4E0;
extern s32 lbl_804CA4E4;
extern s32 lbl_804CA5A8;
#endif

s8 *fn_8012486C(s8 *arg0) {
    u32 temp_r30;
    u32 temp_r30_2;
    u32 temp_r30_3;
    u32 temp_r30_4;
    u32 temp_r30_5;
    s8 *var_r29;

    var_r29 = NULL;
    temp_r30 = M2C_FIELD(arg0, u32 *, 0xEC);
    if (temp_r30 == fn_8010B1D8(lbl_80369088 + 0xA)) {
        if (fn_8011B77C(arg0 + 0x12C, lbl_804CA4E4) != 0) {
            var_r29 = lbl_80369088 + 0x80;
        } else if (fn_8011B77C(arg0 + 0x12C, lbl_804CA4E0) != 0) {
            var_r29 = fn_80118F8C(M2C_FIELD(arg0, u32 *, 0xEC));
        }
    } else {
        temp_r30_2 = M2C_FIELD(arg0, u32 *, 0xEC);
        if (temp_r30_2 == fn_8010B1D8(lbl_80369088 + 0x1B)) {
            if (fn_8011B77C(arg0 + 0x12C, lbl_804CA4E4) != 0) {
                var_r29 = lbl_80369088 + 0x8B;
            } else if (fn_8011B77C(arg0 + 0x12C, lbl_804CA4E0) != 0) {
                var_r29 = lbl_80369088 + 0x9A;
            } else {
                var_r29 = fn_80118F8C(M2C_FIELD(arg0, u32 *, 0xEC));
            }
        } else {
            temp_r30_3 = M2C_FIELD(arg0, u32 *, 0xEC);
            if (temp_r30_3 == fn_8010B1D8(lbl_80369088 + 0x41)) {
                if (fn_8011B77C(arg0 + 0x12C, lbl_804CA4E4) != 0) {
                    var_r29 = lbl_80369088 + 0xA9;
                } else if (fn_8011B77C(arg0 + 0x12C, lbl_804CA4E0) != 0) {
                    var_r29 = fn_80118F8C(M2C_FIELD(arg0, u32 *, 0xEC));
                }
            } else {
                temp_r30_4 = M2C_FIELD(arg0, u32 *, 0xEC);
                if (temp_r30_4 == fn_8010B1D8(lbl_80369088 + 0x56)) {
                    if (fn_8011B77C(arg0 + 0x12C, lbl_804CA5A8) != 0) {
                        var_r29 = lbl_80369088 + 0xB6;
                    } else {
                        var_r29 = fn_80118F8C(M2C_FIELD(arg0, u32 *, 0xEC));
                    }
                } else {
                    temp_r30_5 = M2C_FIELD(arg0, u32 *, 0xEC);
                    if (temp_r30_5 == fn_8010B1D8(lbl_80369088 + 0x6F)) {
                        if (fn_8011B77C(arg0 + 0x12C, lbl_804CA5A8) != 0) {
                            var_r29 = lbl_80369088 + 0xC5;
                        } else {
                            var_r29 = fn_80118F8C(M2C_FIELD(arg0, u32 *, 0xEC));
                        }
                    } else {
                        var_r29 = fn_80118F8C(M2C_FIELD(arg0, u32 *, 0xEC));
                    }
                }
            }
        }
    }
    return var_r29;
}
