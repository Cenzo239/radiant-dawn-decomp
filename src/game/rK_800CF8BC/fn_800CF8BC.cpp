#include "game/rK_800CF8BC/types.h"
#include "game/rH_80112B48/map.h"
#include "game/rH_80112B48/unit.h"

#pragma use_lmw_stmw on

extern Map lbl_803EC898;
extern TileList lbl_803E7320;
extern char lbl_80366400[];
extern u32 lbl_804CB700;
extern u8 lbl_804CB728;
extern u8 lbl_80383A78[];
extern u8 lbl_80383A88[];
extern u8 lbl_80383AA0[];
extern u8 lbl_80383AB0[];

struct Act {
    u8 pad0[4];
    Unit* unit;
    u8 pad8[0x13 - 8];
    s8 x;
    s8 y;
    u8 pad15[0x130 - 0x15];
};
extern Act lbl_803CA870;

struct Fl {
    u8 pad[0x92C];
    u8 b92C;
    u8 pad92D[0x934 - 0x92D];
    f32 f934;
    f32 f938;
    u8 pad93C[0x944 - 0x93C];
    f32 x;
    f32 y;
};
extern Fl lbl_803CAB38;

struct MsgVar {
    int len;
    char str[0x40];
};
extern MsgVar lbl_803E8D28[];
extern char lbl_803E8528[0x800];
extern char lbl_803E8E38[];
extern char* lbl_804CA480;
extern char lbl_804CA0C0[8];
extern char lbl_80366438[];
extern const char* lbl_8037AB10[];

struct Tex {
    u32 w[8];
};
struct Img {
    Tex t;
    u16 w;
    u16 h;
};
struct Cap {
    int id;
    int x4;
    int x8;
    int xC;
    int x10;
};
struct CapProc {
    u8 proc[0x30];
    void* o30;
    void* o34;
    void* o38;
    Cap* cap;
    u32 t;
};
struct SelProc : MapSelProc {
    s8 b48;
    s8 b49;
};

extern u8 lbl_80383AC8[];

extern "C" {
int fn_801D09F0();
u8 fn_80118130(Map*, int, int);
void fn_80114B44(Map*, int, int);
void fn_8013F1C4();
void fn_8013F204();
void fn_80131DE4();
void fn_800620A8(Fl*, f32, f32);
void fn_80253EE4(const char*, f32);
void fn_80133034();
SelProc* fn_80081194(u8*, void*);
#if TARGET_PC
FE10_PROTO SelProc* fn_80081050(u8*, p32arg);
#else
SelProc* fn_80081050(u8*, int);
#endif
f32 fn_8017F68C(int, f32, f32, f32, f32);
char* fn_80076F54(const char*);
int fn_80290D04(char*, int, const char*, ...);
int fn_80290DDC(char*, const char*, ...);
int strlen(const char*);
char* strcpy(char*, const char*);
void fn_80291CEC(int, char*, int);
int fn_8023F9F4(const char*);
s8 fn_80244D88();
void fn_80079474(void*);
void fn_800761F0(void*);
void fn_80006A2C(void*);
void fn_80083DC4(void*, int);
void fn_80083B78(void*);
void fn_800068EC(void*, void*, int);
void fn_80006A64(void*, Tex*, int);
u16 fn_80305DF8(Tex*);
u16 fn_80305E0C(Tex*);
void fn_8007E154();
void fn_8007E164();
void fn_8007E4E4(f32, f32, f32, f32);
void fn_8007E7DC(int);
void fn_8007E7E8(int);
void fn_8007E84C(int);
void fn_8007E174(Tex*, int);
void fn_800800D4(int);
void fn_80080388(f32, f32, f32, f32);
void fn_800803C8(f32, f32, f32, f32);
void fn_800804F4(u8);
void fn_80080308();
const char* fn_800CEB4C();
const char* fn_800CEC24();
const char* fn_800CECFC();
const char* fn_800CEDD4();
const char* fn_800CEEAC();
const char* fn_800CEF84();
const char* fn_800CF05C();
const char* fn_800CF134();
const char* fn_800CF20C();
const char* fn_800CF2D8();
const char* fn_800CF3A4();
const char* fn_800CF470();
const char* fn_800CF53C();
const char* fn_800CF608();
const char* fn_800CF6E0();
const char* fn_800CF7B8();
char* fn_800D0BFC(const char*);
int fn_800D0998(const char*);


int fn_800CF8BC() { return 0; }
int fn_800CF8C4() { return 0x20; }
int fn_800CF8CC() { return fn_801D09F0() ? 18.331657f : 24.0f; }
int fn_800CF90C() { return 0x18; }
int fn_800CF914() { return 0x18; }
int fn_800CF91C() { return fn_801D09F0() ? 18.331657f : 24.0f; }
int fn_800CF95C() { return 0xA; }
int fn_800CF964() { return 0xF0; }
int fn_800CF96C() { return fn_801D09F0() ? 586.61304f : 768.0f; }
int fn_800CF9AC() { return 0x20; }
int fn_800CF9B4() { return fn_801D09F0() ? 24.442211f : 32.0f; }
int fn_800CF9F4() { return 0x20; }
int fn_800CF9FC() { return fn_801D09F0() ? 24.442211f : 32.0f; }
int fn_800CFA3C() { return 3; }
int fn_800CFA44() { return 0x20; }
int fn_800CFA4C() { return 0x60; }
int fn_800CFA54() { return fn_801D09F0() ? 782.15076f : 1024.0f; }
int fn_800CFA94() { return 1; }
u8* fn_800CFA9C() { return fn_801D09F0() ? lbl_80383A88 : lbl_80383A78; }
u8* fn_800CFAD4() { return fn_801D09F0() ? lbl_80383AB0 : lbl_80383AA0; }

Unit* fn_800CFB0C(TileEntry* e) {
    int u = e->unit;
    if (u) {
        return &lbl_804CB810[u - 1];
    }
    return 0;
}

void fn_800CFB34(TileList* l) {
    l->n = 0;
    l->cur = 0;
    l->e[0].x = -1;
}

static inline TileEntry* ListGet(TileList* l, int i) {
    if (i >= l->n) {
        return 0;
    }
    return &l->e[i];
}

int fn_800CFB4C(TileList* l) {
    int r = 0;
    int i;
    for (i = 0; i < l->n; i++) {
        int t = fn_80118130(&lbl_803EC898, ListGet(l, i)->x, (s8)*(u8*)&ListGet(l, i)->y);
        if (r == 0) {
            r = t;
        } else if (r != t) {
            break;
        }
    }
    return r;
}

TileEntry* fn_800CFBFC(TileList* l) {
    TileEntry* e = &l->e[l->n++];
    e->x = 0;
    e->y = 0;
    e->unit = 0;
    e->p4 = 0;
    e->p8 = 0;
    e->pC = 0;
    e->p10 = 0;
    l->e[l->n].x = -1;
    return e;
}

TileEntry* fn_800CFC50(TileList* l, s8 x, s8 y, u8 unit, void* p) {
    TileEntry* e = &l->e[l->n++];
    e->x = 0;
    e->y = 0;
    e->unit = 0;
    e->p4 = 0;
    e->p8 = 0;
    e->pC = 0;
    e->p10 = 0;
    l->e[l->n].x = -1;
    e->x = x;
    e->y = y;
    e->unit = unit;
    e->p4 = p;
    return e;
}

TileEntry* fn_800CFCB4(TileList* l, s8 x, s8 y) {
    int i;
    for (i = 0; i < l->n; i++) {
        if (x == l->e[i].x && y == l->e[i].y) {
            return &l->e[i];
        }
    }
    return 0;
}

TileEntry* fn_800CFD18(TileList* l, int i) {
    if (i >= l->n) {
        return 0;
    }
    return &l->e[i];
}

TileEntry* fn_800CFD3C(TileList* l) {
    int i = l->cur;
    if (i >= l->n) {
        return 0;
    }
    return &l->e[i];
}

void fn_800CFD64(TileList* l) { l->cur++; }
void fn_800CFD74(TileList* l) { l->n = l->cur; }

void fn_800CFD80() {
    int i;
    fn_80114B44(&lbl_803EC898, 6, -1);
    fn_80114B44(&lbl_803EC898, 9, 0);
    for (i = 0; i < lbl_803E7320.n; i++) {
        TileEntry* e = ListGet(&lbl_803E7320, i);
        lbl_803EC898.g4[e->x + (e->y << 6)] = 1;
    }
    fn_8013F1C4();
}

void fn_800CFE3C() { fn_8013F204(); }

int fn_800CFE40(Menu*, MapSelProc* p) {
    TileEntry* e = p->e40;
    if (e == 0) {
        return 0x10;
    }
    s8 x = e->x;
    s8 y = e->y;
    lbl_803CA870.x = x;
    lbl_803CA870.y = y;
    if (e->unit) {
        lbl_803CA870.unit = fn_800CFB0C(e);
    }
    return 5;
}

int fn_800CFEA8() {
    lbl_803CAB38.b92C = 0xF;
    return 9;
}

static inline void SetPos(MapSelProc* p, f32 x, f32 y) {
    p->px = p->x;
    p->py = p->y;
    p->fx = x;
    p->fy = y;
    p->x = (int)p->fx;
    p->y = (int)p->fy;
    if (p->px != p->x || p->py != p->y) {
        TileEntry* e = fn_800CFCB4(&lbl_803E7320, p->x, p->y);
        p->e40 = e;
        if (e) {
            p->e44 = e;
        }
    }
}

static inline BOOL Moved(MapSelProc* p) {
    return p->x != p->px || p->y != p->py;
}

void fn_800CFEC0(Menu* m, MapSelProc* p) {
    if ((lbl_804CB5B8->v34() & 0xF) == 0) {
        fn_80131DE4();
        f32 y = lbl_803CAB38.y;
        f32 x = lbl_803CAB38.x;
        SetPos(p, x, y);
    } else {
        TileEntry* n = 0;
        TileEntry* cur = p->e44;
        if (lbl_804CB5B8->v3C() & 9) {
            n = cur->left;
        }
        if (lbl_804CB5B8->v3C() & 6) {
            n = cur->right;
        }
        if (n == 0 || n == cur) {
            return;
        }
        s8 ix = n->x;
        s8 iy = n->y;
        SetPos(p, 0.5f + ix, 0.5f + iy);
        fn_800620A8(&lbl_803CAB38, n->x, n->y);
        fn_80253EE4(lbl_80366400, 0.0f);
        p->e40 = n;
        if (n) {
            p->e44 = n;
        }
    }
    if (Moved(p)) {
        m->v1C(p);
    }
}

void fn_800D0258() { fn_80133034(); }

void fn_800D025C(MapSelProc* p) {
    u8 r = 0;
    if (p->e40 == 0) {
        p->menu->count = 0;
    } else {
        p->menu->count++;
    }
    if (lbl_804CB700 & 0x80) {
        p->menu->v28(p);
    } else {
        p->menu->v24(p);
        p->menu->v28(p);
        if (lbl_804CB5B8->v48() & 0x400) {
            r = p->menu->v14(p);
        } else if (lbl_804CB5B8->v48() & 0x800) {
            r = p->menu->v18(p);
        }
    }
    lbl_804CB728 = r;
    if (r & 4) {
        fn_80253EE4(p->menu->v30(), 0.0f);
    }
    if (r & 8) {
        fn_80253EE4(lbl_80366400 + 0x19, 0.0f);
    }
    if (r & 0x10) {
        fn_80253EE4(lbl_80366400 + 0x29, 0.0f);
    }
    if (r & 1) {
        fn_80083DC4(p, 0x63);
    }
}

int fn_800D03FC(MapSelProc* p) { return p->menu->v10(p); }
int fn_800D0414(MapSelProc* p) { return p->menu->v2C(p); }

static inline TileEntry* First() {
    if (0 >= lbl_803E7320.n) {
        return 0;
    }
    return &lbl_803E7320.e[0];
}

SelProc* fn_800D042C(Menu* m, void* parent);

void fn_800D0788(int* a, int* b, int* c, int* d) {
    int t;
    *c = 0;
    t = *a;
    t += 1;
    if (t > 8) {
        t = 8;
    }
    *b = fn_8017F68C(6, -64.0f, 0.0f, t, 8.0f);
    *d = fn_8017F68C(0, 0.0f, 255.0f, t, 8.0f);
}

static inline const char* MsgGet(const char* s) {
    const char* p = fn_80076F54(s);
    if (p == 0) {
        p = s;
    } else if (*p == 0x40) {
        p = fn_800D0BFC(p + 1);
    }
    return p;
}

const char* fn_800D0864(const char* s) { return MsgGet(s); }

const char* fn_800D08B4(const char* s, int fm) {
    char buf[0x80];
    if (fm == 0) {
        return MsgGet(s);
    }
    fn_80290D04(buf, 0x80, lbl_80366438, s);
    if (fn_80076F54(buf) == 0) {
        return MsgGet(s);
    }
    return MsgGet(buf);
}

#define IS_SJIS(s) ((((u8)(s)[0] >= 0x81 && (u8)(s)[0] <= 0x9F) || ((u8)(s)[0] >= 0xE0 && (u8)(s)[0] <= 0xFC)) && (((u8)(s)[1] >= 0x40 && (u8)(s)[1] <= 0x7E) || ((u8)(s)[1] >= 0x80 && (u8)(s)[1] <= 0xFC)))

static inline BOOL IsSjis(const u8* s) {
    u8 c = s[0];
    if ((c >= 0x81 && c <= 0x9F) || (c >= 0xE0 && c <= 0xFC)) {
        c = s[1];
        if ((c >= 0x40 && c <= 0x7E) || (c >= 0x80 && c <= 0xFC)) {
            return 1;
        }
    }
    return 0;
}

const char* fn_800D0B90(int c);

int fn_800D0998(const char* s) {
    MsgVar* tbl = lbl_803E8D28;
    int n = 0;
    while (*s) {
        if (*s == '@') {
            s++;
            switch (*s) {
            case '@':
                s++;
                n++;
                continue;
            case '{': {
                int i = (s8)s[1] - '0';
                s += 3;
                n += tbl[i].len;
                continue;
            }
            case '[': {
                int i = s[1];
                s += 3;
                n += strlen(fn_800D0B90(i));
                continue;
            }
            default:
                n++;
                break;
            }
        }
        if (IsSjis((const u8*)s)) {
            n += 2;
            s += 2;
        } else {
            n++;
            s++;
        }
    }
    return n;
}

char* fn_800D0AE4(int i, int v) {
    MsgVar* e = &lbl_803E8D28[i];
    fn_80291CEC(v, e->str, 10);
    e->len = strlen(e->str);
    return e->str;
}

void fn_800D0B38(int i, const char* s) {
    MsgVar* e = &lbl_803E8D28[i];
    e->len = strlen(s);
    strcpy(e->str, s);
}

const char* fn_800D0B90(int c) {
    const char* r = 0;
    switch (c) {
    case 0x41: r = fn_800CEB4C(); break;
    case 0x42: return fn_800CEC24();
    case 0x58: return fn_800CECFC();
    case 0x59: return fn_800CEDD4();
    case 0x4C: return fn_800CEEAC();
    case 0x52: return fn_800CEF84();
    case 0x5A: return fn_800CF05C();
    case 0x50:
    case 0x53: return fn_800CF134();
    case 0x64: return fn_800CF20C();
    case 0x73: return fn_800CF2D8();
    case 0x7C: return fn_800CF3A4();
    case 0x2D: return fn_800CF470();
    case 0x2B: return fn_800CF53C();
    case 0x43: return fn_800CF608();
    case 0x6C: return fn_800CF6E0();
    case 0x5F: r = fn_800CF7B8(); break;
    }
    return r;
}

char* fn_800D0BFC(const char* s);

char* fn_800D0DBC(const char* name) {
    s8 lang = fn_80244D88();
    fn_80290DDC(lbl_803E8E38, lbl_80366438 + 6, lang >= 0 ? lbl_8037AB10[lang] : lbl_804CA0C0, name);
    if (fn_8023F9F4(lbl_803E8E38) == 0x40000) {
        fn_80290DDC(lbl_803E8E38, lbl_80366438 + 0x10, name);
    }
    return lbl_803E8E38;
}

void fn_800D0E6C() {}

void fn_800D0E70(CapProc* p) {
    if (p->o30) {
        fn_80079474(p->o30);
        p->o30 = 0;
    }
    if (p->o34) {
        fn_800761F0(p->o34);
        p->o34 = 0;
    }
    if (p->o38) {
        fn_80006A2C(&p->o38);
    }
}

static inline void ImgDraw(Img* i, u8 a) {
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 9.0f, 1.0f);
    fn_8007E7DC(0xFF);
    fn_8007E7E8(0x80);
    fn_8007E84C(1);
    fn_8007E164();
    fn_8007E154();
    fn_8007E174(&i->t, 0x10);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080388((0x260 - i->w) >> 1, 0x1B0 - i->h, i->w, i->h);
    fn_800803C8(0.0f, 0.0f, 1.0f, 1.0f);
    fn_800804F4(a);
    fn_80080308();
}

void fn_800D0EE0(CapProc* p) {
    Cap* c = p->cap;
    f32 d = c->x10 / 16.666666f;
    if (d <= (f32)(p->t = p->t + 1)) {
        p->t = 0;
        p->cap++;
        if (p->cap->id >= 0) {
            fn_80083DC4(p, 1);
        } else {
            fn_80083DC4(p, 2);
        }
    } else {
        f32 v = fn_8017F68C(0, 1.0f, 0.0f, p->t, p->cap->x10 / 16.666666f);
        Tex t;
        fn_80006A64(p->o38, &t, p->cap->id);
        Img i;
        i.t = t;
        i.w = fn_80305DF8(&i.t);
        i.h = fn_80305E0C(&i.t);
        ImgDraw(&i, 255.9f * v);
    }
}

void fn_800D1124(CapProc* p) {
    Cap* c = p->cap;
    f32 d = c->xC / 16.666666f;
    if (d <= (f32)(p->t = p->t + 1)) {
        p->t = 0;
        Tex t;
        fn_80006A64(p->o38, &t, p->cap->id);
        Img i;
        i.t = t;
        i.w = fn_80305DF8(&i.t);
        i.h = fn_80305E0C(&i.t);
        ImgDraw(&i, 0xFF);
        fn_80083B78(p);
    } else {
        Tex t;
        fn_80006A64(p->o38, &t, p->cap->id);
        Img i;
        i.t = t;
        i.w = fn_80305DF8(&i.t);
        i.h = fn_80305E0C(&i.t);
        ImgDraw(&i, 0xFF);
    }
}

void fn_800D1418(CapProc* p) {
    Cap* c = p->cap;
    f32 d = c->x8 / 16.666666f;
    if (d <= (f32)(p->t = p->t + 1)) {
        p->t = 0;
        Tex t;
        fn_80006A64(p->o38, &t, p->cap->id);
        Img i;
        i.t = t;
        i.w = fn_80305DF8(&i.t);
        i.h = fn_80305E0C(&i.t);
        ImgDraw(&i, 0xFF);
        fn_80083B78(p);
    } else {
        f32 v = fn_8017F68C(0, 0.0f, 1.0f, p->t, p->cap->x8 / 16.666666f);
        Tex t;
        fn_80006A64(p->o38, &t, p->cap->id);
        Img i;
        i.t = t;
        i.w = fn_80305DF8(&i.t);
        i.h = fn_80305E0C(&i.t);
        ImgDraw(&i, 255.9f * v);
    }
}

void fn_800D176C(CapProc* p) {
    Cap* c = p->cap;
    if (c->x4 / 16.666666f <= (f32)(p->t = p->t + 1)) {
        if (p->o38 == 0) {
            fn_800068EC(&p->o38, p->o30, 0x2080);
        }
        p->t = 0;
        fn_80083B78(p);
    }
}
}
