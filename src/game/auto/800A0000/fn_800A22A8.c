#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80083B78(void *);
FE10_PROTO void * fn_800C357C(void);
FE10_PROTO void fn_801D0D58(void *, unsigned char *);
FE10_PROTO int fn_801D0E18(char *);
#else
M2C_UNK fn_80083B78();
s32 fn_800C357C();
M2C_UNK fn_801D0D58();
M2C_UNK fn_801D0E18();
#endif

void fn_800A22A8(s8 *arg0) {
    if ((s32) M2C_FIELD(arg0, u8 *, 0x58) != 0) {
        M2C_FIELD(arg0, u8 *, 0x58) = 0U;
        fn_801D0D58(M2C_FIELD(arg0, s32 *, 0x54), M2C_FIELD(arg0, s32 *, 0x50));
    }
    fn_801D0E18(M2C_FIELD(arg0, s32 *, 0x54));
    if (fn_800C357C() != 6) {
        fn_80083B78(arg0);
    }
}
