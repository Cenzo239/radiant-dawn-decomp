/* fn_801846D0: per-chapter score list. */
#include "game/rF_8017F400/types.h"
#pragma pool_strings on
extern "C" {
void StringPool(const char** p) {
    p[0] = "%6d";
    p[1] = "MS_ACH_GOUKEI";
    p[2] = "P";
}
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
typedef struct BoxD { u8 pad[0x38]; int x38[5]; int x4c; u8 pad50[0x60-0x50]; void* arch; } BoxD;
typedef struct BD { u8 pad[0x124]; int n; } BD;
extern BD* fn_8008D750(void);
#if TARGET_PC
extern FE10_PROTO const char* fn_8008DB4C(p32arg, int);
#else
extern const char* fn_8008DB4C(BD*, int);
#endif
extern void fn_801C6DA0(int, const char*, f32, f32);
extern char* fn_800D0864(const char*);
extern void fn_80080B00(int, void*, f32);
static inline GXColor mk(const u8* p, u8 a) { GXColor c; c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = a; return c; }
static inline void DrawC(void* arch, int tile, GXColor c, f32 x, f32 y, f32 w, f32 h) {
    TexH** t = (TexH**)fn_80006A0C(arch, tile);
    f32 tw = (*t)->x2, th = (*t)->x0;
    fn_801BC88C(arch, tile, c, 0x11, 0, x, y, x + w, y + h, 0.0f, 0.0f, tw, th);
}
static inline void Tile(void* arch, int tile, f32 x, f32 y) {
    TexH** t = (TexH**)fn_80006A0C(arch, tile);
    f32 w = (*t)->x2;
    f32 h = (*t)->x0;
    DrawC(arch, tile, mk(fn_800CD204(1), 0xFF), x, y, w, h);
}
static inline void Num(int v, int x, int y) {
    char buf[0x10];
    fn_80290DDC(buf, "%6d", v);
    fn_801BCA94();
    fn_800800D4(5);
    fn_80080330(x, y);
    fn_800804D4(0, 0x61, 0, 0xff);
    fn_80080B00(1, fn_800CD204(0x2a), 2.0f);
    fn_80080C24(buf);
    fn_80080308();
}
void fn_801846D0(BoxD* p, f32 x, f32 y) {
    /*P*/
    BD* d;
    int i;
    int ofs;
    f32 ry;
    /*E*/
    d = fn_8008D750();
    fn_801BCA5C(-1.0f);
    Tile(p->arch, 1, x, y);
    fn_801BCA5C(-1.0f);
    fn_801BCA94();
    for (i = 0; i < d->n; i++) {
        ry = 84.0f + y + i * 0x20;
        fn_801C6DA0(8, fn_8008DB4C(d, i), 40.0f + x, ry);
        if (fn_801D09F0() == 0) Num(p->x38[i], 380.0f + x, ry);
        else Num(p->x38[i], 395.0f + x, ry);
    }
    fn_801C6DA0(8, fn_800D0864("MS_ACH_GOUKEI"), 324.0f + x, 264.0f + y);
    if (fn_801D09F0() == 0) Num(p->x4c, 380.0f + x, 264.0f + y);
    else Num(p->x4c, 395.0f + x, 264.0f + y);
    fn_801C6DA0(8, "P", 464.0f + x, 264.0f + y);
    fn_801BCA5C(2.0f);
}
}
