#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern s8 lbl_804CB490;
extern void* lbl_804CB494;
extern u8 lbl_8037EE70[];
extern s8 lbl_804CB498;
extern void* lbl_804CB49C;
extern u8 lbl_8037EE18[];
extern s8 lbl_804CB4A0;
extern void* lbl_804CB4A4;
extern u8 lbl_8037EC60[];
extern s8 lbl_804CB4A8;
extern void* lbl_804CB4AC;
extern u8 lbl_8037EB58[];
extern s8 lbl_804CB4B0;
extern void* lbl_804CB4B8;
extern u8 lbl_8037EB00[];
extern s8 lbl_804CB4C0;
extern void* lbl_804CB4C4;
extern u8 lbl_8037EAA8[];
extern s8 lbl_804CB4C8;
extern Lazy2 lbl_804CB4D0;
extern u8 lbl_8037E198[];
extern u8 lbl_8037F294[];

extern "C" int fn_8005FD50(void* a, Menu* m) {
    MenuProc* p;
    if (fn_801A2224(lbl_8041EB20)) {
        return 0x40;
    }
    lbl_804CB550 = 0x87;
    p = m->proc;
    LAZY1(lbl_804CB490, lbl_804CB494, lbl_8037EE70);
    LAZY1(lbl_804CB498, lbl_804CB49C, lbl_8037EE18);
    LAZY1(lbl_804CB4A0, lbl_804CB4A4, lbl_8037EC60);
    LAZY1(lbl_804CB4A8, lbl_804CB4AC, lbl_8037EB58);
    LAZY1(lbl_804CB4B0, lbl_804CB4B8, lbl_8037EB00);
    LAZY1(lbl_804CB4C0, lbl_804CB4C4, lbl_8037EAA8);
    LAZY2(lbl_804CB4C8, lbl_804CB4D0, lbl_8037E198, lbl_8037F294);
    fn_800453B4(&lbl_803CA870, 0);
    fn_800D5448(&lbl_804CB4D0, p, 0);
    return 9;
}
