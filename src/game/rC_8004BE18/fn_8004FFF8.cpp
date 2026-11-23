/* Round 16: unit command usability checks that try each carried item (rC item-loop family). The item loop is an inline returning 0/3. */
#include "game/rC_8004BE18/helpbox.h"
#pragma use_lmw_stmw on
static inline int useItemsR(int& i, ItemSlot*& s) {
    for (i = 0; i < 7; i++) {
        s = cmdItem(i);
        if (s == 0 || s->data == 0) {
            break;
        }
        if ((fn_801116B8(s)->flags4 & 1) && (fn_801116B8(s)->flags4 & 0x10) == 0 &&
            fn_8012BA20(lbl_803CA870.unit, s->data)) {
            fn_80039AE4(lbl_803CA870.unit, s->data);
            if (lbl_803E7320.i0) {
                return 0;
            }
        }
    }
    return 3;
}
static inline int useItems(void) {
    int i;
    ItemSlot* s;
    return useItemsR(i, s);
}
/* fn_8004FFF8 */
extern "C" int fn_8004FFF8(void) {
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (unitHas(lbl_804CA69C) == 0) {
        return 3;
    }
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (flagExists(&lbl_803CAB38, lbl_8037D724)) {
        return 3;
    }
    return useItems();
}

/* fn_80050248 */
extern "C" int fn_80050248(void) {
/*P*/
    int i;
    ItemSlot* s;
/*E*/
    if (lbl_803CA870.b16) {
        return 3;
    }
    if (flagExists(&lbl_803CAB38, lbl_8037D724)) {
        return 3;
    }
    return useItemsR(i, s);
}

