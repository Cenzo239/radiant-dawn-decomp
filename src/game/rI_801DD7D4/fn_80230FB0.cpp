/* fn_80230FB0 (exact, round m5): dims (a28 = 8) every one of the five row widgets except the selected one, then, in
   state 1, re-attaches the panel (tail call to fn_801E5558). */
#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
struct WF { u8 p[0x28]; s16 a28; };
struct LC { u8 p[0x4c]; WF* s[5]; };
struct Roll { u8 p[0x30]; u8 a30; s8 a31; s8 a32; u8 p33; void* a34; LC* a38; };
extern "C" {
void fn_801E5558(void*, void*, int);
static inline WF* Get(LC* l, int i) { return l->s[i]; }
void fn_80230FB0(Roll* o) {
    WF* w;
    LC* l = o->a38;
    int i;
    for (i = 0; i < 5; i++) {
        w = Get(l, i);
        if (w != NULL && i != o->a32) w->a28 = 8;
    }
    if ((int)o->a30 == 1) fn_801E5558(o->a34, o->a38, 0);
}
}
