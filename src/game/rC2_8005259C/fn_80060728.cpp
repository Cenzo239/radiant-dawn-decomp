#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" Opt44* fn_80060728(GameData* g) {
    return (Opt44*)((u8*)fn_8024BCA0() + 0x44);
}

extern "C" NamedThing* fn_8006074C(GameData* g) {
    return fn_8010B094(g->b10);
}

extern "C" int fn_80060754(void* p) {
    return fn_801059B0(p) != 0;
}

extern "C" int fn_80060780(GameData* g) {
    return g->b10 >= 4 || g->b10 == 0;
}

extern "C" int fn_800607A0(GameData* g) {
    return fn_802912A4(fn_8010B094(g->b10)->name, lbl_803620E4 + 4, 3) == 0;
}

extern "C" int fn_800607E4(GameData* g) {
    return fn_802912A4(fn_8010B094(g->b10)->name, lbl_803620E4 + 0xc, 3) == 0;
}
