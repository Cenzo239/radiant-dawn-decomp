/* fn_80181788: gmap: release resources. */
#include "game/rF_8017F400/gmap.h"

#pragma auto_inline off

extern "C" {

extern void fn_80006A2C(void* p);         /* release resource handle */
extern void fn_800763E0(const char* path); /* unload message file */
extern int fn_801D09F0(void);             /* widescreen? */
extern void* lbl_8041C9D8[8];             /* gmap/curve/linedefine%d.bin */

/* gmap: release resources */
void fn_80181788(GMap* g) {
    /*P*/
    int j;
    int i;
    int z;
    GMapCurve* c;
    void** w;
/*E*/
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
    w = lbl_8041C9D8 + 1;
    for (i = 1; i <= 8; i++, w++) {
        fn_8023F1A8(w[-1]);
    }
    z = 0;
    c = g->curves;
    for (j = 0; j < 8; j++, c++) {
        c->flags = z;
        if (c->data != NULL) {
            fn_8023F1A8(c->data);
            c->data = NULL;
        }
    }
}

}
