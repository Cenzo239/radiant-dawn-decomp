#include "game/rI_801DD7D4/types.h"
#include "game/rI_801DD7D4/vobj.h"
#pragma auto_inline off

extern "C" {

extern char lbl_803711E8[];
extern char lbl_803CAB38[];
extern u8 lbl_803CA870[];
extern VO0N* lbl_804CB5B8;
typedef struct Pt { s16 x, y; } Pt;
typedef struct W {
    u8 pad[8];
    u8 x8[2];
    s16 xa, xc;
    u8 paxe[0x30 - 0xe];
    f32 x30, x34;
    u8 pad38[4];
    struct W* x3c;
    u8 pad40[0x4e - 0x40];
    u8 x4e;
    u8 pad4f[0x64-0x4f];
    const char* x64;
    u8 x68;
} W;
typedef struct Msgs {
    u8 pad[0xc];
    int xc;
    int x10, x14;
    u8 pad18[0x28-0x18];
    int x28, x2c;
    u8 pad30[8];
    int x38;
    u8 pad3c[8];
    int x44, x48;
    u8 pad4c[0x6c-0x4c];
    const char* x6c;
    u8 pad70[0x7c-0x70];
    const char* x7c;
} Msgs;
class RO {
public:
    virtual void destroy(int);
    int rc;
};
typedef struct Sc {
    u8 pad[0x4c];
    W* x4c;
    W* x50;
    W* x54;
    RO* x58;
    u8 pad5c[2];
    u8 x5e;
    u8 pad5f;
    u8 pad60[4];
    Msgs* x64;
    void* x68;
} Sc;

typedef struct K { u8 pad[8]; s16 x8, xa; u8 pad_c[0x24-0xc]; u8 x24; } K;
K* fn_801E041C(const char*, const char*);
void fn_800D5448(void*, void*, int);
W* fn_801E5640(void*, int, int);
void fn_801E5448(void*, void*);
void fn_801E5734(void*, void*);
void fn_801E459C(void*, void*, void*, int);
void fn_801E495C(void*, void*, void*, int);
void fn_801E4D1C(void*, void*, int);
void fn_801E4F50(void*, void*, int);
void fn_801E518C(void*, void*, int, f32);
f32 fn_801E33B4(W*);
f32 fn_801E3468(W*);
#if TARGET_PC
FE10_PROTO void fn_8014C2AC(p32arg);
#else
void fn_8014C2AC(int);
#endif
void fn_80083DC4(void*, int);
void fn_80083B78(void*);
void fn_800D3C30(void*, int);
void fn_80253EE4(const char*, f32);
void* fn_80060728(void*);
#if TARGET_PC
FE10_PROTO void fn_801E7938(void*, p32arg);
#else
void fn_801E7938(void*, int);
#endif
#if TARGET_PC
FE10_PROTO p32ret fn_801E7A28(void*);
#else
int fn_801E7A28(void*);
#endif

#define setHelp(o, e) { \
    const char* s = e; \
    W* p = fn_801E5640(o, -0x1000, 0); \
    if (p != NULL) { \
        p->x64 = s; \
    } \
}

#define ASK(fn, a, b) \
void fn(Sc* o) { \
    K* w = fn_801E041C(a, b); \
    w->x8 = 0x180; \
    w->xa = 0x1b; \
    w->x24 = 1; \
    fn_800D5448(w, o, 0); \
    setHelp(o, o->x64->x6c); \
}
static inline void ask2(Sc* o, const char* base) {
    K* w = fn_801E041C(base + 0xa2, base + 0xaa);
    w->x8 = 0x180;
    w->xa = 0x1b;
    w->x24 = 1;
    fn_800D5448(w, o, 0);
    setHelp(o, o->x64->x6c);
}
void fn_80208264(Sc* o) { ask2(o, lbl_803711E8); }
void fn_80208A84(Sc* o) { ask2(o, lbl_803711E8); }
void fn_8020D81C(Sc* o) { ask2(o, lbl_803711E8); }
void fn_8020E03C(Sc* o) { ask2(o, lbl_803711E8); }
ASK(fn_80209DAC, NULL, NULL)
ASK(fn_8020A448, NULL, NULL)
ASK(fn_8020F364, NULL, NULL)
ASK(fn_8020FA00, NULL, NULL)

#define ensure(w, id, f) \
    w = fn_801E5640(o, id, 0); \
    if (w == NULL) { \
        w = f; \
        fn_801E5448(o, w); \
    }
static inline void mvA(Sc* o, W* w, s16 x, s16 y) {
    Pt p;
    p.x = x;
    p.y = y;
    fn_801E459C(o, w, &p, 0);
}
static inline f32 scale30(W* w) {
    f32 f0 = w->x30;
    W* p0 = w->x3c;
    if (p0 != NULL) {
        W* p1 = p0->x3c;
        f32 f1 = p0->x30;
        if (p1 != NULL) {
            W* p2 = p1->x3c;
            f32 f2 = p1->x30;
            if (p2 != NULL) {
                W* p3 = p2->x3c;
                f32 f3 = p2->x30;
                if (p3 != NULL) {
                    f3 = f3 * fn_801E33B4(p3);
                }
                f2 = f2 * f3;
            }
            f1 = f1 * f2;
        }
        f0 = f0 * f1;
    }
    return f0;
}
#define SHOW(fn) \
void fn(Sc* o) { \
    W* w; \
    ensure(w, 0, o->x4c); \
    if (w->xa != 0xe0) { \
        s16 y = w->xc; \
        Pt p; \
        p.x = 0xe0; \
        p.y = y; \
        fn_801E459C(o, w, &p, 0); \
    } \
    ensure(w, 1, o->x54); \
    if (w->xa != 0x14e) { \
        s16 y = w->xc; \
        Pt p; \
        p.x = 0x14e; \
        p.y = y; \
        fn_801E459C(o, w, &p, 0); \
    } \
    ensure(w, 2, o->x50); \
    if (1.0f != scale30(w)) { \
        fn_801E4D1C(o, w, 0); \
    } \
}

#define STEP5(fn) \
void fn(Sc* o) { \
    switch (lbl_803CA870[0xc]) { \
    case 0x81: \
        fn_8014C2AC(o->x64->x28); \
        break; \
    case 0x80: \
        if (o->x58 != NULL) { \
            RO* r = o->x58; \
            if (--r->rc == 0) { \
                if (r != NULL) { \
                    r->destroy(1); \
                } \
            } \
            o->x58 = NULL; \
        } \
        fn_801E5734(o, fn_801E5640(o, 0, 0)); \
        fn_8014C2AC(o->x64->xc); \
        setHelp(o, o->x64->x7c); \
        fn_80083DC4(o, 5); \
        break; \
    } \
}
STEP5(fn_80208B08)
STEP5(fn_8020E0C0)

#define HIDE(fn) \
void fn(Sc* o) { \
    W* w; \
    { \
        W* a = o->x4c; \
        s16 y = a->xc; \
        Pt p; \
        p.x = 0x134; \
        p.y = y; \
        fn_801E495C(o, a, &p, 0); \
    } \
    w = fn_801E5640(o, 1, 0); \
    { \
        s16 y = w->xc; \
        Pt q; \
        q.x = 0x1a2; \
        q.y = y; \
        fn_801E495C(o, w, &q, 0); \
    } \
    fn_801E4F50(o, o->x50, 0); \
    fn_800D3C30(o->x68, 0xc); \
}
HIDE(fn_80208C00)
HIDE(fn_8020E1B8)

static inline f32 scale34(W* w) {
    f32 f0 = w->x34;
    W* p0 = w->x3c;
    if (p0 != NULL) {
        W* p1 = p0->x3c;
        f32 f1 = p0->x34;
        if (p1 != NULL) {
            W* p2 = p1->x3c;
            f32 f2 = p1->x34;
            if (p2 != NULL) {
                W* p3 = p2->x3c;
                f32 f3 = p2->x34;
                if (p3 != NULL) {
                    f3 = f3 * fn_801E3468(p3);
                }
                f2 = f2 * f3;
            }
            f1 = f1 * f2;
        }
        f0 = f0 * f1;
    }
    return f0;
}
#define S34(fn) \
void fn(Sc* o) { \
    W* w = fn_801E5640(o, 3, 0); \
    if (0.5f != scale34(w)) { \
        fn_801E518C(o, w, 1, 0.5f); \
    } \
    w = fn_801E5640(o, 4, 0); \
    w->x68 = 1; \
    w->x4e = 0; \
    fn_801E4F50(o, fn_801E5640(o, 7, 0), 0); \
    fn_8014C2AC(o->x64->x2c); \
}
S34(fn_80209C70)
S34(fn_8020F228)
#define S34B(fn) \
void fn(Sc* o) { \
    W* w = fn_801E5640(o, 3, 0); \
    if (0.5f != scale34(w)) { \
        fn_801E518C(o, w, 1, 0.5f); \
    } \
    w = fn_801E5640(o, 4, 0); \
    w->x68 = 0; \
    fn_801E4F50(o, fn_801E5640(o, 7, 0), 0); \
    fn_8014C2AC(o->x64->x48); \
}
S34B(fn_8020A314)
S34B(fn_8020F8CC)

#define BACK(fn) \
void fn(Sc* o) { \
    fn_801E5734(o, fn_801E5640(o, -0x1000, 0)); \
    if (inputBlocked()) { \
        return; \
    } \
    if (lbl_804CB5B8->v48() & 0xc00) { \
        switch (o->x5e) { \
        case 4: \
            fn_801E5734(o, o->x4c); \
            fn_8014C2AC(o->x64->x38); \
            break; \
        case 8: \
            fn_801E5734(o, fn_801E5640(o, 7, 0)); \
            fn_8014C2AC(o->x64->x14); \
            break; \
        } \
        fn_80253EE4(lbl_803711E8 + 0xb5, 0.0f); \
        fn_80083DC4(o, o->x5e); \
    } \
}
BACK(fn_8020AC0C)
BACK(fn_802101C4)

void fn_8020AD10(Sc* o) {
    fn_801E5734(o, fn_801E5640(o, -0x1000, 0));
    if (inputBlocked()) {
        return;
    }
    if (lbl_804CB5B8->v48() & 0xc00) {
        fn_801E5734(o, fn_801E5640(o, 3, 0));
        fn_8014C2AC(o->x64->x44);
        fn_80253EE4(lbl_803711E8 + 0xb5, 0.0f);
        fn_80083B78(o);
    }
}

void fn_8020ADD8(Sc* o) {
    fn_801E5734(o, fn_801E5640(o, -0x1000, 0));
    if (inputBlocked()) {
        return;
    }
    if (lbl_804CB5B8->v48() & 0xc00) {
        fn_801E5734(o, fn_801E5640(o, 3, 0));
        fn_80253EE4(lbl_803711E8 + 0xb5, 0.0f);
        fn_80083B78(o);
    }
}

void fn_8020B03C(Sc* o) {
    W* a = fn_801E5640(o, 3, 0);
    VO0* b = (VO0*)fn_801E5640(o, 4, 0);
    fn_801E7938(a, *(int*)((u8*)fn_80060728(lbl_803CAB38) + 0x24));
    b->v34(fn_801E7A28(a));
}

void fn_8020B1C8(Sc* o) {
    if (inputBlocked()) {
        return;
    }
    if (lbl_804CB5B8->v48() & 0xc00) {
        fn_80253EE4(lbl_803711E8 + 0xb5, 0.0f);
        fn_80083B78(o);
    }
}

}
