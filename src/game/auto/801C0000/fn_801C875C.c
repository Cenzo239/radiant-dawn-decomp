#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_8010B228(char *);
#else
u32 fn_8010B228();
#endif
extern u8 lbl_8036E6D8[0x258];

s32 fn_801C875C(u32 arg0) {
    u32 temp_r3;

    if (arg0 == fn_8010B228(lbl_8036E6D8)) {
        return 5;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 9)) {
        return 0xF;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 0x14)) {
        return 0x19;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 0x20)) {
        return 0x14;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 0x2B)) {
        return 0x1E;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 0x37)) {
        return 0x1E;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 0x46)) {
        return 0x14;
    }
    temp_r3 = fn_8010B228(lbl_8036E6D8 + 0x51);
    return ((s32) ~((arg0 - temp_r3) | (temp_r3 - arg0)) >> 0x1F) & 0x14;
}
