/* Laguz transform checks, 80120CA0..801212C0. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off

extern "C" {

extern int fn_8011B77C(void*, void*);
extern void* fn_8010B1D8(void*);
extern void* lbl_804CA5C4;
extern void* lbl_804CA4EC;
extern void* lbl_804CA4F8;
extern void* lbl_804CA4FC;
extern char lbl_80369010[];

int fn_80120CA0(Unit* u) {
    return fn_8011B77C(u->skills, lbl_804CA5C4);
}

static inline BOOL GaugeMid(Unit* u) {
    s8 v = u->gauge;
    return v >= 15 && v < 30;
}

static inline BOOL GaugeHi(Unit* u) {
    s8 v = u->gauge;
    return v >= 30;
}

static inline BOOL IsLaguz(Unit* u) {
    if (!fn_8011B77C(u->skills, lbl_804CA5C4)) {
        return 0;
    }
    return GaugeMid(u) || u->gauge >= 30;
}

static inline BOOL fn_80120CAC_i(Unit* u) {
    BOOL r;
    if (!fn_8011B77C(u->skills, lbl_804CA5C4)) {
        return 0;
    }
    r = 1;
    if (!GaugeMid(u) && u->gauge < 30) {
        r = 0;
    }
    return r;
}

BOOL fn_80120CAC(Unit* u) {
    return IsLaguz(u);
}

BOOL fn_80120D2C(Unit* u) {
    return IsLaguz(u);
}

static inline BOOL IsLaguz2(Unit* u) {
    if (fn_8011B77C(u->skills, lbl_804CA5C4)) {
        return u->gauge >= 30;
    }
    return 0;
}

BOOL fn_80120DAC(Unit* u) {
    return IsLaguz2(u);
}

static inline BOOL IsLaguz3(Unit* u) {
    if (fn_8011B77C(u->skills, lbl_804CA5C4)) {
 return u->gauge == u->job->fb;
    }
    return 0;
}

BOOL fn_80120E0C(Unit* u) {
    return IsLaguz3(u);
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

int fn_80120E6C(Unit* u) {
    if (!fn_8011B77C(u->skills, lbl_804CA5C4)) {
        return -1;
    }
    return HeroId(u, 0x12, 0x2c, 0x40, 0x2c);
}

int fn_801211B0(Unit* u) {
    if (!IsLaguz2(u)) {
        return -1;
    }
    return HeroId(u, 0x48, 0x4a, 0x49, 0x4a);
}

int fn_801212C0(Unit* u) {
    if (!IsLaguz3(u)) {
        return -1;
    }
    return HeroId(u, 0x4b, 0x4d, 0x4c, 0x4d);
}

BOOL fn_80121DEC(Unit* u) {
    if (fn_8011B77C(u->skills, lbl_804CA4F8)) {
        return 1;
    }
    return fn_8011B77C(u->skills, lbl_804CA4FC);
}

}
