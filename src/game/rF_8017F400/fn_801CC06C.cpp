#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
/* map object init from the map stream */
typedef struct MDef { u8 pad[0xB8]; u32 fl; } MDef;
typedef struct MH { u32 fl; void* x4; u8 pad[0x54]; f32 x5C; u8 pad60[0xC8 - 0x74]; } MH;
typedef struct MObj {
    u8 x0; s8 x1, x2; u8 x3; s8 x4, x5, x6, x7;
    s16 x8; s16 xA; f32 xC; MDef* def;
    MH h;
    u32 xC8; u8 xCC, xCD; s8 xCE, xCF;
} MObj;
typedef struct MMap { u8 pad[8]; u8* defs; u8 padC[0xB1 - 0xC]; u8 xB1; } MMap;
extern MMap* fn_8013B9A8(void);
extern void fn_80006E94(void*);
extern u8 fn_80109A18(void*);
extern u16 fn_80109A2C(void*);
extern f32 fn_80109AD0(void*);
extern void fn_80006F20(void*);
extern void* fn_80007F3C(void*);
extern void fn_80008F54(void*, int);
#if TARGET_PC
extern FE10_PROTO struct GEntry20 * fn_80008110(void*, const char*);
#else
extern int fn_80008110(void*, const char*);
#endif
extern int fn_80014D40(void*, const char*, int);
extern int fn_80014DE4(void*, int);
extern u8* fn_80007F10(void*);
extern int fn_80009D60(void*, int, void*);
extern u32 fn_80089ED0(void);
extern void fn_8000866C(void*, f32);
extern void fn_80007C58(void*);
extern int fn_800A05B0(int, int, int);
extern void fn_80008F5C(void*, int);
extern int fn_8000A168(void*, int, u16*);
extern char lbl_8036E9AC[];


typedef struct Vc { f32 x, y, z; } Vc;
typedef struct C4 { u8 r, g, b, a; } C4;
extern void fn_80006A64(void*, void*, int);
extern void fn_80022254(void*, int);
extern void fn_80021B68(int);
extern void fn_803031CC(void);
extern void fn_80302B80(int, int);
extern void fn_80303200(int, int, int, int, int);
extern void fn_80021B2C(int);
extern void fn_80021A08(int, int, int, int, int, int, int);
extern void fn_80021BF4(int);
extern void fn_80021CB4(int, int, int, int);
extern void fn_80021C34(int);
extern void fn_803128AC(f32, f32, f32, void*);
extern void* fn_8000FB88(void);
extern void fn_80312378(void*, void*, void*);
extern void fn_80307E48(void*, int);
extern void fn_80021784(int);
extern void fn_80021860(int, int, int);
extern void fn_80021BA4(int, int, int, int);
extern void fn_80021808(int, int, int, int, int);
extern void fn_80021EF8(int, int);
extern void fn_8001D44C(void*, void*);
extern void fn_80312DB4(void*, Vc*, Vc*);
extern void fn_800F33A4(f32, f32, f32, f32, f32, int, void*);
extern void fn_80307F10(void*, int, int);
extern void fn_80021F7C(int, int, int, int);
extern void fn_800F3360(f32, f32, C4, int);
extern void fn_80011838(int);
extern const Vc lbl_8036E988;
extern void fn_800081D4(void*);
extern int fn_80008C98(void*, int);
extern void fn_80008F20(void*, u8);
extern void fn_801CC5CC(MObj*, f32, f32, f32, f32);
extern void fn_80010788(int, int, void*, void*);
extern void fn_800180F0(void*);
extern void fn_8001AFE0(void*);
extern void fn_801CD478(MObj*);
void fn_801CC06C(u8* o);

void fn_801CC06C(u8* o) {
    u8 tex[0x20];
    u8 m2[0x30];
    u8 m1[0x30];
    u8 mtx[0x30];
    fn_80006A64(*(void**)((u8*)fn_8013B9A8() + 0x7C), tex, 0);
    fn_80022254(tex, 0);
    fn_80021B68(2);
    fn_803031CC();
    fn_80302B80(9, 1);
    fn_80302B80(0xB, 1);
    fn_80303200(0, 9, 1, 4, 0);
    fn_80303200(0, 0xB, 1, 5, 0);
    fn_80021B2C(1);
    fn_80021A08(4, 0, 1, 1, 0, 0, 2);
    fn_80021BF4(1);
    fn_80021CB4(0, 0, 0, 4);
    fn_80021C34(1);
    fn_803128AC(0.0f, 0.0f, -0.01f, m1);
    fn_80312378(fn_8000FB88(), m1, m2);
    fn_80307E48(m2, 0);
    fn_80021784(0);
    fn_80021860(1, 3, 0);
    fn_80021BA4(1, 4, 5, 7);
    fn_80021808(7, 0, 1, 7, 0);
    fn_80021EF8(0, 0);
    fn_8001D44C(o + 0x20, mtx);
    {
    Vc v = lbl_8036E988;
    f32 x, y;
    fn_80312DB4(mtx, &v, &v);
    x = v.x;
    y = v.y;
    {
    u8 a = o[0x1F];
    fn_800F33A4(x, y, 0.5f, 0.5f, 0.0f, 0, m2);
    fn_80307F10(m2, 0x1E, 0);
    fn_80021F7C(0, 0, 0, 0x1E);
    {
    C4 c = {0xFF, 0xFF, 0xFF, a};
    fn_800F3360(x, y, c, 1);
    }
    }
    }
    fn_80011838(-1);
}

int fn_801CC2BC(MObj* o, u32 need, u32 skip) {
    MDef* d = o->def;
    MH* h = &o->h;
    if (d->fl & skip) return 0;
    if (need != (need & d->fl)) return 0;
    if (o->x0 & 4) return 0;
    if ((d->fl & 0x400) && !(o->x0 & 0x10)) {
        if (o->x8 > 0) {
            o->x8--;
        } else {
            fn_800081D4(h);
            if ((h->fl & 2) || fn_80008C98(h, 0x37)) {
                u8* a = fn_80007F10(h);
                if (d->fl & 0x800000) {
                    void* tbl[0x40];
                    int n = fn_80009D60(fn_80007F10(h), 0x37, tbl);
                    if (d->fl & 0x4000) n--;
                    if (n > 0) {
                        fn_8000866C(h, (int)*(u16*)tbl[fn_80089ED0() % n]);
                        fn_80007C58(h);
                    }
                }
                if (d->fl & 0x400000) {
                    int len = *(int*)(a + 0x18) - *(int*)(a + 0x14);
                    if (d->fl & 0x800000) {
                        int hl = len / 2;
                        len = hl + fn_80089ED0() % hl;
                        o->xA = 64.0f * (f32)(fn_80089ED0() % 0x168);
                        {
                        u8 s = 64.0f * ((f32)((fn_80089ED0() & 0x1FF) + 0x200) / 1024.0f);
                        o->x3 = s;
                        }
                        fn_801CC5CC(o, 0.0f, 0.0f, 0.0f, 0.0f);
                    }
                    o->x8 = len;
                }
            }
        }
    }
    if (o->x0 & 0x60) return 0;
    if (d->fl & 0x10000000) {
        u8 v = o->xCD;
        fn_80008F20(&o->h, v);
        fn_801CC5CC(o, 0.0f, 0.0f, 0.0f, 0.0f);
        if (v == 0) return 0;
    }
    if (d->fl & 0x10000) fn_80010788(3, 0x84, (void*)fn_801CC06C, o);
    if (d->fl & 0x400) fn_80007C58(h);
    fn_800180F0(h);
    if (o->x0 & 2) fn_8001AFE0(h);
    if (d->fl & 0x2000000) fn_801CD478(o);
    return 1;
}

}
