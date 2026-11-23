#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_80244D90(void *);
FE10_PROTO void fn_80245DC4(void *);
FE10_PROTO int * fn_8024BC94(void);
FE10_PROTO int * fn_8024BCA0(void);
FE10_PROTO void fn_8028392C(void *, int, int, unsigned char, void *, int);
#else
M2C_UNK fn_80244D90(M2C_UNK);
M2C_UNK fn_80245DC4(M2C_UNK);
M2C_UNK fn_8024BC94();
M2C_UNK fn_8024BCA0();
M2C_UNK fn_8028392C();
#endif
extern u8 lbl_80361260[0xa8];
extern s32 lbl_804CB700;

void fn_80025660(s32 arg0) {
    fn_8028392C(lbl_80361260 + 0x47, 0, 0, 1, arg0, 1);
    lbl_804CB700 = lbl_804CB700 | 0x200000 | 0x100;
    fn_80244D90(fn_8024BC94());
    fn_80245DC4(fn_8024BCA0());
}
