/* Update all unit markers with the zoom scale, 8012D158. */
#include "game/rH_80112B48/unit.h"
#include "game/rH_80112B48/map.h"
#pragma auto_inline off
extern "C" {
extern int fn_8012FA3C(void);
extern void* fn_8012FCD0(void);
extern f32 fn_8001EF30(f32, f32, f32, f32);
extern void fn_800F7D30(void);
extern void fn_800F7D5C(void);
extern void fn_800F7890(Unit*, f32);
extern void fn_8010E41C(u8*, int);
extern f32 lbl_804CDD44, lbl_804CDD40, lbl_804CDD48;
void fn_8012D158(void) {
    f32 mn;
    f32 mx;
    f32 v;
    u8 tbl[0xb];
    int i;
    mx = 64.0f;
    v = mx;
    mn = 16.0f;
    if (fn_8012FA3C() == 0) {
        u8* c = (u8*)fn_8012FCD0();
        if (c) {
            v = fn_8001EF30(mx, mn, 10.0f, *(f32*)(c + 0x18) - 16.0f);
            if (v < mn) v = mn;
            if (v > mx) v = mx;
        }
    }
    fn_800F7D30();
    fn_8010E41C(tbl, 3);
    for (i = 1; i <= 0xfe; i++) {
        Unit* u = UnitGet(i);
        if (u->person && tbl[u->team[8]]) {
            fn_800F7890(u, v);
        }
    }
    fn_800F7D5C();
}
}
