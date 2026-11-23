#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO int fn_800C3C3C(char *, void *, unsigned char);
#else
M2C_UNK fn_800C3C3C();
#endif
extern u8 fn_8008DA3C[0x110];
extern u8 fn_8008DD14[0x14];
extern u8 fn_8008DD28[0x14];
extern u8 fn_8008DD3C[0x74];
extern u8 fn_8008DDB0[0xac];
extern u8 fn_8008DE5C[0x78];
extern u8 fn_8008DED4[0x78];
extern u8 fn_8008DF4C[0x130];
extern u8 fn_8008E07C[0x134];
extern u8 fn_8008E1B0[0xa8];
extern u8 fn_8008E258[0x38];
extern u8 lbl_803631E0[0x110];

void fn_8008E290(void) {
    fn_800C3C3C(lbl_803631E0 + 0x4D, fn_8008DA3C, 2);
    fn_800C3C3C(lbl_803631E0 + 0x58, fn_8008DD14, 0);
    fn_800C3C3C(lbl_803631E0 + 0x68, fn_8008DD28, 0);
    fn_800C3C3C(lbl_803631E0 + 0x77, fn_8008DD3C, 1);
    fn_800C3C3C(lbl_803631E0 + 0x8B, fn_8008DDB0, 0);
    fn_800C3C3C(lbl_803631E0 + 0x9A, fn_8008DE5C, 0);
    fn_800C3C3C(lbl_803631E0 + 0xB0, fn_8008DED4, 0);
    fn_800C3C3C(lbl_803631E0 + 0xC0, fn_8008DF4C, 0);
    fn_800C3C3C(lbl_803631E0 + 0xD2, fn_8008E07C, 0);
    fn_800C3C3C(lbl_803631E0 + 0xE4, fn_8008E1B0, 0);
    fn_800C3C3C(lbl_803631E0 + 0xF7, fn_8008E258, 0);
}
