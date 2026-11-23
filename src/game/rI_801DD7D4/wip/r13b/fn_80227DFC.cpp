#include "game/rI_801DD7D4/fn_wf.h"
#pragma auto_inline off
extern "C" {
void* fn_801E5640(void*, int, int);
void fn_801E5734(void*, void*);
void fn_801E495C(void*, void*, void*, int);
void fn_801E41E4(void*, void*, void*, int);
s16 fn_802225E8(void*, int);
void** fn_8022291C(void*);
extern char lbl_80371E1C[];
extern u8 lbl_8038FBD0[];
struct XY { s16 x, y; };
struct Wy { void* vt; int rc; s16 id; s16 x, y; u8 pe[0x22]; f32 a30, a34; u8 p38[4]; Wy* parent; const char* a40; u8 p44[8]; u8 a4c, a4d, a4e, p4f; s16 a50; };
struct S5 { u8 p[0x48]; Wy* a48; u8 p4c[0xc]; Wy* a58; };
struct WU { WF w; void* a40; void* a44; void* a48; };
static inline void mv(void* s, Wy* w, s16 x, s16 y, int f) { XY p; p.x = x; p.y = y; fn_801E459C(s, w, &p, f); }
static inline void mv4(void* s, Wy* w, s16 x, s16 y, int f) { XY p; p.x = x; p.y = y; fn_801E41E4(s, w, &p, f); }
struct WB2 { u8 p[0x4c]; bool a4c; }; struct WB3 { u8 p[0x4c]; u8 b:1; u8 c:7; }; struct WB4 { u8 p[0x4c]; s8 a4c; };
struct HH { u8 p[0x64]; const char* a64; };
static inline void setHelpR(void* s, const char* const& str) { HH* h = (HH*)fn_801E5640(s, -0x1000, 0); if (h != NULL) h->a64 = str; }
static inline void clr(Wy* a) { a->a4c = 0; }
static inline void* getU(Wy* a) { if (fn_8022291C(a) != NULL) return *fn_8022291C(a); return NULL; }
static inline void* getV(Wy* a) { void** p = fn_8022291C(a); if (p != NULL) return *fn_8022291C(a); return NULL; }
static inline void* getW(Wy* a) { return fn_8022291C(a) != NULL ? *fn_8022291C(a) : NULL; }
static inline void getX(Wy* a, void*& u) { if (fn_8022291C(a) != NULL) u = *fn_8022291C(a); else u = NULL; }
void fn_80227DFC(S5* s) {
/*P*/
    Wy* a;
    Wy* b;
    void* u;
    Wy* d;
/*E*/
    a = (Wy*)fn_801E5640(s, 0x82, 0);
    /*C*/
    {
        int v = fn_802225E8(a, a->a50);
        a->a50 = v & ~(v >> 31);
    }
    u = getU(a);
    b = (Wy*)fn_801E5640(s, 0x87, 0);
    if (b == NULL) {
        WU* o = (WU*)fn_80079150(0x4c);
        b = (Wy*)o;
        if (o != NULL) {
            wfInit(&o->w, 0x191, 0x45, 0x297, 0x10b, 0x106, 0xc6, 0x1cc, 0x10);
            o->w.vt = lbl_8038FBD0;
            o->a40 = 0;
            ((VO0N*)o)->v2C();
        }
        ((WF*)b)->id = 0x87;
        ((WF*)b)->a28 = 8;
        b->a40 = (const char*)u;
        fn_801E5448(s, b);
    }
    if (b->x != 0x13d) mv(s, b, 0x13d, b->y, 1);
    b = (Wy*)fn_801E5640(s, 0x88, 0);
    if (b == NULL) { b = s->a58; fn_801E5448(s, b); }
    if (b->x != 0x144) mv(s, b, 0x144, b->y, 1);
    d = (Wy*)fn_801E5640(s, 0x83, 0);
    if (d == NULL) {
        b = s->a48;
        fn_801E5448(s, b);
        if (b->x != 0x150 || b->y != 0x112) mv(s, b, 0x150, 0x112, 0);
    } else {
        if (d->x != 0x150 || d->y != 0x112) mv4(s, d, 0x150, 0x112, 0);
    }
    {
        Wy* t = (Wy*)fn_801E5640(s, 0x80, 0);
        const char* c = lbl_80371E1C;
        t->a40 = c + 0x8a;
        fn_801E5734(s, a);
        setHelpR(s, c + 0x76);
    }
}
}
