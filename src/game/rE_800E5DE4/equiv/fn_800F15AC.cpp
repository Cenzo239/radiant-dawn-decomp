/* fn_800F15AC: functionally equal (renamed, 18 of 96 words differ in registers only). Written in round 18 as C++ (reference parameter and assignment copies), although its neighbours in fn_800F080C.c are C. Evs() and the declaration order only set the entry schedule. */
/* fn_800F15AC: plays the up to four sound events of a model (ids at +0x8C, with a condition word:
   1000 = only while the frame counter is not negative, 2000 = only while it is not positive) at the
   position of its "se" joint, or at (x, y, z) when it has none. Below z = -1000 the sound is not positional. */
#include "game/rE_800E5DE4/types.h"
#pragma auto_inline off

typedef struct SeEv { u16 id; u16 cond; } SeEv;
typedef struct SeHost { u8 pad[0x5C]; f32 frame; u8 pad60[0x2C]; SeEv ev[4]; } SeHost;

extern "C" {
extern u8 lbl_803674B4[];
extern u32 fn_800F14B4(u32 id);
extern int fn_80007630(void*, char*);
extern Vec fn_800076E8(void*, int);
extern void fn_802549C4(u32, const Vec&, f32);
extern void fn_80253EE4(u32, f32);

static inline void SePlay(u32 s, const Vec& v) {
    Vec w;
    w = v;
    fn_802549C4(s, w, 0.0f);
}
static inline SeEv* Evs(SeHost* h) { return h->ev; }
static inline char* Base() { return (char*)lbl_803674B4; }
void fn_800F15AC(f32 x, f32 y, f32 z, SeHost* h) {
    SeEv* e = Evs(h);
    char* base = (char*)lbl_803674B4;
    f32 lim = -1000.0f;
    f32 zero = 0.0f;
    int i;
    for (i = 0; i < 4; i++, e++) {
        u32 s = fn_800F14B4(e->id);
        if (s) {
            if (e->cond == 1000 && h->frame < zero) continue;
            if (e->cond == 2000 && h->frame > zero) continue;
            {
                Vec p;
                int j;
                p.x = x;
                p.y = y;
                p.z = z;
                j = fn_80007630(h, base + 0x592);
                if (j >= 0) {
                    p = fn_800076E8(h, j);
                }
                if (p.z > lim) {
                    SePlay(s, p);
                } else {
                    fn_80253EE4(s, 0.0f);
                }
            }
        }
    }
}
}
