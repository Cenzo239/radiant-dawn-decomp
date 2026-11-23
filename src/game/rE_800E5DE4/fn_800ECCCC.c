#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off

typedef struct BSeq { u8 pad[2]; s16 kind; } BSeq;

typedef struct BtlProc {
    u8 pad[0x30];
    BSeq* seq;    /* 0x30 */
    Handle* h1;   /* 0x34 */
    Handle* h2;   /* 0x38 */
    void* v3C;    /* 0x3C */
    u8 b40;       /* 0x40 */
    u8 b41;       /* 0x41 */
    u8 b42;       /* 0x42 */
    u8 b43;       /* 0x43 */
    u8 pad44[3];
    s8 b47;       /* 0x47 */
    s8 b48;       /* 0x48 */
    s8 b49;       /* 0x49 */
} BtlProc;

typedef struct Ctl {
    u8 pad[0xA4];
    BtlProc* a;   /* 0xA4 */
    void* b;      /* 0xA8 */
    u8 padAC[8];
    s32 d;        /* 0xB4 */
} Ctl;
typedef struct Cmd { u8 pad[0x30]; Ctl* ctl; } Cmd;

typedef struct Popup {
    u8 pad[0x30];
    void* font;   /* 0x30 */
    Vec pos;      /* 0x34 */
    u8 pad40[8];
    f32 f48;      /* 0x48 */
    u8 pad4C[4];
    s32 alpha;    /* 0x50 */
    s32 y;        /* 0x54 */
    s32 n;        /* 0x58 */
} Popup;

typedef struct Fade {
    u8 pad[0x30];
    Handle* h;    /* 0x30 */
    s32 t;        /* 0x34 */
    s32 n;        /* 0x38 */
    u8 pad3C[4];
    f32 from;     /* 0x40 */
    f32 to;       /* 0x44 */
} Fade;

extern u8 lbl_803672A0[];
extern u8 lbl_80367458[];
extern u8 lbl_803C8E80[];
typedef struct Cfg { u8 pad[0x13]; s8 x; s8 y; } Cfg;
extern Cfg lbl_803CA870;
extern GXColor lbl_804CD9F8[1];
extern const f32 lbl_804CD9B8;
extern const f32 lbl_804CD9C0;
extern const f32 lbl_804CD9C8;
extern const f32 lbl_804CDA10;
extern const f32 lbl_804CDA14;
extern const f32 lbl_804CDA18;
#if TARGET_PC
extern FE10_PROTO char ** fn_801CE474(Handle*);
#else
extern int fn_801CE474(Handle*);
#endif
extern u32 fn_801125B4(void);
extern void fn_80103374(void*, GXColor*, void*);
#if TARGET_PC
extern FE10_PROTO void fn_80102928(void*, int, int, int, void *);
extern FE10_PROTO void fn_80102D70(void*, char*, void *, void *);
#else
extern void fn_80102928(void*, int, int, int, int);
extern void fn_80102D70(void*, char*, int, int);
#endif
extern Vec fn_800D5B4C(Handle*);
extern void fn_800E59CC(Cmd*, Vec*, Vec*);
extern void fn_800E5BC0(Cmd*, UnitObj*, UnitObj*);
extern void fn_800F4284(void*, char*);
extern int fn_801CFCE0(BSeq*);
extern int fn_801CFC0C(BSeq*);
extern void fn_800EBB74(BtlProc*);
extern void fn_800EB988(BtlProc*);
extern void fn_800EBE80(BtlProc*);
extern void fn_800EFEB8(Handle*, int, BtlProc*);
extern Vec fn_800D5C44(Handle*);
extern void fn_800EE61C(Vec*, int, BtlProc*);
extern void fn_80103234(void*, int, int, BtlProc*);
extern void* fn_800D68BC(void);
extern void fn_801CE800(void*);
extern Handle* fn_801D0784(void*, int);
#if TARGET_PC
extern FE10_PROTO int fn_801D04AC();
#else
extern void* fn_801D04AC(void*);
#endif
#if TARGET_PC
extern FE10_PROTO void fn_800D619C(Handle*, int);
#else
extern void fn_800D619C(Handle*, void*);
#endif
extern void fn_80103304(void*, BtlProc*);
#if TARGET_PC
extern FE10_PROTO void * fn_8013B9A8(void);
extern FE10_PROTO void* fn_80135800(void *, int, int, int, int);
#else
extern int fn_8013B9A8(void);
extern void* fn_80135800(int, int, int, int, int);
#endif
extern int fn_800D7D74(void);
extern void fn_800D6624(void*);
#if TARGET_PC
extern FE10_PROTO void fn_80011B90(void *, Vec*, Vec*);
#else
extern void fn_80011B90(int, Vec*, Vec*);
#endif
extern void fn_8007E154(void);
extern void fn_8007E164(void);
#if TARGET_PC
extern FE10_PROTO void fn_8007E174(void *, int);
#else
extern void fn_8007E174(int, int);
#endif
extern void fn_8007E4E4(f32, f32, f32, f32);
#if TARGET_PC
extern FE10_PROTO void fn_8007E374(void*, void *, int);
#else
extern void fn_8007E374(void*, int, int);
#endif
extern void fn_8007E7DC(u8);
extern void fn_8007E7F4(void);
extern void fn_80176B54(int, int, int, GXColor*, int, int, int, int, int, int);
extern int fn_800CA3DC(void*, int, f32);
extern void fn_800CB3A8(s16, int, int, int, int, void*, f32, f32, ...);
extern void fn_800800D4(int);
extern void fn_80080430(f32, f32, f32, f32, f32, f32);
extern void fn_80080578(int);
extern void fn_80080308(void);
extern f32 fn_8001EF30(f32, f32, f32, f32);
extern void fn_800D5AF0(Handle*);
extern void fn_80253EE4(char*, f32);
extern void fn_80083B78(void*);

static inline void Cv(GXColor* c, u32 v) {
    c->a = v;
    c->r = v >> 24;
    c->g = v >> 16;
    c->b = v >> 8;
}


void fn_800ECD90(Cmd* c) {
    Ctl* ctl = c->ctl;
    BtlProc* a = ctl->a;
    void* b = ctl->b;
    s32 d = ctl->d;
    switch (a->b40) {
    case 1: {
        Vec x = fn_800D5B4C(a->h1);
        Vec y = fn_800D5B4C(a->h2);
        fn_800E59CC(c, &x, &y);
        break;
    }
    default:
        fn_800E5BC0(c, a->h1->obj, a->h2->obj);
        break;
    }
    if (d == 3) {
        fn_800F4284(b, (char*)lbl_803672A0 + 0x159);
    }
}

static inline void Pop(Vec v, int n, BtlProc* p) { fn_800EE61C(&v, n, p); }

void fn_800ED918(BtlProc* p) {
    Handle* h;
    int i;
    p->b41 = 0;
    p->b47 = -1;
    p->b48 = -1;
    p->b49 = -1;
    p->b43 = 0;
    p->seq = fn_800D68BC();
    fn_801CE800(p->seq);
    for (i = 0; i < 3; i++) {
        void* a;
        h = fn_801D0784(p->seq, i);
        fn_800D619C(h, fn_801D04AC(p->seq));
        a = HandleActor(h);
        if (a) {
            fn_80103304(a, p);
        }
    }
    if (*(u32*)(lbl_803C8E80 + 0x15EC) & 0x40000000) {
        p->b42 = 1;
    } else {
        p->b42 = 0;
    }
    if (*(u32*)(lbl_803C8E80 + 0x15EC) & 0x100) {
        p->b40 = 1;
        {
        int g = fn_8013B9A8();
        if (g) {
            Cfg* c = &lbl_803CA870;
            p->v3C = fn_80135800(g, c->x, c->y, 0x1000, 0x10);
        } else {
            p->v3C = 0;
        }
        }
    } else {
        p->b40 = 0;
    }
    if (fn_800D7D74()) {
        p->b40 = 2;
    }
    fn_800D6624(p->seq);
}

static inline void SC(GXColor* d, GXColor s) { *d = s; }

void fn_800EE798(u8* p, int a, int n, void* s, f32 x, f32 y) {
    if (s) {
        int w;
        if (n > 4) n = 4;
        if (n < 0) n = 0;
        fn_8007E154();
        fn_8007E4E4(x, y, lbl_804CDA10, lbl_804CD9B8);
        fn_8007E174(0, 0x13);
        fn_8007E7DC(a);
        fn_8007E164();
        w = fn_800CA3DC(s, -1, lbl_804CD9B8);
        fn_800CB3A8((0xA4 - w) / 2 + 0x36, 2, 1, 1, 0, s, lbl_804CD9B8, lbl_804CD9C0);
        fn_8007E154();
        fn_8007E4E4(x, y, lbl_804CDA14, lbl_804CD9B8);
        fn_8007E374(*(void**)(p + 0x3C), n, 0x11);
        fn_8007E7DC(a);
        fn_8007E164();
        fn_800800D4(2);
        fn_80080430(lbl_804CD9C0, lbl_804CD9C0, lbl_804CD9C0, lbl_804CD9C0, lbl_804CDA18, lbl_804CD9C8);
        fn_80080578(0);
        fn_80080308();
        fn_8007E7F4();
    }
}

void fn_800EFDB0(Fade* p) {
    p->t++;
    p->h->unk6 = fn_8001EF30(p->from, p->to, (f32)p->n, (f32)p->t);
    fn_800D5AF0(p->h);
    if (p->to > p->from && (p->t & 1)) {
        fn_80253EE4((char*)lbl_80367458 + 0x28, lbl_804CD9C0);
    }
    if (p->t >= p->n) {
        fn_80083B78(p);
    }
}
