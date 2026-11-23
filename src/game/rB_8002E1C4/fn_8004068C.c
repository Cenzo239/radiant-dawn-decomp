#include "game/rB_8002E1C4/types.h"

extern char lbl_80379E78[0xc]; /* item name */
extern Item lbl_803CA800;
ItemData* fn_8010B228(const char* name); /* find item by id string */
void fn_80110BB4(Item* it, ItemData* d);

Item* fn_8004068C(void)
{
    fn_80110BB4(&lbl_803CA800, fn_8010B228(lbl_80379E78));
    return &lbl_803CA800;
}
