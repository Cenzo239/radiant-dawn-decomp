#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {

/* unit list window: input handling. Same layout as fn_801B78F0. */
struct W2 { u32 a, b; };
struct LStat { W2 a; u16 hit; s8 atk; s8 avo; s8 crit; s8 cavo; u8 rmax; u8 rmin; };
struct LEnt { u8* u; u32* h; void* w; LStat s;
 LEnt() {}
 LEnt(const LEnt& o) { u = o.u; h = o.h; w = o.w; s = o.s; }
 LEnt& operator=(const LEnt& o) { u = o.u; h = o.h; w = o.w; s = o.s; return *this; }
};
class LPage {
public:
    u8 pad[0x20];
    u8 n20; u8 n21; u8 a22; u8 b23;
    s16 x24[13];
    s16 x3E[13];
    virtual void v08();
    virtual int cmp(LEnt* e, int col);
    virtual const char* help(int k);
    virtual void v14();
};
struct LView;
typedef int (*LCb)(LView*, u8*);
typedef struct LView {
    u8 pad[0x30];
    void* x30;
    LPage** pages;
    LEnt* ents;
    void* tex;
    void* x40; void* x44; void* x48; void* x4C; void* x50; LCb cb;
    s16 x58, x5A, x5C, x5E;
    u8 x60; u8 n; s8 x62; u8 x63; u8 x64; s8 x65; u8 x66; s8 x67;
    s16 x68, x6A;
    u8 x6C, x6D, x6E, x6F;
    u32 x70;
} LView;
class LWin { public: u8 pad[0x28]; virtual void v08(); virtual void v0C(); virtual void v10(); virtual void destroy(int); };
class Pad {
public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2C(); virtual void v30();
    virtual u32 trig(); /* +0x34 */
    virtual void v38();
    virtual u32 rep();  /* +0x3C */
    virtual void v40();
    virtual u32 rep2(); /* +0x44 */
    virtual u32 held(); /* +0x48 */
};
extern Pad* lbl_804CB5B8;
extern u32 lbl_804CB700;
extern char lbl_8036DEB0[];
extern u8 lbl_803CAB38[];
extern u32 lbl_8041EB20[];
extern void fn_80253EE4(const char* s, f32 v);
extern void fn_80083DC4(void* p, int r);
extern void fn_80083B78(void* p);
extern void fn_80081A90(void* p);
extern void fn_8017A968(void* p, const char* s);
extern void fn_80179888(void* p, int a);
extern f32 fn_8001EBC8(int m, f32 a, f32 b, f32 c, f32 d);
extern int fn_801B76F8(LView* p);
extern void fn_801791E0(void* p);
extern void fn_8005874C(LView* p);
extern void fn_80024640(LView* p);
extern void fn_800FAFF0(u8* u, int a);
extern int fn_801A2224(void* h);
extern void fn_801A1CFC(void* h);
extern void fn_801A1AC4(void* h, void* p, const char* s, f32 x, f32 y);
extern void fn_801A1DCC(void* h, const char* s, f32 x, f32 y);
extern u8* fn_80060728(void* p);
extern void fn_80079210(void* p);
extern void fn_80079474(void* p);
extern void fn_80006EE0(void* p);
extern void fn_8017AB5C(void* p, int a);
extern void fn_801795E8(void* p, int a);
extern void fn_8001D424(void* p);


extern u32* fn_8024BC94(void);
extern const u8* fn_800CD204(int);
extern void fn_800800D4(int);
extern void fn_80080330(f32, f32);
extern void fn_80080308(void);
typedef struct C4 { u8 r, g, b, a; } C4;
extern void fn_80080508(C4);
extern void fn_80080B00(int, const u8*, f32);
extern void fn_80080C24(const char*);
#if TARGET_PC
extern FE10_PROTO void fn_801B5EB4(int, int, p32arg, float, float);
#else
extern void fn_801B5EB4(f32, f32, int, void*, const char*);
#endif

void fn_801B9F30(u8* u, LView* p) {
    {
    LEnt* e = p->ents;
    int k;
    for (k = 0; k < p->n; k++, e++) {
        if (e->u == u) { p->x62 = k; break; }
    }
    }
    {
    int q;
    int d;
    int n;
    d = (q = p->x62) - p->x6A / 32;
    if (d < 1 || d >= 8) {
        if (q == 0) p->x6A = 0;
        else if (n = p->n, q == n - 1) p->x6A = (n - 9) * 32;
        else if (d <= 0) p->x6A = (q - 1) * 32;
        else p->x6A = (q - 7) * 32;
    }
    }
    fn_80179888(p->x4C, p->x6A);
    if (p->x62 < 0) {
        p->x58 = p->pages[p->x63]->x3E[p->x65];
        p->x5A = 0x42;
        p->x5C = 0;
        p->x5E = 0;
    } else {
        p->x58 = 0x28;
        p->x5A = (p->x62 << 5) + 0x68 - p->x6A;
        p->x5C = 0x1B8;
        p->x5E = 0x16;
    }
}

int fn_801BA20C(void* a, u8* u) {
    u64* pf = (u64*)(u + 0x108);
    u64 st;
    st = *pf & 0xC0000000ULL;
    *pf &= ~0xC0000000ULL;
    {
    u32 v;
    u32 f = fn_8024BC94()[8];
    v = f & 1;
    if (v == 0) v = (f >> 1) & 1;
    if (v == 0) v = (f >> 2) & 1;
    if (v == 0) v = (f >> 3) & 1;
    if (v == 0) {
        switch (st) {
        case 0x40000000: break;
        case 0: *pf |= 0x40000000ULL; break;
        }
    } else {
        switch (st) {
        case 0x80000000: break;
        case 0: *pf |= 0x40000000ULL; break;
        case 0x40000000: *pf |= 0x80000000ULL; break;
        }
    }
    }
    return 1;
}
}
