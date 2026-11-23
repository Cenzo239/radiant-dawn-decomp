#include "game/auto/m2c_prelude.h"
#pragma use_lmw_stmw on
#if TARGET_PC
FE10_PROTO void * fn_80060728(void *);
#else
s8 * fn_80060728();
#endif
#if TARGET_PC
FE10_PROTO int * fn_801D5DC4(void);
#else
s32 fn_801D5DC4();
#endif
M2C_UNK fn_801D5EC8();
#if TARGET_PC
FE10_PROTO void fn_8023F1A0(char *, int);
#else
M2C_UNK fn_8023F1A0();
#endif
M2C_UNK strcpy();
extern u8 lbl_8038C088[0x14];
extern u8 lbl_8038C09C[0x14];
extern u8 lbl_8038C0B0[0x14];
extern u8 lbl_803CAB38[0x988];

void fn_801D2BB0(void) {
    u8 sp8[0x44];
    u8 temp_r0;

    fn_801D5EC8();
    fn_8023F1A0(fn_801D5DC4(), 0x80);
    temp_r0 = M2C_FIELD(fn_80060728(lbl_803CAB38), u8 *, 0x11);
    switch ((s32) temp_r0) {                        /* irregular */
    case 3:
    case 0:
        strcpy(sp8, lbl_8038C0B0);
        break;
    case 1:
        strcpy(sp8, lbl_8038C09C);
        break;
    case 2:
        strcpy(sp8, lbl_8038C088);
        break;
    }
    fn_8023F1A0(sp8, 0x80);
}

