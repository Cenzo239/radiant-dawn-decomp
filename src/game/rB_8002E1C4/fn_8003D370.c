#include "game/rB_8002E1C4/types.h"

typedef struct MapUnit MapUnit;
typedef struct RangeState { MapUnit* unit; u32 x4; u8 pad[0x130 - 8]; } RangeState;
extern RangeState lbl_803CA870; /* current map-range state */
void fn_800D042C(void* a, void* b);
extern u8 lbl_804CB190[8];
void fn_8003AFF8(MapUnit* u);

void fn_8003D370(void* a)
{
    fn_8003AFF8(lbl_803CA870.unit);
    fn_800D042C(lbl_804CB190, a);
}

extern u8 lbl_804CB188[8];
void** fn_80044FD0(RangeState* s);
void fn_8003A90C(MapUnit* u, void* target);

void fn_8003D3B0(void* a)
{
    fn_8003A90C(lbl_803CA870.unit, *fn_80044FD0(&lbl_803CA870));
    fn_800D042C(lbl_804CB188, a);
}
