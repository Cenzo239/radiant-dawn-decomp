/*
 * fn_80093084 (round 22, exact): story-flag lookup by name. Returns the flag bit of `name` in
 * the flag table lbl_803CAB38, 0 for an empty name or an unknown flag.
 * The name parameter is a plain `char*`: with `const char*` (old wip in wip/fn_80092E10.cpp)
 * the `lbz` of name[0] is scheduled before the register saves (7 words off).
 * Helpers are the same inlines as in fn_80092D04.cpp.
 */
#include "game/rD_8008E3B4/types.h"

extern "C" {

typedef struct FlagTable {
    u8 pad0[0x10];
    u8 b10;             /* 0x10 */
    u8 b11;             /* 0x11: difficulty / mode */
    u8 pad12[0x144 - 0x12];
    char* names[0x80];  /* 0x144 */
    u32 hashes[0x80];   /* 0x344 */
    u8 bits[0x10];      /* 0x544 */
    u8 pad554[0x988 - 0x554];
} FlagTable;

extern FlagTable lbl_803CAB38;
u32 fn_80076D18(const char* s);                /* string hash */
int fn_80291188(const char* a, const char* b); /* strcmp */

static inline int flagFind(FlagTable* t, char* name)
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

BOOL fn_80093084(char* name)
{
    if (*name == '\0') {
        return 0;
    }
    return flagGetBit(&lbl_803CAB38, flagFind(&lbl_803CAB38, name));
}

}
