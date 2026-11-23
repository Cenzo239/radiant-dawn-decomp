/* fn_800D1EDC: functionally equal (regs, 18 of 114 words differ in registers only). Helpers from fn_800D1818.cpp (exported bodies removed), body from wip/fn_800D1818.cpp. */
#include "game/rK_800CF8BC/types.h"

#pragma use_lmw_stmw on

extern u32 lbl_804CB700;
extern char lbl_804CA488[4];
extern char lbl_804CA48C[8];
extern char lbl_804CA0C0[8];
extern const char* lbl_8037AB10[];
extern char lbl_80366474[];
extern u8 lbl_80383CC0[];
extern u8 lbl_80383C70[];
extern u8 lbl_80383D28[];
extern char lbl_80383D18[];

struct Color {
    u8 r, g, b, a;
};
static inline Color MkColor(u8 r, u8 g, u8 b, u8 a) {
    Color c;
    c.r = r;
    c.g = g;
    c.b = b;
    c.a = a;
    return c;
}

struct MovProc {
    u8 proc[0x30];
    void* o30;
    int w;   /* 0x34 */
    int h;   /* 0x38 */
    u8 pad3C[4];
    u8 o40[0x10];
    int o50;
    int o54;
    u8 b58;
    u8 b59;
    u8 pad5A[2];
    char* name; /* 0x5C */
};

struct CapMain {
    u8 proc[0x30];
    char* o30;
    void* o34;
    void* o38;
    void* o3C;
    u32 t;
};

struct CapName {
    const char* name;
    const char** e;
};

struct ChapProc {
    u8 proc[0x30];
    int o30;
    void* o34;
    int t;     /* 0x38 */
    u8 pad3C[4];
    s16 x;     /* 0x40 */
    s16 y;     /* 0x42 */
    char s44[0x3F];
    u8 b83;
    u8 b84;
    u8 b85;
};

static const Color k1 = {0, 0, 0, 0xFF};
static const Color k2 = {0, 0, 0, 0xFF};
extern "C" {
int fn_801D09F0();
void* fn_802356AC();
void fn_80236218(int);
int fn_8024DE78();
int fn_80236384(void*, int, int);
void fn_8023731C(void*);
void fn_80237364(void*);
int fn_80236680();
void* fn_80078D9C(int, char*, int);
void fn_80236738(void* buf);
int fn_80236A5C(int, int, int);
void fn_80237958(int, int);
void fn_80236CDC();
void fn_80083DC4(void*, int);
void fn_80083B78(void*);
void fn_8007E154();
void fn_8007E164();
void fn_8007E4E4(f32, f32, f32, f32);
void fn_8007E7DC(int);
void fn_8007E7E8(int);
void fn_8007E84C(int);
void fn_8007E174(void*, int);
void fn_8007E7B4();
void fn_8007E374(void*, int, int);
void fn_800800D4(int);
void fn_80080388(f32, f32, f32, f32);
void fn_80080348(f32, f32, f32, f32);
void fn_80080368(f32, f32, f32, f32);
void fn_80080508(Color);
void fn_800804D4(int, int, int, int);
void fn_80080308();
void fn_80080928(void*, void*);
int fn_802373AC();
void fn_802373BC();
void fn_8023721C(void*, int, int, int, Color, int, int);
void fn_80236D3C();
void fn_8023662C();
void fn_80236334();
void fn_80079474(void*);
void fn_80078E24(void*);
int fn_8023F9F4(const char*);
void* fn_80081050(u8*, void*);
void* fn_800791B0(int);
void fn_802910CC(char*, const char*, int);
void* fn_80075FB4(u8*, int);
void* fn_80076F54(const char*);
char* fn_80291314(const char*, int);
int fn_80291C44(const char*, const char*);
u8* fn_8024BC94();
int fn_80290D04(char*, int, const char*, ...);
void fn_8023F1A0(char*, int);
void* fn_80085708(const char*);
int fn_8010B100(int);
void fn_80081A90(void*);
void fn_800068A0(void*, char*);
f32 fn_8017F68C(int, f32, f32, f32, f32);
void fn_800D1B4C(MovProc* p, Color c, int a, int b, f32 f);
void fn_800D1818(MovProc* p);


static inline BOOL IsEnd(MovProc* p) {
    BOOL r = 0;
    if (p->b58 == 0) {
        r = fn_802373AC() == 3;
    }
    return r;
}

static inline void BarTop() {
    fn_800800D4(1);
    {
        int h = 0x34;
        fn_80080388(0.0f, 0.0f, 608.0f, h);
    }
    fn_80080508(k1);
    fn_80080308();
}

static inline void BarBottom() {
    fn_800800D4(1);
    {
        int y = 0x18C;
        fn_80080388(0.0f, y, 608.0f, 448.0f);
    }
    fn_80080508(k2);
    fn_80080308();
}

static inline void Bars() {
    BarTop();
    BarBottom();
}

void fn_800D194C(MovProc* p);
void fn_800D1B4C(MovProc* p, Color c, int a, int b, f32 f);

void fn_800D1CA4(MovProc* p);


static inline s8 Lang() {
    return fn_8024BC94()[0x1BC8];
}

static inline const char* LangStr() {
    s8 l = Lang();
    return l >= 0 ? lbl_8037AB10[l] : lbl_804CA0C0;
}

static inline void CapCreate(MovProc* p, const char* s) {
    u32 i;
    u32 cnt;
    CapName* n;
    CapMain* c;
    c = (CapMain*)fn_80081050(lbl_80383C70, p);
    c->o30 = 0;
    c->o34 = fn_80075FB4(lbl_80383D28, 0x80);
    c->o38 = 0;
    c->o3C = 0;
    c->t = 0;
    {
        u32* t = (u32*)fn_80076F54(lbl_80383D18);
        cnt = t[0];
        n = (CapName*)(t + 1);
    }
    for (i = 0; i < cnt; i++, n++) {
        if (fn_80291C44(n->name, fn_80291314(s, '/') + 1) == 0) {
            c->o30 = (char*)fn_800791B0(0x100);
            {
                const char* l = LangStr();
                fn_80290D04(c->o30, 0xFF, lbl_804CA48C, n->e[0], l, n->e[1]);
            }
            c->o30[0xFF] = 0;
            if (fn_8023F9F4(c->o30) != 0x40000) {
                fn_8023F1A0(c->o30, 0x2080);
                c->o3C = n->e + 2;
                break;
            }
        }
    }
    if (c->o3C == 0) {
        fn_80083DC4(c, 2);
    }
}

void fn_800D1D14(const char* name, u8 a, u8 b);

void fn_800D1EDC(const char* name, int vol, u8 a, u8 b);
void fn_800D20A4();

void fn_800D20B0();

int fn_800D20EC();

int fn_800D2150();

void fn_800D2188(ChapProc* p);

void fn_800D2294(ChapProc* p);

}

/* ---- from rK_800CF8BC/wip/fn_800D1818.cpp ---- */
extern "C" {


/* fn_800D1EDC: ['DIFF fn_800D1EDC: 18 of 114 words differ'] */
void fn_800D1EDC(const char* name, int vol, u8 a, u8 b) {
    MovProc* p;
    if (fn_8023F9F4(name) == 0x40000) {
        name = lbl_80366474;
    }
    p = (MovProc*)fn_80081050(lbl_80383CC0, (void*)3);
    p->name = (char*)fn_800791B0(0x100);
    fn_802910CC(p->name, name, 0xFE);
    p->name[0xFF] = 0;
    CapCreate(p, p->name);
    p->o54 = vol;
    p->b58 = a;
    p->b59 = b;
    p->o30 = 0;
}
}
