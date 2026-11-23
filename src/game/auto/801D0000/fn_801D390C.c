#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80060728(void *);
FE10_PROTO void fn_80083B78(void *);
FE10_PROTO void fn_8014BED4(char *, void *);
#else
s8 * fn_80060728();
M2C_UNK fn_80083B78();
M2C_UNK fn_8014BED4();
#endif
s8 * fn_8024BCA0();
extern u8 lbl_8038C120[0xf];
extern u8 lbl_803CAB38[0x988];

void fn_801D390C(s8 *arg0) {
    s8 *temp_r29;
    s8 *temp_r30;

    temp_r29 = M2C_FIELD(arg0, s8 **, 0x4C);
    if ((s32) M2C_FIELD(temp_r29, u8 *, 0xA5) == 0) {
        temp_r30 = fn_8024BCA0();
        if ((((u8) M2C_FIELD(fn_80060728(lbl_803CAB38), u8 *, 0x11) == 3) || ((s32) M2C_FIELD(fn_80060728(lbl_803CAB38), u8 *, 0x11) == 0)) && !(M2C_FIELD(temp_r30, s32 *, 0x40) & 2)) {
            fn_8014BED4(lbl_8038C120, temp_r29);
        }
        M2C_FIELD(temp_r30, s32 *, 0x40) = (s32) (M2C_FIELD(temp_r30, s32 *, 0x40) | 2);
        fn_80083B78(arg0);
    }
}
