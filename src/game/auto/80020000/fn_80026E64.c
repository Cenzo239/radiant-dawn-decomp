#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8002E910(void *, void *);
FE10_PROTO void fn_8002F05C(void *, void *);
FE10_PROTO void * fn_80030CBC(void *);
FE10_PROTO void fn_80110D38(void *);
FE10_PROTO void * fn_801116B8(void *);
FE10_PROTO int fn_8011B77C(void *, void *);
#else
M2C_UNK fn_8002E910();
M2C_UNK fn_8002F05C(void *, s32);
M2C_UNK fn_80030CBC();
M2C_UNK fn_80110D38(M2C_UNK);
s8 * fn_801116B8();
s32 fn_8011B77C();
#endif
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA510;
#else
extern s32 lbl_804CA510;
#endif

void fn_80026E64(
#if TARGET_PC
s8 *arg0, void *arg1
#else
s8 *arg0, s32 arg1
#endif
) {
    fn_8002F05C(arg0, arg1);
    if ((M2C_FIELD(fn_801116B8(arg1), s32 *, 4) & 0x4000) && (fn_8011B77C(arg0 + 0x12C, lbl_804CA510) != 0)) {
        M2C_FIELD(arg0, s32 *, 0x15EC) = (s32) (M2C_FIELD(arg0, s32 *, 0x15EC) | 0x200);
        fn_80110D38(fn_80030CBC(arg0 + 0x4A0));
    }
    fn_8002E910(arg0 + 0x4A0, arg0);
}
