#include "game/rI_801DD7D4/types.h"
extern "C" {
int fn_8028DB44(int);
int fn_800CB0FC(int, f32);
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E720(f32);
void fn_8007E7E8(int);
void fn_800712E8(int, int, int);
}
struct KO { u8 p[8]; void* x8; };
struct KB { u8 pad[0x2d]; u8 x2d; u8 x2e; u8 p2f[5]; int x34; KO* x38; };
class MW {
public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(KB*); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3C(); virtual void v40(int, int, int, int, int);
    u8 p4[0xe]; s16 x12, x14, x16, x18; u8 p1a[4]; s16 x1e, x20; u8 p22[0x2a]; u8 x4c, x4d; u8 p4e[2]; s16 x50, x52, x54, x56, x58;
};
static inline int gx(MW* o) { return o->x1e; }
static inline int gx2(MW* o) { int v = o->x1e; return v; }
static inline void ALPHA(f32 f) { fn_8007E154(); fn_8007E720(f); fn_8007E164(); }
static inline void BL(int v) { fn_8007E154(); fn_8007E7E8(v); fn_8007E164(); }
static inline BOOL kbTest(KB* a) { BOOL b = 0; if (a->x2d != 0 || a->x2e != 0) b = 1; return b; }
extern "C" void fn_801E9F38(MW* o, KB* a) {
/*P*/
    int d;
    BOOL sel;
    s16 yy;
    s16 hh1;
    s16 h;
    int x;
    s16 y;
    s16 hh;
    s16 px;
/*E*/
    o->v18(a);
    if (o->x50 >= 0) {
        h = o->x58;
        px = o->x54;
        { int m = o->x50 * h; y = m + o->x20; }
        x = gx(o);
        if ((px == -0x8000 && o->x56 == -0x8000) || (fn_8028DB44(px - x) <= 1 && fn_8028DB44(o->x56 - y) <= 1)) {
            o->x54 = x;
            o->x56 = y;
        } else {
            o->x54 = (px + x + 1) >> 1;
            o->x56 = (y + o->x56 + 1) >> 1;
        }
        if (o->x4c) {
            sel = 0;
            if (!kbTest(a)) {
                void* p = a->x34 ? a->x38->x8 : 0;
                if (p == o) sel = 1;
            }
            ALPHA(-2.0f);
            {
            hh1 = o->x58;
            fn_800712E8(o->x54, o->x56 + ((hh1 - fn_800CB0FC(-1, 1.0f)) >> 1), sel);
            }
            ALPHA(1.0f);
            o->v40(0, y, (s16)(o->x16 - o->x12), h, sel);
        }
    }
    if (o->x4d) {
        o->v18(a);
        ALPHA(-1.0f);
        {
        int m = o->x52 * h; yy = m + o->x20;
        hh = o->x58;
        d = (hh - fn_800CB0FC(-1, 1.0f)) >> 1;
        BL(0x40);
        fn_800712E8((s16)x, yy + d, 0);
        BL(0x80);
        }
    }
}
