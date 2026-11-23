#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

typedef struct Obj58 {
    u8 pad0[0x30];
    void* p30;
    u8 pad34[0x58 - 0x34];
    s8 x58;
    s8 y59;
} Obj58;
extern "C" void fn_8005804C(Obj58* p) {
    fn_80126EB0(p->p30, p->x58, p->y59);
    fn_800F39DC(p->p30);
}
