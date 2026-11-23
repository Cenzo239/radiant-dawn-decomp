#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern s8 lbl_804CB440;
extern void* lbl_804CB444;
extern u8 lbl_8037EC08[];
extern s8 lbl_804CB448;
extern void* lbl_804CB44C;
extern u8 lbl_8037EBB0[];
extern s8 lbl_804CB450;
extern Lazy2 lbl_804CB458;
extern u8 lbl_8037E178[];
extern u8 lbl_8037F16C[];

extern "C" int fn_8005E7CC(void* a, Menu* m) {
    MenuProc* p;
    fn_800453B4(&lbl_803CA870, 0x8c);
    lbl_804CB550 = 0x8c;
    p = m->proc;
    LAZY1(lbl_804CB440, lbl_804CB444, lbl_8037EC08);
    LAZY1(lbl_804CB448, lbl_804CB44C, lbl_8037EBB0);
    LAZY2(lbl_804CB450, lbl_804CB458, lbl_8037E178, lbl_8037F16C);
    fn_800453B4(&lbl_803CA870, 0);
    fn_800D5448(&lbl_804CB458, p, 0);
    return 5;
}
