#include "game/rC2_8005259C/more.h"
#pragma use_lmw_stmw on

extern "C" void fn_80052A78(void) {
    if (fn_800677E4()) {
        ((GD2*)&lbl_803CAB38)->b92c = 0xb;
    } else {
        GD2* g = (GD2*)&lbl_803CAB38;
        s8 y = g->f938;
        s8 x = g->f934;
        fn_80118098(lbl_803EC898, x, y);
        g->b92c = 9;
    }
    if (lbl_803CA870.b16) {
        switch (((GD2*)&lbl_803CAB38)->b92c) {
        case 9: ((GD2*)&lbl_803CAB38)->b92c = 0xc; break;
        case 10: ((GD2*)&lbl_803CAB38)->b92c = 0xd; break;
        case 11: ((GD2*)&lbl_803CAB38)->b92c = 0xe; break;
        }
    }
}
