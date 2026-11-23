#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_800F0994(char *, ...);
FE10_PROTO void * fn_80102928(void *, int, int, unsigned short, void *);
#else
s32 fn_800F0994();
M2C_UNK fn_80102928();
#endif
extern u8 lbl_80367D50[0x140];

void fn_8010139C(s8 *arg0) {
    s32 temp_r31;

    temp_r31 = M2C_FIELD(arg0, s32 *, 0x34);
    fn_80102928(temp_r31, fn_800F0994(lbl_80367D50 + 5, lbl_80367D50), 4, 0, 0);
}
