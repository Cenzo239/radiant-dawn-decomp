#include "game/auto/m2c_prelude.h"
M2C_UNK fn_8031FF98();
extern u8 lbl_80420A98[0x1318];
extern s32 lbl_804CBF70;

void fn_80237B3C(void) {
    if ((s32) lbl_804CBF70 != 0) {
        fn_8031FF98(lbl_80420A98);
        lbl_804CBF70 = 0;
    }
}
