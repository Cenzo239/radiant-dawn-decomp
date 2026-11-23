/* WIP (round 19, zero-idiom family): complete draft for the port, class `other` like its sibling.
   Generated from wip/fn_80206310.cpp (same body, 6 weapon lists instead of 3, fields shifted);
   the `li rI,0; mr rZ,rI` zero idiom before the sort loop is not reproduced (see NOTES_round18.md). */
#pragma auto_inline off
#pragma inline_max_size(20000)
extern "C" {
#include "game/rI_801DD7D4/fn_shop.h"
extern u8 lbl_8038E8D0[], lbl_8038CFA8[], lbl_8038E8A0[], lbl_8038E870[], lbl_8038E198[];
void fn_802109D8(void*);
void* fn_801EEEEC(void*, int);
void fn_8028BFD8(void*, void*, void*, int, int);
void* memset(void*, int, u32);
void fn_801E2F40(void*, void*);
void fn_80210F10(void*, void*);
void fn_8014BED4(int, void*);
void* fn_800D4188(const char*, void*);
class RL0 { public: int size; void* p; void* n; };
typedef void (RL0::*MF0)();
extern MF0 lbl_8038F440;
extern MF0 lbl_8038F44C;
struct F0 { MF0 f; };

class VC { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C(); virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); virtual int v38(); virtual int v3C(); virtual int v40(); virtual int v44(); virtual int v48(); virtual int v4C(void*, int); virtual int v50(); virtual int v54(); virtual int v58(); virtual int v5C(); virtual int v60(); virtual int v64(f32); };
class VC2 { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C(); virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(MF0); };
struct T3 { int a, b, c; };
struct L50 { WF w; int a40; MF0 t; };
extern MF0 lbl_803741A8;
struct L44 { WF w; int a40; };
struct LSH {
    WF w; int a40; LN l44; int a4c; u8 a50, a51, a52; u8 p53; f32 a54; u8 a58[0xc]; u8 a5e[0xc]; u8 p70[2]; s16 a66, a68, a6a; f32 a6c; s16 a70, a72;
    RL0 ls[6]; u8 pc8[8]; int aa0; u8 pa4[4]; f32 aa8; L50* aac;
};
struct MemF { MF0 f; MemF(MF0 x) : f(x) {} void operator()(RL0& r) { (r.*f)(); } };
static inline MemF forEachA(RL0* b, RL0* e, MemF f) { for (; b != e; b++) f(*b); return f; }
static inline MemF memf(MF0 f) { return MemF(f); }
static inline L50* newT(WF* o) {
    L50* b = (L50*)fn_80079150(0x50);
    if (b != NULL) {
        wfInit(&b->w, 0, 0, 0x154, 0x20, 0x154, 0x20, o->a26, 0x10);
        b->w.vt = lbl_8038E8A0;
        b->a40 = 0;
        b->t = lbl_803741A8;
        b->w.vt = lbl_8038E870;
    }
    return b;
}
static inline void setX(WF* w, s16 x) { w->x1 = x + (s16)(w->x1 - w->x0); w->x0 = x; }
static inline void setY(WF* w, s16 y) { w->y1 = y + (s16)(w->y1 - w->y0); w->y0 = y; }
static inline void setXY(WF* w, s16 x, s16 y) { setX(w, x); setY(w, y); }
static inline void g3(G40* g, LN* q, s16 x0, s16 y0, s16 x1, s16 y1, s16 ix1, s16 iy1, s16 a26, int fl) {
    wfInit(&g->w, x0, y0, x1, y1, ix1, iy1, a26, fl);
    g->w.vt = lbl_8038CAF0;
    g->a40 = 0;
    q->next = q; q->prev = q;
}
static inline LSH* newS(LN*& s44, RL0*& rb, RL0*& re) {
    LSH* o = (LSH*)fn_80079150(0xe0);
    if (o != NULL) {
        s44 = &o->l44; g3((G40*)o, s44, 0xe0, 0x6c, 0x238, 0x146, 0x158, 0xda, 500, 0x10);
        o->w.vt = lbl_8038E8D0;
        o->a4c = 0;
        o->a50 = 0;
        o->a51 = 1;
        o->a52 = 0;
        o->a54 = 2.0f;
        o->a66 = -0x8000;
        o->a68 = -0x8000;
        o->a6a = 0;
        o->a6c = 0.0f;
        o->a70 = 0;
        o->a72 = 0;
        fn_8028BFD8(o->ls, fn_802109D8, fn_801EEEEC, 0xc, 6);
        o->aa0 = 0;
        memset(o->a58, 0, 0xc);
        memset(o->a5e, 0, 0xc);
        {
            rb = o->ls; re = o->ls + 6; forEachA(rb, re, memf(lbl_8038F440));
        }
        o->w.vt = lbl_8038CFA8;
        o->aa8 = 1.0f;
        ((Lst*)o)->v2C();
        {
            L50* b = newT(&o->w);
            o->aac = b;
            setXY(&b->w, -o->w.ix0, 4 - (s16)(b->w.y1 - b->w.y0));
            o->aac->w.x1 = o->aac->w.x0 + (s16)(o->w.x1 - o->w.x0);
            o->aac->w.flags |= 0x10;
            ((VC2*)o->aac)->v2C(lbl_8038F44C);
            fn_801E2F40(o, o->aac);
            o->w.tx = 0x12;
            o->w.ty = 8;
            o->a6a = 7;
        }
    }
    return o;
}
static inline L44* newU() {
    L44* o = (L44*)fn_80079150(0x44);
    if (o != NULL) {
        wfInit(&o->w, 0x1a2, 0x149, 0x28a, 0x173, 0xe8, 0x2a, 500, 0x10);
        o->w.vt = lbl_8038E198;
        o->a40 = 0;
        ((Lst*)o)->v2C();
    }
    return o;
}
#define X4C ((LSH*)o->x4c)
#define X54 ((L44*)o->x54)
struct EC { u8 c; EC(u8 x=0) { c = x; } };
void fn_8020B8C8(Sc* o) {
    /*P*/
    LS* n;
    LS* e;
    u8* s;
    RL0* rb;
    RL0* re;
    int i;
    LN* s44;
    LSH* m;
/*E*/
    {
        m = newS(s44, rb, re);
        o->x4c = (W*)m;
        if (m != NULL) m->w.rc++;
    }
    X4C->w.id = 0;
    X4C->w.a28 = 8;
    ((VC*)o->x4c)->v64(*(f32*)((u8*)o + 0x60));
    {
        n = *(LS**)((u8*)o + 0x48);
        e = (LS*)((u8*)o + 0x44);
        while (n != e) {
            ((VC*)o->x4c)->v4C(&n->val, 0);
            n = n->next;
        }
    }
    {
        s = (u8*)o->x4c; i = 0; while (1) { EC e; fn_80210F10(s + i * 0xc + 0x80, &e); if (++i == 6) break; }
    }
    X4C->a51 = 0;
    fn_801E5448(o, o->x4c);
    {
        L44* u = newU();
        o->x54 = (W*)u;
        if (u != NULL) u->w.rc++;
    }
    X54->w.id = 1;
    X54->w.a28 = 8;
    {
        VL* w = *(VL**)&o->x4c;
        if (atB(w, w->v34()) != NULL) {
            int v;
            w = *(VL**)&o->x4c;
            v = *(int*)atB(w, w->v34());
            X54->a40 = v;
        }
    }
    fn_8014BED4(*(int*)o->x64, o);
    o->x68 = fn_800D4188(lbl_803711E8 + 0x5c, o);
    fn_800D3BCC(o->x68, 0xc);
}
}
