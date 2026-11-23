#include "game/rF_8017F400/gmap.h"

#pragma auto_inline off

extern "C" {

extern void fn_80081A90(void* proc);  /* delete process */
extern void fn_80078E24(void* p);     /* free */
extern void* fn_80078CCC(u32 size, const char* tag, int arg); /* alloc */
extern void* fn_80081050(void* cls, void* parent);           /* create process */
extern void* memset(void* p, int c, u32 n);
extern void fn_801818E0(GMap* g);
extern void fn_801820CC(GMap* g);
extern void fn_80181788(GMap* g);
extern void fn_80181470(GMap* g);
extern void fn_80183FE8(GMap* g, u8 idx, GMapInfo* info, GMapProc* proc);
extern u8 lbl_80387FF0[]; /* process class: GMapProc */

/* GMapProc update / draw */
void fn_80184398(GMapProc* p)
{
    fn_801818E0(lbl_804CB908[p->idx]);
    fn_801820CC(lbl_804CB908[p->idx]);
}

static inline void GMapEntC_Stop(GMapEntC* e)
{
    if (e->state) {
        e->state = 3;
    }
}

static inline void GMap_StopAllC(GMap* p)
{
    GMapEntC* e = p->c;
    for (int i = 0; i < 9; i++) {
        if (p->c[i].state) {
            e->state = 3;
        }
        e++;
    }
}

static inline void GMap_ClearA(GMap* g)
{
    GMapEntA* a = g->a;
    for (int i = 0; i < 20; i++, a++) {
        a->state = 0;
        if (a->proc != NULL) {
            fn_80081A90(a->proc);
            a->proc = NULL;
        }
    }
}

static inline void GMap_ClearB(GMap* g)
{
    GMapEntB* b = g->b;
    for (int i = 0; i < 10; i++, b++) {
        b->state = 0;
        if (b->model != NULL) {
            fn_80081A90(b->model);
            b->model = NULL;
        }
    }
}

static inline void Proc_Delete(void*& proc)
{
    if (proc != NULL) {
        fn_80081A90(proc);
        proc = NULL;
    }
}

/* GMapProc destroy */
void fn_801843EC(GMapProc* p)
{
    fn_80181788(lbl_804CB908[p->idx]);
    GMap_ClearA(lbl_804CB908[p->idx]);
    GMap_ClearB(lbl_804CB908[p->idx]);
    GMap_StopAllC(lbl_804CB908[p->idx]);
    Proc_Delete(lbl_804CB908[p->idx]->proc21C);
}

/* create gmap for chapter id */
void fn_8018454C(const char* id, void* parent)
{
    GMapInfo* info = lbl_80387D10;
    for (;;) {
        if (fn_80291188(id, info->id) == 0) {
            break;
        }
        info++;
    }
    for (int i = 0; i < 2; i++) {
        if (lbl_804CB908[i] == NULL) {
            GMap* g;
            g = lbl_804CB908[i] = (GMap*)fn_80078CCC(sizeof(GMap), lbl_8036BA4C + 0x1A3, 0);
            memset(g, 0, sizeof(GMap));
            g->proc = (GMapProc*)fn_80081050(lbl_80387FF0, parent);
            g->proc->idx = i;
            fn_80183FE8(g, i, info, g->proc);
            fn_80181470(g);
            return;
        }
    }
}

/* find gmap by chapter id */
GMap* fn_80184648(const char* id)
{
    for (int i = 0; i < 2; i++) {
        if (lbl_804CB908[i] != NULL && fn_80291188(lbl_804CB908[i]->info->id, id) == 0) {
            return lbl_804CB908[i];
        }
    }
    return NULL;
}

}
