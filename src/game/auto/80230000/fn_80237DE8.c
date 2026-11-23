#include "game/auto/m2c_prelude.h"
M2C_UNK fn_8031FF98();
extern u8 lbl_80421DB0[0x1318];
extern s32 lbl_804CBF78;

void fn_80237DE8(void) {
    if ((s32) lbl_804CBF78 != 0) {
        fn_8031FF98(lbl_80421DB0);
        lbl_804CBF78 = 0;
    }
}
