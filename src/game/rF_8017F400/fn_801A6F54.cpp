#include "game/rF_8017F400/types.h"
#pragma auto_inline off
#pragma pool_strings on
extern "C" {
void StringPool(const char** p) {
    p[0] = "%7d"; p[1] = "%s%s %s%s"; p[2] = "MD_TOMAP"; p[3] = "MD_LEADER"; p[4] = "MD_CUR"; p[5] = "MD_RTN"; p[6] = "E_TutEvent"; p[7] = "MCTTUT00_0"; p[8] = "MCTTUT00_1"; p[9] = "MCTTUT00_2"; p[10] = "%3d"; p[11] = "%02d"; p[12] = ":"; p[13] = "%s"; p[14] = "MP_LV"; p[15] = "%2d"; p[16] = "MP_HP"; p[17] = "/%3d"; p[18] = "EID_POINT_APP"; p[19] = "window/jyokyo/jyokyo"; p[20] = ".cms"; p[21] = "SFX_SYS_STATE_WINDOW_OPEN1";
}
typedef struct OData {
    u8 x0; u8 p1[3]; int x4; u8 x8; u8 p9; s16 xA; int xC; u8 p10[0x310]; int x320; int x324;
    u8 p328[0x10]; u8 x338; u8 x339; u8 p33A[6]; s16 x340; u8 p342[6]; int x348; int x34C; int x350; int x354; u16 x358;
} OData;
extern OData* lbl_804CB964;
extern void* lbl_804CB960;
extern u8 lbl_803CAB38[];
extern void fn_8006074C(u8*);
extern int fn_801D09F0(void);
extern int fn_80060960(void);
extern void* fn_8013B9A8(void);
extern void fn_80138A78(void*, f32, f32, f32, f32, f32, f32, void*);
extern void fn_801389C0(void*, u16, int, void*);
extern void fn_801A6BFC(void);
extern void fn_80250D64(int, f32, f32);
extern void fn_801C6EAC(const char*, const char*, char*);
extern void fn_800068EC(int*, char*, int);
extern void fn_80253EE4(const char*, f32);

void fn_801A6F54(void) {
    char buf[0x80];
    int z;
    fn_8006074C(lbl_803CAB38);
    if (fn_801D09F0() == 0) lbl_804CB964->x358 = 0x138;
    else lbl_804CB964->x358 = 0xEE;
    if (lbl_803CAB38[0x10] == 7) {
        if (fn_80060960()) fn_80138A78(fn_8013B9A8(), 15.0f, 12.0f, 28.0f, 22.0f, lbl_804CB964->x358, 262.0f, lbl_804CB960);
        else fn_80138A78(fn_8013B9A8(), 24.5f, 35.0f, 27.0f, 18.0f, lbl_804CB964->x358, 262.0f, lbl_804CB960);
    } else {
        fn_801389C0(fn_8013B9A8(), lbl_804CB964->x358, 0x106, lbl_804CB960);
    }
    z = 0;
    lbl_804CB964->x4 = 0xF;
    lbl_804CB964->x8 = z;
    lbl_804CB964->xA = z;
    lbl_804CB964->xC = z;
    lbl_804CB964->x320 = z;
    lbl_804CB964->x324 = z;
    lbl_804CB964->x338 = 0xFF;
    lbl_804CB964->x339 = z;
    lbl_804CB964->x340 = z;
    lbl_804CB964->x348 = z;
    lbl_804CB964->x34C = 3;
    lbl_804CB964->x350 = 1;
    lbl_804CB964->x354 = 2;
    fn_801A6BFC();
    fn_80250D64(6, 0.5f, 250.0f);
    lbl_804CB964->x0 = z;
    lbl_804CB964->xC = z;
    fn_801C6EAC("window/jyokyo/jyokyo", ".cms", buf);
    fn_800068EC(&lbl_804CB964->xC, buf, 0x2080);
    fn_80253EE4("SFX_SYS_STATE_WINDOW_OPEN1", 0.0f);
}
}
