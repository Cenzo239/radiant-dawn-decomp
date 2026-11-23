#include "game/rA_800068A0/types.h"

/* GMaterial hook slots and GActor particle copy. */

extern char lbl_80360D24[];
extern void* fn_80078CCC(u32, const char*, u32);

typedef struct MatHook { u8 type; u8 b1; u16 h2; void* func; } MatHook;
typedef struct GMat { u8 pad[7]; u8 flags; u8 pad8[0x10]; MatHook* hooks; } GMat;

void fn_800148C0(GMat* m, void* func, u8 type) {
    MatHook* h;
    int i;
    if (func == 0) {
        return;
    }
    if (m->hooks == 0) {
        h = fn_80078CCC(0x40, lbl_80360D24 + 0xBB, 0);
        m->hooks = h;
        for (i = 0; i < 8; i++) {
            h[i].type = 0;
            h[i].func = 0;
            h[i].b1 = 0;
            h[i].h2 = 0;
        }
    }
    h = m->hooks;
    for (i = 0; i < 8; i++, h++) {
        if (h->func == func) {
            return;
        }
        if (h->func == 0) {
            h->type = type;
            h->func = func;
            m->flags |= type;
            return;
        }
    }
}

typedef struct W3 { u32 a, b, c; } W3;
typedef struct H2 { u16 a, b; } H2;
typedef struct PartC {
    W3 p;
    W3 v;
    f32 f18, f1C, f20, f24, f28;
    u8 c0, c1, c2, c3;
    H2 h30, h34, h38, h3C, h40, h44;
    u8 b48, b49;
    s16 s4A;
} PartC;
typedef struct BufC { u8 pad[0xC]; PartC* parts; u8 pad10[4]; } BufC;
typedef struct SegC { u8 pad[0x1E]; u16 count; u8 pad20[0x14]; } SegC;
typedef struct InfoC { u8 pad[6]; u16 n; SegC segs[1]; } InfoC;
typedef struct StC { u8 pad[0x30]; InfoC* info; BufC* buf; } StC;
typedef struct ActC { u8 pad[0x54]; StC* st; } ActC;

static inline void copyPart(PartC* r, PartC* q) {
    r->p = q->p;
    r->v = q->v;
    r->f18 = q->f18;
    r->f1C = q->f1C;
    r->f20 = q->f20;
    r->f24 = q->f24;
    r->f28 = q->f28;
    r->c0 = q->c0;
    r->c1 = q->c1;
    r->c2 = q->c2;
    r->c3 = q->c3;
    { u16 y; u16 x; y = q->h30.a; x = q->h30.b; r->h30.a = y; r->h30.b = x; }
    { u16 y; u16 x; y = q->h34.a; x = q->h34.b; r->h34.a = y; r->h34.b = x; }
    { u16 y; u16 x; y = q->h38.a; x = q->h38.b; r->h38.a = y; r->h38.b = x; }
    { u16 y; u16 x; y = q->h3C.a; x = q->h3C.b; r->h3C.a = y; r->h3C.b = x; }
    { u16 y; u16 x; y = q->h40.a; x = q->h40.b; r->h40.a = y; r->h40.b = x; }
    { u16 y; u16 x; y = q->h44.a; x = q->h44.b; r->h44.a = y; r->h44.b = x; }
    r->b48 = q->b48;
    r->b49 = q->b49;
    r->s4A = q->s4A;
}

void fn_800161E0(ActC* a, ActC* b);
