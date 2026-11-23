#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
void fn_80035218(int,int,void*,void*,void*);
#if TARGET_PC
FE10_PROTO void fn_80069CE4(void *, void *, int);
#else
void fn_80069CE4(int,int,int);
#endif
extern u8 lbl_804CA138[0x6];
extern u8 lbl_804CA140[0x6];
extern u8 lbl_804CA148[0x6];
void fn_8004B590(int a, int b) {
    fn_80069CE4(a, b, 0);
    fn_80035218(0x138, 0xA0, lbl_804CA148, lbl_804CA140, lbl_804CA138);
}
