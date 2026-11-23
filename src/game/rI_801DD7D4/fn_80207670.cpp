// fn_80207670 and neighbours: the shop buy flow. fn_802xxxxx pairs differ only in the list slot and callbacks.
#pragma auto_inline off
#pragma inline_max_size(20000)
extern "C" {
#include "game/rI_801DD7D4/fn_shop.h"
extern u8 lbl_8038E0E0[], lbl_8038C294[], lbl_8038CD98[];
extern s16 lbl_804CAA0C[1];
void* fn_8010E41C(void*, int);
struct Col { u8 r, g, b, a; Col& operator=(const Col& o) { if (this != &o) { r = o.r; g = o.g; b = o.b; a = o.a; } return *this; } };
struct Eff { void* vt; int a4; int a8; u8 ac, ad; u8 pe[6]; s16 a14; u8 p16[2]; f32 a18, a1c; Col c; f32 a24; };
struct LA0 { WF w; int a40, a44; s16 a48, a4a; u8 a4c; u8 p4d[3]; Eff m1; Eff m2; };
static inline void effB(Eff* m, int a8) {
    m->vt = lbl_8038C294;
    m->a4 = 0;
    m->a8 = a8;
    m->ac = 1;
    m->ad = 1;
    m->a14 = 0;
    m->a18 = 1.0f;
    m->a1c = 1.0f;
    m->c.r = 0x80; m->c.g = 0x80; m->c.b = 0x80; m->c.a = 0xff;
    m->a24 = 0.0f;
    ((VO0N*)m)->v0C();
}
static inline void effD(Eff* m) {
    m->vt = lbl_8038CD98;
    m->ad = 0;
    {
        Col k;
        k.r = 0x40; k.g = 0x40; k.b = 0x80; k.a = 0xff;
        m->c = k;
    }
}
static inline void effC(Eff* m, int a8) {
    m->vt = lbl_8038C294;
    m->a4 = 0;
    m->a8 = a8;
    m->ac = 1;
    m->ad = 1;
    m->a14 = 0;
    m->a18 = 1.0f;
    m->a1c = 1.0f;
    m->c.r = 0x80; m->c.g = 0x80; m->c.b = 0x80; m->c.a = 0xff;
    m->a24 = 0.0f;
}
static inline void effX(Eff* m, int a8) { effB(m, a8); effD(m); }
static inline LA0* newA() {
    Eff* m1; LA0* o = (LA0*)fn_80079150(0xa0);
    if (o != NULL) {
        wfInit(&o->w, 0x15c, 0x13, 0x23c, 0x3b, 0xe0, 0x28, 100, 0x10);
        o->w.vt = lbl_8038E0E0;
        o->a40 = 0;
        o->a44 = 0;
        o->a48 = 1;
        o->a4a = 0x63;
        o->a4c = 1;
m1 = &o->m1; effX(m1, 2);
{ Eff* m = &o->m2; effC(m, 3); ((VO0N*)m)->v0C(); effD(m); }
        ((Lst*)o)->v2C();
    }
    return o;
}
static inline const s16& minS(const s16& a, const s16& b) { if (b < a) return b; return a; }
extern u8* lbl_804CB810;
struct Un { u8 p[0xec]; int xec; u8 p2[4]; struct { u8 p[8]; u8 x8; }* xf4; };
static inline Un* unitAt(u8 id) { if (id != 0) return (Un*)(lbl_804CB810 + (id - 1) * 0x3f0); return NULL; }
static inline void give(int u, Item* it, s16& n) {
    while (n > 0 && (u8)fn_8012BDFC(u) < 7) {
        fn_8012A440(u, it->x0 != NULL ? *it->x0 : 0);
        n--;
    }
}
struct SWa { u8 p[0x5e]; s16 cur[3]; };
struct SWb { u8 p[0x64]; s16 cur[6]; };
#define BODY_fn_80207670(FN, AT) \
void FN(Sc* o) { \
    int j; \
    int it; \
    int i; \
    int pr; \
    u8* bp; \
    VL* w; \
    s16 n; \
    u8 buf[0x10]; \
    w = *(VL**)&o->x4c; \
    it = (int)*AT(w, w->v34()); \
    { \
        LA0* a = newA(); \
        o->x58 = (RO*)a; \
        if (a != NULL) a->w.rc++; \
    } \
    ((LA0*)o->x58)->w.id = 7; \
    ((LA0*)o->x58)->w.a28 = 4; \
    ((LA0*)o->x58)->a40 = 1; \
    ((LA0*)o->x58)->a4c = 0; \
    ((LA0*)o->x58)->w.sy = 0.0f; \
    ((LA0*)o->x58)->a44 = it; \
    pr = PRICE(o, it); \
    n = fn_800626E0(lbl_803CAB38) / pr; \
    j = 0; \
    fn_8010E41C(buf, 4); \
    bp = buf; \
    for (i = 1; i <= 0xfe; i++) { \
        Un* u = unitAt(i); \
        if (u->xec != 0 && bp[u->xf4->x8] != 0) { \
            int k = 7 - (u8)fn_8012BDFC((int)u); \
            if (j < k) j = k; \
        } \
    } \
    if (fn_80060754(lbl_803CAB38) != 0) { \
        j += avail2(); \
    } \
    { \
        s16 b = j; \
        s16 c = minS(n, b); \
        LA0* q = (LA0*)o->x58; \
        q->a4a = minS(c, *lbl_804CAA0C); \
    } \
    fn_801E5448(o, w); \
    fn_8014C2AC(o->x64->x14); \
}
BODY_fn_80207670(fn_80207670, atA)
BODY_fn_80207670(fn_8020CC28, atB)
#define BODY_fn_80208388(FN, AT) \
void FN(Sc* o) { \
    int it; \
    { \
        VL* w = *(VL**)&o->x4c; \
        it = (int)*AT(w, w->v34()); \
    } \
    { \
        LA0* a = newA(); \
        o->x58 = (RO*)a; \
        if (a != NULL) a->w.rc++; \
    } \
    ((LA0*)o->x58)->w.id = 7; \
    ((LA0*)o->x58)->w.a28 = 4; \
    ((LA0*)o->x58)->a40 = 0; \
    ((LA0*)o->x58)->a4c = 0; \
    ((LA0*)o->x58)->w.sy = 0.0f; \
    ((LA0*)o->x58)->a44 = it; \
    ((LA0*)o->x58)->a48 = 1; \
    { \
        s16 one = 1; \
        LA0* q = (LA0*)o->x58; q->a4a = minS(one, *lbl_804CAA0C); \
    } \
}
BODY_fn_80208388(fn_80208388, atA)
BODY_fn_80208388(fn_8020D940, atB)
void fn_80207C50(void*);
void fn_80206C1C(void*);
void fn_8020D208(void*);
void fn_8020C1D4(void*);
void fn_80212348(void*, int);
#define MV(w, xv, yv) {     s16 y = yv;     Pt p;     p.x = xv;     p.y = y;     fn_801E495C(o, w, &p, 0); }
#define BODY_fn_80209768(FN, NM, CN) \
void FN(Sc* o) { \
W* a; \
W* b; \
W* c; \
W* d; \
int* m; \
u32 cur; \
int k; \
     a = fn_801E5640(o, 3, 0);     b = fn_801E5640(o, 4, 0);     c = fn_801E5640(o, 6, 0);     d = fn_801E5640(o, 5, 0);     cur = fn_801E7A28(a);     fn_801E5954(o);     if (cur != fn_801E7A28(a)) {         cur = fn_801E7A28(a);         ((VS*)b)->v34(cur);         fn_801EA538(d, cur);     }     if (!inputBlocked()) {         k = ((VS*)lbl_804CB5B8)->v48();         if ((k & 0x400) && cur != 0) {             SND(0x82);             if (((VS*)a)->v50(cur) == 0) {                 fn_8014C2AC(o->x64->x40);                 { m = (int*)o->x64->x74; W* p = fn_801E5640(o, -0x1000, 0); if (p != NULL) { p->x64 = (const char*)m; } }                 fn_80083DC4(o, 0x14);             } else {                 fn_80083DC4(o, 0x11);             }         } else if ((k & 0x4000) && fn_80060754(lbl_803CAB38) != 0) {             SND(0x82);             m = fn_801059B0(); if (*m - fn_80105158(m) < ((W*)o->x58)->x48) {                 fn_8014C2AC(o->x64->x4c);                 { m = (int*)o->x64->x74; W* p = fn_801E5640(o, -0x1000, 0); if (p != NULL) { p->x64 = (const char*)m; } }                 fn_80083DC4(o, 0x16);             } else {                 fn_80083DC4(o, 0x12);             }         } else if ((k & 0x2000) && cur != 0) {             fn_801E6C44(cur, o, 1);             o->x5e = 0xf;             fn_80083DC4(o, 0x18);         } else if ((k & 0x1000) && cur != 0) {             fn_801E6D50(cur, o);             o->x5e = 0xf;             fn_80083DC4(o, 0x19);         } else if (k & 0x800) {             if (((W*)o->x58)->x44p->x26 == 0xff) {                 MV(a, a->xa, -(s16)(a->x10 - a->xc) >> 2);                 MV(b, -0x34, b->xc);                 if (c != NULL) {                     MV(c, 0x1a4, c->xc);                 }                 MV(d, 0x17e, d->xc);                 NM(o);                 fn_8014C2AC(o->x64->x18);                 fn_800D3BCC(o->x68, 0xc);                 fn_80083DC4(o, 9);             } else {                 MV(a, a->xa, -(s16)(a->x10 - a->xc) >> 2);                 MV(b, -0x34, b->xc);                 if (c != NULL) {                     MV(c, 0x1a4, c->xc);                 }                 MV(d, 0x17e, d->xc);                 fn_801E4F50(o, o->x58, 0);                 RELEASE(o);                 CN(o);                 fn_8014C2AC(o->x64->x10);                 fn_800D3BCC(o->x68, 0xc);                 { m = (int*)o->x64->x7c; W* p = fn_801E5640(o, -0x1000, 0); if (p != NULL) { p->x64 = (const char*)m; } }                 fn_80083DC4(o, 5);             }             SND(0x92);         }     } }
BODY_fn_80209768(fn_80209768, fn_80207C50, fn_80206C1C)
BODY_fn_80209768(fn_8020ED20, fn_8020D208, fn_8020C1D4)
#define BODY_fn_80209E28(FN, AT, SLOT, CNT, SW, CU, SETF) \
void FN(Sc* o) { \
    W* sel; \
    VL* w; \
    W* b; \
    Item* it; \
    Slot* l; \
    s16 count; \
    W* h; \
    int j; \
    s16 n2; \
    s16 n; \
    int pr; \
    int id; \
    int id2; \
    h = fn_801E5640(o, 5, 0); \
    switch (lbl_803CA870[0xc]) { \
    case 0x81: { \
        b = fn_801E5640(o, 3, 0); \
        w = *(VL**)&o->x4c; \
        sel = (W*)o->x58; \
        it = *(Item**)AT(w, w->v34()); \
        { \
            n = sel->x48; \
            pr = PRICE(o, (int)it); \
            fn_800615DC(lbl_803CAB38, fn_800626E0(lbl_803CAB38) - pr * n); \
        } \
        { \
            n2 = sel->x48; \
            count = 0; \
            give(fn_801E7A28(b), (Item*)it, n2); \
            if (n2 > 0 && fn_80060754(lbl_803CAB38) != 0) { \
                while (n2 > 0 && avail2() > 0) { \
                    if (it->x0 != NULL) id2 = *it->x0; else id2 = 0; \
                    fn_80105260(fn_801059B0(), id2); \
                    n2--; \
                    count++; \
                } \
            } \
        } \
        { \
            u32* p; u32 v; \
            v = it->x26; \
            if (v != 0xff) { \
                p = (u32*)(lbl_803CAB38 + 0x104); \
                for (; v >= 0x20; v -= 0x20, p++) {} \
                *p |= 1 << v; \
                { \
                    l = (Slot*)((u8*)w + SLOT); \
                    for (j = 0; j < CNT; l++, j++) { \
                        LS* f = findIf(l->next, (LS*)&l->prev, B2(it)); \
                        if (f != (LS*)&l->prev) { \
                            f->prev->next = f->next; \
                            f->next->prev = f->prev; \
                            fn_80079210(f); \
                            { \
                                u32 sz = --l->size; \
                                s16& c = ((SW*)w)->cur[j]; \
                                if (c >= sz) c = sz - 1; \
                            } \
                            break; \
                        } \
                    } \
                } \
            } \
        } \
        { \
            int q = w->v34(); \
            SETF(w, *(s16*)((u8*)w + q * 2 + CU)); \
        } \
        if (count > 0) fn_8014C2AC(o->x64->x30); \
        if (h != NULL) fn_801E5734(o, h); \
        break; \
    } \
    case 0x80: \
        fn_8014C2AC(o->x64->x24); \
        fn_80083DC4(o, 0xe); \
        break; \
    } \
}
BODY_fn_80209E28(fn_80209E28, atA, 0x74, 3, SWa, 0x5e, fn_802121F8)
BODY_fn_80209E28(fn_8020F3E0, atB, 0x80, 6, SWb, 0x64, fn_80212348)
#define BODY_fn_8020A4C4(FN, AT, SLOT, CNT, SW, CU, SETF) \
void FN(Sc* o) { \
    W* sel; \
    VL* w; \
    Item* it; \
    W* h; \
    Slot* l; \
    int j; \
    s16 n; \
    int pr; \
    int id; \
    h = fn_801E5640(o, 5, 0); \
    switch (lbl_803CA870[0xc]) { \
    case 0x81: { \
        fn_801E5640(o, 3, 0); \
        w = *(VL**)&o->x4c; \
        sel = (W*)o->x58; \
        it = *(Item**)AT(w, w->v34()); \
        { \
            n = sel->x48; \
            pr = PRICE(o, (int)it); \
            fn_800615DC(lbl_803CAB38, fn_800626E0(lbl_803CAB38) - pr * n); \
        } \
        { \
            s16 n2 = sel->x48; \
            if (n2 > 0 && fn_80060754(lbl_803CAB38) != 0) { \
                while (n2 > 0 && avail2() > 0) { \
                    int id2; \
                    if (it->x0 != NULL) id2 = *it->x0; else id2 = 0; \
                    fn_80105260(fn_801059B0(), id2); \
                    n2--; \
                } \
            } \
        } \
        { \
            u32* p; u32 v; \
            v = it->x26; \
            if (v != 0xff) { \
                p = (u32*)(lbl_803CAB38 + 0x104); \
                for (; v >= 0x20; v -= 0x20, p++) {} \
                *p |= 1 << v; \
                { \
                    l = (Slot*)((u8*)w + SLOT); \
                    for (j = 0; j < CNT; l++, j++) { \
                        LS* f = findIf(l->next, (LS*)&l->prev, B2(it)); \
                        if (f != (LS*)&l->prev) { \
                            f->prev->next = f->next; \
                            f->next->prev = f->prev; \
                            fn_80079210(f); \
                            { \
                                u32 sz = --l->size; \
                                s16& c = ((SW*)w)->cur[j]; \
                                if (c >= sz) c = sz - 1; \
                            } \
                            break; \
                        } \
                    } \
                } \
            } \
        } \
        { \
            int q = w->v34(); \
            SETF(w, *(s16*)((u8*)w + q * 2 + CU)); \
        } \
        if (h != NULL) fn_801E5734(o, h); \
        break; \
    } \
    case 0x80: \
        fn_8014C2AC(o->x64->x24); \
        fn_80083DC4(o, 0xe); \
        break; \
    } \
}
BODY_fn_8020A4C4(fn_8020A4C4, atA, 0x74, 3, SWa, 0x5e, fn_802121F8)
BODY_fn_8020A4C4(fn_8020FA7C, atB, 0x80, 6, SWb, 0x64, fn_80212348)
}
