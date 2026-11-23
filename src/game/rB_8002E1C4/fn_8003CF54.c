#include "game/rB_8002E1C4/types.h"

typedef struct MapUnit MapUnit;
typedef struct RangeState { MapUnit* unit; u32 x4; u8 pad[0x130 - 8]; } RangeState;
extern RangeState lbl_803CA870; /* current map-range state */
void fn_800D042C(void* a, void* b);
extern u8 lbl_804CB188[8];
void fn_8003A2A4(MapUnit* u);
void fn_8003A30C(MapUnit* u);

void fn_8003CF54(void* a)
{
    fn_8003A2A4(lbl_803CA870.unit);
    fn_800D042C(lbl_804CB188, a);
}

void fn_8003CF94(void* a)
{
    fn_8003A30C(lbl_803CA870.unit);
    fn_800D042C(lbl_804CB188, a);
}
