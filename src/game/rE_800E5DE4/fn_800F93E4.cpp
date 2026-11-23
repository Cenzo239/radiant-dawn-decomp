#include "game/rE_800E5DE4/mapunit.h"
#pragma auto_inline off
#pragma use_lmw_stmw on
extern "C" {
extern void fn_80008F10(void*, u8, u8, u8);
extern void fn_80008F20(void*, u8);
extern void fn_8001B254(void*);
extern void fn_800180F0(void*);
extern void fn_80007C58(void*);
static inline int Vis(MapUnit* m) {
    if (m->flags2 & 0x40100009CULL) return 0;
    if ((m->flags2 & 0x240) == 0x40) return 0;
    if ((m->flags & 0x22U) != 2) return 0;
    return m->unk33 != 0;
}
static inline void SetC(MapUnit* m, int i) {
    GXColor t[14] = {{0x80,0x80,0x80,0xFF}, {0xFF,0xFF,0xE0,0xFF}, {0x40,0x40,0x40,0xFF}, {0xFF,0xFF,0xFF,0x00}, {0xFF,0xFF,0xFF,0xFF}, {0x00,0x00,0x00,0xFF}, {0x80,0x00,0x00,0xFF}, {0x00,0x80,0x00,0xFF}, {0x00,0x00,0x80,0xFF}, {0x80,0x80,0x00,0xFF}, {0x80,0x00,0x80,0xFF}, {0x40,0x40,0x40,0xFF}, {0xFF,0xFF,0xFF,0xFF}, {0xFF,0xFF,0xFF,0x00}};
    GXColor c = t[i];
    void* mdl = m->model;
    if (mdl) {
        fn_80008F10(mdl, c.r, c.g, c.b);
        fn_80008F20(mdl, c.a);
    }
}
void fn_800F93E4(MapUnit* m) {
    void* mdl = m->model;
    if (!Vis(m) && (m->flags & 0x22U) == 2 && (((const MapUnit*)m)->flags2 & 0x10000DCULL) == 0x40) {
        SetC(m, 11);
        fn_8001B254(mdl);
        fn_800180F0(mdl);
        fn_80007C58(mdl);
    }
}
}
