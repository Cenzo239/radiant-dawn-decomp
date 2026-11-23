/* Title-card banner draw, fn_8014CBC8. */
#include "game/rM_8014C9F8/types.h"
struct Banner : Proc {
    char str[0x20];  /* 0x30 */
    u32 id;          /* 0x50 */
    s16 x;           /* 0x54 */
    s16 y;           /* 0x56 */
    u8 fadeFrom;     /* 0x58 */
    u8 fadeTo;       /* 0x59 */
    u8 fadeCur;      /* 0x5A */
    u8 fadeLen;      /* 0x5B */
    u8 alpha;        /* 0x5C */
    u8 width;        /* 0x5D */
};
struct Color { u8 r, g, b, a; };
struct Tx { u8 obj[0x20]; u16 w; u16 h; };
extern "C" {
extern u32 lbl_804CB700;
extern f32 fn_8017F68C(int, f32, f32, f32, f32);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32, f32, f32, f32);
extern void fn_8007E7DC(u8);
extern void* fn_801485FC(void);
extern void fn_80006A64(void*, void*, int);
extern u16 fn_80305DF8(void*);
extern u16 fn_80305E0C(void*);
extern void fn_8007E174(void*, int);
extern int fn_801D09F0(void);
extern void fn_800800D4(int);
extern void fn_80080388(f32, f32, f32, f32);
extern void fn_80080308(void);
extern void fn_8007E720(f32);
extern void fn_80080330(f32, f32);
extern void fn_80080508(Color);
extern void* fn_800CD204(int);
extern void fn_80080B00(int, void*, f32);
extern void fn_80080A94(f32);
extern void fn_80080C24(const char*);
static const Color kc = {0, 0, 0, 0xB4};

#pragma inline_max_size(4000)
static inline void F_i(Banner* b) {
    
    Tx t;
    f32 s;
    s16 x;

    if (lbl_804CB700 & 3) {
        return;
    }
    x = b->x;
    if (x >= 1000) {
        x -= 1000;
    }
    if (x > 0x1F8) {
        x = 0x1F8;
    }
    if (x < 0x68) {
        x = 0x68;
    }
    b->alpha = fn_8017F68C(0, b->fadeFrom, b->fadeTo, b->fadeCur, b->fadeLen);
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 70.0f, 1.0f);
    fn_8007E7DC(b->alpha);
    fn_8007E164();
    fn_80006A64(fn_801485FC(), &t, 1);
    t.w = fn_80305DF8(&t);
    t.h = fn_80305E0C(&t);
    fn_8007E154();
    fn_8007E174(&t, 0x10);
    fn_8007E164();
    if (fn_801D09F0()) {
        t.w = 608.0f * t.w / 796.0f;
    }
    fn_800800D4(1);
    fn_80080388(x - (int)((u32)t.w >> 1), b->y - 0xC, t.w, t.h);
    fn_80080308();
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 70.0f, 1.0f);
    fn_8007E174(0, 0x13);
    fn_8007E720(-1.0f);
    fn_8007E164();
    s = 0.85f;
    fn_800800D4(5);
    fn_80080330((int)((f32)x - (f32)b->width * s / 2.0f), b->y - 7);
    fn_80080508(kc);
    fn_80080B00(1, fn_800CD204(0x29), 1.0f);
    fn_80080A94(s);
    fn_80080C24(b->str);
    fn_80080308();
    fn_8007E154();
    fn_8007E7DC(0xFF);
    fn_8007E164();
}
void fn_8014CBC8(Banner* b) { F_i(b); }
}
