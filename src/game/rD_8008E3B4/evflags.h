#ifndef RD_8008E3B4_EVFLAGS_H
#define RD_8008E3B4_EVFLAGS_H

/* Global flag table inlines shared by the event files. Names are guesses. */

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

/* Takes the name by const reference: keeps the string above the index. */
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

/* Hash and walker ranked by the caller's declaration order. */
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

static inline BOOL flagGet(FlagTable* t, const char* const& name)
{
    if (name[0] == 0) {
        return 0;
    }
    return flagGetBit(t, flagFind(t, name));
}

/* The name ranks below the index and walker, by the caller's locals. */
#define FLAG_GET_R(r, q, name, h, i)                 \
    if (*(name) == 0) {                              \
        r = 0;                                       \
    } else {                                         \
        i = flagFindR(q, name, h);                   \
        r = flagGetBit(&lbl_803CAB38, i);            \
    }

static inline BOOL flagHas(FlagTable* t, const char* const& name)
{
    if (name[0] == 0) {
        return 0;
    }
    return flagFind(t, name) >= 0;
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

}

#endif
