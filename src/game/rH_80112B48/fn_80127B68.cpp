/* Find the partner unit of a side, 80127B68 and 80127CA0. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
extern void fn_8010E41C(u8*, int);
Unit* fn_80127B68(Unit* u) {
    u8* t;
    u32 f;
    int i;
    Unit* v;
    u8 tbl[5];
    fn_8010E41C(tbl, 5);
    for (i = 1; i <= 0xfe; i++) {
        v = UnitGet(i);
        if (v->person) {
            t = v->team;
            if (tbl[t[8]]) {
                f = v->flags10C;
                if ((f & 0x100) && !(f & 8) && t == u->team && u->fd == v->fd) {
                    return v;
                }
            }
        }
    }
    return 0;
}
Unit* fn_80127CA0(Unit* u) {
    u8* t;
    u32 f;
    int i;
    Unit* v;
    u8 tbl[5];
    if (u->u117 == 0) {
        return 0;
    }
    fn_8010E41C(tbl, 0);
    for (i = 1; i <= 0xfe; i++) {
        v = UnitGet(i);
        if (v->person) {
            t = v->team;
            if (tbl[t[8]]) {
                f = v->flags10C;
                if ((f & 0x4000000) && !(f & 8) && t == u->team && u->u117 == v->u117) {
                    return v;
                }
            }
        }
    }
    return 0;
}
}
