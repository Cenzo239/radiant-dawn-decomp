/* NOT MATCHING, not compiled. fn_8012E944 (7), fn_8012E9B4 (13), fn_8012EDA0, fn_8012EEFC: a volatile read of person->dc reproduces the reload the original has; registers still swapped. */
/* Support bits and links, 8012E440..8012F050. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off

extern "C" {
extern u8* lbl_804CB808;
extern Unit* fn_8012CECC(void*);
extern s8 fn_801197F4(void*, int);
extern u8* fn_8010B250(u8);

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

static inline u8 SupN(SupData* d) { if (d == 0) { return 0; } return d->n; }

static inline s8 SupIdx(Person* p0, void* who) {
    s8 r = -1; int off = 0; int i; Person* p = p0;
    for (i = 0; i < SupN(SUPD(p)); i++) {
        void* q = i < 0 ? 0 : *(void**)((u8*)SUPD(p) + off + 8);
        if (q == who) {
            r = (s8)i;
            break;
        }
        off += 8;
    }
    return r;
}
s8 fn_8012E944(Unit* u, void* pid) {
    return SupIdx(u->person, pid);
}
s8 fn_8012E9B4(Unit* a, Unit* b) {
    return SupIdx(a->person, b->person);
}

void fn_8012EC2C(Unit* u, int n, u8* o) {
    s8 k = *(s8*)&u->u118;
    u8* c;
    if (k == -1) {
        k = *((s8*)u->person + 0xe1);
    }
    c = fn_8010B250((int)(u8)k);
    o[4] += n * c[4];
    o[5] += n * c[5];
    o[6] += n * c[6];
    o[7] += n * c[7];
    o[8] += n * c[8];
    o[9] += n * c[9];
}

void fn_8012EDA0(Unit* u, void* who) {
    Unit* o = fn_8012CECC(who);
    if (SUPD(u->person)) {
        if (*(void**)((u8*)u + 0x2fc) == o->person) {
            *(void**)((u8*)u + 0x2fc) = 0;
            *(void**)((u8*)o + 0x2fc) = 0;
        }
        {
            Person* po = o->person;
            Person* pu = u->person;
            int a = SupIdx(pu, po);
            int b = SupIdx(po, pu);
            if (a >= 0) {
                u->sup[a] = 0;
            }
            if (b >= 0) {
                o->sup[b] = 0;
            }
        }
    }
}

void fn_8012EEFC(Unit* u) {
    if (SUPD(u->person)) {
        int i;
        *(void**)((u8*)u + 0x2fc) = 0;
        for (i = 0; i < SupN(SUPD(u->person)); i++) {
            Unit* o;
            if (i < 0) {
                o = 0;
            } else {
                o = fn_8012CECC(i < 0 ? 0 : SUPD(u->person)->e[i].person);
            }
            if (o) {
                int k = SupIdx(o->person, u->person);
                if (k >= 0) {
                    if (i >= 0) {
                        u->sup[i] = 0;
                    }
                    if (k >= 0) {
                        o->sup[k] = 0;
                    }
                    if (*(void**)((u8*)o + 0x2fc) == u->person) {
                        *(void**)((u8*)o + 0x2fc) = 0;
                    }
                }
            }
        }
    }
}

}
