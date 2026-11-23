#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

typedef struct Obj4CB {
    u8 pad0[0x4c];
    void* p4c;
} Obj4CB;
extern "C" void fn_8005A3B4(Obj4CB* p) {
    void* q;
    void* r;
    fn_80280EE0(fn_801930DC(fn_801856C8()));
    q = p->p4c;
    fn_80083E18(q, fn_8005997C);
    fn_80083DC4(q, 1);
    r = fn_800D4228(lbl_80361F9C + 0x15);
    if (r) {
        fn_800D3C90(r, 4);
    }
}
