#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_8010B228(char *);
#else
u32 fn_8010B228();
#endif
extern u8 lbl_8036E6D8[0x258];

s32 fn_801C8858(
#if TARGET_PC
void *arg0
#else
u32 arg0
#endif
) {
#if TARGET_PC
    void *temp_r3;
#else
    u32 temp_r3;
#endif

    if (arg0 == fn_8010B228(lbl_8036E6D8 + 0x5D)) {
        return 0xA;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 0x66)) {
        return 0x14;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 0x74)) {
        return 0x28;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 0x83)) {
        return 0x78;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8)) {
        return 0xA;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 9)) {
        return 0x14;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 0x14)) {
        return 0x78;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 0x20)) {
        return 0xA;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 0x2B)) {
        return 0xA;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 0x37)) {
        return 0x78;
    }
    if (arg0 == fn_8010B228(lbl_8036E6D8 + 0x51)) {
        return 0x78;
    }
    temp_r3 = fn_8010B228(lbl_8036E6D8 + 0x8E);
#if TARGET_PC
    return arg0 == temp_r3 ? 0xF : 0;
#else
    return ((s32) ~((arg0 - temp_r3) | (temp_r3 - arg0)) >> 0x1F) & 0xF;
#endif
}
