#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

typedef struct ObjU30 {
    u8 pad0[0x30];
    Unit* u30;
} ObjU30;
extern "C" void fn_800551AC(ObjU30* p) {
    Unit* u = p->u30;
    fn_800620A8(&lbl_803CAB38, u->x102, u->y103);
}

typedef struct Obj30 {
    u8 pad0[0x30];
    void* p30;
    u8 pad34[0x3a - 0x34];
    u8 b3a;
} Obj30;
extern "C" void fn_80055218(Obj30* p) {
    fn_8006CCAC(&lbl_803C8E80, p->p30, p->b3a, p, 1);
}

extern "C" void fn_80055234(void) {
    lbl_803C8E80.f15ec |= 1;
    fn_8002BCC4(&lbl_803C8E80);
}

extern "C" void fn_8005524C(void* parent) {
    fn_80081194(lbl_8037DE64, parent);
}
