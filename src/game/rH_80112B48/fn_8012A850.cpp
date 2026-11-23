/* Compact the inventory, 8012A850. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
extern int fn_8011B77C(void*, void*);
extern u8* fn_801116B8(Inv*);
extern void fn_80111B34(Inv*);
extern void fn_80111C24(Inv*, int);
extern void fn_80111C78(Inv*, Inv*);
extern void fn_80110D38(Inv*);
void fn_8012A850(Unit* u) {
    Inv* s;
    Inv* it;
    int n;
    int i;
    int j;
    Inv t[7];
    fn_80111B34(&t[0]);
    fn_80111B34(&t[1]);
    fn_80111B34(&t[2]);
    fn_80111B34(&t[3]);
    fn_80111B34(&t[4]);
    fn_80111B34(&t[5]);
    fn_80111B34(&t[6]);
    it = u->inv;
    i = 0;
    n = 0;
    for (; i < 7; i++) {
        if (it->item) {
            fn_80111C78(&t[n++], it);
            fn_80110D38(it);
        }
        it++;
    }
    s = t;
    for (j = 0; j < 7; j++) {
        if (s->item == 0) break;
        fn_801116B8(s);
        fn_80111C78(&u->inv[(u8)j], s);
        s++;
    }
    fn_80111C24(&t[6], -1);
    fn_80111C24(&t[5], -1);
    fn_80111C24(&t[4], -1);
    fn_80111C24(&t[3], -1);
    fn_80111C24(&t[2], -1);
    fn_80111C24(&t[1], -1);
    fn_80111C24(&t[0], -1);
}
}
