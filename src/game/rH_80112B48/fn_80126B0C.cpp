/* Level-up allowance, 80126B0C. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
extern int fn_8011B77C(void*, void*);
extern u8* fn_801116B8(Inv*);
extern u8* fn_80060728(void*);
extern u8 lbl_803CAB38[];
static inline BOOL E(u8 v, u8 k) { return v == k; }
u8 fn_80126B0C(Unit* u) {
    if (*(u32*)fn_80060728(lbl_803CAB38) & 3) {
        return 0xff;
    }
    if ((u32)u->team[8] == 1 || (u32)u->team[8] == 2 || (u32)u->team[8] == 3) {
        return 0xff;
    }
    return u->ff;
}
}
