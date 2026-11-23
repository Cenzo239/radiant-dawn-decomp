/* Round 18, functionally equal (check_regs.py: regs): the animation track evaluators
 * fn_8000AB6C (chunk type 6, u8 result), fn_8000AE38 (8), fn_8000B100 (9), fn_8000B3C8 (10, scale 1/16),
 * fn_8000B690 (11) and fn_8000B958 (12). All six share one body: find the chunk of the given type,
 * binary-search the key frames of track id, interpolate (kind 0 linear, kind 1 step) and store the scaled value.
 * Written as one macro; the declaration order came from a search (tools-style permutation) and the gotos are
 * the expanded key search inline. Self-contained. */
#include "game/rA_800068A0/types.h"
typedef struct AChunk { u32 type; void* data; struct AChunk* next; } AChunk;
typedef struct AList { AChunk* head; } AList;
typedef struct ASet { u16 count; u16* offs; } ASet;
typedef struct ATrack { u16 n; u16 kind; u16 keys[1]; } ATrack;
typedef struct K { s16 f; s16 v; } K;
#define ANIM_TRACK_FN(NAME, TYPE, OUT_T, STORE) \
extern "C" int NAME(AList* an, int id, OUT_T* out, f32 frame) { \
    AChunk* c; \
    s16 f0; \
    int kv; \
    ATrack* t; \
    ASet* set; \
    int has; \
    s32 mid; \
    u16 off; \
    int i; \
    s32 hi; \
    int kv2; \
    s32 lo; \
    s16 v0; \
    int n; \
    s16 v1; \
    s32 last; \
    int kind; \
    f32 v; \
    s16 f1; \
    u16* keys; \
 \
    set = 0; \
    if (an != 0) { \
        for (c = an->head; c != 0; c = c->next) { \
            if (c->type == TYPE) { \
                set = (ASet*)c->data; \
                goto found; \
            } \
        } \
    } \
    set = 0; \
found: \
    if (set == 0) return 0; \
    off = set->offs[id]; \
    if (off == 0xFFFF) { \
        t = 0; \
    } else { \
        t = (ATrack*)((u8*)set + off); \
    } \
    if (t == 0) return 0; \
    n = t->n; \
    keys = t->keys; \
    kind = t->kind; \
    f0 = -1; \
    f1 = -1; \
    v1 = 0; \
    if (n == 0) { \
        v = 0.0f; \
        goto done; \
    } \
    if (n == 0) { \
        i = -1; \
        goto sdone; \
    } \
    last = n - 1; \
    hi = last; \
    lo = 0; \
    while (lo <= hi) { \
        mid = lo + ((hi - lo) >> 1); \
        kv = keys[mid * 2]; \
        if (kv < (s32)frame) { \
            lo = mid + 1; \
        } else if (kv > (s32)frame) { \
            hi = mid - 1; \
        } else { \
            i = mid; \
            goto sdone; \
        } \
    } \
    if (hi < 0) { \
        i = -1; \
        goto sdone; \
    } \
    if (lo > last) { \
        i = last; \
        goto sdone; \
    } \
    kv2 = keys[lo * 2]; \
    i = lo - 1; \
    if (kv2 <= (s32)frame) { \
        i = lo; \
    } \
sdone: \
    if (i < 0) { \
        v0 = keys[1]; \
        has = 0; \
    } else if (i < n - 1) { \
        f0 = keys[i * 2]; \
        v0 = keys[i * 2 + 1]; \
        f1 = keys[(i + 1) * 2]; \
        v1 = keys[(i + 1) * 2 + 1]; \
        goto yes; \
    } else { \
        has = 0; \
        v0 = keys[i * 2 + 1]; \
        goto no; \
yes: \
        has = 1; \
no:; \
    } \
    if (!has) { \
        v = v0; \
        goto done; \
    } \
    switch (kind) { \
    case 0: \
        v = (f32)v0 + (f32)(v1 - v0) * (frame - (f32)f0) / (f32)(f1 - f0); \
        break; \
    case 1: \
        v = v0; \
        break; \
    default: \
        v = 0.0f; \
        break; \
    } \
done: \
    STORE; \
    return 1; \
}

ANIM_TRACK_FN(fn_8000AB6C, 6, u8, *out = v)
ANIM_TRACK_FN(fn_8000AE38, 8, f32, *out = 0.0009765625f * v)
ANIM_TRACK_FN(fn_8000B100, 9, f32, *out = 0.0009765625f * v)
ANIM_TRACK_FN(fn_8000B3C8, 10, f32, *out = 0.0625f * v)
ANIM_TRACK_FN(fn_8000B690, 11, f32, *out = 0.0009765625f * v)
ANIM_TRACK_FN(fn_8000B958, 12, f32, *out = 0.0009765625f * v)
