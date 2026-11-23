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
    int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26, a28; u8 p2a[2]; f32 sx, sy, sz; u32 flags; void* parent; It* a40;
};
#define SCALE(k) fn_8007E154(); fn_8007E720(k); fn_8007E164();
#define FLAGS(o, m) fn_8007E154(); fn_8007E174(0, (u16)(o->flags | m)); fn_8007E164();
void dummy1(const char** p) {
    *p = "+0000";
    *p = "+%4d";
    *p = "MESS_EDU_EXP_BONUS";
    *p = "%s #C%02x%6d#c P";
    *p = "%s #C%02x%9d#c P";
    *p = "--";
    *p = "%2d";
    *p = "        ";
    *p = "    ";
    *p = "%s #C01%2d#c%s%s #C01%s";
    *p = "BMI_LV";
    *p = "BMI_EX";
    *p = "%s #C%02x%2d#c%s%s #C01%s";
    *p = "SFX_SYS_ALLOT_EVENT_EXP1";
    *p = "\x0a";
    *p = "";
    *p = "SFX_SYS_CAPACITY_UP1";
}

static inline s16 gx(MV* o) { return o->tx; }
void fn_8021ED04(MV* o) {
/*P*/
s16 x;
s16 w;
int e;
int r2;
s16 y;
int y3;
int yy;
int xx;
const char* s3;
int y2;
const char* s1;
const char* s4;
const char* s2;
s16 ty;
s16 k2;
s16 cw;
const char* s0;
int k;
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
    s0 = fn_800D0864("MESS_EDU_SKL_SKILLITEM");
    fn_800CB278((s16)(x + ((w - (s16)fn_800CA3DC(1.0f, s0, -1)) >> 1)), (s16)(y + ty), 0x1e, s0);
    y = y + 0x1a;
    if (o->a40 != NULL) {
        s1 = fn_8010F5E0(o->a40);
        k = fn_800CA3DC(1.0f, s1, -1);
        k = (s16)(int)((char*)FONT->v4c() + k);
        yy = y + ty;
        xx = x + ((w - k) >> 1);
        fn_801E6DA0((s16)(xx + FONT->v4c()), (s16)yy, 0x1f, s1);
        FONT->v18(xx, yy, o->a40->a16 + 0x81);
        FLAGS(o, 3)
    } else {
        s4 = "\x81\x7c\x81\x7c\x81\x7c";
        k = (s16)fn_800CA3DC(1.0f, s4, -1);
        fn_801E6DA0((s16)(x + ((w - k) >> 1)), (s16)(y + ty), 0x1f, s4);
    }
    y3 = y + 0x1c;
    s2 = fn_800D0864("MESS_SHOPINFO_NUM");
    cw = (s16)fn_800CA3DC(1.0f, s2, -1);
    y2 = (s16)y3 + ty;
    fn_800CB278(x, (s16)y2, 0x1e, fn_800D0864("MESS_SHOPINFO_HAVE"));
    e = x + w;
    r2 = e - cw;
    fn_800CB278((s16)r2, (s16)y2, 0x1e, s2);
    if (o->a40 != NULL) {
        fn_800800D4(5);
        fn_80080508(*fn_800CD204(0x1f));
        fn_80080B00(1, fn_800CD204(0x2a), 1.0f);
        fn_80176F7C(r2 - 8, y2, 0, 0, fn_801E733C(o->a40));
        fn_80080308();
    } else {
        s3 = "\x81\x7c\x81\x7c\x81\x7c";
        k2 = (s16)fn_800CA3DC(1.0f, s3, -1);
        fn_800800D4(5);
        fn_80080508(*fn_800CD204(0x1f));
        fn_80080B00(1, fn_800CD204(0x2a), 1.0f);
        fn_80176EA8(e - k2 - 8, (s16)y3, 0, s3);
        fn_80080308();
    }
}
}
