#include "game/rB_8002E1C4/types.h"

/* translucent panel with a light border */
extern const f32 lbl_804CCCF4; /* 0.0f */
struct GXColor { u8 r, g, b, a; };
extern GXColor lbl_804CCD38; /* {0, 0, 0, 0x66} */
extern "C" {
void fn_8007E154(void);
void fn_8007E174(void* tex, int a);
void fn_8007E164(void);
void fn_800800D4(int a);
void fn_80080388(f32 x, f32 y, f32 w, f32 h);
void fn_80080508(GXColor c);
void fn_80080308(void);
void fn_800804D4(int r, int g, int b, int a);

struct Col2 { GXColor a; GXColor b; };
static inline void set_c(GXColor c) { fn_80080508(c); }
static inline void assignC(GXColor& d, GXColor c) { d = c; }
void fn_80032560(int x, int y) {
    Col2 t;
    assignC(t.a, lbl_804CCD38);

    int w;
    int h;
    fn_8007E154();
    fn_8007E174(0, 0x10);
    fn_8007E164();
    fn_800800D4(1);
    w = 0xde;
    h = 0x3f;
    fn_80080388(x, y, w, h);
    fn_80080508(t.a);
    fn_80080308();
    fn_800800D4(4);
    fn_80080388(x, y, w, lbl_804CCCF4);
    fn_800804D4(0xff, 0xff, 0xff, 0x33);
    fn_80080308();
    fn_800800D4(4);
    fn_80080388(x, y + 0x40, w, lbl_804CCCF4);
    fn_800804D4(0xff, 0xff, 0xff, 0x33);
    fn_80080308();
    fn_800800D4(4);
    fn_80080388(x, y, lbl_804CCCF4, h);
    fn_800804D4(0xff, 0xff, 0xff, 0x33);
    fn_80080308();
    fn_800800D4(4);
    fn_80080388(x + 0xdf, y, lbl_804CCCF4, h);
    fn_800804D4(0xff, 0xff, 0xff, 0x33);
    fn_80080308();
}
}
