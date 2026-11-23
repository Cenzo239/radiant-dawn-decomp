/* Confirm dialog: per-frame update and draw */
#pragma inline_max_size(4000)
#include "game/rN_8025EEF0/prim2d.h"

extern "C" {

extern char lbl_80373AA0[];
extern void* lbl_804CB58C;
f32 fn_8017F68C(f32 a, f32 b, f32 c, f32 d, int e);
int fn_800CA3DC(const char* s, int a, f32 v);
void fn_801BCA5C(f32 v);
void fn_801BCA94(void);
void fn_8006FE30(f32 a, f32 b, f32 c, f32 d, int e);
u16** fn_80006A0C(void* tex, int i);
void fn_80080348(f32 a, f32 b, f32 c, f32 d);
void fn_80080368(f32 a, f32 b, f32 c, f32 d);
void fn_800CB3A8(int x, int y, int a, int b, int c, f32 s, f32 t, const char* f, ...);
void fn_800712E8(int x, int y, int a);

struct Dlg {
    s16 fl;
    s16 cx, cy, m6, m8, mA, mC;
    s16 cnt, max;
    s16 st, state, sel, dx, dy, w, h;
    s16 m20, m22, m24, m26;
    s16 fr;
    char line[7][0x41];
    char sub[7][0x41];
    s8 nline, nsub;
};

enum WinKind { WK_3B = 0x3B, WK_3C = 0x3C };

#define YF(v) (s16)((off + y) + (v - p->dy) + 4)
#define XF(v) (s16)(x + v - p->dx)
void fn_80282D00(Dlg* p) {
/*P*/
    s16 a;
    s16 b;
    int d;
    u16 x;
    int yi;
    s16 y;
    s16 c;
    int k;
    int xi;
    s16 q;
/*E*/
    switch (p->state) {
    case 0:
        p->st = 0;
        break;
    case 100:
        p->st |= 1;
        p->state = 0x6E;
    case 0x6E:
        if (++p->fr >= 5) {
            p->fr = 5;
            p->state = 200;
        }
        break;
    case 200:
        break;
    case 300:
        p->st |= 1;
        p->state = 0x136;
    case 0x136:
        if (--p->fr <= 0) {
            p->fr = 0;
            p->state = 0;
            p->st = 0;
        }
        break;
    }
    a = fn_800CA3DC(fn_800D0864(lbl_80373AA0), -1, 1.0f);
    b = fn_800CA3DC(fn_800D0864(lbl_80373AA0 + 7), -1, 1.0f);
    k = (p->st & 4) ? 0x28 : 0;
    switch (p->sel) {
    case 0:
    case 1:
xi = (0x260 - p->w) / 2;
p->dx = xi;
yi = (0x1E0 - p->h) / 2;
p->dy = yi;
q = (p->w - a - b) / 3;
p->m20 = xi + q;
c = yi + k + 0x12 + p->nline * 0x14;
p->m24 = xi + a + q * 2;
p->m22 = c;
p->m26 = c;
            break;
    }
    if ((p->fl & 1) && p->cnt > 0) {
        p->cnt--;
        p->cx = fn_8017F68C(p->m6, p->mA, p->max - p->cnt, p->max, 4);
        p->cy = fn_8017F68C(p->m8, p->mC, p->max - p->cnt, p->max, 4);
    }
}

static inline u16 big(s16 st) { return (u16)(st & 4) != 0; }

}
