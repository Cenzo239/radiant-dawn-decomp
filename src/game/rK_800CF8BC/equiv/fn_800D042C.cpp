/* fn_800D042C: functionally equal (regs, 15 of 215 words differ in registers only). Helpers from fn_800CF8BC.cpp (exported bodies removed), body from wip/fn_800D042C_r17.cpp. fn_800CFCB4_i is a local inline copy of fn_800CFCB4, which the original inlines here. */
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
SelProc* fn_80081050(u8*, int);
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
int fn_800CF8BC();

int fn_800CF8C4();

int fn_800CF8CC();

int fn_800CF90C();

int fn_800CF914();

int fn_800CF91C();

int fn_800CF95C();

int fn_800CF964();

int fn_800CF96C();

int fn_800CF9AC();

int fn_800CF9B4();

int fn_800CF9F4();

int fn_800CF9FC();

int fn_800CFA3C();

int fn_800CFA44();

int fn_800CFA4C();

int fn_800CFA54();

int fn_800CFA94();

u8* fn_800CFA9C();

u8* fn_800CFAD4();

Unit* fn_800CFB0C(TileEntry* e);

void fn_800CFB34(TileList* l);


static inline TileEntry* ListGet(TileList* l, int i) {
    if (i >= l->n) {
        return 0;
    }
    return &l->e[i];
}
int fn_800CFB4C(TileList* l);

TileEntry* fn_800CFBFC(TileList* l);

TileEntry* fn_800CFC50(TileList* l, s8 x, s8 y, u8 unit, void* p);

TileEntry* fn_800CFCB4(TileList* l, s8 x, s8 y);
/* Local inline copy of fn_800CFCB4 (matched in fn_800CF8BC.cpp): the original inlines it here. */
static inline TileEntry* fn_800CFCB4_i(TileList* l, s8 x, s8 y) {
    int i;
    for (i = 0; i < l->n; i++) {
        if (x == l->e[i].x && y == l->e[i].y) {
            return &l->e[i];
        }
    }
    return 0;
}

TileEntry* fn_800CFD18(TileList* l, int i);

TileEntry* fn_800CFD3C(TileList* l);

void fn_800CFD64(TileList* l);

void fn_800CFD74(TileList* l);

void fn_800CFD80();

void fn_800CFE3C();

int fn_800CFE40(Menu*, MapSelProc* p);

int fn_800CFEA8();


static inline void SetPos(MapSelProc* p, f32 x, f32 y) {
    p->px = p->x;
    p->py = p->y;
    p->fx = x;
    p->fy = y;
    p->x = (int)p->fx;
    p->y = (int)p->fy;
    if (p->px != p->x || p->py != p->y) {
        TileEntry* e = fn_800CFCB4_i(&lbl_803E7320, p->x, p->y);
        p->e40 = e;
        if (e) {
            p->e44 = e;
        }
    }
}

static inline BOOL Moved(MapSelProc* p) {
    return p->x != p->px || p->y != p->py;
}
void fn_800CFEC0(Menu* m, MapSelProc* p);

void fn_800D0258();

void fn_800D025C(MapSelProc* p);

int fn_800D03FC(MapSelProc* p);

int fn_800D0414(MapSelProc* p);


static inline TileEntry* First() {
    if (0 >= lbl_803E7320.n) {
        return 0;
    }
    return &lbl_803E7320.e[0];
}

SelProc* fn_800D042C(Menu* m, void* parent);
void fn_800D0788(int* a, int* b, int* c, int* d);


static inline const char* MsgGet(const char* s) {
    const char* p = fn_80076F54(s);
    if (p == 0) {
        p = s;
    } else if (*p == 0x40) {
        p = fn_800D0BFC(p + 1);
    }
    return p;
}
const char* fn_800D0864(const char* s);

const char* fn_800D08B4(const char* s, int fm);


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
int fn_800D0998(const char* s);

char* fn_800D0AE4(int i, int v);

void fn_800D0B38(int i, const char* s);

const char* fn_800D0B90(int c);


char* fn_800D0BFC(const char* s);
char* fn_800D0DBC(const char* name);

void fn_800D0E6C();

void fn_800D0E70(CapProc* p);


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
void fn_800D0EE0(CapProc* p);

void fn_800D1124(CapProc* p);

void fn_800D1418(CapProc* p);

void fn_800D176C(CapProc* p);

}

/* ---- from rK_800CF8BC/wip/fn_800D042C_r17.cpp ---- */
extern "C" {
/* fn_800D042C (round 17 near miss): 15 of 215 words (was 21). Append to a copy of fn_800CF8BC.cpp inside its extern "C"
 * block with #pragma use_lmw_stmw on. The pv/nx locals fixed the modulo order; left: the loop counter, list base and
 * count rotate among r9/r10/r11 (volatile registers; loop forms and declaration order did not move them). */
static inline void Link(TileList* l, int i) { int n = l->n; l->e[i].left = &l->e[(i + n - 1) % n]; l->e[i].right = &l->e[(i + 1) % n]; }
static inline void Link2(TileList* l, int i, int n) { l->e[i].left = &l->e[(i + n - 1) % n]; l->e[i].right = &l->e[(i + 1) % n]; }
SelProc* fn_800D042C(Menu* m, void* parent) {
/*P*/
    SelProc* p;
    int i;
    int n;
    int pv;
    int nx;
    TileList* l;
/*E*/
    if (parent) {
        p = fn_80081194(lbl_80383AC8, parent);
    } else {
        p = fn_80081050(lbl_80383AC8, 3);
    }
    p->b48 = (int)lbl_803CAB38.f934;
    p->b49 = (int)lbl_803CAB38.f938;
    for (i = 0; i < lbl_803E7320.n; i++) {
        n = lbl_803E7320.n;
        pv = (i + n - 1) % n;
        nx = (i + 1) % n;
        lbl_803E7320.e[i].left = &lbl_803E7320.e[pv];
        lbl_803E7320.e[i].right = &lbl_803E7320.e[nx];
    }
    p->menu = m;
    {
        TileEntry* e = First();
        p->e40 = e;
        if (e) {
            p->e44 = e;
        }
    }
    {
        TileEntry* a = First();
        TileEntry* b = First();
        s8 ix = a->x;
        s8 iy = b->y;
        SetPos(p, 0.5f + ix, 0.5f + iy);
    }
    fn_800620A8(&lbl_803CAB38, First()->x, First()->y);
    m->v0C(p);
    m->count = 0;
    m->v1C(p);
    lbl_803CAB38.b92C = 0x10;
    return p;
}
}
