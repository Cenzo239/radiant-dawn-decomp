/* r20 wip, self-contained (wip/fn_801C6830.cpp + declarations of fn_801C6830.cpp via mkself.py), still `other`:
   six instructions short (148 of 154); not analysed this round. */
#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
typedef struct ActState {
    u8* unit;  /* 0x00 */
    u8* x4;
    u8 pad8[0xC - 8];
    u8 xC;
    u8 xD;
    u8 xE;
    u8 padF[0x13 - 0xF];
    u8 x13;
    u8 x14;
    u8 x15, x16, x17;
    int x18;
} ActState;
extern ActState lbl_803CA870;
extern u8 lbl_803C8E80[0x1648];
extern struct { int n; u8 pad[0x20]; } lbl_803E7320;
extern char lbl_8036E538[];
extern u8 lbl_8038AA20[];
extern char lbl_8036E6D8[];
extern u8 lbl_8038AB70[];
extern u8 lbl_8038AB9C[];
extern u8 lbl_803CB770[];
extern u8 lbl_803CAB38[];
extern u8 lbl_803EC898[];
extern u8 lbl_804CA504[4];
extern u8* lbl_804CB810;
extern u8 lbl_804CB830;
extern void fn_8003B3DC(void*, int);
extern void fn_8003A3BC(void*, void*);
extern void fn_8003A664(void*, void*);
extern void fn_8003A7B8(void*, void*);
extern void fn_8003A90C(void*, void*);
extern void fn_8003AFF8(void*, void*);
extern void fn_8003A510(void*, void*);
extern void fn_8003B04C(void*, void*);
extern void fn_8003AA60(void*, void*);
extern BOOL fn_8011B77C(void*, u32);
extern void fn_80039AE4(void*, void*);
extern void fn_80076D48(const char*, void*);
extern void fn_801C7AF0(void);
extern void fn_801C7898(void);
extern void fn_80026C44(void*, void*, void*);
extern void fn_80026CD8(void*, void*, int);
extern void fn_8002C0EC(void*, int);
extern void fn_8002C474(void*, int);
extern void** fn_80044FD0(void*);
extern int fn_80123998(void*);
extern int fn_801C8858(void*);
extern void fn_8002BDA0(void*, int);
extern void fn_8006C794(void*);
extern void fn_801C89B4(void*, void*, void*);
extern void fn_80119A88(void*, void*, int);
extern void* fn_800CFD18(void*, int);
extern u8* fn_800CFB0C(void*);
extern void fn_80126D9C(void*, int);
extern u8 fn_80120928(void*, void*);
extern BOOL fn_80089D68(int);
extern BOOL fn_80121DEC(void*);
extern void fn_801088DC(void*, void*, int);
extern void fn_80108948(void*, void*, int);
extern void fn_8010889C(void*, void*, int);
extern void fn_8002C06C(void*, int);
extern void fn_801C8ED0(void);
extern void* fn_80081194(void*, void*);
extern void fn_8010E41C(void*, int);
extern s16 fn_801237EC(void*);
extern BOOL fn_80108F68(void*);
extern void fn_8010904C(void*);
extern u8 fn_80109014(void*);
extern f32 fn_801072E4(void*);
extern void fn_800482F8(void*, void*);

#define HASTARGETS() (lbl_803E7320.n != 0)

BOOL fn_801C8380(u8* u, void* b);

BOOL fn_801C8434(void* a);

BOOL fn_801C8598(void* a);

BOOL fn_801C8C80(void* a, void* b);

BOOL fn_801C8E9C(void* a, void* b);

BOOL fn_801C8FB4(void* a, void* b);

BOOL fn_801C936C(void* a, void* b);

BOOL fn_801C9484(void* a, void* b);

BOOL fn_801C9A0C(void* a, void* b);

BOOL fn_801C9CCC(void* a, void* b);


#pragma use_lmw_stmw on
static inline int HealTo(u8* u, void* it) {
    int b = fn_80123998(u);
    return b + fn_801C8858(it);
}
static inline s16 HealTo2(u8* u, void* it) {
    s16 a = fn_80123998(u);
    return a + fn_801C8858(it);
}
int fn_801C8CB4(void* p);

int fn_801C8D70(void* p);

int fn_801C9A40(void* p);

#pragma use_lmw_stmw off

int fn_801C8F10(void* p);

#define STAT3(NAME, FN, K) \
int NAME(void* p) { \
    fn_80026C44(lbl_803C8E80, lbl_803CA870.unit, lbl_803CA870.x4); \
    fn_8002C0EC(lbl_803C8E80, (s8)lbl_803CA870.xE); \
    if (fn_80089D68(fn_80120928(lbl_803CA870.unit, lbl_803CA870.x4)) && !fn_80121DEC(lbl_803CA870.x4)) { \
        FN(lbl_803C8E80 + 0x5B0, lbl_803C8E80 + 0x4A0, K); \
        fn_8002C06C(lbl_803C8E80, 1); \
    } else { \
        fn_8002C06C(lbl_803C8E80, 0); \
    } \
    fn_8006C794(lbl_803C8E80); \
    fn_801C89B4(*fn_80044FD0(&lbl_803CA870), p, 0); \
    return 0; \
}

void* fn_801C94B8(void* p);

void* fn_801C9D00(void* p);

int fn_801C9D10(void* p);

static inline BOOL ModeOK(void) {
    BOOL t = 1;
    if (lbl_804CB830 != 1 && lbl_804CB830 != 2) t = 0;
    return t;
}
u8 fn_801C9DCC(void);

BOOL fn_801C9B18(void);

static inline u8* UnitAt(int id) {
    u8 i = id;
    if (i) return lbl_804CB810 + (i - 1) * 0x3F0;
    return 0;
}
#pragma use_lmw_stmw on

BOOL fn_801C97D0(void);

#pragma use_lmw_stmw off

void fn_801C9890(void);


extern u8 fn_801196F0x;
extern void* fn_8012759C(void*);
extern int fn_8012C250(void*, int);
extern int fn_8012C0A8(void*, int, int);
extern int fn_80111230(int);
extern void fn_8012C398(void*, int);
extern void fn_8012A7B8(void*, int);
extern void fn_80128D70(void*);
extern void fn_80031D8C(int, void*, int, int, int);
extern void fn_8010F4F0(void*, void*);
extern void fn_8010F598(void*);
extern char lbl_8036E3E0[];
extern u8 lbl_8038A990[];
extern u32 lbl_804CA4E8;
extern u32 lbl_804CA5C0;
extern s16 fn_80123288(void*), fn_80123318(void*), fn_801233A8(void*), fn_80123438(void*), fn_801234C8(void*), fn_80123558(void*), fn_801235E8(void*), fn_80123678(void*);
extern s8 fn_80123780(void*), fn_80123708(void*);
typedef struct ItemS { u8 pad[0x12]; u8 x12; } ItemS;
#pragma use_lmw_stmw on

BOOL fn_801C7404(u8* u, u8* it);

#pragma use_lmw_stmw off
static inline u8 ItT(ItemS* it) { return it ? it->x12 : 0x13; }
BOOL fn_801C7558(u8* u);

int fn_801C7668(void* p);

typedef struct Mask8 { u8 b; } Mask8;
BOOL fn_801C7988(u8* u, void* job);

#pragma use_lmw_stmw on
#pragma use_lmw_stmw off

extern void fn_8017F68C_(void);

typedef struct Vec3 { f32 x, y, z; } Vec3;
typedef struct Vec2 { f32 x, y; } Vec2;
extern void fn_8006625C(void*, int, int, int);
extern u8* fn_800661A0(void*, int, int, int, u8);
extern u8 fn_80110DA8(void*);
extern void fn_80065E4C(void*, int);
extern Vec3 fn_80118B94(void*, int, int);
extern void fn_802549C4(const char*, Vec3*, f32);
typedef struct BData2 { u8 pad[8]; s16 t; u8 pad0A[6]; int dir; u8 pad14[4]; f32 x18, x1C; u8 pad20[4]; f32 x, y; } BData2;
typedef struct BProc2 { u8 pad[0x30]; BData2* d; } BProc2;
extern f32 fn_8017F68C(int a, f32 x, f32 y, f32 t, f32 d);
extern void fn_80083B78(void*);
void fn_801C6830(BProc2* p);

extern u8 lbl_8038A8A8[];
typedef struct PA { u8 pad[0x34]; int x34, x38, x3C, x40; } PA;
PA* fn_801C6D2C(int a, void* parent, int b, int c, int d);

typedef struct GXC { u8 r, g, b, a; } GXC;
extern void fn_800800D4(int);
extern void fn_80080330(f32, f32);
extern u8* fn_800CD204(int);
extern void fn_80080508(GXC);
extern void fn_80080B00(int, void*, f32);
extern void fn_80080C24(const char*);
extern void fn_80080308(void);
void fn_801C6DA0(int col, const char* s, f32 x, f32 y);

extern char* strcpy(char*, const char*);
extern char* fn_80291110(char*, const char*);
extern BOOL fn_801D09F0(void);
extern u8* fn_80060728(void*);
extern char lbl_8036E118[];
void fn_801C6EAC(const char* a, const char* b, char* out);

}

/* ---- from rF_8017F400/wip/fn_801C6830.cpp ---- */
extern "C" {


BOOL fn_801C7110(u8* u, u8* it) {
    int a0, a1, a2, a3, a4, a5, a6, a7;
    s8 b7, b6, b5, b4, b3, b2, b1, b0;
    a0 = (s8)u[0x119]; a1 = (s8)u[0x11A]; a2 = (s8)u[0x11B]; a3 = (s8)u[0x11C]; a4 = (s8)u[0x11D]; a5 = (s8)u[0x11E]; a6 = (s8)u[0x11F]; a7 = (s8)u[0x120];
    b0 = a0 + it[0x22]; b1 = a1 + it[0x23]; b2 = a2 + it[0x24]; b3 = a3 + it[0x25]; b4 = a4 + it[0x26]; b5 = a5 + it[0x27]; b6 = a6 + it[0x28]; b7 = a7 + it[0x29];
    if (b0 > fn_80123288(u)) b0 = fn_80123288(u);
    if (b1 > fn_80123318(u)) b1 = fn_80123318(u);
    if (b2 > fn_801233A8(u)) b2 = fn_801233A8(u);
    if (b3 > fn_80123438(u)) b3 = fn_80123438(u);
    if (b4 > fn_801234C8(u)) b4 = fn_801234C8(u);
    if (b5 > fn_80123558(u)) b5 = fn_80123558(u);
    if (b6 > fn_801235E8(u)) b6 = fn_801235E8(u);
    if (b7 > fn_80123678(u)) b7 = fn_80123678(u);
    {
    BOOL same;
    if (a0 != b0) same = 0;
    else if (a1 != b1) same = 0;
    else if (a2 != b2) same = 0;
    else if (a4 != b4) same = 0;
    else if (a3 != b3) same = 0;
    else if (a5 != b5) same = 0;
    else if (a6 != b6) same = 0;
    else same = a7 == b7;
    return !same;
    }
}
}
