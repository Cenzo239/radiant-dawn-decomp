#include "game/rT_80026898/types.h"
#pragma use_lmw_stmw on
extern "C" {
extern GameState lbl_803CAB38;
extern u8 lbl_803EC898[];
extern Unit** lbl_804CB814;
extern u8* lbl_804CB810;
extern u8 lbl_80379F58[];
void fn_80083DC4(void*, int);
int fn_8011799C(void*, int, int);
Unit* fn_8012D2B0(u8);
Unit* fn_8012D280(u8);
void fn_800620A8(f32, f32, void*);
u32* fn_80060728(void*);
void* fn_80081194(void*, void*);
void* fn_80081050(void*, void*);
void fn_800CD4A4(int);
void fn_8010E41C(char*, int);
void fn_80122460(Unit*);
struct Group { Unit* head; u8 pad[8]; };

static inline Unit* unitAt(u8 id) {
    return id ? (Unit*)(lbl_804CB810 + (id - 1) * 0x3f0) : 0;
}

void fn_80042C84(void) {
    u8 m[0x10];
    int i;
    Unit* u;
    fn_8010E41C((char*)m, 0);
    for (i = 1; i <= 0xfe; i++) {
        u = unitAt(i);
        if (u->ec && m[u->f4[8]]) {
            {u64 mm = ~0ULL; FLAGS(u) &= mm;}
            fn_80122460(u);
        }
    }
}

void fn_80043214(void* p) {
    Unit* u = ((Group*)lbl_804CB814)[lbl_803CAB38.side].head;
    while (u) {
        Unit* n = u->next;
        if (fn_8011799C(lbl_803EC898, u->x102, (s8)*(u8*)&u->y103)) return;
        u = n;
    }
    fn_80083DC4(p, 5);
}

void fn_8004333C(void) {
    if (lbl_803CAB38.side == 0 && !((*fn_80060728(&lbl_803CAB38) >> 14) & 1) && lbl_803CAB38.sideOn[lbl_803CAB38.side]) {
        Unit* u = fn_8012D2B0(lbl_803CAB38.side);
        if (u == 0) u = fn_8012D280(lbl_803CAB38.side);
        if (u && (u->f10c & 0x10000DC) == 0) {
            fn_800620A8(u->x102, u->y103, &lbl_803CAB38);
        }
    }
}

struct Scripts { u8 a[0x34]; u8 b[0x1c]; u8 c[0x10]; };
}
