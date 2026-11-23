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
void fn_80253EE4(const char*, f32);
}
struct BV;
struct IC { virtual void v08(); virtual void v0C(); virtual void* v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44(BV*, PD*); virtual void v48(BV*, PD*); };
struct BV { u8 p[0x30]; s16 x30, x32; u8 p34[0xc]; u8 x40[0x64]; s8 xa4; u8 pa5; s8 xa6, xa7; };
class IN { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44(); virtual u32 v48(); };
extern "C" IN* lbl_804CB5B8;
class OV { public: u32 x0; virtual void v8(); virtual void vC(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4C(); virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5C(); virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6C(); virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7C(); virtual void v80(); virtual void v84(); virtual const char* v88(); };
static inline BOOL blk(void) {
    u32 f1 = *(volatile u32*)&lbl_804CB700;
    u32 f2 = *(volatile u32*)&lbl_804CB700;
    BOOL b = FALSE;
    if ((f1 & 0x10) && !(f2 & 0x20)) b = TRUE;
    return b;
}
static inline int flg(u32 k, u32 m) { return k & m; }
extern "C" void fn_801DFA2C(OV* o, BV* b) {
    /*P*/
    f32 x;
    f32 y;
/*E*/
    if (blk()) return;
    {
    u32 k = lbl_804CB5B8->v48();
    b->xa7 = b->xa6;
    if (b->xa6 != 0 && (k & 0x100001)) b->xa6--;
    if (b->xa6 != b->xa4 - 1 && (k & 0x200002)) b->xa6++;
    }
    if (b->xa6 != b->xa7 && fn_801A2224(lbl_8041EB20)) {
        { PD* p = fn_80085EF8(b->x40[b->xa6]); x = b->x30 + p->x30; }
        { PD* p = fn_80085EF8(b->x40[b->xa6]); y = b->x32 + p->x32; }
        {
        void* q = fn_80085EF8(b->x40[b->xa6])->x34->v10();
        if (q) fn_801A1DCC(lbl_8041EB20, q, x, y);
        }
    }
    if (b->xa6 != b->xa7) {
        PD* p = fn_80085EF8(b->x40[b->xa7]);
        p->x34->v48(b, p);
        p = fn_80085EF8(b->x40[b->xa6]);
        p->x34->v44(b, p);
        if (o->v88()) fn_80253EE4(o->v88(), 0.0f);
    }
}
