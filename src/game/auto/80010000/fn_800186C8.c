#include "game/auto/m2c_prelude.h"
M2C_UNK fn_80010980();
#if TARGET_PC
FE10_PROTO void fn_80021860(int, int, unsigned char);
FE10_PROTO void fn_80021BA4(int, int, int, int);
#else
M2C_UNK fn_80021860();
M2C_UNK fn_80021BA4();
#endif

s32 fn_800186C8(s8 *arg0) {
    s32 temp_r0;
    s32 temp_r4_2;
    u16 temp_r4;

    temp_r4 = M2C_FIELD(arg0, u16 *, 4);
    if (!(temp_r4 & 0xE038)) {
        return 0;
    }
    temp_r4_2 = temp_r4 & 0xE000;
    switch (temp_r4_2) {                            /* switch 1; irregular */
    case 0x2000:                                    /* switch 1 */
        fn_80021BA4(1, 4, 1, 0);
        break;
    case 0x4000:                                    /* switch 1 */
        fn_80021BA4(3, 0, 0, 0);
        break;
    case 0x6000:                                    /* switch 1 */
        fn_80021BA4(1, 2, 0, 0);
        break;
    case 0x8000:                                    /* switch 1 */
        fn_80021BA4(1, 2, 2, 0);
        break;
    case 0xA000:                                    /* switch 1 */
        fn_80021BA4(1, 3, 3, 7);
        break;
    }
    temp_r0 = M2C_FIELD(arg0, u16 *, 4) & 0x30;
    switch (temp_r0) {                              /* switch 2; irregular */
    case 16:                                        /* switch 2 */
        fn_80021860(1, 3, 1);
        break;
    case 32:                                        /* switch 2 */
        fn_80021860(0, 3, 0);
        break;
    case 48:                                        /* switch 2 */
        fn_80021860(1, 6, 0);
        break;
    }
    if (M2C_FIELD(arg0, u16 *, 4) & 8) {
        fn_80010980();
    }
    return 0;
}
