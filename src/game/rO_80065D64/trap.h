#ifndef RO_TRAP_H
#define RO_TRAP_H
#include "game/rO_80065D64/types.h"
#include "game/rO_80065D64/unit.h"
#include "game/rO_80065D64/map.h"

/* Map object ("trap") entry: 8 bytes, array of 0x80 in TrapList.traps. */
struct Trap {
    s8 x;       /* 0 */
    s8 y;       /* 1 */
    u8 type;    /* 2 */
    s8 ext;     /* 3 */
    u8 d[4];    /* 4: type specific; d[2]/d[3] hold an actor handle */
};

struct TrapList {
    Trap* traps;  /* 0 */
    int n;        /* 4 */
    char* strs;   /* 8: string pool, 0x200 bytes */
    int strn;     /* C */
};

extern TrapList lbl_803CB770;
extern Map lbl_803EC898;
extern char lbl_803621A8[];

static inline Trap* At(TrapList* l, int i) {
    return &l->traps[i];
}
#endif
