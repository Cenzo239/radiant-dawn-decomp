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
#define FINI1(name, off) \
void name(Sm* s) { \
    fn_801E5734(s, fn_801E5640(s, -0x1000, 0)); \
    if (!inputBlocked() && (lbl_804CB5B8->v48() & 0xC00)) { \
        fn_801E5734(s, fn_801E5640(s, 0, 0)); \
        fn_8014C2AC(*(void**)(s->a88 + off)); \
        fn_80253EE4(lbl_80372600 + 0x52, 0.0f); \
        fn_80083B78(s); \
    } \
}
void fn_801051D8(int*, void*);
void fn_801E5D60(void*, void*, void*, int);
void fn_801E6120(void*, void*, void*, int);
struct RW { u8 p[0xa]; s16 x0, y0, x1, y1; u8 p12[0x16]; s16 a28; };
struct Roll { u8 p[0x28]; s16 a28; u8 p2a[6]; u8 a30; s8 a31; s8 a32; u8 p33[5]; u8* a38; };
void fn_801E59A8(void*, void*, void*, int);
extern char lbl_80390B28[];
extern char lbl_80390B14[];
extern char lbl_80390B00[];
void fn_802319E8(void);
struct LV { VO0N* v; };
void fn_8021A47C(void*, int, int);
void fn_8021B14C(void*, int);
extern char lbl_80390AE8[];
struct Ct { u8 p[0x30]; s8 a30; u8 a31, a32, a33, a34; u8 p35[3]; void* a38; void* a3c; };
#if TARGET_PC
FE10_PROTO ptr32<u8> fn_8021CD58(void*);
#else
u8* fn_8021CD58(void*);
#endif
void* fn_80081194(void*, void*);
extern u8 lbl_80390AB0[];
struct C4 { u8 a, b, c, d; C4& operator=(const C4& q) { a = q.a; b = q.b; c = q.c; d = q.d; return *this; } };
FINI1(fn_80233DB4, 0x54)
FINI1(fn_80233E7C, 0x5c)
void fn_80233F44(Sm* s) {
    fn_801E5734(s, fn_801E5640(s, -0x1000, 0));
    if (!inputBlocked() && (lbl_804CB5B8->v48() & 0xC00)) {
        fn_801E5734(s, fn_801E5640(s, 1, 0));
        fn_80253EE4(lbl_80372600 + 0x52, 0.0f);
        fn_80083B78(s);
    }
}
struct Sm70 { u8 p[0x70]; void* a70; };
void fn_80234000(Sm70* s) {
    int b;
    fn_801E5734(s, fn_801E5640(s, -0x1000, 0));
    b = lbl_804CB5B8->v48();
    if (!inputBlocked() && (b & 0xC00)) {
        fn_801E5734(s, s->a70);
        fn_80253EE4(lbl_80372600 + 0x52, 0.0f);
        fn_80083B78(s);
    }
}
#define FINI2(name, off) \
void name(Sm* s) { \
    fn_801E5734(s, fn_801E5640(s, -0x1000, 0)); \
    if (!inputBlocked() && (lbl_804CB5B8->v48() & 0xC00)) { \
        fn_801E5734(s, fn_801E5640(s, 6, 0)); \
        fn_8014C2AC(*(void**)(s->a88 + off)); \
        setHelpV(s, *(const char**)(s->a88 + 0x90)); \
        fn_80253EE4(lbl_80372600 + 0x52, 0.0f); \
        fn_80083B78(s); \
    } \
}
FINI2(fn_802340AC, 0x6c)
void fn_802341A0(Sm* s) {
    fn_801E5734(s, fn_801E5640(s, -0x1000, 0));
    if (!inputBlocked() && (lbl_804CB5B8->v48() & 0xC00)) {
        fn_801E5734(s, fn_801E5640(s, 6, 0));
        setHelpV(s, *(const char**)(s->a88 + 0x90));
        fn_80253EE4(lbl_80372600 + 0x52, 0.0f);
        fn_80083B78(s);
    }
}
FINI2(fn_80234288, 0x80)
void fn_8023437C(Sm* s) {
    fn_801E5734(s, fn_801E5640(s, -0x1000, 0));
    if (!inputBlocked() && (lbl_804CB5B8->v48() & 0xC00)) {
        fn_8014C2AC(*(void**)(s->a88 + 0x74));
        fn_80253EE4(lbl_80372600 + 0x52, 0.0f);
        setHelpV(s, *(const char**)(s->a88 + 0xa8));
        fn_80083B78(s);
    }
}
void fn_80230EDC(void* s) {
    WY* a = (WY*)fn_801E5640(s, 3, 0);
    WY* b = (WY*)fn_801E5640(s, 0xb, 0);
    mvx(s, a, 0x198, a->y, 0);
    mvx(s, b, 0x19d, b->y, 0);
    switch (lbl_803CA870[0xc]) {
    case 0x81:
        break;
    case 0x80:
        fn_80083DC4(s, 0x1c);
        break;
    }
}
struct WF { u8 p[0xa]; s16 x, y; u8 pe[0x1a]; s16 a28; };
void fn_80232590(void* s) {
    WF* a = (WF*)fn_801E5640(s, 0xd, 0);
    WF* b = (WF*)fn_801E5640(s, 0xe, 0);
    WF* c = (WF*)fn_801E5640(s, 3, 0);
    WF* d = (WF*)fn_801E5640(s, 0xb, 0);
    a->a28 = 8;
    mvx(s, (WY*)a, 0x14, a->y, 0);
    mvx(s, (WY*)b, -0x2c, b->y, 0);
    mvx(s, (WY*)c, 0x198, c->y, 0);
    mvx(s, (WY*)d, 0x19d, d->y, 0);
}
int fn_80060754(void*);
int* fn_801059B0(void);
int fn_80105158(int*);
int fn_8012BDFC(void*);
int fn_80232864(void* u, int n) {
    u8 t;
    int r;
    if (fn_80060754(lbl_803CAB38) != 0) {
        int* p = fn_801059B0();
        n -= *p - fn_80105158(p);
        if (n < 0) n = 0;
    }
    t = 7 - fn_8012BDFC(u);
    r = 0;
    if (t != 0 && n <= t) r = 1;
    return r;
}
void* fn_801E7A28(void*);
void fn_8012A0F4(void*, void*);
void fn_802338A0(void* s) {
    void* w = fn_801E5640(s, 8, 0);
    switch (lbl_803CA870[0xc]) {
    case 0x81:
        fn_8012A0F4(fn_801E7A28(fn_801E5640(s, 6, 0)), (u8*)s + 0x40);
        if (w != NULL) fn_801E5734(s, w);
        break;
    case 0x80:
        fn_80083DC4(s, 0x22);
        break;
    }
}
void* fn_80060728(void*);
#if TARGET_PC
FE10_PROTO void fn_801E7938(void*, p32arg);
#else
void fn_801E7938(void*, int);
#endif
struct S81 { u8 p[0x81]; u8 a81; };
void fn_802344EC(S81* s) {
    VO0N* a = (VO0N*)fn_801E5640(s, 6, 0);
    VO0N* b = (VO0N*)fn_801E5640(s, 7, 0);
    fn_801E7938(a, *(int*)((u8*)fn_80060728(lbl_803CAB38) + 0x28));
    ((VO0*)b)->v34((int)fn_801E7A28(a));
    fn_80083DC4(s, s->a81);
}
void fn_80110D38(void*);
void fn_8012A850(void*);
struct Ite { u32 id; u8 a4; u8 a5; u8 p[0x22]; };
int fn_80231968(u8* u, u32 id) {
    int r = 0;
    Ite* it = (Ite*)(u + 0x1bc);
    int i;
    for (i = 0; i < 7; i++, it++) {
        if (it == NULL) break;
        if (it->id == 0) break;
        if (!((it->a5 >> 5) & 1) && id == it->id) {
            fn_80110D38(it);
            fn_8012A850(u);
            r = 1;
            break;
        }
    }
    return r;
}
void fn_80231130(Roll* o) {
    u8* t = o->a38;
    int i;
    for (i = 0; i < 5; i++, t += 4) {
        RW* w = *(RW**)(t + 0x4c);
        if (i != o->a32) {
            XY p;
            w->a28 = 0x1e;
            p.x = 0xf0;
            p.y = 0;
            fn_801E59A8(o, w, &p, 0);
        }
    }
    fn_80253EE4(lbl_80390B14, 0.0f);
    o->a28 = 0x1e;
}
void fn_8021C278(void*, int, int, void*, int);
void fn_802311CC(Roll* o) {
    u8* t = o->a38;
    int i;
    for (i = 0; i < 5; i++, t += 4) {
        RW* w = *(RW**)(t + 0x4c);
        if (i != o->a32) {
            w->a28 = 0x1e;
            fn_8021C278(w, 0, 0x1e, o, 0);
        }
    }
    fn_80253EE4(lbl_80390B00, 0.0f);
    o->a28 = 0x1e;
}
}
