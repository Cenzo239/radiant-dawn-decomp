typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef float f32;
extern "C" {
extern u32 lbl_804CB700;
extern char lbl_803E7290[];
extern char lbl_803C8E80[];
void* fn_8012E3A4(void*);
int fn_800CB0FC(int, f32);
void fn_8007E154(void);
void fn_8007E164(void);
#if TARGET_PC
FE10_PROTO void fn_8007E174(p32arg, int);
#else
void fn_8007E174(int, int);
#endif
void fn_8007E720(f32);
void fn_80027088(void*, void*, int);
int fn_8012E9B4(void*, void*);
int fn_801196F0(int);
const char* fn_80118C44(void*);
void fn_800CB278(int, int, int, const char*, ...);
u8 fn_8012E8BC(void*, int);
void fn_800800D4(int);
void fn_80080308(void);
void fn_80176EA8(int, int, int, const char*);
void fn_801D92D0(int, int, int, int);
void fn_801D8ADC(int, int, int, int);
void fn_8002FC64(void*, void*, int);
const char* fn_800D0864(const char*);
void fn_800CB3A8(int x, int y, int a, int b, int c, f32 s, f32 t, const char* f, ...);
struct GXC { u8 r, g, b, a; };
u8* fn_800CD204(int i);
void fn_80080508(GXC*);
void fn_80176F7C(int, int, int, int, int);
int fn_8012EA2C(void*, int);
}
#pragma pool_strings on
struct DB { u8 pad[0x44]; };
class DV : public DB {
public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14();
    virtual int v18(int, int, int);
    virtual int v1C(); virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34();
    virtual int v38(); virtual int v3C(); virtual int v40(); virtual int v44(); virtual int v48();
    virtual int v4C(); virtual int v50();
};
class MV { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(int); };
struct TU { u8 p[0xe1]; u8 xe1; };
struct TT { u8 p[0xec]; TU* xec; u8 p2[0x118 - 0xf0]; u8 x118; };
struct WB { u8 pad[0x12]; s16 x12, x14, x16; u8 p18[6]; s16 x1e, x20; u8 p22[0x38 - 0x22]; u32 x38; u8 p3c[4]; void* x40; MV m44; u8 p48[8]; u8 x50; };
class WO : public WB { };
struct WV { virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual int v30(); };
struct BONUS { int x; s8 v[6]; };
#define ALPHA(f) { fn_8007E154(); fn_8007E720(f); fn_8007E164(); }
#define ZS(o) { fn_8007E154(); fn_8007E174(0, (u16)(o->x38 | 3)); fn_8007E164(); }
#define SEP(yy) { ALPHA(1.8f); fn_801D8ADC(x, (s16)(yy + V->v30() - 8), w, 0x10); ALPHA(-1.8f); }
#define HDR(yy, s) { yy2 = (s16)yy + r30; \
   fn_800CB3A8(x, (s16)yy2, 1, 1, 0, 1.0f, 0.0f, fn_800D0864("MD_SPT")); }
#define VAL(i, yy) { GXC c; fn_800800D4(5); c = *(GXC*)fn_800CD204(b.v[i] > 0 ? 4 : 1); fn_80080508(&c); s8 vv = b.v[i]; fn_80176F7C((x + w), yy, 0, vv > 0, vv); fn_80080308(); }
#define ROWV(yv, s, i, first) { yv = (s16)r25 + r30; \
   fn_800CB3A8(x, (s16)yv, 1, 1, 0, 1.0f, 0.0f, fn_800D0864("MD_SPT")); \
   if (first) xm = x + (w >> 1); \
   fn_800CB3A8((s16)xm, (s16)yv, 0x1d, 1, 0, 1.0f, 0.0f, fn_800D0864(s)); \
   VAL(i, yv); SEP(r25); }
#define ROWE2(s, first) { y2e = (s16)r25e + r30; \
   fn_800CB3A8(x, (s16)y2e, 1, 1, 0, 1.0f, 0.0f, fn_800D0864("MD_SPT")); \
   if (first) xme = x + (w >> 1); \
   fn_800CB3A8((s16)xme, (s16)y2e, 0x1d, 1, 0, 1.0f, 0.0f, fn_800D0864(s)); \
   fn_800800D4(5); fn_80176EA8(xwe, y2e, 0, "\x81\x7c\x81\x7c"); fn_80080308(); SEP(r25e); }
static inline void bon(BONUS* b) {
    u32 fl = (*(volatile u32*)&lbl_804CB700) & 0x10000;
    b->v[5] = 0; b->v[4] = 0; b->v[3] = 0; b->v[2] = 0; b->v[1] = 0; b->v[0] = 0;
    lbl_804CB700 = (*(volatile u32*)&lbl_804CB700) & ~fl;
    fn_8002FC64(lbl_803C8E80, b, 1);
    lbl_804CB700 |= fl;
}

static inline int cen(s16 a, int b) { return (a - b) >> 1; }
static inline int cen2(s16 a, const int& b) { int c = a - b; return c >> 1; }
static inline int cen4(WV* V) { s16 a = V->v30(); return (a - ((DV*)lbl_803E7290)->v50()) >> 1; }
static inline int cen5(WV* V) { s16 a = V->v30(); return (a - fn_800CB0FC(-1, 1.0f)) >> 1; }
static inline int cen3(WV* V, int k) { s16 a = V->v30(); int b = k ? fn_800CB0FC(-1, 1.0f) : ((DV*)lbl_803E7290)->v50(); return (a - b) >> 1; }
static inline int cs(int a) { return (s16)a; }
static inline u8 clsOf(TT* t) { u8 v = t->x118; if ((s8)v == -1) return t->xec->xe1; return v; }
#pragma inline_max_size(4000)
extern "C" void fn_802125CC(WO* o) {
    /*P*/
    int y4;
    int r31;
    int r30;
    void* u;
    s16 x;
    s16 y;
    int xme;
    int yy;
    int y2;
    int y2e;
    TT* t;
    const char* nm;
    int xm;
    int xwe;
    int r25;
    int r25e;
    s16 w;
    s8 k;
/*E*/
    WV* V = (WV*)o;
    BONUS b;
    V->v18();
    u = o->x40;
    t = (TT*)fn_8012E3A4(u);
    x = o->x1e;
    y = o->x20;
    r31 = cen4(V);
    r30 = cen5(V);
    w = (s16)(o->x16 - o->x12) - o->x1e * 2;
    ALPHA(-1.1f);
    if (t != 0) {
        fn_80027088(lbl_803C8E80, u, -1);
        k = fn_8012E9B4(u, t);
        ((DV*)lbl_803E7290)->v18(x, y + r31, fn_801196F0(clsOf(t)));
        ZS(o);
        y2 = y + r30;
        {
            nm = fn_80118C44(t->xec);
            fn_800CB278((s16)(x + ((DV*)lbl_803E7290)->v4C() + 2), (s16)y2, 0x1d, "#E%s", nm);
        }
        {
            u8 lv = fn_8012E8BC(u, k);
            switch (lv) {
            case 0:
                fn_800800D4(5);
                fn_80176EA8((x + w), y2, 0, "\x81\x7c\x81\x7c");
                fn_80080308();
                break;
            default:
                fn_801D92D0((s16)(x + w), (s16)(y - 8), lv, 0x10);
                break;
            }
        }
        ALPHA(1.8f);
        fn_801D8ADC(x, (s16)(y + V->v30() - 8), w, 0x10);
        ALPHA(-1.8f);
        r25 = y + V->v30();
        ZS(o);
        {
            bon(&b);
        }
        ROWV(yy, "MP_ATK", 0, 1);
        r25 += V->v30();
        ROWV(y2, "MP_GUARD", 1, 0);
        r25 += V->v30();
        ROWV(y2, "MP_HIT", 2, 0);
        r25 += V->v30();
        ROWV(y4, "MP_AVO", 3, 0);
        o->x50 = fn_8012EA2C(u, k);
        o->m44.v2C(o->x38);
    } else {
        ZS(o);
        y2e = y + r30;
        fn_800CB278(x, (s16)y2e, 1, "\x81\x7c\x81\x7c\x81\x7c");
        fn_800800D4(5);
        xwe = x + w;
        fn_80176EA8(xwe, y2e, 0, "\x81\x7c\x81\x7c");
        fn_80080308();
        ALPHA(1.8f);
        fn_801D8ADC(x, (s16)(y + V->v30() - 8), w, 0x10);
        ALPHA(-1.8f);
        r25e = y + V->v30();
        ZS(o);
        ROWE2("MP_ATK", 1);
        r25e += V->v30();
        ROWE2("MP_GUARD", 0);
        r25e += V->v30();
        ROWE2("MP_HIT", 0);
        r25e += V->v30();
        ROWE2("MP_AVO", 0);
        o->x50 = 0;
        o->m44.v2C(o->x38);
    }
}
