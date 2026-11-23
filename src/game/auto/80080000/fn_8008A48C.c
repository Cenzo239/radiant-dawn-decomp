#include "game/auto/m2c_prelude.h"
#if TARGET_PC
/* Host: stream object layout of MemStream (rD fn_80089AA8.cpp, TARGET_PC): base 0,
   cur 8, size 0x10, owned 0x18, vtbl 0x20; arg1 is the data pointer. */
extern u8 lbl_803810B0[];

void fn_8008A48C(s8 *arg0, void* arg1) {
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    M2C_FIELD(arg0, void **, 0x20) = lbl_803810B0;
    M2C_FIELD(arg0, void **, 8) = arg1;
    M2C_FIELD(arg0, void **, 0) = arg1;
    M2C_FIELD(arg0, s8 *, 0x18) = 0;
}
#else
extern u8 lbl_803810B0[0x18];

void fn_8008A48C(s8 *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0x10) = lbl_803810B0;
    M2C_FIELD(arg0, s32 *, 4) = arg1;
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s8 *, 0xC) = 0;
}
#endif
