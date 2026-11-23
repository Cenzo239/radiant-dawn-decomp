/* AI: follow-the-leader action command, fn_8015A6B0. */
#include "game/rM_8014C9F8/ai.h"
struct AiCmd {
    int op;
    int a;
    int b;
    int c;
    int d;
    u32 fl;
    u32 x;
    u32 y;
    u32 z;
    u32 w;
};
struct F2 { void* vt; Unit* u; };
struct F3 { void* vt; Unit* u; u8 b; };
struct F4 { void* vt; Unit* u; u32 x; u8 k; };
struct F5 { void* vt; Unit* u; u32 x; u32 c; u8 k; };
static inline void F2Set(F2* f, void* vt, Unit* u) { f->u = u; f->vt = vt; }
static inline void F4Set(F4* f, void* vt, Unit* u, u32 x, u8 k) { f->u = u; f->vt = vt; f->x = x; f->k = k; }
static inline void F5Set(F5* f, void* vt, Unit* u, u32 x, u32 c, u8 k) { f->u = u; f->vt = vt; f->x = x; f->c = c; f->k = k; }
extern "C" {
extern u8 lbl_803872B8[], lbl_803872C8[], lbl_80387278[], lbl_80387268[], lbl_80387258[], lbl_80387288[];
extern AiCmd* lbl_804CB8B8;
#if TARGET_PC
FE10_PROTO extern p32ret lbl_804CB8B4;
#else
extern int lbl_804CB8B4;
#endif
extern int fn_80089C88(int);
extern void fn_80129550(Unit*, int);
extern int fn_80152C20(void*, void*, u8);
extern void fn_80129170(void*, void*);
extern void fn_80129160(void*);
#define W3C0(u) (*(Unit**)((u8*)(u) + 0x3C0))
#define W3C4(u) (*(Unit**)((u8*)(u) + 0x3C4))
#define B3CE(u) (*((u8*)(u) + 0x3CE))
#define B3CF(u) (*((u8*)(u) + 0x3CF))

void fn_8015A6B0(Unit* u) {
    
    Unit* l;
    AiCmd* c;
    
    F5 e2, e3, h2, h3;
    F4 e1;
    F3 f;
    F4 h1;
    F4 b2, b3;
    F2 g2, g3, g4, g1, b1;
    void* s;
    c = lbl_804CB8B8;
    lbl_804183F0.res[0] = 0;
    if (lbl_804183F0.res[0x86] == 0 && u == W3C0(u)) {
        if (fn_80089C88(100) < c->a) {
            F2Set(&b1, lbl_80387308, u);
            F4Set(&b3, lbl_803872C8, u, c->x, 3);
            F4Set(&b2, lbl_803872B8, u, c->x, 1);
            if (c->x == 0) {
                s = &b1;
            } else {
                s = &b3;
                if (c->fl & 1) {
                    s = &b2;
                }
            }
            F2Set(&g1, lbl_80387338, u);
            fn_80152C20(s, &g1, 0xF);
        }
        fn_80129550(u, lbl_804CB8B4);
        if (lbl_804183F0.done) {
            fn_80129170((u8*)u + 0x3C4, &lbl_803CA870);
            u->w3B4 |= 0x400000;
        } else {
            fn_80129160((u8*)u + 0x3C4);
        }
        return;
    }
    l = W3C0(u);
    if (l == 0) {
        lbl_804183F0.res[0] = 1;
    } else if (W3C4(l) == 0) {
        lbl_804183F0.res[0] = 9;
    } else if (W3C4(l)->flags10C & 8) {
        if (c->c > 0 && fn_80089C88(100) < c->a) {
            W3C4(u) = W3C4(l);
            B3CE(u) = B3CE(l);
            B3CF(u) = B3CF(l);
            F4Set(&e1, lbl_80387278, u, c->c, 1);
            F5Set(&e2, lbl_80387268, u, c->x, c->c, 3);
            F5Set(&e3, lbl_80387258, u, c->x, c->c, 1);
            if (c->x == 0) {
                s = &e1;
            } else {
                s = &e2;
                if (c->fl & 1) {
                    s = &e3;
                }
            }
            F2Set(&g2, lbl_80387338, u);
            if (fn_80152C20(s, &g2, 0xF) == 0) {
                lbl_804183F0.res[0] = 9;
            }
        } else {
            lbl_804183F0.res[0] = 9;
        }
    } else if (fn_80089C88(100) < c->a) {
        W3C4(u) = W3C4(l);
        B3CE(u) = B3CE(l);
        B3CF(u) = B3CF(l);
        f.u = u;
        f.vt = lbl_80387288;
        f.b = 1;
        g3.vt = lbl_80387338;
        g3.u = u;
        if (fn_80152C20(&f, &g3, 0xF) == 0) {
            if (c->c > 0) {
                F4Set(&h1, lbl_80387278, u, c->c, 1);
                F5Set(&h2, lbl_80387268, u, c->x, c->c, 3);
                F5Set(&h3, lbl_80387258, u, c->x, c->c, 1);
                if (c->x == 0) {
                    s = &h1;
                } else {
                    s = &h2;
                    if (c->fl & 1) {
                        s = &h3;
                    }
                }
                F2Set(&g4, lbl_80387338, u);
                if (fn_80152C20(s, &g4, 0xF) == 0) {
                    lbl_804183F0.res[0] = 9;
                }
            } else {
                lbl_804183F0.res[0] = 9;
            }
        }
    }
    fn_80129550(u, lbl_804CB8B4);
}
}
