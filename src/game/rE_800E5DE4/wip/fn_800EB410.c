/* NEAR MISS (3 of 39 words): original emits "addi r31,r31,lbl@l; addi r3,r31,0"
 * i.e. the class descriptors are separate statics defined in the same TU and
 * MWCC pools their addresses off one base. Not reproducible with externs. */
#include "game/rE_800E5DE4/evproc.h"

extern void fn_800846BC(void*);

/* Registers all event-process classes of this module (class descriptors are
 * laid out consecutively from lbl_80384300). */
void fn_800EB410(void) {
    u8* t = lbl_80384300;
    fn_800846BC(t + 0x0);
    fn_800846BC(t + 0x30);
    fn_800846BC(t + 0xF8);
    fn_800846BC(t + 0x128);
    fn_800846BC(t + 0x188);
    fn_800846BC(t + 0x230);
    fn_800846BC(t + 0x2B0);
    fn_800846BC(t + 0x3C0);
    fn_800846BC(t + 0x478);
    fn_800846BC(t + 0x4D0);
    fn_800846BC(t + 0x598);
    fn_800846BC(t + 0x680);
    fn_800846BC(t + 0x704);
    fn_800846BC(t + 0x7B8);
}
