/* Combat stats with bonus struct returned in registers, 801209D0..801278B8. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off

extern "C" {
struct Bon7 {
    s8 v[7];
};
extern int fn_8011B77C(void*, void*);
extern s16 fn_80123AC4(Unit*);
extern f32 fn_80127868(Unit*);
extern Bon7 fn_801278B8(Unit*, f32);
extern void fn_80107864(Bon7*, u8*, f32);
extern void* lbl_804CA4F8;
extern void* lbl_804CA4FC;

static inline BOOL NoHit(Unit* b) {
    if (fn_8011B77C(b->skills, lbl_804CA4F8)) {
        return 1;
    }
    return fn_8011B77C(b->skills, lbl_804CA4FC);
}

#define HITF(name)                                                      \
u8 name(Unit* a, Unit* b) {                                             \
    int v;                                                              \
    if (NoHit(b)) {                                                     \
        return 0;                                                       \
    }                                                                   \
    v = fn_80123AC4(a);                                                 \
    f32 bio = fn_80127868(a);                                           \
    {                                                                   \
        Bon7 t = fn_801278B8(a, bio);                                   \
        int r = v / 2 + t.v[5];                                         \
        if (r > 100) {                                                  \
            r = 100;                                                    \
        }                                                               \
        if (r < 0) {                                                    \
            r = 0;                                                      \
        }                                                               \
        return r;                                                       \
    }                                                                   \
}

HITF(fn_801209D0)
HITF(fn_80120AC0)
HITF(fn_80120BB0)

Bon7 fn_801278B8(Unit* u, f32 bio) {
    Bon7 t;
    fn_80107864(&t, u->skills, bio);
    return t;
}

}
