/* fn_801820CC: world map draw, one label per country. */
#include "game/rF_8017F400/types.h"
extern "C" {
typedef struct TexH { u16 x0, x2; } TexH;
extern void* fn_80006A0C(void*, int);
extern u8* fn_800CD204(int);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
#if TARGET_PC
extern FE10_PROTO void fn_8007E174(p32arg, int);
#else
extern void fn_8007E174(int, int);
#endif
extern void fn_8007E4E4(f32, f32, f32, f32);
extern void fn_8007E7DC(int);
extern void fn_8007E7E8(int);
extern void fn_801BCA5C(f32);
extern void fn_801BCA94(void);
extern void fn_801BC88C(void* a, int b, GXColor c, int d, u32 fl, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, f32 f7, f32 f8);
extern void fn_800800D4(int);
extern void fn_80080308(void);
extern void fn_80080330(f32, f32);
extern void fn_80080388(f32, f32, f32, f32);
extern void fn_800804D4(int, int, int, int);
extern void fn_80080508(GXColor);
extern void fn_80080578(int);
extern void fn_80080A94(f32);
extern void fn_80080C24(const char*);
extern int fn_801D09F0(void);
extern int fn_80290DDC(char*, const char*, ...);
typedef struct Ent { u8 x0; s8 x1; s16 x2; s16 x4; s8 x6; u8 x7; } Ent;
typedef struct GMap { void* x0; void* x4; u8 pad8[0xc-8]; u8 xc; u8 padd[0x10-0xd]; f32 x10, x14, x18, x1c, x20, x24; u8 x28; u8 pad29[0x14c-0x29]; Ent ent[9]; u8 pad[0x244-0x194]; f32 x244; } GMap;
extern void* lbl_804CB908[2];
extern void fn_8007E5C0(f32, f32, f32, f32, f32, f32, f32, f32);
#if TARGET_PC
extern FE10_PROTO void fn_8007E374(void*, p32arg, int);
#else
extern void fn_8007E374(void*, int, int);
#endif
extern void fn_80080348(f32, f32, f32, f32);
extern void fn_80080368(f32, f32, f32, f32);
extern void fn_800804F4(int);
#if TARGET_PC
extern FE10_PROTO void fn_80080910(ptr32<const void>, ptr32<const void>);
#else
extern void fn_80080910(void*, void*);
#endif
extern void fn_80182D24(void* p);
extern int fn_800CA3DC(const char*, int, f32);
extern char* fn_800D0864(const char*);
static inline void DrawK(GMap* m, Ent* e, int tile, f32 off, f32 w, f32 h, f32 sc) {
    GXColor k = { 0xff, 0xff, 0xff, e->x7 };
    fn_801BC88C(m->x0, tile, k, 0x11, 0, e->x2 + off, e->x4, e->x2 + off + w * sc, e->x4 + h, 0.0f, 0.0f, w, h);
}
void fn_801820CC(GMap* m) {
    /*P*/
    Ent* e;
    GMap* q;
    int i;
    u8* c;
    int tile;
    const char* s;
    f32 w;
    f32 h;
/*E*/
    fn_8007E154();
    fn_8007E5C0(m->x10, m->x14, m->x244, 0.0f, 0.0f, m->x18, m->x1c, 0.0f);
    fn_8007E7DC(m->x28);
    fn_8007E164();
    fn_8007E154();
    fn_8007E374(m->x4, 0, 0x11);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080348(0.0f, 0.0f, 0.0f, 0.0f);
    fn_80080368(m->x20, m->x24, m->x20, m->x24);
    fn_800804D4(0xff, 0xff, 0xff, 0xff);
    fn_80080308();
    fn_801BCA5C(-2.0f);
    fn_8007E154();
    fn_8007E5C0(0.0f, 0.0f, 925.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    fn_8007E164();
    q = m;
    e = m->ent;
    for (i = 0; i < 9; i++, e++, q = (GMap*)((u8*)q + 8)) {
        const char* names[9] = {
            "MS_CHIMEI_CRIMEA", "MS_CHIMEI_GALIA", "MS_CHIMEI_DAYNE", "MS_CHIMEI_BEGNION", "MS_CHIMEI_SERINOS",
            "MS_CHIMEI_KILVAS", "MS_CHIMEI_PHENICIS", "MS_CHIMEI_GOLDOA", "MS_CHIMEI_HATALI",
        };
        GXColor cols[9] = {
            { 0xcf, 0xe7, 0x9a, 0x00 }, { 0x6c, 0x92, 0x62, 0x00 }, { 0xed, 0xc1, 0xbb, 0x00 }, { 0xa2, 0xc5, 0xf6, 0x00 },
            { 0x00, 0x80, 0x80, 0x00 }, { 0x75, 0x71, 0x6b, 0x00 }, { 0x97, 0x74, 0x4e, 0x00 }, { 0xc9, 0xb9, 0xd4, 0x00 },
            { 0x6d, 0x93, 0x83, 0x00 },
        };
        if (q->ent[0].x1 == 0) continue;
        if (!(e->x0 & 1)) {
            TexH** t = (TexH**)fn_80006A0C(m->x0, 0x17);
            w = (*t)->x2;
            h = (*t)->x0;
            fn_8007E154();
            fn_8007E374(m->x0, 0x17, 0x10);
            fn_8007E164();
            c = (u8*)&cols[e->x6];
            fn_800800D4(1);
            fn_80080388(e->x2 + 0x24, e->x4 + 0x16, w, h);
            fn_800804D4(c[0], c[1], c[2], e->x7);
            fn_800804F4(e->x7);
            fn_80080308();
        }
        fn_801BCA5C(-1.0f);
        tile = (u16)(e->x6 + 9);
        {
        TexH** t = (TexH**)fn_80006A0C(m->x0, tile);
        f32 sc;
        w = (*t)->x2;
        h = (*t)->x0;
        if (fn_801D09F0()) sc = 0.764f; else sc = 1.0f;
        {
        f32 off = 0.5f * ((1.0f - sc) * w);
        DrawK(m, e, tile, off, w, h, sc);
        }
        }
        if (!(e->x0 & 1)) {
            int tw;
            s = names[e->x6];
            fn_801BCA94();
            fn_800800D4(5);
            tw = fn_800CA3DC(fn_800D0864(s), -1, 0.8f);
            f32 fx = e->x2 + 0x73 - tw / 2; fn_80080330(fx, e->x4 + 0x1a);
            fn_800804D4(0, 0, 0, e->x7);
            fn_80080A94(0.8f);
            fn_80080C24(fn_800D0864(s));
            fn_80080308();
        }
        fn_801BCA5C(1.0f);
    }
    fn_8007E154();
    fn_8007E374(m->x0, 0, 0x10);
    fn_8007E164();
    fn_800800D4(0xb);
    fn_80080910((void*)fn_80182D24, lbl_804CB908[m->xc]);
    fn_80080308();
    fn_8007E154();
    fn_8007E7DC(0xff);
    fn_8007E164();
}
}
