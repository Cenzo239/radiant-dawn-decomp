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
extern u8 lbl_8041EB20[0x100];
struct PtS { u16 x, y; };
struct Fl2 { s16 x, y; };
void* fn_801E9B28(void*);
void fn_801E5954(void*);
int fn_801A2224(void*);
void fn_801A1F64(void*, void*, f32, f32);
void fn_801A1CFC(void*);
void fn_801A1BE0(void*, void*, void*, f32, f32);
u32* fn_801116B8(void*);
void fn_801E6B64(const char*, void*, f32, f32);
int fn_801F43E0(void*);
void fn_80253EE4(const char*, f32);
void fn_801E5734(void*, void*);
void fn_80083DC4(void*, int);
void fn_801FE76C(void*, int);
int fn_801E9A30(void*);
int fn_801E999C(void*, int);
}
class VL { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual PtS v30(); };
class IN { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44(); virtual u32 v48(); };
extern "C" IN* lbl_804CB5B8;
struct LL { u8 p[0xa]; s16 xa, xc; u8 pe[0x3e]; u8 x4c; u8 p4d[3]; s16 x50; u8 p52[2]; PtS x54; u8 p58[8]; int x60; };
struct LM { u8 p[0xa]; s16 xa, xc; u8 pe[0x43]; u8 x51, x52; u8 p53[0x35]; s16 x88; PtS x8a; };
struct It { void* x0; u8 x4; u8 p:5; u8 b:1; u8 q:2; };
struct OO { u8 p[0x4c]; LL* x4c; u8 p50[4]; LM* x54; };
static inline BOOL blk(void) {
    u32 f1 = *(volatile u32*)&lbl_804CB700;
    u32 f2 = *(volatile u32*)&lbl_804CB700;
    BOOL b = FALSE;
    if ((f1 & 0x10) && !(f2 & 0x20)) b = TRUE;
    return b;
}
static inline PtS getP(LL* l) { return ((VL*)l)->v30(); }
extern "C" void fn_801F6490(OO* a) {
    /*P*/
    LM* m;
    LL* l;
    /*E*/
    l = a->x4c;
    m = a->x54;
    fn_801E5734(a, l);
    l->x60 = 1;
    {
    int k = fn_801E9A30(l);
    if ((s16)k >= 0) l->x50 = k;
    else l->x50 = fn_801E999C(l, 0);
    }
    {
    PtS r = m->x8a;
    int dx = m->xa - l->xa;
    int dy = m->xc - l->xc;
    r.x = (s16)r.x + dx;
    r.y = (s16)r.y + dy;
    l->x54 = r;
    l->x4c = 1;
    }
}
static inline void back(OO* o, LL* l, LM* m) {
    PtS r = l->x54;
    int dx = l->xa - m->xa;
    int dy = l->xc - m->xc;
    r.x = (s16)r.x + dx;
    r.y = (s16)r.y + dy;
    m->x8a = r;
}
static inline void a1(LL* l, It* it) { PtS p = getP(l); Fl2 q = *(Fl2*)&p; fn_801A1F64(lbl_8041EB20, it, q.x, q.y); }
static inline void a2(LL* l, OO* o) { PtS p = getP(l); Fl2 q = *(Fl2*)&p; fn_801E6B64(lbl_8036F03C + 0xe5, o, q.x, q.y); }
static inline void a3(LL* l, OO* o, It* it) { PtS p = getP(l); Fl2 q = *(Fl2*)&p; fn_801A1BE0(lbl_8041EB20, o, it, q.x, q.y); }
extern "C" void fn_801F654C(OO* o) {
    /*P*/
    LM* m;
    LL* l;
    It* it;
    u32 k;
    int z;
    int bb;
/*E*/
    l = o->x4c;
    m = o->x54;
    it = (It*)fn_801E9B28(l);
    fn_801E5954(o);
    if (it != fn_801E9B28(l)) {
        it = (It*)fn_801E9B28(l);
        if (fn_801A2224(lbl_8041EB20)) {
            if (it && it->x0) {
                a1(l, it);
            } else {
                fn_801A1CFC(lbl_8041EB20);
            }
        }
    }
    if (blk()) return;
    k = lbl_804CB5B8->v48();
    if ((k & 0x400) && it && !fn_801A2224(lbl_8041EB20)) {
        if (fn_801116B8(it)[1] & 4) goto msg;
        bb = 1;
        if ((fn_801116B8(it)[0] & 0x1000000) == 0 && it->b == 0) bb = 0;
        if (bb) {
msg:
            a2(l, o);
            return;
        }
        if (!fn_801F43E0(o)) {
            fn_80253EE4(lbl_8036F03C + 0xf3, 0.0f);
            return;
        }
        z = 0;
        m->x52 = z;
        back(o, l, m);
        fn_801E5734(o, m);
        l->x60 = z;
        l->x4c = z;
        m->x51 = 1;
        fn_80083DC4(o, 0xf);
        fn_80253EE4(lbl_8036F03C + 0x2b, 0.0f);
    } else if ((k & 0x2000) && !fn_801A2224(lbl_8041EB20) && it && it->x0) {
        a3(l, o, it);
        *(u32*)lbl_8041EB20 |= 2;
    } else if ((k & 0x2800) && fn_801A2224(lbl_8041EB20)) {
        fn_801A1CFC(lbl_8041EB20);
    } else if ((k & 0x800) && !fn_801A2224(lbl_8041EB20)) {
        z = 0;
        m->x52 = z;
        fn_801FE76C(m, m->x88);
        back(o, l, m);
        fn_801E5734(o, m);
        l->x60 = z;
        l->x4c = z;
        m->x51 = 1;
        fn_80083DC4(o, 0xf);
        fn_80253EE4(lbl_8036F03C + 0x3b, 0.0f);
    }
}
