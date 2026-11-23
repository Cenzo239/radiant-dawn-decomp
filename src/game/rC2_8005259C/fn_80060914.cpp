#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

static inline u32 sysBit3(void) { return (fn_8024BCA0()->w40 >> 3) & 1; }
static inline u32 sysBit4(void) { return (fn_8024BCA0()->w40 >> 4) & 1; }
static inline u32 sysBit5(void) { return (fn_8024BCA0()->w40 >> 5) & 1; }
extern "C" int fn_80060914(GameData* g) {
    u32 r = sysBit3();
    if (r == 0) {
        r = sysBit4();
    }
    if (r == 0) {
        r = sysBit5();
    }
    return r;
}

extern "C" u32 fn_80060960(void) {
    return (fn_8024BCA0()->w40 >> 3) & 1;
}

extern "C" u32 fn_80060988(void) {
    return (fn_8024BCA0()->w40 >> 4) & 1;
}

extern "C" u32 fn_800609B0(void) {
    return (fn_8024BCA0()->w40 >> 5) & 1;
}
