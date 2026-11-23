#include "game/auto/m2c_prelude.h"
s32 strchr();

s32 fn_8010F5B4(s32 *arg0) {
    return strchr(*arg0, 0x5F) + 1;
}
