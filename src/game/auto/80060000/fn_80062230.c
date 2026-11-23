#include "game/auto/m2c_prelude.h"
f32 fn_801142F0(void *, f32, f32);
extern u8 lbl_803EC898[0x15867];

void fn_80062230(s8 *arg0, f32 farg0, f32 farg1) {
    f32 var_f1;

    var_f1 = fn_801142F0(lbl_803EC898, farg0, farg1);
    if (var_f1 > M2C_FIELD(lbl_803EC898, f32 *, 0x1D428)) {
        var_f1 = M2C_FIELD(lbl_803EC898, f32 *, 0x1D428);
    }
    M2C_FIELD(arg0, f32 *, 0x93C) = farg0;
    M2C_FIELD(arg0, f32 *, 0x940) = farg1;
    M2C_FIELD(arg0, f32 *, 0x94C) = var_f1;
}
