#include "game/rA_800068A0/types.h"
extern "C" {
typedef struct GXC { u8 r, g, b, a; } GXC;
typedef struct GXBlock { u32 w[8]; } GXBlock;
extern u32 lbl_804CB0DC;
extern u8 lbl_804CB0D8;
extern u32 lbl_804CB0E0;
extern u8 lbl_804CB0E4;
extern u8 lbl_804CB0E5;
extern u8 lbl_804CB0E6;
extern u8 lbl_804CB0EA;
extern u32 lbl_803BF878[16];
extern u32 lbl_803BF8B8[16];
extern u32 lbl_803BF8F8[16];
extern u32 lbl_803BF938[16];
extern u32 lbl_803BF978[16];
extern u32 lbl_803BF9B8[16];
extern u32 lbl_803BF9F8[16];
extern u32 lbl_803BFA98[16];
extern GXBlock lbl_803BFAD8[];
extern void fn_80012268(void);
extern void fn_80305794(int);
extern void fn_80021A08(int ch, int a1, int a2, int a3, int a4, int a5, int a6);
extern u32 fn_80011E28(void);
extern u32 fn_80011F38(void);
extern u32 fn_80011EB4(void);
extern u32 fn_80011EAC(void);
extern u32 fn_80011FBC(void);
extern u32 fn_800120CC(void);
extern void fn_80307118(int, int, int, int);
extern void fn_80306C18(int, int);
extern void fn_80305A40(void* obj, void* image, u16 w, u16 h, u32 fmt, u32 wrapS, u32 wrapT, u8 mip);
extern void fn_80305C94(void* obj, int, int, f32, f32, f32, int, int, int);
extern void fn_80305FC4(const GXBlock*, int);
extern void fn_80303634(int, int, int, int, int, int);
extern void fn_80306CAC(int, int, int, int, int);
extern void fn_80306D2C(int, int, int, int, u8, int);
extern void fn_80306CEC(int, int, int, int, int);
extern void fn_80306D84(int, int, int, int, u8, int);
extern void fn_80306F9C(int, int, int);
extern void fn_80306FD8(int, int, int, int, int);
extern void fn_80307748(int, int, int, int);
extern void fn_80307274(int);
extern void fn_8030385C(int);
extern void fn_80306B04(int);
extern void fn_803031CC(void);
extern void fn_80302B80(int, int);
extern void fn_80303200(int, int, int, int, int);
extern void fn_803045DC(int);
extern void fn_80304314(int, int, int);

#define WGF (*(volatile f32*)0xCC008000)
#define WGB (*(volatile u8*)0xCC008000)

static inline void sOrder(int i, int a1, int a2, int a3) {
    u32 key = a1 | (a2 << 8) | (a3 << 16);
    if (key != lbl_803BF878[i]) {
        fn_80307118(i, a1, a2, a3);
        lbl_803BF878[i] = key;
    }
}
static inline void sColorIn(int i, int a1, int a2, int a3, int a4) {
    u32 key = a1 | (a2 << 8) | (a3 << 16) | (a4 << 24);
    if (key != lbl_803BF978[i]) {
        fn_80306CAC(i, a1, a2, a3, a4);
        lbl_803BF978[i] = key;
    }
}
static inline void sAlphaIn(int i, int a1, int a2, int a3, int a4) {
    u32 key = a1 | (a2 << 8) | (a3 << 16) | (a4 << 24);
    if (key != lbl_803BF9B8[i]) {
        fn_80306CEC(i, a1, a2, a3, a4);
        lbl_803BF9B8[i] = key;
    }
}
static inline void sColorOp(int i, int a1, int a2, int a3, u8 a4, int a5) {
    u32 key = a1 | (a2 << 4) | (a3 << 8) | (a4 << 12) | (a5 << 16);
    if (key != lbl_803BF8F8[i]) {
        fn_80306D2C(i, a1, a2, a3, a4, a5);
        lbl_803BF8F8[i] = key;
        lbl_803BF8B8[i] = -1;
    }
}
static inline void sAlphaOp(int i, int a1, int a2, int a3, u8 a4, int a5) {
    u32 key = a1 | (a2 << 4) | (a3 << 8) | (a4 << 12) | (a5 << 16);
    if (key != lbl_803BF938[i]) {
        fn_80306D84(i, a1, a2, a3, a4, a5);
        lbl_803BF938[i] = key;
        lbl_803BF8B8[i] = -1;
    }
}
static inline void sTexGen(int i, int a1, int a2, int a3) {
    u32 lo = a1 | (a2 << 8);
    u32 hi = a3 << 16;
    u32 key = hi | lo;
    if (key != lbl_803BF9F8[i]) {
        fn_80303634(i, a1, a2, a3, 0, 0x7D);
        lbl_803BF9F8[i] = key;
    }
}
static inline void sMode(int i, u32 key) {
    if (key != lbl_803BF8B8[i]) {
        lbl_803BF8F8[i] = -1;
        lbl_803BF938[i] = -1;
        lbl_803BF978[i] = -1;
        lbl_803BF9B8[i] = -1;
        fn_80306C18(i, key);
        lbl_803BF8B8[i] = key;
    }
}
static inline void sTexObj(GXBlock* p, int n) {
    GXBlock* c = &lbl_803BFAD8[n];
    int i;
    for (i = 0; i < 8; i++) {
        if (p->w[i] != c->w[i]) {
            fn_80305FC4(p, n);
            c->w[0] = p->w[0];
            c->w[1] = p->w[1];
            c->w[2] = p->w[2];
            c->w[3] = p->w[3];
            c->w[4] = p->w[4];
            c->w[5] = p->w[5];
            c->w[6] = p->w[6];
            c->w[7] = p->w[7];
            return;
        }
    }
}
static inline void sBlend(int a0, int a1, int a2, int a3) {
    u32 key = a0 | (a1 << 8) | (a2 << 16) | (a3 << 24);
    if (key != lbl_804CB0E0) {
        fn_80307748(a0, a1, a2, a3);
        lbl_804CB0E0 = key;
    }
}

static inline void pos3(f32 x, f32 y, f32 z) {
    WGF = x;
    WGF = y;
    WGF = z;
}
static inline void col4(u8 r, u8 g, u8 b, u8 a) {
    WGB = r;
    WGB = g;
    WGB = b;
    WGB = a;
}
static inline void tex2f(f32 u, f32 v) {
    WGF = u;
    WGF = v;
}
#define vtx(x, y, c, u, v) pos3(x, y, 0.0f); col4(c.r, c.g, c.b, c.a); tex2f(u, v)
static inline void sN0(int n) {
    if (lbl_804CB0E4 != n) {
        fn_80307274(n);
        lbl_804CB0E4 = n;
    }
}
static inline void sN1(int n) {
    if (lbl_804CB0E5 != n) {
        fn_8030385C(n);
        lbl_804CB0E5 = n;
    }
}
static inline void sN2(int n) {
    if (lbl_804CB0E6 != n) {
        fn_80306B04(n);
        lbl_804CB0E6 = n;
    }
}
void fn_8001F5B8(int x, int y, int w, int h, int dw, int dh, void* img, int fmt, const GXC* cols, GXBlock* tex2, u16 fl) {
    GXC def[4] = {{0xFF, 0xFF, 0xFF, 0xFF}, {0xFF, 0xFF, 0xFF, 0xFF}, {0xFF, 0xFF, 0xFF, 0xFF}, {0xFF, 0xFF, 0xFF, 0xFF}};
    GXBlock obj;
    if (cols == NULL) {
        cols = def;
    } else if (cols[0].a + cols[1].a + cols[2].a + cols[3].a == 0) {
        return;
    }
    if (dw < 0) {
        dw = w;
    }
    if (dh < 0) {
        dh = h;
    }
    fn_80012268();
    if (lbl_804CB0D8 != 1) {
        fn_80305794(1);
        lbl_804CB0D8 = 1;
    }
    fn_80021A08(4, 0, 1, 1, 0, 0, 2);
    if (img == NULL) {
        int st = fn_80011E28();
        sOrder(st, 0xFF, 0xFF, 4);
        sMode(st, 4);
    } else {
        int st = fn_80011E28();
        int tc = fn_80011F38();
        int tm = fn_80011EB4();
        int lin = 1;
        if (w == dw && h == dh) {
            lin = 0;
        }
        if (fmt == 0x28) {
            fmt = 1;
        }
        fn_80305A40(&obj, img, dw, dh, fmt, 0, 0, 0);
        fn_80305C94(&obj, lin, lin, 0.0f, 0.0f, 0.0f, 0, 0, 0);
        sTexObj(&obj, tm);
        sOrder(st, tc, tm, 4);
        sTexGen(tc, 1, 4, 0x3C);
        switch (fl & 0xE000) {
        case 0xC000:
            sColorIn(st, 0xF, 0xF, 0xF, 8);
            sColorOp(st, 0, 2, 1, 1, 0);
            break;
        case 0xE000:
            sColorIn(st, 0xF, 0xF, 0xF, 8);
            sColorOp(st, 0, 2, 2, 1, 0);
            break;
        default:
            if (fmt == 0x11 || fmt == 0x13 || fmt == 0x16) {
                sColorIn(st, 0xA, 0xF, 8, 0xF);
                sColorOp(st, 0, 0, 0, 1, 0);
            } else {
                sColorIn(st, 0xF, 0xA, 8, 0xF);
                sColorOp(st, 0, 0, 0, 1, 0);
            }
            break;
        }
        sAlphaIn(st, 7, 7, 7, 5);
        sAlphaOp(st, 0, 0, 0, 1, 0);
    }
    if (tex2 != NULL) {
        int st = fn_80011E28();
        int tc = fn_80011F38();
        int tm = fn_80011EB4();
        {
            u32 key = 3 << 16;
            if (key != lbl_803BFA98[st]) {
                fn_80306F9C(st, 0, 3);
                lbl_803BFA98[st] = key;
                lbl_804CB0EA = 1;
            }
        }
        fn_80306FD8(3, 0, 0, 0, 0);
        sTexGen(tc, 1, 4, 0x3C);
        sTexObj(tex2, tm);
        sOrder(st, tc, tm, 4);
        sColorIn(st, 0xF, 0xF, 0xF, 0);
        sColorOp(st, 0, 0, 0, 1, 0);
        if (fmt == 0x11 || fmt == 0x13 || fmt == 0x16) {
            sAlphaIn(st, 0, 7, 4, 7);
            sAlphaOp(st, 0, 0, 0, 1, 0);
        } else {
            sAlphaIn(st, 7, 4, 0, 7);
            sAlphaOp(st, 0, 0, 0, 1, 0);
        }
    }
    switch (fl & 0xE000) {
    case 0x2000:
        sBlend(1, 4, 1, 0);
        break;
    case 0x4000:
        sBlend(3, 0, 0, 0);
        break;
    case 0x6000:
        sBlend(1, 2, 0, 0);
        break;
    case 0x8000:
        sBlend(1, 2, 2, 0);
        break;
    case 0xA000:
        sBlend(1, 3, 3, 7);
        break;
    default:
        sBlend(1, 4, 5, 7);
        break;
    }
    sN0((u8)fn_80011EAC());
    sN1((u8)fn_80011FBC());
    sN2((u8)fn_800120CC());
    fn_803031CC();
    fn_80302B80(9, 1);
    fn_80302B80(0xB, 1);
    fn_80302B80(0xD, 1);
    fn_80303200(0, 9, 1, 4, 0);
    fn_80303200(0, 0xB, 1, 5, 0);
    fn_80303200(0, 0xD, 1, 4, 0);
    if (lbl_804CB0DC != 0) {
        fn_803045DC(0);
        lbl_804CB0DC = 0;
    }
    fn_80304314(0x80, 0, 4);
    vtx(x, y, cols[0], 0.0f, 0.0f);
    vtx(x + w, y, cols[1], 1.0f, 0.0f);
    vtx(x + w, y + h, cols[2], 1.0f, 1.0f);
    vtx(x, y + h, cols[3], 0.0f, 1.0f);
}
}
