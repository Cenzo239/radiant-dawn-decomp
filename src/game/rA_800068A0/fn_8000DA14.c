#include "game/rA_800068A0/types.h"

/* Blend channel idx of an animation value array towards src by weight t.
 * Channels 3..5 and 27..30 are not blended. */
void fn_8000DA14(f32 t, s32 idx, f32* dst, f32* src) {
    switch (idx) {
    case 3:
    case 4:
    case 5:
    case 27:
    case 28:
    case 29:
    case 30:
        return;
    }
    dst[idx] = (1.0f - t) * dst[idx] + t * src[idx];
}
