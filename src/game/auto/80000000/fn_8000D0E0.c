#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8017F480(unsigned int *, unsigned int *, unsigned int);
FE10_PROTO void fn_8017F4A0(unsigned int *, unsigned int *, unsigned int);
#else
M2C_UNK fn_8017F480();
M2C_UNK fn_8017F4A0();
#endif

void fn_8000D0E0(s8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg2 & 8) {
        fn_8017F480(arg3, arg1 + 0x40, 0xC);
        if (arg2 & 0x100) {
            fn_8017F480(arg3 + 0x3C, arg1 + 0x7C, 0xC);
            if (arg2 & 0x400) {
                fn_8017F480(arg3 + 0x54, arg1 + 0x94, 0xC);
            }
        }
    }
    if (arg2 & 0x20) {
        fn_8017F480(arg3 + 0x18, arg1 + 0x58, 0xC);
    }
    if (arg2 & 0x10) {
        fn_8017F480(arg3 + 0xC, arg1 + 0x4C, 0xC);
        if (arg2 & 0x40) {
            fn_8017F480(arg3 + 0x24, arg1 + 0x64, 0xC);
        }
        if (arg2 & 0x800) {
            fn_8017F480(arg3 + 0x60, arg1 + 0xA0, 0xC);
        }
        if (arg2 & 0x80) {
            fn_8017F480(arg3 + 0x30, arg1 + 0x70, 0xC);
            if (arg2 & 0x200) {
                fn_8017F480(arg3 + 0x48, arg1 + 0x88, 0xC);
            }
        }
        if ((arg0 != NULL) && (M2C_FIELD(arg0, s32 *, 0xC) & 2)) {
            fn_8017F4A0(arg3 + 0x6C, arg1 + 0xAC, 0x10);
        }
    }
}
