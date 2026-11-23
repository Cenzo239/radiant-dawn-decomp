/* 2D render pass: draws the sorted node list. */
#include "game/rJ_800799AC/types.h"

extern "C" {

struct GState2 {
    u8 pad00[0x94];
    f32 v94;
    f32 v98;
    f32 v9C;
    f32 vA0;
    u32 tick;
    u8 padA8;
    u8 vA9;
};

extern GState2* lbl_804CB5C0;
extern s16 lbl_80380F44[10];

void fn_80312F48(f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, void* m);
void fn_80307D98(void* m, int x);
void fn_803031CC(void);
void fn_80302B80(int a, int b);
void fn_80303200(int a, int b, int c, int d, int e);
void fn_80021B2C(int a);
void fn_80021A08(int a, int b, int c, int d, int e, int f, int g);
void fn_80021BF4(int a);
void fn_80308144(u32* a, u32* b, u32* d, u32* e);
void fn_803080DC(u32 a, u32 b, u32 d, u32 e);
void fn_80308090(f32 a, f32 b, f32 d, f32 e, f32 f, f32 g);
void fn_80021860(int a, int b, int d);
void fn_800217CC(int a);
void fn_80021808(int a, int b, int d, int e, int f);
void fn_80021784(int a);
void fn_8007EB30(u16 f, void* tex, void* a, void* b);
void fn_8007F048(void* a, u32 b, u8 c);
void fn_80307E48(void* a, int b);
u32 OSGetTick(void);
u8** fn_8007FFDC(void);
void fn_8007FCB8(u8** np);

static inline void setupProjection(void* m) {
    fn_80312F48(0.0f, 448.0f, 0.0f, 608.0f, 0.0f, -1000.0f, m);
    fn_80307D98(m, 1);
    fn_803031CC();
    fn_80302B80(9, 1);
    fn_80302B80(0xB, 1);
    fn_80302B80(0xD, 1);
    fn_80303200(0, 9, 1, 4, 0);
    fn_80303200(0, 0xB, 1, 5, 0);
    fn_80303200(0, 0xD, 1, 4, 0);
    fn_80021B2C(1);
    fn_80021A08(4, 0, 0, 1, 0, 0, 2);
    fn_80021BF4(1);
}

static inline void depthOpaque(void) {
    fn_80021860(1, 3, 1);
    fn_800217CC(0);
    fn_80021808(6, 0x80, 1, 0, 0);
}

static inline void depthBlend(void) {
    fn_80021860(1, 3, 0);
    fn_800217CC(1);
    fn_80021808(7, 0, 1, 7, 0);
}

#define DRAW_NODE()                                                            \
    fn_80308144(&x1, &y1, &w1, &h1);                                           \
    if (x0 != x1 || y0 != y1 || w0 != w1 || h0 != h1) {                        \
        fn_803080DC(x0, y0, w0, h0);                                           \
    }                                                                          \
    fn_8007FCB8(list);

/* Render the state's list */
void fn_8007F874(void) {
    u8** list;
    GState2* g;
    f32 m[16];
    u32 x0;
    u32 y0;
    u32 w0;
    u32 h0;
    u32 x1;
    u32 y1;
    u32 w1;
    u32 h1;
    lbl_804CB5C0->tick = OSGetTick();
    setupProjection(m);
    list = fn_8007FFDC();
    fn_80308144(&x0, &y0, &w0, &h0);
    fn_80308090(0.0f, 0.0f, 608.0f, 448.0f, lbl_804CB5C0->v9C, lbl_804CB5C0->vA0);
    depthOpaque();
    while (*list != 0) {
        u16 f = *(u16*)(*list + 0x10);
        if (f & 0xF0) {
            goto blended;
        }
        if (f & 0x800) {
            break;
        }
        DRAW_NODE()
        list++;
    }
    fn_80308090(0.0f, 0.0f, 608.0f, 448.0f, lbl_804CB5C0->v94, lbl_804CB5C0->v98);
    while (*list != 0) {
        if (*(u16*)(*list + 0x10) & 0xF0) {
            break;
        }
        DRAW_NODE()
        list++;
    }
blended:
    fn_80308090(0.0f, 0.0f, 608.0f, 448.0f, lbl_804CB5C0->v94, lbl_804CB5C0->v98);
    depthBlend();
    while (*list != 0) {
        if (!(*(u16*)(*list + 0x10) & 0x800)) {
            break;
        }
        DRAW_NODE()
        list++;
    }
    fn_80308090(0.0f, 0.0f, 608.0f, 448.0f, lbl_804CB5C0->v9C, lbl_804CB5C0->vA0);
    while (*list != 0) {
        DRAW_NODE()
        list++;
    }
    g = lbl_804CB5C0;
    g->tick = OSGetTick() - g->tick;
    lbl_804CB5C0->vA9 = 0xFF;
}

typedef void (*NodeCb)(u16, u32, void*, void*, u8);

/* Draw one node */
void fn_8007FCB8(u8** np) {
    u8* n = *np;
    if (*(u16*)(n + 0x10) & 0x1000) {
        ((NodeCb) * (void**)(n + 0x1C))(*(u16*)(n + 0x10), *(u32*)(n + 0x20), n + 0x24, n + 0x44, n[0x12]);
        *(u16*)(*np + 0x10) &= ~0x1000;
    } else {
        fn_8007EB30(*(u16*)(n + 0x10), n + 0x24, n + 0x44, (void*)(u32)n[0x12]);
    }
    if (*(s16*)(*np + 0xC) < 0) {
        u8** q = np;
        int i = 0;
        const s16* t = lbl_80380F44;
        while (*q != 0 && i < 10) {
            if (*(u16*)(*q + 0x10) & 0x400) {
                *(s16*)(*q + 0xC) = lbl_80380F44[i];
                fn_80307E48(*q + 0x50, lbl_80380F44[i]);
                break;
            }
            *(s16*)(*q + 0xC) = *t;
            fn_80307E48(*q + 0x50, *t);
            q++;
            t++;
            i++;
        }
    }
    fn_80021784(*(s16*)(*np + 0xC));
    n = *np;
    if (*(u16*)(n + 0x10) & 0x2000) {
        ((NodeCb) * (void**)(n + 0x1C))(*(u16*)(n + 0x10), *(u32*)(n + 0x20), n + 0x24, n + 0x44, n[0x12]);
    }
    {
        u8 a = lbl_804CB5C0->vA9;
        u8* k;
        if (a == 0xFF || ((k = *np), *(u16*)(k + 0x10) & 0x400)) {
            k = *np;
            fn_8007F048(*(void**)(k + 4), k[0x13], k[0x14]);
        } else if (a != 0) {
            fn_8007F048(*(void**)(k + 4), ((a * k[0x13]) >> 8) & 0xFF, k[0x14]);
        }
    }
    n = *np;
    if (*(u16*)(n + 0x10) & 0x4000) {
        ((NodeCb) * (void**)(n + 0x1C))(*(u16*)(n + 0x10), *(u32*)(n + 0x20), n + 0x24, n + 0x44, n[0x12]);
    }
    {
        u16 f = *(u16*)(*np + 0x10);
        if (f & 0x400) {
            f32 m[16];
            if ((f & 0xF0) == 0) {
                depthOpaque();
            } else {
                depthBlend();
            }
            setupProjection(m);
        }
    }
}

}
