/* fn_801D820C (round 22, agent r22b): class `sched`, 2 masked words differ.
 * Draw a selectable icon frame: background sprite 0xA at (x, y), then sprite idx of the
 * icon sheet (fn_80006B84) tinted white when `on` (grey 80 80 80 E4 when off). With `on`
 * and `pulse` the tint pulses once a second: v = 255 * (0.5 * (1 + sin(2*pi*ms/1000))
 * + 0.5), clamped to 255, colour (v, v, v, 255). Drawn squeezed (0.7638191 * width) at
 * (x+6, y+6) when fn_801D09F0() returns non-zero, else at (x+4, y+4).
 * Built with tools/equiv/mkself.py from rR_80175E5C/fn_801D772C.cpp and the section in
 * rR_80175E5C/wip/fn_801D772C.cpp (161 of 212 words before), with these fixes:
 *  - the base colours are local POD aggregate initialisers returned from an inline
 *    (baseCol): the original reads them as .sdata2 templates (lbl_804CF7FF+1..+8) and
 *    copies the result word-wise; the fragment indexed lbl_804CF7FF as an array;
 *  - fn_8028C764 (s64 -> float, __cvt_sll_flt) returns f32: the fragment declared it f64
 *    and added an frsp; fn_8028C418/fn_8028C634 are the signed __div2i/__mod2i;
 *  - `r = &lbl_804CBAE8` after the second alpha call.
 * Remaining: the colour argument's byte copies and the squeezed-width conversion are
 * scheduled differently; our pulse colour reads its 0xFF from a 4-byte template instead of
 * the original's single byte (same value, verified). symcheck --anon --xargs: 48 blocks,
 * 0 differ.
 */
/* Window parts built from the sheet sprite primitives. The primitives are declared here
   with s16 and u16 arguments, which is what the callers extend to; the definitions in
   fn_801D60D0.cpp take int. */
#include "game/rR_80175E5C/types.h"
#include "game/rR_80175E5C/rects.h"

extern "C" {
extern u8 lbl_8041EF60[0x20];
extern u8 lbl_8041EF80[0x20];
void fn_801D60D0(s16 x, s16 y, s16 w, s16 h, u16 fl, Rect* src, int flip);
void fn_801D620C(s16 x, s16 y, s16 w, s16 h, u16 fl, Rect* src, int flip);
void fn_801D6388(s16 x, s16 y, s16 w, s16 h, u16 fl, const Color& c, int flip);
void fn_801D64AC(s16 x, s16 y, u16 fl, Rect* src, const Color& c, int flip);
void fn_801D65EC(s16 x, s16 y, u16 fl, Rect* src, const Color* c, int flip);
void fn_801D68E4(s16 x, s16 y, s16 w, s16 h, u16 fl, Rect* src, const Color& c, int flip);
void fn_801D6A4C(s16 x, s16 y, s16 w, s16 h, u16 fl, Rect* src, const Color& c, int flip);
void fn_801D6BC0(s16 x, s16 y, s16 w, s16 h, u16 fl, Rect* src, const Color& c, int flip);
void fn_801D6D68(s16 x, s16 y, s16 w, s16 h, u16 fl, Rect* src, const Color& c, int flip);
void fn_801D6F1C(s16 x, s16 y, s16 w, s16 h, u16 fl, const Color& c);


extern void* lbl_804CBDF8;

#define SPR(i) fn_80006A64(lbl_804CBDF8, lbl_8041EF60, i)
#define SPRB(i) fn_80006A64(lbl_804CBE08, lbl_8041EF60, i)
static inline void Alpha(f32 v) { fn_8007E154(); fn_8007E720(v); fn_8007E164(); }

#define ONE(name, idx, rect) \
void name(s16 x, s16 y, u16 fl) { \
    SPR(idx); \
    fn_801D60D0(x, y, RW(rect), RH(rect), fl, &rect, 0); \
}















#pragma use_lmw_stmw on


#pragma use_lmw_stmw off

void fn_801D855C(s16 x, s16 y, s16 w, u16 fl);

void fn_801D870C(s16 x, s16 y, s16 w, u16 fl);

void fn_801D88F4(s16 x, s16 y, s16 w, u16 fl);

void fn_801D95A0(s16 x, s16 y, s16 w, u16 fl);

void fn_801D8ADC(s16 x, s16 y, s16 w, u16 fl);


#pragma use_lmw_stmw on
#define WAVE(name, a, b, ra, rb) \
void name(s16 x, s16 y, u16 fl) { \
    s16 rem = 0x260 - x; \
    SPR(a); \
    fn_801D60D0(x, y, RW(ra), RH(ra), fl, &ra, 0); \
    fn_801D60D0(x, y + RH(ra), RW(ra), RH(ra), fl, &ra, 2); \
    s16 w = RW(ra); \
    if (rem > w) { \
        SPR(b); \
        int nr = rem - w; \
        int nx = x + w; \
        fn_801D620C(nx, y, nr, RH(rb), fl, &rb, 0); \
        fn_801D620C(nx, y + RH(rb), nr, RH(rb), fl, &rb, 2); \
    } \
}

void fn_801D9064(s16 x, s16 y, u16 fl);


void fn_8006E610(int, int, int, int, int, int);
int fn_801D09F0();
void fn_801D92D0(s16 x, s16 y, int kind, u16 fl);


#pragma use_lmw_stmw on

#pragma use_lmw_stmw off

void fn_801DA350(s16 x, s16 y, s16 w, u16 fl);

void fn_801DA618(s16 x, s16 y, s16 w, u16 fl);



extern void* lbl_804CBE08;
void fn_801D9E24(s16 x, s16 y, int sel, u16 fl);


#pragma use_lmw_stmw on

void fn_801DB770(s16 x, s16 y, s16 w, s16 h, u16 fl);

void fn_801DBA68(s16 x, s16 y, s16 w, s16 h, u8 a, u16 fl);

#pragma use_lmw_stmw off

extern u8 lbl_804CF840[8];
}
static inline void Inner(s16 x, s16 y, s16 w, s16 h, u16 fl) {
    int y2, x2;
    SPR(0x78);
    fn_801D60D0(x, y, RW(lbl_804CBD50), RH(lbl_804CBD50), fl, &lbl_804CBD50, 0);
    x2 = x + w;
    fn_801D60D0(x2 - RW(lbl_804CBD50), y, RW(lbl_804CBD50), RH(lbl_804CBD50), fl, &lbl_804CBD50, 1);
    y2 = y + h;
    fn_801D60D0(x, y2 - RH(lbl_804CBD50), RW(lbl_804CBD50), RH(lbl_804CBD50), fl, &lbl_804CBD50, 2);
    fn_801D60D0(x2 - RW(lbl_804CBD50), y2 - RH(lbl_804CBD50), RW(lbl_804CBD50), RH(lbl_804CBD50), fl, &lbl_804CBD50, 3);
    SPR(0x79);
    fn_801D620C(x + RW(lbl_804CBD50), y, w - RW(lbl_804CBD50) * 2, RH(lbl_804CBD50), fl, &lbl_804CBD58, 0);
    fn_801D620C(x + RW(lbl_804CBD50), y2 - RH(lbl_804CBD50), w - RW(lbl_804CBD50) * 2, RH(lbl_804CBD50), fl, &lbl_804CBD58, 2);
    SPR(0x7A);
    fn_801D620C(x, y + RH(lbl_804CBD50), RW(lbl_804CBD50), h - RH(lbl_804CBD50) * 2, fl, &lbl_804CBD60, 0);
    fn_801D620C(x2 - RW(lbl_804CBD50), y + RH(lbl_804CBD50), RW(lbl_804CBD50), h - RH(lbl_804CBD50) * 2, fl, &lbl_804CBD60, 1);
    SPR(0x7B);
    fn_801D620C(x + RW(lbl_804CBD50), y + RH(lbl_804CBD50), w - RW(lbl_804CBD50) * 2, h - RH(lbl_804CBD50) * 2, fl, &lbl_804CBD68, 0);
}
extern "C" {
#define BIGWIN(name) \
void name(s16 x, s16 y, s16 w, s16 h, u16 fl) { \
    int ch = RH(lbl_804CBD78); \
    int cw = RW(lbl_804CBD80); \
    SPR(0x7F); \
    int iw = w - cw * 2; \
    int ix = x + cw; \
    fn_801D620C(ix, y, iw, RH(lbl_804CBD78), fl, &lbl_804CBD78, 0); \
    fn_801D620C(ix, y + h - RH(lbl_804CBD78), iw, RH(lbl_804CBD78), fl, &lbl_804CBD78, 2); \
    SPR(0x80); \
    int ih = h - ch * 2; \
    int iy = y + ch; \
    fn_801D620C(x, iy, RW(lbl_804CBD80), ih, fl, &lbl_804CBD80, 0); \
    fn_801D620C(x + w - RW(lbl_804CBD80), iy, RW(lbl_804CBD80), ih, fl, &lbl_804CBD80, 1); \
    Alpha(3.0f); \
    Color a(lbl_804CF840[4], lbl_804CF840[5], lbl_804CF840[6], lbl_804CF840[7]); \
    Color b(a); \
    fn_801D6388(ix, iy, iw, ih, fl, b, 0); \
    Alpha(-3.0f); \
    Alpha(2.9f); \
    Inner(x + 0xC, y + 0xE0, w - 0x18, h - 0xEC, 0x10); \
    Alpha(-2.9f); \
}

#pragma use_lmw_stmw off

void fn_801DBDF0(s16 x, s16 y, u16 fl);


extern const u8 lbl_804CF7FF[9];
typedef unsigned long long u64;
long long OSGetTime();
long long fn_8028C418(long long, long long); /* __div2i */
long long fn_8028C634(long long, long long); /* __mod2i */
f32 fn_8028C764(long long); /* __cvt_sll_flt */
f64 fn_80295940(f64);
void fn_80006B84(void*, void*, void*, int, int);
#define ALPHAQ(v) do { fn_8007E154(); fn_8007E720(v); fn_8007E164(); } while (0)

}

/* ---- from build/tmp/r22b/fr_20c.cpp ---- */
extern "C" {
extern "C" {
/* fn_801D820C: 161 of 212 words differ */
struct GC { u8 r, g, b, a; };
static inline GC baseCol(int on) {
    if (on) {
        GC t = {0xFF, 0xFF, 0xFF, 0xFF};
        return t;
    }
    GC t = {0x80, 0x80, 0x80, 0xE4};
    return t;
}
void fn_801D820C(s16 x, s16 y, int idx, int on, int pulse, u16 fl) {
    ALPHAQ(on ? -1.0f : -0.0f);
    SPR(0xA);
    fn_801D60D0(x, y, RW(lbl_804CBAE0), RH(lbl_804CBAE0), fl, &lbl_804CBAE0, 0);
    ALPHAQ(on ? 1.0f : 0.0f);
    Rect* r = &lbl_804CBAE8;
    ALPHAQ(on ? -1.01f : -0.01f);
    GC c = baseCol(on);
    if (on && pulse) {
        f32 s = fn_80295940(6.2831855f * (fn_8028C764(fn_8028C634(fn_8028C418(OSGetTime(), (*(u32*)0x800000F8 / 4) / 1000), 1000)) / 1000.0f));
        u16 v = 255.0f * (0.5f * (1.0f + s) + 0.5f);
        if (v > 0xFF) v = 0xFF;
        GC t = {v, v, v, 0xFF};
        c = t;
    }
    fn_80006B84(lbl_804CBDF8, lbl_8041EF60, lbl_8041EF80, 0, idx);
    if (fn_801D09F0()) {
        fn_801D6D68(x + 6, y + 6, (s16)(0.7638191f * RW(*r)), RH(*r), fl, r, Color(c.r, c.g, c.b, c.a), 0);
    } else {
        fn_801D6A4C(x + 4, y + 4, RW(*r), RH(*r), fl, r, Color(c.r, c.g, c.b, c.a), 0);
    }
    ALPHAQ(on ? 1.01f : 0.01f);
}

}
}
