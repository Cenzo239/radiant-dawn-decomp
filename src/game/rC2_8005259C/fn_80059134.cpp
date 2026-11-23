#include "game/rC2_8005259C/more.h"
#pragma use_lmw_stmw on
extern s8 lbl_804CB490; extern void* lbl_804CB494; extern u8 lbl_8037EE70[];
extern s8 lbl_804CB498; extern void* lbl_804CB49C; extern u8 lbl_8037EE18[];
extern s8 lbl_804CB4A0; extern void* lbl_804CB4A4; extern u8 lbl_8037EC60[];
extern s8 lbl_804CB4A8; extern void* lbl_804CB4AC; extern u8 lbl_8037EB58[];
extern s8 lbl_804CB4B0; extern void* lbl_804CB4B8; extern u8 lbl_8037EB00[];
extern s8 lbl_804CB4C0; extern void* lbl_804CB4C4; extern u8 lbl_8037EAA8[];
extern s8 lbl_804CB4C8; extern Lazy2 lbl_804CB4D0; extern u8 lbl_8037E198[]; extern u8 lbl_8037F294[];
extern s8 lbl_804CB460; extern void* lbl_804CB464; extern u8 lbl_8037EDC0[];
extern s8 lbl_804CB468; extern void* lbl_804CB46C; extern u8 lbl_8037ED68[];
extern s8 lbl_804CB470; extern void* lbl_804CB474; extern u8 lbl_8037ED10[];
extern s8 lbl_804CB478; extern void* lbl_804CB47C; extern u8 lbl_8037ECB8[];
extern s8 lbl_804CB480; extern Lazy2 lbl_804CB488; extern u8 lbl_8037E184[]; extern u8 lbl_8037F200[];

extern "C" void fn_80059134(void* p) {
    if (!lbl_804CB818) fn_8012FCB0();
    fn_801856F4();
    LAZY1(lbl_804CB490, lbl_804CB494, lbl_8037EE70);
    LAZY1(lbl_804CB498, lbl_804CB49C, lbl_8037EE18);
    LAZY1(lbl_804CB4A0, lbl_804CB4A4, lbl_8037EC60);
    LAZY1(lbl_804CB4A8, lbl_804CB4AC, lbl_8037EB58);
    LAZY1(lbl_804CB4B0, lbl_804CB4B8, lbl_8037EB00);
    LAZY1(lbl_804CB4C0, lbl_804CB4C4, lbl_8037EAA8);
    LAZY2(lbl_804CB4C8, lbl_804CB4D0, lbl_8037E198, lbl_8037F294);
    fn_800453B4(&lbl_803CA870, 0);
    fn_800D5448(&lbl_804CB4D0, p, 0);
    SALLY_TAIL(p);
}

extern "C" void fn_800592F0(void* p) {
    if (!lbl_804CB818) fn_8012FCB0();
    fn_801856F4();
    LAZY1(lbl_804CB460, lbl_804CB464, lbl_8037EDC0);
    LAZY1(lbl_804CB468, lbl_804CB46C, lbl_8037ED68);
    LAZY1(lbl_804CB470, lbl_804CB474, lbl_8037ED10);
    LAZY1(lbl_804CB478, lbl_804CB47C, lbl_8037ECB8);
    LAZY2(lbl_804CB480, lbl_804CB488, lbl_8037E184, lbl_8037F200);
    fn_800453B4(&lbl_803CA870, 0);
    fn_800D5448(&lbl_804CB488, p, 0);
    SALLY_TAIL(p);
}
