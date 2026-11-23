/* Result report: scroll input */
#include "game/rN_8025EEF0/calls.h"

struct Rep {
    u8 pad[8];
    s16 n;
    u8 padA[0x202];
    s16 t, tMax;
    f32 cur, from, to;
};

extern "C" {

extern Rep* lbl_804CC0D4;
extern void* lbl_804CC0D0;
extern char lbl_80373CF0[];
f32 fn_8017F68C(f32 a, f32 b, f32 c, f32 d, int e);
double fn_80295CF0(double a);
void fn_80253EE4(const char* s, f32 v);

static inline void go(f32 v, s16 t) {
    lbl_804CC0D4->from = lbl_804CC0D4->cur;
    lbl_804CC0D4->to = v;
    lbl_804CC0D4->tMax = t;
    lbl_804CC0D4->t = t;
}
static inline void go8(f32 v) { go(v, 8); }

void fn_8028831C(void) {
/*P*/
    u32 pr;
    u32 held;
    f32 old;
/*E*/
    pr = lbl_804CB5B8->v48();
    held = lbl_804CB5B8->v3C();
    if (lbl_804CC0D4->t > 0) {
        lbl_804CC0D4->t--;
        lbl_804CC0D4->cur = fn_8017F68C(lbl_804CC0D4->from, lbl_804CC0D4->to, lbl_804CC0D4->tMax - lbl_804CC0D4->t, lbl_804CC0D4->tMax, 0);
    }
    if (lbl_804CC0D4->t > 0) return;
    if (pr & 0x800) {
        fn_80253EE4(lbl_80373CF0 + 0x73, 0.0f);
        fn_80083B78(lbl_804CC0D0);
        return;
    }
    if (lbl_804CC0D4->n < 9) return;
    old = lbl_804CC0D4->to;
    if ((held & 0x100001) && old != 0.0f) {
        if (old - 9.0f < 0.0f) {
            go8(0.0f);
        } else {
            go8(old - 9.0f);
        }
    }
    if (held & 0x200002) {
        int n = lbl_804CC0D4->n;
        if (lbl_804CC0D4->to != (f32)n - 9.0f) {
            f32 v = 9.0f + lbl_804CC0D4->to;
            if (v > (f32)n - 9.0f) {
                { f32 w = (f32)n - 9.0f; go8(w); }
            } else {
                go8(v);
            }
        }
    }
    if (lbl_804CC0D4->to == 0.0f) {
        if ((pr & 0x800008) && lbl_804CC0D4->n - 9 >= 0) {
            s16 s = fn_80295CF0(lbl_804CC0D4->n * 8);
            go(lbl_804CC0D4->n - 9, s);
        }
    } else if (held & 0x800008) {
        go8(lbl_804CC0D4->to - 1.0f);
    }
    if (lbl_804CC0D4->to == lbl_804CC0D4->n - 9) {
        if (pr & 0x400004) {
            s16 s = fn_80295CF0(lbl_804CC0D4->n * 8);
            go(0.0f, s);
        }
    } else if (held & 0x400004) {
        go8(1.0f + lbl_804CC0D4->to);
    }
    if (old != lbl_804CC0D4->to) {
        fn_80253EE4(lbl_80373CF0 + 0x83, 0.0f);
    }
}

}
