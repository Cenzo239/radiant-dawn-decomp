#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
#pragma pool_strings on
extern "C" {
struct C4 { u8 r, g, b, a; };
void fn_8007E154(void);
void fn_8007E164(void);
#if TARGET_PC
FE10_PROTO void fn_8007E174(p32arg, u32);
#else
void fn_8007E174(int, u32);
#endif
void fn_8007E720(f32);
int fn_800CB0FC(f32, int);
const char* fn_800D0864(const char*);
int fn_800CA3DC(f32, const char*, int);
int fn_800CA7A4(f32, const char*, int);
void fn_800CB278(int, int, int, const char*, ...);
void fn_801E6DA0(int, int, int, const char*, ...);
void fn_800800D4(int);
void fn_80080308(void);
void fn_80080508(C4);
void fn_80080B00(int, void*, f32);
void fn_80080A94(f32);
void fn_800804F4(u8);
C4* fn_800CD204(int);
void fn_80176F7C(int, int, int, int, int);
void fn_80176EA8(int, int, int, const char*);
const char* fn_8010F5E0(void*);
#if TARGET_PC
FE10_PROTO int fn_801E733C(ptr32<const void>);
#else
int fn_801E733C(void*);
#endif
void fn_80291CEC(int, char*, int);
extern u8 lbl_803E7290[];
struct D44 { u8 p[0x44]; };
struct FontV : D44 { virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18(int, int, int); virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48(); virtual int v4c(); };
#define FONT ((FontV*)lbl_803E7290)
struct It { u8 p[0x16]; u16 a16; };
struct MV {
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18();
    int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26, a28; u8 p2a[2]; f32 sx, sy, sz; u32 flags; void* parent; s8 a40; u8 p41[3]; It* a44; u8 a48; u8 p49[3]; f32 a4c;
};
#define SCALE(k) fn_8007E154(); fn_8007E720(k); fn_8007E164();
#define FLAGS(o, m) fn_8007E154(); fn_8007E174(0, (u16)(o->flags | m)); fn_8007E164();
void dummy1(const char** p) {
    *p = "FSHOP_ITEMS_%s";
    *p = "xwp/";
    *p = "forge/";
    *p = "_b.cmp";
    *p = "_b.g";
    *p = "_b.gs";
    *p = "_b.tpl";
    *p = "SFX_SYS_CURSOR_WINDOW_MOVE1";
    *p = "MESS_FORGE_KIND";
    *p = "MESS_FORGE_POINT";
    *p = "MESS_FORGE_ABLE";
    *p = "MESS_SHOPINFO_NUM";
    *p = "#E%s";
    *p = "MESS_FORGE_INITIAL_PARAM";
    *p = "MP_POW";
    *p = "MP_HIT";
    *p = "MP_CRIT";
    *p = "MP_WGT";
    *p = "MESS_SHOPINFO_GOLD";
    *p = "MESS_FORGE_COLOR";
    *p = "MMM_DECIDE";
    *p = "MMM_GOBACK";
    *p = "SFX_SYS_ALLOT_EVENT_EXP1";
    *p = "EID_STATUS";
    *p = "EID_ARROW2";
}
static inline s16 gx(MV* o) { return o->tx; }
void fn_8021B444(MV* o) {
/*P*/
    int y3;
    int yy;
    int e;
    int r;
    int r2;
    s16 x;
    s16 w;
    int xx;
    const char* s5;
    int y2;
    const char* s1;
    const char* s6;
    const char* s2;
    const char* s3;
    const char* s4;
    s16 ty;
    s16 cw;
    int cw0;
    const char* s0;
    int k;
    int n;
    s16 y;
    s16 dw;
    s16 dh;
    int t;
    int t2;
/*E*/
    o->v18();
    y = o->ty + 6;
    x = gx(o);
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E174(0, (u16)(o->flags | 3));
    fn_8007E164();
    w = (s16)((s16)(o->ix1 - o->ix0) - o->tx * 2);
    ty = (0x1c - fn_800CB0FC(1.0f, -1)) >> 1;
    s0 = fn_800D0864("MESS_FSHOP_COININFO");
    fn_800CB278((s16)(x + ((w - (s16)fn_800CA3DC(1.0f, s0, -1)) >> 1)), (s16)(y + ty), 0x1e, s0);
    y += 0x1a;
    if (o->a44 != NULL) {
        s1 = fn_8010F5E0(o->a44);
        yy = y + ty;
        fn_801E6DA0((s16)(x + FONT->v4c()), (s16)yy, 0x1f, s1);
        FONT->v18(x, yy, o->a44->a16 + 0x81);
        FLAGS(o, 3)
    } else {
        s6 = "\x81\x7c\x81\x7c\x81\x7c";
        k = (s16)fn_800CA3DC(1.0f, s6, -1);
        yy = y + ty;
        fn_801E6DA0((s16)(x + ((w - k) >> 1)), (s16)yy, 0x1f, s6);
    }
    s2 = fn_800D0864("MESS_SHOPINFO_CHIP");
    cw0 = (s16)fn_800CA3DC(1.0f, s2, -1);
    e = x + w;
    r = e - cw0;
    fn_800CB278((s16)r, (s16)yy, 0x1e, s2);
    if (o->a44 != NULL && o->a40 >= 0) {
        fn_800800D4(5);
        fn_80080508(*fn_800CD204(0x1f));
        fn_80080B00(1, fn_800CD204(0x2a), 1.0f);
        fn_80176F7C(r - 8, yy, 0, 0, o->a40);
        fn_80080308();
    } else {
        s3 = "\x81\x7c\x81\x7c";
        fn_800800D4(5);
        fn_80080508(*fn_800CD204(0x1f));
        fn_80080B00(1, fn_800CD204(0x2a), 1.0f);
        fn_80176EA8(r - 8, y, 0, s3);
        fn_80080308();
    }
    y3 = y + 0x1c;
    s4 = fn_800D0864("MESS_SHOPINFO_CHIP");
    cw = (s16)fn_800CA3DC(1.0f, s4, -1);
    y2 = (s16)y3 + ty;
    fn_800CB278(x, (s16)y2, 0x1e, fn_800D0864("MESS_SHOPINFO_HAVE"));
    r2 = e - cw;
    fn_800CB278((s16)r2, (s16)y2, 0x1e, s4);
    n = 0;
    if (o->a44 != NULL) {
        n = fn_801E733C(o->a44);
        fn_800800D4(5);
        fn_80080508(*fn_800CD204(0x1f));
        fn_80080B00(1, fn_800CD204(0x2a), 1.0f);
        xx = r2 - 8;
        fn_80176F7C(xx, y2, 0, 0, n);
        fn_80080308();
    } else {
        s5 = "\x81\x7c\x81\x7c";
        fn_800800D4(5);
        fn_80080508(*fn_800CD204(0x1f));
        fn_80080B00(1, fn_800CD204(0x2a), 1.0f);
        xx = r2 - 8;
        fn_80176EA8(xx, (s16)y3, 0, s5);
        fn_80080308();
    }
    if (o->a48 & 1) {
        char buf[8];
        SCALE(-1.0f)
        fn_80291CEC(n, buf, 10);
        t = fn_800CA3DC(o->a4c, buf, -1);
        dw = (s16)(t - fn_800CA3DC(1.0f, buf, -1));
        t2 = fn_800CA7A4(o->a4c, buf, -1);
        dh = (s16)(t2 - fn_800CA7A4(1.0f, buf, -1));
        fn_800800D4(5);
        fn_80080508(*fn_800CD204(0x1f));
        fn_80080B00(1, fn_800CD204(0x2a), 1.0f);
        fn_80080A94(o->a4c);
        fn_800804F4(255.99f * (o->a4c - 1.0f));
        fn_80176F7C((dw >> 1) + xx, y2 - (dh >> 1), 0, 0, n);
        fn_80080308();
        SCALE(1.0f)
        o->a4c -= 0.05f;
        if (o->a4c <= 1.0f) {
            o->a4c = 1.0f;
            o->a48 &= 0xFE;
        }
    }
}
}
