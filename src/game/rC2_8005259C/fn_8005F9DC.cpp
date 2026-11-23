#include "game/rC2_8005259C/decls.h"
#pragma use_lmw_stmw on

extern "C" int fn_8005F9DC(void) {
    return 0x51;
}

extern "C" int fn_8005F9E4(Obj4* o) {
    return (0x260 - o->v50()) >> 1;
}

extern "C" int fn_8005FA1C(void) {
    return 0xb0;
}

extern "C" int fn_8005FA24(void) {
    return 0x0;
}

extern "C" void fn_8005FA2C(Obj4* o) {
    o->v90();
}

extern "C" void fn_8005FA3C(Obj4* o) {
    o->v90();
}

typedef struct PosBox {
    u8 pad0[0x32];
    s16 y32;
    u8 pad34[2];
    s16 h36;
} PosBox;
extern "C" void fn_8005FA4C(void* a, PosBox* p) {
    p->y32 = (0x1c0 - p->h36) >> 1;
}

extern "C" int fn_8005FA60(void) {
    return 0x21;
}

extern "C" void fn_8005FA68(void) {
}

extern "C" void fn_8005FA6C(void) {
}
