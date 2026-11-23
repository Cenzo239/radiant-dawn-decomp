/* GMap init. StringPool is scaffolding: it sets the pool offsets and is not game code. The zero stores are written out one by one; the source was probably array member constructors or loops. */
#include "game/rF_8017F400/types.h"
#pragma pool_strings on
extern "C" {
void StringPool(const char** p) {
    p[0] = "gmap/tpl/gmap.tpl"; p[1] = "gmap/tpl/gmap_w.tpl"; p[2] = "mess/e_%s.m"; p[3] = "GID_0105"; p[4] = "gmap/rect/%s_w.bin"; p[5] = "gmap/rect/%s.bin"; p[6] = "gmap/curve/linedefine%d.bin"; p[7] = "gmap/curve/%s.bin"; p[8] = "EID_POINT_APP";
}
typedef struct GN { u8 pad[8]; s16 x8; u8 padA[0x18-0xA]; u32 x18; } GN;
typedef struct GM { u8 pad[0x30]; GN* node; } GM;
typedef struct GR { u8 pad[4]; u16 x4; } GR;
typedef struct GMap {
    u8 pad[8]; int x8; u8 xc; u8 padd[3]; f32 x10, x14, x18, x1c; u8 pad20[8]; u8 x28; u8 pad29[7]; GR* x30;
    u8 x34[0xd5-0x34]; u8 xd5[0x198-0xd5]; u8 x198[0x214-0x198]; s16 x214, x216, x218, x21a; GM* x21c; char x220[0x24]; f32 x244;
} GMap;
extern int fn_801D09F0(void);
extern char* strcpy(char*, const char*);
extern GM* fn_800E3C04(const char*, void*);
extern void fn_800E48AC(GM*, f32, f32, f32);
void fn_80183FE8(GMap* g, int idx, GR* r, void* arch) {
    char b[0x28];
    g->xc = idx;
    g->x30 = r;
    g->x8 = 0;
    g->x10 = 0.0f; g->x14 = 0.0f; g->x18 = 1.0f; g->x1c = 1.0f;
    g->x28 = 0xff;
    g->x244 = idx * 10 + 0x3b6;
((u8*)g)[0x34] = 0; ((u8*)g)[0x3c] = 0; ((u8*)g)[0x44] = 0; ((u8*)g)[0x4c] = 0; ((u8*)g)[0x54] = 0; ((u8*)g)[0x5c] = 0; ((u8*)g)[0x64] = 0; ((u8*)g)[0x6c] = 0; ((u8*)g)[0x74] = 0; ((u8*)g)[0x7c] = 0; ((u8*)g)[0x84] = 0; ((u8*)g)[0x8c] = 0; ((u8*)g)[0x94] = 0; ((u8*)g)[0x9c] = 0; ((u8*)g)[0xa4] = 0; ((u8*)g)[0xac] = 0; ((u8*)g)[0xb4] = 0; ((u8*)g)[0xbc] = 0; ((u8*)g)[0xc4] = 0; ((u8*)g)[0xcc] = 0; ((u8*)g)[0xd5] = 0; ((u8*)g)[0xe1] = 0; ((u8*)g)[0xed] = 0; ((u8*)g)[0xf9] = 0; ((u8*)g)[0x105] = 0; ((u8*)g)[0x111] = 0; ((u8*)g)[0x11d] = 0; ((u8*)g)[0x129] = 0; ((u8*)g)[0x135] = 0; ((u8*)g)[0x141] = 0; ((u8*)g)[0x14d] = 0; ((u8*)g)[0x155] = 0; ((u8*)g)[0x15d] = 0; ((u8*)g)[0x165] = 0; ((u8*)g)[0x16d] = 0; ((u8*)g)[0x175] = 0; ((u8*)g)[0x17d] = 0; ((u8*)g)[0x185] = 0; ((u8*)g)[0x18d] = 0;
*(s16*)((u8*)g + 0x198) = 0; *(s16*)((u8*)g + 0x1a8) = 0; *(s16*)((u8*)g + 0x1b8) = 0; *(s16*)((u8*)g + 0x1c8) = 0; *(s16*)((u8*)g + 0x1d8) = 0; *(s16*)((u8*)g + 0x1e8) = 0; *(s16*)((u8*)g + 0x1f8) = 0; *(s16*)((u8*)g + 0x208) = 0;
    switch (r->x4) {
    case 0:
        if (fn_801D09F0() == 0) strcpy(g->x220, "gmap/tpl/gmap_zentai.cms"); else strcpy(g->x220, "gmap/tpl/gmap_zentai_w.cms");
        strcpy(b, "EID_GMAP_HAZE");
        break;
    case 1:
        if (fn_801D09F0() == 0) strcpy(g->x220, "gmap/tpl/gmap_dayne.cms"); else strcpy(g->x220, "gmap/tpl/gmap_dayne_w.cms");
        strcpy(b, "EID_GMAP_HAZE_RU");
        break;
    case 2:
        if (fn_801D09F0() == 0) strcpy(g->x220, "gmap/tpl/gmap_crimea.cms"); else strcpy(g->x220, "gmap/tpl/gmap_crimea_w.cms");
        strcpy(b, "EID_GMAP_HAZE_LU");
        break;
    case 3:
        if (fn_801D09F0() == 0) strcpy(g->x220, "gmap/tpl/gmap_tokasakusen.cms"); else strcpy(g->x220, "gmap/tpl/gmap_tokasakusen_w.cms");
        strcpy(b, "EID_GMAP_HAZE");
        break;
    }
    g->x21c = fn_800E3C04(b, arch);
    fn_800E48AC(g->x21c, 304.0f, 224.0f, 0.0f);
    g->x21c->node->x8 = (int)(g->x244 - 8.0f);
    g->x21c->node->x18 |= 0x8000004;
    g->x21c->node->x18 &= ~0x8000;
    g->x218 = 0;
    g->x216 = 0;
    g->x214 = 1;
    g->x21a = 0xff;
}
}
