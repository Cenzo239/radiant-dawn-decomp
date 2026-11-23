#include "game/auto/m2c_prelude.h"
#if TARGET_PC
/* Host: SFXC string pointer, not s32 */
s32 fn_801109FC(const char*);

void fn_8011097C(u16 *arg0, const char* arg1) {
    *arg0 |= fn_801109FC(arg1);
}
#else
s32 fn_801109FC();

void fn_8011097C(u16 *arg0, s32 arg1) {
    *arg0 |= fn_801109FC(arg1);
}
#endif
