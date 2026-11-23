/* NEAR MISS (round 17): 95 positional lines. Constant 4 for the tween calls is kept in a saved register (orig rematerializes li r3,4 and converts it), which shifts volatile and saved registers. */
/* Random-order list (soundroom): per-frame input, scrolling and playback */
#include "game/rN_8025EEF0/calls.h"

struct ListItem { const char* name; s16 x; s16 y; s16 s; };
struct ListE2 { const char* name; const char* b; };
struct ListSt {
    void* tex;
    void* tex2;
    int* file;
    int n;
    int m10;
    ListItem* items;
    ListE2* e2;
    int m1C;
    int m20;
    int m24;
    int m28;
    int m2C;
    int m30;
    u8* m34;
    const char* m38;
    const char* m3C;
    s16 m40, m42;
    void* bar;
    char txt[0x100];
    f32 m148;
    s16 m14C, m14E, m150, m152;
    s16 m154, m156, m158, m15A, m15C, m15E, m160, m162, m164, m166, m168, m16A, m16C, m16E;
};

class Bgm {
public:
    virtual void v08(); virtual void v0C();
    virtual int v10();
    virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20();
    virtual void v24(int t);
};

extern "C" {

extern ListSt* lbl_804CC044;
extern void* lbl_804CC040;
extern char lbl_8037340C[];
s16 fn_8024F3C8(const char* s);
int fn_802454C8(void* s, int a);
int fn_8024F61C(const char* s);
Bgm* fn_8024F3FC(int a);
void fn_8026D470(void);
void fn_8026D63C(void);
f32 fn_8017F68C(f32 a, f32 b, f32 c, f32 d, int e);
f64 fn_80295CF0(f64 x);
void fn_80251838(int a, const char* s, f32 v);
void fn_80253EE4(const char* s, f32 v);

static inline f32 ease(f32 a, f32 b, int t) { int k = 4; return fn_8017F68C(a, b, t, k, k); }
static inline f32 ease2(f32 a, f32 b, int t, int k) { return fn_8017F68C(a, b, t, k, k); }
static inline f32 ease3(f32 a, f32 b, int t) { s16 k = 4; return fn_8017F68C(a, b, t, k, k); }
static inline void scrollTo(f32 to, s16 n) {
    lbl_804CC044->m14C = lbl_804CC044->m148;
    lbl_804CC044->m14E = to;
    lbl_804CC044->m152 = n;
    lbl_804CC044->m150 = n;
}

static inline void moved(void) {
    lbl_804CC044->m158 = 4;
    lbl_804CC044->m15A = lbl_804CC044->m154;
    lbl_804CC044->m15C = lbl_804CC044->m156;
    lbl_804CC044->m15E = lbl_804CC044->m162 + 0x16;
    lbl_804CC044->m160 = lbl_804CC044->m164 + (lbl_804CC044->m24 - lbl_804CC044->m14E) * 0x1C + 0xE;
}

static inline void nextModel(void) {
    lbl_804CC044->m1C++;
    if (lbl_804CC044->m1C > lbl_804CC044->n - 1) lbl_804CC044->m1C = 0;
    fn_8026D470();
}

static inline void fadeBgm(int t) {
    Bgm* b = fn_8024F3FC(0);
    if (b != 0 && b->v10() != 0) b->v24(t);
}

void fn_8026E9DC(void) {
/*P*/
    u32 pr;
    u32 held;
    int old;
    void* save;
    int k;
    int t;
    int sel;
    int lim;
    int t2;
    f32 f;
/*E*/
    pr = lbl_804CB5B8->v48();
    held = lbl_804CB5B8->v3C();
    old = lbl_804CC044->m24;
    save = fn_8024BC94();
    if (lbl_804CC044->m150 > 0) {
        lbl_804CC044->m150 = lbl_804CC044->m150 - 1;
        lbl_804CC044->m148 = fn_8017F68C(lbl_804CC044->m14C, lbl_804CC044->m14E,
                                         lbl_804CC044->m152 - lbl_804CC044->m150, lbl_804CC044->m152, 0);
    }
    if (lbl_804CC044->m158 > 0) {
        lbl_804CC044->m158 = lbl_804CC044->m158 - 1;
        t = 4 - lbl_804CC044->m158;
        lbl_804CC044->m154 = fn_8017F68C(lbl_804CC044->m15A, lbl_804CC044->m15E, t, k = 4, k);
        lbl_804CC044->m156 = fn_8017F68C(lbl_804CC044->m15C, lbl_804CC044->m160, t, k = 4, k);
    }
    lbl_804CC044->m16A = 0x80;
    if (lbl_804CC044->m28 != -1) {
        lbl_804CC044->m16C = lbl_804CC044->m16C - 4;
        if (lbl_804CC044->m16C < 0x72) lbl_804CC044->m16C = 0x72;
        lbl_804CC044->m16E = lbl_804CC044->m16E + 8;
        if (lbl_804CC044->m16E > 0xFF) lbl_804CC044->m16E = 0xFF;
    } else {
        lbl_804CC044->m16C = lbl_804CC044->m16C + 4;
        if (lbl_804CC044->m16C > lbl_804CC044->m164) lbl_804CC044->m16C = lbl_804CC044->m164;
        lbl_804CC044->m16E = lbl_804CC044->m16E - 0x10;
        if (lbl_804CC044->m16E < 0) lbl_804CC044->m16E = 0;
    }
    if (lbl_804CC044->m40 > lbl_804CC044->m42) {
        lbl_804CC044->m40 = lbl_804CC044->m40 - 0x18;
        if (lbl_804CC044->m40 < lbl_804CC044->m42) lbl_804CC044->m40 = lbl_804CC044->m42;
    }
    if (lbl_804CC044->m40 < lbl_804CC044->m42) {
        lbl_804CC044->m40 = lbl_804CC044->m40 + 0x18;
        if (lbl_804CC044->m40 > lbl_804CC044->m42) lbl_804CC044->m40 = lbl_804CC044->m42;
    }
    if (lbl_804CC044->m20 >= 0) {
        if (lbl_804CC044->m20 == 0) fn_80251838(0, lbl_804CC044->e2[lbl_804CC044->m28].name, 100.0f);
        lbl_804CC044->m20 = lbl_804CC044->m20 - 1;
    }
    if (lbl_804CC044->m150 > 0) return;
    if (lbl_804CC044->m42 != 0) {
        if (pr & 0x400) {
            if (lbl_804CC044->m20 >= 0) return;
            if (fn_802454C8(save, fn_8024F3C8(lbl_804CC044->e2[lbl_804CC044->m24].name)) == 0) return;
            nextModel();
            if (fn_8024F61C(lbl_804CC044->e2[lbl_804CC044->m24].name) == 0) {
                fn_8026D63C();
                sel = lbl_804CC044->m24;
                fadeBgm(100);
                lbl_804CC044->m20 = 10;
                lbl_804CC044->m28 = sel;
                return;
            }
        }
        if (pr & 0x10) {
            if (lbl_804CC044->m20 >= 0) return;
            if (lbl_804CC044->m30 == 0) return;
            nextModel();
            if (fn_8024F61C(lbl_804CC044->e2[lbl_804CC044->m34[lbl_804CC044->m2C]].name) == 0) {
                sel = lbl_804CC044->m34[lbl_804CC044->m2C];
                fadeBgm(100);
                lbl_804CC044->m20 = 10;
                lbl_804CC044->m28 = sel;
            }
            if (lbl_804CC044->m2C >= lbl_804CC044->m30 - 1) {
                fn_8026D63C();
            } else {
                lbl_804CC044->m2C = lbl_804CC044->m2C + 1;
            }
        } else if (pr & 0x800) {
            if (lbl_804CC044->m28 != -1) {
                fadeBgm(0xFA);
                lbl_804CC044->m20 = -1;
                lbl_804CC044->m28 = -1;
                fn_8026D63C();
            } else {
                fn_80253EE4(lbl_8037340C + 0x71, 0.0f);
                fn_80083B78(lbl_804CC040);
            }
        } else if (pr & 0x1000) {
            lbl_804CC044->m42 = 0;
        } else if (held & 0x100001) {
            if (lbl_804CC044->m14E != 0) {
                t2 = lbl_804CC044->m14E - 7;
                if (t2 < 0) {
                    scrollTo(0, 4);
                } else {
                    scrollTo(t2, 4);
                }
            }
            lbl_804CC044->m24 = lbl_804CC044->m24 - 7;
            if (lbl_804CC044->m24 < 0) lbl_804CC044->m24 = 0;
            if (old != lbl_804CC044->m24) moved();
        } else if (held & 0x200002) {
            lim = lbl_804CC044->m10 - 7;
            if (lbl_804CC044->m14E != lim) {
                t2 = lbl_804CC044->m14E + 7;
                if (t2 > lim) {
                    scrollTo(lim, 4);
                } else {
                    scrollTo(t2, 4);
                }
            }
            lbl_804CC044->m24 = lbl_804CC044->m24 + 7;
            if (lbl_804CC044->m24 > lbl_804CC044->m10 - 1) lbl_804CC044->m24 = lbl_804CC044->m10 - 1;
            if (old != lbl_804CC044->m24) moved();
        } else {
            if (lbl_804CC044->m24 == 0) {
                if (pr & 0x800008) {
                    lbl_804CC044->m24 = lbl_804CC044->m10 - 1;
                    scrollTo(lbl_804CC044->m10 - 7, fn_80295CF0(lbl_804CC044->m10 * 4));
                }
            } else if (held & 0x800008) {
                lbl_804CC044->m24 = lbl_804CC044->m24 - 1;
                f = lbl_804CC044->m148;
                if ((f32)lbl_804CC044->m24 - f <= 1.0f && f > 0.0f) scrollTo(f - 1.0f, 4);
            }
            if (lbl_804CC044->m24 == lbl_804CC044->m10 - 1) {
                if (pr & 0x400004) {
                    lbl_804CC044->m24 = 0;
                    scrollTo(0, fn_80295CF0(lbl_804CC044->m10 * 4));
                }
            } else if (held & 0x400004) {
                lbl_804CC044->m24 = lbl_804CC044->m24 + 1;
                f = lbl_804CC044->m148;
                if ((f32)lbl_804CC044->m24 - f >= 5.0f && f < (f32)(lbl_804CC044->m10 - 7)) scrollTo(1.0f + f, 4);
            }
            if (old != lbl_804CC044->m24) moved();
        }
    } else {
        if ((pr & 0x400) || (pr & 0x200002)) {
            nextModel();
        } else if (pr & 0x100001) {
            lbl_804CC044->m1C = lbl_804CC044->m1C - 1;
            if (lbl_804CC044->m1C < 0) lbl_804CC044->m1C = lbl_804CC044->n - 1;
            fn_8026D470();
        } else if ((pr & 0x800) || (pr & 0x1000) || (pr & 0x4000)) {
            lbl_804CC044->m42 = 0xFF;
        }
    }
}

}
