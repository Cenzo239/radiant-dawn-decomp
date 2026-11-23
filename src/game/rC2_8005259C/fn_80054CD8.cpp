#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" void fn_80054CD8(void) {
    Word* w = fn_800CFD3C(&lbl_803E7320);
    fn_80108E20(fn_800CFB0C(w) + 0x110, *((u32*)w + 1));
}

extern "C" void fn_80054D20(void* p) {
    fn_80026CD8(&lbl_803C8E80, fn_800CFB0C(fn_800CFD3C(&lbl_803E7320)), -1);
    fn_8002C170(&lbl_803C8E80);
    fn_800262D8((u8*)&lbl_803C8E80 + 0xde0);
    fn_800E990C(p, fn_80054CD8);
}
