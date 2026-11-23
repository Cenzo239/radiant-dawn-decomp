#include "game/rB_8002E1C4/types.h"

typedef struct MapUnit MapUnit;
typedef struct RangeState { MapUnit* unit; u32 x4; u8 pad[0x130 - 8]; } RangeState;
extern RangeState lbl_803CA870; /* current map-range state */
void fn_800D042C(void* a, void* b);
extern u8 lbl_804CB188[8];
extern u8 lbl_80379728[];
int fn_801108F8(MapUnit* u);
int fn_80110940(MapUnit* u);
void fn_801213D0(void* a, u8 b);
void fn_8013F1C4(void);
void fn_80081194(void* a, void* b);
void fn_8003B0A0(MapUnit* u);

void fn_8003D5D8(void* a)
{
    fn_801213D0((void*)lbl_803CA870.x4, fn_801108F8(lbl_803CA870.unit));
    fn_8013F1C4();
    fn_80081194(lbl_80379728, a);
}

void fn_8003D638(void* a)
{
    fn_801213D0(lbl_803CA870.unit, fn_80110940(lbl_803CA870.unit));
    fn_8013F1C4();
    fn_80081194(lbl_80379728, a);
}

void fn_8003D694(void* a)
{
    fn_8003B0A0(lbl_803CA870.unit);
    fn_800D042C(lbl_804CB188, a);
}
