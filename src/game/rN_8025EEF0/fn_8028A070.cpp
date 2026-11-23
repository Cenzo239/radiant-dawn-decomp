/* Staff roll: per-frame logic */
#include "game/rN_8025EEF0/calls.h"

extern "C" {

f32 fn_8017F68C(f32 a, f32 b, f32 t, f32 d, int mode);
u32 fn_8028C1A0(f32 v);
void fn_80251838(int a, void* b, f32 c);

class Snd {
public:
    virtual void v08(); virtual void v0C();
    virtual int v10();
    virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20();
    virtual void v24(int a);
};
Snd* fn_8024F3FC(int a);

struct Roll {
    u8 pad[0x32];
    u16 m32;
    f32 m34;
    u8 m38, m39;
    u16 m3A;
    void* m3C; void* m40;
    u32 m44, m48;
    int m4C;
    u32 m50;
    u8 pad54[6];
    u8 m5A;
    u8 pad5B[0x70 - 0x5B];
    s64 m70;
    f32 t;
    s16 m7C, m7E, m80;
    u8 pad82[0x9C - 0x82];
    u32* k;
};

void fn_8028A070(Roll* r) {
    u32 in = lbl_804CB5B8->v48();
    if ((s64)r->m32 < r->m70) {
        r->m32++;
    } else {
        r->m5A = 0;
    }
    if (!((s64)r->m32 < r->m70)) {
        r->m80 = 0;
        r->t = 0.0f;
        fn_80083B78(r);
        return;
    }
    if (r->m3A == 0) {
        if (r->m34 >= (f32)r->m44) {
            r->m3A = 1;
            fn_80251838(0, r->m3C, 0.0f);
        }
    } else if (r->m3A == 1) {
        if (r->m34 >= (f32)r->m48) {
            Snd* s;
            r->m3A = 2;
            s = fn_8024F3FC(0);
            if (s != 0 && s->v10() != 0) {
                s->v24(r->m4C);
            }
        }
    } else if (r->m3A == 2) {
        if (r->m34 >= (f32)r->m50) {
            r->m3A = 3;
            fn_80251838(0, r->m40, 0.0f);
        }
    }
    if (r->k[0] != 999) {
/*P*/
        f32 q;
        u32* k;
        u32 a;
        u32 b;
        u32 c;
        u32 d;
        f32 f;
        f32 t;
/*E*/
        k = r->k;
        f = r->t;
        q = 16.666666f;
        t = f + q;
        r->t = t;
        a = k[1];
        if (t < (f32)a) {
            r->m7E = 0;
        } else if (b = k[2], t < (f32)b) {
            r->m7E = (int)fn_8017F68C(0.0f, 255.0f, t - (f32)a, (f32)(b - a), 0);
        } else if (c = k[3], t < (f32)c) {
            r->m7E = 0xFF;
        } else if (d = k[4], t < (f32)d) {
            r->m7E = (int)fn_8017F68C(255.0f, 0.0f, t - (f32)c, (f32)(d - c), 0);
        } else {
            u32 w = fn_8028C1A0(t);
            r->m7E = 0;
            r->k = r->k + 5;
            r->t -= (f32)w;
        }
    }
    if ((in & 0x4000) && r->m38 != 0 && r->m34 >= 10000.0f) {
        r->m39 = 1;
        r->t = 0.0f;
        fn_80083DC4(r, 1);
    }
}

}
