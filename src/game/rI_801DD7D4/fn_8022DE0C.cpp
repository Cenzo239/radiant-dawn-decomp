#include "game/rI_801DD7D4/types.h"
extern "C" {
u32 strlen(const char*);
void* fn_80081194(void*, void*);
void fn_801E4094(void*);
void fn_800453B4(void*, int);
void* fn_80079150(u32);
void fn_802167C8(void*, int, int, int, int, int, int);
void fn_801E5448(void*, void*);
void* fn_801E5640(void*, int, int);
void fn_8022B758(void*, const char*);
struct E { E() {} char c; };
void fn_800250B0(void*, int, u32, const char*, const char*, E);
extern u8 lbl_803904D0[], lbl_803CA870[], lbl_80390540[];
struct V { virtual void v08(); virtual void v0c(); virtual void* v10(int, int); virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38(int); };
struct W80 { void* vt; u8 p[4]; s16 x8; u8 p2[0x1e]; s16 x28; u8 p3[6]; f32 x30; u8 p4[0x3c]; int x70, x74, x78, x7c; };
struct Str { u32 w; u32 sz; u32 x; };
struct P1 { u8 p[0x40]; const char* x40; union { struct { u8 b0; }; u32 u; } x44; u32 x48; u32 x4c; };
P1* fn_8022DE0C(const char* a, const char* b, int c, void* d) {
    P1* o = (P1*)fn_80081194(lbl_803904D0, d);
    W80* w;
    if (o) {
        fn_801E4094(o);
        o->x40 = 0;
        o->x44.u = 0;
        o->x48 = 0;
        o->x4c = 0;
    }
    fn_800453B4(lbl_803CA870, 0);
    w = (W80*)fn_80079150(0x80);
    if (w) {
        fn_802167C8(w, 0x7a, 0x5e, 0x1ce, 0x11c, 0x1f4, 0);
        w->vt = lbl_80390540;
        w->x70 = 0;
        w->x74 = 0;
        w->x78 = 0;
        w->x7c = 0;
        ((V*)w)->v2c();
    }
    w->x8 = 0;
    w->x28 = 8;
    w->x30 = 0.0f;
    ((V*)w)->v38(0);
    fn_801E5448(o, w);
    ((W80*)((V*)fn_801E5640(o, 0, 0))->v10(0x80, 0))->x7c = c;
    {
    V* q = (V*)fn_801E5640(o, 0, 0);
    o->x40 = a;
    fn_8022B758(q->v10(0x80, 0), a);
    }
    {
    u32 sz;
    if ((o->x44.u >> 31) == 0) sz = o->x44.b0 & 0x7f; else sz = o->x48;

    fn_800250B0(&o->x44, 0, sz, b, b + strlen(b), E());
    }
    return o;
}
}
