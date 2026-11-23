/* Config menu input handler. StringPool is scaffolding: it sets the pool offsets and is not game code. */
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

typedef struct CfgEnt { u8 k; u8 a; u8 b; u8 pad[5]; const char* name; } CfgEnt;
typedef struct Cfg { u8 pad[0x36]; s16 x36; u8 pad38[4]; f32 x3c; s16 x40, x42, x44, x46; u8 x48; u8 x49; s16 x4a, x4c, x4e, x50, x52, x54; u8 pad56[0x64-0x56];
  u16 x64; u8 x66, x67, x68; s8 x69; s8 x6a; u8 x6b, x6c, x6d, x6e, x6f, x70; s8 x71, x72, x73, x74, x75; u8 pad76[6]; u8 x7c; u8 x7D[1]; } Cfg;
class Pad { public: virtual void v08(); virtual void v0C(); virtual int v10(); virtual int v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30();
 virtual u32 v34(); virtual void v38(); virtual u32 v3C(); virtual void v40(); virtual void v44(); virtual u32 v48();
 virtual void v4C(); virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5C(); virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6C(); virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7C(); virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8C(); virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9C(); virtual void vA0();
 virtual int vA4(); virtual void vA8(int); };
extern Pad* lbl_804CB5B8;
extern u8 lbl_803881E8[];
extern u8* fn_8024BC94(void);
extern void fn_80253EE4(const char*, f32);
extern void fn_80083DC4(void*, int);
extern double fn_80295CF0(double);
extern u8 fn_8018F3AC(int v, const u8* tbl, int n);
extern void fn_8024DDF8(int);
extern void fn_80250AB4(f32, f32);
extern void fn_80250C0C(f32, f32);
extern void fn_80250B60(f32, f32);
extern void fn_80250CB8(f32, f32);
extern void fn_8007A83C(int);
extern void fn_8007A84C(int);
extern u8 fn_80109A10(void);
extern u8 fn_801099A0(void);
extern int fn_801D09F0(void);
static inline CfgEnt* EntAt(int k) { CfgEnt* p; if (k < 0) return 0; p = (CfgEnt*)(lbl_803881E8 + (k << 4)); if (k >= 0x1D) p = 0; return p; }
static inline int Flg(void) {
    u32 f;
    int t;
    f = *(u32*)(fn_8024BC94() + 0x20);
    t = f & 1;
    if (t == 0) t = (f >> 1) & 1;
    if (t == 0) t = (f >> 2) & 1;
    if (t == 0) t = (f >> 3) & 1;
    return t;
}
static inline int Vis(CfgEnt* e) {
    if (e == 0) return 0;
    if (Flg()) return e->b;
    return e->a;
}
#define MOVE2 fn_80253EE4("SFX_SYS_CURSOR_WINDOW_MOVE2", 0.0f)
#define MOVED { c->x49 = 4; c->x4e = c->x4a; c->x50 = c->x4c; c->x52 = 0x10; c->x54 = (c->x48 - c->x42) * 0x20 + 0x5c; }
#define L 0x100001
#define R 0x200002
/* flag toggles; f1=left-repeat op, f2=right-repeat op */
#define TG(op1, op2, bit) { int o = c->x64; if (trig & L) c->x64 = o ^ bit; else if (rep & L) c->x64 = op1; \
    if (trig & R) c->x64 ^= bit; else if (rep & R) c->x64 = op2; if (c->x64 != o) MOVE2; break; }
#define TGON(bit) TG(o | bit, c->x64 & ~bit, bit)
#define TGOFF(bit) TG(o & ~bit, c->x64 | bit, bit)
#define CY(f, n) { int o = c->f; \
    if (trig & L) { int t = o - 1; c->f = t < 0 ? n : t; } else if (rep & L) { int t = o - 1; c->f = t < 0 ? 0 : t; } \
    if (trig & R) { int t = c->f + 1; c->f = t > n ? 0 : t; } else if (rep & R) { int t = c->f + 1; c->f = t > n ? n : t; } \
    if (c->f != o) MOVE2; }
#define VOL(f, fn0) { int o = c->f; if (press & L) c->f -= step; if (press & R) c->f += step; if (c->f < 0) c->f = 0; if (c->f > 100) c->f = 100; \
    { v = (s8)*(u8*)&c->f; if (v != o) { if (press & 0x1000) { c->x71 = *(s8*)&c->f; c->x72 = v; c->x73 = v; c->x74 = v; \
      fn_80250AB4(0.01f * v, 0.0f); fn_80250C0C(0.01f * v, 0.0f); fn_80250B60(0.01f * v, 0.0f); fn_80250CB8(0.01f * v, 0.0f); } \
      else { fn0(0.01f * v, 0.0f); } } } break; }
#define STEP(f) { if (press & L) c->f -= step; if (press & R) c->f += step; if (c->f < 0) c->f = 0; if (c->f > 100) c->f = 100; break; }


static inline BOOL IsW(void) { if (lbl_804CB5B8->v14() == 0 || lbl_804CB5B8->v14() == 1) return 1; return 0; }
static inline BOOL IsW2(void) { return lbl_804CB5B8->v14() == 0 || lbl_804CB5B8->v14() == 1; }
static inline BOOL IsW3(void) { int r; if (lbl_804CB5B8->v14() == 0 || lbl_804CB5B8->v14() == 1) r = 1; else r = 0; return r; }
static inline void Set71(Cfg* c, u8 x) { c->x71 = x; }
static inline void Set71b(Cfg* c, const u8& x) { c->x71 = x; }
void fn_8018F4F4(Cfg* c) {
    /*P*/
    u32 press;
    u32 rep;
    u32 trig;
    int old;
    int o70;
    s8 o1a;
    int step;
    int v;
/*E*/
    trig = lbl_804CB5B8->v48();
    rep = lbl_804CB5B8->v3C();
    press = lbl_804CB5B8->v34();
    old = c->x48;
    step = 1;
    if (press & 0x400) step = 4;
    if (c->x44 > 0 || c->x49 != 0) return;
    if (trig & 0x800) {
        fn_80253EE4("SFX_SYS_CANCEL1", 0.0f);
        fn_80083DC4(c, 3);
        return;
    }
    if ((trig & 0x800008) || (rep & 0x800008)) {
        if (old == 0 && (trig & 0x800008)) {
            int n = c->x7c;
            c->x48 = n - 1;
            c->x40 = (int)c->x3c;
            c->x42 = n - 9;
            { s16 v = (int)fn_80295CF0(n * 4); c->x46 = v; c->x44 = v; }
        } else {
            int j = old;
            do {
                if (j <= 0) break;
                j--;
            } while (!Vis(EntAt(c->x7D[j])));
            if (j >= 0) c->x48 = j;
            {
                if ((f32)c->x48 - c->x3c <= 1.0f && c->x3c > 0.0f) {
                    c->x46 = 4;
                    c->x44 = 4;
                    c->x40 = (int)c->x3c;
                    c->x42 = c->x40 - 1.0f;
                }
            }
        }
        MOVED;
    }
    if ((trig & 0x400004) || (rep & 0x400004)) {
        v = c->x48;
        if (v == c->x7c - 1 && (trig & 0x400004)) {
            c->x48 = 0;
            c->x40 = (int)c->x3c;
            c->x42 = 0;
            { s16 v = (int)fn_80295CF0(c->x7c * 4); c->x46 = v; c->x44 = v; }
        } else {
            do {
                if (v >= c->x7c - 1) break;
                v++;
            } while (!Vis(EntAt(c->x7D[v])));
            if (v <= c->x7c - 1) c->x48 = v;
            {
                f32 t = c->x3c;
                if ((f32)c->x48 - t >= 7.0f && t < c->x7c - 9) {
                    c->x46 = 4;
                    c->x44 = 4;
                    c->x40 = (int)t;
                    c->x42 = 1.0f + c->x40;
                }
            }
        }
        MOVED;
    }
    if (old != c->x48) fn_80253EE4("SFX_SYS_CURSOR_WINDOW_MOVE1", 0.0f);
    if (EntAt(c->x48) == 0) return;
    switch (EntAt(c->x7D[c->x48])->k) {
    case 0:
        if ((trig & 0x400) && c->x66 == 3) {
            fn_80083DC4(c, 1);
            fn_80253EE4("SFX_SYS_SELECT1", 0.0f);
        } else if (!Flg()) {
            u8 t[3] = {0, 1, 3};
            c->x66 = fn_8018F3AC(c->x66, t, 3);
        } else {
            u8 t[4] = {0, 1, 2, 3};
            c->x66 = fn_8018F3AC(c->x66, t, 4);
        }
        break;
    case 1: TGOFF(0x200)
    case 2: CY(x67, 2) break;
    case 3: CY(x68, 3) break;
    case 4: STEP(x69)
    case 5: TGON(1)
    case 6: {
        int o = c->x6a;
        if (trig & L) {
            if (o == 0) c->x6a = 6; else if (o == 1) c->x6a = 0; else c->x6a = c->x6a - 1;
        } else if (rep & L) {
            if (o == 0) c->x6a = 6; else if (o != 1) c->x6a = c->x6a - 1;
        }
        if (trig & R) {
            s8 v = c->x6a;
            if (v == 6) c->x6a = 0; else if (v == 0) c->x6a = 1; else c->x6a = c->x6a + 1;
        } else if (rep & R) {
            s8 v = c->x6a;
            if (v == 6) c->x6a = 0; else if (v != 0) c->x6a = c->x6a + 1;
        }
        if (c->x6a < 0) c->x6a = 6;
        if (c->x6a > 6) c->x6a = 0;
        if (c->x6a != o) MOVE2;
        break;
    }
    case 7: CY(x6b, 2) break;
    case 8: {
        int o = c->x6c;
        if (trig & L) { int t = o - 1; c->x6c = t < 1 ? 2 : t; } else if (rep & L) { int t = o - 1; c->x6c = t < 1 ? 1 : t; }
        if (trig & R) { int t = c->x6c + 1; c->x6c = t > 2 ? 1 : t; } else if (rep & R) { int t = c->x6c + 1; c->x6c = t > 2 ? 2 : t; }
        if (c->x6c != o) MOVE2;
        break;
    }
    case 9: TGON(0x800)
    case 10: TGON(0x2000)
    case 11: TGON(0x4000)
    case 12: TGON(2)
    case 13: {
        BOOL b; if (lbl_804CB5B8->v14() == 0 || lbl_804CB5B8->v14() == 1) b = 1; else b = 0;
        if (b) CY(x6d, 1)
        break;
    }
    case 14: TGON(4)
    case 15: TGON(8)
    case 16: TGOFF(0x400)
    case 17:
        if (trig & 0x400) { fn_80083DC4(c, 2); fn_80253EE4("SFX_SYS_SELECT1", 0.0f); }
        break;
    case 18: TGON(0x10)
    case 19: TGON(0x20)
    case 20: TGON(0x100)
    case 21: {
        o70 = c->x70;
        {
        if (trig & L) { int t = o70 - 1; c->x70 = t < 0 ? 2 : t; } else if (rep & L) { int t = o70 - 1; c->x70 = t < 0 ? 0 : t; }
        if (trig & R) { int t = c->x70 + 1; c->x70 = t > 2 ? 0 : t; } else if (rep & R) { int t = c->x70 + 1; c->x70 = t > 2 ? 2 : t; }
        if (c->x70 != o70) MOVE2; }
        if (c->x70 != o70) {
            switch (c->x70) { case 0: fn_8024DDF8(3); break; case 1: fn_8024DDF8(0); break; case 2: fn_8024DDF8(2); break; }
        }
        break;
    }
    case 22: VOL(x71, fn_80250AB4)
    case 23: VOL(x72, fn_80250C0C)
    case 24: VOL(x73, fn_80250B60)
    case 25: VOL(x74, fn_80250CB8)
    case 26: {
        int nz; nz = lbl_804CB5B8->vA4() != 0; if (nz) {
            o1a = (s8)(u8)c->x75;
            if (trig & L) { int t = o1a - 1; c->x75 = t < 0 ? 2 : t; } else if (rep & L) { int t = o1a - 1; c->x75 = t < 0 ? 0 : t; }
            if (trig & R) { int t = c->x75 + 1; c->x75 = t > 2 ? 0 : t; } else if (rep & R) { int t = c->x75 + 1; c->x75 = t > 2 ? 2 : t; }
            if (c->x75 != o1a) MOVE2;
            if (c->x75 != o1a) {
                switch (c->x75) { case 2: fn_8007A84C(6); break; case 0: fn_8007A84C(6); fn_8007A83C(2); break; case 1: fn_8007A83C(6); break; }
                int kk = *(u8*)&c->x75; if (kk != 2) lbl_804CB5B8->vA8(8);
            }
        }
        break; }
    case 28:
        if (trig & 0x400) {
            int z = 0;
            c->x66 = z; c->x67 = z; c->x68 = 1; c->x69 = 0x14; c->x6a = 1; c->x6b = z; c->x6c = 2; c->x6d = 1;
            c->x75 = fn_80109A10();
            c->x70 = fn_801099A0();
            c->x6e = z; c->x6f = z;
            if (fn_801D09F0()) c->x64 = 0x3d3f; else c->x64 = 0x393f;
            c->x71 = 100; c->x72 = 100; c->x73 = 100; c->x74 = 100;
            fn_80250AB4(1.0f, 0.0f); fn_80250C0C(1.0f, 0.0f); fn_80250B60(1.0f, 0.0f); fn_80250CB8(1.0f, 0.0f);
            switch (c->x70) { case 0: fn_8024DDF8(3); break; case 1: fn_8024DDF8(0); break; case 2: fn_8024DDF8(2); break; }
            switch (c->x75) { case 2: fn_8007A84C(6); break; case 0: fn_8007A84C(6); fn_8007A83C(2); break; case 1: fn_8007A83C(6); break; }
            fn_80253EE4("SFX_SYS_SELECT1", 0.0f);
        }
        break;
    case 27: TGON(0x80)
    }
}
}
