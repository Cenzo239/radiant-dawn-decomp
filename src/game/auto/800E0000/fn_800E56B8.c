#include "game/auto/m2c_prelude.h"
#if TARGET_PC
FE10_PROTO void fn_800180F0(void *);
FE10_PROTO void fn_8001A610(void *);
FE10_PROTO void fn_8001AFE0(char *);
FE10_PROTO void fn_8001B134(unsigned char *);
FE10_PROTO void fn_8001B254(void *);
#else
M2C_UNK fn_800180F0();
M2C_UNK fn_8001A610();
M2C_UNK fn_8001AFE0();
M2C_UNK fn_8001B134();
M2C_UNK fn_8001B254();
#endif
M2C_UNK fn_8007E154();
M2C_UNK fn_8007E164();
#if TARGET_PC
FE10_PROTO void fn_8007E174(void *, unsigned short);
FE10_PROTO void fn_8007E4E4(float, float, float, float, ...);
FE10_PROTO void fn_8007E7DC(unsigned char);
FE10_PROTO void fn_800800D4(unsigned int);
#else
M2C_UNK fn_8007E174();
M2C_UNK fn_8007E4E4();
M2C_UNK fn_8007E7DC();
M2C_UNK fn_800800D4();
#endif
M2C_UNK fn_80080308();
#if TARGET_PC
FE10_PROTO void fn_80080910(int, int);
#else
M2C_UNK fn_80080910();
#endif
extern u8 fn_800E3594[0x80];
extern f32 lbl_804CD8D8;
extern f32 lbl_804CD8FC;

void fn_800E56B8(s8 *arg0) {
    s32 temp_r3;
    s32 temp_r31;
    s8 *temp_r4;
    s32 temp_r5;

    temp_r4 = M2C_FIELD(arg0, s8 **, 0x30);
    temp_r31 = M2C_FIELD(temp_r4, s32 *, 0);
    if (temp_r31 != 0) {
        temp_r5 = M2C_FIELD(temp_r4, s32 *, 0x18);
        if (!(temp_r5 & 8) && !(M2C_FIELD(M2C_FIELD(temp_r4, s8 **, 0xC4), u16 *, 8) & 7)) {
            if (temp_r5 & 0x100) {
                fn_8001B254(temp_r31);
            }
            fn_800180F0(temp_r31);
            fn_8001AFE0(temp_r31);
            fn_8001A610(temp_r31);
            fn_8001B134(temp_r31);
            return;
        }
        fn_8007E154();
        temp_r3 = M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x30), s16 *, 8);
        fn_8007E4E4(temp_r3, lbl_804CD8D8, lbl_804CD8D8, (f32) temp_r3, lbl_804CD8FC);
        fn_8007E174(0, 0x410);
        fn_8007E7DC(0xFF);
        fn_8007E164();
        fn_800800D4(0xB);
        fn_80080910(fn_800E3594, temp_r31);
        fn_80080308();
    }
}
