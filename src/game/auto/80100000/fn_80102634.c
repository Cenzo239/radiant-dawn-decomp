#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80007F10(void *);
FE10_PROTO void fn_80083DC4(void *, int);
FE10_PROTO int fn_800F0994(char *, ...);
FE10_PROTO void * fn_80102928(void *, int, int, unsigned short, void *);
#else
s8 * fn_80007F10();
M2C_UNK fn_80083DC4();
s32 fn_800F0994();
M2C_UNK fn_80102928();
#endif
extern u8 lbl_80367D50[0x140];

void fn_80102634(s8 *arg0) {
    s32 temp_r0;
    s32 temp_r3;
    s8 *temp_r3_2;
    s8 *temp_r5;

    temp_r3 = fn_800F0994(lbl_80367D50 + 0x11C, lbl_80367D50);
    temp_r5 = M2C_FIELD(arg0, s8 **, 0x30);
    if (temp_r3 == (s8) M2C_FIELD(temp_r5, u8 *, 0xC7)) {
        fn_80083DC4(arg0, 0);
        return;
    }
    fn_80102928(temp_r5, temp_r3, 0x10, 0, 0);
    temp_r3_2 = fn_80007F10(M2C_FIELD(arg0, s8 **, 0x30) + 0x28);
    if (temp_r3_2 == NULL) {
        fn_80083DC4(arg0, 0x63);
        return;
    }
    temp_r0 = (M2C_FIELD(temp_r3_2, s32 *, 0x18) - M2C_FIELD(temp_r3_2, s32 *, 0x14)) - 8;
    M2C_FIELD(arg0, s32 *, 0x3C) = temp_r0;
    if (temp_r0 < 0) {
        M2C_FIELD(arg0, s32 *, 0x3C) = 0;
    }
    M2C_FIELD(arg0, s32 *, 0x34) = 0;
}
