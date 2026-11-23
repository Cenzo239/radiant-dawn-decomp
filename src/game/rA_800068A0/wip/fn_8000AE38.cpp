/* fn_8000AE38 template (also 8000B100, 8000B3C8, 8000B690, 8000B958; only the chunk type and scale differ): 27 words differ, registers only. Expanding searchKey in place with goto (so declarations rank its variables) fixed n r12 and last r30. Left: a rotation of keys/f0/f1, which must be r8/r4/r3; a block search can get f0/f1 right but then keys and i swap (r9/r8). */
/* fn_8000AE38 template (also 8000B100, 8000B3C8, 8000B690, 8000B958; only the chunk type and scale differ): about 28 words differ, registers only. Right shape: s16 locals read from a u16* key array keep the extsh at each use; searchKey is an inline, the rest is flat. Wanted: n r12, keys r8, kind r0, f0 r4, f1 r3, v1 r31, last r30. */
#include "game/rA_800068A0/types.h"
typedef struct AChunk { u32 type; void* data; struct AChunk* next; } AChunk;
typedef struct AList { AChunk* head; } AList;
typedef struct ASet { u16 count; u16* offs; } ASet;
typedef struct ATrack { u16 n; u16 kind; u16 keys[1]; } ATrack;
typedef struct K { s16 f; s16 v; } K;
extern "C" int fn_8000AE38(AList* an, int id, f32* out, f32 frame) {
    int i;
    int kv2;
    s16 f1;
    int kv;
    ASet* set;
    u16 off;
    AChunk* c;
    int has;
    s32 mid;
    int kind;
    ATrack* t;
    s16 v0;
    s32 hi;
    s32 lo;
    s16 f0;
    int n;
    s16 v1;
    u16* keys;
    s32 last;
    f32 v;

    set = 0;
    if (an != 0) {
        for (c = an->head; c != 0; c = c->next) {
            if (c->type == 8) {
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
    if (n == 0) {
        v = 0.0f;
        goto done;
    }
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
        f1 = keys[(i + 1) * 2];
        v0 = keys[i * 2 + 1];
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
        v = v0;
        goto done;
    }
    switch (kind) {
    case 0:
        v = (f32)v0 + (f32)(v1 - v0) * (frame - (f32)f0) / (f32)(f1 - f0);
        break;
    case 1:
        v = v0;
        break;
    default:
        v = 0.0f;
        break;
    }
done:
    *out = 0.0009765625f * v;
    return 1;
}
