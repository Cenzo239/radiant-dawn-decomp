/*
 * fn_800F98E4 (round 22 draft, `other`: size 0x99C, want 0x980; 530 of 608 words differ, mostly
 * frame offsets and scheduling). Draws a unit's ground shadow (blob) with fn_800F280C.
 *   m: the map unit; a, b: joint indices of its model (both >= 0: the shadow is stretched and rotated
 *   between the two joints, e.g. for long monsters); alphaMul: 0..255 fade.
 * Shadow size: height above the ground d = clamp(-(z - fn_801142F0(map, x, y)), .., 5);
 * scale = fn_8001EF30(1.0, 0.1, 5.0, d) (falls off with height); size = 1e-4 * 4 * scale * 0.06 *
 * (m->unkC6 * lbl_804CA4AC). Nothing is drawn when size is 0.
 * Two-joint case: midpoint of the joints, half-extent vector (w, h) from the first joint; if it is not
 * zero, its angle against +X (acos of the dot product of the normalised, 1000x-quantised vector with
 * {1,0,0}, negated when h < 0) rotates the quad and (w, h) is rotated back and padded by 0.2. Extents
 * times scale, at least `size`. Debug flag 0x100 (fn_8017DA30) draws two 0.2 markers at the joints
 * instead of the shadow (and returns).
 * One-point case: model translation (fn_8001E9E4, z - 0.5) when flag 2 is set and unkC8 < 0, else
 * joint unkC8, else position + offset (fn_80313460) with z - 0.5. The quad is +-size.
 *
 * What differs: the original's camera constants ({0,0,-1} eye direction, {1,0,0}, four {0,1,0} up
 * vectors) are at lbl_80367A58 + 0x48, + 0xD8, + 0xE4, + 0xF0, + 0xFC, + 0x108 in the file's pooled
 * .rodata (0x14C bytes shared with the other draw functions of the file: dummy.tpl name, colour
 * tables, a pointer table into .sdata2). Here they are aggregate initialisers, so the compiler pools
 * them from offset 0 of this file's own pool; reproducing the offsets needs the other functions'
 * constants in the same file. The frame is 0x10 bytes larger (temporary placement) and the schedule
 * differs. Draw calls, arguments and constants were checked by hand against the asm, block by block.
 * The colours {255,255,255,alpha} come out as the 3-byte .sdata2 objects lbl_804CDB0C / lbl_804CDB10.
 */
#include "game/rE_800E5DE4/mapunit.h"
#pragma auto_inline off
typedef f32 Mtx34[3][4];
extern "C" {
extern u8 lbl_803EC898[];
extern u8 lbl_804CA4AC;
extern Vec fn_800076E8(void* actor, s32 idx);
extern void fn_8001E9E4(const f32 (*m)[4], Vec* v);
extern f32 fn_8001EF30(f32, f32, f32, f32);
extern void fn_80021F7C(int, int, int, int);
extern void fn_800F280C(GXColor col, int p, f32 x, f32 y);
extern f32 fn_801142F0(void* map, f32 x, f32 y);
extern u64 fn_8017DA30(u64 mask);
extern double fn_80295A90(double x);
extern void fn_80307F10(f32*, int, int);
extern void fn_80312378(f32*, f32*, f32*);
extern void fn_80312654(f32*, int, f32);
extern void fn_803128AC(f32*, f32, f32, f32);
extern void fn_80312AC0(f32*, const Vec*, const Vec*, const Vec*);
extern void fn_80312D2C(f32*, f32, f32, f32, f32, f32, f32, f32, f32);
extern void fn_80312DB4(f32*, const Vec*, Vec*);
extern void fn_80313460(const Vec*, const Vec*, Vec*);
extern void fn_803134C4(const Vec*, Vec*);
extern f32 fn_8031354C(const Vec*, const Vec*);

static inline Vec Eye(f32 x, f32 y)
{
    Vec v = {0.0f, 0.0f, -1.0f};
    v.x = x;
    v.y = y;
    return v;
}

static inline Vec Target(f32 x, f32 y)
{
    Vec v = {0.0f, 0.0f, 0.0f};
    v.x = x;
    v.y = y;
    return v;
}

static inline Vec XY0(f32 x, f32 y)
{
    Vec v = {0.0f, 0.0f, 0.0f};
    v.x = x;
    v.y = y;
    return v;
}

void fn_800F98E4(MapUnit* m, int a, int b, int alphaMul)
{
    Mtx34 mv;
    Mtx34 tmp;
    Mtx34 rot;
    Mtx34 look;
    Mtx34 proj;
    Mtx34 look1;
    Mtx34 proj1;
    Mtx34 look2;
    Mtx34 proj2;
    Mtx34 look3;
    Mtx34 proj3;
    Vec p0;
    Vec p1;
    Vec pos;
    f32 x = m->x;
    f32 y = m->y;
    f32 z = m->z;
    void* actor = m->model;
    int alpha = (alphaMul * m->unk33) / 255;
    f32 d = -(z - fn_801142F0(lbl_803EC898, x, y));
    f32 scale;
    f32 size;
    f32 w, h;
    f32 ang;
    if (d > 5.0f) {
        d = 5.0f;
    }
    scale = fn_8001EF30(1.0f, 0.1f, 5.0f, d);
    size = 0.0001f * (4.0f * (scale * (0.06f * (f32)(m->unkC6 * lbl_804CA4AC))));
    if (0.0f == size) {
        return;
    }
    if (a >= 0 && b >= 0) {
        p0 = fn_800076E8(actor, a);
        p1 = fn_800076E8(actor, b);
        x = (p0.x + p1.x) * 0.5f;
        y = (p0.y + p1.y) * 0.5f;
        ang = 0.0f;
        w = x - p0.x;
        h = y - p0.y;
        if (0.0f != w || 0.0f != h) {
            Vec dir = XY0((int)(1000.0f * w), (int)(1000.0f * h));
            Vec ref = {1.0f, 0.0f, 0.0f};
            f32 c;
            f32 r;
            fn_803134C4(&dir, &dir);
            c = fn_8031354C(&ref, &dir);
            if (c > 1.0f) {
                c = 1.0f;
            }
            if (c < -1.0f) {
                c = -1.0f;
            }
            r = fn_80295A90(c);
            if (h < 0.0f) {
                r *= -1.0f;
            }
            dir = XY0(w, h);
            fn_80312654(&mv[0][0], 'z', -r);
            fn_80312DB4(&mv[0][0], &dir, &dir);
            ang = 57.29578f * r;
            w = 0.2f + dir.x;
            h = 0.2f + dir.y;
        }
        w *= scale;
        h *= scale;
        if (w < size) {
            w = size;
        }
        if (h < size) {
            h = size;
        }
        {
            Vec tgt = Target(x, y);
            Vec eye = Eye(x, y);
            Vec up = {0.0f, 1.0f, 0.0f};
            if (0.0f != ang) {
                fn_80312654(&rot[0][0], 'Z', 0.017453292f * ang);
                fn_80312DB4(&rot[0][0], &up, &up);
                fn_80312AC0(&look[0][0], &eye, &up, &tgt);
                fn_80312D2C(&proj[0][0], -h, h, -w, w, 0.5f, 0.5f, 0.5f, 0.5f);
                fn_80312378(&proj[0][0], &look[0][0], &mv[0][0]);
                fn_803128AC(&tmp[0][0], -0.5f, -0.5f, 0.0f);
                fn_80312378(&rot[0][0], &tmp[0][0], &rot[0][0]);
                fn_803128AC(&tmp[0][0], 0.5f, 0.5f, 0.0f);
                fn_80312378(&tmp[0][0], &rot[0][0], &rot[0][0]);
                fn_80312378(&rot[0][0], &mv[0][0], &mv[0][0]);
            } else {
                fn_80312AC0(&look[0][0], &eye, &up, &tgt);
                fn_80312D2C(&proj[0][0], -h, h, -w, w, 0.5f, 0.5f, 0.5f, 0.5f);
                fn_80312378(&proj[0][0], &look[0][0], &mv[0][0]);
            }
        }
        if (fn_8017DA30(0x100)) {
            /* debug: also mark both end points */
            GXColor c = {0xff, 0xff, 0xff, alpha};
            {
                Vec tgt = Target(p0.x, p0.y);
                Vec eye = Eye(p0.x, p0.y);
                Vec up = {0.0f, 1.0f, 0.0f};
                fn_80312AC0(&look1[0][0], &eye, &up, &tgt);
                fn_80312D2C(&proj1[0][0], -0.2f, 0.2f, -0.2f, 0.2f, 0.5f, 0.5f, 0.5f, 0.5f);
                fn_80312378(&proj1[0][0], &look1[0][0], &mv[0][0]);
                fn_80307F10(&mv[0][0], 0x1E, 0);
                fn_80021F7C(0, 0, 0, 0x1E);
                fn_800F280C(c, 1, x, y);
            }
            {
                Vec tgt = Target(p1.x, p1.y);
                Vec eye = Eye(p1.x, p1.y);
                Vec up = {0.0f, 1.0f, 0.0f};
                fn_80312AC0(&look2[0][0], &eye, &up, &tgt);
                fn_80312D2C(&proj2[0][0], -0.2f, 0.2f, -0.2f, 0.2f, 0.5f, 0.5f, 0.5f, 0.5f);
                fn_80312378(&proj2[0][0], &look2[0][0], &mv[0][0]);
                fn_80307F10(&mv[0][0], 0x1E, 0);
                fn_80021F7C(0, 0, 0, 0x1E);
                fn_800F280C(c, 1, x, y);
            }
            return;
        }
    } else {
        if (m->flags & 2) {
            if (m->unkC8 < 0) {
                fn_8001E9E4((const f32 (*)[4])(m->model + 0x10), &pos);
                pos.z -= 0.5f;
            } else {
                pos = fn_800076E8(m->model, m->unkC8);
            }
        } else {
            Vec at = *(Vec*)&m->x;
            Vec off = *(Vec*)&m->offX;
            pos.x = at.x;
            pos.y = at.y;
            pos.z = at.z - 0.5f;
            fn_80313460(&pos, &off, &pos);
        }
        {
            Vec p = pos;
            Vec tgt = Target(p.x, p.y);
            Vec eye = Eye(p.x, p.y);
            Vec up = {0.0f, 1.0f, 0.0f};
            fn_80312AC0(&look3[0][0], &eye, &up, &tgt);
            fn_80312D2C(&proj3[0][0], -size, size, -size, size, 0.5f, 0.5f, 0.5f, 0.5f);
            fn_80312378(&proj3[0][0], &look3[0][0], &mv[0][0]);
        }
    }
    fn_80307F10(&mv[0][0], 0x1E, 0);
    fn_80021F7C(0, 0, 0, 0x1E);
    {
        GXColor c = {0xff, 0xff, 0xff, alpha};
        fn_800F280C(c, 1, x, y);
    }
}
}
