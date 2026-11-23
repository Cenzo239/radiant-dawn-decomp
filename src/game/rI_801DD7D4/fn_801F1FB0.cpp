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
extern const f32 lbl_804CFA08;
struct Ps { s16 x, y; };
struct W;
W* fn_801E5640(void*, int, int);
void fn_801E5448(void*, W*);
void fn_801E459C(void*, W*, Ps*, int);
void fn_801E518C(void*, W*, int, f32);
void fn_801E495C(void*, W*, Ps*, int);
void* fn_801E7A28(void*);
void fn_801E5734(void*, W*);
f32 fn_801E3468(W*);
struct W { u8 p[0xa]; s16 xa, xc; u8 pe[0x34 - 0xe]; f32 x34; u8 p38[4]; W* x3c; u8 p40[0xe]; u8 x4e; u8 p4f[2]; u8 x51; u8 p52[0x12]; const char* x64; u8 x68; u8 p69[0x13]; int x7c, x80; };
struct Sc { u8 p[0x40]; W* x40, *x44, *x48, *x4c, *x50; };
static inline void setX(Sc* o, W* w, s16 x, int f) { s16 y = w->xc; Ps t; t.x = x; t.y = y; fn_801E459C(o, w, &t, f); }
static inline void setY(Sc* o, W* w, s16 y, int f) { Ps t; t.x = w->xa; t.y = y; fn_801E459C(o, w, &t, f); }
#define FETCH(v, id, d) \
    v = fn_801E5640(o, id, 0); \
    if (v == 0) { v = o->d; fn_801E5448(o, v); }
static inline BOOL eq1(f32 k) { return k == 1.0f; }
static inline BOOL nearE(const f32& a, const f32& b) { return a != b; }
#define CHECK CHAIN(k, a, fn_801E3468, x34); { f32 one = 1.0f; if (one != k) fn_801E518C(o, a, 0, one); }
#define CHAIN(res, W0, FN, F) {     W* w1 = (W0);     v1 = w1->F;     if (w1->x3c) {         W* w2 = w1->x3c;         v2 = w2->F;         if (w2->x3c) {             W* w3 = w2->x3c;             v3 = w3->F;             if (w3->x3c) {                 W* w4 = w3->x3c;                 v4 = w4->F;                 if (w4->x3c) v4 *= FN(w4->x3c);                 v3 *= v4;             }             v2 *= v3;         }         v1 *= v2;     }     res = v1; }
static inline W* fetch(Sc* o, int id, W* const& d) { W* v = fn_801E5640(o, id, 0); if (v == 0) { v = d; fn_801E5448(o, v); } return v; }
static inline W* fetchA(Sc* o) { W* v = fn_801E5640(o, 0x100, 0); if (v == 0) { v = o->x40; fn_801E5448(o, v); } return v; }
static inline void help(Sc* o, const char* const& s) {
    W* h = fn_801E5640(o, -0x1000, 0);
    if (h) h->x64 = s;
}
void fn_801F1FB0(Sc* o) {
    /*P*/
    W* a;
    W* b;
    f32 k;
    f32 v4;
    f32 v3;
    f32 v2;
    f32 v1;
/*E*/
    a = fetchA(o);
    if (a->xc != 0x1c) setY(o, a, 0x1c, 0);
    a->x51 = 0;
    a->x7c = 0;
    a->x80 = 0;
    CHECK
    FETCH(b, 0x101, x44);
    if (b->xa != 0x12a) setX(o, b, 0x12a, 0);
    FETCH(b, 0x102, x48);
    if (b->xc != 0x13) setY(o, b, 0x13, 0);
    FETCH(b, 0x103, x4c);
    b->x68 = 0;
    b->x4e = 1;
    fn_801E5734(o, a);
    help(o, lbl_8036F03C + 0x18);
}

static inline void setX5(Sc* o, W* w, s16 x, int f) { s16 y = w->xc; Ps t; t.x = x; t.y = y; fn_801E495C(o, w, &t, f); }
class VW { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(void*); };
void fn_801F37BC(Sc* o) {
    /*P*/
    W* a;
    W* b;
    f32 k;
    f32 v4;
    f32 v3;
    f32 v2;
    f32 v1;
/*E*/
    a = fetchA(o);
    if (a->xc != 0x1c) setY(o, a, 0x1c, 1);
    CHECK
    {
    W* c;
    int one = 1;
    a->x51 = one;
    c = o->x4c;
    c->x68 = 0;
    c->x4e = one;
    }
    {
    W* w = fn_801E5640(o, 0x105, 0);
    if (w) setX5(o, w, 0x189, 0);
    }
    {
    W* w = fn_801E5640(o, 0x109, 0);
    if (w) setX5(o, w, 0x197, 0);
    }
    FETCH(b, 0x104, x50);
    if (b->xa != 0x138) setX(o, b, 0x138, 0);
    ((VW*)b)->v34(fn_801E7A28(a));
    fn_801E5734(o, a);
    help(o, lbl_8036F03C + 0x5e);
}
}
