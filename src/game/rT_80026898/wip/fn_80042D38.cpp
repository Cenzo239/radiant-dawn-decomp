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
void fn_80044530(void* a) {
    Scripts* b = (Scripts*)lbl_80379F58;
    fn_80081194(b->b, fn_80081050(b->a, fn_80081194(b->c, a)));
    fn_800CD4A4(0x13);
}

#pragma use_lmw_stmw off
void fn_80102E10(Unit*, int, int, f32, int);
void fn_80114D00(void*);
void fn_80042D38(void) {
    u8 m1[0xC];
    u8 m0[0xC];
    u8* t;
    int o;
    int n;
    Unit* h;
    Unit* w;
    int s;
    int i;
    Unit* u;
    int i2;
    Unit* u2;
    s = 0;
    t = (u8*)&lbl_803CAB38;
    o = 0;
    for (; s < 4; s++, t++, o += 0xC) {
        if (t[0x14] && ((fn_80060728(&lbl_803CAB38)[1] >> 28) & 3) == 2) {
            n = 0;
            h = *(Unit**)((u8*)lbl_804CB814 + o);
            for (w = h; w;) {
                u32 f = w->f10c;
                w = w->next;
                if ((f & 1) == 0) n++;
            }
            if (n == 0) {
                while (h) { Unit* nx = h->next; FLAGS(h) &= ~1ULL; h = nx; }
            }
        }
    }
    fn_8010E41C((char*)m1, 3);
    for (i = 1; i <= 0xfe; i++) {
        u = unitAt(i);
        if (u->ec && m1[u->f4[8]]) {
            if (((fn_80060728(&lbl_803CAB38)[1] >> 28) & 3) != 2) FLAGS(u) &= ~1ULL;
            if (!((*fn_80060728(&lbl_803CAB38) >> 12) & 1) && fn_8011799C(lbl_803EC898, u->x102, u->y103)) {
                fn_80102E10(u, 0x10, 0, 0.0f, 0);
            }
            FLAGS(u) &= ~0x800ULL;
        }
    }
    fn_8010E41C((char*)m0, 0);
    for (i2 = 1; i2 <= 0xfe; i2++) {
        u2 = unitAt(i2);
        if (u2->ec && m0[u2->f4[8]]) {
            u8 d = *((u8*)u2 + 0x379);
            if ((s8)d < 0) d = *((u8*)u2->ec + 0xE3);
            u2->f37c += d;
            {u64 mm = ~0ULL; FLAGS(u2) &= mm;}
        }
    }
    fn_80114D00(lbl_803EC898);
}
}
