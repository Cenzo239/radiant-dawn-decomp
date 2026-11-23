/* fn_80213B4C: builds the title box (0x50 widget, id 0x80) and the help bar (0x68 widget, id -0x1000) of a
   menu screen, enables the help bar's second line in the special modes and sets its text.
   Exact (check_func.py --symbol-map fn_80213B4C.symbols.json --strict-references). */
#include "game/helpbar.h"
#include "game/rI_801DD7D4/fn_wf.h"
#pragma auto_inline off
extern "C" {
extern u8 lbl_8038CA50[], lbl_8038CA18[];
extern char lbl_803712F8[];
void* fn_801E5640(void*, int, int);
int fn_80058718(void);
int fn_8002460C(void);
}
struct WA { WF w; void* a40; s16 a44; u8 a46; };
static inline void setHelp(void* s, char* const& str) {
    HbHelpBar* h = (HbHelpBar*)fn_801E5640(s, -0x1000, 0);
    if (h != NULL) h->a64 = str;
}
extern "C" void fn_80213B4C(void* s) {
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
    a->w.id = 0x80;
    a->a40 = lbl_803712F8;
    fn_801E5448(s, a);
    HbHelpBar* b = new HbHelpBar;
    int one = 1;
    b->id = -0x1000;
    b->s.w[3] = one;
    b->a64 = lbl_803712F8 + 0x19;
    b->flags |= 0x10;
    b->a60 = 0;
    b->a28 = 8;
    fn_801E5448(s, b);
    if (fn_80058718() != 0 && fn_8002460C() != 0) {
        HbHelpBar* h = (HbHelpBar*)fn_801E5640(s, -0x1000, 0);
        if (h != NULL) h->a60 = one;
    }
    setHelp(s, lbl_803712F8 + 0x1a);
}
