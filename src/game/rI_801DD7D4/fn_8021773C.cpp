#include "game/rI_801DD7D4/fn_wf.h"
#pragma auto_inline off
extern "C" {
#if TARGET_PC
FE10_PROTO void * fn_8010B228(p32arg);
#else
int fn_8010B228(int);
#endif
#if TARGET_PC
FE10_PROTO void fn_80110BB4(void*, p32arg);
#else
void fn_80110BB4(void*, int);
#endif
struct WK { WF w; void* a40; };
struct Slot { int a0, a4; int a8; };
struct LV {
    void* vt0; int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1;
    s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26, a28; u8 p2a[2]; u8 p2c[0x28]; s16 a54; u8 p56[0x16]; Slot* a6c; u8 a70[0x28]; int a98; void* a9c;
};
class LVV { public: virtual int v08(); virtual int v0C(void*, int); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
 virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual s16 v34(); virtual int v38(); virtual int v3C();
 virtual int v40(); virtual int v44(); virtual int v48(); virtual int v4C(); virtual int v50(void*); };
static inline void rm(LVV* o, void* c) { if (c != NULL) o->v0C(c, 0); }
static inline WK* newK(LV* p, s16 x0, s16 y0, s16 x1, s16 y1, s16 ix1, s16 iy1) {
    WK* o = (WK*)fn_80079150(0x44);
    if (o != NULL) {
        s16 a = p->a26;
        wfInit(&o->w, x0, y0, x1, y1, ix1, iy1, a - 5, 0x10);
        o->w.vt = lbl_8038FA04;
        o->a40 = 0;
        ((Lst*)o)->v2C();
    }
    return o;
}
static inline s16 W(LV* o) { return o->x1 - o->x0; }
static inline s16 H(LV* o) { return o->y1 - o->y0; }
static inline void setI(LV* o, int a, int b, int c, int d) { o->ix0 = a; o->iy0 = b; o->ix1 = c; o->iy1 = d; }
void fn_8021773C(LV* o) {
    Slot* s;
    setI(o, 4, 3, W(o) - 4, H(o) - 3);
    o->tx = 0x12;
    o->ty = 9;
    o->a54 = 0x1c;
    s = (Slot*)((u8*)o->a6c + o->a98 * 0x78);
    {
        int n = ((LVV*)o)->v34();
        int j;
        int k = 0;
        for (j = 0; j < 10; j++, s++) {
            if (s->a8 != 0) {
                if ((s16)k++ == n) break;
            }
        }
    }
    fn_80110BB4(o->a70, fn_8010B228(s->a8));
    ((LVV*)o)->v50(o->a70);
    rm((LVV*)o, o->a9c);
    {
        WK* k = newK(o, 0x5d, -0x1c, 0x161, 4, 0x104, 0x20);
        o->a9c = k;
        k->a40 = o->a70;
        fn_801E2F40(o, o->a9c);
    }
}

struct R28 { s16 x, y, z; u8 p[0x22]; };
struct LX { LV v; u8 pa0[0x118]; void* a1b8; WF* a1bc; };
void fn_8021876C(LX* o) {
    setI(&o->v, 4, 4, W(&o->v) - 4, H(&o->v) - 4);
    o->v.tx = 8;
    o->v.ty = 0x14;
    o->v.a54 = 0x1c;
    rm((LVV*)o, o->a1b8);
    {
        WK* k = newK(&o->v, 0, -0x1c, 0x104, 4, 0x104, 0x20);
        o->a1b8 = k;
        k->a40 = 0;
        fn_801E2F40(o, o->a1b8);
    }
    rm((LVV*)o, o->a1bc);
    {
        WF* f = (WF*)fn_80079150(0x40);
        if (f != NULL) {
            s16 a = o->v.a26;
            wfInit(f, 0, 0, 0xfe, 0x88, 0xfe, 0x88, a - 4, 0x10);
            f->vt = lbl_8038CAC0;
        }
        o->a1bc = f;
        f->c[0] = 0; f->c[1] = 0; f->c[2] = 0; f->c[3] = 0;
        fn_801E2F40(o, o->a1bc);
    }
    {
        int h = o->v.a54;
        int ty = o->v.ty;
        int m = h >> 1;
        R28* r = (R28*)((u8*)o + 0x86);
        int y = ty + h;
        r[0].x = 0x9e; r[0].y = ty + m; r[0].z = 0;
        r[1].x = 0x9e; r[1].y = y + m; r[1].z = 0;
        y += h;
        r[2].x = 0x9e; r[2].y = y + m; r[2].z = 0;
        y += h;
        r[3].x = 0x9e; r[3].y = y + m; r[3].z = 0;
    }
}
}
