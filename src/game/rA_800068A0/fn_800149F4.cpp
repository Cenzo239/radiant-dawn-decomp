#include "game/rA_800068A0/types.h"
extern "C" {
extern void fn_80078E24(void* p);
struct GHook {
    u8 type;
    u8 x1;
    u16 x2;
    void* func;
    GHook& operator=(const GHook& o) {
        type = o.type;
        x1 = o.x1;
        x2 = o.x2;
        func = o.func;
        return *this;
    }
};
typedef struct GEnt {
    u8 x0[7];
    u8 x7;
    u8 x8[0x18 - 8];
    GHook* hooks;
} GEnt;
typedef struct Cnt { u8 a, b, c; } Cnt;
void fn_800149F4(GEnt* e, void* f) {
    int i;
    int j;
    GHook* h;
    GHook* q;
    h = e->hooks;
    if (h != 0) {
        if (f != 0) {
            Cnt n = {0, 0, 0};
            for (i = 0; i < 8; i++, h++) {
                if (h->func == 0) {
                    break;
                }
                if (h->func == f) {
                    h->func = 0;
                    h->type = 0;
                    q = h;
                    for (j = i; j < 7; j++, q++) {
                        q[0] = q[1];
                    }
                    q->type = 0;
                    q->func = 0;
                    q->x1 = 0;
                    q->x2 = 0;
                    i--;
                    h--;
                } else {
                    switch (h->type) {
                    case 1:
                        n.a++;
                        break;
                    case 2:
                        n.b++;
                        break;
                    case 4:
                        n.c++;
                        break;
                    }
                }
            }
            if (n.a == 0) {
                e->x7 &= ~1;
            }
            if (n.b == 0) {
                e->x7 &= ~2;
            }
            if (n.c == 0) {
                e->x7 &= ~4;
            }
        } else {
            fn_80078E24(h);
            e->hooks = 0;
            e->x7 &= ~7;
        }
    }
}

extern char lbl_80360DF8[];
extern void* fn_80078D9C(u32 size, const char* name, int flags);
extern void fn_80312318(void* m);
typedef struct GVert { s16 x0, x2, x4, x, y, z; } GVert;
typedef struct GPart { f32 pos[3]; f32 vel[3]; f32 x18; f32 x1C; f32 x20; f32 x24; f32 x28; u8 r, g, b, a; u8 x30[0x48 - 0x30]; u8 x48, x49; s16 x4A; } GPart;
typedef struct GSeg { u8 x0[6]; u16 flags; u8 x8[0x1C - 8]; u16 node; u16 count; GVert* verts; u8 x24[0x34 - 0x24]; } GSeg;
typedef struct GHdr { u32 magic; u16 flags; u16 count; GSeg segs[1]; } GHdr;
typedef struct GTrailEnt { f32 frame; f32 x4; s16 min; s16 max; GPart* parts; void* buf; } GTrailEnt;
typedef struct GState { f32 m[12]; GHdr* hdr; GTrailEnt* ents; } GState;
typedef struct GChunk { u32 type; void* data; struct GChunk* next; } GChunk;
typedef struct GRes { GChunk* head; } GRes;
typedef struct GNode { u8 x0[0xC]; u32 flags; } GNode;
typedef struct GA { u8 x0[0x54]; GState* st; f32 frame; } GA;
extern GRes* fn_80007F10(GA* a);
extern void* fn_80007EE4(GA* a);
extern GNode* fn_8000F3D4(void* m, u16 idx);
#if TARGET_PC
extern FE10_PROTO void fn_800151EC(ptr32<const void>, GHdr* h);
#else
extern void fn_800151EC(GRes* r, GHdr* h);
#endif

static inline void* find(GRes* r) {
    GChunk* c;
    for (c = r->head; c != 0; c = c->next) {
        if (c->type == 0xD) {
            return c->data;
        }
    }
    return 0;
}
static inline void reset(GA* a) {
    GState* s;
    GHdr* h;
    GSeg* sg;
    GTrailEnt* en;
    int i;
    GPart* p;
    GVert* v;
    int j;
    s = a->st;
    if (s != 0) {
        h = s->hdr;
        en = s->ents;
        sg = h->segs;
        for (i = 0; i < h->count; i++, sg++, en++) {
            v = sg->verts;
            p = en->parts;
            en->frame = a->frame;
            en->x4 = 0.0f;
            en->min = 0;
            en->max = 0;
            for (j = 0; j < sg->count; j++, p++) {
                p->pos[0] = 0.015625f * v->x;
                p->pos[1] = 0.015625f * v->y;
                p->pos[2] = 0.015625f * v->z;
                v++;
                p->vel[0] = 0.0f;
                p->vel[1] = 0.0f;
                p->vel[2] = 0.0f;
                p->x18 = -1.0f;
                p->x1C = 0.0f;
                p->x20 = 1.0f;
                p->x24 = 1.0f;
                p->r = 0xFF;
                p->g = 0xFF;
                p->b = 0xFF;
                p->a = 0;
                p->x48 = 0;
                p->x49 = 0;
            }
            if (sg->flags & 0x10) {
                en->min = 10000;
                en->max = -10000;
                v = sg->verts;
                for (j = 0; j < sg->count; j++, v++) {
                    if (en->min > v->x2) {
                        en->min = v->x2;
                    }
                    if (en->max < v->x2 + 1) {
                        en->max = v->x2 + 1;
                    }
                }
            }
        }
    }
}

void fn_8001528C(GA* a) {
    int i;
    void* mdl;
    GState* s;
    int k;
    GSeg* sg;
    GTrailEnt* en;
    GPart* p;
    int j;
    GRes* r;
    r = fn_80007F10(a);
    mdl = fn_80007EE4(a);
    if (r != 0) {
        GHdr* h = (GHdr*)find(r);
        if (h != 0 && h->magic == 0x12345678) {
            fn_800151EC(r, h);
            if (h->count != 0) {
                s = (GState*)fn_80078D9C(0x38, lbl_80360DF8, 0);
                a->st = s;
                en = (GTrailEnt*)fn_80078D9C(h->count * 0x14, lbl_80360DF8, 0);
                s->ents = en;
                sg = h->segs;
                for (i = 0; i < h->count; i++, sg++, en++) {
                    if (fn_8000F3D4(mdl, sg->node)->flags & 0xC00000) {
                        sg->flags = (sg->flags & 0xFFF8) | 5;
                    }
                    if ((sg->flags & 7) == 6) {
                        h->flags |= 0x4000;
                    }
                    en->buf = 0;
                    if (sg->count == 0) {
                        en->parts = 0;
                    } else {
                        p = (GPart*)fn_80078D9C(sg->count * 0x4C, lbl_80360DF8, 0);
                        en->parts = p;
                        if ((sg->flags & 7) == 5) {
                            en->buf = fn_80078D9C(sg->count * 0xC0, lbl_80360DF8, 0);
                            j = 0;
                            k = 0;
                            for (; j < sg->count; j++, p++) {
                                p->x4A = k;
                                k += 0x20;
                            }
                        } else {
                            for (j = 0; j < sg->count; j++, p++) {
                                p->x4A = -1;
                            }
                        }
                    }
                }
                s->hdr = h;
                fn_80312318(s);
                reset(a);
            }
        }
    }
}
}
