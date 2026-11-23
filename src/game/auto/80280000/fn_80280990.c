#include "game/auto/m2c_prelude.h"
extern u8 lbl_803CAB38[0x988];
extern s8 *lbl_804CC0A8;

void fn_80280990(void) {
    if (((s16) M2C_FIELD(lbl_804CC0A8, s16 *, 0x12) == 8) && ((s16) M2C_FIELD(lbl_804CC0A8, s16 *, 0x16) == 0)) {
        M2C_FIELD(lbl_804CC0A8, s16 *, 0) = (s16) M2C_FIELD(lbl_804CC0A8, s16 *, 2);
        M2C_FIELD(lbl_804CC0A8, s16 *, 2) = (s16) (M2C_FIELD(lbl_803CAB38, s16 *, 0xC4) + M2C_FIELD(lbl_803CAB38, s16 *, 0xC6) + (M2C_FIELD(lbl_803CAB38, s16 *, 0xC0) + M2C_FIELD(lbl_803CAB38, s16 *, 0xC2)));
        if ((s16) M2C_FIELD(lbl_804CC0A8, s16 *, 0) != (s16) M2C_FIELD(lbl_804CC0A8, s16 *, 2)) {
            M2C_FIELD(lbl_804CC0A8, s16 *, 0x16) = 0x20;
        }
    }
}
