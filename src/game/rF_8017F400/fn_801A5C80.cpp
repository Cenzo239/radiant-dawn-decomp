#include "game/rF_8017F400/drawinl.h"
#pragma auto_inline off
#pragma pool_strings on
extern "C" {
void StringPool(const char** p) {
    p[0] = "%7d";
    p[1] = "%s%s %s%s";
    p[2] = "MD_TOMAP";
    p[3] = "MD_LEADER";
    p[4] = "MD_CUR";
    p[5] = "MD_RTN";
    p[6] = "E_TutEvent";
    p[7] = "MCTTUT00_0";
    p[8] = "MCTTUT00_1";
    p[9] = "MCTTUT00_2";
    p[10] = "%3d";
    p[11] = "%02d";
    p[12] = ":";
    p[13] = "%s";
    p[14] = "MP_LV";
    p[15] = "%2d";
    p[16] = "MP_HP";
    p[17] = "/%3d";
    p[18] = "EID_POINT_APP";
    p[19] = "window/jyokyo/jyokyo";
    p[20] = ".cms";
    p[21] = "SFX_SYS_STATE_WINDOW_OPEN1";
    p[22] = "SFX_SYS_STATE_WINDOW_MOVE1";
    p[23] = "SFX_SYS_STATE_WINDOW_SELECT1";
    p[24] = "SFX_SYS_CANCEL1";
    p[25] = "";
    p[26] = "E_JyokyoMap";
}
extern void fn_801BCA5C(f32);
extern void fn_801BCA94(void);
extern int fn_800625F0(void*, int*, int*, int*);
extern u8 lbl_803CAB38[];
extern char lbl_8036D22C[];
extern u8* fn_80060728(void*);
typedef struct OvA { u8 pad[0xC]; void* arch; } OvA;
extern OvA* lbl_804CB964;
static inline void TileK(int tile, u8 alpha, f32 x, f32 y, f32 sc) {
    u8* p = fn_800CD204(1);
    GXColor2 c;
    c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = alpha;
    {
    TexH** t = (TexH**)fn_80006A0C(lbl_804CB964->arch, tile);
    f32 w = (*t)->x2;
    f32 h = (*t)->x0;
    fn_801BC88C(lbl_804CB964->arch, tile, c, 0x11, 0, x, y, x + w * sc, y + h * sc, 0.0f, 0.0f, w, h);
    }
}
void fn_801A5C80(f32 x, f32 y) {
    int a, b, c;
    int f;
    fn_801BCA5C(-1.0f);
    fn_801BCA94();
    f = fn_800625F0(lbl_803CAB38, &a, &b, &c);
    if (a > 0x63) {
        a = 0x63;
        b = 0x3B;
        c = 0x3B;
    }
    fn_800CB3A8(0.8f, 0.0f, 6.0f + x, y, 1, 1, 0, "%02d", a);
    if (f != 0) fn_800CB3A8(0.8f, 0.0f, 30.0f + x, y - 2.0f, 1, 1, 0, ":");
    fn_800CB3A8(0.8f, 0.0f, 38.0f + x, y, 1, 1, 0, "%02d", b);
    if (f != 0) fn_800CB3A8(0.8f, 0.0f, 62.0f + x, y - 2.0f, 1, 1, 0, ":");
    fn_800CB3A8(0.8f, 0.0f, 70.0f + x, y, 1, 1, 0, "%02d", c);
    fn_801BCA5C(1.0f);
}

void fn_801A5ECC(f32 x, f32 y) {
    int k;
    int i;
    int m;
    int j;
    int n;
    n = lbl_803CAB38[0x9F];
    fn_801BCA5C(-1.0f);
    if (n > 0x18) n = 0x18;
    if (n <= 0xC) {
        for (i = 0, k = 0; i < n; k += 0xF, i++) {
            TileK(5, 0xFF, x + k, y, 1.0f);
        }
    } else {
        for (j = 0, m = 0; j < 0xC; j++, m += 0xF) {
            if (j + 0xC < n) TileK(6, 0xFF, x + m, y, 1.0f);
            else TileK(5, 0xFF, x + m, y, 1.0f);
        }
    }
    fn_801BCA5C(1.0f);
}

extern const char* fn_8006233C(void*, int);
extern const char* fn_80062370(void*, int);
extern void fn_8006FED4(f32, f32, f32, f32);
extern void fn_80074EB4(int, int, int, int);
static inline void L2(f32 x, f32 y, int n2) {
    int j;
    for (j = 0; j < n2; j++) {
        int m = 0x6E;
        fn_800CB3A8(1.0f, 0.0f, x + m, y, 2, 0, 0, fn_80062370(lbl_803CAB38, j));
        y += 24.0f;
    }
}
void fn_801A5800(f32 x, f32 y) {
    int n1;
    int n2;
    int i;
    int k;
    f32 y2;
    int j;
    n1 = 0;
    n2 = 0;
    fn_801BCA5C(-4.0f);
    TileK(2, 0xFF, x, y, 1.0f);
    fn_801BCA5C(-1.0f);
    for (i = 0; i < 3; i++) {
        if (*(s8*)fn_8006233C(lbl_803CAB38, i) == 0) break;
        n1++;
    }
    for (i = 0; i < 5; i++) {
        if (*(s8*)fn_80062370(lbl_803CAB38, i) == 0) break;
        n2++;
    }
    k = 0x1B;
    y2 = y + k;
    TileK(3, 0xFF, 36.0f + x, 4.0f + y2, 1.0f);
    fn_801BCA94();
    k = 0x6E;
    for (i = 0; i < n1; i++) {
        fn_800CB3A8(1.0f, 0.0f, x + k, y2, 2, 0, 0, fn_8006233C(lbl_803CAB38, i));
        y2 += 24.0f;
    }
    {
    int m = 0x1B;
    y += m;
    }
    if (n2 > 3) y += (6 - n2) * 24;
    else y += 72.0f;
    TileK(4, 0xFF, 36.0f + x, 4.0f + y, 1.0f);
    fn_801BCA94();
    L2(x, y, n2);
    fn_801BCA5C(5.0f);
}

extern void fn_800CB278(s16, s16, int, const char*, ...);
static inline void SprK(int tile, u8 alpha, f32 x, f32 y, f32 w, f32 h) {
    u8* p = fn_800CD204(1);
    GXColor2 c;
    c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = alpha;
    {
    TexH** t = (TexH**)fn_80006A0C(lbl_804CB964->arch, tile);
    f32 tw = (*t)->x2;
    f32 th = (*t)->x0;
    fn_801BC88C(lbl_804CB964->arch, tile, c, 0x11, 0, x, y, x + w, y + h, 0.0f, 0.0f, tw, th);
    }
}
typedef struct MsgE { u8 pad[0xC]; const char* s; int v; u8 pad14[0x10]; } MsgE;
typedef struct OvW { u8 pad[0x14]; f32 x, y; int n; MsgE e[1]; } OvW;
static inline void MsgList(OvW* w, f32 x, f32 y) {
    int j, m;
    MsgE* e = w->e;
    for (j = 0, m = 0; j < w->n; e++, m += 0x18, j++) {
        fn_800CB278(16.0f + x, 20.0f + y + m, 1, e->s);
        fn_800CB278(178.0f + x, 20.0f + y + m, 1, "%3d", e->v);
    }
}
void fn_801A53DC(void) {
    OvW* w;
    int k;
    MsgE* e;
    int i;
    f32 x;
    f32 y;
    f32 h;
    int j;
    int m;
    int kind;
    f32 wd;
    for (i = 0, k = 0; i < 4; i++, k += 4) {
        kind = *(int*)((u8*)lbl_804CB964 + k + 0x348);
        w = (OvW*)((u8*)lbl_804CB964 + kind * 0xC4);
        if (w->n != 0) {
            x = w->x;
            y = w->y;
            h = w->n * 0x18 + 0x1C;
            fn_801BCA5C(-1.0f);
            wd = 224.0f;
            SprK((u16)(kind + 0xB), 0xC4, x, y, wd, h);
            fn_801BCA5C(-1.0f);
            fn_8006FED4(x, y, wd, h);
            TileK((u16)(kind + 7), 0xFF, 6.0f + x, 8.0f + y, 1.0f);
            for (j = 0, m = 0; j < w->n; m += 0x18, j++) {
                fn_80074EB4((int)(8.0f + x), (int)(20.0f + (20.0f + y) + m), 0xD0, 0xA0);
            }
            fn_801BCA5C(-1.0f);
            MsgList(w, x, y);
            fn_801BCA5C(3.0f);
        }
    }
}

extern void* fn_8006074C(void*);
extern void* fn_80085708(const char*);
extern const char* fn_8009285C(void*);
extern const char* fn_80092904(void*);
extern const char* fn_80092958(void*);
extern const char* fn_800D0864_(const char*);
extern void fn_801C6DA0(int col, const char* s, f32 x, f32 y);
static inline void Ctr(const char* s, int cx, int y) {
    fn_801C6DA0(8, s, cx - fn_800CA3DC(s, -1, 1.0f) / 2, y);
}
void fn_801A50C4(f32 x, f32 y) {
    int x0;
    int x1;
    int x2;
    int y0;
    int y1;
    int y2;
    void* m;
    m = fn_8006074C(lbl_803CAB38);
    x0 = 60.0f + x;
    x1 = 156.0f + x;
    x2 = 156.0f + x;
    y0 = 22.0f + y;
    y1 = 22.0f + x;
    y2 = 46.0f + x;
    fn_801BCA5C(-1.0f);
    fn_801BCA94();
    if (fn_80085708("E_TutEvent") == 0) {
        Ctr(fn_8009285C(m), x0, y0);
        { const char* s = fn_80092904(m); Ctr(s, x1, y1); }
        { const char* s = fn_80092958(m); Ctr(s, x2, y2); }
    } else {
        Ctr(fn_800D0864("MCTTUT00_0"), x0, y0);
        { const char* s = fn_800D0864("MCTTUT00_1"); Ctr(s, x1, y1); }
        { const char* s = fn_800D0864("MCTTUT00_2"); Ctr(s, x2, y2); }
    }
    fn_801BCA5C(1.0f);
}
}
