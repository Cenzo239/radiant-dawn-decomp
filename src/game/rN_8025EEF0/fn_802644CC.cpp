/* Dictionary list page frame and text lines */
#pragma inline_max_size(4000)
#pragma inline_max_total_size(4000)
#include "game/rN_8025EEF0/dict.h"
#include "game/rN_8025EEF0/prim2d.h"

struct GXC { u8 r, g, b, a; };
struct DRect { s16 x, y, w, h; };

extern "C" {

void fn_801BCA5C(f32 v);
void fn_801BCA94(void);
void* fn_80076F54(const char* s);
u16** fn_80006A0C(void* tex, int i);
u8* fn_800CD204(int i);
void fn_801BC88C(f32 x, f32 y, f32 x2, f32 y2, f32 a, f32 b, f32 w, f32 h, void* tex, int i, GXC c, int d, int e);
const char* fn_80118C44(void* u);
void fn_800CB278(s16 x, s16 y, int a, const char* f, ...);
#if TARGET_PC
FE10_PROTO void fn_8007E74C(ptr32<const void>, ptr32<const void>);
#else
void fn_8007E74C(void* f, void* a);
#endif
void fn_8007E7B4(void);
void fn_80072ACC(int x, int y, int w, int h, int a, int b, int c);
void fn_800712E8(int x, int y, int a);
void fn_80263B4C(void* p, void* arg);

extern char lbl_804CC014;
extern DRect lbl_804CC018;

static inline GXC mk(const u8* p) { GXC c; c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = 0xFF; return c; }

static inline void draw(int i, int x0, int y0, int x1, int y1, int r) {
/*P*/
    u16* d;
    u16 w;
    u16 h;
    void* tex;
    u8* p;
    GXC c;
/*E*/
    tex = *(void**)lbl_804CC004;
    d = *fn_80006A0C(tex, i);
    w = d[1];
    h = d[0];
    p = fn_800CD204(1);
    c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = 0xFF;
    fn_801BC88C(x0, y0, x1, y1, 0.0f, 0.0f, w, h, tex, i, c, 0x11, r);
}
static inline void draw2(int i, int x0, int y0, int r) {
/*P*/
    u16* d;
    u16 w;
    u16 h;
    void* tex;
    u8* p;
    GXC c;
/*E*/
    tex = *(void**)lbl_804CC004;
    d = *fn_80006A0C(tex, i);
    w = d[1];
    h = d[0];
    p = fn_800CD204(1);
    c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = 0xFF;
    fn_801BC88C(x0, y0, x0 + w, y0 + h, 0.0f, 0.0f, w, h, tex, i, c, 0x11, r);
}

static inline void drawB(int i, int x0, int y0, int x1, int y1, int r, void*& tex, u16& w, u16& h) {
/*P*/
    u16* d;
    u8* p;
    GXC c;
/*E*/
    tex = *(void**)lbl_804CC004;
    d = *fn_80006A0C(tex, i);
    w = d[1];
    h = d[0];
    p = fn_800CD204(1);
    c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = 0xFF;
    fn_801BC88C(x0, y0, x1, y1, 0.0f, 0.0f, w, h, tex, i, c, 0x11, r);
}
static inline void draw2B(int i, int x0, int y0, int r, void*& tex, u16& w, u16& h) {
/*P*/
    u16* d;
    u8* p;
    GXC c;
/*E*/
    tex = *(void**)lbl_804CC004;
    d = *fn_80006A0C(tex, i);
    w = d[1];
    h = d[0];
    p = fn_800CD204(1);
    c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = 0xFF;
    fn_801BC88C(x0, y0, x0 + w, y0 + h, 0.0f, 0.0f, w, h, tex, i, c, 0x11, r);
}

static inline void sides(int x, int y) {
/*P*/
        u16 w;
        u16 h;
        int ym;
        u16 w2;
        u16 h2;
        void* tex2;
        void* tex;
/*E*/
        ym = y + 0x10;
        drawB(5, x, ym, x + 8, ym + 0xF8, 0, tex, w, h);
        drawB(5, x + 0xB8, ym, x + 0xC0, ym + 0xF8, 1, tex2, w2, h2);
}
static inline void bottom(int x, int y) {
/*P*/
        u16 w;
        u16 w2;
        u16 w3;
        u16 h2;
        u16 h;
        void* tex2;
        u16 h3;
        void* tex;
        void* tex3;
        int ym2;
/*E*/
        ym2 = y + 0x108;
        draw2B(7, x, ym2, 2, tex, w, h);
        drawB(6, x + 0x20, ym2 + 8, x + 0xA0, ym2 + 0x10, 2, tex2, w2, h2);
        draw2B(7, x + 0xA0, ym2, 3, tex3, w3, h3);
}
static inline void lines(int x, int y, DictState* pg, f32 frac, const char*& s) {
/*P*/
    int k;
    DictState* st;
    int i;
    void* u;
/*E*/
    {
        for (i = 0; i < 10; i++) {
            k = (int)pg->f38 + i;
            if (k >= (st = lbl_804CC004)->listCount) break;
            switch (st->page) {
            case 0: {
                u = fn_80076F54(*(const char**)st->list[k]);
                if (u == 0) {
                    s = lbl_80372C90 + 0x213;
                } else {
                    s = fn_80118C44(u);
                }
                break;
            }
            case 1:
                s = *(const char**)st->list[k];
                break;
            }
            fn_800CB278(x + 0xC, 28.0f * ((f32)i - frac) + (f32)(y + 0x10), 1, fn_800D0864(s));
        }
    }
}
static inline void inner(int x,int y,const char*& s){
/*P*/
 f32 frac;
 DictState* pg;
/*E*/
    pg = DICT_PAGE(lbl_804CC004, lbl_804CC004->page);
    lbl_804CC018.x = x + 0xB;
    lbl_804CC018.y = y + 9;
    lbl_804CC018.w = 0x96;
    lbl_804CC018.h = 0x105;
    frac = pg->f38 - (f32)(int)pg->f38;
    fn_801BCA5C(-1.0f);
    draw(8, x, y, x + 0xC7, y + 0x118, 0);
    fn_801BCA5C(-1.0f);
    draw2(7, x, y, 0);
    draw(6, x + 0x20, y, x + 0xA0, y + 8, 0);
    draw2(7, x + 0xA0, y, 1);
    sides(x, y);
    bottom(x, y);
    fn_801BCA5C(-1.0f);
    fn_8007E154();
    fn_8007E74C(fn_80263B4C, &lbl_804CC018);
    fn_8007E164();
    fn_801BCA94();
    lines(x, y, pg, frac, s);
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
    if (lbl_804CC004->mode == 1) {
        fn_801BCA5C(-1.0f);
        fn_80072ACC(pg->m2A + 0x50, pg->m2C + 0x10, 0xA0, 0x17, 0x19, 0x4B, 1);
        fn_801BCA5C(-1.0f);
        fn_800712E8(pg->m2A, pg->m2C, 1);
        fn_801BCA5C(2.0f);
    }
    fn_801BCA5C(3.0f);
}
void fn_802644CC(int x, int y) {
    const char* s;
    if (!lbl_804CC014) {
        lbl_804CC014 = 1;
    }
    inner(x,y,s);
}

}
