/* fn_800CB69C (0x1080): functionally equal at `sched` level (tools/check_regs.py, round 21; 1056 of 1056
 * instructions, 18 integer and 18 float saved registers as in the original). New this round, written from the
 * disassembly. Needs fn_800CB69C.symbols.json (the function-local static `dirs` is lbl_80382E68, its guard
 * lbl_804CB6F8; the four constant rows were compared with the DOL, the four diagonal rows are filled at run time
 * with cos/sin as in the original).
 * Moved instructions (tools/equiv/dd.py): in the entry block the `lbz` of colBot b/a and the stores of
 * lbl_804CB6F0 (0x110) and 0 (0x118) are in another order; before the main loop `subf` and two `lis` swap; in
 * the glyph set-up block before `bl fn_80077D18` the glyph byte loads, int-to-float scratch stores and float
 * operations are interleaved differently.
 * symcheck.py --anon flags 7 of 113 blocks:
 *   - block 2 (entry): "stack bytes differ at 0x110..0x113". Both store the word loaded from lbl_804CB6F0 there;
 *     ours loads it after the unrelated `stw 0,0x118(r1)`, the original before, which the checker numbers as
 *     different load versions. No aliasing: 0x118 is a local.
 *   - block 8: the loop-invariant set-up (`lis`/`subf` order, anonymous float names); same values.
 *   - block 14 (#C colour): r4/r6 hold the two palette bytes the other way round; stores are the same.
 *   - block 77 (glyph set-up): the checker sees a different leftover in f1 at `bl fn_80077D18`, which takes only
 *     integer arguments (r3..r7 are equal); live-out floats are the same values computed in another order.
 *   - blocks 92, 101, 103: the names `dirs$NN` / `@GUARD@dirs$NN` against lbl_80382E68 / lbl_804CB6F8 (mapped by
 *     the symbols.json), plus `lis; li; addi` order in 103.
 * Notes for a port:
 *   - WGPIPE is the GX FIFO at 0xCC008000; Pos3/Col4/Tex2 are GXPosition3f32/GXColor4u8/GXTexCoord2f32.
 *   - Res is a local view of the class of lbl_804CB6E0/lbl_804CB6E8/lbl_804CB6F0 (only slots 5, 15, 16 named);
 *     Glyph8/FontHdr8 are local views of the font structures (see fn_800CA3DC for the width function).
 *   - Val(), the top/bot save copies and the per-quad `C4 ct, cb` copies reproduce the original's stack copies.
 *   - check_func.py --strict-references prints three "wrong reference" lines; they come from the one-slot
 *     shifts and the static's local name, not from wrong targets.
 */
/* fn_800CB69C: draws a string at (x, y, z) with the current font, glyph by glyph as textured quads through the
 * GX FIFO. Handles the same '#' escapes as the width function fn_800CA3DC: #Cnn palette colour, #Rnn #Gnn #Bnn
 * #Ann colour channels, #c restore colour, #Snn #Xnn #Ynn scale (nn/64) and #s #x #y reset, #Inn slant (nn/16)
 * and #i reset, #E/#e shadow on/off, #O/#o outline on/off, #D reset all, ## literal '#', #Pnnn ruby/icon nnn
 * drawn by the resource object lbl_804CB6F0, #K/#k switch that object, #Fnn switch font. Names guessed. */
#pragma auto_inline off
#include "game/rG_800A3D88/types.h"
extern "C" {
typedef struct C4 { u8 r, g, b, a; } C4;
typedef struct V3 { f32 x, y, z; } V3;
typedef struct Glyph8 { u8 p0[8]; u8 w; u8 h; s8 left; s8 top; } Glyph8;
typedef struct FontHdr8 { u8 p0[8]; u16 base; u8 pA[0x18 - 0xA]; u16 fmt; u8 p1A[4]; u16 texW; u16 texH; } FontHdr8;
struct Res {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(int id, C4* col, f32 x, f32 y, f32 z);
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual int v15();
    virtual int v16();
};
typedef union Fifo { u8 u8; f32 f32; } Fifo;
volatile Fifo WGPIPE : 0xCC008000;
extern void* lbl_803E7260[6];
extern u8 lbl_804CB6E0[8];
extern u8 lbl_804CB6E8[8];
extern Res* lbl_804CB6F0;
#define RA ((Res*)lbl_804CB6E0)
#define RB ((Res*)lbl_804CB6E8)
FontHdr8* fn_80077F5C(void);
Glyph8* fn_80077DDC(const u8* s);
char* fn_80077D18(char* s, int* tex, int* u, int* v, int* adv);
int fn_80077BF0();
void* fn_80077DB0(void*);
int fn_800CA1B4(char**, u32);
u8* fn_800CD204(int);
void fn_8031292C(void*, f32, f32, f32);
void fn_80307F10(void*, int, int);
void fn_80305A40(void*, void*, u16, u16, int, int, int, int);
int fn_80305E4C(void*);
void fn_80305DB4(void*, int, int);
void fn_80022254(void*, int);
void fn_80304314(int, int, int);
f64 fn_80295534(f64);   /* cos */
f64 fn_80295940(f64);   /* sin */
void fn_800CB69C(f32 x, f32 y, f32 z, f32 scale, f32 slant, s16 sw, s16 sh, int alpha, C4* colTop, C4* colBot,
                 C4* colShadow, C4* colOutline, char* s);
}
static inline int SwapMode(int idx) {
    void* old = fn_80077DB0(lbl_803E7260[idx]);
    int i;
    for (i = 0; i < 6; i++) {
        if (lbl_803E7260[i] == old) return i;
    }
    return -1;
}
static inline void Pos3(f32 x, f32 y, f32 z) { WGPIPE.f32 = x; WGPIPE.f32 = y; WGPIPE.f32 = z; }
static inline void Col4(u8 r, u8 g, u8 b, u8 a) { WGPIPE.u8 = r; WGPIPE.u8 = g; WGPIPE.u8 = b; WGPIPE.u8 = a; }
static inline void Tex2(f32 s, f32 t) { WGPIPE.f32 = s; WGPIPE.f32 = t; }
static inline C4 Val(C4* p) { C4 t = *p; return t; }
static inline void FontMtx(FontHdr8* f, f32 (*m)[4]) {
    fn_8031292C(m, 1.0f / f->texW, 1.0f / f->texH, 1.0f);
    fn_80307F10(m, 0x1e, 1);
}

#define MAINQUAD() \
    fn_80304314(0x80, 0, 4); \
    Pos3(x0 + slTop, y0, z); Col4(tr, tg, tb, ta); Tex2(u0, v0); \
    Pos3(w + (x0 + slTop), y0, z); Col4(tr, tg, tb, ta); Tex2(u1, v0); \
    Pos3(w + (x0 + slBot), y0 + h, z); Col4(br, bg, bb, ba); Tex2(u1, v1); \
    Pos3(x0 + slBot, y0 + h, z); Col4(br, bg, bb, ba); Tex2(u0, v1)

void fn_800CB69C(f32 x, f32 y, f32 z, f32 scale, f32 slant, s16 sw, s16 sh, int alpha, C4* colTop, C4* colBot,
                 C4* colShadow, C4* colOutline, char* s) {
    f32 mtx[3][4];
    u8 texobj[0x20];
    void* texId;
    FontHdr8* font = fn_80077F5C();
    bool shadow = sw != 0;
    bool outline = sh != 0;
    f32 sx = 1.0f;
    f32 sy = sx;
    Res* saveRes = lbl_804CB6F0;
    C4 top = Val(colTop);
    C4 bot = Val(colBot);
    C4 topSave = top;
    C4 botSave = bot;
    texId = 0;
    int half;
    int ruby;
    f32 adv;

    if (!shadow) sw = 0x200;
    if (!outline) sh = 0x100;
    FontMtx(font, mtx);
    half = (((alpha & 0xFF) << 8) - alpha) >> 7;
    while (*s) {
        ruby = -1;
        if (*s == '#') {
            char* p = s;
            s = p + 2;
            switch (p[1]) {
            case 'C': {
                u8* q;
                topSave = top;
                botSave = bot;
                q = fn_800CD204((u8)fn_800CA1B4(&s, 2));
                bot.r = q[0]; bot.g = q[1]; bot.b = q[2];
                top.r = q[0]; top.g = q[1]; top.b = q[2];
                top.a = topSave.a;
                bot.a = botSave.a;
                continue;
            }
            case 'R':
                top.r = bot.r = fn_800CA1B4(&s, 2);
                continue;
            case 'G':
                top.g = bot.g = fn_800CA1B4(&s, 2);
                continue;
            case 'B':
                top.b = bot.b = fn_800CA1B4(&s, 2);
                continue;
            case 'A':
                top.a = bot.a = fn_800CA1B4(&s, 2);
                continue;
            case 'c':
                top = topSave;
                bot = botSave;
                continue;
            case 'S':
                sy = (u32)fn_800CA1B4(&s, 2) / 64.0f;
                sx = sy;
                continue;
            case 's':
                sy = 1.0f;
                sx = sy;
                continue;
            case 'X':
                sx = (u32)fn_800CA1B4(&s, 2) / 64.0f;
                continue;
            case 'x':
                sx = 1.0f;
                continue;
            case 'Y':
                sy = (u32)fn_800CA1B4(&s, 2) / 64.0f;
                continue;
            case 'y':
                sy = 1.0f;
                continue;
            case 'I':
                slant = (u32)fn_800CA1B4(&s, 2) / 16.0f;
                continue;
            case 'i':
                slant = 0.0f;
                continue;
            case 'E':
                shadow = 1;
                continue;
            case 'e':
                shadow = 0;
                continue;
            case 'O':
                outline = 1;
                continue;
            case 'o':
                outline = 0;
                continue;
            case 'D':
                shadow = 0;
                sy = 1.0f;
                sx = sy;
                outline = 0;
                top = *colTop;
                bot = *colBot;
                slant = 0.0f;
                continue;
            case '#':
                s--;
                break;
            case 'P':
                ruby = fn_800CA1B4(&s, 3);
                break;
            case 'K':
                saveRes = lbl_804CB6F0;
                lbl_804CB6F0 = RB ? RB : RA;
                continue;
            case 'k':
                lbl_804CB6F0 = saveRes ? saveRes : RA;
                continue;
            case 'F': {
                int n = fn_800CA1B4(&s, 2);
                if (n == -1) n = 0;
                SwapMode(n);
                font = fn_80077F5C();
                FontMtx(font, mtx);
                continue;
            }
            }
        }
        {
            u8 tr = top.r * alpha >> 7, tg = top.g * alpha >> 7, tb = top.b * alpha >> 7;
            u8 br = bot.r * alpha >> 7, bg = bot.g * alpha >> 7, bb = bot.b * alpha >> 7;
            u8 ta = top.a, ba = bot.a;
            f32 sxs = sx * scale;
            f32 sys = sy * scale;
            adv = 0.0f;
            if (ruby >= 0) {
                Res* r = lbl_804CB6F0;
                if (r != 0) {
                    f32 lh;
                    C4 rc;
                    r->v3();
                    r->v4();
                    r->v1();
                    lh = sys * fn_80077BF0();
                    lh = 0.5f * (lh - r->v16());
                    rc.b = half; rc.g = half; rc.r = half;
                    rc.a = (ta + ba + 1) >> 1;
                    r->v5(ruby, &rc, x, y + lh, z);
                    r->v2();
                    adv = r->v15();
                }
            } else {
                Glyph8* g = fn_80077DDC((const u8*)s);
                f32 gw = g->w;
                f32 gh = g->h;
                f32 w = gw * sxs;
                f32 h = gh * sys;
                f32 x0 = g->left * sxs + x;
                f32 y0 = font->base * sys + y - g->top * sys;
                f32 slTop = slant * sxs * ((f32)g->top / font->base);
                f32 slBot = slant * sxs * ((f32)(g->top - g->h) / font->base);
                u8 dirty = 0;
                int tex, tu, tv, ta4;
                f32 u0, v0, u1, v1;
                s = fn_80077D18(s, &tex, &tu, &tv, &ta4);
                u0 = tu;
                v0 = tv;
                u1 = u0 + gw;
                v1 = v0 + gh;
                adv = ta4 * sxs;
                if (texId != (void*)tex) {
                    fn_80305A40(texobj, (void*)tex, font->texW, font->texH, font->fmt, 0, 0, 0);
                    texId = (void*)tex;
                    dirty = 1;
                }
                if (fn_80305E4C(texobj) != 1) {
                    fn_80305DB4(texobj, 1, 1);
                    dirty = 1;
                }
                if (dirty) fn_80022254(texobj, 0);
                if (shadow) {
                    C4 ct = Val(colShadow);
                    f32 ox = sw / 256.0f * sxs;
                    C4 cb = ct;
                    f32 oy = sw / 256.0f * sys;
                    ct.a = 0.003921569f * (ct.a * ta);
                    cb.a = 0.003921569f * (cb.a * ba);
                    fn_80304314(0x80, 0, 4);
                    Pos3(ox + (x0 + slTop), y0 + oy, z); Col4(ct.r, ct.g, ct.b, ct.a); Tex2(u0, v0);
                    Pos3(ox + (w + (x0 + slTop)), y0 + oy, z); Col4(ct.r, ct.g, ct.b, ct.a); Tex2(u1, v0);
                    Pos3(ox + (w + (x0 + slBot)), oy + (y0 + h), z); Col4(cb.r, cb.g, cb.b, cb.a); Tex2(u1, v1);
                    Pos3(ox + (x0 + slBot), oy + (y0 + h), z); Col4(cb.r, cb.g, cb.b, cb.a); Tex2(u0, v1);
                    MAINQUAD();
                } else if (outline) {
                        static V3 dirs[8] = {
                            {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, -1.0f, 0.0f},
                            {fn_80295534(0.7853981852531433), fn_80295940(0.7853981852531433), 0.0f},
                            {fn_80295534(2.356194496154785), fn_80295940(2.356194496154785), 0.0f},
                            {fn_80295534(3.9269909858703613), fn_80295940(3.9269909858703613), 0.0f},
                            {fn_80295534(5.4977874755859375), fn_80295940(5.4977874755859375), 0.0f},
                        };
                    C4 ct = Val(colOutline);
                    C4 cb = ct;
                    f32 rad;
                    int i;
                    V3* d;
                    ct.a = 0.003921569f * (ct.a * ta);
                    cb.a = 0.003921569f * (cb.a * ba);
                    rad = sh / 256.0f;
                    fn_80304314(0x80, 0, 0x20);
                    for (i = 0, d = dirs; i < 8; i++, d++) {
                        f32 dx = rad * d->x;
                        f32 dy = rad * d->y;
                        Pos3(dx + (x0 + slTop), y0 + dy, z); Col4(ct.r, ct.g, ct.b, ct.a); Tex2(u0, v0);
                        Pos3(dx + (w + (x0 + slTop)), y0 + dy, z); Col4(ct.r, ct.g, ct.b, ct.a); Tex2(u1, v0);
                        Pos3(dx + (w + (x0 + slBot)), dy + (y0 + h), z); Col4(cb.r, cb.g, cb.b, cb.a); Tex2(u1, v1);
                        Pos3(dx + (x0 + slBot), dy + (y0 + h), z); Col4(cb.r, cb.g, cb.b, cb.a); Tex2(u0, v1);
                    }
                    MAINQUAD();
                } else {
                    MAINQUAD();
                }
            }
            x += adv;
        }
    }
}
