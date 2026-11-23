/* Find the nearest free tile for a unit's rescue partner, 8011EB4C. */
#include "game/rH_80112B48/unit.h"
#include "game/rH_80112B48/map.h"
#pragma auto_inline off
extern "C" {
extern Map lbl_803EC898;
struct TileT { u8 pad0[8]; u8* p8; };
extern void fn_80114888(Map*, int);
extern void fn_801151BC(Map*, Unit*);
extern void fn_8011567C(Map*, void*);
extern void fn_80115764(Map*, int, int, int);
extern s16 fn_80115CD8(Map*, int, int);
extern TileT* fn_801181E8(Map*, int, int);
#define M ((Map*)&lbl_803EC898)
#pragma push
#pragma use_lmw_stmw on
void fn_8011EB4C(Unit* u, s8* ox, s8* oy) {
    /*P*/
    int best;
    int y;
    int x;
    Unit* v;
/*E*/
    v = (Unit*)u->actor;
    lbl_803EC898.ter[0][u->x + (u->y << 6)] = 0;
    fn_80114888(&lbl_803EC898, 6);
    fn_801151BC(&lbl_803EC898, u);
    fn_8011567C(&lbl_803EC898, 0);
    fn_80115764(&lbl_803EC898, u->x, (s8)*(u8*)&u->y, 0x3e8);
    fn_801151BC(&lbl_803EC898, v);
    fn_8011567C(&lbl_803EC898, v->team);
    *ox = -1;
    *oy = -1;
    best = 0x7fff;
    for (y = lbl_803EC898.y0; y <= lbl_803EC898.y1 - 1; y++) {
        for (x = lbl_803EC898.x0; x <= lbl_803EC898.x1 - 1; x++) {
            if (fn_80115CD8(M, (s8)x, (s8)y) <= 0x7530) {
                Map* q = (Map*)(((u8*)&lbl_803EC898 + (s8)y * 0x40) + (s8)x);
                if (*(s8*)&q->g5[0] == 0 && q->ter[0][0] == 0 && q->ter[3][0] == 0 &&
                    !(fn_801181E8(M, (s8)x, (s8)y)->p8[7] & 0x10) &&
                    !(fn_801181E8(M, (s8)x, (s8)y)->p8[7] & 8)) {
                    s16 c = ((s16*)lbl_803EC898.cur + (s8)y * 0x40)[(s8)x];
                    if ((u16)best > (u16)c) {
                        *ox = x;
                        best = (u16)c;
                        *oy = y;
                    }
                }
            }
        }
    }
    lbl_803EC898.ter[0][u->x + (u->y << 6)] = u->padFC;
}
#pragma pop
}
