#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern s8 lbl_804CB41C;
extern void* lbl_804CB420;
extern u8 lbl_8037EA50[];
extern s8 lbl_804CB424;
extern void* lbl_804CB428;
extern u8 lbl_8037E9F8[];
extern s8 lbl_804CB42C;
extern void* lbl_804CB430;
extern u8 lbl_8037E9A0[];
extern s8 lbl_804CB434;
extern Lazy2 lbl_804CB438;
extern u8 lbl_8037E168[];
extern u8 lbl_8037F0D8[];

extern "C" int fn_8005E290(void* a, Menu* m) {
    MenuProc* p;
    fn_800453B4(&lbl_803CA870, 0x91);
    lbl_804CB550 = 0x91;
    p = m->proc;
    LAZY1(lbl_804CB41C, lbl_804CB420, lbl_8037EA50);
    LAZY1(lbl_804CB424, lbl_804CB428, lbl_8037E9F8);
    LAZY1(lbl_804CB42C, lbl_804CB430, lbl_8037E9A0);
    LAZY2(lbl_804CB434, lbl_804CB438, lbl_8037E168, lbl_8037F0D8);
    fn_800453B4(&lbl_803CA870, 0);
    fn_800D5448(&lbl_804CB438, p, 0);
    return 5;
}
