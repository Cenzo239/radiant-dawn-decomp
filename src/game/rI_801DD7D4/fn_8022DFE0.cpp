/* fn_8022DFE0 (round 19): builds the help bar (0x68 widget, id -0x1000) and the 0x48 funds box of a shop
   screen, sets the help text from the screen data and the text scale (halved in one display mode).
   Exact (check_func.py --symbol-map fn_8022DFE0.symbols.json --strict-references): help bar via game/helpbar.h. */
#include "game/helpbar.h"
#include "game/rI_801DD7D4/fn_wf.h"
#pragma auto_inline off
extern "C" {
extern u8 lbl_8038E070[];
extern char lbl_80372600[];
extern char lbl_80390B3C[];
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
struct Dat { u8 p[0xa0]; const char* xa0; };
struct Sc { u8 p[0x74]; G3* a74; u8 p78[8]; u8 a80; u8 p81[3]; f32 a84; Dat* a88; };
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
extern "C" void fn_8022DFE0(Sc* s) {
    {
        HbHelpBar* b = new HbHelpBar;
        b->id = -0x1000;
        b->s.w[3] = 1;
        b->a64 = lbl_80372600;
        b->flags |= 0x10;
        b->a60 = 0;
        b->a28 = 8;
        fn_801E5448(s, b);
    }
    {
        G3* g = newG();
        s->a74 = g;
        if (g != NULL) g->w.rc++;
    }
    s->a74->w.id = 5;
    s->a74->w.a28 = 8;
    s->a74->a40 = fn_800D0864(lbl_80372600 + 1);
    s->a74->a44 = fn_801E7204(s->a80);
    fn_801E5448(s, s->a74);
    setHelp(s, s->a88->xa0);
    s->a84 = 1.0f;
    if (fn_801E7218(fn_8010B228(lbl_80390B3C))) s->a84 *= 0.5f;
}
