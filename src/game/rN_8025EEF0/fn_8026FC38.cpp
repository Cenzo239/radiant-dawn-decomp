/* fn_8026FC38 (round 22, agent r22b): exact.
 * Draw callback (passed to fn_8007E74C with a pointer to a widget's clip rectangle): clamps
 * the four corner coordinates to 0..0x7FF and sets the GX scissor (fn_803080DC =
 * GXSetScissor) to x, y, right - x, bottom - y. The first argument is unused.
 * Instruction-identical to rI's fn_801E2104 (fn_801E1454.cpp); same source.
 */
#include "game/rN_8025EEF0/types.h"
extern "C" {
void fn_803080DC(int, int, int, int);
struct Rect16 { s16 x, y, w, h; };
static inline void sr5(s16 w, s16 h, const Rect16& r) { fn_803080DC(r.x, r.y, w, h); }
void fn_8026FC38(void* a, Rect16* src) {
    Rect16 r = *src;
    r.x = r.x < 0 ? 0 : r.x > 0x7ff ? 0x7ff : r.x;
    r.y = r.y < 0 ? 0 : r.y > 0x7ff ? 0x7ff : r.y;
    r.w = r.w < 0 ? 0 : r.w > 0x7ff ? 0x7ff : r.w;
    r.h = r.h < 0 ? 0 : r.h > 0x7ff ? 0x7ff : r.h;
    sr5(r.w - r.x, r.h - r.y, r);
}
}
