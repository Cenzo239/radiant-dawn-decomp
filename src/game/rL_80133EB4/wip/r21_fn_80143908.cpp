/* fn_80143908 (0x480): complete self-contained draft (round 21), the round 14 section of wip/near4.cpp unchanged.
 * Level `other`: 287 of 288 instructions, 17 masked lines, all in the texture write loop. The original computes a
 * dead `srawi r3,r9,2` (y >> 2) in the outer loop next to `extlwi r4,r9,25,5` ((y >> 2) * 128) and `clrlslwi`
 * ((y & 3) * 4) and adds the two after the x counter is cleared; ours has no srawi and two volatile registers
 * shift. Forms tried this round without getting the srawi: named `by`/`bx`/`oy`/`ox` locals in the inner or the
 * outer loop, `y / 4`, `<< 7`, an inline `Px(tex, x, y)` with locals, each also with opt_propagation off, and
 * opt_strength_reduction off; a hoisted `row` local breaks the 2x unrolling (435 instructions).
 * fn_8017C40C and fn_8017D428 (region R) have the same dead srawi.
 */
/* Water surface: 32x32 height field step, written into the tiled IA8 texture. */
#include "game/rL_80133EB4/types.h"
#pragma use_lmw_stmw off

struct Ripple {
    u8 pad0[0x48];
    u8* x48;
    u8* x4c;
    f32* x50;
    f32* x54;
    f32* x58;
    f32* x5c;
};
struct MM63 {
    u8 pad0[0x63];
    u8 x63;
};
extern "C" {
extern MM63* fn_8013B9A8(void);
extern void DCFlushRange(void*, u32);

void fn_80143908(Ripple* r) {
    /*P*/
    MM63* mm;
    int x;
    int y;
    /*E*/
    f32 a[0x400];
    f32 b[0x400];
    if (r->x48 == 0) return;
    mm = fn_8013B9A8();
    if (mm == 0) return;
    if (mm->x63 == 0) return;
    for (y = 0; y < 32; y++) {
        for (x = 0; x < 32; x++) {
            int i = x + y * 32;
            a[i] = r->x50[i];
            b[i] = r->x54[i];
        }
    }
    DCFlushRange(a, 0x1000);
    DCFlushRange(b, 0x1000);
    f32 k = 1.0f / (f32)mm->x63;
    for (y = 0; y < 32; y++) {
        for (x = 0; x < 32; x++) {
            f32 ax = 0.0f;
            f32 ay = ax;
            int ym = y - 1;
            int i = x + y * 32;
            if (ym < 0) ym = 31;
            int yp = y + 1;
            if (yp > 31) yp = 0;
            int xm = x - 1;
            if (xm < 0) xm = 31;
            int xp = x + 1;
            if (xp > 31) xp = 0;
            ax += k * a[x + ym * 32];
            ay += k * b[x + ym * 32];
            ax += k * a[xp + y * 32];
            ay += k * b[xp + y * 32];
            ax += k * a[xm + y * 32];
            ay += k * b[xm + y * 32];
            ax += k * a[x + yp * 32];
            ay += k * b[x + yp * 32];
            ax -= 4.0f * (k * a[i]);
            ay -= 4.0f * (k * b[i]);
            r->x58[i] += ax;
            r->x5c[i] += ay;
            r->x50[i] += k * r->x58[i];
            r->x54[i] += k * r->x5c[i];
            if (x == 0 || x == 31) r->x50[i] = 0.0f;
            if (y == 0 || y == 31) r->x54[i] = 0.0f;
        }
    }
    u8* old = r->x48;
    u8* tex = r->x4c;
    for (y = 0; y < 32; y++) {
        
        for (x = 0; x < 32; x++) {
            int i = x + y * 32; u8 h = 127.0f * (1.0f + r->x50[i]); u8 v = 127.0f * (1.0f + r->x54[i]); u8* d = tex + ((y >> 2) * 128 + (y & 3) * 4 + ((x >> 2) * 16 + (x & 3))) * 2; d[0] = h; d[1] = v;
        }
    }
    DCFlushRange(tex, 0x800);
    r->x4c = old;
    r->x48 = tex;
}
}
