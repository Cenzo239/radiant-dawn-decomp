#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_8011B77C(void *, void *);
FE10_PROTO int fn_8011FF28(void *, int, ...);
#else
s32 fn_8011B77C();
s32 fn_8011FF28();
#endif
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA4E0;
FE10_PROTO extern void *lbl_804CA558;
#else
extern s32 lbl_804CA4E0;
extern s32 lbl_804CA558;
#endif

s32 fn_801C6FB8(s32 arg0, s8 *arg1) {
    if (fn_8011B77C(arg0 + 0x12C, lbl_804CA4E0) == 0) {
        return 0;
    }
    if ((fn_8011B77C(arg0 + 0x12C, lbl_804CA558) != 0) && !(M2C_FIELD(arg1, s32 *, 0x3C) & 0x10000000)) {
        return 0;
    }
    if ((M2C_FIELD(arg1, s32 *, 0x3C) & 0x10000000) && (fn_8011B77C(arg0 + 0x12C, lbl_804CA558) == 0)) {
        return 0;
    }
    return fn_8011FF28(arg0, 1, 1);
}
