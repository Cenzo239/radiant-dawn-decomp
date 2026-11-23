/* fn_80145078 (0x2A4): functionally equal at `regs` level (tools/check_regs.py, round 21; 16 words differ, all
 * in the choice of f0..f3 for the position copy and the velocity products). Written from the disassembly.
 * Weather: spawn one particle (names guessed). Takes a node from the pool's free stack and links it at the tail,
 * picks a random position inside the box lo..hi (in steps of 0.1), a random horizontal velocity of
 * 0..99 * 0.0001 per axis stored as s16 with 8 fraction bits, and a life of w->x36 (randomised to 7/8..9/8 of it
 * when above 8). The float/s16 conversions go through GQR5 like fn_80144BAC, which reads the velocity back.
 * Port caveats: the GQR5 inlines are `(s16)f` (scale 0), `(s16)(f * 256.0f)` (scale 8) and `(f32)s16`; the three
 * s16 scratch locals are reused for the velocity randoms as in the original. ST5b/ST5c are wrappers that only
 * place the three conversion temporaries in ascending stack slots; the block-scoped fx/fy/fz fix the order of the
 * float operations (all differences, then all conversions).
 */
#include "game/rL_80133EB4/types.h"
#pragma use_lmw_stmw off
struct Part {
    s16 t;      /* 0x08 */
    s16 life;   /* 0x0A */
    u8 alpha;   /* 0x0C */
    u8 pad5;
    s16 vel[3]; /* 0x0E */
    Vec pos;    /* 0x14 */
};
struct PNode { PNode* n; PNode* p; Part d; };
struct PL { PNode** a; PNode** b; PNode** c; PNode* d; PNode* e; int f; };
struct RP2 { u8 pad0[0x30]; u8 x30, x31, x32, pad33; f32 x34; void* x38; PL* x3c; };
struct WeatherP {
    u8 pad0[0x36];
    s16 x36;
    u8 pad38[0x54 - 0x38];
    Vec lo;       /* 0x54 */
    Vec hi;       /* 0x60 */
};
extern "C" {
extern u32 fn_80089ED0(void);
}
static inline void SetGQR5(register u32 v) { asm { mtspr GQR5, v } }
static inline f32 LD5(register const void* p) { register f32 r; asm { psq_l r, 0(p), 1, 5 } return r; }
static inline s16 ST5(register f32 v) { u32 tmp; register u32* p = &tmp; register s16 out; asm { psq_st v, 0(p), 1, 5; lha out, 0(p) } return out; }
static inline s16 ST5b(f32 v) { return ST5(v); }
static inline s16 ST5c(f32 v) { return ST5b(v); }
static inline PNode* Alloc(PL* l) {
    PNode* n = *l->c;
    if (n == 0) {
        return 0;
    }
    n->p = l->e;
    n->n = 0;
    if (l->e) {
        l->e->n = n;
    }
    if (l->d == 0) {
        l->d = n;
    }
    l->e = n;
    l->c++;
    l->f++;
    return n;
}
extern "C" void fn_80145078(RP2* r, WeatherP* w) {
    PNode* n = Alloc(r->x3c);
    if (n) {
        s16 life = w->x36;
        Vec lo = w->lo;
        Vec hi = w->hi;
        Vec pos;
        Vec vel;
        s16 dx, dy, dz;
        if (life > 8) {
            life = life * 7 / 8 + fn_80089ED0() % (life * 2 / 8);
        }
        SetGQR5(0x00070007);
        {
            f32 fx = hi.x - lo.x;
            f32 fy = hi.y - lo.y;
            f32 fz = hi.z - lo.z;
            dx = ST5(fx);
            dy = ST5(fy);
            dz = ST5(fz);
        }
        dx = fn_80089ED0() % (dx * 10);
        dy = fn_80089ED0() % (dy * 10);
        dz = fn_80089ED0() % (dz * 10);
        {
            f32 fx = LD5(&dx);
            f32 fy = LD5(&dy);
            f32 fz = LD5(&dz);
            pos.x = 0.1f * fx + lo.x;
            pos.y = 0.1f * fy + lo.y;
            pos.z = 0.1f * fz + lo.z;
        }
        dx = fn_80089ED0() % 100;
        dz = fn_80089ED0() % 100;
        {
            f32 fx = LD5(&dx);
            f32 fz = LD5(&dz);
            n->d.pos = pos;
            vel.x = 0.0001f * fx;
            vel.y = 0.0f;
            vel.z = 0.0001f * fz;
        }
        SetGQR5(0x08070807);
        n->d.vel[0] = ST5c(vel.x);
        n->d.vel[1] = ST5b(vel.y);
        n->d.vel[2] = ST5(vel.z);
        n->d.life = life;
        n->d.t = 0;
    }
}
