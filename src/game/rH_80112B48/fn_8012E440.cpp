/* Bits and growth, 8012E440, 8012E618, 8012EC2C. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off

extern "C" {
extern u8* fn_8010B250(int);
static inline void BitSet(u32* p, u32 k) {
    while (k >= 32) {
        k -= 32;
        p++;
    }
    *p |= 1 << k;
}

static inline void BitSetI(u32* p, int k) {
    if (k >= 0) {
        BitSet(p, k);
    }
}

static inline BOOL BitTest(u32* p, u32 k) {
    while (k >= 32) {
        k -= 32;
        p++;
    }
    return (*p & (1 << k)) != 0;
}

static inline BOOL BitTestI(u32* p, int k) {
    if (k < 0) {
        return 0;
    }
    return BitTest(p, k);
}

void fn_8012E440(Unit* u, int k, int i) {
    if (k >= 0) {
        switch (i) {
        case 3:
            BitSetI((u32*)((u8*)u + 0x34c), k);
            break;
        case 2:
            BitSetI((u32*)((u8*)u + 0x35c), k);
            break;
        case 1:
            BitSetI((u32*)((u8*)u + 0x36c), k);
            break;
        }
    }
}

BOOL fn_8012E618(Unit* u, int k, int i) {
    BOOL r;
    if (k < 0) {
        return 0;
    }
    r = 0;
    switch (i) {
    case 3:
        r = BitTestI((u32*)((u8*)u + 0x34c), k);
        break;
    case 2:
        r = BitTestI((u32*)((u8*)u + 0x35c), k);
        break;
    case 1:
        r = BitTestI((u32*)((u8*)u + 0x36c), k);
        break;
    }
    return r;
}


static inline s8 Kk(Unit* u) { if (*(s8*)&u->u118 == -1) { return *((s8*)u->person + 0xe1); } return *(s8*)&u->u118; }
void fn_8012EC2C(Unit* u, int n, u8* o) {
    
    u8* c = fn_8010B250((u8)Kk(u));
    o[4] += n * c[4];
    o[5] += n * c[5];
    o[6] += n * c[6];
    o[7] += n * c[7];
    o[8] += n * c[8];
    o[9] += n * c[9];
}
}
