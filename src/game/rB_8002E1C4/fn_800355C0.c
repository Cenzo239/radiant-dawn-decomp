#include "game/rB_8002E1C4/types.h"

typedef struct Obj355C0 {
    u8 pad[0x34];
    void* x34;
} Obj355C0;

void fn_80078E24(void* p); /* free/release */

void fn_800355C0(Obj355C0* o)
{
    if (o->x34 != 0) {
        fn_80078E24(o->x34);
        o->x34 = 0;
    }
}
