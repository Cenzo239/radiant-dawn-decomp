/* functionally equal (check_regs). Round 18: the sign flip is `side == 0 ? r : -r` (gives the bne; b; fneg shape). */
/* Two-group slide animation proc */
#include "game/rN_8025EEF0/calls.h"

extern "C" {

f32 fn_8017F68C(int mode, f32 from, f32 to, f32 t, f32 d);

struct Anim { f32 pad0[6]; s16 r18; s16 r1A; f32 s1C; };
struct Anim2 { u8 pad[0x104]; f32 s; };
struct Slide {
    u8 pad[0x40];
    int side;
    u32 t;
    u8 pad48[8];
    Anim* a[2];
    Anim* b[2];
    Anim2* c[2];
    Anim2* d[2];
};

static inline f32 sg(int s, f32 r) { if (s != 0) { return -r; } else { return r; } }
static inline f32 sg2(Slide* p, f32 r) { switch (p->side) { case 0: return r; default: return -r; } }
static inline f32 sg3(int s, f32 r) { switch (s) { case 0: break; default: r = -r; } return r; }
static inline f32 sg4(Slide* p, f32 r) { return p->side == 0 ? r : -r; }
void fn_80271434(Slide* p) {
    Anim* a;
    Anim2* c;
    Anim* b;
    Anim2* d;
    f32 s;
    u32 n = 45;
    f32 r;
    int k;
    int t;
    t = p->t + 1;
    k = p->side;
    a = p->a[k];
    c = p->c[k];
    b = p->b[k];
    d = p->d[k];
    p->t = t;
    s = fn_8017F68C(5, 0.0f, 1.0f, t, n);
    r = fn_8017F68C(5, 64.0f, 0.0f, (int)p->t, n);
    a->s1C = s;
    r = sg4(p, r);
    a->r18 = (int)r;
    a->r1A = 0;
    c->s = s;
    n = 45;
    s = fn_8017F68C(5, 1.0f, 0.0f, (int)p->t, n);
    r = fn_8017F68C(5, 0.0f, 64.0f, (int)p->t, n);
    b->s1C = s;
    r = sg4(p, r);
    b->r18 = (int)r;
    b->r1A = 0;
    d->s = s;
    if (p->t >= n) {
        a->s1C = 1.0f;
        a->r18 = 0;
        a->r1A = 0;
        c->s = 1.0f;
        b->s1C = 0.0f;
        b->r18 = 0;
        b->r1A = 0;
        d->s = 0.0f;
        p->t = 0;
        fn_80083B78(p);
    }
}

}
