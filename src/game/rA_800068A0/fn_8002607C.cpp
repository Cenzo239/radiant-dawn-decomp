/* Text/pad command list (names guessed): a list of up to 511 4-byte entries
   {code, pad, value} with a count, a mark, a "current group" pointer and a
   layout mode that swaps two blocks of the code translation. */
#include "game/rA_800068A0/types.h"

struct Ent { u8 code; u8 x1; s16 val; };
struct Seq {
    s16 n;          /* 0x000 */
    s16 mark;       /* 0x002 */
    Ent e[0x1ff];   /* 0x004 */
    Ent* cur;       /* 0x800 */
    u8 mode;        /* 0x804 */
};

extern "C" {
/* Translates an input code: below 0x88 unchanged, 0x89..0x9A through one of
   two tables chosen by the mode, anything else 0. */
u32 fn_8002607C(Seq* s, u32 code) {
    if (code < 0x88) {
        return code;
    }
    if (s->mode == 0) {
        switch (code) {
        case 0x89: return 0x3;
        case 0x8a: return 0x4;
        case 0x8b: return 0x5;
        case 0x8c: return 0x6;
        case 0x8d: return 0x7;
        case 0x8e: return 0x8;
        case 0x8f: return 0x9;
        case 0x90: return 0xe;
        case 0x91: return 0xf;
        case 0x92: return 0x10;
        case 0x93: return 0x11;
        case 0x94: return 0x12;
        case 0x95: return 0x13;
        case 0x96: return 0x14;
        case 0x97: return 0x17;
        case 0x98: return 0x18;
        case 0x99: return 0x19;
        case 0x9a: return 0x1a;
        }
    } else {
        switch (code) {
        case 0x89: return 0xe;
        case 0x8a: return 0xf;
        case 0x8b: return 0x10;
        case 0x8c: return 0x11;
        case 0x8d: return 0x12;
        case 0x8e: return 0x13;
        case 0x8f: return 0x14;
        case 0x90: return 0x3;
        case 0x91: return 0x4;
        case 0x92: return 0x5;
        case 0x93: return 0x6;
        case 0x94: return 0x7;
        case 0x95: return 0x8;
        case 0x96: return 0x9;
        case 0x97: return 0x19;
        case 0x98: return 0x1a;
        case 0x99: return 0x17;
        case 0x9a: return 0x18;
        }
    }
    return 0;
}
}
