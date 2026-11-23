/*
 * fn_80092E10 (round 22, exact). Returns the u8 result of fn_801194FC on the string at +0x90.
 * The parameter is `const`: that is what lets the `lwz r3,0x90(r3)` schedule before
 * `stw r0,0x14(r1)` (the old wip in wip/fn_80092E10.cpp had a plain pointer, 2 words off).
 */
#include "game/rD_8008E3B4/types.h"

extern "C" {

int fn_801194FC(char* s);

typedef struct Obj90 {
    u8 pad[0x90];
    char* p90; /* 0x90 */
} Obj90;

u8 fn_80092E10(const Obj90* p)
{
    return fn_801194FC(p->p90);
}

}
