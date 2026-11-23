#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
struct C4 { u8 r, g, b, a; };
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E720(f32);
#if TARGET_PC
FE10_PROTO void fn_8007E174(p32arg, u32);
#else
void fn_8007E174(int, u32);
#endif
int fn_800CB0FC(f32, int);
int fn_800CABA0(f32, const char*, int);
void fn_801D9788(int, int, u32);
void fn_800800D4(int);
void fn_80080308(void);
void fn_80080330(f32, f32);
void fn_80080508(C4);
void fn_80080ABC(int, f32);
void fn_80080C24(const char*);
C4* fn_800CD204(int);
extern u8 lbl_803E7290[];
struct D44 { u8 p[0x44]; };
struct FontV : D44 { virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18(int, int, void*); virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48(); virtual int v4c(); virtual int v50(); };
#define FONT ((FontV*)lbl_803E7290)
class MV { public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(void*); virtual int v18(void*);
    int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26, a28; u8 p2a[2]; f32 sx, sy, sz; u32 flags; void* parent; char a40[0x34]; s16 a74; u8 p76[6]; void* a7c;
};
static inline s16 gx(MV* o) { return o->tx; }
static inline s16 gy(MV* o) { return o->ty; }
void fn_8022BCA0(MV* o, int a) {
/*P*/
    s16 x;
    s16 y;
    s16 t1;
    s16 t2;
    int yy;
    char* s;
    u32 i;
    int d;
/*E*/
    o->v14((void*)a);
    fn_801D9788(0, 0, o->flags);
    o->v18((void*)a);
    fn_8007E154();
    fn_8007E720(-0.1f);
    fn_8007E164();
    x = gx(o);
    y = gy(o);
    { s16 z = FONT->v4c(); a = z; }
    t1 = (0x1a - FONT->v50()) >> 1;
    t2 = (0x1a - fn_800CB0FC(1.0f, -1)) >> 1;
    if (o->a7c != NULL) FONT->v18(x - a, y + t1, o->a7c);
    fn_8007E154();
    fn_8007E174(0, 0x13);
    fn_8007E164();
    yy = y + t2;
    s = o->a40;
    i = 0;
    while (*(int*)s != 0) {
        d = (0xe - fn_800CABA0(1.0f, s, -1)) >> 1;
        fn_800800D4(5);
        fn_80080330((s16)x + d, yy);
        fn_80080508(*fn_800CD204(i == o->a74 ? 6 : 1));
        fn_80080ABC(1, 2.0f);
        fn_80080C24(s);
        fn_80080308();
        s += 4;
        x += 0xe;
        i++;
    }
}
}
