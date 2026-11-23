/* Chapter clear records: 0x3c entries of 16 bytes. */
#include "game/rC2_8005259C/base.h"
struct Rec { u8 b0, b1; u16 h2; u32 w4; s16 h8; s16 ha; int wc; };
struct OldRec { u8 b0, b1; u16 h2; u32 w4; s16 h8; s16 ha; };
struct Ver { u8 pad[0xc]; u32 v; };
struct UX { u8 pad[0xec]; struct UE* ec; };
struct UE { u8 pad[0x1c]; u16 h1c; };
struct GS { u8 pad[0x10]; u8 b10; u8 p11; u16 h12; u8 p14[0x94]; u64 ta8; u8 pb0[0xc]; int wbc; };
struct RE { u8 pad[0x1c]; s16 h1c; };
extern "C" {
extern void* lbl_804CBFC8;
extern GS lbl_803CAB38;
Ver* fn_8024BCA0(void);
void fn_8008A43C(void*, int, void*);
void* fn_80244470(void*, u16);
RE* fn_8010B1D8(void*);
UX* fn_80062914(GS*);
u64 fn_8028C418(u64, u64); /* __div2u */
}
#define BUS_CLOCK (*(u32*)0x800000F8)
static inline int firstFree(Rec* e) {
    int i;
    for (i = 0; i < 0x3c; e++, i++) {
        if (e->h2 == 0) {
            return i;
        }
    }
    return -1;
}

#pragma use_lmw_stmw on
extern "C" void fn_800601E4(Rec* t, void* s) {
    OldRec o;
    Rec* e;
    Ver* v = fn_8024BCA0();
    int i;
    if (v->v < 0xc) {
        int h = 1;
        int z = 0;
        for (i = 0; i < 0x3c; i++) {
            fn_8008A43C(s, 8, t);
            t->h8 = h;
            t->ha = z;
            t->wc = z;
            t++;
        }
        return;
    }
    if (v->v < 0x10) {
        int j;
        e = t;
        for (j = 0; j < 0x3c; j++) {
            fn_8008A43C(s, 0x10, &o);
            e->b0 = o.b0;
            e->b1 = o.b1;
            e->h2 = o.h2;
            e->w4 = o.w4;
            e->h8 = o.h8;
            e->wc = o.ha;
            e++;
        }
    } else {
        fn_8008A43C(s, 0x3c0, t);
    }
    if (v->v < 0x11) {
        for (i = 0x3b; i > 0; i--) {
            t[i].w4 -= t[i - 1].w4;
        }
    }
    {
        void* x = lbl_804CBFC8;
        int k;
        if (x) {
            for (k = 0; k < 0x3c; k++) {
                if (t->h8 != 0) {
                    t->h8 = fn_8010B1D8(fn_80244470(x, t->h8))->h1c;
                }
                t++;
            }
        }
    }
}
#pragma use_lmw_stmw off

extern "C" int fn_8006041C(Rec* e) {
    int i;
    for (i = 0; i < 0x3c; e++, i++) {
        if (e->h2 == 0) {
            return i;
        }
    }
    return -1;
}

extern "C" void fn_80060580(Rec* t, u8 k) {
    int i = firstFree(t);
    UX* v = fn_80062914(&lbl_803CAB38);
    t[i].b0 = lbl_803CAB38.b10;
    t[i].b1 = k;
    t[i].h2 = lbl_803CAB38.h12;
    t[i].w4 = fn_8028C418(lbl_803CAB38.ta8, BUS_CLOCK / 4);
    t[i].h8 = v ? v->ec->h1c : 0;
    t[i].wc = lbl_803CAB38.wbc;
}
