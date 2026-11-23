#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#pragma auto_inline off
extern "C" {
struct C4 { u8 r, g, b, a; };
extern VO0N* lbl_804CB5B8;
extern char lbl_80371B80[];
extern u8 lbl_803CAB38[];
int fn_80120378(void*);
f32 fn_80120524(void*, int);
f32 fn_80062850(void*);
void fn_80253EE4(const char*, f32);
u8 fn_80126B0C(void*);
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E174(int, u32);
void fn_8007E720(f32);
int fn_800CB0FC(f32, int);
const char* fn_800D0864(const char*);
int fn_800CA3DC(f32, const char*, int);
void fn_800CB3A8(f32, f32, int, int, int, int, int, const char*, ...);
int fn_80290D04(char*, int, const char*, ...);
char* strcpy(char*, const char*);
void fn_800800D4(int);
void fn_80080308(void);
void fn_80080330(f32, f32);
void fn_80080508(C4);
void fn_80080A94(f32);
void fn_80080C24(const char*);
int fn_801D09F0(void);
int fn_8011FF28(void*, int, int);
struct Un { u8 p[0xf0]; struct { u8 p[0xfb]; u8 afb; }* af0; u8 pf4[0xa]; s8 afe; };
struct E28 { void* vt; u8 p4[8]; u8 ac, ad; u8 pe[6]; s16 a14; u8 p16[0x12]; };
class EV { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(u32); };
struct Ctx { u8 p[0x2d]; u8 a2d; u8 a2e; u8 p2f[5]; int a34; struct { u8 p[8]; void* a8; }* a38; };
class BO { public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(void*); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34();
    int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26, a28; u8 p2a[2]; f32 sx, sy, sz; u32 flags; u8 p3c[4]; Un* a40; f32 a44; int a48; E28 e[4]; u8 pec[0]; E28 f; };
static inline BOOL ctxBusy(Ctx* c) { BOOL b = FALSE; if (c->a2d != 0 || c->a2e != 0) b = TRUE; return b; }
static inline void* ctxTop(Ctx* c) { return c->a34 != 0 ? c->a38->a8 : NULL; }
static inline f32 cost(Un* u, int k) {
    f32 r;
    if (k == 0) {
        r = 0.0f;
    } else {
        f32 v = fn_80120524(u, k);
        if (v < 1.0f) v = 1.0f;
        r = v;
    }
    return r;
}
static inline BOOL canUp(BO* o) {
    int v = o->a48;
    BOOL b = fn_80120378(o->a40) - v > 0;
    if (b) b = fn_80062850(lbl_803CAB38) >= cost(o->a40, o->a48 + 1);
    return b;
}
static inline void sfx(void) { fn_80253EE4(lbl_80371B80 + 0x95, 0.0f); }
static inline int lvSum(BO* o, Un* u) { int n = o->a48; int k = fn_80126B0C(u); return k + n; }
static inline s16 gy(BO* o) { return o->ty; }
#define LV d + w0
static inline int ad(int a, int b) { return a + b; }
static inline int ad2(const int& a, const int& b) { return a + b; }
static inline int ad3(s8 a, int b) { return a + b; }
static inline int ad4(int b, s8 a) { return a + b; }
void fn_8021DAD4(BO* o, void* c) {
    char buf[0x10];
/*P*/
    const char* b;
    int off;
    Un* u;
    s16 x;
    int n;
    int n2;
    s8 l0;
    s16 y;
    s16 yy;
    s8 l1;
    s16 w;
    s16 h;
    int lv;
    const char* s;
    const char* m;
    const char* e;
    int r;
    const char* j;
    int t;
/*E*/
    u = o->a40;
    o->v34();
    o->v18(c);
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E164();
    fn_8007E154();
    fn_8007E174(0, (u16)(o->flags | 3));
    fn_8007E164();
    {
        w = fn_800CA3DC(2.0f, lbl_80371B80, -1);
        h = fn_800CB0FC(2.0f, -1);
        b = lbl_80371B80;
        fn_80290D04(buf, 0x10, b + 6, o->a48);
        fn_800800D4(5);
        fn_80080330((f32)(0xc1 - (w >> 1)), (f32)(0x41 - (h >> 1)));
    }
    {
        C4 col = {0xd2, 0xb4, 0x6c, 0xff};
        fn_80080508(col);
    }
    fn_80080A94(2.0f);
    fn_80080C24(buf);
    fn_80080308();
    x = o->tx;
    y = gy(o);
    off = (0x20 - fn_800CB0FC(1.0f, -1)) >> 1;
    s = fn_800D0864(b + 0xb);
    if (fn_801D09F0() == 0) {
        fn_800CB3A8(1.0f, 0.0f, x, (s16)(y + off), 0x1d, 1, 0, b + 0x1e, s, 4, (int)o->a44);
    } else {
        fn_800CB3A8(1.0f, 0.0f, x, (s16)(y + off), 0x1d, 1, 0, b + 0x2f, s, 4, (int)o->a44);
    }
    yy = y + 0x20;
    t = o->a48;
    if (t != 0) {
        if (t == fn_80120378(u) && fn_8011FF28(u, 0, 0) == 0) {
            strcpy(buf, lbl_80371B80 + 0x40);
        } else {
            n2 = o->a48;
            { int k = fn_80126B0C(u); fn_80290D04(buf, 0x10, lbl_80371B80 + 0x43, (k + n2) % 100); }
        }
    } else if (fn_80126B0C(u) != 0xff) {
        fn_80290D04(buf, 0x10, lbl_80371B80 + 0x43, fn_80126B0C(u));
    } else {
        strcpy(buf, lbl_80371B80 + 0x40);
    }
    j = fn_801D09F0() != 0 ? lbl_80371B80 + 0x47 : lbl_80371B80 + 0x50;
    if (fn_80126B0C(u) != 0xff && lvSum(o, u) >= 100) {
        n = o->a48;
        l0 = u->afe;
        /*Q*/
        if (lv <= u->af0->afb) {
            m = lbl_80371B80;
            e = fn_800D0864(m + 0x74);
            fn_800CB3A8(1.0f, 0.0f, x, (s16)(yy + off), 0x1d, 1, 0, m + 0x55, fn_800D0864(m + 0x6d), lv, j, e, buf);
        } else {
            m = lbl_80371B80;
            e = fn_800D0864(m + 0x74);
            fn_800CB3A8(1.0f, 0.0f, x, (s16)(yy + off), 0x1d, 1, 0, m + 0x7b, fn_800D0864(m + 0x6d), 0x14, 1, j, e, buf);
        }
    } else {
        m = lbl_80371B80;
        l1 = u->afe;
        e = fn_800D0864(m + 0x74);
        fn_800CB3A8(1.0f, 0.0f, x, (s16)(yy + off), 0x1d, 1, 0, m + 0x55, fn_800D0864(m + 0x6d), l1, j, e, buf);
    }
    {
        r = 0;
        if (fn_80126B0C(u) != 0xff && lvSum(o, u) >= 100) r = 1;
        o->f.ac = r;
    }
    ((EV*)&o->f)->v2C(o->flags);
}
}
