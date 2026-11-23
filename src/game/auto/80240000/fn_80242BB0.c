#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO char * fn_8008A37C(void *, int);
FE10_PROTO void fn_80242E50(void *, void **);
FE10_PROTO void fn_80243114(void *, void **);
FE10_PROTO void fn_802433D8(void *, void **);
FE10_PROTO void fn_8024369C(void *, void **);
FE10_PROTO void fn_80243960(void *, void **);
FE10_PROTO void fn_80243C24(void *, void **);
FE10_PROTO void fn_80243EE8(void *, void **);
FE10_PROTO void fn_802441AC(void *, void **);
FE10_PROTO int fn_8024CAD0(int, int *);
FE10_PROTO void fn_8024CB10(void *, unsigned int);
#else
s32 fn_8008A37C();
M2C_UNK fn_80242E50();
M2C_UNK fn_80243114();
M2C_UNK fn_802433D8();
M2C_UNK fn_8024369C();
M2C_UNK fn_80243960();
M2C_UNK fn_80243C24();
M2C_UNK fn_80243EE8();
M2C_UNK fn_802441AC();
M2C_UNK fn_8024CAD0();
M2C_UNK fn_8024CB10();
#endif

s32 fn_80242BB0(s32 arg0, s32 arg1) {
    s32 sp44;
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 var_r29;
    s32 var_r29_2;
    s32 var_r29_3;
    s32 var_r29_4;
    s32 var_r29_5;
    s32 var_r29_6;
    s32 var_r29_7;
    s32 var_r29_8;

    fn_8024CAD0(arg1, &sp44);
    fn_8024CB10(arg0, sp44);
    var_r29 = 0;
    goto loop_2;
block_1:
    sp24 = fn_8008A37C(arg1, -1);
    fn_80242E50(arg0, &sp24);
    var_r29 += 1;
loop_2:
    if (var_r29 < sp44) {
        goto block_1;
    }
    fn_8024CAD0(arg1, &sp40);
    fn_8024CB10(arg0 + 0xC, sp40);
    var_r29_2 = 0;
    goto loop_5;
block_4:
    sp20 = fn_8008A37C(arg1, -1);
    fn_80243114(arg0, &sp20);
    var_r29_2 += 1;
loop_5:
    if (var_r29_2 < sp40) {
        goto block_4;
    }
    fn_8024CAD0(arg1, &sp3C);
    fn_8024CB10(arg0 + 0x18, sp3C);
    var_r29_3 = 0;
    goto loop_8;
block_7:
    sp1C = fn_8008A37C(arg1, -1);
    fn_802433D8(arg0, &sp1C);
    var_r29_3 += 1;
loop_8:
    if (var_r29_3 < sp3C) {
        goto block_7;
    }
    fn_8024CAD0(arg1, &sp38);
    fn_8024CB10(arg0 + 0x24, sp38);
    var_r29_4 = 0;
    goto loop_11;
block_10:
    sp18 = fn_8008A37C(arg1, -1);
    fn_8024369C(arg0, &sp18);
    var_r29_4 += 1;
loop_11:
    if (var_r29_4 < sp38) {
        goto block_10;
    }
    fn_8024CAD0(arg1, &sp34);
    fn_8024CB10(arg0 + 0x30, sp34);
    var_r29_5 = 0;
    goto loop_14;
block_13:
    sp14 = fn_8008A37C(arg1, -1);
    fn_80243960(arg0, &sp14);
    var_r29_5 += 1;
loop_14:
    if (var_r29_5 < sp34) {
        goto block_13;
    }
    fn_8024CAD0(arg1, &sp30);
    fn_8024CB10(arg0 + 0x3C, sp30);
    var_r29_6 = 0;
    goto loop_17;
block_16:
    sp10 = fn_8008A37C(arg1, -1);
    fn_80243C24(arg0, &sp10);
    var_r29_6 += 1;
loop_17:
    if (var_r29_6 < sp30) {
        goto block_16;
    }
    fn_8024CAD0(arg1, &sp2C);
    fn_8024CB10(arg0 + 0x48, sp2C);
    var_r29_7 = 0;
    goto loop_20;
block_19:
    spC = fn_8008A37C(arg1, -1);
    fn_80243EE8(arg0, &spC);
    var_r29_7 += 1;
loop_20:
    if (var_r29_7 < sp2C) {
        goto block_19;
    }
    fn_8024CAD0(arg1, &sp28);
    fn_8024CB10(arg0 + 0x54, sp28);
    var_r29_8 = 0;
    goto loop_23;
block_22:
    sp8 = fn_8008A37C(arg1, -1);
    fn_802441AC(arg0, &sp8);
    var_r29_8 += 1;
loop_23:
    if (var_r29_8 < sp28) {
        goto block_22;
    }
    return 1;
}
