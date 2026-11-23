/* Item use by a staff or promotion item, 8011E120. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
extern int fn_8011B77C(void*, void*);
extern u8* fn_801116B8(Inv*);
#if TARGET_PC
extern FE10_PROTO int fn_8010B678(ptr32<const void>);
extern FE10_PROTO struct Inv * fn_8012759C(Unit*);
#else
extern int fn_8010B678(void*);
extern int fn_8012759C(Unit*);
#endif
extern void fn_80129CB8(Unit*, int);
extern int fn_8012ABFC(Unit*);
extern s8 fn_8012AC88(Unit*);
extern void fn_8012A80C(Unit*, int);
extern void fn_8012A850(Unit*);
extern void fn_80111B34(Inv*);
extern void fn_80111C24(Inv*, int);
extern void* fn_8010B528(void*, int);
extern void fn_8010B5AC(void*, int);
extern void* fn_8010B228(void*);
extern int fn_8012B63C(Unit*, void*);
extern void fn_80110BFC(Inv*, void*);
extern void fn_8012A0F4(Unit*, Inv*);
extern void fn_800F491C(Unit*);
BOOL fn_8011E120(Unit* u, void* x) {
    s8 k;
    int i;
    void* s;
    Inv t;
    if (fn_8010B678(x) == 0) {
        return 0;
    }
    if (fn_8012759C(u)) {
        return 0;
    }
    fn_80129CB8(u, -1);
    if (fn_8012759C(u)) {
        return 0;
    }
    if (fn_8012ABFC(u)) {
        k = fn_8012AC88(u);
        if (k < 0) {
            return 0;
        }
        fn_8012A80C(u, k);
    }
    fn_8012A850(u);
    fn_80111B34(&t);
    for (i = 0; i < 7; i++) {
        s = fn_8010B528(x, i);
        fn_8010B5AC(x, i);
        if (s && fn_8012B63C(u, fn_8010B228(s))) {
            fn_80110BFC(&t, s);
            t.bits2 = 1;
            fn_8012A0F4(u, &t);
            break;
        }
    }
    fn_80129CB8(u, -1);
    fn_800F491C(u);
    fn_80111C24(&t, -1);
    return 1;
}
}
