#include "game/auto/m2c_prelude.h"
M2C_UNK DCFlushRange();
M2C_UNK DCInvalidateRange();
s32 OSEnableInterrupts();
M2C_UNK OSRestoreInterrupts();
#if TARGET_PC
FE10_PROTO void fn_80237590(short *, short *, unsigned int);
#else
M2C_UNK fn_80237590();
#endif
M2C_UNK fn_802BCDA4();
s32 fn_802BCE44();
extern u8 lbl_804206C0[0x300];
extern s32 lbl_804CBF5C;
extern M2C_UNK (*lbl_804CBF60)();
extern s32 lbl_804CBF64;
extern s32 lbl_804CBF68;
extern s32 lbl_804CBF6C;

void fn_80237428(void) {
    s32 temp_r30;
    s32 temp_r30_2;
    s32 temp_r3;
    s32 temp_r5;

    if ((s32) lbl_804CBF6C == 0) {
        temp_r3 = lbl_804CBF5C ^ 1;
        lbl_804CBF5C = temp_r3;
        fn_802BCDA4(lbl_804206C0 + (temp_r3 * 0x180), 0x180);
        temp_r30 = OSEnableInterrupts();
        fn_80237590(lbl_804206C0 + (lbl_804CBF5C * 0x180), 0, 0x60);
        DCFlushRange(lbl_804206C0 + (lbl_804CBF5C * 0x180), 0x180);
        OSRestoreInterrupts(temp_r30);
        return;
    }
    if ((s32) lbl_804CBF6C == 1) {
        if ((s32) lbl_804CBF64 != 0) {
            lbl_804CBF68 = lbl_804CBF64;
        }
        lbl_804CBF60();
        lbl_804CBF64 = fn_802BCE44() + 0x80000000;
    } else {
        lbl_804CBF60();
        lbl_804CBF68 = fn_802BCE44() + 0x80000000;
    }
    temp_r5 = lbl_804CBF5C ^ 1;
    lbl_804CBF5C = temp_r5;
    fn_802BCDA4(lbl_804206C0 + (temp_r5 * 0x180), 0x180, temp_r5);
    temp_r30_2 = OSEnableInterrupts();
    if ((s32) lbl_804CBF68 != 0) {
        DCInvalidateRange(lbl_804CBF68, 0x180);
    }
    fn_80237590(lbl_804206C0 + (lbl_804CBF5C * 0x180), lbl_804CBF68, 0x60);
    DCFlushRange(lbl_804206C0 + (lbl_804CBF5C * 0x180), 0x180);
    OSRestoreInterrupts(temp_r30_2);
}
