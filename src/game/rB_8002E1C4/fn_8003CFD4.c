#include "game/rB_8002E1C4/statefn_bss.h"

void fn_8003A664(MapUnit* u, void* t);
void fn_8003AFF8(MapUnit* u);
void fn_8003A7B8(MapUnit* u, void* t);
void fn_8003A368(MapUnit* u);
void fn_8003AA60(MapUnit* u, u8* p);
void fn_8003ACB8(MapUnit* u);
void fn_8003AB90(MapUnit* u);

MID_FN(fn_8003CFD4, INIT_CG, lbl_804CB21A, sState_8003CFD4, lbl_80379BCC, fn_8003A664(lbl_803CA870.unit, TARGET))
MID_FN(fn_8003D09C, INIT_CG, lbl_804CB21B, sState_8003D09C, lbl_80379B98, fn_8003AFF8(lbl_803CA870.unit))
STATE_FN(fn_8003D154, INIT_CG, lbl_804CB21C, lbl_804CB220, lbl_80379B64, fn_8003A7B8(lbl_803CA870.unit, TARGET))
STATE_FN(fn_8003D1D0, INIT_CG, lbl_804CB228, lbl_804CB230, lbl_80379B30, fn_8003A368(lbl_803CA870.unit))
STATE_FN(fn_8003D234, INIT_CG, lbl_804CB238, lbl_804CB240, lbl_80379AFC,
         u8 b = lbl_803CA870.x17; fn_8003AA60(lbl_803CA870.unit, &b))
STATE_FN(fn_8003D2A8, INIT_CG, lbl_804CB248, lbl_804CB250, lbl_80379AFC, fn_8003ACB8(lbl_803CA870.unit))
STATE_FN(fn_8003D30C, INIT_CG, lbl_804CB258, lbl_804CB260, lbl_80379AFC, fn_8003AB90(lbl_803CA870.unit))
