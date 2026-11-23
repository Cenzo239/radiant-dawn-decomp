/* Layout part fade, split from fn_800D2560.cpp. lbl_804CD7D0 is the 0.0f constant: as an extern it keeps fcmpu a,0, where the literal flips the operands. */
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
#if TARGET_PC
FE10_PROTO ptr32<WinProc> fn_8014C828(void);
#else
WinProc* fn_8014C828();
#endif
void fn_80083E90(u8*, void*);
char* strcpy(char*, const char*);
void fn_800800D4(int);
void fn_80080308();
void fn_80080578(int);
void fn_80080940(Color, Color, Color, Color);
void fn_80080388(f32, f32, f32, f32);
void fn_800803C8(f32, f32, f32, f32);
void fn_80080494();
void fn_800D2690(Mov2*, Color, int, int, f32);
void fn_800D43B8(PartH*, int);

void fn_800D2690(Mov2* p, Color c, int a, int b, f32 f);

#pragma use_lmw_stmw off

#pragma use_lmw_stmw on

static inline void OutSet(Out6* o, s16 a, s16 b, u8 d) {
    o->a = a;
    o->b = b;
    o->c = d;
}

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

void fn_800D43B8(PartH* p, int t);

static inline int nz(f32 a) { return a != 0.0f; }
extern f32 lbl_804CD7D0;
void fn_800D3218(Layout* l, f32 f) {
    u8 m = l->mode;
    if (m == 0) {
        int i;
        for (i = l->n - 1; i >= 0; i--) {
            l->parts[i]->v0C(0xFF);
        }
    } else if (m == 2) {
        int i = f;
        int next = (i + 1) % l->n;
        f32 a = 255.99f * (f - (f32)(int)f);
        if (a != lbl_804CD7D0) {
            l->parts[next]->v0C(256.0f + a);
        }
        l->parts[i]->v0C(0x1FF - (int)a);
    } else if (m == 1) {
        l->parts[(int)f]->v0C(0xFF);
    }
}
}
