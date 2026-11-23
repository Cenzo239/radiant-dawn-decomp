/* Interrupt guard object and the graphics state block at lbl_804CB5C0. */
#include "game/rJ_800799AC/proc.h"

struct IntGuard {
    void* vt;
    int level;
};

struct Mat8 {
    u32 w[8];
};

struct Col3 {
    u32 w[3];
};

struct GState {
    GState* self;   /* 0x00 */
    u32 size;       /* 0x04 */
    u8 pad08[4];
    u8* list;       /* 0x0C */
    int v10;        /* 0x10 */
    int v14;        /* 0x14 */
    u32 v18;        /* 0x18 */
    u8 pad1C[4];
    u16 flags;      /* 0x20 */
    u8 alpha;       /* 0x22 */
    u8 v23;         /* 0x23 */
    u8 v24;         /* 0x24 */
    u8 pad25[3];
    f32 time;       /* 0x28 */
    int v2C;        /* 0x2C */
    int v30;        /* 0x30 */
    Mat8 mat;       /* 0x34 */
    Col3 color;     /* 0x54 */
    f32 m60[13];    /* 0x60 */
    f32 v94;        /* 0x94 */
    f32 v98;        /* 0x98 */
    f32 v9C;        /* 0x9C */
    f32 vA0;        /* 0xA0 */
    u8 padA4[4];
    u8 mode;        /* 0xA8 */
    u8 vA9;         /* 0xA9 */
};

extern "C" {

extern void* lbl_80380F00[];
extern const char lbl_80362570[];
extern GState* lbl_804CB5C0;
extern void* (*lbl_804CA3C0)(u32);
void fn_80079210(void* p);
void* fn_80078CCC(int size, const char* name, int x);
int fn_8017F418(const void* a, const void* b, int n);
void fn_8017F44C(void* p, int v, int n);
#if TARGET_PC
FE10_PROTO void fn_80006A64(void* a, void* out, ptr32<const void>);
#else
void fn_80006A64(void* a, void* out, void* b);
#endif
#if TARGET_PC
FE10_PROTO void fn_80006B84(void* a, void* out, void* b, ptr32<const void>, ptr32<const void>);
#else
void fn_80006B84(void* a, void* out, void* b, void* c, void* d);
#endif
void fn_8007E244(Mat8* m, Col3* c, u8 a, u16 f);
void fn_80312344(void* a, void* b);

IntGuard* fn_8007DEE4(IntGuard* g, int del) {
    if (g != 0) {
        g->vt = lbl_80380F00;
        OSRestoreInterrupts(g->level);
        if (del > 0) {
            fn_80079210(g);
        }
    }
    return g;
}

void* fn_8007DF48(int size) {
    return fn_80078CCC(size, lbl_80362570, 0);
}

GState* fn_8007DF58(u32 size) {
    if (size == 0) {
        size = 0x16570;
    }
    size &= ~7;
    lbl_804CB5C0 = (GState*)lbl_804CA3C0(size);
    lbl_804CB5C0->self = lbl_804CB5C0;
    lbl_804CB5C0->size = size;
    lbl_804CB5C0->v98 = 1.0f;
    lbl_804CB5C0->v94 = 0.5f;
    lbl_804CB5C0->vA0 = 0.5f;
    lbl_804CB5C0->v9C = 0.0f;
    lbl_804CB5C0->v10 = 0;
    lbl_804CB5C0->v14 = 0;
    lbl_804CB5C0->flags = 0;
    lbl_804CB5C0->vA9 = 0xFF;
    return lbl_804CB5C0;
}

void fn_8007E00C(f32 a, f32 b, f32 c, f32 d) {
    lbl_804CB5C0->v98 = a;
    lbl_804CB5C0->v94 = b;
    lbl_804CB5C0->vA0 = c;
    lbl_804CB5C0->v9C = d;
}

void fn_8007E030(u8 v) {
    lbl_804CB5C0->vA9 = v;
}

u8 fn_8007E03C(void) {
    return lbl_804CB5C0->vA9;
}

f32 fn_8007E048(void) {
    u8* n = *(u8**)(lbl_804CB5C0->list + 4);
    if (n == 0) {
        return 1.0f;
    }
    return *(f32*)(n + 0x24);
}

/* Sum of 0x1C words */
#if TARGET_PC
int fn_8007E06C(int* w) {
    int s = 0;
    int i;
    for (i = 0; i < 0x1C; i++) s += w[i];
    return s;
}
#else
asm int fn_8007E06C(int* w) {
    nofralloc
    subi r3, r3, 4
    li r4, 0x1C
    li r11, 0
    mtctr r4
loop:
    lwzu r12, 4(r3)
    add r11, r11, r12
    bdnz loop
    addi r3, r11, 0
    blr
}
#endif

static inline int keyCmp(u8* n, GState* s) {
    return fn_8017F418(n + 0x10, &s->flags, 0x70);
}

u8* fn_8007E090(void) {
    GState* s = lbl_804CB5C0;
    u8* n = s->list;
    u8* prev = 0;
    for (; n != 0; prev = n, n = *(u8**)n) {
        if (*(u32*)(n + 8) == s->v18 && keyCmp(n, s) == 0) {
            if (lbl_804CB5C0->list == n) {
                return n;
            }
            if (prev != 0) {
                *(u8**)prev = *(u8**)n;
            }
            *(u8**)n = lbl_804CB5C0->list;
            lbl_804CB5C0->list = n;
            return n;
        }
    }
    return 0;
}

void fn_8007E154(void) {
    lbl_804CB5C0->mode = 1;
}

void fn_8007E164(void) {
    lbl_804CB5C0->mode = 2;
}

void fn_8007E174(Mat8* m, u16 f) {
    if (m != 0) {
        lbl_804CB5C0->mat = *m;
    } else {
        fn_8017F44C(&lbl_804CB5C0->mat, 0, 0x2C);
        if ((f & 3) == 0) {
            f &= ~3;
            f |= 2;
        }
    }
    lbl_804CB5C0->alpha = 0xFF;
    lbl_804CB5C0->flags &= ~0x84F3;
    lbl_804CB5C0->flags |= f;
}

void fn_8007E244(Mat8* m, Col3* c, u8 a, u16 f) {
    if (m != 0) {
        lbl_804CB5C0->mat = *m;
    } else {
        fn_8017F44C(&lbl_804CB5C0->mat, 0, 0x20);
        if ((f & 3) == 0) {
            f &= ~3;
            f |= 2;
        }
    }
    if (c != 0) {
        f |= 0x8000;
        lbl_804CB5C0->color = *c;
        lbl_804CB5C0->alpha = a;
    } else {
        fn_8017F44C(&lbl_804CB5C0->color, 0, 0xC);
        lbl_804CB5C0->alpha = 0xFF;
    }
    lbl_804CB5C0->flags &= ~0x84F3;
    lbl_804CB5C0->flags |= f;
}

void fn_8007E374(void* a, void* b, u16 f) {
    Mat8 m;
    fn_80006A64(a, &m, b);
    lbl_804CB5C0->mat = m;
    lbl_804CB5C0->alpha = 0xFF;
    lbl_804CB5C0->flags &= ~0x84F3;
    lbl_804CB5C0->flags |= f;
}

void fn_8007E41C(void* a, void* b, u8 c, u16 f) {
    Col3 color;
    u8 pad[4];
    Mat8 mat;
    fn_80006B84(a, &mat, &color, (void*)(u32)c, b);
    fn_8007E244(&mat, &color, c, f);
}

void fn_8007E478(f32 t, void* a) {
    fn_80312344(a, lbl_804CB5C0->m60);
    lbl_804CB5C0->time = t;
    lbl_804CB5C0->flags &= ~0x800;
}

f32* fn_8007E4C4(f32* out) {
    if (out != 0) {
        *out = lbl_804CB5C0->time;
    }
    return lbl_804CB5C0->m60;
}

void fn_8007E720(f32 d) {
    lbl_804CB5C0->time += d;
}

f32 fn_8007E734(void) {
    return lbl_804CB5C0->time;
}

void fn_8007E740(f32 t) {
    lbl_804CB5C0->time = t;
}

void fn_8007E74C(int a, int b) {
    lbl_804CB5C0->v2C = a;
    lbl_804CB5C0->v30 = b;
    lbl_804CB5C0->flags &= ~0x7000;
    lbl_804CB5C0->flags |= 0x2000;
}

void fn_8007E780(int a, int b) {
    lbl_804CB5C0->v2C = a;
    lbl_804CB5C0->v30 = b;
    lbl_804CB5C0->flags &= ~0x7000;
    lbl_804CB5C0->flags |= 0x5000;
}

void fn_8007E7B4(void) {
    lbl_804CB5C0->v2C = 0;
    lbl_804CB5C0->v30 = 0;
    lbl_804CB5C0->flags &= ~0x7000;
}

void fn_8007E7DC(u8 v) {
    lbl_804CB5C0->v23 = v;
}

void fn_8007E7E8(u8 v) {
    lbl_804CB5C0->v24 = v;
}

void fn_8007E7F4(void) {
    lbl_804CB5C0->mode = 1;
    lbl_804CB5C0->v23 = 0xFF;
    lbl_804CB5C0->v24 = 0x80;
    lbl_804CB5C0->v2C = 0;
    lbl_804CB5C0->v30 = 0;
    lbl_804CB5C0->flags &= ~0x7000;
    lbl_804CB5C0->mode = 2;
}


/* Current 2D command in the state's list */
#define CUR() (*(u8**)(lbl_804CB5C0->list + 4))
#define F(c, o) (*(f32*)((c) + (o)))

int fn_801D09F0(void);
void fn_803128AC(f32 a, f32 b, f32 c, void* m);
void fn_8031292C(f32 a, f32 b, f32 c, void* m);
void fn_80312378(void* a, void* b, void* c);
void fn_80312318(void* m);

/* Adjust the 2D projection for widescreen */
void fn_8007E84C(int mode) {
    u8 c[0x30];
    u8 b[0x30];
    u8 a[0x30];
    if (fn_801D09F0() == 0) {
        return;
    }
    lbl_804CB5C0->pad25[0] = mode;
    switch (mode) {
    case 1:
        fn_803128AC(-304.0f, 0.0f, 0.0f, a);
        fn_8031292C(0.76381909847f, 1.0f, 1.0f, b);
        fn_80312378(b, a, c);
        fn_803128AC(304.0f, 0.0f, 0.0f, a);
        fn_80312378(a, c, c);
        fn_80312378(c, lbl_804CB5C0->m60, lbl_804CB5C0->m60);
        break;
    case 2:
        fn_8031292C(0.76381909847f, 1.0f, 1.0f, b);
        fn_80312378(b, lbl_804CB5C0->m60, lbl_804CB5C0->m60);
        break;
    case 3:
        fn_803128AC(-608.0f, 0.0f, 0.0f, a);
        fn_8031292C(0.76381909847f, 1.0f, 1.0f, b);
        fn_80312378(b, a, c);
        fn_803128AC(608.0f, 0.0f, 0.0f, a);
        fn_80312378(a, c, c);
        fn_80312378(c, lbl_804CB5C0->m60, lbl_804CB5C0->m60);
        break;
    }
}

/* Screen x under widescreen scaling */
int fn_8007E9BC(int x) {
    f32 v;
    if (fn_801D09F0() != 0) {
        v = 0.76381909847f * ((f32)x - 304.0f) + 304.0f;
    } else {
        v = (f32)x;
    }
    return v;
}

void fn_80312F48(f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, void* m);
void fn_80307D98(void* m, int x);
void fn_803031CC(void);
void fn_80302B80(int a, int b);
void fn_80303200(int a, int b, int c, int d, int e);
void fn_80021B2C(int a);
void fn_80021A08(int a, int b, int c, int d, int e, int f, int g);
void fn_80021BF4(int a);

void fn_8007EA48(void) {
    u8 m[0x48];
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

/* Reset the 2D command list */
void fn_8007F7E0(void) {
    u32* g = (u32*)lbl_804CB5C0;
    g[2] = g[0] + 0xAC;
    lbl_804CB5C0->list = 0;
    *(s16*)((u8*)lbl_804CB5C0 + 0x92) = 0;
    *(s16*)((u8*)lbl_804CB5C0 + 0x90) = 0;
    fn_80312318(lbl_804CB5C0->m60);
    lbl_804CB5C0->v2C = 0;
    lbl_804CB5C0->v30 = 0;
    lbl_804CB5C0->v23 = 0xFF;
    lbl_804CB5C0->v24 = 0x80;
    lbl_804CB5C0->flags = 0;
    lbl_804CB5C0->mode = 0;
}

void fn_80080308(void) {
    (*(s16*)((u8*)lbl_804CB5C0 + 0x92))++;
}

void fn_8008031C(f32 z) {
    F(CUR(), 8) = z;
}

void fn_80080330(f32 a, f32 b) {
    u8* c = CUR();
    F(c, 0x10) = a;
    F(c, 0x14) = b;
}

void fn_80080348(f32 a, f32 b, f32 d, f32 e) {
    u8* c = CUR();
    F(c, 0x10) = a;
    F(c, 0x14) = b;
    F(c, 0x18) = d;
    F(c, 0x1C) = e;
}

void fn_80080368(f32 a, f32 b, f32 d, f32 e) {
    u8* c = CUR();
    F(c, 0x20) = a;
    F(c, 0x24) = b;
    F(c, 0x28) = d;
    F(c, 0x2C) = e;
}

void fn_80080388(f32 x, f32 y, f32 w, f32 h) {
    u8* c = CUR();
    F(c, 0x10) = x;
    F(c, 0x20) = x + w;
    F(c, 0x14) = y;
    F(c, 0x24) = y + h;
    F(c, 0x1C) = 0.0f;
    F(c, 0x18) = 0.0f;
    F(c, 0x2C) = 1.0f;
    F(c, 0x28) = 1.0f;
}

void fn_800803C8(f32 x, f32 y, f32 w, f32 h) {
    u8* c = CUR();
    F(c, 0x18) = x;
    F(c, 0x1C) = y;
    F(c, 0x28) = x + w;
    F(c, 0x2C) = y + h;
}

void fn_800803F0(f32 a, f32 b, f32 d, f32 e) {
    u8* c = CUR();
    F(c, 0x10) = a;
    F(c, 0x14) = b;
    F(c, 0x20) = d;
    F(c, 0x24) = e;
}

void fn_80080410(f32 a, f32 b, f32 d, f32 e) {
    u8* c = CUR();
    F(c, 0x18) = a;
    F(c, 0x1C) = b;
    F(c, 0x28) = d;
    F(c, 0x2C) = e;
}

void fn_80080430(f32 x, f32 y, f32 u, f32 v, f32 w, f32 h) {
    u8* c = CUR();
    F(c, 0x10) = x;
    F(c, 0x20) = x + w;
    F(c, 0x14) = y;
    F(c, 0x24) = y + h;
    F(c, 0x1C) = 0.0f;
    F(c, 0x18) = 0.0f;
    F(c, 0x2C) = 1.0f;
    F(c, 0x28) = 1.0f;
    c = CUR();
    F(c, 0x18) = u;
    F(c, 0x1C) = v;
    F(c, 0x28) = u + w;
    F(c, 0x2C) = v + h;
}

void fn_80080494(void) {
    u8* c = CUR();
    f32 t = F(c, 0x18);
    F(c, 0x18) = F(c, 0x28);
    F(c, 0x28) = t;
}

void fn_800804B4(void) {
    u8* c = CUR();
    f32 t = F(c, 0x1C);
    F(c, 0x1C) = F(c, 0x2C);
    F(c, 0x2C) = t;
}

void fn_800804D4(u8 r, u8 g, u8 b, u8 a) {
    u8* c = CUR();
    c[0xC] = r;
    c[0xD] = g;
    c[0xE] = b;
    c[0xF] = a;
}

void fn_800804F4(u8 a) {
    CUR()[0xF] = a;
}

void fn_80080508(
#if TARGET_PC
fe10_rgba colv
#else
const u8* col
#endif
) {
#if TARGET_PC
    const u8* col = (const u8*)&colv;
#endif
    u8* c = CUR();
    c[0xC] = col[0];
    c[0xD] = col[1];
    c[0xE] = col[2];
    c[0xF] = col[3];
}

void fn_80080538(f32 a, f32 b, f32 d, f32 e) {
    u8* c = CUR();
    F(c, 0x30) = a;
    F(c, 0x34) = b;
    F(c, 0x38) = d;
    F(c, 0x3C) = e;
}

void fn_80080558(f32 a, f32 b, f32 d, f32 e) {
    u8* c = CUR();
    F(c, 0x40) = a;
    F(c, 0x44) = b;
    F(c, 0x48) = d;
    F(c, 0x4C) = e;
}

void fn_80080690(void) {
    u8* c = CUR();
    f32 x = F(c, 0x18);
    f32 y = F(c, 0x1C);
    F(c, 0x18) = F(c, 0x38);
    F(c, 0x1C) = F(c, 0x3C);
    F(c, 0x38) = F(c, 0x28);
    F(c, 0x3C) = F(c, 0x2C);
    F(c, 0x28) = F(c, 0x48);
    F(c, 0x2C) = F(c, 0x4C);
    F(c, 0x48) = x;
    F(c, 0x4C) = y;
}

void fn_800806E0(void) {
    u8* c = CUR();
    f32 x = F(c, 0x18);
    f32 y = F(c, 0x1C);
    F(c, 0x18) = F(c, 0x48);
    F(c, 0x1C) = F(c, 0x4C);
    F(c, 0x48) = F(c, 0x28);
    F(c, 0x4C) = F(c, 0x2C);
    F(c, 0x28) = F(c, 0x38);
    F(c, 0x2C) = F(c, 0x3C);
    F(c, 0x38) = x;
    F(c, 0x3C) = y;
}

void fn_800808F8(f32 a, f32 b) {
    u8* c = CUR();
    F(c, 0x30) = a;
    F(c, 0x34) = b;
}

void fn_80080910(int a, int b) {
    u8* c = CUR();
    *(int*)(c + 0x10) = a;
    *(int*)(c + 0x14) = b;
}

void fn_80080928(int a, int b) {
    u8* c = CUR();
    *(int*)(c + 0x10) = a;
    *(int*)(c + 0x14) = b;
}

void fn_80080940(
#if TARGET_PC
fe10_rgba av, fe10_rgba bv, fe10_rgba dv, fe10_rgba ev
#else
const u8* a, const u8* b, const u8* d, const u8* e
#endif
) {
#if TARGET_PC
    const u8* a = (const u8*)&av;
    const u8* b = (const u8*)&bv;
    const u8* d = (const u8*)&dv;
    const u8* e = (const u8*)&ev;
#endif
    u8* c = CUR();
    c[0xC] = a[0];
    c[0xD] = a[1];
    c[0xE] = a[2];
    c[0xF] = a[3];
    c[0x50] = b[0];
    c[0x51] = b[1];
    c[0x52] = b[2];
    c[0x53] = b[3];
    c[0x54] = d[0];
    c[0x55] = d[1];
    c[0x56] = d[2];
    c[0x57] = d[3];
    c[0x58] = e[0];
    c[0x59] = e[1];
    c[0x5A] = e[2];
    c[0x5B] = e[3];
}

u8* fn_800CD204(int i);

/* Text command defaults */
static inline void textDefaults(void) {
    u8* c = CUR();
    u8* t;
    F(c, 0x24) = 1.0f;
    F(c, 0x28) = 0.0f;
    *(s16*)(c + 0x2C) = 0;
    *(s16*)(c + 0x2E) = 0;
    t = fn_800CD204(1);
    c[0x18] = t[0];
    c[0x19] = t[1];
    c[0x1A] = t[2];
    c[0x1B] = t[3];
    t = fn_800CD204(2);
    c[0x1C] = t[0];
    c[0x1D] = t[1];
    c[0x1E] = t[2];
    c[0x1F] = 0x80;
    t = fn_800CD204(2);
    c[0x20] = t[0];
    c[0x21] = t[1];
    c[0x22] = t[2];
    c[0x23] = t[3];
}

void fn_800809D0(void) {
    textDefaults();
}

void fn_80080A94(f32 v) {
    F(CUR(), 0x24) = v;
}

void fn_80080AA8(f32 v) {
    F(CUR(), 0x28) = v;
}

static inline void setCol1C(const u8* col) {
    u8 r = col[0];
    u8 b = col[2];
    u8 g = col[1];
    u8 a = col[3];
    u8* c = CUR();
    c[0x1C] = r;
    c[0x1D] = g;
    c[0x1E] = b;
    c[0x1F] = a;
}

static inline void setCol20(const u8* col) {
    u8 r = col[0];
    u8 b = col[2];
    u8 g = col[1];
    u8 a = col[3];
    u8* c = CUR();
    c[0x20] = r;
    c[0x21] = g;
    c[0x22] = b;
    c[0x23] = a;
}

void fn_80080ABC(int on, f32 v) {
    u8* c = CUR();
    *(s16*)(c + 0x2C) = on == 0 ? 0 : (s16)(256.0f * v);
}

void fn_80080B00(int on, const u8* col, f32 v) {
    u8* c = CUR();
    *(s16*)(c + 0x2C) = on == 0 ? 0 : (s16)(256.0f * v);
    setCol1C(col);
}

void fn_80080B70(int on, f32 v) {
    u8* c = CUR();
    *(s16*)(c + 0x2E) = on == 0 ? 0 : (s16)(256.0f * v);
}

void fn_80080BB4(int on, const u8* col, f32 v) {
    u8* c = CUR();
    *(s16*)(c + 0x2E) = on == 0 ? 0 : (s16)(256.0f * v);
    setCol20(col);
}


/* Sort the commands of the current state by depth, back to front */
u8** fn_8007FFDC(void) {
    u8** list = *(u8***)((u8*)lbl_804CB5C0 + 8);
    int i;
    u8** p;
    u8** out = list;
    u8* a;
    u8* b;
    int swapped = 1;
    u16 f;
    int n;
    u8* c;
    *(u8***)((u8*)lbl_804CB5C0 + 8) = list + (*(s16*)((u8*)lbl_804CB5C0 + 0x90) + 1);
    for (c = lbl_804CB5C0->list; c != 0; c = *(u8**)c) {
        *out++ = c;
        f = *(u16*)(c + 0x10);
        if ((f & 0xF0) == 0) {
            if (f & 0x800) {
                F(c, 0x18) = 2000.0f;
            } else {
                F(c, 0x18) = 2001.0f;
            }
        } else if (f & 0x800) {
            F(c, 0x18) += 1000.0f;
        }
    }
    n = *(s16*)((u8*)lbl_804CB5C0 + 0x90);
    while (swapped) {
        p = list;
        swapped = 0;
        for (i = 0; i < n - 1; i++) {
            b = p[1];
            a = p[0];
            if (F(a, 0x18) < F(b, 0x18)) {
                p[0] = b;
                swapped = 1;
                p[1] = a;
            }
            p++;
        }
        n--;
    }
    list[*(s16*)((u8*)lbl_804CB5C0 + 0x90)] = 0;
    return list;
}

extern const char lbl_804CB5C4[4];

/* Attach a string to the current text command */
void fn_80080C24(const char* s) {
    GState* g = lbl_804CB5C0;
    int n = 1;
    u32 sz;
    u8* c = *(u8**)(g->list + 4);
    u8* d;
    if (s == 0) {
        s = lbl_804CB5C4;
    }
    while (*s++ != 0) {
        n++;
    }
    s -= n;
    sz = (n + 3) & 0xFC;
    if (sz > 0xCC) {
        sz = 0xCC;
    }
    d = *(u8**)((u8*)g + 8);
    *(u8**)((u8*)g + 8) = d + sz;
    while (*s != 0) {
        *d++ = *s++;
    }
    *d = 0;
    c[5] += sz;
    c[0x18] = c[0xC];
    c[0x19] = c[0xD];
    c[0x1A] = c[0xE];
    c[0x1B] = c[0xF];
}

void fn_80080578(int mode) {
    u8* c = CUR();
    if (mode != 0 && fn_801D09F0() != 0) {
        switch (mode) {
        case 1: {
            f32 r = F(c, 0x20);
            f32 x = F(c, 0x10);
            f32 d = 0.5f * (r - x);
            x += d;
            F(c, 0x10) = x - 0.76381909847f * d;
            F(c, 0x20) = 0.76381909847f * d + x;
            break;
        }
        case 2: {
            f32 r = F(c, 0x20);
            f32 x = F(c, 0x10);
            F(c, 0x20) = 0.76381909847f * (r - x) + x;
            break;
        }
        case 3: {
            f32 r = F(c, 0x20);
            F(c, 0x10) = r - 0.76381909847f * (r - F(c, 0x10));
            break;
        }
        }
    }
    F(c, 0x30) = F(c, 0x20);
    F(c, 0x34) = F(c, 0x14);
    F(c, 0x40) = F(c, 0x10);
    F(c, 0x44) = F(c, 0x24);
    F(c, 0x38) = F(c, 0x28);
    F(c, 0x3C) = F(c, 0x1C);
    F(c, 0x48) = F(c, 0x18);
    F(c, 0x4C) = F(c, 0x2C);
}


void fn_80312654(f32 a, void* m, int axis);

static inline void xform(const f32* m, u8* c, int o) {
    f32 y = F(c, o + 4);
    f32 x = F(c, o);
    F(c, o) = m[3] + (m[0] * x + m[1] * y);
    F(c, o + 4) = m[7] + (m[4] * x + m[5] * y);
}

/* Rotate the current quad about a point */
void fn_80080730(f32 x, f32 y, f32 deg) {
    u8* c = CUR();
    f32 t[12];
    f32 m[12];
    fn_803128AC(-x, -y, 0.0f, t);
    fn_80312654(0.017453292f * deg, m, 0x5A);
    fn_80312378(m, t, m);
    fn_803128AC(x, y, 0.0f, t);
    fn_80312378(t, m, m);
    xform(m, c, 0x10);
    xform(m, c, 0x30);
    xform(m, c, 0x40);
    xform(m, c, 0x20);
}


void fn_8007E4E4(f32 x, f32 y, f32 z, f32 s) {
    f32 b[12];
    f32 a[12];
    if (1.0f == s) {
        fn_803128AC(x, y, z, a);
    } else {
        fn_8031292C(s, s, 1.0f, b);
        fn_803128AC(x, y, z, a);
        fn_80312378(a, b, a);
    }
    fn_80312344(a, lbl_804CB5C0->m60);
    lbl_804CB5C0->time = z;
    lbl_804CB5C0->flags &= ~0x800;
    lbl_804CB5C0->pad25[0] = 0;
}

void fn_8007E5C0(f32 x, f32 y, f32 z, f32 cx, f32 cy, f32 sx, f32 sy, f32 deg) {
    f32 sm[12];
    f32 tm[12];
    f32 rm[12];
    f32 c2[12];
    f32 c1[12];
    f32 m[12];
    fn_803128AC(x, y, z, tm);
    fn_8031292C(sx, sy, 1.0f, sm);
    fn_80312654(0.017453292f * deg, rm, 0x5A);
    fn_803128AC(-cx, -cy, 0.0f, c1);
    fn_803128AC(cx, cy, 0.0f, c2);
    fn_80312378(sm, c1, m);
    fn_80312378(rm, m, m);
    fn_80312378(c2, m, m);
    fn_80312378(tm, m, m);
    fn_80312344(m, lbl_804CB5C0->m60);
    lbl_804CB5C0->time = z;
    lbl_804CB5C0->flags &= ~0x800;
    lbl_804CB5C0->pad25[0] = 0;
}

int fn_8007E06C(int* w);
u8* fn_8007E090(void);
void fn_8017F480(void* a, void* b, int n);
void OSPanic(const char* file, int line, const char* msg, ...);

/* Append a command of the given type to the list */
void fn_800800D4(u32 type) {
    int size;
    u8* c;
    if (lbl_804CB5C0->mode == 2) {
        lbl_804CB5C0->v18 = fn_8007E06C((int*)&lbl_804CB5C0->flags);
        if (fn_8007E090() == 0) {
            u8* n = *(u8**)((u8*)lbl_804CB5C0 + 8);
            *(u8**)((u8*)lbl_804CB5C0 + 8) = n + 0x80;
            *(u8**)n = lbl_804CB5C0->list;
            lbl_804CB5C0->list = n;
            *(int*)(n + 4) = 0;
            *(s16*)(n + 0xC) = -1;
            *(u32*)(n + 8) = lbl_804CB5C0->v18;
            fn_8017F480(n + 0x10, &lbl_804CB5C0->flags, 0x70);
            (*(s16*)((u8*)lbl_804CB5C0 + 0x90))++;
        }
        lbl_804CB5C0->mode = 3;
    }
    switch (type) {
    case 1:
    case 4:
        size = 0x30;
        break;
    case 2:
        size = 0x50;
        break;
    case 3:
        size = 0x5C;
        break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        size = 0x30;
        break;
    case 10:
        size = 0x38;
        break;
    case 11:
        size = 0x18;
        break;
    case 12:
        size = 0x18;
        break;
    default:
        OSPanic(lbl_80362570 + 1, 0x5D2, lbl_80362570 + 10);
        break;
    }
    c = *(u8**)((u8*)lbl_804CB5C0 + 8);
    *(u8**)((u8*)lbl_804CB5C0 + 8) = c + size;
    c[4] = type;
    c[5] = size;
    F(c, 8) = 0.0f;
    *(int*)(c + 0xC) = -1;
    *(u8**)c = *(u8**)(lbl_804CB5C0->list + 4);
    *(u8**)(lbl_804CB5C0->list + 4) = c;
    switch ((int)type) {
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        textDefaults();
        break;
    }
}

}
