/* fn_80129B20: moves one inventory slot to the front and compacts. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
extern int fn_8011B77C(void*, void*);
extern u8* fn_801116B8(Inv*);
extern s8 fn_80127520(Unit*);
extern void fn_80111B34(Inv*);
extern void fn_80111C24(Inv*, int);
extern void fn_80111C78(Inv*, Inv*);
extern void fn_80110D38(Inv*);
#pragma use_lmw_stmw on
Inv* fn_80129B20(Unit* u, s8 k) {
    /*P*/
    Inv* s;
    Inv* q;
    Inv* it;
    int off;
    Inv* r;
    int i;
    int j;
/*E*/
    Inv t[7];
    if (k < 0) k = fn_80127520(u);
    if (k < 0) return 0;
    fn_80111B34(&t[0]);
    fn_80111B34(&t[1]);
    fn_80111B34(&t[2]);
    fn_80111B34(&t[3]);
    fn_80111B34(&t[4]);
    fn_80111B34(&t[5]);
    fn_80111B34(&t[6]);
    q = &u->inv[k];
    fn_80111C78(&t[0], q);
    fn_80110D38(q);
    it = u->inv;
    i = 0;
    q = it;
    off = 1;
    for (; i < 7; i++) {
        if (q->item) {
            fn_80111C78(&t[off++], q);
        }
        q++;
    }
    for (j = 0; j < 7; j++, it++) {
        fn_801116B8(&t[j]);
        fn_80111C78(&u->inv[(u8)j], &t[j]);
        if (it->item && it->equipped) r = it;
    }
    fn_80111C24(&t[6], -1);
    fn_80111C24(&t[5], -1);
    fn_80111C24(&t[4], -1);
    fn_80111C24(&t[3], -1);
    fn_80111C24(&t[2], -1);
    fn_80111C24(&t[1], -1);
    fn_80111C24(&t[0], -1);
    return r;
}
}
