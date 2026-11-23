/* r20 wip, self-contained (wip/fn_801BDF20.cpp + declarations of fn_801BDF20.cpp via mkself.py), still `other`:
   one instruction short (215 of 216). The colour temporary and its by-value copy sit at 0x14/0xC (original 0x10/0x14), one `andc` of the sign clamp and one `li r7,0` are missing or placed differently, and the first colour byte load reads +3 where the original reads +0. */
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
void fn_801BDF20(const char* s, int col, int a, int top);

void fn_801BE2A4(void* proc);



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
extern void fn_8007E74C(void*, Rect16s*);
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
void fn_801BF50C(const char* name, int a, int b, int mode, f32 x, f32 y);


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
void fn_801BF80C(const char* name, void* vp, f32 x, f32 y);


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

extern void* fn_8011B77C(void*, void*);
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

void fn_801C0220(u8* d);


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
extern void fn_80107C80(void*, void*, int, int);
void fn_801C0E94(u8* d);


extern void* lbl_804CA4E8;
extern int fn_801284C4(void*);
void fn_801C2ED8(u8* d);



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
void fn_801C25D8(u8* o);


typedef struct Rn { u8 pad[0x10]; u8 a; } Rn;
typedef struct Rm { u8 pad[0x30]; Rn* n; } Rm;
extern void* fn_80127B68(void*);
extern const char* fn_80127B28(void*);
extern const char* fn_80118C44(void*);
extern int fn_80112F64(void*);
extern void* fn_80112FFC(void*, int);
extern int fn_8012CE54(void*);
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
void fn_801C4268(u8* d);


extern void* fn_80127A90(void*);
extern int fn_8011B8A4(void*);
extern void fn_801C3AB4(void*, f32, f32, f32);
extern const char* fn_8011A054(void*);
extern u8 lbl_803E7290[];
extern u8 lbl_803E72D8[];
typedef struct Sl { u8* p; u8 x4; u8 x5; } Sl;
extern void fn_801C336C(u8* d);
void fn_801C13D0(u8* d);



static inline u8 GetC5(s16 m,s16 q) { u8 r=1; if (m==q) r=0x27; return r;}
static inline void GetC3v(char* buf, char* name, u8* unit, int i, int& col) {
    if (fn_80291188(name, "-") == 0) { strcpy(buf, "--"); col=1; return; }
    strcpy(buf, name);
    { s16 m = *(s16*)(*(u8**)(unit + 0xF0) + (u8)i * 2 + 0xD0);
    s16 q = fn_8012C250(unit, (u8)i);
    col=GetC5(m,q);
    }}
void fn_801C2828(u8* o, int i, f32 x, f32 y);


}

/* ---- from rF_8017F400/wip/fn_801BDF20.cpp ---- */
extern "C" {


void fn_801BD420(int v, int plus, f32 x, f32 y) {
/*P*/
    int fl;
    f32 f;
    int a;
    char* s;
    void* arch;
    int len;
    s16 py;
    int px;
    int i;
    int n;
/*E*/
    char buf[8];
    if (v != 0) {
        n = fn_8028DB44(v);
        arch = lbl_804CB588;
        f = 1.0f + (f32)fn_80295940(6.2831855f * (fn_8017F990(0, 3000) / 3000.0f));
        if (plus) a = 127.0f * f; else a = 0xFF;
        fl = 0x11;
        if (plus) fl = 0x51;
        {
s16 sv = v > 0 ? 0 : 0x14;
s16 u0 = 0;
s16 ix = x;
s16 iy = y;
GXColor2 c = {a, a, a, 0xFF};
        Digit(arch, c, fl, ix, iy, u0, sv);
        }
        fn_80290DDC(buf, "%d", n);
        len = strlen(buf);
        {
        s16 sv = v > 0 ? 0 : 0x14;
        py = 4.0f + y;
        px = 10.0f + x;
        s = buf;
        for (i = 0; i < len; i++, s++) {
            GXColor2 c = {a, a, a, 0xFF};
            s16 ix = px;
            s16 u = (*s - 0x2F) * 13;
            Digit(arch, c, fl, ix, py, u, sv);
            px = (s16)(px + 0xB);
        }
        }
    }
}
}
