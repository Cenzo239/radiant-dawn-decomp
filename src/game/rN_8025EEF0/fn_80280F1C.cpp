/* EXACT (round 23a): fn_80280F1C, from equiv/fn_80280F1C.cpp; fn_8017F68C declared with its real prototype (int mode first, from the CATALOG) and called in that order, and go() stores m4C before from */
/* (older header, kept for history)  symcheck: r21 review, flag was an artefact. fn_80280F1C: (a) 3 blocks: int-to-float conversion temporaries left
   in f2/f3 before fn_80253EE4(const char*, f32) (reads r3, f1); stores equal. See docs/SCHED_REVIEW.md. */
/* r19: copied from wip/fn_80280F1C.cpp; `sched` level (same instructions per basic block, order differs). */
/* NEAR MISS: 10 lines: float temporaries in the scroll helper differ by site. */
/* Save record list: input */
#include "game/rN_8025EEF0/calls.h"

struct RecScr {
    u8 pad[0x3C];
    f32 cur, from, to;
    u16 t, tMax;
    u8 m4C, m4D, m4E;
};

extern "C" {

extern char lbl_80392BE8[], lbl_80392C08[];
f32 fn_8017F68C(int mode, f32 from, f32 to, f32 t, f32 d);
double fn_80295CF0(double a);
void fn_80253EE4(const char* s, f32 v);

static inline void go(RecScr* o, u16 k, u16 t) {
    f32 w = k * -0x46;
    o->m4C = k;
    o->from = o->cur;
    o->to = w;
    o->tMax = t;
    o->t = t;
    fn_80253EE4(lbl_80392BE8, 0.0f);
}

void fn_80280F1C(RecScr* o) {
/*P*/
    u32 pr;
    u32 held;
/*E*/
    o->m4E++;
    pr = lbl_804CB5B8->v48();
    held = lbl_804CB5B8->v3C();
    if ((pr & 0x400) || (pr & 0x800)) {
        fn_80253EE4(lbl_80392C08, 0.0f);
        fn_80083B78(o);
        return;
    }
    if (o->m4D == 4) return;
    if (held & 0x800008) {
        if (o->m4C == 0) {
            if (pr & 0x800008) {
                s16 s = fn_80295CF0(o->m4D * 4);
                go(o, o->m4D - 4, s);
            }
        } else {
            go(o, o->m4C - 1, 4);
        }
    } else if (held & 0x400004) {
        if (o->m4C == o->m4D - 4) {
            if (pr & 0x400004) {
                s16 s = fn_80295CF0(o->m4D * 4);
                go(o, 0, s);
            }
        } else {
            go(o, o->m4C + 1, 4);
        }
    }
    if (o->t > 0) {
        o->cur = fn_8017F68C(0, o->from, o->to, o->tMax - o->t, o->tMax);
        o->t--;
    } else if (o->t == 0) {
        o->cur = o->to;
    }
}

}
