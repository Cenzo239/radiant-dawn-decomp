#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80006A64(void *, void *, unsigned int);
#else
M2C_UNK fn_80006A64();
#endif
M2C_UNK fn_8007E154();
M2C_UNK fn_8007E164();
#if TARGET_PC
FE10_PROTO void fn_8007E720(float);
FE10_PROTO void fn_801D60D0(int, int, int, int, int, void *, int);
#else
M2C_UNK fn_8007E720();
M2C_UNK fn_801D60D0();
#endif
extern u8 lbl_8041EF60[0x20];
extern u8 lbl_804CBB50[0x8];
extern u8 lbl_804CBB98[0x8];
#if TARGET_PC
FE10_PROTO extern void *lbl_804CBDF8;
#else
extern s32 lbl_804CBDF8;
#endif
extern f32 lbl_804CF7F4;
extern f32 lbl_804CF7F8;

void fn_801D8CB4(s32 arg0, s16 arg1, s32 arg2) {
    fn_80006A64(lbl_804CBDF8, lbl_8041EF60, 0x2D);
    fn_801D60D0(arg0, (s16) (arg1 - 0x1A), (s16) (M2C_FIELD(lbl_804CBB98, s16 *, 4) - M2C_FIELD(lbl_804CBB98, s16 *, 0)), (s16) (M2C_FIELD(lbl_804CBB98, s16 *, 6) - M2C_FIELD(lbl_804CBB98, s16 *, 2)), arg2, lbl_804CBB98, 0);
    fn_8007E154();
    fn_8007E720(lbl_804CF7F8);
    fn_8007E164();
    fn_80006A64(lbl_804CBDF8, lbl_8041EF60, 0x24);
    fn_801D60D0(arg0, arg1, (s16) (M2C_FIELD(lbl_804CBB50, s16 *, 4) - M2C_FIELD(lbl_804CBB50, s16 *, 0)), (s16) (M2C_FIELD(lbl_804CBB50, s16 *, 6) - M2C_FIELD(lbl_804CBB50, s16 *, 2)), arg2, lbl_804CBB50, 0);
    fn_8007E154();
    fn_8007E720(lbl_804CF7F4);
    fn_8007E164();
}
