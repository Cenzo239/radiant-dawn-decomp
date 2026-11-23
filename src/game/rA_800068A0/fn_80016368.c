#include "game/rA_800068A0/types.h"

/* Particle/trail material drawing (draws 0x4C-byte particles through the GX
 * FIFO) and the per-segment draw loop. */

typedef struct Vec { f32 x, y, z; } Vec;
typedef f32 Mtx[3][4];

#define GXFIFO_F32 (*(volatile f32*)0xCC008000)
#define GXFIFO_U8 (*(volatile u8*)0xCC008000)

typedef struct Part {
    Vec p;        /* 0x00 */
    Vec v;        /* 0x0C */
    f32 age;      /* 0x18 */
    f32 x1C;
    f32 size;     /* 0x20 */
    u8 pad24[8];
    u8 r, g, b, a;/* 0x2C */
    u8 pad30[0x1C];
} Part;

typedef struct Seg {
    u8 pad0[6];
    u16 flags;    /* 0x06 */
    u8 pad8[2];
    s16 mat;      /* 0x0A */
    u8 padC[0x10];
    u16 node;     /* 0x1C */
    u16 count;    /* 0x1E */
    s16 s20, s22; /* unused here */
    u8 pad24[0x10];
} Seg;

typedef struct NodeF {
    u8 pad[0xC];
    u32 flags;
} NodeF;

#if TARGET_PC
extern FE10_PROTO void fn_8000FBA0(void *, Mtx);
#else
extern void fn_8000FBA0(int, Mtx);
#endif
extern void fn_8001E9E4(const Mtx, Vec*);
extern void fn_803128AC(Mtx, f32, f32, f32);
extern void fn_80312378(const Mtx, const Mtx, Mtx);
extern void fn_8001E70C(const Mtx, Mtx);
extern void* fn_8000FB88(void);
extern void fn_80312444(const void*, Mtx);
extern void fn_8001E694(const Mtx, Mtx);
extern void fn_8001E8E8(const Mtx, Mtx);
extern void fn_80312344(const Mtx, Mtx);
extern void fn_8001E6AC(const Mtx, Mtx);
extern void fn_80312494(const Mtx, Mtx);
extern void fn_80312318(Mtx);

void fn_80016368(Seg* s, const NodeF* n, Mtx src, Mtx out) {
    Mtx a;
    Mtx b;
    Mtx c;
    Mtx d;
    Mtx e;
    Mtx f;
    Vec t;
    u32 fl = n->flags;
    if (fl & 0x10000) {
        fn_8000FBA0(0, e);
        fn_8001E9E4(src, &t);
        fn_803128AC(f, -t.x, -t.y, -t.z);
        fn_80312378(e, f, out);
    } else if (s->flags & 0x20) {
        switch (fl & 0x1C0000) {
        case 0xC0000:
            fn_8001E70C(src, b);
            fn_80312444(fn_8000FB88(), d);
            fn_80312378(d, b, a);
            fn_8001E694(src, c);
            fn_80312378(c, a, out);
            break;
        case 0x100000:
            fn_8001E8E8(src, b);
            fn_80312378(src, b, out);
            break;
        default:
            fn_80312344(src, out);
            break;
        }
    } else {
        switch (fl & 0x1C0000) {
        case 0xC0000:
            fn_8001E6AC(src, c);
            fn_8001E70C(src, b);
            fn_80312378(b, c, a);
            fn_80312444(fn_8000FB88(), d);
            fn_80312378(d, a, a);
            fn_8001E694(src, c);
            fn_80312378(c, a, out);
            break;
        case 0x100000:
            fn_80312494(src, c);
            fn_8001E8E8(src, b);
            fn_80312378(b, c, a);
            fn_80312378(src, a, out);
            break;
        default:
            fn_80312318(out);
            break;
        }
    }
}

typedef struct Tex { u16 x0; u8 pad2; u8 x3; } Tex;
typedef struct MatF {
    u8 pad[4];
    u16 flags;
    u8 x6;
    u8 x7;
    u8 pad8[0xC];
    Tex* tex;
} MatF;
typedef struct Anim { s32 x0; } Anim;
typedef struct Key { u8 pad[0xA]; s16 id; } Key;

extern void fn_80012268(void);
extern u32 fn_80011E28(void);
extern u32 fn_80011F38(void);
extern u32 fn_80011EB4(void);
extern void* fn_80012308(void*, Tex*);
extern void fn_80022254(void*, int);
extern void fn_80021CB4(int, int, int, int);
extern void fn_80021EF8(int, int);
extern void fn_80021E20(int, int, int, int, int);
extern void fn_80021D18(int, int, int, int, int, int);
extern void fn_80021E8C(int, int, int, int, int);
extern void fn_80021D9C(int, int, int, int, int, int);
extern int fn_8000B3C8(Anim*, s16, f32*, f32);
extern int fn_8000AE38(Anim*, s16, f32*, f32);
extern int fn_8000B100(Anim*, s16, f32*, f32);
extern int fn_8000B690(Anim*, s16, f32*, f32);
extern int fn_8000B958(Anim*, s16, f32*, f32);
extern void fn_80021F7C(int, int, int, int);
extern void fn_80014158(MatF*, Mtx);
extern u32 fn_80011EAC(void);
extern u32 fn_80011FBC(void);
extern u32 fn_800120CC(void);
extern void fn_80021BF4(u8);
extern void fn_80021C34(u8);
extern void fn_80021C74(u8);

int fn_80016568(Key* k, MatF* m, void* b, Anim* an) {
    int r;
    int st;
    int c;
    int t;
    Tex* tex;
    fn_80012268();
    r = 0x3C;
    st = fn_80011E28();
    c = fn_80011F38();
    t = fn_80011EB4();
    tex = m->tex;
    fn_80022254(fn_80012308(b, tex), t);
    fn_80021CB4(st, c, t, 4);
    switch (tex->x3) {
    case 0:
        fn_80021EF8(st, 0);
        break;
    case 7:
        fn_80021E20(st, 0xF, 0xF, 0xF, 0xA);
        fn_80021D18(st, 0, 0, 0, 1, 0);
        fn_80021E8C(st, 7, 4, 5, 7);
        fn_80021D9C(st, 0, 0, 0, 0, 0);
        break;
    }
    if (!(tex->x0 & 1)) {
        r = 0x1E;
    } else if (an != 0 && an->x0 != 0) {
        f32 v = 0.0f;
        s16 id = k->id;
        if (fn_8000B3C8(an, id, &v, 0.0f) != 0) r = 0x1E;
        if (fn_8000AE38(an, id, &v, 0.0f) != 0) r = 0x1E;
        if (fn_8000B100(an, id, &v, 0.0f) != 0) r = 0x1E;
        if (fn_8000B690(an, id, &v, 0.0f) != 0) r = 0x1E;
        if (fn_8000B958(an, id, &v, 0.0f) != 0) r = 0x1E;
    }
    fn_80021F7C(c, 1, 4, r);
    if (m->flags & 0x40) {
        Mtx mt;
        fn_80312318(mt);
        fn_80014158(m, mt);
    }
    fn_80021BF4(fn_80011EAC());
    fn_80021C34(fn_80011FBC());
    fn_80021C74(fn_800120CC());
    return r;
}

static inline void gxPos3(f32 x, f32 y, f32 z) {
    GXFIFO_F32 = x;
    GXFIFO_F32 = y;
    GXFIFO_F32 = z;
}
static inline void gxCol4(u8 r, u8 g, u8 b, u8 a) {
    GXFIFO_U8 = r;
    GXFIFO_U8 = g;
    GXFIFO_U8 = b;
    GXFIFO_U8 = a;
}

extern void* fn_80007EE4(void*);
extern void fn_80021B68(int);
extern void fn_803031CC(void);
extern void fn_80302B80(int, int);
extern void fn_80303200(int, int, int, int, int);
extern void fn_80307E48(void*, int);
extern void fn_80021784(int);
extern void* fn_8000F3D4(void*, u16);
extern void fn_80312DB4(const Mtx, const void*, void*);
extern void fn_8030456C(u8, int);
extern void fn_80304314(int, int, int);
extern void fn_803045A0(int, int, int);

typedef struct MatH { u8 pad[6]; u8 x6; u8 pad7[0xD]; Tex* tex; } MatH;

void fn_800170B8(void* a, Seg* s, Part* p, MatH* m, void* x) {
    void* res = fn_80007EE4(a);
    Mtx mv;
    Vec v;
    int i;
    fn_80021B68(0);
    fn_803031CC();
    fn_80302B80(9, 1);
    fn_80302B80(0xB, 1);
    fn_80303200(0, 9, 1, 4, 0);
    fn_80303200(0, 0xB, 1, 5, 0);
    fn_80307E48(fn_8000FB88(), 0);
    fn_80021784(0);
    fn_80016368(s, fn_8000F3D4(res, s->node), mv, mv);
    if (m->x6 != 0) {
        fn_80022254(fn_80012308(x, m->tex), 0);
        fn_80302B80(0xD, 1);
        fn_80303200(0, 0xD, 1, 4, 0);
        fn_80021C34(1);
        fn_80021BF4(1);
        fn_80021F7C(0, 1, 4, 0x3C);
        fn_80021CB4(0, 0, 0, 4);
        fn_80021EF8(0, 0);
        fn_803045A0(0, 0, 1);
    } else {
        fn_80021C34(0);
        fn_80021BF4(1);
        fn_80021CB4(0, 0xFF, 0xFF, 4);
        fn_80021EF8(0, 4);
    }
    for (i = 0; i < s->count; i++, p++) {
        if (!(p->age < 0.0f) && p->a != 0) {
            fn_80312DB4(mv, p, &v);
            fn_8030456C(6.0f * p->size, 5);
            fn_80304314(0xB8, 0, 1);
            gxPos3(v.x, v.y, v.z);
            gxCol4(p->r, p->g, p->b, p->a);
            if (m->x6 != 0) {
                GXFIFO_F32 = 0.0f;
                GXFIFO_F32 = 0.0f;
            }
        }
    }
}

static inline f32 fx6f(s16 v) { return 0.015625f * v; }
extern void fn_8001E6D0(const Mtx, Mtx);
extern void fn_80304538(u8, int);

void fn_80017344(void* a, Seg* s, Part* p);

typedef struct AnimInfo { u8 pad[6]; u16 n; Seg segs[1]; } AnimInfo;
typedef struct AnimState { u8 pad[0x30]; AnimInfo* info; u8* buf; } AnimState;
typedef struct GAct { u8 pad[0x54]; AnimState* s; } GAct;
typedef struct ResM { u8 pad[0x34]; u8* mats; } ResM;
typedef struct BufE { u8 pad[0xC]; Part* parts; u8 pad10[4]; } BufE;
typedef struct MatX { u8 pad[4]; u16 x4; u8 pad6; u8 x7; } MatX;

extern ResM* fn_80007F3C(GAct*);
extern void fn_80007F10(GAct*);
extern void* fn_800080B8(GAct*);
extern void* fn_80007F68(GAct*);
extern void fn_800184BC(GAct*, int);
extern int fn_8001883C(MatX*);
extern void fn_80021B2C(int);
extern void fn_80021A08(int, int, int, int, int, int, int);
extern void fn_800186C8(MatX*);
extern void fn_800167B0(GAct*, BufE*, Seg*, MatX*, void*);
extern void fn_8001762C(GAct*, BufE*, Seg*, MatX*, void*);
extern void fn_80018684(GAct*, int);
extern Vec lbl_80360DEC;

void fn_80017B08(GAct* a) {
    ResM* res = fn_80007F3C(a);
    u8* nodes;
    AnimInfo* info;
    Seg* s;
    BufE* b;
    void* x;
    MatX* last;
    int i;
    fn_80007F10(a);
    nodes = fn_800080B8(a);
    info = a->s->info;
    b = (BufE*)a->s->buf;
    s = info->segs;
    x = fn_80007F68(a);
    fn_800184BC(a, 3);
    last = 0;
    for (i = 0; i < info->n; i++, s++, b++) {
        MatX* m = (MatX*)(res->mats + (s->mat << 5));
        if (last != 0 && last->x4 != m->x4) {
            if (fn_8001883C(last) != 0) {
                fn_800184BC(a, 3);
            }
        }
        if (!(m->x7 & 0x10)) {
            Vec v;
            Mtx t;
            v = lbl_80360DEC;
            fn_8001E6D0((void*)(nodes + s->node * 0x30), t);
            fn_80312DB4(t, &v, &v);
            if (0.0f != v.x * v.x + v.y * v.y + v.z * v.z) {
                fn_80021B2C(1);
                fn_80021A08(0, 0, 0, 1, 0, 0, 2);
                fn_80021A08(2, 0, 1, 1, 0, 0, 2);
                fn_800186C8(m);
                last = m;
                switch (s->flags & 7) {
                case 1:
                    fn_800170B8(a, s, b->parts, (MatH*)m, x);
                    break;
                case 2:
                    fn_80017344(a, s, b->parts);
                    break;
                case 3:
                    break;
                case 4:
                    fn_800167B0(a, b, s, m, x);
                    break;
                case 5:
                    fn_8001762C(a, b, s, m, x);
                    break;
                }
            }
        }
    }
    fn_8001883C(last);
    fn_80018684(a, 3);
    fn_80012268();
}

static inline f32 fpow(f32 b, f32 s, int n) {
    int i;
    for (i = 1; i < n; i++) {
        s *= b;
    }
    return s;
}

f32 fn_8001EBC8(f32 a, f32 b, f32 x, f32 y, int n);

f32 fn_8001ECE4(f32 a, f32 b, f32 x, f32 y, int n);

extern void fn_80313484(const void*, const void*, Vec*);
extern f32 fn_80313508(const Vec*);

void fn_8001F0A4(Vec* a, Vec* b, Vec* c, Vec* d) {
    Vec v;
    f32 len;
    fn_80313484(c, b, &v);
    len = fn_80313508(&v);
    if (len > 0.0f) {
        f32 l;
        fn_80313484(b, a, &v);
        l = fn_80313508(&v);
        if (l > 0.0f) {
            f32 k = len / l;
            a->x = b->x - v.x * k;
            a->y = b->y - v.y * k;
            a->z = b->z - v.z * k;
        }
        fn_80313484(c, d, &v);
        l = fn_80313508(&v);
        if (l > 0.0f) {
            f32 k = len / l;
            d->x = c->x - v.x * k;
            d->y = c->y - v.y * k;
            d->z = c->z - v.z * k;
        }
    }
}

typedef struct RMode { u8 pad[0x19]; u8 x19; u8 a1A[0x18]; u8 a32[7]; } RMode;
extern RMode* fn_802356AC(void);
extern void fn_80304CEC(int, u8*, int, u8*);
extern void fn_803047B0(u16, u16, u16, u16);
extern void fn_80304814(u16, u16, int, int);
#if TARGET_PC
extern FE10_PROTO void fn_80305020(void *, u8);
#else
extern void fn_80305020(int, u8);
#endif
extern void fn_80303D74(void);
extern void fn_803061BC(void);

#pragma use_lmw_stmw on
void fn_8001F4D8(
#if TARGET_PC
int x, int y, int w, int h, int dw, int dh, void* t, int fmt, u8 clr
#else
int x, int y, int w, int h, int dw, int dh, int t, int fmt, u8 clr
#endif
) {
    RMode* m = fn_802356AC();
    if (dw < 0) {
        dw = w;
    }
    if (dh < 0) {
        dh = h;
    }
    fn_80304CEC(0, m->a1A, 0, m->a32);
    fn_803047B0(x, y, w, h);
    fn_80304814(dw, dh, fmt, w != dw || h != dh);
    fn_80305020(t, clr);
    fn_80304CEC(m->x19, m->a1A, 1, m->a32);
    fn_80303D74();
    fn_803061BC();
}
#pragma use_lmw_stmw off

typedef struct PKey { s16 x0, y0, z0, x, y, z; } PKey;
typedef struct PSeg {
    u8 pad[6];
    u16 flags;
    u8 pad8[0x18];
    PKey* keys;       /* 0x20 */
    u8 pad24[0x10];
} PSeg;
typedef struct PBuf {
    f32 cur;
    f32 delta;
    s16 lo, hi;
    Part* parts;
    u8 pad10[4];
} PBuf;
typedef struct PInfo { u8 pad[6]; u16 n; PSeg segs[1]; } PInfo;
typedef struct PState { u8 pad[0x30]; PInfo* info; PBuf* buf; } PState;
typedef struct PActor { u8 pad[0x54]; PState* s; f32 x58; f32 x5C; } PActor;

extern f32 fn_800081B4(PActor*);

void fn_800156C8(PActor* a);
