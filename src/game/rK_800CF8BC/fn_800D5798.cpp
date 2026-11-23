/* Menu item list build, split from fn_800D4528.cpp. The inline wrapper exists only to rank the parameters below the locals. */
#include "game/rK_800CF8BC/menu.h"

#pragma use_lmw_stmw on

struct Color {
    u8 r, g, b, a;
};

struct HelpWin {
    u32 flags;
    u8 pad4[0x100];
};
extern HelpWin lbl_8041EB20;
extern u8 lbl_80383ED0[];
extern u8 lbl_80383F10[];
extern u32 lbl_804CB700;
extern u8 lbl_804CB728;
extern int lbl_804CB72C;

static const Color k0a = {0, 0, 0, 0xFF};
static const Color k0b = {0, 0, 0, 0x40};
static const Color k0c = {0, 0, 0, 0xFF};
static const Color k0d = {0, 0, 0, 0x40};
static const Color k1a = {0xC8, 0, 0, 0xFF};
static const Color k1b = {0xC8, 0, 0, 0xFF};

extern "C" {
ItemProc* fn_80085EF8(u8);
u8 fn_80085ECC(ItemProc*);
void* fn_80081050(u8*, void*);
void fn_800D5798(MenuProc*, MenuDef*);

static inline BOOL ItemEq(ItemProc* a, ItemProc* b) {
    return a == b;
}

static inline BOOL Paused(MenuProc* p) {
    return p->lockCnt || p->pause;
}

#pragma use_lmw_stmw off

#pragma use_lmw_stmw on

static inline ItemProc* Cur(MenuProc* p) { return fn_80085EF8(p->items[p->cur]); }

static inline int MenuH(MenuDef* m, s8 n) {
    return m->v5C() * n + m->v4C();
}

void fn_800D5798(MenuProc* p, MenuDef* m);

struct Sel {
    u8* unit;
    u8 pad4[2];
    s16 x6;
};

static inline void fn_800D5798_i(MenuProc* p, MenuDef* m) {

    int i;
    int y;
    y = 0;
    i = 0;
    p->n = y;
    p->cur = -1;
    for (;;) {
        MenuItem* it = m->v44(i);
        int st;
        if (it == 0) {
            break;
        }
        st = it->v28(it, i);
        if ((u8)st != 3) {
            ItemProc* q;
            if ((u8)st == 1) {
                if (p->cur < 0) {
                    p->cur = p->n;
                }
                st = 0;
            }
            q = (ItemProc*)fn_80081050(lbl_80383F10, p);
            q->item = it;
            q->idx = i;
            q->vis = p->n;
            q->state = st;
            q->x = m->v48();
            q->y = y + m->v4C();
            q->o3C = 0;
            y += m->v5C();
            p->items[p->n++] = fn_80085ECC(q);
        }
        i++;
    }
    if (p->cur < 0) {
        p->cur = 0;
    }
}
void fn_800D5798(MenuProc* p, MenuDef* m) { fn_800D5798_i(p, m); }



}
