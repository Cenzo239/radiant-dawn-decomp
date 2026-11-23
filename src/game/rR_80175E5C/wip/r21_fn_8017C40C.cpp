/* fn_8017C40C (0x974): complete draft, round 21, class `other`: 597 of 605 instructions, same frame (0x320),
 * same saved registers (r23..r31, f17..f31), same calls, constants and references (check_func.py -v shows no
 * wrong constant; the "wave" literal is pool offset 0xC3 of strpool.h).
 * What differs from the original:
 *   - the 8 missing instructions are dead `srawi rX,y,2` (one in the outer pixel loop, seven in the unrolled
 *     left/right edge loop): the original computes y >> 2, never uses it and forms (y >> 2) * 0x80 straight from
 *     y with extlwi. Same open puzzle as fn_8017D428 and rL fn_80143908; about 90 spellings of the index tried
 *     this round on both functions (see NOTES Round 21). No effect on behaviour;
 *   - the texel index adds the row term to (x >> 2) * 16 before (x & 3) (original: column term first);
 *   - the six prm loads after fn_8000DD0C and the fall/phase set-up at the top of the inner loop are scheduled
 *     in another order, and the edge loops allocate their temporaries differently.
 * Port notes: prm is the 0xB0-byte record fn_8000DD0C fills (only six floats used); `ys`/`xs` are the texel
 * centres in screen units (448/32 and 608/32 per step, integer division as in the original).
 * Screen "wave" (heat-haze) filter: builds the 32x32 two-channel displacement texture lbl_804CB8CC (4x4-block
 * layout, 2 bytes per texel, 0x80 = no displacement) from the model joint "wave" (names guessed):
 *   prm[0], prm[1]  amplitude in s and t (x 127)
 *   prm[2]          radius of the effect around the joint's screen position (x 256); 0 = whole screen
 *   prm[3], prm[4]  phase in degrees for the rows / columns (x 8)
 *   prm[5]          frequency in degrees per texel (x 8 / 32)
 * Each texel gets 128 + fall * amp * sin(phase + n * freq), with fall = 1 or (rad - dist) / rad (texels outside
 * the radius stay 0x80). The sine comes from the 0x4000-entry s16 table lbl_803B7878 (2607.5945 = 0x4000 / 2pi,
 * 1/16384 scale). The outer ring of texels is then forced to 0x80 (t channel on the left/right columns, s
 * channel on the top/bottom rows). With both amplitudes 0 the texture is just filled with 0x80.
 */
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;
typedef float f32;
#include "game/rR_80175E5C/strpool.h"

extern "C" {
struct WVec { f32 x, y, z; };
extern s8 lbl_804CB8CA;
extern u8* lbl_804CB8CC;
extern s16 lbl_803B7878[0x4000];
int fn_80007630(void*, const char*);
void* fn_800078E4(void*, int);
void fn_8000DD0C(void*, void*, f32*, f32);
WVec fn_800076E8(void*, int);
void fn_80011B90(int, WVec*, WVec*);
void fn_80313484(WVec*, WVec*, WVec*);
f32 fn_80313508(WVec*);
u32 fn_8028C1A0(f32);
void fn_8017F464(void*, u32, int);
void DCFlushRange(void*, int);
void fn_8017C40C(void* mdl);
}
/* texel (x, y) of a 32-wide 4x4-block texture */
#define IX(x, y) (((y) >> 2) * 0x80 + ((y) & 3) * 4 + (((x) >> 2) * 0x10 + ((x) & 3)))
static inline f32 Sin16(f32 a) {
    return 0.000061035156f * lbl_803B7878[fn_8028C1A0(2607.5945f * a) & 0x3FFF];
}
extern "C" void fn_8017C40C(void* mdl) {
    f32 prm[0x2C]; /* fn_8000DD0C fills a 0xB0-byte record; only the first six floats are used here */
    f32 xs[0x20];
    f32 ys[0x20];
    int i;
    int j;
    int n = fn_80007630(mdl, "wave");
    if (n >= 0 && lbl_804CB8CA != 0) {
        f32 rad, inv, ax, ay, phx, phy, frq;
        fn_8000DD0C(mdl, fn_800078E4(mdl, n), prm, -1.0f);
        rad = 256.0f * prm[2];
        ax = 127.0f * prm[0];
        ay = 127.0f * prm[1];
        inv = 0.0f == rad ? 0.0f : 1.0f / rad;
        phx = 8.0f * (0.017453292f * prm[3]);
        phy = 8.0f * (0.017453292f * prm[4]);
        frq = 8.0f * (0.017453292f * prm[5]) * 0.03125f;
        if (0.0f == ax && 0.0f == ay) {
            fn_8017F464(lbl_804CB8CC, 0x80808080, 0x800);
        } else {
            WVec c = fn_800076E8(mdl, n);
            fn_80011B90(0, &c, &c);
            c.z = 0.0f;
            for (i = 0; i < 0x20; i++) {
                ys[i] = i * 448 / 32;
            }
            for (i = 0; i < 0x20; i++) {
                xs[i] = i * 608 / 32;
            }
            for (j = 0; j < 0x20; j++) {
                f32 aj = j * frq + phx;
                for (i = 0; i < 0x20; i++) {
                    f32 ai = i * frq + phy;
                    int o = IX(i, j) * 2;
                    f32 fall = 1.0f;
                    if (rad >= 0.0f) {
                        WVec t = {0.0f, 0.0f, 0.0f};
                        t.x = xs[i];
                        t.y = ys[j];
                        fn_80313484(&c, &t, &t);
                        fall = inv * (rad - fn_80313508(&t));
                    }
                    if (fall < 0.0f) {
                        lbl_804CB8CC[o] = 0x80;
                        lbl_804CB8CC[o + 1] = 0x80;
                    } else {
                        f32 va = fall * (ax * Sin16(aj));
                        f32 vb = fall * (ay * Sin16(ai));
                        lbl_804CB8CC[o] = (int)(128.0f + va);
                        lbl_804CB8CC[o + 1] = (int)(128.0f + vb);
                    }
                }
            }
            for (j = 0; j < 0x20; j++) {
                lbl_804CB8CC[IX(0, j) * 2 + 1] = 0x80;
                lbl_804CB8CC[IX(0x1F, j) * 2 + 1] = 0x80;
            }
            for (i = 0; i < 0x20; i++) {
                lbl_804CB8CC[IX(i, 0) * 2] = 0x80;
                lbl_804CB8CC[IX(i, 0x1F) * 2] = 0x80;
            }
        }
        DCFlushRange(lbl_804CB8CC, 0x800);
    }
}
