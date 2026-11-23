#include "game/rB_8002E1C4/types.h"

/* Frame and stat-line drawing used by the help windows. */
extern const char lbl_80361390[0x200];
extern const f32 lbl_804CCCF4; /* 0.0f */
extern const f32 lbl_804CCD24; /* -1.0f */
extern const f32 lbl_804CCD28; /* 1.0f */
extern void* lbl_804CB58C;
typedef struct TexObj { u8 data[0x20]; } TexObj;
typedef struct Tex { TexObj tex; u16 w; u16 h; } Tex;
struct GXColor { u8 r, g, b, a; };
extern "C" {
void fn_8007E154(void);
void fn_8007E164(void);
void fn_8007E174(void* t, int a);
void fn_800800D4(int a);
void fn_80080388(f32 x, f32 y, f32 w, f32 h);
void fn_80080508(GXColor c);
void fn_80080308(void);
void fn_8006E030(f32 a);
void fn_8006E068(void);
void fn_80074EB4(int x, int y, int w, int h);
void fn_80006A64(void* arc, TexObj* tex, u16 id);
u16 fn_80305DF8(TexObj* tex);
u16 fn_80305E0C(TexObj* tex);
const char* fn_800D0864(const char* key);
int fn_800CB0FC(f32 a, int b);
int fn_800CA3DC(const char* s, int n, f32 a);
void fn_800CB3A8(f32 a, f32 b, s16 x, s16 y, int c, int d, int e, const char* fmt, ...);

static inline void setc(int a) {
    GXColor c = {0xff, 0xff, 0xff, a};
    fn_80080508(c);
}

void fn_80031ED4(int x, int y, int w, int h) {
    int a = 0x33;
    fn_8007E154();
    fn_8007E174(0, 0x12);
    fn_8007E164();
    fn_800800D4(4);
    fn_80080388(x, y, w, lbl_804CCCF4);
    setc(a);
    fn_80080308();
    fn_800800D4(4);
    fn_80080388(x + w, y, lbl_804CCCF4, h);
    setc(a);
    fn_80080308();
    fn_800800D4(4);
    fn_80080388(x, y + h, w, lbl_804CCCF4);
    setc(a);
    fn_80080308();
    fn_800800D4(4);
    fn_80080388(x, y, lbl_804CCCF4, h);
    setc(a);
    fn_80080308();
    fn_800800D4(1);
    fn_80080388(x, y, w - 1, h - 1);
    { int a2 = 0x19; setc(a2); }
    fn_80080308();
}

void fn_800327D8(int kind, int x, int y, int frame) {
    int id;
    int col;
    const char* s;
    Tex t;
    if (frame) fn_80031ED4(x + 0x16, y - 4, 0xde, 0x20);
    fn_8006E030(lbl_804CCD24);
    fn_80074EB4(x + 0x1e, y + 0x12, 0xcc, 0xa0);
    fn_8006E030(lbl_804CCD24);
    switch (kind) {
    case 0: id = 0x30; col = 0xa; s = fn_800D0864(lbl_80361390 + 0x146); break;
    case 1: id = 0x31; col = 0xa; s = fn_800D0864(lbl_80361390 + 0x152); break;
    case 2: id = -1; col = 1; s = fn_800D0864(lbl_80361390 + 0x15e); break;
    case 3: id = 0x32; col = 0xb; s = fn_800D0864(lbl_80361390 + 0x16c); break;
    case 4: id = 0x33; col = 0xb; s = fn_800D0864(lbl_80361390 + 0x177); break;
    }
    if (id >= 0) {
        fn_80006A64(lbl_804CB58C, &t.tex, id);
        t.w = fn_80305DF8(&t.tex);
        t.h = fn_80305E0C(&t.tex);
        fn_8007E154();
        fn_8007E174(&t.tex, 0x10);
        fn_8007E164();
        fn_800800D4(1);
        fn_80080388(x + 0x30, y + ((0x1c - t.h) >> 1), t.w, t.h);
        fn_80080308();
    }
    fn_8006E068();
    {
    y = (s16)(y + ((0x1c - fn_800CB0FC(lbl_804CCD28, -1)) >> 1));
    fn_800CB3A8(lbl_804CCD28, lbl_804CCCF4, x + ((0x108 - fn_800CA3DC(s, -1, lbl_804CCD28)) >> 1), y, col, 1, 0, s);
    }
}
}
