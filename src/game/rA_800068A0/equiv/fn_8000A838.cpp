/* Round 18, functionally equal (check_regs.py: regs): fn_8000A838, the colour track evaluator.
 * Same chunk lookup and key search as the fn_8000AB6C family (equiv/fn_8000AB6C.cpp), but the chunk type is a
 * parameter and each key value is a packed RGB565 colour, interpolated per channel into out[0..2]. Self-contained. */
#include "game/rA_800068A0/types.h"
typedef struct AChunk { u32 type; void* data; struct AChunk* next; } AChunk;
typedef struct AList { AChunk* head; } AList;
typedef struct ASet { u16 count; u16* offs; } ASet;
typedef struct ATrack { u16 n; u16 kind; u16 keys[1]; } ATrack;
typedef struct K { s16 f; s16 v; } K;
extern "C" int fn_8000A838(AList* an, int id, u32 type, u8* out, f32 frame) {
    AChunk* c;
    s16 f0;
    int kv;
    ATrack* t;
    ASet* set;
    int has;
    s32 mid;
    u16 off;
    int i;
    s32 hi;
    int kv2;
    s32 lo;
    s16 v0;
    int n;
    s16 v1;
    s32 last;
    int kind;
    f32 tt;
    u32 r0;
    u32 g0;
    u32 b0;
    u32 r1;
    u32 g1;
    u32 b1;
    s16 f1;
    u16* keys;

    set = 0;
    if (an != 0) {
        for (c = an->head; c != 0; c = c->next) {
            if (c->type == type) {
                set = (ASet*)c->data;
                goto found;
            }
        }
    }
    set = 0;
found:
    if (set == 0) return 0;
    off = set->offs[id];
    if (off == 0xFFFF) {
        t = 0;
    } else {
        t = (ATrack*)((u8*)set + off);
    }
    if (t == 0) return 0;
    n = t->n;
    keys = t->keys;
    kind = t->kind;
    f0 = -1;
    f1 = -1;
    v1 = 0;
    if (n == 0) goto done;
    if (n == 0) {
        i = -1;
        goto sdone;
    }
    last = n - 1;
    hi = last;
    lo = 0;
    while (lo <= hi) {
        mid = lo + ((hi - lo) >> 1);
        kv = keys[mid * 2];
        if (kv < (s32)frame) {
            lo = mid + 1;
        } else if (kv > (s32)frame) {
            hi = mid - 1;
        } else {
            i = mid;
            goto sdone;
        }
    }
    if (hi < 0) {
        i = -1;
        goto sdone;
    }
    if (lo > last) {
        i = last;
        goto sdone;
    }
    kv2 = keys[lo * 2];
    i = lo - 1;
    if (kv2 <= (s32)frame) {
        i = lo;
    }
sdone:
    if (i < 0) {
        v0 = keys[1];
        has = 0;
    } else if (i < n - 1) {
        f0 = keys[i * 2];
        v0 = keys[i * 2 + 1];
        f1 = keys[(i + 1) * 2];
        v1 = keys[(i + 1) * 2 + 1];
        goto yes;
    } else {
        has = 0;
        v0 = keys[i * 2 + 1];
        goto no;
yes:
        has = 1;
no:;
    }
    if (!has) {
        out[0] = (v0 >> 8) & 0xF8;
        out[1] = (v0 >> 3) & 0xFC;
        out[2] = (v0 << 3) & 0xF8;
        goto done;
    }
    tt = 0.0f;
    if (f1 != f0) {
        tt = (frame - (f32)f0) / (f32)(f1 - f0);
    }
    r0 = (v0 >> 8) & 0xF8;
    g0 = (v0 >> 3) & 0xFC;
    b0 = (v0 << 3) & 0xF8;
    r1 = (v1 >> 8) & 0xF8;
    g1 = (v1 >> 3) & 0xFC;
    b1 = (v1 << 3) & 0xF8;
    switch (kind) {
    case 0:
        out[0] = tt * (f32)(int)(r1 - r0) + (f32)r0;
        out[1] = tt * (f32)(int)(g1 - g0) + (f32)g0;
        out[2] = tt * (f32)(int)(b1 - b0) + (f32)b0;
        break;
    case 1:
        out[0] = r0;
        out[1] = g0;
        out[2] = b0;
        break;
    }
done:
    return 1;
}
