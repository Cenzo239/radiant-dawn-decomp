/* fn_80019504: MATCH. The volatile casts on the last two stores are not likely to be in the original. */
#include "game/rA_800068A0/types.h"
extern "C" {
typedef f32 Mtx[3][4];
typedef struct Vec { f32 x, y, z; } Vec;
typedef struct GNd { u8 x0[0xC]; u32 flags; Mtx m; u8 x40[0x7C - 0x40]; Vec pivot; } GNd;
typedef struct GPrim { u8 x0[4]; struct GPrim* next; u16 x8; s16 x0A; s16 node; s16 xE; u32 x10; u8 x14[0x1C - 0x14]; u8* pal; } GPrim;
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
extern void fn_80312318(void* m);
extern void fn_80307E48(const void* m, int id);
extern void fn_80307E98(const void* m, int id);
extern void fn_800217C0(void);
void fn_80019504(u32* a, GPrim* p, GMd* md, const Mtx view, const Mtx* bones) {

    s16* q;
    s16* o;
    int j;
    s16 idx;
    int n;
    void* vp;
    GNd* nd;

    Mtx out;
    Mtx mb0;
    Mtx mb1;
    Mtx m110;
    Mtx m140;
    Mtx m170;
    Mtx m1a0;
    Mtx m1d0;
    Mtx m200;
    Mtx m230;
    Mtx m260;
    Mtx m290;
    Mtx m2c0;
    Mtx m2f0;
    Mtx m320;
    Mtx m350;
    Mtx m380;
    Mtx m3b0;
    Mtx m3e0;
    Mtx m410;
    Mtx m440;
    Mtx m470;
    Mtx m4a0;
    Mtx m4d0;
    s16 seen[10];
    Vec v4e0;
    Vec v4ec;
    vp = fn_8000FB88();
    seen[0] = -1;
    seen[1] = -1;
    seen[2] = -1;
    seen[3] = -1;
    seen[4] = -1;
    seen[5] = -1;
    seen[6] = -1;
    seen[7] = -1;
    seen[8] = -1;
    seen[9] = -1;
    n = 0;
    for (; p != 0 && n < 10; p = p->next) {
        if (p->x10 & 1) {
            break;
        }
        q = seen;
        idx = p->node;
        for (j = 0; j < n; q++, j++) {
            if (idx == *q) {
                p->xE = lbl_803788A8[j];
                goto next;
            }
        }
        nd = fn_8000F3D4(md, idx);
        if (p->x8 & 1) {
            fn_80312318(mb0);
        } else {
            fn_80312344(bones[p->node], mb0);
        }
        switch (nd->flags & 0x1F0000) {
        case 0x40000:
            v4ec = nd->pivot;
            fn_8001E70C(view, m410);
            fn_80312444(fn_8000FB88(), m380);
            fn_80312378(m380, m410, m410);
            fn_80312378(view, mb0, m380);
            fn_80312DB4(m380, &v4ec, &v4ec);
            fn_803128AC(m3b0, -v4ec.x, -v4ec.y, -v4ec.z);
            fn_803128AC(m3e0, v4ec.x, v4ec.y, v4ec.z);
            if (nd->flags & 0x200000) {
                fn_80018E48(m410, m410, 0.5f);
            }
            fn_80312378(m3b0, m380, m380);
            fn_80312378(m410, m380, m380);
            fn_80312378(m3e0, m380, m380);
            fn_80312378(vp, m380, out);
            break;
        case 0x80000:
            v4e0 = nd->pivot;
            fn_80312DB4(mb0, &v4e0, &v4e0);
            fn_803128AC(m320, -v4e0.x, -v4e0.y, -v4e0.z);
            fn_803128AC(m350, v4e0.x, v4e0.y, v4e0.z);
            fn_8001E694(mb0, m2f0);
            fn_8001E638(mb0, m2c0);
            fn_8001E8E8(view, m290);
            fn_80312378(m2f0, m2c0, m260);
            fn_80312378(m320, m260, m260);
            fn_80312378(m290, m260, m260);
            fn_80312378(m350, m260, m260);
            fn_80312378(view, m260, m260);
            fn_80312378(vp, m260, out);
            break;
        case 0xC0000:
            fn_8001E694(view, m230);
            fn_8001E638(view, m200);
            fn_80312444(fn_8000FB88(), m1d0);
            fn_80312378(m200, mb0, m1a0);
            fn_80312378(m1d0, m1a0, m1a0);
            fn_80312378(m230, m1a0, m1a0);
            fn_80312378(vp, m1a0, out);
            break;
        case 0x100000:
            fn_8001E8E8(view, m170);
            fn_80312378(m170, mb0, m140);
            fn_80312378(view, m140, m140);
            fn_80312378(vp, m140, out);
            break;
        case 0x10000:
            fn_8000FBA0(0, m110);
            fn_80312378(m110, mb0, m110);
            fn_80312378(vp, m110, out);
            break;
        case 0x20000:
            fn_8000FD20(0, mb1);
            fn_80312378(mb1, mb0, mb1);
            fn_80312378(vp, mb1, out);
            break;
        default:
            fn_80312378(view, mb0, m4a0);
            fn_80312378(vp, m4a0, out);
            break;
        }
        if ((*a & 0x200000) && (*fn_8000F470() & 4)) {
            fn_8001E694(out, m440);
            fn_8001E6D0(out, out);
            fn_8031292C(m470, 0.75000006f, 1.0f, 1.0f);
            fn_80312378(m470, out, out);
            fn_80312378(m440, out, out);
        }
        fn_80307E48(out, lbl_803788A8[n]);
        fn_8031258C(out, out);
        if (p->x10 & 0x800) {
            Vec v4f8 = lbl_80360E30;
            fn_8001E638(out, m4d0);
            if (fn_80312494(m4d0, m4d0)) {
                fn_80312DB4(m4d0, &v4f8, &v4f8);
            }
            fn_80312954(out, out, v4f8.x, v4f8.y, v4f8.z);
        }
        fn_80307E98(out, lbl_803788A8[n]);
/* The volatile casts only pin the store order. The original got sth before sthx some other way. */
        *(volatile s16*)&p->xE = lbl_803788A8[n];
        *(volatile s16*)&seen[n++] = idx;
    next:;
    }
}
}
