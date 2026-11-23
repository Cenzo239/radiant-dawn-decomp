#include "game/rA_800068A0/types.h"

/* GAnim.c: animation resource with a linked list of typed chunks.
 * Chunk type 5 is the key-set ("flag") table used by GActor key queries. */

typedef struct GKey {
    u16 id;
    s16 val;
} GKey;

typedef struct GKeySet {
    u16 frame;          /* 0x00 */
    u8 x2;
    u8 count;           /* 0x03 */
    GKey keys[1];       /* 0x04 */
} GKeySet;

typedef struct GKeyTable {
    u16 count;
    u16 x2;
    u16* offsets;       /* 0x04: byte offsets from the table, 0xFFFF = none */
} GKeyTable;

typedef struct GChunk {
    u32 type;
    void* data;
    struct GChunk* next;
} GChunk;

typedef struct GAnim {
    GChunk* chunks;
} GAnim;

extern char lbl_80360B08[]; /* "GAnim.c" + messages */
extern void fn_8001E008(const char* file, int line, const char* msg);

static inline void* GAnim_FindChunk(GAnim* an, u32 type) {
    GChunk* c;
    if (an != NULL) {
        for (c = an->chunks; c != NULL; c = c->next) {
            if (c->type == type) {
                return c->data;
            }
        }
    }
    return NULL;
}

static inline GKeySet* GKeyTable_Get(GKeyTable* t, s32 i) {
    if (t->offsets[i] == 0xFFFF) {
        return NULL;
    }
    return (GKeySet*)((u8*)t + t->offsets[i]);
}

/* GAnim_FindKeySetByFrame */
GKeySet* fn_80009CD0(GAnim* an, s32 frame) {
    GKeyTable* t = (GKeyTable*)GAnim_FindChunk(an, 5);
    s32 i;
    if (t == NULL) {
        return NULL;
    }
    for (i = 0; i < t->count; i++) {
        GKeySet* ks = GKeyTable_Get(t, i);
        if (ks->frame == frame) {
            return ks;
        }
    }
    return NULL;
}

/* GAnim_GetKeySetsWithKey */
s32 fn_80009D60(GAnim* an, u16 id, GKeySet** out) {
    GKeyTable* t = (GKeyTable*)GAnim_FindChunk(an, 5);
    s32 n;
    s32 i;
    s32 j;
    if (t == NULL) {
        return 0;
    }
    n = 0;
    for (i = 0; i < t->count; i++) {
        GKeySet* ks = GKeyTable_Get(t, i);
        GKey* k = ks->keys;
        for (j = 0; j < ks->count; j++, k++) {
            if (k->id == id) {
                *out++ = ks;
                n++;
                break;
            }
        }
    }
    return n;
}

/* GAnimGetFlagListByAll */
s32 fn_80009E20(GAnim* an, GKeySet** out) {
    GKeyTable* t = (GKeyTable*)GAnim_FindChunk(an, 5);
    s32 i;
    if (t == NULL) {
        return 0;
    }
    if (t->count > 0x40) {
        fn_8001E008(lbl_80360B08, 0x60, lbl_80360B08 + 8);
    }
    for (i = 0; i < t->count; i++) {
        *out++ = GKeyTable_Get(t, i);
    }
    return t->count;
}


/* GAnim_CountKeys */
s32 fn_8000A0A8(GAnim* an, u32 id) {
    GKeyTable* t;
    s32 i;
    s32 j;
    s32 n = 0;
    t = (GKeyTable*)GAnim_FindChunk(an, 5);
    if (t == NULL) {
        return 0;
    }
    for (i = 0; i < t->count; i++) {
        GKeySet* ks = GKeyTable_Get(t, i);
        GKey* k = ks->keys;
        for (j = 0; j < ks->count; j++, k++) {
            if (id == 0xFFFF || k->id == id) {
                n++;
            }
        }
    }
    return n;
}


s32 fn_80009EF8(GAnim* an, s32 limit, u32 id) {
    s32 n;
    s32 best;
    s32 i;
    s32 j;
    GKeySet* ks;
    GKey* k;
    GKeyTable* t;
    t = (GKeyTable*)GAnim_FindChunk(an, 5);
    if (t == NULL) {
        return -1;
    }
    n = t->count;
    best = -1;
    for (i = 0; i < n; i++) {
        if (t->offsets[i] == 0xFFFF) {
            ks = NULL;
        } else {
            ks = (GKeySet*)((u8*)t + t->offsets[i]);
        }
        k = ks->keys;
        for (j = 0; j < ks->count; j++, k++) {
            if (ks->frame < limit && (id == 0xFFFF || k->id == id) &&
                (best < 0 || ks->frame >= best)) {
                best = ks->frame;
            }
        }
    }
    return best;
}

s32 fn_80009FD0(GAnim* an, s32 limit, u32 id) {
    s32 n;
    s32 best;
    s32 i;
    s32 j;
    GKeySet* ks;
    GKey* k;
    GKeyTable* t;
    t = (GKeyTable*)GAnim_FindChunk(an, 5);
    if (t == NULL) {
        return -1;
    }
    n = t->count;
    best = -1;
    for (i = 0; i < n; i++) {
        if (t->offsets[i] == 0xFFFF) {
            ks = NULL;
        } else {
            ks = (GKeySet*)((u8*)t + t->offsets[i]);
        }
        k = ks->keys;
        for (j = 0; j < ks->count; j++, k++) {
            if (ks->frame > limit && (id == 0xFFFF || k->id == id) &&
                (best < 0 || ks->frame <= best)) {
                best = ks->frame;
            }
        }
    }
    return best;
}

s32 fn_8000A168(GAnim* an, u16 id, u16* out) {

    GKeyTable* t;
    s32 i;
    s32 n;
    s32 j;
    GKeySet* ks;
    GKey* k;

    n = 0;
    t = (GKeyTable*)GAnim_FindChunk(an, 5);
    if (t == NULL) {
        return 0;
    }
    for (i = 0; i < t->count; i++) {
        if (t->offsets[i] == 0xFFFF) {
            ks = NULL;
        } else {
            ks = (GKeySet*)((u8*)t + t->offsets[i]);
        }
        k = ks->keys;
        for (j = 0; j < ks->count; j++, k++) {
            if (k->id == id) {
                n++;
                *out = (u16)k->val;
            }
        }
    }
    return n;
}
