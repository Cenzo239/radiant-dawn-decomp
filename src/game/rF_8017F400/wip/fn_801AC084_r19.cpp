/* r19 wip, self-contained (parent fn_801ACD98.cpp helpers + fragment). fn_801AC084 is `other` by one scheduling
   line: the original keeps the "0" width in r25, computes w1*2 and w1+w0, and only then sign-extends the third width
   into r25 again; ours colours the third width differently and the extsh comes first. Fixed this round: the tile
   kind switch runs before fn_8007E154() (value held in a saved register). Decl orders and w1 reuse tried. */
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
void fn_801ABC34(void* tex, TerP* p, int x, int y);


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
extern void fn_8007E374(void*, int, int);
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
void fn_801ACB9C(void);

void fn_801ACD98(PrepD* d);

}

/* ---- from rF_8017F400/wip/fn_801ACD98.cpp ---- */
extern "C" {
/* fn_801AC084: 55 words, register colouring only (the tile switch and terrain lookup probably are inlines). Declarations as in ../fn_801ACD98.cpp. */

void fn_801AC084(TileD* d, void* tex, int a, f32 x, f32 y) {
/*P*/
    int cx;
    int cy;
    int t;
    void* ter;
    int nob;
    const char* s;
/*E*/
    char buf[0x100];
    s = 0;
    fn_8007E154();
    fn_8007E4E4(x, y, 105.0f, 1.0f);
    fn_8007E7DC((u8)a);
    fn_8007E164();
    { int tt;     switch (lbl_803CAB38[0x92]) {
    case 1: tt = 2; break;
    case 3: tt = 3; break;
    case 2: tt = 4; break;
    case 4: tt = 5; break;
    case 7: tt = 6; break;
    case 8: tt = 7; break;
    case 6: tt = 8; break;
    case 5: tt = 9; break;
    }
 fn_8007E154();
 fn_8007E374(tex, tt, 0x11); }
    fn_8007E164();
    fn_800800D4(1);
    fn_80080430(0.0f, 0.0f, 0.0f, 0.0f, 48.0f, 40.0f);
    fn_80080578(0);
    fn_80080308();
    SetScale(-1.0f);
    fn_8007E154();
    fn_8007E374(tex, 0, 0x11);
    fn_8007E164();
    fn_800800D4(1);
    fn_80080430(0.0f, 0.0f, 0.0f, 0.0f, 184.0f, 72.0f);
    fn_80080578(0);
    fn_80080308();
    SetScale(-1.0f);
    cx = (s8)(int)*(f32*)(lbl_803CAB38 + 0x934);
    cy = (s8)(int)*(f32*)(lbl_803CAB38 + 0x938);
    t = TerAt(cx, cy);
    if (t < 0) {
        s = "????";
        fn_801ABC34(tex, 0, 0x30, 0x23);
    } else {
        ter = fn_8010B240(t);
        nob = 1;
        switch (fn_8011D260(t)) {
        case 0x71:
        case 0xB1:
        case 0xB6:
            {
            TUnit* q;
            s = fn_8011D39C(ter);
            q = fn_80066130(lbl_803CB770, cx, cy, 4);
            if (q != 0 && q->x4 != 0) {
                nob = 0;
                FontReset();
                fn_80290DDC(buf, "%s %d", fn_800D0864("MTERR_VIT"), q->x4);
                fn_800CB3A8(0.75f, 0.0f, 0x60 - fn_800CA3DC(buf, -1, 0.75f) / 2, 0x23, 6, 0, 0, buf);
            }
            }
            break;
        case 0x99:
        case 0x9A:
            {
            TUnit* w;
            w = fn_80066DA8(lbl_803CB770, cx, cy, 7);
            if (w != 0) {
                s16 w0;
                s16 w1;
                int w12;
                s16 px;
                s16 w2;
                int su;
                nob = 0;
                FontReset();
                w0 = fn_800CA3DC(fn_800D0864("MP_POW"), -1, 0.75f);
                w1 = fn_800CA3DC("0", -1, 0.75f);
                {
                int r0 = fn_800CA3DC(fn_800D0864("MTERR_REST"), -1, 0.75f);
                w12 = w1 * 2;
                su = w1 + w0;
                w2 = r0;
                px = 0x60 - ((s16)(w12 + su + w2 + 0xC) >> 1);
                }
                fn_800CB3A8(0.75f, 0.0f, px, 0x23, 6, 0, 0, fn_800D0864("MP_POW"));
                px = px + w0 + 2;
                fn_80290DDC(buf, "%2d", (u8)fn_80110DA8(fn_80066D18(w)));
                fn_800CB3A8(0.75f, 0.0f, px, 0x23, 6, 0, 0, buf);
                px = px + w12 + 8;
                fn_800CB3A8(0.75f, 0.0f, px, 0x23, 6, 0, 0, fn_800D0864("MTERR_REST"));
                px = px + w2 + 2;
                fn_80290DDC(buf, "%d", w->x5);
                fn_800CB3A8(0.75f, 0.0f, px, 0x23, 6, 0, 0, buf);
                if (d->id[0] == 0) {
                    d->id[0] = fn_8010B228("IID_LONGARCH")->xE;
                    d->id[1] = fn_8010B228("IID_IRONARCH")->xE;
                    d->id[2] = fn_8010B228("IID_KILLERARCH")->xE;
                    d->id[3] = fn_8010B228("IID_ONAGER")->xE;
                    d->nm[0] = fn_800D0864("MT_\x83""A\x81""[\x83""`\x82""\xEB""");
                    d->nm[1] = fn_800D0864("MT_\x83""A\x81""[\x83""`\x82""\xA0""");
                    d->nm[2] = fn_800D0864("MT_\x83""A\x81""[\x83""`\x82""\xAB""");
                    d->nm[3] = fn_800D0864("MT_\x93""\x8A""\x90""\xCE""\x8A""\xED""");
                }
                {
                int i;
                for (i = 0; i < 4; i++) {
                    { u16 idv = d->id[i]; if (idv == w->x4) {
                        s = d->nm[i];
                        break;
                    } }
                }
                }
            } else {
                s = "\x83""V\x83""\x85""\x81""[\x83""^\x81""[\x96""\xA2""\x94""z\x92""u!";
            }
            }
            break;
        default:
            switch (fn_800A0644(cx, cy)) {
            case 9:
                s = fn_8011D39C(fn_8010B240(0x6B));
                break;
            case 0xD:
                s = fn_8011D39C(fn_8010B240(0x6C));
                break;
            case 0xE:
                s = fn_8011D39C(fn_8010B240(0x6E));
                break;
            case 0x2A:
                s = fn_8011D39C(fn_8010B240(0x6D));
                break;
            default:
                s = fn_8011D39C(ter);
                break;
            }
            {
            TUnit* q2 = fn_80066130(lbl_803CB770, cx, cy, 0x10);
            if (q2 != 0) s = fn_8011D39C(fn_8010B240(q2->x4));
            }
            break;
        }
        if (nob != 0) fn_801ABC34(tex, (TerP*)ter, 0x30, 0x23);
    }
    if (s != 0) {
        FontReset();
        fn_800CB3A8(0.8f, 0.0f, 0x60 - fn_800CA3DC(s, -1, 0.8f) / 2, 0xE, 1, 0, 0, s);
    }
    SetScale(1.0f);
    fn_8007E7F4();
}
}
