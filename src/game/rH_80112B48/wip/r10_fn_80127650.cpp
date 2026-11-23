/* NOT MATCHING, not compiled. fn_80127650: 3 words: the case 10 result wants r30. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
extern void fn_8010E41C(u8*, int);
extern int fn_8011B77C(void*, void*);
extern void* lbl_804CA4E8;
extern u8 fn_8010B260(void*);
extern void* fn_8010B1D8(void*);
extern void* fn_8010B200(void*);
extern void* fn_8010B228(void*);
extern void* fn_801059B0(void);
extern int fn_8010536C(void*, void*);
extern s8 fn_8012C9BC(Unit*, void*);
extern int fn_801109B8(void*, void*);
static inline BOOL PersonIs(Unit* u, void* x) { Person* q = u->person; return q == fn_8010B1D8(x); }
static inline BOOL JobHas(Unit* u, u8* promo, void* x) { BOOL r = 0;
        if (fn_801109B8((u8*)u->job + 0xee, x) || (promo && fn_801109B8(promo + 0xee, x))) {
            r = 1;
        }
        return r;
 }
#pragma push
#pragma use_lmw_stmw on
BOOL fn_80127650(Unit* u, void* x) {
    /*P*/
    BOOL r;
    Person* p;
    Job* j;
    u8* promo;
    BOOL t;
    int i;
    Unit* v;
/*E*/
    u8 tbl[0x18];
    promo = 0;
    if (fn_8011B77C(u->skills, lbl_804CA4E8)) {
        promo = (u8*)u->job->promoted;
    }
    switch ((u8)fn_8010B260(x)) {
    case 1: {
        return PersonIs(u, x);
    }
    case 2: {
        j = u->job;
        r = 1;
        if (j != fn_8010B200(x)) {
            t = 0;
            if (promo && promo == fn_8010B200(x)) {
                t = 1;
            }
            if (!t) {
                r = 0;
            }
        }
        return r;
    }
    case 3: {
        if (fn_801059B0() && fn_8010536C(fn_801059B0(), x) >= 0) {
            return 1;
        }
        fn_8010E41C(tbl, 4);
        for (i = 1; i <= 0xfe; i++) {
            v = UnitGet(i);
            if (v->person && tbl[v->team[8]]) {
                if ((s8)fn_8012C9BC(v, fn_8010B228(x)) >= 0) {
                    return 1;
                }
            }
        }
        return 0;
    }
    case 9:
        return fn_8011B77C(u->skills, x);
    case 10: {
t = 0;
        if (fn_801109B8((u8*)u->job + 0xee, x) || (promo && fn_801109B8(promo + 0xee, x))) {
            t = 1;
        }
        return t;
    }
    }
    return 0;
}
#pragma pop
}
