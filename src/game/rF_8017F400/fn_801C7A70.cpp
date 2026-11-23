#include "game/rF_8017F400/types.h"

#pragma auto_inline off

extern "C" {

/* current actor state for event commands */
typedef struct ActState {
    u8* unit;  /* 0x00 */
    u8 pad4[0xC - 4];
    u8 xC;
    u8 xD;
    u8 xE;
    u8 padF[0x13 - 0xF];
    u8 x13;
    u8 x14;
} ActState;

typedef struct BattleSys {
    u8 pad[0x110];
    u8 x110[0x15EC - 0x110];
    u32 flags; /* 0x15EC */
} BattleSys;

extern ActState lbl_803CA870;
extern BattleSys lbl_803C8E80;
extern char lbl_8036E500[];
extern char lbl_8036E538[];
extern u8 lbl_8038AA08[];
extern u8 lbl_8038AA20[];
extern u8 lbl_8038AA38[];
extern u8 lbl_804CB830;
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA4E8;
FE10_PROTO extern void *lbl_804CA4EC;
FE10_PROTO extern void *lbl_804CA5E0;
#else
extern int lbl_804CA4E8;
extern int lbl_804CA4EC;
extern int lbl_804CA5E0;
#endif
extern void fn_800A04C8(void* a, u8 b, int c, int d);
extern void fn_8012A7B8(u8* u, int a);
extern void fn_80076D48(const char* s, void* a);
extern s16 fn_801237EC(u8* u);
extern void fn_80026CD8(BattleSys* b, u8* u, int a);
#if TARGET_PC
extern FE10_PROTO void * fn_8010B228(const char* s);
#else
extern int fn_8010B228(const char* s);
#endif
#if TARGET_PC
extern FE10_PROTO s8 fn_801C8858(p32arg);
#else
extern s8 fn_801C8858(int a);
#endif
extern void fn_8002C270(BattleSys* b, int a, int c);
extern void fn_8002C394(BattleSys* b, int a, int c);
extern void fn_8002C474(BattleSys* b, int a);
#if TARGET_PC
extern FE10_PROTO void fn_800E7054(void* p, p32arg);
extern FE10_PROTO void fn_800E709C(void* p, p32arg);
extern FE10_PROTO void fn_800E70E4(void* p, p32arg);
extern FE10_PROTO void fn_800E712C(void* p, p32arg);
extern FE10_PROTO void fn_800E6F34(void* p, p32arg);
extern FE10_PROTO void fn_800E6F7C(void* p, p32arg);
extern FE10_PROTO void fn_800E6FC4(void* p, p32arg);
extern FE10_PROTO void fn_800E700C(void* p, p32arg);
extern FE10_PROTO void fn_800E73B0(void* p, p32arg);
#else
extern void fn_800E7054(void* p, int a);
extern void fn_800E709C(void* p, int a);
extern void fn_800E70E4(void* p, int a);
extern void fn_800E712C(void* p, int a);
extern void fn_800E6F34(void* p, int a);
extern void fn_800E6F7C(void* p, int a);
extern void fn_800E6FC4(void* p, int a);
extern void fn_800E700C(void* p, int a);
extern void fn_800E73B0(void* p, int a);
#endif
extern void fn_80194524(void* p);
#if TARGET_PC
extern FE10_PROTO int fn_8011B77C(u8* a, p32arg);
#else
extern int fn_8011B77C(u8* a, int b);
#endif
extern s8 fn_801284C4(u8* u);
extern void fn_80109068(void* p);
extern void fn_8010904C(void* p);
extern u8 fn_80108F68(void* p);
extern u8 fn_80109030(void* p);
extern u8 fn_80109014(void* p);
extern void fn_80108C80(void* p, void* b, int a);
extern void fn_80108CC0(void* p, void* b, int a);
#if TARGET_PC
extern FE10_PROTO p32ret fn_801038D0(u8* u, p32arg);
#else
extern u8 fn_801038D0(u8* u, int a);
#endif
extern u8 fn_801288D4(u8* u);
extern void* fn_80081194(void* cls, void* parent);

int fn_801C7A70(void* a) {
    s8 t;
    fn_800A04C8(a, lbl_803CA870.xC, (s8)lbl_803CA870.x13, (s8)lbl_803CA870.x14);
    t = lbl_803CA870.xE;
    if (t < 0) {
        return 1;
    }
    fn_8012A7B8(lbl_803CA870.unit, t);
    lbl_803C8E80.flags |= 0x2000;
    return 1;
}

void fn_801C7AF0(void) {
    fn_80076D48(lbl_8036E500, lbl_8038AA08);
    fn_80076D48(lbl_8036E500 + 0x14, lbl_8038AA08);
    fn_80076D48(lbl_8036E500 + 0x24, lbl_8038AA08);
}

static inline BOOL IsAbove(u8* u) {
    int v = *(s8*)(u + 0x114);
    return v < fn_801237EC(u);
}

BOOL fn_801C7B4C(u8* u) {
    return IsAbove(u);
}

int fn_801C7B94(void* p) {
    u8 e;
    fn_80026CD8(&lbl_803C8E80, lbl_803CA870.unit, -1);
    e = lbl_803CA870.xE;
    fn_8002C270(&lbl_803C8E80, (s8)e, fn_801C8858(fn_8010B228(lbl_8036E538)));
    fn_800E7054(p, 0);
    return 1;
}

BOOL fn_801C7C1C(u8* u) {
    return IsAbove(u);
}

int fn_801C7C64(void* p) {
    u8 e;
    fn_80026CD8(&lbl_803C8E80, lbl_803CA870.unit, -1);
    e = lbl_803CA870.xE;
    fn_8002C270(&lbl_803C8E80, (s8)e, fn_801C8858(fn_8010B228(lbl_8036E538 + 0x9)));
    fn_800E709C(p, 0);
    return 1;
}

BOOL fn_801C7CF0(u8* u) {
    return IsAbove(u);
}

int fn_801C7D38(void* p) {
    u8 e;
    fn_80026CD8(&lbl_803C8E80, lbl_803CA870.unit, -1);
    e = lbl_803CA870.xE;
    fn_8002C270(&lbl_803C8E80, (s8)e, fn_801C8858(fn_8010B228(lbl_8036E538 + 0x17)));
    fn_800E70E4(p, 0);
    return 1;
}

BOOL fn_801C7DC4(u8* u) {
    return IsAbove(u);
}

int fn_801C7E0C(void* p) {
    u8 e;
    fn_80026CD8(&lbl_803C8E80, lbl_803CA870.unit, -1);
    e = lbl_803CA870.xE;
    fn_8002C270(&lbl_803C8E80, (s8)e, fn_801C8858(fn_8010B228(lbl_8036E538 + 0x26)));
    fn_800E712C(p, 0);
    return 1;
}

BOOL fn_801C7E98(u8* u) {
    if (fn_8011B77C(u + 0x12C, lbl_804CA4E8) != 0) {
        return fn_801284C4(u) < 0x1E;
    }
    return FALSE;
}

int fn_801C7EFC(void* p) {
    u8 e;
    fn_80026CD8(&lbl_803C8E80, lbl_803CA870.unit, -1);
    e = lbl_803CA870.xE;
    fn_8002C394(&lbl_803C8E80, (s8)e, fn_801C8858(fn_8010B228(lbl_8036E538 + 0x31)));
    fn_800E6F34(p, 0);
    fn_80194524(p);
    return 1;
}

typedef struct UBits {
    u8 pad[0x110];
    u16 x : 3;
} UBits;

BOOL fn_801C7F90(UBits* u) {
    return u->x != 0;
}

int fn_801C7FA8(void* p) {
    fn_80026CD8(&lbl_803C8E80, lbl_803CA870.unit, -1);
    fn_8002C474(&lbl_803C8E80, (s8)lbl_803CA870.xE);
    fn_80109068(lbl_803C8E80.x110);
    fn_800E6F7C(p, 0);
    return 1;
}

u8 fn_801C8028(u8* u) {
    return fn_80108F68(u + 0x110);
}

int fn_801C8030(void* p) {
    fn_80026CD8(&lbl_803C8E80, lbl_803CA870.unit, -1);
    fn_8002C474(&lbl_803C8E80, (s8)lbl_803CA870.xE);
    fn_8010904C(lbl_803C8E80.x110);
    fn_800E6FC4(p, 0);
    return 1;
}

u8 fn_801C80B0(void) {
    return fn_80109030(lbl_803CA870.unit + 0x110);
}

int fn_801C80C0(void* p) {
    fn_80026CD8(&lbl_803C8E80, lbl_803CA870.unit, -1);
    fn_8002C474(&lbl_803C8E80, (s8)lbl_803CA870.xE);
    fn_80108C80(lbl_803C8E80.x110, &lbl_803C8E80, 7);
    fn_800E700C(p, 0);
    return 1;
}

static inline BOOL Is1(void) { return lbl_804CB830 == 1; }
static inline BOOL Is2(void) { return lbl_804CB830 == 2; }

static inline BOOL Check12(void) { return Is1() || Is2(); }

u8 fn_801C8144(void) {
    if (Check12() == FALSE) {
        return 0;
    } else {
        return fn_80109014(lbl_803CA870.unit + 0x110);
    }
}

int fn_801C8184(void* p) {
    fn_80026CD8(&lbl_803C8E80, lbl_803CA870.unit, -1);
    fn_8002C474(&lbl_803C8E80, (s8)lbl_803CA870.xE);
    fn_80108CC0(lbl_803C8E80.x110, &lbl_803C8E80, 4);
    fn_800E73B0(p, 0);
    return 1;
}

BOOL fn_801C8208(u8* u) {
    if (fn_8011B77C(u + 0x12C, lbl_804CA4E8) == 0) {
        return FALSE;
    }
    if (fn_8011B77C(u + 0x12C, lbl_804CA4EC) != 0) {
        return FALSE;
    }
    return fn_8011B77C(u + 0x12C, lbl_804CA5E0) == 0;
}

u8 fn_801C827C(int a) {
    return fn_801038D0(lbl_803CA870.unit, a);
}

u8 fn_801C828C(void) {
    return fn_801288D4(lbl_803CA870.unit);
}

int fn_801C8298(void* parent) {
    fn_8012A7B8(lbl_803CA870.unit, *(s8*)&lbl_803CA870.xE);
    lbl_803C8E80.flags |= 0x2000;
    fn_80081194(lbl_8038AA20, parent);
    return 1;
}

int fn_801C8318(void* parent) {
    fn_8012A7B8(lbl_803CA870.unit, *(s8*)&lbl_803CA870.xE);
    lbl_803C8E80.flags |= 0x2000;
    fn_80081194(lbl_8038AA38, parent);
    return 1;
}

}
