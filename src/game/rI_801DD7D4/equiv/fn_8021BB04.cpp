/* symcheck: r21 review, real but harmless. fn_8021BB04: (b) 4 blocks: the four colour bytes are read before
   instead of between the GX FIFO writes; the FIFO (0xCC008000) write sequence and values are identical and the
   colour can't live in the FIFO register. See docs/SCHED_REVIEW.md. */
/* fn_8021BB04: class `sched` (round 19): same instructions per basic block as the original, a few of them
   (independent loads, constants or stores) in another order; checked with tools/equiv/dd.py. */
/* fn_8021BB04: draw callback of the flipping card widget (registered by fn_8021BFC0): sets a 30 degree
   perspective over the widget's rectangle, rotates the quad about Y by the layer angle, scales by the
   inherited scale chain, darkens the colour, draws one textured quad (mirrored while the back faces
   the camera, 90..270 degrees) and restores the viewport. */
#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
void fn_80312E5C(f32* m, f32 fovy, f32 aspect, f32 n, f32 f);
void fn_80307D98(f32* m, int type);
void fn_803080BC(f32* vp);
void fn_80308090(f32 x, f32 y, f32 w, f32 h, f32 nz, f32 fz);
void fn_80312654(f32* m, int axis, f32 rad);
void fn_80312954(f32* a, f32* b, f32 x, f32 y, f32 z);
void fn_803128E0(f32* a, f32* b, f32 x, f32 y, f32 z);
void fn_80307E48(f32* m, int id);
void fn_80021784(int);
void fn_80021B68(int);
void fn_80304314(int, int, int);
int fn_801D09F0(void);
f64 fn_80295A18(f64);
u32* fn_801E2204(void*, s16*, s16*);
}
struct W { u8 p[0xa]; s16 x0, y0, x1, y1; u8 p12[0x1a]; f32 sx, sy, sz; u32 flags; W* parent; };
extern "C" f32 fn_801E3300(W*);
struct LY { W* o; f32 ang; };
union WG { f32 f; u8 b; };
volatile WG WGPIPE : 0xCC008000;
#define WF WGPIPE.f
#define WB WGPIPE.b
static inline void pos3(f32 x, f32 y, f32 z) { WF = x; WF = y; WF = z; }
struct C4 { u8 r, g, b, a; };
static inline void col4(const u8* c) { WB = c[0]; WB = c[1]; WB = c[2]; WB = c[3]; }
#define VTX(x, y, z, c, s, t) { pos3(x, y, z); col4(c); tex2(s, t); }
static inline void tex2(f32 s, f32 t) { WF = s; WF = t; }
#define CHAIN(o, fld, fn, v0, v1, v2, v3) { \
    W* p; W* q; W* r; W* t; \
    v0 = (o)->fld; p = (o)->parent; \
    if (p) { v1 = p->fld; q = p->parent; if (q) { v2 = q->fld; r = q->parent; if (r) { v3 = r->fld; t = r->parent; if (t) { v3 *= fn(t); } v2 *= v3; } v1 *= v2; } v0 *= v1; } \
}
static inline void xform(LY* l, f32 s, f32 hh, f32 fov) {
    f32 mt[12];
        fn_80312654(mt, 'Y', 0.017453292f * l->ang);
        fn_80312954(mt, mt, fn_801D09F0() ? 0.7638191f * s * s : s, s, s);
        fn_803128E0(mt, mt, 0.0f, 0.0f, -(hh / (f32)fn_80295A18(0.017453292f * (fov * 0.5f))));
        fn_80307E48(mt, 0);
}
#pragma opt_propagation off
extern "C" void fn_8021BB04(LY* l, u8* c, int a, int k, f32 z) {
    f32 fov;
    W* o = l->o;
    if (o != NULL) {
        f32 m[16];
        f32 vp[6];
        s16 pos[2];
        BOOL back;
        f32 x, y, w, h, hw, hh;
        f32 s, s1, s2, s3;
        if (o->parent != NULL) {
            fn_801E2204(o->parent, pos, &o->x0);
        } else {
            pos[0] = o->x0;
            pos[1] = o->y0;
        }
        back = FALSE;
        if (90.0f <= l->ang && l->ang < 270.0f) back = TRUE;
        x = pos[0];
        y = pos[1];
        w = (s16)(o->x1 - o->x0);
        h = (s16)(o->y1 - o->y0);
        fov = 30.0f;
        hw = w * 0.5f;
        hh = h * 0.5f;
        fn_80312E5C(m, fov, w / h, 1.0f, 1000.0f);
        fn_80307D98(m, 0);
        fn_803080BC(vp);
        fn_80308090(x, y, w, h, vp[4], vp[5]);
        CHAIN(o, sx, fn_801E3300, s, s1, s2, s3)
        xform(l, s, hh, fov);
        fn_80021784(0);
        fn_80021B68(0);
        c[0] = c[0] * k >> 7;
        c[1] = c[1] * k >> 7;
        c[2] = c[2] * k >> 7;
        c[3] = c[3] * a >> 8;
        fn_80304314(0x98, 0, 4);
        VTX(-hw, hh, z, c, back ? w : 0.0f, 0.0f)
        VTX(hw, hh, z, c, back ? 0.0f : w, 0.0f)
        VTX(-hw, -hh, z, c, back ? w : 0.0f, h)
        VTX(hw, -hh, z, c, back ? 0.0f : w, h)
        fn_80021B68(2);
        fn_80308090(vp[0], vp[1], vp[2], vp[3], vp[4], vp[5]);
    }
}
