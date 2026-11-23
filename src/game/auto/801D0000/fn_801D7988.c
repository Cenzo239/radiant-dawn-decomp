#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_80006A64(void *, void *, unsigned int);
FE10_PROTO void fn_801D60D0(int, int, int, int, int, void *, int);
#else
M2C_UNK fn_80006A64();
M2C_UNK fn_801D60D0();
#endif
extern u8 lbl_8041EF60[0x20];
extern u8 lbl_804CBAC8[0x8];
extern u8 lbl_804CBAD0[0x8];
#if TARGET_PC
FE10_PROTO extern void *lbl_804CBDF8;
#else
extern s32 lbl_804CBDF8;
#endif

void fn_801D7988(s16 arg0, s32 arg1, s32 arg2) {
    fn_80006A64(lbl_804CBDF8, lbl_8041EF60, 7);
    fn_801D60D0(arg0, arg1, (s16) (M2C_FIELD(lbl_804CBAC8, s16 *, 4) - M2C_FIELD(lbl_804CBAC8, s16 *, 0)), (s16) (M2C_FIELD(lbl_804CBAC8, s16 *, 6) - M2C_FIELD(lbl_804CBAC8, s16 *, 2)), arg2, lbl_804CBAC8, 0);
    fn_80006A64(lbl_804CBDF8, lbl_8041EF60, 8);
    fn_801D60D0((s16) (arg0 + (s16) (M2C_FIELD(lbl_804CBAC8, s16 *, 4) - M2C_FIELD(lbl_804CBAC8, s16 *, 0))), arg1, (s16) (M2C_FIELD(lbl_804CBAD0, s16 *, 4) - M2C_FIELD(lbl_804CBAD0, s16 *, 0)), (s16) (M2C_FIELD(lbl_804CBAD0, s16 *, 6) - M2C_FIELD(lbl_804CBAD0, s16 *, 2)), arg2, lbl_804CBAD0, 0);
}
