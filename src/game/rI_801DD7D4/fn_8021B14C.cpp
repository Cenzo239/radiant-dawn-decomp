#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#pragma auto_inline off
extern "C" {
struct C4 { u8 r, g, b, a; };
struct XY { s16 x, y; };
struct Ms { u8 p[8]; s16 a8; u8 pa[0x5a]; C4 c; };
struct Ef { u8 p[0x30]; Ms* a30; };
void* fn_801059B0(void);
#if TARGET_PC
FE10_PROTO void fn_80105558(void*, p32arg);
#else
void fn_80105558(void*, int);
#endif
#if TARGET_PC
FE10_PROTO int fn_801E733C(ptr32<const void>);
#else
int fn_801E733C(void*);
#endif
void fn_80291CEC(int, char*, int);
int fn_800CA3DC(f32, const char*, int);
int fn_800CB0FC(f32, int);
const char* fn_800D0864(const char*);
#if TARGET_PC
FE10_PROTO Ef* fn_800E3C04(const char*, p32arg);
#else
Ef* fn_800E3C04(const char*, int);
#endif
void fn_801E2204(void*, XY*, XY*);
void fn_800E48AC(Ef*, f32, f32, f32);
void fn_800E4AD4(Ef*, f32);
void fn_8007E154(void);
void fn_8007E164(void);
#if TARGET_PC
FE10_PROTO void fn_8007E174(p32arg, u32);
#else
void fn_8007E174(int, u32);
#endif
void fn_8007E7DC(int);
void fn_8007E7E8(int);
void fn_8007E7B4(void);
void fn_800800D4(int);
void fn_80080308(void);
#if TARGET_PC
FE10_PROTO void fn_80080928(ptr32<const void>, ptr32<const void>);
#else
void fn_80080928(void*, void*);
#endif
#if TARGET_PC
FE10_PROTO void fn_801DAECC(ptr32<const void>);
FE10_PROTO void fn_801DAEDC(ptr32<const void>, int);
#else
void fn_801DAECC(void*);
void fn_801DAEDC(void*, int);
#endif
void fn_800CB278(int, int, int, const char*, ...);
f32 fn_801E33B4(void*);
f32 fn_801E3468(void*);
#if TARGET_PC
FE10_PROTO void fn_8021BB04(void* p, void* a, ptr32<const void>, ptr32<const void>, f32 t);
#else
void fn_8021BB04(void* p, void* a, void* b, void* c, f32 t);
#endif
extern char lbl_80371974[];
struct MP { void* vt; int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26; u8 p28[0x1c]; int* a44; u8 a48; u8 p49[3]; f32 a4c; };
static inline s16 mW(MP* o) { return o->ix1 - o->ix0; }
static inline void setC(Ms* m, C4 t) { m->c.r = t.r; m->c.g = t.g; m->c.b = t.b; m->c.a = t.a; }
void fn_8021B14C(MP* o, s8 d) {
    if (d < 0) d = 0;
    if (d != 0 && fn_801059B0() != NULL) {
/*P*/
        int n;
        int* p;
        s16 y;
        s16 x;
        s16 w;
        int i;
/*E*/
        p = o->a44;
        if (p != NULL) {
            o->a48 |= 1;
            x = o->tx;
            y = o->ty;
            w = mW(o) - x * 2;
            o->a4c = 2.0f;
            fn_801E733C(p);
            n = d;
            for (i = 0; i < n; i++) {
                fn_80105558(fn_801059B0(), *p);
            }
            {
                char buf[8];
                s16 sw;
                s16 tx;
                s16 ty;
                fn_80291CEC(fn_801E733C(o->a44), buf, 10);
                sw = fn_800CA3DC(1.0f, buf, -1);
                tx = x + w - 8 - (sw >> 1);
                ty = y + 0x46;
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
struct N3 { u8 p[0x30]; f32 sy, sz; u8 p38[4]; N3* parent; };
struct LY { void* o; f32 a4; };
class FX { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18();
    int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26, a28; u8 p2a[2]; f32 sx, sy, sz; u32 flags; N3* parent; u8 a40; u8 p41[3]; f32 a44; LY* a48; };
#define CHAIN(o, fld, fn, v0, v1, v2, v3) { \
    N3* p; N3* q; N3* r; N3* t; \
    v0 = (o)->fld; p = (o)->parent; \
    if (p) { v1 = p->fld; q = p->parent; if (q) { v2 = q->fld; r = q->parent; if (r) { v3 = r->fld; t = r->parent; if (t) { v3 *= fn(t); } v2 *= v3; } v1 *= v2; } v0 *= v1; } \
}
void fn_8021BFC0(FX* o) {
    f32 e, d, b, a;
    u8 buf[0x20];
    LY* l;
    o->v18();
    l = o->a48;
    l->o = o;
    l->a4 = o->a44;
    fn_8007E154();
    if (90.0f <= l->a4 && l->a4 < 270.0f) {
        fn_801DAECC(buf);
    } else {
        fn_801DAEDC(buf, (s8)o->a40);
    }
    fn_8007E174((int)buf, (u16)(o->flags | 0x411));
    CHAIN(o, sy, fn_801E33B4, a, b, d, e)
    fn_8007E7DC((u8)(255.99f * a));
    CHAIN(o, sz, fn_801E3468, e, d, b, a)
    fn_8007E7E8((u8)(128.99f * e));
    fn_8007E164();
    fn_800800D4(0xc);
    fn_80080928(fn_8021BB04, l);
    fn_80080308();
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
}
}
