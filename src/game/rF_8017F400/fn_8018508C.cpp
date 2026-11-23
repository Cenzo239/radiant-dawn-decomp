/* fn_8018508C, fn_801854B4: achievement window draw and init. */
#include "game/rF_8017F400/types.h"
#pragma pool_strings on
extern "C" {
void StringPool(const char** p) {
    p[0] = "%6d";
    p[1] = "MS_ACH_GOUKEI";
    p[2] = "P";
    p[3] = "window/achieve/achieve";
    p[4] = ".cms";
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
typedef struct BD { u8 pad[0x100]; int x100[9]; int n; } BD;
typedef struct BP { u8 pad[0x30]; int st; int t; int cur[6]; int x50; s16 inc[6]; u8 pad60[0x60-0x60]; void* arch; } BP;
extern void fn_8007E7B4(void);
extern void fn_801C6EAC(const char*, const char*, char*);
extern int fn_8023F880(const char*);
extern void fn_8023F1A0(const char*, int);
extern void fn_800068A0(void*, const char*);
extern void fn_801846D0(BP*, f32, f32);
extern void fn_80184BEC(BP*, f32, f32);
extern BD* fn_8008D750(void);
extern int fn_8008DB58(BD*);
extern int fn_8008DC34(BD*);
extern void fn_802512C4(f32);
extern double fn_80295CF0(double);
static inline void Sprite(void* arch, int tile, f32 x, f32 y, f32 w, f32 h) {
    u8* p = fn_800CD204(1);
    GXColor c;
    TexH** t;
    c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = 0xFF;
    t = (TexH**)fn_80006A0C(arch, tile);
    {
    f32 tw = (*t)->x2, th = (*t)->x0;
    fn_801BC88C(arch, tile, c, 0x11, 0, x, y, x + w, y + h, 0.0f, 0.0f, tw, th);
    }
}
static inline void Tile(void* arch, int tile, f32 x, f32 y) {
    TexH** t = (TexH**)fn_80006A0C(arch, tile);
    f32 h, w;
    w = (*t)->x2;
    h = (*t)->x0;
    Sprite(arch, tile, x, y, w, h);
}
void fn_8018508C(BP* p) {
    char path[0x80];
    fn_801C6EAC("window/achieve/achieve", ".cms", path);
    if (fn_8023F880(path)) {
        if (p->arch == 0) fn_800068A0(&p->arch, path);
        fn_8007E154();
        fn_8007E4E4(0.0f, 0.0f, 30.0f, 1.0f);
        fn_8007E7DC(0xff);
        fn_8007E7B4();
        fn_8007E164();
        Tile(p->arch, 0, 0.0f, 0.0f);
        fn_801846D0(p, 48.0f, 25.0f);
        fn_80184BEC(p, 246.0f, 356.0f);
        fn_8007E154();
        fn_8007E7DC(0xff);
        fn_8007E164();
    }
}
void fn_801854B4(BP* p) {
    /*P*/
    int i;
    BD* d;
    /*E*/
    char path[0x80];
    d = fn_8008D750();
    fn_802512C4(1000.0f);
    p->arch = 0;
    p->st = 0;
    p->t = 0;
    for (i = 0; i < 6; i++) {
        p->cur[i] = 0;
        p->inc[i] = (int)fn_80295CF0(d->x100[i]);
        if (p->inc[i] < 1) p->inc[i] = 1;
    }
    p->x50 = fn_8008DC34(d) - fn_8008DB58(d);
    fn_801C6EAC("window/achieve/achieve", ".cms", path);
    fn_8023F1A0(path, 0);
}
}
