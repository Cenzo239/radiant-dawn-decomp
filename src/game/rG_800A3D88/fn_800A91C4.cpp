#include "game/rG_800A3D88/chr.h"
extern "C" {
struct ES { u8 p[0x30]; u8 m30; };
struct BC { u8 p[0x30]; ES* m30; u8 p34[8]; Chr* e[2]; u8 p44[9]; u8 m4d; u8 m4e; u8 m4f; int m50; };
struct GS { u8 p[0x30]; BC* m30; };
void fn_800A9A74(BC*);
int fn_800BD280(Chr*);
void fn_800BA2C8(Chr*);
void* fn_8028C1A0(f32);
void fn_800BE340(Chr*);
void fn_800BE2BC(Chr*);
void fn_80010788(int, int, void*, void*);
void fn_800AA360(u8);
void fn_800AA400();
void fn_80176A34(int);
f32 fn_800A84A4(const char*);
extern char lbl_803653B8[];
static inline Chr* At(BC* b, int i) { if (i < 0) return NULL; return b->e[i]; }
#pragma use_lmw_stmw on
static inline Chr* AtQ(BC* q, int i) { if (i < 0) return NULL; return q->e[0]; }
#define ADV(q) (q = (BC*)((u8*)q + 4))
void fn_800A91C4(GS* g) {
    int n2;
    int i3;
    int i4;
    int i5;
    int i2;
    int i1;
    void* p;
    int n3;
    BC* q2;
    BC* b3;
    BC* b2;
    BC* b1;
    BC* q4;

    fn_800A9A74(g->m30);
    b1 = g->m30;
    if (b1->m30 != NULL && b1->m30->m30 != 0) {
        for (i1 = 0; i1 < 2; i1++, ADV(b1)) {
            if (fn_800BD280(AtQ(b1, i1))) fn_800BA2C8(AtQ(b1, i1));
        }
    }
    b2 = g->m30;
    n2 = 0;
    for (q2 = b2, i2 = 0; i2 < 2; i2++, ADV(q2)) {
        if (fn_800BD280(AtQ(q2, i2))) n2++;
    }
    if (n2 != 0 && b2->m4e != 0) {
        p = fn_8028C1A0(fn_800A84A4(lbl_803653B8));
        if (p != NULL) {
            for (i3 = 0; i3 < 2; i3++, ADV(b2)) fn_800BE340(AtQ(b2, i3));
            fn_80010788(2, 0x88, fn_800AA360, p);
        }
    }
    b3 = g->m30;
    if (b3->m4d != 0) {
        q4 = b3;
        n3 = 0;
        for (i4 = 0; i4 < 2; i4++, ADV(q4)) {
            if (fn_800BD280(AtQ(q4, i4))) n3++;
        }
        if (n3 != 0) {
            fn_80010788(3, 0x87, fn_800AA400, b3);
            for (i5 = 0; i5 < 2; i5++, ADV(b3)) fn_800BE2BC(AtQ(b3, i5));
            fn_80176A34(0x87);
        }
    }
}
}
