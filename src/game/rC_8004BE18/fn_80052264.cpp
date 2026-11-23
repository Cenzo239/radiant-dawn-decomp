/* fn_80052264 (round 16). */
#include "game/rC_8004BE18/types.h"
#pragma use_lmw_stmw on
class Pad {
public:
    VPAD(0) VPAD(1) VPAD(2) VPAD(3) VPAD(4) VPAD(5) VPAD(6) VPAD(7)
    VPAD(8) VPAD(9) VPAD(10) VPAD(11) VPAD(12) VPAD(13) VPAD(14) VPAD(15)
    virtual u32 v48();
};
struct GCur { u8 pad[0x934]; f32 x; f32 y; };
struct MapG { u8 pad[0x710e]; s16 cost[0x1000]; u8 p910e[0xf18e - 0x910e]; s8 g5[0x1000]; u8 rest[0x2542c - 0x1018e]; };
extern "C" {
extern Pad* lbl_804CB5B8;
extern GCur lbl_803CAB38;
extern MapG lbl_803EC898;
extern u8 lbl_804CB728;
extern char lbl_80361B38[];
void* fn_800677E4(void);
void fn_800312E8(void);
void fn_80083DC4(void*, int);
}
/* Unit-command target cursor: track the cursor tile, confirm (0x400) or cancel (0x800). */
extern "C" void fn_80052264(MenuProc* p) {
    u32 t = lbl_804CB5B8->v48();
    fn_800677E4();
    int x = (int)lbl_803CAB38.x;
    int y = (int)lbl_803CAB38.y;
    int i = (s8)x + (s8)y * 0x40;
    CursorRef* c;
    if (lbl_803EC898.g5[i] != 0 || lbl_803EC898.cost[i] < 0) {
        c = p->cursor;
        c->w0 = lbl_803CA870.unit;
        c->b4 = 0;
    } else {
        c = p->cursor;
        c->w0 = lbl_803CA870.unit;
        c->b4 = 3;
        if ((s8)x >= 0) {
            c->x = x;
        }
        if ((s8)y >= 0) {
            c->y = y;
        }
    }
    if (t & 0x400) {
        if (lbl_803EC898.g5[i] == 0 && lbl_803EC898.cost[i] >= 0) {
            lbl_804CB728 = 0;
            lbl_803CA870.pos13.x = x;
            lbl_803CA870.pos13.y = y;
            fn_80083DC4(p, 0x63);
            fn_80253EE4(lbl_80361B38 + 0x15, 0.0f);
        }
    } else if (t & 0x800) {
        lbl_804CB728 = 9;
        fn_800453B4(&lbl_803CA870, 0);
        fn_800312E8();
        *p->cursor = p->saved;
        fn_80083DC4(p, 0x63);
        fn_80253EE4(lbl_80361B38 + 0x25, 0.0f);
    }
}
