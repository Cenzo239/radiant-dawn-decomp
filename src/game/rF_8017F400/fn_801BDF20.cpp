#include "game/rF_8017F400/drawinl.h"
#pragma auto_inline off
#pragma pool_strings on
extern "C" {
void StringPool(const char** p) {
    p[0] = "EID_FLAG1";
    p[1] = "EID_ARROW1";
    p[2] = "EID_BIORHYTHM_P";
    p[3] = "SFX_SYS_INFO_WINDOW_OPEN1";
    p[4] = "";
    p[5] = "SFX_SYS_CANCEL1";
    p[6] = "SFX_SYS_INFO_WINDOW_SELECT1";
    p[7] = "SFX_SYS_INFO_WINDOW_UNIT_SELECT1";
    p[8] = "\x83""_\x83""~\x81""[";
    p[9] = "%d";
    p[10] = "%s%s %s%s %s%s %s%s ";
    p[11] = "MD_PAGE";
    p[12] = "MD_HLP";
    p[13] = "MD_RTN";
    p[14] = "MD_NXTCHA";
    p[15] = "MD_LNKCHA";
    p[16] = "MP_LV";
    p[17] = "MP_EX";
    p[18] = "\x81""|\x81""|";
    p[19] = "MP_HP";
    p[20] = "\x81""^";
    p[21] = "MP_ATK";
    p[22] = "MP_ATSPD";
    p[23] = "MP_HIT";
    p[24] = "MP_AVO";
    p[25] = "MP_CRIT";
    p[26] = "MP_CAVO";
    p[27] = "MP_RNG";
    p[28] = "MP_SFX";
    p[29] = "%d\x81""|%d";
    p[30] = "MP_STR";
    p[31] = "MP_MPOW";
    p[32] = "MP_TECH";
    p[33] = "MP_QUICK";
    p[34] = "MP_LUCK";
    p[35] = "MP_DEF";
    p[36] = "MP_MDEF";
    p[37] = "%3d >>";
    p[38] = "%3d";
    p[39] = "%2d";
    p[40] = "MP_BUILD";
    p[41] = "MP_WGT";
    p[42] = "MP_IDO";
    p[43] = "MP_DIV";
    p[44] = "MP_RACE";
    p[45] = "MRACE_HUM";
    p[46] = "MRACE_ANI";
    p[47] = "MRACE_???";
    p[48] = "MP_LINK";
    p[49] = "MP_COND";
    p[50] = "MP_POISON";
    p[51] = "%s %d";
    p[52] = "MP_SLEEP";
    p[53] = "MP_SILENCE";
    p[54] = "MP_SHOCK";
    p[55] = "MP_PARALYZE";
    p[56] = "MP_STONE";
    p[57] = "-";
    p[58] = "--";
    p[59] = "/";
    p[60] = "MD_SPT";
    p[61] = "+%d";
    p[62] = "MP_GUARD";
    p[63] = "MD_BOND_B";
    p[64] = "MD_BELONG";
    p[65] = "\x81""\x9A"" ";
    p[66] = "MD_DIRECTION";
    p[67] = "MD_COMMANDER";
    p[68] = "MD_BOND";
    p[69] = "MD_BIO_BEST";
    p[70] = "MD_BIO_WORST";
    p[71] = "MD_BIO_GOOD";
    p[72] = "MD_BIO_BAD";
    p[73] = "MD_BIO_NORMAL";
    p[74] = "SFX_SYS_INFO_WINDOW_MOVE1";
    p[75] = "_en";
    p[76] = "_w";
}
typedef struct C4 { union { u32 v; struct { u8 r, g, b, a; } c; } u; } C4;
struct C5 { union { u32 v; struct { u8 r, g, b, a; } c; } u; C5(u32 x) { u.v = x; } C5(u32 x, u8 a) { u.v = x; u.c.a = a; } };
extern void fn_80080940(C5, C5, C5, C5);
extern void* fn_800E48AC(void*, f32, f32, f32);
extern void fn_801BE4E4(u8*);
extern void fn_801BFB58(u8*);
extern const char* fn_800CF3A4(void);
extern const char* fn_800CEC24(void);
extern const char* fn_800CEDD4(void);
extern const char* fn_800CF470(void);
extern const char* fn_800CEB4C(void);

void fn_801BDF20(const char* s, int col, int a, int top) {
    if (s != 0) {
        if (a != 0) {
            fn_8007E154();
            fn_8007E174(0, 0x12);
            fn_8007E164();
            fn_800800D4(3);
            fn_80080348(0.0f, 390.0f, 0.0f, 0.0f);
            fn_80080368(608.0f, 420.0f, 0.0f, 0.0f);
            fn_80080940(C5(0), C5(0), C5(0, a), C5(0, a));
            fn_80080578(0);
            fn_80080308();
            fn_800800D4(3);
            fn_80080348(0.0f, 420.0f, 0.0f, 0.0f);
            fn_80080368(608.0f, 450.0f, 0.0f, 0.0f);
            fn_80080940(C5(0, a), C5(0, a), C5(0), C5(0));
            fn_80080578(0);
            fn_80080308();
        }
        SetScale(-1.0f);
        FontReset();
        {
        s16 x;
        if (top != 0) x = 0x18;
        else x = 0x130 - fn_800CA3DC(s, -1, 0.75f) / 2;
        fn_800800D4(5);
        fn_80080330(x, 412.0f);
        fn_80080508(*(GXColor2*)fn_800CD204(1));
        fn_800804F4(col);
        fn_80080A94(0.75f);
        fn_80080C24(s);
        fn_80080308();
        }
        SetScale(1.0f);
    }
}

void fn_801BE2A4(void* proc) {
    if (proc != 0) {
        u8* d = *(u8**)((u8*)proc + 0x30);
        f32 sl[2];
        *(u8*)(*(u8**)(*(u8**)(d + 0x68) + 0x30) + 0x10) = 0;
        {
        int i;
        for (i = 0; i < 2; i++) {
            f32* v = (f32*)(d + 0x58);
            v[2 + i] -= 0.15f;
            v[i] += v[2 + i];
            if (v[i] < 0.0f) { v[i] = 0.0f; v[2 + i] = 0.0f; }
            if (v[i] > 100.0f) v[i] = 100.0f;
            if (v[i] > 14.0f) sl[i] = 14.0f; else sl[i] = v[i];
        }
        }
        fn_800E48AC(*(void**)(d + 0x50), 18.0f - sl[0], 287.0f, 0.0f);
        fn_800E48AC(*(void**)(d + 0x54), 590.0f + sl[1], 287.0f, 0.0f);
        fn_801BE4E4(d);
        fn_801BFB58(d);
        fn_8007E154();
        fn_8007E7DC(*(u8*)(d + 0x14));
        fn_8007E4E4(0.0f, 0.0f, 160.0f, 1.0f);
        fn_8007E164();
        {
        char buf[0x80];
        fn_80290DDC(buf, "%s%s %s%s %s%s %s%s ", fn_800CF470(), fn_800D0864("MD_PAGE"), fn_800CEDD4(), fn_800D0864("MD_HLP"), fn_800CEC24(), fn_800D0864("MD_RTN"), fn_800CF3A4(), fn_800D0864("MD_NXTCHA"));
        if (*(int*)(*(u8**)(d + 0x44) + 0xF8) != 0) {
            fn_80291110(buf, fn_800CEB4C());
            fn_80291110(buf, fn_800D0864("MD_LNKCHA"));
        }
        fn_801BDF20(buf, 0xFF, 0, 0);
        }
        fn_8007E154();
        fn_8007E7DC(0xFF);
        fn_8007E164();
    }
}


typedef struct RNode { u8 pad[0x64]; GXColor2 col; } RNode;
typedef struct RMdl { u8 pad[0x30]; RNode* n; } RMdl;
typedef struct Rect16s { s16 x, y, w, h; } Rect16s;
extern u8 lbl_803C8E80[];
extern s8 lbl_804CB9D8;
extern Rect16s lbl_804CB9E0;
extern void* fn_80030CF4(void*);
extern void** fn_80030CBC(void*);
extern int fn_8012BA20(void*, void*);
extern void fn_801BE28C(void* p, void* arg);
#if TARGET_PC
extern FE10_PROTO void fn_8007E74C(ptr32<const void>, ptr32<const void>);
#else
extern void fn_8007E74C(void*, Rect16s*);
#endif
extern void fn_8007E7B4(void);
extern void fn_800C4DDC(int, int, int, void*);
extern void fn_80106F98(f32*, f32);
extern f32 fn_80127868(void*);
extern const char* fn_80118C44(void*);
extern const char* fn_80118F00(void*);
extern u32 fn_80126B0C(void*);
extern int fn_801237EC(void*);
extern u32 fn_801107C0(void*, void*);
extern u32 fn_801107A0(void*, void*);
extern void fn_801BF50C(const char* name, int a, int b, int mode, f32 x, f32 y);
extern void fn_801BF80C(const char* name, void* p, f32 x, f32 y);
void fn_801BF50C(const char* name, int a, int b, int mode, f32 x, f32 y);
extern void fn_801BF80C(const char* name, void* p, f32 x, f32 y);
static inline void TileC(int tile, GXColor2 c, u32 fl, f32 x, f32 y, f32 sc) {
    TexH** t = (TexH**)fn_80006A0C(lbl_804CB588, tile);
    f32 w = (*t)->x2;
    f32 h = (*t)->x0;
    DrawC(lbl_804CB588, tile, c, fl, x, y, w * sc, h * sc);
}
static inline void MdlCol(RMdl* m, GXColor2 c) { m->n->col = c; }
static inline void TextW(f32 x, f32 y, int col, const char* s) {
    TextCol(s, x, y, col);
}
static inline BOOL Chk(void* b) {
    BOOL r = 0;
    if (*fn_80030CBC(b) != 0 && fn_8012BA20(b, *fn_80030CBC(b)) != 0) r = 1;
    return r;
}
#define CX(s, cx) ((cx) - fn_800CA3DC(s, -1, 1.0f) / 2)

static inline GXColor2 mk7F(u8 a) { GXColor2 c = {0x7F, 0x7F, 0x7F, a}; return c; }
static inline GXColor2 G0a(void){ GXColor2 c = {0x04, 0xA4, 0x04, 0xFF}; return c; }
static inline GXColor2 G1a(void){ GXColor2 c = {0xC8, 0x18, 0x00, 0xFF}; return c; }
static inline GXColor2 G0b(void){ return G0a(); }
static inline GXColor2 G1b(void){ return G1a(); }
static inline GXColor2 G0(void){ return G0b(); }
static inline GXColor2 G1(void){ return G1b(); }

void fn_801BF50C(const char* name, int a, int b, int mode, f32 x, f32 y) {
    SetScale(-1.0f);
    FontReset();
    if (mode != 0) {
        const char* s = "\x81""|\x81""|";
        TextCol(s, x - 0.5f * fn_800CA3DC(s, -1, 1.0f), y, 8);
    } else {
        char buf[0x10];
        if (fn_80291188(name, "MP_RNG") == 0) {
            if (a == b) fn_80290DDC(buf, "%d", a);
            else fn_80290DDC(buf, "%d\x81""|%d", a, b);
            TextCol(buf, x - 0.5f * fn_800CA3DC(buf, -1, 1.0f), y, 8);
        } else {
            fn_80290DDC(buf, "%d", a);
            TextCol(buf, x - 0.5f * fn_800CA3DC(buf, -1, 1.0f), y, 8);
            SetScale(1.0f);
        }
    }
}

class IconFont {
public:
    u8 pad[0x44];
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void draw(int x, int y, int id);
};
extern u8 lbl_803E7290[];
static inline BOOL IconIf(u16* p, u32 m, int id, f32 x, f32 y) {
    if (*p & m) {
        ((IconFont*)lbl_803E7290)->draw((int)x, (int)y, id);
        return 1;
    }
    return 0;
}
void fn_801BF80C(const char* name, void* vp, f32 x, f32 y) {
    u16* p = (u16*)vp;
    f32 z = 0.0f;
    SetScale(-1.0f);
    FontReset();
    if (IconIf(p, 0x20, 0x34, x, y)) x += 28.0f;
    if (IconIf(p, 0x10, 0x35, x, y)) z += 28.0f;
    if (IconIf(p, 4, 0x36, x, y)) x += 28.0f;
    if (IconIf(p, 8, 0x37, x, y)) x += 28.0f;
    if (IconIf(p, 0x40, 0x39, x, y)) x += 28.0f;
    if (IconIf(p, 0x100, 0x3A, x, y)) x += 28.0f;
    if (IconIf(p, 2, 0x38, x, y)) x += 28.0f;
    if (IconIf(p, 0x80, 0x3B, x, y)) x += 28.0f;
    SetScale(2.0f);
}

extern void fn_801BD780(u8 a, f32 x, f32 y, f32 w, f32 h, f32 s);
extern void fn_801C0220(u8*);
extern void fn_801C0E94(u8*);
extern void fn_801C13D0(u8*);
extern void fn_801C25D8(u8*);
extern void fn_801C2ED8(u8*);
extern void fn_801C336C(u8*);
extern void fn_801C4268(u8*);
extern void fn_801C4F0C(u8*);
extern void fn_801C5874(u8*);
extern void* fn_8012E3A4(void*);
extern int fn_8012E9B4(void*, void*);
extern u32 fn_8012E8BC(void*, int);

#if TARGET_PC
extern FE10_PROTO ptr32<void> fn_8011B77C(void*, void*);
#else
extern void* fn_8011B77C(void*, void*);
#endif
extern void* lbl_804CA4EC;
extern int fn_8012386C(void*);
extern int fn_80123998(void*);
extern int fn_80123AC4(void*);
extern int fn_80123BF0(void*);
extern int fn_80123D1C(void*);
extern int fn_80123DC4(void*);
extern int fn_80123EF0(void*);
extern int fn_80122770(void*);
extern int fn_80122880(void*);
extern int fn_80122990(void*);
extern int fn_80122AA0(void*);
extern int fn_80122BB0(void*);
extern int fn_80122C20(void*);
extern int fn_80122D30(void*);
extern int fn_801224BC(void*);
extern int fn_8012250C(void*);
extern int fn_8012255C(void*);
extern int fn_801225AC(void*);
extern int fn_801225FC(void*);
extern int fn_8012264C(void*);
extern int fn_8012269C(void*);
extern void fn_801C0638(const char* name, s8 a, s8 b, s8 c, s8 e, void* p, f32 x, f32 y);
extern void fn_801BD420(int v, int plus, f32 x, f32 y);
#define UF(o) (*(s8*)(*(u8**)(u + 0xF0) + (o)))
void fn_801C0220(u8* d) {
    f32 x = *(f32*)(d + 0x24);
    f32 y = *(f32*)(d + 0x28);
    u8* u = *(u8**)(d + 0x44);
    void* p;
    SetScale(-1.0f);
    Hdr(0x19, 122.0f + x, 12.0f + y);
    p = fn_8011B77C(u + 0x12C, lbl_804CA4EC);
    {
    f32 cx = 26.0f + x;
    f32 cy = 30.0f + y;
    fn_801C0638("MP_STR", fn_801224BC(u), fn_80122770(u), fn_8012386C(u), UF(0x105), p, cx, cy);
    cy += 28.0f;
    fn_801C0638("MP_MPOW", fn_8012250C(u), fn_80122880(u), fn_80123998(u), UF(0x106), p, cx, cy);
    cy += 28.0f;
    fn_801C0638("MP_TECH", fn_8012255C(u), fn_80122990(u), fn_80123AC4(u), UF(0x107), p, cx, cy);
    cy += 28.0f;
    fn_801C0638("MP_QUICK", fn_801225AC(u), fn_80122AA0(u), fn_80123BF0(u), UF(0x108), p, cx, cy);
    cy += 28.0f;
    fn_801C0638("MP_LUCK", fn_801225FC(u), fn_80122BB0(u), fn_80123D1C(u), UF(0x109), p, cx, cy);
    cy += 28.0f;
    fn_801C0638("MP_DEF", fn_8012264C(u), fn_80122C20(u), fn_80123DC4(u), UF(0x10A), p, cx, cy);
    cy += 28.0f;
    fn_801C0638("MP_MDEF", fn_8012269C(u), fn_80122D30(u), fn_80123EF0(u), UF(0x10B), p, cx, cy);
    }
    SetScale(1.0f);
}

static inline void GaugeBg(f32 x, f32 y, f32 w) {
    Tile1(1, 0xFF, 0xF, 0, x, y, 1.0f);
    Tile1(1, 0xFF, 0x10, 0, 66.0f + x, y, 1.0f);
    Sprite3(1, 0xFF, 0x11, 0, 67.0f + x, y, w, 8.0f);
    Tile(1, 0xFF, 0x12, 0, 67.0f + x + w, y, 1.0f);
}

extern int fn_8028DB44(int);
extern int fn_8017F990(int, int);
extern double fn_80295940(double);
extern u32 strlen(const char*);
static inline void Digit(void* arch, GXColor2 c, int fl, s16 x, s16 y, s16 u, s16 v) {
    fn_801BC88C(arch, 0x22, c, fl, 0, x, y, x + 0xD, y + 0x14, u, v, 0xD + u, v + 0x14);
}

extern int fn_8012401C(void*);
extern int fn_80124144(void*);
extern int fn_80122E40(void*);
extern int fn_8012408C(void*);
extern int fn_801196F0(u8);
extern const char* fn_80119640(u8);
extern char* fn_800D0864_(const char*);
typedef struct UFl { u16 a : 3; u16 b : 3; u16 c : 3; u16 d : 3; u16 e : 3; u16 f : 1; } UFl;
#define ICONS ((IconFont*)lbl_803E7290)
static inline void Label(f32 x, f32 y, const char* key) {
    fn_800CB3A8(1.0f, 0.0f, 8.0f + x, y, 9, 1, 0, fn_800D0864(key));
}
static inline void IcoIf(u8* cl, u32 m, int id, f32& px, f32 cy) {
    if (*(u16*)(cl + 0xEE) & m) {
        ICONS->draw((int)px, (int)(1.0f + cy), id);
        px += 32.0f;
    }
}
static inline void Affin(f32 x, f32 y, int icon, const char* key, int n, char* b) {
    ICONS->draw((int)x, (int)(1.0f + y), icon);
    FontReset();
    fn_80290DDC(b, "%s %d", fn_800D0864(key), n);
    fn_800CB3A8(1.0f, 0.0f, 30.0f + x, y, 1, 1, 0, b);
}
static inline s8 GetW(u8* u) { s8 w = *(s8*)(u + 0x118); if (w == -1) return *(s8*)(*(u8**)(u + 0xEC) + 0xE1); return w; }

extern void* fn_8012B120(void*, void*);
#if TARGET_PC
extern FE10_PROTO void fn_80107C80(void*, ptr32<const void>, int, int);
#else
extern void fn_80107C80(void*, void*, int, int);
#endif
void fn_801C0E94(u8* d) {
    f32 q;
    f32 cx;
    f32 cy;
    f32 lx;
    f32 ly;
    f32 x;
    int i;
    u8* u;
    int j;
    f32 y;
    u8* it;
    f32 iy;
    x = *(f32*)(d + 0x24);
    y = *(f32*)(d + 0x28);
    u = *(u8**)(d + 0x44);
    SetScale(-1.0f);
    cx = 404.0f + x;
    cy = 12.0f + y;
    Hdr(0x18, cx, cy);
    SetScale(-1.0f);
    lx = 280.0f + x;
    ly = 30.0f + y;
    q = 213.0f;
    for (i = 0; i < 7; i++) {
        Bar(0xA0, 18.0f + lx, 18.0f + ly, q, 9);
        ly += 28.0f;
    }
    SetScale(-1.0f);
    it = u + 0x1BC;
    iy = 30.0f + y;
    for (j = 0; j < 7; j++, it += 0x28) {
        if (*(void**)it != 0) {
            fn_80107C80(it, fn_8012B120(u, *(void**)it), (int)lx, (int)iy);
            iy += 28.0f;
        }
    }
    SetScale(3.0f);
}

extern void* lbl_804CA4E8;
extern int fn_801284C4(void*);
void fn_801C2ED8(u8* d) {
    f32 by;
    f32 bx;
    u8* u;
    f32 cx;
    f32 cy;
    f32 x;
    f32 y;
    f32 bw;
    int tile;
    char buf[0x10];
    u = *(u8**)(d + 0x44);
    x = *(f32*)(d + 0x24);
    y = *(f32*)(d + 0x28);
    if (fn_8011B77C(u + 0x12C, lbl_804CA4E8) == 0) return;
    SetScale(-1.0f);
    Hdr(0x1B, 333.0f + x, 205.0f + y);
    fn_8011B77C(u + 0x12C, lbl_804CA4EC);
    cx = 450.0f + x;
    cy = 209.0f + y;
    bw = 85.0f * ((s8)fn_801284C4(u) / 30.0f);
    Tile1(1, 0xFF, 0x14, 0, cx, cy, 1.0f);
    SetScale(-1.0f);
    { void* z = fn_8011B77C(u + 0x12C, lbl_804CA4EC); tile = 0x16; if (z == 0) tile = 0x15; }
    Sprite3(1, 0xFF, tile, 0, 11.0f + cx, 5.0f + cy, bw, 8.0f);
    FontReset();
    fn_80290DDC(buf, "%d", (s8)fn_801284C4(u));
    fn_800CB3A8(1.0f, 0.0f, 431.0f + x - 0.5f * fn_800CA3DC(buf, -1, 1.0f), 203.0f + y, 1, 1, 0, buf);
    SetScale(2.0f);
}


extern void fn_801BE4E4(u8* d);

extern void fn_801BFB58(u8* d);

extern void fn_801C0638(const char* name, s8 a, s8 b, s8 c, s8 e, void* p, f32 x, f32 y);

extern void fn_801BD420(int v, int plus, f32 x, f32 y);

extern void fn_801C13D0(u8* d);

extern u8 lbl_803E7290[];
extern int fn_8012C250(void*, u8);
extern char* fn_801113DC(s16);
extern int fn_80111488(s16);
extern int fn_80111230(s16);
extern u8 fn_800CEABC(u8);
extern const char* fn_8010FECC(u8, int);

static inline int GetC(char* buf, char* name, u8* unit, int i) {
    int r = 1;
    if (fn_80291188(name, "-") == 0) {
        strcpy(buf, "--");
        return 1;
    }
    strcpy(buf, name);
    {
    s16 m = *(s16*)(*(u8**)(unit + 0xF0) + (u8)i * 2 + 0xD0);
    s16 q = fn_8012C250(unit, (u8)i);
    if (m == q) r = 0x27;
    return r;
    }
}
extern void fn_801C2828(u8* o, int i, f32 x, f32 y);

void fn_801C25D8(u8* o) {
    f32 x = *(f32*)(o + 0x24);
    f32 y = *(f32*)(o + 0x28);
    SetScale(-1.0f);
    Hdr(0x1A, 398.0f + x, 12.0f + y);
    {
    int k, i;
    f32 px, py;
    for (i = 0, k = 0; i < 12; i++, k += 0x1C) {
        if (i <= 5) { px = 248.0f + x; py = 30.0f + y + k; }
        else { px = 410.0f + x; py = 30.0f + y + (k - 0xA8); }
        fn_801C2828(o, i, px, py);
    }
    }
    SetScale(1.0f);
}

typedef struct Rn { u8 pad[0x10]; u8 a; } Rn;
typedef struct Rm { u8 pad[0x30]; Rn* n; } Rm;
extern void* fn_80127B68(void*);
extern const char* fn_80127B28(void*);
extern const char* fn_80118C44(void*);
extern int fn_80112F64(void*);
extern void* fn_80112FFC(void*, int);
#if TARGET_PC
extern FE10_PROTO struct Unit * fn_8012CE54(void*);
#else
extern int fn_8012CE54(void*);
#endif
extern void fn_80106F98(f32*, f32);
extern f32 fn_80127868(void*);
extern f32 fn_801071C4(void*, s16);
extern void fn_801BE154(const GXColor2&, f32, f32, f32, f32);
extern int lbl_804CB9EC;

static inline void Pair(const char* label, const char* val, f32 x, f32 y) {
    SetScale(-1.0f);
    if (label != 0) fn_800CB3A8(1.0f, 0.0f, 6.0f + x, y, 9, 1, 0, fn_800D0864(label));
    if (val != 0) fn_800CB3A8(1.0f, 0.0f, 110.0f + x, y, 1, 1, 0, fn_800D0864(val));
    SetScale(1.0f);
}
extern void fn_801C4F0C(u8* d);

static inline u8 IsTwo(int i) { return i == 2; }
extern void fn_801C5874(u8* d);

extern volatile u32 lbl_804CB700;
extern u8 lbl_803C8E80[];
extern void fn_8002FC64(void*, void*, int);
extern s8 fn_80112CD4(void*, int);
#pragma push
static inline void Row(const char* lab, const char* key, int v, f32 x, f32 y) {
    char buf[0x10];
    int col;
    fn_800CB3A8(1.0f, 0.0f, x, y, 1, 1, 0, fn_800D0864(lab));
    fn_800CB3A8(1.0f, 0.0f, 107.0f + x, y, 9, 1, 0, fn_800D0864(key));
    if (v > 0) {
        fn_80290DDC(buf, "+%d", v);
        col = 4;
    } else {
        fn_80290DDC(buf, "%d", v);
        col = 1;
    }
    fn_800CB3A8(1.0f, 0.0f, 172.0f + x - fn_800CA3DC(buf, -1, 1.0f) / 2, y, col, 1, 0, buf);
}
#pragma pop
typedef struct Mods { u32 a; s8 v[6]; u8 pad[6]; } Mods;
void fn_801C4268(u8* d) {
    u8* u;
    u32 m;
    s8 c;
    int k;
    int i;
    f32 q;
    f32 tx;
    f32 ty;
    f32 x;
    f32 y;
    Mods s;
    m = lbl_804CB700 & 0x30000;
    x = *(f32*)(d + 0x24);
    y = *(f32*)(d + 0x28);
    u = *(u8**)(d + 0x44);
    s.v[5] = 0; s.v[4] = 0; s.v[3] = 0; s.v[2] = 0; s.v[1] = 0; s.v[0] = 0;
    lbl_804CB700 = lbl_804CB700 & ~m;
    fn_8002FC64(lbl_803C8E80, &s, *(int*)(d + 4) != 0);
    c = fn_80112CD4(u, *(int*)(d + 4) != 0);
    lbl_804CB700 |= m;
    SetScale(-1.0f);
    Hdr(0x1E, 461.0f + x, 62.0f + y);
    q = 191.0f;
    for (i = 0, k = 0; i < 5; i++, k += 0x1C) {
        Bar(0xA0, 361.0f + x, 101.0f + y + k, q, 9);
    }
    SetScale(-1.0f);
    tx = 367.0f + x;
    ty = 83.0f + y;
    Row("MD_SPT", "MP_ATK", s.v[0], tx, ty);
    ty += 28.0f;
    Row("MD_SPT", "MP_GUARD", s.v[1], tx, ty);
    ty += 28.0f;
    Row("MD_SPT", "MP_HIT", s.v[2], tx, ty);
    ty += 28.0f;
    Row("MD_SPT", "MP_AVO", s.v[3], tx, ty);
    ty += 28.0f;
    Row("MD_BOND_B", "MP_CRIT", c, tx, ty);
    SetScale(2.0f);
}

#if TARGET_PC
extern FE10_PROTO ptr32<void> fn_80127A90(void*);
#else
extern void* fn_80127A90(void*);
#endif
extern int fn_8011B8A4(void*);
#if TARGET_PC
extern FE10_PROTO void fn_801C3AB4(ptr32<const void>, f32, f32, f32);
#else
extern void fn_801C3AB4(void*, f32, f32, f32);
#endif
extern const char* fn_8011A054(void*);
extern u8 lbl_803E7290[];
extern u8 lbl_803E72D8[];
typedef struct Sl { u8* p; u8 x4; u8 x5; } Sl;
extern void fn_801C336C(u8* d);

void fn_801C13D0(u8* d) {
    f32 cy;
    f32 q;
    f32 ax;
    u8* cl;
    f32 cx;
    f32 lx;
    f32 px;
    f32 ly;
    f32 x;
    f32 y;
    int i;
    f32 ofs;
    u8* u;
    s8 wep;
    UFl* fl;
    char buf[0x18];
    u = *(u8**)(d + 0x44);
    x = *(f32*)(d + 0x24);
    y = *(f32*)(d + 0x28);
    cl = *(u8**)(u + 0xF0);
    ofs = 10.0f;
    SetScale(-1.0f);
    Hdr(0x1F, 130.0f + x, 12.0f + y);
    SetScale(-1.0f);
    {
    lx = 26.0f + x;
    ly = 30.0f + y;
    q = 183.0f;
    for (i = 0; i < 7; i++) {
        Bar(0xA0, lx, 18.0f + ly, q, 9);
        ly += 28.0f;
    }
    }
    SetScale(-1.0f);
    FontReset();
    {
    cx = 26.0f + x;
    cy = 30.0f + y;
    fn_80290DDC(buf, "%2d", (s8)fn_8012401C(u));
    Label(cx, cy, "MP_BUILD");
    fn_800CB3A8(1.0f, 0.0f, 68.0f + cx + ofs - 0.5f * fn_800CA3DC(buf, -1, 1.0f), cy, 1, 1, 0, buf);
    cy += 28.0f;
    fn_80290DDC(buf, "%2d", (s8)fn_80124144(u));
    Label(cx, cy, "MP_WGT");
    fn_800CB3A8(1.0f, 0.0f, 68.0f + cx + ofs - 0.5f * fn_800CA3DC(buf, -1, 1.0f), cy, 1, 1, 0, buf);
    cy += 28.0f;
    fn_80290DDC(buf, "%2d", (s8)fn_80122E40(u));
    Label(cx, cy, "MP_IDO");
    fn_800CB3A8(1.0f, 0.0f, 68.0f + cx + ofs - 0.5f * fn_800CA3DC(buf, -1, 1.0f), cy, 1, 1, 0, buf);
    fn_801BD420((s8)fn_8012408C(u) - (s8)fn_80122E40(u), 0, 82.0f + cx + ofs, cy);
    cy += 28.0f;
    FontReset();
    Label(cx, cy, "MP_DIV");
    {
    wep = GetW(u);
    ICONS->draw((int)(56.0f + cx + ofs), (int)(1.0f + cy), fn_801196F0(wep));
    FontReset();
    fn_800CB3A8(1.0f, 0.0f, 86.0f + cx + ofs, cy, 1, 1, 0, fn_80119640(wep));
    }
    cy += 28.0f;
    Label(cx, cy, "MP_RACE");
    if (*(u16*)(cl + 0xEE) & 0x20) strcpy(buf, fn_800D0864("MRACE_HUM"));
    else if (*(u16*)(cl + 0xEE) & 0x10) strcpy(buf, fn_800D0864("MRACE_ANI"));
    else strcpy(buf, fn_800D0864("MRACE_???"));
    fn_800CB3A8(1.0f, 0.0f, 56.0f + cx + ofs, cy, 1, 1, 0, buf);
    {
    px = 120.0f + cx + ofs;
    IcoIf(cl, 4, 0x36, px, cy);
    IcoIf(cl, 8, 0x37, px, cy);
    IcoIf(cl, 0x40, 0x39, px, cy);
    IcoIf(cl, 0x100, 0x3A, px, cy);
    IcoIf(cl, 2, 0x38, px, cy);
    IcoIf(cl, 0x80, 0x3B, px, cy);
    }
    cy += 28.0f;
    FontReset();
    Label(cx, cy, "MP_LINK");
    if (*(u8**)(u + 0xF8) != 0) {
        strcpy(buf, fn_80118C44(*(void**)(*(u8**)(u + 0xF8) + 0xEC)));
        fn_800CB3A8(1.0f, 0.0f, 56.0f + cx + ofs, cy, 1, 1, 0, buf);
    }
    cy += 28.0f;
    Label(cx, cy, "MP_COND");
    {
    ax = 56.0f + cx + ofs;
    fl = (UFl*)(u + 0x110);
    if ((int)fl->a > 0) { int n = fl->a;
        char b[0x40];
        Affin(ax, cy, 0x1A, "MP_POISON", n, b);
    } else if ((int)fl->c > 0) { int n = fl->c;
        char b[0x40];
        Affin(ax, cy, 0x1B, "MP_SLEEP", n, b);
    } else if ((int)fl->d > 0) { int n = fl->d;
        char b[0x40];
        Affin(ax, cy, 0x1C, "MP_SILENCE", n, b);
    } else if ((int)fl->b > 0) { int n = fl->b;
        char b[0x40];
        Affin(ax, cy, 0x1D, "MP_SHOCK", n, b);
    } else if ((int)fl->e > 0) { int n = fl->e;
        char b[0x40];
        Affin(ax, cy, 0x1E, "MP_PARALYZE", n, b);
    } else if ((int)fl->f > 0) { int n = fl->f;
        char b[0x40];
        Affin(ax, cy, 0x1F, "MP_STONE", n, b);
    }
    }
    }
}


static inline u8 GetC5(s16 m,s16 q) { u8 r=1; if (m==q) r=0x27; return r;}
static inline void GetC3v(char* buf, char* name, u8* unit, int i, int& col) {
    if (fn_80291188(name, "-") == 0) { strcpy(buf, "--"); col=1; return; }
    strcpy(buf, name);
    { s16 m = *(s16*)(*(u8**)(unit + 0xF0) + (u8)i * 2 + 0xD0);
    s16 q = fn_8012C250(unit, (u8)i);
    col=GetC5(m,q);
    }}
void fn_801C2828(u8* o, int i, f32 x, f32 y) {
    f32 bx;
    f32 by;
    u8* unit;
    f32 v;
    char* name;
    f32 d;
    f32 r;
    int col;
    const char* s;
    f32 bw;
    char buf[8];
    unit = *(u8**)(o + 0x44);
    SetScale(-1.0f);
    Tile(1, 0xFF, 0x13, 0, x, 16.0f + y, 1.0f);
    SetScale(-1.0f);
    v = (s16)fn_8012C250(unit, (u8)i);
    name = fn_801113DC(v);
    d = (s16)fn_80111488(v) - (s16)fn_80111230(v);
    if (fn_80291188(name, "-") == 0) {
        r = 0.0f;
    } else {
        r = v - (s16)fn_80111230(v);
    }
    if (r > 0.0f) {
        bx = 73.0f + x;
        by = 18.0f + y;
        bw = 71.0f * r / d - 6.0f;
        Tile(1, 0xFF, 0xC, 0, bx, by, 1.0f);
        Sprite3(1, 0xFF, 0xD, 0, 3.0f + bx, by, bw, 8.0f);
        Tile(1, 0xFF, 0xE, 0, 3.0f + bx + bw, by, 1.0f);
    }
    SetScale(-1.0f);
    col = fn_800CEABC((u8)i);
    s = fn_8010FECC((u8)i, 0);
    ((IconFont*)lbl_803E7290)->draw((int)(4.0f + x), (int)y, col);
    FontReset();
    fn_800CB3A8(1.0f, 0.0f, 34.0f + x, y, 9, 1, 0, s);
    GetC3v(buf, name, unit, i, col);
    fn_800CB3A8(1.0f, 0.0f, 119.0f + x - fn_800CA3DC(buf, -1, 1.0f) / 2, y, (u8)col, 1, 0, buf);
    SetScale(3.0f);
}

}
