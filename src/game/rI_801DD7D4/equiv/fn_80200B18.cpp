/* fn_80200B18: draw of the two-line price / funds box (label, amount or dashes, unit). */
#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
struct C4 { u8 r, g, b, a; };
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E174(int, u32);
void fn_8007E720(f32);
int fn_800CB0FC(f32, int);
const char* fn_800D0864(const char*);
int fn_800CA3DC(f32, const char*, int);
void fn_800CB278(int, int, int, const char*, ...);
void fn_801E6DA0(int, int, int, const char*, ...);
void fn_800800D4(int);
void fn_80080308(void);
void fn_80080508(C4*);
void fn_80080B00(int, void*, f32);
C4* fn_800CD204(int);
void fn_80176F7C(int, int, int, int, int);
int fn_800626E0(void*);
extern char lbl_8036F328[];
extern char lbl_803CAB38[];
}
class MV { public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(void*);
    int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26, a28; u8 p2a[2];
    f32 sx, sy, sz; u32 flags; void* parent; int a40; int a44;
};
static inline void numStyle() {
    fn_800800D4(5);
    {
        C4 k;
        C4* p = fn_800CD204(0x1f);
        k.r = p->r; k.g = p->g; k.b = p->b; k.a = p->a;
        fn_80080508(&k);
    }
    fn_80080B00(1, fn_800CD204(0x2a), 1.0f);
}
static inline int adv(int y) { int r = y + 0x1c; return r; }
extern "C" void fn_80200B18(MV* o, void* c) {
    int x, y;
    int xr;
    const char* unit;
    s16 uw;
    o->v18(c);
    {
        int t = 0x1c - fn_800CB0FC(1.0f, -1);
        y = ((t + 0xc) >> 1) + o->ty;
    }
    x = o->tx + 0x16;
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E174(0, (u16)(o->flags | 3));
    fn_8007E164();
    unit = fn_800D0864(lbl_8036F328 + 0x2c);
    uw = fn_800CA3DC(1.0f, unit, -1);
    fn_800CB278((s16)x, (s16)y, 0x1e, fn_800D0864(lbl_8036F328 + 0x53));
    fn_800CB278((s16)((s16)x + 0xb8 - uw), (s16)y, 0x1e, unit);
    if (o->a44 >= 0) {
        numStyle();
        xr = (s16)x + 0xb0;
        fn_80176F7C(xr - uw, (s16)y, 0, 0, o->a44);
        fn_80080308();
    } else {
        const char* s = lbl_8036F328 + 0x25;
        s16 w = fn_800CA3DC(1.0f, s, -1);
        xr = (s16)x + 0xb0;
        fn_801E6DA0((s16)(xr - uw - w), (s16)y, 0x1f, s);
    }
    y = adv(y);
    unit = fn_800D0864(lbl_8036F328 + 0x2c);
    uw = fn_800CA3DC(1.0f, unit, -1);
    fn_800CB278((s16)x, (s16)y, 0x1e, fn_800D0864(lbl_8036F328 + 0x3f));
    fn_800CB278((s16)((s16)x + 0xb8 - uw), (s16)y, 0x1e, unit);
    numStyle();
    fn_80176F7C(xr - uw, (s16)y, 0, 0, fn_800626E0(lbl_803CAB38));
    fn_80080308();
}
