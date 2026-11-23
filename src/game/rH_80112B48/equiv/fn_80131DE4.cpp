/* fn_80131DE4 (0x1250): map cursor movement from the pad (names guessed). Complete draft, round 21.
 * Level: `sched` (tools/check_regs.py, 65 words differ; 1172 of 1172 instructions, same blocks).
 * Moved/differing lines (tools/equiv/dd.py): in both inlined copies of Step, the four float-to-int scratch
 * doubles of the "occupied tile" test (cur x/y, new x/y) sit in other r1 slots (0x18..0x37) and their stfd/lwz
 * pairs are scheduled one or two lines apart; in Settle the first fn_80062230 call loads f2 (G.f938) before
 * `mr r3` and f1 where ours loads f1 first.
 * symcheck --anon: 178 blocks, 2 differ, both "stack bytes differ at 0x20..0x37" in the Step test block: these
 * bytes are the fctiwz scratch doubles, each read back in the same block and dead afterwards, so the flag is
 * an artefact of which scratch slot holds which conversion.
 * Port notes: fn_80062230 is (GmC*, f32 x, f32 y) here (the floats are passed in f1/f2). `cs` is the s8
 * conversion helper of fn_80133034.cpp. `e` as a named local keeps 0.001f in one register (as the original).
 * The `int ax, cx, cy, ay` locals only reproduce the early conversions and the 0xb0 frame.
 *
 * What it does: when the cursor model is on (W.b6D5), the d-pad (v3C bits 0..3) switches to digital mode
 * (W.b6B4 = 1) and any stick deflection (v50/v54) back to analogue (0).
 *   digital: target (G.f934, G.f938) is snapped to tile centres; with a direction held (v34 & 0xF) the cursor
 *     moves one tile per press (v3C), or every other frame at double speed while v34 & 0x800 is held
 *     (lbl_804CB828 counts frames, reset on the press v48 & 0x800). (G.x, G.y) then follows the target by
 *     0.5 (fast, lbl_804CB819 = 2) or 0.25 (lbl_804CB819 = 1; also when idle) per frame.
 *   analogue: the stick vector is rotated by the camera yaw (fn_8000F470()->f108) and added at 1/133.33 per unit
 *     (fast, v34 & 0x800) or 1/400; with the stick released the cursor settles toward the tile centre.
 * Tile 0xA7 (fn_80118098) blocks the cursor; movement then slides along one axis when that tile is free.
 * A change of tile plays SFX_SYS_CURSOR_MAP_MOVE1.
 */
#include "game/rH_80112B48/campad.h"
#include "game/rH_80112B48/map.h"
extern "C" {
struct CamW {
    f32 f0;
    f32 f4;
    u8 pad8[0x658 - 8];
    f32 f658;
    f32 f65C;
    u8 pad660[0x6b4 - 0x660];
    u8 b6B4;
    u8 pad6B5[0x6d4 - 0x6b5];
    u8 b6D4;
    u8 b6D5;
};
struct GmC {
    u8 pad0[0x934];
    f32 f934, f938;
    u8 pad93C[8];
    f32 x, y;
};
struct CamS {
    u8 pad0[0x108];
    f32 yaw;
};
extern CamW lbl_80413510;
extern GmC lbl_803CAB38;
extern Map lbl_803EC898;
extern s8 lbl_80369430[16][2];
extern char lbl_80386018[];
extern u32 lbl_804CB700;
extern u8 lbl_804CB819;
extern int lbl_804CB828;
u8 fn_80118098(Map* m, s8 x, s8 y);
void fn_80062230(GmC*, f32, f32);
CamS* fn_8000F470(void);
double fn_80295534(double);
double fn_80295940(double);
void fn_80253EE4(const char*, f32);

#define W lbl_80413510
#define G lbl_803CAB38
#define M lbl_803EC898

static inline s8 cs(f32 v) { return (int)v; }
static inline BOOL Enter(s8 cx, s8 cy, s8 nx, s8 ny) {
    return ((s16*)M.cur)[cx + (cy << 6)] < 0 || ((s16*)M.cur)[nx + (ny << 6)] >= 0;
}
static inline void Clamp(void) {
    if (W.b6D5) {
        f32 x = G.x;
        f32 y = G.y;
        if (x < M.x0) x = M.x0;
        if (x >= M.x1) x = M.x1 - 0.5f;
        if (y < M.y0) y = M.y0;
        if (y >= M.y1) y = M.y1 - 0.5f;
        if (x != G.x || y != G.y) {
            G.f934 = x;
            G.f938 = y;
            G.x = x;
            G.y = y;
        }
    }
}
static inline void Snap(void) {
    if (W.b6D5) {
        G.f934 = (int)G.f934 + 0.5f;
        G.f938 = (int)G.f938 + 0.5f;
    }
}
static inline void Step(int pad) {
    if (W.b6D5) {
        u32 d = pad & 0xF;
        if (d != 0 && !(lbl_804CB700 & 0x80)) {
            f32 ox = G.f934;
            f32 nx = ox + lbl_80369430[d][0];
            f32 oy = G.f938;
            f32 ny = oy + lbl_80369430[d][1];
            if (nx <= M.x0 || nx >= M.x1) nx = ox;
            if (ny <= M.y0 || ny >= M.y1) ny = oy;
            if (fn_80118098(&M, cs(nx), cs(ny)) == 0xA7) {
                if (fn_80118098(&M, cs(ox), cs(ny)) != 0xA7) {
                    nx = ox;
                } else if (fn_80118098(&M, cs(nx), cs(oy)) != 0xA7) {
                    ny = oy;
                } else {
                    return;
                }
            }
            if (lbl_804CB700 & 0x400) {
                int ax = (int)nx;
                int cx = (int)G.f934;
                int cy = (int)G.f938;
                int ay = (int)ny;
                if (((s16*)M.cur)[(s8)cx + ((s8)cy << 6)] >= 0
                    && ((s16*)M.cur)[(s8)ax + ((s8)ay << 6)] < 0
                    && d != (lbl_804CB5B8->v48() & 0xF)) {
                    return;
                }
            }
            G.f934 = nx;
            G.f938 = ny;
            G.x = 0.5f + (int)G.x;
            G.y = 0.5f + (int)G.y;
        }
    }
}
static inline void Follow(f32 k) {
    if (W.b6D5) {
        f32 x = G.x;
        f32 y = G.y;
        f32 e = 0.001f;
        if (G.f934 < x - e) x -= k;
        if (G.f934 > x + e) x += k;
        if (G.f938 < y - e) y -= k;
        if (G.f938 > y + e) y += k;
        G.x = x;
        G.y = y;
        fn_80062230(&G, x, y);
    }
}
static inline void Stick(f32 div) {
    if (!(lbl_804CB700 & 0x80) && W.b6D5) {
        f32 ox = G.x;
        f32 oy = G.y;
        f32 yaw = -fn_8000F470()->yaw;
        f32 sx = (f32)lbl_804CB5B8->v50() / div;
        f32 sy = (f32)lbl_804CB5B8->v54() / div;
        f32 c = fn_80295534(0.017453292f * yaw);
        f32 s = fn_80295940(0.017453292f * yaw);
        f32 ny = oy - (s * sx + c * sy);
        f32 nx = ox + (c * sx - s * sy);
        if (nx < M.x0) nx = M.x0;
        if (nx >= M.x1) nx = M.x1 - 0.01f;
        if (ny < M.y0) ny = M.y0;
        if (ny >= M.y1) ny = M.y1 - 0.01f;
        if (fn_80118098(&M, cs(nx), cs(ny)) == 0xA7) {
            if (fn_80118098(&M, cs(ox), cs(ny)) != 0xA7) {
                nx = ox;
            } else if (fn_80118098(&M, cs(nx), cs(oy)) != 0xA7) {
                ny = oy;
            } else {
                return;
            }
        }
        G.f934 = nx;
        G.f938 = ny;
        G.x = nx;
        G.y = ny;
        fn_80062230(&G, nx, ny);
    }
}
static inline void Settle(void) {
    f32 x, y, cx, cy;
    fn_80062230(&G, G.f934, G.f938);
    x = G.x;
    y = G.y;
    W.f0 = W.f4 = 0.0f;
    cx = 0.5f + (int)x;
    cy = 0.5f + (int)y;
    x = (3.0f * x + cx) * 0.25f;
    y = (3.0f * y + cy) * 0.25f;
    G.x = x;
    G.y = y;
    G.f934 = x;
    G.f938 = y;
    fn_80062230(&G, x, y);
}

void fn_80131DE4(void) {
    int tx, ty;
    if (W.b6D5) {
        if (lbl_804CB5B8->v3C() & 0xF) {
            W.b6B4 = 1;
        }
        if (lbl_804CB5B8->v50() | lbl_804CB5B8->v54()) {
            W.b6B4 = 0;
        }
        Clamp();
        lbl_804CB819 = 0;
        tx = G.x;
        ty = G.y;
        if (W.b6B4) {
            Snap();
            if (lbl_804CB5B8->v34() & 0xF) {
                if (lbl_804CB5B8->v34() & 0x800) {
                    int pad;
                    if (lbl_804CB5B8->v48() & 0x800) {
                        lbl_804CB828 = 0;
                    }
                    if (++lbl_804CB828 & 1) {
                        pad = lbl_804CB5B8->v34();
                    } else {
                        pad = 0;
                    }
                    Step(pad);
                    Follow(0.5f);
                    lbl_804CB819 = 2;
                } else {
                    Step(lbl_804CB5B8->v3C());
                    Follow(0.25f);
                    lbl_804CB819 = 1;
                }
            } else {
                Follow(0.25f);
            }
        } else {
            if (lbl_804CB5B8->v50() | lbl_804CB5B8->v54()) {
                if (lbl_804CB5B8->v34() & 0x800) {
                    Stick(133.33333f);
                    lbl_804CB819 = 2;
                } else {
                    Stick(400.0f);
                }
            } else {
                Settle();
            }
        }
        if (tx != (int)G.x || ty != (int)G.y) {
            fn_80253EE4(lbl_80386018, 0.0f);
        }
        W.b6D4 = 0;
    }
}
}
