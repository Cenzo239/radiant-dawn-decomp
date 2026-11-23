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
void fn_8007E7E8(int);
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
extern u8 lbl_8041EB20[0x100];
struct IC;
struct PD { u8 p[0x30]; s16 x30, x32; IC* x34; };
PD* fn_80085EF8(int);
int fn_801A2224(void*);
void fn_801A1DCC(void*, void*, f32, f32);
void fn_801A1F64(void*, void*, f32, f32);
void fn_80253EE4(const char*, f32);
}
struct BV;
struct IC { virtual void v08(); virtual void v0C(); virtual void* v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44(BV*, PD*); virtual void v48(BV*, PD*); virtual void* v4C(PD*); };
struct BV { u8 p[0x30]; s16 x30, x32; u8 p34[0xc]; u8 x40[0x64]; s8 xa4; u8 pa5; s8 xa6, xa7; };
class IN { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual u32 v3C(); virtual void v40(); virtual void v44(); virtual u32 v48(); };
extern "C" IN* lbl_804CB5B8;
static inline BOOL blk(void) {
    u32 f1 = *(volatile u32*)&lbl_804CB700;
    u32 f2 = *(volatile u32*)&lbl_804CB700;
    BOOL b = FALSE;
    if ((f1 & 0x10) && !(f2 & 0x20)) b = TRUE;
    return b;
}
class OV { public: u32 x0; virtual int v8(); virtual int vC(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C(); virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); virtual int v38(); virtual int v3C(); virtual int v40(); virtual int v44(); virtual int v48(); virtual int v4C(); virtual int v50(); virtual int v54(); virtual int v58(); virtual int v5C(); virtual int v60(); virtual int v64(); virtual int v68(); virtual int v6C(); virtual int v70(); virtual int v74(); virtual int v78(); virtual int v7C(); virtual int v80(); virtual int v84(); virtual const char* v88(); virtual int v8C(); virtual int v90(); virtual int v94(); virtual int v98(); virtual int v9C(); virtual int vA0(BV*); virtual int vA4(); };
static inline int flg(u32 k, u32 m) { return k & m; }
extern "C" void fn_801DE85C(OV* o, BV* b) {
    /*P*/
    u32 pr;
    int rows;
    int n;
    int cols;
    s16 col;
    s16 row;
    u32 tr;
/*E*/
    f32 x;
    f32 y;
    n = b->xa4;
    rows = o->vA0(b);
    cols = o->vA4();
    row = b->xa6 / (s16)cols;
    col = b->xa6 % (s16)cols;
    if (blk()) return;
    pr = lbl_804CB5B8->v3C();
    tr = lbl_804CB5B8->v48();
    b->xa7 = b->xa6;
    if ((s16)cols > 1) {
        int lim = (s16)(n - row * cols);
        if (lim > (s16)cols) lim = cols;
        if (flg(pr, 0x100001)) {
            if (col > 0) b->xa6 -= 1;
            else if (pr == tr) b->xa6 += lim - 1;
        } else if (flg(pr, 0x200002)) {
            int m = (s16)lim - 1;
            if (col < m) b->xa6 += 1;
            else if (pr == tr) b->xa6 -= m;
        }
    }
    if (flg(pr, 0x800008)) {
        if (row == 0) {
            if (pr == tr) {
                int k = (rows - 1) * cols;
                int mx = n - 1;
                b->xa6 += k;
                if (b->xa6 > mx) b->xa6 = mx;
            }
        } else {
            b->xa6 -= cols;
        }
    } else if (flg(pr, 0x400004)) {
        int m = (s16)rows - 1;
        if (row == m) {
            if (pr == tr) b->xa6 -= m * cols;
        } else {
            int mx = n - 1;
            b->xa6 += cols;
            if (b->xa6 > mx) b->xa6 = mx;
        }
    }
    if (b->xa6 != b->xa7) {
        PD* p = fn_80085EF8(b->x40[b->xa7]);
        p->x34->v48(b, p);
        p = fn_80085EF8(b->x40[b->xa6]);
        p->x34->v44(b, p);
        if (fn_801A2224(lbl_8041EB20)) {
            { PD* q = fn_80085EF8(b->x40[b->xa6]); x = b->x30 + q->x30; }
            { PD* q = fn_80085EF8(b->x40[b->xa6]); y = b->x32 + q->x32; }
            {
            void* s = fn_80085EF8(b->x40[b->xa6])->x34->v10();
            if (s) {
                fn_801A1DCC(lbl_8041EB20, s, x, y);
            } else {
                PD* q = fn_80085EF8(b->x40[b->xa6]);
                fn_801A1F64(lbl_8041EB20, q->x34->v4C(q), x, y);
            }
            }
        }
        if (o->v88()) fn_80253EE4(o->v88(), 0.0f);
    }
}
