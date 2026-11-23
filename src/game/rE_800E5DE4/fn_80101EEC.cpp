/* Round 20, exact (check_regs.py: exact): fn_80101EEC. Self-contained. check_func.py --strict-references: MATCH. fn_80100760.cpp with exported bodies removed plus the draft from wip/fn_80101EEC.cpp. Key: the halved fade time is an inline with a local constant (int x = 0x10; return x >> 1;) compiled under #pragma opt_propagation off, which keeps the original's li r0,0x10; srawi r28,r0,1. */
#include "game/rE_800E5DE4/mapunit.h"
#pragma auto_inline off

typedef struct Opt { u8 pad[4]; u32 hi : 6; u32 mode : 2; u32 rest : 24; } Opt;

class Pad {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual u32 Held();
};

typedef union PSlot {
    s32 i;
    u32 u;
    f32 f;
    u16 h;
    GXColor c;
    void* p;
    MapUnit* m;
} PSlot;

typedef struct UProc {
    u8 pad0[0x30];
    MapUnit* unit; /* 0x30 */
    PSlot s34;     /* 0x34 */
    PSlot s38;     /* 0x38 */
    PSlot s3C;     /* 0x3C */
    PSlot s40;     /* 0x40 */
} UProc;

typedef struct Probe { u8 pad[0x30]; void* a; } Probe;

extern "C" {
extern u8 lbl_803CAB38[];
extern Pad* lbl_804CB5B8;
extern Opt* fn_80060728(void*);
extern void fn_800088A0(void*, f32);
extern void fn_800F74D0(MapUnit*, int);
extern int fn_8011B77C(void*, void*);
extern void fn_80083DC4(void*, int);
extern void fn_802549C4(const char*, const Vec&, f32);
extern void* lbl_804CA58C;

extern u8 lbl_80385120[];
extern u8 lbl_80385148[];
extern u8 lbl_80367D50[];
extern UProc* fn_800811E4(void*, void*);
extern void* fn_800893E4(void*, void*, Probe*);
#if TARGET_PC
extern FE10_PROTO UProc* fn_80081050(void*, p32arg);
#else
extern UProc* fn_80081050(void*, int);
#endif
extern void fn_80104A70(void* a, void* b);
#if TARGET_PC
extern FE10_PROTO ptr32<void> fn_800F0994(char*);
#else
extern void* fn_800F0994(char*);
#endif
#if TARGET_PC
extern FE10_PROTO void fn_80102928(MapUnit*, i32arg, int, int, p32arg);
#else
extern void fn_80102928(MapUnit*, void*, int, int, int);
#endif
extern GXColor fn_800F201C(int);
extern int fn_80008C98(void*, int);


#pragma pool_strings on
void pool_7d50() {
    const char* volatile s;
    s = "\x95""\xe0""\x82""\xab"""; /* 0x0 */
    s = "\x88""\xda""\x93""\xae"""; /* 0x5 */
    s = ""; /* 0xa */
    s = "\x93""o\x82""\xe8"""; /* 0xb */
    s = "\x8d""~\x82""\xe8"""; /* 0x10 */
    s = "\x83""_\x83""\x81""\x81""[\x83""W"; /* 0x15 */
    s = "EID_SMITE"; /* 0x1e */
    s = "EID_TACKLE"; /* 0x28 */
    s = "\x91""\xcc""\x93""\x96""\x82""\xbd""\x82""\xe8"""; /* 0x33 */
    s = "SFX_BMP_DAMAGE_TACKLE1"; /* 0x3c */
    s = "EID_QUICK_REWARP_F1"; /* 0x53 */
    s = "EID_QUICK_REWARP_T1"; /* 0x67 */
    s = "EID_QUICK_REWARP_W1"; /* 0x7b */
    s = "EID_QUICK_REWARP1"; /* 0x8f */
    s = "EID_RESCUE1"; /* 0xa1 */
    s = "EID_QUICK_REWARP_F2"; /* 0xad */
    s = "EID_QUICK_REWARP_T2"; /* 0xc1 */
    s = "EID_QUICK_REWARP_W2"; /* 0xd5 */
    s = "EID_QUICK_REWARP2"; /* 0xe9 */
    s = "EID_RESCUE2"; /* 0xfb */
    s = "\x95""\xcf""\x90""g"; /* 0x107 */
    s = "EID_INCARNATION"; /* 0x10c */
    s = "\x8e""\x80""\x96""S"; /* 0x11c */
    s = "SFX_BMP_FADE_DIE_AWAY1"; /* 0x121 */
    s = "\x91""\xd2""\x8b""@"; /* 0x138 */
}

static inline void Play(MapUnit* u, char* n) {
    fn_80102928(u, fn_800F0994(n), 2, 0, 0);
}
static inline UProc* Fade(MapUnit* u, int i, int n, void* parent) {
    Probe s;
    UProc* q;
    s.a = u;
    fn_800893E4(lbl_80385148, fn_80104A70, &s);
    q = fn_800811E4(lbl_80385148, parent);
    q->unit = u;
    q->s3C.i = n;
    q->s38.c = fn_800F201C(i);
    q->s34.c = u->color;
    return q;
}
static inline UProc* Fade2(MapUnit* u, int i, int n, int pri) {
    Probe s;
    UProc* q;
    s.a = u;
    fn_800893E4(lbl_80385120, fn_80104A70, &s);
    q = fn_80081050(lbl_80385120, pri);
    q->unit = u;
    q->s40.i = n;
    q->s38.c = fn_800F201C(i);
    return q;
}
void fn_80100760(UProc* p);


typedef struct Task { u8 pad[0x18]; UProc* owner; u8 pad1c[0x14]; MapUnit** ctl; } Task;
void fn_801018F8(Task* t);

void fn_80101B80(Task* t);

void fn_80102858(UProc* p);

#if TARGET_PC
FE10_PROTO UProc* fn_80103234(MapUnit* u, int i, int n, p32arg);
#else
UProc* fn_80103234(MapUnit* u, int i, int n, int pri);
#endif


typedef struct R2438 { u8 pad[0x30]; MapUnit* u; u8 b34; u8 b35; u8 b36; } R2438;
typedef struct Task2 { u8 pad[0x30]; MapUnit* ctl; } Task2;
typedef struct Ctl { MapUnit* m; u8 pad[0xA0]; R2438* owner; } Ctl;
static inline BOOL Boost(R2438* p) {
    if (p->b36) {
        if (lbl_804CB5B8->Held() & 0xFFF0) return 1;
        if (fn_80060728(lbl_803CAB38)->mode == 2) return 1;
    }
    return 0;
}
void fn_80102714(R2438* p);


typedef struct Tile8 { u8 pad[7]; u8 b7; } Tile8;
typedef struct Tile { u8 pad[8]; Tile8* v8; } Tile;
typedef struct MapData { u8 pad[0xD]; u8 g0[0x3000]; u8 g1[0x12183]; s16* g2; } MapData;
extern MapData lbl_803EC898;
extern u8 lbl_80385290[];
extern void fn_80104AA4(void* a, void* b);
extern void fn_80067230(MapUnit*);
extern u8 fn_800F40F4(MapUnit*);
extern int fn_8011799C(void*, int, int);
extern Tile* fn_801181E8(void*, int, int);
extern void* fn_80116658(void*, int, int);
extern void* fn_80081194(void*, void*);
extern void fn_800FF998(void*, MapUnit*, int);
extern void fn_800FFFDC(void*, void*);
extern void fn_80100384(void*);

static inline u8 DirBit(int i) {
    switch (i) {
    case 0: return 1;
    case 1: return 2;
    case 2: return 4;
    case 3: return 8;
    }
    return 0x40;
}
static inline int DirX(u8 d) {
    switch (d) {
    case 1: return -1;
    case 2: return 1;
    }
    return 0;
}
static inline int DirY(u8 d) {
    switch (d) {
    case 4: return 1;
    case 8: return -1;
    }
    return 0;
}
#pragma use_lmw_stmw on

void* fn_80103A20(MapUnit* u, void* parent);

#pragma use_lmw_stmw off
}

#pragma use_lmw_stmw off
#pragma opt_propagation off
/* ---- from rE_800E5DE4/wip/fn_80101EEC.cpp ---- */
extern "C" {
/* fn_80101EEC, fn_80102030: 1 word differs in each. Structs and helpers are in ../fn_80100760.cpp.
 * The original has `li r0,0x10; srawi r28,r0,1` (same as fn_800FD65C with 0xC). Half(const int&) with a
 * literal gets everything right except it loads the constant with `lwz r0,@sda21` instead of `li`.
 * Every other form tried folds to `li r28,8` or gives `srawi r28,r28,1`: see NOTES.md. */
static inline int Half(void) { int x = 0x10; return x >> 1; }
void fn_80101EEC(Task2* t) {
    R2438* o = ((Ctl*)t->ctl)->owner;
    int n = 0x10;
    if (Boost(o)) n = Half();
    Fade(o->u, 3, n, o);
}
}
