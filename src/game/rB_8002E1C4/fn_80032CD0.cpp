#include "game/rB_8002E1C4/helpwin.h"
extern const f32 lbl_804CCD3C; /* 106.0f */
extern const f32 lbl_804CCD40; /* 30.0f */
extern const f32 lbl_804CCD34; /* 2.0f */
extern void* lbl_804CB58C;
typedef struct TexObj { u8 data[0x20]; } TexObj;
typedef struct Tex { TexObj tex; u16 w; u16 h; } Tex;
struct WPers { u8 pad[0x18]; WPers* x18; u8 pad1c[0xee - 0x1c]; u16 xee; u8 padf0[0x10b - 0xf0]; s8 x10b; };
extern "C" {
void fn_80006A64(void* arc, TexObj* tex, int id);
u16 fn_80305DF8(TexObj* tex);
u16 fn_80305E0C(TexObj* tex);
void fn_800800D4(int a);
void fn_80080388(f32 x, f32 y, f32 w, f32 h);
void fn_80080308(void);
s8 fn_801284C4(BUnit* p);
int fn_800CB0FC(f32 a, int b);

void fn_80032CD0(BUnit* p, int x, int y, int v) {
    int id = v >= 0;
    Tex t;
    if (v < 0) v = fn_801284C4(p);
    if (id) fn_80031ED4(x + 0x16, y - 4, 0xde, 0x20);
    fn_8006E030(lbl_804CCD24);
    fn_80074EB4(x + 0x1e, y + 0x12, 0xcc, 0xa0);
    fn_8006E030(lbl_804CCD24);
    {
    u16 f = (fn_8011B77C(p->x12c, lbl_804CA4EC) ? (WPers*)p->xf0 : ((WPers*)p->xf0)->x18)->xee;
    if (f & 0x40) id = 0x34;
    else if (f & 0x100) id = 0x35;
    else if (f & 0x80) id = 0x36;
    }
    fn_80006A64(lbl_804CB58C, &t.tex, id);
    t.w = fn_80305DF8(&t.tex);
    t.h = fn_80305E0C(&t.tex);
    fn_8007E154();
    fn_8007E174(&t.tex, 0x10);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080388(x + 0x30, y + ((0x1c - t.h) >> 1), t.w, t.h);
    fn_80080308();
    fn_8006E068();
    fn_800CB3A8(lbl_804CCD28, lbl_804CCCF4, x + 0x58, y + ((0x1c - fn_800CB0FC(lbl_804CCD28, -1)) >> 1), 1, 1, 0, lbl_80361390 + 0x184, v);
    { int r = fn_8011B77C(p->x12c, lbl_804CA4EC); int k = 0x38; if (r == 0) k = 0x37; fn_80006A64(lbl_804CB58C, &t.tex, k); }
    t.w = fn_80305DF8(&t.tex);
    t.h = fn_80305E0C(&t.tex);
    fn_8007E154();
    fn_8007E174(&t.tex, 0x10);
    fn_8007E164();
    {
    int w = lbl_804CCD3C * (f32)v / lbl_804CCD40;
    int h = 8;
    fn_800800D4(1);
    fn_80080388(x + 0x7c, y + 0xc, w, h);
    }
    fn_80080308();
    fn_8006E030(lbl_804CCD34);
}

static inline void head(BUnit* p, int h) {
    int i;
    WIN_FRAME(p, h)
    WIN_HP(p, 0, 0x34)
    WIN_ITEMS(p, 0x34)
}
static inline void stat(BUnit* p, int x, int y, int d) {
    int l = ((WPers*)p->xf0)->x10b;
    fn_801C6E64(x, y, lbl_80361390 + 0x188, fn_8012269C(p), fn_80122D30(p), (s8)(fn_80123EF0(p) + d), l, fn_8011B77C(p->x12c, lbl_804CA4EC));
}
#define STAT(p, x, y, d) { int xx = x; int yy = y; stat(p, xx, yy, d); }
void fn_80033684(BUnit* p, int unused, int v) {
    head(p, 0x8c);
    fn_8006E068();
    fn_8006E068();
    STAT(p, 0x1e, 0x50, 0);
    fn_80031ED4(0x16, 0x84, 0xde, 0x20);
    fn_8006E068();
    STAT(p, 0x1e, 0x88, v);
}

void fn_800346D0(BUnit* p, int v) {
    head(p, 0x72);
    fn_8006E068();
    fn_8006E068();
    STAT(p, 0x1e, 0x50, 0);
    fn_80074EB4(0x1e, 0x7e, 0xcc, 0xa0);
    fn_8006E030(lbl_804CCD24);
    fn_8006E068();
    fn_800CB3A8(lbl_804CCD28, lbl_804CCCF4, 0x26, 0x6c, 9, 1, 0, fn_800D0864(lbl_80361390 + 0x1b0));
    fn_800CB3A8(lbl_804CCD28, lbl_804CCCF4, 0xa5, 0x6c, 1, 1, 0, lbl_80361390 + 0x1b7, v);
    fn_8006E030(lbl_804CCD28);
}
}
