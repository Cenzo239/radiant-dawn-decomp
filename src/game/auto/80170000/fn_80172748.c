#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_8011B77C(void *, void *);
FE10_PROTO s8 fn_801284C4(void *);
#else
s32 fn_8011B77C();
s8 fn_801284C4(s32);
#endif
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA4E8;
FE10_PROTO extern void *lbl_804CA4EC;
FE10_PROTO extern void *lbl_804CA5E0;
FE10_PROTO extern void *lbl_804CA650;
#else
extern s32 lbl_804CA4E8;
extern s32 lbl_804CA4EC;
extern s32 lbl_804CA5E0;
extern s32 lbl_804CA650;
#endif

s32 fn_80172748(s32 arg0) {
    s32 var_r31;

    var_r31 = -1;
    if ((fn_8011B77C(arg0 + 0x12C, lbl_804CA4E8) != 0) && (fn_8011B77C(arg0 + 0x12C, lbl_804CA4EC) == 0)) {
        if (fn_8011B77C(arg0 + 0x12C, lbl_804CA5E0) != 0) {
            var_r31 = 0;
        } else if (fn_801284C4(arg0) >= 0x1E) {
            var_r31 = 0;
        } else if (fn_8011B77C(arg0 + 0x12C, lbl_804CA650) != 0) {
            var_r31 = 1;
        }
    }
    return var_r31;
}
