#include "game/rB_8002E1C4/statefn.h"

void** fn_8012759C(MapUnit* u);
void fn_80039C40(MapUnit* u, void* t);
void fn_80039AE4(MapUnit* u, void* t);
extern u8 lbl_803CA7C0[];

void fn_8003F6BC(void* a)
{
    if (((u8*)&lbl_803CA870)[0xc] == 0x28)
        fn_80039C40(lbl_803CA870.unit, *fn_8012759C(lbl_803CA870.unit));
    else
        fn_80039AE4(lbl_803CA870.unit, *fn_8012759C(lbl_803CA870.unit));
    fn_800D042C(lbl_803CA7C0, a);
}
