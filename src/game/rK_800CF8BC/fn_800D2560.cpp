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
#if TARGET_PC
FE10_PROTO ptr32<WinProc> fn_8014C828(void);
#else
WinProc* fn_8014C828();
#endif
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
#if TARGET_PC
FE10_PROTO void fn_80080928(ptr32<const void>, ptr32<const void>);
#else
void fn_80080928(void*, void*);
#endif
void fn_80080308();
void fn_80236D3C();
void fn_8023662C();
void fn_80079978(void*);
void fn_800068EC(void*, void*, int);
int fn_80006CC8(void*, int);
#if TARGET_PC
FE10_PROTO void fn_8007E41C(void*, p32arg, int, int);
#else
void fn_8007E41C(void*, int, int, int);
#endif
#if TARGET_PC
FE10_PROTO void fn_8007E374(void*, p32arg, int);
#else
void fn_8007E374(void*, int, int);
#endif
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

void fn_800D2560(S2* p) {
    if (p->o34) {
        fn_80006A2C(&p->o34);
    }
}

void fn_800D2578(void* a) {
    void* p = fn_80085708(lbl_80366474 + 0xC);
    if (p) {
        S2* q = (S2*)fn_80081050(lbl_80383CF0, p);
        q->o30 = a;
        q->o34 = 0;
    }
}

char* fn_800D25D4(char* out, const char* in) {
    if (fn_801D09F0() == 0) {
        char* d;
        strcpy(lbl_803E8E78, in);
        d = fn_80291314(lbl_803E8E78, '.');
        if (d == 0) {
            strcpy(out, in);
        } else {
            *d = 0;
            fn_80290DDC(out, lbl_80366474 + 0x2C, lbl_803E8E78, d + 1);
        }
    } else {
        strcpy(out, in);
    }
    return out;
}

void fn_800D2690(Mov2* p, Color c, int a, int b, f32 f) {
    void* v = fn_802356AC();
    c.r = (c.r * b) >> 7;
    c.g = (c.g * b) >> 7;
    c.b = (c.b * b) >> 7;
    c.a = (c.a * (a + 1)) >> 8;
    fn_8023721C(v, p->xC, p->xE, f, c, p->o18, p->o1C);
    fn_802373BC();
}

void fn_800D2768(Mov2* p) {
    fn_80236384(p->name, p->fl & 1, fn_8024DE78() == 3);
    fn_8023731C(&p->o18);
    p->buf = fn_80079958(fn_80236680(), 0x40);
    fn_80236738(p->buf);
    fn_80236A5C(0, (p->fl >> 1) & 1, 0);
}

void fn_800D27E0(Mov2* p, int a) {
    switch (fn_802373AC()) {
    case 1:
        fn_80236CDC();
        break;
    case 5:
        break;
    }
    fn_8007E154();
    fn_8007E174(0, 0x410);
    fn_8007E164();
    fn_800800D4(0xC);
    fn_8008031C(p->z);
    fn_800804F4(a);
    fn_80080928(fn_800D2690, p);
    fn_80080308();
}

void fn_800D2890(Mov2* p) {
    fn_80236D3C();
    fn_8023662C();
    if (p->buf) {
        fn_80079978(p->buf);
        p->buf = 0;
    }
}

void fn_800D28D8(PicPart* p) {
    if (!(p->fl & 0x80)) {
        int f = 0;
        if (p->fl & 1) {
            f |= 0x20;
        }
        if (p->fl & 4) {
            f |= 0x80;
        }
        if (p->fl & 8) {
            f |= 0x1000;
        }
        if (p->fl & 0x10) {
            f |= 0x2000;
        }
        fn_800068EC(&p->tex, p->path, f);
        if (fn_80006CC8(p->tex, p->b12)) {
            p->fl |= 2;
            p->b11 = 0;
        }
        p->fl |= 0x80;
    }
}

void fn_800D2980(PicPart* p) {
    if (p->fl & 0x80) {
        fn_80006A2C(&p->tex);
        p->fl &= 0x7F;
    }
}

void fn_800D29C8(PicPart* p, int a) {
    int f;
    if (!(p->fl & 0x80)) {
        p->v08(0);
    }
    f = 0x10;
    if (a >= 0x100) {
        f = 0x20;
        a -= 0x100;
    }
    if (a != 0) {
        s16 dx, dy;
        fn_8007E154();
        if (p->fl & 2) {
            fn_8007E41C(p->tex, p->b12, p->b11, f | 1);
        } else {
            fn_8007E374(p->tex, p->b12, f | 1);
        }
        fn_8007E164();
        dx = p->u1 - p->u0;
        if (dx < 0) {
            dx = -dx;
        }
        dy = p->v1 - p->v0;
        if (dy < 0) {
            dy = -dy;
        }
        if (p->x1 == p->x0) {
            p->x1 = p->x0 + dx;
        }
        if (p->y1 == p->y0) {
            p->y1 = p->y0 + dy;
        }
        {
            u8 al = a;
            if (al == 0xFF) {
                al = p->b13;
            }
            fn_800800D4(1);
            fn_8008031C(p->z);
            fn_800803F0(p->x0, p->y0, p->x1, p->y1);
            fn_80080410(p->u0, p->v0, p->u1, p->v1);
            fn_800804F4(al);
            fn_80080308();
        }
    }
}

#pragma use_lmw_stmw off
void fn_800D2BD0(PicPart* p, int a) {
    fn_8007E154();
    if (p->fl & 2) {
        fn_8007E41C(p->tex, p->b12, p->b11, 0x11);
    } else {
        fn_8007E374(p->tex, p->b12, 0x11);
    }
    fn_8007E164();
    if (p->x1 == p->x0) {
        p->x1 = p->x0 + p->u1 - p->u0;
    }
    if (p->y1 == p->y0) {
        p->y1 = p->y0 + p->v1 - p->v0;
    }
    {
        u8 al = a;
        Color c0, c1, c2, c3;
        if (al == 0xFF) {
            al = p->b13;
        }
        c0.r = p->c[0].r;
        c0.g = p->c[0].g;
        c0.b = p->c[0].b;
        c0.a = (al * p->c[0].a) >> 8;
        c1.r = p->c[1].r;
        c1.g = p->c[1].g;
        c1.b = p->c[1].b;
        c1.a = (al * p->c[1].a) >> 8;
        c2.r = p->c[2].r;
        c2.g = p->c[2].g;
        c2.b = p->c[2].b;
        c2.a = (al * p->c[2].a) >> 8;
        c3.r = p->c[3].r;
        c3.g = p->c[3].g;
        c3.b = p->c[3].b;
        c3.a = (al * p->c[3].a) >> 8;
        fn_800800D4(3);
        fn_8008031C(p->z);
        fn_800803F0(p->x0, p->y0, p->x1, p->y1);
        fn_80080410(p->u0, p->v0, p->u1, p->v1);
        fn_80080578(0);
        fn_80080940(c0, c1, c2, c3);
        fn_80080308();
    }
}

void fn_800D306C(RectPart* p);
#pragma use_lmw_stmw on

void fn_800D2E48(TextPart* p, int a) {
    f32 x = 0.0f;
    const char* s = fn_800D0864(p->msg);
    switch (p->align) {
    case -1:
        x = p->x;
        break;
    case 0:
        x = p->x - fn_800CA3DC(s, -1, 1.0f) / 2;
        break;
    case 1:
        x = p->x - fn_800CA3DC(s, -1, 1.0f);
        break;
    }
    fn_8007E154();
    fn_8007E174(0, 0x13);
    fn_8007E164();
    fn_800800D4(5);
    fn_80080330(x, p->y);
    fn_8008031C(p->z);
    fn_80080508(*fn_800CD204(p->color));
    fn_800804F4(a);
    fn_80080ABC(p->b10, 2.0f);
    fn_80080B70(p->b11, 1.0f);
    fn_80080C24(s);
    fn_80080308();
}

static inline void OutSet(Out6* o, s16 a, s16 b, u8 d) {
    o->a = a;
    o->b = b;
    o->c = d;
}

void fn_800D3008(ListPart* p) {
    int n = 0;
    int i;
    for (i = 0; i < p->n; i++) {
        switch (p->e[i].c) {
        case 0:
            OutSet(&lbl_803E50F0[(s8)n++], p->e[i].a, p->e[i].b, p->e[i].d);
            break;
        }
    }
}

void fn_800D3218(Layout* l, f32 f);

void fn_800D339C(WinProc* p, const char* name) {
    Layout* l;
    int i;
    Layout* q;
    p->z = 0.0f;
    p->y = 0.0f;
    p->x = 0.0f;
    p->h = 0.0f;
    p->w = 0.0f;
    p->sy = 1.0f;
    p->sx = 1.0f;
    p->rot = 0.0f;
    p->alpha = 0xFF;
    p->b65 = 0x80;
    p->fence = 0;
    l = (Layout*)fn_80077064(name);
    p->l = l;
    q = l;
    for (i = 0; i < l->n; i++) {
        fn_800D43B8((PartH*)q->parts[0], q->parts[0]->type);
        if (q->parts[0]->type == 2) {
            *(s16*)((u8*)q->parts[0] + 0x24) = l->z;
        }
        q->parts[0]->v08(l->bF);
        q = (Layout*)((u8*)q + 4);
    }
    switch (p->l->bE) {
    case 1:
        fn_8014D9FC(p, &p->alpha);
        break;
    case 2:
        fn_8014E314(p);
        break;
    case 3:
        fn_8014ECD4(p, -1.0f);
        break;
    case 4:
        fn_8014ED80(p, -1.0f);
        break;
    }
    p->h = 0.0f;
    p->w = 0.0f;
    {
        PicPart* pic = (PicPart*)p->l->parts[0];
        switch (pic->type) {
        case 1:
            p->w = pic->u1 - pic->u0;
            p->h = pic->v1 - pic->v0;
            break;
        }
    }
    p->w *= 0.5f;
    p->h *= 0.5f;
    if (p->l->bC != 0 && p->l->bC != 0xFF) {
        p->b65 = (p->l->bC >> 1) + 1;
    }
    p->cur = 0.0f;
    if (p->l->n == 1 || p->l->rate == 0.0f) {
        p->frames = 1.0f;
        p->rate = 0.0f;
    } else {
        p->frames = p->l->n;
        p->rate = p->frames / (60.0f * p->l->rate);
    }
    if (fn_801D09F0() && (p->l->bF & 0x80)) {
        fn_800068EC(&p->fence, lbl_803664C4, 0x80);
    }
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

void fn_800D363C(WinProc* p);
void fn_800D3928(WinProc* p, f32 f) { p->z = f - (f32)p->l->z; }
f32 fn_800D395C(WinProc* p) { return p->z + (f32)p->l->z; }

void fn_800D3990(WinProc* p) {
    if (p->fence) {
        fn_80006A2C(&p->fence);
        p->fence = 0;
    }
}

void fn_800D39D4(WinProc* p, int a) {
    f32 h = 0.0f;
    f32 w = h;
    PicPart* pic = (PicPart*)p->l->parts[0];
    switch (pic->type) {
    case 1:
        w = pic->u1 - pic->u0;
        h = pic->v1 - pic->v0;
        break;
    }
    w = 608.0f - w;
    h = 448.0f - h;
    {
        f32 cx = w / 2.0f;
        f32 cy = h / 2.0f;
        switch (a) {
        case 1:
            p->y = h;
            p->x = 0.0f;
            break;
        case 2:
            p->x = cx;
            p->y = h;
            break;
        case 3:
            p->x = w;
            p->y = h;
            break;
        case 4:
            p->y = cy;
            p->x = 0.0f;
            break;
        case 5:
            p->x = cx;
            p->y = cy;
            break;
        case 6:
            p->x = w;
            p->y = cy;
            break;
        case 7:
            p->x = 0.0f;
            p->y = 0.0f;
            break;
        case 8:
            p->x = cx;
            p->y = 0.0f;
            break;
        case 9:
            p->x = w;
            p->y = 0.0f;
            break;
        }
    }
}

void fn_800D3B00(FadeProc* p) {
    WinProc* w = p->win;
    p->t++;
    w->alpha = fn_8017F68C(0, p->from, p->to, p->t, p->d);
    if (p->t >= p->d) {
        fn_80083B78(p);
    }
}

void fn_800D3BCC(WinProc* w, int d) {
    FadeProc* p = (FadeProc*)fn_80081050(lbl_80383D68, w);
    p->win = w;
    p->t = 0;
    p->d = d;
    p->from = 0;
    p->to = 0xFF;
    w->alpha = 0;
}

void fn_800D3C30(WinProc* w, int d) {
    FadeProc* p = (FadeProc*)fn_80081050(lbl_80383D68, w);
    p->win = w;
    p->t = 0;
    p->d = d;
    p->from = w->alpha;
    p->to = 0;
}

void fn_800D3C90(WinProc* w, int d) {
    FadeProc* p = (FadeProc*)fn_80081050(lbl_80383D68, w);
    p->win = w;
    p->t = 0;
    p->d = d;
    p->from = w->alpha;
    p->to = 0;
    w->sleep = d;
}

u8 fn_800D3CF4(WinProc* p) { return p->l->bD; }

void fn_800D3D00(WinProc* p, u8 k, f32 f) {
    if (123456792.0f != f) {
        switch (k) {
        case 0: p->x = f; break;
        case 1: p->y = f; break;
        case 2: p->z = f; break;
        case 3: p->w = f; break;
        case 4: p->h = f; break;
        case 5: p->sx = f; break;
        case 6: p->sy = f; break;
        case 7: p->sx = f; p->sy = f; break;
        case 8: p->rot = f; break;
        case 9: p->alpha = (int)f; break;
        case 10: p->b65 = (int)f; break;
        }
    }
}

f32 fn_800D3DA8(WinProc* p, u8 k) {
    switch (k) {
    case 0: return p->x;
    case 1: return p->y;
    case 2: return p->z;
    case 3: return p->w;
    case 4: return p->h;
    case 5: case 7: return p->sx;
    case 6: return p->sy;
    case 8: return p->rot;
    case 9: return p->alpha;
    case 10: return p->b65;
    }
    return 0.0f;
}

void fn_800D3E58(TweenProc* p) {
    p->t += 16.666666f;
    if (p->t >= p->dur) {
        p->t = p->dur;
        fn_80083B78(p);
    }
    fn_800D3D00(p->win, p->k, fn_8017F68C(p->type, p->from, p->to, p->t, p->dur));
}

void fn_800D3ECC(TweenProc* p) { fn_800D3D00(p->win, p->k, p->to); }

void fn_800D3EE0(WinProc* w, int k, int type, f32 from, f32 to, f32 dur) {
    if ((lbl_804CB700 & 3) != 0 || dur == 0.0f) {
        fn_800D3D00(w, k, to);
    } else if (from == to) {
        fn_800D3D00(w, k, from);
    } else {
        TweenProc* q = (TweenProc*)fn_80081050(lbl_80383DD4, w);
        q->win = q->parent;
        q->k = k;
        q->type = type;
        if (123456792.0f == from) {
            q->from = fn_800D3DA8(q->win, k);
        } else {
            q->from = from;
        }
        q->to = to;
        q->dur = (int)dur;
        q->t = 0.0f;
        fn_800D3D00(w, k, from);
    }
}

void fn_800D40C8(WinProc* p) {
    p->cur += p->rate;
    if (p->cur >= p->frames) {
        p->cur -= p->frames;
    }
    fn_800D363C(p);
}

void fn_800D40F4(WinProc* p) {
    int i;
    Layout* q;
    Layout* l = p->l;
    if (l) {
        q = l;
        i = 0;
        for (; i < l->n; i++) {
            q->parts[0]->v10();
            q = (Layout*)((u8*)q + 4);
        }
        if (p->fence) {
            fn_80006A2C(&p->fence);
        }
    }
}

WinProc* fn_800D4188(const char* name, void* parent) {
    WinProc* p = (WinProc*)fn_80081050(lbl_80383E1C, parent ? parent : (void*)3);
    fn_800D339C(p, name);
    return p;
}

struct LayoutH {
    char* name;
};

void fn_800D41E4(WinProc* p) {
    if (fn_80291188(*(char**)p->l, lbl_804CB718) == 0) {
        lbl_804CB71C = p;
    }
}

static inline WinProc* WinFind(char* s) {
    if (s[0] == 'T' && s[1] == 'B' && s[2] == 'G' && s[3] == 0) {
        return fn_8014C828();
    }
    lbl_804CB71C = 0;
    lbl_804CB718 = s;
    fn_80083E90(lbl_80383E1C, fn_800D41E4);
    return lbl_804CB71C;
}

WinProc* fn_800D4228(char* s) { return WinFind(s); }

void fn_800D42A0(char* s) {
    if (s == 0) {
        fn_800846BC(lbl_80383E1C);
    } else {
        WinProc* p = WinFind(s);
        if (p) {
            fn_80081A90(p);
        }
    }
}

void fn_800D433C(const char* name) {
    int i;
    Layout* q;
    Layout* l = (Layout*)fn_80077064(name);
    i = 0;
    q = l;
    for (; i < l->n; i++) {
        PicPart* p = (PicPart*)q->parts[0];
        switch (p->type) {
        case 1:
            fn_8023F1A0(p->path, 0);
            break;
        }
        q = (Layout*)((u8*)q + 4);
    }
}


void fn_800D43B8(PartH* p, int t) {
    switch (t) {
    case 1:
        if (p) {
            p->vt = lbl_80383EBC;
        }
        p->type = t;
        p->size = 0x24;
        return;
    case 2:
        if (p) {
            p->vt = lbl_80386B50;
        }
        p->type = t;
        p->size = 0x30;
        return;
    case 3:
        if (p) {
            p->vt = lbl_80383E94;
        }
        p->type = t;
        p->size = 0x18;
        return;
    case 4:
        if (p) {
            p->vt = lbl_80383E80;
        }
        p->type = t;
        p->size = 0x14;
        return;
    case 5:
        if (p) {
            p->vt = lbl_80383E6C;
        }
        p->type = t;
        p->size = 0x20;
        return;
    case 6:
        if (p) {
            p->vt = lbl_80383EA8;
        }
        p->type = t;
        p->size = 0x34;
        return;
    case 7:
        if (p) {
            p->vt = lbl_80383E58;
        }
        p->type = t;
        p->size = 0x24;
        return;
    }
}

void fn_800D44D4(WinProc* p) {
    if (p->fence) {
        lbl_804CB720 = 1;
    }
}

u8 fn_800D44EC() {
    lbl_804CB720 = 0;
    fn_80083E90(lbl_80383E1C, fn_800D44D4);
    return lbl_804CB720;
}
}
