/* fn_800DA430: functionally equal (regs, 8 of 123 words differ in registers only). Helpers from fn_800D7D74.cpp (exported bodies removed), body from wip/round12.cpp. */
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
extern u32 lbl_804CA4EC;

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
extern u32 lbl_804CA5A8;
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
void fn_801484B4(int a);
void fn_801050A8();
int fn_8011F5B4(Unit*);
void fn_80104ABC(Unit*);
int fn_80104F18();
int fn_80104C2C(Unit*);
int fn_800F0994(const char*);
f32 fn_801142F0(Map*, f32, f32);
f32 fn_80113F00(Map*, f32, f32);
void fn_8010D8B4(int, int, void*);
u8* fn_80060728(u8*);
void fn_8010DE10(int, int);
void fn_8010D018(int);
void fn_8011FE74(Unit*, int);
void fn_800F39DC(Unit*);
void fn_8010CC50(int, s8*, s8*);
u8* fn_8010B46C(int);
void fn_80126EB0(Unit*, int, int);
void fn_800F4B94(Unit*, int);
void fn_8010316C(Unit*, int, int, int, int);
void fn_80103410(Unit*, void*, int, void*);
void fn_80114D00(Map*);
void* fn_8010B964(Unit*, s8*, s8*, int, int);
int fn_800FC09C(Unit*, f32);
void fn_80102E10(Unit*, int, u8, void*, f32);
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
void fn_80103CE4(Unit*, int, int, int, void*);
void fn_8010354C(Unit*, Unit*, int, int, void*);
void fn_80100A04(Unit*, int, int, void*);
void fn_801288D4(Unit*);
int fn_8011B77C(void*, u32);
void* fn_801772EC(void*, Unit*, int, void*);
void fn_8010395C(Unit*, void*);
u32 fn_800F3FE4(Unit*);
int fn_800FAFD4(Unit*, int);
void* fn_80062380(u8*, int);
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
void fn_80131294(int, int, void*, f32, f32, f32);
void fn_8013144C(int a);
void fn_80131490();
void fn_801314D4();
void fn_80131534();
void* fn_80006E1C();
void fn_80009030(void*, void*);
void fn_80009090(void*, void*);
void* fn_8017F37C(char*, const char*, int);
void fn_80006F20(void*);
int fn_80290DDC(char*, const char*, ...);
void fn_80008F6C(void*, char*);
void fn_80312654(void*, f32, int);
void fn_803128AC(void*, f32, f32, f32);
void fn_80312378(void*, void*, void*);
void fn_80006EE0(void*);
void fn_800081D4(void*);
void fn_80007C58(void*);
void fn_8000BF68(void*, int);
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
void fn_8013E34C(int, int, int, int, int);
void fn_801476E8();
int fn_800DD7C4(int, int);
int fn_800DD940(int, int);
void fn_8013E530(int, int, int, int);
void* fn_801358A8(void*, int, int);
void fn_801CA33C(void*, int, int);
void fn_8013B2B8(void*);
void fn_801CA300(void*);
void fn_8013C80C(int, int, int, void*);
u8 fn_8011D1E4(const char*);
void fn_80133B10(void*, void*);
int fn_800E272C(char*);
void* fn_800E3C04(char*, int);
void* fn_800E3810(char*, int);
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
void fn_800E7260(void*, int);
void fn_800E4AD4(void*, f32);
void fn_800E4B20(void*, int);
int fn_800E44CC();
void fn_8013C14C(f32, int, int, void*);
void fn_8013C200();
void fn_8011AEA0(void*, u32, int, int);
void fn_8011B430(void*, u32);
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
u8 fn_800D7D74();

int fn_800D7DB0(u8 v);

void fn_800D7E74(void* p);

void fn_800D7EB8(int a);


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
void fn_800D7EBC();


static inline Unit* UnitId(int id) {
    id = (u8)id;
    if (id) {
        return &lbl_804CB810[id - 1];
    }
    return 0;
}
int fn_800D7F14(int x);


static inline BOOL Has30() {
    return fn_80083B84(lbl_80384030) != 0;
}
int fn_800D7F98(int x);

int fn_800D805C();

int fn_800D8124();


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

int fn_800D8498(const char* s);

s16 fn_800D858C();

int fn_800D85C8(int v);

s16 fn_800D868C();

int fn_800D86C8(int v);

s16 fn_800D878C();

int fn_800D88AC(int v);

int fn_800D8990(int v);

int fn_800D8A68();

int fn_800D8B34();

int fn_800D8C00();

int fn_800D8CC8(int v);

int fn_800D8D8C(s8 x, s8 y);

int fn_800D8E00(s8 x, s8 y);

int fn_800D8E74(int v);

u16 fn_800D8F4C();

int fn_800D8F88(const char* s);

s16 fn_800D907C();

int fn_800D90B8(int v);


#define GLOBSET(name, g) \
    int name(int v) { \
        OptGet(); \
        g = v != 0; \
        return 1; \
    }

int fn_800D9588(int a, int b);

int fn_800D9610(int a, int b);

void fn_800D9638(int a);

int fn_800D967C(int a);

int fn_800D9764(int a, int* ox, int* oy);

int fn_800D97C0(int a);

u16 fn_800D9800(int a);

u16 fn_800D9834(int i);


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
int fn_800D987C(int id, const char* s);


int fn_800D9AC8(int id, int ax, int ay);

int fn_800D9C80(const char** ps, int def);

int fn_800D9CE8(int id, const char* s);
int fn_800D9EB8(int id, int x, int y);


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
int fn_800DA61C(int id, u8 v);

int fn_800DA74C(int id, u8 r, u8 g, u8 b, u8 al);

int fn_800DA898(int id, const char* s);

int fn_800DA9F4(int id, const char* s);


#pragma use_lmw_stmw off

int fn_800DAB6C(int id, int a, int b, int c);


int fn_800DADA0(int id, int s, int scale, int dur, int x);
#pragma use_lmw_stmw on

int fn_800DACF8(int id, const char* s);

int fn_800DAF74(int id, int k);

int fn_800DAF84(int id);

int fn_800DB0B0(int id);

int fn_800DB138(int id);

int fn_800DB214(int id);

int fn_800DB2FC(int id);

int fn_800DB3E4(int aid, int bid, int d);

int fn_800DB56C(int id, int dir, int d);

void fn_800DB6E0(Unit* u);

int fn_800DB6E4(int id, int v);

int fn_800DB7B0(int id, int v);

u8 fn_800DB98C(int id);

int fn_800DBA10(int id);

int fn_800DBAB4(int id);


static inline void SceneDirty() {
    u8* s = fn_800C3558();
    s[0x1C] = 1;
}
int fn_800DBB58(int aid, int bid);

int fn_800DBD48(u8 v);

int fn_800DBE1C(int a);

int fn_800DBE58();

int fn_800DBE98(void* a);

int fn_800DBEBC(void* a);

int fn_800DBEE0();

int fn_800DBF74(int v);

int fn_800DC0A8(int v);


static inline void MapTint(int a, int b, int c, UColor col) {
    fn_80134E98(a, b, c, col);
}

int fn_800DC114(int a, int b, int c, u8 r, u8 g, u8 bl);
int fn_800DC1B0(u8 v);

u8 fn_800DC204();


static inline void ColSet(UColor* d, UColor c) {
    d->r = c.r;
    d->g = c.g;
    d->b = c.b;
    d->a = c.a;
}
int fn_800DC20C(int i, u8 r, u8 g, u8 b);

int fn_800DC2CC(int i, u8 r, u8 g, u8 b);

int fn_800DC38C(int a, int b, int d);

int fn_800DC424(int a, int b, int c);

int fn_800DC5A8(int a, int b, int c);


int fn_800DC680(int a, int b, int c);
int fn_800DCAD4(int v);

int fn_800DCB34();


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

int fn_800DCDF0(int a, int v);

int fn_800DCEAC(int a, void* u);

int fn_800DCEEC(int a);

int fn_800DCF10();

int fn_800DCF34();

void fn_800DCF58();

void fn_800DCF5C(EffProc* p);

void fn_800DD050(EffProc* p);

void fn_800DD094(EffProc* p);


#pragma use_lmw_stmw off

int fn_800DD0F0(const char* name, int x, int y, int z);

#pragma use_lmw_stmw on

static inline BOOL EffBusy() {
    return fn_80083B84(lbl_80384110) != 0;
}
int fn_800DD1B8();

int fn_800DD20C();

int fn_800DD214(int x, int y, int t);

int fn_800DD3E4(int x, int y);

int fn_800DD4A0(int x, int y);

int fn_800DD560(int x, int y, int v);

int fn_800DD680(const char* name, int v);


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

int fn_800DDAB8(int x, int y);

#pragma use_lmw_stmw on

int fn_800DDC7C(int x, int y);

int fn_800DDDAC(int x, int y);

int fn_800DDE60(int x, int y);

int fn_800DDF54(int x, int y);


int fn_800DE044(int x, int y);

int fn_800DE1B8(int x, int y);
int fn_800DE324(int a, int b, int c, int d);

int fn_800DE3C0(int a, int b, int d);

int fn_800DE45C(int x, int y);

int fn_800DE4C8(int x, int y);


int fn_800DE534(int v);
int fn_800DE5FC();

int fn_800DE604(int a, int x, int y);

int fn_800DE6D8(int x, int y, int v);


int fn_800DE794(int x, int y);
int fn_800DE854(int x, int y, const char* s);

int fn_800DE8EC(int x, int y, const char* s);

void fn_800DE998(PairProc* p);

int fn_800DE9A8(void* a, void* b);

int fn_800DE9FC();

int fn_800DEA28(LoadProc* p);

int fn_800DEAE8(const char* s);

int fn_800DEB88(const char* s);


static inline void* ObjGet(u32 id) {
    if (id == 0) {
        return 0;
    }
    if (id >= 0x10000) {
        return 0;
    }
    return fn_800E45B0((u16)id);
}
int fn_800DEC18(u32 id, int x, int y);

int fn_800DED44(u32 id, int x, int y, int z);

int fn_800DEE80(u32 id, int a, int b, int c);


#pragma use_lmw_stmw off
int fn_800DF0B8(u32 id, int uid, int t, const char* s);
#pragma use_lmw_stmw on

int fn_800DF2C8(u32 id, int v);


int fn_800DF368(u32 id, int v);
int fn_800DF438(u32 id, int v);

int fn_800DF4DC(u32 id, int v);

int fn_800DF56C(u32 id, u8 v);

int fn_800DF5DC(u32 id, int v);

int fn_800DF64C(u32 id, int v);

int fn_800DF6C8(int id);

int fn_800DF738(u32 id, int d);

int fn_800DF7D4(const char* s);

int fn_800DF80C(int id);

int fn_800DF894(int a, int b, int c);

int fn_800DF940();

int fn_800DF964(int v);

int fn_800DF984(int v);

int fn_800DF9A4(int v);

int fn_800DF9C4(int v);

int fn_800DF9E4(int id, int v);

int fn_800DFA60(int id, int v);

int fn_800DFB28(int id, int v);

void fn_800DFC70();

int fn_800DFC78(int v);

int fn_800DFCC4();

int fn_800DFD00();

int fn_800E0284(int x, int y, u8 r, u8 g, u8 b);

void fn_800E0434();

int fn_800E0468(int d);

void fn_800E04F8();

int fn_800E052C(int d);


#pragma use_lmw_stmw off

int fn_800E0C14(int a, s16 b, u8 c, int d);

#pragma use_lmw_stmw on

int fn_800E0D78(int id, int d);

u8 fn_800E0E10(s8 x, s8 y);

u8 fn_800E0E60(s8 x, s8 y);

int fn_800E0EB0(int v);

int fn_800E0F9C(int id, int v);

}

/* ---- from build/tmp/r18egkr/r12b_frag.cpp ---- */
extern "C" {
/* fn_800DA430 (fn_800D7D74.cpp): 8 words: dur and flag swap r29/r30 */
int fn_800DA430(int id, int a, int dur) {
    /*P*/
    int fl;
    int d2;
    Unit* u;
/*E*/
    id = (u8)id;
    if (id) {
        u = &lbl_804CB810[id - 1];
    } else {
        u = 0;
    }
    UNIT_CHECK(u)
    d2 = TurnFrames(u, a, dur);
    fl = 0;
    if (TurnSnap(u)) {
        fl |= 1;
    }
    if ((lbl_804CB700 & 0x8001) || d2 == 0) {
        fn_80102E10(u, 0, fl, 0, a);
    } else {
        fn_80102E10(u, d2, fl, Get30(), a);
    }
    return 1;
}

/* fn_800D9FA8 (fn_800D7D74.cpp): 16 words: unit, dir and flag rotate */
static inline int fn_800D9FA8_i(int id, int dir, int dur) {

    Unit* u = UnitId(id);
    int a;
    UNIT_CHECK(u)
    switch ((u8)dir) {
    case 4:
        a = 0;
        break;
    case 6:
        a = 0x2D;
        break;
    case 2:
        a = 0x5A;
        break;
    case 10:
        a = 0x87;
        break;
    case 8:
        a = 0xB4;
        break;
    case 9:
        a = 0xE1;
        break;
    case 1:
        a = 0x10E;
        break;
    case 5:
        a = 0x13B;
        break;
    default:
        a = 0;
        break;
    }
    dur = TurnFrames(u, a, dur);
    dir = 0;
    if (TurnSnap(u)) {
        dir |= 1;
    }
    if ((lbl_804CB700 & 0x8001) || dur == 0) {
        fn_80102E10(u, 0, dir, 0, a);
    } else {
        fn_80102E10(u, dur, dir, Get30(), a);
    }
    return 1;
}




/* fn_800DA1FC (fn_800D7D74.cpp): 13 words: y and dur swap r28/r30 */
static inline int fn_800DA1FC_i(int id, int x, int dur, int y) {

    Unit* u = UnitId(id);
    UNIT_CHECK(u)
    y = fn_800FB100(u, 0.5f + x, 0.5f + y);
    dur = TurnFrames(u, y, dur);
    x = 0;
    if (TurnSnap(u)) {
        x |= 1;
    }
    if ((lbl_804CB700 & 0x8001) || dur == 0) {
        fn_80102E10(u, 0, x, 0, y);
    } else {
        fn_80102E10(u, dur, x, Get30(), y);
    }
    return 1;
}
}
