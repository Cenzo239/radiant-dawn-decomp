/* EQUIVALENT (sched, round 19b): fn_801197F4. Moved instruction (checked with dd.py): the lbz 0xd(r4) load sits two slots later in the prologue (and goes straight to r30). From wip/r16_fn_801197F4.cpp. */
/* NOT MATCHING, not compiled. fn_801197F4: 4 of 53 words: wants lbz r0 then extsb r30,r0 before the stw r29 save (ours loads straight into r30). The rest matches. */
#include "game/rH_80112B48/types.h"
extern "C" {
struct Pr { void* a; void* b; u8 c; };
extern Pr lbl_80412C18[0x60];
extern int lbl_804CB80C;
struct SEnt { void* pid; u8 pad4; u8 val; u8 pad6[2]; };
struct SData { void* pid; u32 n; SEnt e[1]; };
extern void* fn_8010B1D8(void*);
static inline u8 PairGet(void* a, void* b) {
    int i;
    void* t;
    Pr* e;
    int n;
    u8 r;
    n = lbl_804CB80C;
    e = lbl_80412C18;
    for (i = 0, r = 0; i < n; i++, e++) {
        t = e->a;
        if ((a == t && b == e->b) || (a == e->b && b == t)) {
            r = e->c;
            break;
        }
    }
    return r;
}
static inline int Clamp(int v) { if ((s8)v > 4) v = 4; if ((s8)v < 0) v = 0; return v; }
static inline int SV(SData* p, int i) { return (s8)p->e[i].val; }
static inline s8 SV2(SData* p, int i) { return p->e[i].val; }
int fn_801197F4(SData* p, int i) {
    int v = *(s8*)&p->e[i].val;
    void* a = fn_8010B1D8(p->pid);
    v -= PairGet(a, p->e[i].pid);
    if ((s8)v > 4) v = 4;
    if ((s8)v < 0) v = 0;
    return v;
}
}