/* fn_801B6B18 (round 22, agent r22b): class `regs`, 10 words differ.
 * Unit list window draw. Mode 1: count the units of list 0 without flag 0x10 (deployed
 * count), mode 2: the units of list 5 with flag 0x400000; then print "label  d/n" against
 * the limit lbl_803E7320[0], with a different label when the count is short (and
 * fn_800D0AE4(0, n - d) to format the difference). Otherwise the current page's draw
 * (vfunc 0x18) at (48, 18).
 * Built with tools/equiv/mkself.py from ../fn_801B7644.cpp and wip/fn_801B6B18.cpp; the
 * parent's LPage slot 0x18 is declared here as draw(tex, x, y) (it was a no-argument v18).
 * Bugs fixed in the old fragment (checked against the original constants):
 *  - the alpha/depth value passed to fn_8007E720 is -0.1f (lbl_804CF334), not 5.0f;
 *  - the page is drawn at (48.0f, 18.0f) (lbl_804CF338/33C), not (0, 0).
 * (check_func.py -v reports both as "constant ... but original has".)
 * Codegen: the 0x10 flag test is `s64 m = k;` from `int k = 0x10` (the unfolded zero high
 * word `srawi r0,r4,31`), and the counters are zeroed after the render-state calls.
 * Remaining: the count d and the limit n swap r29/r30 in mode 1 (so the `mr r7`/`mr r8`
 * before the two fn_800CB278 calls name the other register; d still goes in r7 and n in
 * r8). symcheck --anon --xargs: 50 blocks, 0 differ.
 */
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
    virtual const char* name(void* a, int k);
    virtual int cmp(LEnt* e, int col);
    virtual const char* help(int k);
    virtual void v14x(void* tex, f32 x, f32 y);
    virtual void draw(void* tex, f32 x, f32 y); /* +0x18 */
    virtual void cell(void* e, int a, int k, f32 x, f32 y);
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


extern const u8* fn_800CD204(int);
extern void fn_800800D4(int);
extern void fn_80080330(f32, f32);
extern void fn_80080308(void);
typedef struct C4 { u8 r, g, b, a; } C4;
extern void fn_80080508(C4);
extern void fn_80080B00(int, const u8*, f32);
extern void fn_80080C24(const char*);
extern int fn_80290C84(char*, const char*, void*);
extern void fn_801B5EB4(int, int, const char*, f32, f32);
extern void fn_801B6EBC(int, int, u32, const char*, ...);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E7B4(void);
extern void fn_8007E7DC(int);
extern void fn_8007E720(f32);
extern void fn_8007E174(int, int);
extern void fn_8007E4E4(f32, f32, f32, f32);
extern const char* fn_800D0864(const char*);
extern void fn_800CB278(int, int, int, const char*, ...);
extern void fn_800D0AE4(int, int);
extern const char* fn_80118C44(void*);
extern void fn_801791D8(void*, int);
typedef struct LHead { u8* head; u32 a, b; } LHead;
extern LHead* lbl_804CB814;
extern s32 lbl_803E7320[0x10];

static inline const char* Help0(LPage* g, void* a, int k) { return g->name(a, k); }
#define STR(o) (lbl_8036DEB0 + (o))
typedef struct va_list_ { char gpr; char fpr; char reserved[2]; char* input_arg_area; char* reg_save_area; } va_list_;
void fn_801B6EBC(int x, int y, u32 col, const char* fmt, ...);

void fn_801B7644(LPage* g, void* a, void* e, int k, f32 x, f32 y);

void fn_801BA814(LPage* g, void* a, void* e, int k, f32 x, f32 y);


static inline BOOL Vis(LView* p, int i) {
    int f = p->x6A / 32;
    int l = f + 8;
    if (p->x6A % 32 != 0) l++;
    if (i >= f && i <= l) return 1;
    return 0;
}
void fn_801B739C(LPage* g, LView* p, int page);

}

/* ---- from build/tmp/r22b/fr_b18.cpp ---- */
extern "C" {
extern "C" {
static inline void Count(int d, int n, const char* full, const char* rest) {
    fn_8007E154();
    fn_8007E720(-0.1f);
    fn_8007E174(0, 0x13);
    fn_8007E164();
    if (d == n) {
        fn_800CB278(0x2C, 0x17, 0x33, fn_800D0864(full));
        fn_800CB278(0xE8, 0x17, 1, STR(0x12), d, n);
    } else {
        fn_800D0AE4(0, n - d);
        fn_800CB278(0x2C, 0x17, 0x33, fn_800D0864(rest));
        fn_800CB278(0xE8, 0x17, 1, STR(0x2F), d, n);
    }
}
void fn_801B6B18(LView* p) {
    switch (p->x6C) {
    case 1: {
        s16 d;
        int k = 0x10;
        s64 m = k;
        u8* u;
        fn_8007E154();
        fn_8007E7B4();
        fn_8007E7DC(0xFF);
        fn_8007E164();
        d = 0;
        for (u = lbl_804CB814[0].head; u != 0; ) {
            u64 f = *(u64*)(u + 0x108);
            u = *(u8**)(u + 0xE8);
            if (!(f & m)) d++;
        }
        Count(d, (s16)lbl_803E7320[0], STR(0), STR(0x1F));
        break;
    }
    case 2: {
        s16 d;
        u8* u;
        fn_8007E154();
        fn_8007E7B4();
        fn_8007E7DC(0xFF);
        fn_8007E164();
        d = 0;
        for (u = lbl_804CB814[5].head; u != 0; ) {
            u64 f = *(u64*)(u + 0x108);
            u = *(u8**)(u + 0xE8);
            if (f & 0x400000) d++;
        }
        Count(d, (s16)lbl_803E7320[0], STR(0x40), STR(0x56));
        break;
    }
    default:
        p->pages[p->x63]->draw(p->tex, 48.0f, 18.0f);
        break;
    }
}

}
}
