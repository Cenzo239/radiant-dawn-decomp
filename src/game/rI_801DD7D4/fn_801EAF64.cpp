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
extern char lbl_8036EF28[];
int fn_8012386C(void*);
int fn_80122770(void*);
int fn_801224BC(void*);
int fn_80123998(void*);
int fn_80122880(void*);
int fn_8012250C(void*);
int fn_80123AC4(void*);
int fn_80122990(void*);
int fn_8012255C(void*);
int fn_80123BF0(void*);
int fn_80122AA0(void*);
int fn_801225AC(void*);
int fn_80123D1C(void*);
int fn_80122BB0(void*);
int fn_801225FC(void*);
int fn_80123DC4(void*);
int fn_80122C20(void*);
int fn_8012264C(void*);
int fn_80123EF0(void*);
int fn_80122D30(void*);
int fn_8012269C(void*);
}
struct UF { u8 p[0x105]; s8 s[7]; };
struct UO { u8 p[0xf0]; UF* xf0; };
class WO { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(void*); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual int v30(); virtual int v34(); virtual void v38(void*, int, int, int, int, const char*, int, int, int, int);
  u32 x4; u8 p8[0xa]; s16 x12, x14, x16, x18; u8 p1a[4]; s16 x1e, x20; u8 p22[0x38 - 0x22]; u32 x38; u8 p3c[4]; UO* x40; u8 p44[0xa]; s16 x4e, x50, x52, x54; };
extern "C" void fn_801EAF64(WO* o, void* a) {
/*P*/
    int c;
    const char* base;
    int hh;
    UO* u;
    int y;
    s16 x;
    s16 w;
    int a2;
    int b2;
    int b;
    int e;
/*E*/
    u = o->x40;
    o->v34();
    o->v18(a);
    {
    s16 hx = o->x18 - o->x14;
    s16 wx = o->x16 - o->x12;
    o->x4e = 0;
    o->x50 = 0;
    o->x52 = wx;
    o->x54 = hx;
    }
    fn_801E2204(o, &o->x4e, &o->x4e);
    fn_801E2204(o, &o->x52, &o->x52);
    fn_8007E154();
    fn_8007E74C(fn_801E2104, &o->x4e);
    fn_8007E164();
    ALPHA(-1.0f);
    x = o->x1e;
    y = o->x20;
    w = (s16)(o->x16 - o->x12) - x * 2;
    hh = o->v30();
    base = lbl_8036EF28;
    e = fn_8012386C(u);
    b = fn_80122770(u);
    c = fn_801224BC(u);
    o->v38(a, x, (s16)y, w, (s16)hh, base + 0x1e, (s16)c, (s16)b, (s16)e, u->xf0->s[0]);
    y += hh;
    e = fn_80123998(u);
    b = fn_80122880(u);
    c = fn_8012250C(u);
    o->v38(a, x, (s16)y, w, (s16)hh, base + 0x25, (s16)c, (s16)b, (s16)e, u->xf0->s[1]);
    y += hh;
    e = fn_80123AC4(u);
    b = fn_80122990(u);
    c = fn_8012255C(u);
    o->v38(a, x, (s16)y, w, (s16)hh, base + 0x2d, (s16)c, (s16)b, (s16)e, u->xf0->s[2]);
    y += hh;
    e = fn_80123BF0(u);
    b = fn_80122AA0(u);
    c = fn_801225AC(u);
    o->v38(a, x, (s16)y, w, (s16)hh, base + 0x35, (s16)c, (s16)b, (s16)e, u->xf0->s[3]);
    y += hh;
    e = fn_80123D1C(u);
    b = fn_80122BB0(u);
    c = fn_801225FC(u);
    o->v38(a, x, (s16)y, w, (s16)hh, base + 0x3e, (s16)c, (s16)b, (s16)e, u->xf0->s[4]);
    y += hh;
    e = fn_80123DC4(u);
    b = fn_80122C20(u);
    c = fn_8012264C(u);
    o->v38(a, x, (s16)y, w, (s16)hh, base + 0x46, (s16)c, (s16)b, (s16)e, u->xf0->s[5]);
    y += hh;
    a2 = fn_80123EF0(u);
    b2 = fn_80122D30(u);
    c = fn_8012269C(u);
    o->v38(a, x, (s16)y, w, (s16)hh, base + 0x4d, (s16)c, (s16)b2, (s16)a2, u->xf0->s[6]);
    ALPHA(1.0f);
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
}
