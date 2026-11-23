/* gmap: load resources; curve definitions are byte-swapped once on first load. */
#include "game/rF_8017F400/gmap.h"
#pragma auto_inline off
extern "C" {
extern void* memcpy(void*, const void*, u32);
extern void fn_800068A0(void* out, const char* path);
extern void** fn_80006A0C(void* res, int i);
extern void fn_80075D78(const char* path);
extern int fn_801D09F0(void);
extern u8* lbl_8041C9D8[8];
struct LFile { u64 a; u64 b; u32 flag; };
static inline u64 Sw(u64 v) {
    return ((v & 0xFF00000000000000ULL) >> 56) | ((v & 0xFF000000000000ULL) >> 40) | ((v & 0xFF0000000000ULL) >> 24) | ((v & 0xFF00000000ULL) >> 8) | ((v & 0xFF000000ULL) << 8) | ((v & 0xFF0000ULL) << 24) | ((v & 0xFF00ULL) << 40) | (v << 56);
}
static inline void SwapIn(u64* p) { u64 v = Sw(*p); memcpy(p, &v, 8); }
void fn_80181470(GMap* g) {
    /*P*/
    u8** w;
    int i;
    u32 r0;
    /*E*/
    char path[0x80];
    char name[0x80];
    if (fn_801D09F0() == 0) {
        fn_800068A0(g, lbl_8036BA4C);
    } else {
        fn_800068A0(g, lbl_8036BA4C + 0x12);
    }
    fn_800068A0(&g->tpl2, (char*)g + 0x220);
    {
        u16** d = (u16**)fn_80006A0C(g->tpl2, 0);
        g->width = (*d)[1];
        g->height = (*d)[0];
    }
    if (g->info->mess != NULL) {
        fn_80290DDC(path, lbl_8036BA4C + 0x26, g->info->mess);
        fn_80075D78(path);
    }
    if (g->info->rect != NULL) {
        if (fn_80291188(lbl_80387D10[0].id, lbl_8036BA4C + 0x32) == 0 && fn_801D09F0()) {
            fn_80290DDC(path, lbl_8036BA4C + 0x3B, g->info->rect);
        } else {
            fn_80290DDC(path, lbl_8036BA4C + 0x4E, g->info->rect);
        }
        fn_80075D78(path);
    }
    w = lbl_8041C9D8 + 1;
    for (i = 1; i <= 8; i++, w++) {
        u8* f;
        fn_80290DDC(name, lbl_8036BA4C + 0x5F, i);
        f = (u8*)fn_8023F1A4(name, 0);
        w[-1] = f;
        if (*(int*)(f + 0x10) == 0) {
            *(int*)(f + 0x10) = 1;
            SwapIn((u64*)w[-1]);
            SwapIn((u64*)(w[-1] + 8));
        }
    }
}
}
