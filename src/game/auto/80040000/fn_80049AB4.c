#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_8011B77C(void *, void *, ...);
FE10_PROTO int fn_8011E414(void *);
#else
s32 fn_8011B77C();
M2C_UNK fn_8011E414();
#endif
extern u8 lbl_803CAB38[0x988];
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA58C;
#else
extern s32 lbl_804CA58C;
#endif

void fn_80049AB4(s8 *arg0) {
    s32 var_r31;
    u8 temp_r30;
    s8 *temp_r4;
    s8 *temp_r4_2;
    s8 *temp_r5;
    s8 *temp_r6;

    var_r31 = 0;
    temp_r6 = M2C_FIELD(arg0, s8 **, 0x34);
    temp_r5 = M2C_FIELD(temp_r6, s8 **, 0xF4);
    temp_r30 = M2C_FIELD(temp_r5, u8 *, 8);
    if ((fn_8011B77C(temp_r6 + 0x12C, lbl_804CA58C, temp_r5, temp_r6) == 0) && ((s8) M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x34), u8 *, 0x114) == 0)) {
        var_r31 = 1;
    }
    fn_8011E414(M2C_FIELD(arg0, s8 **, 0x34));
    if (var_r31 != 0) {
        switch ((s32) temp_r30) {                   /* irregular */
        case 0:
            M2C_FIELD(lbl_803CAB38, s32 *, 0xC8) = (s32) (M2C_FIELD(lbl_803CAB38, s32 *, 0xC8) + 1);
            M2C_FIELD(lbl_803CAB38, s16 *, 0xC0) = (s16) (M2C_FIELD(lbl_803CAB38, s16 *, 0xC0) + 1);
            return;
        case 1:
            M2C_FIELD(lbl_803CAB38, s32 *, 0xCC) = (s32) (M2C_FIELD(lbl_803CAB38, s32 *, 0xCC) + 1);
            M2C_FIELD(lbl_803CAB38, s16 *, 0xC2) = (s16) (M2C_FIELD(lbl_803CAB38, s16 *, 0xC2) + 1);
            temp_r4 = M2C_FIELD(arg0, s8 **, 0x34);
            M2C_FIELD(temp_r4, u16 *, 0x384) = (u16) (M2C_FIELD(temp_r4, u16 *, 0x384) + 1);
            temp_r4_2 = M2C_FIELD(arg0, s8 **, 0x34);
            M2C_FIELD(temp_r4_2, u16 *, 0x386) = (u16) (M2C_FIELD(temp_r4_2, u16 *, 0x386) + 1);
            return;
        case 2:
            M2C_FIELD(lbl_803CAB38, s32 *, 0xD0) = (s32) (M2C_FIELD(lbl_803CAB38, s32 *, 0xD0) + 1);
            M2C_FIELD(lbl_803CAB38, s16 *, 0xC4) = (s16) (M2C_FIELD(lbl_803CAB38, s16 *, 0xC4) + 1);
            return;
        case 3:
            M2C_FIELD(lbl_803CAB38, s32 *, 0xD4) = (s32) (M2C_FIELD(lbl_803CAB38, s32 *, 0xD4) + 1);
            M2C_FIELD(lbl_803CAB38, s16 *, 0xC6) = (s16) (M2C_FIELD(lbl_803CAB38, s16 *, 0xC6) + 1);
            break;
        }
    }
}
