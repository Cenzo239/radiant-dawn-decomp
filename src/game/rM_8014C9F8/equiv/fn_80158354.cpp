/* Round 18, functionally equal (check_regs.py: regs): fn_80158354. The order of the temporaries in the two-strike branch came from a search. Expected damage of one attack between two battle units:
 * dmg = atk(+0x448) - def(+0x44A); hit% at +0x458 and crit% at +0x452 as 0..1 values, optionally reshaped
 * with pow() when adj is set. With map flag 0x100 the attack is treated as two strikes (all hit/crit
 * combinations weighted), otherwise as one. Returns 0 when dmg <= 0. Names are guesses. Self-contained. */
#include "game/rM_8014C9F8/types.h"
extern "C" {
extern void* fn_80030CBC(void*);
extern u32* fn_801116B8(void*);
extern double fn_80295AA4(double, double); /* pow */

static inline f32 Clamp01(f32 x) {
    if (x > 1.0f) {
        x = 1.0f;
    }
    if (x < 0.0f) {
        x = 0.0f;
    }
    return x;
}

#define CLAMP01(x) \
    if (x > 1.0f) { \
        x = 1.0f; \
    } \
    if (x < 0.0f) { \
        x = 0.0f; \
    }

static inline f32 Powf(f32 x, f32 y) {
    return fn_80295AA4(x, y);
}

int fn_80158354(u8* at, u8* d, int adj, int alt) {
    BOOL two = (*(u64*)fn_801116B8(fn_80030CBC(at)) & 0x100) != 0;
    f32 dmg = *(s16*)(at + 0x448) - *(s16*)(d + 0x44A);
    f32 hit;
    f32 crit;
    f32 r;
    if (dmg <= 0.0f) {
        return 0;
    }
    hit = 0.01f * *(s16*)(at + 0x458);
    if (adj) {
        CLAMP01(hit);
        if (alt) {
            hit = Powf(hit, 1.5f);
        } else {
            hit = fn_80295AA4(hit, 1.5);
        }
    }
    CLAMP01(hit);
    crit = 0.01f * *(s16*)(at + 0x452);
    if (adj) {
        CLAMP01(crit);
        if (alt) {
            crit = fn_80295AA4(crit, 0.5);
        } else {
            crit = fn_80295AA4(crit, 2.0);
        }
    }
    CLAMP01(crit);
    if (two) {
        f32 h2 = hit * hit;
        f32 omh = 1.0f - hit;
        f32 omc = 1.0f - crit;
        f32 omc2 = omc * omc;
        f32 c2 = crit * crit;
        f32 a = 1.0f - c2;
        f32 p8 = (1.0 - hit) * (2.0 * c2 * hit);
        f32 m = a - omc2;
        f32 omh2 = omh * omh;
        f32 p7 = c2 * h2;
        f32 p6 = m * hit;
        f32 p5 = c2 * omh2;
        f32 p9 = m * omh;
        CLAMP01(p7);
        CLAMP01(p8);
        CLAMP01(p5);
        CLAMP01(p6);
        CLAMP01(p9);
        r = p7 * (3.0f * dmg + 3.0f * dmg) + p8 * (3.0f * dmg + dmg) + p5 * (dmg + dmg) + 3.0f * dmg * p6 + dmg * p9;
    } else {
        f32 p3 = crit * hit;
        f32 p2 = crit * (1.0f - hit);
        CLAMP01(p3);
        CLAMP01(p2);
        r = 3.0f * dmg * p3 + dmg * p2;
    }
    return r;
}
}
