/* Weapon rank gain, 8012C260. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
extern int fn_8011B77C(void*, void*);
extern u8* fn_801116B8(Inv*);
extern s16 fn_8012C0A8(Unit*, int, int);
extern s16 fn_8010EF00(void);
extern s16 fn_80111230(int);
extern void* lbl_804CA67C;
static inline s16 Lv(s16 r) { return fn_80111230(r); }
static inline s16 Rk(const Unit* u, int i) { return u->s2D4[i]; }
static inline s16 Rk2(Unit* u, u8 i) { return u->s2D4[i]; }
static inline void Wk(Unit* u, u8 i, s16 v) { u->s2D4[i] = v; }
BOOL fn_8012C260(Unit* u, u8* it) {
    u8 i = it[0x12];
    s16 old = fn_8012C0A8(u, i, ((const Unit*)u)->s2D4[i]);
    s16 now;
    s16 g;
    int v;
    if (old >= 0x14b) return 0;
    if (fn_8011B77C(u->skills, lbl_804CA67C)) g = it[0x1a] * 2; else g = it[0x1a];
    v = (s16)(old + (s16)((f32)g * ((f32)fn_8010EF00() / 100.0f)));
    if (v > 0x14b) v = 0x14b;
    now = fn_8012C0A8(u, i, v);
    u->s2D4[i] = now;
    old = fn_80111230(old); now = fn_80111230(now); return old != now;
}
}
