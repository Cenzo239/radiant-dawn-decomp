/* Mostly process callbacks for map screens: phase banner, fades, weather, screen capture. */
#include "game/rL_80133EB4/map3d.h"
#pragma auto_inline off
#pragma use_lmw_stmw on

extern "C" {

extern u8 lbl_803CAB38[];
extern u8 lbl_80386540[];
extern u8 lbl_803865F0[];
extern u8 lbl_80386618[];
extern u8 lbl_80386670[];
extern u8 lbl_80386698[];
extern u8 lbl_803866C0[];
extern u8 lbl_80369AF8[];
extern char lbl_80369B30[];
extern u8 lbl_804CB830;
extern u8 lbl_804CB870;
extern u8 lbl_804CB871;
extern u16 lbl_804CB872;
extern u16 lbl_804CB874;
extern void* lbl_80413F00[3];

extern MapModel* fn_8013B9A8(void);
extern u32 fn_8013B9CC(void);
extern void fn_8013602C(MapModel*, void*, void*);
#if TARGET_PC
extern FE10_PROTO void fn_80135F90(MapModel*, p32arg, void*, int, int, p32arg);
#else
extern void fn_80135F90(MapModel*, int, void*, int, int, int);
#endif
extern void fn_80078E24(void*);
extern void fn_80010788(int, int, void*, void*);
extern void fn_80143908(void*);
extern void fn_80140E68(void);
extern void* fn_80083B84(void*);
extern void fn_80083B78(void*);
extern void* fn_80081050(void*, void*);
extern void* fn_80081194(void*, void*);
extern void* fn_800811E4(void*, void*);
extern void fn_800846BC(void*);
extern void fn_8001D424(void*);
extern void* fn_8001D3B4(void*);
extern u8 fn_8001F04C(int, int, int, int);
extern f32 fn_8001EF30(f32, f32, f32, f32);
extern f32 fn_8001EBC8(f32, f32, f32, f32, int);
extern void fn_80043DE8(int);
extern void fn_80053A7C(void);
extern void fn_800E24F8(const char*);
extern int fn_800E272C(const char*);
extern u8* fn_80060728(void*);
extern void fn_8017F4A0(void*, void*, u32);
extern void DCFlushRange(void*, u32);
extern void fn_801476E8(void);
extern void fn_80147EF4(int);
extern void fn_80147B58(void);

struct SndV {
    virtual void v08();
    virtual void v0C();
    virtual int v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24(int);
};
extern SndV* fn_8024F484(s8);

struct PA { u8 pad0[0x30]; u8 x30; s8 x31; u8 pad32[6]; void* x38; void* x3c; void* x40; void* x44; void* x48; void* x4c; void* x50; void* x54; void* x58; void* x5c; };

void fn_801435E4(PA* p) {
    MapModel* mm = fn_8013B9A8();
    if (mm) fn_8013602C(mm, 0, 0);
    p->x3c = 0;
    p->x40 = 0;
    p->x50 = 0;
    p->x54 = 0;
    p->x58 = 0;
    p->x5c = 0;
    fn_80078E24(p->x38);
    p->x38 = 0;
    fn_80078E24(p->x44);
    p->x44 = 0;
}

struct PB { u8 pad0[0x30]; u32 t; f32 x34; u8 pad38[4]; void* x3c; };

void fn_80143660(PB* p) {
    MapModel* mm;
    fn_80143908(p);
    if (p->x3c) fn_80010788(0, 0x42, fn_80140E68, 0);
    mm = fn_8013B9A8();
    if (mm) {
        p->x34 += 0.01f;
        p->t += ((u8*)mm)[0x65];
    }
}

struct PC { u8 pad0[0x30]; u8 x30; s8 x31; u8 pad32[2]; f32 x34; f32 x38; f32 x3c; f32 x40; f32 x44; f32 x48; f32 x4c; void* x50; };
struct WeatherProc { u8 pad0[0x30]; u8 x30; u8 x31; u8 x32; u8 x33; u8 x34; u8 pad35; u16 x36; f32 x38; f32 x3c; f32 x40; u8 pad44[0x54 - 0x44]; Vec v54; Vec v60; u8 pad6C[0x78 - 0x6C]; u8 c[4]; u32 x7c; };

void fn_80144B2C(PC* p) {
    fn_8001D424(p->x50);
    if (p->x31 >= 0) {
        SndV* s = fn_8024F484(p->x31);
        if (s && s->v10()) s->v24(0);
    }
}

void fn_801458B4(PA* p) {
    SndV* s;
    void** b = (void**)p->x3c;
    if (b) {
        if (b) {
            fn_80078E24(b[0]);
            b[0] = 0;
            fn_80078E24(b[1]);
            b[1] = 0;
            fn_80078E24(b);
        }
        p->x3c = 0;
    }
    fn_8001D424(p->x38);
    if (p->x31 >= 0) {
        s = fn_8024F484(p->x31);
        if (s && s->v10()) s->v24(0);
    }
}

extern void fn_80079474(void*);
struct PD { u8 pad0[0x38]; s8 x38; u8 pad39[3]; void* x3c; void* x40; void* x44; void* x48; };

void fn_80146928(PD* p) {
    fn_80079474(p->x48);
    fn_80079474(p->x44);
    fn_80079474(p->x40);
    fn_8001D424(p->x3c);
    if (p->x38 >= 0) {
        SndV* s = fn_8024F484(p->x38);
        if (s && s->v10()) s->v24(0);
    }
}

struct PE { u8 pad0[0x30]; u8* x30; };

void fn_801469D4(PE* p) {
    WeatherProc* w = (WeatherProc*)fn_80083B84(lbl_80386540);
    u8* o = p->x30;
    if (o) {
        if (w->x30) {
            *(u32*)(*(u8**)(o + 0x30) + 0x18) &= ~0x10;
        } else {
            *(u32*)(*(u8**)(o + 0x30) + 0x18) |= 0x10;
        }
    }
}

extern struct Color4 { u8 r, g, b, a; } lbl_804CA720;
extern u8 lbl_804CA721;
extern u8 lbl_804CA722;
extern u8 lbl_804CA723;
struct Vec2I {
    int x, y, z;
    f32 fx() { return *(f32*)&x; }
    f32 fy() { return *(f32*)&y; }
    f32 fz() { return *(f32*)&z; }
};

static inline void SetC4(WeatherProc* w, const Color4& c) {
    w->c[0] = c.r;
    w->c[1] = c.g;
    w->c[2] = c.b;
    w->c[3] = c.a;
}

struct PF { u8 pad0[0x30]; int a; int b; int n; int t; };

void fn_80146EC8(PF* p) {
    WeatherProc* w;
    p->t++;
    if (p->t > p->n) {
        p->t = p->n;
        fn_80083B78(p);
    }
    w = (WeatherProc*)fn_80083B84(lbl_80386540);
    w->x34 = fn_8001F04C(p->a, p->b, p->n, p->t);
}

void fn_80146F40(WeatherProc* w, int from, int to, int n) {
    if (n == 0) {
        w->x34 = to;
    } else {
        PF* p = (PF*)fn_80081050(lbl_803865F0, w);
        p->a = from;
        p->b = to;
        p->n = n;
        w->x34 = from;
    }
}

static inline const char* PhaseEid(void) {
    switch (lbl_803CAB38[0x11]) {
    case 0: return lbl_80369B30;
    case 1: return lbl_80369B30 + 0x10;
    case 2: return lbl_80369B30 + 0x1F;
    case 3: return lbl_80369B30 + 0x2E;
    }
    return 0;
}

void fn_80146FF8(void) {
    fn_80043DE8(0xFA);
    fn_80053A7C();
    fn_800E24F8(PhaseEid());
}

void fn_80147098(void* p) {
    if (fn_800E272C(PhaseEid())) fn_80083B78(p);
}

extern void fn_800E4B20(void*, int);

void fn_801473D4(u8* p) {
    int* t = (int*)(p + 0x48);
    *t -= 1;
    if (*t == 0) {
        fn_80083B78(p);
    } else if (lbl_804CB5B8->v48() & 0x400) {
        if (*(void**)(p + 0x4C)) fn_800E4B20(*(void**)(p + 0x4C), 0x14);
        fn_80083B78(p);
    }
}

void fn_80147524(void) { lbl_804CB5B8->vA8(10); }

struct Banner { u8 pad0[0x30]; int t; int a; f32 x38; f32 x3c; u8 pad40[4]; int n; };

void fn_801472F8(Banner* p) {
    p->t++;
    p->x38 = fn_8001EBC8(-256.0f, 0.0f, p->n, p->t, 2);
    p->a = fn_8001EF30(0.0f, 255.0f, p->n, p->t);
    if (p->t >= p->n) fn_80083B78(p);
}

void fn_8014744C(Banner* p) {
    p->t--;
    p->x38 = fn_8001EBC8(256.0f, 0.0f, p->n, p->t, 2);
    p->a = fn_8001EF30(0.0f, 255.0f, p->n, p->t);
    if (p->t <= 0) fn_80083B78(p);
}

extern u8* lbl_804CB814;

void fn_8014753C(void* parent) {
    u8* u = *(u8**)(lbl_804CB814 + lbl_803CAB38[0x11] * 0xC);
    while (u) {
        u32 f = *(u32*)(u + 0x10C);
        u = *(u8**)(u + 0xE8);
        if (!(f & 4)) goto found;
    }
    return;
found:
    fn_80081194(lbl_80386618, parent);
    if ((*(u32*)fn_80060728(lbl_803CAB38) & 3) == 2 && *(u32*)(fn_80060728(lbl_803CAB38) + 4) >> 31) {
        fn_80081050(lbl_80386670, parent);
    }
}

void fn_80147AF8(void) {
    if (lbl_804CB830 == 0) {
        fn_8013602C(fn_8013B9A8(), 0, fn_80147B58);
    } else {
        fn_80135F90(fn_8013B9A8(), 0, fn_80147B58, 0, 0, 2);
    }
}

struct PG { u8 pad0[0x60]; int t; };

void fn_80148198(PG* p) {
    void* d;
    int i;
    p->t = 0;
    for (i = 1; i < 3; i++) {
        d = lbl_80413F00[(lbl_804CB871 + i) % 3];
        fn_8017F4A0(d, lbl_80413F00[lbl_804CB871], 0x2000);
        DCFlushRange(d, 0x2000);
    }
    fn_801476E8();
    lbl_804CB871 = (u8)(lbl_804CB871 + 1) % 3;
}

void fn_80148270(PG* p) {
    p->t++;
    fn_80147EF4((u8)fn_8001EF30(0.0f, 128.0f, 16.0f, p->t));
    if (p->t == 0x10) fn_80083B78(p);
}

static inline BOOL IsShadowMode(void) { return lbl_804CB830 == 1 || lbl_804CB830 == 2; }

void fn_801484B4(void* parent) {
    if (fn_8013B9CC()) {
        if (IsShadowMode()) {
            fn_800811E4(lbl_80386698, parent);
            fn_800811E4(lbl_803866C0, parent);
        }
    }
}

void fn_8014857C(void) {
    int i;
    fn_800846BC(lbl_803866C0);
    fn_800846BC(lbl_80386698);
    for (i = 0; i < 3; i++) {
        fn_80078E24(lbl_80413F00[i]);
        lbl_80413F00[i] = 0;
    }
    lbl_804CB870 = 0;
}

} /* extern "C" */
