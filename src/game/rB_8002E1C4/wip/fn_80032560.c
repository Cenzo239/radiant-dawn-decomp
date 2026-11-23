/* fn_80032560: size 0x268 vs 0x278 - original keeps two stack copies of the colour
 * (0xc and 0x10) plus a by-value temp at 0x8; we only get one copy. */
#include "game/rB_8002E1C4/types.h"

typedef struct GXColor { u8 r, g, b, a; } GXColor;
extern GXColor lbl_804CCD38; /* {0, 0, 0, 0x66} */
extern const f32 lbl_804CCCF4; /* 0.0f */
void fn_8007E154(void);
void fn_8007E174(void* tex, int a);
void fn_8007E164(void);
void fn_800800D4(int a);
void fn_80080388(f32 x, f32 y, f32 w, f32 h);
void fn_80080508(GXColor c);
void fn_80080308(void);
void fn_800804D4(int r, int g, int b, int a);

static inline void set_color(GXColor c) { fn_80080508(c); }

/* translucent panel with a light border */
void fn_80032560(int x, int y)
{
    int w;
    int h;
/*V*/
/*V*/
    fn_8007E154();
    fn_8007E174(0, 0x10);
    fn_8007E164();
    fn_800800D4(1);
    w = 0xde;
    h = 0x3f;
    fn_80080388(x, y, w, h);
    set_color(c);
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
