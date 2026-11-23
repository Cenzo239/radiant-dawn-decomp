#include "game/rA_800068A0/types.h"

/* GAnim.c */

typedef struct GAnimKey {
    u16 frame;
    u16 x2;
} GAnimKey;

static inline s32 GAnim_SearchKeyInline(GAnimKey* keys, s32 frame, s32 n) {
    s32 lo;
    s32 hi;
    s32 mid;
    if (n == 0) {
        return -1;
    }
    hi = n - 1;
    lo = 0;
    while (lo <= hi) {
        mid = lo + ((hi - lo) >> 1);
        if (keys[mid].frame < frame) {
            lo = mid + 1;
        } else if (keys[mid].frame > frame) {
            hi = mid - 1;
        } else {
            return mid;
        }
    }
    if (hi < 0) {
        return -1;
    }
    if (lo > n - 1) {
        return n - 1;
    }
    if ((s16)keys[lo].frame <= frame) {
        return lo;
    }
    return lo - 1;
}

/* GAnim_SearchKey: binary search for frame; returns the index of the last key
 * at or before frame, -1 if none. The body is an inline (returns become
 * branches to a shared result register). */
s32 fn_8000A7A0(GAnimKey* keys, s32 frame, s32 n) {
    return GAnim_SearchKeyInline(keys, frame, n);
}
