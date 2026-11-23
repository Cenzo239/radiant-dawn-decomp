#include "game/rF_8017F400/types.h"
#pragma auto_inline off
#pragma pool_strings on
extern "C" {
void StringPool(const char** p) {
    p[0] = "MTM_NAVI_SELECT";
    p[1] = "MTM_NAVI_OK";
    p[2] = "MTM_YES";
    p[3] = "MTM_NO";
    p[4] = "MTM_TRI_MAP1";
    p[5] = "MTM_TRI_MAP1_EX";
    p[6] = "MTM_TRI_MAP2";
    p[7] = "MTM_TRI_MAP2_EX";
    p[8] = "MTM_TRI_MAP3";
    p[9] = "MTM_TRI_MAP3_EX";
    p[10] = "MTM_TRI_MAP4";
    p[11] = "MTM_TRI_MAP4_EX";
    p[12] = "MTM_TRI_MAP5";
    p[13] = "MTM_TRI_MAP5_EX";
    p[14] = "MTM_TRI_MAP6";
    p[15] = "MTM_TRI_MAP6_EX";
    p[16] = "window/trialmenu.tpl";
    p[17] = "%s%s %s%s %s%s";
    p[18] = "MTM_SELECT";
    p[19] = "MTM_DECIDE";
    p[20] = "MTM_RETURN";
    p[21] = "SFX_SYS_SELECT1";
    p[22] = "SFX_SYS_CANCEL1";
    p[23] = "SFX_SYS_CURSOR_WINDOW_MOVE1";
    p[24] = "SFX_SYS_ATT_WINDOW_OPEN1";
    p[25] = "MTM_CANCEL";
    p[26] = "SFX_SYS_SELECT3";
    p[27] = "SFX_SYS_CURSOR_WINDOW_MOVE2";
    p[28] = "window/achieve.cms";
    p[29] = "MTM_TRI_RES_TITLE";
    p[30] = "MTM_TRI_RES_COMP_TURN";
    p[31] = "%d";
    p[32] = "MTM_TRI_RES_TURN";
    p[33] = "#C01%s  #C06%02d\x81""F%02d\x81""F%02d";
    p[34] = "MTM_TRI_RES_PLAYTIME";
    p[35] = "MTM_TRI_RES_TACT_RANK";
    p[36] = "%c";
    p[37] = "MTM_TRI_RES_ALIVE_RANK";
    p[38] = "MTM_TRI_RES_BTL_RANK";
    p[39] = "MTM_TRI_RES_TOTAL_RANK";
    p[40] = "#C01%s   #C06%02d\x81""F%02d\x81""F";
}
typedef struct CData { u8 x0[4]; u8 x4; u8 x5; s16 x6; s16 x8; s16 xA; u8 pad0[8]; u8 x14[2]; u8 x16; u8 x17; s16 x18; s16 x1A; s16 x1C; u8 pad[0x28-0x1E]; char title[0x60]; u8 x88; } CData;
typedef struct CProc { u8 pad[0x30]; CData* d; } CProc;
extern const char* fn_800D0864(const char*);
#if TARGET_PC
extern FE10_PROTO char * fn_800CEC24(void);
extern FE10_PROTO char * fn_800CEB4C(void);
extern FE10_PROTO char * fn_800CF3A4(void);
extern FE10_PROTO char * fn_800CF470(void);
#else
extern int fn_800CEC24(void);
extern int fn_800CEB4C(void);
extern int fn_800CF3A4(void);
extern int fn_800CF470(void);
#endif
extern int fn_80290DDC(char*, const char*, ...);
extern void fn_801ADE00(CData*);
extern void fn_80253EE4(const char*, f32);
#pragma use_lmw_stmw on
void fn_801AEB78(CProc* p) {
    CData* d = p->d;
    d->x88 = 0;
    d->x4 = 1;
    d->x5 = 1;
    d->x8 = 0x31;
    d->xA = d->x6 * 0x18 + 0x78;
    d->x16 = 0;
    fn_80290DDC(d->title, "%s%s %s%s %s%s", fn_800CF3A4(), fn_800D0864("MTM_SELECT"), fn_800CEB4C(), fn_800D0864("MTM_DECIDE"), fn_800CEC24(), fn_800D0864("MTM_RETURN"));
}
#pragma use_lmw_stmw off
void fn_801AEDC4(CProc* p) {
    CData* d = p->d;
    d->x88 = 1;
    d->x5 = 0;
    d->x16 = 1;
    d->x17 = 1;
    d->x18 = 0;
    d->x1A = 0x1C2;
    d->x1C = 0x3D;
    fn_801ADE00(d);
    fn_80253EE4("SFX_SYS_ATT_WINDOW_OPEN1", 0.0f);
    fn_80290DDC(d->title, "%s%s %s%s %s%s", fn_800CF470(), fn_800D0864("MTM_SELECT"), fn_800CEB4C(), fn_800D0864("MTM_DECIDE"), fn_800CEC24(), fn_800D0864("MTM_CANCEL"));
}
}
