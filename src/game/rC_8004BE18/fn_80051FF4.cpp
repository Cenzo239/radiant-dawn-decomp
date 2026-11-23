#include "game/rC_8004BE18/helpbox.h"
#pragma use_lmw_stmw on
class CmdV {
public:
    VPAD(0) VPAD(1) VPAD(2) VPAD(3) VPAD(4) VPAD(5) VPAD(6) VPAD(7)
    VPAD(8) VPAD(9) VPAD(10) VPAD(11) VPAD(12) VPAD(13) VPAD(14) VPAD(15)
    VPAD(16) VPAD(17) VPAD(18) VPAD(19)
    virtual int v58();
};
typedef struct MCEntry {
    u8 pad0[0x34];
    CmdV* cmd;
    u8 pad38[3];
    u8 b3b;
} MCEntry;
extern "C" MCEntry* fn_80085EF8(u8 id);
extern char lbl_80361B38[];
extern u8 lbl_804CB3F8;
extern u8 lbl_804CB410[8];
static inline int slotKind(void) {
    int k = 3;
    if (lbl_804CB3F8 == 0x33) {
        k = 0;
    }
    return k;
}
/* The table address goes through a named local (else it was materialised after
 * the kind), and the declaration order (found by a permutation search) puts the
 * loop counter in r27 below the slot byte. */
extern "C" void fn_80051FF4(void* parent) {
    u8* p;
    CursorRef* slot;
    MCEntry* e;
    u8 b;
    int i;
    FlagTable* t;
    lbl_804CB3F8 = lbl_803CA870.b0c;
    if (lbl_804CB3F8 == 0x33) {
        fn_800310E4((void*)fn_800D0864(lbl_80361B38), 0, 0x28, 0);
    } else {
        fn_800310E4((void*)fn_800D0864(lbl_80361B38 + 0xa), 0, 0x28, 0);
    }
    p = (u8*)fn_800D5448(lbl_804CB410, parent, 0);
    if (p) {
        t = &lbl_803CAB38;
        slot = fn_80062A9C(t, slotKind());
        if (slot) {
            for (i = 0; i < *(s8*)(p + 0xa4); i++) {
                e = fn_80085EF8(p[0x40 + i]);
                b = slot->b4;
                if (b == (u8)e->cmd->v58()) {
                    p[0xa6] = p[0xa7] = e->b3b;
                    break;
                }
            }
        }
    }
}
