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
struct W;
struct Ps { s16 x, y; };
W* fn_801E5640(void*, int, int);
void fn_801E5448(void*, W*);
void fn_801E459C(void*, W*, Ps*, int);
void fn_801E495C(void*, W*, Ps*, int);
void fn_801E5734(void*, W*);
}
struct LN { LN* prev; LN* next; u8 val[4]; };
struct RG { int size; LN* prev; LN* next; };
struct W { virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual int v34();
   u8 p4[6]; s16 xa, xc; u8 pe[0x4e - 0xe - 0]; u8 x4e_; };
struct Sc { u8 p[0x4c]; u8* x4c; u8 p50[4]; W* x54; W* x58; };
struct SS { u8 p[0x70]; s16 cur[12]; u8 p88[0x10]; RG l[12]; };
#define GW(o, w) ((Wr*)(w))
struct Wr { u8 p[0xa]; s16 xa, xc; };
static inline void setY(Sc* o, W* w, s16 y, int f) { Ps t; t.x = ((Wr*)w)->xa; t.y = y; fn_801E495C(o, w, &t, f); }
static inline void setX(Sc* o, W* w, s16 x, int f) { s16 yy = ((Wr*)w)->xc; Ps t; t.x = x; t.y = yy; fn_801E495C(o, w, &t, f); }
static inline void setXb(Sc* o, W* w, s16 x, int f) { s16 yy = ((Wr*)w)->xc; Ps t; t.x = x; t.y = yy; fn_801E459C(o, w, &t, f); }
static inline void help(Sc* o, const char* const& s) {
    W* h = fn_801E5640(o, -0x1000, 0);
    if (h) *(const char**)((u8*)h + 0x64) = s;
}
static inline LN* adv(LN* p, s16 n) {
    if (n >= 0) {
        for (s16 k = n; k > 0; k--) p = p->next;
    } else {
        for (s16 k = n; k < 0; k++) p = p->prev;
    }
    return p;
}
static inline u8* curVal(W* b) {
    int i = b->v34();
    SS* s = (SS*)b;
    s16* c = &s->cur[i];
    RG* r = &s->l[i];
    if (r->size == 0) return 0;
    return adv(r->next, *c)->val;
}
extern "C" void fn_801F56C4(Sc* o) {
    /*P*/
    W* b;
    W* c;
    /*E*/
    {
    W* w = fn_801E5640(o, 0x100, 0);
    if (w) setY(o, w, -0x24, 1);
    }
    {
    u8* m = o->x4c;
    m[0x68] = 1;
    m[0x4e] = 0;
    }
    {
    W* w = fn_801E5640(o, 0x104, 0);
    if (w) setX(o, w, 0x18c, 0);
    }
    b = fn_801E5640(o, 0x105, 0);
    if (b == 0) { b = o->x54; fn_801E5448(o, b); }
    if (((Wr*)b)->xa != 0x135) setXb(o, b, 0x135, 0);
    c = fn_801E5640(o, 0x109, 0);
    if (c == 0) { c = o->x58; fn_801E5448(o, c); }
    if (((Wr*)c)->xa != 0x143) setXb(o, c, 0x143, 0);
    fn_801E5734(o, b);
    if (curVal(b)) {
        help(o, lbl_8036F03C + 0xb0);
    } else {
        help(o, lbl_8036F03C + 0xca);
    }
}
