#include "game/auto/m2c_prelude.h"
M2C_UNK fn_8007E154();
M2C_UNK fn_8007E164();
#if TARGET_PC
FE10_PROTO void fn_8007E720(float);
#else
M2C_UNK fn_8007E720();
#endif

void fn_801BCA5C(f32 farg0) {
    fn_8007E154();
    fn_8007E720(farg0);
    fn_8007E164();
}
