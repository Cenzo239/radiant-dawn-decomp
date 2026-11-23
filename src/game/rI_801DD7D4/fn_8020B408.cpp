/* fn_8020B408 (round 19): builds the help bar and the funds box of a shop list screen (title depends on the
   buy/sell flag) and sets the text scale. Same shape as fn_8022DFE0.
   Exact (check_func.py --symbol-map fn_8020B408.symbols.json --strict-references): help bar via game/helpbar.h. */
#include "game/helpbar.h"
#include "game/rI_801DD7D4/fn_wf.h"
#pragma auto_inline off
extern "C" {
extern u8 lbl_8038E070[];
extern char lbl_803711E8[];
extern char lbl_8038F468[];
void* fn_801E5640(void*, int, int);
const char* fn_800D0864(const char*);
int fn_801E7204(int);
int fn_801E7218(int);
#if TARGET_PC
FE10_PROTO p32ret fn_8010B228(const char*);
#else
int fn_8010B228(const char*);
#endif
}
struct G3 { WF w; const char* a40; int a44; };
struct Dat { u8 p[0x70]; const char* x70; };
struct Sc { u8 p[0x50]; G3* a50; u8 p54[8]; u8 a5c; u8 a5d; u8 p5e[2]; f32 a60; Dat* a64; };
static inline G3* newG(void) {
    G3* g = (G3*)fn_80079150(0x48);
    if (g != NULL) {
        wfInit(&g->w, 0x14, 0x144, 0xe4, 0x194, 0xd0, 0x50, 0x46, 0x10);
        g->w.vt = lbl_8038E070;
        g->a40 = 0;
        g->a44 = 0;
        ((VO0N*)g)->v2C();
    }
    return g;
}
static inline void setHelp(void* s, const char* t) {
    HbHelpBar* h = (HbHelpBar*)fn_801E5640(s, -0x1000, 0);
    if (h != NULL) h->a64 = t;
}
extern "C" void fn_8020B408(Sc* s) {
    {
        HbHelpBar* b = new HbHelpBar;
        b->id = -0x1000;
        b->s.w[3] = 1;
        b->a64 = lbl_803711E8 + 0x45;
        b->flags |= 0x10;
        b->a60 = 0;
        b->a28 = 8;
        fn_801E5448(s, b);
    }
    {
        G3* g = newG();
        s->a50 = g;
        if (g != NULL) g->w.rc++;
    }
    s->a50->w.id = 2;
    s->a50->w.a28 = 8;
    if (s->a5c == 0) {
        s->a50->a40 = fn_800D0864(lbl_803711E8 + 0x46);
    } else {
        s->a50->a40 = fn_800D0864(lbl_803711E8 + 0x51);
    }
    s->a50->a44 = fn_801E7204(s->a5d);
    fn_801E5448(s, s->a50);
    setHelp(s, s->a64->x70);
    s->a60 = 1.0f;
    if (fn_801E7218(fn_8010B228(lbl_8038F468))) s->a60 *= 0.5f;
}
