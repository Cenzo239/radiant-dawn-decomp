/* fn_801FA9BC (0x288), zero-idiom family, round 20: complete draft, class `other`.
 * Convoy "store item" confirm: if the convoy is full shows message +0x240; else moves the unit's current
 * item into the convoy (fn_801051D8), re-sorts the twelve category lists, selects the stored item's
 * category and row, and repositions the unit's inventory cursor (or leaves with state 0x27 if empty).
 * Differences from the original (tools/equiv/dd.py, registers masked): 161 of 162 instructions;
 *   1. the zero idiom: original `li r25,0; li r27,0; mr r26,r25`, ours `li; li; li r27,0` (same values);
 *   2. the original sign-extends the row index once more (`extsh r4,r4`) before fn_801FE76C; ours omits
 *      this redundant instruction.
 * NOT only the mr/li instruction: one redundant extsh is also missing. Functionally equal.
 * Self-contained: fn_801FA670.cpp's declarations with its exported functions reduced to prototypes. */
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
extern "C" void fn_801FA670(OO* o);

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
extern "C" void fn_801FA160(OO* o);


/* ---- from build/tmp/r20i/frag_A9BC.cpp ---- */
extern "C" {
extern "C" {
int* fn_801059B0(void);
int fn_80105194(int*);
int fn_801051D8(int*, void*);
void* fn_80081194(void*, void*);
void fn_801FDC38(void*, void*);
extern u8 lbl_8038D690[];
extern u8 lbl_803CA870[];
}
class SQ { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(int); virtual int v34(); virtual void v38(); virtual void v3C(); virtual void v40(); virtual int v44(void*); virtual PtS v48(); virtual void v4C(void*, void*); };
struct EC { u8 c; EC() { c = 0; } };
static inline void sortAll(SS* s) {
    int i = 0;
    while (1) { EC e; fn_801FDC38((u8*)s + i * 0xc + 0x98, &e); if (++i == 12) break; }
}
struct Bk { int n; u8* items; };
/* index of `it` in its category list, or -1 */
static inline int indexOf(SS* s, void* it) {
    int r;
    int k = ((SQ*)s)->v44(it);
    if (k == 0xd) {
        r = -1;
    } else {
        RG* g = &s->l[k];
        Pr pr(it);
        LN* b = g->next;
        LN* f = fnd(b, (LN*)&g->prev, pr);
        r = -1;
        if (f != (LN*)&g->prev) {
            int n = 0;
            for (; b != f; b = b->next) n++;
            r = (s16)n;
        }
    }
    return r;
}
extern "C" void fn_801FA9BC(OO* o) {
    LL* l = o->x4c;
    SS* s = (SS*)o->x54;
    void* it = fn_801E9B28(l);
    s16 n = fn_80105194(fn_801059B0());
    if (fn_801051D8(fn_801059B0(), it) == 0) {
        PtS p = getP(l); Fl2 q = *(Fl2*)&p;
        fn_801E6B64(lbl_8036F03C + 0x240, o, q.x, q.y);
        return;
    }
    fn_80253EE4(lbl_8036F03C + 0x2b, 0.0f);
    void* e = ((Bk*)fn_801059B0())->items + n * 0x28;
    ((SQ*)s)->v4C(e, 0);
    sortAll(s);
    ((SQ*)s)->v30(((SQ*)s)->v44(e));
    fn_801FE76C(s, (s16)indexOf(s, e));
    fn_80110D38(it);
    fn_801E9BE0(l);
    ((void**)lbl_803CA870)[1] = 0;
    fn_80081194(lbl_8038D690, o);
    {
    int m = fn_801E9914(l, l->x50);
    if ((s16)m < 0) m = fn_801E999C(l, l->x50);
    if ((s16)m >= 0) l->x50 = m;
    else fn_80083DC4(o, 0x27);
    }
}
}
