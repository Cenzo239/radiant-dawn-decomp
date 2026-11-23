/* NEAR MISS: fn_80054378, 14 of 73 words, better than wip/fn_80054378.cpp. With a u8 unitAt only u and v swap (want u r25, v r26), plus r5/r6 at the cell store. */
/* NEAR MISS: 20 of 73 words, all register numbers. The original keeps the unit in r25 and the
 * index in r30; hill-climbing the declarations did not reach that. */
#include "game/rC2_8005259C/more.h"
#pragma use_lmw_stmw on
extern "C" {
void fn_800E24F8(const char* s);
void fn_800C7B18(const char* s, int n);
int fn_8005449C(void* u);
int fn_80089C88(int n);
typedef struct Cell { s8 x; s8 y; u8 fc; u8 p3; int a4; int a8; } Cell;
Cell* fn_800CFBFC(Word* w);
void fn_8005474C(void);
}
extern u8 lbl_8037DD88[];
extern s8 lbl_804CB460; extern void* lbl_804CB464; extern u8 lbl_8037EDC0[];
extern s8 lbl_804CB468; extern void* lbl_804CB46C; extern u8 lbl_8037ED68[];
extern s8 lbl_804CB470; extern void* lbl_804CB474; extern u8 lbl_8037ED10[];
extern s8 lbl_804CB478; extern void* lbl_804CB47C; extern u8 lbl_8037ECB8[];
extern s8 lbl_804CB480; extern Lazy2 lbl_804CB488; extern u8 lbl_8037E184[]; extern u8 lbl_8037F200[];
typedef struct U7 { u8 pad[0xec]; void* ec; u8 padf0[4]; UnitSub* f4; u8 padf8[4]; u8 fc; u8 padfd[5]; s8 x; s8 y; u8 pad104[8]; u32 flags; u16 h110 : 3; } U7;
static inline void setCell(Cell* c, s8 x, s8 y, u8 fc, int a, int b) { c->x = x; c->y = y; c->fc = fc; c->a4 = a; c->a8 = b; }
static inline U7* unitAt(u8 id) { if (id) return (U7*)((u8*)lbl_804CB810 + (id - 1) * 0x3f0); return 0; }
extern "C" int fn_80054378(void* parent) {
    u8 buf[24];
        s8 v;
    int i;
    Cell* c;
    U7* u;

    fn_800CFB34(&lbl_803E7320);
    fn_8010E41C(buf, 0);
    for (i = 1; i <= 0xfe; i++) {
        u = unitAt(i);
        if (u->ec == 0) continue;
        if (!buf[u->f4->b8]) continue;
        if (u->flags & 4) continue;
        fn_8005449C(u);
        if (!u->h110) continue;
        v = fn_80089C88(3) + 1;
        c = fn_800CFBFC(&lbl_803E7320);
        setCell(c, u->x, u->y, u->fc, 3, -v);
    }
    fn_8005474C();
    if (lbl_803E7320.i0 == 0) {
        return 0;
    }
    fn_80081194(lbl_8037DD88, parent);
    return 1;
}
