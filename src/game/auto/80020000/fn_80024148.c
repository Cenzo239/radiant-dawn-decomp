#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80083DC4(void *, int);
#else
M2C_UNK fn_80083DC4();
#endif
M2C_UNK fn_8012FCC0();
extern u8 lbl_803CA870[0x130];

void fn_80024148(s8 *arg0) {
    fn_8012FCC0();
    switch ((s32) M2C_FIELD(lbl_803CA870, u8 *, 0xC)) { /* irregular */
    case 0x81:
        fn_80083DC4(arg0, 0xBU);
        return;
    case 0x80:
        fn_80083DC4(arg0, M2C_FIELD(arg0, u8 *, 0x54));
        return;
    }
}
