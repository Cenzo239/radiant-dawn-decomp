/* fn_8021CF08: draw of a small stat box: the (localised) title centred on the first line, then either
   one value line (when the fourth value is positive) or three value lines 0x1b apart. */
#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
const char* fn_800D0864(const char*);
int fn_800CA3DC(f32, const char*, int);
int fn_800CB0FC(f32, int);
void fn_800CB278(int, int, int, const char*, ...);
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E174(int, u32);
extern char lbl_80371974[];
}
struct St { const char* name; s8 v0, v1, v2, v3; };
class SB { public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(void*); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(void*); virtual int v34(int, int, const char*, int);
    int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26, a28; u8 p2a[2];
    f32 sx, sy, sz; u32 flags; void* parent; u8 p40[4]; St* st;
};
extern "C" void fn_8021CF08(SB* o, void* c) {
    s16 x;
    int cy;
    int cx;
    s16 y;
    const char* name;
    o->v30(c);
    o->v18(c);
    x = o->tx;
    y = o->ty;
    name = fn_800D0864(o->st->name);
    cx = (s16)(o->ix1 - o->ix0);
    cx = (cx - fn_800CA3DC(1.0f, name, -1)) >> 1;
    cy = (0x1b - fn_800CB0FC(1.0f, -1)) >> 1;
    fn_8007E154();
    fn_8007E174(0, (u16)(o->flags | 3));
    fn_8007E164();
    fn_800CB278(cx, (s16)(cy + 2), 1, name);
    if (o->st->v3 > 0) {
        o->v34(x, y, lbl_80371974 + 0x1a4, o->st->v3);
    } else {
        o->v34(x, y, lbl_80371974 + 0xb1, o->st->v0);
        y += 0x1b;
        o->v34(x, y, lbl_80371974 + 0xb8, o->st->v1);
        o->v34(x, (s16)(y + 0x1b), lbl_80371974 + 0xbf, o->st->v2);
    }
}
