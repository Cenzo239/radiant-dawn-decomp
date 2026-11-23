/* Support level at a threshold, support gain, 8012EA2C and 8012EAB4. */
#include "game/rH_80112B48/unit.h"
#pragma auto_inline off
extern "C" {
extern int fn_8011B77C(void*, void*);
extern u8* fn_801116B8(Inv*);
struct SupItem { void* a; void* b; };
struct SupData { u8 pad0[8]; SupItem e[1]; };
struct SupCfg { u8 lv[4]; u8 padb[7]; s8 gain[5]; };
extern SupCfg* lbl_804CB808;
extern s8 fn_801197F4(SupData*, int);
static inline SupData* SD(Person* p) { return *(SupData**)((u8*)p + 0xdc); }
static inline u8 SV(Unit* u, int i) { if (i < 0) return 0; return u->sup[i]; }
static inline BOOL Maxed(Unit* u, int i) {
    SupData* d;
    SupCfg* c;
    SupItem* e;
    u8 v;
    BOOL r;
    if (i < 0) return 0;
    d = SD(u->person);
    if (d == 0) return 0;
    c = lbl_804CB808;
    e = &d->e[i];
    if (e == 0) return 0;
    v = SV(u, i);
    r = 0;
    if (v == c->lv[0] || v == c->lv[1] || v == c->lv[2]) r = 1;
    return r;
}
BOOL fn_8012EA2C(Unit* u, int i) { return Maxed(u, i); }
static inline int Lim(u8 v, SupCfg* c) {
    u8 lim = c->lv[0];
    if (v < lim) return lim;
    lim = c->lv[1];
    if (v < lim) return lim;
    lim = c->lv[2];
    if (v < lim) return lim;
    return c->lv[3];
}
static inline BOOL Maxed2(Unit* u, int i) {
    SupCfg* c; SupData* d; SupItem* e; u8 v; BOOL r;
    if (i < 0) return 0;
    d = *(SupData**)((u8*)u->person + 0xdc);
    if (d == 0) return 0;
    c = lbl_804CB808;
    e = &d->e[i];
    if (e == 0) return 0;
    v = SV(u, i);
    r = 0;
    if (v == c->lv[0] || v == c->lv[1] || v == c->lv[2]) r = 1;
    return r;
}
void fn_8012EAB4(Unit* u, int i, int v) {
    if (!Maxed2(u, i)) {
        SupCfg* c = lbl_804CB808;
        v += c->gain[(s8)fn_801197F4(SD(u->person), i)];
        if (v < 0) v = 0;
        {
            u8* s = &u->sup[i];
            int lim = Lim(*s, c);
            *s += v;
            if (*s > lim) *s = lim;
        }
    }
}
}
