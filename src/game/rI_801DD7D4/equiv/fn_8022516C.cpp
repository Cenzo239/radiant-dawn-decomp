/* fn_8022516C (round 19): builds the title bar (0x50 widget, id 0x80) and the help bar of a screen and
   sets the help text. Same shape as fn_8021F5C4 with another string table. */
#include "game/rI_801DD7D4/fn_wf.h"
#pragma auto_inline off
extern "C" {
extern u8 lbl_8038CA50[], lbl_8038CA18[], lbl_8038C1C0[];
int fn_80058718(void);
int fn_8002460C(void);
void* fn_801E5640(void*, int, int);
extern char lbl_80371CCC[];
extern char lbl_80371E1C[];
extern char lbl_803712F8[];
}
struct WA { WF w; const char* a40; s16 a44; u8 a46; };
struct WB { WF w; int a40, a44, a48, a4c; u8 a50; f32 a54; s16 a58, a5a, a5c, a5e; int a60; const char* a64; };
struct Sc { u8 p[0x5c]; WA* a5c; };
static inline WA* newA(void) {
    WA* a = (WA*)fn_80079150(0x50);
    if (a != NULL) {
        wfInit(&a->w, 0x10, 0x13, 0x250, 0x3b, 0x240, 0x28, 0x1c2, 0x10);
        a->w.vt = lbl_8038CA50;
        a->a40 = 0;
        a->a44 = 0x20;
        a->a46 = 0;
        ((VO0N*)a)->v2C();
        a->w.vt = lbl_8038CA18;
        ((VO0N*)a)->v2C();
    }
    return a;
}
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
static inline void setHelp(void* s, const char* const& t) {
    WB* h = (WB*)fn_801E5640(s, -0x1000, 0);
    if (h != NULL) h->a64 = t;
}
extern "C" {
void fn_8022516C(Sc* s) {
    {
        WA* r = newA();
        s->a5c = r;
        if (r != NULL) r->w.rc++;
    }
    s->a5c->w.id = 0x80;
    s->a5c->w.a28 = 8;
    s->a5c->a40 = lbl_80371E1C;
    fn_801E5448(s, s->a5c);
    {
        WB* b = newB();
        int one = 1;
        b->w.id = -0x1000;
        b->a4c = one;
        b->a64 = lbl_80371E1C + 0x18;
        b->w.flags |= 0x10;
        b->a60 = 0;
        b->w.a28 = 8;
        fn_801E5448(s, b);
        if (fn_80058718() != 0 && fn_8002460C() != 0) {
            WB* h = (WB*)fn_801E5640(s, -0x1000, 0);
            if (h != NULL) h->a60 = one;
        }
    }
    setHelp(s, lbl_80371E1C + 0x19);
}
}
