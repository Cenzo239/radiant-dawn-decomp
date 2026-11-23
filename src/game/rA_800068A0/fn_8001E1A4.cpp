#include "game/rA_800068A0/types.h"

/* Math helpers: fixed-point matrix conversion, sine table, matrix/quaternion
 * utilities. */

typedef struct Vec { f32 x, y, z; } Vec;
typedef f32 Mtx[3][4];

extern "C" {

static inline f32 fx2f(s16 v) { return 0.0078125f * v; }
static inline s32 f2fx(f32 v) { return 128.0f * v; }

typedef struct SMtx { s16 m[12]; } SMtx;
typedef struct FMtx { f32 m[12]; } FMtx;

FMtx* fn_8001E1A4(SMtx* in, FMtx* out) {
#define R(i) out->m[i] = fx2f(in->m[i]);
    R(0) R(1) R(2) R(3) R(4) R(5) R(6) R(7) R(8) R(9) R(10) R(11)
#undef R
    return out;
}

SMtx* fn_8001E318(FMtx* in, SMtx* out) {
#define R(i) out->m[i] = f2fx(in->m[i]);
    R(0) R(1) R(2) R(3) R(4) R(5) R(6) R(7) R(8) R(9) R(10) R(11)
#undef R
    return out;
}

extern s16 lbl_803B7878[0x4000];
extern f64 fn_80295940(f64);
extern void fn_80006D00(f32);

void fn_8001E44C(void) {
    int i;
    for (i = 0; i < 0x4000; i++) {
        f32 v = fn_80295940(6.2831855f * i / 16384.0f);
        v *= 16384.0f;
        lbl_803B7878[i] = v;
    }
    fn_80006D00(1.0f);
}

void fn_8001E51C(f32* a) {
    a[0] = 0.5f;
    a[1] = 0.0f;
    a[2] = 0.0f;
    a[3] = 0.0f;
    a[4] = 0.5f;
    a[5] = 0.0f;
}

int fn_8001E548(const char* s, const char* key) {
    if (s == 0 || *s == 0) {
        return 0;
    }
    if (key != 0) {
        const char* p = 0;
        while (*s != 0) {
            if (p != 0) {
                if (*p++ == *s++) {
                    if (*p == 0 && *s == '_') {
                        return 1;
                    }
                } else {
                    p = 0;
                }
            } else {
                if (*s++ == '_') {
                    p = key;
                }
            }
        }
    } else {
        for (; *s != 0; s++) {
            if (*s == '_') {
                while (*s != 0) {
                    s++;
                }
                if (s[-1] == '_') {
                    return 1;
                }
                break;
            }
        }
    }
    return 0;
}

extern void fn_80312344(const void*, void*);
extern void fn_80312378(const void*, const void*, void*);
extern void fn_80312318(void*);
extern void fn_803128AC(void*, f32, f32, f32);
extern void fn_80312DB4(const void*, const void*, void*);
extern void fn_803134C4(const void*, void*);
extern void fn_8031356C(const void*, const void*, void*);
extern f32 fn_8031354C(const void*, const void*);
extern f64 fn_80295A90(f64);
extern void fn_80312830(void*, const void*, f32);
extern f32 fn_80313508(const void*);
void fn_8001E70C(const Mtx, Mtx);

void fn_8001E638(const Mtx src, Mtx dst) {
    Mtx m;
    Mtx r;
    fn_80312344(src, m);
    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
    fn_8001E70C(m, r);
    fn_80312378(r, m, dst);
}

void fn_8001E694(const Mtx m, void* o) {
    fn_803128AC(o, m[0][3], m[1][3], m[2][3]);
}

void fn_8001E6AC(const Mtx m, void* o) {
    fn_803128AC(o, -m[0][3], -m[1][3], -m[2][3]);
}

void fn_8001E6D0(const Mtx src, Mtx dst) {
    fn_80312344(src, dst);
    dst[0][3] = 0.0f;
    dst[1][3] = 0.0f;
    dst[2][3] = 0.0f;
}

void fn_8001E70C(const Mtx src, Mtx rot) {
    Mtx m;
    Mtx r;
    fn_80312344(src, m);
    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
    fn_80312318(rot);
    Vec axes[3] = {{0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}};
    Vec v;
    Vec c;
    Vec* a = axes;
    for (int i = 0; i < 3; i++) {
        fn_80312DB4(m, a, &v);
        if (0.0f != v.x * v.x + v.y * v.y + v.z * v.z) {
            fn_803134C4(&v, &v);
            fn_8031356C(a, &v, &c);
            if (0.0f == c.x * c.x + c.y * c.y + c.z * c.z) {
                fn_80312318(r);
            } else {
                f32 d = fn_8031354C(a, &v);
                f32 ang;
                if (d >= 0.9999f) {
                    ang = 0.0f;
                } else if (d <= -0.9999f) {
                    ang = 3.1415927f;
                } else {
                    ang = fn_80295A90(d);
                }
                fn_80312830(r, &c, -ang);
            }
            fn_80312378(r, rot, rot);
            fn_80312378(r, m, m);
        }
        a++;
    }
}

extern void* fn_8000F470(void);
extern void fn_80313484(const void*, const void*, void*);
extern void fn_80312444(const void*, void*);
extern f64 fn_802952C8(f64);
extern void fn_80312654(void*, int, f32);

void fn_8001E8E8(const Mtx a, Mtx o) {
    u8* cam = (u8*)fn_8000F470();
    Vec d;
    Vec u;
    f32 ang;
    fn_80313484(cam + 0xE0, cam + 0xD4, &d);
    fn_80312444(a, o);
    fn_80312DB4(o, &d, &d);
    fn_80312DB4(o, cam + 0xEC, &u);
    if (0.0f == d.x) {
        fn_80312318(o);
        return;
    }
    ang = fn_802952C8(d.z / d.x);
    if (d.x < 0.0f) {
        ang = 1.5707964f + -ang;
    } else {
        ang = -ang - 1.5707964f;
    }
    if (u.y < 0.0f) {
        ang -= 3.1415927f;
    }
    fn_80312654(o, 0x59, ang);
}

void fn_8001E9E4(const Mtx m, Vec* v) {
    v->x = 0.0f;
    v->y = 0.0f;
    v->z = 0.0f;
    fn_80312DB4(m, v, v);
}

extern void fn_803135A8(void*, const void*);
extern void fn_80313774(const void*, const void*, void*, f32);
extern void fn_803129AC(void*, const void*);

void fn_8001E9FC(const Mtx a, const Mtx b, void* o, f32 t) {
    f32 q0[4];
    f32 q1[4];
    f32 q[4];
    fn_803135A8(q0, a);
    fn_803135A8(q1, b);
    fn_80313774(q0, q1, q, t);
    fn_803129AC(o, q);
}

f32 fn_8001EA74(const Vec* a, const Vec* b) {
    f32 d = fn_8031354C(a, b);
    if (d >= 0.9999f) {
        return 0.0f;
    }
    if (d <= -0.9999f) {
        return 3.1415927f;
    }
    return fn_80295A90(d);
}

void fn_8001EACC(const Vec* a, const Vec* b, Mtx m) {
    Vec na;
    Vec nb;
    Vec c;
    fn_80312318(m);
    if (0.0f == fn_80313508(a)) {
        return;
    }
    if (0.0f == fn_80313508(b)) {
        return;
    }
    fn_803134C4(a, &na);
    fn_803134C4(b, &nb);
    fn_8031356C(&na, &nb, &c);
    if (0.0f == fn_80313508(&c)) {
        return;
    }
    fn_80312830(m, &c, fn_8001EA74(&na, &nb));
}

} /* extern "C" */
