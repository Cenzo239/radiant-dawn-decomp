/* Small leaf functions and one-line wrappers across the region. */
#include "game/rL_80133EB4/types.h"
#pragma auto_inline off

extern "C" {

struct Color { u8 r, g, b, a; };
extern u8 lbl_804CB830;
extern u8 lbl_804CB839;
extern u8 lbl_804CB83A;
extern u8 lbl_804CB83B;
extern Color lbl_804CB83C;
extern u8 lbl_804CB834;
extern u32 lbl_804CB700;

struct Sc;
extern Sc* lbl_804CB860;
#if TARGET_PC
#if TARGET_PC
extern FE10_PROTO int fn_80135C44(void*, void*, void*, int);
#else
extern FE10_PROTO void fn_80135C44(void*, p32arg, p32arg, int);
#endif
#else
extern void fn_80135C44(void*, int, int, int);
#endif
extern void fn_8013A054(Sc*);
extern void fn_80078E24(void*);
extern void fn_8013CE9C(void*);
extern void fn_8013D404(void*);
extern void fn_8013D7B4(void*);
extern void fn_80143D88(void*);
extern void fn_80144938(void*);
extern void fn_80145704(void*);
extern void fn_80146554(void*);
extern void fn_80082230(void*);
extern void fn_8012D908(void);
extern void fn_8013BEE4(void*);
extern void fn_80081A90(void*);
#if TARGET_PC
extern FE10_PROTO void* fn_80081050(void*, p32arg);
#else
extern void* fn_80081050(void*, int);
#endif
extern void fn_800846BC(void*);
extern void fn_80083DC4(void*, int);
extern void* fn_800811E4(void*, void*);
extern void fn_800E24F8(void*);
extern void fn_801379F8(Sc*, int);
extern void fn_80146BAC(void*, int);
extern void fn_80146B40(void*);
#if TARGET_PC
extern FE10_PROTO void fn_8013BC74(void*, ptr32<const void>);
#else
extern void fn_8013BC74(void*, void*);
#endif
extern void fn_801CA4FC(void*, int);
extern void fn_801CA568(void*, int);
extern void fn_80010788(int, int, void*, void*);
extern void fn_8013F3D8(void);
extern void fn_801402B8(void*);
extern void fn_8013FCE8(void*, int, int);
#if TARGET_PC
extern FE10_PROTO void fn_8014021C(void*, p32arg);
#else
extern void fn_8014021C(void*, int);
#endif
extern void fn_8013FC20(void*, int);
extern void fn_80011274(void);
#if TARGET_PC
extern FE10_PROTO void fn_80011280(p32arg);
#else
extern void fn_80011280(int);
#endif
extern int fn_80011E80(void);
#if TARGET_PC
extern FE10_PROTO void fn_80141334(p32arg);
#else
extern void fn_80141334(int);
#endif
extern void fn_8001D424(void*);
#if TARGET_PC
extern FE10_PROTO void fn_8013602C(Sc*, p32arg, void*);
#else
extern void fn_8013602C(Sc*, int, void*);
#endif
extern void fn_801444B8(void);
extern void fn_80147EF4(int);
extern void* fn_80083B84(void*);
extern void fn_800068EC(void*, void*, int);
extern void fn_8023F1A0(void*, int);
extern void fn_8023F880(void*);
extern void fn_800C835C(u8, int);

extern u8 lbl_80386158[];
extern u8 lbl_80386174[];
extern u8 lbl_803861A0[];
extern u8 lbl_803697B4[];
extern u8 lbl_80386320[];
extern u8 lbl_8038634C[];
extern u8 lbl_80386378[];
extern u8 lbl_803863E8[];
extern u8 lbl_80386468[];
extern u8 lbl_80386698[];
extern u8 lbl_803866C0[];
extern u8 lbl_80369BBC[];
extern void* lbl_804CB868;
extern void* lbl_804CB86C;
extern void* lbl_804CB880;
extern f32 lbl_804CB854;
extern f32 lbl_804CB858;

struct Cam { u8 pad0[8]; f32 x8; u8 padC[4]; f32 x10; };
extern Cam* lbl_804CB85C;

void fn_80134E90(u8 x) { lbl_804CB830 = x; }

void fn_80134E98(
#if TARGET_PC
u8 a, u8 b, u8 c, Color d
#else
u8 a, u8 b, u8 c, const Color& d
#endif
) {
    lbl_804CB839 = a;
    lbl_804CB83A = b;
    lbl_804CB83B = c;
    lbl_804CB83C = d;
}

struct T50 { u8 pad0[8]; struct N50* n; u8 padC[0x50 - 0xC]; s16 cnt; s16 cnt52; };
struct N50 { u8 pad0[0xB8]; u32 flags; u8 padBC[4]; };

u8 fn_8013554C(u8* p) { return p[0xB0]; }

int fn_801357C8(T50* p, u32 m) {
    int i;
    N50* n = p->n;
    for (i = 0; i < p->cnt; i++) {
        if (n->flags & m) return 1;
        n++;
    }
    return 0;
}

#if TARGET_PC
int fn_80135F88(void* a, void* b, void* c) { return fn_80135C44(a, b, c, 0); }
#else
void fn_80135F88(void* a, int b, int c) { fn_80135C44(a, b, c, 0); }
#endif

f32 fn_80138698(void) {
    Cam* c = lbl_804CB85C;
    f32 n = c->x10;
    f32 d = c->x8;
    return n / d;
}

struct E18 { u8 pad0[0x14]; void* key; };
struct T114 { u8 pad0[0x114]; E18 e[16]; };

E18* fn_8013A890(T114* t, void* key) {
    E18* e;
    int i;
    if (key) {
        e = t->e;
        for (i = 0; i < 16; i++) {
            if (e->key == key) return &t->e[i];
            e++;
        }
    }
    return 0;
}

struct T1C { u8 pad0[0x1C]; void* tbl[8]; u32 w[4]; };

void fn_8013B1F4(T1C* t) {
    int i;
    for (i = 0; i < 8; i++) t->tbl[i] = 0;
}

void fn_8013B21C(T1C* t, void* x) {
    int i;
    for (i = 0; i < 8; i++) {
        if (t->tbl[i] == x) return;
        if (t->tbl[i] == 0) {
            t->tbl[i] = x;
            return;
        }
    }
}

void* fn_8013B260(T1C* t, int i) { return t->tbl[i]; }

void fn_8013B270(T1C* t) {
    int i;
    for (i = 0; i < 4; i++) t->w[i] = 0;
}

struct M0D { u8 pad0[0x14]; u32 flags; u8 pad18[0xD0 - 0x18]; };
struct T0D { u8 pad0[0xC]; M0D* m; u8 pad10[0x52 - 0x10]; s16 n; };

void fn_8013B288(T0D* t, u32 x) {
    M0D* m = t->m;
    int i;
    for (i = 0; i < t->n; i++) {
        m->flags ^= x;
        m++;
    }
}

struct O31 { u8 pad0[0x31]; u8 x31; };
struct H18 { u8 pad0[0x18]; O31* o; };

static inline void O31Draw(O31* o, int mode) {
    if (mode != o->x31) fn_80146BAC(o, mode);
    fn_80146B40(o);
}

void fn_8013B974(void) {
    fn_8013A054(lbl_804CB860);
    fn_80078E24(lbl_804CB860);
    lbl_804CB860 = 0;
}

Sc* fn_8013B9A8(void) { return lbl_804CB860; }

struct Sc { u8 pad0[0x10]; u32 x10; u8 pad14[0x60 - 0x14]; u8 x60; u8 pad61[0xB4 - 0x61]; u32 pad_b0_bit31 : 1; u32 bit30 : 1; };

u32 fn_8013B9B0(void) {
    Sc* s = lbl_804CB860;
    if (s == 0) return 0;
    return s->x10;
}

u32 fn_8013B9CC(void) {
    Sc* s = lbl_804CB860;
    if (s == 0) return 0;
    return s->bit30;
}

void fn_8013BE60(void) {
    Sc* s = fn_8013B9A8();
    if (s) fn_801379F8(s, 0);
}

void fn_8013BE90(void* x, int parent) {
    if (parent == 0) parent = 3;
    fn_8013BC74(fn_80081050(lbl_80386158, parent), x);
}

void fn_8013BED8(void) { fn_800846BC(lbl_80386158); }

void fn_8013C148(void* p) { fn_8013BEE4(p); }

void fn_8013C200(void) { fn_800846BC(lbl_80386174); }

struct P18 { u8 pad0[0x18]; void* x18; };
void fn_8013C20C(P18* p) {
    if (lbl_804CB700 & 0x8001) fn_80081A90(p->x18);
}

void fn_8013C224(int parent) { fn_80081050(lbl_803861A0, parent); }

void fn_8013C9CC(void) { fn_800E24F8(lbl_803697B4 + 0x10); }

int fn_8013CC7C(void* p) {
    fn_80083DC4(p, 1);
    return 1;
}

void fn_8013DA14(void* p) { fn_8013CE9C(p); }
void fn_8013DA18(void* p) { fn_8013D404(p); }
void fn_8013DA1C(void* p) { fn_8013D7B4(p); }

struct W70 { u8 pad0[0x30]; u8* w[16]; int n; u32 x74; };
void fn_8013DD44(W70* p) {
    int i;
    p->x74 = 0;
    for (i = 0; i < p->n; i++) {
        p->w[i][0] &= ~0xC;
    }
}

struct P30 { u8 pad0[0x30]; void* x30; };

void fn_8013E014(P30* p) {
    if (fn_8013B9CC()) fn_801CA4FC(p->x30, 1);
}

void fn_8013E054(void* x, void* parent) { ((P30*)fn_800811E4(lbl_80386320, parent))->x30 = x; }

void fn_8013E158(P30* p) {
    if (fn_8013B9CC()) fn_801CA568(p->x30, 1);
}

void fn_8013E198(void* x, void* parent) { ((P30*)fn_800811E4(lbl_8038634C, parent))->x30 = x; }

void fn_8013E1D0(void) { fn_800E24F8(lbl_803697B4 + 0xA4); }

void fn_8013E314(void* x, void* parent) { ((P30*)fn_800811E4(lbl_80386378, parent))->x30 = x; }

void fn_8013F138(void) {}

void fn_8013F1C4(void) {
    P30* p = (P30*)fn_80081050(lbl_803863E8, 4);
    p->x30 = 0;
    lbl_804CB700 |= 0x400;
}

void fn_8013F204(void) {
    fn_800846BC(lbl_803863E8);
    lbl_804CB700 &= ~0x400;
}

void fn_8013F808(void) { fn_80010788(3, 0x91, fn_8013F3D8, 0); }

extern u8 lbl_80413C48[];

void fn_8014083C(u8 a, u8 b, u8 c) {
    lbl_80413C48[0] = a;
    lbl_80413C48[0x40] = b;
    lbl_80413C48[0x80] = c;
    lbl_80413C48[0xC0] = 0x14;
    lbl_80413C48[0x100] = 0;
}

void fn_80140864(s8 a, s8 b) { fn_8013FCE8(lbl_80413C48, a, b); }

void fn_80140880(void) { fn_80010788(3, 0x92, fn_801402B8, lbl_80413C48); }

void fn_8014089C(int a) { fn_8014021C(lbl_80413C48, a); }

void fn_801408AC(s8 a) { fn_8013FC20(lbl_80413C48, a); }

void fn_80140B58(void) {
    if (lbl_804CB868) {
        fn_80081A90(lbl_804CB868);
        lbl_804CB868 = 0;
    }
    if (lbl_804CB86C) {
        fn_80081A90(lbl_804CB86C);
        lbl_804CB86C = 0;
    }
}

struct P14 { u8 pad0[0x14]; u8* x14; };
void fn_80143464(void) {
    fn_80011274();
    fn_80011280(0);
}

void fn_801435A4(void) {
    Sc* s = fn_8013B9A8();
    if (s && (s->x60 & 1)) {
        fn_80141334(fn_80011E80());
    }
}

void fn_801435E0(void* p) { fn_80143D88(p); }

void
#if TARGET_PC
*
#endif
fn_801436DC(
#if TARGET_PC
void* parent
#else
int parent
#endif
) {
#if TARGET_PC
return fn_80081050(lbl_80386468, parent);
#else
fn_80081050(lbl_80386468, parent);
#endif
}

struct P38 { u8 pad0[0x38]; void* x38; };
void fn_801442E0(P38* p) {
    fn_8013602C(fn_8013B9A8(), 0, fn_801444B8);
    fn_8001D424(p->x38);
}

void fn_80144BA8(void* p) { fn_80144938(p); }
void fn_8014597C(void* p) { fn_80145704(p); }
void fn_801469BC(void* p) { fn_80146554(p); }

void fn_801469C0(P30* p) {
    if (p->x30) fn_80081A90(p->x30);
}

void fn_80146A44(void* p) { fn_80082230(p); }
void fn_80146A48(void) {}

struct P3C { u8 pad0[0x3C]; u32 x3C; };
void fn_80146EBC(P3C* p) { p->x3C = 0; }

struct Q58 { u8 pad0[0x31]; u8 x31; u8 pad32[0x58 - 0x32]; f32 x58; u8 pad5C[0x64 - 0x5C]; f32 x64; };
void fn_80146FBC(Q58* q, f32 d) {
    switch (q->x31) {
    case 7:
    case 8:
    case 9:
    case 0x13:
        q->x58 += d;
        q->x64 += d;
    }
}

struct PA4 { u8 pad0[0x30]; struct PA4b* p; };
struct PA4b { u8 pad0[0xA4]; struct PA4c* c; };
struct PA4c { u8 pad0[0x4C]; u32 x4C; };
void fn_80147148(PA4* p) { p->p->c->x4C = 0; }

void fn_801482F8(void) { fn_80147EF4(0x80); }

struct P60 { u8 pad0[0x60]; u32 x60; };
void fn_80148300(P60* p) { p->x60 = 0; }

void fn_801484B0(void) { fn_8012D908(); }

int fn_8014852C(void) {
    if (fn_80083B84(lbl_80386698)) return 1;
    return fn_80083B84(lbl_803866C0) != 0;
}

void* fn_801485FC(void) { return lbl_804CB880; }

void fn_80148604(void) { fn_800068EC(&lbl_804CB880, lbl_80369BBC, 0x80); }
void fn_80148618(void) { fn_8023F1A0(lbl_80369BBC, 0x80); }
void fn_80148628(void) { fn_8023F880(lbl_80369BBC); }

struct S2 { u8 pad0[0x1C]; u8 pad1C[0x19C - 0x1C]; s8 x19c[0x200 - 0x19C]; s8 x200; u8 pad201[7]; u32 x208[5]; u32 x21C[9]; u32 x240; };

u32 fn_8014A4C8(u8* p) {
    int i = (s8)p[0x200];
    if (i < 0) return 0;
    i = (s8)(p + i)[0x19C];
    if (i < 0) return 0;
    return *(u32*)(p + 0x208 + i * 4);
}

u32 fn_8014A578(u8* p) {
    if (p[0x1E8] != 0) return *(u32*)(p + 0x21C);
    if (*(u32*)(p + 0x240) == 0) return *(u32*)(p + 0x21C);
    return *(u32*)(p + 0x240);
}

void fn_8014ADCC(u8* p, int i) {
    if (p[0x1E8] != 0) return;
    *(u32*)(p + 0x240) = *(u32*)(p + 0x21C + i * 4);
}

u8* fn_8014ADEC(u8* p) { return p + (s8)p[0x200] * 0x18 + 0x1C; }

extern u8 lbl_804181AC[];
void fn_8014B544(void) { fn_800C835C(lbl_804181AC[0x1F2], 0x320); }

u32 fn_8014C828(void) { return *(u32*)(lbl_804181AC + 0x14); }

void fn_8014C598(void) {}
void fn_8014C838(void) {}

} /* extern "C" */
