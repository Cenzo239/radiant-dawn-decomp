/* Clear the enemy sides and rebuild their lists, 8012CC80. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
struct Team { Unit* head; Unit* tail; int n; };
extern Team* lbl_804CB814;
extern u32 lbl_804CA710;
extern void fn_8010E41C(u8*, int);
extern void fn_8010DF10(void*, int);
extern void fn_8010DF24(void*);
extern void fn_8010E168(void*, Unit*);
extern void fn_8010E27C(void*, Unit*);
extern void fn_801221E8(Unit*, int);
extern void fn_8011FDD8(Unit*, int);
extern void fn_80126EB0(Unit*, int, int);
extern u8* fn_8024BCA0(void);
extern int fn_80121A28(Unit*, void*);
extern void* memset(void*, int, u32);
static inline void SideSet(u8* tbl, const u8* a) {
    for (; *a != 0xff; a++) {
        tbl[*a] = 1;
    }
}
void fn_8012CC80(void) {
    int off;
    Unit* p;
    int i;
    Unit* u;
    Unit* v;
    int j;
    Unit* w;
    u = lbl_804CB814[0].tail;
    while (u) {
        p = u->prev;
        fn_8011FDD8(u, 5);
        u = p;
    }
    for (i = 0, off = 0; i < 0xfe; i++) {
        v = (Unit*)((u8*)lbl_804CB810 + off);
        if (v->person) {
            switch (v->team[8]) {
            case 0:
                break;
            case 1:
            case 2:
            case 3:
                fn_8010E27C(&lbl_804CB814[v->team[8]], v);
                fn_801221E8(v, -1);
                fn_8010E168(&lbl_804CB814[4], v);
            }
        }
        off += 0x3f0;
    }
    {
    u8 a[] = {5, 7, 8, 9, 10, 0xff};
    u8 tbl[0xb];
        memset(tbl, (u8)lbl_804CA710, 0xb);
        SideSet(tbl, a);
        for (j = 1; j <= 0xfe; j++) {
            w = UnitGet(j);
            if (w->person && tbl[w->team[8]]) {
                fn_80126EB0(w, 0, 0);
            }
        }
    }
    fn_8010DF10(&lbl_804CB814[0], 0);
    fn_8010DF10(&lbl_804CB814[1], 1);
    fn_8010DF10(&lbl_804CB814[2], 2);
    fn_8010DF10(&lbl_804CB814[3], 3);
}
}
