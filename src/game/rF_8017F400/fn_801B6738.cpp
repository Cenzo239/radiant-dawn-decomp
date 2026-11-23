/* fn_801B6738: unit list: draw each visible row's 3D unit model (tilted, scaled, greyed by the sort column state). */
#include "game/rF_8017F400/types.h"
#pragma use_lmw_stmw off
extern "C" {
typedef struct Vec3 { f32 x, y, z; } Vec3;
typedef struct Mtx34 { f32 m[3][4]; } Mtx34;
struct LEnt { u8* u; u8* h; u8 pad8[0x1c - 8]; };
typedef struct LView {
    u8 pad[0x38];
    LEnt* ents;
    u8 pad3C[0x61 - 0x3C];
    u8 n;
    u8 pad62[0x6A - 0x62];
    s16 x6A;
    u8 x6C;
} LView;
extern void fn_80312654(Mtx34*, int, f32);
extern void fn_8031292C(Mtx34*, f32, f32, f32);
extern void fn_80312378(Mtx34*, Mtx34*, void*);
extern void fn_803128AC(Mtx34*, f32, f32, f32);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32, f32, f32, f32);
#if TARGET_PC
extern FE10_PROTO void fn_8007E174(p32arg, int);
#else
extern void fn_8007E174(int, int);
#endif
extern void fn_8007E7DC(int);
extern void fn_8007E7B4(void);
#if TARGET_PC
extern FE10_PROTO void fn_8007E74C(ptr32<const void>, ptr32<const void>);
#else
extern void fn_8007E74C(void*, void*);
#endif
extern void fn_800800D4(int);
#if TARGET_PC
extern FE10_PROTO void fn_80080910(ptr32<const void>, ptr32<const void>);
#else
extern void fn_80080910(void*, void*);
#endif
extern void fn_80080308(void);
extern Vec3 fn_800FB178(u8*, f32);
extern void fn_80008F10(void*, u8, u8, u8);
extern void fn_80008F20(void*, u8);
extern void fn_80008F64(void*, u8);
extern void fn_800081D4(void*);
extern void fn_80007C58(void*);
extern void fn_800F629C(void*, void*);
extern void fn_800F7E40(int);
extern void fn_801B5E78(void);
extern void fn_801B5E8C(void);
extern void fn_801B5EA0(void);
extern void fn_801B6698(void);
extern void fn_801B66E8(void);
extern void fn_8001A4DC(void*);
static inline BOOL RowVis(LView* p, int k) {
    int a = p->x6A / 32;
    int b = a + 8;
    if (p->x6A % 32 != 0) b++;
    if (k >= a && k <= b) return TRUE;
    return FALSE;
}
void fn_801B6738(LView* p) {
    Mtx34 t;
    Mtx34 rx;
    Mtx34 ry;
    Mtx34 rx2;
    Mtx34 s;
    int k;
    f32 sc;
    fn_80312654(&rx, 'X', 3.1415927f);
    fn_80312654(&ry, 'Y', 0.5235988f);
    fn_80312654(&rx2, 'X', 0.5235988f);
    fn_8031292C(&s, 2.5f, 2.5f, 2.5f);
    fn_80312378(&rx, &s, &s);
    fn_80312378(&ry, &s, &s);
    fn_80312378(&rx2, &s, &s);
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 201.0f, 1.0f);
    fn_8007E174(0, 0x410);
    fn_8007E7DC(0xFF);
    fn_8007E74C((void*)fn_801B5EA0, 0);
    fn_8007E164();
    fn_800800D4(0xB);
    fn_80080910((void*)fn_801B6698, 0);
    fn_80080308();
    sc = 0.625f;
    for (k = p->n - 1; k >= 0; k--) {
        u8* u = p->ents[k].u;
        u8* h = p->ents[k].h;
        Vec3 v = fn_800FB178(u, sc);
        f32 x = 56.0f + v.x;
        f32 y = 20.0f + (v.y + (k * 32 + 0x68 - p->x6A));
        if (RowVis(p, k)) {
            fn_80008F10(h, 0x80, 0x80, 0x80);
            switch (p->x6C) {
            case 1:
                if (*(u32*)(u + 0x10C) & 0x10) fn_80008F10(h, 0x40, 0x40, 0x40);
                break;
            case 2:
                if (!(*(u32*)(u + 0x10C) & 0x400000)) fn_80008F10(h, 0x40, 0x40, 0x40);
                break;
            }
            fn_803128AC(&t, x, y, 200.0f);
            fn_80312378(&t, &s, h + 0x10);
            fn_80008F20(h, 0xFF);
            fn_80008F64(h, 0xFF);
            fn_800081D4(h);
            fn_80007C58(h);
            fn_800F629C(u, h);
            fn_8007E154();
            fn_8007E4E4(0.0f, 0.0f, 200.0f, 1.0f);
            fn_8007E174(0, 0x410);
            fn_8007E7DC(0xFF);
            if (p->x6A % 32 != 0) fn_8007E74C((void*)fn_801B5E78, 0);
            fn_8007E164();
            fn_800800D4(0xB);
            fn_80080910((void*)fn_8001A4DC, h);
            fn_80080308();
            fn_800800D4(0xB);
            fn_80080910((void*)fn_801B66E8, 0);
            fn_80080308();
        }
    }
    fn_8007E154();
    fn_8007E74C((void*)fn_801B5E8C, 0);
    fn_8007E164();
    fn_800F7E40(100);
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
}
}
