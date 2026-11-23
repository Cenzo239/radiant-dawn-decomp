#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off

/* Same stand-in statics as fn_80104ABC.cpp: the classes live in one data block at lbl_80385050. */
typedef struct Probe { u8 pad[0x30]; void* a; } Probe;

static u8 c000[0x20];
static u8 c020[0x20];
static u8 c040[0x20];
static u8 c060[0x18];
static u8 c078[0x30];
static u8 c0A8[0x28];
static u8 c0D0[0x28];
static u8 c0F8[0x28];
static u8 c120[0x28];
static u8 c148[0x30];
static u8 c178[0xC8];
static u8 c240[0xDC];
static u8 c31C[0x34];
static u8 c350[0x48];
static u8 c398[0x34];
static u8 c3CC[0x34];
static u8 c400[0x34];
static u8 c434[0x4C];
static u8 c480[0x48];
static u8 c4C8[0xB4];
static u8 c57C[0xAC];
static u8 c628[0x50];

extern "C" {
extern void* fn_800893E4(void*, void*, Probe*);
extern void fn_80104AA4(void* a, void* b);

static inline void* Has(u8* cls, void* u) {
    Probe s;
    s.a = u;
    return fn_800893E4(cls, fn_80104AA4, &s);
}
u32 fn_80104C2C(void* u) {
    if (Has(c000, u)) return 1;
    if (Has(c020, u)) return 1;
    if (Has(c078, u)) return 1;
    if (Has(c0A8, u)) return 1;
    if (Has(c0D0, u)) return 1;
    if (Has(c120, u)) return 1;
    if (Has(c0F8, u)) return 1;
    if (Has(c4C8, u)) return 1;
    if (Has(c148, u)) return 1;
    if (Has(c57C, u)) return 1;
    if (Has(c628, u)) return 1;
    if (Has(c240, u)) return 1;
    if (Has(c350, u)) return 1;
    if (Has(c31C, u)) return 1;
    if (Has(c434, u)) return 1;
    if (Has(c400, u)) return 1;
    if (Has(c3CC, u)) return 1;
    if (Has(c398, u)) return 1;
    return Has(c480, u) != 0;
}
}
