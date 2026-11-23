#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80011CBC(void (*)(void *), void *);
FE10_PROTO void * fn_80083B84(void *);
#else
M2C_UNK fn_80011CBC();
s8 * fn_80083B84();
#endif
extern u8 fn_800E36E4[0x88];
extern u8 lbl_80384218[0x24];
extern s32 lbl_804CB5F4;

void fn_800E376C(s8 *arg0) {
    M2C_UNK (*temp_r12)();
    s8 *temp_r3;

    temp_r12 = M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x30), M2C_UNK (**)(), 0xA0);
    if (temp_r12 != NULL) {
        temp_r12();
    }
    if (M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x30), s32 *, 0x18) & 0x40000000) {
        lbl_804CB5F4 &= 0xFFFFFFFE;
    }
    if (M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x30), s32 *, 0x18) & 0x10000000) {
        temp_r3 = fn_80083B84(lbl_80384218);
        if (temp_r3 != NULL) {
            M2C_FIELD(temp_r3, s32 *, 0x30) = (s32) (M2C_FIELD(temp_r3, s32 *, 0x30) - 1);
            M2C_FIELD(temp_r3, s32 *, 0x38) = 0;
        }
    }
    fn_80011CBC(fn_800E36E4, M2C_FIELD(arg0, s8 **, 0x30));
}
