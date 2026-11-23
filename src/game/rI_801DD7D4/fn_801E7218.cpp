#include "game/rI_801DD7D4/types.h"
#pragma use_lmw_stmw on
extern "C" {
void fn_8010E41C(void*, int);
extern u8 lbl_803CAB38[];
int fn_80060754(void*);
struct It;
struct Un;
struct Tb { int n; struct It* a; };
Tb* fn_801059B0(void);
s8 fn_8012C9BC(Un*, u32);
#if TARGET_PC
FE10_PROTO int fn_80105328(Tb*, p32arg);
#else
int fn_80105328(Tb*, u32);
#endif
}
struct It { u32 x0; u8 x4, x5; u8 p6[0x22]; };
struct Cl { u8 p[8]; u8 x8; };
struct Un { u8 p[0xec]; int xec; u8 pf0[4]; Cl* xf4; u8 pf8[0xc4]; It it[7]; u8 p2d4[0x11c]; };
extern "C" Un* lbl_804CB810;
static inline Un* unitAt(int i) { if ((u8)i) return &lbl_804CB810[(u8)i - 1]; return 0; }
extern "C" BOOL fn_801E7218(u32 id) {
/*P*/
    BOOL f;
    Un* u;
    int i;
    int k;
/*E*/
    if (id == 0) return 0;
    f = 0;
    {
    u8 m[4];
    fn_8010E41C(m, 4);
    for (i = 1; i <= 0xfe; i++) {
        u = unitAt(i);
        if (u->xec && m[u->xf4->x8]) {
            k = fn_8012C9BC(u, id);
            if (k >= 0 && !((u->it[k].x5 >> 5) & 1)) { f = 1; break; }
        }
    }
    }
    if (!f && fn_80060754(lbl_803CAB38)) {
        id = fn_80105328(fn_801059B0(), id);
        if ((int)id >= 0 && !((fn_801059B0()->a[(int)id].x5 >> 5) & 1)) f = 1;
    }
    return f;
}
