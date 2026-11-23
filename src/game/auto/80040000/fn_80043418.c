#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80060728(void *);
FE10_PROTO void * fn_8007B594(s32);
FE10_PROTO void fn_8014753C(void *);
FE10_PROTO void fn_802525A0(int, float);
#else
s8 * fn_80060728();
s32 fn_8007B594(s32);
M2C_UNK fn_8014753C();
M2C_UNK fn_802525A0();
#endif
extern u8 lbl_803CAB38[0x988];
#if TARGET_PC
FE10_PROTO extern void *lbl_804CB5B8;
#else
extern s32 lbl_804CB5B8;
#endif
extern f32 lbl_804CCDF8;

void fn_80043418(s32 arg0) {
    u8 temp_r0;

    temp_r0 = M2C_FIELD((lbl_803CAB38 + M2C_FIELD(lbl_803CAB38, u8 *, 0x11)), u8 *, 0x14);
    if ((s32) temp_r0 != 0) {
        if ((temp_r0 == 1) && (((u32) M2C_FIELD(fn_80060728(lbl_803CAB38), u32 *, 4) >> 0x1FU) != 0)) {
            lbl_804CB5B8 = fn_8007B594(M2C_FIELD(lbl_803CAB38, u8 *, 0x11));
        }
        fn_802525A0(3, lbl_804CCDF8);
        fn_8014753C(arg0);
    }
}
