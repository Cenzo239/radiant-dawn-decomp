/* near miss: fn_801AF2A8, 53 words: only registers in the first (lang 0) branch. str/lbl take r30/r29, the original r29/r28. Adding a use of r after the join (fn_801BCA5C(r)) makes that whole branch match, so r30 must be live across the branch in the original, with no instruction reading it afterwards. if(0), code after return, self assignments had no effect. */
#include "game/rF_8017F400/types.h"
#pragma auto_inline off
extern "C" {
/* chapter result screen: turn count, play time, ranks */
struct C4 { u8 r, g, b, a; };
typedef struct PData { u32 x0; u32 x4; s64 t; void* x10; } PData;
typedef struct Lang { u8 pad[0x1BC8]; s8 lang; } Lang;
extern u8 lbl_803CAB38[];
extern char lbl_8036D68C[];
extern void fn_8017FA84(s64, u32*, u32*, u32*);
extern void fn_801BCA5C(f32);
extern void fn_801BCA94(void);
extern const C4* fn_800CD204(int);
extern void** fn_80006A0C(void*, int);
extern void fn_801BC88C(void*, int, C4, int, u32, f32, f32, f32, f32, f32, f32, f32, f32);
extern Lang* fn_8024BC94(void);
extern const char* fn_800D0864(const char*);
extern int fn_800CA3DC(const char*, int, f32);
extern void fn_800CB3A8(f32, f32, s16, s16, int, int, int, const char*, ...);
extern u8 fn_800634D8(void*);
extern u8 fn_80063568(void*);
extern u8 fn_80063620(void*);
extern u8 fn_8006376C(void*);

static inline C4 Mk(const C4* q) {
    C4 c;
    c.r = q->r; c.g = q->g; c.b = q->b; c.a = 0xFF;
    return c;
}
static inline void Tile2(PData* d, int b, const C4* q, f32 px, f32 py, f32 z) {
    C4 c0 = Mk(q);
    u16* t = *(u16**)fn_80006A0C(d->x10, b);
    f32 w = t[1];
    f32 h = t[0];
    fn_801BC88C(d->x10, b, c0, 0x11, 0, px, py, px + w, py + h, z, z, w, h);
}
void fn_801AF2A8(PData* d, f32 x, f32 y) {
    u32 h, m, s;
/*P*/
    const char* nm;
    int r;
    char* st1;
    u8* gb1;
    char* st2;
    u8* gb2;
/*E*/
    fn_8017FA84(d->t, &h, &m, &s);
    if (h > 0x63) { h = 0x63; m = 0x3B; s = 0x3B; }
    fn_801BCA5C(-1.0f);
    Tile2(d, 0, fn_800CD204(1), x, y, 0.0f);
    fn_801BCA5C(-1.0f);
    fn_801BCA94();
    if (fn_8024BC94()->lang == 0) {
    st1 = lbl_8036D68C;
    gb1 = lbl_803CAB38;
    fn_800CB3A8(1.0f, 0.0f, 96f + x, 48f + y, 1, 1, 0, fn_800D0864(st1 + 0x1CF));
    fn_800CB3A8(1.2f, 0.0f, 216f + x, 44f + y, 6, 1, 0, st1 + 0x1E5, *(s16*)(gb1 + 0x12));
    fn_800CB3A8(1.0f, 0.0f, 248f + x, 48f + y, 1, 1, 0, fn_800D0864(st1 + 0x1E8));
    fn_800CB3A8(1.0f, 0.0f, 94f + x, 80f + y, 1, 1, 0, st1 + 0x1F9, fn_800D0864(st1 + 0x216), h, m, s);
    fn_800CB3A8(1.0f, 0.0f, 94f + x, 112f + y, 1, 1, 0, fn_800D0864(st1 + 0x22B));
    fn_800CB3A8(1.2f, 0.0f, 182f + x, 108f + y, 6, 1, 0, st1 + 0x241, fn_800634D8(gb1));
    fn_800CB3A8(1.0f, 0.0f, 254f + x, 112f + y, 1, 1, 0, fn_800D0864(st1 + 0x244));
    fn_800CB3A8(1.2f, 0.0f, 342f + x, 108f + y, 6, 1, 0, st1 + 0x241, fn_80063568(gb1));
    fn_800CB3A8(1.0f, 0.0f, 94f + x, 144f + y, 1, 1, 0, fn_800D0864(st1 + 0x25B));
    fn_800CB3A8(1.2f, 0.0f, 182f + x, 140f + y, 6, 1, 0, st1 + 0x241, fn_80063620(gb1));
    fn_800CB3A8(1.2f, 0.0f, 294f + x, 184f + y, 25, 1, 0, fn_800D0864(st1 + 0x270));
    fn_800CB3A8(1.2f, 0.0f, 406f + x, 184f + y, 6, 1, 0, st1 + 0x241, fn_8006376C(gb1));
    } else {
    st2 = lbl_8036D68C;
    gb2 = lbl_803CAB38;
    fn_800CB3A8(1.0f, 0.0f, 96f + x, 48f + y, 1, 1, 0, fn_800D0864(st2 + 0x1CF));
    fn_800CB3A8(1.2f, 0.0f, 216f + x, 44f + y, 6, 1, 0, st2 + 0x1E5, *(s16*)(gb2 + 0x12));
    fn_800CB3A8(1.0f, 0.0f, 94f + x, 80f + y, 1, 1, 0, st2 + 0x287, fn_800D0864(st2 + 0x216), h, m, s);
    fn_800CB3A8(1.0f, 0.0f, 94f + x, 112f + y, 1, 1, 0, fn_800D0864(st2 + 0x22B));
    r = fn_800634D8(gb2); fn_800CB3A8(1.2f, 0.0f, 32.0f + (94f + x + fn_800CA3DC(fn_800D0864(st2 + 0x22B), -1, 1.0f)), 108f + y, 6, 1, 0, st2 + 0x241, r);
    fn_800CB3A8(1.0f, 0.0f, 254f + x, 112f + y, 1, 1, 0, fn_800D0864(st2 + 0x244));
    r = fn_80063568(gb2); fn_800CB3A8(1.2f, 0.0f, 32.0f + (254f + x + fn_800CA3DC(fn_800D0864(st2 + 0x244), -1, 1.0f)), 108f + y, 6, 1, 0, st2 + 0x241, r);
    fn_800CB3A8(1.0f, 0.0f, 94f + x, 144f + y, 1, 1, 0, fn_800D0864(st2 + 0x25B));
    r = fn_80063620(gb2); fn_800CB3A8(1.2f, 0.0f, 32.0f + (94f + x + fn_800CA3DC(fn_800D0864(st2 + 0x25B), -1, 1.0f)), 140f + y, 6, 1, 0, st2 + 0x241, r);
    fn_800CB3A8(1.2f, 0.0f, 294f + x, 184f + y, 25, 1, 0, fn_800D0864(st2 + 0x270));
    r = fn_8006376C(gb2); fn_800CB3A8(1.2f, 0.0f, 32.0f + (294f + x + fn_800CA3DC(fn_800D0864(st2 + 0x270), -1, 1.0f)), 184f + y, 6, 1, 0, st2 + 0x241, r);
    }
    fn_801BCA5C(-2.0f);
    fn_801BCA5C(-1.0f);
    fn_801BCA94();
    switch (lbl_803CAB38[0x10]) {
    case 0x5B: nm = fn_800D0864(lbl_8036D68C + 0x2B); break;
    case 0x5C: nm = fn_800D0864(lbl_8036D68C + 0x48); break;
    case 0x5D: nm = fn_800D0864(lbl_8036D68C + 0x65); break;
    case 0x5E: nm = fn_800D0864(lbl_8036D68C + 0x82); break;
    case 0x5F: nm = fn_800D0864(lbl_8036D68C + 0x9F); break;
    case 0x60: nm = fn_800D0864(lbl_8036D68C + 0xBC); break;
    }
    {
        s16 w = fn_800CA3DC(nm, -1, 1.0f);
        fn_800CB3A8(1.0f, 0.0f, 240.0f + x - w / 2, y - 12.0f, 1, 1, 0, nm);
    }
    fn_801BCA5C(5.0f);
}
}
