/* Manhattan distance between two units, 80126F34. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
extern int fn_8011B77C(void*, void*);
extern u8* fn_801116B8(Inv*);
#define ABS(a) ((a) < 0 ? -(a) : (a))
u8 fn_80126F34(Unit* a, Unit* b) { return ABS(a->x - b->x) + ABS(a->y - b->y); }
}
