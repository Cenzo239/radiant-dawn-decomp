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
extern char lbl_8036EEE0[];
void* fn_8012E390(void*);
const char* fn_80118C44(void*);
int fn_801196F0(int);
int fn_8012E9B4(void*, void*);
u8 fn_8012E8BC(void*, int);
int fn_800CA3DC(const char*, f32, int);
}
struct C7 { u8 p[0xec]; void* xec; u8 pf0[0x118 - 0xf0]; u8 x118; };
static inline u8 clsOf(C7* t) { u8 v = t->x118; if ((s8)v == -1) return ((u8*)t->xec)[0xe1]; return v; }
class WK { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C(); virtual void v40(); virtual int v44();
    u8 p4[0x1a]; s16 x1e; u8 p20[0x18]; u32 x38; u8 p3c[0x22]; s16 x5e; u8 p60[0x24]; void* x84; };
#pragma pool_strings off
static inline const char* grade(u8 i) {
    const char* t[] = {"|", "b", "a", "`"};
    return t[i];
}
static inline void grade2(u8 i, const char*& s) {
    const char* t[] = {"|", "b", "a", "`"};
    s = t[i];
}
extern "C" void fn_801E8A84(WK* o, int x, int y, void* a, C7* t, int e) {
    /*P*/
    int dy2;
    int yy;
    int v;
    const char* nm;
    s16 w;
    int kk;
    int c;
    int y2;
    int dy;
    int c0;
    const char* s;
    s16 pad;
    s16 h1;
    s16 h2;
    void* q;
/*E*/
    v = e != 0;
    if (v) {
        q = t->xec;
        if (fn_8012E390(o->x84) == q) v = 4;
    }
    nm = fn_80118C44(t->xec);
    pad = o->x1e;
    w = o->v44() - pad * 2;
    h1 = o->x5e;
    dy = (h1 - FONT->v50()) >> 1;
    h2 = o->x5e;
    dy2 = (h2 - fn_800CB0FC(-1, 1.0f)) >> 1;
    FONT->v18(x, y + dy, fn_801196F0(clsOf(t)));
    fn_8007E154();
    fn_8007E174(0, (u16)(o->x38 | 3));
    fn_8007E164();
    yy = y + dy2;
    fn_800CB278((s16)(x + FONT->v4C() + 2), (s16)yy, (u8)v, lbl_8036EEE0 + 5, nm);
    c = e != 0;
    kk = fn_8012E9B4(o->x84, t);
    if (c) {
        if (fn_8012E8BC(o->x84, (s8)kk) >= 3) c = 0x27;
    }
    grade2(fn_8012E8BC(o->x84, (s8)kk), s);
    fn_800CB278((s16)(x + w - fn_800CA3DC(s, 1.0f, -1) - 8), (s16)yy, (u8)c, lbl_8036EEE0 + 5, s);
    ALPHA(1.8f);
    fn_801D8ADC(x, (s16)(y + o->x5e - 8), w, 0x10);
    ALPHA(-1.8f);
}
