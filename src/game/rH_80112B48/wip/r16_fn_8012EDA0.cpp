/* NOT MATCHING, not compiled. fn_8012EDA0: 15 of 87 words, volatile registers only (result flag and offset swapped in the first SupIdx, counter and result in the second). Structure, the volatile list reload and the SupIdx shape all match. */
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
    u8 padF0[0x2fc - 0xf0];
    SPer* pair;
    u8 sup[0x48];
};
extern SUnit* fn_8012CECC(void*);
static inline u8 SupN(volatile SPer* p) { SupData* d = p->sup; if (d == 0) { return 0; } return d->n; }
static inline void* SupAt(const SPer* p, int i) { if (i < 0) return 0; return p->sup->e[i].person; }
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
static inline void Clr(SUnit* u, int a, SUnit* o, int b) { if (a >= 0) u->sup[a] = 0; if (b >= 0) o->sup[b] = 0; }
void fn_8012EDA0(SUnit* u, void* pid) {
    /*P*/
    s8 a;
    s8 b;
    SPer* up;
    SPer* op;
/*E*/
    SUnit* o = fn_8012CECC(pid);
    if (u->person->sup) {
        if (u->pair == o->person) {
            u->pair = 0;
            o->pair = 0;
        }
        op = o->person;
        up = u->person;
        a = SupIdx(up, op);
        b = SupIdx(op, up);
        if (a >= 0) u->sup[a] = 0;
        if (b >= 0) o->sup[b] = 0;
    }
}
}
