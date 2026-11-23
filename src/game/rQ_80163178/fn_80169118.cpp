/* AI: spawn the move-cursor marker at the chosen tile (names guessed). */
#include "game/rQ_80163178/common.h"
struct Mk { u8 pad[0x30]; f32 x, y; u8 pad38[0x60 - 0x38]; int w60, w64; };
extern "C" {
extern u8 lbl_80387438[];
void fn_800454A8(AiAct*, int, int);


void fn_80169118(void* p) {
    AiAct* a = &lbl_803CA870;
    int x;
    s16 y;
    fn_800454A8(a, a->x, (s8)*(u8*)&a->y);
    switch (a->action) {
    case 1:
    case 3:
    case 4:
    case 5:
    case 6:
    case 13:
    case 14:
    case 19:
    case 20:
    case 26:
    case 27:
    case 28:
    case 29:
    case 33:
    case 34:
    case 35:
    case 37:
    case 42:
    case 44:
    case 45:
    case 53:
    case 55:
    case 59:
    case 61:
    case 64:
        return;
    case 80:
    case 81:
    case 82:
    case 86:
    case 91:
    case 92:
        return;
    case 93:
    case 94:
    case 95:
        return;
    case 9:
    case 38:
        x = a->x;
        y = a->y - 1;
        break;
    case 10:
    case 11:
    case 12:
    case 40:
    case 43:
    case 47:
    case 50:
    case 58:
        x = a->x2;
        y = a->y2;
        break;
    case 7:
    case 15:
    case 16:
    case 17:
    case 18:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 30:
    case 31:
    case 32:
    case 60:
    case 65:
    case 83:
    case 84:
    case 85:
    case 87:
    case 88:
    case 89:
    case 96:
        {
            Unit* u = a->unit2 ? a->unit2 : a->unit;
            x = u->x;
            y = u->y;
        }
        break;
    default:
        return;
    }
    Mk* m = (Mk*)fn_80081194(lbl_80387438, p);
    m->x = x;
    m->y = (s8)y;
    m->w60 = 0;
    m->w64 = 0;
}
}
