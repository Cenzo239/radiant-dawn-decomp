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
int fn_801A2224(HelpWin*);
ItemProc* fn_80085EF8(u8);
u8 fn_80085ECC(ItemProc*);
f32 fn_8007E734();
void fn_8007E740(f32);
void fn_8007E7F4();
void fn_8007E154();
void fn_8007E164();
void fn_8007E174(void*, int);
void fn_8007E4E4(f32, f32, f32, f32);
void fn_8007E7DC(int);
void fn_800800D4(int);
void fn_80080388(f32, f32, f32, f32);
void fn_80080578(int);
void fn_80080940(Color, Color, Color, Color);
void fn_80080308();
void fn_801A1DCC(HelpWin*, const char*, f32, f32);
void fn_801A1F64(HelpWin*, const char*, f32, f32);
void fn_801A1AC4(HelpWin*, MenuProc*, const char*, f32, f32);
void fn_801A1BE0(HelpWin*, MenuProc*, const char*, f32, f32);
void fn_801A1CFC(HelpWin*);
void fn_80253EE4(const char*, f32);
void fn_80083B78(void*);
void fn_80083E90(u8*, void*);
void fn_80081A90(void*);
void* fn_80081050(u8*, void*);
MenuProc* fn_800811E4(u8*, void*);
void fn_800D5798(MenuProc*, MenuDef*);
void fn_80126D9C(void*, int);
void fn_800FAFF0(void*, int);

void fn_800D4528() {}
void fn_800D452C() {}
void fn_800D4530() {}
void fn_800D4534() {}

int fn_800D4538() { return fn_801A2224(&lbl_8041EB20) ? 0x40 : 9; }
int fn_800D4570() { return fn_801A2224(&lbl_8041EB20) ? 0x40 : 0x20; }

static inline BOOL ItemEq(ItemProc* a, ItemProc* b) {
    return a == b;
}

void fn_800D45A8(MenuDef*, MenuProc* p) {
    if (p->vis) {
        p->def->v10();
        {
            f32 z = fn_8007E734();
            ItemProc* it;
            int i;
            for (i = 0; i < p->n; i++) {
                it = fn_80085EF8(p->items[i]);
                it->sel = ItemEq(it, fn_80085EF8(p->items[p->cur]));
                it->item->v2C(p, it);
                fn_8007E740(z);
            }
            if (p->state == 0 && p->cur >= 0) {
                p->def->v30(p);
            }
            fn_8007E7F4();
        }
    }
}

static inline BOOL Paused(MenuProc* p) {
    return p->lockCnt || p->pause;
}

#pragma use_lmw_stmw off
void fn_800D46B8(MenuDef*, MenuProc* p) {
    fn_8007E154();
    fn_8007E4E4(p->x, p->y, p->def->v70(), 1.0f);
    fn_8007E174(0, 0x12);
    if (Paused(p)) {
        fn_8007E7DC(0x28);
    }
    fn_8007E164();
    fn_800800D4(3);
    fn_80080388(0.0f, 0.0f, p->w, p->h);
    fn_80080578(0);
    fn_80080940(k0a, k0b, k0c, k0d);
    fn_80080308();
}
#pragma use_lmw_stmw on

static inline ItemProc* Cur(MenuProc* p) { return fn_80085EF8(p->items[p->cur]); }

void fn_800D4864(MenuDef*, MenuProc* p);

void fn_800D4A10(MenuDef* m, MenuProc* p) {
    u32 rep = lbl_804CB5B8->v3C();
    u32 held = lbl_804CB5B8->v48();
    p->prev = p->cur;
    if (rep & 0x800008) {
        if (p->prev == 0) {
            if (held != rep) {
                return;
            }
            p->cur = p->n;
        }
        p->cur--;
    }
    if (rep & 0x400004) {
        if (p->cur == p->n - 1) {
            if (held != rep) {
                return;
            }
            p->cur = -1;
        }
        p->cur++;
    }
    if (p->cur != p->prev) {
        {
            ItemProc* it = fn_80085EF8(p->items[p->prev]);
            it->item->v48(p, it);
        }
        {
            ItemProc* it = Cur(p);
            it->item->v44(p, it);
        }
        if (fn_801A2224(&lbl_8041EB20)) {
            f32 x = p->x + Cur(p)->x;
            f32 y = p->y + Cur(p)->y;
            const char* s = Cur(p)->item->v1C(Cur(p));
            if (s) {
                fn_801A1DCC(&lbl_8041EB20, s, x, y);
            } else {
                ItemProc* it = Cur(p);
                fn_801A1F64(&lbl_8041EB20, it->item->v4C(it), x, y);
            }
        }
        if (m->v88()) {
            fn_80253EE4(m->v88(), 0.0f);
        }
    }
}

void fn_800D4CF0(MenuDef*, MenuProc* p) {
    if (lbl_804CB5B8->v34() & 0x300003) {
        ItemProc* it = Cur(p);
        it->item->v3C(p, it);
    }
}

void fn_800D4D68(MenuDef* m, MenuProc* p) {
    if (lbl_804CB5B8->v48() & 0xC0000C) {
        p->cur = 0;
        if (m->v88()) {
            fn_80253EE4(m->v88(), 0.0f);
        }
    }
}

u8 fn_800D4DFC(MenuDef*, MenuProc* p) {
    u32 b = lbl_804CB5B8->v48();
    ItemProc* it = Cur(p);
    if ((b & 0x400) && fn_801A2224(&lbl_8041EB20) == 0) {
        return it->item->v30(p, it);
    }
    if (b & 0x800) {
        return p->def->v20(p, it);
    }
    if (b & 0x1000) {
        return it->item->v34(p, it);
    }
    if (b & 0x2000) {
        return p->def->v24(p, it);
    }
    if (b & 0x10) {
        u8 r = it->item->v38(p, it);
        u8 r2 = p->def->v28(p, it);
        return r2 | r;
    }
    if (b & 0x4000) {
        return p->def->v2C(p, it);
    }
    return it->item->v40(p, it);
}

void fn_800D4FAC(MenuProc* p) {
    MenuDef* m = p->def;
    u8 r = 0;
    if (!(lbl_804CB700 & 0x80)) {
        if (p->cur < 0) {
            m->v3C(p);
            return;
        }
        m->v34(p);
        p->def->v38(p);
        r = p->def->v40(p);
        if (p->layer != 0x7B) {
            lbl_804CB728 = r;
        }
    }
    if (r & 4) {
        if (m->v7C()) {
            fn_80253EE4(m->v7C(), 0.0f);
        }
    }
    if (r & 8) {
        if (m->v80()) {
            fn_80253EE4(m->v80(), 0.0f);
        }
    }
    if (r & 0x10) {
        if (m->v84()) {
            fn_80253EE4(m->v84(), 0.0f);
        }
    }
    if (r & 1) {
        fn_80083B78(p);
        {
            ItemProc* it = Cur(p);
            it->item->v48(p, it);
        }
        if (m->v78()) {
            fn_80253EE4(m->v78(), 0.0f);
        }
        return;
    }
    if (r & 2) {
        if (m->v78()) {
            fn_80253EE4(m->v78(), 0.0f);
        }
        while (p && *(u8**)p == lbl_80383ED0) {
            fn_80083B78(p);
            if (p->flags & 4) {
                p->flags &= ~4;
                p->parent->lockCnt--;
            }
            p = p->parent;
        }
        return;
    }
    if (r & 0x20) {
        f32 x = p->x + Cur(p)->x;
        f32 y = p->y + Cur(p)->y;
        const char* s = Cur(p)->item->v1C(Cur(p));
        if (s) {
            fn_801A1AC4(&lbl_8041EB20, p, s, x, y);
        } else {
            ItemProc* it = Cur(p);
            fn_801A1BE0(&lbl_8041EB20, p, it->item->v4C(it), x, y);
        }
        lbl_8041EB20.flags |= 2;
    } else if (r & 0x40) {
        fn_801A1CFC(&lbl_8041EB20);
    }
}

void fn_800D53C4(MenuProc* p) { p->def->v18(p); }
int fn_800D53DC(MenuProc* p) { return p->def->v8C(p); }
void fn_800D53F4(MenuProc* p) { p->state = 0; }

void fn_800D5400(MenuProc* p) {
    p->state = 2;
    p->sleep = p->def->v6C();
}

static inline int MenuH(MenuDef* m, s8 n) {
    return m->v5C() * n + m->v4C();
}

MenuProc* fn_800D5448(MenuDef* m, void* parent, int layer);

int fn_800D5684() { return 0; }
int fn_800D568C(MenuItem* i) { return i->v24(); }

MenuProc* fn_800D569C(MenuProc* p) {
    MenuProc* cur = p;
    MenuProc* q = p->parent;
    while (q) {
        if (*(u32*)q != *(u32*)p) {
            return cur;
        }
        if (q == 0) {
            return cur;
        }
        cur = q;
        q = q->parent;
    }
    return 0;
}

void fn_800D56E8(MenuProc* p) {
    int i;
    for (i = 0; i < p->n; i++) {
        fn_80081A90(fn_80085EF8(p->items[i]));
    }
    fn_800D5798(p, p->def);
    {
        ItemProc* it = Cur(p);
        it->item->v44(p, it);
    }
    p->def->v1C(p);
}

void fn_800D5798(MenuProc* p, MenuDef* m);

f32 fn_800D58FC(MenuProc* p) {
    int t = p->sleep + 1;
    switch (p->state) {
    case 0:
        return 1.0f;
    case 1: {
        int d = p->def->v68() + 1;
        return 1.0f / d * (d - t);
    }
    case 2: {
        int d = p->def->v6C() + 1;
        return 1.0f / d * t;
    }
    }
    return 0.0f;
}

void fn_800D5A04() { lbl_804CB72C++; }

s16 fn_800D5A14() {
    lbl_804CB72C = 0;
    fn_80083E90(lbl_80383ED0, fn_800D5A04);
    return (lbl_804CB72C - 1) * 8 + 0x80;
}

s16 fn_800D5A60() {
    lbl_804CB72C = 0;
    fn_80083E90(lbl_80383ED0, fn_800D5A04);
    return (lbl_804CB72C - 1) * 0x10 + 0x20;
}

void fn_800D5AAC(void* p) { fn_80083B78(p); }
void fn_800D5AB0() { fn_80083E90(lbl_80383ED0, fn_800D5AAC); }

void fn_800D5AC4() {}
int fn_800D5AC8() { return 0; }
int fn_800D5AD0() { return 0; }
void fn_800D5AD8() {}
void fn_800D5ADC() {}
int fn_800D5AE0() { return 1; }
int fn_800D5AE8() { return 0x10; }

struct Sel {
    u8* unit;
    u8 pad4[2];
    s16 x6;
};

void fn_800D5AF0(Sel* s) {
    void* a = s->unit ? *(void**)(s->unit + 0x3F0) : 0;
    if (a) {
        fn_80126D9C(a, s->x6);
    }
}

void fn_800D5B20(Sel* s) {
    void* a = s->unit ? *(void**)(s->unit + 0x3F0) : 0;
    if (a) {
        fn_800FAFF0(a, 0);
    }
}
}
