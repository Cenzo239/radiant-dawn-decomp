#include "game/rF_8017F400/gmap.h"

#pragma auto_inline off

extern "C" {

typedef struct ModelNode {
    u8 pad0[8];
    s16 unk8;   /* 0x08 */
    u8 padA[0xE];
    u32 flags;  /* 0x18 */
} ModelNode;

typedef struct Model {
    u8 pad0[0x30];
    ModelNode* node; /* 0x30 */
} Model;

extern Model* fn_800E3C04(const char* name, void* archive);
extern void fn_800E48AC(Model* m, f32 x, f32 y, f32 z);
extern void fn_800E4AD4(Model* m, f32 v);
extern const f32 lbl_804CE610;


static inline void GMapEntA_Stop(GMapEntA* e)
{
    if (e->state) {
        e->state = 5;
    }
}

void fn_80183B10(GMap* p, int i)
{
    GMapEntA_Stop(&p->a[i]);
}

void fn_80183B30(GMap* p)
{
    GMapEntA* e = p->a;
    for (int i = 0; i < 20; i++) {
        if (p->a[i].state) {
            e->state = 5;
        }
        e++;
    }
}

BOOL fn_80183BA8(GMap* p, int i)
{
    return p->a[i].state != 0;
}

void fn_80183BC8(GMap* p, int i, const char* name)
{
    GMapEntB* e = &p->b[i];
    e->state = 1;
    e->alpha = 0xFF;
    Model* m = fn_800E3C04(name, p->proc);
    e->model = m;
    fn_800E48AC(m, 0.0f, 0.0f, 0.0f);
    m->node->unk8 = 0x3A7;
    fn_800E4AD4(m, lbl_804CE610 /* 1.0f */);
    m->node->flags |= 0x08000004;
}

static inline void GMapEntB_Stop(GMapEntB* e)
{
    if (e->state) {
        e->state = 2;
    }
}

void fn_80183C60(GMap* p, int i)
{
    GMapEntB_Stop(&p->b[i]);
}

void fn_80183C80(GMap* p)
{
    GMapEntB* e = p->b;
    for (int i = 0; i < 10; i++) {
        if (p->b[i].state) {
            e->state = 2;
        }
        e++;
    }
}

BOOL fn_80183CF4(GMap* p, int i)
{
    return p->b[i].state != 0;
}

extern int fn_801D09F0(void); /* widescreen? */

void fn_80183D14(GMap* g, int i, int x, s16 dur, u8 u6, BOOL flag)
{
    GMapEntC* e = &g->c[i];
    f32 fx;
    e->flags = 0;
    if (flag) {
        e->flags |= 1;
    }
    e->state = 1;
    if (!fn_801D09F0()) {
        fx = x;
    } else {
        f32 scale = 608.0 / g->view[2];
        f32 c = (304.0f - g->view[0]) / g->view[2];
        f32 lo = c - 0.5f * scale;
        f32 hi = 0.5f * scale + c;
        f32 base = 608.0f * ((0.5f * g->width - lo) / (hi - lo));
        fx = 0.76381909847f * ((f32)x - base) + base;
    }
    e->x = fx;
    e->dur = dur;
    e->unk6 = u6;
    e->unk7 = 0;
}

static inline void GMapEntC_Stop(GMapEntC* e)
{
    if (e->state) {
        e->state = 3;
    }
}

void fn_80183E34(GMap* p, int i)
{
    GMapEntC_Stop(&p->c[i]);
}

void fn_80183E54(GMap* p)
{
    GMapEntC* e = p->c;
    for (int i = 0; i < 9; i++) {
        if (p->c[i].state) {
            e->state = 3;
        }
        e++;
    }
}

BOOL fn_80183EA8(GMap* p, int i)
{
    return p->c[i].state != 0;
}

void fn_80183EC8(GMap* g, int dur)
{
    g->fadeDur = dur;
    g->fadeTimer = dur;
    g->fadeOn = 1;
    if (dur == 0) {
        g->fadeAlpha = 0xFF;
    }
}

void fn_80183EEC(GMap* g, int dur)
{
    g->fadeDur = dur;
    g->fadeTimer = dur;
    g->fadeOn = 0;
    if (dur == 0) {
        g->fadeAlpha = 0;
    }
}

void fn_80183F0C(GMap* g, f32 x0, f32 y0, f32 x1, f32 y1, int dur, u32 arg)
{
    if (dur <= 0) {
        g->view[0] = x0;
        g->view[1] = y0;
        g->view[2] = x1;
        g->view[3] = y1;
        g->viewDur = 0;
        g->viewTimer = 0;
        return;
    }
    g->viewLerp[0][0] = g->view[0];
    g->viewLerp[1][0] = g->view[1];
    g->viewLerp[2][0] = g->view[2];
    g->viewLerp[3][0] = g->view[3];
    g->viewLerp[0][1] = x0;
    g->viewLerp[1][1] = y0;
    g->viewLerp[2][1] = x1;
    g->viewLerp[3][1] = y1;
    g->viewDur = dur;
    g->viewTimer = dur;
    g->unk2C = arg;
}

void fn_80183F74(GMap* g, int dur)
{
    if (dur <= 0) {
        g->alpha = 0xFF;
        g->alphaDur = 0;
        g->alphaTimer = 0;
        return;
    }
    u8 a = g->alpha;
    g->alphaTo = 0xFF;
    g->alphaFrom = a;
    g->alphaDur = dur;
    g->alphaTimer = dur;
}

void fn_80183FB0(GMap* g, int dur)
{
    if (dur <= 0) {
        g->alpha = 0;
        g->alphaDur = 0;
        g->alphaTimer = 0;
        return;
    }
    u8 a = g->alpha;
    g->alphaTo = 0;
    g->alphaFrom = a;
    g->alphaDur = dur;
    g->alphaTimer = dur;
}

}
