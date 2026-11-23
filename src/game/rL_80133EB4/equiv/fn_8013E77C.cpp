/* symcheck: r21 review, flag was an artefact. fn_8013E77C: (a) tool bug: `@sda21(r0)` base (fixed in symcheck.py).
   See docs/SCHED_REVIEW.md. */
/* fn_8013E77C (0x80): functionally equal at `sched` level (tools/check_regs.py, round 20). Scrolls the wrapped
 * map origin by one step (names guessed). From wip/near3.cpp, the already matched neighbours removed.
 * Moved instructions (tools/equiv/dd.py): the three sda byte loads (lbl_804CB84D/E/F) and their `extsb` come in
 * another order; all loads are before the first store, so the order is free.
 */
#include "game/rL_80133EB4/map3d.h"
#pragma auto_inline off
struct Wx { u8 pad[0x31]; u8 x31; };
struct MA { u8 pad[0x18]; Wx* x18; };
class VO { public: u8 pad[0x6C]; virtual void v(Vec*); };
struct H44 { u8 pad[0x44]; VO* x44; };
struct Grid { s32 w, h; u8 pad[0x20000]; };
struct P14 { u8 pad[8]; f32 x8, xc; };
struct C5 { u8 pad[0x14]; P14* x14; };
struct Cm { f32 x0, x4, x8, xc, x10; };
extern "C" {
extern u8 lbl_804CB834;
extern void fn_80146BAC(Wx*, int);
extern void fn_80146B40(Wx*);
extern u8 lbl_804CB84C;
extern s8 lbl_804CB84D, lbl_804CB84E, lbl_804CB84F, lbl_804CB850;
extern u8 lbl_804CB852;
extern Grid lbl_803EC898;
static inline void Mv(u8 h, u8 w, s8 dx, s8 y) {
    s8 x = lbl_804CB84D;
    s8 dy = lbl_804CB850;
    lbl_804CB852 = 1;
    int a = x + w - dx;
    int b = y + h - dy;
    lbl_804CB84D = a % w;
    lbl_804CB84E = b % h;
}
void fn_8013E77C(void) {
    if (lbl_804CB84C) {
        Mv(lbl_803EC898.h, lbl_803EC898.w, lbl_804CB84F, lbl_804CB84E);
    }
}
}
