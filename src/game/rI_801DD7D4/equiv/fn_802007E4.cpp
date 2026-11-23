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
void fn_8007E174(int, int);
void fn_8007E720(f32);
void fn_8007E74C(void*, void*);
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
}
class WU { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); u32 x4; u8 p8[0x16]; s16 x1e, x20; u8 p22[0x16]; u32 x38; u8 p3c[0x4]; void* x40; };
static inline int wd(const char* s) { return fn_800CA3DC(s, 1.0f, -1); }
extern "C" void fn_802007E4(WU* o) {
/*P*/
    int y2;
    int x;
    int y;
    int xq;
    int xr;
    s16 w1;
    const char* b0;
    const char* d;
    const char* b2;
    const char* s2;
    s16 w2;
    const char* s0;
/*E*/
    o->v18();
    {
    int a = 0x1c - fn_800CB0FC(-1, 1.0f);
    a = (a + 0xc) >> 1;
    x = o->x1e + 0x16;
    y = a + o->x20;
    }
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E174(0, (u16)(o->x38 | 3));
    fn_8007E164();
    s0 = fn_800D0864(lbl_8036F328);
    w1 = fn_800CA3DC(s0, 1.0f, -1);
    b0 = lbl_8036F328;
    fn_800CB278((s16)x, (s16)y, 0x1e, fn_800D0864(b0 + 0x12));
    xr = (s16)x + 0xb8;
    fn_800CB278((s16)(xr - w1), (s16)y, 0x1e, s0);
    if (o->x40) {
        fn_800800D4(5);
        fn_80080508(*fn_800CD204(0x1f));
        fn_80080B00(1, fn_800CD204(0x2a), 1.0f);
        {
        int v = fn_801E7490(o->x40);
        xq = (s16)x + 0xb0;
        fn_80176F7C(xq - w1, (s16)y, 0, 0, v);
        }
        fn_80080308();
    } else {
        int dw;
        d = b0 + 0x25;
        dw = fn_800CA3DC(d, 1.0f, -1);
        xq = (s16)x + 0xb0;
        fn_801E6DA0((s16)((xq - w1) - (s16)dw), (s16)y, 0x1f, d);
    }
    y2 = y + 0x1c;
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
}
