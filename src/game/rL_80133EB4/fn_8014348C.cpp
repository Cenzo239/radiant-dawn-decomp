/* Screen effects drawn with GX: fades, weather overlay, sunlight, reflections. */
#include "game/rL_80133EB4/map3d.h"
#pragma auto_inline off
#pragma use_lmw_stmw on

extern "C" {

struct Color { u8 r, g, b, a; };

extern u8 lbl_80386490[];
extern u8 lbl_80386540[];
extern u8 lbl_80369AF8[];
extern u8 lbl_803CAB38[];
extern u8 lbl_80413EA0[];
extern void* lbl_80413F00[3];
extern u8 lbl_804CB870;
extern u8 lbl_804CB871;
extern u16 lbl_804CB872;
extern u16 lbl_804CB874;
extern char lbl_80369BA8[];

extern MapModel* fn_8013B9A8(void);
extern void* fn_80083B84(void*);
#if TARGET_PC
extern FE10_PROTO ptr32<void> fn_80011E28(void);
#else
extern void* fn_80011E28(void);
#endif
#if TARGET_PC
extern FE10_PROTO ptr32<void> fn_80012170(void);
extern FE10_PROTO ptr32<void> fn_800121C8(ptr32<const void>);
#else
extern void* fn_80012170(void);
extern void* fn_800121C8(void*);
#endif
#if TARGET_PC
extern FE10_PROTO void fn_80306EA0(ptr32<const void>, Color*);
#else
extern void fn_80306EA0(void*, Color*);
#endif
#if TARGET_PC
extern FE10_PROTO void fn_80021FF0(ptr32<const void>, ptr32<const void>);
extern FE10_PROTO void fn_80021CB4(ptr32<const void>, ptr32<const void>, ptr32<const void>, int);
extern FE10_PROTO void fn_80021E20(ptr32<const void>, int, int, int, int);
extern FE10_PROTO void fn_80021D18(ptr32<const void>, int, int, int, int, int);
extern FE10_PROTO void fn_80021E8C(ptr32<const void>, int, int, int, int);
extern FE10_PROTO void fn_80021D9C(ptr32<const void>, int, int, int, int, int);
#else
extern void fn_80021FF0(void*, void*);
extern void fn_80021CB4(void*, void*, void*, int);
extern void fn_80021E20(void*, int, int, int, int);
extern void fn_80021D18(void*, int, int, int, int, int);
extern void fn_80021E8C(void*, int, int, int, int);
extern void fn_80021D9C(void*, int, int, int, int, int);
#endif
extern void fn_80019D9C(void*);
#if TARGET_PC
extern FE10_PROTO ptr32<void> fn_80011F38(void);
extern FE10_PROTO ptr32<void> fn_80011EB4(void);
#else
extern void* fn_80011F38(void);
extern void* fn_80011EB4(void);
#endif
#if TARGET_PC
extern FE10_PROTO ptr32<void> fn_80011FC4(void);
#else
extern void* fn_80011FC4(void);
#endif
extern void fn_80312378(void*, void*, void*);
#if TARGET_PC
extern FE10_PROTO void fn_80307F10(void*, ptr32<const void>, int);
#else
extern void fn_80307F10(void*, void*, int);
#endif
extern void fn_80006A64(void*, void*, int);
#if TARGET_PC
extern FE10_PROTO void fn_80022254(void*, ptr32<const void>);
extern FE10_PROTO void fn_80021F7C(ptr32<const void>, int, int, ptr32<const void>);
#else
extern void fn_80022254(void*, void*);
extern void fn_80021F7C(void*, int, int, void*);
#endif
extern void fn_80312D2C(void*, f32, f32, f32, f32, f32, f32, f32, f32);
extern void fn_803128AC(void*, f32, f32, f32);
extern void fn_80312318(void*);
extern void* fn_80078CCC(int, const char*, int);
extern void fn_80305A40(void*, void*, int, int, int, int, int, int);
extern void fn_80305C94(void*, int, int, int, int, int, f32, f32, f32);
extern void DCFlushRange(void*, u32);
extern void fn_801476E8(void);

void fn_8014348C(void) {
    MapModel* mm = fn_8013B9A8();
    if (mm) {
        void* a = fn_80011E28();
        void* b = fn_80012170();
        void* c = fn_800121C8(b);
        Color col;
        col = *(Color*)((u8*)mm + 0x66);
        fn_80306EA0(b, &col);
        fn_80021FF0(a, c);
        fn_80021CB4(a, (void*)0xFF, (void*)0xFF, 4);
        fn_80021E20(a, 0xC, 0, 0xE, 0xF);
        fn_80021D18(a, 0, 0, 0, 1, 0);
        fn_80021E8C(a, 7, 7, 7, 0);
        fn_80021D9C(a, 0, 0, 0, 1, 0);
    }
}

void fn_801444B8(void) {
    u8* o = (u8*)fn_80083B84(lbl_80386490);
    if (o) {
        u8 tex[0x20];
        u8 m1[0x30];
        u8 m0[0x30];
        void* a;
        void* b;
        void* c;
        void* d;
        fn_80019D9C(m0);
        b = fn_80011F38();
        a = fn_80011E28();
        c = fn_80011EB4();
        d = fn_80011FC4();
        fn_80312378(o + 0x3C, m0, m1);
        fn_80307F10(m1, d, 0);
        fn_80006A64(*(void**)(o + 0x38), tex, 4);
        fn_80022254(tex, c);
        fn_80021F7C(b, 0, 0, d);
        fn_80021CB4(a, b, c, 4);
        fn_80021E20(a, 0xF, 0, 8, 0xF);
        fn_80021D18(a, 0, 0, 0, 1, 0);
        fn_80021E8C(a, 7, 7, 7, 0);
        fn_80021D9C(a, 1, 0, 0, 1, 0);
    }
}

void fn_801475F4(void) {
    void** q = lbl_80413F00;
    u8* t = lbl_80413EA0;
    int i;
    lbl_804CB870 = 1;
    lbl_804CB871 = 0;
    lbl_804CB872 = 0x80;
    lbl_804CB874 = 0x80;
    for (i = 0; i < 3; i++, q++, t += 0x20) {
        *q = fn_80078CCC(0x2000, lbl_80369BA8, 0);
        fn_80305A40(t, *q, 0x80, 0x80, 0, 0, 0, 0);
        fn_80305C94(t, 1, 1, 0, 0, 0, 0.0f, 0.0f, 0.0f);
        DCFlushRange(*q, 0x2000);
    }
    fn_801476E8();
}

void fn_80147D78(void) {
    u8 c[0x30];
    u8 b[0x30];
    u8 a[0x30];
    void* t0;
    void* t1;
    void* t2;
    void* t3;
    fn_80312D2C(b, 64.0f, -64.0f, -64.0f, 64.0f, 0.5f, 0.5f, 0.5f, 0.5f);
    fn_803128AC(c, -63.0f, -63.0f, 0.0f);
    fn_80312318(a);
    fn_80312378(c, a, a);
    fn_80312378(b, a, a);
    t0 = fn_80011E28();
    t1 = fn_80011F38();
    t2 = fn_80011EB4();
    fn_80022254(lbl_80413EA0 + lbl_804CB871 * 0x20, t2);
    t3 = fn_80011FC4();
    fn_80307F10(a, t3, 1);
    fn_80021F7C(t1, 1, 0, t3);
    fn_80021CB4(t0, t1, t2, 0xFF);
    fn_80021E20(t0, 0xF, 0, 8, 0xF);
    fn_80021D18(t0, 0, 0, 0, 1, 0);
    fn_80021E8C(t0, 7, 7, 7, 0);
    fn_80021D9C(t0, 0, 0, 0, 1, 0);
}

extern u8* fn_80010BB0(int);
extern u8* fn_80010DA4(u8*, int);
extern u8* fn_8000F470(void);
extern void fn_80313484(void*, void*, void*);
extern void fn_80011274(void);
extern void fn_80011280(u8*);
extern void fn_800218A8(int, void*);
extern void* fn_8001D3B4(void*);

void fn_80143390(void) {
    u8* l = fn_80010BB0(0);
    u8* d;
    if (l && (d = fn_80010DA4(l, 1)) != 0) {
        Vec save = *(Vec*)(d + 8);
        u8* cam;
        Vec dir;
        u32 z;
        cam = fn_8000F470();
        fn_80313484(cam + 0xE0, cam + 0xD4, &dir);
        *(Vec*)(d + 8) = dir;
        fn_80011274();
        fn_80011280(l);
        z = 0;
        fn_800218A8(4, &z);
        *(Vec*)(d + 8) = save;
    }
}

struct WP {
    u8 pad0[0x30];
    u8 x30;
    u8 x31;
    u8 x32;
    u8 pad33;
    u8 x34;
    u8 pad35[0x6C - 0x35];
    f32 x6c;
    f32 x70;
};
struct RP {
    u8 pad0[0x31];
    s8 x31;
    u8 pad32[2];
    f32 x34;
    f32 x38;
    f32 x3c;
    f32 x40;
    f32 x44;
    f32 x48;
    f32 x4c;
    void* x50;
};

void fn_80144888(RP* p) {
    WP* w = (WP*)fn_80083B84(lbl_80386540);
    w->x34 = 0x40;
    p->x50 = fn_8001D3B4(lbl_80369AF8);
    p->x44 = 0.0f;
    p->x48 = 0.0f;
    p->x4c = 0.0f;
    p->x31 = -1;
    p->x34 = 0.0f;
    p->x3c = 0.0f;
    p->x38 = 0.0f;
    p->x40 = 0.0f;
    if (w->x32 == 0) {
        w->x6c = 2.0f;
        w->x70 = 1.0f;
    } else {
        w->x6c = 3.0f;
        w->x70 = 0.5f;
    }
}

extern int fn_8013B664(MapModel*);
struct WQ { u8 pad0[0x31]; u8 x31; u8 pad32[2]; u8 x34; };

void fn_80146B40(WQ* w) {
    MapModel* mm = fn_8013B9A8();
    if (mm) {
        int n = fn_8013B664(mm);
        switch (w->x31) {
        case 0x13:
            w->x34 = n * 0xFF / 100;
        }
    }
}

} /* extern "C" */
