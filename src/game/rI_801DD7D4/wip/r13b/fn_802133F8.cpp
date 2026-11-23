#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E174(int, u32);
void fn_8007E720(f32);
int fn_800CB0FC(f32, int);
int fn_800CA3DC(f32, const char*, int);
void fn_801E6DA0(int, int, int, const char*, ...);
const char* fn_80118C44(void*);
void* fn_801196F0(u8);
void* fn_801246A4(void*);
u8* fn_800C6210(void*, int);
void fn_800C4DDC(int, int, int, void*);
void fn_800C429C(void*);
extern u8 lbl_803E7290[];
struct D44 { u8 p[0x44]; };
struct FontV : D44 { virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18(int, int, void*); virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48(); virtual int v4c(); virtual int v50(); };
#define FONT ((FontV*)lbl_803E7290)
struct It { u8 p[0xe1]; u8 ae1; };
struct U { u8 p[0xec]; It* aec; u8 pf0[0x28]; u8 a118; };
struct G { u8 p[0x48]; u32 a48; };
class MV { public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(void*); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); virtual int v38(void*);
    int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26, a28; u8 p2a[2]; f32 sx, sy, sz; u32 flags; void* parent; U* a40;
};
static inline u8 ic(U* u) { u8 c = u->a118; if ((s8)c == -1) return u->aec->ae1; return c; }
static inline s16 mWd(MV* o) { return o->x1 - o->x0; }
static inline BOOL lf(MV* o) { s16 cx = o->x0 + (mWd(o) >> 1); return cx < 0x130; }
static inline BOOL lf2(MV* o) { s16 cx = o->x0 + ((s16)(o->x1 - o->x0) >> 1); return cx < 0x130; }
static inline s16 cxf(MV* o) { return o->x0 + (mWd(o) >> 1); }
static inline BOOL lf4(MV* o) { int d = o->x1 - o->x0; s16 cx = o->x0 + ((s16)d >> 1); return cx < 0x130; }
static inline BOOL lf5(MV* o) { s16 d = o->x1 - o->x0; s16 cx = o->x0 + (d >> 1); return cx < 0x130; }
static inline BOOL lf6(MV* o, s16 x0, s16 x1) { int d = x1 - x0; s16 cx = x0 + ((s16)d >> 1); return cx < 0x130; }
static inline BOOL lf3(s16 cx) { return cx < 0x130; }
void fn_802133F8(MV* o, void* a) {
/*P*/
    int w;
    int t2;
    U* u;
    int nw;
    int t1;
    void* sp;
    G* g;
/*E*/
    o->v18(a);
    w = (s16)(o->ix1 - o->ix0) >> 1;
    u = o->a40;
    t1 = (0x1c - FONT->v50()) >> 1;
    t2 = (0x1c - fn_800CB0FC(1.0f, -1)) >> 1;
    nw = (s16)fn_800CA3DC(1.0f, fn_80118C44(u->aec), -1);
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E164();
    {
        u8 v = ic(u);
        nw = w - (nw >> 1);
        sp = fn_801196F0(v);
    }
    FONT->v18(nw - FONT->v4c(), t1 - 2, sp);
    fn_8007E154();
    fn_8007E174(0, (u16)(o->flags | 3));
    fn_8007E164();
    fn_801E6DA0((s16)(nw + 2), t2, 0x1f, fn_80118C44(u->aec));
    g = (G*)fn_800C6210(fn_801246A4(u), 0x200);
    g->a48 = (g->a48 & ~1) | (s16)lf(o);
    fn_800C4DDC(w, 0x99, 0xff, g);
    fn_800C429C(g);
    o->v38(a);
}
}
