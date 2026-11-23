#include "game/auto/m2c_prelude.h"
M2C_UNK fn_80246ADC();
extern s32 lbl_804CBFCC;

s32 fn_80246E0C(void) {
    fn_80246ADC();
    switch ((s32) lbl_804CBFCC) {                   /* irregular */
    case 0:
        return 0;
    case -12:
    case -256:
        return 0;
    default:
        return 0;
    }
}
