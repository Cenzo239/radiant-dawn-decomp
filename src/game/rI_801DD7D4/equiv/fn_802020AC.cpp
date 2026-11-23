/* fn_802020AC (round 19, `sched`): round 15 draft with the help text passed by value (it is loaded before the lookup call). */
#include "game/rI_801DD7D4/fn_wf.h"
extern "C" {
void* fn_801E5640(void*, int, int);
extern u8 lbl_8038C1C0[];
extern u8 lbl_8038E070[];
extern char lbl_8036FBC0[];
void* fn_800D0864(const char*);
void* fn_801E7204(u8);
}
struct G3 { WF w; int a40; int a44; };
struct Sp { WF w; u8 p40[0xc]; int a4c; u8 a50; u8 p51[3]; f32 a54; s16 a58, a5a, a5c, a5e; int a60; const char* a64; };
struct Ctx { u8 p[0x30]; int x30; };
struct Sc { u8 p[0x44]; u8 x44; u8 p45[3]; Ctx* x48; };
static inline void help(void* o, int s) {
    void* w = fn_801E5640(o, -0x1000, 0);
    if (w) *(int*)((u8*)w + 0x64) = s;
}
static inline void spInit(Sp* s) {
    wfInit(&s->w, 0, 0x190, 0x260, 0x1c0, 0x260, 0x30, 0x78, 0x10);
    *(int*)((u8*)s + 0x40) = 0; *(int*)((u8*)s + 0x44) = 0; *(int*)((u8*)s + 0x48) = 0;
    s->a4c = 0;
    s->a50 = 1;
    s->a5a = 0;
    s->a5e = 0;
    s->w.vt = lbl_8038C1C0;
    s->a60 = 0;
    s->a64 = 0;
    s->a58 = 0x30;
    s->a5c = 0x30;
    s->a54 = 0.75f;
}
extern "C" void fn_802020AC(Sc* o) {
    Sp* s;
    G3* g;
    s = (Sp*)fn_80079150(0x68);
    if (s) spInit(s);
    s->w.id = -0x1000;
    s->a4c = 1;
    s->a64 = lbl_8036FBC0;
    s->w.flags |= 0x10;
    s->a60 = 0;
    s->w.a28 = 8;
    fn_801E5448(o, s);
    g = (G3*)fn_80079150(0x48);
    if (g) {
        wfInit(&g->w, 0x14, 0x13c, 0xe4, 0x18c, 0xd0, 0x50, 0x46, 0x10);
        g->w.vt = lbl_8038E070;
        g->a40 = 0;
        g->a44 = 0;
        ((Lst*)g)->v2C();
    }
    g->w.id = 3;
    g->w.a28 = 0;
    g->a40 = (int)fn_800D0864(lbl_8036FBC0 + 1);
    g->a44 = (int)fn_801E7204(o->x44);
    fn_801E5448(o, g);
    help(o, o->x48->x30);
}
