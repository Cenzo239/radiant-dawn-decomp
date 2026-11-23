/* fn_800156C8: exact (round m4, m4-c). From equiv/fn_800156C8.c: declarations first, k read before p, len as the only named local. */
/* symcheck: r21 review. Fixed: `k = s->keys` is now read after the two `b->lo/b->hi` resets, as in the original (the
   draft read it before them: a load moved across two stores; harmless unless segs and buf overlap, but now gone). Still
   `sched`, 7 words. Left flagged: block 3 only, an artefact (the two int-to-float temporaries sit in each other's stack
   slot 0x8/0x10; both high words are set in the prologue, the compare and the kept value are the same). */
/* Round 20, functionally equal (check_regs.py: sched): fn_800156C8. Self-contained. fn_80016368.c with exported bodies removed plus the draft from wip/fn_800156C8.c. Moved (harmless): the two int-to-float conversion temporaries use each other's stack slot (0x8/0x10), so their stw/lfd pairs are interleaved differently; before the second inner loop the two sth resets are scheduled before instead of after the lwz of the vertex pointer. */
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

extern void fn_8000FBA0(int, Mtx);
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
void fn_80016368(Seg* s, const NodeF* n, Mtx src, Mtx out);


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
int fn_80016568(Key* k, MatF* m, void* b, Anim* an);


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
void fn_800170B8(void* a, Seg* s, Part* p, MatH* m, void* x);


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
void fn_80017B08(GAct* a);


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
void fn_8001F0A4(Vec* a, Vec* b, Vec* c, Vec* d);


typedef struct RMode { u8 pad[0x19]; u8 x19; u8 a1A[0x18]; u8 a32[7]; } RMode;
extern RMode* fn_802356AC(void);
extern void fn_80304CEC(int, u8*, int, u8*);
extern void fn_803047B0(u16, u16, u16, u16);
extern void fn_80304814(u16, u16, int, int);
extern void fn_80305020(int, u8);
extern void fn_80303D74(void);
extern void fn_803061BC(void);

#pragma use_lmw_stmw on

void fn_8001F4D8(int x, int y, int w, int h, int dw, int dh, int t, int fmt, u8 clr);

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

#pragma use_lmw_stmw off
/* ---- from rA_800068A0/wip/fn_800156C8.c ---- */
/* fn_800156C8: near miss, 47 of 141 words differ. Depends on types and helpers from ../fn_80016368.c; goes there in address order. */
void fn_800156C8(PActor* a) {
    PState* st;
    f32 frame;
    PInfo* info;
    PSeg* s;
    PBuf* b;
    int i;
    st = a->s;
    frame = fn_800081B4(a);
    info = st->info;
    i = 0;
    b = st->buf;
    s = info->segs;
    for (; i < info->n; i++, s++, b++) {
        if (s->flags & 0x10) {
            b->delta = a->x5C;
            b->cur += b->delta;
            {
                f32 len = b->hi - b->lo;
                if (b->cur > b->hi) {
                    b->cur = b->cur - len;
                }
            }
        } else {
            f32 d = frame - b->cur;
            b->delta = d;
            b->cur = frame;
            if (d < 0.0f) {
                Part* p;
                PKey* k = s->keys;
                int j;
                p = b->parts;
                b->cur = a->x58;
                b->delta = 0.0f;
                b->lo = 0;
                b->hi = 0;
                for (j = 0; j < *(u16*)((u8*)s + 0x1E); j++, k = (PKey*)((u8*)k + 0xC), p++) {
                    p->p.x = 0.015625f * k->x;
                    p->p.y = 0.015625f * k->y;
                    p->p.z = 0.015625f * k->z;
                    p->v.x = 0.0f;
                    p->v.y = 0.0f;
                    p->v.z = 0.0f;
                    p->age = -1.0f;
                    p->x1C = 0.0f;
                    p->size = 1.0f;
                    *(f32*)((u8*)p + 0x24) = 1.0f;
                    p->r = 0xFF;
                    p->g = 0xFF;
                    p->b = 0xFF;
                    p->a = 0;
                    ((u8*)p)[0x48] = 0;
                    ((u8*)p)[0x49] = 0;
                }
                if (s->flags & 0x10) {
                    b->lo = 0x2710;
                    b->hi = -0x2710;
                    k = s->keys;
                    for (j = 0; j < *(u16*)((u8*)s + 0x1E); j++, k = (PKey*)((u8*)k + 0xC)) {
                        if (b->lo > k->y0) {
                            b->lo = k->y0;
                        }
                        if (b->hi < k->y0 + 1) {
                            b->hi = k->y0 + 1;
                        }
                    }
                }
            }
        }
    }
}