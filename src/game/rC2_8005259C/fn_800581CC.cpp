#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

typedef struct Obj4C_fn_800581CC {
    u8 pad0[0x4c];
    void* p4c;
} Obj4C_fn_800581CC;
extern "C" void fn_800581CC(Obj4C_fn_800581CC* p) {
    if (p->p4c) {
        fn_800893AC(p->p4c);
    }
}

typedef struct Obj4C_fn_800581E0 {
    u8 pad0[0x4c];
    void* p4c;
} Obj4C_fn_800581E0;
extern "C" void fn_800581E0(Obj4C_fn_800581E0* p) {
    if (p->p4c) {
        fn_8008939C(p->p4c);
    }
}
