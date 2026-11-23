#include "game/rL_80133EB4/map3d.h"
#pragma auto_inline off
extern "C" {
extern u8 lbl_80386540[];
extern u8 lbl_803864B4[];
struct WeatherP {
    u8 pad0[0x30];
    u8 x30, x31, x32, x33, x34, pad35;
    s16 x36;
    f32 x38, x3c, x40;
    u8 pad44[4];
    Vec dir;      /* 0x48 */
    Vec lo;       /* 0x54 */
    Vec hi;       /* 0x60 */
    f32 x6c, x70;
    u8 pad74[4];
    u8 x78, x79, x7a, pad7b;
    void* x7c;
};
struct Layer {
    u8 pad0[0x30];
    f32 x30;
    f32 x34;
    void* x38;
};
struct Particle { void* n; void* p; u8 pad[0x18]; };
struct ParticleList { Particle* a; Particle** b; Particle** c; void* d; void* e; int f; int g; };
struct RainP {
    u8 pad0[0x30];
    u8 x30; s8 x31; u8 x32, pad33;
    f32 x34;
    void* x38;
    ParticleList* x3c;
};
extern u8 lbl_80369AF8[];
extern char lbl_80369B0D[];
extern char lbl_804CA72C[8];
extern char lbl_804CA728[4];
extern char lbl_804CA724[4];
extern void* fn_80083B84(void*);
extern void* fn_80081050(void*, void*);
extern void* fn_8001D3B4(void*);
extern void fn_80082230(void*);
extern MapModel* fn_8013B9A8(void);
#if TARGET_PC
extern FE10_PROTO void fn_80135F90(MapModel*, p32arg, void*, int, int, p32arg);
#else
extern void fn_80135F90(MapModel*, int, void*, int, int, int);
#endif
extern void fn_801444B8(void);
extern void fn_801461D8(void*);
extern void fn_8014531C(RainP*);
extern void fn_80144888(void*);
extern void* fn_800E4060(const char*, void*);
extern int fn_8013B664(MapModel*);
extern void* fn_80078CCC(int, const char*, int);
extern void DCFlushRange(void*, u32);
extern void fn_803134A8(f32, Vec*, Vec*);

struct W1 { u8 pad0[0x30]; f32 x30; f32 x34; void* x38; };
struct WD { u8 pad0[0x30]; u8 x30; };
struct WF { u8 pad0[0x30]; u8* x30; };


/* fn_8014531C: only lis r28,1 hoist is missing */
static inline ParticleList* NewPL(void) {
    ParticleList* l = (ParticleList*)fn_80078CCC(0x1C, lbl_804CA72C, 0);
    if (l) {
        l->a = 0;
        l->b = 0;
        l->c = 0;
        l->f = 0;
        l->d = 0;
        l->e = 0;
    }
    return l;
}
static inline void InitPL(ParticleList* l, int n) {
    l->g = n;
    int sz = l->g * sizeof(Particle);
    l->a = (Particle*)fn_80078CCC(sz, lbl_804CA728, 0);
    l->b = (Particle**)fn_80078CCC(n * 4 + 4, lbl_804CA724, 0);
    DCFlushRange(l->a, sz);
    DCFlushRange(l->b, n * 4 + 4);
    l->f = 0;
    {
        int i;
        for (i = 0; i < l->g; i++) {
            Particle* e = l->a + i;
            e->n = 0;
            e->p = 0;
            l->b[i] = &l->a[i];
        }
    }
    l->c = l->b;
    l->b[l->g] = 0;
    l->d = 0;
    l->e = 0;
}
void fn_8014531C(RainP* r) {
    WeatherP* w = (WeatherP*)fn_80083B84(lbl_80386540);
    r->x38 = fn_8001D3B4(lbl_80369AF8);
    ParticleList* l = NewPL();
    r->x3c = l;
    InitPL(l, 0x800);
    r->x32 = 1;
    r->x31 = -1;
    switch (r->x30) {
    case 7:
        w->x33 = 10;
        w->x38 = 0.75f;
        w->x34 = 0xC0;
        w->dir.x = 0.025f;
        w->dir.y = -0.05f;
        w->dir.z = 0.025f;
        w->x78 = 0xFF;
        w->x79 = 0xFF;
        w->x7a = 0xFF;
        w->x36 = 300;
        break;
    case 8:
        w->x33 = 2;
        w->x38 = 0.5f;
        w->x34 = 0xC0;
        w->dir.x = 0.005f;
        w->dir.y = -0.025f;
        w->dir.z = 0.005f;
        w->x78 = 0xFF;
        w->x79 = 0xFF;
        w->x7a = 0xFF;
        w->x36 = 600;
        break;
    case 9:
    {
        WD* d;
        w->x33 = 0x32;
        w->x38 = 0.75f;
        w->x34 = 0xC0;
        w->dir.x = 0.5f;
        w->dir.y = -0.25f;
        w->dir.z = 0.05f;
        w->x78 = 0xFF;
        w->x79 = 0xFF;
        w->x7a = 0xFF;
        w->x36 = 100;
        d = (WD*)fn_80081050(lbl_803864B4, r);
        d->x30 = 1;
        fn_80144888(d);
        break;
    }
    case 0x13:
        w->x33 = 3;
        w->x38 = 0.6f;
        w->x34 = 0xFF;
        w->dir.x = -0.024999999f;
        w->dir.y = 0.099999994f;
        w->dir.z = 0.024999999f;
        w->x78 = 0xFF;
        w->x79 = 0x6B;
        w->x7a = 0;
        w->x36 = 300;
        break;
    }
    {
        MapModel* mm = fn_8013B9A8();
        switch (w->x32) {
        case 0:
            {
{ f32 m = -8.0f; w->lo.x = m; { f32 s = mm->scale; w->lo.y = 20.0f * s; } w->lo.z = m; w->hi.x = mm->x4c + 8; { f32 s = mm->scale; w->hi.y = 40.0f * s; } w->hi.z = mm->x4d + 8; } }
            break;
        case 1:
        case 2:
        case 3:
        case 4:
            {
                        f32 a;
            f32 e;
            f32 d;
            f32 c;
            f32 b;
            f32 f;
            { f32 s = mm->scale; a=-80.0f; a *= s; w->lo.x = a; }
            b=10.0f;
            c=-60.0f;
            d=80.0f;
            e=20.0f;
            f=30.0f;
            { f32 s = mm->scale; b *= s; w->lo.y = b; }
            { f32 s = mm->scale; c *= s; w->lo.z = c; }
            { f32 s = mm->scale; d *= s; w->hi.x = d; }
            { f32 s = mm->scale; e *= s; w->hi.y = e; }
            { f32 s = mm->scale; f *= s; w->hi.z = f; }
            }
            break;
        }
        r->x34 = mm->scale;
        fn_803134A8(r->x34, &w->dir, &w->dir);
    }
    w->x3c = 0.0f;
}

}
