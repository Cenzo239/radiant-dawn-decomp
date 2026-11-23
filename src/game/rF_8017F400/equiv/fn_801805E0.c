/* fn_801805E0: per-frame update of a map path trail (Track). Advances the head along the key range, resamples the
   key points with a Catmull-Rom spline (16 steps per segment) into pts[], builds 2D normals into nrm[], trims the
   last point to the fractional head position and reports the head position to the game data.
   Compiled as C like fn_8017FDC8.c: only C keeps the dead stack copy of the default colour. */
#include "game/rF_8017F400/types.h"
typedef struct Track2 {
    GXColor color; u8 unk4; s16 unk6; u8 count; s16 unkA;
    f32 unkC, unk10, unk14, unk18, unk1C;
    s32 keys[32];
    Vec vals[32];
    Vec pts[514];
    Vec nrm[514];
} Track2;
extern u8 lbl_804CA7D0, lbl_804CA7D1, lbl_804CA7D2, lbl_804CA7D3;
extern u8 lbl_803CAB38[];
extern f32 fn_8001EBC8(int, f32, f32, f32, f32);
extern f32 fn_8001EF30(f32, f32, f32, f32);
extern f32 fn_8001EFE4(f32, f32, f32, f32, f32);
extern void fn_803134C4(const Vec* a, Vec* b);
extern void fn_800620A8(void*, f32 x, f32 y);
void fn_801805E0(Track2* t);

static inline void Reset(Track2* p) {
    GXColor c;
    p->count = 0;
    p->unkA = 0;
    p->unkC = 0.0f;
    p->unk10 = 0.0f;
    p->unk14 = 0.0f;
    p->unk18 = 0.0f;
    p->unk1C = 0.0f;
    p->unk4 = 0;
    p->unk6 = 0;
    c.r = lbl_804CA7D0;
    c.g = lbl_804CA7D1;
    c.b = lbl_804CA7D2;
    c.a = lbl_804CA7D3;
    p->color = c;
}
static inline f32 KeyPos(Track2* t, f32 x) {
    int i;
    if (t->count < 2) return 0.0f;
    for (i = 0; i < t->count; i++) {
        if ((f32)t->keys[i] >= x) break;
    }
    if (i == 0) return 0.0f;
    if (t->keys[i] == t->keys[i - 1]) return (f32)(i - 1);
    return fn_8001EF30((f32)(i - 1), (f32)i, (f32)(t->keys[i] - t->keys[i - 1]), x - (f32)t->keys[i - 1]);
}
static inline Vec MkVec(f32 x, f32 y) { Vec r = { 0.0f, 0.0f, 0.0f }; r.x = x; r.y = y; return r; }

static inline f32 Ease(f32 x, f32 b, f32 a) { return fn_8001EBC8(2, a, b, b - a, x); }
static inline Vec MkVec2(f32 y, f32 x) { Vec r = { 0.0f, 0.0f, 0.0f }; r.x = x; r.y = y; return r; }
void fn_801805E0(Track2* t) {
    int i, j;
    Vec* out;
    Vec* p;
    Vec* p1;
    Vec* n;
    f32 f;
    t->unkA = 0;
    if (t->unk6 > 0) {
        t->unk6++;
        if (t->unk6 == 0x1e) {
            Reset(t);
        }
    }
    if (t->count < 2) return;
    if (t->unk14 >= t->unk18) return;
    t->unk1C += 1.0f;
    if (t->unk1C > t->unk18 - t->unk14) t->unk1C = t->unk18 - t->unk14;
    t->unk10 = Ease(t->unk1C, t->unk18, t->unk14);
    if (t->unk10 > t->unk18) t->unk10 = t->unk18;
    t->unkC = KeyPos(t, t->unk10);
    t->pts[0].x = t->vals[0].x;
    t->pts[0].y = t->vals[0].y;
    t->pts[0].z = t->vals[0].z;
    p1 = t->vals;
    out = &t->pts[1];
    for (i = 0; i < t->count - 1; p1++, i++) {
        Vec* p0;
        Vec* p2;
        Vec* p3;
        if (i == 0) p0 = &t->vals[0]; else p0 = &t->vals[i - 1];
        p2 = &t->vals[i + 1];
        if (i == t->count - 2) p3 = &t->vals[t->count - 1]; else p3 = &t->vals[i + 2];
        for (j = 1; j <= 0x10; j++) {
            f32 s = (f32)j * 0.0625f;
            out->x = fn_8001EFE4(p0->x, p1->x, p2->x, p3->x, s);
            out->y = fn_8001EFE4(p0->y, p1->y, p2->y, p3->y, s);
            out->z = fn_8001EFE4(p0->z, p1->z, p2->z, p3->z, s);
            out++;
        }
    }
    out->x = out[-1].x + (out[-1].x - out[-2].x);
    out->y = out[-1].y + (out[-1].y - out[-2].y);
    out->z = out[-1].z + (out[-1].z - out[-2].z);
    t->unkA = ((t->count - 1) << 4) + 1;
    p = t->pts;
    n = t->nrm;
    for (i = 0; i < t->unkA; i++) {
        f32 dy = p[1].y - p[0].y;
        f32 dx = p[1].x - p[0].x;
        Vec a = MkVec(-dy, dx);
        fn_803134C4(&a, &a);
        if (i > 0) {
            f32 ey = p[-1].y - p[0].y;
            f32 ex = p[-1].x - p[0].x;
            Vec b = MkVec(ey, -ex);
            fn_803134C4(&b, &b);
            a.x = (a.x + b.x) * 0.5f;
            a.y = (a.y + b.y) * 0.5f;
        }
        n->x = a.x;
        n->y = a.y;
        n->z = a.z;
        p++;
        n++;
    }
    f = 1.0f + fn_8001EF30(0.0f, (f32)(t->unkA - 1), (f32)(t->count - 1), t->unkC);
    if ((f32)t->unkA > f) {
        if (0.0f == f - (f32)(int)f) {
            t->unkA = (int)f;
        } else {
            f32 fr;
            Vec* a;
            Vec* b;
            t->unkA = (int)f + 1;
            fr = f - (f32)(int)f;
            a = &t->pts[t->unkA - 2];
            b = &t->pts[t->unkA - 1];
            b->x = fn_8001EF30(a->x, b->x, 1.0f, fr);
            b->y = fn_8001EF30(a->y, b->y, 1.0f, fr);
            b->z = fn_8001EF30(a->z, b->z, 1.0f, fr);
            a = &t->nrm[t->unkA - 2];
            b = &t->nrm[t->unkA - 1];
            b->x = fn_8001EF30(a->x, b->x, 1.0f, fr);
            b->y = fn_8001EF30(a->y, b->y, 1.0f, fr);
            b->z = fn_8001EF30(a->z, b->z, 1.0f, fr);
        }
    }
    if (t->unk4 != 0) {
        if (t->unk10 >= t->unk18) return;
        fn_800620A8(lbl_803CAB38, t->pts[t->unkA - 1].x, t->pts[t->unkA - 1].y);
    }
}
