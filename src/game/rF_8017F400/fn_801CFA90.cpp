#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
typedef struct SK { s8 x0; u8 pad1[0xB]; u8 xC; u8 padD; u16 xE[32]; } SK;
typedef struct EQ { u8 pad[0xE]; s16 xE; } EQ;
static inline BOOL Is1(int k) {
 switch (k) {
 case 0x42: case 0x43: case 0x44: case 0x48: case 0x4A: case 0x4B: case 0x4C: case 0x4D: case 0x4E: case 0x4F: case 0x50: case 0x51: case 0x52: case 0x53: case 0x54: case 0x55: case 0x56: case 0x63: return 1;
 case 0x45: case 0x46: case 0x47: case 0x49: case 0x57: case 0x58: case 0x59: case 0x5A: case 0x5B: case 0x5C: case 0x5D: case 0x5E: case 0x5F: case 0x60: case 0x61: case 0x62: default: return 0; }
}
static inline BOOL Is2(int k) {
 switch (k) {
 case 0x45: case 0x46: case 0x47: case 0x49: case 0x6F: return 1;
 case 0x48: default: return 0; }
}
static inline BOOL Is3(int k) {
 switch (k) {
 case 0x57: case 0x58: case 0x59: case 0x5A: case 0x5B: case 0x5C: case 0x5D: case 0x5E: case 0x5F: case 0x60: case 0x64: case 0x69: case 0x6A: case 0x6D: case 0x7E: case 0x7F: case 0x80: case 0x81: case 0x82: case 0x83: case 0x84: case 0x85: case 0x86: case 0x87: return 1;
 case 0x61: case 0x62: case 0x63: case 0x65: case 0x66: case 0x67: case 0x68: case 0x6B: case 0x6C: case 0x6E: case 0x6F: case 0x70: case 0x71: case 0x72: case 0x73: case 0x74: case 0x75: case 0x76: case 0x77: case 0x78: case 0x79: case 0x7A: case 0x7B: case 0x7C: case 0x7D: default: return 0; }
}
static inline BOOL Is4(int k) {
 switch (k) {
 case 0x57: case 0x58: case 0x59: case 0x5A: case 0x64: case 0x69: return 1;
 case 0x5B: case 0x5C: case 0x5D: case 0x5E: case 0x5F: case 0x60: case 0x61: case 0x62: case 0x63: default: return 0; }
}

#define FIND(NAME, IS) \
int NAME(SK* s) { \
    int i; \
    for (i = 0; i < s->xC; i++) { \
        int k = *(u16*)((u8*)s + 0xE); \
        if (IS(k)) return k; \
        s = (SK*)((u8*)s + 2); \
    } \
    return 0; \
}

int fn_801CFA90(SK* s) { int n = s->xC; int i; for (i = 0; i < n; i++, s = (SK*)((u8*)s + 2)) { int k = s->xE[0]; if (Is1(k)) return k; } return 0; }
int fn_801CFB10(SK* s) { int n = s->xC; int i; for (i = 0; i < n; i++, s = (SK*)((u8*)s + 2)) { int k = s->xE[0]; if (Is4(k)) return k; } return 0; }
int fn_801CFB7C(SK* s) { int n = s->xC; int i; for (i = 0; i < n; i++, s = (SK*)((u8*)s + 2)) { int k = s->xE[0]; if (Is3(k)) return k; } return 0; }
static inline BOOL Has(SK* s, int v) {
    int n = s->xC;
    int i;
    SK* q = s;
    for (i = 0; i < n; i++, q = (SK*)((u8*)q + 2)) {
        if (q->xE[0] == v) return 1;
    }
    return 0;
}
EQ* fn_801D0784(SK* s, int i);
static inline EQ* EqAt(SK* s, int i) {
    if (i < 0) return 0;
    return (EQ*)((u8*)s + (i << 5) + 0x50);
}
BOOL fn_801CFC58(SK* s) {
    if (Has(s, 0x67)) {
        int i = -1;
        if (s->x0 >= 0) i = s->x0;
        if (EqAt(s, i)->xE > 0) return 1;
    }
    return 0;
}
BOOL fn_801CFD50(SK* s);
BOOL fn_801CFCE0(SK* s) {
    if (Has(s, 0x6D) && fn_801CFD50(s) == 0) return 1;
    return 0;
}
BOOL fn_801CFD50(SK* s) {
    int n = s->xC;
    int i;
    for (i = 0; i < n; s = (SK*)((u8*)s + 2), i++) {
        switch (s->xE[0]) {
        case 0x7E: return 1;
        case 0x7F: return 1;
        case 0x80: return 1;
        case 0x81: return 1;
        case 0x82: return 1;
        case 0x83: return 1;
        case 0x84: return 1;
        case 0x85: return 1;
        case 0x86: return 1;
        case 0x87: return 1;
        }
    }
    return 0;
}
BOOL fn_801CFDEC(SK* s, int k) { return Is1(k); }
BOOL fn_801CFE3C(SK* s, int k) { return Is2(k); }
BOOL fn_801CFE78(SK* s, int k) { return Is3(k); }
BOOL fn_801CFED8(SK* s, int k) { int n = s->xC; int i; for (i = 0; i < n; i++, s = (SK*)((u8*)s + 2)) { if (k == s->xE[0]) return 1; } return 0; }
EQ* fn_801D0784(SK* s, int i) { return EqAt(s, i); }
typedef struct BQ { s16 i; u8 pad[2]; struct { u8 k; u8 p[3]; } e[1]; } BQ;
extern u8 lbl_803C8E80[0x1648];
#define Q ((BQ*)(lbl_803C8E80 + 0xDE0))
int fn_801D02FC(void) {
    BQ* q;
    int k;
    s16 save = Q->i;
    q = Q;
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
int fn_801D038C(void) {
    int r = -1;
    s16 save = Q->i;
    BQ* q = Q;
    Q->i = 0;
    for (;;) {
        int k = q->e[q->i].k;
        switch (k) {
        case 0: goto done;
        case 0xB: r = 1; goto done;
        case 0x16: r = 0; goto done;
        }
        q->i++;
    }
done:
    Q->i = save;
    return r;
}
extern u8 lbl_804CB9F0;
extern const f32 lbl_804CF770;
extern u32 fn_803080DC(u32, u32, u32, u32);
void fn_801D0940(u32 x, u32 y, u32 w, u32 h) {
    if (lbl_804CB9F0) {
        x = (u32)((f32)x * lbl_804CF770) + 0x48;
        w = (u32)((f32)w * lbl_804CF770);
    }
    fn_803080DC(x, y, w, h);
}
#if TARGET_PC
extern FE10_PROTO void* fn_8010B23C(p32arg);
#else
extern void* fn_8010B23C(u32);
#endif
#if TARGET_PC
FE10_PROTO extern p32ret lbl_804CA5DC;
FE10_PROTO extern p32ret lbl_804CA5E4;
FE10_PROTO extern p32ret lbl_804CA5E8;
FE10_PROTO extern p32ret lbl_804CA5EC;
FE10_PROTO extern p32ret lbl_804CA5F0;
FE10_PROTO extern p32ret lbl_804CA5F4;
FE10_PROTO extern p32ret lbl_804CA5F8;
FE10_PROTO extern p32ret lbl_804CA5FC;
FE10_PROTO extern p32ret lbl_804CA600;
FE10_PROTO extern p32ret lbl_804CA604;
FE10_PROTO extern p32ret lbl_804CA608;
FE10_PROTO extern p32ret lbl_804CA60C;
FE10_PROTO extern p32ret lbl_804CA610;
FE10_PROTO extern p32ret lbl_804CA614;
FE10_PROTO extern p32ret lbl_804CA618;
FE10_PROTO extern p32ret lbl_804CA61C;
FE10_PROTO extern p32ret lbl_804CA620;
FE10_PROTO extern p32ret lbl_804CA624;
FE10_PROTO extern p32ret lbl_804CA628;
FE10_PROTO extern p32ret lbl_804CA63C;
FE10_PROTO extern p32ret lbl_804CA640;
FE10_PROTO extern p32ret lbl_804CA644;
FE10_PROTO extern p32ret lbl_804CA648;
FE10_PROTO extern p32ret lbl_804CA64C;
FE10_PROTO extern p32ret lbl_804CA670;
FE10_PROTO extern p32ret lbl_804CA674;
FE10_PROTO extern p32ret lbl_804CA680;
FE10_PROTO extern p32ret lbl_804CA684;
FE10_PROTO extern p32ret lbl_804CA688;
FE10_PROTO extern p32ret lbl_804CA68C;
FE10_PROTO extern p32ret lbl_804CA690;
FE10_PROTO extern p32ret lbl_804CA694;
FE10_PROTO extern p32ret lbl_804CA698;
FE10_PROTO extern p32ret lbl_804CA69C;
FE10_PROTO extern p32ret lbl_804CA6A0;
FE10_PROTO extern p32ret lbl_804CA6A8;
FE10_PROTO extern p32ret lbl_804CA6E0;
FE10_PROTO extern p32ret lbl_804CA6F0;
FE10_PROTO extern p32ret lbl_804CA6F4;
#else
extern u32 lbl_804CA5DC;
extern u32 lbl_804CA5E4;
extern u32 lbl_804CA5E8;
extern u32 lbl_804CA5EC;
extern u32 lbl_804CA5F0;
extern u32 lbl_804CA5F4;
extern u32 lbl_804CA5F8;
extern u32 lbl_804CA5FC;
extern u32 lbl_804CA600;
extern u32 lbl_804CA604;
extern u32 lbl_804CA608;
extern u32 lbl_804CA60C;
extern u32 lbl_804CA610;
extern u32 lbl_804CA614;
extern u32 lbl_804CA618;
extern u32 lbl_804CA61C;
extern u32 lbl_804CA620;
extern u32 lbl_804CA624;
extern u32 lbl_804CA628;
extern u32 lbl_804CA63C;
extern u32 lbl_804CA640;
extern u32 lbl_804CA644;
extern u32 lbl_804CA648;
extern u32 lbl_804CA64C;
extern u32 lbl_804CA670;
extern u32 lbl_804CA674;
extern u32 lbl_804CA680;
extern u32 lbl_804CA684;
extern u32 lbl_804CA688;
extern u32 lbl_804CA68C;
extern u32 lbl_804CA690;
extern u32 lbl_804CA694;
extern u32 lbl_804CA698;
extern u32 lbl_804CA69C;
extern u32 lbl_804CA6A0;
extern u32 lbl_804CA6A8;
extern u32 lbl_804CA6E0;
extern u32 lbl_804CA6F0;
extern u32 lbl_804CA6F4;
#endif
void* fn_801CFF0C(SK* self, int k) {
    u32 s = 0;
    switch (k) {
    case 0x44: s = lbl_804CA5E4; break;
    case 0x42: s = lbl_804CA5E8; break;
    case 0x4A: s = lbl_804CA5EC; break;
    case 0x51: s = lbl_804CA5F0; break;
    case 0x48: s = lbl_804CA5F4; break;
    case 0x4B: s = lbl_804CA5F8; break;
    case 0x4C: s = lbl_804CA5FC; break;
    case 0x4F: s = lbl_804CA600; break;
    case 0x50: s = lbl_804CA604; break;
    case 0x4D: s = lbl_804CA608; break;
    case 0x4E: s = lbl_804CA60C; break;
    case 0x43: s = lbl_804CA610; break;
    case 0x63: s = lbl_804CA614; break;
    case 0x52: s = lbl_804CA618; break;
    case 0x53: s = lbl_804CA61C; break;
    case 0x54: s = lbl_804CA620; break;
    case 0x55: s = lbl_804CA624; break;
    case 0x56: s = lbl_804CA628; break;
    case 0x45: s = lbl_804CA690; break;
    case 0xA: s = lbl_804CA6A8; break;
    case 0x15: s = lbl_804CA6A8; break;
    case 0x1B: s = lbl_804CA6A8; break;
    case 0x1C: s = lbl_804CA6A8; break;
    case 0x3F: s = lbl_804CA698; break;
    case 0x49: s = lbl_804CA688; break;
    case 0x46: s = lbl_804CA684; break;
    case 0x47: s = lbl_804CA684; break;
    case 0x40: s = lbl_804CA6F4; break;
    case 0x3D: s = lbl_804CA6F0; break;
    case 0x41: s = lbl_804CA69C; break;
    case 0x64: s = lbl_804CA694; break;
    case 0x57: s = lbl_804CA640; break;
    case 0x58: s = lbl_804CA644; break;
    case 0x59: s = lbl_804CA648; break;
    case 0x5A: s = lbl_804CA64C; break;
    case 0x69: s = lbl_804CA5DC; break;
    case 0x5B: s = lbl_804CA670; break;
    case 0x5C: s = lbl_804CA674; break;
    case 0x5D: s = lbl_804CA68C; break;
    case 0x5E: s = lbl_804CA6E0; break;
    case 0x5F: s = lbl_804CA680; break;
    case 0x60: s = lbl_804CA6A0; break;
    case 0x6A: s = lbl_804CA63C; break;
    }
    if (s) return fn_8010B23C(s);
    return 0;
}

int fn_801D0214(SK* s, int k) {
    switch (k) {
    case 0xA: case 0x1B: case 0x3C: case 0x3D: case 0x40: case 0x41: return 0;
    case 0x15: case 0x1C: case 0x3F: return 1;
    case 0x47: case 0x5E: case 0x5F: case 0x6A: case 0x6D:
    case 0x7E: case 0x7F: case 0x80: case 0x81: case 0x82: case 0x83: case 0x84: case 0x85: case 0x86: case 0x87: {
        s8 v = s->x0;
        if (v < 0) return -1;
        return 1 - v;
    }
    case 0x3E:
    default: {
        s8 v = s->x0;
        if (v < 0) return -1;
        return v;
    }
    }
}
int fn_801D040C(void) {
    int r = -1;
    s16 save = Q->i;
    BQ* q = Q;
    Q->i = 0;
    for (;;) {
        int k = q->e[q->i].k;
        switch (k) {
        case 0: goto done;
        case 0xB: r = 1; goto done;
        case 0x16: r = 0; goto done;
        }
        q->i++;
    }
done:
    Q->i = save;
    if (r < 0) return -1;
    return 1 - r;
}
typedef struct UQ { u8 pad[0x48B]; u8 x48B; } UQ;
static inline EQ* At(u8* e, int i) {
    if (i < 0) return 0;
    return (EQ*)e;
}
static inline int Side(UQ* u, int i) {
    if (u) {
        if (u->x48B) return 0;
        return 1;
    }
    return i;
}
int fn_801D0674(SK* s, int k) {
    int i;
    u8* e = (u8*)s + 0x50;
    for (i = 0; i < 3; i++, e += 0x20) {
        if (k == Side(*(UQ**)At(e, i), i)) return i;
    }
    return k;
}

#pragma use_lmw_stmw on
typedef struct EC { u32 x0; u8 x4, x5; s16 x6, x8, xA, xC, xE, x10, x12, x14, x16, x18, x1A, x1C, x1E; } EC;
void fn_801CE760(EC* d, const EC* s) {
    d->x0 = s->x0;
    d->x4 = s->x4;
    d->x5 = s->x5;
    d->x6 = s->x6;
    d->x8 = s->x8;
    d->xA = s->xA;
    d->xC = s->xC;
    d->xE = s->xE;
    d->x10 = s->x10;
    d->x12 = s->x12;
    d->x14 = s->x14;
    d->x16 = s->x16;
    d->x18 = s->x18;
    d->x1A = s->x1A;
    d->x1C = s->x1C;
    d->x1E = s->x1E;
}
typedef struct SKC {
    u8 x0, x1; s16 x2, x4, x6; u8 x8, x9, xA, xB, xC; u8 padD; u16 xE[32]; EC x50[3]; s16 xB0;
} SKC;
SKC* fn_801D0518(SKC* d, const SKC* s) {
    int i;
    d->x0 = s->x0;
    d->x1 = s->x1;
    d->x2 = s->x2;
    d->x4 = s->x4;
    d->x6 = s->x6;
    d->x8 = s->x8;
    d->x9 = s->x9;
    d->xA = s->xA;
    d->xB = s->xB;
    d->xC = s->xC;
    for (i = 0; i < 32; i++) d->xE[i] = s->xE[i];
    for (i = 0; i < 3; i++) fn_801CE760(&d->x50[i], &s->x50[i]);
    d->xB0 = s->xB0;
    Q->i = d->xB0;
    return d;
}
#pragma use_lmw_stmw off
extern int* fn_80030CF4(void*);
#if TARGET_PC
extern FE10_PROTO BOOL fn_8011B77C(void*, p32arg);
#else
extern BOOL fn_8011B77C(void*, u32);
#endif
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA4E8, *lbl_804CA4EC;
#else
extern u32 lbl_804CA4E8, lbl_804CA4EC;
#endif
extern u32* fn_801116B8(void*);
typedef struct UA { u8 pad[0x3F0]; u8* x3F0; } UA;
typedef struct ItemT { u8 pad[0x12]; u8 x12; } ItemT;
typedef struct EW { UA* u; } EW;
typedef struct SKW { s8 x0; u8 x1; u8 pad2[4]; s16 x6; } SKW;
static inline u8 ItT(ItemT* it) { return it ? it->x12 : 0x13; }
static inline EQ* At2(SK* s, int i) {
    if (i < 0) return 0;
    return (EQ*)((u8*)s + (i << 5) + 0x50);
}
static inline void* Wpn(EW* e) {
    if (e->u) {
        void* w = fn_80030CF4(e->u);
        u8* v = e->u ? e->u->x3F0 : 0;
        if (w && v && fn_8011B77C(v + 0x12C, lbl_804CA4E8) && !fn_8011B77C(v + 0x12C, lbl_804CA4EC)) {
            if (ItT(*(ItemT**)w) == 5) return 0;
        }
        return w;
    }
    return 0;
}
typedef struct SKV { s8 x0; u8 pad1[5]; s16 x6; u8 pad8; u8 x9; } SKV;
static inline int Ev6E(void) {
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
static inline int Ev25(void) {
    s16 save = Q->i;
    BQ* q = Q;
    int k;
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
}
