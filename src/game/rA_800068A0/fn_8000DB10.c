/* Round 18, exact: fn_8000DB10 (hide nodes whose visibility key is 0). Self-contained: fn_8000DA60.c with its exported bodies removed plus the function. Fix: read the key header through a walking u16 pointer (n = *keys++; id = *keys++). */
#include "game/rA_800068A0/types.h"

/* GModel: node binding, relocation and hierarchy walks. */

typedef struct Vec { f32 x, y, z; } Vec;
typedef f32 Mtx[3][4];
typedef struct GQuat { f32 x, y, z, w; } GQuat;

typedef struct GNode {
    struct GNode* parent;   /* 0x00 */
    struct GNode* sibling;  /* 0x04 */
    struct GNode* child;    /* 0x08 */
    u32 flags;              /* 0x0C */
    Mtx mtx;                /* 0x10 */
    u8 x40[0xEC - 0x40];
    u32 idx : 12;           /* 0xEC */
    u32 xEC : 16;
    u32 mode : 4;
    char* name;             /* 0xF0 */
} GNode;

typedef struct GModelH {
    u32 flags;
    u32 strings;
    s32 count;
    GNode* nodes;
} GModelH;

typedef struct KeyX {
    u8 pad[0xC];
    f32 x, y, z;
    u8 pad18[0x54];
    GQuat q;       /* 0x6C */
} KeyX;

extern void fn_8001D748(Mtx, int, f32, f32, f32);
extern void fn_803135A8(GQuat*, const Mtx);
extern void fn_80313774(const GQuat*, const GQuat*, GQuat*, f32);

void fn_8000DA60(GModelH* m, GNode* n, KeyX* k, GQuat* out, f32 t);

extern int fn_8001E548(const char*, const char*);

#pragma use_lmw_stmw on
void fn_8000E9DC(GModelH* m);
#pragma use_lmw_stmw off

extern void fn_8001E638(const Mtx, Mtx);
extern int fn_80312494(const Mtx, Mtx);
extern void fn_80312DB4(const Mtx, const Vec*, Vec*);
extern void fn_8001E694(const Mtx, Mtx);
extern void fn_8001E6D0(const Mtx, Mtx);
extern void fn_80312378(const Mtx, const Mtx, Mtx);
extern void fn_80312344(const Mtx, Mtx);

void fn_8000EC30(GNode* n, Mtx* buf, Mtx* out);

#pragma push
#pragma inline_depth(1)
void fn_8000EDEC(GNode* n, Mtx* buf);
#pragma pop

extern void fn_8031292C(Mtx, f32, f32, f32);

/* Hierarchy scale: recursive; d counts depth, siblings are visited only below
 * the root. fn_8000F1D4 carries the same walk inlined three levels deep. */
#pragma push
#pragma inline_depth(2)
#pragma use_lmw_stmw on
void fn_8000EF88(GNode* n, Mtx* buf, const Mtx m, int d);
#pragma use_lmw_stmw off
#pragma pop


#define CALL fn_8000EF88
static inline void lv2(GNode* g, Mtx* buf, const Mtx m, int d0, int d1) {
    fn_80312378(m, buf[g->idx], buf[g->idx]);
    if (g->child != 0) {
        CALL(g->child, buf, m, d0);
    }
    if (g->sibling != 0) {
        CALL(g->sibling, buf, m, d1);
    }
}
void fn_8000F1D4(GNode* n, Mtx* buf);

/* GAnim chunk list: {type, data, next}. */
typedef struct AChunk { s32 type; void* data; struct AChunk* next; } AChunk;
typedef struct AList { AChunk* head; } AList;
typedef struct AFrame { u16 frame; s16 val; } AFrame;
typedef struct ASet { u16 count; u16* offs; } ASet;

static inline s32 searchKey(AFrame* keys, s32 frame, s32 n) {
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
    if (keys[lo].frame <= frame) {
        return lo;
    }
    return lo - 1;
}

static inline void* findChunk(AList* l, s32 type) {
    AChunk* c;
    if (l != 0) {
        for (c = l->head; c != 0; c = c->next) {
            if (c->type == type) {
                return c->data;
            }
        }
    }
    return 0;
}

extern GNode* fn_8000F3D4(void*, u16);

void fn_8000DB10(void* model, AList* a, Mtx* buf, f32 frame);

/* fn_8000DB10: near miss, 7 of 127 words differ. Depends on types and helpers from ../fn_8000DA60.c; goes there in address order. */
void fn_8000DB10(void* model, AList* a, Mtx* buf, f32 frame) {
    ASet* set = findChunk(a, 0);
    int i;
    if (set != 0) {
        for (i = 0; i < set->count; i++) {
            u16 off = set->offs[i];
            u16* keys = off == 0xFFFF ? 0 : (u16*)((u8*)set + off);
            u16 n = *keys++;
            u16 id = *keys++;
            if (n != 0) {
                s32 k = searchKey((AFrame*)keys, frame, n);
                s16 v = k < 0 ? ((AFrame*)keys)[0].val : ((AFrame*)keys)[k].val;
                if (v == 0) {
                    GNode* node = fn_8000F3D4(model, id);
                    if (!(node->flags & 0x10000000)) {
                        Mtx m;
                        fn_8031292C(m, 0.0f, 0.0f, 0.0f);
                        fn_80312378(buf[id], m, buf[id]);
                        node->flags |= 0x4000000;
                    }
                }
            }
        }
    }
}
