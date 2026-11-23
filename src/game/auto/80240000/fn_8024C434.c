#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_8004A55C(void *, void *);
FE10_PROTO void fn_80062DE0(void *, void *);
FE10_PROTO void fn_80066B84(void *, void *);
FE10_PROTO void fn_8008A43C(char *, int, void *);
FE10_PROTO int fn_8008A518(void *, char *);
FE10_PROTO void fn_801057DC(void *, void *);
FE10_PROTO void fn_80105928(void *);
FE10_PROTO void fn_80113274(void *);
FE10_PROTO void fn_80119CD8(void *);
FE10_PROTO void fn_8012D3EC(void *);
FE10_PROTO void fn_80134B80(void *);
FE10_PROTO void fn_8017DA48(int);
FE10_PROTO void fn_80245F9C(void *, void *);
#else
M2C_UNK fn_8004A55C();
M2C_UNK fn_80062DE0();
M2C_UNK fn_80066B84();
M2C_UNK fn_8008A43C();
M2C_UNK fn_8008A518();
M2C_UNK fn_801057DC();
M2C_UNK fn_80105928();
M2C_UNK fn_80113274();
M2C_UNK fn_80119CD8();
M2C_UNK fn_8012D3EC();
M2C_UNK fn_80134B80();
M2C_UNK fn_8017DA48();
M2C_UNK fn_80245F9C();
#endif
extern u8 lbl_80372B4C[0x134];
extern u8 lbl_803CA870[0x130];
extern u8 lbl_803CAB38[0x988];
extern u8 lbl_803CB770[0x10];
extern u8 lbl_803E9000[0x288];
extern u8 lbl_803E9288[0x18];
extern u8 lbl_80429400[0x1070];

s32 fn_8024C434(
#if TARGET_PC
void *arg0
#else
s32 arg0
#endif
) {
    fn_80245F9C(lbl_80429400, arg0);
    fn_8008A518(arg0, lbl_80372B4C + 0xC4);
    fn_80062DE0(lbl_803CAB38, arg0);
    fn_8008A518(arg0, lbl_80372B4C + 0xC9);
    fn_80134B80(arg0);
    fn_8008A518(arg0, lbl_80372B4C + 0xCE);
    fn_8012D3EC(arg0);
    fn_8008A518(arg0, lbl_80372B4C + 0xD3);
    fn_80105928(arg0);
    fn_801057DC(lbl_803E9000, arg0);
    fn_8008A518(arg0, lbl_80372B4C + 0xD8);
    fn_8008A43C(arg0, 0xC, lbl_803E9288);
    fn_8008A518(arg0, lbl_80372B4C + 0xDD);
    fn_80066B84(lbl_803CB770, arg0);
    fn_8008A518(arg0, lbl_80372B4C + 0xE2);
    fn_80119CD8(arg0);
    fn_8008A518(arg0, lbl_80372B4C + 0xE7);
    fn_80113274(arg0);
    fn_8008A518(arg0, lbl_80372B4C + 0xF2);
    fn_8004A55C(lbl_803CA870, arg0);
    fn_8008A518(arg0, lbl_80372B4C + 0xEC);
    fn_8017DA48(arg0);
    return 1;
}
