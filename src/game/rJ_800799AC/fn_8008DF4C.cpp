/* Army checks (names guessed): fn_8008DF4C is true when no unit of teams 0
   and 5 lacks flag 0x4000 (e.g. everyone has moved or is gone);
   fn_8008E07C counts the units of teams 0 and 5 that have it. */
#include "game/rJ_800799AC/types.h"

extern "C" void* memset(void*, int, u32);

struct Unit {
    u8 pad0[0xec];
    void* person;   /* 0xEC */
    void* job;      /* 0xF0 */
    u8* team;       /* 0xF4 */
    u8 padF8[0x10c - 0xf8];
    u32 flags10C;   /* 0x10C */
    u8 pad110[0x3f0 - 0x110];
};
extern "C" Unit* lbl_804CB810;
extern "C" int lbl_804CA448;

static inline Unit* UnitGet(int id) {
    id = (u8)id;
    if (id) {
        return &lbl_804CB810[id - 1];
    }
    return 0;
}

struct TeamMask {
    u8 m[11];
    TeamMask(const u8* list) {
        const u8* p;
        memset(m, (u8)lbl_804CA448, 11);
        for (p = list; *p != 0xff; p++) {
            m[*p] = 1;
        }
    }
    bool has(Unit* u) const { return m[u->team[8]]; }
};

extern "C" {
int fn_8008DF4C(void) {
    u8 list[3] = { 0, 5, 0xff };
    TeamMask mask(list);
    int i;
    for (i = 1; i < 0xff; i++) {
        Unit* u = UnitGet(i);
        if (u->person != NULL && mask.has(u) && !(u->flags10C & 0x4000)) {
            return 0;
        }
    }
    return 1;
}

int fn_8008E07C(void) {
    int n = 0;
    u8 list[3] = { 0, 5, 0xff };
    TeamMask mask(list);
    int i;
    for (i = 1; i < 0xff; i++) {
        Unit* u = UnitGet(i);
        if (u->person != NULL && mask.has(u) && (u->flags10C & 0x4000)) {
            n++;
        }
    }
    return n;
}
}
