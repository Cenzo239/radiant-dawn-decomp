#include "game/rB_8002E1C4/statefn.h"

typedef struct HealStateObj {
    u32 x0;
    void* desc;
    int x8;
    Effect* xc;
    Effect* x10;
    u8 pad[4];
} HealStateObj;

typedef struct HpUnit { u8 pad[0x114]; s8 hp; } HpUnit;

void fn_8003B514(MapUnit* u);
extern s8 lbl_804CB2C0;
extern HealStateObj lbl_803CA858;
extern u8 lbl_803797E0[];

void fn_8003FC90(void* a)
{
    void* p;
    fn_8003B514(lbl_803CA870.unit);
    if (!lbl_804CB2C0) INIT_CG(lbl_804CB2C0, lbl_803CA858, lbl_803797E0);
    lbl_803CA858.x8 = ((HpUnit*)lbl_803CA870.unit)->hp - 1;
    p = fn_800D042C(&lbl_803CA858, a);
    lbl_803CA858.xc = fn_800E3C04(lbl_803615A8, p);
    lbl_803CA858.xc->x30->flags |= 4;
    fn_800E4AD4(lbl_803CA858.xc, 0.03f);
    lbl_803CA858.xc->x30->x8 = 0x14;
    lbl_803CA858.x10 = fn_800E3C04(lbl_803615A8, p);
    lbl_803CA858.x10->x30->flags |= 4;
    fn_800E4AD4(lbl_803CA858.x10, 0.03f);
    lbl_803CA858.x10->x30->x8 = 0x14;
}

void fn_8003B574(MapUnit* u);

STATE_FN(fn_8003FDAC, INIT_GC, lbl_804CB2C1, lbl_804CB2C8, lbl_803797AC, fn_8003B574(lbl_803CA870.unit))
