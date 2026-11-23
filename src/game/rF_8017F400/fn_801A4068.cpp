#include "game/rF_8017F400/types.h"
#pragma auto_inline off
#pragma pool_strings on
extern "C" {
void StringPool(const char** p) {
    p[0] = "%7d"; p[1] = "%s%s %s%s"; p[2] = "MD_TOMAP"; p[3] = "MD_LEADER"; p[4] = "MD_CUR"; p[5] = "MD_RTN";
}
struct C4 { u8 r, g, b, a; };
struct TexH { u16 x0, x2; };
typedef struct OData {
    u8 p0[8]; s8 x8; u8 p9; s16 xA; void* arch; u8 p10[0x310]; void* x320; int x324; s16 x328, x32A, x32C, x32E, x330, x332;
    u8 p334[4]; u8 x338; u8 x339; u8 p33A[6]; s16 x340;
} OData;
extern OData* lbl_804CB964;
extern u8 lbl_803CAB38[];
extern int fn_8017F990(int, int);
extern double fn_80295940(double);
extern void fn_801BCA5C(f32);
extern void fn_801BCA94(void);
extern void* fn_80006A0C(void*, int);
extern const u8* fn_800CD204(int);
extern void fn_801BC88C(void* a, int b, C4* c, int d, u32 fl, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, f32 f7, f32 f8);
extern void fn_800CB3A8(f32 a, f32 b, s16 x, s16 y, u8 c, int d, int e, const char* fmt, ...);
extern const char* fn_800D0864(const char*);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32, f32, f32, f32);
extern void fn_8007E7DC(u8);
extern f32 fn_8017F68C(int a, f32 x, f32 y, f32 t, f32 d);
extern void fn_801A4744(u8, f32, f32);
extern void fn_801A50C4(f32, f32);
extern int fn_800626E0(u8*);
extern void fn_801A5C80(f32, f32);
extern void fn_801A5ECC(f32, f32);
extern void fn_801A53DC(void);
#if TARGET_PC
extern FE10_PROTO char * fn_800CEB4C(void);
extern FE10_PROTO char * fn_800CEC24(void);
extern FE10_PROTO char * fn_800CF3A4(void);
#else
extern int fn_800CEB4C(void);
extern int fn_800CEC24(void);
extern int fn_800CF3A4(void);
#endif
extern int fn_80290DDC(char*, const char*, ...);
extern void fn_801C6D9C(char*, int, int, int);
extern void fn_800712E8(int, int, int);
extern void fn_801A5800(f32, f32);
extern void fn_801A6220(f32, f32);

static inline void Bg(int tile, f32 x, f32 y, f32 sx, f32 sy) {
    C4 t;
    C4 c;
    const u8* cp = fn_800CD204(1);
    c.r = cp[0]; c.g = cp[1]; c.b = cp[2]; c.a = 0xFF;
    TexH* q = *(TexH**)fn_80006A0C(lbl_804CB964->arch, tile);
    f32 tw = q->x2;
    f32 th = q->x0;
    *(u32*)&t = *(u32*)&c;
    fn_801BC88C(lbl_804CB964->arch, tile, &t, 0x11, 0, x, y, tw * sx + x, th * sy + y, x, y, tw, th);
}

static inline int Mode(void) { return *(u8*)&lbl_804CB964->x8; }
static inline void Win(f32 v, f32 k) { }
void fn_801A4068(void) {
    char buf[0x80];
    lbl_804CB964->x340 = (int)(126.0f * (f32)fn_80295940(3.141592f * (2.0f * (f32)fn_8017F990(0, 1000)) / 1000.0f) + 128.0f);
    fn_8007E154();
    fn_8007E7DC(lbl_804CB964->x338);
    fn_8007E4E4(0.0f, 0.0f, 150.0f, 1.0f);
    fn_8007E164();
    Bg(0, 0.0f, 0.0f, 1.0f, 1.0f);
    lbl_804CB964->x339 = (int)fn_8017F68C(0, 0.0f, 255.0f, lbl_804CB964->xA, 6.0f);
    fn_801A4744(0xFF - ((u32)lbl_804CB964->x339 >> 1), 242.0f, 72.0f);
    fn_8007E154();
    fn_8007E7DC(0xFF - lbl_804CB964->x339);
    fn_8007E164();
    fn_8007E154();
    fn_8007E7DC(lbl_804CB964->x338);
    fn_8007E164();
    fn_801A50C4(0.0f, 0.0f);
    fn_801BCA5C(-1.0f);
    fn_801BCA94();
    fn_800CB3A8(0.8f, 0.0f, 0x148, 0x180, 1, 1, 0, "%7d", *(s16*)(lbl_803CAB38 + 0x12));
    fn_800CB3A8(0.8f, 0.0f, 0x1E8, 0x180, 1, 1, 0, "%7d", fn_800626E0(lbl_803CAB38));
    fn_801BCA5C(1.0f);
    fn_801A5C80(472.0f, 28.0f);
    fn_801A5ECC(377.0f, 54.0f);
    fn_801A53DC();
    switch (lbl_804CB964->x8) {
    case 0: case 1:
        fn_80290DDC(buf, "%s%s %s%s", fn_800CEC24(), fn_800D0864("MD_TOMAP"), fn_800CEB4C(), fn_800D0864("MD_LEADER"));
        break;
    case 2: case 3:
        fn_80290DDC(buf, "%s%s %s%s", fn_800CF3A4(), fn_800D0864("MD_CUR"), fn_800CEC24(), fn_800D0864("MD_RTN"));
        break;
    }
    fn_801BCA5C(-8.0f);
    fn_801C6D9C(buf, 0xFF, 0xFF, 0);
    fn_801BCA5C(8.0f);
    if (Mode() == 2) {
        fn_801BCA5C(-50.0f);
        if (lbl_804CB964->x320) {
            if (lbl_804CB964->x324 > 0) {
                int k = 6;
                int t;
                lbl_804CB964->x324--;
                t = k - lbl_804CB964->x324;
                lbl_804CB964->x328 = (int)fn_8017F68C(4, lbl_804CB964->x32C, lbl_804CB964->x330, t, k);
                lbl_804CB964->x32A = (int)fn_8017F68C(4, lbl_804CB964->x32E, lbl_804CB964->x332, t, k);
            }
            fn_800712E8(lbl_804CB964->x328, lbl_804CB964->x32A, 1);
        }
        fn_801BCA5C(50.0f);
    }
    if (lbl_804CB964->x8 != 0) {
        fn_801BCA5C(-25.0f);
        fn_8007E154();
        fn_8007E7DC(lbl_804CB964->x339);
        fn_8007E164();
        { f32 v = fn_8017F68C(4, -100.0f, 0.0f, lbl_804CB964->xA, 6.0f); fn_801A5800(252.0f, 17.0f + v); }
        { f32 v = fn_8017F68C(4, 100.0f, 0.0f, lbl_804CB964->xA, 6.0f); fn_801A6220(252.0f, 219.0f + v); }
        fn_8007E154();
        fn_8007E7DC(lbl_804CB964->x338);
        fn_8007E164();
        fn_801BCA5C(25.0f);
    }
    fn_8007E154();
    fn_8007E7DC(0xFF);
    fn_8007E164();
}
}
