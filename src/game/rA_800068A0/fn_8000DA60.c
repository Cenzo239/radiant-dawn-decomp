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

void fn_8000DA60(GModelH* m, GNode* n, KeyX* k, GQuat* out, f32 t) {
    GQuat q;
    Mtx r;
    u32 fl = (u32)m->nodes;
    if (fl & 1) {
        fn_8001D748(r, n->mode, k->x, k->y, k->z);
        fn_803135A8(&q, r);
    } else if (fl & 2) {
        q.x = k->q.x;
        q.y = k->q.y;
        q.z = k->q.z;
        q.w = k->q.w;
    }
    fn_80313774(out, &q, out, t);
}

extern int fn_8001E548(const char*, const char*);

#pragma use_lmw_stmw on
void fn_8000E9DC(GModelH* m) {
    int off;
    int i;
    GNode* n;
    if (m->nodes != 0) {
        m->nodes = (GNode*)((u32)m->nodes + (u32)m);
    }
    if (m->strings != 0) {
        m->strings = m->strings + (u32)m;
    }
    for (i = 0, off = 0; i < m->count; off += 0xF4, i++) {
        n = (GNode*)((u8*)m->nodes + off);
        if ((s32)n->parent == -1) {
            n->parent = 0;
        } else {
            n->parent = (GNode*)((u8*)m->nodes + (s32)n->parent * 0xF4);
        }
        if ((s32)n->sibling == -1) {
            n->sibling = 0;
        } else {
            n->sibling = (GNode*)((u8*)m->nodes + (s32)n->sibling * 0xF4);
        }
        if ((s32)n->child == -1) {
            n->child = 0;
        } else {
            n->child = (GNode*)((u8*)m->nodes + (s32)n->child * 0xF4);
        }
        if (n->name != 0) {
            n->name = n->name + m->strings;
        }
        n->idx = i;
        if (n->name != 0 && fn_8001E548(n->name, 0) != 0) {
            n->flags |= 0x80000000;
        }
        if (n->flags & 0x40) {
            n->flags |= 0x10;
        }
        if (n->flags & 0xC00000) {
            m->flags |= 0x20000000;
        }
        if (n->flags & 0x10000) {
            m->flags |= 0x40000000;
        }
        if (n->flags & 0x20000) {
            m->flags |= 0x80000000;
        }
    }
}
#pragma use_lmw_stmw off

extern void fn_8001E638(const Mtx, Mtx);
extern int fn_80312494(const Mtx, Mtx);
extern void fn_80312DB4(const Mtx, const Vec*, Vec*);
extern void fn_8001E694(const Mtx, Mtx);
extern void fn_8001E6D0(const Mtx, Mtx);
extern void fn_80312378(const Mtx, const Mtx, Mtx);
extern void fn_80312344(const Mtx, Mtx);

void fn_8000EC30(GNode* n, Mtx* buf, Mtx* out) {
    Mtx a;
    Mtx b;
    Mtx c;
    if (!(n->flags & 0x10000000)) {
        if (n->parent != 0) {
            if (n->flags & 0x2000) {
                fn_8001E638(buf[n->parent->idx], a);
                if (fn_80312494(a, a) != 0) {
                    Vec v = {1.0f, 1.0f, 1.0f};
                    fn_80312DB4(a, &v, &v);
                    fn_8001E694(buf[n->idx], b);
                    fn_8001E6D0(buf[n->idx], c);
                    fn_80312378(a, c, c);
                    fn_80312378(b, c, buf[n->idx]);
                }
            }
            fn_80312378(buf[n->parent->idx], buf[n->idx], buf[n->idx]);
        }
        if (out != 0) {
            if (n->flags & 2) {
                fn_80312378(buf[n->idx], n->mtx, out[n->idx]);
            } else {
                fn_80312344(buf[n->idx], out[n->idx]);
            }
        }
    }
    if (n->child != 0) {
        fn_8000EC30(n->child, buf, out);
    }
    if (n->sibling != 0) {
        fn_8000EC30(n->sibling, buf, out);
    }
}

#pragma push
#pragma inline_depth(1)
void fn_8000EDEC(GNode* n, Mtx* buf) {
    Mtx m;
    if (n->flags & 0x10000000) {
        return;
    }
    if (n->child != 0) {
        fn_8000EDEC(n->child, buf);
    }
    if (n->sibling != 0) {
        fn_8000EDEC(n->sibling, buf);
    }
    if (n->parent != 0) {
        if (fn_80312494(buf[n->parent->idx], m) != 0) {
            fn_80312378(m, buf[n->idx], buf[n->idx]);
        }
    }
}
#pragma pop

extern void fn_8031292C(Mtx, f32, f32, f32);

/* Hierarchy scale: recursive; d counts depth, siblings are visited only below
 * the root. fn_8000F1D4 carries the same walk inlined three levels deep. */
#pragma push
#pragma inline_depth(2)
#pragma use_lmw_stmw on
void fn_8000EF88(GNode* n, Mtx* buf, const Mtx m, int d) {
    { Mtx* p = &buf[n->idx]; fn_80312378(m, *p, *p); }
    if (n->child != 0) {
        fn_8000EF88(n->child, buf, m, d + 1);
    }
    if (n->sibling != 0 && d != 0) {
        fn_8000EF88(n->sibling, buf, m, d);
    }
}
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
void fn_8000F1D4(GNode* n, Mtx* buf) {
    Mtx m;
    GNode* c;
    GNode* g;
    GNode* h;
    fn_8031292C(m, 0.0f, 0.0f, 0.0f);
    fn_80312378(m, buf[n->idx], buf[n->idx]);
    c = n->child;
    if (c != 0) {
        fn_80312378(m, buf[c->idx], buf[c->idx]);
        g = c->child;
        if (g != 0) {
            lv2(g, buf, m, 3, 2);
        }
        h = c->sibling;
        if (h != 0) {
            lv2(h, buf, m, 2, 1);
        }
    }
}

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
