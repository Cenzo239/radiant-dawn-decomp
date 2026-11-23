/* fn_801D5914 (round 22, agent r22b): class `sched`, 6 words differ (2 masked lines).
 * Help/text window draw: alignment of the label (+0x4C: 0 left, 1 centred, 2 right, using
 * the text width fn_800CA3DC(str, -1, scale)), vertical centring with the font height
 * fn_800CB0FC(scale, -1), then draws the small-string text at +0x40 (inline at +0x41 or
 * heap pointer at +0x48) in colour +0x50 at scale +0x54.
 * Built with tools/equiv/mkself.py from rR_80175E5C/fn_801D41FC.cpp and the old fragment in
 * rR_80175E5C/wip/fn_801D41FC.cpp, with three fixes:
 *  - `case 0: x = (s16)x;` keeps case 0 as its own block (the original's extra
 *    `cmpwi 0; bge` and lone `b`); the statement does nothing (x already holds an s16);
 *  - the text width goes through textW(), an inline with the callee's own parameter order,
 *    so the scale is loaded before the string-select branch;
 *  - fn_800CB0FC is declared with its catalogued order (f32 scale, int idx), which also
 *    fixes its argument load order. The parent file declares it (int, f32): same registers.
 * Remaining: the font-height lfs and one subtraction are scheduled one slot apart, and the
 * registers of x/vp/y differ. symcheck --anon --xargs: 41 blocks, 0 differ.
 */
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

int fn_801D4C18(void*, MenuProc* m, ItemProc* it);

int fn_801D4E1C(void*, MenuProc* m, ItemProc* it);

void fn_801D4CC4(u8* obj, void*, ItemProc* it);

void fn_801D4EC8(void*, void*, ItemProc* it);

void fn_801D550C(void* a, MenuProc* m);


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
int fn_801D4A44();


void fn_80079210(void*);
u8* fn_801D5D54(u8* w, int del);


void fn_801D7574(int, int, int, int, int);
void fn_801D5B34(Widget* w);


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

int fn_801D4A90(void*, MenuProc* m, ItemProc* it);

int fn_801D4F74(void*, MenuProc* m, ItemProc* it);


extern u8 lbl_8038BE88[];
int fn_801D50DC(void*, MenuProc* m, ItemProc* it);


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
void fn_801D39C0(u8* p);

void fn_801D2458(u8* p);


int fn_800CA3DC(const char*, int, f32);
int fn_800CB0FC(f32, int);
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
int fn_801D474C();

int fn_801D489C();

}

/* ---- from build/tmp/r22b/fr_y5.cpp ---- */
extern "C" {
extern "C" {
static inline int textW(const char* s, int i, f32 f) { return fn_800CA3DC(s, i, f); }
void fn_801D5914(Widget* w, void* a) {
    int ww;
    s16 pad;
    w->v2C();
    w->v18(a);
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E174(0, F(w, int, 0x38) | 0x13);
    fn_8007E164();
    pad = F(w, s16, 0x5C);
    ww = F(w, s16, 0xE) - F(w, s16, 0xA);
    int x = F(w, s16, 0x58);
    int sh = !(F(w, u32, 0x40) >> 31);
    s16 room = (s16)ww - (x + pad);
    if (WIDSEL(w, sh) != NULL) {
        switch (F(w, int, 0x4C)) {
        case 0:
            x = (s16)x;
            break;
        case 1:
            x = (s16)(x + ((room - textW(WIDSEL(w, sh), -1, F(w, f32, 0x54))) >> 1));
            break;
        case 2:
            x = (s16)((s16)ww - (pad + textW(WIDSEL(w, sh), -1, F(w, f32, 0x54))));
            break;
        default:
            break;
        }
        int h = (s16)(F(w, s16, 0x10) - F(w, s16, 0xC));
        s16 vp = F(w, s16, 0x5A);
        int y = (vp + (h - fn_800CB0FC(F(w, f32, 0x54), -1))) >> 1;
        fn_800800D4(5);
        fn_80080330((s16)x, y);
        fn_80080A94(F(w, f32, 0x54));
        fn_80080508(*(Color*)fn_800CD204(F(w, u8, 0x50)));
        fn_80080C24((F(w, u32, 0x40) >> 31) == 0 ? (char*)w + 0x41 : F(w, char*, 0x48));
    fn_80080308();
    }
}

}
}
