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
extern u8 lbl_803CA870[0x10];
struct W;
struct Pu { u16 x, y; };
struct Fl2 { s16 x, y; };
void* fn_801E7A28(void*);
void fn_801E5954(void*);
void fn_801E6B64(const char*, void*, f32, f32);
int fn_8012BCB0(void*);
void fn_80083B78(void*);
void fn_80083DC4(void*, int);
void fn_80253EE4(const char*, f32);
#if TARGET_PC
FE10_PROTO void fn_801E6C44(void*, void*, p32arg);
#else
void fn_801E6C44(void*, void*, int);
#endif
void fn_801E77E8(W*, int);
void fn_801E518C(void*, W*, int, f32);
void fn_801E495C(void*, W*, void*, int);
void fn_801E5558(void*, W*, int);
f32 fn_801E3468(W*);
}
class VI { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(void*); virtual void v38(); virtual Pu v3C(); };
class IN { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44(); virtual u32 v48(); };
extern "C" IN* lbl_804CB5B8;
struct SA { u8 p[0x40]; VI* x40; u8 p44[0xc]; VI* x50; u8 p54[0x18]; u8 x6c; };
static inline BOOL blk(void) {
    u32 f1 = *(volatile u32*)&lbl_804CB700;
    u32 f2 = *(volatile u32*)&lbl_804CB700;
    BOOL b = FALSE;
    if ((f1 & 0x10) && !(f2 & 0x20)) b = TRUE;
    return b;
}
static inline Pu getP(VI* w) { return w->v3C(); }
static inline void msgAt(VI* w, const char* s, void* o) {
    Pu r = getP(w);
    Fl2 q = *(Fl2*)&r;
    fn_801E6B64(s, o, q.x, q.y);
}
extern "C" void fn_801F3A3C(SA* o) {
    /*P*/
    VI* v;
    VI* w;
    void* it;
/*E*/
    w = o->x40;
    v = o->x50;
    it = fn_801E7A28(w);
    fn_801E5954(o);
    if (it != fn_801E7A28(w)) {
        it = fn_801E7A28(w);
        v->v34(it);
    }
    if (blk()) return;
    {
    u32 k = lbl_804CB5B8->v48();
    if ((k & 0x400) && it) {
        if (*(void**)lbl_803CA870 == it) {
            msgAt(w, lbl_8036F03C + 0x78, o);
        } else if (fn_8012BCB0(*(void**)lbl_803CA870) && fn_8012BCB0(it)) {
            msgAt(w, lbl_8036F03C + 0x86, o);
        } else {
            ((void**)lbl_803CA870)[1] = it;
            fn_80083B78(o);
            fn_80253EE4(lbl_8036F03C + 0x2b, 0.0f);
        }
    } else if ((k & 0x2000) && it) {
        fn_801E6C44(it, o, 1);
        o->x6c = 0xb;
        fn_80083DC4(o, 0x2d);
    } else if ((k & 0x1000) && it) {
        fn_80083DC4(o, 0xe);
        fn_80253EE4(lbl_8036F03C + 0x94, 0.0f);
    } else if (k & 0x800) {
        fn_80083DC4(o, 0xc);
        fn_80253EE4(lbl_8036F03C + 0x3b, 0.0f);
    }
    }
}
struct W { u8 p[0xa]; s16 xa, xc; u8 pe[0x34 - 0xe]; f32 x34; u8 p38[4]; W* x3c; u8 p40[0x11]; u8 x51; u8 p52[2]; s16 x54; u8 p56[0x26]; int x7c, x80; };
class RC { public: virtual void v08(int); int rc; };
struct SB { u8 p[0x40]; W* x40; u8 p44[0xc]; W* x50; W* x54; W* x58; };
struct Ps { s16 x, y; };
#define REL(f) { RC* p = (RC*)o->f; if (p) { if (--p->rc == 0 && p) p->v08(1); o->f = 0; } }
extern "C" void fn_801F41E4(SB* o) {
    /*P*/
    W* a;
    f32 k;
    f32 v4;
    f32 v3;
    f32 v2;
    f32 v1;
/*E*/
    a = o->x40;
    fn_801E77E8(a, a->x54);
    a->x51 = 0;
    a->x7c = 0;
    a->x80 = 0;
    {
    W* w1 = a;
    v1 = w1->x34;
    if (w1->x3c) {
        W* w2 = w1->x3c;
        v2 = w2->x34;
        if (w2->x3c) {
            W* w3 = w2->x3c;
            v3 = w3->x34;
            if (w3->x3c) {
                W* w4 = w3->x3c;
                v4 = w4->x34;
                if (w4->x3c) v4 *= fn_801E3468(w4->x3c);
                v3 *= v4;
            }
            v2 *= v3;
        }
        v1 *= v2;
    }
    k = v1;
    }
    { f32 one = 0.5f; if (one != k) fn_801E518C(o, a, 0, one); }
    {
    s16 y = o->x50->xc;
    Ps t;
    t.x = 0x18c;
    t.y = y;
    fn_801E495C(o, o->x50, &t, 1);
    }
    REL(x50);
    fn_801E5558(o, o->x54, 0);
    REL(x54);
    fn_801E5558(o, o->x58, 0);
    REL(x58);
}
