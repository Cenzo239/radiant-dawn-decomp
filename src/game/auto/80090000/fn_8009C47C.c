#include "game/auto/m2c_prelude.h"
s32 * fn_8006074C();
#if TARGET_PC
FE10_PROTO int fn_80291188(char *, char *);
#else
s32 fn_80291188();
#endif
extern u8 lbl_803CAB38[0x988];
extern u8 lbl_804CA0A4[0x7];

s32 fn_8009C47C(void) {
    return fn_80291188(lbl_804CA0A4, *fn_8006074C(lbl_803CAB38)) == 0;
}
