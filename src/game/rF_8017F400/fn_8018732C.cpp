/* Config menu list draw, plus two small neighbours. StringPool is scaffolding: it sets the pool offsets and is not game code. */
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
typedef struct Rect16 { s16 x, y, w, h; } Rect16;
typedef struct CfgEnt { u8 k; u8 a; u8 b; u8 pad[5]; const char* name; } CfgEnt;
typedef struct Cfg { u8 pad[0x36]; s16 x36; u8 pad38[4]; f32 x3c; s16 x40, x42, x44, x46; u8 x48; u8 x49; u8 pad4a[0x7D-0x4a]; u8 x7D[1]; } Cfg;
class Pad { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual u32 v3C(); virtual void v40(); virtual void v44(); virtual u32 v48(); };
extern Pad* lbl_804CB5B8;
extern u8 lbl_803881E8[];
extern s8 lbl_804CB918;
extern Rect16 lbl_804CB920;
extern f32 fn_8017F68C(int, f32, f32, f32, f32);
extern void fn_801BCA5C(f32);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
#if TARGET_PC
extern FE10_PROTO void fn_8007E74C(ptr32<const void>, ptr32<const void>);
#else
extern void fn_8007E74C(void*, Rect16*);
#endif
extern void fn_8007E7B4(void);
extern void fn_80186F8C(void* p, void* arg);
extern u8* fn_8024BC94(void);
extern void fn_801875CC(Cfg* c, CfgEnt* e, f32 x0, f32 y, int hl);
extern void fn_8018F4F4(void*);
extern void fn_80253EE4(const char*, f32);
static inline CfgEnt* EntAt(int k) { CfgEnt* p; if (k < 0) return 0; p = (CfgEnt*)(lbl_803881E8 + (k << 4)); if (k >= 0x1D) p = 0; return p; }
static inline int Vis(CfgEnt* e) {
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
void fn_8018732C(Cfg* c) {
    int i;
    if (!lbl_804CB918) lbl_804CB918 = 1;
    lbl_804CB920.x = 0x28; lbl_804CB920.y = 0x5f; lbl_804CB920.w = 0x208; lbl_804CB920.h = 0x119;
    if (c->x44 > 0) {
        c->x44--;
        c->x3c = fn_8017F68C(0, c->x40, c->x42, c->x46 - c->x44, c->x46);
    }
    fn_801BCA5C(-2.0f);
    fn_8007E154();
    fn_8007E74C(fn_80186F8C, &lbl_804CB920);
    fn_8007E164();
    for (i = 0; i < 0xb; i++) {
        u8* p;
        int line = i + (int)c->x3c - 1;
        p = (u8*)c + line;
        if (Vis(EntAt(p[0x7d]))) {
            f32 fr = c->x3c - (int)c->x3c;
            CfgEnt* e = EntAt(p[0x7d]);
            fn_801875CC(c, e, 22.0f, 32.0f * (i - fr) + 64.0f, line == c->x48 && c->x49 == 0);
        }
    }
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
    fn_801BCA5C(-2.0f);
}
void fn_8018F394(Cfg* c) {
    switch (c->x36) { case 0: fn_8018F4F4(c); break; default: break; }
}
u8 fn_8018F3AC(int v, const u8* tbl, int n) {
    int sel = 0;
    int old;
    int i;
    for (i = 0; i < n; i++) if (v == tbl[i]) { sel = i; break; }
    old = sel;
    if (sel > 0) { if (lbl_804CB5B8->v3C() & 0x100001) sel--; }
    else { if (lbl_804CB5B8->v48() & 0x100001) sel = n - 1; }
    if (sel < n - 1) { if (lbl_804CB5B8->v3C() & 0x200002) sel++; }
    else { if (lbl_804CB5B8->v48() & 0x200002) sel = 0; }
    if (sel != old) fn_80253EE4("SFX_SYS_CURSOR_WINDOW_MOVE2", 0.0f);
    return tbl[sel];
}
}
