#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80075FB4(void *, int, ...);
#else
M2C_UNK fn_80075FB4();
#endif
M2C_UNK fn_801E74CC();
#if TARGET_PC
FE10_PROTO void fn_8024B654(void *);
#else
M2C_UNK fn_8024B654();
#endif
extern u8 lbl_80366184[0xb4];

void fn_800CDA94(s32 arg0) {
    fn_80075FB4(lbl_80366184 + 9, 0xA0, lbl_80366184);
    fn_801E74CC();
    fn_8024B654(arg0);
}
