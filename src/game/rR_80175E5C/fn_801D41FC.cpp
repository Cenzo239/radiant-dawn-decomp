/* Title menu items: each draws a help text or opens its screen. */
#include "game/rR_80175E5C/menu.h"

#define F(p, t, o) (*(t*)((u8*)(p) + (o)))

extern "C" {
extern volatile u32 lbl_804CB700;
extern Pad* lbl_804CB5B8;
extern u8 lbl_8041EB20[];
extern u8 lbl_8038B160[];
extern u8 lbl_8038C028[], lbl_8038BFE8[], lbl_8038BFBC[], lbl_8038BF90[], lbl_8038BF64[], lbl_8038BF2C[];
extern u8 lbl_8038BEF0[], lbl_8038BEC0[], lbl_8038BE88[];
void fn_801E6B64(void*, void*, f32, f32);
void* fn_80083B84(void*);
void fn_80083DC4(void*, int);
void* fn_800CD204(int);
void fn_80080508(Color);
void fn_80080ABC(int, f32);
ItemProc* fn_80085EF8(u8);
int fn_801A2224(void*);

static inline BOOL inputBlocked(void) {
    u32 f1 = lbl_804CB700;
    u32 f2 = lbl_804CB700;
    BOOL b = 0;
    if ((f1 & 0x10) && !(f2 & 0x20)) {
        b = 1;
    }
    return b;
}

#define HELPITEM(name, tbl, sc) \
int name(void*, MenuProc* m, ItemProc* it) { \
    if (it->state == 2) { \
        s16 ix = it->x; \
        int a = (s16)m->def->v60(); \
        f32 fx = a + ix; \
        s16 iy = it->y; \
        int b = (s16)m->def->v64(); \
        fn_801E6B64(tbl, m, fx, b + iy); \
        return 0; \
    } \
    void* p = fn_80083B84(lbl_8038B160); \
    F(p, MenuProc*, 0x50) = m; \
    fn_80083DC4(p, sc); \
    return 4; \
}

HELPITEM(fn_801D41FC, lbl_8038C028, 0x10)
HELPITEM(fn_801D43A8, lbl_8038BFE8, 0xB)
HELPITEM(fn_801D44F8, lbl_8038BFBC, 0xA)
HELPITEM(fn_801D4648, lbl_8038BF90, 9)
HELPITEM(fn_801D4798, lbl_8038BF64, 8)
HELPITEM(fn_801D4940, lbl_8038BF2C, 0x17)

int fn_801D4C18(void*, MenuProc* m, ItemProc* it) {
    if (it->state == 2) {
        fn_801E6B64(lbl_8038BEF0, m, m->x + it->x, m->y + it->y);
        return 0;
    }
    void* p = fn_80083B84(lbl_8038B160);
    F(p, MenuProc*, 0x50) = m;
    fn_80083DC4(p, 0x12);
    return 4;
}

int fn_801D4E1C(void*, MenuProc* m, ItemProc* it) {
    if (it->state == 2) {
        fn_801E6B64(lbl_8038BEC0, m, m->x + it->x, m->y + it->y);
        return 0;
    }
    void* p = fn_80083B84(lbl_8038B160);
    F(p, MenuProc*, 0x50) = m;
    fn_80083DC4(p, 0x11);
    return 4;
}

void fn_801D4CC4(u8* obj, void*, ItemProc* it) {
    if (it->state == 2) {
        fn_80080508(*(Color*)fn_800CD204(0));
    } else if ((int)obj[4] != 0) {
        fn_80080508(*(Color*)fn_800CD204(0x13));
        fn_80080ABC(1, 2.0f);
    } else {
        fn_80080508(*(Color*)fn_800CD204(0x1D));
        fn_80080ABC(1, 2.0f);
    }
}

void fn_801D4EC8(void*, void*, ItemProc* it) {
    if (it->state == 2) {
        fn_80080508(*(Color*)fn_800CD204(0));
    } else {
        fn_80080508(*(Color*)fn_800CD204(0x1D));
        fn_80080ABC(1, 2.0f);
    }
}

void fn_801D550C(void* a, MenuProc* m) {
    ItemProc* it = fn_80085EF8(m->items[m->cur]);
    if (inputBlocked()) {
        it->item->v40(m, it);
        return;
    }
    u32 k = lbl_804CB5B8->v48();
    if ((k & 0x400) && fn_801A2224(lbl_8041EB20) == 0) {
        it->item->v30(m, it);
        return;
    }
    if (k & 0x800) {
        m->def->v20(m, it);
        return;
    }
    if (k & 0x1000) {
        it->item->v34(m, it);
        return;
    }
    if (k & 0x2000) {
        m->def->v24(m, it);
        return;
    }
    if (k & 0x10) {
        it->item->v38(m, it);
        return;
    }
    if ((k & 0x4000) && fn_801A2224(lbl_8041EB20) == 0) {
        m->def->v20(m, it);
        return;
    }
    it->item->v40(m, it);
}

struct WStr {
    u32 heap : 1;
    u32 len7 : 7;
    u8 inl[3];
    int len;
    char* ptr;
};

#define WIDS(w) (F(w, u32, 0x40) >> 31 == 0 ? (char*)(w) + 0x41 : F(w, char*, 0x48))

class Widget {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18(void*);
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
};

int fn_802450BC(void*);
void* fn_8024BC94();
int fn_801D4A44() {
    int v = fn_802450BC(fn_8024BC94());
    int r = 2;
    if (v != 0) r = 0;
    return r;
}

void fn_80079210(void*);
u8* fn_801D5D54(u8* w, int del) {
    if (w != NULL) {
        if (w != NULL && (w + 0x40) != NULL && (F(w, u32, 0x40) >> 31) != 0) fn_80079210(F(w, void*, 0x48));
        if (del > 0) fn_80079210(w);
    }
    return w;
}

void fn_801D7574(int, int, int, int, int);
void fn_801D5B34(Widget* w) {
    w->v14();
    switch (F(w, int, 0x60)) {
    case 1:
        fn_801D7574(0, 0, (s16)(F(w, s16, 0xE) - F(w, s16, 0xA)), (s16)(F(w, s16, 0x10) - F(w, s16, 0xC)), F(w, int, 0x38));
        break;
    case 0:
        break;
    }
}

#define LAZY(g, v, val) if ((s8)g == 0) { g = 1; v = val; }
#define G(n) extern u8 lbl_##n; extern void* lbl_##n##_v;
extern u8 lbl_804CBA40, lbl_804CBA48, lbl_804CBA50, lbl_804CBA58, lbl_804CBA60, lbl_804CBA70, lbl_804CBA78, lbl_804CBA80;
extern void* lbl_804CBA44, *lbl_804CBA4C, *lbl_804CBA54, *lbl_804CBA5C, *lbl_804CBA68, *lbl_804CBA74, *lbl_804CBA7C, *lbl_804CBA84;
extern u8 lbl_804CB9F8, lbl_804CBA00, lbl_804CBA08, lbl_804CBA10, lbl_804CBA18, lbl_804CBA20, lbl_804CBA28, lbl_804CBA30, lbl_804CBA38;
extern void* lbl_804CB9FC, *lbl_804CBA04, *lbl_804CBA0C, *lbl_804CBA14, *lbl_804CBA1C, *lbl_804CBA24, *lbl_804CBA2C, *lbl_804CBA34, *lbl_804CBA3C;
extern u8 lbl_8038BBE8[], lbl_8038BB90[], lbl_8038BB38[], lbl_8038BAE0[], lbl_8038BA88[], lbl_8038BA30[], lbl_8038B9D8[], lbl_8038B980[];
extern u8 lbl_8038B718[], lbl_8038B6C0[], lbl_8038B668[], lbl_8038B7C8[], lbl_8038B770[], lbl_8038B928[], lbl_8038B8D0[], lbl_8038B878[], lbl_8038B820[];
extern u8 lbl_8038B138[], lbl_8038C8A8[], lbl_8038BCE8[], lbl_8038B108[], lbl_8038BC40[], lbl_8038B118[], lbl_8038B124[];
extern char lbl_8038BE7C[], lbl_8038BE70[], lbl_8038BE60[], lbl_8038BE54[], lbl_8038BE44[], lbl_8038BE38[], lbl_8038BE28[], lbl_8038BE1C[];
void* fn_80079150(int);
void* fn_800D5448(void*, void*, int);
void fn_8008319C(void*);
void fn_800E24F8(const char*);
void fn_800C7B18(const char*, int);
u8 fn_801E7024();

#define MENUDEF2(p, vt, vt2, a, b, c, d, e, f0, g, h) \
    if (p != NULL) { \
        F(p, void*, 0) = vt; \
        F(p, void*, 4) = lbl_8038C8A8; \
        F(p, s16, 8) = 0; \
        F(p, s16, 0xA) = 0; \
        F(p, s16, 0xC) = a; \
        F(p, s16, 0xE) = b; \
        F(p, s16, 0x10) = c; \
        F(p, s16, 0x12) = d; \
        F(p, s16, 0x14) = e; \
        F(p, s16, 0x16) = 0; \
        F(p, f32, 0x18) = f0; \
        F(p, s16, 0x1C) = g; \
        F(p, void*, 4) = vt2; \
        F(p, s16, 0x1E) = h; \
    }

#define MENUDEF(p, vt, vt2, a, b, c, d, e, f0, g, h, i, j, k) \
    if (p != NULL) { \
        F(p, void*, 0) = vt; \
        F(p, void*, 4) = lbl_8038C8A8; \
        F(p, s16, 8) = 0; \
        F(p, s16, 0xA) = 0; \
        F(p, s16, 0xC) = a; \
        F(p, s16, 0xE) = b; \
        F(p, s16, 0x10) = c; \
        F(p, s16, 0x12) = d; \
        F(p, s16, 0x14) = e; \
        F(p, s16, 0x16) = 0; \
        F(p, f32, 0x18) = f0; \
        F(p, s16, 0x1C) = g; \
        F(p, s16, 0x1E) = h; \
        F(p, void*, 4) = vt2; \
    }

int fn_801D4A90(void*, MenuProc* m, ItemProc* it) {
    if (it->state == 2) return 0;
    LAZY(lbl_804CB9F8, lbl_804CB9FC, lbl_8038B718)
    LAZY(lbl_804CBA00, lbl_804CBA04, lbl_8038B6C0)
    LAZY(lbl_804CBA08, lbl_804CBA0C, lbl_8038B668)
    u8* d = (u8*)fn_80079150(0x20);
    MENUDEF(d, lbl_8038B108, lbl_8038BC40, 0x80, 0, 2, 0xC, 0x10, 0.0f, 0x20, 4,0,0,0)
    int y = it->vis * 0x22 + 0x59;
    F(d, s16, 8) = 0xDA;
    F(d, s16, 0xA) = y;
    F(d, s16, 0xC) = 0x8A;
    F(d, s16, 0x14) = 0;
    F(d, f32, 0x18) = 880.0f;
    F(d, s16, 0x1E) = 4;
    fn_800D5448(d, m, 0);
    return 4;
}

int fn_801D4F74(void*, MenuProc* m, ItemProc* it) {
    if (it->state == 2) return 0;
    LAZY(lbl_804CBA10, lbl_804CBA14, lbl_8038B7C8)
    LAZY(lbl_804CBA18, lbl_804CBA1C, lbl_8038B770)
    u8* d = (u8*)fn_80079150(0x20);
    MENUDEF(d, lbl_8038B118, lbl_8038BC40, 0x80, 0, 2, 0xC, 0x10, 0.0f, 0x20, 4,0,0,0)
    int y = it->vis * 0x22 + 0x59;
    F(d, s16, 8) = 0xDA;
    F(d, s16, 0xA) = y;
    F(d, s16, 0xC) = 0x8A;
    F(d, s16, 0x14) = 0;
    F(d, f32, 0x18) = 880.0f;
    F(d, s16, 0x1E) = 4;
    fn_800D5448(d, m, 0);
    return 4;
}

extern u8 lbl_8038BE88[];
int fn_801D50DC(void*, MenuProc* m, ItemProc* it) {
    if (it->state == 2) {
        if (fn_801E7024() == 0) {
            s16 ix = it->x;
            int a = (s16)m->def->v60();
            f32 fx = a + ix;
            s16 iy = it->y;
            int b = (s16)m->def->v64();
            fn_801E6B64(lbl_8038BE88, m, fx, b + iy);
            return 0;
        }
        return 0;
    }
    fn_800E24F8(lbl_8038BE7C);
    fn_800E24F8(lbl_8038BE70);
    fn_800C7B18(lbl_8038BE60, 0);
    fn_800C7B18(lbl_8038BE54, 0);
    fn_800C7B18(lbl_8038BE44, 0);
    fn_800C7B18(lbl_8038BE38, 0);
    fn_800C7B18(lbl_8038BE28, 0);
    fn_800C7B18(lbl_8038BE1C, 0);
    LAZY(lbl_804CBA20, lbl_804CBA24, lbl_8038B928)
    LAZY(lbl_804CBA28, lbl_804CBA2C, lbl_8038B8D0)
    LAZY(lbl_804CBA30, lbl_804CBA34, lbl_8038B878)
    LAZY(lbl_804CBA38, lbl_804CBA3C, lbl_8038B820)
    u8* d = (u8*)fn_80079150(0x20);
    MENUDEF(d, lbl_8038B124, lbl_8038BC40, 0x80, 0, 2, 0xC, 0x10, 0.0f, 0x20, 4,0,0,0)
    int y = it->vis * 0x22 + 0x59;
    F(d, s16, 8) = 0xDA;
    F(d, s16, 0xA) = y;
    F(d, s16, 0xC) = 0x8A;
    F(d, s16, 0x14) = 0;
    F(d, f32, 0x18) = 880.0f;
    F(d, s16, 0x1E) = 4;
    fn_800D5448(d, m, 0);
    return 4;
}

#define MENU0(d) \
    LAZY(lbl_804CBA40, lbl_804CBA44, lbl_8038BBE8) \
    LAZY(lbl_804CBA48, lbl_804CBA4C, lbl_8038BB90) \
    LAZY(lbl_804CBA50, lbl_804CBA54, lbl_8038BB38) \
    LAZY(lbl_804CBA58, lbl_804CBA5C, lbl_8038BAE0) \
    LAZY(lbl_804CBA60, lbl_804CBA68, lbl_8038BA88) \
    LAZY(lbl_804CBA70, lbl_804CBA74, lbl_8038BA30) \
    LAZY(lbl_804CBA78, lbl_804CBA7C, lbl_8038B9D8) \
    LAZY(lbl_804CBA80, lbl_804CBA84, lbl_8038B980) \
    u8* d = (u8*)fn_80079150(0x20); \
    MENUDEF2(d, lbl_8038B138, lbl_8038BCE8, 0xC0, 0x1C0, -0x20, 0x59, 0, 10.0f, 0x22, 0) \
    F(d, f32, 0x18) = 890.0f; \
    F(d, s16, 0x1E) = 0;

void fn_8008319C(void*);
void fn_801D39C0(u8* p) {
    MENU0(d)
    void* m = fn_800D5448(d, p, 0);
    fn_8008319C(m);
    F(p, void*, 0x4C) = m;
}

void fn_801D2458(u8* p) {
    MENU0(d)
    u8* m = (u8*)fn_800D5448(d, p, 0);
    fn_8008319C(m);
    m[0xA6] = 2;
    m[0xA5] = 0;
    F(p, void*, 0x4C) = m;
    LAZY(lbl_804CBA10, lbl_804CBA14, lbl_8038B7C8)
    LAZY(lbl_804CBA18, lbl_804CBA1C, lbl_8038B770)
    u8* e = (u8*)fn_80079150(0x20);
    MENUDEF(e, lbl_8038B118, lbl_8038BC40, 0x80, 0, 2, 0xC, 0x10, 0.0f, 0x20, 4,0,0,0)
    F(e, s16, 8) = 0xDA;
    F(e, s16, 0xA) = 0xBF;
    F(e, s16, 0xC) = 0x8A;
    F(e, s16, 0x14) = 0;
    F(e, f32, 0x18) = 880.0f;
    F(e, s16, 0x1E) = 4;
    u8* n = (u8*)fn_800D5448(e, m, 0);
    n[0xA5] = 0;
    F(p, void*, 0x50) = n;
}

int fn_800CA3DC(const char*, int, f32);
int fn_800CB0FC(int, f32);
void fn_800800D4(int);
void fn_80080330(f32, f32);
void fn_80080A94(f32);
void fn_80080C24(const char*);
void fn_80080308();
void fn_8007E154();
void fn_8007E164();
void fn_8007E174(void*, u16);
void fn_8007E720(f32);
#define WIDSEL(w, sh) ((sh) ? (char*)(w) + 0x41 : F(w, char*, 0x48))



u8 fn_801E7114();
u8 fn_801E70C4();
int fn_801D474C() { return (fn_801E7114() == 0) ? 2 : 0; }
int fn_801D489C() { return (fn_801E70C4() == 0) ? 2 : 0; }
}
