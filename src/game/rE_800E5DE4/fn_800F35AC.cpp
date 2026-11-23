#include "game/rE_800E5DE4/types.h"
struct Nd { u32 a, b, c, d; };
struct Pl { Nd* pool; Nd** st; Nd** top; Nd* xc; Nd* x10; int x14; int n; };
struct UD { u8 pad8[8]; u8 x8; };
struct Un {
    u16 x0;
    u16 x2;
    u8 pad4[0x1c - 4];
    f32 x1c, x20, x24;
    u8 pad28[0xc4 - 0x28];
    u16 xc4;
    u8 xc6;
    u8 padc7[0xd8 - 0xc7];
    s8 xd8, xd9;
    s16 xda;
    u32 xdc, xe0;
    u8 pade4[0xec - 0xe4];
    void* xec;
    u8 padf0[4];
    UD* xf4;
    u8 padf8[0x3f0 - 0xf8];
};
extern char lbl_80367BA4[];
#if TARGET_PC
FE10_PROTO extern void *lbl_804CB730;
#else
extern u32 lbl_804CB730;
#endif
extern Pl* lbl_804CB748;
#if TARGET_PC
FE10_PROTO extern void *lbl_804CB734, *lbl_804CB738;
#else
extern u32 lbl_804CB734, lbl_804CB738;
#endif
extern char lbl_804CA4BC[4], lbl_804CA4B8[4], lbl_804CA4B4[4];
extern u8 lbl_804CB73C, lbl_804CB73D, lbl_804CB73E, lbl_804CB73F, lbl_804CB740, lbl_804CB741, lbl_804CB742, lbl_804CA4AC;
extern Un* lbl_804CB810;
extern "C" {
#if TARGET_PC
FE10_PROTO p32ret fn_8001D3B4(const char*);
#else
u32 fn_8001D3B4(const char*);
#endif
void* fn_80078CCC(int, const char*, int);
void DCFlushRange(void*, u32);
int fn_8030585C(int, int, int, int, int);
#if TARGET_PC
FE10_PROTO p32ret fn_80079940(int, int);
#else
u32 fn_80079940(int, int);
#endif
void fn_8010E41C(u8*, int);
static inline Un* UAt(u8 id) { return id ? &lbl_804CB810[id - 1] : 0; }
void fn_800F35AC(void) {
    /*P*/
    int i;
    int z;
    int z2;
    int o1;
    int o2;
    Pl* p;
    int j;
    Un* u;
/*E*/
    u8 mask[0x10];
    lbl_804CB730 = fn_8001D3B4(lbl_80367BA4);
    p = (Pl*)fn_80078CCC(0x1c, lbl_804CA4BC, 0);
    if (p) {
        p->pool = 0;
        p->st = 0;
        p->top = 0;
        p->x14 = 0;
        p->xc = 0;
        p->x10 = 0;
    }
    lbl_804CB748 = p;
    p->n = 0x40;
    p->pool = (Nd*)fn_80078CCC(0x400, lbl_804CA4B8, 0);
    p->st = (Nd**)fn_80078CCC(0x104, lbl_804CA4B4, 0);
    DCFlushRange(p->pool, 0x400);
    DCFlushRange(p->st, 0x104);
    z2 = 0;
    p->x14 = z2;
    i = 0;
    o1 = 0;
    o2 = 0;
    for (; i < p->n; i++) {
        Nd* q = (Nd*)((u8*)p->pool + o1);
        q->a = z2;
        q->b = z2;
        *(Nd**)((u8*)p->st + o2) = (Nd*)((u8*)p->pool + o1);
        o1 += 0x10; o2 += 4;
    }
    z = 0;
    p->top = p->st;
    p->st[p->n] = 0;
    p->xc = 0;
    p->x10 = 0;
    lbl_804CB734 = fn_80079940(fn_8030585C(0x260, 0x1c0, 0x27, 0, 0), 0x40);
    lbl_804CB738 = fn_80079940(fn_8030585C(0x98, 0x70, 0, 0, 0), 0x40);
    fn_8010E41C(mask, 5);
    for (j = 1; j < 0xff; j++) {
        u = UAt(j);
        if (u->xec && mask[u->xf4->x8]) {
            u->xc4 = z;
            u->xc6 = 0x64;
            u->x2 = z;
            u->xda = -1;
            u->xd9 = -1;
            u->xd8 = -1;
            u->x1c = 0.0f;
            u->x20 = 0.0f;
            u->x24 = 0.0f;
            u->xe0 = z;
            u->x0 = z;
            u->x0 |= 0x3c0;
            u->xdc = z;
        }
    }
    lbl_804CB73C = 1;
    lbl_804CB73E = 1;
    lbl_804CB73D = 1;
    lbl_804CB73F = 1;
    lbl_804CB740 = 0;
    lbl_804CB741 = 0xff;
    lbl_804CB742 = 0;
    lbl_804CA4AC = 0x64;
}
}
