/* NOT MATCHING, not compiled. fn_8012EEFC: 30 of 93 words, saved registers only: the hoisted 0 wants r28 and the unit r29 (ours 0 on top). Structure matches; SupIdxU reads o->person on every SupAt, which the volatile SupN makes possible. */
#pragma inline_max_size(4000)
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
    u8 padF0[0x2fc - 0xf0];
    SPer* pair;
    u8 sup[0x48];
};
extern SUnit* fn_8012CECC(void*);
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
static inline void* SupPid(const SPer* p, int i) {
    if (i < 0) return 0;
    return SupAt(p, i);
}
static inline u8 SupN2(SPer* p) { if (p->sup == 0) { return 0; } return p->sup->n; }
static inline void* SupPid2(SPer* p, int i) { if (i < 0) return 0; if (i < 0) return 0; return p->sup->e[i].person; }
static inline void* SupAtU(const SUnit* u, int i) { if (i < 0) return 0; return u->person->sup->e[i].person; }
static inline void* SupAtU2(SUnit* u, int i) { if (i < 0) return 0; return SupAt(u->person, i); }
static inline u8 SupNU(SUnit* u) { return SupN(u->person); }
static inline s8 SupIdxU(SUnit* u, void* who) {
    s8 r = -1;
    int i;
    for (i = 0; i < SupN(u->person); i++) {
        if (SupAtU(u, i) == who) {
            r = i;
            break;
        }
    }
    return r;
}
static inline void SetSup(SUnit* u, int i, u8 v) {
    if (i >= 0) u->sup[i] = v;
}
static inline void Brk(SUnit* u) {
    if (u->person->sup) {
        int i;
        u->pair = 0;
        for (i = 0; i < SupN2(u->person); i++) {
            SUnit* o = fn_8012CECC(SupPid2(u->person, i));
            if (o) {
                s8 b = SupIdxU(o, u->person);
                if (b >= 0) {
                    SetSup(u, i, 0);
                    SetSup(o, b, 0);
                    if (o->pair == u->person) o->pair = 0;
                }
            }
        }
    }
}
void fn_8012EEFC(SUnit* u) { Brk(u); }
}
