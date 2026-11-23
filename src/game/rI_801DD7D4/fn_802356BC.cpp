/* THP audio decode thread: file statics at lbl_8041F090. */
#include "game/rI_801DD7D4/fn_thp.h"
#pragma auto_inline off

extern "C" {
static u8 sThread[0x318];
static u8 sStack[0x1000];
static u8 sQ1[0x20];
static u8 sQ2[0x20];
static u32 mQ1[6];
static u32 mQ2[6];
void fn_802357E4(void*);
void fn_8023580C(void*);
extern int lbl_804CBF48;
struct RB { int* ptr; int frame; };
void fn_802358B8(RB*);
extern u8 lbl_804203A8[];
extern u8 lbl_804203C8[];
int fn_8032D644(void*, void*, int);
struct AB { void* a0; void* a4; int a8; };
int fn_802356BC(int prio, void* mem) {
    if (mem != NULL) {
        if (fn_8031FC48(sThread, fn_8023580C, mem, sStack + 0x1000, 0x1000, prio, 1) == 0) {
            return 0;
        }
    } else {
        if (fn_8031FC48(sThread, fn_802357E4, 0, sStack + 0x1000, 0x1000, prio, 1) == 0) {
            return 0;
        }
    }
    fn_8031D224(sQ1, mQ1, 6);
    fn_8031D224(sQ2, mQ2, 6);
    lbl_804CBF48 = 1;
    return 1;
}
}
