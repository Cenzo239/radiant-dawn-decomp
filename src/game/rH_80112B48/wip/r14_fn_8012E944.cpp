/* NOT MATCHING, not compiled. fn_8012E944 (7), fn_8012E9B4 (15): volatile read keeps the original's reload; pointer, offset and counter still rotate. */
/* Support links: index of a person in a support list, breaking links, 8012E944..8012F050. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
extern Unit* fn_8012CECC(void*);
struct SupEnt {
    void* person;
    u8 pad4[4];
};
struct SupData {
    u8 pad0[4];
    u32 n;
    SupEnt e[1];
};
#define SUPD(p) (*(SupData* volatile*)((u8*)(p) + 0xdc))
static inline u8 SupN(Person* p) { SupData* d = SUPD(p); if (d == 0) { return 0; } return d->n; }
static inline void* SupAt(Person* p, int i) { if (i < 0) return 0; return SUPD(p)->e[i].person; }
static inline s8 SupIdx(Person* p, void* who) {
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
s8 fn_8012E944(Unit* u, void* pid) {
    return SupIdx(u->person, pid);
}
s8 fn_8012E9B4(Unit* a, Unit* b) {
    return SupIdx(a->person, b->person);
}
}
