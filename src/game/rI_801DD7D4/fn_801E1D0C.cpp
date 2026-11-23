/* symcheck: r21 review. REAL BUG FIXED: the draft set x88 = (x44 > x40 - x42); the original computes
   x88 = (x44 < x40 - x42) (the `and` of the branch-free compare takes the other operand, which `sched` accepted as a
   moved instruction). With the fix check_regs.py reports this file `exact` (0 words), symcheck clean. */
/* fn_801E1D0C: class `sched` (round 19): same instructions per basic block as the original, a few of them
   (independent loads, constants or stores) in another order; checked with tools/equiv/dd.py. */
#include "game/rI_801DD7D4/types.h"
struct C4 { u8 r, g, b, a; };
extern "C" {
void fn_8007E154(void);
void fn_8007E164(void);
#if TARGET_PC
FE10_PROTO void fn_8007E174(p32arg, int);
#else
void fn_8007E174(int, int);
#endif
void fn_801D7D38(int, int, s16, s16, s16, s16, C4*, u32);
extern s8 lbl_804CBE20;
extern C4 lbl_804CBE28[2];
}
class Sub { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(u32); };
class SB { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(void*); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual int v30();
  u8 p4[0xe]; s16 x12, x14, x16, x18; u8 p1a[0x1e]; u32 x38; u8 p3c[4]; s16 x40, x42, x44; u8 x46; u8 p47[9]; int x50; Sub s54; u8 p58[8]; u8 x60; u8 p61[0x1b]; Sub s7c; u8 p80[8]; u8 x88; };
static inline BOOL gt0(int a) { return a > 0; }
static inline BOOL lt(int a, int b) { return a < b; }
static inline BOOL gt(int a, int b) { return a > b; }
static inline void en(void* p, BOOL v) { *(u8*)p = v; }
static inline void en2(SB* o, int l, int d) { o->x60 = l > 0; o->x88 = d < l; }
static inline void en3(SB* o, int d, int l) { o->x60 = l > 0; o->x88 = d < l; }
extern "C" void fn_801E1D0C(SB* o, void* a) {
    if (!o->x46) return;
    if (o->x40 <= o->x42) return;
    o->v18(a);
    fn_8007E154();
    fn_8007E174(0, (u16)(o->x38 | 0x10));
    fn_8007E164();
    {
    s16 tot = o->x40;
    f32 k = (f32)(s16)o->v30() / (f32)tot;
    int len = k * o->x44;
    int pos = k * o->x42;
    if (!lbl_804CBE20) {
        lbl_804CBE28[0].r = 0x80; lbl_804CBE28[0].g = 0x80; lbl_804CBE28[0].b = 0xff; lbl_804CBE28[0].a = 0xff;
        lbl_804CBE28[1].r = 0x80; lbl_804CBE28[1].g = 0xff; lbl_804CBE28[1].b = 0x80; lbl_804CBE28[1].a = 0xff;
        lbl_804CBE20 = 1;
    }
    fn_801D7D38(0, 0, o->x16 - o->x12, o->x18 - o->x14, len, pos, &lbl_804CBE28[o->x50], o->x38 | 0x10);
    }
    o->x60 = o->x44 > 0;
    o->x88 = o->x44 < o->x40 - o->x42;
    o->s54.v2C(o->x38);
    o->s7c.v2C(o->x38);
}
