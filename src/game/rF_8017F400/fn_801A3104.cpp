#include "game/rF_8017F400/types.h"
#pragma auto_inline off
#pragma pool_strings on
extern "C" {
void StringPool(const char** p) {
    p[0] = "MIR_NAVI_SELECT"; p[1] = "\x81H\x81H\x81H\x81H\x81H\x81H"; p[2] = "window/illustroom/illustroom"; p[3] = ".cms"; p[4] = "%s%s %s%s %s%s"; p[5] = "MIR_SELECT"; p[6] = "MIR_END"; p[7] = "MIR_DECIDE"; p[8] = "SFX_SYS_SELECT1"; p[9] = "SFX_SYS_CANCEL1"; p[10] = "SFX_SYS_CURSOR_WINDOW_MOVE1"; p[11] = "%s%s %s\x81^%s%s"; p[12] = "MIR_RETURN"; p[13] = "illust/akatuki/";
}
struct Pic { const char* x0; const char* x4; };
typedef struct IData {
    u8 p0[4]; void* x4; void* x8; int xC; s16 x10; s16 x12; s16 x14; s16 x16; u8 p18[8]; u8 x20; u8 p21; s16 x22; u8 p24[6]; s16 x2A; u8 p2C[4]; Pic* x30; char x34[0x80];
} IData;
extern IData* lbl_804CB94C;
extern Pic lbl_80388AA0[];
extern const char* fn_800D0864(const char*);
#if TARGET_PC
extern FE10_PROTO char * fn_800CEB4C(void);
extern FE10_PROTO char * fn_800CEC24(void);
extern FE10_PROTO char * fn_800CF53C(void);
extern FE10_PROTO char * fn_800CF3A4(void);
#else
extern int fn_800CEB4C(void);
extern int fn_800CEC24(void);
extern int fn_800CF53C(void);
extern int fn_800CF3A4(void);
#endif
extern int fn_80290DDC(char*, const char*, ...);
extern void fn_80006A2C(void**);
extern char* strcpy(char*, const char*);
extern char* fn_80291110(char*, const char*);
extern void fn_801C6EAC(const char*, const char*, char*);
extern void fn_800068A0(void**, char*);

#pragma use_lmw_stmw on
void fn_801A3104(void) {
    IData* d = lbl_804CB94C;
    int z = 0;
    Pic* q = lbl_80388AA0;
    d->xC = 3;
    lbl_804CB94C->x34[0] = z;
    d->x30 = q;
    d->x20 = z;
    for (; q->x0; q++) d->x20++;
    {
    int r = d->x20 / 3;
    if (d->x20 % 3 > 0) r++;
    d->x22 = r * 0x1C + 0x30;
    if (d->x22 > 0xF0) d->x22 = 0xF0;
    }
    {
    int i;
    int z2 = 0;
    i = lbl_804CB94C->x10 - lbl_804CB94C->x2A * 3;
    lbl_804CB94C->x16 = z2;
    lbl_804CB94C->x12 = (i % 3) * 0x92 + 0x4D;
    lbl_804CB94C->x14 = (i / 3) * 0x1C + 0x98;
    fn_80290DDC(lbl_804CB94C->x34, "%s%s %s%s %s%s", fn_800CF53C(), fn_800D0864("MIR_SELECT"), fn_800CEC24(), fn_800D0864("MIR_END"), fn_800CEB4C(), fn_800D0864("MIR_DECIDE"));
    if (lbl_804CB94C->x4) {
        fn_80006A2C(&lbl_804CB94C->x4);
        lbl_804CB94C->x4 = (void*)z2;
    }
    if (lbl_804CB94C->x8) {
        fn_80006A2C(&lbl_804CB94C->x8);
        lbl_804CB94C->x8 = 0;
    }
    }
}
#pragma use_lmw_stmw on
void fn_801A3898(void) {
    char buf[0x48];
    IData* d = lbl_804CB94C;
    int z = 0;
    d->xC = 4;
    lbl_804CB94C->x34[0] = z;
    fn_80290DDC(lbl_804CB94C->x34, "%s%s %s\x81^%s%s", fn_800CF3A4(), fn_800D0864("MIR_SELECT"), fn_800CEB4C(), fn_800CEC24(), fn_800D0864("MIR_RETURN"));
    if (lbl_804CB94C->x8) {
        fn_80006A2C(&lbl_804CB94C->x8);
        lbl_804CB94C->x8 = (void*)z;
    }
    lbl_804CB94C->x8 = lbl_804CB94C->x4;
    strcpy(buf, "illust/akatuki/");
    fn_80291110(buf, d->x30[lbl_804CB94C->x10].x4);
    fn_801C6EAC(buf, ".cms", buf);
    fn_800068A0(&lbl_804CB94C->x4, buf);
}
#pragma use_lmw_stmw off
}
