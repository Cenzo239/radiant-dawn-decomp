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
struct Node { u8 pad[0x2c]; f32 x2c, x30, x34; u8 pad38[4]; Node* parent; };
f32 fn_801E33B4(Node*);
#define animY(s, a, k) { \
    f32 v3; f32 v2; f32 v1; f32 v0; Node* p; Node* q; Node* r; Node* o; \
    v0 = a->x30; p = a->parent; \
    if (p) { v1 = p->x30; q = p->parent; if (q) { v2 = q->x30; r = q->parent; if (r) { v3 = r->x30; o = r->parent; if (o) { v3 *= fn_801E33B4(o); } v2 *= v3; } v1 *= v2; } v0 *= v1; } \
    if (k != v0) fn_801E4D1C(s, a, 0); \
}
struct SM { u8 p[0x40]; u8 a40[0x28]; void* a68; void* a6c; void* a70; void* a74; void* a78; u8 p7c[8]; f32 a84; u8* a88; };
static inline void mv(void* s, WY* w, s16 x, s16 y, int f) { XY p; p.x = x; p.y = y; fn_801E459C(s, w, &p, f); }
#if TARGET_PC
FE10_PROTO ptr32<void> fn_802172F8(void*);
#else
void* fn_802172F8(void*);
#endif
void* fn_802167C8(void*, int, int, int, int, int, int);
void fn_80111B34(void*);
extern u8 lbl_8038F9A0[];
extern u8 lbl_8038F8D0[];
struct LW { void* vt; int rc; s16 id; u8 p[0x1e]; s16 a28; };
void fn_8022E7A0(SM* s) {
    WY* a = (WY*)fn_801E5640(s, 0, 0);
    if (a == NULL) {
        a = (WY*)s->a68;
        fn_801E5448(s, a);
    }
    if (a->x != 0xe0) mv(s, a, 0xe0, a->y, 0);
    {
        WY* b = (WY*)fn_801E5640(s, 4, 0);
        if (b == NULL) {
            b = (WY*)s->a78;
            fn_801E5448(s, b);
        }
        if (b->x != 0x14e) mv(s, b, 0x14e, b->y, 0);
        *(int*)((u8*)b + 0x44) = -1;
    }
    {
        Node* c = (Node*)fn_801E5640(s, 5, 0);
        if (c == NULL) {
            c = (Node*)s->a74;
            fn_801E5448(s, c);
        }
        animY(s, c, 1.0f);
    }
    fn_801E5734(s, a);
    setHelpV(s, *(const char**)(s->a88 + 0x8c));
}
void fn_8022E9A0(SM* s) {
    WY* a = (WY*)fn_801E5640(s, 0, 0);
    if (a == NULL) {
        a = (WY*)s->a68;
        fn_801E5448(s, a);
    }
    if (a->x != 0xe0) mv(s, a, 0xe0, a->y, 0);
    ((V38*)a)->v38(0);
    {
        WY* b = (WY*)fn_801E5640(s, 4, 0);
        if (b == NULL) {
            b = (WY*)s->a78;
            fn_801E5448(s, b);
        }
        if (b->x != 0x14e) mv(s, b, 0x14e, b->y, 0);
        *(int*)((u8*)b + 0x44) = -1;
    }
    {
        Node* c = (Node*)fn_801E5640(s, 5, 0);
        if (c == NULL) {
            c = (Node*)s->a74;
            fn_801E5448(s, c);
        }
        animY(s, c, 1.0f);
    }
    fn_801E5734(s, a);
    setHelpV(s, *(const char**)(s->a88 + 0x8c));
}
void* fn_80217ABC(void*);
void fn_80110BB4(void*, void*);
int fn_80111074(void*);
void fn_8022F064(SM* s) {
    WY* a = (WY*)fn_801E5640(s, 1, 0);
    if (a == NULL) {
        a = (WY*)s->a6c;
        fn_801E5448(s, a);
    }
    if (a->x != 0xe0) mv(s, a, 0xe0, a->y, 1);
    {
        void* it = fn_80217ABC(a);
        u8* w = (u8*)fn_801E5640(s, 4, 0);
        if (it != NULL) {
            fn_80110BB4(s->a40, it);
            *(int*)(w + 0x44) = s->a84 * (f32)fn_80111074(s->a40);
        }
    }
    fn_801E5734(s, a);
    fn_8014C2AC(*(void**)(s->a88 + 0x10));
    setHelpV(s, *(const char**)(s->a88 + 0x8c));
}
void fn_8022FC44(SM* s) {
    WY* a = (WY*)fn_801E5640(s, 2, 0);
    if (a == NULL) {
        a = (WY*)s->a70;
        fn_801E5448(s, a);
    }
    if (a->x != 0xe0) mv(s, a, 0xe0, a->y, 0);
    fn_801E5734(s, a);
    fn_8014C2AC(*(void**)(s->a88 + 0x18));
    setHelpV(s, *(const char**)(s->a88 + 0x98));
}
void fn_800615DC(void*, int);
int fn_800626E0(void*);
void fn_80230410(SM* s) {
    int n;
    V38* l = (V38*)s->a70;
    WY* a = (WY*)fn_801E5640(s, 3, 0);
    switch (lbl_803CA870[0xc]) {
    case 0x81:
        fn_8014C2AC(*(void**)(s->a88 + 0x20));
        setHelpV(s, *(const char**)(s->a88 + 0xa4));
        {
            n = *(int*)((u8*)fn_801E5640(s, 4, 0) + 0x44);
            fn_800615DC(lbl_803CAB38, fn_800626E0(lbl_803CAB38) - n);
        }
        l->v38(0);
        break;
    case 0x80:
        mvx(s, a, 0x198, a->y, 0);
        fn_80083DC4(s, 0xe);
        break;
    }
}
#if TARGET_PC
FE10_PROTO p32ret fn_8010B228(const char*);
#else
int fn_8010B228(const char*);
#endif
int fn_801E733C(int);
void fn_802305AC(void* s) {
    WY* a = (WY*)fn_801E5640(s, 3, 0);
    WY* b = (WY*)fn_801E5640(s, 4, 0);
    if (fn_801E733C(fn_8010B228(lbl_80372600 + 0x62)) > 0) {
        fn_80083DC4(s, 0x11);
    } else {
        mvx(s, a, 0x198, a->y, 0);
        fn_80083DC4(s, 0x1c);
    }
    mvx(s, b, 0x1a2, b->y, 0);
}
void fn_8021A434(void*, void*);
void fn_800D0AE4(int, int);
void fn_80230288(SM* s) {
    u8* n = (u8*)fn_801E5640(s, 4, 0);
    u8* o = (u8*)fn_80079150(0x8c);
    if (o != NULL) {
        fn_802167C8(o, 0x198, 0x66, 0x104, 0xda, 0x1e0, 1);
        *(void**)o = lbl_8038F8D0;
        o[0x74] = 0;
        *(int*)(o + 0x88) = 0;
        ((VO0N*)o)->v2C();
    }
    ((LW*)o)->id = 3;
    ((LW*)o)->a28 = 8;
    fn_8021A434(o, *(void**)((u8*)s->a70 + 0x70));
    fn_801E5448(s, o);
    mv(s, (WY*)o, 0x144, ((WY*)o)->y, 1);
    fn_800D0AE4(0, *(int*)(n + 0x44));
    fn_8014C2AC(*(void**)(s->a88 + 0x1c));
}
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
extern u8 lbl_8038F898[];
extern char lbl_80390B4C[];
struct G1 { WF w; s8 a40; int a44; u8 a48; };
void fn_80230688(SM* s) {
    G1* o = (G1*)fn_80079150(0x50);
    if (o != NULL) {
        wfInit(&o->w, 0x19d, 0x13c, 0x293, 0x19c, 0xf6, 0x60, 0x1c2, 0x10);
        o->w.vt = lbl_8038F898;
        o->a40 = -1;
        o->a44 = fn_8010B228(lbl_80390B4C);
        o->a48 = 0;
        ((VO0N*)o)->v2C();
    }
    o->w.id = 0xb;
    o->w.a28 = 8;
    o->a40 = 1;
    fn_801E5448(s, o);
    setHelpV(s, *(const char**)(s->a88 + 0xa4));
}
}
