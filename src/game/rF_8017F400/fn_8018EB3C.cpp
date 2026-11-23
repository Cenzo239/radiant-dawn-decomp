/* Config menu: read options into the menu (fn_8018EB3C) and menu init (fn_8018F19C). StringPool is scaffolding: it sets the pool offsets and is not game code. */
#include "game/rF_8017F400/types.h"
#pragma auto_inline off
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
typedef struct CfgEnt { u8 k; u8 a; u8 b; u8 pad[9]; const char* name; } CfgEnt;
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
void fn_8018EB3C(Cfg* c) {
    COpt* o = fn_80060728(lbl_803CAB38);
    c->fl = 0;
    c->x66 = o->a;
    if (!o->b27) c->fl |= 0x200;
    c->x67 = o->x67;
    c->x68 = o->x68;
    c->x69 = o->x9;
    if (!o->b5) c->fl |= 1;
    c->x6A = o->x8;
    c->x6B = o->x6b;
    c->x6C = o->x6c;
    if (!o->b7) c->fl |= 0x800;
    if (!o->b28) c->fl |= 0x2000;
    if (!o->b6) c->fl |= 0x4000;
    if (!o->b14) c->fl |= 2;
    c->x6D = o->x6d;
    if (!o->b15) c->fl |= 4;
    if (!o->b16) c->fl |= 8;
    if (!o->b17) c->fl |= 0x10;
    if (fn_801D09F0()) c->fl |= 0x400;
    if (!o->b18) c->fl |= 0x20;
    if (!o->b19) c->fl |= 0x40;
    if (!o->b11) c->fl |= 0x1000;
    if (!o->b26) c->fl |= 0x100;
    c->x70 = o->x70;
    c->x71 = o->xd;
    c->x72 = o->xe;
    c->x73 = o->xf;
    c->x74 = o->x10;
    c->x75 = o->x75;
    if (!o->b23) c->fl |= 0x80;
    o->x75 = 1;
    fn_801097FC(o);
}
static inline CfgEnt* Ent2(int k) { if (k < 0) return 0; if (k >= 0x1D) return 0; return &((CfgEnt*)lbl_803881E8)[k]; }
static inline u8 Vis(CfgEnt* e) {
    u32 f;
    int t;
    if (e == 0) return 0;
    f = *(u32*)(fn_8024BC94() + 0x20);
    t = f & 1;
    if (t == 0) t = (f >> 1) & 1;
    if (t == 0) t = (f >> 2) & 1;
    if (t == 0) t = (f >> 3) & 1;
    if (t) return e->b;
    return e->a;
}
void fn_8018F19C(Cfg* c) {
    char b[0x88];
    int i;
    fn_80060728(lbl_803CAB38);
    c->x34 = 0;
    c->x36 = 0;
    c->x38 = 0;
    c->x3c = 0.0f;
    c->x44 = 0;
    c->x42 = 0;
    c->x40 = 0;
    c->x48 = 0;
    c->x49 = 0;
    c->x4a = 0x10;
    c->x4c = 0x5c;
    c->x7c = 0;
    for (i = 0; i < 0x1d; i++) {
        if (Vis(Ent2(i)) == 1) { c->x7D[c->x7c] = i; c->x7c++; }
    }
    fn_8018EB3C(c);
    c->x76 = 0;
    c->arch = 0;
    c->x78 = fn_80177284(fn_8018708C, c);
    fn_801C6EAC("window/configmode/configmode", ".cms", b);
    fn_800068A0(&c->arch, b);
    {
    void* p = fn_80078CCC(0x2c, lbl_804CA798, 0);
    if (p) p = fn_80179660(p);
    c->x60 = p;
    }
    fn_80179854(c->x60, 135.0f);
    fn_8017980C(c->x60, 0x236, 0x61, 0x123);
    fn_801798A8(c->x60, 1);
    fn_8017985C(c->x60, c->x7c << 5);
    fn_80179864(c->x60, 0x120);
    fn_80179888(c->x60, 0);
}
}
