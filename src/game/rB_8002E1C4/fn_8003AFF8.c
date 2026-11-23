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

RANGE_FN(fn_8003AFF8, lbl_803795C8)
RANGE_FN(fn_8003B04C, lbl_803795B8)
RANGE_FN(fn_8003B0A0, lbl_803795A8)
RANGE_FN(fn_8003B0F4, lbl_80379598)
RANGE_FN(fn_8003B148, lbl_80379588)
RANGE_FN(fn_8003B19C, lbl_80379578)
RANGE_FN(fn_8003B1F0, lbl_80379568)
RANGE_FN(fn_8003B244, lbl_80379558)
