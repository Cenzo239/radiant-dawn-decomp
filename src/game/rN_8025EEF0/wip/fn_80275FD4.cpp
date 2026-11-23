/* Same instructions and stack as the original (1935 words), registers only: score about 193. x lands in r21 instead of r31, and everything else shifts by one. The cause is the CSE of x + w: without it x gets r31, but the original has both. */
/* Conversation room: main list draw */
#include "game/rN_8025EEF0/roomdraw.h"

extern "C" {
extern char lbl_80373558[];
extern char lbl_80373564[];
extern s8 lbl_804CC078;
extern RC lbl_804CC080;

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
void fn_80275FD4(void) {
/*P*/
    int x;
    f32 fr;
    int h;
    int y;
    f32 sc;
    int w;
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
    {
/*P*/
        const char* names[2] = {lbl_80373558, lbl_80373564};
        int i;
/*E*/
        for (i = 0; i < 2; i++) {
/*P*/
            f32 d;
            int col;
            int xx = x + 0xC;
            int yy = y + 0xE + i * 0x1C;
/*E*/
            if (i == roomData()->m24[0]) {
                d = 2.0f;
                col = 0x35;
            } else {
                d = 0.0f;
                col = 0;
            }
            fn_801BCA5C(-(2.4f - 0.2f * i) - d);
            pA(8, xx, yy);
            fn_801BCA5C(-0.1f);
            fn_801BCA94();
            {
                const char* s = fn_800D0864(names[i]);
                fn_800CB3A8(xx + 0x34 - fn_800CA3DC(s, -1, 1.0f) / 2, yy + 4, col, 1, 0, 1.0f, 0.0f, s);
            }
            fn_801BCA5C(0.1f + ((2.4f - 0.2f * i) + d));
        }
    }
    fn_801BCA5C(-1.0f);
    fn_8007E154();
    fn_8007E174(0, 0x12);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080388(x + 0xC, y + 2, w - 0x18, h - 4);
    fn_800804D4(0, 0, 0, 0x99);
    fn_80080308();
    fn_801BCA5C(-1.0f);
    fn_8007E154();
    fn_8007E174(0, 0x12);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080388(x + 0x6E, y + 2, w - 0x7C, h - 4);
    fn_800804D4(0x26, 0x1E, 0x16, 0xFF);
    fn_80080308();
    fn_801BCA5C(-1.0f);
    pA(4, x, y);
    pB(x + 0xC, y, w - 0x18, 8.0f, 6);
    pB(x + 0xC, y + h - 4, w - 0x18, 8.0f, 6);
    pA(5, x + w - 0xC, y);
    fn_801BCA5C(-0.5f);
    pB(x + 0x6D, y + 3, 8.0f, h - 6, 7);
    fn_801BCA5C(0.5f);
    if (!lbl_804CC078) {
        lbl_804CC078 = 1;
    }
    {
        int hh = (int)(196.0f * roomData()->m50);
        int yy = (int)(roomData()->m4C - (f32)(hh / 2));
        lbl_804CC080.x = 0;
        lbl_804CC080.y = yy;
        lbl_804CC080.w = 0x260;
        lbl_804CC080.h = hh;
    }
    fn_8007E154();
    fn_8007E74C(fn_80272F94, &lbl_804CC080);
    fn_8007E164();
    switch (roomData()->m24[0]) {
    case 0:
        sc = roomData()->m4[1];
        fr = sc - (f32)(int)sc;
        break;
    case 1:
        sc = roomData()->m4[2];
        fr = sc - (f32)(int)sc;
        break;
    }
    {
        int i;
        for (i = 0; i < 8; i++) {
            switch (roomData()->m24[0]) {
            case 0: {
/*P*/
                int tx = x + 0x88;
                int ty = (int)(28.0f * ((f32)i - fr) + (f32)(y + 0xC));
                int n;
/*E*/
                fn_80074EB4(tx, ty + 0x12, 0xC0, 0x80);
                n = (int)sc + i;
                if (n >= 0 && n <= ((ConvSt*)lbl_804CC06C)->m14 - 1) {
/*P*/
                    void* e;
                    const char* s;
/*E*/
                    fn_801BCA5C(-1.0f);
                    e = fn_8010B100(((ConvSt*)lbl_804CC06C)->names[n]);
                    fn_800CB3A8(tx + 8, ty, 1, 1, 0, 1.0f, 0.0f, fn_8009285C(e));
                    s = fn_800929AC(e);
                    fn_800CB3A8(tx + 0x80 - fn_800CA3DC(fn_800929AC(e), -1, 1.0f) / 2, ty, 1, 1, 0, 1.0f, 0.0f, s);
                    fn_801BCA5C(1.0f);
                }
                break;
            }
            case 1: {
/*P*/
                int tx = x + 0x88;
                int ty = (int)(28.0f * ((f32)i - fr) + (f32)(y + 0xC));
                int n;
/*E*/
                fn_80074EB4(tx, ty + 0x12, 0xC0, 0x80);
                n = (int)sc + i;
                if (n >= 0 && n <= ((ConvSt*)lbl_804CC06C)->m1C - 1) {
                    fn_801BCA5C(-1.0f);
                    char** t = ((ConvSt*)lbl_804CC06C)->names2;
                    char* name = t[n];
                    const char* s;
                    if (fn_80291188(name, lbl_8037359C + 0x2F) != 0) {
                        if (fn_8010B1D8(name) == 0) break;
                        s = fn_80118C44(fn_8010B1D8(t[n]));
                    } else {
                        s = fn_800D0864(lbl_8037359C + 0x35);
                    }
                    fn_800CB3A8(tx + 8, ty, 1, 1, 0, 1.0f, 0.0f, s);
                    fn_801BCA5C(1.0f);
                }
                break;
            }
            }
        }
    }
    fn_8007E154();
    fn_8007E7B4();
    fn_8007E164();
    fn_801BCA5C(-1.0f);
    if (roomData()->m30 != 0) {
        fn_80072ACC(roomData()->m40 + 0xE8, roomData()->m34 + 0xC, 0xC8, 0x17, 0x19, 0x64, 1);
    }
    fn_801BCA5C(-1.0f);
    fn_800712E8(roomData()->m32, roomData()->m34, 1);
    fn_801BCA5C(2.0f);
    {
        int cnt;
        switch (roomData()->m24[0]) {
        case 0:
            cnt = ((ConvSt*)lbl_804CC06C)->m14;
            break;
        case 1:
            cnt = ((ConvSt*)lbl_804CC06C)->m1C;
            break;
        }
        fn_8017980C(roomData()->m58, (int)((f32)(x + w - 0x1E) + roomData()->m48), (int)((f32)(y + 0xC) + roomData()->m4C), h - 0x18);
        fn_80179888(roomData()->m58, (int)(28.0f * sc));
        fn_8017985C(roomData()->m58, cnt * 0x1C);
    }
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
