#include "game/rA_800068A0/types.h"
extern "C" {
typedef struct Key { int frame; int ofs; int cnt; int ofs2; int cnt2; u8 pad[0x1C-0x14]; } Key;
typedef struct SRes { u8 x0[8]; u8 s0; u8 s1; u8 xA[0x1C-0xA]; int n; Key* keys; u8* d24; u8* d28; } SRes;
typedef struct MRes { u8 x0[0x24]; void* base; u8 x28[0x4C-0x28]; u16 c0; u16 c1; u8 x50[0x5C-0x50]; u8 s; } MRes;
typedef struct Act { u8 x0[0x48]; MRes* m; u8 x4C[4]; SRes* st; u8 x54[4]; f32 frame; u8 x5C[0x6C-0x5C]; s16* o6c; s8* o70; } Act;
extern void memcpy(void*, const void*, u32);
extern void DCFlushRange(void*, u32);
#if TARGET_PC
/* Host: GQR model and quantized loads/stores of fe10/gekko.h */
static inline void SetG2(u32 v) { fe10_gqr[2] = v; }
static inline void SetG3(u32 v) { fe10_gqr[3] = v; }
static inline void SetG4(u32 v) { fe10_gqr[4] = v; }
static inline void FastCast(void) { fe10_fastcast_init(); }
#define LD(dst, ofs, reg, q) ((dst) = fe10_psq_l((const u8*)(reg) + (ofs), q))
static inline f32 LD2(const void* p) { return fe10_psq_l(p, 2); }
static inline f32 LD3(const void* p) { return fe10_psq_l(p, 3); }
static inline f32 LD4(const void* p) { return fe10_psq_l(p, 4); }
static inline u16 ST3(f32 v) { union { u32 w; u16 h; } t; fe10_psq_st(&t, v, 3); return t.h; }
static inline s8 ST4(f32 v) { union { u32 w; s8 b; } t; fe10_psq_st(&t, v, 4); return t.b; }
#else
static inline void SetG2(register u32 v) { asm { mtspr 0x392, v } }
static inline void SetG3(register u32 v) { asm { mtspr 0x393, v } }
static inline void SetG4(register u32 v) { asm { mtspr 0x394, v } }
static inline void FastCast(void) {
    asm {
        li r3, 4
        oris r3, r3, 4
        mtspr 0x392, r3
        li r3, 5
        oris r3, r3, 5
        mtspr 0x393, r3
        li r3, 6
        oris r3, r3, 6
        mtspr 0x394, r3
        li r3, 7
        oris r3, r3, 7
        mtspr 0x395, r3
    }
}
#define LD(dst, ofs, reg, q) asm { psq_l dst, ofs(reg), 1, q }
static inline f32 LD2(register const void* p) { register f32 r; asm { psq_l r, 0(p), 1, 2 } return r; }
static inline f32 LD3(register const void* p) { register f32 r; asm { psq_l r, 0(p), 1, 3 } return r; }
static inline f32 LD4(register const void* p) { register f32 r; asm { psq_l r, 0(p), 1, 4 } return r; }
/* These follow the SDK's OSFastCast.h shape: the compiler folds the pointer into the psq displacement and still schedules the asm. */
static inline u16 ST3(register f32 v) { u32 tmp; register u32* p = &tmp; register u16 out; asm { psq_st v, 0(p), 1, 3; lhz out, 0(p) } return out; }
static inline s8 ST4(register f32 v) { u32 tmp; register u32* p = &tmp; register s8 out; asm { psq_st v, 0(p), 1, 4; lbz out, 0(p); extsb out, out } return out; }
#endif
static inline f32 LERP(f32 a, f32 b, f32 t) { f32 d = a * t; return b + d; }
#pragma fp_contract off
void fn_8001C904(Act* a) {
    SRes* st;
    Key* k;
    Key* prev;
    int i;
    int n;
    register f32 t;
    st = a->st;
    k = st->keys;
    memcpy(a->o6c, a->m->base, a->m->c0 * 6 + a->m->c1 * 3);
    n = st->n;
    for (i = 0; i < n; i++) {
        if (a->frame < (f32)k->frame) break;
        prev = k;
        k++;
    }
    {
        u32 q = st->s0 << 8 | 6;
        SetG2(q | q << 16);
    }
    {
        u32 q = a->m->s << 8 | 7;
        SetG3(q | q << 16);
    }
    t = (a->frame - (f32)prev->frame) / (f32)(k->frame - prev->frame);
    {
    s16* o = a->o6c;
    register u8* rec = st->d24 + k->ofs * 4;
    for (i = 0; i < k->cnt; i++, rec += 4) {
        o += rec[0] * 3;
        {f32 x = LD2(rec + 1); f32 y = LD3(o); o[0] = ST3(y + (x * t));}
        {f32 x = LD2(rec + 2); f32 y = LD3(o + 1); o[1] = ST3(y + (x * t));}
        {f32 x = LD2(rec + 3); f32 y = LD3(o + 2); o[2] = ST3(y + (x * t));}
    }
    }
    t = 1.0f - t;
    {
    s16* o = a->o6c;
    register u8* rec = st->d24 + prev->ofs * 4;
    for (i = 0; i < prev->cnt; i++, rec += 4) {
        o += rec[0] * 3;
        {f32 x = LD2(rec + 1); f32 y = LD3(o); o[0] = ST3(y + (x * t));}
        {f32 x = LD2(rec + 2); f32 y = LD3(o + 1); o[1] = ST3(y + (x * t));}
        {f32 x = LD2(rec + 3); f32 y = LD3(o + 2); o[2] = ST3(y + (x * t));}
    }
    }
    {
        u32 q = st->s1 << 8 | 6;
        SetG2(q | q << 16);
    }
    SetG4(0x07060706);
    t = 1.0f - t;
    {
    s8* o = a->o70;
    register u8* rec = st->d28 + k->ofs2 * 4;
    for (i = 0; i < k->cnt2; i++, rec += 4) {
        o += rec[0] * 3;
        {f32 x = LD2(rec + 1); f32 y = LD4(o); o[0] = ST4(y + (x * t));}
        {f32 x = LD2(rec + 2); f32 y = LD4(o + 1); o[1] = ST4(y + (x * t));}
        {f32 x = LD2(rec + 3); f32 y = LD4(o + 2); o[2] = ST4(y + (x * t));}
    }
    }
    t = 1.0f - t;
    {
    s8* o = a->o70;
    register u8* rec = st->d28 + prev->ofs2 * 4;
    for (i = 0; i < prev->cnt2; i++, rec += 4) {
        o += rec[0] * 3;
        {f32 x = LD2(rec + 1); f32 y = LD4(o); o[0] = ST4(y + (x * t));}
        {f32 x = LD2(rec + 2); f32 y = LD4(o + 1); o[1] = ST4(y + (x * t));}
        {f32 x = LD2(rec + 3); f32 y = LD4(o + 2); o[2] = ST4(y + (x * t));}
    }
    }
    DCFlushRange(a->o6c, a->m->c0 * 6 + a->m->c1 * 3);
    FastCast();
}
#pragma fp_contract on
}
