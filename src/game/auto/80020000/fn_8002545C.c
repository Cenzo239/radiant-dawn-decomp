#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80060728(void *);
#else
s8 * fn_80060728();
#endif
M2C_UNK fn_80193054();
s32 fn_80245DFC(s8 *);
#if TARGET_PC
FE10_PROTO void fn_8024BA84(unsigned char, void *);
#else
M2C_UNK fn_8024BA84();
#endif
s8 * fn_8024BCA0();
#if TARGET_PC
FE10_PROTO void fn_8028392C(void *, int, int, unsigned char, void *, int);
#else
M2C_UNK fn_8028392C();
#endif
extern u8 lbl_80361260[0xa8];
extern u8 lbl_803CAB38[0x988];

void fn_8002545C(s32 arg0) {
    s8 *temp_r31;

    temp_r31 = fn_8024BCA0();
    if (fn_80245DFC(temp_r31) != 0) {
        fn_8024BA84(M2C_FIELD(temp_r31, u8 *, 0x30), arg0);
    }
    fn_80193054();
    if ((u8) M2C_FIELD(fn_80060728(lbl_803CAB38), u8 *, 0x11) == 2) {
        fn_8028392C(lbl_80361260, 0, 0, 0, arg0, 1);
        return;
    }
    fn_8028392C(lbl_80361260 + 0xF, 0, 0, 0, arg0, 1);
}
