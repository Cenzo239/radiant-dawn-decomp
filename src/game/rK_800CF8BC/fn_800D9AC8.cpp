/* Unit commands split from fn_800D7D74.cpp. The unit lookup is written in place because a variable assigned from the UnitId inline ignores declaration order. */
#include "game/rK_800CF8BC/types.h"
#include "game/rH_80112B48/map.h"
#include "game/rH_80112B48/unit.h"

#pragma use_lmw_stmw on

extern Map lbl_803EC898;
extern u32 lbl_804CB700;
extern u8 lbl_80384018[];
extern u8 lbl_80384030[];
extern u8 lbl_803CAB38[];
extern u8 lbl_804CB838;
extern u8 lbl_804CB73C;
extern u8 lbl_804CB73D;
extern u8 lbl_804CB73E;
extern u8 lbl_804CB73F;
extern u8 lbl_804CB740;
extern u8* lbl_804CB814;
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA4EC;
#else
extern u32 lbl_804CA4EC;
#endif

/* Script-side map option block: created on demand by every setter. */
struct OptProc {
    u8 proc[0x30];
    union {
        u16 fl;   /* 0x30 */
        struct {
            u16 flHi : 12;
            u16 flLo : 4;
        };
    };
    s16 x32;
    s16 x34;
    s16 x36;
    s16 x38;
    u8 b3A;
    u8 b3B;
    u8 b3C;
    u8 b3D;
    u8 b3E;
    u8 b3F;
    u8 b40;
    u8 b41;
    u8 b42;
    u8 b43;
    u8 b44;
    u8 b45;
    u8 pad46[2];
    int o48;
    u8 b4C;
    u8 b4D;
    u8 b4E;
};

struct UColor {
    u8 r, g, b, a;
};

/* Fields of a unit not named in rH's Unit. */
struct UX {
    u16 h0;
    u8 pad2[0xE];
    f32 f10;
    f32 f14;
    f32 f18;
    u8 pad1C[0xC4 - 0x1C];
    s16 hC4;
    u8 bC6;
    u8 padC7[0xDA - 0xC7];
    s16 hDA;
};

struct FCam {
    u8 pad0[4];
    f32 f4;
    f32 f8;
    f32 fC;
    f32 f10;
    f32 f14;
    u8 pad18[0x38 - 0x18];
    Vec v38;
    u8 pad44[0x68 - 0x44];
    f32 f68;
};

struct MapCtl {
    u8 pad0[0x18];
    void* o18;
    u8 pad1C[0x6C - 0x1C];
    f32 f6C;
    f32 f70;
    f32 f74;
};

struct SavedCam {
    u8 valid;
    u8 pad1[3];
    f32 f4;
    f32 f8;
    f32 fC;
    Vec v10;
    s16 h1C;
    s16 h1E;
};
extern SavedCam lbl_803E8F78;
extern u8 lbl_804CA4AC;
extern char lbl_80366654[];
extern u8 lbl_80384110[];
extern u8 lbl_803CB770[];

struct MapCtl2 {
    u8 pad0[0xC];
    u8* tiles;   /* 0x0C */
    u8 pad10[0x52 - 0x10];
    s16 n;       /* 0x52 */
};

struct TileEv {
    u8 pad0;
    s8 x;
    s8 y;
};

struct ObjData {
    u32* o0;
    u16 h4;
    s16 h6;
    s16 h8;
    u8 padA[2];
    u8 bC;
    u8 padD[2];
    u8 bF;
    u8 pad10[8];
    u32 fl18;
    u8 pad1C[0x68 - 0x1C];
    u8 m68[0x34];
    void* o9C;
};
struct ObjH {
    u8 pad0[0x30];
    ObjData* d;
};
struct LoadProc {
    u8 proc[0x30];
    char name[0x20];
    u16 h50;
    u8 b52;
};
struct PairProc {
    u8 proc[0x30];
    void* a;
    void* b;
};
extern u8 lbl_80384138[];
extern u8 lbl_803C8E80[];
extern u8 lbl_80384188[];
extern u8 lbl_803841AC[];
extern u8 lbl_803841C8[];

struct PointProc {
    u8 proc[0x30];
    s16 x;
    s16 y;
    u8 r, g, b;
};
struct MapHide {
    u8 pad0[0xB4];
    u32 flB4;
};
struct PfxData {
    u8 pad0[0x25];
    u8 b25;
    u8 pad26[2];
    s16 h28;
    u8 pad2A;
    u8 c2B, c2C, c2D, c2E;
};
struct PfxObj {
    u8 pad0[0x30];
    PfxData* d;
    u8 pad34[8];
    u16 id3C;
};
extern u8 lbl_80384170[];
#if TARGET_PC
FE10_PROTO extern void *lbl_804CA5A8;
#else
extern u32 lbl_804CA5A8;
#endif
extern u8 lbl_80384158[];

struct EffProc {
    u8 proc[0x30];
    u8* eff;      /* 0x30 */
    char name[0x40]; /* 0x34 */
    f32 x;        /* 0x74 */
    f32 y;
    f32 z;
};
extern u8 lbl_804CB834;
extern UColor lbl_80413BF8[];
extern UColor lbl_80413BE8[];

extern "C" {
OptProc* fn_80083B84(u8*);
void* fn_8009E898();
void* fn_800A237C();
OptProc* fn_80081050(u8*, void*);
void fn_801476E8();
int fn_8011F5B4(Unit*);
void fn_800F39DC(Unit*);
void fn_80126EB0(Unit*, int, int);
void fn_800F4B94(Unit*, int);
#if TARGET_PC
FE10_PROTO void fn_8010316C(Unit*, int, p32arg, p32arg, p32arg);
#else
void fn_8010316C(Unit*, int, int, int, int);
#endif
void fn_80103410(Unit*, void*, int, void*);
void fn_80114D00(Map*);
#if TARGET_PC
FE10_PROTO void* fn_8010B964(Unit*, s8*, s8*, p32arg, p32arg);
#else
void* fn_8010B964(Unit*, s8*, s8*, int, int);
#endif
int fn_800FC09C(Unit*, f32);
int fn_800DADA0(int, int, int, int, int);
u8* fn_800C3558();
void* fn_8013B9A8();
void fn_80134E98(int, int, int, UColor);
#if TARGET_PC
FE10_PROTO void fn_80131294(int, int, ptr32<const void>, f32, f32, f32);
#else
void fn_80131294(int, int, void*, f32, f32, f32);
#endif
char* strcpy(char*, const char*);
int fn_801CA248(void*);
int fn_801CA260(void*);
int fn_80135F88(void*, void*, void**);
void fn_801CA444(void*, int);
void fn_801CA49C(void*, int);
void fn_801476E8();
int fn_800DD7C4(int, int);
int fn_800DD940(int, int);
void* fn_800E45B0(int);

static inline OptProc* OptGet() {
    OptProc* p = fn_80083B84(lbl_80384018);
    if (p) {
        return p;
    }
    p = fn_80081050(lbl_80384018, fn_8009E898());
    p->fl = 0x2C0;
    p->x32 = -1;
    p->x34 = -1;
    p->x36 = -1;
    p->x38 = -1;
    p->b3A = 1;
    p->o48 = 1;
    p->b3B = 0;
    p->b3C = 0;
    p->b3D = 0;
    p->b3E = 0;
    p->b3F = 0;
    p->b40 = 0;
    p->b41 = 0;
    p->b42 = 0;
    p->b43 = 0;
    p->b44 = 0;
    p->b45 = 1;
    p->b4C = 0;
    p->b4D = 0;
    p->b4E = 0;
    return p;
}

static inline void* Parent30() {
    void* q = fn_800A237C();
    if (q == 0) {
        q = fn_8009E898();
    }
    return q;
}

static inline OptProc* Get30() {
    OptProc* p = fn_80083B84(lbl_80384030);
    if (p) {
        return p;
    }
    return fn_80081050(lbl_80384030, Parent30());
}

static inline Unit* UnitId(int id) {
    id = (u8)id;
    if (id) {
        return &lbl_804CB810[id - 1];
    }
    return 0;
}

static inline BOOL Has30() {
    return fn_80083B84(lbl_80384030) != 0;
}

#define BITSET(name, m) \
    int name(int v) { \
        OptProc* p = OptGet(); \
        if (v) { \
            p->fl |= m; \
        } else { \
            p->fl &= ~m; \
        } \
        return 1; \
    }



#define GLOBSET(name, g) \
    int name(int v) { \
        OptGet(); \
        g = v != 0; \
        return 1; \
    }


static inline u16 OptFlags() {
    OptProc* p = fn_80083B84(lbl_80384018);
    if (p) {
        return p->fl;
    }
    return 0x2C0;
}

static inline int OptX38() {
    OptProc* p = fn_80083B84(lbl_80384018);
    if (p) {
        return p->x38;
    }
    return -1;
}

int fn_800D9C80(const char** ps, int def);

#define UNIT_CHECK(u) \
    if (u == 0 || u->person == 0) { \
        return 0; \
    } \
    if (fn_8011F5B4(u) == 0) { \
        return 0; \
    }

static inline BOOL TurnSnap(Unit* u) {
    OptProc* p = fn_80083B84(lbl_80384018);
    if (p && p->b45 == 0) {
        return 0;
    }
    return (((UX*)u)->h0 & 0xC000) == 0;
}

static inline int TurnFrames(Unit* u, int angle, int dur) {
    if (dur < 0) {
        return fn_800FC09C(u, angle);
    }
    return dur / 16.666666f;
}

#pragma use_lmw_stmw off

int fn_800DADA0(int id, int s, int scale, int dur, int x);
#pragma use_lmw_stmw on

static inline void SceneDirty() {
    u8* s = fn_800C3558();
    s[0x1C] = 1;
}

static inline void MapTint(int a, int b, int c, UColor col) {
    fn_80134E98(a, b, c, col);
}

static inline void ColSet(UColor* d, UColor c) {
    d->r = c.r;
    d->g = c.g;
    d->b = c.b;
    d->a = c.a;
}

static inline int OptO48() {
    OptProc* p = fn_80083B84(lbl_80384018);
    if (p) {
        return p->o48;
    }
    return 1;
}

#define TINT(name, k) \
    int name(int a, int b, int c, int d) { \
        f32 w = OptO48(); \
        fn_80131294(k, a, 0, b / w, c / w, d / w); \
        return 1; \
    }


#pragma use_lmw_stmw off

#pragma use_lmw_stmw on

static inline BOOL EffBusy() {
    return fn_80083B84(lbl_80384110) != 0;
}

static inline void NotifyOpen(void* e2) {
    void* list[16];
    void* mm = fn_8013B9A8();
    if (mm) {
        int n = fn_80135F88(mm, e2, list);
        void** q = list;
        int i = 0;
        for (; i < n; q++, i++) {
            void* t = *q;
            if (fn_801CA248(t) == 0) {
                fn_801CA444(t, 0);
            }
        }
    }
}

static inline void NotifyClose(void* e2) {
    void* list[16];
    void* mm = fn_8013B9A8();
    if (mm) {
        int n = fn_80135F88(mm, e2, list);
        void** q = list;
        int i = 0;
        for (; i < n; q++, i++) {
            void* t = *q;
            if (fn_801CA260(t) == 0) {
                fn_801CA49C(t, 0);
            }
        }
    }
}

int fn_800DD7C4(int x, int y);

int fn_800DD940(int x, int y);

#pragma use_lmw_stmw off

#pragma use_lmw_stmw on

static inline void* ObjGet(u32 id) {
    if (id == 0) {
        return 0;
    }
    if (id >= 0x10000) {
        return 0;
    }
    return fn_800E45B0((u16)id);
}

#pragma use_lmw_stmw off
#pragma use_lmw_stmw on

#pragma use_lmw_stmw off

#pragma use_lmw_stmw on

int fn_800D9AC8(int id, int ax, int ay) {
    u16 fl;
    Unit* u;
    void* path;
    id = (u8)id;
    if (id) {
        u = &lbl_804CB810[id - 1];
    } else {
        u = 0;
    }
    s8 x;
    s8 y;
    if (u == 0 || u->person == 0) {
        return 0;
    }
    if (fn_8011F5B4(u) == 0) {
        return 0;
    }
    fl = OptFlags();
    x = ax;
    y = ay;
    path = fn_8010B964(u, &x, &y, 0, 0);
    if (path) {
        fn_80126EB0(u, (s8)*(u8*)&x, (s8)*(u8*)&y);
        if (lbl_804CB700 & 0x8001) {
            fn_800F4B94(u, OptX38());
            fn_8010316C(u, fl & 0xF, 0, 0, 0);
            fn_800F39DC(u);
        } else {
            fn_80103410(u, path, fl, Get30());
        }
    }
    fn_80114D00(&lbl_803EC898);
    return 1;
}

int fn_800D9CE8(int id, const char* s) {
    int fl;
    Unit* u;
    id = (u8)id;
    if (id) {
        u = &lbl_804CB810[id - 1];
    } else {
        u = 0;
    }
    u8* o;
    int x;
    int y;
    u8 buf[0x100];
    if (u == 0 || u->person == 0) {
        return 0;
    }
    if (fn_8011F5B4(u) == 0) {
        return 0;
    }
    fl = OptFlags() | 0x400;
    {
        x = u->x;
        y = u->y;
        o = buf + 2;
        buf[0] = x;
        buf[1] = y;
        while (*s) {
            x = fn_800D9C80(&s, x);
            y = fn_800D9C80(&s, y);
            o[0] = x;
            o[1] = y;
            o += 2;
        }
        *o = 0x40;
        fn_80126EB0(u, (s8)x, (s8)y);
    }
    if (lbl_804CB700 & 0x8001) {
        fn_800F4B94(u, OptX38());
        fn_8010316C(u, fl & 0xF, 0, 0, 0);
        fn_800F39DC(u);
    } else {
        fn_80103410(u, buf, fl, Get30());
    }
    fn_80114D00(&lbl_803EC898);
    return 1;
}
}
