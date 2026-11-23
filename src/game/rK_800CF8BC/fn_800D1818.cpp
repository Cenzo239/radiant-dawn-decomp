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
#if TARGET_PC
FE10_PROTO void fn_8007E374(void*, p32arg, int);
#else
void fn_8007E374(void*, int, int);
#endif
void fn_800800D4(int);
void fn_80080388(f32, f32, f32, f32);
void fn_80080348(f32, f32, f32, f32);
void fn_80080368(f32, f32, f32, f32);
void fn_80080508(Color);
void fn_800804D4(int, int, int, int);
void fn_80080308();
#if TARGET_PC
FE10_PROTO void fn_80080928(ptr32<const void>, ptr32<const void>);
#else
void fn_80080928(void*, void*);
#endif
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
#if TARGET_PC
FE10_PROTO struct ItemRec * fn_8010B100(p32arg);
#else
int fn_8010B100(int);
#endif
void fn_80081A90(void*);
void fn_800068A0(void*, char*);
f32 fn_8017F68C(int, f32, f32, f32, f32);
void fn_800D1B4C(MovProc* p, Color c, int a, int b, f32 f);

void fn_800D1818(MovProc* p) {
    lbl_804CB700 |= 0x200000;
    fn_802356AC();
    fn_80236218(1);
    if (fn_80236384(p->name, 0, fn_8024DE78() == 3) == 0) {
        fn_80083DC4(p, 0x63);
        return;
    }
    fn_8023731C(&p->w);
    fn_80237364(p->o40);
    p->o30 = fn_80078D9C(-fn_80236680(), lbl_804CA488, 0);
    if (p->o30 == 0) {
        fn_80083DC4(p, 0x63);
        return;
    }
    fn_80236738(p->o30);
    p->o50 = 0;
    if (fn_80236A5C(0, p->b58 != 0, 0) == 0) {
        fn_80083DC4(p, 0x63);
        return;
    }
    fn_80237958(1.27f * p->o54, 0);
    fn_80236CDC();
}

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

void fn_800D1B4C(MovProc* p, Color c, int a, int b, f32 f) {
    void* v = fn_802356AC();
    c.r = (c.r * b) >> 7;
    c.g = (c.g * b) >> 7;
    c.b = (c.b * b) >> 7;
    c.a = (c.a * (a + 1)) >> 8;
    if (fn_801D09F0() == 0 && p->b59) {
        fn_8023721C(v, 0, 0x34, f, c, p->w, p->h - 0x68);
    } else {
        fn_8023721C(v, 0, 0, f, c, p->w, p->h);
    }
    fn_802373BC();
}

void fn_800D1CA4(MovProc* p) {
    lbl_804CB700 &= ~0x200000;
    fn_80236D3C();
    fn_8023662C();
    fn_80236334();
    if (p->name) {
        fn_80079474(p->name);
        p->name = 0;
    }
    if (p->o30) {
        fn_80078E24(p->o30);
        p->o30 = 0;
    }
}

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

void fn_800D20A4() { fn_80237958(0, 100); }

void fn_800D20B0() {
    void* p = fn_80085708(lbl_80366474 + 0xC);
    if (p) {
        fn_80083DC4(p, 0x63);
    }
}

int fn_800D20EC() {
    MovProc* p = (MovProc*)fn_80085708(lbl_80366474 + 0xC);
    if (p == 0) {
        return 0;
    }
    return !IsEnd(p);
}

int fn_800D2150() { return fn_80085708(lbl_80366474 + 0xC) != 0; }

void fn_800D2188(ChapProc* p) {
    p->t = 0;
    p->o34 = 0;
    if (fn_8010B100(p->o30) == 0) {
        fn_80081A90(p);
        return;
    }
    if (fn_801D09F0() == 0) {
        fn_80290D04(p->s44, 0x3F, lbl_80366474 + 0x14, LangStr(), p->o30 + 1);
    } else {
        fn_80290D04(p->s44, 0x3F, lbl_80366474 + 0x14, LangStr(), p->o30 + 1);
    }
    p->b83 = 0;
    fn_800068A0(&p->o34, p->s44);
}

void fn_800D2294(ChapProc* p) {
    p->t++;
    p->x = 0x40;
    if (p->t < 120.00001f) {
        p->b84 = 0;
    }
    if (p->t >= 120.00001f && p->t <= 210.00002f) {
        p->b85 = 8;
        p->y = fn_8017F68C(4, 156.0f, 116.0f, p->t - 120.00001f, 90.0f);
        p->b84 = fn_8017F68C(0, 0.0f, 255.0f, p->t - 120.00001f, 90.0f);
    }
    if (p->t >= 360.0f && p->t <= 480.00003f) {
        p->b84 = fn_8017F68C(0, 255.0f, 0.0f, p->t - 360.0f, 120.00001f);
    }
    if (p->t > 480.00003f) {
        fn_80083B78(p);
    }
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 0.0f, 1.0f);
    fn_8007E7DC(0xFF);
    fn_8007E374(p->o34, 0, 0x11);
    fn_8007E84C(1);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080348(p->x, p->y, 0.0f, 0.0f);
    {
        int w = 0x1E0;
        int h = 0xA0;
        fn_80080368(p->x + 0x1E0, p->y + 0xA0, w, h);
    }
    fn_800804D4(0xFF, 0xFF, 0xFF, p->b84);
    fn_80080308();
}
}
