/* EQUIVALENT (register-only, round 19): fn_8009EEEC and fn_8009F1A8 at regs level (22 words each, volatile registers in the unit loop). evAny and clearUnitFlags were rewritten in round 19 (the round 12 copies were lost). */
/* Event triggers: 0x8009E900..0x8009F630. */
#include "game/rD_8008E3B4/types.h"

extern "C" {

typedef struct FlagTable {
    u8 pad0[0x11];
    u8 b11;             /* 0x11 */
    s16 s12;            /* 0x12 */
    u8 pad14[0x144 - 0x14];
    char* names[0x80];  /* 0x144 */
    u32 hashes[0x80];   /* 0x344 */
    u8 bits[0x10];      /* 0x544 */
    u8 pad554[0x988 - 0x554];
} FlagTable;

extern FlagTable lbl_803CAB38;
u32 fn_80076D18(const char* s);        /* string hash */
int fn_80291188(const char* a, const char* b); /* strcmp */

extern u32 lbl_804CB700;
extern u8* lbl_804CB810;
extern char lbl_80364B30[];
extern u8 lbl_80381B80[];
extern u8 lbl_80381BD4[];
extern u8 lbl_803C8DA0[];
extern u8 lbl_803C8E80[];
extern u8 lbl_803E50B0[];
extern u8 lbl_803EC898[];

u8* fn_800C3558(void);
int fn_800C357C(void);
u8* fn_800C3BC8(void* p);
void* fn_80081194(void* cls, void* parent);
void fn_801D0D58(void* ctx, void* p);
void fn_801D0E18(void* ctx);
void fn_80081A90(void* p);
void fn_80083B78(void* p);
char* fn_8009D948(void* p, int ofs);
int fn_8009EB54(u8* p);
void* fn_8010B1D8(void* x);
void* fn_8002C590(void* x);
void fn_8013F204(void);
void fn_801856F4(void);
void fn_8010E41C(u8* mask, int k);
void fn_80114D00(void* map);
void fn_8010E7F4(void* p, int k);
void fn_8008D75C(void);
int fn_8009394C(void);
u8* fn_80060728(void* p);
char* fn_80118DE8(void* pid);
void* fn_8011906C(void* pid);
void* fn_80076F54(void* p);
int fn_80290D04(char* buf, int n, const char* fmt, ...);
void fn_8014BED4(void* ctx, void* p);

typedef int (*EvCond)(u8*);
typedef struct EvProc {
    u8 pad0[0x30];
    u8* cur;     /* 0x30 */
    int kind;    /* 0x34 */
    EvCond cond; /* 0x38 */
} EvProc;

static inline int flagFind(FlagTable* t, const char* const& name)
{
    u32 h = fn_80076D18(name);
    int i;
    for (i = 0; i < 0x80; i++) {
        if (h == t->hashes[i] && fn_80291188(t->names[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

static inline BOOL flagSlotUsed(FlagTable* t, int i)
{
    return i >= 0 && i < 0x80 && t->names[i] != NULL;
}

static inline void flagClearBit(FlagTable* t, int i)
{
    if (i >= 0 && i < 0x80) {
        t->bits[i >> 3] &= ~(1 << (i & 7));
    }
}

static inline void flagRegist(char* name)
{
    int i;
    if (flagFind(&lbl_803CAB38, name) < 0) {
        for (i = 0; i < 0x80; i++) {
            if (!flagSlotUsed(&lbl_803CAB38, i)) {
                lbl_803CAB38.names[i] = name;
                lbl_803CAB38.hashes[i] = fn_80076D18(name);
                flagClearBit(&lbl_803CAB38, i);
                break;
            }
        }
    }
}

static inline BOOL flagTestBit(FlagTable* t, int i)
{
    if (i < 0 || i >= 0x80) {
        return 0;
    }
    return (t->bits[i >> 3] & (1 << (i & 7))) != 0;
}

static inline BOOL flagGetBit(FlagTable* t, int i)
{
    if (i < 0 || i >= 0x80) {
        return 0;
    }
    return flagTestBit(t, i);
}

static inline BOOL flagGet(FlagTable* t, const char* name)
{
    if (name[0] == 0) {
        return 0;
    }
    return flagGetBit(t, flagFind(t, name));
}

static inline void flagSetBit3(FlagTable* t, int i)
{
    if (i < 0 || i >= 0x80) {
        return;
    }
    t->bits[i >> 3] |= (1 << (i & 7));
}

static inline void flagSetBit2(FlagTable* t, int i)
{
    if (i < 0 || i >= 0x80) {
        return;
    }
    flagSetBit3(t, i);
}

static inline void flagSetBit(FlagTable* t, int i)
{
    if (i < 0 || i >= 0x80) {
        return;
    }
    flagSetBit2(t, i);
}

static inline void flagClrBit3(FlagTable* t, int i)
{
    if (i < 0 || i >= 0x80) {
        return;
    }
    t->bits[i >> 3] &= ~(1 << (i & 7));
}

static inline void flagClrBit2(FlagTable* t, int i)
{
    if (i < 0) {
        return;
    }
    flagClrBit3(t, i);
}

static inline void flagClrBit(FlagTable* t, int i)
{
    if (i < 0 || i >= 0x80) {
        return;
    }
    flagClrBit2(t, i);
}

static inline int flagFindV(FlagTable* t, const char* name)
{
    u32 h = fn_80076D18(name);
    int i;
    for (i = 0; i < 0x80; i++) {
        if (h == t->hashes[i] && fn_80291188(t->names[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

static inline int flagFindR(FlagTable*& q, const char* name, u32& h)
{
    int k;
    h = fn_80076D18(name);
    q = &lbl_803CAB38;
    for (k = 0; k < 0x80; k++, q = (FlagTable*)((u32*)q + 1)) {
        if (h == q->hashes[0] && fn_80291188(q->names[0], name) == 0) {
            return k;
        }
    }
    return -1;
}

struct RunBits { u32 pad : 29; u32 b4 : 1; u32 b2 : 1; u32 b1 : 1; };

#pragma push
#pragma use_lmw_stmw on

void fn_8009E900(EvProc* e);

#pragma pop

static inline BOOL evCheck(u8* p)
{
    s16 m = *(s16*)(p + 0x18);
    if (m >= 0 && m != lbl_803CAB38.b11) {
        return 0;
    }
    if (*(s16*)(p + 0x14) == 0) {
        return 1;
    }
    if (*(s16*)(p + 0x14) > lbl_803CAB38.s12) {
        return 0;
    }
    return *(s16*)(p + 0x16) >= lbl_803CAB38.s12;
}

static inline int evRun(void* parent, int kind, EvCond c)
{
    EvProc* q;
    lbl_803E50B0[0xa] = 0;
    q = (EvProc*)fn_80081194(lbl_80381BD4, parent);
    q->kind = kind;
    q->cond = c;
    return 1;
}
int fn_8009EBC4(void* parent);

int fn_8009ECD8(void* parent);


#pragma push
#pragma auto_inline off

int fn_8009EDEC(u8* p);

#pragma pop

#pragma push
#pragma use_lmw_stmw on
#pragma pop

int fn_8009F390(u8* p);


static inline BOOL evAny2(int kind)
{
    u8* p = fn_800C3BC8(NULL);
    while (p != NULL) {
        if ((int)p[0xc] == kind && fn_8009F390(p)) {
            return 1;
        }
        p = fn_800C3BC8(p);
    }
    return 0;
}
int fn_8009F3F0(void* parent);


#pragma push
#pragma use_lmw_stmw on

int fn_8009F630(void* ctx);

#pragma pop

}

/* ---- from build/tmp/r19hpbs/frag_eeec.cpp ---- */
extern "C" {
static inline BOOL evAny(int kind)
{
    u8* p = fn_800C3BC8(NULL);
    while (p != NULL) {
        if ((int)p[0xc] == kind && fn_8009EDEC(p)) {
            return 1;
        }
        p = fn_800C3BC8(p);
    }
    return 0;
}
static inline u8* unitAt(int i)
{
    int z = (u8)i;
    if (z) {
        return lbl_804CB810 + (z - 1) * 0x3f0;
    }
    return NULL;
}
/* Clear flag bits 0 and 11 on every unit of the sides in mask 5. */
static inline void clearUnitFlags(void)
{
    u8 mask[0x10];
    int i;
    fn_8010E41C(mask, 5);
    for (i = 1; i < 0xff; i++) {
        u8* u = unitAt(i);
        if (*(void**)(u + 0xec) && mask[(*(u8**)(u + 0xf4))[8]]) {
            *(u64*)(u + 0x108) &= ~1ULL;
            *(u64*)(u + 0x108) &= ~0x800ULL;
        }
    }
}
#pragma push
#pragma use_lmw_stmw on
int fn_8009EEEC(void* parent)
{
    if (!evAny(1)) {
        return 0;
    }
    if (flagGet(&lbl_803CAB38, lbl_80364B30 + 0x23)) {
        return 0;
    }
    fn_8013F204();
    fn_801856F4();
    clearUnitFlags();
    fn_80114D00(lbl_803EC898);
    fn_8010E7F4((u8*)&lbl_803CAB38 + 0x134, 0);
    fn_8010E7F4((u8*)&lbl_803CAB38 + 0x13c, 3);
    fn_8008D75C();
    return evRun(parent, 1, fn_8009EDEC);
}

#pragma pop
/* fn_8009F1A8 (from ../fn_8009E900.cpp): 22 of 122 words: same unit loop as fn_8009EEEC. */
int fn_8009F1A8(void* parent)
{
    if (!evAny(2)) {
        return 0;
    }
    fn_8013F204();
    fn_801856F4();
    clearUnitFlags();
    fn_80114D00(lbl_803EC898);
    fn_8010E7F4((u8*)&lbl_803CAB38 + 0x134, 0);
    fn_8010E7F4((u8*)&lbl_803CAB38 + 0x13c, 3);
    return evRun(parent, 2, fn_8009EDEC);
}
}
