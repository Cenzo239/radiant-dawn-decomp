/* Skill scroll: give the unit the pending skill item (names guessed). */
#include "game/rT_80026898/types.h"
extern "C" {
extern Unit* lbl_804CB3E0;
extern void* lbl_804CB3E8;
void fn_8011B32C(void*, void*);
void* fn_8011A158(void*);
void fn_80111B34(Item*);
void fn_80110BB4(Item*, void*);
void fn_80111B64(Item*, Item*);
void fn_80111C24(Item*, int);
void fn_8004AD18(Unit*, Slot*, void*);
static inline void* skl() { return fn_8011A158(lbl_804CB3E8); }
void fn_8004AF14(void* proc) {
    Item a;
    Item b;
    void* d;
    Unit* u = lbl_804CB3E0;
    fn_8011B32C(u->x12c, lbl_804CB3E8);
    d = skl();
    if (d) {
        fn_80111B34(&a);
        fn_80110BB4(&a, d);
        fn_80111B64(&b, &a);
        fn_8004AD18(u, (Slot*)&b, proc);
        fn_80111C24(&b, -1);
        fn_80111C24(&a, -1);
    }
}
}
