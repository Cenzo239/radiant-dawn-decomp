#include "game/rF_8017F400/drawinl.h"
#pragma auto_inline off
#pragma pool_strings on
extern "C" {
void StringPool(const char** p) {
    p[0] = "MTM_NAVI_SELECT";
    p[1] = "MTM_NAVI_OK";
    p[2] = "MTM_YES";
    p[3] = "MTM_NO";
    p[4] = "MTM_TRI_MAP1";
    p[5] = "MTM_TRI_MAP1_EX";
    p[6] = "MTM_TRI_MAP2";
    p[7] = "MTM_TRI_MAP2_EX";
    p[8] = "MTM_TRI_MAP3";
    p[9] = "MTM_TRI_MAP3_EX";
    p[10] = "MTM_TRI_MAP4";
    p[11] = "MTM_TRI_MAP4_EX";
    p[12] = "MTM_TRI_MAP5";
    p[13] = "MTM_TRI_MAP5_EX";
    p[14] = "MTM_TRI_MAP6";
    p[15] = "MTM_TRI_MAP6_EX";
    p[16] = "window/trialmenu.tpl";
    p[17] = "%s%s %s%s %s%s";
    p[18] = "MTM_SELECT";
    p[19] = "MTM_DECIDE";
    p[20] = "MTM_RETURN";
    p[21] = "SFX_SYS_SELECT1";
    p[22] = "SFX_SYS_CANCEL1";
    p[23] = "SFX_SYS_CURSOR_WINDOW_MOVE1";
    p[24] = "SFX_SYS_ATT_WINDOW_OPEN1";
    p[25] = "MTM_CANCEL";
    p[26] = "SFX_SYS_SELECT3";
    p[27] = "SFX_SYS_CURSOR_WINDOW_MOVE2";
    p[28] = "window/achieve.cms";
    p[29] = "MTM_TRI_RES_TITLE";
    p[30] = "MTM_TRI_RES_COMP_TURN";
    p[31] = "%d";
    p[32] = "MTM_TRI_RES_TURN";
    p[33] = "#C01%s  #C06%02d\x81""F%02d\x81""F%02d";
    p[34] = "MTM_TRI_RES_PLAYTIME";
    p[35] = "MTM_TRI_RES_TACT_RANK";
    p[36] = "%c";
    p[37] = "MTM_TRI_RES_ALIVE_RANK";
    p[38] = "MTM_TRI_RES_BTL_RANK";
    p[39] = "MTM_TRI_RES_TOTAL_RANK";
    p[40] = "#C01%s   #C06%02d\x81""F%02d\x81""F%02d";
    p[41] = "";
}

typedef struct PmE { u8 flag; u8 alpha; u8 pad[2]; s16 x, y; s16 t; s16 fx, fy, tx, ty; } PmE;
typedef struct PmD {
    void* arch;
    PmE e[2];
    u8 pad28[0x60];
    u8 mode; s8 cur; s8 last; u8 pad8B;
    s16 alpha; s16 dim; f32 k;
    u8 nlist; u8 nline; u8 pad96[2];
    const char* list[12];
    u8 xC8[6];
    char line[5][0x40];
} PmD;
extern void fn_801BCA5C(f32);
extern void fn_801BCA94(void);
extern f32 fn_8017F68C(int, f32, f32, f32, f32);
#if TARGET_PC
extern FE10_PROTO void fn_8007E374(void*, p32arg, int);
#else
extern void fn_8007E374(void*, int, int);
#endif
extern void fn_800804D4(int, int, int, int);
extern void fn_800712E8(int, int, int);
extern void fn_80072ACC(int, int, int, int, int, int, int);
extern void* fn_8010B094(int);
extern const char* fn_80092D04(void*, int);
extern void fn_801C6D9C(void*, int, int, int);
static inline void Pic(void) {
    s16 x = 0xE2;
    s16 y = 0x6E;
    fn_80080348(x, y, 0.0f, 0.0f);
    {
    s16 x2 = 0x24A;
    s16 y2 = 0x17C;
    fn_80080368(x2, y2, 360.0f, 270.0f);
    }
}
static inline void TI(PmD* d, int tile, u32 fl, f32 x, f32 y) {
    u8* p = fn_800CD204(1);
    GXColor2 c;
    c.r = p[0]; c.g = p[1]; c.b = p[2]; c.a = 0xFF;
    {
    TexH** t = (TexH**)fn_80006A0C(d->arch, tile);
    f32 tw = (*t)->x2, th = (*t)->x0;
    fn_801BC88C(d->arch, tile, c, 0x11, fl, x, y, x + tw, y + th, 0.0f, 0.0f, tw, th);
    }
}
void fn_801ADED4(void* proc) {
    int y;
    PmD* d;
    PmD* q;
    PmE* e;
    char* p2;
    int i;
    int mx;
    int yy;
    int w;
    char* s;
    int j2;
    int k;
    void* m;
    int j;
    int n;
    int j1;
    d = *(PmD**)((u8*)proc + 0x30);
    if ((s8)d->mode == 0) {
        d->dim -= 0x1E;
        if (d->dim < 0) d->dim = 0;
        d->k -= 0.2f;
        if (d->k < 0.0f) d->k = 0.0f;
    }
    if ((int)d->mode == 1) {
        d->dim += 0x1E;
        if (d->dim > 0x80) d->dim = 0x80;
        d->k += 0.2f;
        if (d->k > 1.0f) d->k = 1.0f;
    }
    d->alpha += 0x14;
    if (d->alpha > 0xFF) d->alpha = 0xFF;
    e = d->e;
    for (i = 0; i < 2; i++, e++) {
        if (e->t > 0) {
            e->t--;
            k = 4 - e->t;
            n = 4;
            e->x = fn_8017F68C(n, e->fx, e->tx, k, n);
            e->y = fn_8017F68C(n, e->fy, e->ty, k, n);
        }
    }
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 100.0f, 1.0f);
    fn_8007E7DC(0xFF);
    fn_8007E164();
    if (d->last != -1) {
        fn_8007E154();
        fn_8007E374(d->arch, d->last + 4, 0x11);
        fn_8007E164();
        fn_800800D4(1);
        Pic();
        fn_800804F4(0xFF);
        fn_80080308();
    }
    fn_801BCA5C(-1.0f);
    fn_8007E154();
    fn_8007E374(d->arch, d->cur + 4, 0x11);
    fn_8007E164();
    fn_800800D4(1);
    Pic();
    fn_800804F4((u8)d->alpha);
    fn_80080308();
    fn_801BCA5C(-1.0f);
    fn_801BCA94();
    {
    q = d;
    j = 0;
    yy = 0x78;
    for (; j < d->nlist; j++) {
        fn_800CB3A8(1.0f, 0.0f, 0x38, yy, 1, 1, 0, fn_800D0864(q->list[0]));
        q = (PmD*)((u8*)q + 4);
        yy += 0x18;
    }
    }
    fn_801BCA5C(1.0f);
    fn_801BCA5C(-5.0f);
    if (d->e[0].flag != 0) {
        fn_800712E8(d->e[0].x, d->e[0].y, d->e[0].alpha);
        fn_80072ACC(d->e[0].x + 0x50, d->e[0].y + 0xE, 0xA0, 0x17, 0x19, 0x64, d->e[0].alpha);
    }
    fn_801BCA5C(-5.0f);
    fn_8007E154();
    fn_8007E174(0, 0x12);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080348(0.0f, 0.0f, 0.0f, 0.0f);
    fn_80080368(604.0f, 448.0f, 0.0f, 0.0f);
    fn_800804D4(0, 0, 0, (u8)d->dim);
    fn_80080308();
    fn_801BCA5C(-1.0f);
    fn_801BCA5C(-2.0f);
    TI(d, 0, 0, 23.0f, 18.0f);
    fn_801BCA5C(-1.0f);
    TI(d, 1, 0, 39.0f, 26.0f);
    fn_801BCA5C(2.0f);
    fn_801BCA5C(-1.0f);
    TI(d, 2, 0, 0.0f, 47.0f);
    TI(d, 2, 1, 304.0f, 47.0f);
    fn_801BCA5C(-1.0f);
    fn_801BCA94();
    if ((s8)d->mode == 0) {
        fn_800CB3A8(1.0f, 0.0f, 0xF0, 0x3D, 2, 0, 0, fn_800D0864("MTM_NAVI_SELECT"));
    }
    if ((int)d->mode == 1) {
        fn_800CB3A8(1.0f, 0.0f, 0x8C, 0x3D, 2, 0, 0, fn_800D0864("MTM_NAVI_OK"));
        fn_800CB3A8(1.0f, 0.0f, 0x1C2, 0x3D, 2, 0, 0, fn_800D0864("MTM_YES"));
        fn_800CB3A8(1.0f, 0.0f, 0x1FE, 0x3D, 2, 0, 0, fn_800D0864("MTM_NO"));
    }
    fn_801BCA5C(2.0f);
    fn_801BCA5C(-5.0f);
    if (d->e[1].flag != 0) {
        fn_800712E8(d->e[1].x, d->e[1].y, d->e[1].alpha);
        fn_80072ACC(d->e[1].x + 0x1C, d->e[1].y + 0xC, 0x50, 0x18, 0x19, 0x4B, d->e[1].alpha);
    }
    fn_801BCA5C(8.0f);
    if (0.0f != d->k) {
        fn_8007E154();
        fn_8007E4E4(304.0f, 244.0f, 50.0f, d->k);
        fn_8007E164();
        {
        int tx = -0xE8, ty = -0x88;
        TI(d, 3, 0, tx, ty);
        }
        fn_801BCA5C(-1.0f);
        { s16 w1; w1 = fn_800CA3DC(fn_800D0864(d->list[*(s16*)((u8*)d + 6)]), -1, 1.0f);
        fn_800CB3A8(1.0f, 0.0f, -6 - w1 / 2, -0x68, 2, 0, 0, fn_800D0864(d->list[*(s16*)((u8*)d + 6)])); }
        m = fn_8010B094(*((u8*)d + 0xC8 + *(s16*)((u8*)d + 6)) + 0x5B);
        if (fn_80092D04(m, 0) != 0) fn_800CB3A8(1.0f, 0.0f, -0x50, -0x42, 2, 0, 0, fn_800D0864(fn_80092D04(m, 0)));
        if (fn_80092D04(m, 1) != 0) fn_800CB3A8(1.0f, 0.0f, 0x28, -0x42, 2, 0, 0, fn_800D0864(fn_80092D04(m, 1)));
        s = (char*)d + 0xCE;
        mx = 0;
        {
        p2 = s;
        j1 = 0;
        for (; j1 < d->nline; p2 += 0x40, j1++) {
            w = fn_800CA3DC(p2, -1, 1.0f);
            if (w > mx) mx = w;
        }
        }
        mx = 0x1D0 - mx;
        n = -0xE8;
        j2 = 0;
        y = -0x16;
        for (; j2 < d->nline; s += 0x40, y += 0x18, j2++) {
            fn_800CB3A8(1.0f, 0.0f, 0.5f * mx + n, y, 0xF, 0, 0, s);
        }
        fn_801BCA5C(1.0f);
    }
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 50.0f, 1.0f);
    fn_8007E164();
    fn_801C6D9C((u8*)d + 0x28, 0xFF, 0xFF, 0);
    fn_8007E154();
    fn_8007E7DC(0xFF);
    fn_8007E164();
}

#if TARGET_PC
extern FE10_PROTO void fn_8017FA84(long long, p32arg, u32*, u32*);
#else
extern void fn_8017FA84(u32, u32, u32*, u32*, u32*);
#endif
extern u8* fn_8024BC94(void);
extern u8 lbl_803CAB38[];
extern u32 fn_800634D8(void*);
extern u32 fn_80063568(void*);
extern u32 fn_80063620(void*);
extern u32 fn_8006376C(void*);
extern const char* fn_800D0864_x(const char*);
typedef struct TrD { u8 pad[8]; u32 tlo, thi; void* arch; } TrD;
#define T1(col, sc, X, Y, ...) fn_800CB3A8(sc, 0.0f, X, Y, col, 1, 0, __VA_ARGS__)
static inline void Rate(const char* key, u32 v, f32 x, f32 y) {
    fn_800CB3A8(1.2f, 0.0f, x + fn_800CA3DC(fn_800D0864(key), -1, 1.0f) + 32.0f, y, 6, 1, 0, "%c", v);
}
static inline void TI0(TrD* d, f32 x, f32 y) {
    GXColor2 c = mk(fn_800CD204(1), 0xFF);
    TexH** t = (TexH**)fn_80006A0C(d->arch, 0);
    f32 tw = (*t)->x2, th = (*t)->x0;
    fn_801BC88C(d->arch, 0, c, 0x11, 0, x, y, x + tw, y + th, 0.0f, 0.0f, tw, th);
}
}
