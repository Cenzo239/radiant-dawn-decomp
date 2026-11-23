#include "game/auto/m2c_prelude.h"
#if TARGET_PC
/* Host: the m2c draft drops the tail-call result; the function returns the block. */
void* fn_8030E344(u32 heap, u32 size, s32 align);
extern u32 lbl_804CBF40;

void* fn_80079940(s32 arg0, s32 arg1) {
    return fn_8030E344(lbl_804CBF40, (arg0 + 0x1F) & 0xFFFFFFE0, (arg1 + 0x1F) & 0xFFFFFFE0);
}
#else
M2C_UNK fn_8030E344();
extern s32 lbl_804CBF40;

void fn_80079940(s32 arg0, s32 arg1) {
    fn_8030E344(lbl_804CBF40, (arg0 + 0x1F) & 0xFFFFFFE0, (arg1 + 0x1F) & 0xFFFFFFE0);
}
#endif
