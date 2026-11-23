/* Sprite drawing from the window texture sets, 8006E098..80072ACC (part). */
#include "game/rO_80065D64/types.h"
#pragma auto_inline off

struct Tex {
    u32 d[8];  /* 0 */
    u16 w;     /* 20 */
    u16 h;     /* 22 */
};
struct Color { u8 r, g, b, a; };

extern "C" {
extern void* lbl_804CB580;
extern void* lbl_804CB58C;
extern void fn_80006A64(void*, Tex*, u16);
extern u16 fn_80305DF8(Tex*);
extern u16 fn_80305E0C(Tex*);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E174(Tex*, int);
extern void fn_8007E720(f32);
extern void fn_800800D4(int);
extern void fn_80080348(f32, f32, f32, f32);
extern void fn_80080368(f32, f32, f32, f32);
extern void fn_80080388(f32, f32, f32, f32);
extern Color* fn_800CD204(u8);
extern void fn_80080508(Color*);
extern void fn_800804F4(u8);
extern void fn_80080578(int);
extern void fn_80080690(void);
extern void fn_800806E0(void);
extern void fn_80080308(void);
extern void fn_800804B4(void);
extern int fn_801D09F0(void);
extern void fn_8006E610(int, int, int, int, int, int);
extern void fn_803080DC(int, int, int, int);

static inline void TexLoad(void* set, Tex* t, u16 id) {
    fn_80006A64(set, t, id);
    t->w = fn_80305DF8(t);
    t->h = fn_80305E0C(t);
}

void fn_8006E098(Tex* t, int x, int y, int w, int h, int u0, int v0, int u1, int v1, int color, u8 alpha, u16 id, int flags) {
    TexLoad(lbl_804CB58C, t, id);
    fn_8007E154();
    fn_8007E174(t, 0x11);
    fn_8007E164();
    if (w == -1) {
        w = t->w;
    }
    if (h == -1) {
        h = t->h;
    }
    if (flags & 1) {
        int s = u0;
        u0 = u1;
        u1 = s;
    }
    if (flags & 2) {
        int s = v0;
        v0 = v1;
        v1 = s;
    }
    fn_800800D4(2);
    fn_80080348(x, y, u0, v0);
    fn_80080368(x + w, y + h, u1, v1);
    Color c = *fn_800CD204(color);
    fn_80080508(&c);
    fn_800804F4(alpha);
    fn_80080578(0);
    if (flags & 4) {
        fn_80080690();
    }
    if (flags & 8) {
        fn_800806E0();
    }
    fn_80080308();
}

void fn_800715B0(int x, int y) {
    Tex t;
    TexLoad(lbl_804CB580, &t, 0x13);
    fn_8007E154();
    fn_8007E174(&t, 0x10);
    fn_8007E164();
    f32 ox;
    f32 sh;
    f32 sw;
    sw = t.w;
    sh = t.h;
    ox = 0.0f;
    if (fn_801D09F0()) {
        sw *= 0.7638191f;
        ox = (f32)t.w - sw;
    }
    fn_800800D4(1);
    fn_80080388((f32)(x - 0x20) + ox, y + 0xC, sw, sh);
    fn_80080308();
}

void fn_800716F8(int x, int y, int f) {
    Tex t;
    TexLoad(lbl_804CB58C, &t, 0x39);
    fn_8007E154();
    fn_8007E174(&t, 0x10);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080388(x, y, t.w, t.h);
    if (f == 0) {
        fn_800804B4();
    }
    fn_80080308();
}

void fn_800717E4(int x, int y, int f) {
    Tex t;
    TexLoad(lbl_804CB58C, &t, 0x3A);
    fn_8007E154();
    fn_8007E174(&t, 0x10);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080388(x, y, t.w, t.h);
    if (f == 0) {
        fn_800804B4();
    }
    fn_80080308();
}

void fn_800718D0(int a, int b, int c, int d, int e) {
    switch (e) {
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
        e = 0;
    }
    fn_8006E610(a, b, c, d, e, 0);
}

void fn_80071C30(int a, int b) {
    fn_803080DC(b - 0x5D, 0, 0xBA, 0x1E0);
}

u16 fn_8007265C(int x, int y) {
    Tex copy;
    Tex ret;
    Tex t1;
    Tex t0;
    int h;
    int w;
    fn_8007E154();
    fn_8007E720(1.0f);
    fn_8007E164();
    TexLoad(lbl_804CB58C, &t0, 0x18);
    h = t0.h;
    w = t0.w;
    TexLoad(lbl_804CB58C, &t1, 0x18);
    fn_8007E154();
    fn_8007E174(&t1, 0x11);
    fn_8007E164();
    if (w == -1) {
        w = t1.w;
    }
    if (h == -1) {
        h = t1.h;
    }
    fn_8006E098(&ret, x, y, w, h, 0, 0, t1.w, t1.h, 1, 0xFF, 0x18, 0);
    copy = ret;
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E164();
    return copy.w;
}

u16 fn_800727E4(int x, int y, int w, int h) {
    Tex copy;
    Tex ret;
    Tex t;
    fn_8007E154();
    fn_8007E720(1.0f);
    fn_8007E164();
    TexLoad(lbl_804CB58C, &t, 0x18);
    fn_8007E154();
    fn_8007E174(&t, 0x11);
    fn_8007E164();
    if (w == -1) {
        w = t.w;
    }
    if (h == -1) {
        h = t.h;
    }
    fn_8006E098(&ret, x, y, w, h, 0, 0, t.w, t.h, 1, 0xFF, 0x18, 0);
    copy = ret;
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E164();
    return copy.w;
}
u16 fn_80072944(int x, int y) {
    Tex copy;
    Tex ret;
    Tex t1;
    Tex t0;
    int h;
    int w;
    fn_8007E154();
    fn_8007E720(1.0f);
    fn_8007E164();
    TexLoad(lbl_804CB58C, &t0, 0x19);
    h = t0.h;
    w = t0.w;
    TexLoad(lbl_804CB58C, &t1, 0x19);
    fn_8007E154();
    fn_8007E174(&t1, 0x11);
    fn_8007E164();
    if (w == -1) {
        w = t1.w;
    }
    if (h == -1) {
        h = t1.h;
    }
    fn_8006E098(&ret, x, y, w, h, 0, 0, t1.w, t1.h, 1, 0xFF, 0x19, 0);
    copy = ret;
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E164();
    return copy.w;
}


extern void fn_8006FB94(int, f32, f32, f32, f32);
extern void fn_8006FED4(f32, f32, f32, f32);
extern void fn_80070688(f32, f32, f32, f32);

void fn_8006FE30(f32 a, f32 b, f32 c, f32 d, int color) {
    fn_8006FB94(color, a, b, c, d);
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E164();
    fn_8006FED4(a, b, c, d);
    fn_8007E154();
    fn_8007E720(1.0f);
    fn_8007E164();
}

void fn_800705E4(f32 a, f32 b, f32 c, f32 d, int color) {
    fn_8006FB94(color, a, b, c, d);
    fn_8007E154();
    fn_8007E720(-1.0f);
    fn_8007E164();
    fn_80070688(a, b, c, d);
    fn_8007E154();
    fn_8007E720(1.0f);
    fn_8007E164();
}
}
