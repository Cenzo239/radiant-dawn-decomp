/* near miss (round 13): fn_8019FFE4, right shape and stack, registers almost right; FP scheduling in frame draws 4..13 is what remains, plus r25..r28 ranks in the item block. */
/* fn_8019FFE4: help window draw, with the item stat block. StringPool is scaffolding for the file's pool. */
#include "game/rF_8017F400/types.h"
#pragma pool_strings on
extern "C" {
void StringPool(const char** p) {
    p[0] = "%s";
    p[1] = "%d";
    p[2] = "MP_WGT";
    p[3] = "MP_RNG";
    p[4] = "IID_GODDESSROD";
    p[5] = "MP_RNG_ALL";
    p[6] = " %d";
    p[7] = "%d\x81|%d";
    p[8] = "%d\x81|%s";
    p[9] = "MP_MPOW_HF";
    p[10] = "MP_POW";
    p[11] = "MP_HIT";
    p[12] = "MP_CRIT";
    p[13] = "MD_IMPOSSIBLE";
}
typedef struct TexH { u16 x0, x2; } TexH;
typedef struct TwoC { GXColor a, b; } TwoC;
typedef struct IData { const char* x0; u8 pad4[0x12-4]; u8 x12; u8 pad13[0x18-0x13]; s16 x18; } IData;
typedef struct Slot { IData* d; } Slot;
typedef struct IInfo { u32 x0, x4; } IInfo;
typedef struct HWin {
    u32 flags; char lines[3][0x40]; u8 pad[0xc4-0xc4];
    void* arch; Slot* item; int xcc; u8 padd0[0xd8-0xd0]; s16 xd8; u8 padda[0xdc-0xda];
    f32 xdc, xe0, xe4, xe8, xec, xf0, xf4, xf8, xfc, x100, x104, x108, x10c, x110, x114, x118, x11c, x120;
} HWin;
extern void fn_80083B78(void*);
extern f32 fn_8017F68C(int, f32, f32, f32, f32);
extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E7DC(int);
extern void fn_8007E4E4(f32, f32, f32, f32);
extern void fn_8007E5C0(f32, f32, f32, f32, f32, f32, f32, f32);
extern void fn_8007E174(int, int);
extern void fn_8007E74C(void*, int);
extern void fn_8007E7B4(void);
extern void fn_800712E8(int, int, int);
extern u8* fn_800CD204(int);
extern void* fn_80006A0C(void*, int);
extern void fn_801BC88C(void* a, int b, GXColor c, int d, u32 fl, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, f32 f7, f32 f8);
extern void fn_8019FF0C(void);
extern IInfo* fn_801116B8(Slot*);
extern const char* fn_8010FECC(int, int);
extern char* fn_800D0864(const char*);
extern void fn_800800D4(int);
extern void fn_80080330(f32, f32);
extern void fn_80080508(GXColor);
extern void fn_80080BB4(int, const GXColor*, f32);
extern void fn_80080C24(const char*);
extern void fn_80080308(void);
extern int fn_800CA3DC(const char*, int, f32);
extern void fn_800CB3A8(f32 a, f32 b, s16 x, s16 y, u8 c, int d, int e, const char* fmt, ...);
extern const char* fn_801113DC(int);
extern u8 fn_80110EB0(Slot*);
extern u8 fn_80110DA8(Slot*);
extern u8 fn_80110E00(Slot*);
extern u8 fn_80110E58(Slot*);
extern int fn_80290DDC(char*, const char*, ...);
extern int fn_80291188(const char*, const char*);
extern char* strcpy(char*, const char*);
extern u8 fn_801107B8(IData*, int);
extern u8 fn_801108F0(IData*);
extern u8 fn_801107A0(IData*, int);
extern u8 fn_801108D8(IData*);
static inline u8 Kind(IData* d) { return d ? d->x12 : 0x13; }
static inline void Label(char* s, s16 x, s16 y) {
    GXColor a = { 0xff, 0xff, 0xff, 0xff };
    GXColor b = { 0x24, 0x24, 0x24, 0xff };
    fn_800800D4(5);
    fn_80080330(x, y);
    fn_80080508(a);
    fn_80080BB4(1, &b, 1.0f);
    fn_80080C24(s);
    fn_80080308();
}
#define TXT(X, Y, ...) fn_800CB3A8(1.0f, 0.0f, X, Y, 2, 0, 0, __VA_ARGS__)
static inline void Lines3(HWin* e, int x, s16 y) {
    int i;
    for (i = 0; i < 3; i++) {
        if (e->lines[i]) TXT(x, y + i * 0x18, e->lines[i]);
    }
}
#define DRAWHEAD(TILE) GXColor t = col; TexH** p = (TexH**)fn_80006A0C(e->arch, TILE); t.a = 0xe6; f32 tw = (*p)->x2, th = (*p)->x0;
#define DRAW(e, col, TILE, X, Y, W, H) { DRAWHEAD(TILE) fn_801BC88C(e->arch, TILE, t, 0x11, 0, X, Y, (X) + (W), (Y) + (H), 0.0f, 0.0f, tw, th); }
void fn_8019FFE4(HWin* e, void* proc) {
    /*P*/
    s16 w2;
    char* s2;
    const char* key2;
    char* s4;
    char* s5;
    char* s6;
    char* s7;
    char* s8;
    char* s9;
    const char* key1;
    char* s3;
    int tw1;
    int tw2;
    char* s1;
    s16 w3;
    s16 w4;
    int xc;
    u32 mn;
    IData* d0;
    s16 xx;
    int x;
    int y;
    int tile;
    f32 w;
    f32 h;
    f32 sx;
    f32 sy;
/*E*/
    GXColor col;
    char buf[0x18];
    if ((e->flags & 1) && e->xcc <= 0) {
        fn_80083B78(proc);
        return;
    }
    if (e->xcc > 0) {
        int d, t;
        e->xcc--;
        d = 8;
        t = 8 - e->xcc;
        e->xdc = fn_8017F68C(4, e->xe4, e->xec, t, d);
        e->xe0 = fn_8017F68C(4, e->xe8, e->xf0, t, d);
        e->xf4 = fn_8017F68C(4, e->xfc, e->x104, t, d);
        e->xf8 = fn_8017F68C(4, e->x100, e->x108, t, d);
        e->x10c = fn_8017F68C(4, e->x114, e->x11c, t, d);
        e->x110 = fn_8017F68C(4, e->x118, e->x120, t, d);
    }
    fn_8007E154();
    fn_8007E7DC(0xff);
    fn_8007E164();
    if (!(e->flags & 1) && !(e->flags & 2)) {
        fn_8007E154();
        fn_8007E4E4(0.0f, 0.0f, 3.0f, 1.0f);
        fn_8007E164();
        fn_800712E8(36.0f + e->xdc - 8.0f, 3.0f + e->xe0, 1);
    }
    sx = 1.0f;
    sy = sx;
    w = e->x10c;
    h = e->x110;
    switch (e->xd8) {
    case 1: { GXColor t2 = { 0xe9, 0xb7, 0x99, 0xff }; col = t2; break; }
    default: col = *(GXColor*)fn_800CD204(1); break;
    }
    if (e->x10c < 112.0f) { sx = e->x10c / 112.0f; w = 112.0f; }
    if (e->x110 < 57.0f) { sy = e->x110 / 57.0f; h = 57.0f; }
    fn_8007E154();
    fn_8007E5C0(e->xf4, e->xf8, 2.0f, 0.0f, 0.0f, sx, sy, 0.0f);
    fn_8007E164();
    tile = 0;
    if (e->xd8 == 1) tile = 9;
    DRAW(e, col, tile, 0.0f, 0.0f, 72.0f, 24.0f);
    DRAW(e, col, 1, 72.0f, 0.0f, w - 72.0f - 11.0f, 16.0f);
    DRAW(e, col, 2, w - 11.0f, 0.0f, 16.0f, 16.0f);
    { DRAWHEAD(4) f32 y_ = 11.0f; fn_801BC88C(e->arch, 4, t, 0x11, 0, 72.0f, y_, (72.0f) + (w - 72.0f - 11.0f), (y_) + (13.0f), 0.0f, 0.0f, tw, th); }
    DRAW(e, col, 5, w - 11.0f, 11.0f, 16.0f, 13.0f);
    DRAW(e, col, 3, 0.0f, 24.0f, 16.0f, h - 24.0f - 32.0f);
    { DRAWHEAD(4) f32 h_ = h - 24.0f - 32.0f; f32 x_ = 11.0f; fn_801BC88C(e->arch, 4, t, 0x11, 0, x_, 24.0f, (x_) + (w - 11.0f - 11.0f), (24.0f) + (h_), 0.0f, 0.0f, tw, th); }
    DRAW(e, col, 5, w - 11.0f, 24.0f, 16.0f, h - 24.0f - 32.0f);
    DRAW(e, col, 3, 0.0f, h - 32.0f, 16.0f, 21.0f);
    DRAW(e, col, 4, 11.0f, h - 32.0f, w - 11.0f - 40.0f, 21.0f);
    DRAW(e, col, 6, 0.0f, h - 11.0f, 16.0f, 16.0f);
    { DRAWHEAD(7) f32 x2_ = (11.0f) + (w - 11.0f - 40.0f); f32 y2_ = (h - 11.0f) + (16.0f); fn_801BC88C(e->arch, 7, t, 0x11, 0, 11.0f, h - 11.0f, x2_, y2_, 0.0f, 0.0f, tw, th); }
    tile = 8;
    if (e->xd8 == 1) tile = 0xa;
    DRAW(e, col, tile, w - 40.0f, h - 32.0f, 40.0f, 32.0f);
    if (e->flags & 1) return;
    x = 15.0f + e->xf4;
    y = 20.0f + e->xf8;
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 1.0f, 1.0f);
    fn_8007E174(0, 0x13);
    fn_8007E74C((void*)fn_8019FF0C, 0);
    fn_8007E164();
    if (e->item) {
        if (Kind(e->item->d) == 0xb && (fn_801116B8(e->item)->x4 & 0x10)) {
            key1 = fn_8010FECC(Kind(e->item->d), 0);
            s1 = fn_800D0864(key1); Label(s1, x, y);
            tw1 = fn_800CA3DC(fn_800D0864(key1), -1, 1.0f);
            xx = tw1 + x + 6;
            {
            IData* d = e->item->d;
            TXT(xx, y, "%s", fn_801113DC(d ? d->x18 : 0));
            }
            xx += 0x1e;
            fn_80290DDC(buf, "%d", fn_80110EB0(e->item));
            {
            w2 = fn_800CA3DC(buf, -1, 1.0f);
            s2 = fn_800D0864("MP_WGT"); Label(s2, xx, y);
            xx += 0x37;
            TXT(xx - w2 / 2, y, "%d", fn_80110EB0(e->item));
            }
            xx += 0x19;
            s3 = fn_800D0864("MP_RNG"); Label(s3, xx, y);
            xx += 0x46;
            {
            IData* d = e->item->d;
            if (fn_80291188(d ? d->x0 : 0, "IID_GODDESSROD") == 0) {
                strcpy(buf, fn_800D0864("MP_RNG_ALL"));
            } else {
                mn = d ? fn_801107B8(d, 0) : 0;
                if (mn == fn_801108F0(e->item->d)) {
                    d = e->item->d;
                    fn_80290DDC(buf, " %d", d ? fn_801107B8(d, 0) : 0);
                } else {
                    if (fn_801108F0(e->item->d) != 0xff) {
                        IData* d2 = e->item->d;
                        u32 m2 = d2 ? fn_801107B8(d2, 0) : 0;
                        fn_80290DDC(buf, "%d\x81|%d", m2, fn_801108F0(d2));
                    } else {
                        IData* d2 = e->item->d;
                        u32 m2 = d2 ? fn_801107B8(d2, 0) : 0;
                        fn_80290DDC(buf, "%d\x81|%s", m2, fn_800D0864("MP_MPOW_HF"));
                    }
                    xx += 0xc;
                }
            }
            }
            {
            w3 = fn_800CA3DC(buf, -1, 1.0f);
            TXT(xx - w3 / 2, y, buf);
            }
            {
            int i;
            for (i = 0; i < 2; i++) {
                if (e->lines[i]) TXT(x, i * 0x18 + y + 0x18, e->lines[i]);
            }
            }
        } else {
            d0 = e->item->d;
            if (Kind(d0) == 0xf || Kind(d0) == 0xe) {
                Lines3(e, x, y);
            } else {
                xc = x;
                if (Kind(d0) != 5 && Kind(d0) != 0xd) {
                    key2 = fn_8010FECC(Kind(d0), 0);
                    s4 = fn_800D0864(key2); Label(s4, x, y);
                    tw2 = fn_800CA3DC(fn_800D0864(key2), -1, 1.0f);
                    xc = (s16)(tw2 + x + 6);
                    {
                    IData* d2 = e->item->d;
                    TXT(xc, y, "%s", fn_801113DC(d2 ? d2->x18 : 0));
                    }
                    xc = (s16)(xc + 0x1e);
                }
                fn_80290DDC(buf, "%d", fn_80110DA8(e->item));
                w4 = fn_800CA3DC(buf, -1, 1.0f);
                s5 = fn_800D0864("MP_POW"); Label(s5, xc, y);
                xc = (s16)(xc + 0x37);
                TXT(xc - w4 / 2, y, buf);
                xc = (s16)(xc + 0x19);
                fn_80290DDC(buf, "%d", fn_80110E00(e->item));
                w4 = fn_800CA3DC(buf, -1, 1.0f);
                s6 = fn_800D0864("MP_HIT"); Label(s6, xc, y);
                xc = (s16)(xc + 0x37);
                TXT(xc - w4 / 2, y, buf);
                xc = (s16)(xc + 0x19);
                fn_80290DDC(buf, "%d", fn_80110E58(e->item));
                w4 = fn_800CA3DC(buf, -1, 1.0f);
                s7 = fn_800D0864("MP_CRIT"); Label(s7, xc, y);
                xc = (s16)(xc + 0x37);
                if (*(u64*)fn_801116B8(e->item) & 0x8000ULL) {
                    char* s = fn_800D0864("MD_IMPOSSIBLE");
                    int w5 = fn_800CA3DC(fn_800D0864("MD_IMPOSSIBLE"), -1, 1.0f);
                    TXT(xc - w5 / 2, y, s);
                } else {
                    TXT(xc - w4 / 2, y, buf);
                }
                xc = (s16)(xc + 0x19);
                fn_80290DDC(buf, "%d", fn_80110EB0(e->item));
                w4 = fn_800CA3DC(buf, -1, 1.0f);
                s8 = fn_800D0864("MP_WGT"); Label(s8, xc, y);
                xc = (s16)(xc + 0x37);
                TXT(xc - w4 / 2, y, "%d", fn_80110EB0(e->item));
                xc = (s16)(xc + 0x19);
                s9 = fn_800D0864("MP_RNG"); Label(s9, xc, y);
                {
                IData* d3 = e->item->d;
                u32 m8 = d3 ? fn_801108D8(d3) : 0;
                d3 = e->item->d;
                u32 m10 = d3 ? fn_801107A0(d3, 0) : 0;
                if (m10 == m8) {
                    d3 = e->item->d;
                    fn_80290DDC(buf, " %d", d3 ? fn_801107A0(d3, 0) : 0);
                } else if (fn_801108D8(e->item->d) != 0xff) {
                    IData* d4 = e->item->d;
                    u32 m9 = d4 ? fn_801107A0(d4, 0) : 0;
                    fn_80290DDC(buf, "%d\x81|%d", m9, fn_801108D8(d4));
                } else {
                    IData* d4 = e->item->d;
                    u32 m9 = d4 ? fn_801107A0(d4, 0) : 0;
                    fn_80290DDC(buf, "%d\x81|%s", m9, fn_800D0864("MP_MPOW_HF"));
                }
                }
                w4 = fn_800CA3DC(buf, -1, 1.0f);
                TXT((s16)(xc + 0x46) - w4 / 2, y, buf);
                {
                int i;
                for (i = 0; i < 2; i++) {
                    if (e->lines[i]) TXT(x, i * 0x18 + y + 0x18, e->lines[i]);
                }
                }
            }
        }
    } else {
        Lines3(e, x, y);
    }
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
}
}
