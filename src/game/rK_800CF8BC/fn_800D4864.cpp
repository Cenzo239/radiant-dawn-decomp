/* fn_800D4864: menu cursor bar (round m25b). Helpers from fn_800D4528.cpp. The zero colour comes from a tiny inline returning a Color, so it is built at argument evaluation, after the constant colour copies (r0, not a saved register). */
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
void fn_800D4528();

void fn_800D452C();

void fn_800D4530();

void fn_800D4534();

int fn_800D4538();

int fn_800D4570();


static inline BOOL ItemEq(ItemProc* a, ItemProc* b) {
    return a == b;
}
void fn_800D45A8(MenuDef*, MenuProc* p);


static inline BOOL Paused(MenuProc* p) {
    return p->lockCnt || p->pause;
}

#pragma use_lmw_stmw off

void fn_800D46B8(MenuDef*, MenuProc* p);

#pragma use_lmw_stmw on

static inline ItemProc* Cur(MenuProc* p) { return fn_80085EF8(p->items[p->cur]); }

void fn_800D4864(MenuDef*, MenuProc* p);
void fn_800D4A10(MenuDef* m, MenuProc* p);

void fn_800D4CF0(MenuDef*, MenuProc* p);

void fn_800D4D68(MenuDef* m, MenuProc* p);

u8 fn_800D4DFC(MenuDef*, MenuProc* p);

void fn_800D4FAC(MenuProc* p);

void fn_800D53C4(MenuProc* p);

int fn_800D53DC(MenuProc* p);

void fn_800D53F4(MenuProc* p);

void fn_800D5400(MenuProc* p);


static inline int MenuH(MenuDef* m, s8 n) {
    return m->v5C() * n + m->v4C();
}

MenuProc* fn_800D5448(MenuDef* m, void* parent, int layer);
int fn_800D5684();

int fn_800D568C(MenuItem* i);

MenuProc* fn_800D569C(MenuProc* p);

void fn_800D56E8(MenuProc* p);


void fn_800D5798(MenuProc* p, MenuDef* m);
f32 fn_800D58FC(MenuProc* p);

void fn_800D5A04();

s16 fn_800D5A14();

s16 fn_800D5A60();

void fn_800D5AAC(void* p);

void fn_800D5AB0();

void fn_800D5AC4();

int fn_800D5AC8();

int fn_800D5AD0();

void fn_800D5AD8();

void fn_800D5ADC();

int fn_800D5AE0();

int fn_800D5AE8();


struct Sel {
    u8* unit;
    u8 pad4[2];
    s16 x6;
};
void fn_800D5AF0(Sel* s);

void fn_800D5B20(Sel* s);

}

/* ---- from rK_800CF8BC/wip/fn_800D4528.cpp ---- */
extern "C" {
/* fn_800D4864: ['DIFF fn_800D4864: 19 of 107 words differ'] */
static inline Color zc() { Color z; *(u32*)&z = 0; return z; }
void fn_800D4864(MenuDef*, MenuProc* p) {
    s16 y = Cur(p)->y;
    if (p->curY < 0) {
        p->curY = y;
    } else {
        p->curY = (p->curY + y) / 2;
    }
    fn_8007E154();
    fn_8007E4E4(p->x, p->y, p->def->v70() - 1.0f, 1.0f);
    fn_8007E174(0, 0x12);
    fn_8007E164();
    fn_800800D4(3);
    {
        f32 h = (s16)p->def->v5C();
        fn_80080388(0.0f, p->curY, p->w, h);
    }
    fn_80080578(0);
    fn_80080940(zc(), zc(), k1a, k1b);
    fn_80080308();
}
}
