/* fn_8001B284: 12 words differ, registers only (the parameter a must be r27, the child walker r20, the alpha walker r23). The earlier 0.5f in the size rounding was wrong: the constant at 804CCBC0 is 0.1f. sPad and rodata_dummy keep the anonymous rodata templates at the right offsets. */
#include "game/rA_800068A0/types.h"
extern "C" {
typedef f32 Mtx[3][4];
typedef struct Vec { f32 x, y, z; } Vec;
typedef struct GNd { u8 x0[4]; struct GNd* next; struct GNd* child; u32 flags; Mtx m; u8 x40[0x7C - 0x40]; Vec pivot; u8 x88[0xEC - 0x88]; u32 idx : 12; } GNd;
typedef struct GPrim { u8 x0[0x10]; u32 x10; u8 x14[0x1C - 0x14]; u8* pal; } GPrim;
typedef struct GMd { u8 x0[8]; int count; } GMd;
extern char lbl_80360EEC[];
static const u32 sPad[17] = {0x3BA3D70A, 0x3BA3D70A, 0x3BA3D70A, 0, 0, 0x3F800000, 0xD, 0xE, 0xF, 0x10, 0x11, 0x12, 0x13, 0x14, 0, 0xBF800000, 0};
extern void fn_8001E008(const char* file, int line, const char* msg);
extern void* fn_8000FB88(void);
extern GNd* fn_8000F3D4(GMd* m, s32 idx);
extern void fn_80312344(const void* a, void* b);
extern void fn_80312378(const void* a, const void* b, void* c);
extern void fn_80312444(const void* a, void* b);
extern int fn_80312494(const void* a, void* b);
extern void fn_8031258C(const void* a, void* b);
extern void fn_803128AC(void* m, f32 x, f32 y, f32 z);
extern void fn_8031292C(void* m, f32 x, f32 y, f32 z);
extern void fn_80312954(const void* a, void* b, f32 x, f32 y, f32 z);
extern void fn_80312DB4(const void* a, const Vec* b, Vec* c);
extern void fn_8001E70C(const void* a, void* b);
extern void fn_8001E694(const void* a, void* b);
extern void fn_8001E638(const void* a, void* b);
extern void fn_8001E6D0(const void* a, void* b);
extern void fn_8001E8E8(const void* a, void* b);
extern void fn_80018E48(const void* a, void* b, f32 t);
extern void fn_8000FBA0(void* c, void* m);
extern void fn_8000FD20(void* c, void* m);
extern u16* fn_8000F470(void);
extern void fn_80307E48(const void* m, int id);
extern void fn_80307E98(const void* m, int id);
extern void fn_800217C0(void);

extern f32 fn_800081B4(u32* a);
extern void fn_8000E510(f32 t, u32* a, GNd* n, int k, void* m, void* m2);
extern f32 fn_80313508(const Vec* v);
extern void fn_8001BD34(f32 w, GNd* n, void* m, Vec* pos, f32* sz, u8* al, int cnt, int mode);
extern void fn_8001D44C(const void* a, void* b);
extern void fn_80312318(void* m);
extern Mtx* fn_800080B8(u32* a);
extern void fn_80021784(int);
extern void fn_80312344(const void* a, void* b);
typedef struct W3 { u32 x, y, z; } W3;
#define SETK(t, k) *(W3*)&t = *(W3*)&k; v = t
#define SETZ(t) ((u32*)&t)[0] = 0; ((u32*)&t)[1] = 0; ((u32*)&t)[2] = 0; v = t
void rodata_dummy(void) { fn_80021784(sPad[0]); }
static inline void h40000(GNd* nd, Mtx view, Mtx mb0, Mtx mid, Mtx world, Mtx m670, Mtx m6a0, Mtx m6d0, Mtx m700) {
    Vec v838;
        v838 = nd->pivot;
        fn_8001E70C(view, m700);
        fn_80312444(fn_8000FB88(), m670);
        fn_80312378(m670, m700, m700);
        fn_80312378(view, mb0, m670);
        fn_80312DB4(m670, &v838, &v838);
        fn_803128AC(m6a0, -v838.x, -v838.y, -v838.z);
        fn_803128AC(m6d0, v838.x, v838.y, v838.z);
        if (nd->flags & 0x200000) {
            fn_80018E48(m700, m700, 0.5f);
        }
        fn_80312378(m6a0, m670, m670);
        fn_80312378(m700, m670, m670);
        fn_80312378(m6d0, m670, m670);
        fn_80312378(mid, m670, world);
}
static inline void h4(GNd* nd, Mtx view, Mtx mb0, Mtx mid, Mtx world, Mtx m670, Mtx m6a0, Mtx m6d0, Mtx m700) {
    h40000(nd, view, mb0, mid, world, m670, m6a0, m6d0, m700);
}
static inline void h80000(GNd* nd, Mtx view, Mtx mb0, Mtx mid, Mtx world, Mtx m550, Mtx m580, Mtx m5b0, Mtx m5e0, Mtx m610, Mtx m640) {
    Vec v82c;
        v82c = nd->pivot;
        fn_80312DB4(mb0, &v82c, &v82c);
        fn_803128AC(m610, -v82c.x, -v82c.y, -v82c.z);
        fn_803128AC(m640, v82c.x, v82c.y, v82c.z);
        fn_8001E694(mb0, m5e0);
        fn_8001E638(mb0, m5b0);
        fn_8001E8E8(view, m580);
        fn_80312378(m5e0, m5b0, m550);
        fn_80312378(m610, m550, m550);
        fn_80312378(m580, m550, m550);
        fn_80312378(m640, m550, m550);
        fn_80312378(view, m550, m550);
        fn_80312378(mid, m550, world);
}
void fn_8001B284(u32* aa, GNd* nd) {
    u32* a = aa;
    Vec* pp2;
    u8* pa2;
    GNd* c;
    f32* ps2;
    GNd* c2;
    int i2;
    int i;
    u8* pa;
    Mtx* bones;
    int n2;
    Vec* pp;
    f32* ps;
    int mode;
    int cnt;
    f32 tm;
    Vec vpos[32];
    f32 size[32];
    Mtx view;
    Mtx world;
    Mtx rot;
    Mtx mb0;
    Mtx mid;
    Mtx mt2;
    Mtx m3d0;
    Mtx m400;
    Mtx m430;
    Mtx m460;
    Mtx m490;
    Mtx m4c0;
    Mtx m4f0;
    Mtx m520;
    Mtx m550;
    Mtx m580;
    Mtx m5b0;
    Mtx m5e0;
    Mtx m610;
    Mtx m640;
    Mtx m670;
    Mtx m6a0;
    Mtx m6d0;
    Mtx m700;
    Mtx m730;
    Mtx m760;
    Mtx m790;
    u8 alpha[32];
    Vec v;
    mode = 4;
    bones = fn_800080B8(a);
    fn_8001D44C(a + 3, view);
    fn_80312318(mb0);
    fn_80312318(mid);
    switch (nd->flags & 0x1F0000) {
    case 0x40000:
        h4(nd, view, mb0, mid, world, m670, m6a0, m6d0, m700);
        break;
    case 0x80000:
        h80000(nd, view, mb0, mid, world, m550, m580, m5b0, m5e0, m610, m640);
        break;
    case 0xC0000:
        fn_8001E694(view, m520);
        fn_8001E638(view, m4f0);
        fn_80312444(fn_8000FB88(), m4c0);
        fn_80312378(m4f0, mb0, m490);
        fn_80312378(m4c0, m490, m490);
        fn_80312378(m520, m490, m490);
        fn_80312378(mid, m490, world);
        break;
    case 0x100000:
        fn_8001E8E8(view, m460);
        fn_80312378(m460, mb0, m430);
        fn_80312378(view, m430, m430);
        fn_80312378(mid, m430, world);
        break;
    case 0x10000:
        fn_8000FBA0(0, m400);
        fn_80312378(m400, mb0, m400);
        fn_80312378(mid, m400, world);
        break;
    case 0x20000:
        fn_8000FD20(0, m3d0);
        fn_80312378(m3d0, mb0, m3d0);
        fn_80312378(mid, m3d0, world);
        break;
    default:
        fn_80312378(view, mb0, m790);
        fn_80312378(mid, m790, world);
        break;
    }
    if ((*a & 0x200000) && (*fn_8000F470() & 4)) {
        fn_8001E694(world, m730);
        fn_8001E6D0(world, world);
        fn_8031292C(m760, 0.75000006f, 1.0f, 1.0f);
        fn_80312378(m760, world, world);
        fn_80312378(m730, world, world);
    }
    fn_80312344(fn_8000FB88(), mid);
    fn_80307E48(mid, 0);
    fn_80021784(0);
    fn_8031258C(mid, mid);
    fn_80307E98(mid, 0);
    cnt = 0;
    for (c = nd->child; c != 0; c = c->next) {
        cnt++;
    }
    if (cnt == 0) {
        return;
    }
    fn_8001E638(world, rot);
    if (cnt == 1) {
        c = nd->child;
        tm = fn_800081B4(a);
        fn_8000E510(tm, a, c, 0, mb0, 0);
        fn_8001E6D0(mb0, view);
        Vec t0 = {0.0f, 1.0f, 0.0f};
        v = t0;
        fn_80312DB4(view, &v, &v);
        cnt = fn_80313508(&v) + 0.1f;
        if (cnt == 0) {
            return;
        }
        Vec t1 = {0.0f, 0.0f, 1.0f};
        v = t1;
        fn_80312DB4(view, &v, &v);
        n2 = fn_80313508(&v) + 0.1f;
        if (n2 == 0) {
            return;
        }
        pp = vpos;
        ps = size;
        pa = alpha;
        for (i = 0; i < cnt; pp++, ps++, pa++, i++) {
            fn_8000E510(tm, a, c, 0, mb0, mt2);
        Vec t2 = {0.0f, 0.0f, 0.0f};
        v = t2;
            fn_80312378(world, mt2, view);
            fn_80312DB4(view, &v, pp);
        Vec t3 = {1.0f, 0.0f, 0.0f};
        v = t3;
            fn_8001E6D0(mb0, view);
            fn_80312378(rot, view, view);
            fn_80312DB4(view, &v, &v);
            *ps = fn_80313508(&v);
            *pa = 0xFF;
            tm -= (f32)n2;
            if (tm < 0.0f) {
                tm = 0.0f;
            }
        }
    } else {
        pp2 = vpos;
        pa2 = alpha;
        ps2 = size;
        c2 = nd->child;
        for (i2 = 0; i2 < cnt; c2 = c2->next, pp2++, pa2++, ps2++, i2++) {
            fn_80312344(bones[c2->idx], mb0);
            fn_80312378(world, mb0, view);
        Vec t4 = {0.0f, 0.0f, 0.0f};
        v = t4;
            fn_80312DB4(view, &v, pp2);
            fn_8001E6D0(mb0, view);
        Vec t5 = {0.0f, 1.0f, 0.0f};
        v = t5;
            fn_80312DB4(view, &v, &v);
            *pa2 = (int)(255.0f * fn_80313508(&v));
            fn_80312378(rot, view, view);
        Vec t6 = {1.0f, 0.0f, 0.0f};
        v = t6;
            fn_80312DB4(view, &v, &v);
            *ps2 = fn_80313508(&v);
        Vec t7 = {0.0f, 0.0f, 1.0f};
        v = t7;
            fn_8001E6D0(mb0, view);
            fn_80312DB4(view, &v, &v);
            if (0.0f == fn_80313508(&v)) {
                mode = 0;
            }
        }
    }
    fn_8001BD34(0.0f, nd, world, vpos, size, alpha, cnt, mode);
}
}
