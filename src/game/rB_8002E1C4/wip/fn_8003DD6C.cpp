/* NEAR MISS: fn_8003DD6C, 13 positions of 1620 (not counting the pool label): after the arrow draws, xb wants r29 and yc r27; this gives r27 and r25 (yc takes y's register). See NOTES.md round 14. */
#include "game/rE_800E5DE4/types.h"
typedef unsigned long long u64;
#pragma pool_strings on
#pragma inline_max_size(4000)
#pragma inline_depth(20)
typedef GXColor C4;
struct ItemD { u8 pad[0x16]; u16 x16; };
struct Slot { ItemD* data; };
struct UD { u8 pad[0x10c]; u32 x10c; };
struct BU {
    u8 pad0[0xec];
    void* xec;
    u8 padf0[0x114 - 0xf0];
    s8 x114;
    u8 pad115[0x3f0 - 0x115];
    UD* x3f0;
    u8 pad3f4[0x446 - 0x3f4];
    u8 x446;
    u8 pad447;
    s16 x448, x44a, x44c;
    u8 pad44e[0x452 - 0x44e];
    s16 x452;
    u8 pad454[0x458 - 0x454];
    s16 x458;
    u8 pad45a[0x476 - 0x45a];
    s16 x476;
    u8 pad478[0x4a0 - 0x478];
};
struct Opt { u32 a : 8; u32 k : 2; };
struct Ctl { u8 pad[0x10]; u8 alpha; u8 pad11[7]; u32 flags; };
struct Cmd { u8 pad[0x30]; Ctl* ctl; };
struct Arw { u8 pad[8]; Cmd* c[4]; };
struct Pt4 { Cmd* c[4]; };
struct DB { u8 pad[0x44]; };
class DV : public DB {
public:
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1C(int, int, int, int, int, int);
};
extern u8 lbl_803C8E80[];
extern u8 lbl_803CAB38[];
extern char lbl_803E7290[];
extern "C" {
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E174(int, int);
void fn_8007E4E4(f32, f32, f32, f32);
void fn_8007E7DC(u8);
void fn_8007E374(void*, int, int);
void fn_8007E720(f32);
void fn_800800D4(int);
void fn_80080348(f32, f32, f32, f32);
void fn_80080368(f32, f32, f32, f32);
void fn_80080508(C4);
void fn_800804F4(u8);
void fn_80080308(void);
C4* fn_800CD204(int);
Opt* fn_80060728(void*);
void fn_801C6EAC(const char*, const char*, char*);
int fn_8023F880(char*);
void* fn_8023F8EC(char*);
void fn_800068A0(void**, char*);
u64 OSGetTime(void);
u64 fn_8028C418(u64, u64);
u64 fn_8028C634(u64, u64);
f32 fn_8017F68C(int, f32, f32, f32, f32);
void fn_800CB3A8(f32 s, f32 t, s16 x, s16 y, int a, int b, int c, const char* f, ...);
int fn_8002C84C(void*, int);
void fn_801BCA94(void);
const char* fn_80118C44(void*);
int fn_800CA3DC(const char*, int, f32);
void fn_80075714(int, int, BU*);
Slot* fn_80030CF4(BU*);
const char* fn_80110F08(Slot*);
u16** fn_80006A0C(void*, int);
int fn_801D09F0(void);
void fn_800E48AC(Cmd*, f32, f32, f32);
#define B ((BU*)lbl_803C8E80)
#define PRN(x, y, a, s, ...) fn_800CB3A8(1.0f, 0.0f, x, y, 1, a, 0, s, __VA_ARGS__)
#define PR3(x, y, v) fn_800CB3A8(1.0f, 0.0f, x, y, 1, 1, 0, "%3d", v)
#define PRS(x, y, a, s) fn_800CB3A8(1.0f, 0.0f, x, y, 1, a, 0, s)
void pool_15a8(void) {
    const char* volatile s;
    s = "EID_ARROW4"; s = "SFX_SYS_SELECT4"; s = "IID_REST"; s = "IID_RELIVE"; s = "window/btl_mae/btl_mae"; s = ".cms"; s = "%3d"; s = " ??"; s = "\x81|\x81|";
}
static inline void Name(BU* u, int y1, int y2, f32 c) {
    f32 w = fn_800CA3DC(fn_80118C44(u->xec), -1, 1.0f);
    fn_800CB3A8(1.0f, 0.0f, c - w / 2.0f, y1, 1, 1, 0, fn_80118C44(u->xec));
    fn_80075714(2.0f + (c + w / 2.0f), y2, u);
}
static inline void Set(const C4& v) { fn_80080508(v); }
static inline void U(void* tex, int k, f32 x, f32 y, f32 w, f32 h, u8 a, f32 sc) {
    fn_8007E154();
    fn_8007E374(tex, k, 0x11);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080348(x, (y + h) - h * sc, 0.0f, 0.0f);
    fn_80080368(w * sc + x, y + h, w, h);
    Set(*fn_800CD204(1));
    fn_800804F4(a);
    fn_80080308();
}
static inline void D(void* tex, int k, f32 x, f32 y, f32 w, f32 h, u8 a, f32 sc) {
    fn_8007E154();
    fn_8007E374(tex, k, 0x11);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080348(x, y, 0.0f, 0.0f);
    fn_80080368(w * sc + x, h * sc + y, w, h);
    Set(*fn_800CD204(1));
    fn_800804F4(a);
    fn_80080308();
}
#define AR(F, k, Y, cnt) { \
    y##cnt = Y; \
    x##cnt = 20.0f; \
    tx##cnt = tex; \
    d##cnt = *fn_80006A0C(tx##cnt, k); \
    w##cnt = d##cnt[1]; \
    h##cnt = d##cnt[0]; \
    F(tx##cnt, k, x##cnt, y##cnt, w##cnt, h##cnt, show, 1.0f); }
static inline void Icon(BU* u, int side, int y) {
    if (fn_80030CF4(u)->data) {
        int k = 0;
        if (u->x446 && fn_8002C84C(lbl_803C8E80, side) >= 1) k = 1;
        ItemD* d = fn_80030CF4(u)->data;
        ((DV*)lbl_803E7290)->v1C(10, y, (u8)(d ? d->x16 : 0) + 0x81, k, 0xff, 0x258);
    }
}
static inline void Act(Cmd* c, f32 x, f32 y, u8 a) {
    fn_800E48AC(c, x, y, 0.0f);
    c->ctl->alpha = a;
    c->ctl->flags &= ~0x10;
}
static inline void body(Arw* o, int sh, int x, int y, int alpha, int& show, char* buf, Pt4& cp, int* xs, C4& c, void*& tex) {
    /*P*/
    f32 x8;
    f32 y8;
    f32 w8;
    f32 h8;
    f32 x7;
    f32 y7;
    f32 w7;
    f32 h7;
    f32 x6;
    f32 y6;
    f32 w6;
    f32 h6;
    f32 x5;
    f32 y5;
    f32 w5;
    f32 h5;
    f32 x4;
    f32 y4;
    f32 w4;
    f32 h4;
    f32 x3;
    f32 y3;
    f32 w3;
    f32 h3;
    f32 x2;
    f32 y2;
    f32 w2;
    f32 h2;
    f32 x1;
    f32 y1;
    f32 w1;
    f32 h1;
    f32 v;
    u16* d8;
    void* tx8;
    u16* d7;
    void* tx7;
    u16* d6;
    void* tx6;
    u16* d5;
    void* tx5;
    u16* d4;
    void* tx4;
    u16* d3;
    void* tx3;
    u16* d2;
    void* tx2;
    u16* d1;
    void* tx1;
    int yc;
    int xa;
    int xb;
    Opt* opt;
    const char* n2;
    const char* n4;
    const char* n3;
    int j;
    int i;
    int un;
    BU* du;
    BU* au;
    const char* n1;
    /*E*/
    c = *fn_800CD204(1);
    au = B;
    du = B + 1;
    opt = fn_80060728(lbl_803CAB38);
    un = 0;
    if (du->x3f0 && (du->x3f0->x10c & 0x10000000)) un = 1;
    fn_801C6EAC("window/btl_mae/btl_mae", ".cms", buf);
    if (sh == 0) return;
    if (opt->k == 2) return;
    if (!fn_8023F880(buf)) return;
    tex = fn_8023F8EC(buf);
    if (!tex) fn_800068A0(&tex, buf);
    show = fn_8028C634(fn_8028C418(OSGetTime(), (*(u32*)0x800000F8 >> 2) / 1000), 500);
    if ((u32)show <= 200) {
        v = fn_8017F68C(4, 0.0f, 4.0f, (u32)show, 200.0f);
        show = fn_8017F68C(4, 128.0f, 255.0f, (u32)show, 200.0f);
    } else {
        v = fn_8017F68C(4, 4.0f, 0.0f, (u32)(show - 200), 300.0f);
        show = fn_8017F68C(4, 255.0f, 128.0f, (u32)(show - 200), 300.0f);
    }
    cp = *(Pt4*)o->c;
    if (opt->k == 0) {
        u32 kw = 0xc0;
        u32 kh = 0x120;
        fn_8007E154();
        fn_8007E4E4(x + 0x1c, y + 0x50, 120.0f, 1.0f);
        fn_8007E7DC((u8)alpha);
        fn_8007E164();
        fn_8007E154();
        fn_8007E374(tex, 1, 0x11);
        fn_8007E164();
        fn_800800D4(1);
        fn_80080348(0.0f, 0.0f, 0.0f, 0.0f);
        fn_80080368(kw, kh, kw, kh);
        Set(c);
        fn_80080308();
        fn_8007E154();
        fn_8007E720(-1.0f);
        fn_8007E174(0, 0x13);
        fn_8007E164();
        PR3(0x8a, 0x54, au->x114);
        { int dm = au->x448 - du->x44a; PR3(0x8a, 0x72, dm < 0 ? 0 : dm); }
        PR3(0x8a, 0x90, au->x452);
        PR3(0x8a, 0xae, au->x458);
        if (un) {
            PRS(0xc, 0x54, 0, " ??");
            PRS(0xc, 0x72, 1, " ??");
            PRS(0xc, 0x90, 1, " ??");
            PRS(0xc, 0xae, 1, " ??");
        } else {
            fn_800CB3A8(1.0f, 0.0f, 0xc, 0x54, 1, 0, 0, "%3d", du->x114);
            if (fn_8002C84C(lbl_803C8E80, 1)) {
                int dm = du->x448 - au->x44a;
                PR3(0xc, 0x72, dm < 0 ? 0 : dm);
                PR3(0xc, 0x90, du->x452);
                PR3(0xc, 0xae, du->x458);
            } else {
                PRS(0xc, 0x72, 1, "\x81|\x81|");
                PRS(0xc, 0x90, 1, "\x81|\x81|");
                PRS(0xc, 0xae, 1, "\x81|\x81|");
            }
        }
        fn_801BCA94();
        Name(au, 0xc, 0xe, 84.0f);
        fn_801BCA94();
        Name(du, 0xd6, 0xd8, 84.0f);
        fn_801BCA94();
        n1 = fn_80110F08(fn_80030CF4(au));
        n2 = fn_80110F08(fn_80030CF4(du));
        if (fn_80030CF4(au)->data) PRS(0x22, 0x24, 1, n1);
        if (fn_80030CF4(du)->data) PRS(0x22, 0xee, 1, n2);
        if (au->x476 > 0) AR(U, 3, 38.0f - v, 1);
        if (au->x476 < 0) AR(D, 4, 44.0f + v, 2);
        if (du->x476 > 0) AR(U, 3, 240.0f - v, 3);
        if (du->x476 < 0) AR(D, 4, 246.0f + v, 4);
        Icon(au, 0, 0x24);
        Icon(du, 1, 0xee);
        if (!un) {
            xa = x + 0xe3;
            xb = x + 0x66;
            yc = y + 0xcf;
            if (fn_801D09F0()) {
                xa -= 0xc;
                xb -= 0xc;
            }
            xs[0] = xa;
            xs[1] = xb;
            xs[2] = xa;
            xs[3] = xb;
            i = -1;
            j = -1;
            if (fn_8002C84C(lbl_803C8E80, 0) == 2) i = 0;
            if (fn_8002C84C(lbl_803C8E80, 1) == 2) j = 1;
            if (fn_8002C84C(lbl_803C8E80, 0) == 4) i = 2;
            if (fn_8002C84C(lbl_803C8E80, 1) == 4) j = 3;
            if (i != -1) { int xv = xs[i]; Act(cp.c[i], xv, yc, alpha); }
            if (j != -1) { int xv = xs[j]; Act(cp.c[j], xv, yc, alpha); }
        }
    } else {
        u32 kw = 0xc0;
        u32 kh = 0x1c0;
        fn_8007E154();
        fn_8007E4E4(x + 0x1c, y, 120.0f, 1.0f);
        fn_8007E7DC((u8)alpha);
        fn_8007E164();
        fn_8007E154();
        fn_8007E374(tex, 0, 0x11);
        fn_8007E164();
        fn_800800D4(1);
        fn_80080348(0.0f, 0.0f, 0.0f, 0.0f);
        fn_80080368(kw, kh, kw, kh);
        Set(c);
        fn_80080308();
        fn_8007E154();
        fn_8007E720(-1.0f);
        fn_8007E174(0, 0x13);
        fn_8007E164();
        PR3(0x8a, 0x86, au->x114);
        PR3(0x8a, 0xa4, au->x448);
        PR3(0x8a, 0xc2, au->x44a);
        PR3(0x8a, 0xe0, au->x452);
        PR3(0x8a, 0xfe, au->x458);
        PR3(0x8a, 0x11c, au->x44c);
        if (un) {
            PRS(0xc, 0x86, 1, " ??");
            PRS(0xc, 0xc2, 1, " ??");
            PRS(0xc, 0x11c, 1, " ??");
            PRS(0xc, 0xa4, 1, " ??");
            PRS(0xc, 0xe0, 1, " ??");
            PRS(0xc, 0xfe, 1, " ??");
        } else {
            PR3(0xc, 0x86, du->x114);
            PR3(0xc, 0xc2, du->x44a);
            PR3(0xc, 0x11c, du->x44c);
            if (fn_8002C84C(lbl_803C8E80, 1)) {
                PR3(0xc, 0xa4, du->x448);
                PR3(0xc, 0xe0, du->x452);
                PR3(0xc, 0xfe, du->x458);
            } else {
                PRS(0xc, 0xa4, 1, "\x81|\x81|");
                PRS(0xc, 0xe0, 1, "\x81|\x81|");
                PRS(0xc, 0xfe, 1, "\x81|\x81|");
            }
        }
        fn_801BCA94();
        Name(au, 0x3e, 0x40, 93.0f);
        fn_801BCA94();
        Name(du, 0x142, 0x144, 93.0f);
        fn_801BCA94();
        n3 = fn_80110F08(fn_80030CF4(au));
        n4 = fn_80110F08(fn_80030CF4(du));
        if (fn_80030CF4(au)->data) PRS(0x22, 0x56, 1, n3);
        if (fn_80030CF4(du)->data) PRS(0x22, 0x15a, 1, n4);
        if (au->x476 > 0) AR(U, 3, 88.0f - v, 5);
        if (au->x476 < 0) AR(D, 4, 94.0f + v, 6);
        if (du->x476 > 0) AR(U, 3, 348.0f - v, 7);
        if (du->x476 < 0) AR(D, 4, 354.0f + v, 8);
        Icon(au, 0, 0x56);
        Icon(du, 1, 0x15a);
    }
    fn_8007E154();
    fn_8007E7DC(0xff);
    fn_8007E164();
}
void fn_8003DD6C(Arw* o, int sh, int x, int y, int alpha) { char buf[0x60]; Pt4 cp; int xs[4]; C4 c; void* tex; int show; body(o, sh, x, y, alpha, show, buf, cp, xs, c, tex); }
}
