#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#pragma auto_inline off
extern "C" {
struct C4 { u8 r, g, b, a;  };
extern VO0N* lbl_804CB5B8;
extern char lbl_80371974[];
extern const C4 lbl_80371930[12];
void fn_80253EE4(const char*, f32);
u8 fn_80110DA8(void*);
u8 fn_80110E00(void*);
u8 fn_80110E58(void*);
u8 fn_80110EB0(void*);
struct It { u8 p0[5]; u8 b0 : 2; u8 fl : 1; u8 b3 : 5; u8 p6[0x18]; s8 a1e, a1f, a20, a21; C4 c; };
struct MO { void* vt; u8 p4[0x6c]; It* a70; s16 a74; };
static inline void sfx(void) { fn_80253EE4(lbl_80371974 + 0x108, 0.0f); }
#define GET(p, f) ((p)->fl ? (p)->f : 0)
#define UP(p, f, mx, st) { int fl = (p)->fl; if ((fl ? (p)->f : 0) < (mx)) { s16 t = (fl ? (p)->f : 0) + (st); if (t > (mx)) t = (mx); (p)->f = t; sfx(); } }
#define DN(p, f, mx, st, chk) { if (GET(p, f) > -(mx) && chk) { s16 t = GET(p, f) - (st); if (t < -(mx)) t = -(mx); (p)->f = t; sfx(); } }
void fn_80219C68(MO* o) {
    ((VO0N*)o)->v24();
    if (!inputBlocked()) {
        It* p = o->a70;
        int k = lbl_804CB5B8->v3C();
        int q = lbl_804CB5B8->v48();
        switch ((s16)((VO0N*)o)->v34()) {
        case 0:
            if (k & 0x200002) UP(p, a1e, 5, 1)
            else if (k & 0x100001) DN(p, a1e, 5, 1, fn_80110DA8(p) > 1)
            break;
        case 1:
            if (k & 0x200002) UP(p, a1f, 0x19, 5)
            else if (k & 0x100001) DN(p, a1f, 0x19, 5, fn_80110E00(p) > 1)
            break;
        case 2:
            if (k & 0x200002) UP(p, a20, 0xf, 3)
            else if (k & 0x100001) DN(p, a20, 0xf, 3, fn_80110E58(p) != 0)
            break;
        case 3:
            if (k & 0x200002) UP(p, a21, 5, 1)
            else if (k & 0x100001) DN(p, a21, 5, 1, fn_80110EB0(p) > 1)
            break;
        case 4: {
            int c = o->a74;
            if (k & 0x100001) {
                if (c == 0) {
                    if (q == k) o->a74 = 0xb;
                } else {
                    o->a74 = c - 1;
                }
                { s16 i = ((VO0N*)o)->v64(); p->c.r = lbl_80371930[i].r; p->c.g = lbl_80371930[i].g; p->c.b = lbl_80371930[i].b; p->c.a = lbl_80371930[i].a; }
            } else if (k & 0x200002) {
                if (c == 0xb) {
                    if (q == k) o->a74 = 0;
                } else {
                    o->a74 = c + 1;
                }
                { s16 i = ((VO0N*)o)->v64(); p->c.r = lbl_80371930[i].r; p->c.g = lbl_80371930[i].g; p->c.b = lbl_80371930[i].b; p->c.a = lbl_80371930[i].a; }
            }
            if (c != o->a74) sfx();
            break;
        }
        }
    }
}

struct XY { s16 x, y; };
struct Ms { u8 p[8]; s16 a8; u8 pa[0x5a]; C4 c; };
struct Ef { u8 p[0x30]; Ms* a30; };
void fn_800CB0FC_(void);
int fn_800CB0FC(f32, int);
int fn_800CA3DC(f32, const char*, int);
void fn_80291CEC(int, char*, int);
#if TARGET_PC
FE10_PROTO Ef* fn_800E3C04(const char*, p32arg);
#else
Ef* fn_800E3C04(const char*, int);
#endif
void fn_801E2204(void*, XY*, XY*);
void fn_800E48AC(Ef*, f32, f32, f32);
void fn_800E4AD4(Ef*, f32);
struct MP { void* vt; int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26; u8 p28[0x2c]; s16 a54; u8 p56[0x1a]; It* a70; u8 a74; u8 p75[3]; f32 a78[4]; };
static inline s16 mW(MP* o) { return o->ix1 - o->ix0; }
static inline void setC(Ms* m, C4 t) { m->c.r = t.r; m->c.g = t.g; m->c.b = t.b; m->c.a = t.a; }
void fn_8021A47C(MP* o, u32 k, int d) {
    It* p = o->a70;
    if (p != NULL) {
        s16 x, y, w;
        if (k == 3) {
            if ((u8)fn_80110EB0(p) <= 1) return;
        }
        o->a74 |= 1 << k;
        o->a78[(u8)k] = 2.0f;
        x = o->tx;
        y = o->ty + 0x4e;
        w = mW(o) - x * 2;
        fn_800CB0FC(1.0f, -1);
        switch ((int)k) {
        case 0:
            d = (s8)d + GET(p, a1e);
            if (d > 0x7f) d = 0x7f;
            if (d < -0x80) d = -0x80;
            p->a1e = d;
            d = fn_80110DA8(p);
            break;
        case 1: {
            int v = (s8)d + GET(p, a1f);
            if (v > 0x7f) v = 0x7f;
            if (v < -0x80) v = -0x80;
            p->a1f = v;
            d = fn_80110E00(p);
            break;
        }
        case 2: {
            int v = (s8)d + GET(p, a20);
            if (v > 0x7f) v = 0x7f;
            if (v < -0x80) v = -0x80;
            p->a20 = v;
            d = fn_80110E58(p);
            break;
        }
        case 3: {
            int v = (s8)d + GET(p, a21);
            if (v > 0x7f) v = 0x7f;
            if (v < -0x80) v = -0x80;
            p->a21 = v;
            d = fn_80110EB0(p);
            break;
        }
        }
        {
            char buf[8];
            s16 sw;
            s16 tx;
            s16 ty;
            fn_80291CEC(d, buf, 10);
            sw = fn_800CA3DC(1.0f, buf, -1);
            tx = x + w - 8 - (sw >> 1);
            ty = y + k * o->a54 + 0xe;
            {
                Ef* e = fn_800E3C04(lbl_80371974 + 0x121, 4);
                XY in;
                XY out;
                in.x = tx;
                in.y = ty;
                fn_801E2204(o, &out, &in);
                fn_800E48AC(e, out.x, out.y, 0.0f);
                e->a30->a8 = o->a26 - 3.0f;
            }
            {
                Ef* e = fn_800E3C04(lbl_80371974 + 0x12c, 4);
                XY in;
                XY out;
                XY in2;
                XY out2;
                C4 c;
                in.x = tx;
                in.y = ty;
                fn_801E2204(o, &out, &in);
                in2.x = tx + 0x18;
                in2.y = ty - 7;
                fn_801E2204(o, &out2, &in2);
                fn_800E48AC(e, out2.x, out2.y, 0.0f);
                e->a30->a8 = o->a26 - 3.0f;
                fn_800E4AD4(e, 0.05f);
                {
                    Ms* m = e->a30;
                    c.a = 0xff;
                    c.r = m->c.r;
                    c.g = m->c.g;
                    c.b = m->c.b;
                    setC(m, c);
                }
            }
        }
    }
}
}
