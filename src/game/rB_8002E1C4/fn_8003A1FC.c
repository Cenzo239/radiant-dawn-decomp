#include "game/rB_8002E1C4/types.h"

/* Map-range highlight helpers. Each builds a small functor on the stack
 * ({vtable, unit}) and runs it over the map around the unit's position. */

typedef struct MapUnit {
    u8 pad[0x102];
    s8 x;     /* 0x102 */
    s8 y;     /* 0x103 */
    u8 pad104[0x114 - 0x104];
    s8 x114;    /* current HP */
} MapUnit;

typedef struct Functor {
    void* vt;
    MapUnit* u;
} Functor;

extern u8 lbl_803E7320[];
void fn_800CFB34(void* map);            /* clear highlight layer */
void fn_800392FC(Functor* f, s8 x, s8 y); /* run functor over range */

#define RANGE_FN(name, vtbl) \
    extern u8 vtbl[]; \
    void name(MapUnit* u) \
    { \
        Functor f; \
        f.vt = vtbl; \
        f.u = u; \
        fn_800CFB34(lbl_803E7320); \
        fn_800392FC(&f, f.u->x, f.u->y); \
    }

RANGE_FN(fn_8003A1FC, lbl_80379698)
RANGE_FN(fn_8003A250, lbl_80379688)

extern u8 lbl_80379678[];
typedef struct RangeState { u32 x0; u32 x4; u8 pad[0x130 - 8]; } RangeState;
extern RangeState lbl_803CA870;

void fn_8003A2A4(MapUnit* u)
{
    Functor f;
    f.vt = lbl_80379678;
    fn_800CFB34(lbl_803E7320);
    fn_800392FC(&f, u->x, u->y);
    lbl_803CA870.x4 = 0;
}

extern u8 lbl_80379668[];

void fn_8003A30C(MapUnit* u)
{
    Functor f;
    f.vt = lbl_80379668;
    fn_800CFB34(lbl_803E7320);
    f.u = u;
    fn_800392FC(&f, u->x, u->y);
}

RANGE_FN(fn_8003A368, lbl_80379658)
