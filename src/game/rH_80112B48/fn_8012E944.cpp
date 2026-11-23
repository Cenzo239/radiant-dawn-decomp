/* Support links: index of a person in a unit's support list, 8012E944 and 8012E9B4. */
#include "game/rH_80112B48/types.h"
extern "C" {
struct SupEnt {
    void* person;
    u8 pad4[4];
};
struct SupData {
    u8 pad0[4];
    u32 n;
    SupEnt e[1];
};
struct SPer {
    u8 pad0[0xdc];
    SupData* sup;
};
struct SUnit {
    u8 pad0[0xec];
    SPer* person;
};
/* The volatile read keeps the original's reload of the list pointer on every test;
   the original probably reached it some other way. */
static inline u8 SupN(volatile SPer* p) {
    SupData* d = p->sup;
    if (d == 0) {
        return 0;
    }
    return d->n;
}
static inline void* SupAt(const SPer* p, int i) {
    if (i < 0) return 0;
    return p->sup->e[i].person;
}
static inline s8 SupIdx(SPer* const& p, void* who) {
    s8 r = -1;
    int i;
    for (i = 0; i < SupN(p); i++) {
        if (SupAt(p, i) == who) {
            r = i;
            break;
        }
    }
    return r;
}
s8 fn_8012E944(SUnit* u, void* pid) {
    s8 r = -1;
    int i;
    for (i = 0; i < SupN(u->person); i++) {
        if (SupAt(u->person, i) == pid) {
            r = i;
            break;
        }
    }
    return r;
}
s8 fn_8012E9B4(SUnit* a, SUnit* b) {
    return SupIdx(a->person, b->person);
}
}
