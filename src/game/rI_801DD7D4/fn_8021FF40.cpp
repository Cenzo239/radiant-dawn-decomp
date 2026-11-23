#include "game/rI_801DD7D4/fn_wf.h"
#pragma auto_inline off
extern "C" {
void* fn_801E5640(void*, int, int);
void fn_801E5734(void*, void*);
void fn_801E518C(void*, void*, int, f32);
void fn_801E4D1C(void*, void*, int);
f32 fn_801E33B4(void*);
f32 fn_801E3468(void*);
extern char lbl_80371CCC[];
struct XY { s16 x, y; };
struct Wy { void* vt; int rc; s16 id; s16 x, y; u8 pe[0x22]; f32 a30, a34; u8 p38[4]; Wy* parent; const char* a40; u8 p44[0x20]; const char* a64; };
struct S4 { u8 p[0x48]; Wy* a48; Wy* a4c; Wy* a50; u8 p54[4]; Wy* a58; };
static inline void mv(void* s, Wy* w, s16 x, s16 y, int f) { XY p; p.x = x; p.y = y; fn_801E459C(s, w, &p, f); }
static inline void setHelpR(void* s, const char* const& str) { Wy* h = (Wy*)fn_801E5640(s, -0x1000, 0); if (h != NULL) h->a64 = str; }
#define CHAIN(o, fld, fn, v0, v1, v2, v3) { \
    Wy* p; Wy* q; Wy* r; Wy* t; \
    v0 = (o)->fld; p = (o)->parent; \
    if (p) { v1 = p->fld; q = p->parent; if (q) { v2 = q->fld; r = q->parent; if (r) { v3 = r->fld; t = r->parent; if (t) { v3 *= fn(t); } v2 *= v3; } v1 *= v2; } v0 *= v1; } \
}
#define FIND(v, id_, fld) v = (Wy*)fn_801E5640(s, id_, 0); if (v == NULL) { v = s->fld; fn_801E5448(s, v); }
void fn_8021FF40(S4* s) {
    Wy* a;
    Wy* b;
    f32 v3, v2, v1, v0;
    FIND(a, 0x81, a48)
    if (a->y != 0x1c) mv(s, a, a->x, 0x1c, 1);
    CHAIN(a, a34, fn_801E3468, v0, v1, v2, v3)
    if (1.0f != v0) fn_801E518C(s, a, 1, 1.0f);
    FIND(b, 0x82, a4c)
    if (b->x != 0x20) mv(s, b, 0x20, b->y, 0);
    b->a40 = (const char*)fn_801E7A28(a);
    FIND(b, 0x83, a50)
    if (b->x != 0x129) mv(s, b, 0x129, b->y, 0);
    b->a40 = (const char*)fn_801E7A28(a);
    {
        Wy* t = (Wy*)fn_801E5640(s, 0x80, 0);
        const char* c = lbl_80371CCC;
        t->a40 = c;
        fn_801E5734(s, a);
        setHelpR(s, c + 0x19);
    }
}
void fn_80220A1C(S4* s) {
    Wy* a;
    f32 v3, v2, v1, v0;
    FIND(a, 0x84, a58)
    CHAIN(a, a30, fn_801E33B4, v0, v1, v2, v3)
    if (1.0f != v0) fn_801E4D1C(s, a, 1);
    {
        Wy* t = (Wy*)fn_801E5640(s, 0x80, 0);
        const char* c = lbl_80371CCC;
        t->a40 = c + 0x75;
        fn_801E5734(s, a);
        setHelpR(s, c + 0x89);
    }
}
}
