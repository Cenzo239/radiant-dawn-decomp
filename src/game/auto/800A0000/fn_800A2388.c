#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80076F54(char *);
FE10_PROTO void * fn_80081050(void *, void *);
FE10_PROTO void fn_80084F0C(char *, ...);
#else
s32 fn_80076F54();
s8 * fn_80081050();
M2C_UNK fn_80084F0C();
#endif
#if TARGET_PC
FE10_PROTO char * fn_802910CC(char *, char *, unsigned int);
#else
M2C_UNK fn_802910CC();
#endif
extern u8 lbl_80364C1C[0x424];
extern u8 lbl_80381BF0[0x2c];
extern u8 lbl_803E5064[0x24];

s32 fn_800A2388(s8 *arg0) {
    s8 *temp_r3;

    fn_80084F0C(lbl_80364C1C + 5, lbl_80364C1C);
    if (fn_80076F54(arg0) == 0) {
        return 0;
    }
    temp_r3 = fn_80081050(lbl_80381BF0, 2);
    fn_802910CC(temp_r3 + 0x30, arg0, 0x1F);
    M2C_FIELD(temp_r3, s8 *, 0x4F) = 0;
    M2C_FIELD(temp_r3, s32 *, 0x50) = fn_80076F54(temp_r3 + 0x30);
    M2C_FIELD(temp_r3, s8 *, 0x58) = 1;
    M2C_FIELD(temp_r3, M2C_UNK **, 0x54) = lbl_803E5064;
    return 1;
}
