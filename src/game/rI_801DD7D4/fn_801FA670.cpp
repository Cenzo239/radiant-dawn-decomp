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
extern char lbl_8036F03C[];
extern u8 lbl_8041EB20[0x100];
struct PtS { u16 x, y; };
struct Fl2 { s16 x, y; };
void* fn_801E9B28(void*);
void fn_801E5954(void*);
void fn_80083B78(void*);
void* fn_801E9BF4(void*, int);
void fn_80111C78(void*, void*);
void fn_80079210(void*);
void fn_80110D38(void*);
void fn_801E9BE0(void*);
int fn_801E9914(void*, int);
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
struct LL { u8 p[0xa]; s16 xa, xc; u8 pe[0x3e]; u8 x4c; u8 p4d[3]; s16 x50; u8 p52[2]; PtS x54; u8 p58[4]; void* x5c; int x60; };
struct LM { u8 p[0xa]; s16 xa, xc; u8 pe[0x43]; u8 x51, x52; u8 p53[0x35]; s16 x88; PtS x8a; };
struct It { void* x0; u8 x4; u8 p:5; u8 b:1; u8 q:2; };
struct BX { u8 p[0x40]; void* x40; void* x44; };
struct OO { u8 p[0x4c]; LL* x4c; u8 p50[4]; LM* x54; BX* x58; };
static inline BOOL blk(void) {
    u32 f1 = *(volatile u32*)&lbl_804CB700;
    u32 f2 = *(volatile u32*)&lbl_804CB700;
    BOOL b = FALSE;
    if ((f1 & 0x10) && !(f2 & 0x20)) b = TRUE;
    return b;
}
static inline PtS getP(LL* l) { return ((VL*)l)->v30(); }
static inline void a1(LL* l, It* it) { PtS p = getP(l); Fl2 q = *(Fl2*)&p; fn_801A1F64(lbl_8041EB20, it, q.x, q.y); }
static inline void a2(LL* l, OO* o) { PtS p = getP(l); Fl2 q = *(Fl2*)&p; fn_801E6B64(lbl_8036F03C + 0x22e, o, q.x, q.y); }
static inline void a3(LL* l, OO* o, It* it) { PtS p = getP(l); Fl2 q = *(Fl2*)&p; fn_801A1BE0(lbl_8041EB20, o, it, q.x, q.y); }
static inline void setB(BX* b, void* a, void* c) { b->x40 = a; b->x44 = c; if (!b->x44) b->x40 = 0; }
extern "C" void fn_801FA670(OO* o) {
    /*P*/
    LL* l;
    It* it;
    OO* oo;
    BX* b;
    u32 k;
    int bb;
/*E*/
    l = o->x4c;
    b = o->x58;
    it = (It*)fn_801E9B28(l);
    fn_801E5954(o);
    if (it != fn_801E9B28(l)) {
        it = (It*)fn_801E9B28(l);
        if (fn_801A2224(lbl_8041EB20)) {
            if (it) {
                a1(l, it);
            } else {
                fn_801A1CFC(lbl_8041EB20);
            }
        }
    }
    if (it) setB(b, l->x5c, it);
    else setB(b, 0, 0);
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
        fn_80083B78(o);
    } else if ((k & 0x2000) && !fn_801A2224(lbl_8041EB20) && it) {
        a3(l, o, it);
        *(u32*)lbl_8041EB20 |= 2;
    } else if ((k & 0x2800) && fn_801A2224(lbl_8041EB20)) {
        fn_801A1CFC(lbl_8041EB20);
    } else if ((k & 0x800) && !fn_801A2224(lbl_8041EB20)) {
        fn_80083DC4(o, 0x27);
        fn_80253EE4(lbl_8036F03C + 0x3b, 0.0f);
    }
}
struct LN { LN* prev; LN* next; void* val; };
struct RG { u32 size; LN* prev; LN* next; };
class SS { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual int v34(); virtual void v38(); virtual void v3C(); virtual void v40(); virtual void v44(); virtual PtS v48(); u8 p4[0x6c]; s16 cur[12]; u8 p88[0x10]; RG l[12]; };
static inline LN* adv(LN* p, s16 n) {
    if (n >= 0) {
        for (s16 k = n; k > 0; k--) p = p->next;
    } else {
        for (s16 k = n; k < 0; k++) p = p->prev;
    }
    return p;
}
static inline void** curVal(SS* s) {
    int i = s->v34();
    s16* c = &s->cur[i];
    RG* r = &s->l[i];
    if (r->size == 0) return 0;
    return &adv(r->next, *c)->val;
}
struct Pr { int pad; void* v; Pr(void* x) { v = x; } };
static inline LN* fnd(LN* b, LN* e, Pr p) { while (b != e && b->val != p.v) b = b->next; return b; }
static inline PtS getM(SS* s) { return s->v48(); }
static inline void a4(SS* s, const char* m, OO* o) { PtS p = getM(s); Fl2 q = *(Fl2*)&p; f32 x = q.x; f32 y = q.y; fn_801E6B64(m, o, x, y); }
extern "C" void fn_801FA160(OO* o) {
    /*P*/
    void* it;
    int n;
    RG* r;
    SS* s;
    LL* l;
    int j;
/*E*/
    s = (SS*)o->x54;
    l = o->x4c;
    it = *curVal(s);
    n = fn_801E9A30(l);
    if ((s16)n < 0) {
        a4(s, lbl_8036F03C + 0x204, o);
        return;
    }
    fn_80253EE4(lbl_8036F03C + 0x2b, 0.0f);
    fn_80111C78(fn_801E9BF4(l, (s16)n), it);
    fn_801E9BE0(l);
    r = s->l;
    for (j = 0; j < 12; r++, j++) {
        Pr pr(it);
        LN* f = fnd(r->next, (LN*)&r->prev, pr);
        if (f != (LN*)&r->prev) {
            f->prev->next = f->next;
            f->next->prev = f->prev;
            fn_80079210(f);
            {
            u32 sz = --r->size;
            s16* c = &s->cur[j];
            if (*c >= sz) *c = sz - 1;
            }
            break;
        }
    }
    {
    int i = s->v34();
    fn_801FE76C(s, s->cur[i]);
    }
    fn_80110D38(it);
    {
    int m = fn_801E9914(l, l->x50);
    if ((s16)m < 0) m = fn_801E999C(l, l->x50);
    if ((s16)m >= 0) l->x50 = m;
    else fn_80083DC4(o, 0x24);
    }
}
