/* NEAR MISS: same size; off is coloured first (r31, should be r29) so x and yy shift; fn_80282D00 in this file is a copy of the matched one. */
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
    s16 q;
    s16 y;
    s16 c;
    int k;
    int xi;
    int yi;
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
        d = p->w - a - b;
        xi = (0x260 - p->w) / 2;
        p->dx = xi;
        q = d / 3;
        yi = (0x1E0 - p->h) / 2;
        p->dy = yi;
        p->m20 = xi + q;
        c = yi + k + p->nline * 0x14 + 0x12;
        p->m24 = q * 2 + xi + a;
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

static inline void icon(Dlg* p, s16 x, s16 y, u32& w, u32& h, s16& ay) {
/*P*/
    void* m;
    int ax;
/*E*/
        m = lbl_804CB58C;
        u16* d = *fn_80006A0C(m, 0x25);
        w = d[1];
        h = d[0];
        ax = (s16)(x + p->w / 2 - 0x18);
        ay = y + 0x10;
        fn_8007E154();
        fn_8007E374(m, 0x25, 0x11);
        fn_8007E164();
        fn_800800D4(1);
        fn_80080348(ax, ay, 0.0f, 0.0f);
        fn_80080368((int)(ax + w), (int)(ay + h), w, h);
        fn_80080308();
    }

void fn_80282FF4(Dlg* p) {
/*P*/
    s16 x;
    u32 w;
    int yy;
    char* s2;
    int off;
    int yy2;
    s16 ay;
    char* s;
    int i2;
    s16 y;
    u32 h;
    int i;
/*E*/
    if (!(p->st & 1)) return;
    {
        f32 sc = fn_8017F68C(0.0f, 1.0f, p->fr, 5.0f, 0);
        fn_8007E154();
        fn_8007E4E4(304.0f, 244.0f, 120.0f, sc);
        fn_8007E164();
    }
    {
        x = 0.5f * (f32)-p->w;
        y = 0.5f * (f32)-p->h;
        fn_801BCA5C(-10.0f);
    }
    {
        fn_8006FE30(x, y, p->w, p->h, (p->st & 4) ? WK_3C : WK_3B);
    }
    fn_801BCA5C(-3.0f);
    off = (p->st & 4) ? 0x28 : 0;
    if (big(p->st) == 1) icon(p, x, y, w, h, ay);
    fn_801BCA94();
    s = p->line[0];
    yy = 0xE + off + y;
    for (i = 0; i < p->nline; i++) {
        int t = fn_800CA3DC(s, -1, 1.0f);
        fn_800CB3A8((s16)(int)-(0.5f * (f32)t - (f32)(x + p->w / 2)), yy, 1, 1, 0, 1.0f, 0.0f, s);
        s += 0x41;
        yy += 0x14;
    }
    switch (p->sel) {
    case 1:
        fn_800CB3A8(XF(p->m20), YF(p->m22), 1, 1, 0, 1.0f, 0.0f, fn_800D0864(lbl_80373AA0));
        fn_800CB3A8(XF(p->m24), YF(p->m26), 1, 1, 0, 1.0f, 0.0f, fn_800D0864(lbl_80373AA0 + 7));
        break;
    }
    s2 = p->sub[0];
    yy2 = off * 2;
    for (i2 = 0; i2 < p->nsub; i2++) {
        int t = fn_800CA3DC(s2, -1, 1.0f);
        fn_800CB3A8((s16)(int)-(0.5f * (f32)t - (f32)(x + p->w / 2)), (s16)(p->m22 + (yy2 + 0x20 - p->dy) + y), 1, 1, 0, 1.0f, 0.0f, s2);
        s2 += 0x41;
        yy2 += 0x14;
    }
    fn_801BCA5C(13.0f);
    if (p->fl & 1) {
        fn_8007E154();
        fn_8007E4E4(0.0f, 0.0f, 100.0f, 1.0f);
        fn_8007E164();
        fn_801BCA5C(-20.0f);
        fn_800712E8(p->cx, p->cy, 1);
        fn_801BCA5C(20.0f);
    }
}

}
