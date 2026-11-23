#include "game/rC2_8005259C/more.h"
#pragma use_lmw_stmw on

extern "C" void fn_80055024(E55* e) {
    fn_8002BCC4(&lbl_803C8E80);
    if (!((U5*)&lbl_803C8E80)->b114) {
        switch (((U5*)&lbl_803C8E80)->f4->b8) {
        case 0: GD3P->c8++; GD3P->hc0++; break;
        case 1: GD3P->cc++; GD3P->hc2++; e->u->h384++; e->u->h386++; break;
        case 2: GD3P->d0++; GD3P->hc4++; break;
        case 3: GD3P->d4++; GD3P->hc6++; break;
        }
    }
    fn_80026C44(&lbl_803C8E80, e->u, fn_800CFB0C(fn_800CFD3C(&lbl_803E7320)));
    if (e->b3b) {
        ((u8*)&lbl_803C8E80)[0x492] = 1;
    }
    fn_8006C440(&lbl_803C8E80);
    if (e->b3a < ((u8*)&lbl_803C8E80)[0x47f]) {
        e->b3a = ((u8*)&lbl_803C8E80)[0x47f];
    }
}
