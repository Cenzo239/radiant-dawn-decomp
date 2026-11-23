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
int fn_800CA3DC(f32, const char*, int);
void fn_801DBD98(int, int, int, int);
void fn_801DB3F4(int, int, int, int, int, int, u32);
}
struct WE { u8 p[0x38]; u32 x38; u8 p3c[8]; u8 x44; };
#define TX3(x, y, c, b, s, ...) fn_800CB3A8(x, y, c, b, 0, 1.0f, 0.0f, s, ##__VA_ARGS__)
extern "C" void fn_801EACE8(WE* o, int a, int x, int y, int w, int h, const char* name, int v, s16 p0, s16 p1, s16 p2) {
    /*P*/
    int dy;
    int yy;
    s16 z1;
    s16 z2;
    s16 z3;
    int ty;
    int xr;
    int xr2;
    const char* base;
    s16 sh;
/*E*/
    dy = (h - fn_800CB0FC(-1, 1.0f)) >> 1;
    fn_8007E154();
    fn_8007E174(0, (u16)(o->x38 | 3));
    fn_8007E164();
    yy = y + dy;
    fn_800CB3A8(x, (s16)yy, 0x1d, 1, 0, 1.0f, 0.0f, fn_800D0864(name));
    if (v < p0) {
        f32 s = 0.7f;
        sh = fn_800CB0FC(-1, s);
        {
        int d;
        s16 sw;
        int col;
        sw = fn_800CA3DC(s, lbl_8036EF28 + 0x18, -1);
        d = (h - sh) >> 1;
        col = 1;
        if (v >= p2) col = 0x27;
        xr = x + w;
        base = lbl_8036EF28;
        ty = y + d;
        fn_800CB3A8((s16)(xr - 0x3e - sw), (s16)ty, col, 1, 0, s, 0.0f, base + 5, v);
        fn_800CB3A8((s16)(xr - 0x3a), (s16)ty, 1, 0, 0, s, 0.0f, base + 0x1b);
        }
    }
    fn_800800D4(5);
    {
        int ci = 1;
        if (p0 >= p2) ci = 0x27;
        fn_80080508(*fn_800CD204(ci));
    }
    fn_80080ABC(1, 2.0f);
    xr2 = x + w;
    fn_80176F7C(xr2 - 0x10, yy, 0, 0, p0);
    fn_80080308();
    ALPHA(-1.0f);
    {
        s16 d = p1 - p0;
        if (d != 0 && o->x44 != 1) {
            fn_801DBD98((s16)(xr2 - 0xe), (s16)yy, d, 0x10);
        }
    }
    ALPHA(1.5f);
    fn_801DB3F4(x, (s16)(y + h - 0xc - dy), w, p0, p2, 0x32, o->x38);
    ALPHA(-0.5f);
}
