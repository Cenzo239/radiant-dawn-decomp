/* Screen filter setup: allocates the filter object and its texture buffers per mode (names guessed). */
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;
#pragma use_lmw_stmw on

struct C4 { u8 r, g, b, a; };
struct Filter {
    u8* base;
    int a;
    int b;
    int c;
    int d;
    int w14, w18, w1C, w20;
    u8 mode;
    u8 a1;
    u8 a2;
    u8 n;
    s16 x28;
    u8 x2a;
    C4 col;
};
struct Panel {
    u8 pad[0x30];
    Filter* f;
    s16 h34, h36, h38, h3A, h3C, h3E;
    u8 b40;
};


static C4 kTint = {0xFF, 0xC0, 0x6C, 0xFF};
extern "C" {
extern char lbl_804CA7C8[4];
extern C4 lbl_804CE4E0;
void* fn_80078CCC(int, const char*, int);
int fn_8030585C(int, int, int, int, int);
void fn_80079978(void*);
u8* fn_80079940(int, int);
void DCInvalidateRange(void*, int);

static inline void SetCol0(Filter* f, C4 c) { f->col = c; }
static inline void SetCol(Filter* f, C4 c) { SetCol0(f, c); }
static inline Filter* newFilter() {
    Filter* f = (Filter*)fn_80078CCC(0x30, lbl_804CA7C8, 0);
    if (f) {
        f->x2a = 1;
        f->mode = 0;
        f->base = 0;
        f->a1 = 0xFF;
        f->n = 3;
        f->x28 = 0;
        f->a2 = 0;
        C4 c = lbl_804CE4E0;
        f->col = c;
        f->a = 0;
        f->b = 0;
        f->c = 0;
        f->d = 0;
        f->w14 = 0;
        f->w18 = 0;
        f->w1C = 0;
        f->w20 = 0;
    }
    return f;
}

void fn_8017ABE4(Panel* p, u32 mode) {
    int sz;
    p->f = newFilter();
    p->b40 = 0;
    sz = 0;
    p->h3C = 0;
    p->h3E = 0;
    p->h34 = 0;
    p->h36 = 0x10;
    p->h38 = 0;
    p->h3A = 0xFF;
    switch (mode) {
    case 0:
        p->f->a = 0;
        sz = fn_8030585C(0x260, 0x1C0, 6, 0, 0);
        p->f->a1 = 0x7F;
        break;
    case 5:
    case 6:
        p->f->a = 0;
        sz = fn_8030585C(0x260, 0x1C0, 6, 0, 0);
        p->f->x28 = 8;
        p->f->a1 = 0x7F;
        break;
    case 1:
        p->f->a = 0;
        sz = fn_8030585C(0x130, 0xE0, 6, 0, 0);
        p->f->b = sz;
        sz += fn_8030585C(0x130, 0xE0, 6, 0, 0);
        p->f->c = sz;
        sz += fn_8030585C(0x98, 0x70, 6, 0, 0);
        break;
    case 3:
        p->f->a = 0;
        sz = fn_8030585C(0x130, 0xE0, 6, 0, 0);
        p->f->b = sz;
        sz += fn_8030585C(0x130, 0xE0, 6, 0, 0);
        p->f->c = sz;
        sz += fn_8030585C(0x98, 0x70, 6, 0, 0);
        break;
    case 7:
    case 8:
        p->f->a = 0;
        sz = fn_8030585C(0x130, 0xE0, 6, 0, 0);
        p->f->b = sz;
        sz += fn_8030585C(0x130, 0xE0, 6, 0, 0);
        p->f->c = sz;
        sz += fn_8030585C(0x98, 0x70, 6, 0, 0);
        p->f->d = sz;
        sz += fn_8030585C(0x130, 0xE0, 0x13, 0, 0);
        p->f->x28 = 0xEF;
        break;
    case 2:
        p->f->a = 0;
        sz = fn_8030585C(0x130, 0xE0, 6, 0, 0);
        p->f->a2 = 0xFF;
        p->h38 = p->f->a2;
        p->h3A = 0;
        p->h34 = 0;
        p->h36 = 0x1E;
        break;
    case 4:
        p->f->a = 0;
        sz = fn_8030585C(0x260, 0x1C0, 0x28, 0, 0);
        break;
    case 9:
        p->f->a = 0;
        sz = fn_8030585C(0x130, 0xE0, 0x13, 0, 0);
        break;
    case 12: {
        p->f->a = 0;
        sz = fn_8030585C(0x260, 0x1C0, 0x28, 0, 0);
        SetCol(p->f, kTint);
        break;
    }
    }
    p->f->mode = mode;
    Filter* f = p->f;
    if (f->base) fn_80079978(f->base);
    if (sz > 0) {
        f->base = fn_80079940(sz, 0x40);
        DCInvalidateRange(f->base, sz);
    }
}
}
