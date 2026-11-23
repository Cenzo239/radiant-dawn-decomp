#include "game/rB_8002E1C4/types.h"

typedef struct MapUnit MapUnit;
typedef struct RangeState { MapUnit* unit; u32 x4; u8 pad[0x130 - 8]; } RangeState;
extern RangeState lbl_803CA870;
extern u8 lbl_803CA7D8[0x28];
void** fn_80044FD0(RangeState* s);
void fn_80039AE4(MapUnit* u, void* target);
void fn_800D042C(void* a, void* b);

void fn_8003F744(void* a)
{
    fn_80039AE4(lbl_803CA870.unit, *fn_80044FD0(&lbl_803CA870));
    fn_800D042C(lbl_803CA7D8, a);
}
