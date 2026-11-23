#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80006A64(void *, void *, unsigned int);
FE10_PROTO void fn_8006E610(int, int, int, int, int, int);
#else
M2C_UNK fn_80006A64();
M2C_UNK fn_8006E610();
#endif
M2C_UNK fn_8007E154();
M2C_UNK fn_8007E164();
#if TARGET_PC
FE10_PROTO void fn_8007E478(float, void *);
#else
M2C_UNK fn_8007E478();
#endif
#if TARGET_PC
FE10_PROTO float * fn_8007E4C4(float *);
FE10_PROTO void fn_8007E720(float);
FE10_PROTO void fn_801D60D0(int, int, int, int, int, void *, int);
#else
s32 fn_8007E4C4();
M2C_UNK fn_8007E720();
M2C_UNK fn_801D60D0();
#endif
extern u8 lbl_8041EF60[0x20];
extern u8 lbl_804CBBE0[0x8];
extern u8 lbl_804CBBE8[0x8];
#if TARGET_PC
FE10_PROTO extern void *lbl_804CBDF8;
#else
extern s32 lbl_804CBDF8;
#endif
extern f32 lbl_804CF7E0;
extern f32 lbl_804CF7E4;
extern f32 lbl_804CF7F4;

void fn_801D9428(
#if TARGET_PC
s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4
#else
s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, M2C_UNK arg_sp0
#endif
) {
    f32 spC;
    f32 sp8;
#if TARGET_PC
    f32 *temp_r27;
    f32 *temp_r31;
#else
    s32 temp_r27;
    s32 temp_r31;
#endif

    temp_r31 = fn_8007E4C4(&spC);
    temp_r27 = fn_8007E4C4(&sp8);
    fn_8007E154();
    fn_8007E720(lbl_804CF7E0);
    fn_8007E164();
    fn_8006E610(arg0, arg1, arg2, arg3, 0, 1);
    fn_8007E154();
    fn_8007E720(lbl_804CF7E4);
    fn_8007E164();
#if TARGET_PC
    fn_8007E478(sp8, temp_r27);
#else
    fn_8007E478(temp_r27, sp8);
#endif
    fn_8007E154();
    fn_8007E720(lbl_804CF7F4);
    fn_8007E164();
    fn_80006A64(lbl_804CBDF8, lbl_8041EF60, 0x36);
    fn_801D60D0((s16) (arg0 + 3), (s16) (arg1 + 6), (s16) (M2C_FIELD(lbl_804CBBE0, s16 *, 4) - M2C_FIELD(lbl_804CBBE0, s16 *, 0)), (s16) (M2C_FIELD(lbl_804CBBE0, s16 *, 6) - M2C_FIELD(lbl_804CBBE0, s16 *, 2)), arg4, lbl_804CBBE0, 0);
    fn_8007E154();
    fn_8007E720(lbl_804CF7F4);
    fn_8007E164();
    fn_80006A64(lbl_804CBDF8, lbl_8041EF60, 0x37);
    fn_801D60D0((s16) (arg0 + 0x20), (s16) (arg1 + 2), (s16) (M2C_FIELD(lbl_804CBBE8, s16 *, 4) - M2C_FIELD(lbl_804CBBE8, s16 *, 0)), (s16) (M2C_FIELD(lbl_804CBBE8, s16 *, 6) - M2C_FIELD(lbl_804CBBE8, s16 *, 2)), arg4, lbl_804CBBE8, 0);
#if TARGET_PC
    fn_8007E478(spC, temp_r31);
#else
    fn_8007E478(temp_r31, spC);
#endif
}
