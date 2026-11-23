#include "game/rF_8017F400/types.h"
#pragma inline_depth(30)
#pragma inline_max_size(4000)
#pragma inline_max_total_size(20000)
extern "C" {
typedef struct SInfo { u8 pad[0x28]; s64 time; u8 x30[4]; u8 x34, x35, x36, x37; u8 pad38[8]; u32 x40; } SInfo;
typedef struct SEnt { s16 flags; s16 x2; s16 x4; s16 x6; s16 x8; s16 xa; u8 padc[0x14-0xc]; s16 x14; u8 pad16[0x1a-0x16]; s16 x1a; u8 pad1c[0x26-0x1c]; s16 x26; int x28, x2c, x30; s16 x34; s16 x36; char x38[0x40]; f32 x78; } SEnt;
static u8 s_c1[0x10]; static u8 s_b1[0x1070]; static u8 s_c2[0x10]; static u8 s_b2[0x1070];
extern s8 lbl_804CB938;
extern s8 lbl_804CB939;
extern int lbl_804CBFCC;
#if TARGET_PC
FE10_PROTO extern void *lbl_804CB778;
#else
extern char lbl_804CB778[8];
#endif
extern void* memset(void*, int, u32);
extern char* strcpy(char*, const char*);
extern void fn_80245C88(void*);
extern void fn_8019FAC8(void*, int);
extern void __register_global_object(void*, void*, void*);
#if TARGET_PC
extern FE10_PROTO void fn_8024B978(int, ptr32<const void>, p32arg);
extern FE10_PROTO void fn_8024BB8C(int, ptr32<const void>, p32arg);
#else
extern void fn_8024B978(int, void*, int);
extern void fn_8024BB8C(int, void*, int);
#endif
extern void fn_80246494(void);
extern int fn_80067FE8(int);
extern void* fn_80106A6C(void*, int);
extern int fn_80105B88(void*);
extern int fn_80105BBC(void*);
extern void fn_80105DC0(void*, int*, int*, int*);
extern void* fn_80105DB8(void*);
extern int fn_80105F94(void*);
extern char lbl_803889DC[], lbl_803889CC[], lbl_803889BC[], lbl_803889AC[], lbl_803889A0[], lbl_80388994[], lbl_80388988[], lbl_8038897C[], lbl_80388970[], lbl_80388964[], lbl_80388958[], lbl_8038894C[], lbl_80388940[], lbl_80388934[], lbl_80388928[];
#define OS_BUS_CLOCK (*(u32*)0x800000F8)
static inline SInfo* Sv1(int slot) {
    if (!lbl_804CB938) {
        fn_80245C88(s_b1);
        __register_global_object(s_b1, fn_8019FAC8, s_c1);
        lbl_804CB938 = 1;
    }
    fn_8024B978(slot, s_b1, 0);
    fn_80246494();
    if (lbl_804CBFCC == 0) return (SInfo*)(s_b1);
    return 0;
}
static inline SInfo* Sv2(int slot) {
    if (!lbl_804CB939) {
        fn_80245C88(s_b2);
        __register_global_object(s_b2, fn_8019FAC8, s_c2);
        lbl_804CB939 = 1;
    }
    fn_8024BB8C(slot, s_b2, 0);
    fn_80246494();
    if (lbl_804CBFCC == 0) return (SInfo*)(s_b2);
    return 0;
}
static inline void P2(SEnt* e) { void* p = fn_80106A6C(lbl_804CB778, e->x4);
        if (p == 0) return;
        if (fn_80105B88(p) == 0) return;
        e->flags |= 4;
        if (fn_80105BBC(p)) e->flags |= 8;
        e->x26 = *((u8*)p + 0x64);
        fn_80105DC0(p, &e->x28, &e->x2c, &e->x30);
        if (e->x28 >= 0x63) { e->x28 = 0x63; e->x2c = 0x3b; e->x30 = 0x3b; }
        e->x34 = *((u8*)p + 0x66);
        e->x36 = (u8)fn_80105F94(fn_80105DB8(p)) - 1;
        if (e->x36 < 0) e->x36 = 0;
        if (e->x26 == 0x20) e->flags |= 0x10; }
static inline void Fill(SEnt* e) {
    if (e->x2 == 0) {
        SInfo* s = Sv1(e->x4);
        SInfo* s2 = Sv2(e->x4);
        if (s == 0) return;
        e->flags |= 4;
        if (s2) { e->flags |= 8; s = s2; }
        e->x26 = s->x36;
        switch (s->x37) {
        case 3: e->flags |= 0x40; break;
        case 1: strcpy(e->x38, lbl_803889DC); break;
        case 2:
            if (s->x40 & 8) strcpy(e->x38, lbl_803889CC);
            else if (s->x40 & 0x10) strcpy(e->x38, lbl_803889BC);
            else if (s->x40 & 0x20) strcpy(e->x38, lbl_803889AC);
            else if (s->x40 & 0x40) {
                switch (e->x26) {
                case 0x32: strcpy(e->x38, lbl_803889A0); break;
                case 0x34: strcpy(e->x38, lbl_80388994); break;
                case 0x33:
                default: strcpy(e->x38, lbl_80388988); break;
                }
            } else strcpy(e->x38, lbl_8038897C);
            break;
        case 5: strcpy(e->x38, lbl_80388970); break;
        case 6: strcpy(e->x38, lbl_80388964); break;
        case 7: strcpy(e->x38, lbl_80388958); break;
        case 9:
            if (e->x26 != 0x37) { e->x26 = (u8)fn_80067FE8(e->x26); strcpy(e->x38, lbl_8038894C); }
            else e->x38[0] = 0;
            break;
        case 8:
            if (s->x40 & 8) strcpy(e->x38, lbl_80388940);
            else if (s->x40 & 0x10) strcpy(e->x38, lbl_80388934);
            else if (s->x40 & 0x20) strcpy(e->x38, lbl_80388928);
            else e->x38[0] = 0;
            break;
        default: e->x38[0] = 0; break;
        }
        {
        u32 sec = s->time / (OS_BUS_CLOCK / 4);
        e->x30 = sec % 60;
        e->x2c = (sec / 60) % 60;
        e->x28 = sec / 3600;
        if (e->x28 > 0x63) { e->x28 = 0x63; e->x2c = 0x3b; e->x30 = 0x3b; }
        }
        e->x34 = s->x35;
        e->x36 = s->x34 - 1;
        if (s->x40 & 4) e->flags |= 0x10;
    } else {
        P2(e);
    }
}

typedef struct TexH { u16 x0, x2; } TexH;
extern void* lbl_804CB92C;
extern void* fn_80006A0C(void*, int);
extern u8* fn_800CD204(int);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32, f32, f32, f32);
extern void fn_8007E7DC(int);
extern void fn_8007E7E8(int);
extern void fn_801BCA5C(f32);
extern void fn_801BCA94(void);
extern void fn_801BC88C(void* a, int b, GXColor c, int d, u32 fl, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, f32 f7, f32 f8);
extern f32 fn_8017F68C(int, f32, f32, f32, f32);
extern void fn_800800D4(int);
extern void fn_80080308(void);
extern void fn_80080330(f32, f32);
extern void fn_800804D4(int, int, int, int);
extern void fn_80080508(GXColor);
extern void fn_80080A94(f32);
extern void fn_80080C24(const char*);
extern const char* fn_800D0864(const char*);
extern int fn_800CA3DC(const char*, int, f32);
extern void fn_800CB278(s16, s16, int, const char*, ...);
extern int fn_80290DDC(char*, const char*, ...);
extern void* fn_8010B094(int);
extern const char* fn_8009285C(void*);
extern const char* fn_80092904(void*);
extern const char* fn_80092958(void*);
extern char lbl_804CA7F8[8], lbl_804CA7F0[8], lbl_804CA7E8[8], lbl_804CA7E0[8], lbl_804CA7D8[8];
extern char lbl_8038891C[], lbl_80388910[], lbl_803888FC[], lbl_803888EC[], lbl_803888D8[], lbl_803888C4[], lbl_803888B0[], lbl_8038889C[], lbl_80388888[];
static inline void Refresh(SEnt* e) {
    e->flags &= ~4;
    e->flags &= ~8;
    e->flags &= ~0x10;
    e->flags &= ~0x40;
    Fill(e);
}
static inline GXColor mk(const u8* p, u8 a) { GXColor c; c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = a; return c; }
static inline void Sprite(int col, u8 alpha, int tile, u32 fl, f32 x, f32 y, f32 w, f32 h) {
    u8* p = fn_800CD204(col);
    GXColor c;
    TexH** t;
    c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = alpha;
    t = (TexH**)fn_80006A0C(lbl_804CB92C, tile);
    {
    f32 tw = (*t)->x2, th = (*t)->x0;
    fn_801BC88C(lbl_804CB92C, tile, c, 0x11, fl, x, y, x + w, y + h, 0.0f, 0.0f, tw, th);
    }
}
static inline void A0(SEnt* e, int ox, int oy) {
    s16 y, u, v, x;
    s16 fr;
    e->x78 += 0.35f;
    y = e->xa + oy;
    x = e->x8 + ox;
    if (e->x78 >= 32.0f) e->x78 -= 32.0f;
    fr = (int)e->x78;
    u = (fr % 16) * 32;
    v = (fr / 16) * 32;
    fn_801BC88C(lbl_804CB92C, 0x10, *(GXColor*)fn_800CD204(1), 0x11, 0, x, y, x + 0x20, y + 0x20, u, v, u + 0x20, v + 0x20);
}
static inline void B0(SEnt* e, int ox, int oy) {
    s16 y2, u2, v2, x2;
    s16 fr;
    e->x78 += 0.35f;
    y2 = e->xa + oy;
    x2 = e->x8 + ox;
    if (e->x78 >= 32.0f) e->x78 -= 32.0f;
    fr = (int)e->x78;
    u2 = (fr % 16) * 32;
    v2 = (fr / 16) * 32;
    fn_801BC88C(lbl_804CB92C, 0x10, *(GXColor*)fn_800CD204(1), 0x11, 0, x2, y2, x2 + 0x20, y2 + 0x20, u2, v2, u2 + 0x20, v2 + 0x20);
}
#define WA(N,B) static inline void N(SEnt* e, int ox, int oy) { B(e, ox, oy); }
WA(B1,B0) WA(B2,B1) WA(B3,B2) WA(B4,B3) WA(B5,B4) WA(B6,B5) WA(B7,B6) WA(B8,B7) WA(B9,B8) WA(Anim2,B9)
WA(A1,A0) WA(A2,A1) WA(A3,A2) WA(A4,A3) WA(A5,A4) WA(A6,A5) WA(A7,A6) WA(A8,A7) WA(A9,A8) WA(Anim,A9)
#define TextAt(S, X, Y) fn_800CB278(X, Y, 1, S)
static inline void TextP(SEnt* e, const char* const& s, int ox, int oy) {
    if (s) fn_800CB278(e->x8 + ox, e->xa + oy, 1, fn_800D0864(s));
}
#define WR(N,B) static inline void N(u8 alpha, int tile, f32 x, f32 y, f32 w, f32 h) { B(1, alpha, tile, 0, x, y, w, h); }
static inline void S0(int col, u8 alpha, int tile, u32 fl, f32 x, f32 y, f32 w, f32 h) { Sprite(col, alpha, tile, fl, x, y, w, h); }
#define WW(N,B) static inline void N(int col, u8 alpha, int tile, u32 fl, f32 x, f32 y, f32 w, f32 h) { B(col, alpha, tile, fl, x, y, w, h); }
WW(S1,S0) WW(S2,S1) WW(S3,S2) WW(S4,S3) WW(S5,S4) WW(S6,S5) WW(S7,S6) WW(S8,S7)
static inline void Tile(int col, u8 alpha, int tile, u32 fl, f32 x, f32 y) {
    TexH** t = (TexH**)fn_80006A0C(lbl_804CB92C, tile);
    f32 w = (*t)->x2;
    f32 h = (*t)->x0;
    S8(col, alpha, tile, fl, x, y, w, h);
}
static inline void Fade(SEnt* e, int a) {
        fn_801BCA5C(-2.0f);
        { f32 x, y; y = e->xa; x = e->x8; S7(1, a, 0x11, 0, x, y, 8.0f, 56.0f); }
        { f32 x, y; y = e->xa; x = e->x8 + 8; S6(1, a, 0x12, 0, x, y, 503.0f, 56.0f); }
        { f32 x, y; y = e->xa; x = e->x8 + 0x1ff; S5(1, a, 0x13, 0, x, y, 8.0f, 56.0f); }
        fn_801BCA5C(2.0f);
}
static inline void Frame(SEnt* e) {
    int tile;
    tile = 4;
    if (e->flags & 4) {
        if (e->x2 == 0) {
            switch (e->x34) {
            case 0: tile = 4; break;
            case 1: tile = 5; break;
            case 2: tile = 6; break;
            default: tile = 4; break;
            }
        } else if (e->x2 == 1) {
            switch (e->x34) {
            case 3: tile = 4; break;
            case 0: tile = 5; break;
            case 1: tile = 6; break;
            case 2:
            default: tile = 4; break;
            }
        }
    } else {
        tile = 7;
    }
    { f32 x, y; y = e->xa + 3; x = e->x8 + 0xc; S4(1, 0xFF, tile, 0, x, y, 496.0f, 48.0f); }
    fn_801BCA5C(-1.0f);
    { f32 x, y; y = e->xa; x = e->x8; S3(1, 0xFF, 9, 0, x, y, 16.0f, 56.0f); }
    { f32 x, y; y = e->xa; x = e->x8 + 0x1fb; S2(1, 0xFF, 0xa, 0, x, y, 16.0f, 56.0f); }
    { f32 x, y; y = e->xa; x = e->x8 + 0xc; S1(1, 0xFF, 0xb, 0, x, y, 495.0f, 8.0f); }
    { f32 x, y; y = e->xa + 0x30; x = e->x8 + 0xc; S0(1, 0xFF, 0xc, 0, x, y, 495.0f, 8.0f); }
}
void fn_80198CC0(SEnt* e) {
    /*P*/
    int a;
    /*E*/
    char buf[0x40];
    if (!(e->flags & 1)) return;
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 120.0f, 1.0f);
    fn_8007E164();
    fn_8007E154();
    fn_8007E7DC((u8)e->x1a);
    if (e->flags & 2) fn_8007E7E8(0x80);
    else if (e->x2 == 0) fn_8007E7E8(0x40);
    else if (e->x2 == 1) {
        if (e->flags & 0x10) fn_8007E7E8(0x40);
        else fn_8007E7E8(0x14);
    }
    fn_8007E164();
    fn_801BCA5C(-1.0f);
    Frame(e);
    fn_801BCA5C(1.0f);
    if (e->flags & 0x20) {
        if (e->x6 >= 0x23) a = fn_8017F68C(0, 172.0f, 0.0f, e->x6 - 0x23, 35.0f);
        else a = fn_8017F68C(0, 0.0f, 172.0f, e->x6, 35.0f);
        Fade(e, a);
        e->x6--;
        if (e->x6 == 0x23) Refresh(e);
        if (e->x6 <= 0) e->flags &= ~0x20;
    }
    if (e->x2 == 0) {
        fn_801BCA5C(-2.0f);
        if (e->flags & 4) {
            Tile(1, 0xFF, 0xd, 0, e->x8 + 0x54, e->xa + 6);
            Tile(1, 0xFF, 0xe, 0, e->x8 + 0x6c, e->xa + 0x1e);
            Tile(1, 0xFF, 0xf, 0, e->x8 + 0x128, e->xa + 0x1e);
            if (e->flags & 8) {
                const char* s;
                Anim(e, 0x188, 0x14);
                fn_801BCA94();
                fn_800800D4(5);
                if (e->x34 == 2) s = fn_800D0864(lbl_804CA7F8);
                else s = fn_800D0864(lbl_8038891C);
                {
                int w = fn_800CA3DC(s, -1, 1.0f);
                f32 fx = e->x8 + 0x1cd - w / 2; fn_80080330(fx, e->xa + 0x18);
                }
                fn_800804D4(0xa4, 0x39, 0x39, 0xff);
                fn_80080C24(fn_800D0864(s));
                fn_80080308();
            }
            fn_801BCA94();
            {
            void* p = fn_8010B094(e->x26);
            if (!(e->flags & 0x10)) {
                fn_800800D4(5);
                fn_80080330(e->x8 + 0x14, e->xa + 4);
                fn_800804D4(0xd8, 0xb8, 0x80, 0xff);
                fn_80080C24(fn_8009285C(p));
                fn_80080308();
                TextAt(fn_80092904(p), e->x8 + 0x6c, e->xa + 4);
                if (!(e->flags & 0x40)) TextAt(fn_80092958(p), e->x8 + 0xd4, e->xa + 4);
            } else {
                TextAt(fn_800D0864(lbl_80388910), e->x8 + 0xcc, e->xa + 4);
            }
            }
            fn_800800D4(5);
            fn_80080330(e->x8 + 0x1a7, e->xa + 4);
            fn_80080A94(0.8f);
            fn_800804D4(0xff, 0xbc, 0x75, 0xff);
            fn_80080C24(fn_800D0864(e->x38));
            fn_80080308();
            fn_80290DDC(buf, lbl_803888FC, e->x28, e->x2c, e->x30);
            TextAt(fn_800D0864(buf), e->x8 + 0xa0, e->xa + 0x18);
            fn_80290DDC(buf, lbl_804CA7F0, e->x36);
            TextAt(fn_800D0864(buf), e->x8 + 0x16b, e->xa + 0x18);
        }
        fn_801BCA5C(2.0f);
    } else if (e->x2 == 1) {
        fn_801BCA5C(-2.0f);
        if (e->flags & 4) {
            Tile(1, 0xFF, 0xe, 0, e->x8 + 0x148, e->xa + 0xa);
            Tile(1, 0xFF, 0xf, 0, e->x8 + 0x148, e->xa + 0x1e);
            if (e->flags & 8) {
                Anim2(e, 0x1a7, 0x16);
                fn_801BCA94();
                fn_800800D4(5);
                {
                int w = fn_800CA3DC(fn_800D0864(lbl_804CA7E8), -1, 1.0f);
                f32 fx = e->x8 + 0x1db - w / 2; fn_80080330(fx, e->xa + 0x18);
                }
                fn_800804D4(0xa4, 0x39, 0x39, 0xff);
                fn_80080C24(fn_800D0864(lbl_804CA7E0));
                fn_80080308();
            }
            fn_801BCA94();
            fn_80290DDC(buf, lbl_803888EC, e->x26);
            TextP(e, buf, 0xf, 4);
            fn_80290DDC(buf, lbl_803888D8, e->x26);
            TextP(e, buf, 0x6a, 4);
            fn_800800D4(5);
            fn_80080330(e->x8 + 0x6a, e->xa + 0x1c);
            fn_80080A94(0.8f);
            switch (e->x34) {
            case 3:
                fn_80080508(*(GXColor*)fn_800CD204(4));
                fn_80080C24(fn_800D0864(lbl_803888C4));
                break;
            case 0:
                fn_80080508(*(GXColor*)fn_800CD204(7));
                fn_80080C24(fn_800D0864(lbl_803888B0));
                break;
            case 1:
                fn_80080508(*(GXColor*)fn_800CD204(3));
                fn_80080C24(fn_800D0864(lbl_8038889C));
                break;
            case 2:
            default:
                break;
            }
            fn_80080308();
            fn_80290DDC(buf, lbl_80388888, e->x28, e->x2c, e->x30);
            TextAt(fn_800D0864(buf), e->x8 + 0x18b, e->xa + 4);
            fn_80290DDC(buf, lbl_804CA7D8, e->x36);
            TextAt(fn_800D0864(buf), e->x8 + 0x18b, e->xa + 0x18);
        }
        fn_801BCA5C(2.0f);
    }
    fn_801BCA5C(1.0f);
    fn_8007E154();
    fn_8007E7DC(0xff);
    fn_8007E7E8(0x80);
    fn_8007E164();
}
}
