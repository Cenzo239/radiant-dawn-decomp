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
void fn_801E4D1C(void*, void*, int);
void* fn_80079150(int);
void* fn_801E2204(void*, void*, void*);
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

struct Node { u8 pad[0x2c]; f32 x2c, x30, x34; u8 pad38[4]; Node* parent; };
f32 fn_801E33B4(Node*);
#define animY(s, a, k, fl) { \
    f32 v3; f32 v2; f32 v1; f32 v0; Node* p; Node* q; Node* r; Node* o; \
    v0 = a->x30; p = a->parent; \
    if (p) { v1 = p->x30; q = p->parent; if (q) { v2 = q->x30; r = q->parent; if (r) { v3 = r->x30; o = r->parent; if (o) { v3 *= fn_801E33B4(o); } v2 *= v3; } v1 *= v2; } v0 *= v1; } \
    if (k != v0) fn_801E4D1C(s, a, fl); \
}
int fn_8022B620(int);
int fn_8022B6A0(int);
extern s16 lbl_804CAA78;
static inline const s16& smin(const s16& a, const s16& b) { return a < b ? a : b; }
struct Nm { u8 p[0x40]; int s[13]; s16 a74; };
extern s16 lbl_804CAA80;
extern s16 lbl_804CAA82;
extern char lbl_80371FA0[];
struct Lst { u8 p[0x1e]; s16 tx, ty; u8 p22[0x32]; s16 a54; };
extern u8 lbl_80390258[];
struct Gd { WF w; int a40; s16 a44, a46, a48, a4a, a4c, a4e, a50, a52; u8 p54[8]; f32 a5c; };
Gd* fn_8022A5F8(Gd* o, int a, s16 x, s16 y, s16 z) {
    wfInit(&o->w, x, y, x, y, 0, 0, z, 0x10);
    o->w.vt = lbl_80390258;
    o->a40 = a;
    o->a44 = 0; o->a46 = 0; o->a48 = 0; o->a4a = 0; o->a4c = 0; o->a4e = 0;
    o->a50 = -0x8000; o->a52 = -0x8000;
    o->a5c = 0.0f;
    ((VO0N*)o)->v2C();
    return o;
}
void fn_8022D404(void* s) {
    Node* a = (Node*)fn_801E5640(s, 0, 0);
    animY(s, a, 1.0f, 1);
    *(int*)((u8*)a + 0x70) = 0;
    fn_801E5734(s, a);
}
void fn_801E6B64(const char*, void*, f32, f32);
void fn_800453B4(void*, int);
extern char lbl_80390220[];
struct P30 { u8 p[0x30]; s16 x, y; };
struct P39 { u8 p[0x30]; s16 x, y; u8 p34[5]; u8 a39; };
int fn_80228DC4(void* a, P30* b, P39* c) {
    if (c->a39 == 2) {
        fn_801E6B64(lbl_80390220, b, b->x + c->x, b->y + c->y);
        return 0;
    }
    fn_800453B4(lbl_803CA870, 0x81);
    return 5;
}
extern char lbl_803901E4[], lbl_803901CC[], lbl_803901B4[];
struct E4 { int a; s8 a4; };
int fn_80228F8C(E4* e, P30* b, P39* c) {
    if (c->a39 == 2) {
        f32 x = b->x + c->x;
        f32 y = b->y + c->y;
        switch (e->a4) {
        case -1: fn_801E6B64(lbl_803901E4, b, x, y); break;
        case -2: fn_801E6B64(lbl_803901CC, b, x, y); break;
        case -3: fn_801E6B64(lbl_803901B4, b, x, y); break;
        }
        return 0;
    }
    fn_800453B4(lbl_803CA870, 0x80);
    return 5;
}
}
