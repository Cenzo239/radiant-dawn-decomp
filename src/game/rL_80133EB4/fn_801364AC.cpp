#include "game/rL_80133EB4/types.h"
struct Color { u8 r, g, b, a; };
struct Lit2 { u8 pad[4]; Color c; u8 pad8[0x14 - 8]; Vec dir; };
struct Li { u8 pad[2]; Color c; };
struct MM { u8 pad[0xE4]; u8 xe4[0x30]; };
struct Mtx { f32 m[12]; };
extern "C" {
extern Color lbl_80413BF8[4];
extern Color lbl_80413BE8[4];
extern s16 lbl_804CB840, lbl_804CB842, lbl_804CB844;
extern void fn_80011680(void);
extern void fn_8001E6D0(void*, void*);
extern Li* fn_80010BB0(int);
extern Lit2* fn_80010E38(Li*, int);
extern void fn_800110F4(Li*, Mtx*);
extern void fn_80010C38(Li*, Li*);

extern Color lbl_804CDE88;
static inline void SetL(Li* l, Color c) { l->c = c; }
static inline void SetD(Lit2* r, Color c) { r->c = c; }
static inline Vec Dir() { Vec v; v.x = lbl_804CB840; v.y = lbl_804CB842; v.z = lbl_804CB844; return v; }
static inline void SetV(Lit2* r, Vec v) { r->dir = v; }

void fn_801364AC(MM* mm) {
    Mtx m;
    fn_80011680();
    fn_8001E6D0(mm->xe4, &m);
    Li* l = fn_80010BB0(0);
    if (l) {
        SetL(l, lbl_80413BF8[0]);
        Lit2* r = fn_80010E38(l, 1);
        SetV(r, Dir());
        SetD(r, lbl_80413BE8[0]);
        fn_800110F4(l, &m);
    }
    l = fn_80010BB0(1);
    if (l) {
        SetL(l, lbl_80413BF8[1]);
        Lit2* r = fn_80010E38(l, 1);
        SetV(r, Dir());
        SetD(r, lbl_80413BE8[1]);
        fn_800110F4(l, &m);
        if (fn_80010BB0(2)) fn_80010C38(fn_80010BB0(1), fn_80010BB0(2));
    }
    l = fn_80010BB0(3);
    if (l) { Color w = lbl_804CDE88; l->c = w; }
}
}
