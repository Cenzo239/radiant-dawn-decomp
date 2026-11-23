#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800C900C(int, int);
#else
M2C_UNK fn_800C900C();
#endif
u16 fn_800C9078();
#if TARGET_PC
FE10_PROTO void fn_80250E38(char, float, float);
FE10_PROTO void fn_80250F0C(char, float, float);
FE10_PROTO void fn_80250FE0(char, float, float);
#else
M2C_UNK fn_80250E38();
M2C_UNK fn_80250F0C();
M2C_UNK fn_80250FE0();
#endif
extern f32 lbl_804CD248;
extern f32 lbl_804CD24C;

void fn_8009E36C(void) {
    if (fn_800C9078() == 6) {
        fn_800C900C(2, 0x85);
    }
    fn_80250E38(1, lbl_804CD248, lbl_804CD24C);
    fn_80250F0C(1, lbl_804CD248, lbl_804CD24C);
    fn_80250FE0(1, lbl_804CD248, lbl_804CD24C);
}
