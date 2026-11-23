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
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA504;
#else
extern u8 lbl_804CA504[4];
#endif
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
#if TARGET_PC
extern FE10_PROTO BOOL fn_8011B77C(void*, p32arg);
#else
extern BOOL fn_8011B77C(void*, u32);
#endif
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
#if TARGET_PC
extern FE10_PROTO void fn_801C89B4(void*, void*, ptr32<const void>);
#else
extern void fn_801C89B4(void*, void*, void*);
#endif
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
BOOL fn_801C8380(u8* u, void* b) {
    if (fn_8011B77C(u + 0x12C, *(u32*)lbl_804CA504)) return 0;
    fn_80039AE4(u, b);
    return HASTARGETS();
}
BOOL fn_801C8434(void* a) { fn_8003B3DC(a, 0xC); return HASTARGETS(); }
BOOL fn_801C8598(void* a) { fn_8003B3DC(a, 0xD); return HASTARGETS(); }
BOOL fn_801C8C80(void* a, void* b) { fn_8003A3BC(a, b); return HASTARGETS(); }
BOOL fn_801C8E9C(void* a, void* b) { fn_8003A664(a, b); return HASTARGETS(); }
BOOL fn_801C8FB4(void* a, void* b) { fn_8003A7B8(a, b); return HASTARGETS(); }
BOOL fn_801C936C(void* a, void* b) { fn_8003A90C(a, b); return HASTARGETS(); }
BOOL fn_801C9484(void* a, void* b) { fn_8003AFF8(a, b); return HASTARGETS(); }
BOOL fn_801C9A0C(void* a, void* b) { fn_8003A510(a, b); return HASTARGETS(); }
BOOL fn_801C9CCC(void* a, void* b) { fn_8003B04C(a, b); return HASTARGETS(); }

#pragma use_lmw_stmw on
static inline int HealTo(u8* u, void* it) {
    int b = fn_80123998(u);
    return b + fn_801C8858(it);
}
static inline s16 HealTo2(u8* u, void* it) {
    s16 a = fn_80123998(u);
    return a + fn_801C8858(it);
}
int fn_801C8CB4(void* p) {
    u8* u;
    void* it;
    int a;
    fn_80026C44(lbl_803C8E80, lbl_803CA870.unit, lbl_803CA870.x4);
    fn_8002C0EC(lbl_803C8E80, (s8)lbl_803CA870.xE);
    u = lbl_803CA870.unit;
    it = *fn_80044FD0(&lbl_803CA870);
    a = fn_80123998(u);
    fn_8002BDA0(lbl_803C8E80, (s16)(int)((char*)fn_801C8858(it) + a));
    fn_8006C794(lbl_803C8E80);
    fn_801C89B4(*fn_80044FD0(&lbl_803CA870), p, 0);
    fn_80119A88(lbl_803CA870.unit, lbl_803CA870.x4, 3);
    return 0;
}
int fn_801C8D70(void* p) {
    u8* u = lbl_803CA870.unit;
    void* it = *fn_80044FD0(&lbl_803CA870);
    int h = (s16)fn_80123998(u);
    int b = fn_801C8858(it);
    int v = b + h;
    int i;
    int k;
    fn_8003A3BC(u, it);
    for (i = 0; i < lbl_803E7320.n; i++) {
        u8* t = fn_800CFB0C(fn_800CFD18(&lbl_803E7320, i));
        fn_80126D9C(t, v + *(s8*)(t + 0x114));
    }
    fn_80026CD8(lbl_803C8E80, lbl_803CA870.unit, -1);
    fn_8002C0EC(lbl_803C8E80, (s8)lbl_803CA870.xE);
    fn_8006C794(lbl_803C8E80);
    fn_801C89B4(*fn_80044FD0(&lbl_803CA870), p, 0);
    for (k = 0; k < lbl_803E7320.n; k++) {
        u8* a = lbl_803CA870.unit;
        fn_80119A88(a, fn_800CFB0C(fn_800CFD18(&lbl_803E7320, k)), 3);
    }
    return 0;
}
int fn_801C9A40(void* p) {
    u8* u;
    void* it;
    int a;
    fn_80026C44(lbl_803C8E80, lbl_803CA870.unit, lbl_803CA870.x4);
    fn_8002C0EC(lbl_803C8E80, (s8)lbl_803CA870.xE);
    u = lbl_803CA870.unit;
    it = *fn_80044FD0(&lbl_803CA870);
    a = fn_80123998(u);
    fn_8002BDA0(lbl_803C8E80, (s16)(int)((char*)fn_801C8858(it) + a));
    fn_8006C794(lbl_803C8E80);
    *(s16*)(lbl_803CA870.x4 + 0x37C) = fn_801072E4(lbl_803CA870.x4);
    fn_801C89B4(*fn_80044FD0(&lbl_803CA870), p, 0);
    fn_80119A88(lbl_803CA870.unit, lbl_803CA870.x4, 3);
    return 1;
}
#pragma use_lmw_stmw off
int fn_801C8F10(void* p) {
    fn_80026C44(lbl_803C8E80, lbl_803CA870.unit, lbl_803CA870.x4);
    fn_8002C0EC(lbl_803C8E80, (s8)lbl_803CA870.xE);
    fn_8006C794(lbl_803C8E80);
    fn_801C89B4(*fn_80044FD0(&lbl_803CA870), p, (void*)fn_801C8ED0);
    fn_80119A88(lbl_803CA870.unit, lbl_803CA870.x4, 3);
    return 0;
}
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
STAT3(fn_801C8FE8, fn_801088DC, 5)
STAT3(fn_801C90E0, fn_80108948, 5)
STAT3(fn_801C91D8, fn_8010889C, 0)
void* fn_801C94B8(void* p) { return fn_80081194(lbl_8038AB70, p); }
void* fn_801C9D00(void* p) { return fn_80081194(lbl_8038AB9C, p); }
int fn_801C9D10(void* p) {
    u8* s = lbl_803CA870.x4 + lbl_803CA870.x18 * 0x28;
    u8* it = *(u8**)(s + 0x1BC);
    u8 v;
    if (it) v = it[0x1B]; else v = 0;
    s[0x1C0] = v;
    fn_80026C44(lbl_803C8E80, lbl_803CA870.unit, lbl_803CA870.x4);
    fn_8002C0EC(lbl_803C8E80, (s8)lbl_803CA870.xE);
    fn_8006C794(lbl_803C8E80);
    fn_801C89B4(*fn_80044FD0(&lbl_803CA870), p, 0);
    return 0;
}
static inline BOOL ModeOK(void) {
    BOOL t = 1;
    if (lbl_804CB830 != 1 && lbl_804CB830 != 2) t = 0;
    return t;
}
u8 fn_801C9DCC(void) {
    if (ModeOK() == 0) return 0;
    return fn_80109014(lbl_803CA870.unit + 0x110);
}
BOOL fn_801C9B18(void) {
    u8 c[4];
    u8 d[4];
    c[0] = 0x43;
    fn_800482F8(&lbl_803CA870, c);
    d[0] = lbl_803CA870.x17;
    fn_8003AA60(lbl_803CA870.unit, d);
    return HASTARGETS();
}
static inline u8* UnitAt(int id) {
    u8 i = id;
    if (i) return lbl_804CB810 + (i - 1) * 0x3F0;
    return 0;
}
#pragma use_lmw_stmw on
BOOL fn_801C97D0(void) {
    u8 m[0x10];
    u8* mm;
    u8* u;
    int hp;
    int r = 0;
    int i;
    fn_8010E41C(m, 2);
    for (i = 1; i <= 0xFE; i++) {
        u = UnitAt(i);
        if (*(int*)(u + 0xEC) && m[*(u8*)(*(u8**)(u + 0xF4) + 8)]) {
            hp = *(s8*)(u + 0x114);
            if (hp < fn_801237EC(u) || fn_80108F68(u + 0x110)) {
                r = 1;
                break;
            }
        }
    }
    return r;
}
#pragma use_lmw_stmw off
void fn_801C9890(void) {
    u8 m[0x14];
    int i;
    fn_8010E41C(m, 2);
    for (i = 1; i <= 0xFE; i++) {
        u8* u = UnitAt(i);
        if (*(int*)(u + 0xEC) && m[*(u8*)(*(u8**)(u + 0xF4) + 8)]) {
            fn_80126D9C(u, fn_801237EC(u));
            fn_8010904C(u + 0x110);
            fn_80119A88(lbl_803CA870.unit, u, 3);
        }
    }
    fn_80126D9C(lbl_803C8E80, fn_801237EC(lbl_803C8E80));
    fn_8010904C(lbl_803C8E80 + 0x110);
}

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
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA4E8;
FE10_PROTO extern void *lbl_804CA5C0;
#else
extern u32 lbl_804CA4E8;
extern u32 lbl_804CA5C0;
#endif
extern s16 fn_80123288(void*), fn_80123318(void*), fn_801233A8(void*), fn_80123438(void*), fn_801234C8(void*), fn_80123558(void*), fn_801235E8(void*), fn_80123678(void*);
extern s8 fn_80123780(void*), fn_80123708(void*);
typedef struct ItemS { u8 pad[0x12]; u8 x12; } ItemS;
#pragma use_lmw_stmw on
BOOL fn_801C7404(u8* u, u8* it) {
    u8 a = u[0x116];
    u8 b = u[0x115];
    s8 c = a + it[0x2A];
    s8 d = b + it[0x2B];
    if (c > fn_80123780(u)) c = fn_80123780(u);
    if (d > fn_80123708(u)) d = fn_80123708(u);
    if (c == (s8)a && d == (s8)b) return 0;
    return 1;
}
#pragma use_lmw_stmw off
static inline u8 ItT(ItemS* it) { return it ? it->x12 : 0x13; }
BOOL fn_801C7558(u8* u) {
    ItemS** s = (ItemS**)fn_8012759C(u);
    if (fn_8011B77C(u + 0x12C, lbl_804CA4E8)) return 0;
    if (s == NULL || *s == NULL) return 0;
    if (ItT(*s) >= 0xC) return 0;
    {
    int a = fn_8012C250(u, ItT(*s));
    int b = fn_8012C0A8(u, ItT(*s), 0x14B);
    int pa = fn_80111230((s16)a);
    int pb = fn_80111230((s16)b);
    if ((s16)pa == (s16)pb) return 0;
    return 1;
    }
}
int fn_801C7668(void* p) {
    u8* u = lbl_803CA870.unit;
    ItemS** s = (ItemS**)fn_8012759C(u);
    fn_8012C398(u, ItT(*s));
    fn_8012A7B8(u, *(s8*)&lbl_803CA870.xE);
    *(u32*)(lbl_803C8E80 + 0x15EC) |= 0x2000;
    if (fn_8011B77C(u + 0x12C, lbl_804CA4E8)) fn_80128D70(u);
    fn_80031D8C((s8)ItT(*s), p, -1, -1, -1);
    return 1;
}
typedef struct Mask8 { u8 b; } Mask8;
BOOL fn_801C7988(u8* u, void* job) {
    Mask8 m[4];
    Mask8 d[4];
    fn_8010F4F0(m, job);
    if (fn_8011B77C(u + 0x12C, lbl_804CA5C0)) fn_8010F598(m);
    d[0].b = m[0].b;
    fn_8003AA60(u, d);
    if (lbl_803E7320.n) return 1;
    return 0;
}
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
void fn_801C6830(BProc2* p) {
    BData2* d = p->d;
    d->t--;
    if (d->dir == 1) {
        d->x1C = fn_8017F68C(4, 0.0f, -100.0f, 7 - d->t, 7.0f);
        d->y = 170.0f;
    } else {
        d->x1C = fn_8017F68C(4, 0.0f, 100.0f, 7 - d->t, 7.0f);
        d->y = 170.0f;
    }
    d->x18 = 0.0f;
    d->x = 16.0f;
    if (d->t <= 0) fn_80083B78(p);
}
extern u8 lbl_8038A8A8[];
typedef struct PA { u8 pad[0x34]; int x34, x38, x3C, x40; } PA;
PA* fn_801C6D2C(int a, void* parent, int b, int c, int d) {
    PA* r = (PA*)fn_80081194(lbl_8038A8A8, parent);
    r->x38 = a;
    r->x34 = b;
    r->x3C = c;
    r->x40 = d;
    return r;
}
typedef struct GXC { u8 r, g, b, a; } GXC;
extern void fn_800800D4(int);
extern void fn_80080330(f32, f32);
extern u8* fn_800CD204(int);
extern void fn_80080508(GXC);
extern void fn_80080B00(int, void*, f32);
extern void fn_80080C24(const char*);
extern void fn_80080308(void);
void fn_801C6DA0(int col, const char* s, f32 x, f32 y) {
    fn_800800D4(5);
    fn_80080330(x, y);
    fn_80080508(*(GXC*)fn_800CD204((u8)col));
    fn_80080B00(1, fn_800CD204(0x2A), 1.0f);
    fn_80080C24(s);
    fn_80080308();
}
extern char* strcpy(char*, const char*);
extern char* fn_80291110(char*, const char*);
extern BOOL fn_801D09F0(void);
extern u8* fn_80060728(void*);
extern char lbl_8036E118[];
void fn_801C6EAC(const char* a, const char* b, char* out) {
    char buf[0x80];
    fn_80060728(lbl_803CAB38);
    strcpy(buf, a);
    fn_80291110(buf, lbl_8036E118 + 0x2BC);
    if (fn_801D09F0()) fn_80291110(buf, lbl_8036E118 + 0x2C0);
    fn_80291110(buf, b);
    strcpy(out, buf);
}
}
