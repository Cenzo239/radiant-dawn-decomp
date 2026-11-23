#include "game/auto/m2c_prelude.h"
s32 fn_803164E0();
extern s32 lbl_804CBFCC;

s32 fn_80246568(s32 **arg0) {
    s32 sp8;
    s32 *temp_r4;
    s32 var_r3;

    do {
        sp8 = 0;
        var_r3 = fn_803164E0(0x4D, 2, &sp8);
        if (var_r3 == 0) {
            var_r3 = sp8;
        }
        temp_r4 = *arg0;
        if (temp_r4 != NULL) {
            *temp_r4 = sp8;
        }
        lbl_804CBFCC = var_r3;
    } while (var_r3 == -3);
    return 0;
}
