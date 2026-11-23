#include "game/rA_800068A0/types.h"
/* Collects the key events between two frames from the type 5 chunk, padding the list with 0xFFFF. Returns the event count. */
typedef struct AChunk { u32 type; void* data; struct AChunk* next; } AChunk;
typedef struct AList { AChunk* head; } AList;
typedef struct ASet { u16 count; u16* offs; } ASet;
typedef struct GKey { u16 id; s16 val; } GKey;
typedef struct AEv { u16 frame; u8 x2; u8 count; GKey keys[1]; } AEv;
static inline ASet* findSet(AList* an) {
    AChunk* c;
    if (an != 0) {
        for (c = an->head; c != 0; c = c->next) {
            if (c->type == 5) {
                return (ASet*)c->data;
            }
        }
    }
    return 0;
}
extern "C" int fn_8000A22C(f32 a, f32 b, AList* an, GKey* out) {
    GKey* o;
    int ofs;
    int i;
    int j;
    AEv* e;
    GKey* k;
    int n;
    ASet* set;
    int i2;
    set = findSet(an);
    n = 0;
    if (set != 0) {
        if (a > b) {
            f32 t = a;
            a = b;
            b = t;
        }
        for (i = 0, ofs = 0; i < set->count; ofs += 2, i++) {
            if (*(u16*)((u8*)set->offs + ofs) == 0xFFFF) {
                e = 0;
            } else {
                e = (AEv*)((u8*)set + *(u16*)((u8*)set->offs + ofs));
            }
            if ((f32)e->frame > a && (f32)e->frame <= b) {
                k = e->keys;
                for (j = 0; j < e->count; j++, k++) {
                    if (n >= 4) break;
                    o = &out[n++];
                    o->id = k->id;
                    o->val = k->val;
                }
            }
        }
    }
    for (i2 = n; i2 < 4; i2++) {
        out[i2].id = 0xFFFF;
    }
    return n;
}
