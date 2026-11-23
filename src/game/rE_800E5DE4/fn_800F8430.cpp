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
#if TARGET_PC
extern FE10_PROTO void fn_8000F9E8(p32arg, f32, f32, f32, f32);
extern FE10_PROTO void fn_8000F9C8(p32arg, int, int, int, int);
extern FE10_PROTO void fn_8000FF74(p32arg);
extern FE10_PROTO void fn_80020354(int, int, int, int, p32arg, f32);
#else
extern void fn_8000F9E8(int, f32, f32, f32, f32);
extern void fn_8000F9C8(int, int, int, int, int);
extern void fn_8000FF74(int);
extern void fn_80020354(int, int, int, int, int, f32);
#endif
extern u8 lbl_804CB73F;
extern void* lbl_804CB738;
#if TARGET_PC
/* Host: C++ does not allow a type defined in a return type. MWCC allocates bitfields from the
   MSB (b = bit 3), clang from the LSB: bitfield order is still to be fixed (P2 bitfield audit). */
struct Opt44B { u32 pad:28; u32 b:1; };
extern Opt44B* fn_80060728(void*);
#else
extern struct { u32 pad:28; u32 b:1; }* fn_80060728(void*);
#endif
extern void fn_80021E20(int, int, int, int, int);
extern void fn_80021D18(int, int, int, int, int, int);
extern void fn_80021E8C(int, int, int, int, int);
extern void fn_80021D9C(int, int, int, int, int, int);
extern void fn_80021F7C(int, int, int, int);
#if TARGET_PC
extern FE10_PROTO void fn_800104DC(p32arg);
extern FE10_PROTO void fn_800100C8(p32arg);
#else
extern void fn_800104DC(int);
extern void fn_800100C8(int);
#endif
extern void fn_800F8044(MapUnit*, f32);
extern void fn_800F8294(f32);
extern int fn_80131DC4(void);
extern void fn_80131DD4(int);
extern void fn_8001F4D8(int, int, int, int, int, int, void*, int, int);
void fn_800F8430(void) {
    u8 seen[0x10];
    u8 tex[0x20];
    fn_8000F9E8(0, 0.0f, 0.0f, 152.0f, 112.0f);
    fn_8000F9C8(0, 0, 0, 0x98, 0x70);
    fn_8000FF74(0);
    fn_80020354(0, 0, 0x98, 0x70, 0, 0.0f);
    if (lbl_804CB73F && !fn_80060728(lbl_803CAB38)->b) {
        fn_80006A64(lbl_804CB730, tex, 2);
        fn_80022254(tex, 0);
        fn_803031CC();
        fn_80302B80(9, 1);
        fn_80302B80(0xB, 1);
        fn_80302B80(0xD, 1);
        fn_80303200(0, 9, 1, 4, 0);
        fn_80303200(0, 0xB, 1, 5, 0);
        fn_80303200(0, 0xD, 1, 4, 0);
        fn_80021C34(1);
        fn_80021F7C(0, 1, 4, 0x3C);
        fn_80021B2C(1);
        fn_80021A08(4, 0, 1, 1, 0, 0, 2);
        fn_80021BF4(1);
        fn_80021CB4(0, 0, 0, 4);
        fn_80021B68(0);
        fn_80021E20(0, 0xF, 8, 0xA, 0xF);
        fn_80021D18(0, 0, 0, 0, 1, 0);
        fn_80021E8C(0, 7, 7, 7, 6);
        fn_80021D9C(0, 0, 0, 0, 1, 0);
        fn_80021BA4(1, 1, 1, 0);
        fn_80021860(0, 3, 0);
        fn_800104DC(0);
        fn_8000F9E8(0, 0.0f, 0.0f, 152.0f, 112.0f);
        fn_8000F9C8(0, 0, 0, 0x98, 0x70);
        fn_800100C8(0);
        fn_8010E41C(seen, 3);
        for (int i = 1; i <= 254; i++) {
            MapUnit* m = UnitAt(i);
            if (m->tbl && seen[m->unkF4->unk8] && Vis(m)) {
                fn_800F8044(m, 0.5f);
            }
        }
        if (fn_80131DC4()) {
            fn_800F8294(1.0f);
            fn_80131DD4(0);
        }
    }
    fn_8001F4D8(0, 0, 0x98, 0x70, 0x98, 0x70, lbl_804CB738, 0x20, 1);
    fn_800104DC(0);
    fn_80011838(-1);
}
}
