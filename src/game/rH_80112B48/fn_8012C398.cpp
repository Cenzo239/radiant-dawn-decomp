/* Weapon rank step, 8012C398. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
extern int fn_8011B77C(void*, void*);
extern u8* fn_801116B8(Inv*);
extern s16 fn_8012C0A8(Unit*, int, int);
extern s16 fn_80111488(int);
extern s16 fn_80111230(int);
BOOL fn_8012C398(Unit* u, u8 i) {
    s16 old = fn_8012C0A8(u, i, ((const Unit*)u)->s2D4[i]);
    s16 now; {s16 t=fn_80111488(old); now=fn_8012C0A8(u,i,t);}
    u->s2D4[i] = now;
    old = fn_80111230(old); now = fn_80111230(now); return old != now;
}
}
