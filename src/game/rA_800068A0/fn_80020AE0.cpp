#include "game/rA_800068A0/types.h"
/* Flat-colour screen quad through the GX state cache. */
extern "C" {
extern u8 lbl_804CB0D8;
extern u8 lbl_804CB0E4;
extern u8 lbl_804CB0E5;
extern u32 lbl_804CB0DC;
extern u32 lbl_804CB0E0;
extern u32 lbl_804CB0C0;
extern u32 lbl_804CB0C4;
extern u32 lbl_803BF878[16];
extern u32 lbl_803BF8B8[16];
extern u32 lbl_803BF8F8[16];
extern u32 lbl_803BF938[16];
extern u32 lbl_803BF978[16];
extern u32 lbl_803BF9B8[16];
extern void fn_803031CC(void);
extern void fn_80302B80(int, int);
extern void fn_80303200(int, int, int, int, int);
extern void fn_80305794(int);
extern void fn_80021A08(int, int, int, int, int, int, int);
extern void fn_8030385C(int);
extern void fn_80307274(int);
extern void fn_80306C18(int, int);
extern void fn_80307118(int, int, int, int);
extern void fn_80307748(int, int, int, int);
extern void fn_803077F0(int, int, int);
extern void fn_80307054(int, int, int, int, int);
extern void fn_803045DC(int);
extern void fn_80307798(int);
extern void fn_80304314(int, int, int);
extern void fn_80011838(int);
#define WGF (*(volatile f32*)0xCC008000)
#define WGB (*(volatile u8*)0xCC008000)
static inline void vtx(f32 x, f32 y, f32 z) {
    WGF = x;
    WGF = y;
    WGF = z;
    WGB = 0;
    WGB = 0;
    WGB = 0;
    WGB = 0xFF;
}
static inline void sE4(int n) {
    if (lbl_804CB0E4 != n) {
        fn_80307274(n);
        lbl_804CB0E4 = n;
    }
}
void fn_80020AE0(int x, int y, int w, int h, f32 z) {
    fn_803031CC();
    fn_80302B80(9, 1);
    fn_80302B80(0xB, 1);
    fn_80303200(0, 9, 1, 4, 0);
    fn_80303200(0, 0xB, 1, 5, 0);
    if (lbl_804CB0D8 != 1) {
        fn_80305794(1);
        lbl_804CB0D8 = 1;
    }
    fn_80021A08(4, 0, 1, 1, 0, 0, 2);
    if (lbl_804CB0E5 != 0) {
        fn_8030385C(0);
        lbl_804CB0E5 = 0;
    }
    sE4(1);
    if (lbl_803BF8B8[0] != 4) {
        lbl_803BF8F8[0] = -1;
        lbl_803BF938[0] = -1;
        lbl_803BF978[0] = -1;
        lbl_803BF9B8[0] = -1;
        fn_80306C18(0, 4);
        lbl_803BF8B8[0] = 4;
    }
    if (lbl_803BF878[0] != 0x4FFFF) {
        fn_80307118(0, 0xFF, 0xFF, 4);
        lbl_803BF878[0] = 0x4FFFF;
    }
    if (lbl_804CB0E0 != 0) {
        fn_80307748(0, 0, 0, 0);
        lbl_804CB0E0 = 0;
    }
    if (lbl_804CB0C4 != 0x10701) {
        fn_803077F0(1, 7, 1);
        lbl_804CB0C4 = 0x10701;
    }
    if (lbl_804CB0C0 != 0x7100) {
        fn_80307054(0, 0, 1, 7, 0);
        lbl_804CB0C0 = 0x7100;
    }
    if (lbl_804CB0DC != 0) {
        fn_803045DC(0);
        lbl_804CB0DC = 0;
    }
    fn_80307798(0);
    fn_80304314(0x98, 0, 4);
    vtx(x, y, z);
    vtx(x + w, y, z);
    vtx(x, y + h, z);
    vtx(x + w, y + h, z);
    fn_80307798(1);
    fn_80011838(-1);
}
}
