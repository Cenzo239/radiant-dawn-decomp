/* fn_801478F4 (round 22, agent r22b): complete draft, class `other` (0x178 bytes,
 * original 0x204).
 * Packs the 8-bit shadow image `src` (width lbl_804CB872, height lbl_804CB874) into the
 * I4 texture lbl_80413F00[lbl_804CB871], one 8x8 tile at a time (one u32 of eight
 * nibbles per tile row, top nibble of each byte), then flushes the 0x2000-byte texture.
 * With src == NULL the texture is cleared instead (fn_8017F464(tex, 0, 0x2000)).
 *
 * What differs: only code shape. The original unrolls the 8-row loop twice (ctr 4, the
 * row counter stepped twice per pass, stores at d+0/d+4 then d += 8) and keeps the nibble
 * chain strictly sequential (shift, load, extract, or per byte). Here the row loop stays
 * a ctr-8 loop with the 8 bytes loaded ahead. Neither `#pragma opt_unroll_loops on` /
 * `opt_unroll_count 2` nor hand-written 2x bodies (wip/near4.cpp, which spill) reproduce
 * it. Same loads, same values stored, same order of stores to the texture; v carries
 * over between rows exactly as in the original (its old nibbles are shifted out).
 */
/* Packs an 8-bit shadow image into an I4 texture, one 8x8 tile at a time. */
#include "game/rL_80133EB4/types.h"
extern "C" {
extern u8 lbl_804CB871;
extern s16 lbl_804CB872;
extern s16 lbl_804CB874;
extern u8* lbl_80413F00[];
extern void fn_8017F464(void*, int, int);
extern void DCFlushRange(void*, u32);

static inline u32 Pack(u32 v, u8* q) { int k; for (k = 0; k < 8; k++) { v <<= 4; v |= (q[k] >> 4) & 0xF; } return v; }
void fn_801478F4(u8* src) {
    if (src == 0) {
        fn_8017F464(lbl_80413F00[lbl_804CB871], 0, 0x2000);
    } else {
        int w = lbl_804CB872;
        int h = lbl_804CB874;
        u32* d = (u32*)lbl_80413F00[lbl_804CB871];
        u32 v = 0;
        for (int y = 0; y < h; y += 8) {
            for (int x = 0; x < w; x += 8) {
                u8* s = src + x;
                for (int r = 0; r < 8; r++) {
                    u8* q = s + w * (y + r);
                    v = Pack(v, q);
                    *d = v;
                    d++;
                }
            }
        }
    }
    DCFlushRange(lbl_80413F00[lbl_804CB871], 0x2000);
}
}
