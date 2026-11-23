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
void fn_800846BC(u8*);
void fn_80081A90(void*);
void fn_801476E8();
void fn_800E4548();
#if TARGET_PC
FE10_PROTO void fn_801484B4(p32arg);
#else
void fn_801484B4(int a);
#endif
void fn_801050A8();
int fn_8011F5B4(Unit*);
void fn_80104ABC(Unit*);
int fn_80104F18();
int fn_80104C2C(Unit*);
int fn_800F0994(const char*);
f32 fn_801142F0(Map*, f32, f32);
f32 fn_80113F00(Map*, f32, f32);
#if TARGET_PC
FE10_PROTO void fn_8010D8B4(p32arg, int, void*);
#else
void fn_8010D8B4(int, int, void*);
#endif
u8* fn_80060728(u8*);
#if TARGET_PC
FE10_PROTO void fn_8010DE10(p32arg, int);
FE10_PROTO void fn_8010D018(p32arg);
#else
void fn_8010DE10(int, int);
void fn_8010D018(int);
#endif
void fn_8011FE74(Unit*, int);
void fn_800F39DC(Unit*);
#if TARGET_PC
FE10_PROTO void fn_8010CC50(p32arg, s8*, s8*);
#else
void fn_8010CC50(int, s8*, s8*);
#endif
u8* fn_8010B46C(int);
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
#if TARGET_PC
FE10_PROTO void fn_80102E10(Unit*, int, p32arg, float, void *);
#else
void fn_80102E10(Unit*, int, u8, void*, f32);
#endif
f32 fn_800FB100(Unit*, f32, f32);
void fn_800F3EB0(Unit*, UColor);
int fn_800F080C(const char*);
void fn_800F3F30(Unit*, int);
s16* fn_800F0B04(const char*);
void fn_800F3F28(Unit*, int);
void fn_800F74D0(Unit*, int);
void fn_800F6604(Unit*, const char*);
int fn_800F760C(Unit*);
int fn_800F4628(Unit*, int);
void fn_80104948(Unit*, int, int, u16, void*, f32);
int fn_800DADA0(int, int, int, int, int);
void fn_801039E8(Unit*, void*);
void fn_80103A20(Unit*, void*);
void fn_800F3B90(Unit*, int);
#if TARGET_PC
FE10_PROTO void fn_80103CE4(Unit*, int, p32arg, p32arg, void*);
#else
void fn_80103CE4(Unit*, int, int, int, void*);
#endif
void fn_8010354C(Unit*, Unit*, int, int, void*);
void fn_80100A04(Unit*, int, int, void*);
void fn_801288D4(Unit*);
#if TARGET_PC
FE10_PROTO int fn_8011B77C(void*, p32arg);
#else
int fn_8011B77C(void*, u32);
#endif
#if TARGET_PC
FE10_PROTO void* fn_801772EC(ptr32<const void>, ptr32<const void>, int, void*);
#else
void* fn_801772EC(void*, Unit*, int, void*);
#endif
void fn_8010395C(Unit*, void*);
u32 fn_800F3FE4(Unit*);
int fn_800FAFD4(Unit*, int);
#if TARGET_PC
FE10_PROTO void fn_80062380(u8*, p32arg);
#else
void* fn_80062380(u8*, int);
#endif
void* fn_80062598(u8*, void*);
u8* fn_800C3558();
void fn_8010DB48(void* a);
void fn_8010DC58(void* a);
void fn_80134DB0();
void fn_80134E30();
void fn_80062454(u8*);
void fn_800620A8(u8*, f32, f32);
void fn_8012FF30();
void* fn_8013B9A8();
void fn_80137988(void*, int);
void fn_80134E90(int);
void fn_8013A638(void*);
void fn_8012D908();
void fn_80134E98(int, int, int, UColor);
void fn_801368DC(void*);
void fn_8013B8D0(void*);
void fn_801364AC(void*);
void fn_80146F40(void*, int, int, int);
void fn_8013AC48(void*);
void fn_8013AE18(void*);
FCam* fn_8012FCD0();
void fn_8012F58C(FCam*);
void fn_8012F580(FCam*, f32);
void fn_801313E4(void*);
#if TARGET_PC
FE10_PROTO void fn_80131294(int, int, ptr32<const void>, f32, f32, f32);
#else
void fn_80131294(int, int, void*, f32, f32, f32);
#endif
void fn_8013144C(int a);
void fn_80131490();
void fn_801314D4();
void fn_80131534();
void* fn_80006E1C();
void fn_80009030(void*, void*);
void fn_80009090(void*, void*);
#if TARGET_PC
FE10_PROTO void* fn_8017F37C(char*, const char*, p32arg);
#else
void* fn_8017F37C(char*, const char*, int);
#endif
void fn_80006F20(void*);
int fn_80290DDC(char*, const char*, ...);
void fn_80008F6C(void*, char*);
void fn_80312654(void*, f32, int);
void fn_803128AC(void*, f32, f32, f32);
void fn_80312378(void*, void*, void*);
void fn_80006EE0(void*);
void fn_800081D4(void*);
void fn_80007C58(void*);
#if TARGET_PC
FE10_PROTO void fn_8000BF68(void*, p32arg);
#else
void fn_8000BF68(void*, int);
#endif
void fn_80083B78(void*);
char* strcpy(char*, const char*);
void* fn_80135800(void*, int, int, int, int);
u8* fn_800661A0(u8*, int, int, int, int);
void fn_8006625C(u8*, int, int, int);
void fn_801CAA24(void*, void*, u8);
void fn_801CA3E4(void*, int);
void fn_801379F8(void*, int);
void fn_801CA40C(void*, int);
int fn_80291188(const char*, const char*);
int fn_801CA248(void*);
int fn_801CA260(void*);
u8* fn_80066130(u8*, int, int, int);
void fn_801CA4FC(void*, int);
void fn_801CA568(void*, int);
void* fn_80135A54(void*, int, int, int, int);
int fn_80135F88(void*, void*, void**);
void fn_801CA444(void*, int);
void fn_801CA49C(void*, int);
u8** fn_801181E8(Map*, int, int);
void* fn_800E3A10(const char*, void*);
f32 fn_80114728(Map*, int, int);
void fn_8013E054(void*, void*);
void fn_8013E198(void*, void*);
void fn_8013E314(void*, void*);
void fn_8013DCF0(void*, void*);
void fn_8013DEF4(void*, void*);
#if TARGET_PC
FE10_PROTO void fn_8013E34C(int, int, int, int, p32arg);
#else
void fn_8013E34C(int, int, int, int, int);
#endif
void fn_801476E8();
int fn_800DD7C4(int, int);
int fn_800DD940(int, int);
#if TARGET_PC
FE10_PROTO void fn_8013E530(int, int, int, p32arg);
#else
void fn_8013E530(int, int, int, int);
#endif
void* fn_801358A8(void*, int, int);
void fn_801CA33C(void*, int, int);
void fn_8013B2B8(void*);
void fn_801CA300(void*);
void fn_8013C80C(int, int, int, void*);
u8 fn_8011D1E4(const char*);
#if TARGET_PC
FE10_PROTO void fn_80133B10(ptr32<const void>, ptr32<const void>);
#else
void fn_80133B10(void*, void*);
#endif
int fn_800E272C(char*);
#if TARGET_PC
FE10_PROTO void* fn_800E3C04(char*, p32arg);
FE10_PROTO void* fn_800E3810(char*, p32arg);
#else
void* fn_800E3C04(char*, int);
void* fn_800E3810(char*, int);
#endif
void* fn_801773BC(void*);
void fn_80177418(void*, void*);
int fn_80175E5C();
void* fn_800811E4(u8*, void*);
void fn_800E24F8(const char*);
void* fn_800E45B0(int);
int fn_800E4674(void*);
void fn_800E48AC(void*, f32, f32, f32);
void fn_8001D748(void*, int, f32, f32, f32);
void fn_80312344(void*, void*);
int fn_800F4284(Unit*, const char*);
int fn_800F4394(Unit*, const char*);
void fn_800E5878(void*, Unit*);
void fn_800E49AC(void*, f32);
void fn_800E4904(void*, int, void*);
void fn_800E48F0(void*, int, int);
void fn_800DEF6C(void*);
void fn_800DF250(void*);
void fn_800C835C(int, int);
void* fn_80081194(u8*, void*);
void* fn_8017C218(int, void*);
void fn_8017C1E0(void*, int);
void* fn_8017C2B0(u16);
void fn_8017C2E8();
void fn_8017C1AC(void*, int);
void fn_80006D00(f32);
void fn_80026CD8(u8*, Unit*, int);
void fn_8002C170(u8*);
void fn_8002BE64(u8*, s16);
void fn_800262D8(u8*);
#if TARGET_PC
FE10_PROTO void fn_800E7260(void*, p32arg);
#else
void fn_800E7260(void*, int);
#endif
void fn_800E4AD4(void*, f32);
void fn_800E4B20(void*, int);
int fn_800E44CC();
void fn_8013C14C(f32, int, int, void*);
void fn_8013C200();
#if TARGET_PC
FE10_PROTO void fn_8011AEA0(void*, p32arg, int, int);
FE10_PROTO void fn_8011B430(void*, p32arg);
#else
void fn_8011AEA0(void*, u32, int, int);
void fn_8011B430(void*, u32);
#endif
void fn_8011A36C(void*);
void fn_800F5090(Unit*);
void fn_8007E030(int);
int fn_801B5DD8(int*, int*);

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

u8 fn_800D7D74() {
    OptProc* p = fn_80083B84(lbl_80384018);
    if (p) {
        return p->b3C;
    }
    return 0;
}

int fn_800D7DB0(u8 v) {
    OptGet()->b3C = v;
    return 1;
}

void fn_800D7E74(void* p) {
    if (lbl_804CB700 & 0x8001) {
        fn_80081A90(p);
        fn_801476E8();
        fn_8012D908();
    }
    if (lbl_804CB700 & 1) {
        fn_800E4548();
    }
}

void fn_800D7EB8(int a) { fn_801484B4(a); }

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

void fn_800D7EBC() {
    switch ((int)fn_80083B84(lbl_80384030)) {
    case 0:
        fn_80081050(lbl_80384030, Parent30());
    }
}

static inline Unit* UnitId(int id) {
    id = (u8)id;
    if (id) {
        return &lbl_804CB810[id - 1];
    }
    return 0;
}

int fn_800D7F14(int x) {
    if (x < 0) {
        fn_800846BC(lbl_80384030);
        fn_801050A8();
    } else {
        Unit* u = UnitId(x);
        if (u && fn_8011F5B4(u)) {
            fn_80104ABC(u);
        }
    }
    return 1;
}

static inline BOOL Has30() {
    return fn_80083B84(lbl_80384030) != 0;
}

int fn_800D7F98(int x) {
    if (!(lbl_804CB700 & 0x8001)) {
        if (x < 0) {
            if (Has30()) {
                return 1;
            }
            if (fn_80104F18()) {
                return 1;
            }
        } else {
            Unit* u = UnitId(x);
            if (u && fn_8011F5B4(u) && fn_80104C2C(u)) {
                return 1;
            }
        }
    }
    return 0;
}

int fn_800D805C() {
    OptProc* p = OptGet();
    p->fl &= ~0x40;
    return 1;
}

int fn_800D8124() {
    OptProc* p = OptGet();
    p->fl |= 0x40;
    return 1;
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

BITSET(fn_800D81EC, 0x200)
BITSET(fn_800D82D0, 0x100)
BITSET(fn_800D83B4, 0x800)

int fn_800D8498(const char* s) {
    OptProc* p = OptGet();
    if (s && s[0]) {
        p->x32 = fn_800F0994(s);
    } else {
        p->x32 = -1;
    }
    return 1;
}

s16 fn_800D858C() {
    OptProc* p = fn_80083B84(lbl_80384018);
    if (p) {
        return p->x32;
    }
    return -1;
}

int fn_800D85C8(int v) {
    OptGet()->x34 = v;
    return 1;
}

s16 fn_800D868C() {
    OptProc* p = fn_80083B84(lbl_80384018);
    if (p) {
        return p->x34;
    }
    return -1;
}

int fn_800D86C8(int v) {
    OptGet()->x36 = v;
    return 1;
}

s16 fn_800D878C() {
    OptProc* p = fn_80083B84(lbl_80384018);
    if (p) {
        return p->x36;
    }
    return -1;
}

BITSET(fn_800D87C8, 0x1000)

int fn_800D88AC(int v) {
    OptProc* p = OptGet();
    if (v) {
        p->fl &= ~0x80;
    } else {
        p->fl |= 0x80;
    }
    return 1;
}

int fn_800D8990(int v) {
    OptProc* p = OptGet();
    p->b45 = v != 0;
    return 1;
}

int fn_800D8A68() {
    OptProc* p = OptGet();
    p->fl = (p->fl & ~0x30) | 0x10;
    return 1;
}

int fn_800D8B34() {
    OptProc* p = OptGet();
    p->fl = (p->fl & ~0x30) | 0x20;
    return 1;
}

int fn_800D8C00() {
    OptProc* p = OptGet();
    p->fl &= ~0x30;
    return 1;
}

int fn_800D8CC8(int v) {
    OptGet()->o48 = v;
    return 1;
}

int fn_800D8D8C(s8 x, s8 y) { return 100.0f * fn_801142F0(&lbl_803EC898, x, y); }
int fn_800D8E00(s8 x, s8 y) { return 100.0f * fn_80113F00(&lbl_803EC898, x, y); }

int fn_800D8E74(int v) {
    OptProc* p = OptGet();
    p->fl = (v & 0xF) | (p->fl & 0xFFF0);
    return 1;
}

u16 fn_800D8F4C() {
    OptProc* p = fn_80083B84(lbl_80384018);
    if (p) {
        return p->fl;
    }
    return 0x2C0;
}

int fn_800D8F88(const char* s) {
    OptProc* p = OptGet();
    if (s && s[0]) {
        p->x38 = fn_800F0994(s);
    } else {
        p->x38 = -1;
    }
    return 1;
}

s16 fn_800D907C() {
    OptProc* p = fn_80083B84(lbl_80384018);
    if (p) {
        return p->x38;
    }
    return -1;
}

int fn_800D90B8(int v) {
    OptGet();
    lbl_804CB838 = v ? (lbl_804CB838 & ~0x10) : (lbl_804CB838 | 0x10);
    return 1;
}

#define GLOBSET(name, g) \
    int name(int v) { \
        OptGet(); \
        g = v != 0; \
        return 1; \
    }

GLOBSET(fn_800D918C, lbl_804CB73C)
GLOBSET(fn_800D9258, lbl_804CB73D)
GLOBSET(fn_800D9324, lbl_804CB73E)
GLOBSET(fn_800D93F0, lbl_804CB73F)
GLOBSET(fn_800D94BC, lbl_804CB740)

int fn_800D9588(int a, int b) {
    fn_8010D8B4(a, b, Get30());
    return 1;
}

int fn_800D9610(int a, int b) {
    fn_8010D8B4(a, b, 0);
    return 1;
}

void fn_800D9638(int a) {
    u8* q = fn_80060728(lbl_803CAB38);
    fn_8010DE10(a, q[0x11]);
}

int fn_800D967C(int a) {
    Unit* next;
    int n;
    Unit* u;
    fn_8010D018(a);
    n = 0;
    u = *(Unit**)(lbl_804CB814 + 0x3C);
    while (u) {
        next = u->next;
        if (u->flags & 0x400000ULL) {
            u->flags &= ~1ULL;
            fn_8011FE74(u, 0);
            fn_800F39DC(u);
            n++;
        }
        u = next;
    }
    if (n > 0) {
        fn_8010D8B4(a, 2, Get30());
    }
    return 1;
}

int fn_800D9764(int a, int* ox, int* oy) {
    s8 x;
    s8 y;
    fn_8010CC50(a, &x, &y);
    *ox = x;
    *oy = y;
    return 0;
}

int fn_800D97C0(int a) {
    u8* p = fn_8010B46C(a);
    if (p && p[0] == 0) {
        return 1;
    }
    return 0;
}

u16 fn_800D9800(int a) {
    u8* p = fn_8010B46C(a);
    if (p) {
        return *(u16*)(p + 2);
    }
    return 0;
}

u16 fn_800D9834(int i) {
    u8* p = fn_8010B46C(i);
    if (p) {
        return ((u16*)(p + 4))[i];
    }
    return 0;
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

int fn_800D987C(int id, const char* s) {
    Unit* u = UnitId(id);
    u16 fl;
    u8 buf[0x100];
    if (u == 0 || u->person == 0) {
        return 0;
    }
    if (fn_8011F5B4(u) == 0) {
        return 0;
    }
    fl = OptFlags();
    {
        int x = u->x;
        int y = u->y;
        u8* o = buf;
        while (*s) {
            switch (*s++) {
            case '8':
                *o++ = 8;
                y--;
                break;
            case '2':
                *o++ = 4;
                y++;
                break;
            case '4':
                *o++ = 1;
                x--;
                break;
            case '6':
                *o++ = 2;
                x++;
                break;
            case 'U':
                fl |= 8;
                break;
            case 'D':
                fl |= 4;
                break;
            case 'L':
                fl |= 1;
                break;
            case 'R':
                fl |= 2;
                break;
            }
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

int fn_800D9AC8(int id, int ax, int ay);

int fn_800D9C80(const char** ps, int def);

int fn_800D9CE8(int id, const char* s);

int fn_800D9EB8(int id, int x, int y) {
    Unit* u = UnitId(id);
    if (u == 0 || u->person == 0) {
        return 0;
    }
    if (fn_8011F5B4(u) == 0) {
        return 0;
    }
    fn_80126EB0(u, (s8)x, (s8)y);
    fn_80114D00(&lbl_803EC898);
    fn_800F39DC(u);
    if (fn_80083B84(lbl_80384030) == 0) {
        fn_80081050(lbl_80384030, Parent30());
    }
    return 1;
}

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

int fn_800D9FA8(int id, int dir, int dur);

int fn_800DA1FC(int id, int x, int y, int dur);

int fn_800DA430(int id, int a, int dur);

int fn_800DA61C(int id, u8 v) {
    Unit* u = UnitId(id);
    UNIT_CHECK(u)
    OptGet()->b3D = 1;
    ((UX*)u)->bC6 = v;
    return 1;
}

int fn_800DA74C(int id, u8 r, u8 g, u8 b, u8 al) {
    Unit* u = UnitId(id);
    UColor c;
    UNIT_CHECK(u)
    {
        OptProc* p = OptGet();
        c.r = r;
        c.g = g;
        c.b = b;
        c.a = al;
        p->b3E = 1;
    }
    fn_800F3EB0(u, c);
    return 1;
}

int fn_800DA898(int id, const char* s) {
    int k;
    Unit* u = UnitId(id);
    UNIT_CHECK(u)
    k = -1;
    if (s && s[0]) {
        k = fn_800F080C(s);
    }
    OptGet()->b3F = 1;
    fn_800F3F30(u, k);
    return 1;
}

int fn_800DA9F4(int id, const char* s) {
    Unit* u = UnitId(id);
    int k;
    UNIT_CHECK(u)
    k = -1;
    if (s && s[0]) {
        s16* q = fn_800F0B04(s);
        if (q == 0) {
            return 0;
        }
        k = q[4];
    }
    if (k != ((UX*)u)->hDA) {
        fn_800F3F28(u, k);
        fn_800F74D0(u, 0);
        fn_800F39DC(u);
        OptGet()->b40 = 1;
    }
    return 1;
}

#pragma use_lmw_stmw off
int fn_800DAB6C(int id, int a, int b, int c) {
    Unit* u = UnitId(id);
    UNIT_CHECK(u)
    {
        OptProc* p = OptGet();
        f32 fa = a / 100.0f;
        f32 fb = b / 100.0f;
        f32 fc = c / 100.0f;
        p->b41 = 1;
        ((UX*)u)->f10 = fa;
        ((UX*)u)->f14 = fb;
        ((UX*)u)->f18 = fc;
    }
    return 1;
}

int fn_800DADA0(int id, int s, int scale, int dur, int x);
#pragma use_lmw_stmw on

int fn_800DACF8(int id, const char* s) {
    Unit* u;
    if (lbl_804CB700 & 0x8001) {
        return 0;
    }
    u = UnitId(id);
    UNIT_CHECK(u)
    fn_800F6604(u, s);
    return 1;
}

int fn_800DAF74(int id, int k) { return fn_800DADA0(id, k, -1, -1, 0); }

int fn_800DAF84(int id) {
    Unit* u = UnitId(id);
    UNIT_CHECK(u)
    OptGet()->b42 = 1;
    ((UX*)u)->h0 |= 0x20;
    return 1;
}

int fn_800DB0B0(int id) {
    Unit* u = UnitId(id);
    UNIT_CHECK(u)
    ((UX*)u)->h0 &= ~0x20;
    return 1;
}

int fn_800DB138(int id) {
    Unit* u = UnitId(id);
    UNIT_CHECK(u)
    if (lbl_804CB700 & 0x8001) {
        return 0;
    }
    fn_801039E8(u, Get30());
    return 1;
}

int fn_800DB214(int id) {
    Unit* u = UnitId(id);
    UNIT_CHECK(u)
    if (lbl_804CB700 & 0x8001) {
        fn_800F3B90(u, 3);
        return 0;
    }
    fn_80103A20(u, Get30());
    return 1;
}

int fn_800DB2FC(int id) {
    Unit* u;
    if (lbl_804CB700 & 0x8001) {
        return 0;
    }
    u = UnitId(id);
    UNIT_CHECK(u)
    fn_80103CE4(u, 2, -1, -1, Get30());
    return 1;
}

int fn_800DB3E4(int aid, int bid, int d) {
    Unit* a = UnitId(aid);
    Unit* b = UnitId(bid);
    int x;
    int y;
    if (a == 0 || fn_8011F5B4(a) == 0) {
        return 0;
    }
    if (b == 0 || fn_8011F5B4(b) == 0) {
        return 0;
    }
    x = b->x;
    y = b->y;
    if (x > a->x) {
        x += d;
    }
    if (x < a->x) {
        x -= d;
    }
    if (y > a->y) {
        y += d;
    }
    if (y < a->y) {
        y -= d;
    }
    fn_80126EB0(b, (s8)x, (s8)y);
    if (lbl_804CB700 & 0x8001) {
        fn_800F39DC(b);
        return 0;
    }
    fn_8010354C(a, b, x, y, Get30());
    return 1;
}

int fn_800DB56C(int id, int dir, int d) {
    Unit* u = UnitId(id);
    int x;
    int y;
    UNIT_CHECK(u)
    x = u->x;
    y = u->y;
    {
        int k;
        switch ((u8)dir) {
        case 1:
            k = -1;
            break;
        case 2:
            k = 1;
            break;
        default:
            k = 0;
            break;
        }
        x += d * k;
    }
    {
        int k;
        switch ((u8)dir) {
        case 4:
            k = 1;
            break;
        case 8:
            k = -1;
            break;
        default:
            k = 0;
            break;
        }
        y += d * k;
    }
    fn_80126EB0(u, (s8)x, (s8)y);
    fn_80114D00(&lbl_803EC898);
    fn_80100A04(u, x, y, Get30());
    return 1;
}

void fn_800DB6E0(Unit* u) { fn_801288D4(u); }

int fn_800DB6E4(int id, int v) {
    Unit* u = UnitId(id);
    if (u == 0 || u->person == 0) {
        return 0;
    }
    if (v) {
        if (fn_8011B77C(u->skills, lbl_804CA4EC) == 0) {
            fn_801288D4(u);
        }
    } else {
        if (fn_8011B77C(u->skills, lbl_804CA4EC)) {
            fn_801288D4(u);
        }
    }
    if (fn_8011F5B4(u)) {
        fn_800F74D0(u, 0);
        fn_800F39DC(u);
    }
    return 1;
}

int fn_800DB7B0(int id, int v) {
    Unit* u;
    if (lbl_804CB700 & 0x8001) {
        u = UnitId(id);
        if (u && u->person) {
            if (v) {
                if (fn_8011B77C(u->skills, lbl_804CA4EC) == 0) {
                    fn_801288D4(u);
                }
            } else {
                if (fn_8011B77C(u->skills, lbl_804CA4EC)) {
                    fn_801288D4(u);
                }
            }
            if (fn_8011F5B4(u)) {
                fn_800F74D0(u, 0);
                fn_800F39DC(u);
            }
        }
        return 0;
    }
    u = UnitId(id);
    UNIT_CHECK(u)
    if (v) {
        if (fn_8011B77C(u->skills, lbl_804CA4EC)) {
            return 0;
        }
    } else {
        if (fn_8011B77C(u->skills, lbl_804CA4EC) == 0) {
            return 0;
        }
    }
    {
        void* q = Get30();
        fn_8010395C(u, fn_801772EC(fn_800DB6E0, u, 1, q));
    }
    return 1;
}

u8 fn_800DB98C(int id) {
    Unit* u = UnitId(id);
    UNIT_CHECK(u)
    return fn_800F3FE4(u);
}

int fn_800DBA10(int id) {
    Unit* u;
    if (lbl_804CB700 & 0x8001) {
        return 1;
    }
    u = UnitId(id);
    if (u == 0 || fn_8011F5B4(u) == 0) {
        return 1;
    }
    if (fn_800FAFD4(u, 0)) {
        return 1;
    }
    return fn_80104C2C(u) == 0;
}

int fn_800DBAB4(int id) {
    Unit* u;
    if (lbl_804CB700 & 0x8001) {
        return 1;
    }
    u = UnitId(id);
    if (u == 0 || fn_8011F5B4(u) == 0) {
        return 1;
    }
    if (fn_800FAFD4(u, 1)) {
        return 1;
    }
    return fn_80104C2C(u) == 0;
}

static inline void SceneDirty() {
    u8* s = fn_800C3558();
    s[0x1C] = 1;
}

int fn_800DBB58(int aid, int bid) {
    Unit* a = UnitId(aid);
    Unit* b = UnitId(bid);
    if (a == 0 || fn_8011F5B4(a) == 0) {
        return 0;
    }
    if (b == 0 || fn_8011F5B4(b) == 0) {
        return 0;
    }
    if (a == b) {
        return 0;
    }
    {
        f32 fa = 0.015625f * ((UX*)a)->hC4;
        f32 fb = 0.015625f * ((UX*)b)->hC4;
        int x = a->x;
        int y = a->y;
        fn_80126EB0(a, b->x, (s8)*(u8*)&b->y);
        ((UX*)a)->hC4 = 64.0f * fb;
        fn_80126EB0(b, x, y);
        ((UX*)b)->hC4 = 64.0f * fa;
    }
    fn_80114D00(&lbl_803EC898);
    fn_800F39DC(a);
    fn_800F39DC(b);
    if (fn_80083B84(lbl_80384030) == 0) {
        fn_80081050(lbl_80384030, Parent30());
    }
    return 1;
}

int fn_800DBD48(u8 v) {
    OptGet()->b3D = 1;
    lbl_804CA4AC = v;
    return 1;
}

int fn_800DBE1C(int a) {
    fn_80062380(lbl_803CAB38, a);
    SceneDirty();
    return 1;
}

int fn_800DBE58() {
    fn_80062598(lbl_803CAB38, fn_8009E898());
    SceneDirty();
    return 1;
}

int fn_800DBE98(void* a) {
    fn_8010DB48(a);
    return 1;
}

int fn_800DBEBC(void* a) {
    fn_8010DC58(a);
    return 1;
}

int fn_800DBEE0() {
    fn_80134DB0();
    fn_80062380(lbl_803CAB38, 0);
    fn_80134E30();
    fn_80062454(lbl_803CAB38);
    fn_800620A8(lbl_803CAB38, (s8)lbl_803CAB38[0x9A], (s8)lbl_803CAB38[0x9B]);
    fn_8012FF30();
    return 1;
}

int fn_800DBF74(int v) {
    void* m = fn_8013B9A8();
    if (m == 0) {
        return 0;
    }
    {
        OptProc* p = OptGet();
        if (v) {
            p->b3A = 1;
            lbl_804CB700 &= ~0x1000;
            fn_80137988(m, 1);
        } else {
            p->b3A = 0;
            lbl_804CB700 |= 0x1000;
            fn_80137988(m, 0);
        }
    }
    return 1;
}

int fn_800DC0A8(int v) {
    void* m = fn_8013B9A8();
    if (m == 0) {
        return 0;
    }
    fn_80134E90(v);
    fn_80114D00(&lbl_803EC898);
    fn_8013A638(m);
    fn_8012D908();
    return 1;
}

static inline void MapTint(int a, int b, int c, UColor col) {
    fn_80134E98(a, b, c, col);
}

int fn_800DC114(int a, int b, int c, u8 r, u8 g, u8 bl);

int fn_800DC1B0(u8 v) {
    void* m = fn_8013B9A8();
    if (m == 0) {
        return 0;
    }
    lbl_804CB834 = v;
    fn_8013B8D0(m);
    SceneDirty();
    return 1;
}

u8 fn_800DC204() { return lbl_804CB834; }

static inline void ColSet(UColor* d, UColor c) {
    d->r = c.r;
    d->g = c.g;
    d->b = c.b;
    d->a = c.a;
}

int fn_800DC20C(int i, u8 r, u8 g, u8 b) {
    void* m = fn_8013B9A8();
    if (m == 0) {
        return 0;
    }
    {
        UColor c = {r, g, b, 0xFF};
        ColSet(&lbl_80413BF8[i], c);
    }
    fn_801364AC(m);
    SceneDirty();
    return 1;
}

int fn_800DC2CC(int i, u8 r, u8 g, u8 b) {
    void* m = fn_8013B9A8();
    if (m == 0) {
        return 0;
    }
    {
        UColor c = {r, g, b, 0xFF};
        ColSet(&lbl_80413BE8[i], c);
    }
    fn_801364AC(m);
    SceneDirty();
    return 1;
}

int fn_800DC38C(int a, int b, int d) {
    MapCtl* m = (MapCtl*)fn_8013B9A8();
    if (m == 0) {
        return 0;
    }
    fn_80146F40(m->o18, a, b, d / 16.666666f);
    return 1;
}

int fn_800DC424(int a, int b, int c) {
    MapCtl* m = (MapCtl*)fn_8013B9A8();
    if (m == 0) {
        return 0;
    }
    fn_8013AC48(m);
    if (a >= 0) {
        m->f6C = a;
    }
    if (b >= 0) {
        m->f70 = b;
    }
    if (c >= 0) {
        m->f74 = c;
    }
    fn_8013AE18(m);
    OptGet()->b4D = 1;
    return 1;
}

int fn_800DC5A8(int a, int b, int c) {
    FCam* m = fn_8012FCD0();
    if (m == 0) {
        return 0;
    }
    if (a <= -10000) {
        a = 0;
    }
    if (b <= -10000) {
        b = 0x28;
    }
    if (c <= -10000) {
        c = 0x10;
    }
    m->f4 = a;
    m->f8 = b;
    m->fC = c;
    m->f68 = 2.0f;
    fn_8012F58C(m);
    return 1;
}

int fn_800DC680(int a, int b, int c);

int fn_800DCAD4(int v) {
    FCam* m = fn_8012FCD0();
    if (m == 0) {
        return 0;
    }
    m->f68 = v;
    return 1;
}

int fn_800DCB34() {
    fn_801313E4(fn_8009E898());
    return 1;
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

TINT(fn_800DCB5C, 0)
TINT(fn_800DCC38, 1)
TINT(fn_800DCD14, 2)

int fn_800DCDF0(int a, int v) {
    if (v < 0) {
        fn_80131294(3, a, 0, 0.0f, 0.0f, 0.0f);
        return 1;
    }
    {
        Unit* u = UnitId(v);
        if (u && fn_8011F5B4(u)) {
            fn_80131294(3, a, u, 0.0f, 0.0f, 0.0f);
            return 1;
        }
    }
    return 0;
}

int fn_800DCEAC(int a, void* u) {
    fn_80131294(4, a, u, 0.0f, 0.0f, 0.0f);
    return 0;
}

int fn_800DCEEC(int a) {
    fn_8013144C(a);
    return 1;
}

int fn_800DCF10() {
    fn_80131490();
    return 1;
}

int fn_800DCF34() {
    fn_801314D4();
    return 1;
}

void fn_800DCF58() { fn_80131534(); }

void fn_800DCF5C(EffProc* p) {
    char buf[0x40];
    u8 m1[0x30];
    u8 m2[0x30];
    fn_80290DDC(buf, lbl_80366654);
    p->eff = (u8*)fn_80006E1C();
    fn_80009030(p->eff, fn_8017F37C(buf, lbl_80366654 + 9, 0));
    fn_80009090(p->eff, fn_8017F37C(buf, lbl_80366654 + 0xD, 0));
    fn_80006F20(p->eff);
    fn_80290DDC(buf, lbl_80366654 + 0x10, p->name);
    fn_80008F6C(p->eff, buf);
    lbl_804CB838 |= 4;
    fn_80312654(m2, 4.712389f, 'x');
    fn_803128AC(m1, p->x, p->y, p->z);
    fn_80312378(m1, m2, p->eff + 0x10);
}

void fn_800DD050(EffProc* p) {
    fn_80006EE0(p->eff);
    p->eff = 0;
    lbl_804CB838 &= ~4;
}

void fn_800DD094(EffProc* p) {
    fn_800081D4(p->eff);
    fn_80007C58(p->eff);
    fn_8000BF68(p->eff, 0);
    if (*(u32*)p->eff & 2) {
        fn_80083B78(p);
    }
}

#pragma use_lmw_stmw off
int fn_800DD0F0(const char* name, int x, int y, int z) {
    EffProc* p = (EffProc*)fn_80081050(lbl_80384110, fn_8009E898());
    strcpy(p->name, name);
    p->x = 0.5f + x;
    p->y = 0.5f + y;
    p->z = z;
    p->eff = 0;
    return 1;
}
#pragma use_lmw_stmw on

static inline BOOL EffBusy() {
    return fn_80083B84(lbl_80384110) != 0;
}

int fn_800DD1B8() {
    if (lbl_804CB700 & 0x8001) {
        fn_800846BC(lbl_80384110);
        return 0;
    }
    return EffBusy();
}

int fn_800DD20C() { return 0; }

int fn_800DD214(int x, int y, int t) {
    void* m = fn_8013B9A8();
    void* e;
    if (m == 0) {
        return 0;
    }
    e = fn_80135800(m, x, y, 0x200, 0x410);
    if (e == 0) {
        return 0;
    }
    switch (t) {
    case 0:
    case 4:
        fn_800661A0(lbl_803CB770, (s8)x, (s8)y, 0x28, 0);
        break;
    case 1:
    case 3:
        fn_8006625C(lbl_803CB770, (s8)x, (s8)y, 0x28);
        break;
    case 2:
        break;
    }
    switch (t) {
    case 0:
        if (lbl_804CB700 & 0x8001) {
            t = 4;
        }
        break;
    case 1:
        if (lbl_804CB700 & 0x8001) {
            t = 3;
        }
        break;
    case 2:
        if (lbl_804CB700 & 0x8001) {
            return 0;
        }
        break;
    }
    switch (t) {
    case 0:
    case 1:
    case 2:
        fn_801CAA24(e, Get30(), t);
        break;
    case 3:
    case 4:
        fn_801CAA24(e, 0, t);
        break;
    }
    return 1;
}

int fn_800DD3E4(int x, int y) {
    void* m = fn_8013B9A8();
    void* e;
    if (m == 0) {
        return 0;
    }
    e = fn_80135800(m, x, y, 0x80000, 0x10);
    if (e == 0) {
        return 0;
    }
    fn_8006625C(lbl_803CB770, (s8)x, (s8)y, 0x29);
    fn_801CA3E4(e, 1);
    fn_801379F8(m, 1);
    fn_8012D908();
    return 1;
}

int fn_800DD4A0(int x, int y) {
    void* m = fn_8013B9A8();
    void* e;
    if (m == 0) {
        return 0;
    }
    e = fn_80135800(m, x, y, 0x80000, 0x10);
    if (e == 0) {
        return 0;
    }
    fn_800661A0(lbl_803CB770, (s8)x, (s8)y, 0x29, 0);
    fn_801CA3E4(e, 0);
    fn_801379F8(m, 1);
    fn_8012D908();
    return 1;
}

int fn_800DD560(int x, int y, int v) {
    void* m = fn_8013B9A8();
    void* e;
    if (m == 0) {
        return 0;
    }
    e = fn_80135800(m, x, y, 0x80000, 0x10);
    if (e == 0) {
        return 0;
    }
    fn_801CA40C(e, v);
    OptGet()->b4C = 1;
    return 1;
}

int fn_800DD680(const char* name, int v) {
    MapCtl2* m = (MapCtl2*)fn_8013B9A8();
    u8* e;
    int off;
    int n;
    int i;
    if (m == 0) {
        return 0;
    }
    n = 0;
    i = 0;
    off = 0;
    for (; i < m->n; off += 0xD0, i++) {
        u32** q;
        e = m->tiles + off;
        q = (u32**)*(u32**)(e + 0x10);
        if (((u32*)q)[0xB8 / 4] & 0x80000) {
            if (fn_80291188(*(const char**)q, name) == 0) {
                fn_801CA40C(e, v);
                n++;
            }
        }
    }
    if (n > 0) {
        OptGet()->b4C = 1;
    }
    return n;
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

int fn_800DD7C4(int x, int y) {
    void* m = fn_8013B9A8();
    void* e;
    if (m == 0) {
        return 0;
    }
    e = fn_80135800(m, x, y, 0x1000, 0x10);
    if (e == 0) {
        return 0;
    }
    if (fn_801CA248(e) && fn_80066130(lbl_803CB770, (s8)x, (s8)y, 0x21)) {
        return 0;
    }
    fn_800661A0(lbl_803CB770, (s8)x, (s8)y, 0x21, 0);
    {
        u8* q = fn_80066130(lbl_803CB770, (s8)x, (s8)y, 4);
        if (q) {
            q[4] = 0;
        }
    }
    fn_801CA4FC(e, 0);
    e = fn_80135A54(m, x, y, 0x800, 0);
    if (e) {
        NotifyOpen(e);
    }
    fn_801379F8(m, 1);
    fn_8012D908();
    return 1;
}

int fn_800DD940(int x, int y) {
    void* m = fn_8013B9A8();
    void* e;
    if (m == 0) {
        return 0;
    }
    e = fn_80135800(m, x, y, 0x1000, 0x10);
    if (e == 0) {
        return 0;
    }
    if (fn_801CA260(e) && fn_80066130(lbl_803CB770, (s8)x, (s8)y, 0x21) == 0) {
        return 0;
    }
    fn_8006625C(lbl_803CB770, (s8)x, (s8)y, 0x21);
    {
        u8* q = fn_80066130(lbl_803CB770, (s8)x, (s8)y, 4);
        if (q) {
            q[4] = q[5];
        }
    }
    fn_801CA568(e, 0);
    e = fn_80135A54(m, x, y, 0x800, 0);
    if (e) {
        NotifyClose(e);
    }
    fn_801379F8(m, 1);
    fn_8012D908();
    return 1;
}

#pragma use_lmw_stmw off
int fn_800DDAB8(int x, int y) {
    void* m = fn_8013B9A8();
    void* v;
    void* e;
    if (m == 0) {
        return 0;
    }
    if (lbl_804CB700 & 0x8001) {
        fn_800DD7C4(x, y);
        return 0;
    }
    e = fn_80135800(m, x, y, 0x1000, 0x10);
    if (e == 0) {
        return 0;
    }
    if (fn_801CA248(e) && fn_80066130(lbl_803CB770, (s8)x, (s8)y, 0x21)) {
        return 0;
    }
    fn_800661A0(lbl_803CB770, (s8)x, (s8)y, 0x21, 0);
    {
        u8* q = fn_80066130(lbl_803CB770, (s8)x, (s8)y, 4);
        if (q) {
            q[4] = 0;
        }
    }
    {
        u8** t = fn_801181E8(&lbl_803EC898, (s8)x, (s8)y);
        if (t) {
            const char* s = *(const char**)(t[2] + 8);
            if (s) {
                v = fn_800E3A10(s, fn_8009E898());
                if (v) {
                    f32 h = fn_80114728(&lbl_803EC898, (s8)x, (s8)y);
                    fn_800E48AC(v, 0.5f + x, 0.5f + y, h);
                }
            }
        }
    }
    fn_8013E054(e, fn_8009E898());
    SceneDirty();
    return 1;
}
#pragma use_lmw_stmw on

int fn_800DDC7C(int x, int y) {
    void* m = fn_8013B9A8();
    void* e;
    if (m == 0) {
        return 0;
    }
    if (lbl_804CB700 & 0x8001) {
        fn_800DD940(x, y);
        return 0;
    }
    e = fn_80135800(m, x, y, 0x1000, 0x10);
    if (e == 0) {
        return 0;
    }
    if (fn_801CA260(e) && fn_80066130(lbl_803CB770, (s8)x, (s8)y, 0x21) == 0) {
        return 0;
    }
    fn_8006625C(lbl_803CB770, (s8)x, (s8)y, 0x21);
    {
        u8* q = fn_80066130(lbl_803CB770, (s8)x, (s8)y, 4);
        if (q) {
            q[4] = q[5];
        }
    }
    fn_8013E198(e, fn_8009E898());
    SceneDirty();
    return 1;
}

int fn_800DDDAC(int x, int y) {
    void* m = fn_8013B9A8();
    void* e;
    if (m == 0) {
        return 0;
    }
    e = fn_80135800(m, x, y, 0x200, 0x410);
    if (e == 0) {
        return 0;
    }
    fn_8013E314(e, fn_8009E898());
    fn_800661A0(lbl_803CB770, (s8)x, (s8)y, 0x23, 0);
    SceneDirty();
    return 1;
}

int fn_800DDE60(int x, int y) {
    void* m = fn_8013B9A8();
    void* e;
    if (m == 0) {
        return 0;
    }
    e = fn_80135800(m, x, y, 0x800, 0x10);
    if (e == 0) {
        return 0;
    }
    fn_800661A0(lbl_803CB770, (s8)x, (s8)y, 0x22, 0);
    NotifyOpen(e);
    fn_801379F8(m, 1);
    fn_8012D908();
    return 1;
}

int fn_800DDF54(int x, int y) {
    void* m = fn_8013B9A8();
    void* e;
    if (m == 0) {
        return 0;
    }
    e = fn_80135800(m, x, y, 0x800, 0x10);
    if (e == 0) {
        return 0;
    }
    fn_8006625C(lbl_803CB770, (s8)x, (s8)y, 0x22);
    NotifyClose(e);
    fn_801379F8(m, 1);
    fn_8012D908();
    return 1;
}

int fn_800DE044(int x, int y);

int fn_800DE1B8(int x, int y);

int fn_800DE324(int a, int b, int c, int d) {
    if (lbl_804CB700 & 0x8001) {
        d = 0;
    }
    fn_8013E34C(a, b, c, d / 16.666666f, 0);
    if (d == 0) {
        fn_80114D00(&lbl_803EC898);
        fn_801476E8();
    } else {
        SceneDirty();
    }
    return 1;
}

int fn_800DE3C0(int a, int b, int d) {
    if (lbl_804CB700 & 0x8001) {
        d = 0;
    }
    fn_8013E530(a, b, d / 16.666666f, 0);
    if (d == 0) {
        fn_80114D00(&lbl_803EC898);
        fn_801476E8();
    } else {
        SceneDirty();
    }
    return 1;
}

int fn_800DE45C(int x, int y) {
    void* m = fn_8013B9A8();
    if (m == 0) {
        return 0;
    }
    {
        TileEv* e = (TileEv*)fn_801358A8(m, x, y);
        if (e) {
            return e->x;
        }
    }
    return x;
}

int fn_800DE4C8(int x, int y) {
    void* m = fn_8013B9A8();
    if (m == 0) {
        return 0;
    }
    {
        TileEv* e = (TileEv*)fn_801358A8(m, x, y);
        if (e) {
            return e->y;
        }
    }
    return y;
}

int fn_800DE534(int v);

int fn_800DE5FC() { return 1; }

int fn_800DE604(int a, int x, int y) {
    void* m = fn_8013B9A8();
    TileEv* e;
    if (m == 0) {
        return 0;
    }
    e = (TileEv*)fn_80135A54(m, x, y, 0x40000, 0x10);
    if (e == 0) {
        return 0;
    }
    fn_800661A0(lbl_803CB770, e->x, (s8)*(u8*)&e->y, 0x24, 0);
    if (lbl_804CB700 & 0x8001) {
        fn_801CA300(e);
        return 0;
    }
    fn_801CAA24(e, fn_8009E898(), 0);
    SceneDirty();
    return 1;
}

int fn_800DE6D8(int x, int y, int v) {
    void* m = fn_8013B9A8();
    u8* e;
    if (m == 0) {
        return 0;
    }
    e = (u8*)fn_80135800(m, x, y, 0x800, 0x10);
    if (e == 0) {
        return 0;
    }
    if (v) {
        *e &= ~8;
    } else {
        *e |= 8;
    }
    fn_801379F8(m, 1);
    fn_8012D908();
    return 1;
}

int fn_800DE794(int x, int y);

int fn_800DE854(int x, int y, const char* s) {
    if (s && s[0]) {
        u8* q = fn_800661A0(lbl_803CB770, (s8)x, (s8)y, 0x10, 0);
        q[4] = fn_8011D1E4(s);
    } else {
        fn_8006625C(lbl_803CB770, (s8)x, (s8)y, 0x10);
    }
    return 1;
}

int fn_800DE8EC(int x, int y, const char* s) {
    if (s && s[0]) {
        u8* q = fn_800661A0(lbl_803CB770, (s8)x, (s8)y, 0x11, 0);
        q[4] = fn_8011D1E4(s);
    } else {
        fn_8006625C(lbl_803CB770, (s8)x, (s8)y, 0x11);
    }
    {
        void* m = fn_8013B9A8();
        if (m) {
            fn_801379F8(m, 0);
        }
    }
    return 1;
}

void fn_800DE998(PairProc* p) { fn_80133B10(p->a, p->b); }

int fn_800DE9A8(void* a, void* b) {
    PairProc* q = (PairProc*)fn_80081050(lbl_80384138, fn_8009E898());
    q->a = a;
    q->b = b;
    return 1;
}

int fn_800DE9FC() {
    fn_800846BC(lbl_80384138);
    return 1;
}

int fn_800DEA28(LoadProc* p) {
    if (lbl_804CB700 & 1) {
        return 0;
    }
    if (fn_800E272C(p->name)) {
        ObjH* q;
        if (p->b52) {
            q = (ObjH*)fn_800E3C04(p->name, 4);
        } else {
            q = (ObjH*)fn_800E3810(p->name, 4);
        }
        if (q) {
            q->d->h4 = p->h50;
            q->d->bC = 1;
            fn_80177418(fn_801773BC(fn_8009E898()), q);
        }
        return 0;
    }
    return 1;
}

int fn_800DEAE8(const char* s) {
    if (lbl_804CB700 & 1) {
        return 0;
    }
    {
        u16 id = fn_80175E5C();
        LoadProc* q = (LoadProc*)fn_800811E4(lbl_80384158, *(void**)(fn_800C3558() + 0x20));
        strcpy(q->name, s);
        q->h50 = id;
        q->b52 = 0;
        fn_800E24F8(s);
        SceneDirty();
        return id;
    }
}

int fn_800DEB88(const char* s) {
    u16 id = fn_80175E5C();
    LoadProc* q = (LoadProc*)fn_800811E4(lbl_80384158, *(void**)(fn_800C3558() + 0x20));
    strcpy(q->name, s);
    q->h50 = id;
    q->b52 = 1;
    fn_800E24F8(s);
    SceneDirty();
    return id;
}

static inline void* ObjGet(u32 id) {
    if (id == 0) {
        return 0;
    }
    if (id >= 0x10000) {
        return 0;
    }
    return fn_800E45B0((u16)id);
}

int fn_800DEC18(u32 id, int x, int y) {
    void* o = ObjGet(id);
    if (o == 0) {
        return 0;
    }
    {
        f32 fx = x;
        f32 fy = y;
        f32 z = 0.0f;
        if (fn_800E4674(o) == 0) {
            fx += 0.5f;
            fy += 0.5f;
            z = fn_80113F00(&lbl_803EC898, fx, fy);
        }
        fn_800E48AC(o, fx, fy, z);
    }
    return 1;
}

int fn_800DED44(u32 id, int x, int y, int z) {
    void* o = ObjGet(id);
    if (o == 0) {
        return 0;
    }
    {
        f32 fx = x / 100.0f;
        f32 fy = y / 100.0f;
        f32 fz = z / 100.0f;
        fz += fn_80113F00(&lbl_803EC898, fx, fy);
        fn_800E48AC(o, fx, fy, fz);
    }
    return 1;
}

int fn_800DEE80(u32 id, int a, int b, int c) {
    ObjH* o = (ObjH*)ObjGet(id);
    u8 m[0x30];
    if (o == 0) {
        return 0;
    }
    fn_8001D748(m, 1, a, b, c);
    fn_80312344(m, o->d->m68);
    return 1;
}

#pragma use_lmw_stmw off
int fn_800DF0B8(u32 id, int uid, int t, const char* s);
#pragma use_lmw_stmw on

int fn_800DF2C8(u32 id, int v) {
    ObjH* o = (ObjH*)ObjGet(id);
    if (o == 0) {
        return 0;
    }
    o->d->o9C = fn_800DF250;
    fn_800E48AC(o, 0.0f, 0.0f, v);
    return 1;
}

int fn_800DF368(u32 id, int v);

int fn_800DF438(u32 id, int v) {
    ObjH* o = (ObjH*)ObjGet(id);
    if (o == 0) {
        return 0;
    }
    {
        u32* q = &o->d->fl18;
        if (v) {
            if (q) {
                *q |= 0x2000;
            }
        } else {
            if (q) {
                *q &= ~0x2000;
            }
        }
    }
    return 1;
}

int fn_800DF4DC(u32 id, int v) {
    void* o = ObjGet(id);
    if (o == 0) {
        return 0;
    }
    fn_800E4AD4(o, v / 100.0f);
    return 1;
}

int fn_800DF56C(u32 id, u8 v) {
    ObjH* o = (ObjH*)ObjGet(id);
    if (o == 0) {
        return 0;
    }
    o->d->bF = v;
    return 1;
}

int fn_800DF5DC(u32 id, int v) {
    ObjH* o = (ObjH*)ObjGet(id);
    if (o == 0) {
        return 0;
    }
    o->d->h8 = v;
    return 1;
}

int fn_800DF64C(u32 id, int v) {
    ObjH* o = (ObjH*)ObjGet(id);
    if (o == 0) {
        return 0;
    }
    if (v < 0) {
        v = 0x98;
    }
    o->d->h6 = v;
    return 1;
}

int fn_800DF6C8(int id) {
    if (id < 0) {
        fn_800E4548();
        return 1;
    }
    {
        void* o = ObjGet(id);
        if (o) {
            fn_80081A90(o);
            return 1;
        }
    }
    return 0;
}

int fn_800DF738(u32 id, int d) {
    void* o = ObjGet(id);
    if (o) {
        fn_800E4B20(o, d / 16.666666f);
        return 1;
    }
    return 0;
}

int fn_800DF7D4(const char* s) {
    if (lbl_804CB700 & 1) {
        return 0;
    }
    fn_800E24F8(s);
    return 1;
}

int fn_800DF80C(int id) {
    if (lbl_804CB700 & 1) {
        return 0;
    }
    if (id < 0) {
        if (fn_800E44CC() == 0) {
            return 0;
        }
    } else if (ObjGet(id) == 0) {
        return 0;
    }
    return 1;
}

int fn_800DF894(int a, int b, int c) {
    if (lbl_804CB700 & 0x8001) {
        return 0;
    }
    {
        void* q = fn_8009E898();
        fn_8013C14C(a, b / 16.666666f, c, q);
    }
    return 1;
}

int fn_800DF940() {
    fn_8013C200();
    return 1;
}

int fn_800DF964(int v) {
    lbl_804CB838 = v ? (lbl_804CB838 & 0xFE) : (lbl_804CB838 | 1);
    return 1;
}

int fn_800DF984(int v) {
    lbl_804CB838 = v ? (lbl_804CB838 | 4) : (lbl_804CB838 & ~4);
    return 1;
}

int fn_800DF9A4(int v) {
    lbl_804CB838 = v ? (lbl_804CB838 | 8) : (lbl_804CB838 & ~8);
    return 1;
}

int fn_800DF9C4(int v) {
    lbl_804CB838 = v ? (lbl_804CB838 & ~2) : (lbl_804CB838 | 2);
    return 1;
}

int fn_800DF9E4(int id, int v) {
    Unit* u = UnitId(id);
    if (u == 0 || u->person == 0) {
        return 0;
    }
    if (v) {
        u->flags |= 1ULL;
    } else {
        u->flags &= ~1ULL;
    }
    return 1;
}

int fn_800DFA60(int id, int v) {
    Unit* u = UnitId(id);
    if (u == 0 || u->person == 0) {
        return 0;
    }
    if (v) {
        if (fn_8011B77C(u->skills, lbl_804CA5A8) == 0) {
            fn_8011AEA0(u->skills, lbl_804CA5A8, 2, 0);
        }
    } else {
        if (fn_8011B77C(u->skills, lbl_804CA5A8)) {
            fn_8011B430(u->skills, lbl_804CA5A8);
            fn_8011A36C(u->skills);
        }
    }
    fn_800F5090(u);
    return 1;
}

int fn_800DFB28(int id, int v) {
    Unit* u = UnitId(id);
    UNIT_CHECK(u)
    if (v) {
        ((UX*)u)->h0 |= 0x800;
    } else {
        ((UX*)u)->h0 &= ~0x800;
    }
    OptGet()->b43 = 1;
    return 1;
}

void fn_800DFC70() { fn_8007E030(0); }

int fn_800DFC78(int v) {
    if (v) {
        fn_80081050(lbl_80384170, fn_8009E898());
    } else {
        fn_800846BC(lbl_80384170);
    }
    return 1;
}

int fn_800DFCC4() {
    int x;
    int y;
    if (fn_801B5DD8(&x, &y)) {
        return x;
    }
    return 0;
}

int fn_800DFD00() {
    int x;
    int y;
    if (fn_801B5DD8(&x, &y)) {
        return y;
    }
    return 0;
}

int fn_800E0284(int x, int y, u8 r, u8 g, u8 b) {
    if (lbl_804CB700 & 0x8001) {
        return 0;
    }
    {
        PointProc* p = (PointProc*)fn_80081050(lbl_80384188, fn_8009E898());
        p->x = x;
        p->y = y;
        p->r = r;
        p->g = g;
        p->b = b;
    }
    return 1;
}

void fn_800E0434() {
    MapHide* m = (MapHide*)fn_8013B9A8();
    if (m) {
        m->flB4 |= 0x80000000;
    }
}

int fn_800E0468(int d) {
    MapHide* m = (MapHide*)fn_8013B9A8();
    if (m == 0) {
        return 0;
    }
    if ((lbl_804CB700 & 0x8001) || d == 0) {
        m->flB4 |= 0x80000000;
    } else {
        fn_800C835C(7, d);
        fn_80081194(lbl_803841AC, fn_8009E898());
        SceneDirty();
    }
    return 1;
}

void fn_800E04F8() {
    MapHide* m = (MapHide*)fn_8013B9A8();
    if (m) {
        m->flB4 &= 0x7FFFFFFF;
    }
}

int fn_800E052C(int d) {
    MapHide* m = (MapHide*)fn_8013B9A8();
    if (m == 0) {
        return 0;
    }
    if ((lbl_804CB700 & 0x8001) || d == 0) {
        m->flB4 &= 0x7FFFFFFF;
    } else {
        fn_800C835C(7, d);
        fn_80081194(lbl_803841C8, fn_8009E898());
        SceneDirty();
    }
    return 1;
}

#pragma use_lmw_stmw off
int fn_800E0C14(int a, s16 b, u8 c, int d) {
    int id;
    int t = d / 16.666666f;
    PfxObj* o;
    if (lbl_804CB700 & 0x8001) {
        t = 0;
    }
    o = (PfxObj*)fn_8017C218(a, fn_8009E898());
    if (o) {
        id = fn_80175E5C();
        o->d->h28 = b;
        o->d->b25 = c;
        fn_8017C1E0(o, t);
        o->id3C = id;
        return (u16)id;
    }
    return 0;
}
#pragma use_lmw_stmw on

int fn_800E0D78(int id, int d) {
    int t = d / 16.666666f;
    if (lbl_804CB700 & 0x8001) {
        t = 0;
    }
    if (id < 0) {
        fn_8017C2E8();
    } else {
        void* o = fn_8017C2B0(id);
        if (o) {
            fn_8017C1AC(o, t);
            return 1;
        }
    }
    return 0;
}

u8 fn_800E0E10(s8 x, s8 y) {
    u8* q = fn_80066130(lbl_803CB770, x, y, 4);
    if (q) {
        return q[4];
    }
    return 0;
}

u8 fn_800E0E60(s8 x, s8 y) {
    u8* q = fn_80066130(lbl_803CB770, x, y, 4);
    if (q) {
        return q[5];
    }
    return 0;
}

int fn_800E0EB0(int v) {
    fn_80006D00(0.01f * v);
    OptGet()->b44 = 1;
    return 1;
}

int fn_800E0F9C(int id, int v) {
    Unit* u = UnitId(id);
    if (u == 0) {
        return 0;
    }
    fn_80026CD8(lbl_803C8E80, u, -1);
    fn_8002C170(lbl_803C8E80);
    fn_8002BE64(lbl_803C8E80, v);
    fn_800262D8(lbl_803C8E80 + 0xDE0);
    fn_800E7260(fn_8009E898(), 0);
    SceneDirty();
    return 1;
}
}
