#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO char * fn_800D0864(u8*);
FE10_PROTO char * fn_8011A054(void *);
FE10_PROTO void * fn_801CFF0C(void *, int);
#else
s32 fn_800D0864(u8*);
s32 fn_8011A054(s32);
s32 fn_801CFF0C();
#endif
extern u8 lbl_8036EA40[0x20];

s32 fn_801D012C(
#if TARGET_PC
void *arg0, s32 arg1
#else
s32 arg0, s32 arg1
#endif
) {
#if TARGET_PC
    void *var_r3;
#else
    s32 var_r3;
#endif

    switch (arg1) {                                 /* irregular */
    case 0x6F:
        var_r3 = fn_800D0864(lbl_8036EA40);
        break;
    case 0x6D:
        var_r3 = fn_800D0864(lbl_8036EA40 + 8);
        break;
    case 0x7E:
        var_r3 = fn_800D0864(lbl_8036EA40 + 0x18);
        break;
    default:
        var_r3 = fn_801CFF0C(arg0, arg1);
        if (var_r3 != 0) {
            var_r3 = fn_8011A054(var_r3);
        } else {
            var_r3 = 0;
        }
        break;
    }
    if (var_r3 != 0) {
        if (arg1 == 0x6F) {
            return 1;
        }
        if (fn_801CFF0C(arg0, arg1) != 0) {
            return 1;
        }
        goto block_17;
    }
block_17:
    return 0;
}
