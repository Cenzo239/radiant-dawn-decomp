/* Result report: teardown; staff-roll style timed procs */
#include "game/rN_8025EEF0/calls.h"

struct Pad28Base { u8 pad[0x28]; };
class RepWin : public Pad28Base {
public:
    virtual void v08(); virtual void v0C(); virtual void v10();
    virtual ~RepWin();
};

extern "C" {

struct Rep { void* tex; RepWin* win; };
extern Rep* lbl_804CC0D4;
extern u8* lbl_804CC0D0;

void fn_8028893C(void) {
    RepWin* w = lbl_804CC0D4->win;
    if (w != 0) {
        delete w;
    }
    if (lbl_804CC0D4->tex != 0) {
        fn_80006A2C(lbl_804CC0D4);
    }
    fn_80078E24(*(void**)(lbl_804CC0D0 + 0x30));
    *(void**)(lbl_804CC0D0 + 0x30) = 0;
}

struct Roll {
    u8 pad[0x34];
    f32 m34;
    u8 m38;
    u8 m39;
    u8 pad3A[0x5A - 0x3A];
    u8 m5A;
    u8 pad5B[0x78 - 0x5B];
    f32 t;
    s16 m7C, m7E, m80, m82;
    u8 pad84[0x9C - 0x84];
    u32* k;
};
f32 fn_8017F68C(f32 a, f32 b, f32 t, f32 d, int mode);

void fn_80288E90(Roll* r) {
/*P*/
    f32 t;
    u32 a;
    u32 b;
    u32* k;
    u32 c;
    u32 d;
    f32 q;
    f32 f;
/*E*/
    q = 16.666666f;
    f = r->t;
    t = f + q;
    k = r->k;
    r->t = t;
    a = k[1];
    if (t < (f32)a) {
        r->m7C = 0;
    } else if (b = k[2], t < (f32)b) {
        r->m7C = (int)fn_8017F68C(0.0f, 255.0f, t - (f32)a, (f32)(b - a), 0);
    } else if (c = k[3], t < (f32)c) {
        r->m7C = 0xFF;
    } else if (d = k[4], t < (f32)d) {
        r->m7C = (int)fn_8017F68C(255.0f, 0.0f, t - (f32)c, (f32)(d - c), 0);
    } else {
        r->m5A = 1;
        r->t = 0.0f;
        r->m7C = 0;
        r->k = k + 5;
        fn_80083B78(r);
        return;
    }
    if ((lbl_804CB5B8->v48() & 0x4000) && r->m38 != 0 && r->m34 >= 10000.0f) {
        r->m39 = 1;
        r->t = 0.0f;
        fn_80083DC4(r, 1);
    }
}

class Snd {
public:
    virtual void v08(); virtual void v0C();
    virtual int v10();
    virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20();
    virtual void v24(int a);
};
Snd* fn_8024F3FC(int a);

void fn_8028905C(Roll* r) {
    if (r->m7C != 0 || r->m7E != 0 || r->m80 != 0) {
        int a = r->m7C - 3;
        int b = r->m7E - 3;
        int c = r->m80 - 3;
        r->m7C = a & ~(a >> 31);
        r->m7E = b & ~(b >> 31);
        r->m80 = c & ~(c >> 31);
        if (r->m7C != 0 || r->m7E != 0 || r->m80 != 0) {
            return;
        }
    }
    if (0.0f == r->t) {
        Snd* s = fn_8024F3FC(0);
        if (s != 0 && s->v10() != 0) {
            s->v24(4000);
        }
    }
    r->t += 16.666666f;
    if ((lbl_804CB5B8->v48() & 0x4000) && r->m38 != 0) {
        r->m39 = 1;
    }
    if (r->t > 7000.0f || (r->t > 4000.0f && r->m39 != 0)) {
        fn_80083B78(r);
    } else if (r->t < 2000.0f) {
        r->m82 = (int)fn_8017F68C(0.0f, 255.0f, r->t, 2000.0f, 0);
    } else if (r->t < 5000.0f) {
        r->m82 = 0xFF;
    }
}

}
