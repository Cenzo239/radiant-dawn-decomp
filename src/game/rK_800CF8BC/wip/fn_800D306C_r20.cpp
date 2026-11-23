/* Round 20 draft, NOT at a counted level (check_regs.py: other): fn_800D306C. Self-contained, complete source. Instruction count ours 103 orig 107. What differs: the original stores the four packed colours to four locals (0x18..0x24, dead stores) and then to the argument copies; here only the argument copies (frame 0x50 vs 0x60, 103 vs 107 instructions). */
#include "game/rK_800CF8BC/types.h"

#pragma use_lmw_stmw on

extern char lbl_80366474[];
extern char lbl_803E8E78[];
extern u8 lbl_80383CF0[];
extern u32 lbl_804CB700;
extern u8 lbl_803664C4[];
extern u8 lbl_80383D68[];
extern u8 lbl_80383DD4[];
extern u8 lbl_80383E1C[];
extern u8 lbl_80383EBC[];
extern u8 lbl_80386B50[];
extern u8 lbl_80383E94[];
extern u8 lbl_80383E80[];
extern u8 lbl_80383E6C[];
extern u8 lbl_80383EA8[];
extern u8 lbl_80383E58[];


struct Color {
    u8 r, g, b, a;
};

struct S2 {
    u8 proc[0x30];
    void* o30;
    void* o34;
};

struct Mov2 {
    u8 pad0[2];
    s16 z;
    u8 pad4[4];
    char* name;
    s16 xC;
    s16 xE;
    u32 fl;
    void* buf;
    int o18;
    int o1C;
};

/* Window part, base of the layout parts. vptr at +4. */
struct PartB {
    u8 type;
    u8 pad1;
    s16 z;
};
class Part : public PartB {
public:
    virtual void v08(int);
    virtual void v0C(int);
    virtual void v10();
};

class PicPart : public Part {
public:
    char* path;  /* 0x08 */
    void* tex;   /* 0x0C */
    u8 fl;       /* 0x10 */
    u8 b11;      /* 0x11 */
    u8 b12;      /* 0x12 */
    u8 b13;      /* 0x13 */
    s16 x0;      /* 0x14 */
    s16 y0;      /* 0x16 */
    s16 x1;      /* 0x18 */
    s16 y1;      /* 0x1A */
    u16 u0;      /* 0x1C */
    u16 v0;      /* 0x1E */
    u16 u1;      /* 0x20 */
    u16 v1;      /* 0x22 */
    Color c[4];  /* 0x24 */
};

struct RectPart {
    u8 type;
    u8 pad1;
    s16 z;
    void* vt;
    s16 x0, y0, x1, y1; /* 0x08 */
    Color c[4];         /* 0x10 */
};

struct TextPart {
    u8 type;
    u8 pad1;
    s16 z;
    void* vt;
    char* msg;  /* 0x08 */
    s16 x;      /* 0x0C */
    s16 y;      /* 0x0E */
    u8 b10;
    u8 b11;
    u8 color;   /* 0x12 */
    u8 pad13;
    s8 align;   /* 0x14 */
};

struct ListEntry {
    s16 a;
    s16 b;
    u8 c;
    u8 pad5;
    u8 d;
    u8 pad7;
};
struct ListPart {
    u8 pad[8];
    s16 n;   /* 0x08 */
    ListEntry e[1];
};
struct Out6 {
    s16 a, b, c;
};
extern Out6 lbl_803E50F0[];

struct Layout {
    u8 pad0[4];
    u8 n;      /* 0x04 */
    u8 mode;   /* 0x05 */
    u16 z;     /* 0x06 */
    f32 rate;  /* 0x08 */
    u8 bC;
    u8 bD;
    u8 bE;
    u8 bF;
    u8 pad10[4];
    Part* parts[1]; /* 0x14 */
};

struct WinProc {
    u8 proc[0x28];
    s16 sleep;
    u8 pad2A[6];
    Layout* l;   /* 0x30 */
    f32 frames;  /* 0x34 */
    f32 rate;    /* 0x38 */
    f32 cur;     /* 0x3C */
    f32 x;       /* 0x40 */
    f32 y;       /* 0x44 */
    f32 z;       /* 0x48 */
    f32 w;       /* 0x4C */
    f32 h;       /* 0x50 */
    f32 sx;      /* 0x54 */
    f32 sy;      /* 0x58 */
    f32 rot;     /* 0x5C */
    void* fence; /* 0x60 */
    u8 alpha;    /* 0x64 */
    u8 b65;      /* 0x65 */
};

struct FadeProc {
    u8 proc[0x30];
    WinProc* win;
    int t;
    int d;
    int from;
    int to;
};

struct TweenProc {
    u8 proc[0x18];
    WinProc* parent;
    u8 pad1C[0x14];
    WinProc* win; /* 0x30 */
    u8 k;         /* 0x34 */
    u8 type;      /* 0x35 */
    u8 pad36[2];
    f32 t;        /* 0x38 */
    f32 dur;      /* 0x3C */
    f32 from;     /* 0x40 */
    f32 to;       /* 0x44 */
};

struct PartH {
    u8 type;
    u8 size;
    u8 pad[2];
    void* vt;
};
extern char* lbl_804CB718;
extern WinProc* lbl_804CB71C;
extern u8 lbl_804CB720;
extern "C" {
int fn_801D09F0();
int fn_80291188(const char*, const char*);
WinProc* fn_8014C828();
void fn_80083E90(u8*, void*);
void fn_800846BC(u8*);
void fn_80081A90(void*);
void fn_8023F1A0(char*, int);
void fn_80006A2C(void*);
void* fn_80085708(const char*);
void* fn_80081050(u8*, void*);
char* strcpy(char*, const char*);
char* fn_80291314(const char*, int);
int fn_80290DDC(char*, const char*, ...);
void* fn_802356AC();
void fn_8023721C(void*, int, int, int, Color, int, int);
void fn_802373BC();
int fn_8024DE78();
int fn_80236384(char*, int, int);
void fn_8023731C(void*);
int fn_80236680();
void* fn_80079958(int, int);
void fn_80236738(void* buf);
int fn_80236A5C(int, int, int);
int fn_802373AC();
void fn_80236CDC();
void fn_8007E154();
void fn_8007E164();
void fn_8007E174(void*, int);
void fn_800800D4(int);
void fn_8008031C(f32);
void fn_800804F4(u8);
void fn_80080928(void*, void*);
void fn_80080308();
void fn_80236D3C();
void fn_8023662C();
void fn_80079978(void*);
void fn_800068EC(void*, void*, int);
int fn_80006CC8(void*, int);
void fn_8007E41C(void*, int, int, int);
void fn_8007E374(void*, int, int);
void fn_800803F0(f32, f32, f32, f32);
void fn_80080410(f32, f32, f32, f32);
void fn_80080578(int);
void fn_80080940(Color, Color, Color, Color);
const char* fn_800D0864(const char*);
int fn_800CA3DC(const char*, int, f32);
void fn_80080330(f32, f32);
Color* fn_800CD204(int);
void fn_80080508(Color);
void fn_80080ABC(int, f32);
void fn_80080B70(int, f32);
void fn_80080C24(const char*);
void* fn_80077064(const char*);
void fn_8014D9FC(WinProc*, u8*);
void fn_8014E314(WinProc*);
void fn_8014ECD4(WinProc*, f32);
void fn_8014ED80(WinProc*, f32);
void fn_8007E5C0(f32, f32, f32, f32, f32, f32, f32, f32);
void fn_8007E84C(int);
void fn_8007E7DC(int);
void fn_8007E7E8(int);
void fn_8007E4E4(f32, f32, f32, f32);
void fn_80080388(f32, f32, f32, f32);
void fn_800803C8(f32, f32, f32, f32);
void fn_80080494();
f32 fn_8017F68C(int, f32, f32, f32, f32);
void fn_80083B78(void*);
void fn_80083DC4(void*, int);
void fn_800D2690(Mov2*, Color, int, int, f32);
void fn_800D43B8(PartH*, int);
void fn_800D3218(Layout*, f32);
void fn_800D2560(S2* p);

void fn_800D2578(void* a);

char* fn_800D25D4(char* out, const char* in);

void fn_800D2690(Mov2* p, Color c, int a, int b, f32 f);

void fn_800D2768(Mov2* p);

void fn_800D27E0(Mov2* p, int a);

void fn_800D2890(Mov2* p);

void fn_800D28D8(PicPart* p);

void fn_800D2980(PicPart* p);

void fn_800D29C8(PicPart* p, int a);


#pragma use_lmw_stmw off

void fn_800D2BD0(PicPart* p, int a);


void fn_800D306C(RectPart* p);
#pragma use_lmw_stmw on

void fn_800D2E48(TextPart* p, int a);


static inline void OutSet(Out6* o, s16 a, s16 b, u8 d) {
    o->a = a;
    o->b = b;
    o->c = d;
}
void fn_800D3008(ListPart* p);


void fn_800D3218(Layout* l, f32 f);
void fn_800D339C(WinProc* p, const char* name);


static inline void FenceDraw() {
    Color c0 = {0xFF, 0xFF, 0xFF, 0xFF};
    Color c1 = {0xFF, 0xFF, 0xFF, 0x00};
            fn_800800D4(1);
            fn_80080388(0.0f, 0.0f, 72.0f, 448.0f);
            fn_800803C8(0.0f, 0.0f, 72.0f, 448.0f);
            fn_80080308();
            fn_800800D4(3);
            fn_80080388(72.0f, 0.0f, 20.0f, 448.0f);
            fn_800803C8(72.0f, 0.0f, 20.0f, 448.0f);
            fn_80080578(0);
            fn_80080940(c0, c1, c0, c1);
            fn_80080308();
            fn_800800D4(3);
            fn_80080388(516.0f, 0.0f, 20.0f, 448.0f);
            fn_800803C8(72.0f, 0.0f, 20.0f, 448.0f);
            fn_80080494();
            fn_80080578(0);
            fn_80080940(c1, c0, c1, c0);
            fn_80080308();
            fn_800800D4(1);
            fn_80080388(536.0f, 0.0f, 72.0f, 448.0f);
            fn_800803C8(0.0f, 0.0f, 72.0f, 448.0f);
            fn_80080494();
            fn_80080308();
}

void fn_800D363C(WinProc* p);
void fn_800D3928(WinProc* p, f32 f);

f32 fn_800D395C(WinProc* p);

void fn_800D3990(WinProc* p);

void fn_800D39D4(WinProc* p, int a);

void fn_800D3B00(FadeProc* p);

void fn_800D3BCC(WinProc* w, int d);

void fn_800D3C30(WinProc* w, int d);

void fn_800D3C90(WinProc* w, int d);

u8 fn_800D3CF4(WinProc* p);

void fn_800D3D00(WinProc* p, u8 k, f32 f);

f32 fn_800D3DA8(WinProc* p, u8 k);

void fn_800D3E58(TweenProc* p);

void fn_800D3ECC(TweenProc* p);

void fn_800D3EE0(WinProc* w, int k, int type, f32 from, f32 to, f32 dur);

void fn_800D40C8(WinProc* p);

void fn_800D40F4(WinProc* p);

WinProc* fn_800D4188(const char* name, void* parent);


struct LayoutH {
    char* name;
};
void fn_800D41E4(WinProc* p);


static inline WinProc* WinFind(char* s) {
    if (s[0] == 'T' && s[1] == 'B' && s[2] == 'G' && s[3] == 0) {
        return fn_8014C828();
    }
    lbl_804CB71C = 0;
    lbl_804CB718 = s;
    fn_80083E90(lbl_80383E1C, fn_800D41E4);
    return lbl_804CB71C;
}
WinProc* fn_800D4228(char* s);

void fn_800D42A0(char* s);

void fn_800D433C(const char* name);

void fn_800D43B8(PartH* p, int t);

void fn_800D44D4(WinProc* p);

u8 fn_800D44EC();

}

#pragma use_lmw_stmw off
/* ---- from rK_800CF8BC/wip/fn_800D2560.cpp ---- */
extern "C" {
/* fn_800D306C: ['DIFF fn_800D306C: 35 of 103 words differ'] */
void fn_800D306C(RectPart* p) {
    fn_8007E154();
    fn_8007E174(0, 0x10);
    fn_8007E164();
    fn_800800D4(3);
    fn_8008031C(p->z);
    fn_800803F0(p->x0, p->y0, p->x1, p->y1);
    fn_80080578(0);
    {
        u32 c0 = p->c[0].a + (p->c[0].b << 8) + ((p->c[0].r << 24) + (p->c[0].g << 16));
        u32 c1 = p->c[1].a + (p->c[1].b << 8) + ((p->c[1].r << 24) + (p->c[1].g << 16));
        u32 c2 = p->c[2].a + (p->c[2].b << 8) + ((p->c[2].r << 24) + (p->c[2].g << 16));
        u32 c3 = p->c[3].a + (p->c[3].b << 8) + ((p->c[3].r << 24) + (p->c[3].g << 16));
        fn_80080940(*(Color*)&c0, *(Color*)&c1, *(Color*)&c2, *(Color*)&c3);
    }
    fn_80080308();
}
}
