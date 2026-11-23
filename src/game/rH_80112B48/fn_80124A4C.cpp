/* Count skill holders next to a unit on the same side, 80124A4C. */
#include "game/rH_80112B48/unit.h"
#include "game/rH_80112B48/map.h"
#pragma auto_inline off
extern "C" {
extern int fn_8011B77C(void*, void*);
extern int fn_80117A0C(Map*, int, int);
extern Map lbl_803EC898;
extern const u8 lbl_804CDD18[8];
static inline int DX(int c) { switch (c) { case 1: return -1; case 2: return 1; } return 0; }
static inline int DY(int c) { switch (c) { case 4: return 1; case 8: return -1; } return 0; }
#pragma push
#pragma use_lmw_stmw on
int fn_80124A4C(Unit* u, void* sk, Unit** out) {
    /*P*/
    Unit** w;
    int n;
    const u8* s;
    s16 x;
    s16 y;
    Unit* v;
    int c;
/*E*/
    n = 0;
    if (!(u->flags108 & 0x100)) {
        w = out;
        s = lbl_804CDD18;
        for (; (c = *s, (s8)c); s++) {
            x = u->x + DX(c);
            y = u->y + DY(c);
            if (fn_80117A0C(&lbl_803EC898, (s8)x, (s8)y) == 0) {
                int id = lbl_803EC898.ter[0][(s8)x + ((s8)y << 6)];
                if (id) {
                    v = UnitGet(id);
                    if (u->team[8] == v->team[8] && fn_8011B77C(v->skills, sk)) {
                        if (out) *w = v;
                        w++;
                        n++;
                    }
                }
            }
        }
    }
    return n;
}
#pragma pop
}
