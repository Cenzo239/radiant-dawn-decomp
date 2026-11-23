/* fn_80265574: exact (round m7). The text position reuses the function's int locals x and y
 * (`x = (int)(...); y = (int)(...); draw((s16)x, (s16)y, ...)`), which gives lwz r0 / lwz r4 before the extsh pair. */
/* Dictionary relation chart: label and text */
#include "game/rN_8025EEF0/dict.h"
#include "game/rN_8025EEF0/prim2d.h"

extern "C" {

void fn_801BCA5C(f32 v);
void fn_801BCA94(void);
int fn_800CA3DC(const char* s, int a, f32 v);
void fn_800CB3A8(int x, int y, int a, int b, int c, f32 s, f32 t, const char* f, ...);
u8* fn_800D4228(const char* s);
u8* fn_800D4188(const char* s, void* p);
void fn_80263DE0(const char* s);

struct RelLabel { const char* name; s16 x; s16 y; const char* msg; int style; u8 pad10[4]; s16 tx; s16 ty; };

static inline void SetPos(u8* p, f32 x, f32 y) { *(f32*)(p + 0x40) = x; *(f32*)(p + 0x44) = y; }
static inline void SetV(u8* p, f32 x, f32 y) { *(f32*)(p + 0x4C) = x; *(f32*)(p + 0x50) = y; }
static inline void SetS(u8* p, f32 x, f32 y) { *(f32*)(p + 0x54) = x; *(f32*)(p + 0x58) = y; }

static inline void DrawA(int x, int y, int c, f32 sc, const char* s) { fn_800CB3A8((s16)x, (s16)y, c, 1, 0, sc, 0.0f, s); }
static inline void DrawB(s16 x, s16 y, int c, f32 sc, const char* s) { fn_800CB3A8(x, y, c, 1, 0, sc, 0.0f, s); }
static inline void DrawC(f32 x, f32 y, int c, f32 sc, const char* s) { fn_800CB3A8((s16)x, (s16)y, c, 1, 0, sc, 0.0f, s); }

void fn_80265574(RelLabel* e) {
        u8* p;
    f32 lh;
    const char* s;
    int x;
    int y;
    int ty;
    f32 sc;
    int color;
    char buf[0x40];
    int tx;
    int i;

    x = e->x;
    y = e->y;
    tx = e->tx;
    ty = e->ty;
    lh = 14.0f;
    sc = 0.7f;
    if (e->name != 0) {
        fn_80290DDC(buf, lbl_80372C90 + 0x11C, e->name);
        p = fn_800D4228(buf);
        if (p == 0) {
            p = fn_800D4188(buf, lbl_804CC000);
        }
        if (p != 0) {
            SetPos(p, (f32)x + lbl_804CC008->f54, (f32)y + lbl_804CC008->f58);
            SetV(p, 0.0f, 0.0f);
            SetS(p, lbl_804CC008->f5C, lbl_804CC008->f60);
        }
    }
    if (e->msg != 0) {
        switch (e->style) {
        case 0:
            color = 0x2E;
            break;
        case 1:
            color = 0x2F;
            break;
        case 2:
            color = 0x30;
            break;
        default:
            color = 0x2E;
            break;
        }
        fn_801BCA5C(-5.0f);
        fn_801BCA94();
        fn_80263DE0(fn_800D0864(e->msg));
        if (lbl_804CC008->nlines >= 2) {
            ty = (f32)ty - lh * (f32)(lbl_804CC008->nlines - 1) / 2.0f;
        }
        for (i = 0; i < lbl_804CC008->nlines; i++) {
            s = lbl_804CC008->lines[i];
            x = (int)((f32)tx - sc * (f32)fn_800CA3DC(s, -1, 1.0f) / 2.0f);
            y = (int)(lh * (f32)i + (f32)ty);
            fn_800CB3A8((s16)x, (s16)y, color, 1, 0, sc, 0.0f, s);
        }
        fn_801BCA5C(5.0f);
    }
}

}
