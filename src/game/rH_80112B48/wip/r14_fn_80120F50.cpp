/* NOT MATCHING, not compiled. fn_80120F50, fn_80121080: 7 words each: the result flag wants r3 and the mid-gauge flag r4. */
/* Laguz transform sprite ids at middle gauge, 80120F50 and 80121080. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
extern int fn_8011B77C(void*, void*);
extern void* fn_8010B1D8(void*);
extern void* lbl_804CA5C4;
extern void* lbl_804CA4EC;
extern char lbl_80369010[];
static inline BOOL GaugeMid(Unit* u) {
    s8 v = u->gauge;
    return v >= 15 && v < 30;
}
static inline BOOL IsLaguz(Unit* u) {
    if (!fn_8011B77C(u->skills, lbl_804CA5C4)) {
        return 0;
    }
    return GaugeMid(u) || u->gauge >= 30;
}
static inline int HeroId(Unit* u, int a, int b, int c, int d) {
    Person* p = u->person;
    char* pool = lbl_80369010;
    if (p == fn_8010B1D8(pool + 0x2e)) {
        return fn_8011B77C(u->skills, lbl_804CA4EC) ? b : a;
    }
    p = u->person;
    if (p == fn_8010B1D8(pool + 0x3b)) {
        fn_8011B77C(u->skills, lbl_804CA4EC);
        return c;
    }
    p = u->person;
    if (p == fn_8010B1D8(pool + 0x46)) {
        fn_8011B77C(u->skills, lbl_804CA4EC);
        return d;
    }
    return a;
}
int fn_80120F50(Unit* u) {
    if (!IsLaguz(u)) {
        return -1;
    }
    return HeroId(u, 0x42, 0x44, 0x43, 0x44);
}
int fn_80121080(Unit* u) {
    if (!IsLaguz(u)) {
        return -1;
    }
    return HeroId(u, 0x45, 0x47, 0x46, 0x47);
}
}
