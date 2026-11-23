#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void * fn_80007F3C(void *);
#else
s8 * fn_80007F3C();
#endif
s32 fn_8000F478();
#if TARGET_PC
FE10_PROTO void fn_8000F484(char);
FE10_PROTO void fn_80011838(int);
FE10_PROTO void fn_80017D94(void *);
FE10_PROTO int fn_80018208(void *, int);
FE10_PROTO void fn_80018888(unsigned int *, int);
#else
M2C_UNK fn_8000F484();
M2C_UNK fn_80011838();
M2C_UNK fn_80017D94();
s32 fn_80018208();
M2C_UNK fn_80018888();
#endif

void fn_8001A218(s32 arg0, s8 *arg1) {
    s32 temp_r30;
    s8 *temp_r31;

    temp_r31 = fn_80007F3C(arg1);
    if ((s32) M2C_FIELD(arg1, u8 *, 0xB) != 0) {
        temp_r30 = fn_8000F478();
        switch (arg0) {                             /* irregular */
        case 1:
            if ((s32) M2C_FIELD(temp_r31, s32 *, 0x3C) != 0) {
                fn_80011838(1);
                if (fn_80018208(arg1, 1) == 0) {
                    fn_80018888(arg1, 1);
                }
            }
            break;
        case 2:
            if ((s32) M2C_FIELD(temp_r31, s32 *, 0x40) != 0) {
                fn_80011838(2);
                if (fn_80018208(arg1, 2) == 0) {
                    fn_80018888(arg1, 2);
                }
            }
            break;
        case 3:
            if ((s32) M2C_FIELD(temp_r31, s32 *, 0x44) != 0) {
                fn_80011838(3);
                if (fn_80018208(arg1, 3) == 0) {
                    fn_80018888(arg1, 3);
                }
            }
            if ((s32) M2C_FIELD(arg1, s32 *, 0x54) != 0) {
                fn_80011838(3);
                fn_80017D94(arg1);
            }
            break;
        default:
            if ((u8) M2C_FIELD(arg1, u8 *, 0xB) != 0xFF) {
                fn_80011838(3);
                if (((s32) M2C_FIELD(temp_r31, s32 *, 0x3C) != 0) && (fn_80018208(arg1, 1) == 0)) {
                    fn_80018888(arg1, 1);
                }
                if (((s32) M2C_FIELD(temp_r31, s32 *, 0x40) != 0) && (fn_80018208(arg1, 2) == 0)) {
                    fn_80018888(arg1, 2);
                }
                if (((s32) M2C_FIELD(temp_r31, s32 *, 0x44) != 0) && (fn_80018208(arg1, 3) == 0)) {
                    fn_80018888(arg1, 3);
                }
                if ((s32) M2C_FIELD(arg1, s32 *, 0x54) != 0) {
                    fn_80017D94(arg1);
                }
            } else {
                if ((s32) M2C_FIELD(temp_r31, s32 *, 0x3C) != 0) {
                    fn_80011838(1);
                    if (fn_80018208(arg1, 1) == 0) {
                        fn_80018888(arg1, 1);
                    }
                }
                if ((s32) M2C_FIELD(temp_r31, s32 *, 0x40) != 0) {
                    fn_80011838(2);
                    if (fn_80018208(arg1, 2) == 0) {
                        fn_80018888(arg1, 2);
                    }
                }
                if ((s32) M2C_FIELD(temp_r31, s32 *, 0x44) != 0) {
                    fn_80011838(3);
                    if (fn_80018208(arg1, 3) == 0) {
                        fn_80018888(arg1, 3);
                    }
                }
                if ((s32) M2C_FIELD(arg1, s32 *, 0x54) != 0) {
                    fn_80011838(3);
                    fn_80017D94(arg1);
                }
            }
            break;
        }
        fn_8000F484(temp_r30);
        fn_80011838(temp_r30);
    }
}
