/* GParticle.c update. Paired-single loads and stores go through OSFastCast-style inline asm. */
#include "game/rA_800068A0/types.h"
extern "C" {
typedef f32 Mtx[3][4];
typedef struct Vec { f32 x, y, z; } Vec;
typedef struct S6 { s16 x, y, z; } S6;
typedef struct C4 { u8 r, g, b, a; } C4;
typedef struct PTrack { u16 id; u8 shift; u8 x3; u16 x4; u16 n; int ofs; } PTrack;
typedef struct PKeyK { s16 f; s16 v; } PKeyK;
typedef struct PEnt { u16 idx; u16 x2; u16 first; u16 cnt; } PEnt;
typedef struct PPart { Vec pos; Vec vel; f32 age; f32 t; f32 sx; f32 sy; f32 size; C4 col; s16 rot[9]; s16 rt[3]; u8 x48; u8 x49; s16 x4A; } PPart;
typedef struct PSeg { u8 x0[6]; u16 flags; u8 x8[2]; s16 mat; u8 xC[2]; s16 xE; u8 x10[2]; s16 x12; u8 x14[2]; s16 x16; s16 x18; s16 x1A; u16 node; u16 count; u8* parts; PEnt* ents; PTrack* tracks; void* keys; u8 x30[4]; } PSeg;
typedef struct PInfo { u8 x0[6]; u16 nseg; PSeg segs[1]; } PInfo;
typedef struct PBuf { f32 cur; f32 dt; u8 x8[4]; PPart* parts; S6* trail; } PBuf;
typedef struct PState { u8 x0[0x30]; PInfo* info; PBuf* buf; } PState;
typedef struct PMatE { u8 x0[8]; C4 col; u8 xC[0x14]; } PMatE;
typedef struct PMats { u8 x0[0x34]; PMatE* e; } PMats;
typedef struct PNode { u8 x0[0xC]; u32 flags; } PNode;
typedef struct PActor { u8 x0[8]; C4 col; u8 mt[0x54 - 0xC]; PState* st; } PActor;
extern char lbl_80360DF8[];
extern PMats* fn_80007F3C(PActor*);
extern void* fn_80007F10(PActor*);
extern void* fn_80007EE4(PActor*);
extern PNode* fn_8000F3D4(void*, int);
extern int fn_8000AB6C(void*, int, u8*, f32);
extern int fn_8000A838(void*, int, int, C4*, f32);
extern void fn_8001E008(const char*, int, const char*);
extern int fn_8000A7A0(PKeyK*, int, int);
extern S6 fn_8001E144(const Vec*);
extern void* fn_8001E1A4(void*, Mtx);
extern void* fn_8001E318(Mtx, void*);
extern void fn_80312DB4(const Mtx, const Vec*, Vec*);
extern void fn_8001D44C(void*, Mtx);
extern void fn_8001E6D0(const Mtx, Mtx);
#if TARGET_PC
/* Host: GQR model and quantized loads/stores of fe10/gekko.h */
static inline void FastCast(void) { fe10_fastcast_init(); }
static inline void SetG5(u32 v) { fe10_gqr[5] = v; }
static inline f32 LD5(const void* p) { return fe10_psq_l(p, 5); }
static inline s16 f2s(f32 v) { union { u32 w; s16 h; } t; fe10_psq_st(&t, v, 5); return t.h; }
#else
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
static inline void SetG5(register u32 v) { asm { mtspr 0x395, v } }
static inline f32 LD5(register const void* p) { register f32 r; asm { psq_l r, 0(p), 1, 5 } return r; }
static inline s16 f2s(register f32 v) { u32 tmp; register u32* p = &tmp; register s16 out; asm { psq_st v, 0(p), 1, 5; lha out, 0(p) } return out; }
#endif
void fn_800158FC(PActor* a) {
/*P*/
    PState* st;
    PMats* mats;
    void* anm;
    void* model;
    PInfo* info;
    PSeg* s;
    PBuf* b;
    int i;
    int zero;
    int idx;
    PPart* p;
    u8* kk;
    PEnt* e;
    int j;
    PTrack* tr;
    int m;
    s16 k;
    PPart* p2;
    u8* k2;
    int j2;
    PKeyK* keys;
    int slot;
    u16 n;
/*E*/
    f32 sx;
    f32 sy;
    f32 fr;
    f32 sz;
    f32 cur;
    C4 col;
    Mtx mv;
    Mtx mp;
    FastCast();
    st = a->st;
    mats = fn_80007F3C(a);
    anm = fn_80007F10(a);
    model = fn_80007EE4(a);
    if (st != 0) {
        zero = 0;
        info = st->info;
        b = st->buf;
        { Vec z = {0.0f, 0.0f, 0.0f}; (void)z; }
        s = info->segs;
        idx = 0;
        for (i = 0; i < info->nseg; i++, s++, b++) {
            if (fn_8000F3D4(model, s->node)->flags & 0x40000000) {
                idx += s->count;
                continue;
            }
            fr = b->cur;
            col = mats->e[s->mat].col;
            fn_8000AB6C(anm, s->mat, &col.a, fr);
            fn_8000A838(anm, s->mat, 7, &col, fr);
            if (a->col.r < 0x80) col.r = (a->col.r * col.r) >> 7;
            if (a->col.g < 0x80) col.g = (a->col.g * col.g) >> 7;
            if (a->col.b < 0x80) col.b = (a->col.b * col.b) >> 7;
            col.a = (col.a * a->col.a) / 255;
            switch (s->flags & 7) {
            case 1: sx = 0.015625f * s->xE; break;
            case 2: sx = 0.015625f * s->x12; break;
            case 4: sx = 0.015625f * s->x16; break;
            case 5: sx = 0.015625f * s->x16; break;
            default: sx = 1.0f; break;
            }
            switch (s->flags & 7) {
            case 1: sy = 0.015625f * s->xE; break;
            case 2: sy = 0.015625f * s->x12; break;
            case 4: sy = 0.015625f * s->x18; break;
            case 5: sy = 0.015625f * s->x18; break;
            default: sy = 1.0f; break;
            }
            p = b->parts;
            kk = s->parts;
            e = s->ents;
            sz = 0.015625f * s->x1A;
            SetG5(0x00070007);
            for (j = 0; j < s->count; j++, e++, p++, kk += 0xC) {
                if (e->idx != idx++) {
                    fn_8001E008(lbl_80360DF8 + 1, 0x204, lbl_80360DF8 + 0xD);
                }
                if (p->age >= 0.0f) {
                    f32 t0 = LD5(kk + 2);
                    f32 t1 = LD5(kk + 4);
                    t1 = t1 - t0;
                    p->age = p->age + b->dt;
                    if (p->age >= t1) {
                        p->age = -1.0f;
                        continue;
                    }
                    p->t = p->age / t1;
                    cur = t0 + p->age;
                    k = f2s(cur);
                    p->sx = sx;
                    p->sy = sy;
                    p->col.a = (1.0f - p->t) * col.a;
                    p->col.r = col.r;
                    p->col.g = col.g;
                    p->col.b = col.b;
                    p->vel.x = 0.0f;
                    p->vel.y = 0.0f;
                    p->vel.z = 0.0f;
                    p->size = sz;
                    tr = s->tracks + e->first;
                    for (m = 0; m < e->cnt; m++, tr++) {
                        f32 v;
                        u32 q;
                        keys = (PKeyK*)s->keys + tr->ofs;
                        q = tr->shift << 8 | 7;
                        SetG5(q | q << 16);
                        n = tr->n;
                        { PKeyK* z = keys + n;
                        if (k >= z[-1].f) {
                            v = LD5(&z[-1].v);
                        } else if (k < keys[0].f) {
                            v = LD5(&keys[0].v);
                        } else {
                            PKeyK* c = &keys[fn_8000A7A0(keys, k, n)];
                            f32 v0 = LD5(&c[0].v);
                            f32 v1 = LD5(&c[1].v);
                            SetG5(0x00070007);
                            {
                                f32 f0 = LD5(&c[0].f);
                                f32 f1 = LD5(&c[1].f);
                                v = v0 + (v1 - v0) * (cur - f0) / (f1 - f0);
                            }
                        }
                        }
                        SetG5(0x00070007);
                        switch (tr->id) {
                        case 0: p->vel.x = v; break;
                        case 1: p->vel.y = v; break;
                        case 2: p->vel.z = v; break;
                        case 3: p->sx = v; p->sy = v; break;
                        case 8: p->sx = v; break;
                        case 9: p->sy = v; break;
                        case 4: p->col.a = v * col.a; break;
                        case 5: p->col.r = v * col.r; break;
                        case 6: p->col.g = v * col.g; break;
                        case 7: p->col.b = v * col.b; break;
                        case 10: p->size = v; break;
                        }
                    }
                    if (p->x4A >= 0) {
                        S6 u;
                        slot = (p->x49 + p->x48) % 32;
                        u = fn_8001E144(&p->pos);
                        b->trail[slot + p->x4A] = u;
                        if (p->x48 < 0x20) {
                            p->x48 = p->x48 + 1;
                        } else {
                            p->x49 = (slot + 1) % 32;
                        }
                    }
                    fn_8001E1A4(p->rot, mv);
                    fn_80312DB4(mv, &p->vel, &p->vel);
                    p->pos.x = p->vel.x * b->dt + p->pos.x;
                    p->pos.y = p->vel.y * b->dt + p->pos.y;
                    p->pos.z = p->vel.z * b->dt + p->pos.z;
                }
            }
            p2 = b->parts;
            k2 = s->parts;
            SetG5(0x00070007);
            for (j2 = 0; j2 < s->count; j2++, p2++, k2 += 0xC) {
                if (p2->age < 0.0f) {
                    f32 t0 = LD5(k2 + 2);
                    LD5(k2 + 4);
                    if (fr - b->dt <= t0 && fr >= t0) {
                        p2->age = 0.0f;
                        p2->t = 0.0f;
                        p2->col.a = zero;
                        SetG5(0x06070607);
                        p2->pos.x = LD5(k2 + 6);
                        p2->pos.y = LD5(k2 + 8);
                        p2->pos.z = LD5(k2 + 0xA);
                        SetG5(0x00070007);
                        fn_8001D44C(a->mt, mp);
                        if (!(s->flags & 0x20)) {
                            fn_80312DB4(mp, &p2->pos, &p2->pos);
                        }
                        fn_8001E6D0(mp, mp);
                        fn_8001E318(mp, p2->rot);
                    }
                }
            }
        }
    }
}
}
