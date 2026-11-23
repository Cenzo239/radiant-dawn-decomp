/* fn_80181788: near miss, 14 of 86 words differ (r29/r30 swapped between loop counter and pointer in both loops) */
#include "game/rF_8017F400/gmap.h"

#pragma auto_inline off

extern "C" {

extern void fn_80006A2C(void* p);         /* release resource handle */
extern void fn_800763E0(const char* path); /* unload message file */
extern int fn_801D09F0(void);             /* widescreen? */
extern void* lbl_8041C9D8[8];             /* gmap/curve/linedefine%d.bin */

/* gmap: release resources */
void fn_80181788(GMap* g)
{
    int i;
    GMapCurve* c;
    char path[0x88];

    fn_80006A2C(g);
    fn_80006A2C(&g->tpl2);
    if (g->info->mess != NULL) {
        fn_80290DDC(path, lbl_8036BA4C + 0x26 /* "mess/e_%s.m" */, g->info->mess);
        fn_800763E0(path);
    }
    if (g->info->rect != NULL) {
        if (fn_80291188(lbl_80387D10[0].id, lbl_8036BA4C + 0x32 /* "GID_0105" */) == 0 && fn_801D09F0()) {
            fn_80290DDC(path, lbl_8036BA4C + 0x3B /* "gmap/rect/%s_w.bin" */, g->info->rect);
        } else {
            fn_80290DDC(path, lbl_8036BA4C + 0x4E /* "gmap/rect/%s.bin" */, g->info->rect);
        }
        fn_800763E0(path);
    }
    for (i = 1; i <= 8; i++) {
        fn_8023F1A8(lbl_8041C9D8[i - 1]);
    }
    for (i = 0; i < 8; i++) {
        c = &g->curves[i];
        c->flags = 0;
        if (c->data != NULL) {
            fn_8023F1A8(c->data);
            c->data = NULL;
        }
    }
}

}
