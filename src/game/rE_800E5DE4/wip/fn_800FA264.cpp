/* 800FA264: 5 of 203 words. The first (c[2]+c[3]+c[4])/3 uses r6/r7 where this gives r4/r6: li r4,1 looks live before the add. About 20 spellings tried. */
#include "game/rE_800E5DE4/mapunit.h"
#pragma auto_inline off
typedef f32 Mtx34[3][4];
typedef f32 Mtx44[4][4];
extern "C" {
extern void* lbl_804CB730;
extern u8* lbl_804CB810;
extern u8 lbl_803CAB38[];
extern u8 lbl_803EC898[];
extern void fn_80006A64(void*, void*, int);
extern void fn_80022254(void*, int);
extern void fn_80021B68(int);
extern void fn_803031CC(void);
extern void fn_80302B80(int, int);
extern void fn_80303200(int, int, int, int, int);
extern void fn_80021B2C(int);
extern void fn_80021A08(int, int, int, int, int, int, int);
extern void fn_80021BF4(int);
extern void fn_80021CB4(int, int, int, int);
extern void fn_80021C34(int);
extern void fn_803128AC(f32*, f32, f32, f32);
extern f32* fn_8000FB88(void);
extern void fn_80312378(f32*, f32*, f32*);
extern void fn_80307E48(f32*, int);
extern void fn_80021784(int);
extern void fn_80021860(int, int, int);
extern void fn_80021BA4(int, int, int, int);
extern void fn_80021808(int, int, int, int, int);
extern void fn_80021EF8(int, int);
extern u8* fn_80010BB0(int);
extern u8* fn_80010DA4(u8*, int);
extern void fn_8010E41C(u8*, int);
extern void fn_800F98E4(MapUnit*, int, int, int);
extern void fn_80011838(int);
extern void fn_800218A8(int, GXColor);
extern int fn_80117A0C(void*, int, int);
extern void fn_800FA590(MapUnit*, int);

static inline MapUnit* UnitAt(u8 id) {
    return id ? (MapUnit*)(lbl_804CB810 + (id - 1) * 0x3F0) : 0;
}
static inline int Vis(MapUnit* m) {
    if (m->flags2 & 0x40100009CULL) return 0;
    if ((m->flags2 & 0x240) == 0x40) return 0;
    if ((m->flags & 0x22U) != 2) return 0;
    return m->unk33 != 0;
}
void fn_800FA264(void) {
    u8 seen[0x10];
    u8 tex[0x20];
    f32 b[3][4];
    f32 a[3][4];
    fn_80006A64(lbl_804CB730, tex, 0);
    fn_80022254(tex, 0);
    fn_80021B68(2);
    fn_803031CC();
    fn_80302B80(9, 1);
    fn_80302B80(0xB, 1);
    fn_80303200(0, 9, 1, 4, 0);
    fn_80303200(0, 0xB, 1, 5, 0);
    fn_80021B2C(1);
    fn_80021A08(4, 0, 1, 1, 0, 0, 2);
    fn_80021BF4(1);
    fn_80021CB4(0, 0, 0, 4);
    fn_80021C34(1);
    fn_803128AC(&a[0][0], 0.0f, 0.0f, -0.015f);
    fn_80312378(fn_8000FB88(), &a[0][0], &b[0][0]);
    fn_80307E48(&b[0][0], 0);
    fn_80021784(0);
    fn_80021860(1, 3, 0);
    fn_80021BA4(1, 4, 5, 7);
    fn_80021808(7, 0, 1, 7, 0);
    fn_80021EF8(0, 0);
    u8* c = fn_80010BB0(1);
    int base = (c[2] + c[3] + c[4]) / 3;
    int v = base;
    u8* e = fn_80010DA4(c, 1);
    if (e) v = (e[4] + e[5] + e[6]) / 3;
    v = v * (255 - base) / 255;
    if (v < 0) v = 0;
    if (v > 255) v = 255;
    fn_8010E41C(seen, 3);
    for (int i = 1; i <= 254; i++) {
        MapUnit* m = UnitAt(i);
        if (m->tbl && seen[m->unkF4->unk8] && Vis(m) && (m->flags & 0x200)) {
            fn_800F98E4(m, m->joints[10], m->joints[11], v);
            if (m->joints[12] >= 0 && m->joints[13] >= 0) fn_800F98E4(m, m->joints[12], m->joints[13], v);
        }
    }
    fn_80011838(-1);
}
}
