/* Assign a unit to a side, 801223E0. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
extern int fn_8011B77C(void*, void*);
extern u8* fn_801116B8(Inv*);
extern void fn_80106DD0(void*, Unit*);
void fn_801223E0(Unit* u, u8* t) {
    u->team = t;
    fn_80106DD0(u->u390, u);
    switch (t[8]) {
    case 0:
    case 5:
    case 8:
    case 9:
    case 10:
        u->flags108 |= 0x10;
    }
}
}
