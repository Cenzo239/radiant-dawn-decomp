#include "game/rI_801DD7D4/fn_wf.h"
#pragma auto_inline off
extern "C" {
void* fn_801E5640(void*, int, int);
void fn_801E5734(void*, void*);
void fn_801E518C(void*, void*, int, f32);
void fn_801E41E4(void*, void*, void*, int);
f32 fn_801E3468(void*);
void* fn_800D5448(void*, void*, int);
extern char lbl_80371E1C[];
extern u8 lbl_8038FF18[], lbl_8038C8A8[], lbl_80390140[], lbl_803900E8[];
extern s8 lbl_804CBF08, lbl_804CBF18;
extern void* lbl_804CBF10, *lbl_804CBF1C;
struct XY { s16 x, y; };
struct Wy { void* vt; int rc; s16 id; s16 x, y, x1, y1; u8 pe[0x1e]; f32 a30, a34; u8 p38[4]; Wy* parent; const char* a40; u8 p44[8]; u8 a4c, a4d, a4e, p4f; u8 a50; u8 p51[0x13]; const char* a64; };
struct S5 { u8 p[0x44]; Wy* a44; Wy* a48; Wy* a4c; };
struct Pe { void* vt; void* vt2; s16 x8, xa, xc, xe, x10, x12, x14, x16; f32 x18; s16 x1c, x1e; };
static inline void mv(void* s, Wy* w, s16 x, s16 y, int f) { XY p; p.x = x; p.y = y; fn_801E459C(s, w, &p, f); }
static inline void mv4(void* s, Wy* w, s16 x, s16 y, int f) { XY p; p.x = x; p.y = y; fn_801E41E4(s, w, &p, f); }
static inline void setHelpR(void* s, const char* const& str) { Wy* h = (Wy*)fn_801E5640(s, -0x1000, 0); if (h != NULL) h->a64 = str; }
static inline void setPos(Wy* w, s16 x, s16 y) { s16 ww = w->x1 - w->x; w->x = x; w->x1 = x + ww; s16 hh = w->y1 - w->y; w->y1 = y + hh; w->y = y; }
#define LZ(g, o, v) if (!g) { g = 1; o = v; }
#define CHAIN(o, fld, fn, v0, v1, v2, v3) { \
    Wy* p; Wy* q; Wy* r; Wy* t; \
    v0 = (o)->fld; p = (o)->parent; \
    if (p) { v1 = p->fld; q = p->parent; if (q) { v2 = q->fld; r = q->parent; if (r) { v3 = r->fld; t = r->parent; if (t) { v3 *= fn(t); } v2 *= v3; } v1 *= v2; } v0 *= v1; } \
}
#define FIND(v, id_, fld) v = (Wy*)fn_801E5640(s, id_, 0); if (v == NULL) { v = s->fld; fn_801E5448(s, v); }
static inline Pe* mk() {
    Pe* e = (Pe*)fn_80079150(0x20);
    if (e) {
        e->vt = lbl_8038FF18;
        e->vt2 = lbl_8038C8A8;
        e->x8 = 0;
        e->xa = 0;
        e->xc = 0x80;
        e->xe = 0;
        e->x10 = 2;
        e->x12 = 0xc;
        e->x14 = 0x10;
        e->x16 = 0;
        e->x18 = 0.0f;
        e->x1c = 0x20;
        e->x1e = 4;
    }
    return e;
}
void fn_80226410(S5* s) {
    Wy* a;
    Wy* b;
    Wy* d;
    f32 v3, v2, v1, v0;
    FIND(a, 0x81, a44)
    if (a->y != 0x1c) mv(s, a, a->x, 0x1c, 1);
    CHAIN(a, a34, fn_801E3468, v0, v1, v2, v3)
    if (0.5f != v0) fn_801E518C(s, a, 1, 0.5f);
    a->a50 = 0;
    FIND(b, 0x82, a4c)
    if (b->x != 0x20) mv(s, b, 0x20, b->y, 0);
    b->a4c = 0;
    d = (Wy*)fn_801E5640(s, 0x83, 0);
    if (d == NULL) {
        b = s->a48;
        fn_801E5448(s, b);
        setPos(b, b->x, 0xe0);
        if (b->x != 0x150 || b->y != 0xe0) mv(s, b, 0x150, 0xe0, 0);
    } else {
        if (d->x != 0x150 || d->y != 0xe0) mv4(s, d, 0x150, 0xe0, 0);
    }
    {
        Wy* t = (Wy*)fn_801E5640(s, 0x80, 0);
        t->a40 = lbl_80371E1C + 0x60;
        fn_801E5734(s, a);
    }
    LZ(lbl_804CBF08, lbl_804CBF10, lbl_80390140);
    LZ(lbl_804CBF18, lbl_804CBF1C, lbl_803900E8);
    {
        Pe* e = mk();
        e->xc = 0x78;
        e->x8 = 0x181;
        e->xa = 0x109;
        e->x14 = 0;
        e->x18 = 200.0f;
        e->x1e = 4;
        fn_800D5448(e, s, 0);
    }
    setHelpR(s, lbl_80371E1C + 0x76);
}
}
