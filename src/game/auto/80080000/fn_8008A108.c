#include "game/auto/m2c_prelude.h"
extern s16 lbl_804CA3C8;

void fn_8008A108(void) {
    if ((s16) lbl_804CA3C8 < 0) {
        lbl_804CA3C8 = 0;
    }
}
