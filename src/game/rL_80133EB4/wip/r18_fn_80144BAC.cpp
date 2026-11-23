/* fn_80144BAC (round 18): other by one instruction (72 of 73). The psq_l/GQR5 code is ordinary C with asm inlines; the original keeps a third stack store (stfs f6,0x10(r1)) of the z velocity that is removed as dead here. */
/* Weather particle step: add the quantized velocity (s16 with 8 fraction bits, read through GQR5)
 * plus wind to the position and fade the alpha in over the first fifth of the life and out over
 * the rest. Names guessed. */
#include "game/rL_80133EB4/types.h"
struct Part {
    s16 t;      /* 0x00 */
    s16 life;   /* 0x02 */
    u8 alpha;   /* 0x04 */
    u8 pad5;
    s16 vel[3]; /* 0x06 */
    Vec pos;    /* 0x0C */
};
extern "C" {
u8 fn_8001F04C(int, int, int, int);
}
static inline void SetGQR5(register u32 v) { asm { mtspr GQR5, v } }
static inline f32 LD5(register const void* p) { register f32 r; asm { psq_l r, 0(p), 1, 5 } return r; }

extern "C" int fn_80144BAC(Part* p, Vec* wind, int a) {
    Vec d;
    int k;
    SetGQR5(0x08070807);
    d.x = LD5(&p->vel[0]);
    d.y = LD5(&p->vel[1]);
    d.z = LD5(&p->vel[2]);
    d.x += wind->x;
    d.y += wind->y;
    d.z += wind->z;
    p->t++;
    if (p->t >= p->life) {
        return 0;
    }
    k = p->life / 5;
    if (p->t < k) {
        p->alpha = fn_8001F04C(0, a, k, p->t);
    } else {
        p->alpha = fn_8001F04C(a, 0, p->life - k, p->t - k);
    }
    p->pos.x += d.x;
    p->pos.y += d.y;
    p->pos.z += d.z;
    return 1;
}
