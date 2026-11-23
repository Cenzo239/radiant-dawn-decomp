typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long u64;
typedef float f32;
typedef int BOOL;
#define TRUE 1
#define FALSE 0
#define NULL 0
extern "C" {
extern u32 lbl_804CB700;
extern char lbl_803E7290[];
extern char lbl_803C8E80[];
struct C4 { u8 r, g, b, a; };
int fn_800CB0FC(int, f32);
void fn_8007E154(void);
void fn_8007E164(void);
#if TARGET_PC
FE10_PROTO void fn_8007E174(p32arg, int);
#else
void fn_8007E174(int, int);
#endif
void fn_8007E720(f32);
#if TARGET_PC
FE10_PROTO void fn_8007E74C(ptr32<const void>, ptr32<const void>);
#else
void fn_8007E74C(void*, void*);
#endif
void fn_8007E7B4(void);
void fn_800800D4(int);
void fn_80080308(void);
void fn_80080330(f32, f32);
void fn_80080ABC(int, f32);
void fn_80080C24(const char*);
void fn_80176EA8(int, int, int, const char*);
void fn_801D8ADC(int, int, int, int);
const char* fn_800D0864(const char*);
void fn_800CB3A8(int x, int y, int a, int b, int c, f32 s, f32 t, const char* f, ...);
void fn_800CB278(int, int, int, const char*, ...);
C4* fn_800CD204(int i);
void fn_80080508(C4);
void fn_80176F7C(int, int, int, int, int);
u32* fn_801E2204(void*, void*, void*);
void fn_801E2104(void* p, void* arg);
}
struct DB { u8 pad[0x44]; };
class DV : public DB {
public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14();
    virtual int v18(int, int, int);
    virtual int v1C(); virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34();
    virtual int v38(); virtual int v3C(); virtual int v40(); virtual int v44(); virtual int v48();
    virtual int v4C(); virtual int v50();
};
#define FONT ((DV*)lbl_803E7290)
class WV { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual int v30(); virtual int v34(); };
static inline void ALPHA(f32 f) { fn_8007E154(); fn_8007E720(f); fn_8007E164(); }

extern "C" {
extern char lbl_8036F03C[];
void* fn_801E9B28(void*);
u8* fn_8024BC94(void);
const char* fn_80110F08(void*);
const char* fn_801110C4(void*, int);
int fn_80290D04(char*, int, const char*, ...);
void fn_800D0B38(int, const char*);
void* fn_801E00D0(const char*);
void* fn_800D5448(void*, void*, int);
struct HW { u8 p[0x64]; const char* x64; };
HW* fn_801E5640(void*, int, int);
struct It { u8 p[0x16]; u16 x16; };
struct IU { It* x0; };
struct OF { u8 p[0x4c]; void* x4c; };
void fn_801F8394(OF* o) {
    char buf[0x80];
    /*P*/
    const char* base;
    const char* hs;
    const char* n;
    u32 ic;
    u32 ic2;
    IU* u;
/*E*/
    u = (IU*)fn_801E9B28(o->x4c);
    switch (fn_8024BC94()[0x1bc8]) {
    case 1:
        if (u->x0) ic = u->x0->x16; else ic = 0;
        n = fn_80110F08(u);
        fn_80290D04(buf, 0x80, lbl_8036F03C + 0x17f, fn_801110C4(u, 0), n, (u8)ic + 0x80);
        break;
    default:
        { const char* z; if (u->x0) ic2 = u->x0->x16; else ic2 = 0; }
        fn_80290D04(buf, 0x80, lbl_8036F03C + 0x18a, (u8)ic2 + 0x80, fn_80110F08(u));
        break;
    }
    fn_800D0B38(1, buf);
    base = lbl_8036F03C;
    fn_800D5448(fn_801E00D0(base + 0x193), o, 0);
    hs = base + 0x1a8;
    {
    HW* h = fn_801E5640(o, -0x1000, 0);
    if (h) h->x64 = hs;
    }
}

extern char lbl_8036EEE0[];
int fn_801196F0(int);
const char* fn_80118C44(void*);
struct C7 { u8 p[0xec]; void* xec; u8 pf0[0x118 - 0xf0]; u8 x118; };


}
static inline u8 clsOf(C7* t) { u8 v = t->x118; if ((s8)v == -1) return ((u8*)t->xec)[0xe1]; return v; }
class WK { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C(); virtual void v40(); virtual int v44();
    u8 p4[0x1a]; s16 x1e; u8 p20[0x18]; u32 x38; u8 p3c[0x22]; s16 x5e; };
extern "C" void fn_801E7C10(WK* o, int x, int y, void* a, C7* t, int e) {
    /*P*/
    int v;
    int dy2;
    int dy;
    const char* nm;
    s16 h;
    s16 h2;
    s16 h3;
    s16 h4;
/*E*/
    v = e != 0;
    nm = fn_80118C44(t->xec);
    h = o->x5e;
    dy = (h - FONT->v50()) >> 1;
    h2 = o->x5e;
    dy2 = (h2 - fn_800CB0FC(-1, 1.0f)) >> 1;
    FONT->v18(x, y + dy, fn_801196F0(clsOf(t)));
    fn_8007E154();
    fn_8007E174(0, (u16)(o->x38 | 3));
    fn_8007E164();
    fn_800CB278((s16)(x + FONT->v4C() + 2), (s16)(y + dy2), v, lbl_8036EEE0 + 5, nm);
    ALPHA(1.8f);
    h3 = o->x1e;
    h4 = o->x5e;
    fn_801D8ADC(x, (s16)(y + h4 - 8), (s16)(o->v44() - h3 * 2), 0x10);
    ALPHA(-1.8f);
}

extern "C" {
struct PD { u8 p[0x30]; s16 x30, x32; };
PD* fn_80085EF8(int);
void fn_8007E7E8(int);
void fn_800712E8(int, int, int);
void fn_80072ACC(int, int, int, int, int, int, int);
}
class AV { public: u32 x0; virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4C(); virtual void v50(); virtual void v54();
  virtual int v58(); virtual int v5C(); virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6C(); virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7C(); virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8C(); virtual void v90(); virtual void v94(); virtual int v98(); };
struct BV { u8 p[0x2d]; u8 x2d, x2e; u8 p2f[9]; s16 x38, x3a; u8 p3c[4]; u8 x40[0x66]; s8 xa6; };
static inline int cx(s16 w, int x, s16 k) { return (w >> 1) + (x - k); }
static inline PD* pdOf(BV* b) { return fn_80085EF8(b->x40[b->xa6]); }
static inline BOOL busy(BV* b) { BOOL r = 0; if (b->x2d != 0 || b->x2e != 0) r = 1; return r; }
static inline BOOL idle(BV* b) { BOOL r = 0; if (b->x2d == 0 && b->x2e == 0) r = 1; return r; }
extern "C" void fn_801DE160(AV* a, BV* b) {
    /*P*/
    int h;
    int w;
    s16 x;
    s16 y;
    BV* bb;
    AV* aa;
    BOOL id;
    /*E*/
    a->v94();
    x = pdOf(b)->x30;
    y = pdOf(b)->x32;
    w = a->v58();
    h = a->v5C();
    if (b->x3a < 0) {
        b->x38 = x;
        b->x3a = y;
    } else {
        int yy = y + b->x3a + 1;
        int xx = x + b->x38 + 1;
        b->x38 = xx / 2;
        b->x3a = yy / 2;
    }
    fn_8007E154();
    fn_8007E720(-1.0f);
    { BOOL bz = busy(b); int c = 0x40; if (!bz) c = 0x80; fn_8007E7E8(c); }
    fn_8007E164();
    fn_800712E8(b->x38, b->x3a, idle(b));
    ALPHA(2.0f);
    id = idle(b);
    {
    fn_80072ACC(((s16)w >> 1) + (x - (s16)a->v98()), y + ((s16)h >> 1), (s16)w, 0x17, 0x19, 0x4c, id);
    }
    fn_8007E154();
    fn_8007E7E8(0x80);
    fn_8007E164();
}

