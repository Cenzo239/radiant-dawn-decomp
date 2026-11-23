#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#pragma auto_inline off
#pragma use_lmw_stmw on
extern "C" {
void fn_80079210(void*);
void* fn_801E5640(void*, int, int);
void fn_80083DC4(void*, int);
void fn_80083B78(void*);
void fn_801E5734(void*, void*);
void fn_8014C2AC(void*);
void fn_80253EE4(const char*, f32);
void fn_801E495C(void*, void*, void*, int);
void fn_801E518C(void*, void*, int, f32);
void fn_801E4F50(void*, void*, int);
extern VO0N* lbl_804CB5B8;
extern u8 lbl_803CA870[0x130];
extern u8 lbl_803CAB38[0x988];
extern char lbl_80372600[];
struct XY { s16 x, y; };
struct Wi { u8 p[0x40]; const char* a40; u8 p44[0x20]; const char* a64; };
struct WY { u8 p[0xa]; s16 x, y; };
struct Sm { u8 p[0x88]; u8* a88; };
static inline void mvx(void* s, WY* w, s16 x, s16 y, int f) { XY p; p.x = x; p.y = y; fn_801E495C(s, w, &p, f); }
static inline void setHelpV(void* s, const char* str) { Wi* h = (Wi*)fn_801E5640(s, -0x1000, 0); if (h != NULL) h->a64 = str; }
#define SL12 virtual int s08(); virtual int s0C(); virtual int s10(); virtual int s14(); virtual int s18(); virtual int s1C(); virtual int s20(); virtual int s24(); virtual int s28(); virtual int s2C(); virtual int s30(); virtual int s34();
class V38 { public: SL12 virtual void v38(int); };
class V382 { public: SL12 virtual void v38(int, int); };
void fn_801E5448(void*, void*);
void fn_801E459C(void*, void*, void*, int);
void fn_801E41E4(void*, void*, void*, int);
void* fn_80079150(int);
void* fn_801E041C(const char*, const char*);
void* fn_800D5448(void*, void*, int);
void* fn_8010B22C(int);
struct WF { void* vt; int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1; s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26; s16 a28; u8 p2a[2]; f32 sx, sy, sz; int flags; int a3c; };
extern u8 lbl_8038CB1C[];
static inline void wfInit(WF* w, s16 x0, s16 y0, s16 x1, s16 y1, s16 ix1, s16 iy1, s16 a26, int fl) {
    w->rc = 0;
    w->vt = lbl_8038CB1C;
    w->id = -1;
    w->x0 = x0; w->y0 = y0; w->x1 = x1; w->y1 = y1;
    w->ix0 = 0; w->iy0 = 0; w->ix1 = ix1; w->iy1 = iy1;
    w->a1a = 0; w->a1c = 0; w->tx = 0; w->ty = 0;
    w->c[0] = 0xff; w->c[1] = 0xff; w->c[2] = 0xff; w->c[3] = 0xff;
    w->a26 = a26; w->a28 = 0;
    w->sx = 1.0f; w->sy = 1.0f; w->sz = 1.0f;
    w->flags = fl; w->a3c = 0;
}

static inline void mv(void* s, WY* w, s16 x, s16 y, int f) { XY p; p.x = x; p.y = y; fn_801E459C(s, w, &p, f); }
static inline void mv2(void* s, WY* w, s16 x, s16 y, int f) { XY p; p.x = x; p.y = y; fn_801E41E4(s, w, &p, f); }
static inline void setHelpR(void* s, const char* const& str) { Wi* h = (Wi*)fn_801E5640(s, -0x1000, 0); if (h != NULL) h->a64 = str; }
extern char lbl_80371E1C[];
struct Wa { u8 p[0x40]; const char* a40; };
struct S54 { u8 p[0x48]; void* a48; u8 p4c[8]; void* a54; void* a58; };
void fn_80226C14(S54* s) {
    WY* b;
    WY* a = (WY*)fn_801E5640(s, 0x85, 0);
    if (a == NULL) {
        a = (WY*)s->a54;
        fn_801E5448(s, a);
    }
    if (a->x != 0x13d) mv(s, a, 0x13d, a->y, 1);
    *((u8*)a + 0x54) = 0;
    b = (WY*)fn_801E5640(s, 0x88, 0);
    {
        if (b == NULL) {
            b = (WY*)s->a58;
            fn_801E5448(s, b);
        }
        if (b->x != 0x144) mv(s, b, 0x144, b->y, 1);
    }
    b = (WY*)fn_801E5640(s, 0x83, 0);
    if (b == NULL) {
        b = (WY*)s->a48;
        fn_801E5448(s, b);
        if (b->x != 0x150 || b->y != 0x112) mv(s, b, 0x150, 0x112, 0);
    } else if (b->x != 0x150 || b->y != 0x112) {
        mv2(s, b, 0x150, 0x112, 0);
    }
    { Wa* t = (Wa*)fn_801E5640(s, 0x80, 0); t->a40 = lbl_80371E1C + 0x8a; }
    fn_801E5734(s, a);
    setHelpR(s, lbl_80371E1C + 0x76);
}
extern u8 lbl_8038FBD0[];
extern u8 lbl_803CA888[];
struct G2 { WF w; void* a40; };
void fn_80227358(void* s) {
    void* u = fn_8010B22C(*(int*)(lbl_803CA870 + 0x18));
    G2* o = (G2*)fn_80079150(0x4c);
    if (o != NULL) {
        wfInit(&o->w, 0x191, 0x45, 0x297, 0x10b, 0x106, 0xc6, 0x1cc, 0x10);
        o->w.vt = lbl_8038FBD0;
        o->a40 = 0;
        ((VO0N*)o)->v2C();
    }
    o->w.id = 0x87;
    o->w.a28 = 8;
    o->a40 = u;
    fn_801E5448(s, o);
    mv(s, (WY*)o, 0x13d, o->w.y0, 1);
    {
        u8* m = (u8*)fn_801E041C(0, 0);
        *(s16*)(m + 8) = 0x180;
        *(s16*)(m + 0xa) = 0x1b;
        m[0x24] = 1;
        fn_800D5448(m, s, 0);
    }
    { Wa* t = (Wa*)fn_801E5640(s, 0x80, 0); t->a40 = lbl_80371E1C + 0xdf; }
    setHelpR(s, lbl_80371E1C + 0xf8);
}
}
