/* r19: copied from wip/fn_8018524C.cpp; `sched` level (same instructions per basic block, order differs). */
/* near miss: 2 of 154 words. Case 0 wants li r0,0 before li r3,1. */
#include "game/rF_8017F400/types.h"
#pragma pool_strings on
extern "C" {
typedef struct BD { u8 pad[0x100]; int x100[9]; int n; } BD;
typedef struct BP { u8 pad[0x30]; int st; int t; int cur[5]; int x4c; int x50; s16 inc[1]; } BP;
class Pad { public: virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual u32 v3C(); virtual void v40(); virtual void v44(); virtual u32 v48(); };
extern Pad* lbl_804CB5B8;
extern int lbl_804CB910;
extern BD* fn_8008D750(void);
extern int fn_8008DB58(BD*);
extern int fn_8008DC34(BD*);
extern void fn_80083B78(void*);
extern void fn_80253EE4(const char*, f32);
extern const char lbl_8036BC00[];
void fn_8018524C(BP* p) {
    BD* d = fn_8008D750();
    u32 held = lbl_804CB5B8->v48();
    switch (p->st) {
    case 0:
        p->st = 1;
        p->t = 0;
        lbl_804CB910 = 0;
        break;
    case 1: case 2: case 3: case 4: case 5:
        if (d->n == 0) { p->st = 6; p->t = 0; break; }
        if ((held & 0x400) || (held & 0x800)) {
            int i;
            for (i = 0; i < d->n; i++) p->cur[i] = d->x100[i];
            p->x4c = fn_8008DB58(d);
            p->x50 = fn_8008DC34(d);
            p->st = 6;
            break;
        }
        {
        int k = p->st - 1;
        if (p->cur[k] >= d->x100[k]) {
            p->cur[k] = d->x100[k];
            p->t++;
            if (p->t >= 10) {
                if (k < d->n - 1) { p->st++; p->t = 0; lbl_804CB910 = 0; }
                else { p->st = 6; p->t = 0; }
            }
            break;
        }
        p->cur[k] += p->inc[k];
        if (p->cur[k] > d->x100[k]) p->cur[k] = d->x100[k];
        p->x4c += p->inc[k];
        if (p->x4c > fn_8008DB58(d)) p->x4c = fn_8008DB58(d);
        p->x50 += p->inc[k];
        if (p->x50 > fn_8008DC34(d)) p->x50 = fn_8008DC34(d);
        if (lbl_804CB910 == 0) fn_80253EE4(lbl_8036BC00 + 0x30, 0.0f);
        lbl_804CB910 = (lbl_804CB910 + 1) % 4;
        }
        break;
    case 6:
        if ((held & 0x400) || (held & 0x800)) fn_80083B78(p);
        break;
    }
}
}
