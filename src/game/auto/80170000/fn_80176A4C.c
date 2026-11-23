#include "game/auto/m2c_prelude.h"
f64 fn_802952C8();
extern f32 lbl_804CE418;
extern f32 lbl_804CE43C;
extern f32 lbl_804CE440;
extern f32 lbl_804CE444;
extern f32 lbl_804CE448;
extern f32 lbl_804CE44C;

f32 fn_80176A4C(f32 farg0, f32 farg1, f32 farg2, f32 farg3) {
    f32 temp_f1;
    f32 temp_f31;
    f32 var_f3;

    temp_f1 = farg2 - farg0;
    temp_f31 = farg3 - farg1;
    if ((temp_f1 < lbl_804CE43C) && (temp_f1 > lbl_804CE440)) {
        if (temp_f31 > lbl_804CE418) {
            return lbl_804CE418;
        }
        return lbl_804CE444;
    }
    var_f3 = lbl_804CE448 * (f32) fn_802952C8(temp_f1 / temp_f31);
    if (temp_f31 < lbl_804CE418) {
        var_f3 += lbl_804CE444;
    }
    return -((lbl_804CE44C * (f32) (s32) (var_f3 / lbl_804CE44C)) - var_f3);
}
