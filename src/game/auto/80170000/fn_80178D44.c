#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80009974(void *);
#else
M2C_UNK fn_80009974();
#endif
M2C_UNK fn_80020EEC();
#if TARGET_PC
FE10_PROTO void fn_80078E24(void *);
#else
M2C_UNK fn_80078E24();
#endif

void fn_80178D44(s8 *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x50) & 4) {
        fn_80009974(M2C_FIELD(arg0, s32 *, 0x30));
    }
    if (M2C_FIELD(arg0, u8 *, 0x50) & 8) {
        fn_80020EEC();
    }
    fn_80078E24(M2C_FIELD(arg0, s32 *, 0x44));
    M2C_FIELD(arg0, s32 *, 0x44) = 0;
    fn_80078E24(M2C_FIELD(arg0, s32 *, 0x40));
    M2C_FIELD(arg0, s32 *, 0x40) = 0;
}
