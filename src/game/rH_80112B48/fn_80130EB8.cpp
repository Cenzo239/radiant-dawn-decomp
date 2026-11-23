/* Camera script tick: advance the time, ease it by the key's curve and apply the keys, 80130EB8. */
#include "game/rH_80112B48/types.h"
#pragma auto_inline off
extern "C" {
struct Ev {
    u8 kind;
    s16 key;
    Vec v;
    int d;
};
struct Evs {
    u8 pad[0x30];
    int mode;
    int t34;
    int maxk;
    u8 done;
    u8 pad3d[3];
    Ev* ev;
    u8 n;
    u8 pad45;
    u8 cnt[5];
    u8 pad4b;
    Ev* first[5];
};
extern u32 lbl_804CB700;
extern void fn_80083DC4(Evs*, int);
extern void fn_80130BB4(Evs*, f32);
extern f32 fn_8001EF30(f32, f32, f32, f32);
extern f32 fn_8001ECE4(int, f32, f32, f32, f32);
extern f32 fn_8001EBC8(int, f32, f32, f32, f32);
static inline int Idx(Evs* s, f32 t) {
    Ev* e;
    int r;
    int i;
    int n = s->cnt[4];
    if (n == 0) return -1;
    e = s->first[4];
    r = 0;
    for (i = 0; i < n; i++, e++) {
        if ((f32)e->key > t) break;
        r = i;
    }
    return r;
}
static inline Ev* Get(Evs* s, int i) {
    if (s->cnt[4] == 0) return 0;
    if (i < 0) return 0;
    if (i >= s->cnt[4]) return 0;
    return &s->first[4][i];
}
void fn_80130EB8(Evs* s) {
    /*P*/
    int k;
    f32 t;
    f32 a;
    f32 b;
    f32 d;
    f32 l;
    int mode;
    /*E*/
    s->t34++;
    if (lbl_804CB700 & 0x8001) {
        s->t34 = s->maxk;
    }
    if (s->t34 >= s->maxk) {
        s->t34 = s->maxk;
        s->done = 1;
        fn_80083DC4(s, 0);
    }
    k = -1;
    t = s->t34;
    a = 0.0f;
    b = s->maxk;
    mode = s->mode;
    if (s->cnt[4]) {
        int i = Idx(s, t);
        Ev* e = Get(s, i);
        if (e) {
            a = e->key;
            mode = e->d;
            e = Get(s, i + 1);
            if (e) b = e->key;
            e = Get(s, i - 1);
            if (e && e->d == 0) k = 0;
        }
    }
    d = t - a;
    l = b - a;
    switch (mode) {
    case 0:
        t = fn_8001EF30(a, b, l, d);
        break;
    case 1:
        t = fn_8001EF30(a, b, l, d);
        t = fn_8001EF30(t, fn_8001ECE4(2, a, b, l, d), l, d);
        break;
    case 2:
        t = fn_8001EF30(a, b, l, d);
        t = fn_8001EF30(t, fn_8001EBC8(2, a, b, l, d), l, d);
        break;
    case 3: {
        f32 h = l / 2.0f;
        if (d < h) {
            t = fn_8001ECE4(2, a, l / 2.0f + a, h, d);
        } else {
            t = fn_8001EBC8(2, l / 2.0f + a, b, h, d - l / 2.0f);
        }
        break;
    }
    }
    switch (k) {
    case 0:
        t = fn_8001EF30(fn_8001EF30(a, b, l, d), t, l, d);
        break;
    default:
        break;
    }
    fn_80130BB4(s, t);
}
}
