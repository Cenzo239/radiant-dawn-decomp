#include "game/rA_800068A0/types.h"
extern "C" {
typedef f32 Mtx[3][4];
typedef struct Vec { f32 x, y, z; } Vec;
typedef struct GNd { u8 x0[0xC]; u32 flags; Mtx m; u8 x40[0x7C - 0x40]; Vec pivot; } GNd;
typedef struct GPrim { u8 x0[8]; u16 x8; s16 xA; s16 node; } GPrim;
typedef struct GMd { u8 x0[8]; int count; } GMd;
extern char lbl_80360EEC[];
extern Vec lbl_80360E30;
extern s16 lbl_803788A8[];
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
typedef struct GActorH { u32 flags; u8 x4[8]; Mtx m; } GActorH;
extern GActorH* lbl_804CB0A0;
extern GPrim* lbl_804CB0A4;
extern void fn_80312318(void* m);
extern GNd* fn_800078E4(GActorH* a, s32 idx);
extern Mtx* fn_800080B8(GActorH* a);
extern void fn_8001D44C(const void* a, void* b);
void fn_80019D9C(void* out) {
    if (lbl_804CB0A4->x8 & 3) {
        fn_8001D44C(lbl_804CB0A0->m, out);
    } else {

    GNd* nd;
    Mtx* bones;
    GActorH* a;

    Mtx mb0;
    Mtx view;
    Mtx vp;
    Mtx mb1;
    Mtx m100;
    Mtx m130;
    Mtx m160;
    Mtx m190;
    Mtx m1c0;
    Mtx m1f0;
    Mtx m220;
    Mtx m250;
    Mtx m280;
    Mtx m2b0;
    Mtx m2e0;
    Mtx m310;
    Mtx m340;
    Mtx m370;
    Mtx m3a0;
    Mtx m3d0;
    Mtx m400;
    Mtx m430;
    Mtx m460;
    Mtx m490;
    Vec v49c;
    Vec v4a8;
    nd = fn_800078E4(lbl_804CB0A0, lbl_804CB0A4->node);
    bones = fn_800080B8(lbl_804CB0A0);
    fn_8001D44C(lbl_804CB0A0->m, view);
    fn_80312344(bones[lbl_804CB0A4->node], mb0);
    fn_80312318(vp);
    a = lbl_804CB0A0;
    switch (nd->flags & 0x1F0000) {
    case 0x40000:
        v4a8 = nd->pivot;
        fn_8001E70C(view, m400);
        fn_80312444(fn_8000FB88(), m370);
        fn_80312378(m370, m400, m400);
        fn_80312378(view, mb0, m370);
        fn_80312DB4(m370, &v4a8, &v4a8);
        fn_803128AC(m3a0, -v4a8.x, -v4a8.y, -v4a8.z);
        fn_803128AC(m3d0, v4a8.x, v4a8.y, v4a8.z);
        if (nd->flags & 0x200000) {
            fn_80018E48(m400, m400, 0.5f);
        }
        fn_80312378(m3a0, m370, m370);
        fn_80312378(m400, m370, m370);
        fn_80312378(m3d0, m370, m370);
        fn_80312378(vp, m370, out);
        break;
    case 0x80000:
        v49c = nd->pivot;
        fn_80312DB4(mb0, &v49c, &v49c);
        fn_803128AC(m310, -v49c.x, -v49c.y, -v49c.z);
        fn_803128AC(m340, v49c.x, v49c.y, v49c.z);
        fn_8001E694(mb0, m2e0);
        fn_8001E638(mb0, m2b0);
        fn_8001E8E8(view, m280);
        fn_80312378(m2e0, m2b0, m250);
        fn_80312378(m310, m250, m250);
        fn_80312378(m280, m250, m250);
        fn_80312378(m340, m250, m250);
        fn_80312378(view, m250, m250);
        fn_80312378(vp, m250, out);
        break;
    case 0xC0000:
        fn_8001E694(view, m220);
        fn_8001E638(view, m1f0);
        fn_80312444(fn_8000FB88(), m1c0);
        fn_80312378(m1f0, mb0, m190);
        fn_80312378(m1c0, m190, m190);
        fn_80312378(m220, m190, m190);
        fn_80312378(vp, m190, out);
        break;
    case 0x100000:
        fn_8001E8E8(view, m160);
        fn_80312378(m160, mb0, m130);
        fn_80312378(view, m130, m130);
        fn_80312378(vp, m130, out);
        break;
    case 0x10000:
        fn_8000FBA0(0, m100);
        fn_80312378(m100, mb0, m100);
        fn_80312378(vp, m100, out);
        break;
    case 0x20000:
        fn_8000FD20(0, mb1);
        fn_80312378(mb1, mb0, mb1);
        fn_80312378(vp, mb1, out);
        break;
    default:
        fn_80312378(view, mb0, m490);
        fn_80312378(vp, m490, out);
        break;
    }
    if ((a->flags & 0x200000) && (*fn_8000F470() & 4)) {
        fn_8001E694(out, m430);
        fn_8001E6D0(out, out);
        fn_8031292C(m460, 0.75000006f, 1.0f, 1.0f);
        fn_80312378(m460, out, out);
        fn_80312378(m430, out, out);
    }
    }
}
}
