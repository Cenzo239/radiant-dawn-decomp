/* Menu create, split from fn_800D4528.cpp. */
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
void fn_80253EE4(const char*, f32);
MenuProc* fn_800811E4(u8*, void*);
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

static inline int MenuH(MenuDef* m, u8 n) {
    return m->v5C() * (s8)n + m->v4C(); //M
}

void fn_800D5798(MenuProc* p, MenuDef* m);

struct Sel {
    u8* unit;
    u8 pad4[2];
    s16 x6;
};

MenuProc* fn_800D5448(MenuDef* m, void* parent, int layer) {
    MenuProc* p = fn_800811E4(lbl_80383ED0, parent);
    if (layer) {
        p->layer = layer;
    }
    fn_800D5798(p, m);
    p->def = m;
    p->x = m->v60();
    p->y = m->v64();
    p->w = m->v50();
    if ((s16)m->v54() != 0) {
        p->h = m->v54();
    } else {
p->h = MenuH(m, p->n);
    }
    p->prev = p->cur;
    p->a38 = -1;
    p->curY = -1;
    p->vis = 1;
    m->v14(p);
    m->v1C(p);
    {
        ItemProc* it = Cur(p);
        Cur(p)->item->v44(p, it);
    }
    p->sleep = m->v68();
    p->state = 1;
    if (m->v74()) {
        fn_80253EE4(m->v74(), 0.0f);
    }
    if (m->v0C()) {
        p->cur = -1;
    }
    return p;
}
}
