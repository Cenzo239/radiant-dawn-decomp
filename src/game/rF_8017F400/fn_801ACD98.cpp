#include "game/rF_8017F400/drawinl.h"
#pragma auto_inline off
#pragma pool_strings on
extern "C" {
void StringPool(const char** p) {
    p[0] = "--";
    p[1] = "%d";
    p[2] = "??";
    p[3] = "????";
    p[4] = "%s %d";
    p[5] = "MTERR_VIT";
    p[6] = "MP_POW";
    p[7] = "0";
    p[8] = "MTERR_REST";
    p[9] = "%2d";
    p[10] = "IID_LONGARCH";
    p[11] = "IID_IRONARCH";
    p[12] = "IID_KILLERARCH";
    p[13] = "IID_ONAGER";
    p[14] = "MT_\x83""A\x81""[\x83""`\x82""\xEB""";
    p[15] = "MT_\x83""A\x81""[\x83""`\x82""\xA0""";
    p[16] = "MT_\x83""A\x81""[\x83""`\x82""\xAB""";
    p[17] = "MT_\x93""\x8A""\x90""\xCE""\x8A""\xED""";
    p[18] = "\x83""V\x83""\x85""\x81""[\x83""^\x81""[\x96""\xA2""\x94""z\x92""u!";
    p[19] = "#O%s";
    p[20] = "#O%4d";
    p[21] = "";
    p[22] = "MW_\x8E""c\x82""\xE8""";
    p[23] = "window/terrain/terrain";
    p[24] = ".cms";
    p[25] = "GetDieEnemyNumToComplete";
}

typedef struct TerB { s8 a, b, c; u8 pad3; u8 pad4[3]; u8 fl; } TerB;
typedef struct TerP { u8 pad[8]; TerB* b; } TerP;
static inline void Ico(void* tex, int tile, int x, int y, f32 ofs, f32 sc) {
    fn_801BC88C(tex, tile, *(GXColor2*)fn_800CD204(1), 0x11, 0, (f32)x + ofs, y + 2, (f32)x + ofs + 16.0f * sc, y + 0x12, 0.0f, 0.0f, 16.0f, 16.0f);
}
void fn_801ABC34(void* tex, TerP* p, int x, int y) {
    f32 sc, ofs;
    char b0[8], b1[8], b2[8];
    if (fn_801D09F0() == 0) { sc = 1.0f; ofs = 0.0f; }
    else { sc = 0.764f; ofs = 3.0f; }
    Ico(tex, 0xB, x, y, ofs, sc);
    Ico(tex, 0xC, x + 0x22, y, ofs, sc);
    Ico(tex, 0xD, x + 0x44, y, ofs, sc);
    FontReset();
    if (p != 0) {
        if (p->b->fl & 1) {
            strcpy(b0, "--");
            strcpy(b1, "--");
            strcpy(b2, "--");
        } else {
            fn_80290DDC(b0, "%d", p->b->a);
            fn_80290DDC(b1, "%d", p->b->b);
            fn_80290DDC(b2, "%d", p->b->c);
        }
    } else {
        strcpy(b0, "??");
        strcpy(b1, "??");
        strcpy(b2, "??");
    }
    fn_800CB3A8(0.75f, 0.0f, x + 0x1C - fn_800CA3DC(b0, -1, 1.0f) / 2, y, 6, 0, 0, b0);
    fn_800CB3A8(0.75f, 0.0f, x + 0x3C - fn_800CA3DC(b1, -1, 1.0f) / 2, y, 6, 0, 0, b1);
    fn_800CB3A8(0.75f, 0.0f, x + 0x60 - fn_800CA3DC(b2, -1, 1.0f) / 2, y, 6, 0, 0, b2);
}

typedef struct LFlags { u32 a : 5; u32 b : 1; u32 c : 24; u32 d : 2; } LFlags;
typedef struct PrepD { u8 pad[0x30]; f32 x, y; void* tex; u8 x3C; u8 a; u8 pad3E[4]; u16 v; } PrepD;
extern u8 lbl_803CAB38[];
extern LFlags* fn_80060728(void*);
extern const char* fn_8006233C(void*, int);
extern void fn_801AC8BC(void*, int, const char*, int, f32, f32);
extern void fn_801AC7AC(void*, int, int, f32, f32);
extern void fn_801AC9D8(void*, int, int, f32, f32);
extern void fn_801ACB9C(void);
extern void fn_800D0AE4(int, int);
extern void fn_801BCA94(void);
extern void fn_8007E7F4(void);
static inline void Cap(const char* s, int a, f32 x, f32 y) {
    fn_8007E154();
    fn_8007E4E4(x, y - 7.0f, 104.0f, 1.0f);
    fn_8007E7DC((u8)a);
    fn_8007E164();
    fn_801BCA94();
    fn_800CB3A8(1.0f, 0.0f, 0xC, 0xC, 1, 0, 1, s);
    fn_8007E7F4();
}
extern u8 lbl_803EC898[];
extern u8 lbl_803CB770[];
typedef struct TUnit { u8 pad[4]; u8 x4; u8 x5; } TUnit;
typedef struct Terr { u8 pad[0xE]; u16 xE; } Terr;
extern void* fn_8010B240(u8);
extern Terr* fn_8010B228(const char*);
extern int fn_80118098(void*, int, int);
extern int fn_8011D260(int);
extern const char* fn_8011D39C(void*);
extern TUnit* fn_80066130(void*, int, int, int);
extern TUnit* fn_80066DA8(void*, int, int, int);
extern void* fn_80066D18(TUnit*);
extern u32 fn_80110DA8(void*);
extern int fn_800A0644(int, int);
#if TARGET_PC
extern FE10_PROTO void fn_8007E374(void*, p32arg, int);
#else
extern void fn_8007E374(void*, int, int);
#endif
extern void fn_80080430(f32, f32, f32, f32, f32, f32);
typedef struct TileD { u8 pad[0x44]; u16 id[4]; const char* nm[4]; } TileD;
static inline int TerAt(int cx, int cy) {
    int r = (u8)fn_80118098(lbl_803EC898, cx, cy);
    if (lbl_803EC898[cx + cy * 0x40 + 0x200D] == 0) r = -1;
    return r;
}
extern void fn_801AC084(TileD* d, void* tex, int a, f32 x, f32 y);

extern u32 lbl_803CB860[];
extern void fn_800CB278(s16, s16, int, const char*, ...);
void fn_801ACB9C(void) {
    u8* pc;
    int* pv;
    const char** pt;
    int* pi;
    int y;
    int i;
    int sw;
    int j;
    int v[4];
    int idx[4];
    fn_8007E154();
    fn_8007E4E4(0.0f, 0.0f, 105.0f, 1.0f);
    fn_8007E174(0, 0x13);
    fn_8007E164();
    idx[0] = 0; v[0] = lbl_803CB860[0];
    idx[1] = 1; v[1] = lbl_803CB860[1];
    idx[2] = 2; v[2] = lbl_803CB860[2];
    idx[3] = 3; v[3] = lbl_803CB860[3];
    sw = 1;
    while (sw != 0) {
        sw = 0;
        for (j = 0; j < 3; j++) {
            if (v[j] < v[j + 1]) {
                int a = v[j], b = v[j + 1];
                int c = idx[j], d = idx[j + 1];
                sw = 1;
                v[j + 1] = a; v[j] = b; idx[j + 1] = c; idx[j] = d;
            }
        }
    }
    {
#pragma pool_strings off
    const char* tb[4] = {"1st", "2nd", "3rd", "4th"};
#pragma pool_strings on
    u8 cl[4] = {7, 3, 4, 6};
    pv = v; pt = tb; pi = idx;
    y = 0x98;
    for (i = 0; i < 4; i++, y += 0x14, pv++, pt++, pi++) {
        if (*pv < 0) break;
        fn_800CB278(0x10, y, 1, "#O%s", *pt);
        fn_800CB278(0x30, y, cl[*pi], "#O%4d", *pv);
    }
    }
}
void fn_801ACD98(PrepD* d) {
    int i;
    int k;
    int a;
    const char* s;
    f32 ox;
    f32 oy;
    if (d->a != 0 && d->tex != 0) {
        if (fn_80060728(lbl_803CAB38)->b == 1) return;
        a = d->a * 2;
        if (a > 0xFF) a = 0xFF;
        fn_801AC084((TileD*)d, d->tex, a, 24.0f + d->x, 24.0f + d->y);
        k = 0x6B;
        for (i = 0; i < 3; i++, k += 0x24) {
            s = fn_8006233C(lbl_803CAB38, i);
            if (s == 0 || fn_80291188(s, "") == 0) break;
            fn_801AC8BC(d->tex, a, s, i, 24.0f + d->x, d->y + k);
            fn_801AC7AC(d->tex, (fn_800CA3DC(s, -1, 1.0f) + 7) / 8, a, d->x, d->y + k);
        }
        if (d->v != 0) {
            oy = d->y + k;
            ox = 24.0f + d->x;
            fn_800D0AE4(0, d->v - *(s16*)(lbl_803CAB38 + 0xC2));
            s = fn_800D0864("MW_\x8E""c\x82""\xE8""");
            Cap(s, a, ox, oy);
            { int nn = fn_800CA3DC(s, -1, 1.0f); fn_801AC7AC(d->tex, (nn + 7) / 8, a, d->x, d->y + k); }
            k += 0x24;
        }
        if (*(s16*)(lbl_803CAB38 + 0x12) != 0) {
            fn_801AC7AC(d->tex, 0x10, a, d->x, d->y + k);
            fn_801AC9D8(d->tex, *(s16*)(lbl_803CAB38 + 0x12), a, 24.0f + d->x, d->y + k);
        }
        if (fn_80060728(lbl_803CAB38)->d == 2) fn_801ACB9C();
        fn_8007E7F4();
    }
}
}
