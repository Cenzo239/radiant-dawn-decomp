/* fn_80184324: near miss (14 of 29 words). Original keeps the u8 idx in r30 and re-shifts it for each
   index; CW here keeps idx*4 instead. Best attempt below (two stores: reloaded g->idx, then cached idx). */
#include "game/rF_8017F400/gmap.h"
extern "C" {
extern void fn_80081A90(void* proc);
extern void fn_80078E24(void* p);
void fn_80184324(GMap* g)
{
    fn_80081A90(g->proc);
    u8 idx = g->idx;
    if (lbl_804CB908[idx] != NULL) {
        fn_80078E24(lbl_804CB908[idx]);
        lbl_804CB908[g->idx] = NULL;
        lbl_804CB908[idx] = NULL;
    }
}
}
