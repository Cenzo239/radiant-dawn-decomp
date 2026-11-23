#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
typedef struct EQ { u8 pad[0xE]; s16 xE; } EQ;
typedef struct EC { void* u; u8 x4, x5; s16 x6, x8, xA, xC, xE, x10, x12, x14, x16, x18, x1A, x1C, x1E; } EC;
typedef struct SKC {
    s8 x0; u8 x1; s16 x2, x4, x6; u8 x8, x9, xA, xB, xC; u8 padD; u16 xE[32]; EC x50[3]; s16 xB0;
} SKC;
typedef struct BQ { s16 i; u8 pad[2]; struct { u8 k; u8 p; s16 v; } e[1]; } BQ;
extern u8 lbl_803C8E80[0x1648];
#define Q ((BQ*)(lbl_803C8E80 + 0xDE0))
typedef struct UQ { u8 pad[0x3F0]; void* x3F0; u8 pad2[0x97]; u8 x48B; } UQ;
extern void fn_80026000(void*);
extern void fn_801CE6A0(EC*, void*);
extern int fn_801CEAE0(SKC*);
extern void fn_801CF040(SKC*);
extern void fn_801CF270(SKC*);
extern void fn_801CF3E4(SKC*);
static inline BOOL Is1(int k) {
 switch (k) {
 case 0x42: case 0x43: case 0x44: case 0x48: case 0x4A: case 0x4B: case 0x4C: case 0x4D: case 0x4E: case 0x4F: case 0x50: case 0x51: case 0x52: case 0x53: case 0x54: case 0x55: case 0x56: case 0x63: return 1;
 case 0x45: case 0x46: case 0x47: case 0x49: case 0x57: case 0x58: case 0x59: case 0x5A: case 0x5B: case 0x5C: case 0x5D: case 0x5E: case 0x5F: case 0x60: case 0x61: case 0x62: default: return 0; }
}
static inline int Find1(SKC* s) { int n = s->xC; int i; for (i = 0; i < n; i++, s = (SKC*)((u8*)s + 2)) { if (Is1(s->xE[0])) return s->xE[0]; } return 0; }
static inline int Side(UQ* u, int i) {
    if (u) {
        if (u->x48B) return 0;
        return 1;
    }
    return i;
}
void fn_801CE800(SKC* d) {
    EC* e1;
    BQ* q;
    u8* b = lbl_803C8E80;
    q = (BQ*)(b + 0xDE0);
    fn_80026000(q);
    fn_801CE6A0(&d->x50[0], b);
    e1 = &d->x50[1];
    fn_801CE6A0(e1, b + 0x4A0);
    d->x50[0].x5 = 0;
    e1->x5 = 1;
    d->x50[2].x5 = 2;
    d->x50[0].x4 = Side((UQ*)d->x50[0].u, 0);
    e1->x4 = Side((UQ*)e1->u, 1);
    d->x50[2].x4 = Side((UQ*)d->x50[2].u, 2);
    d->x0 = 0;
    d->x2 = 0;
    d->x4 = 0;
    d->x6 = 0;
    d->xB0 = 0;
    d->x8 = 0;
    d->x9 = 0;
    fn_801CF3E4(d);
    for (;;) {
        BQ* p = (BQ*)((u8*)q + q->i * 4);
        switch (p->e[0].k) {
        case 0: case 0x72: goto done;
        case 4:
            d->x50[0].x6 = p->e[0].v;
            d->x50[0].x8 = q->e[q->i].v;
            d->x50[0].xA = q->e[q->i].v;
            break;
        case 3: d->x50[0].xC = p->e[0].v; break;
        case 5: d->x50[0].x10 = p->e[0].v; break;
        case 6: d->x50[0].x12 = p->e[0].v; break;
        case 7: d->x50[0].x14 = p->e[0].v; break;
        case 8: d->x50[0].x16 = p->e[0].v; break;
        case 0xF:
            e1->x6 = p->e[0].v;
            e1->x8 = q->e[q->i].v;
            e1->xA = q->e[q->i].v;
            break;
        case 0xE: e1->xC = p->e[0].v; break;
        case 0x10: e1->x10 = p->e[0].v; break;
        case 0x11: e1->x12 = p->e[0].v; break;
        case 0x12: e1->x14 = p->e[0].v; break;
        case 0x13: e1->x16 = p->e[0].v; break;
        }
        q->i++;
    }
done:
    {
    s16 save = Q->i;
    fn_801CEAE0(d);
    Q->i = save;
    d->xB0 = save;
    }
}
static inline int Ev6E2(void) {
    s16 save = Q->i;
    BQ* q = Q;
    int k;
    for (;;) {
        k = q->e[q->i].k;
        switch (k) {
        case 0: case 0x6E: case 0x6F: case 0x70: case 0x71: goto done;
        }
        q->i++;
    }
done:
    Q->i = save;
    return k;
}
static inline int Ev25b(void) {
    int k;
    s16 save = Q->i;
    BQ* q = Q;
    for (;;) {
        k = q->e[q->i].k;
        switch (k) {
        case 0: case 0x25: case 0x26: case 0x27: case 0x28: goto done;
        }
        q->i++;
    }
done:
    Q->i = save;
    return k;
}
int fn_801CEAE0(SKC* d) {
    BQ* q = Q;
    for (;;) {
        switch (q->e[q->i].k) {
        case 0: return 0;
        case 0x24:
            if (Ev6E2() != 0x71) { q->i++; goto found; }
            break;
        }
        q->i++;
    }
found:
    d->x6 = Ev25b();
    switch (d->x6) {
    case 0x25: d->x0 = 0; break;
    case 0x26: d->x0 = 1; break;
    case 0x28: {
        int v = -1;
        if (d->x0 >= 0) v = 1 - d->x0;
        d->x0 = v;
        break;
    }
    case 0x27: d->x0 = 2; break;
    }
    fn_801CF040(d);
    fn_801CF270(d);
    d->xB0 = Q->i;
    return 1;
}
static inline EQ* EqI(u8* e, int i) { if (i < 0) return 0; return (EQ*)e; }
static inline EC* EcI(u8* e, int i) { if (i < 0) return 0; return (EC*)e; }
static inline BOOL Dead(EC* e, void* v) {
    if (v) {
        if (e->x6 <= 0) return 1;
        if (e->xA <= 0) return 1;
    }
    return 0;
}
static inline void* UVal(EC* e) { return e->u ? ((UQ*)e->u)->x3F0 : 0; }
static inline int Owner(SKC* s, int k) {
    switch (k) {
    case 0xA: case 0x1B: case 0x3C: case 0x3D: case 0x40: case 0x41: return 0;
    case 0x15: case 0x1C: case 0x3F: return 1;
    case 0x47: case 0x5E: case 0x5F: case 0x6A: case 0x6D:
    case 0x7E: case 0x7F: case 0x80: case 0x81: case 0x82: case 0x83: case 0x84: case 0x85: case 0x86: case 0x87: {
        int r = -1;
        s8 v = s->x0;
        if (v >= 0) r = 1 - v;
        return r;
    }
    case 0x3E:
    default: {
        s8 v = s->x0;
        if (v < 0) return -1;
        return v;
    }
    }
}
static inline int Mine(SKC* s) { s8 v = s->x0; if (v < 0) return -1; return v; }
static inline int Theirs(SKC* s) { s8 v = s->x0; if (v < 0) return -1; return 1 - v; }
static inline int Prio(SKC* s, int k) {
    if (k == 0x6F) return 0x32;
    if (k == 0x6D) return 0x28;
    if (Is1(k)) return 0x1E;
    if (Owner(s, k) == Mine(s)) return 0x14;
    return Owner(s, k) == Theirs(s) ? 0xA : 0;
}
void fn_801CF3E4(SKC* s) {
    s16 save;
    int k;
    BQ* q;
    s->xC = 0;
    q = Q;
    {
    save = Q->i;
    for (;;) {
        k = q->e[q->i].k;
        switch (k) {
        case 0xA: case 0x15: case 0x1B: case 0x1C:
        case 0x3C: case 0x3D:
        case 0x3F: case 0x40: case 0x41: case 0x42: case 0x43: case 0x44: case 0x45: case 0x46: case 0x47: case 0x48: case 0x49: case 0x4A: case 0x4B: case 0x4C: case 0x4D: case 0x4E: case 0x4F:
        case 0x50: case 0x51: case 0x52: case 0x53: case 0x54: case 0x55: case 0x56: case 0x57: case 0x58: case 0x59: case 0x5A: case 0x5B: case 0x5C: case 0x5D: case 0x5E: case 0x5F: case 0x60:
        case 0x63: case 0x64: case 0x67: case 0x69: case 0x6A: case 0x6D: case 0x6F:
        case 0x7E: case 0x7F: case 0x80: case 0x81: case 0x82: case 0x83: case 0x84: case 0x85: case 0x86: case 0x87:
            s->xE[s->xC++] = k;
            break;
        case 0: case 0x2A: case 0x72: goto done;
        case 0x3E: case 0x61: case 0x62: case 0x65: case 0x66: case 0x68: case 0x6B: case 0x6C: case 0x6E: case 0x70: case 0x71:
            break;
        }
        q->i++;
    }
done:
    Q->i = save;
    }
    {
    SKC* p;
    int i;
    int j;
    for (i = 0; i < s->xC; i++) {
        p = s;
        for (j = 0; j < s->xC - 1 - i; p = (SKC*)((u8*)p + 2), j++) {
            u16 a = p->xE[0];
            int pa = Prio(s, a);
            u16 b = p->xE[1];
            int pb = Prio(s, b);
            if (pa > pb) { p->xE[0] = b; p->xE[1] = a; }
        }
    }
    }
}
}
