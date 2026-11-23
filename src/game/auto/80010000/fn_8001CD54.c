#include "game/auto/m2c_prelude.h"
s32 fn_8001CD54(s8 *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((M2C_FIELD(arg0, s16 *, 0xA) * 0x10) + 0x3F) & 0x7FFFFFC0;
}
