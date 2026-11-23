#include "game/rB_8002E1C4/statefn_bss.h"

/* Map-action range setup: highlight the range, then push a menu/state
 * object (a lazily initialised static {x0, desc}) with fn_800D042C. */

/* Types, STATE_FN and the state objects of fn_8003CD54/fn_8003CE54 come from
 * statefn.h / statefn_bss.h (see there). */
void fn_80039F2C(MapUnit* u, int n);
void fn_8003A03C(MapUnit* u);
void fn_8003A250(MapUnit* u);
void fn_8003A1FC(MapUnit* u);
void fn_8003A0C4(MapUnit* u);
void fn_80039FB4(MapUnit* u);
void fn_800399B0(MapUnit* u, s8 n);

STATE_FN(fn_8003CA20, INIT_CG, lbl_804CB198, lbl_804CB1A0, lbl_80379DA0, fn_80039F2C(lbl_803CA870.unit, 1))
STATE_FN(fn_8003CA88, INIT_CG, lbl_804CB1A8, lbl_804CB1B0, lbl_80379DA0, fn_80039F2C(lbl_803CA870.unit, 2))
STATE_FN(fn_8003CAF0, INIT_CG, lbl_804CB1B8, lbl_804CB1C0, lbl_80379D6C, fn_8003A03C(lbl_803CA870.unit))
STATE_FN(fn_8003CB54, INIT_CG, lbl_804CB1C8, lbl_804CB1D0, lbl_80379D38, fn_8003A250(lbl_803CA870.unit))
STATE_FN(fn_8003CBB8, INIT_CG, lbl_804CB1D8, lbl_804CB1E0, lbl_80379D04, fn_8003A1FC(lbl_803CA870.unit))
STATE_FN(fn_8003CC1C, INIT_CG, lbl_804CB1E8, lbl_804CB1F0, lbl_80379CD0, fn_8003A0C4(lbl_803CA870.unit))
STATE_FN(fn_8003CC80, INIT_CG, lbl_804CB1F8, lbl_804CB200, lbl_80379C9C, fn_80039FB4(lbl_803CA870.unit))
STATE_FN(fn_8003CCE4, INIT_CG, lbl_804CB208, lbl_804CB210, lbl_80379C68, fn_800399B0(lbl_803CA870.unit, lbl_803CA870.xe))

static inline void bigCtor(BigStateObj* o, void* d) { o->desc = lbl_StateBaseVt; o->desc = d; }

int fn_801C8858(void* p);
s16 fn_80123998(MapUnit* u);

#define BIG_FN_CA(name, guard, obj, dsc, call) \
    extern s8 guard; \
    extern u8 dsc[]; \
    void name(void* a) \
    { \
        call(lbl_803CA870.unit, *fn_80044FD0(&lbl_803CA870)); \
        if (!guard) { \
            bigCtor(&obj, dsc); \
            guard = 1; \
        } \
        obj.x8 = fn_801C8858(*fn_80044FD0(&lbl_803CA870)); \
        obj.x8 += fn_80123998(lbl_803CA870.unit); \
        obj.xc = fn_800E3C04(lbl_803615A8, fn_800D042C(&obj, a)); \
        obj.xc->x30->flags |= 4; \
        fn_800E4AD4(obj.xc, 0.03f); \
        obj.xc->x30->x8 = 0x14; \
    }

void fn_8003A3BC(MapUnit* u, void* t);
void fn_8003A510(MapUnit* u, void* t);

BIG_FN_CA(fn_8003CD54, lbl_804CB218, sState_8003CD54, lbl_80379C34, fn_8003A3BC)
BIG_FN_CA(fn_8003CE54, lbl_804CB219, sState_8003CE54, lbl_80379C00, fn_8003A510)
