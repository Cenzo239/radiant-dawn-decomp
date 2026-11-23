/*
 * fn_80094130 (round 22, exact): hands the item at proc+0x58 to fn_8004B03C for the unit at
 * proc+0x54. Ref is the 8-byte item reference (pointer, kind, flag) that fn_8004B03C takes;
 * its definition in rT_80026898/fn_8004A70C.cpp declares it as `ItemRef*`, which is the same
 * call (a by-value struct is passed as a pointer to a caller-made copy).
 * The dead `b; stb r0,0x15(r1)` after the constructor stores is the constructor's
 * `if (p) flag = 1;` after `p = 0` (same Ref as rF_8017F400/fn_801C77DC.cpp).
 */
#include "game/rD_8008E3B4/types.h"
extern "C" {
struct Ref {
    void* p;
    u8 kind;
    u8 flag;
    Ref() { p = 0; kind = 2; flag = 0; if (p) flag = 1; }
};
typedef struct UnitProc {
    u8 pad0[0x54];
    void* unit;  /* 0x54 */
    u8* data;    /* 0x58 */
} UnitProc;
void fn_8004B03C(void* u, Ref r, void* proc);
void fn_80094130(UnitProc* proc)
{
    Ref r;
    r.p = proc->data;
    r.flag = proc->data[0x20] == 0;
    fn_8004B03C(proc->unit, r, proc);
}
}
