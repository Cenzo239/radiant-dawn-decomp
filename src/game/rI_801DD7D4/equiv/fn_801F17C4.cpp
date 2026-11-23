/* fn_801F17C4 (round 19): builds the help bar (0x68 widget, id -0x1000) of the unit-list screen, enables
   its second line in the two special modes and clears the shared selection word. */
#include "game/rI_801DD7D4/fn_wf.h"
#pragma auto_inline off
extern "C" {
extern u8 lbl_8038C1C0[];
extern char lbl_8036F03C[];
extern int lbl_803CA870[];
int fn_80058718(void);
int fn_8002460C(void);
void* fn_801E5640(void*, int, int);
}
struct WB { WF w; int a40, a44, a48, a4c; u8 a50; f32 a54; s16 a58, a5a, a5c, a5e; int a60; const char* a64; };
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
extern "C" void fn_801F17C4(void* s) {
    WB* b = newB();
    int one = 1;
    b->w.id = -0x1000;
    b->a4c = one;
    b->a64 = lbl_8036F03C;
    b->w.flags |= 0x10;
    b->a60 = 0;
    b->w.a28 = 8;
    fn_801E5448(s, b);
    if (fn_80058718() != 0 && fn_8002460C() != 0) {
        WB* h = (WB*)fn_801E5640(s, -0x1000, 0);
        if (h != NULL) h->a60 = one;
    }
    lbl_803CA870[1] = 0;
    if (fn_80058718() != 0 || fn_8002460C() != 0) {
        WB* h = (WB*)fn_801E5640(s, -0x1000, 0);
        if (h != NULL) h->a60 = 1;
    }
}
