/* NOT MATCHING, not compiled. fn_8011D17C: 7 words: table pointer and hash char swapped. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
extern int fn_8011B77C(void*, void*);
extern u8* fn_801116B8(Inv*);
extern u32 lbl_80413098[];
extern u8* fn_8010B240(int);
static inline u32 SH(const u8* s0) { u32 h = 0; const u8* p=s0; while ((s8)*p != 0) { h += *p; p++; h <<= 4; } return h; }
void fn_8011D17C(void) {
    /*P*/
    u8* t;
    u32* d;
    int i;
/*E*/
    t = fn_8010B240(0);
    d = lbl_80413098;
    for (i = 0; i < 0xc7; i++) {
        *d = SH(*(const u8**)t);
        d++;
        t += 0x10;
    }
}
}
