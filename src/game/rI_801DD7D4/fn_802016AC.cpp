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
extern char lbl_8036F328[];
extern u8 lbl_803CAB38[];
int fn_800CA3DC(const char*, f32, int);
void fn_801E6DA0(int, int, int, const char*, ...);
int fn_801E7490(void*);
int fn_800626E0(void*);
void fn_80080B00(int, void*, f32);
const char* fn_80118C44(void*);
void* fn_801246A4(void*);
void* fn_800C6210(void*, int);
void fn_800C48A8(int, int, u8, void*, int);
void fn_800C429C(void*);
struct Nd;
f32 fn_801E33B4(Nd*);
}
struct Nd { u8 p[0x30]; f32 x30, x34; u8 p38[4]; Nd* x3c; };
class WU { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); u32 x4; u8 p8[0x16]; s16 x1e, x20; u8 p22[0x16]; u32 x38; u8 p3c[0x4]; struct UX* x40; int x44; };
struct UX { u8 p[0xec]; void* xec; };
extern "C" void fn_802016AC(WU* o) {
/*P*/
    int xr;
    const char* b0;
    int y;
    int y2;
    int x;
    const char* s0;
    const char* b1;
    const char* b2;
    int xq;
    const char* s2;
    const char* d;
    s16 w2;
    int y1;
    s16 w1;
    const char* s1;
/*E*/
    o->v18();
    {
    int a = 0x1c - fn_800CB0FC(-1, 1.0f);
    a = (a + 0xa) >> 1;
    x = o->x1e + 0x68;
    y = a + o->x20;
    }
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E174(0, (u16)(o->x38 | 3));
    fn_8007E164();
    b0 = lbl_8036F328;
    fn_800CB278((s16)x, (s16)y, 0x1e, fn_800D0864(b0 + 0x8b));
    if (o->x44 == 0) {
        s0 = b0 + 0x25;
    } else if (o->x40) {
        s0 = fn_80118C44(o->x40->xec);
    } else {
        s0 = fn_800D0864(b0 + 0x9d);
    }
    {
    int w0 = fn_800CA3DC(s0, 1.0f, -1);
    xr = (s16)x + 0xbc;
    fn_801E6DA0((s16)(xr - (s16)w0), (s16)y, 0x1f, s0);
    }
    y1 = y + 0x1c;
    s1 = fn_800D0864(lbl_8036F328);
    w1 = fn_800CA3DC(s1, 1.0f, -1);
    b1 = lbl_8036F328;
    fn_800CB278((s16)x, (s16)y1, 0x1e, fn_800D0864(b1 + 0x12));
    fn_800CB278((s16)(xr - w1), (s16)y1, 0x1e, s1);
    if (o->x44) {
        fn_800800D4(5);
        fn_80080508(*fn_800CD204(0x1f));
        fn_80080B00(1, fn_800CD204(0x2a), 1.0f);
        {
        int v = fn_801E7490((void*)o->x44);
        xq = (s16)x + 0xb4;
        fn_80176F7C(xq - w1, (s16)y1, 0, 0, v);
        }
        fn_80080308();
    } else {
        int dw;
        d = b1 + 0x25;
        dw = fn_800CA3DC(d, 1.0f, -1);
        xq = (s16)x + 0xb4;
        fn_801E6DA0((s16)((xq - w1) - (s16)dw), (s16)y1, 0x1f, d);
    }
    y2 = y1 + 0x1c;
    b2 = lbl_8036F328;
    s2 = fn_800D0864(b2 + 0x2c);
    w2 = fn_800CA3DC(s2, 1.0f, -1);
    fn_800CB278((s16)x, (s16)y2, 0x1e, fn_800D0864(b2 + 0x3f));
    fn_800CB278((s16)(xr - w2), (s16)y2, 0x1e, s2);
    fn_800800D4(5);
    fn_80080508(*fn_800CD204(0x1f));
    fn_80080B00(1, fn_800CD204(0x2a), 1.0f);
    fn_80176F7C(xq - w2, (s16)y2, 0, 0, fn_800626E0(lbl_803CAB38));
    fn_80080308();
    if (o->x44 && o->x40) {
        void* m = fn_800C6210(fn_801246A4(o->x40), 0);
        f32 v1;
        f32 v2;
        f32 v3;
        f32 v4;
        Nd* w1 = (Nd*)o;
        v1 = w1->x30;
        if (w1->x3c) {
            Nd* w2 = w1->x3c;
            v2 = w2->x30;
            if (w2->x3c) {
                Nd* w3 = w2->x3c;
                v3 = w3->x30;
                if (w3->x3c) {
                    Nd* w4 = w3->x3c;
                    v4 = w4->x30;
                    if (w4->x3c) v4 *= fn_801E33B4(w4->x3c);
                    v3 *= v4;
                }
                v2 *= v3;
            }
            v1 *= v2;
        }
        fn_800C48A8(0x16, 0x11, (u8)(int)(255.99f * v1), m, 0);
        fn_800C429C(m);
    }
}
