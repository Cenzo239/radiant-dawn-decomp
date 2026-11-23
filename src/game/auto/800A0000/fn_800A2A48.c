#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80085708(char *, ...);
FE10_PROTO void fn_8014BED4(char *, void *);
FE10_PROTO void fn_8014C148(void *);
#else
s32 fn_80085708();
M2C_UNK fn_8014BED4();
M2C_UNK fn_8014C148();
#endif
extern u8 lbl_80364C1C[0x424];

s32 fn_800A2A48(s32 arg0) {
    if (fn_80085708(lbl_80364C1C + 0x14, lbl_80364C1C) != 0) {
        fn_8014C148(arg0);
        return 1;
    }
    fn_8014BED4(arg0, 0);
    return 1;
}
