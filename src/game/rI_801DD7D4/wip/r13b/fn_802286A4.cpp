#include "game/rI_801DD7D4/fn_wf.h"
#pragma auto_inline off
extern "C" {
void* fn_801E5640(void*, int, int);
void fn_801E5734(void*, void*);
void fn_801E518C(void*, void*, int, f32);
void fn_801E4D1C(void*, void*, int);
void fn_801E495C(void*, void*, void*, int);
f32 fn_801E33B4(void*);
f32 fn_801E3468(void*);
void fn_801EA538(void*, void*);
void fn_80083B78(void*);
void fn_80083DC4(void*, int);
void* fn_8010B22C(int);
int fn_8011B8A4(void*);
void* fn_8014C2AC(void*);
extern char lbl_80371E1C[];
extern u8 lbl_803CA870[0x130];
extern u8 lbl_8038FB98[];
void fn_80232864(void* p, void* arg);
struct XY { s16 x, y; };
class MV { public: virtual int v08(); virtual int v0C(); virtual int v10(); virtual int v14(); virtual int v18(); virtual int v1C();
    virtual int v20(); virtual int v24(); virtual int v28(); virtual int v2C(); virtual int v30(); virtual int v34(void*); };
struct Wy { void* vt; int rc; s16 id; s16 x, y; u8 pe[0x22]; f32 a30, a34; u8 p38[4]; Wy* parent; const char* a40; u8 p44[8]; u8 a4c, a4d, a4e, p4f; u8 a50, a51; u8 p52[2]; void* a54; u8 p58[8]; u8 a60; u8 p61[7]; u8 a68; u8 p69[0x13]; void* a7c; int a80; };
static inline void mv(void* s, Wy* w, s16 x, s16 y, int f) { XY p; p.x = x; p.y = y; fn_801E459C(s, w, &p, f); }
static inline void mv3(void* s, Wy* w, s16 x, s16 y, int f) { XY p; p.x = x; p.y = y; fn_801E495C(s, w, &p, f); }
struct HH { u8 p[0x64]; const char* a64; };
struct WU { WF w; f32 a40; void* a44; void* a48; };
static inline WU* newU(void) {
    WU* o = (WU*)fn_80079150(0x4c);
    if (o != NULL) {
        wfInit(&o->w, 0x191, 0x45, 0x297, 0x13b, 0x106, 0xf6, 0x1b8, 0x10);
        o->w.vt = lbl_8038FB98;
        o->a40 = -1.0f;
        o->a44 = 0;
        o->a48 = 0;
        ((VO0N*)o)->v2C();
    }
    return o;
}
static inline void newUnit(void* s, void* u) {
    WU* o = newU();
    o->w.id = 0x86;
    o->w.a28 = 8;
    {
        void* g = *(void**)lbl_803CA870;
        f32 f;
        o->a44 = g;
        f = g != NULL ? (f32)fn_8011B8A4((u8*)g + 0x12c) : -1.0f;
        o->a40 = f;
    }
    o->a48 = u;
    fn_801E5448(s, o);
    mv(s, (Wy*)o, 0x13d, o->w.y0, 1);
}
struct B3 { u8 p[0x4c]; u8 a4c; };
static inline void c0(B3* q) { q->a4c = 0; }
void fn_802286A4(void* s) {
    /*P*/
    u8* g;
    void* u;
    Wy* a;
    Wy* b;
/*E*/
    g = lbl_803CA870;
    u = fn_8010B22C(*(int*)(g + 0x18));
    a = (Wy*)fn_801E5640(s, 0x83, 0);
    b = (Wy*)fn_801E5640(s, 0x87, 0);
    switch (g[0xc]) {
    case 0x81:
        /*Q*/
        mv3(s, a, 0x1a4, a->y, 0);
        newUnit(s, u);
        fn_80083B78(s);
        break;
    case 0x80:
        fn_80083DC4(s, 0xd);
        break;
    }
}
}
