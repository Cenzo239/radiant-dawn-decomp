#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" int fn_8005E118(void) {
    fn_800453B4(&lbl_803CA870, 0x95);
    lbl_804CB550 = 0x95;
    return 5;
}

extern "C" u8 fn_8005E150(void) {
    return lbl_804CB550 == 0x95;
}

extern "C" char* fn_8005E164(void) {
    return lbl_8037F6C4;
}

extern "C" const char* fn_8005E170(void) {
    return fn_800D0864(lbl_8037F6B8);
}

extern "C" int fn_8005E17C(void) {
    fn_800453B4(&lbl_803CA870, 0x94);
    lbl_804CB550 = 0x94;
    return 5;
}

extern "C" u8 fn_8005E1B4(void) {
    return lbl_804CB550 == 0x94;
}

extern "C" char* fn_8005E1C8(void) {
    return lbl_8037F6AC;
}

extern "C" const char* fn_8005E1D4(void) {
    return fn_800D0864(lbl_8037F6A0);
}

extern "C" int fn_8005E1E0(void* a, Menu* m, MenuEntry* e) {
    if (e->active == 2) {
        return 0x10;
    }
    fn_800453B4(&lbl_803CA870, 0x92);
    lbl_804CB550 = 0x92;
    return 5;
}

extern "C" u8 fn_8005E22C(void) {
    if (fn_8006041C((u8*)&lbl_803CAB38 + 0x554) <= 0) {
        return 2;
    }
    return lbl_804CB550 == 0x92;
}

extern "C" char* fn_8005E278(void) {
    return lbl_8037F694;
}

extern "C" const char* fn_8005E284(void) {
    return fn_800D0864(lbl_8037F688);
}
