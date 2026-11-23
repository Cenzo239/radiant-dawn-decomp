/* near miss: 6 real words (plus the jump table name, which the scratch scorer does not normalise). Only the first slider (case 4) is off: arch wants r28 and w wants r29, ours swaps them. Generated from the scratch gen87.py; the P markers are for sw.py. */
#include "game/rF_8017F400/types.h"
#pragma auto_inline off
#pragma inline_max_size(100000)
#pragma inline_max_total_size(1000000)
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
typedef struct GXColor2 { u8 r,g,b,a; } GXColor2;
typedef struct TexH { u16 x0, x2; } TexH;
typedef struct CfgEnt { u8 k; u8 pad[7]; const char* name; } CfgEnt;
typedef struct Cfg { u8 pad[0x30]; void* arch; u8 pad34[0x48-0x34]; u8 x48; u8 pad49[0x58-0x49]; int x58; int x5C; u8 pad60[4]; u16 fl; u8 x66, x67, x68; s8 x69; s8 x6A; u8 x6B, x6C, x6D; u8 pad6E[2]; u8 x70; s8 x71, x72, x73, x74; s8 x75; u8 pad76[7]; u8 x7D[1]; } Cfg;
extern const char* fn_800D0864(const char*);
extern int fn_800CA3DC(const char*, int, f32);
extern void fn_800CB3A8(f32 a, f32 b, s16 x, s16 y, u8 c, int d, int e, const char* fmt, ...);
extern int fn_80290DDC(char*, const char*, ...);
extern void fn_801BCA94(void);
extern void fn_801BCA5C(f32);
extern u8* fn_800CD204(int);
extern void* fn_80006A0C(void*, int);
extern void fn_801BC88C(void* a, int b, GXColor2* c, int d, u32 fl, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, f32 f7, f32 f8);
extern void fn_80186FA4(f32, f32, f32, f32, GXColor2*);
extern u8* fn_8024BC94(void);
extern u8 lbl_803881E8[];
static inline GXColor2 mkc(const u8* p, u8 a) { GXColor2 c; c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = a; return c; }
#define FX(v) ((f32)(int)(v))
static inline const GXColor2& mk2(const u8* p, u8 a) { GXColor2 c; c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = a; return c; }
static inline void Dr2(void* arch, int tile, GXColor2* c, GXColor2* t, f32 x1, f32 y1, f32 x2, f32 y2, u16 th, u16 tw) {
    *(u32*)t = *(u32*)c;
    fn_801BC88C(arch, tile, t, 0x11, 0, x1, y1, x2, y2, 0.0f, 0.0f, tw, th);
}
static inline void Sl3(int px, f32 y) {
    u8* p = fn_800CD204(1);
    GXColor2 k2;
    k2.r = p[0]; k2.g = p[1]; k2.b = p[2]; k2.a = p[3];
    {
    f32 yy = 8.0f + y;
    fn_80186FA4(px, (int)yy - 3, px, (int)yy + 0xB, &k2);
    }
}
static inline void Sl2(int px, f32 y) { Sl3(px, y); }
static inline f32 Fi(f32 v) { return (f32)(int)v; }
static inline f32 Gi(u16 v) { return v; }
static inline void Slider(Cfg* c, f32 x, f32 y, s8 pct, int tile, int& px) {
    GXColor2 k2;
    GXColor2 k;
    GXColor2 kt;
    u8* pp;
/*P*/
    u16 h;
    u16 w;
    void* arch;
    u8* p;
    TexH** t;
/*E*/
    arch = c->arch;
    px = (int)x + pct * 0xF0 / 100;
    t = (TexH**)fn_80006A0C(arch, tile);
    w = (*t)->x2; h = (*t)->x0;
    pp = fn_800CD204(1);
    k.r = pp[0]; k.g = pp[1]; k.b = pp[2]; k.a = 0xFF;
    {
    TexH** t2 = (TexH**)fn_80006A0C(arch, tile);
    Dr2(arch, tile, &k, &kt, FX(x), FX(8.0f + y), FX(x) + (f32)w, FX(8.0f + y) + (f32)h, (*t2)->x0, (*t2)->x2);
    }
    fn_801BCA5C(-1.0f);
    pp = fn_800CD204(1);
    k2.r = pp[0]; k2.g = pp[1]; k2.b = pp[2]; k2.a = pp[3];
    {
    f32 yy = 8.0f + y;
    fn_80186FA4(px, (int)yy - 3, px, (int)yy + 0xB, &k2);
    }
    fn_801BCA5C(1.0f);
}
static inline void Slider4(Cfg* c, f32 x, f32 y, s8 pct, int tile, int& px) {
    GXColor2 k2;
    GXColor2 k;
    GXColor2 kt;
    u8* pp;
/*P*/
    u16 w;
    u16 h;
    void* arch;
    u8* p;
    TexH** t;
/*E*/
    arch = c->arch;
    px = (int)x + pct * 0xF0 / 100;
    t = (TexH**)fn_80006A0C(arch, tile);
    w = (*t)->x2; h = (*t)->x0;
    pp = fn_800CD204(1);
    k.r = pp[0]; k.g = pp[1]; k.b = pp[2]; k.a = 0xFF;
    {
    TexH** t2 = (TexH**)fn_80006A0C(arch, tile);
    Dr2(arch, tile, &k, &kt, FX(x), FX(8.0f + y), FX(x) + (f32)w, FX(8.0f + y) + (f32)h, (*t2)->x0, (*t2)->x2);
    }
    fn_801BCA5C(-1.0f);
    pp = fn_800CD204(1);
    k2.r = pp[0]; k2.g = pp[1]; k2.b = pp[2]; k2.a = pp[3];
    {
    f32 yy = 8.0f + y;
    fn_80186FA4(px, (int)yy - 3, px, (int)yy + 0xB, &k2);
    }
    fn_801BCA5C(1.0f);
}
static inline int Is0(int t) { return t == 0; }
class Pad { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual int v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4C(); virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5C(); virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6C(); virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7C(); virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8C(); virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9C(); virtual void vA0(); virtual int vA4(); };
extern Pad* lbl_804CB5B8;
#define PAD lbl_804CB5B8
static inline u16 Pa(void) { return PAD->vA4() != 0; }
static inline BOOL Pv(void) { BOOL r; if (PAD->v14() == 0 || PAD->v14() == 1) r = 1; else r = 0; return r; }
static inline u8* EntAt(int k) { u8* p; if (k < 0) return 0; p = lbl_803881E8 + (k << 4); if (k >= 0x1D) p = 0; return p; }
#define W(k) (fn_800CA3DC(fn_800D0864(k), -1, 1.0f) / 2)
#define ITEMU(T, KEY, NEXT) { \
    int col; \
    if (hl) { u = T == 0; if (u) col = 0x36; else col = 0; } else { u = T == 0; col = u; } \
    s = fn_800D0864(KEY); \
    if (u) { \
        char b[0x60]; \
        fn_80290DDC(b, "[%s]", s); \
        { int w = fn_800CA3DC(b, -1, 1.0f) / 2; \
        fn_800CB3A8(1.0f, 0.0f, (int)x - w, y, (u8)col, 1, 0, b); } \
    } else { \
        int w = fn_800CA3DC(s, -1, 1.0f) / 2; \
        fn_800CB3A8(1.0f, 0.0f, (int)x - w, y, (u8)col, 1, 0, s); \
    } \
    x += W(KEY) + W(NEXT) + 0x18; \
}
#define ITEMH(T, KEY, NEXT) { \
    if (hl) { u = T == 0; if (u) hl = 0x36; else hl = 0; } else { u = T == 0; hl = u; } \
    s = fn_800D0864(KEY); \
    if (u) { \
        char b[0x60]; \
        fn_80290DDC(b, "[%s]", s); \
        { int w = fn_800CA3DC(b, -1, 1.0f) / 2; \
        fn_800CB3A8(1.0f, 0.0f, (int)x - w, y, (u8)hl, 1, 0, b); } \
    } else { \
        int w = fn_800CA3DC(s, -1, 1.0f) / 2; \
        fn_800CB3A8(1.0f, 0.0f, (int)x - w, y, (u8)hl, 1, 0, s); \
    } \
    x += W(KEY) + W(NEXT) + 0x18; \
}
#define ITEM(SEL, KEY, NEXT) { \
    int col; \
    if (hl) { if (SEL) col = 0x36; else col = 0; } else col = SEL; \
    s = fn_800D0864(KEY); \
    if (SEL) { \
        char b[0x60]; \
        fn_80290DDC(b, "[%s]", s); \
        { int w = fn_800CA3DC(b, -1, 1.0f) / 2; \
        fn_800CB3A8(1.0f, 0.0f, (int)x - w, y, (u8)col, 1, 0, b); } \
    } else { \
        int w = fn_800CA3DC(s, -1, 1.0f) / 2; \
        fn_800CB3A8(1.0f, 0.0f, (int)x - w, y, (u8)col, 1, 0, s); \
    } \
    x += W(KEY) + W(NEXT) + 0x18; \
}
static inline void Gr1(f32 x, f32 y, const char* s) { int w = fn_800CA3DC(s, -1, 1.0f) / 2; fn_800CB3A8(1.0f, 0.0f, (int)x - w, y, 0, 1, 0, s); }
#define GRAY(KEY, NEXT) { \
    Gr1(x, y, fn_800D0864(KEY)); \
    x += W(KEY) + W(NEXT) + 0x18; \
}
#define ITEM6(N, KEY, NEXT) { \
    int col; \
    int t = c->x6A == N; \
    if (t) { \
        if (*EntAt(c->x7D[c->x48]) == 6) { c->x58 = x - 128.0f; c->x5C = y - 90.0f; } \
    } \
    if (hl) { if (t) col = 0x36; else col = 0; } else col = t; \
    s = fn_800D0864(KEY); \
    if (t) { \
        char b[0x60]; \
        fn_80290DDC(b, "[%s]", s); \
        { int w = fn_800CA3DC(b, -1, 1.0f) / 2; \
        fn_800CB3A8(1.0f, 0.0f, (int)x - w, y, (u8)col, 1, 0, b); } \
    } else { \
        int w = fn_800CA3DC(s, -1, 1.0f) / 2; \
        fn_800CB3A8(1.0f, 0.0f, (int)x - w, y, (u8)col, 1, 0, s); \
    } \
    x += W(KEY) + W(NEXT) + 0x18; \
}
static inline int LC(int hl) { int lc = 0x35; if (hl) lc = 0x34; return lc; }
void fn_801875CC(Cfg* c, CfgEnt* e, int hl, f32 x0, f32 y) {
    int px;
    const char* s;
    int u;
    f32 x = 244.0f + x0;
    fn_801BCA94();
    fn_800CB3A8(1.0f, 0.0f, 18.0f + x0, y, LC(hl), 1, 0, fn_800D0864(e->name));
    switch (e->k) {
    case 0:
        x += W("MCFG_CHANGE");
        {
        int t;
        u32 f = *(u32*)(fn_8024BC94() + 0x20);
        t = f & 1;
        if (t == 0) t = (f >> 1) & 1;
        if (t == 0) t = (f >> 2) & 1;
        if (t == 0) t = (f >> 3) & 1;
        if (t == 0) {
        ITEM(c->x66 == 0, "MCFG_CHANGE", "MCFG_MAP")
        ITEM(c->x66 == 1, "MCFG_MAP", "MCFG_IDENT")
        ITEM(c->x66 == 3, "MCFG_IDENT", "dummy")
        } else {
        ITEM(c->x66 == 0, "MCFG_CHANGE", "MCFG_MAP")
        ITEM(c->x66 == 1, "MCFG_MAP", "MCFG_OFF")
        ITEM(c->x66 == 2, "MCFG_OFF", "MCFG_IDENT")
        ITEM(c->x66 == 3, "MCFG_IDENT", "dummy")
        }
        }
        break;
    case 1:
        {
        int t = (c->fl >> 9) & 1;
        x += W("MCFG_NORMAL_2");
        ITEMU(t, "MCFG_NORMAL_2", "MCFG_HORIZON")
        ITEM(t, "MCFG_HORIZON", "dummy")
        }
        break;
    case 2:
        x += W("MCFG_NORMAL");
        ITEM(c->x67 == 0, "MCFG_NORMAL", "MCFG_MANUAL")
        ITEM(c->x67 == 1, "MCFG_MANUAL", "MCFG_FAST")
        ITEM(c->x67 == 2, "MCFG_FAST", "dummy")
        break;
    case 3:
        x += W("MCFG_SLOW");
        ITEM(c->x68 == 0, "MCFG_SLOW", "MCFG_NORMAL")
        ITEM(c->x68 == 1, "MCFG_NORMAL", "MCFG_FAST")
        ITEM(c->x68 == 2, "MCFG_FAST", "MCFG_MAXSPEED")
        ITEM(c->x68 == 3, "MCFG_MAXSPEED", "dummy")
        break;
    case 4:
        Slider4(c, x, y, c->x69, 4, px);
        break;
    case 5:
        {
        int t = (c->fl >> 0) & 1;
        x += W("MCFG_ON");
        ITEM(t, "MCFG_ON", "MCFG_OFF")
        ITEMU(t, "MCFG_OFF", "dummy")
        }
        break;
    case 6:
        x += fn_800CA3DC("1", -1, 1.0f) / 2;
        ITEM6(1, "1", "2")
        ITEM6(2, "2", "3")
        ITEM6(3, "3", "4")
        ITEM6(4, "4", "5")
        ITEM6(5, "5", "6")
        ITEM6(6, "6", "MCFG_OFF")
        ITEM(c->x6A == 0, "MCFG_OFF", "dummy")
        break;
    case 7:
        x += W("MCFG_SIMPLE");
        ITEM(c->x6B == 0, "MCFG_SIMPLE", "MCFG_DETAIL")
        ITEM(c->x6B == 1, "MCFG_DETAIL", "MCFG_OFF")
        ITEM(c->x6B == 2, "MCFG_OFF", "dummy")
        break;
    case 8:
        x += W("MCFG_CAPTION");
        ITEM(c->x6C == 1, "MCFG_CAPTION", "MCFG_OFF")
        ITEM(c->x6C == 2, "MCFG_OFF", "dummy")
        break;
    case 9:
        {
        int t = (c->fl >> 11) & 1;
        x += W("MCFG_ON");
        ITEM(t, "MCFG_ON", "MCFG_OFF")
        ITEMU(t, "MCFG_OFF", "dummy")
        }
        break;
    case 10:
        {
        int t = (c->fl >> 13) & 1;
        x += W("MCFG_ON");
        ITEM(t, "MCFG_ON", "MCFG_OFF")
        ITEMU(t, "MCFG_OFF", "dummy")
        }
        break;
    case 11:
        {
        int t = (c->fl >> 14) & 1;
        x += W("MCFG_ON");
        ITEM(t, "MCFG_ON", "MCFG_OFF")
        ITEMU(t, "MCFG_OFF", "dummy")
        }
        break;
    case 12:
        {
        int t = (c->fl >> 1) & 1;
        x += W("MCFG_ON");
        ITEM(t, "MCFG_ON", "MCFG_OFF")
        ITEMU(t, "MCFG_OFF", "dummy")
        }
        break;
    case 13:
        x += W("MCFG_RM_VERTICAL");
        if (Pv()) {
        ITEM(c->x6D == 0, "MCFG_RM_VERTICAL", "MCFG_RM_HORIZON")
        ITEM(c->x6D == 1, "MCFG_RM_HORIZON", "dummy")
        } else {
            GRAY("MCFG_RM_VERTICAL", "MCFG_RM_HORIZON")
            GRAY("MCFG_RM_HORIZON", "dummy")
        }
        break;
    case 14:
        {
        int t = (c->fl >> 2) & 1;
        x += W("MCFG_NORMAL_E");
        ITEM(t, "MCFG_NORMAL_E", "MCFG_REVERSE")
        ITEMU(t, "MCFG_REVERSE", "dummy")
        }
        break;
    case 15:
        {
        int t = (c->fl >> 3) & 1;
        x += W("MCFG_NORMAL_E");
        ITEM(t, "MCFG_NORMAL_E", "MCFG_REVERSE")
        ITEMU(t, "MCFG_REVERSE", "dummy")
        }
        break;
    case 16:
        {
        int t = (c->fl >> 10) & 1;
        x += W("MCFG_NORMAL");
        ITEMU(t, "MCFG_NORMAL", "MCFG_WIDE")
        ITEM(t, "MCFG_WIDE", "dummy")
        }
        break;
    case 17:
        x += W("MCFG_ADJUST_A");
        {
        char b[0x60];
        hl = hl ? 0x36 : 1;
        fn_80290DDC(b, "[%s]", fn_800D0864("MCFG_ADJUST_A"));
        { int w = fn_800CA3DC(b, -1, 1.0f) / 2;
        fn_800CB3A8(1.0f, 0.0f, (int)x - w, y, hl, 1, 0, b); }
        x += W("MCFG_ADJUST_A") + W("dummy") + 0x18;
        }
        break;
    case 18:
        {
        int t = (c->fl >> 4) & 1;
        x += W("MCFG_ON");
        ITEM(t, "MCFG_ON", "MCFG_OFF")
        ITEMU(t, "MCFG_OFF", "dummy")
        }
        break;
    case 19:
        {
        int t = (c->fl >> 5) & 1;
        x += W("MCFG_ON");
        ITEM(t, "MCFG_ON", "MCFG_OFF")
        ITEMU(t, "MCFG_OFF", "dummy")
        }
        break;
    case 20:
        {
        int t = (c->fl >> 8) & 1;
        x += W("MCFG_ON");
        ITEM(t, "MCFG_ON", "MCFG_OFF")
        ITEMU(t, "MCFG_OFF", "dummy")
        }
        break;
    case 21:
        x += W("MCFG_MONO");
        ITEM(c->x70 == 0, "MCFG_MONO", "MCFG_STEREO")
        ITEM(c->x70 == 1, "MCFG_STEREO", "MCFG_SURROUND")
        ITEM(c->x70 == 2, "MCFG_SURROUND", "dummy")
        break;
    case 22:
        Slider(c, x, y, c->x71, 5, px);
        break;
    case 23:
        Slider(c, x, y, c->x72, 5, px);
        break;
    case 24:
        Slider(c, x, y, c->x73, 5, px);
        break;
    case 25:
        Slider(c, x, y, c->x74, 5, px);
        break;
    case 26:
        x += W("MCFG_ON");
        if (Pa()) {
        ITEM(c->x75 == 0, "MCFG_ON", "MCFG_AUTO")
        ITEM(c->x75 == 1, "MCFG_AUTO", "MCFG_OFF")
        ITEM(c->x75 == 2, "MCFG_OFF", "dummy")
        } else {
            GRAY("MCFG_ON", "MCFG_AUTO")
            GRAY("MCFG_AUTO", "MCFG_OFF")
            GRAY("MCFG_OFF", "dummy")
        }
        break;
    case 27:
        {
        int t = (c->fl >> 7) & 1;
        x += W("MCFG_ON");
        ITEM(t, "MCFG_ON", "MCFG_OFF")
        ITEMH(t, "MCFG_OFF", "dummy")
        }
        break;
    case 28:
        break;
    }
}
}
