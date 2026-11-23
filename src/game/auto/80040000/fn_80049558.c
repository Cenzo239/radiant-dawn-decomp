#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_8002BCC4(void *);
FE10_PROTO int fn_80030D84(void *);
FE10_PROTO void fn_80103D50(void *, int);
#else
M2C_UNK fn_8002BCC4();
s32 fn_80030D84();
M2C_UNK fn_80103D50();
#endif
extern u8 lbl_803C8E80[0x1648];

void fn_80049558(void) {
    M2C_UNK *var_r29;
    s32 var_r28;
    s32 t;

    fn_8002BCC4(lbl_803C8E80);
    var_r28 = 0;
    do {
        switch (var_r28) {                          /* irregular */
        case 0:
            var_r29 = lbl_803C8E80;
            break;
        case 1:
            var_r29 = lbl_803C8E80 + 0x4A0;
            break;
        case 2:
            var_r29 = lbl_803C8E80 + 0x940;
            break;
        default:
            var_r29 = NULL;
            break;
        }
        if ((fn_80030D84(var_r29) == 0) && ((t = M2C_FIELD(var_r29, s32 *, 0x3F0)) != 0)) {
            fn_80103D50(t, 0x10);
        }
        var_r28 += 1;
    } while (var_r28 < 2);
}

