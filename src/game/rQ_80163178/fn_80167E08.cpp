/* AI: build and sort the turn order list (names guessed). */
#include "game/rQ_80163178/common.h"
struct SideL { Unit* head; Unit* tail; int n; };
extern "C" {
extern SideL* lbl_804CB814;
extern u8 lbl_803CAB38[];
void fn_80167704(SideL*);
int fn_80168098(void);
int fn_801681C4(Unit*, Unit*);
void fn_801681E0(Unit**, Unit**, int (*)(Unit*, Unit*));
}
static inline void Sort(Unit** const& b, int n) {
    fn_801681E0(b, b + n, fn_801681C4);
}
extern "C" void fn_80167E08(void) {
    AiCfg* c = &lbl_804183F0;
    u32 n;
    fn_80167704(&lbl_804CB814[lbl_803CAB38[0x11]]);
    n = fn_80168098();
    Sort(c->order, n);
    c->order[n] = 0;
    c->cursor = c->order;
}
