/* THP read thread: file statics at lbl_804209C0 (queues, messages, thread, stack). */
#include "game/rI_801DD7D4/fn_thp.h"
#pragma auto_inline off

extern "C" {
static u8 sFree[0x20];
static u8 sRead[0x20];
static u8 sRead2[0x20];
static u32 mFree[10];
static u32 mRead[10];
static u32 mRead2[10];
static u8 sThread[0x318];
static u8 sStack[0x1000];
void fn_80237B78(void*);
extern int lbl_804CBF70;
int fn_802F6C90(void*, void*, int, int, int);
#if TARGET_PC
FE10_PROTO void fn_80236A48(p32arg);
#else
void fn_80236A48(int);
#endif
struct RB { int* ptr; int frame; };

/* CreateReadThread */
int fn_80237A80(int prio) {
    if (fn_8031FC48(sThread, fn_80237B78, 0, sStack + 0x1000, 0x1000, prio, 1) == 0) {
        return 0;
    }
    fn_8031D224(sFree, mFree, 10);
    fn_8031D224(sRead, mRead, 10);
    fn_8031D224(sRead2, mRead2, 10);
    lbl_804CBF70 = 1;
    return 1;
}
/* ReadThreadStart */
void fn_80237B20(void) {
    if (lbl_804CBF70 != 0) {
        fn_803202B0(sThread);
    }
}
}
