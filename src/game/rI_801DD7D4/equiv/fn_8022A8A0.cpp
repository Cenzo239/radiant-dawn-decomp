/* fn_8022A8A0: draw of a scrolling text grid (rows x columns of strings from fn_8022B6DC),
   with the selected cell drawn 1.5x and re-centred, and the vertical scroll offset eased to 0. */
#include "game/rI_801DD7D4/types.h"
#pragma auto_inline off
extern "C" {
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E174(int, u32);
void fn_8007E74C(void*, void*);
void fn_8007E7B4(void);
int fn_800CB0FC(f32, int);
int fn_800CA3DC(f32, const char*, int);
int fn_800CABA0(f32, const char*, int);
void fn_800CB3A8(f32, f32, s16, s16, int, int, int, const char*, ...);
u32* fn_801E2204(void*, s16*, s16*);
void fn_801E2104(void* p, void* arg);
const char* fn_8022B6DC(void*, s16, s16);
}
struct Par { u8 p[0x70]; int x70; };
class MG { public:
    virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(void*); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(); virtual int v38(); virtual int v3C();
    virtual int v40(); virtual int v44(); virtual int v48(); virtual int v4C(); virtual int v50();
    int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26, a28; u8 p2a[2];
    f32 sx, sy, sz; u32 flags; Par* parent; void* a40; u8 p44[8]; s16 a4c, a4e; u8 p50[4]; s16 a54, a56, a58, a5a; f32 a5c;
};
static inline void setR(MG* o, s16 a, s16 b, s16 c, s16 d) { o->a54 = a; o->a56 = b; o->a58 = c; o->a5a = d; }
static inline int sgn(s16 v) { if (v < 0) return -1; return v > 0; }
extern "C" void fn_8022A8A0(MG* o, void* c) {
    s16 rowH;
    int dy;
    int sc;
    int e;
    s16 s;
    s16 row;
    s16 end;
    s16 col;
    s16 y;
    s16 x;
    BOOL one;
    BOOL sel;
    f32 k;
    f32 ox, oy;
    const char* t;
    o->v50();
    o->v18(c);
    setR(o, 0, 0, o->ix1 - o->ix0, o->iy1 - o->iy0);
    fn_801E2204(o, &o->a54, &o->a54);
    fn_801E2204(o, &o->a58, &o->a58);
    fn_8007E154();
    fn_8007E74C(fn_801E2104, &o->a54);
    fn_8007E174(0, (u16)(o->flags | 3));
    fn_8007E164();
    rowH = o->v34();
    dy = (rowH - fn_800CB0FC(1.0f, -1)) >> 1;
    sc = (int)((const MG*)o)->a5c;
    if (o->a5c < 0.0f) {
        o->a5c += (s16)o->v34() * 0.25f;
        if (o->a5c >= -1.1920929e-07f) o->a5c = 0.0f;
    } else if (o->a5c > 0.0f) {
        o->a5c -= (s16)o->v34() * 0.25f;
        if (o->a5c <= 1.1920929e-07f) o->a5c = 0.0f;
    }
    s = sgn((s16)sc);
    row = s > 0 ? -1 : 0;
    one = o->parent->x70 == 1;
    if (s < 0) e = (s16)o->v3C() + 1; else e = (s16)o->v3C();
    end = e;
    for (; row < end; row++) {
        if (row + (s16)o->v38() < 0) continue;
        {
            int idx = row + (s16)o->v38();
            if ((s16)o->v44() < idx) continue;
        }
        y = row * o->v34() + sc + dy;
        for (col = 0; col < (s16)o->v40(); col++) {
            sel = FALSE;
            if (one && col == o->a4c && o->a4e == row + (s16)o->v38()) sel = TRUE;
            if (sel) k = 1.5f; else k = 1.0f;
            {
                void* g = o->a40;
                t = fn_8022B6DC(g, col, row + o->v38());
            }
            if ((int)*(u8*)t == 9) continue;
            x = ((s16)o->v30() - fn_800CABA0(1.0f, t, -1)) >> 1;
            x = x + col * o->v30();
            ox = 0.0f;
            oy = ox;
            if (sel) {
                ox = 0.5f * (fn_800CA3DC(1.0f, t, -1) - fn_800CA3DC(k, t, -1));
                oy = 0.5f * (fn_800CB0FC(1.0f, -1) - fn_800CB0FC(k, -1));
            }
            fn_800CB3A8(k, 0.0f, (int)(x + ox), (int)(y + oy), 1, 0, 0, t);
        }
    }
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
}
