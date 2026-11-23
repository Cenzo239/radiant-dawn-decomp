#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" void fn_8005D624(void* p) {
    fn_801E5880(p);
}

extern "C" void fn_8005D628(void* a) {
    fn_801C6D2C(lbl_803CA870.unit, a, 0, fn_8005D624, a);
}

typedef struct Proc50 {
    u8 pad0[0x50];
    u8 b50;
} Proc50;
extern "C" void fn_8005D648(Proc50* p) {
    fn_801E5890(p);
    fn_80083DC4(p, p->b50);
}
