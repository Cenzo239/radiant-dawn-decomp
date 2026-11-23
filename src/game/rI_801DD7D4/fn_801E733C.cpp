#include "game/rI_801DD7D4/types.h"
#pragma use_lmw_stmw on
extern "C" {
void fn_8010E41C(void*, int);
extern u8 lbl_803CAB38[];
int fn_80060754(void*);
struct It;
struct Tb { int n; struct It* a; };
Tb* fn_801059B0(void);
}
struct It { u32 x0; u8 x4, x5; u8 p6[0x22]; };
struct Cl { u8 p[8]; u8 x8; };
struct Un { u8 p[0xec]; int xec; u8 pf0[4]; Cl* xf4; u8 pf8[0xc4]; It it[7]; u8 p2d4[0x11c]; };
extern "C" Un* lbl_804CB810;
static inline Un* unitAt(int i) { if ((u8)i) return &lbl_804CB810[(u8)i - 1]; return 0; }
extern "C" int fn_801E733C(u32 id) {
/*P*/
    int c;
    int k;
    int n;
    int total;
    It* it;
    int j;
    u32 v;
    int i2;
    Un* u;
    int i;
/*E*/
    if (id == 0) return 0;
    total = 0;
    {
    u8 m[4];
    fn_8010E41C(m, 4);
    for (i = 1; i <= 0xfe; i++) {
        u = unitAt(i);
        if (u->xec && m[u->xf4->x8]) {
            n = 0;
            it = u->it;
            for (j = 0; j < 7; j++, it++) {
                if (it == 0 || (v = it->x0) == 0) break;
                if (!((it->x5 >> 5) & 1) && id == v) n++;
            }
            total += n;
        }
    }
    }
    if (fn_80060754(lbl_803CAB38)) {
        i2 = 0;
        c = fn_801059B0()->n;
        k = 0;
        for (; i2 < c; i2++) {
            It* it2 = (It*)((u8*)fn_801059B0()->a + k);
            u32 v2;
            if (it2 && (v2 = it2->x0) && !((it2->x5 >> 5) & 1) && id == v2) total++;
            k += 0x28;
        }
    }
    return total;
}
