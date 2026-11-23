/* r20: `sched` (check_regs.py). fn_801CF270 from wip/fn_801CFA90.cpp made self-contained with the declarations of fn_801CFA90.cpp
   (tools/equiv/mkself.py). Moved (dd.py): one `cmpwi r0,0x28` and one `addi` of a table offset one slot apart. The symbolic block check (r20_symcheck.py --anon)
   finds every block equal. */
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

int fn_801CFA90(SK* s);

int fn_801CFB10(SK* s);

int fn_801CFB7C(SK* s);

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
BOOL fn_801CFC58(SK* s);

BOOL fn_801CFD50(SK* s);
BOOL fn_801CFCE0(SK* s);

BOOL fn_801CFD50(SK* s);

BOOL fn_801CFDEC(SK* s, int k);

BOOL fn_801CFE3C(SK* s, int k);

BOOL fn_801CFE78(SK* s, int k);

BOOL fn_801CFED8(SK* s, int k);

EQ* fn_801D0784(SK* s, int i);

typedef struct BQ { s16 i; u8 pad[2]; struct { u8 k; u8 p[3]; } e[1]; } BQ;
extern u8 lbl_803C8E80[0x1648];
#define Q ((BQ*)(lbl_803C8E80 + 0xDE0))

int fn_801D02FC(void);

int fn_801D038C(void);

extern u8 lbl_804CB9F0;
extern const f32 lbl_804CF770;
extern u32 fn_803080DC(u32, u32, u32, u32);
void fn_801D0940(u32 x, u32 y, u32 w, u32 h);

extern void* fn_8010B23C(u32);
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
void* fn_801CFF0C(SK* self, int k);

int fn_801D0214(SK* s, int k);

int fn_801D040C(void);

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
int fn_801D0674(SK* s, int k);


#pragma use_lmw_stmw on
typedef struct EC { u32 x0; u8 x4, x5; s16 x6, x8, xA, xC, xE, x10, x12, x14, x16, x18, x1A, x1C, x1E; } EC;
void fn_801CE760(EC* d, const EC* s);

typedef struct SKC {
    u8 x0, x1; s16 x2, x4, x6; u8 x8, x9, xA, xB, xC; u8 padD; u16 xE[32]; EC x50[3]; s16 xB0;
} SKC;
SKC* fn_801D0518(SKC* d, const SKC* s);

#pragma use_lmw_stmw off
extern int* fn_80030CF4(void*);
extern BOOL fn_8011B77C(void*, u32);
extern u32 lbl_804CA4E8, lbl_804CA4EC;
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

/* ---- from rF_8017F400/wip/fn_801CFA90.cpp ---- */
extern "C" {


void fn_801CF270(SKV* s) {
    BQ* q;
    s16 save;
    int v;
    s->x9 = 0;
    q = Q;
    save = Q->i;
    v = s->x0;
    if (s->x6 == 0x28) {
        v = v < 0 ? -1 : 1 - v;
    }
    for (;;) {
        switch (q->e[q->i].k) {
        case 0: goto done;
        case 0x24:
            if (Ev6E() != 0x71) {
                switch (Ev25()) {
                case 0x25:
                    if (v == 0) s->x9 = 1;
                    break;
                case 0x26:
                    if (v == 1) s->x9 = 1;
                    break;
                }
                goto done;
            }
            break;
        }
        q->i++;
    }
done:
    Q->i = save;
}
}
