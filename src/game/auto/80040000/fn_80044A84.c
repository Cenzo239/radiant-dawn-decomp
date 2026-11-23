#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80062380(char *, char *);
FE10_PROTO void fn_80062454(void *);
#else
M2C_UNK fn_80062380();
M2C_UNK fn_80062454();
#endif
s32 fn_8007857C();
#if TARGET_PC
FE10_PROTO int fn_800785FC(char *, unsigned int);
#else
M2C_UNK fn_800785FC();
#endif
M2C_UNK fn_800787E4();
#if TARGET_PC
FE10_PROTO void fn_80078C2C(char *);
#else
M2C_UNK fn_80078C2C();
#endif
M2C_UNK fn_8012D58C();
M2C_UNK fn_8012D620();
M2C_UNK fn_8012D908();
extern u8 lbl_80361684[0xbc];
extern u8 lbl_803CAB38[0x988];

void fn_80044A84(void) {
    fn_800787E4();
    fn_800785FC(lbl_80361684 + 0x8B, fn_8007857C());
    fn_80078C2C(lbl_80361684 + 0x59);
    fn_8012D58C();
    fn_80062380(lbl_803CAB38, 0);
    fn_80062454(lbl_803CAB38);
    fn_8012D620();
    fn_8012D908();
}
