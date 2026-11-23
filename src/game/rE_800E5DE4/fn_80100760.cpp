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

void fn_80100760(UProc* p) {
    Play(p->unit, "\x83""_\x83""\x81""\x81""[\x83""W");
    Fade2(p->unit, 1, 2, 3);
}

typedef struct Task { u8 pad[0x18]; UProc* owner; u8 pad1c[0x14]; MapUnit** ctl; } Task;

void fn_801018F8(Task* t) {
    UProc* o = t->owner;
    if (fn_80008C98(*t->ctl, 0)) {
        Fade(o->unit, 3, 0x10, 0);
    }
}
void fn_80101B80(Task* t) {
    UProc* o = t->owner;
    if (fn_80008C98(*t->ctl, 0)) {
        Fade(o->unit, 0, 0x10, 0);
    }
}
void fn_80102858(UProc* p) {
    Fade(p->unit, 0xD, 0x10, p);
}
UProc* fn_80103234(
#if TARGET_PC
MapUnit* u, int i, int n, void* pri
#else
MapUnit* u, int i, int n, int pri
#endif
) {
    Probe s;
    UProc* q;
    s.a = u;
    fn_800893E4(lbl_80385120, fn_80104A70, &s);
#if TARGET_PC
    if (pri == 0) pri = (void*)3;
#else
    if (pri == 0) pri = 3;
#endif
    q = fn_80081050(lbl_80385120, pri);
    q->unit = u;
    q->s40.i = n;
    q->s38.c = fn_800F201C(i);
    return q;
}

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
void fn_80102714(R2438* p) {
    if (fn_8011B77C((u8*)p->u + 0x12c, lbl_804CA58C)) {
        fn_80083DC4(p, 10);
    } else {
        Vec v = *(Vec*)&p->u->x;
        Vec w;
        w = v;
        fn_802549C4("SFX_BMP_FADE_DIE_AWAY1", w, 0.0f);
        Fade(p->u, 0xC, 8, p);
    }
}

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
void* fn_80103A20(MapUnit* u, void* parent) {
    int i;
    int x, y;
    if (fn_8011B77C((u8*)u + 0x12c, lbl_804CA58C)) {
        return 0;
    }
    fn_80067230(u);
    for (i = 0; i < 5; i++) {
        u8 d;
        if (i == 0) {
            d = fn_800F40F4(u);
        } else {
            d = DirBit(i - 1);
        }
        x = u->mapX + DirX(d);
        y = u->mapY + DirY(d);
        if (fn_8011799C(&lbl_803EC898, (s8)x, (s8)y)) {
            int k = ((s8)y << 6) + (s8)x;
            if (lbl_803EC898.g0[k] != 0) goto next;
            if (lbl_803EC898.g1[k] != 0) goto next;
            if (lbl_803EC898.g2[k] < 0) goto next;
            if (fn_801181E8(&lbl_803EC898, (s8)x, (s8)y)->v8->b7 & 1) goto next;
            {
                void* q;
                Probe s;
                void* t = fn_80116658(&lbl_803EC898, (s8)x, (s8)y);
                s.a = u;
                q = fn_800893E4(lbl_80385290, fn_80104AA4, &s);
                if (q == 0) {
                    q = fn_80081194(lbl_80385290, parent);
                    fn_800FF998(q, u, 0x20);
                }
                fn_800FFFDC(q, t);
                fn_80100384(q);
                return q;
            }
        }
        next:;
    }
    return Fade(u, 3, 0x10, parent);
}
#pragma use_lmw_stmw off
}
