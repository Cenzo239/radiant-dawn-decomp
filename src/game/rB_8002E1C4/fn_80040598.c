#include "game/rB_8002E1C4/types.h"

typedef struct MapUnit MapUnit;
typedef struct RangeState { MapUnit* unit; u32 x4; u8 pad[0x130 - 8]; } RangeState;
extern RangeState lbl_803CA870;
void fn_8012759C(MapUnit* u);

void fn_80040598(void)
{
    fn_8012759C(lbl_803CA870.unit);
}
