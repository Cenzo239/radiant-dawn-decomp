/* NOT MATCHING, not compiled. fn_80120378: 1 word: a dead b after the switch compare chain. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
extern int fn_8011B77C(void*, void*);
extern u8* fn_801116B8(Inv*);
extern u8* fn_80060728(void*);
extern u8 lbl_803CAB38[];
extern u8 fn_80126B0C(Unit*);
extern void* lbl_804CA4E8; extern void* lbl_804CA594;
static inline BOOL CanPromote(Unit* u) {
    if (fn_8011B77C(u->skills, lbl_804CA4E8)) return 0;
    if (fn_8011B77C(u->skills, lbl_804CA594)) return 0;
    return u->job->p14 != 0;
}
int fn_80120378(Unit* u) {
    switch (*(u32*)fn_80060728(lbl_803CAB38) & 3) {
    case 1:
        return 0;
    case 2:
        return 0x64;
    }
    if (u->hp == 0) {
        return 0;
    }
    switch (u->team[8]) { case 4: break; break; case 1: return 0; case 2: case 3: return 0x64; }
    if (fn_80126B0C(u) == 0xff) {
        return 0;
    }
    {
        /*P*/
        s8 g;
        int m;
        int v;
        /*E*/
        m = (u->job->fb - 1) * 100;
        if (CanPromote(u)) {
            m += 100;
        }
        g = u->gauge;
        {int e = fn_80126B0C(u); v = m - (e + (g - 1) * 100);}
        if (v < 0) {
            v = 0;
        }
        return v;
    }
}
}
