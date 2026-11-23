#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void * fn_80066130(void *, char, char, unsigned int);
FE10_PROTO int fn_800A05B0(int, int, int);
FE10_PROTO void * fn_800CFC50(void *, char, char, unsigned char, void *);
FE10_PROTO void * fn_80135800(void *, int, int, unsigned int, unsigned int);
FE10_PROTO void * fn_8013B9A8(void);
#else
s32 fn_80066130();
s32 fn_800A05B0();
M2C_UNK fn_800CFC50();
s8 * fn_80135800();
s32 fn_8013B9A8();
#endif
extern u8 lbl_803CB770[0x10];
extern u8 lbl_803E7320[0x1208];

void fn_80172C10(s8 *arg0, s8 arg1, s8 arg2) {
    M2C_UNK var_r30;
    s8 var_r28;
    s8 var_r29;
    s8 *temp_r3;
    s32 t;

    var_r30 = 0x3B;
    var_r29 = arg2;
    var_r28 = arg1;
    if ((s32) M2C_FIELD(arg0, u8 *, 4) != 0) {
        var_r30 = 0x37;
    }
    if (fn_800A05B0(var_r30, arg1, arg2) != 0) {
        t = fn_8013B9A8();
        if (t != 0) {
            temp_r3 = fn_80135800(t, var_r28, var_r29, 0x10000000, 0);
            if (temp_r3 != NULL) {
                var_r28 = (s8) M2C_FIELD(temp_r3, u8 *, 1);
                var_r29 = (s8) M2C_FIELD(temp_r3, u8 *, 2);
            }
        }
        if ((s32) M2C_FIELD(arg0, u8 *, 4) != 0) {
            if ((fn_80066130(lbl_803CB770, var_r28, var_r29, 6) == 0) && (fn_80066130(lbl_803CB770, var_r28, var_r29, 0xF) == 0)) {
                fn_800CFC50(lbl_803E7320, var_r28, var_r29, 0, var_r30);
            }
        } else if ((fn_80066130(lbl_803CB770, var_r28, var_r29, 6) != 0) || (fn_80066130(lbl_803CB770, var_r28, var_r29, 0xF) != 0)) {
            fn_800CFC50(lbl_803E7320, var_r28, var_r29, 0, var_r30);
        }
    }
}

