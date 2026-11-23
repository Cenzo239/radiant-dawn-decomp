/* Same instructions and stack as the original (1599 words), registers only: score about 138. bx/i want r19 and tx plus the string base want r25. Rect and flag blocks swap r3/r4/r0. */
/* Conversation room: "other" topics list draw */
#include "game/rN_8025EEF0/roomdraw.h"

extern "C" {
extern s8 lbl_804CC088;
extern RC lbl_804CC090;

static inline int roomFlag(int k) {
    if (isProc(lbl_8037359C)) {
        return fn_80245368(((ConvSt*)lbl_804CC06C)->m8, k);
    }
    if (isProc(lbl_8037359C + 0x13)) {
        return fn_80245368(*(void**)lbl_804CC074, k);
    }
    return 0;
}

static inline BOOL roomFlagB(int k) { return roomFlag(k) != 0; }
static inline int rAlign(int r, const char* s) { return r - fn_800CA3DC(s, -1, 1.0f); }

static inline int rAlign2(const int& r, void* e) { return r - fn_800CA3DC(fn_8009285C(e), -1, 1.0f); }
static inline void label(int x, int y, const int& b, int n) {
    fn_800CB3A8(x, y, b, 1, 0, 1.0f, 0.0f, fn_800D0864(((ConvItem*)((ConvSt*)lbl_804CC06C)->items[n])->m4));
}

static inline void rcSet(RC* r, int x, int y, int w, int h) { r->x = x; r->y = y; r->w = w; r->h = h; }
static inline void rcSet2(int x, int y, int w, int h) { lbl_804CC090.x = x; lbl_804CC090.y = y; lbl_804CC090.w = w; lbl_804CC090.h = h; }
static inline void pA(int i, int x, int y) {
    GXC t;
    GXC c;
/*P*/
    f32 ww;
    f32 hh;
    f32 h2;
    f32 w2;
/*E*/
    texSize(i, ww, hh);
    { const u8* p = fn_800CD204(1); c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = 0xFF; }
    texSize(i, w2, h2);
    { void* tx = roomTex();
    *(u32*)&t = *(u32*)&c;
    fn_801BC88C(x, y, x + ww, y + hh, 0.0f, 0.0f, w2, h2, tx, i, &t, 0x11, 0); }
}
static inline void pB(int x, int y, f32 w, f32 h, int i) {
    GXC c;
    GXC t;
/*P*/
    f32 w2;
    f32 h2;
/*E*/
    { const u8* p = fn_800CD204(1); c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = 0xFF; }
    texSize(i, w2, h2);
    { void* tx = roomTex();
    *(u32*)&t = *(u32*)&c;
    fn_801BC88C(x, y, x + w, y + h, 0.0f, 0.0f, w2, h2, tx, i, &t, 0x11, 0); }
}
void fn_80277E10(void) {
/*P*/
    int tx;
    int bx;
    int i;
    int x;
    int y;
    int w;
    int h;
    int by;
/*E*/
    x = roomData()->m40;
    y = roomData()->m42;
    w = roomData()->m44;
    h = roomData()->m46;
    if (roomData()->m54 > 0) {
        roomData()->m54--;
        roomData()->m50 = fn_8017F68C(0.0f, 1.0f, 5 - roomData()->m54, 5.0f, 0);
    }
    fn_8007E154();
    fn_8007E4E4(roomData()->m48, roomData()->m4C, 100.0f, roomData()->m50);
    fn_8007E164();
    fn_801BCA5C(-1.0f);
    pB(x + 4, y + 3, w - 8, h - 6, 0xC);
    fn_801BCA5C(-1.0f);
    fn_80070688(x, y, w, h);
    fn_801BCA5C(-1.0f);
    {
        bx = x + 0x62;
        by = y - 0x10;
        int ww = 0xFA;
        int hh = 0x1A;
        int bw = 0xF2;
        fn_8007E154();
        fn_8007E174(0, 0x12);
        fn_8007E164();
        fn_800800D4(1);
        fn_80080388(bx + 3, by + 3, ww, hh);
        fn_800804D4(0x15, 8, 5, 0xFF);
        fn_80080308();
        fn_801BCA5C(-1.0f);
        pA(9, bx, by);
        pA(0xA, bx + 0xF8, by);
        pB(bx + 7, by, bw, 8.0f, 0xB);
        pB(bx + 7, by + 0x1C, bw, 8.0f, 0xB);
        fn_801BCA94();
        {
            const char* s = ((ConvSt*)lbl_804CC06C)->text;
            fn_800CB3A8(bx + 0x80 - fn_800CA3DC(s, -1, 1.0f) / 2, by + 4, 0x35, 1, 0, 1.0f, 0.0f, s);
        }
    }
    if (!lbl_804CC088) {
        lbl_804CC088 = 1;
    }
    {
        f32 hh = 196.0f * roomData()->m50;
        int yy = (int)(roomData()->m4C - hh * 0.5f);
        lbl_804CC090.x = 0;
        lbl_804CC090.y = yy;
        lbl_804CC090.w = 0x260;
        lbl_804CC090.h = (int)hh;
    }
    fn_8007E154();
    fn_8007E74C(fn_80272F94, &lbl_804CC090);
    fn_8007E164();
    {
/*P*/
    f32 sc;
    f32 fr;
/*E*/
    sc = roomData()->m4[3];
    tx = x + 0xC;
    fr = sc - (f32)(int)sc;
    {
        for (i = 0; i < 8; i++) {
/*P*/
            int ty = (int)(28.0f * ((f32)i - fr) + (f32)(y + 0x1C));
            int n = (int)(sc + (f32)i);
/*E*/
            if (n >= ((ConvSt*)lbl_804CC06C)->count) break;
            fn_80074EB4(tx, ty + 0x12, 0x18A, 0x80);
            fn_801BCA5C(-1.0f);
            {
                int b = roomFlag(((ConvItem*)((ConvSt*)lbl_804CC06C)->items[n])->mC) ? 1 : 0;
                fn_800CB3A8(tx + 8, ty, b, 1, 0, 1.0f, 0.0f, fn_800D0864(((ConvItem*)((ConvSt*)lbl_804CC06C)->items[n])->m4));
            }
            if (roomData()->m24[0] == 1) {
/*P*/
                void* e = fn_8010B100(((ConvItem*)((ConvSt*)lbl_804CC06C)->items[n])->m0);
                const char* s = fn_800929AC(e);
                int rx;
/*E*/
                rx = rAlign(tx + 0x182, fn_800929AC(e));
                fn_800CB3A8(rx, ty, 0x34, 1, 0, 1.0f, 0.0f, s);
                s = fn_8009285C(e);
                { int k = 8; rx = tx + 0x182 - fn_800CA3DC(fn_800929AC(e), -1, 1.0f) - k - fn_800CA3DC(fn_8009285C(e), -1, 1.0f); }
                fn_800CB3A8(rx, ty, 0x34, 1, 0, 1.0f, 0.0f, s);
            }
            fn_801BCA5C(1.0f);
        }
    }
    }
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
    fn_801BCA5C(-1.0f);
    fn_80072ACC(x + 0xCE, roomData()->m34 + 0xC, 0x188, 0x17, 0x19, 0x64, 1);
    fn_801BCA5C(-1.0f);
    fn_800712E8(roomData()->m32, roomData()->m34, 1);
    fn_801BCA5C(2.0f);
    fn_8017980C(roomData()->m58, (int)((f32)(x + w - 0x16) + roomData()->m48), (int)((f32)(y + 0xC) + roomData()->m4C), h - 0x18);
    fn_80179888(roomData()->m58, (int)(28.0f * curF()));
    fn_8017985C(roomData()->m58, ((ConvSt*)lbl_804CC06C)->count * 0x1C);
    fn_80179864(roomData()->m58, 0xC4);
    fn_80179A7C(roomData()->m58, (u8)*(s16*)(lbl_804CC06C + 0x1E8));
    fn_80179854(roomData()->m58, 95.0f);
    if (1.0f == roomData()->m50) {
        fn_80179A84(roomData()->m58);
    }
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 100.0f, 1.0f);
    fn_8007E164();
}

}
