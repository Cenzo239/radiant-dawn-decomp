#include "game/rP_80105B04/rp.h"
/* Unit-side lists (lbl_804CB814): 11 {head, tail, n} with +8 the side index. */
struct LUnit {
    u8 pad[0xE4];
    LUnit* prev;
    LUnit* next;
    void* person;
    u8 padF0[4];
    struct SideL* side;
    u8 padF8[0x108 - 0xF8];
    u64 flags;
    u8 pad110[0x3F0 - 0x110];
};
struct SideL { LUnit* head; LUnit* tail; u8 idx; };
struct Mode { u32 w; };
extern "C" {
extern char lbl_80368054[];
extern char lbl_803EC318[];
extern LUnit* lbl_804CB810;
extern u8 lbl_803CAB38[];
extern int lbl_804CA4C0;
extern int lbl_804CA4C4;
void* fn_8017F37C(const char* a, void* b, const char* c);
u32 fn_8023F9F4(const void* path);
void fn_80075FB4(void* p, int k);
void fn_800763E0(void* p);
char* strcpy(char* a, const char* b);
char* fn_80291110(char* a, const char* b);
void* fn_80076F54(const char* s);
void fn_801223E0(LUnit* u, SideL* l);
Mode* fn_80060728(void* g);
void* memset(void* p, int v, u32 n);

static inline void Load1(void* a, const char* c) {
    void* p = fn_8017F37C(lbl_80368054 + 0x3F, a, c);
    if (fn_8023F9F4(p) != 0x40000) fn_80075FB4(p, 0x40);
}
static inline void Free1(void* a, const char* c) {
    void* p = fn_8017F37C(lbl_80368054 + 0x3F, a, c);
    if (fn_8023F9F4(p) != 0x40000) fn_800763E0(p);
}
void fn_8010DB48(void* a) {
    Load1(a, lbl_80368054 + 0x45);
    Load1(a, lbl_80368054 + 0x51);
    Load1(a, lbl_80368054 + 0x5F);
    Load1(a, lbl_80368054 + 0x6D);
}
void fn_8010DC58(void* a) {
    Free1(a, lbl_80368054 + 0x6D);
    Free1(a, lbl_80368054 + 0x5F);
    Free1(a, lbl_80368054 + 0x51);
    Free1(a, lbl_80368054 + 0x45);
}
void* fn_8010DD58(void* a, int k) {
    switch (k) {
    case 3: return fn_8017F37C(lbl_80368054 + 0x3F, a, lbl_80368054 + 0x5F);
    case 0: return fn_8017F37C(lbl_80368054 + 0x3F, a, lbl_80368054 + 0x5F);
    case 1: return fn_8017F37C(lbl_80368054 + 0x3F, a, lbl_80368054 + 0x6D);
    case 2: return fn_8017F37C(lbl_80368054 + 0x3F, a, lbl_80368054 + 0x6D);
    case 4: return fn_8017F37C(lbl_80368054 + 0x3F, a, lbl_80368054 + 0x51);
    default: return fn_8017F37C(lbl_80368054 + 0x3F, a, lbl_80368054 + 0x45);
    }
}
char* fn_8010DE10(const char* a, int k) {
    strcpy(lbl_803EC318, a);
    switch (k) {
    case 3: fn_80291110(lbl_803EC318, lbl_80368054 + 0x7B); break;
    case 0: fn_80291110(lbl_803EC318, lbl_80368054 + 0x7B); break;
    case 1: fn_80291110(lbl_803EC318, lbl_80368054 + 0x7E); break;
    case 2: fn_80291110(lbl_803EC318, lbl_80368054 + 0x7E); break;
    case 4: fn_80291110(lbl_803EC318, lbl_80368054 + 0x81); break;
    }
    if (fn_80076F54(lbl_803EC318) == 0) lbl_803EC318[0] = 0;
    return lbl_803EC318;
}
static inline LUnit* UnitGet(int id) {
    u8 k = id;
    if (k) return lbl_804CB810 + (k - 1);
    return 0;
}
void fn_8010E054(SideL* l, LUnit* u);
static inline u8 Rel(u32 a, u32 b) {
    if (a == b) return 0;
    if ((fn_80060728(lbl_803CAB38)->w & 3) == 2) return 1;
    if (a == 1 || b == 1) return 1;
    return 2;
}
u8 fn_8010E314(u32 a, u32 b);
void fn_8010E41C(u8* t, int mode) {
    u8 side;
    memset(t, (u8)lbl_804CA4C0, 0xB);
    side = lbl_803CAB38[0x11];
    switch (mode) {
    case 0:
        t[side] = 1;
        break;
    case 1:
        if (Rel(side, 0) == 1) t[0] = 1;
        if (Rel(side, 1) == 1) t[1] = 1;
        if (Rel(side, 2) == 1) t[2] = 1;
        if (Rel(side, 3) == 1) t[3] = 1;
        break;
    case 2:
        if (Rel(side, 0) != 1) t[0] = 1;
        if (Rel(side, 1) != 1) t[1] = 1;
        if (Rel(side, 2) != 1) t[2] = 1;
        if (Rel(side, 3) != 1) t[3] = 1;
        break;
    case 3:
        t[0] = 1;
        t[1] = 1;
        t[2] = 1;
        t[3] = 1;
        break;
    case 4:
        t[0] = 1;
        t[5] = 1;
        break;
    case 5:
        memset(t, (u8)lbl_804CA4C4, 0xB);
        break;
    }
}

static inline void SideEnter(SideL* l, LUnit* u) {
    fn_801223E0(u, l);
    switch (l->idx) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        u->flags &= ~0x18ULL;
        break;
    case 5:
        u->flags |= 0x18ULL;
        u->flags &= ~8ULL;
        break;
    case 6:
        u->flags |= 8ULL;
        break;
    case 7:
    case 8:
    case 9:
    case 10:
        u->flags |= 0x18ULL;
        u->flags &= ~8ULL;
        break;
    }
}
void fn_8010E054(SideL* l, LUnit* u) {
    SideEnter(l, u);
    LUnit* h = l->head;
    if (h == 0) {
        l->head = u;
        l->tail = u;
    } else {
        h->prev = u;
        u->next = h;
        l->head = u;
    }
}
void fn_8010E168(SideL* l, LUnit* u) {
    SideEnter(l, u);
    LUnit* h = l->tail;
    if (h == 0) {
        l->head = u;
        l->tail = u;
    } else {
        h->next = u;
        u->prev = h;
        l->tail = u;
    }
}
void fn_8010DF24(SideL* l) {
    int i;
    l->head = 0;
    l->tail = 0;
    for (i = 1; i < 0xFF; i++) {
        LUnit* u = UnitGet(i);
        if (l->idx == u->side->idx && (u->prev || u->next)) {
            if (u->prev == 0) l->head = u;
            else if (u->next == 0) l->tail = u;
            if (l->head && l->tail) return;
        }
    }
}
extern "C" int fn_8011996C(void* a, void* b, int k);
void fn_8010E770(SideL* l) {
    LUnit* u;
    LUnit* v;
    for (u = l->head; u; u = u->next) {
        if (u->person) {
            for (v = l->head; v; v = v->next) {
                if (u != v) fn_8011996C(u, v, 0);
            }
        }
    }
}
struct RelS { u8 pad[4]; u8 a; u8 b; s8 c; s8 d; };
void fn_8010E7F4(RelS* r, int k) {
    switch (fn_80060728(lbl_803CAB38)->w & 3) {
    case 0:
    case 1:
        r->b = k;
        r->a = k == 3;
        r->c = -1;
        r->d = -1;
        break;
    case 2:
    default:
        r->b = k;
        r->a = 0;
        r->c = -1;
        r->d = -1;
        break;
    }
}
}
