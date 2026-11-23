/* Raise weapon ranks to what the equipped items need, 8011FC88. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
extern int fn_8011B77C(void*, void*);
extern u8* fn_801116B8(Inv*);
extern int fn_8012B120(Unit*, u8*);
extern s16 fn_8012C250(Unit*, u8);
static inline u8 IT(u8* p) { return p ? p[0x12] : 0x13; }
static inline s16 IR(u8* p) { return p ? *(s16*)(p + 0x18) : 0; }
void fn_8011FC88(Unit* u) {
    Inv* e;
    int i;
    e = u->inv;
    for (i = 0; i < 7; i++) {
        if (e == 0 || e->item == 0) break;
        if ((*(u32*)(fn_801116B8(e) + 4) & 0x11) && fn_8012B120(u, e->item) == 0) {
            if (IT(e->item) < 0xc) {
              if (fn_8012C250(u, IT(e->item)) != 0) {
                s16 a = IR(e->item);
                if (fn_8012C250(u, IT(e->item)) < a) {
                    u->s2D4[IT(e->item)] = IR(e->item);
                }
              }
            }
        }
        e++;
    }
}
}
