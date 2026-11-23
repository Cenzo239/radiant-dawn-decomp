/* Save and load of the global game data (lbl_803CAB38). The save version is at +0xC of fn_8024BCA0()'s result. */
#include "game/rC2_8005259C/types.h"
class SaveObj {
public:
    virtual void v08(void* s);
    virtual void v0C(void* s);
};
struct OldData { u8 pad[0x300]; u8 bits[0xc]; };
struct SavePair { s8 a; s8 b; };
struct SaveData {
    u8 h0[0x10];
    u8 b10, b11;
    u16 h12;
    u8 c14[4];
    u8 a18[0xc];
    u8 a24[0xc];
    u8 a30[0x24];
    u8 a54[0x3c];
    u8 b90, b91, b92;
    u8 p93;
    u16 h94, h96, h98;
    u8 b9a, b9b, b9c, b9d, b9e, b9f;
    u64 ta0, ta8;
    u32 wb0, wb4;
    u16 hb8, hba;
    int wbc;
    u16 hc0, hc2, hc4, hc6;
    u32 wc8, wcc, wd0, wd4;
    SaveObj od8;
    u8 pdc[0x10];
    SaveObj oec;
    u8 pf0[0x10];
    SaveObj o100;
    u8 p104[0x30];
    u8 a134[8];
    u8 a13c[0x408];
    u8 bits[0x10];
    u8 a554[0x3c0];
    u8 a914[0x20];
    f32 x934, y938;
    u8 p93c[0x18];
    u8 n954;
    SavePair pairs[1];
};
extern "C" {
void fn_8008A780(void* s, int n, void* p);
#if TARGET_PC
FE10_PROTO void fn_8008A6CC(void* s, int n, ptr32<const void>);
#else
void fn_8008A6CC(void* s, int n, void* p);
#endif
void fn_8008A5AC(void* s, u8 v);
void fn_8008A5C0(void* s, u16 v);
void fn_8008A5E4(void* s, u32 v);
void fn_8008A628(void* s, u64 v);
#if TARGET_PC
FE10_PROTO void fn_8010E890(void* p, ptr32<const void>);
#else
void fn_8010E890(void* p, void* s);
#endif
void fn_8008A43C(void* s, int n, void* p);
u8 fn_8008A1A0(void* s);
u16 fn_8008A1B4(void* s);
u32 fn_8008A1DC(void* s);
u64 fn_8008A22C(void* s);
f32 fn_8008A31C(void* s);
u16 fn_80089ED0(void);
void* fn_8024BCA0(void);
void fn_8017F44C(void* p, int v, int n);
void fn_800615DC(SaveData* g, u32 v);
void fn_80061808(SaveData* g, f32 v);
void fn_800601E4(void* p, void* s);
#if TARGET_PC
FE10_PROTO void fn_8010E914(void* p, ptr32<const void>);
#else
void fn_8010E914(void* p, void* s);
#endif
}

extern "C" void fn_80062AE8(SaveData* g, void* s) {
    s8 n;
    SaveData* q;
    int i;
    s8 j;
    fn_8008A780(s, 0x10, g);
    fn_8008A5AC(s, g->b10);
    fn_8008A5AC(s, g->b11);
    fn_8008A5C0(s, g->h12);
    for (i = 0; i < 4; i++) {
        fn_8008A5AC(s, g->c14[i]);
    }
    fn_8008A780(s, 0xc, g->a18);
    fn_8008A780(s, 0xc, g->a24);
    fn_8008A780(s, 0x24, g->a30);
    fn_8008A780(s, 0x3c, g->a54);
    fn_8008A5AC(s, g->b90);
    fn_8008A5AC(s, g->b91);
    fn_8008A5AC(s, g->b92);
    fn_8008A780(s, 6, &g->h94);
    fn_8008A5AC(s, (u8)(int)g->x934);
    fn_8008A5AC(s, (u8)(int)g->y938);
    fn_8008A5AC(s, g->b9c);
    fn_8008A5AC(s, g->b9d);
    fn_8008A5AC(s, g->b9e);
    fn_8008A5AC(s, g->b9f);
    fn_8008A628(s, g->ta0);
    fn_8008A628(s, g->ta8);
    fn_8008A5E4(s, g->wb0);
    fn_8008A5E4(s, g->wb4);
    fn_8008A5C0(s, g->hb8);
    fn_8008A5C0(s, g->hba);
    fn_8008A5E4(s, g->wbc);
    fn_8008A5C0(s, g->hc0);
    fn_8008A5C0(s, g->hc2);
    fn_8008A5C0(s, g->hc4);
    fn_8008A5C0(s, g->hc6);
    fn_8008A5E4(s, g->wc8);
    fn_8008A5E4(s, g->wcc);
    fn_8008A5E4(s, g->wd0);
    fn_8008A5E4(s, g->wd4);
    g->od8.v08(s);
    g->oec.v08(s);
    fn_8010E890(g->a134, s);
    fn_8010E890(g->a13c, s);
    fn_8008A780(s, 0x10, g->bits);
    fn_8008A780(s, 0x3c0, g->a554);
    fn_8008A6CC(s, 0x18, g->a914);
    {
        n = (s8)g->n954;
        fn_8008A5AC(s, n);
        q = g;
        for (j = 0; j < n; j++) {
            fn_8008A5AC(s, q->pairs[0].a);
            fn_8008A5AC(s, q->pairs[0].b);
            q = (SaveData*)((u8*)q + 2);
        }
    }
    g->o100.v08(s);
}

static inline int oldBit(OldData* o, int i) {
    if (i < 0 || i >= 0x60) {
        return 0;
    }
    return (o->bits[i >> 3] & (1 << (i & 7))) != 0;
}
static inline void setBit(SaveData* g, int i) {
    if (i >= 0 && i < 0x80) {
        if (i >= 0 && i < 0x80) {
            g->bits[i >> 3] |= 1 << (i & 7);
        }
    }
}
static inline void clearBit(SaveData* g, int i) {
    if (i >= 0 && i < 0x80) {
        g->bits[i >> 3] &= ~(1 << (i & 7));
    }
}

#pragma use_lmw_stmw on
extern "C" void fn_80062DE0(SaveData* g, void* s) {
    OldData old;
    u32* v = (u32*)fn_8024BCA0();
    int i;
    fn_8008A43C(s, 0x10, g);
    g->b10 = fn_8008A1A0(s);
    g->b11 = fn_8008A1A0(s);
    g->h12 = fn_8008A1B4(s);
    for (i = 0; i < 4; i++) {
        g->c14[i] = fn_8008A1A0(s);
    }
    if (v[3] < 0xc) {
        fn_8017F44C(g->a18, 0, 0xc);
        fn_8017F44C(g->a24, 0, 0xc);
        fn_800615DC(g, fn_8008A1DC(s));
        fn_80061808(g, fn_8008A31C(s));
    } else {
        fn_8008A43C(s, 0xc, g->a18);
        fn_8008A43C(s, 0xc, g->a24);
    }
    if (v[3] < 0xe) {
        int k;
        for (k = 0; k < 8; k++) {
            ((u8(*)[0xc])g->a30)[k][0] = 0;
        }
        fn_8008A43C(s, 0x24, g->a30);
        fn_8008A43C(s, 0x24, g->a54);
    } else {
        fn_8008A43C(s, 0x24, g->a30);
        fn_8008A43C(s, 0x3c, g->a54);
    }
    g->b90 = fn_8008A1A0(s);
    g->b91 = fn_8008A1A0(s);
    g->b92 = fn_8008A1A0(s);
    if (v[3] < 9) {
        g->h94 = fn_80089ED0();
        g->h96 = fn_80089ED0();
        g->h98 = fn_80089ED0();
    } else {
        fn_8008A43C(s, 6, &g->h94);
    }
    g->b9a = fn_8008A1A0(s);
    g->b9b = fn_8008A1A0(s);
    g->b9c = fn_8008A1A0(s);
    g->b9d = fn_8008A1A0(s);
    g->b9e = fn_8008A1A0(s);
    g->b9f = fn_8008A1A0(s);
    g->ta0 = fn_8008A22C(s);
    g->ta8 = fn_8008A22C(s);
    g->wb0 = fn_8008A1DC(s);
    g->wb4 = fn_8008A1DC(s);
    g->hb8 = fn_8008A1B4(s);
    g->hba = fn_8008A1B4(s);
    if (v[3] < 0x10) {
        g->wbc = (s16)fn_8008A1B4(s);
    } else {
        g->wbc = fn_8008A1DC(s);
    }
    g->hc0 = fn_8008A1B4(s);
    g->hc2 = fn_8008A1B4(s);
    g->hc4 = fn_8008A1B4(s);
    g->hc6 = fn_8008A1B4(s);
    g->wc8 = fn_8008A1DC(s);
    g->wcc = fn_8008A1DC(s);
    g->wd0 = fn_8008A1DC(s);
    g->wd4 = fn_8008A1DC(s);
    g->od8.v0C(s);
    g->oec.v0C(s);
    fn_8010E914(g->a134, s);
    fn_8010E914(g->a13c, s);
    if (v[3] < 0xf) {
        fn_8008A43C(s, 0xc, old.bits);
        for (i = 0; i < 0x80; i++) {
            clearBit(g, i);
        }
        for (i = 0; i < 0x16; i++) {
            if (oldBit(&old, i)) {
                setBit(g, i);
            }
        }
        for (i = 0x5f; i >= 0x16; i--) {
            int k = i + 0x20;
            if (oldBit(&old, i)) {
                setBit(g, k);
            }
        }
    } else {
        fn_8008A43C(s, 0x10, g->bits);
    }
    fn_800601E4(g->a554, s);
    fn_8008A43C(s, 0x18, g->a914);
    {
        s8 n = fn_8008A1A0(s);
        s8 a;
        s8 j;
        g->n954 = 0;
        for (j = 0; j < n; j++) {
            a = fn_8008A1A0(s);
            s8 b = fn_8008A1A0(s);
            g->pairs[(s8)g->n954].a = a;
            g->pairs[(s8)g->n954].b = b;
            g->n954++;
        }
    }
    g->o100.v0C(s);
}
#pragma use_lmw_stmw off
