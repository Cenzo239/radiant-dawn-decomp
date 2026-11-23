#ifndef RC2_MORE_H
#define RC2_MORE_H
/* Types and prototypes for the second pass over this region. */
#include "game/rC2_8005259C/decls.h"
extern u8* lbl_804CB810;
extern u8 lbl_8037DD48[]; extern u8 lbl_8037DE20[];
typedef struct GD2 { u8 p[0x12]; s16 h12; u8 pad[0x92c-0x14]; u8 b92c; u8 pad2[0x934-0x92d]; f32 f934; f32 f938; } GD2;
extern "C" {
void fn_8010E41C(void* buf, int n);
int fn_8011799C(void* m, s8 x, s8 y);
int fn_80128744(Unit2* u);
s8 fn_801284C4(Unit2* u);
#if TARGET_PC
FE10_PROTO void fn_800CFC50(Word* w, s8 x, s8 y, u8 v, p32arg);
#else
void fn_800CFC50(Word* w, s8 x, s8 y, u8 v, int n);
#endif
void fn_800CFB34(Word* w);
#if TARGET_PC
FE10_PROTO void fn_80045120(UnitCmdState* s, p32arg);
#else
void fn_80045120(UnitCmdState* s, int v);
#endif
void fn_800485C4(UnitCmdState* s, void* p);
void fn_800484B8(UnitCmdState* s, void* p);
void fn_80118098(void* m, s8 x, s8 y);
void fn_80027088(BigState* b, void* u, int n);
s16 fn_801237EC(BigState* b);
void fn_8002BE64(BigState* b, s16 n);
#if TARGET_PC
FE10_PROTO void fn_800E9608(void* p, p32arg);
#else
void fn_800E9608(void* p, int n);
#endif
int fn_80108D00(void* p, int n);
}
typedef struct UFull { u8 pad[0xec]; void* ec; u8 padf0[4]; UnitSub* f4; u8 padf8[4]; u8 fc; u8 padfd[5]; s8 x; s8 y; u8 pad104[8]; u32 flags; u8 sk[4]; } UFull;
static inline s16 gt(void* g) { return ((GD2*)g)->h12; }
static inline UFull* GetU(u8 id) {
    if (id != 0) return (UFull*)(lbl_804CB810 + (id - 1) * 0x3f0);
    return 0;
}
typedef struct P6 { u8 pad[0x30]; int v[12]; u8 b60[12]; s16 h6c; s16 h6e; } P6;
static inline int getV(P6* p, int i) { return p->h6c >= 0xc ? 0 : p->v[i]; }
static inline u8 getB(P6* p, int i) { return p->h6c >= 0xc ? 0 : p->b60[i]; }
typedef struct WW { int a; int b; } WW;
typedef struct E3x { u8 pad[0x34]; s16 h34; u8 pad36[5]; u8 b3b; } E3x;

extern u8 lbl_8037DE20[];
extern "C" {
int fn_80108D00(void* p, int n);
void fn_8002697C(BigState* b);
#if TARGET_PC
FE10_PROTO void fn_800E9380(void* p, p32arg);
FE10_PROTO void fn_800E9458(void* p, p32arg);
FE10_PROTO void fn_800E96E0(void* p, s8 x, s8 y, int a, int b, p32arg);
#else
void fn_800E9380(void* p, int n);
void fn_800E9458(void* p, int n);
void fn_800E96E0(void* p, s8 x, s8 y, int a, int b, int n);
#endif
void fn_8011E414(void* u);
#if TARGET_PC
FE10_PROTO void fn_800E8844(void* p, p32arg);
#else
void fn_800E8844(void* p, int n);
#endif
void fn_80056338x(void* a, void* b, u8* c);
}
typedef struct Q10 { s8 x; s8 y; u8 p2[2]; int a4; int a8; int ac; } Q10;
typedef struct GD3 { u8 pad[0xc0]; s16 hc0; s16 hc2; s16 hc4; s16 hc6; int c8; int cc; int d0; int d4; } GD3;
typedef struct U5 { u8 pad[0xf4]; UnitSub* f4; u8 p[0x114-0xf8]; s8 b114; u8 p2[0x12c-0x115]; u8 x12c[0x384-0x12c]; u16 h384; u16 h386; } U5;
extern void* lbl_804CA58C;
#define GD ((GD3*)&lbl_803CAB38)

extern "C" {
void fn_801856F4(void);
void fn_80026C44(BigState* b, void* a, void* c);
void fn_8006C440(BigState* b);
}
extern s8 lbl_804CB440; extern void* lbl_804CB444; extern u8 lbl_8037EC08[];
extern s8 lbl_804CB448; extern void* lbl_804CB44C; extern u8 lbl_8037EBB0[];
extern s8 lbl_804CB450; extern Lazy2 lbl_804CB458; extern u8 lbl_8037E178[]; extern u8 lbl_8037F16C[];
extern s8 lbl_804CB41C; extern void* lbl_804CB420; extern u8 lbl_8037EA50[];
extern s8 lbl_804CB424; extern void* lbl_804CB428; extern u8 lbl_8037E9F8[];
extern s8 lbl_804CB42C; extern void* lbl_804CB430; extern u8 lbl_8037E9A0[];
extern s8 lbl_804CB434; extern Lazy2 lbl_804CB438; extern u8 lbl_8037E168[]; extern u8 lbl_8037F0D8[];
#define SALLY_TAIL(p) \
    { void* r = fn_800D4228(lbl_80361F9C + 0x15); \
    if (r == 0 || ((s16*)r)[0x14] >= 0) { \
        fn_800D3BCC(fn_800D4188(lbl_80361F9C + 0x15, p), 4); \
    } } \
    { const char* s = ((char**)lbl_804CB554)[1]; \
    Spr* q = fn_801E5640(p, -0x1000, 0); \
    if (q) { q->f64 = s; } }
#define GD3P ((GD3*)&lbl_803CAB38)
static inline void addStat(u8 k, U5* u) {
    switch (k) {
    case 0: GD3P->c8++; GD3P->hc0++; break;
    case 1: GD3P->cc++; GD3P->hc2++; u->h384++; u->h386++; break;
    case 2: GD3P->d0++; GD3P->hc4++; break;
    case 3: GD3P->d4++; GD3P->hc6++; break;
    }
}
typedef struct E55 { u8 pad[0x30]; U5* u; u8 pad34[6]; u8 b3a; u8 b3b; } E55;

#endif
