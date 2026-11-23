#include "game/rP_80105B04/rp.h"

/* Biorhythm. "BioParam" holds the band limits, "BioData" one row per
   curve {amp, scale, freq, base}. Unit +0x378 curve id, +0x37A phase, +0x37C time. */
struct BioRow { f32 a, b, c, d; };
struct BioPerson { u8 pad[0xE4]; s8 e4; s8 e5; };
struct BioUnit {
    u8 pad[0xEC];
    BioPerson* person; /* 0xEC */
    u8 padF0[0x378 - 0xF0];
    s8 curve;  /* 0x378 */
    u8 pad379;
    s16 phase; /* 0x37A */
    s16 time;  /* 0x37C */
};
struct BioParam { f32 v; f32 p[2]; };

static inline f32 BioSign(f32 m) {
    f32 s = 0.0f;
    if (s < m) s = 1.0f;
    else if (m < s) s = -1.0f;
    return s;
}
static inline f32 BioSign2(f32 m) {
    f32 s = 0.0f;
    if (s < m) s = -1.0f;
    else if (m < s) s = 1.0f;
    return s;
}
extern "C" {
extern char lbl_80367F28[];
void* fn_80077064(const char* name);
double fn_80295940(double x);
double fn_80295A94(double x);
int fn_80089C1C();
f32 fn_80127868(BioUnit* u);

void fn_80106F98(f32* out, f32 k) {
    BioParam* p = (BioParam*)fn_80077064(lbl_80367F28);
    out[0] = p[0].v * k;
    out[1] = p[1].v * k;
    out[2] = p[2].v * k;
    out[3] = p[3].v * k;
    out[4] = p[4].v * k;
}

void fn_8010701C(BioUnit* u, f32* a, f32* b, f32* c, f32* d) {
    s8 curve = u->curve;
    BioRow* r;
    if (curve < 0) curve = u->person->e4;
    r = (BioRow*)fn_80077064(lbl_80367F28 + 9);
    *a = r[(u8)curve].a;
    *b = r[(u8)curve].b;
    *c = r[(u8)curve].c;
    *d = r[(u8)curve].d;
}

f32 fn_801070A4(BioUnit* u) {
    s16 t = u->time;
    s8 curve = u->curve;
    BioRow* r;
    f32 d, b, c, a, s, p, q;
    int ph;
    if (curve < 0) curve = u->person->e4;
    r = (BioRow*)fn_80077064(lbl_80367F28 + 9);
    a = r[(u8)curve].a;
    b = r[(u8)curve].b;
    c = r[(u8)curve].c;
    d = r[(u8)curve].d;
    ph = u->phase;
    if (ph < 0) ph = u->person->e5;
    p = 6.2831855f * (u8)ph / 100.0f;
    q = 6.2831855f * t / 100.0f;
    return a * b * (f32)fn_80295940(c * q + p) + d;
}

f32 fn_801071C4(BioUnit* u, int t) {
    s8 curve = u->curve;
    BioRow* r;
    f32 a, b, d, c, p, q;
    int ph;
    if (curve < 0) curve = u->person->e4;
    r = (BioRow*)fn_80077064(lbl_80367F28 + 9);
    a = r[(u8)curve].a;
    b = r[(u8)curve].b;
    c = r[(u8)curve].c;
    d = r[(u8)curve].d;
    ph = u->phase;
    if (ph < 0) ph = u->person->e5;
    p = 6.2831855f * (u8)ph / 100.0f;
    q = 6.2831855f * t / 100.0f;
    return a * b * (f32)fn_80295940(c * q + p) + d;
}

f32 fn_801072E4(BioUnit* u) {
    s8 curve = u->curve;
    BioRow* r;
    f32 a, b, c, p, s;
    int ph;
    if (curve < 0) curve = u->person->e4;
    r = (BioRow*)fn_80077064(lbl_80367F28 + 9);
    a = r[(u8)curve].a;
    b = r[(u8)curve].b;
    c = r[(u8)curve].c;
    ph = u->phase;
    p = 6.2831855f * (u8)(ph < 0 ? u->person->e5 : ph) / 100.0f;
    s = BioSign(a * b);
    if (0.0f == s || 0.0f == c) {
        if (ph < 0) ph = u->person->e5;
        return (u8)ph;
    }
    return 100.0f * (((f32)fn_80295A94(s) - p) / c) / 6.2831855f;
}

f32 fn_80107444(BioUnit* u) {
    s8 curve = u->curve;
    BioRow* r;
    f32 a, b, c, p, s;
    int ph;
    if (curve < 0) curve = u->person->e4;
    r = (BioRow*)fn_80077064(lbl_80367F28 + 9);
    a = r[(u8)curve].a;
    b = r[(u8)curve].b;
    c = r[(u8)curve].c;
    ph = u->phase;
    p = 6.2831855f * (u8)(ph < 0 ? u->person->e5 : ph) / 100.0f;
    s = BioSign2(a * b);
    if (0.0f == s || 0.0f == c) {
        if (ph < 0) ph = u->person->e5;
        return (u8)ph;
    }
    return 100.0f * (((f32)fn_80295A94(s) - p) / c) / 6.2831855f;
}

static inline int BioBand(f32 x) {
    f32 t[5];
    fn_80106F98(t, 1.0f);
    if (t[0] <= x) return 0;
    if (t[1] <= x) return 1;
    if (t[3] < x) return 2;
    if (t[4] < x) return 3;
    return 4;
}
int fn_801076D0(BioUnit* u) {
    return BioBand(fn_80127868(u));
}
int fn_8010779C(BioUnit* u, f32 x) {
    return BioBand(x);
}

f32 fn_801075A4(BioUnit* u, s8 id) {
    s8 curve = u->curve;
    BioRow* r;
    f32 a, b, v;
    if (curve < 0) curve = u->person->e4;
    r = (BioRow*)fn_80077064(lbl_80367F28 + 9);
    a = r[(u8)curve].a;
    b = r[(u8)curve].b;
    switch (id) {
    case 0: v = 25.0f; break;
    case 1: v = 12.5f; break;
    case 2: v = 37.5f; break;
    case 3: v = 0.0f; break;
    case 4: v = 62.5f; break;
    case 5: v = 87.5f; break;
    case 6: v = 75.0f; break;
    default: v = fn_80089C1C(); break;
    }
    if (a * b < 0.0f) v += 50.0f;
    while (100.0f < v) v -= 100.0f;
    return v;
}
}
