#include "game/rA_800068A0/types.h"
/* Applies a light animation (chunk type 2) from an actor to a light set. */
extern "C" {
typedef f32 Mtx[3][4];
typedef struct Vec { f32 x, y, z; } Vec;
typedef struct AChunk { u32 type; void* data; struct AChunk* next; } AChunk;
typedef struct AList { AChunk* head; } AList;
typedef struct ASet { u16 count; u16 node; u16* offs; } ASet;
typedef struct ATrack { u16 n; u8 kind; u8 shift; u16 keys[1]; } ATrack;
typedef struct KK { s16 f; s16 v; } KK;
typedef struct GAct { u8 x0[0xC]; u8 xf[0x58 - 0xC]; f32 frame; } GAct;
typedef struct GLSet { u8 x0[2]; u8 r, g, b; } GLSet;
typedef struct GLt { u8 x0[4]; u8 r, g, b; u8 x7[0x14 - 7]; Vec pos; } GLt;
extern AList* fn_80007F10(GAct* a);
extern GLSet* fn_80010C18(void);
extern GLt* fn_80010DA4(GLSet* s, int type);
extern GLt* fn_80010E38(GLSet* s, int type);
extern void fn_8001D44C(const void* a, void* b);
extern void fn_8001E6D0(const void* a, void* b);
extern void fn_800110F4(GLSet* s, Mtx m);
static inline ASet* findSet(AList* an) {
    AChunk* c;
    if (an != 0) {
        for (c = an->head; c != 0; c = c->next) {
            if (c->type == 2) {
                return (ASet*)c->data;
            }
        }
    }
    return 0;
}
static inline f32 clamp255(f32 x) {
    if (x > 255.0f) return 255.0f;
    return x;
}
int fn_8000C3C4(GAct* a, GLSet* set2) {
/*P*/
    GLt* l;
    KK* keys;
    int mid;
    int i;
    int hi;
    int lo;
    int n;
    int v0;
    int has;
    ASet* set;
    ATrack* t;
    int kv;
    int last;
    u8 shift;
    AList* an;
    int kind;
    int v1;
    int f1;
    int f0;
    int ofs;
    int j;
/*E*/
    f32 frame;
    f32 r1;
    f32 g1;
    f32 b1;
    f32 k1;
    f32 r2;
    f32 g2;
    f32 b2;
    f32 k2;
    f32 v;
    f32 w;
    Mtx m;
    if (a == 0) return 0;
    an = fn_80007F10(a);
    frame = a->frame;
    if (an == 0) return 0;
    set = findSet(an);
    if (set == 0) return 0;
    r1 = 1.0f;
    Vec pos = {0.0f, 0.0f, 0.0f};
    Vec dir = {0.0f, 0.0f, 0.0f};
    g1 = 1.0f;
    b1 = 1.0f;
    k1 = 5.0f;
    r2 = 1.0f;
    g2 = 1.0f;
    b2 = 1.0f;
    k2 = 5.0f;
    j = 0;
    ofs = 0;
    for (; j < set->count; ofs += 2, j++) {
        if (*(u16*)((u8*)set->offs + ofs) == 0xFFFF) {
            t = 0;
        } else {
            t = (ATrack*)((u8*)set + *(u16*)((u8*)set->offs + ofs));
        }
        n = t->n;
        keys = (KK*)t->keys;
        v = 0.0f;
        f0 = -1;
        kind = t->kind;
        shift = t->shift;
        f1 = -1;
        v1 = 0;
        if (n == 0) {
            kind = -1;
        } else {
            if (n == 0) {
                i = -1;
                goto sdone;
            }
            last = n - 1;
            hi = last;
            lo = 0;
            while (lo <= hi) {
                mid = lo + ((hi - lo) >> 1);
                kv = *(u16*)&keys[mid].f;
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
            kv = *(u16*)&keys[lo].f;
            i = lo - 1;
            if (kv <= (s32)frame) {
                i = lo;
            }
        sdone:
            if (i < 0) {
                v0 = keys[0].v;
                has = 0;
            } else if (i < n - 1) {
                KK* p;
                KK* q;
                f0 = (p = &keys[i])->f;
                v0 = p->v;
                f1 = (q = &keys[i + 1])->f;
                v1 = q->v;
                goto yes;
            } else {
                has = 0;
                v0 = keys[i].v;
                goto no;
            yes:
                has = 1;
            no:;
            }
            if (has) {
                w = (f32)v0 + (f32)(v1 - v0) * (frame - (f32)f0) / (f32)(f1 - f0);
            } else {
                w = v0;
            }
            v = w / (f32)(1 << shift);
        }
        switch (kind) {
        case 0: pos.x = v; break;
        case 1: pos.y = v; break;
        case 2: pos.z = v; break;
        case 10: r1 = v; break;
        case 11: g1 = v; break;
        case 12: b1 = v; break;
        case 13: k1 = v; break;
        case 14: r2 = v; break;
        case 15: g2 = v; break;
        case 16: b2 = v; break;
        case 17: k2 = v; break;
        }
    }
    if (set2 == 0) set2 = fn_80010C18();
    k1 *= 51.0f;
    r1 *= k1;
    g1 *= k1;
    b1 *= k1;
    set2->r = clamp255(r1);
    set2->g = clamp255(g1);
    set2->b = clamp255(b1);
    l = fn_80010DA4(set2, 1);
    if (l == 0) l = fn_80010E38(set2, 1);
    k2 *= 51.0f;
    r2 *= k2;
    g2 *= k2;
    b2 *= k2;
    l->r = clamp255(r2);
    l->g = clamp255(g2);
    l->b = clamp255(b2);
    l->pos.x = pos.x;
    l->pos.y = pos.y;
    l->pos.z = pos.z;
    fn_8001D44C(a->xf, m);
    fn_8001E6D0(m, m);
    fn_800110F4(set2, m);
    return 1;
}
}
