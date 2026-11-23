#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
/* Host: name is a pointer. The +0x50 flags offset is the Wii FE layout; on the host FE
   (rI fn_fe.h, vptr 8 bytes) the field is at another offset - unreached in M1 because
   the host file layer registers no FE entries (fn_8023DCC0 returns NULL). */
u8* fn_8023DCC0(const char*);
s32 fn_8023F7EC(const char* a, s32 arg1) {
    u8 *t = fn_8023DCC0(a);
    s32 r;
    if (t != NULL) {
        r = *(s32*)(t + 0x50) | arg1;
        *(s32*)(t + 0x50) = r;
    } else {
        r = 0;
    }
    return r;
}
#else
u8* fn_8023DCC0(int);
s32 fn_8023F7EC(int a, s32 arg1) {
    u8 *t = fn_8023DCC0(a);
    s32 r;
    if (t != NULL) {
        r = *(s32*)(t + 0x50) | arg1;
        *(s32*)(t + 0x50) = r;
    } else {
        r = 0;
    }
    return r;
}
#endif
