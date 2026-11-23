#ifndef RC2_8005259C_DECLS_H
#define RC2_8005259C_DECLS_H
#include "game/rC2_8005259C/types.h"
#include "game/rC2_8005259C/labels.h"

extern u8 lbl_804CB3F8;
extern u8 lbl_804CB550;

/* 0x68-byte screen object created by the fn_8005B508 family (base vtable lbl_8038CB1C,
 * derived vtable lbl_8038C1C0). Constructed inline after operator new (fn_80079150). */
typedef struct Spr {
    void* vt;       /* 0x00 */
    int f4;         /* 0x04 */
    s16 f8;         /* 0x08 */
    s16 fa;
    s16 fc;
    s16 fe;
    s16 f10;
    s16 f12;
    s16 f14;
    s16 f16;
    s16 f18;
    s16 f1a;
    s16 f1c;
    s16 f1e;
    s16 f20;
    u8 f22;
    u8 f23;
    u8 f24;
    u8 f25;
    s16 f26;
    s16 f28;
    u8 pad2a[2];
    f32 f2c;
    f32 f30;
    f32 f34;
    u32 f38;
    int f3c;
    int f40;
    int f44;
    int f48;
    int f4c;
    u8 f50;
    u8 pad51[3];
    f32 f54;
    s16 f58;
    s16 f5a;
    s16 f5c;
    s16 f5e;
    int f60;
    const char* f64;
} Spr;

extern u8 lbl_8038CB1C[44];
extern u8 lbl_8038C1C0[48];
extern char lbl_80361F9C[316];

/* Global game state at lbl_803CAB38 (0x988 bytes; region rC calls it FlagTable). */
typedef struct GDPair { u8 a; u8 b; } GDPair;
typedef struct GameData {
    u8 pad0[0x10 - 0x0];
    u8 b10; /* 0x10 chapter/map id? */
    u8 b11; /* 0x11 */
    u8 pad12[0x91 - 0x12];
    u8 b91; /* 0x91 */
    u8 b92; /* 0x92 */
    u8 pad93[0x9c - 0x93];
    u8 b9c; /* 0x9C */
    u8 b9d; /* 0x9D */
    u8 pad9e[0xa0 - 0x9e];
    u64 t_a0; /* 0xA0 play time counters (u64) */
    u64 t_a8; /* 0xA8 */
    u8 padb0[0x104 - 0xb0];
    u32 w104[12]; /* 0x104 */
    u8 pad134[0x934 - 0x134];
    f32 f934; /* 0x934 */
    f32 f938; /* 0x938 */
    u8 pad93c[0x944 - 0x93c];
    f32 f944; /* 0x944 */
    f32 f948; /* 0x948 */
    u8 pad94c[0x954 - 0x94c];
    s8 n954; /* 0x954 number of pairs */
    GDPair p955[25]; /* 0x955 */
    u8 pad987[0x988 - 0x987];
} GameData;
extern GameData lbl_803CAB38;

typedef struct NamedThing {
    const char* name;
    u8 pad4[0x89 - 4];
    u8 b89;           /* 0x89 */
    u8 pad8a[0xa8 - 0x8a];
    u8 aA8[4];        /* 0xA8 */
    u8 aAC[4];        /* 0xAC */
} NamedThing;

/* Rank stats (same object as GameData, viewed by the end-of-chapter scoring functions). */
typedef struct RankData {
    u8 pad0[0x10];
    u8 b10;
    u8 b11;
    s16 h12;
    u8 pad14[4];
    int w18;
    int w1c;
    int w20;
} RankData;

extern u8 lbl_8037DD18[48];
extern u8 lbl_8037DE64[188];
extern u8 lbl_8037DF90[184];
extern u8 lbl_8037E048[176];

/* Unit as seen by this region: same layout as Unit with more named fields. */
typedef struct Unit2 {
    u8 pad0[0xe4];
    struct Unit2* next4; /* 0x0E4 */
    struct Unit2* next;  /* 0x0E8 */
    struct UnitPers* pers; /* 0x0EC */
    u8 padf0[4];
    struct UnitSub* f4;  /* 0x0F4 */
    struct Unit2* f8;    /* 0x0F8 */
    u8 padfc[0x102 - 0xfc];
    s8 x102;
    s8 y103;
    u8 pad104[0x108 - 0x104];
    u64 flags108;        /* 0x108 (low word = Unit.flags10c) */
    u8 pad110[0x12c - 0x110];
    u8 x12c[0x382 - 0x12c]; /* 0x12C */
    u16 h382;
    u8 pad384[0x3f0 - 0x384];
    struct Unit2* link3f0; /* 0x3F0 */
} Unit2;
typedef struct UnitPers {
    u8 pad0[0xdc];
    int wdc;
} UnitPers;

/* Options returned by fn_80060728. */
typedef struct Opt44 {
    u32 pad0 : 18;
    u32 b18 : 1;
    u32 pad0b : 13;
    u32 pad4 : 2;
    u32 c2 : 2;
    u32 pad4b : 28;
} Opt44;

/* lbl_803C8E80 (0x1648 bytes). */
typedef struct BigState {
    u8 pad0[0x3f0];
    struct Unit2* p3f0;
    u8 pad3f4[0x448 - 0x3f4];
    s16 h448;
    u8 pad44a[0x44e - 0x44a];
    s16 h44e;
    u8 pad450[0x454 - 0x450];
    s16 h454;
    u8 pad456[0x15ec - 0x456];
    u32 f15ec;
    u8 pad15f0[0x1648 - 0x15f0];
} BigState;
extern BigState lbl_803C8E80;

/* Generic object with a vptr at +4. */
class Obj4 {
public:
    u32 f0;
    VPAD(0) VPAD(1) VPAD(2) VPAD(3) VPAD(4) VPAD(5) VPAD(6) VPAD(7)
    VPAD(8) VPAD(9) VPAD(10) VPAD(11) VPAD(12) VPAD(13) VPAD(14) VPAD(15)
    VPAD(16) VPAD(17)
    virtual s16 v50();                       /* 0x50 */
    VPAD(19) VPAD(20) VPAD(21) VPAD(22) VPAD(23)
    VPAD(24) VPAD(25) VPAD(26) VPAD(27) VPAD(28) VPAD(29) VPAD(30) VPAD(31)
    VPAD(32) VPAD(33)
    virtual void v90();                      /* 0x90 */
};

typedef struct Entry16 {
    u8 b0;
    u8 pad1;
    u16 h2;
    u32 w4;
    u8 pad8[8];
} Entry16;

typedef struct NameTable {
    u8 pad0[0x30];
    char a30[3][12];   /* 0x30 */
    char a54[3][12];   /* 0x54 */
    u8 pad78[0xb8 - 0x78];
    s16 hb8;
    s16 hba;
} NameTable;

/* Script interpreter context passed to script-command handlers: +4 is the command pointer. */
typedef struct ScriptCtx {
    u32 f0;
    u32* pc;           /* 0x04 */
} ScriptCtx;

extern u32 lbl_804CB700;
extern u8 lbl_8037E248[1352];
extern u8 lbl_803CB770[16];
extern u8 lbl_803EC898[88167];
typedef struct Word { int i0; u8 pad[0x1204]; } Word;
extern Word lbl_803E7320;

extern u8 lbl_8041EB20[296];

typedef struct Entry16b {
    u8 b0;
    u8 pad1;
    u16 h2;
    u32 w4;
    s16 h8;
    u8 pada[2];
    u32 wc;
} Entry16b;

typedef struct Sys40 {
    u8 pad0[0x40];
    u32 w40;
} Sys40;

typedef struct PairList {
    u8 b0;
    u8 b1;
} PairList;

extern char lbl_80361B8C[180];
extern u8 lbl_804CB728;
extern char lbl_803620E4[116];
extern void* lbl_804CB554;

extern u8 lbl_8037F7B0[48];
extern u8 lbl_804CB558[8];

typedef struct Vec3 { f32 x, y, z; } Vec3;

typedef struct Obj40 {
    u8 pad0[0x40];
    int state40;
} Obj40;

/* Menu command object with a vptr at +0: v58 returns the command id, vC the label. */
class Cmd0 {
public:
    VPAD(0)
    virtual const char* vC();                /* 0x0C */
    VPAD(2) VPAD(3) VPAD(4) VPAD(5) VPAD(6) VPAD(7)
    VPAD(8) VPAD(9) VPAD(10) VPAD(11) VPAD(12) VPAD(13) VPAD(14) VPAD(15)
    VPAD(16) VPAD(17) VPAD(18) VPAD(19)
    virtual int v58();                       /* 0x58 */
};

typedef struct ObjB4 {
    u32 f0;
    u8 b4;
} ObjB4;

extern u8 lbl_8037E0F8[16];
extern u8* lbl_804CB814;
typedef struct Color4 { u8 r, g, b, a; } Color4;

extern u8 lbl_804CB818;
extern void* lbl_804CA4D8;

typedef struct MenuBox {
    u8 pad0[0x30];
    s16 x;
    s16 y;
} MenuBox;

typedef struct Obj4CB2 {
    u8 pad0[0x4c];
    void* p4c;
} Obj4CB2;

/* Lazily built statics used by the main-menu effect callbacks. Lazy2 is a
 * derived object: the dead store of the base vtable lbl_80383F28 is kept because
 * the compiler keeps it too. */
typedef struct Lazy2 { void* a; void* b; } Lazy2;
extern u8 lbl_80383F28[];
#define LAZY1(g, p, v) if (!g) { g = 1; p = v; }
#define LAZY2(g, o, v0, v1) if (!g) { o.b = lbl_80383F28; o.a = v0; o.b = v1; g = 1; }


/* Help popup position: entry position plus the owner's origin. */
#define HELP_XY() \
        s16 ex = e->x; \
        int ox = m->owner->v60(); \
        f32 x = ox + ex; \
        s16 ey = e->y; \
        int oy = m->owner->v64(); \
        f32 y = oy + ey

extern "C" {
void* fn_80079150(u32 size);
Spr* fn_801E5640(void* proc, int id, int n);
void fn_801E5448(void* proc, Spr* s);
void fn_801E5558(void* proc, Spr* s, int n);
void fn_801FBE14(void* proc);
void fn_80083B78(void* proc);
void fn_80242850(void* proc);
void fn_80204348(void* proc);
void fn_80234888(void* proc);
#if TARGET_PC
FE10_PROTO void fn_80221EBC(ptr32<const void>);
FE10_PROTO void fn_80228D38(ptr32<const void>);
FE10_PROTO void fn_80216744(ptr32<const void>);
#else
void fn_80221EBC(void* proc);
void fn_80228D38(void* proc);
void fn_80216744(void* proc);
#endif
void fn_802889AC(void* proc);
void fn_80266E3C(void* proc);
void fn_80266F24(void* proc);
NamedThing* fn_8010B094(u8 id);
NamedThing* fn_8006074C(GameData* g);
int fn_80290D04(char* buf, u32 n, const char* fmt, ...);
void fn_80205778(void* proc, const char* s);
void fn_80205AE4(void* proc, const char* s);
int fn_801059B0(void* p);
void fn_8004559C(UnitCmdState* s, int n);
void fn_80068A58(void);
void fn_80089388(int n, void* p);
int fn_80054D98(void* p, u8 n);
void fn_8006CCAC(void* a, void* b, u8 c, void* d, int e);
void fn_8002BCC4(BigState* b);
void* fn_80081194(void* script, void* parent);
void fn_800893AC(void* p);
void fn_8008939C(void* p);
void fn_801E5880(void* p);
#if TARGET_PC
FE10_PROTO void fn_801C6D2C(ptr32<const void>, void* a, int b, ptr32<const void>, ptr32<const void>);
#else
void fn_801C6D2C(Unit* u, void* a, int b, void (*cb)(void*), void* c);
#endif
void fn_80062380(GameData* g, void* p);
Sys40* fn_8024BCA0(void);
void fn_80060D68(GameData* g);
void fn_802910CC(char* d, const char* s, u32 n);
void fn_8005D624(void* p);
int fn_80068D74(void);
void fn_80131DE4(void);
void fn_80133034(void);
void fn_80083DC4(void* p, int n);
void fn_800466B4(UnitCmdState* s, void* p);
Word* fn_800CFD3C(Word* w);
u8* fn_800CFB0C(void* p);
#if TARGET_PC
FE10_PROTO void fn_801038D0(void* p, p32arg);
#else
void fn_801038D0(void* p, int a);
#endif
void fn_801288D4(void* p);
#if TARGET_PC
FE10_PROTO void fn_800665E4(void* m, ptr32<const void>);
#else
void fn_800665E4(void* m, void* p);
#endif
Obj40* fn_80083B84(void* cls);
void fn_80081A90(void* p);
void fn_801B5D30(void);
void fn_80114D00(void* p);
#if TARGET_PC
FE10_PROTO void fn_801484B4(p32arg);
#else
void fn_801484B4(int n);
#endif
void fn_801A7B20(void* p);
void* fn_801E5890(void* p);
void fn_80185720(void* p);
void fn_801911D4(void* p);
void* fn_800CD4A4(int n);
void fn_800CD514(void* p);
u8 fn_801E71B4(void* p);
int fn_801A2224(void* p);
#if TARGET_PC
FE10_PROTO struct Sc * fn_8013B9A8(void);
#else
int fn_8013B9A8(void);
#endif
void fn_80138FF8(void);
void fn_8012FF30(void);
u8 fn_801E7164(void* p);
u8 fn_801E7114(void* p);
u8 fn_801E70C4(void* p);
void fn_80140864(s8 x, s8 y);
void fn_80140880(void);
void fn_80044E3C(void* p);
void fn_80193014(void);
void fn_800310E4(const char* s, int a, int b, int c);
int fn_8012FCD8(int n);
void fn_800262D8(void* p);
void fn_80108E20(void* p, u8 n);
#if TARGET_PC
FE10_PROTO void fn_80102928(void* p, int a, int b, int c, p32arg);
#else
void fn_80102928(void* p, int a, int b, int c, int d);
#endif
void fn_80126EB0(void* p, s8 x, s8 y);
void fn_800F39DC(void* p);
void* fn_801FBEB0(void* p);
void fn_801E5860(void* p);
void* fn_800D4228(const char* s);
u8* fn_801DFF2C(const char* s);
void fn_800106AC(int n, void (*cb)(void*), void* p);
void fn_800599C4(void* p);
void fn_8019F85C(void* p);
void fn_801BA544(void (*cb)(void*), void* p);
void fn_8005D680(void* p, void* u);
void* fn_8024BC94(void);
int fn_802450BC(void* p);
int fn_8006041C(void* p);
int fn_802912A4(const char* a, const char* b, u32 n);
u64 fn_8017FA24(void);
u8 fn_80092E10(NamedThing* t);
f32 fn_801142F0(void* map, f32 x, f32 y);
void* fn_80068E00(void);
void fn_8013B974(void* p);
#if TARGET_PC
FE10_PROTO void* fn_800811E4(void* script, void* p);
#else
void fn_800811E4(void* script, void* p);
#endif
void fn_8010E7F4(void* p, int n);
Unit* fn_800677E4(void);
void fn_800679EC(void);
s8 fn_8012408C(Unit* u);
void fn_8014083C(s8 x, s8 y, s8 z);
void fn_80122460(Unit* u);
void fn_80026CD8(BigState* b, u8* p, int n);
void fn_8002C170(BigState* b);
void fn_800E990C(void* p, void (*cb)(void));
void fn_80054CD8(void);
void fn_8005556C(void);
void fn_800620A8(GameData* g, f32 x, f32 y);
void* fn_801856C8(void);
void* fn_801930DC(void* p);
void fn_80280EE0(void* p);
void fn_8005997C(void* p);
void fn_80083E18(void* p, void (*cb)(void*));
void fn_800D3C90(void* p, int n);
void fn_8012FCC0(void);
int fn_802428AC(void);
void* fn_80062A9C(GameData* g, u32 k);
Color4* fn_800CD204(int n);
void fn_80080508(Color4* c);
void fn_800454A8(UnitCmdState* s, s8 x, s8 y);
#if TARGET_PC
FE10_PROTO struct Unit * fn_80067880(p32arg);
#else
int fn_80067880(int n);
#endif
void fn_80103D50(Unit2* u, int n);
Unit2* fn_8002C590(BigState* b);
void fn_8011EB4C(Unit2* u, s8* x, s8* y);
#if TARGET_PC
FE10_PROTO void fn_801037D4(Unit2* u, int a, int b, int c, int d, p32arg);
#else
void fn_801037D4(Unit2* u, int a, int b, int c, int d, int e);
#endif
void fn_8011E300(Unit2* u, s8 x, s8 y, int n);
void fn_800392FC(void* l, s8 x, s8 y);
void fn_80039990(void* l, Unit2* u);
void fn_8003B298(s8 x, s8 y);
void fn_800EB3D8(void* p);
s8 fn_8012E944(Unit2* a, UnitPers* p);
void fn_8011996C(Unit2* a, Unit2* b, int n);
void* fn_801FBF08(void* p);
void fn_801E5870(void* p);
int fn_800685B0(NamedThing* t);
#if TARGET_PC
FE10_PROTO s8 fn_8024F7EC(p32arg);
FE10_PROTO void fn_80251838(int a, p32arg, f32 v);
#else
s8 fn_8024F7EC(int t);
void fn_80251838(int a, int t, f32 v);
#endif
void* fn_801D5EC8(void);
void* fn_801D5DC4(void* p);
void fn_8023F1A0(void* p, int n);
char* strcpy(char* d, const char* s);
Opt44* fn_80060728(GameData* g);
void* fn_800D4188(const char* s, void* p);
void fn_800D3BCC(void* p, int n);
void fn_8012FCB0(void);
void fn_80062454(GameData* g);
void fn_8012D620(void);
void fn_8012D908(void);
int fn_8011B77C(void* list, void* key);
void fn_800FAFF0(Unit2* u, int n);
#if TARGET_PC
FE10_PROTO void * fn_80076F54(const char* s);
#else
int fn_80076F54(const char* s);
#endif
int fn_80060914(GameData* g);
void fn_801E6B64(const char* s, void* m, f32 x, f32 y);
#if TARGET_PC
FE10_PROTO struct Proc * fn_80085708(const char* s);
#else
int fn_80085708(const char* s);
#endif
u8 fn_801E7024(void);
}
#endif
