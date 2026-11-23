/* Speed-type stat with skill doubling, aura and 7-byte bonus struct. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
extern int fn_8011B77C(void*, void*);
extern f32 fn_801070A4(Unit*);
extern void* lbl_804CA4EC;
extern void* lbl_804CA4F4;
extern void* lbl_804CA51C;
struct Bonus { s8 v[7]; Bonus(){} Bonus(const Bonus& o); };
extern Bonus fn_80107864(u8*, f32);
extern s8 fn_801252F8(Unit*);
static inline int StatJ(Unit* u, int i) { return u->stat[i] + u->job->base[i]; }
static inline s16 StatBaseF(Unit* u, int i) {
    int a = StatJ(u, i);
    int v = u->person->base[i] + a;
    if (v > u->job->max[i]) {
        v = u->job->max[i];
    }
    if (v < 0) {
        v = 0;
    }
    return v;
}
u8 fn_801278F8(Unit* u) {
    int v = StatBaseF(u, 3);
    if (fn_8011B77C(u->skills, lbl_804CA4EC)) {
        if (fn_8011B77C(u->skills, lbl_804CA4F4) || (u->flags10C & 0x8000000)) {
            v *= 1.5f;
        } else {
            v *= 2;
        }
    }
    if (v > u->job->max[3]) {
        v = u->job->max[3];
    }
    if (v < 0) {
        v = 0;
    }
    {
        s16 r = (s16)v + fn_801252F8(u);
        if (r < 0) {
            r = 0;
        }
        v = r;
    }
    if (fn_8011B77C(u->skills, lbl_804CA51C)) {
        v += 0x3c;
    }
    f32 bio = fn_801070A4(u);
    Bonus t;
    t = fn_80107864(u->skills, bio);
    v += t.v[6];
    if (v > 100) {
        v = 100;
    }
    if (v < 0) {
        v = 0;
    }
    return v;
}
}
