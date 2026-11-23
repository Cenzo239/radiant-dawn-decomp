/* Countdown bars: create the state block and load window/deadcount.cms */
#include "game/rN_8025EEF0/calls.h"

extern "C" {
void* memset(void* p, int v, unsigned n);
extern u8* lbl_804CC0AC;

struct Bars {
    s16 m0, m2, m4, m6, m8, mA, mC, mE, m10, m12, m14, m16, m18, m1A, m1C;
};
extern Bars* lbl_804CC0A8;

#pragma pool_strings on
/* The original strings of this file's pool (lbl_803738BC), in order. */
void StringPool(const char** p) {
    p[0] = "window/deadcount.cms";
    p[1] = "SFX_SYS_0315_COUNT00_09";
    p[2] = "SFX_SYS_0315_COUNT10_19";
    p[3] = "SFX_SYS_0315_COUNT20_29";
    p[4] = "SFX_SYS_0315_COUNT30";
    p[5] = "";
    p[6] = "C0315";
}

void fn_80280CB4(u8* p) {
    lbl_804CC0AC = p;
    *(void**)(lbl_804CC0AC + 0x30) = fn_80078CCC(0x24, "", 0);
    lbl_804CC0A8 = *(Bars**)(lbl_804CC0AC + 0x30);
    memset(lbl_804CC0A8, 0, 0x24);
    lbl_804CC0A8->mC = 0x22C;
    lbl_804CC0A8->m8 = 0x22C;
    lbl_804CC0A8->m4 = 0x22C;
    lbl_804CC0A8->mE = 0x3F;
    lbl_804CC0A8->mA = 0x3F;
    lbl_804CC0A8->m6 = 0x3F;
    lbl_804CC0A8->m10 = 0;
    lbl_804CC0A8->m12 = 0;
    lbl_804CC0A8->m14 = 0;
    lbl_804CC0A8->m16 = 0;
    lbl_804CC0A8->m2 = -1;
    lbl_804CC0A8->m0 = -1;
    lbl_804CC0A8->m18 = 0;
    lbl_804CC0A8->m1A = 0;
    lbl_804CC0A8->m1C = 0;
    fn_8023F1A0("window/deadcount.cms", 0);
}
}
