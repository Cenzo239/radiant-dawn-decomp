/* fn_8022DFE0 (round 19): builds the help bar (0x68 widget, id -0x1000) and the 0x48 funds box of a shop
   screen, sets the help text from the screen data and the text scale (halved in one display mode). */
#include "game/rI_801DD7D4/fn_wf.h"
#pragma auto_inline off
extern "C" {
extern u8 lbl_8038C1C0[], lbl_8038E070[];
extern char lbl_80372600[];
extern char lbl_80390B3C[];
void* fn_801E5640(void*, int, int);
const char* fn_800D0864(const char*);
int fn_801E7204(int);
int fn_801E7218(int);
int fn_8010B228(const char*);
}
struct WB { WF w; int a40, a44, a48, a4c; u8 a50; f32 a54; s16 a58, a5a, a5c, a5e; int a60; const char* a64; };
struct G3 { WF w; const char* a40; int a44; };
struct Dat { u8 p[0xa0]; const char* xa0; };
struct Sc { u8 p[0x74]; G3* a74; u8 p78[8]; u8 a80; u8 p81[3]; f32 a84; Dat* a88; };
static inline WB* newB(void) {
    WB* b = (WB*)fn_80079150(0x68);
    if (b != NULL) {
        wfInit(&b->w, 0, 400, 0x260, 0x1c0, 0x260, 0x30, 0x78, 0x10);
        b->a40 = 0; b->a44 = 0; b->a48 = 0; b->a4c = 0;
        b->a50 = 1;
        b->a5a = 0; b->a5e = 0;
        b->w.vt = lbl_8038C1C0;
        b->a60 = 0; b->a64 = 0;
        b->a58 = 0x30; b->a5c = 0x30;
        b->a54 = 0.75f;
    }
    return b;
}
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
    WB* h = (WB*)fn_801E5640(s, -0x1000, 0);
    if (h != NULL) h->a64 = t;
}
extern "C" void fn_8022DFE0(Sc* s) {
    {
        WB* b = newB();
        b->w.id = -0x1000;
        b->a4c = 1;
        b->a64 = lbl_80372600;
        b->w.flags |= 0x10;
        b->a60 = 0;
        b->w.a28 = 8;
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
