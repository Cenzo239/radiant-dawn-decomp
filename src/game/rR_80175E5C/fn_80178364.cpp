/* fn_80178364 (0x934): exact (round m13: `#pragma opt_lifetimes off`, scalars at the top, own counters for the
 * second spline loop (j2) and the first arc-length loop (i2), `base` computed before `al`). Written in round 20
 * from the disassembly.
 * Caveats a port must undo or know:
 *   - InitCast is OSInitFastCast (GQR2..5); U8F/ToU8 are the SDK's __OSu8tof32/__OSf32tou8 (psq_l/psq_st through
 *     GQR2). On another CPU they are plain (f32)u8 and a saturating (u8)f32 conversion.
 *   - `tot` is unused: the original also computes count*sub and starts converting it to float without using it.
 *   - ToU8b and SetGrey exist only to place the stack slots (tmp 0xC, colour 0x10, its copy 0x14).
 *   - The grey {0x80,0x80,0x80} is the 3-byte constant at lbl_804CE470+0x28 (.sdata2), written here as a local
 *     initialiser; fn_8000987C is declared as taking a pointer to the colour copy (really a by-value colour).
 *   - The arc length loops read verts[0] for the first midpoint, not verts[base]; that is what the original does.
 *   - Field names in Pt/Trail are guesses; Trail matches fn_8017794C.cpp (x4A is `nv` here).
 */
/* fn_80178364: weapon trail update: resamples the ring of recorded segments with a Catmull-Rom style spline into
 * the vertex list (count * sub points), smooths the newest points, then sets each point's alpha and texture
 * coordinate from its distance along the trail, and uploads the trail colour. Names guessed. */
#include "game/rR_80175E5C/types.h"
#pragma use_lmw_stmw off
struct C4 { u8 r, g, b, a; };
struct V3 { f32 x, y, z; };
struct Pt {
    V3 v[2];     /* 0x00: the two edge points */
    V3 mid;      /* 0x18 */
    u8 alpha;    /* 0x24 */
    u8 x25;
    s16 tc;      /* 0x26 */
};
struct Trail {
    u8 pad0[0x30];
    void* arch;
    void* tex;
    C4 c0;
    C4 c1;
    Pt* segs;
    Pt* verts;
    u16 head;
    u16 nv;
    u16 count;
    u16 cap;
    u8 flags;
    u8 pad51;
    u8 sub;
    u8 x53;
    u8 x54;
    u8 fade;
    s16 speed;
};
extern "C" {
void fn_8001F0A4(V3*, V3*, V3*, V3*);
f32 fn_8001EFE4(f32, f32, f32, f32, f32);
f32 fn_8001EF30(f32, f32, f32, f32);
void fn_80313484(const V3*, const V3*, V3*);
f32 fn_80313508(const V3*);
void fn_8000987C(void*, C4*);
void fn_80009A2C(void*);
}
static inline void InitCast() {
    asm {
        li r3, 4
        oris r3, r3, 4
        mtspr GQR2, r3
        li r3, 5
        oris r3, r3, 5
        mtspr GQR3, r3
        li r3, 6
        oris r3, r3, 6
        mtspr GQR4, r3
        li r3, 7
        oris r3, r3, 7
        mtspr GQR5, r3
    }
}
static inline f32 U8F(register u8* p) { register f32 r; asm { psq_l r, 0(p), 1, 2 } return r; }
static inline u8 ToU8(register f32 f) {
    u32 tmp;
    register u8* p = (u8*)&tmp;
    register u8 r;
    asm {
        psq_st f, 0(p), 1, 2
        lbz r, 0(p)
    }
    return r;
}
static inline void Mid(V3* o, Trail* t, int i) {
    o->x = 0.5f * (t->verts[i].v[0].x + t->verts[i].v[1].x);
    o->y = 0.5f * (t->verts[i].v[0].y + t->verts[i].v[1].y);
    o->z = 0.5f * (t->verts[i].v[0].z + t->verts[i].v[1].z);
}

static inline void SetGrey(Trail* t) {
    C4 c = {0x80, 0x80, 0x80, (u32)t->c0.a >> 1};
    C4 cc = c;
    fn_8000987C(t->arch, &cc);
}
static inline u8 ToU8b(f32 f) { return ToU8(f); }
#pragma opt_lifetimes off
extern "C" void fn_80178364(Trail* t) {
        int i;
    f32 al;
    u8 k;
    int j;
    f32 tot;
    int idx;
    f32 v;
    int base;
    int j2;
    u8 a;
    f32 u;
    f32 total;
    f32 acc;
    int i2;
    InitCast();
    tot = t->count * t->sub;
    for (i = 0; i < t->count; i++) {
        Pt p[4];
        if (i > 0) {
            p[0] = t->segs[(i + t->cap + t->head - 1) % t->cap];
        } else {
            p[0] = t->segs[(t->head + i) % t->cap];
        }
        p[1] = t->segs[(t->head + i) % t->cap];
        if (i < t->count - 1) {
            p[2] = t->segs[(i + t->head + 1) % t->cap];
        } else {
            p[2] = p[1];
        }
        if (i < t->count - 2) {
            p[3] = t->segs[(i + t->head + 2) % t->cap];
        } else {
            p[3] = p[2];
        }
        for (j = 0; j < 2; j++) {
            fn_8001F0A4(&p[0].v[j], &p[1].v[j], &p[2].v[j], &p[3].v[j]);
        }
        for (k = 0; k < t->sub; k++) {
            u = (1.0f + U8F(&k)) / U8F(&t->sub);
            idx = k + i * t->sub;
            for (j2 = 0; j2 < 2; j2++) {
                t->verts[idx].v[j2].x = fn_8001EFE4(p[0].v[j2].x, p[1].v[j2].x, p[2].v[j2].x, p[3].v[j2].x, u);
                t->verts[idx].v[j2].y = fn_8001EFE4(p[0].v[j2].y, p[1].v[j2].y, p[2].v[j2].y, p[3].v[j2].y, u);
                t->verts[idx].v[j2].z = fn_8001EFE4(p[0].v[j2].z, p[1].v[j2].z, p[2].v[j2].z, p[3].v[j2].z, u);
            }
        }
    }
    base = t->count * t->sub - t->nv;
    al = t->c0.a * t->x54 / 255;
    for (i = 0; i < t->nv; i++) {
        idx = i + base;
        t->verts[idx].mid.x = fn_8001EF30(t->verts[idx].v[0].x, t->verts[idx].v[1].x, 1.0f, 0.125f);
        t->verts[idx].mid.y = fn_8001EF30(t->verts[idx].v[0].y, t->verts[idx].v[1].y, 1.0f, 0.125f);
        t->verts[idx].mid.z = fn_8001EF30(t->verts[idx].v[0].z, t->verts[idx].v[1].z, 1.0f, 0.125f);
    }
    if (t->nv != 0) {
        V3 prev;
        V3 cur;
        total = 0.0f;
        acc = total;
        Mid(&prev, t, 0);
        for (i2 = 1; i2 < t->nv; i2++) {
            idx = i2 + base;
            Mid(&cur, t, idx);
            fn_80313484(&cur, &prev, &prev);
            total += fn_80313508(&prev);
            prev = cur;
        }
        Mid(&prev, t, 0);
        for (i = 0; i < t->nv; i++) {
            idx = i + base;
            if (i > 0) {
                Mid(&cur, t, idx);
                fn_80313484(&cur, &prev, &prev);
                acc += fn_80313508(&prev);
                prev = cur;
            }
            if (t->tex != 0) {
                v = fn_8001EF30(0.0f, 1.0f, total, acc);
                t->verts[idx].tc = 256.0f * v;
                t->verts[idx].alpha = al;
            } else {
                a = ToU8b(fn_8001EF30(0.0f, al, total, acc));
                t->verts[idx].alpha = a;
            }
        }
    }
    if (t->flags & 4) {
        SetGrey(t);
        fn_80009A2C(t->arch);
    }
}
