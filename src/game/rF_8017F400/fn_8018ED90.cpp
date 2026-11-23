/* Config menu: write options back. StringPool is scaffolding, and IGuard stands in for the interrupt guard class with vtable lbl_80380F00. */
#include "game/rF_8017F400/types.h"
#pragma auto_inline off
#pragma use_lmw_stmw on
#pragma pool_strings on
extern "C" {
void StringPool(const char** p) {
    p[0] = "%s %s %s";
    p[1] = "MCFG_SELE_ITEMS";
    p[2] = "MCFG_SELE_CONTENTS";
    p[3] = "MCFG_RETURN";
    p[4] = "MCFG_CHANGE";
    p[5] = "[%s]";
    p[6] = "MCFG_MAP";
    p[7] = "MCFG_IDENT";
    p[8] = "dummy";
    p[9] = "MCFG_OFF";
    p[10] = "MCFG_NORMAL_2";
    p[11] = "MCFG_HORIZON";
    p[12] = "MCFG_NORMAL";
    p[13] = "MCFG_MANUAL";
    p[14] = "MCFG_FAST";
    p[15] = "MCFG_SLOW";
    p[16] = "MCFG_MAXSPEED";
    p[17] = "MCFG_ON";
    p[18] = "1";
    p[19] = "2";
    p[20] = "3";
    p[21] = "4";
    p[22] = "5";
    p[23] = "6";
    p[24] = "MCFG_SIMPLE";
    p[25] = "MCFG_DETAIL";
    p[26] = "MCFG_CAPTION";
    p[27] = "MCFG_RM_VERTICAL";
    p[28] = "MCFG_RM_HORIZON";
    p[29] = "MCFG_NORMAL_E";
    p[30] = "MCFG_REVERSE";
    p[31] = "MCFG_WIDE";
    p[32] = "MCFG_ADJUST_A";
    p[33] = "MCFG_MONO";
    p[34] = "MCFG_STEREO";
    p[35] = "MCFG_SURROUND";
    p[36] = "MCFG_AUTO";
    p[37] = "window/configmode/configmode";
    p[38] = ".cms";
    p[39] = "SFX_SYS_CURSOR_WINDOW_MOVE2";
    p[40] = "SFX_SYS_CANCEL1";
    p[41] = "SFX_SYS_CURSOR_WINDOW_MOVE1";
    p[42] = "SFX_SYS_SELECT1";
}

typedef struct COpt { u32 a:2; u32 p2:1; u32 x68:2; u32 b5:1; u32 b6:1; u32 b7:1; u32 x6b:2; u32 p10:1; u32 b11:1; u32 x6c:2; u32 b14:1; u32 b15:1; u32 b16:1; u32 b17:1; u32 b18:1; u32 b19:1; u32 x70:2; u32 p22:1; u32 b23:1; u32 p24:2; u32 b26:1; u32 b27:1; u32 b28:1; u32 p29:3;
 u32 q0:5; u32 x6d:1; u32 x67:2; u32 x75:2; u32 q10:22; s8 x8; s8 x9; u8 pada[3]; s8 xd; s8 xe; s8 xf; s8 x10; } COpt;
typedef struct Cfg { u8 pad[0x30]; void* arch; u8 x34; u8 pad35; s16 x36; s16 x38; u8 pad3a[2]; f32 x3c; s16 x40, x42, x44, x46; u8 x48; u8 x49; s16 x4a; s16 x4c; u8 pad4e[0x60-0x4e]; void* x60; u8 pad64[0]; u16 fl; u8 x66, x67, x68; s8 x69; s8 x6A; u8 x6B, x6C, x6D; u8 pad6E[2]; u8 x70; s8 x71, x72, x73, x74; u8 x75; u8 x76; u8 pad77; void* x78; u8 x7c; u8 x7D[1]; } Cfg;
typedef struct CfgEnt { u8 k; u8 a; u8 b; u8 pad[5]; const char* name; } CfgEnt;
extern u8 lbl_803881E8[];
extern u8 lbl_803CAB38[];
extern char lbl_804CA798[8];
extern COpt* fn_80060728(void*);
extern int fn_801D09F0(void);
extern void fn_801097FC(COpt*);
extern u8* fn_8024BC94(void);
extern void fn_8018708C(void*);
#if TARGET_PC
extern FE10_PROTO void* fn_80177284(ptr32<const void>, void*);
#else
extern void* fn_80177284(void*, void*);
#endif
extern void fn_801C6EAC(const char*, const char*, char*);
extern void fn_800068A0(void*, char*);
extern void* fn_80078CCC(int, char*, int);
extern void* fn_80179660(void*);
extern void fn_80179854(void*, f32);
extern void fn_8017980C(void*, int, int, int);
extern void fn_801798A8(void*, int);
extern void fn_8017985C(void*, int);
extern void fn_80179864(void*, int);
extern void fn_80179888(void*, int);

extern int fn_801D09E8(int);
extern int fn_8023F87C(void);
extern void fn_80320978(s64);
extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int);
extern int fn_8023FBF4(void);
extern void fn_8023FBEC(int);
extern void fn_800CA0A4(void);
extern char lbl_804CB6C0[8];
extern void fn_800C3DF0(void*);
extern void fn_800CDB4C(void);
extern void fn_800CDADC(void);
extern void fn_8006DFC4(void);
extern void fn_8006DF48(void);
extern char lbl_80380F00[];
extern u8 lbl_803E7290[];
extern u8 lbl_803E72D8[];
#define OS_BUS_CLOCK (*(u32*)0x800000F8)
struct VB { u8 pad[0x44]; };
class VV : public VB { public: virtual void v08(); virtual void v0C(); virtual void v10(); };
struct IGuard { void* vt; int lv; IGuard() { vt = lbl_80380F00; lv = OSDisableInterrupts(); } ~IGuard() { vt = lbl_80380F00; OSRestoreInterrupts(lv); } };
#define OPT(BIT, F) if (c->fl & BIT) o->F = 0; else o->F = 1
void fn_8018ED90(Cfg* c) {
    COpt* o = fn_80060728(lbl_803CAB38);
    o->a = c->x66;
    OPT(0x200, b27);
    o->x67 = c->x67;
    o->x68 = c->x68;
    o->x9 = c->x69;
    OPT(1, b5);
    o->x8 = c->x6A;
    o->x6b = c->x6B;
    o->x6c = c->x6C;
    OPT(0x800, b7);
    OPT(0x2000, b28);
    OPT(0x4000, b6);
    OPT(2, b14);
    o->x6d = c->x6D;
    OPT(4, b15);
    OPT(8, b16);
    OPT(0x10, b17);
    {
    u8 old = fn_801D09F0();
    fn_801D09E8((c->fl >> 10) & 1);
    if (old != (u8)fn_801D09F0()) {
        while (!fn_8023F87C()) fn_80320978((s64)5 * (OS_BUS_CLOCK / 4 / 1000));
        {
        IGuard g;
        int st;
        st = fn_8023FBF4();
        fn_8023FBEC(0);
        fn_800CA0A4();
        ((VV*)lbl_803E7290)->v10();
        ((VV*)lbl_803E72D8)->v10();
        fn_800C3DF0(lbl_804CB6C0);
        fn_800CDB4C();
        fn_800CDADC();
        fn_8006DFC4();
        fn_8006DF48();
        fn_8023FBEC(st);
        }
    }
    }
    OPT(0x20, b18);
    OPT(0x40, b19);
    OPT(0x1000, b11);
    OPT(0x100, b26);
    o->x70 = c->x70;
    o->xd = c->x71;
    o->xe = c->x72;
    o->xf = c->x73;
    o->x10 = c->x74;
    o->x75 = c->x75;
    OPT(0x80, b23);
    fn_801097FC(o);
}
}
