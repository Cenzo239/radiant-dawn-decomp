#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_800265B4(void *, void *);
#else
M2C_UNK fn_800265B4();
#endif
M2C_UNK fn_8002E508(void *, void *);
M2C_UNK strcpy();

s8 *fn_80026898(s8 *arg0, s8 *arg1) {
    if (arg1 != arg0) {
        fn_8002E508(arg0, arg1);
        fn_8002E508(arg0 + 0x4A0, arg1 + 0x4A0);
        fn_8002E508(arg0 + 0x940, arg1 + 0x940);
        M2C_FIELD(arg0, s32 *, 0x15F0) = (s32) M2C_FIELD(arg1, s32 *, 0x15F0);
        M2C_FIELD(arg0, s32 *, 0x15F4) = (s32) M2C_FIELD(arg1, s32 *, 0x15F4);
        M2C_FIELD(arg0, s32 *, 0x15EC) = (s32) M2C_FIELD(arg1, s32 *, 0x15EC);
        fn_800265B4(arg0 + 0xDE0, arg1 + 0xDE0);
        M2C_FIELD(arg0, s32 *, 0x15E8) = (s32) M2C_FIELD(arg1, s32 *, 0x15E8);
        M2C_FIELD(arg0, s32 *, 0x15F8) = (s32) M2C_FIELD(arg1, s32 *, 0x15F8);
        M2C_FIELD(arg0, u8 *, 0x15FD) = (u8) M2C_FIELD(arg1, u8 *, 0x15FD);
        M2C_FIELD(arg0, s32 *, 0x1600) = (s32) M2C_FIELD(arg1, s32 *, 0x1600);
        strcpy(arg0 + 0x1604, arg1 + 0x1604);
        strcpy(arg0 + 0x1624, arg1 + 0x1624);
    }
    return arg0;
}
