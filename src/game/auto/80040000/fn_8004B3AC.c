#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void fn_80035218(int, int, char *, char *, char *);
FE10_PROTO int fn_80060754(void *);
FE10_PROTO void fn_80069CE4(void *, void *, int);
#else
M2C_UNK fn_80035218();
s32 fn_80060754();
void fn_80069CE4(int,int,int);
#endif
extern u8 lbl_803CAB38[0x988];
extern u8 lbl_804CA0E8[0x6];
extern u8 lbl_804CA0F0[0x6];
extern u8 lbl_804CA0F8[0x6];
extern u8 lbl_804CA100[0x6];
extern u8 lbl_804CA108[0x6];
extern u8 lbl_804CA110[0x6];

void fn_8004B3AC(int a, int b) {
    fn_80069CE4(a, b, 0);
    if (fn_80060754(lbl_803CAB38) != 0) {
        fn_80035218(0x138, 0xA0, lbl_804CA110, lbl_804CA108, lbl_804CA100);
        return;
    }
    fn_80035218(0x138, 0xA0, lbl_804CA0F8, lbl_804CA0F0, lbl_804CA0E8);
}

