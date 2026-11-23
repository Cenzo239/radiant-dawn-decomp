#include "game/rF_8017F400/gmap.h"

#pragma auto_inline off

extern "C" {

/* load gmap/curve/<name>.bin into a free curve slot */
void fn_8018277C(GMap* g, const char* name)
{
    char path[0x80];
    GMapCurve* c = g->curves;
    for (int i = 0; i < 8; i++, c++) {
        if (!(c->flags & 1)) {
            c->pos = 0;
            c->unk2 = 0;
            c->flags = 1;
            c->unk6 = 0;
            c->unk8 = 0xAA;
            c->unkA = 100;
            fn_80290DDC(path, lbl_8036BA4C + 0x7B /* "gmap/curve/%s.bin" */, name);
            c->data = (GMapCurveData*)fn_8023F1A4(path, 0);
            c->data->points = (u8*)c->data + 0x30;
            return;
        }
    }
}

static inline GMapCurve* GMap_FindCurve(GMap* g, const char* name)
{
    GMapCurve* c = g->curves;
    for (int i = 0; i < 8; i++, c++) {
        if ((c->flags & 1) && fn_80291188(name, c->data->name) == 0) {
            return c;
        }
    }
    return NULL;
}

void fn_80182820(GMap* g, const char* name)
{
    GMapCurve* c = GMap_FindCurve(g, name);
    c->flags |= 2;
    c->pos = 1;
    c->unk8 = 0xAA;
}

void fn_801828B8(GMap* g, const char* name)
{
    GMapCurve* c = GMap_FindCurve(g, name);
    c->flags |= 2;
    c->pos = 0;
    c->unk6 = c->data->count;
    c->unk8 = 0xAA;
}

void fn_8018295C(GMap* g, const char* name)
{
    GMapCurve* c = GMap_FindCurve(g, name);
    c->flags &= ~2;
    c->pos = 0;
    c->unk6 = 0;
}

void fn_801829F0(GMap* g, const char* name, BOOL on)
{
    GMapCurve* c = GMap_FindCurve(g, name);
    if (on) {
        c->flags |= 2;
    } else {
        c->flags &= ~2;
    }
}

void fn_80182A9C(GMap* g, const char* name, BOOL on)
{
    GMapCurve* c = GMap_FindCurve(g, name);
    if (on) {
        c->flags |= 4;
    } else {
        c->flags &= ~4;
    }
}

}
