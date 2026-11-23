#include "game/auto/m2c_prelude.h"
extern u8 lbl_80387768[0x28];
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA5BC;
FE10_PROTO extern void *lbl_804CA6F0;
FE10_PROTO extern void *lbl_804CA6F4;
FE10_PROTO extern void *lbl_804CA6F8;
#else
extern s32 lbl_804CA5BC;
extern s32 lbl_804CA6F0;
extern s32 lbl_804CA6F4;
extern s32 lbl_804CA6F8;
#endif

void fn_8016CAEC(void) {
    M2C_FIELD(lbl_80387768, s32 *, 0) = (s32) lbl_804CA6F4;
    M2C_FIELD(lbl_80387768, s32 *, 8) = (s32) lbl_804CA6F0;
    M2C_FIELD(lbl_80387768, s32 *, 0x10) = (s32) lbl_804CA5BC;
    M2C_FIELD(lbl_80387768, s32 *, 0x18) = (s32) lbl_804CA6F8;
}
