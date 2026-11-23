/*
 * fn_80063C30 (round 22, exact): trim a named-flag set. Clears name and hash of the used slots at the
 * top of the table (from slot 0x7F down to the first free one), then clears the value bit of every
 * free slot. The set is the 0x410-byte block at +0x144 of the global game data (names, hashes, bits).
 * The original unrolls the first loop four times and the second twice.
 */
#include "game/rC2_8005259C/base.h"
typedef int BOOL;
struct FlagSet {
    const char* names[0x80]; /* 0x000 */
    u32 hashes[0x80];        /* 0x200 */
    u8 bits[0x10];           /* 0x400 */
};
static inline BOOL slotUsed(FlagSet* t, int i)
{
    return i >= 0 && i < 0x80 && t->names[i] != 0;
}
static inline void clrBit(FlagSet* t, int i)
{
    if (i >= 0 && i < 0x80) {
        t->bits[i >> 3] &= ~(1 << (i & 7));
    }
}
extern "C" void fn_80063C30(FlagSet* t)
{
    int i;
    for (i = 0x7f; i >= 0; i--) {
        if (!slotUsed(t, i)) {
            break;
        }
        t->names[i] = 0;
        t->hashes[i] = 0;
    }
    for (i = 0; i < 0x80; i++) {
        if (!slotUsed(t, i)) {
            clrBit(t, i);
        }
    }
}
