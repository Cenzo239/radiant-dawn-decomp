#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/fn_wf.h"
extern "C" {
extern u8 lbl_8038CE68[], lbl_8038CE30[];
struct W58 { WF w; void* x40; u8 x44; u8 x45[8]; };
struct W50 { WF w; void* x40; u8 x44; };
struct P5 { u8 p[0x4c]; struct { u8 p[0x5c]; void* x5c; }* x4c; };
void fn_801F7CCC(P5* o) {
    W58* w;
    struct L5 { u8 p[0x5c]; void* x5c; }* l;
    l = (L5*)o->x4c;
    {
    w = (W58*)fn_80079150(0x58);
    if (w) {
        wfInit(&w->w, 0x191, 0x50, 0x291, 0x12c, 0x100, 0xdc, 0x1f4, 0x10);
        w->w.vt = lbl_8038CE68;
        w->x40 = 0;
        w->x44 = 0;
        w->x45[7] = 0; w->x45[6] = 0; w->x45[5] = 0; w->x45[4] = 0; w->x45[3] = 0; w->x45[2] = 0; w->x45[1] = 0; w->x45[0] = 0;
        ((Lst*)w)->v2C();
    }
    w->w.id = 0x107;
    w->x40 = l->x5c;
    w->x44 = 1;
    w->w.a28 = 8;
    fn_801E5448(o, w);
    }
    {
    w = (W58*)fn_80079150(0x50);
    if (w) {
        wfInit(&w->w, 0x185, 0x12d, 0x29d, 0x19c, 0x118, 0x6f, 0x1f4, 0x10);
        w->w.vt = lbl_8038CE30;
        w->x40 = 0;
        w->x44 = 0;
        ((Lst*)w)->v2C();
    }
    w->w.id = 0x108;
    w->x44 = 0;
    w->x40 = l->x5c;
    w->w.a28 = 8;
    fn_801E5448(o, w);
    }
}
}
