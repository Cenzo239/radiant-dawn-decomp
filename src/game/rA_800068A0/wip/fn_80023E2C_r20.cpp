/* Round 20 draft, NOT at a counted level (check_regs.py: other): fn_80023E2C. Self-contained, complete source. Instruction count ours 100 orig 99. What differs: 100 vs 99 instructions: in the constructor-style store block the original reuses r0 for 0x190 where ours takes r11 and one more instruction; store order differs. */
#include "game/rA_800068A0/types.h"

/* Sally (battle preparation) / bgm-related procs. Strings at lbl_80361118 and
 * lbl_80361260 are the file's string pools. */

typedef unsigned long long u64;

extern "C" {

extern char lbl_80361118[];
extern char lbl_80361260[];

struct Unit {
    u8 pad[0xE8];
    Unit* next;   /* +0xE8 */
    u8 pad2[0x1C];
    u64 flags;    /* +0x108 */
};
struct UnitList {
    u8 pad[0xC];
    Unit* c;
    u8 pad2[0x2C];
    Unit* l3c;
};
extern UnitList* lbl_804CB814;
extern u8 lbl_804CB818;
extern u32 lbl_804CB700;
extern u8 lbl_803EC898[];

struct SsoStr {
    u32 isLong : 1;
    u32 pad : 31;
    u32 pad4;
    char* ptr;
};
struct Sally {
    u8 pad[0x40];
    SsoStr s;       /* +0x40 */
    void* p4c;      /* +0x4C */
};

extern void fn_800231E4(void);
extern void fn_8010D018(const char*);
extern void fn_80185720(void);
extern void fn_80114D00(void*);
extern void fn_801D607C(void);
extern void fn_800761F0(void*);
extern void fn_8012FCC0(void);
extern void fn_80079210(void*);
extern void fn_801E40B0(void*, int);
extern void fn_8012FC9C(void);
void fn_800235B8(Sally* p);


extern void fn_801856C8(void);
extern void fn_801930DC(void);
extern void fn_80280EE0(void);
extern void* fn_800D4228(const char*);
extern void fn_800D3C90(void*, int);
void fn_8002386C(void);


struct Mnu {
    u8 pad[0x50];
    void* p50;
};
extern void fn_8008939C(void*);
extern void* fn_801E5640(void*, int, int);
extern void fn_801E5558(void*, void*, int);
extern void fn_801FBE14(void*);
void fn_80023DCC(Mnu* p);


extern void fn_8012FCB0(void);
extern void* fn_800D4188(const char*, void*);
extern void fn_800D3BCC(void*, int);
struct X28 { u8 pad[0x28]; s16 s28; };
struct Y24 { u8 pad[0x24]; u8 b24; };
struct Z64 { u8 pad[0x64]; const char* s64; };
extern u8 lbl_80378EA8[];
extern void* fn_800D0864(void*);
extern Y24* fn_801DFF2C(void*);
extern void fn_800D5448(void*, void*, int);
void fn_80024090(void* p);


extern int fn_8002442C(void*, Unit*);
extern void fn_801BA584(void*, void*);
void fn_800241B4(Mnu* p);


extern u32 lbl_803CA870[];
extern void fn_800243D0(void*);
extern void fn_801C6D2C(u32, void*, int, void*, void*);
void fn_800243D4(void* a);


extern int lbl_803E7320[0x20];
int fn_8002442C(void* unused, Unit* u);

void fn_80024640(void* p);


extern u8 lbl_80378E18[];
struct Pos { u8 pad[0x30]; s16 x, y; };
extern void fn_801E6B64(void*, void*, f32, f32);
int fn_800249E8(void* unused, Pos* a, Pos* b);


struct Arr { u32* p; };
u32 fn_80024E80(Arr* a, int i);


extern void fn_8007E154(void);
extern void fn_8007E164(void);
extern void fn_8007E4E4(f32, f32, f32, f32);
extern void fn_8007E7DC(u8);
extern int strlen(const char*);
extern void fn_801C6D9C(const char*, int, int, int);
struct Msg { u8 pad[0x34]; const char* s; s16 a, d; };
void fn_80025388(Msg* p);


struct Cfg { u8 pad[0x11]; u8 b11; };
extern u8 lbl_803CAB38[];
extern Cfg* fn_80060728(void*);
extern void fn_8028392C(const char*, int, int, int, void*, int);
struct Fm { u8 pad[0x28]; s16 t; u8 pad2[0xA]; void* p34; };
void fn_8002573C(Fm* p);


extern void fn_80083B78(void*);
extern void fn_80083DC4(void*, int);
void fn_80025830(void* p);


extern void fn_80252984(f32);
extern void fn_800C835C(int, int);
extern void fn_80084F0C(const char*);
void fn_80025894(void);


extern u8 lbl_804CB728;
extern u8 lbl_80378F80[];
extern void* fn_80085708(const char*);
extern void fn_800D5AB0(void*);
extern void* fn_80081194(void*, void*);
void fn_80025990(void);



/* Widget constructors (see region I wfInit). */
extern char lbl_8038CB1C[];
extern char lbl_8038C1C0[];
struct WF {
    void* vt; int rc; s16 id; s16 x0, y0, x1, y1; s16 ix0, iy0, ix1, iy1;
    s16 a1a, a1c, tx, ty; u8 c[4]; s16 a26, a28; f32 sx, sy, sz; u32 flags; void* a3c;
};
struct WB { WF w; int a40, a44, a48, a4c; u8 a50; f32 a54; s16 a58, a5a, a5c, a5e; int a60; const char* a64; };
static inline void wfInit(WF* w, s16 x0, s16 y0, s16 x1, s16 y1, s16 ix1, s16 iy1, s16 a26, int fl) {
    w->rc = 0;
    w->vt = lbl_8038CB1C;
    w->id = -1;
    w->x0 = x0; w->y0 = y0; w->x1 = x1; w->y1 = y1;
    w->ix0 = 0; w->iy0 = 0; w->ix1 = ix1; w->iy1 = iy1;
    w->a1a = 0; w->a1c = 0; w->tx = 0; w->ty = 0;
    w->c[0] = 0xff; w->c[1] = 0xff; w->c[2] = 0xff; w->c[3] = 0xff;
    w->a26 = a26; w->a28 = 0;
    w->sx = 1.0f; w->sy = 1.0f; w->sz = 1.0f;
    w->flags = fl; w->a3c = 0;
}
static inline void wbInit(WB* b, s16 x0, s16 y0, s16 x1, s16 y1, s16 ix1, s16 iy1, s16 a26, int fl) {
    wfInit(&b->w, x0, y0, x1, y1, ix1, iy1, a26, fl);
    b->a40 = 0; b->a44 = 0; b->a48 = 0; b->a4c = 0;
    b->a50 = 1;
    b->a5a = 0; b->a5e = 0;
    b->w.vt = lbl_8038C1C0;
    b->a60 = 0; b->a64 = 0;
    b->a58 = iy1; b->a5c = iy1;
    b->a54 = 0.75f;
}
extern void* fn_80079150(u32);
extern void fn_801E5448(void*, void*, int);
extern void fn_800893AC(void*);

static inline void mnuAdd(Mnu* p) {
    WB* b = (WB*)fn_80079150(0x68);
    WB* x;
    if (b != 0) {
        wbInit(b, 0, 0x190, 0x260, 0x1C0, 0x260, 0x30, 0x316, 0x10);
    }
    b->w.id = -0x1000;
    b->a4c = 1;
    b->a64 = lbl_80361118;
    b->w.flags |= 0x10;
    b->a60 = 0;
    b->w.a28 = 8;
    fn_801E5448(p, b, b->a60);
    x = (WB*)fn_801E5640(p, -0x1000, 0);
    if (x != 0) {
        x->a60 = 1;
    }
}

void fn_80023E2C(Mnu* p);

void fn_8002421C(Mnu* p);

extern u8 lbl_80378968[];
extern void* fn_80081050(void*, void*);
extern void fn_8012FC90(void);
extern int fn_8010CF20(const char*, char*);
extern void fn_800CFB34(void*);
extern void fn_800CFC50(void*, int, int, int, int);
struct Sub2C { u8 pad[0x2C]; u8 b2C; };
struct Fld { u8 pad[0x21]; u8 b21; u8 b22; u8 pad2[5]; u32 w28; };
extern u8 lbl_804CB140;
struct SallyM { u8 pad[0x40]; SsoStr s; void* p4c; Sub2C* p50; };

void fn_80023360(SallyM* p);

extern s8 lbl_804CB104;
extern void* lbl_804CB108;
extern s8 lbl_804CB10C;
extern void* lbl_804CB110;
extern s8 lbl_804CB114;
extern void* lbl_804CB118;
extern s8 lbl_804CB11C;
extern void* lbl_804CB120;
extern s8 lbl_804CB124;
extern void* lbl_804CB128;
extern s8 lbl_804CB12C;
extern void* lbl_804CB130;
extern s8 lbl_804CB134;
extern u8 lbl_80378CC8[];
extern u8 lbl_80378C70[];
extern u8 lbl_80378C18[];
extern u8 lbl_80378BC0[];
extern u8 lbl_80378B68[];
extern u8 lbl_80378B10[];
extern u8 lbl_80383F28[];
extern u8 lbl_80378984[];
extern u8 lbl_80378D20[];
struct MsgObj { void* name; void* vt; };
extern MsgObj lbl_804CB138;
extern void fn_801856F4(void);
extern void fn_800453B4(void*, int);

#define LAZY(g, o, v) if (!g) { g = 1; o = v; }

void fn_800236AC(void* p);


/* MSL std::basic_string<char> (libc++-style short string). */
struct E { E() {} char c; };
struct Str {
    union {
        struct { u32 lng : 1; u32 cap : 31; u32 len; char* ptr; } l;
        struct { u8 lng : 1; u8 len : 7; char buf[11]; } s;
    };
};
extern u8 __files[];
extern char lbl_80378DB4[];
extern void fn_80290B48(void*, const char*, ...);
extern void fn_80291BD0(void);
extern void* memmove(void*, const void*, u32);
extern void* memcpy(void*, const void*, u32);

#pragma use_lmw_stmw on
void fn_80024EFC(Str* s, u32 n);

extern char lbl_804CA058[1];
extern char lbl_804CA059[1];
static inline u32 dist(const char* f, const char* l) { return l - f; }
static inline const u32& umin(const u32& a, const u32& b) { return b < a ? b : a; }

Str* fn_800250B0(Str* s, u32 pos, u32 n1, const char* f, const char* last, E a);

#pragma use_lmw_stmw off

extern int fn_8010E2F4(void*);
extern u8 lbl_803789A0[];
extern void* fn_80081050(void*, void*);
extern void fn_801E4094(void*);
extern char lbl_804CA05C[1];
struct NameProc { u8 pad[0x40]; Str s; u32 a4c; };

NameProc* fn_800244C4(const char* name, void* parent);

extern void fn_80283A58(void);
extern void fn_8024B5D4(void*);
extern int lbl_804CBFCC;
void fn_80025510(void* p);


} /* extern "C" */


#pragma use_lmw_stmw off
/* ---- from rA_800068A0/wip/fn_80023E2C.cpp ---- */
extern "C" {
/* fn_80023E2C: near miss, 53 of 99 words differ. Depends on types and helpers from ../fn_800235B8.cpp; goes there in address order. */
void fn_80023E2C(Mnu* p) {
    mnuAdd(p);
    fn_800893AC(p->p50);
    fn_80083B78(p);
}
}
