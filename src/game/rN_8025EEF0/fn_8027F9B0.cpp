/* Screen bars: two-digit number at a position, alpha from the bar state */
#include "game/rN_8025EEF0/prim2d.h"

struct Bars {
    s16 m0, m2, m4, m6, m8, mA, mC, mE, m10, m12, m14, m16, m18, m1A, m1C;
    u8 pad1E[2];
    void* m20;
};

extern "C" {

extern Bars* lbl_804CC0A8;
void fn_800804D4(int r, int g, int b, int a);

static inline void digit(s16 x, s16 y, int d, s16 al, f32 z, f32 s) {
    fn_8007E154();
    fn_8007E4E4(lbl_804CC0A8->m4, lbl_804CC0A8->m6, 300.0f + z, s);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080430(x, y, d * 0x27 + 1, 0.0f, 39.0f, 62.0f);
    fn_800804D4(0xFF, 0xFF, 0xFF, (u8)al);
    fn_80080578(0);
    fn_80080308();
}

static inline s16 dv(int v) { return v / 10; }
static inline s16 rm(int v, s16 t) { return v - t * 10; }
static inline s16 mix(int a, int m) { return a * m / 0xFF; }

void fn_8027F9B0(f32 z, f32 s, int v, s16 x, s16 y, int a, u32 fl) {
/*P*/
    s16 o;
    s16 t;
    s16 al;
/*E*/
    al = mix(a, lbl_804CC0A8->m1A);
    if (lbl_804CC0A8->m2 < 0) {
        return;
    }
    fn_8007E154();
    fn_8007E374(lbl_804CC0A8->m20, 0, (u16)(fl | 1));
    fn_8007E164();
    t = dv(v);
    o = rm(v, t);
    if (t > 0) {
        digit(x - 0x24, y - 0x22, t, al, z, s);
        digit(x - 2, y - 0x22, o, al, z, s);
    } else {
        digit(x - 0x12, y - 0x22, o, al, z, s);
    }
}

void fn_8027FD08(f32 z, f32 s, int v, s16 x, s16 y, int a, u32 fl) {
/*P*/
    s16 o;
    s16 t;
    s16 al;
/*E*/
    al = mix(a, lbl_804CC0A8->m1C);
    if (lbl_804CC0A8->m2 < 0) {
        return;
    }
    fn_8007E154();
    fn_8007E374(lbl_804CC0A8->m20, 0, (u16)(fl | 1));
    fn_8007E164();
    t = dv(v);
    o = rm(v, t);
    if (t > 0) {
        digit(x - 0x24, y - 0x22, t, al, z, s);
        digit(x - 2, y - 0x22, o, al, z, s);
    } else {
        digit(x - 0x12, y - 0x22, o, al, z, s);
    }
}

}
