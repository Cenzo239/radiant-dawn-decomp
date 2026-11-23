#ifndef RE_800E5DE4_EVPROC_H
#define RE_800E5DE4_EVPROC_H

#include "game/rE_800E5DE4/types.h"

extern char* strcpy(char*, const char*);

extern void* fn_800D68BC(void);

extern int fn_8002DD1C(void*);

extern int fn_800F0994(char*);

extern void fn_801CE800(void*);

extern int fn_801CEAE0(void*);

extern void fn_801CEC98(void*);

extern Handle* fn_800D683C(void*);

extern Handle* fn_800D6840(void*);

extern int fn_8011F600(void*);

extern void fn_80083DC4(void*, int);

extern u8 lbl_803C8E80[];

extern u8 lbl_8036707C[];

extern void* fn_8012FCD0(void);

extern void fn_800FAFF0(void*, int);

extern void fn_800F651C(void*, int);

extern f32 lbl_804CD928;

extern f32 lbl_804CD92C;

#if TARGET_PC
extern FE10_PROTO void fn_80102928(void*, int, int, int, void *);

extern FE10_PROTO void fn_80102CD8(void*, void *, void *, void *);
#else
extern void fn_80102928(void*, int, int, int, int);

extern void fn_80102CD8(void*, int, int, int);
#endif

extern void fn_80103304(void*, void*);

extern void fn_800FB228(void*, int);

extern void fn_80083B78(void*);

extern int fn_800FAFD4(void*, int);

extern int fn_800FAE98(void*);

extern EvCmd* fn_800E3810(char*, void*);

extern void fn_800E48AC(EvCmd*, f32, f32, f32);

static inline char* SubStr40(EvSub* s) {
    EvSubObj* o = s->obj;
    return o ? o->str40 : NULL;
}

static inline char* SubStr44(EvSub* s) {
    EvSubObj* o = s->obj;
    return o ? o->str44 : NULL;
}

static inline char* SubStr48(EvSub* s) {
    EvSubObj* o = s->obj;
    return o ? o->str48 : NULL;
}

extern void fn_800E4548(void*);

extern int fn_801CE5B8(Handle*);

extern void fn_80103D50(void*, int);

extern int fn_800F7724(void*);

extern int fn_8011F428(void*);

extern void fn_80103A20(void*, void*);

extern void fn_801039E8(void*, void*);

extern EvSub* fn_80030CF4(UnitObj*);

extern void fn_800E24F8(char*);

extern Handle* fn_801D0784(void*, int);

#if TARGET_PC
extern FE10_PROTO void fn_8010301C(void*, void*, int, int, void *);

extern FE10_PROTO void fn_801030B8(void*, int, int, int, int, void *);
#else
extern void fn_8010301C(void*, void*, int, int, void*);

extern void fn_801030B8(void*, int, int, int, int, void*);
#endif

extern void fn_800EFB6C(Handle*, Handle*, void*, int);

extern int fn_80008E28(void*, int);

extern int fn_801D049C(void*);

extern void fn_800D5B20(Handle*);

extern int fn_800E46C4(EvCmd*, int);

extern void fn_800EFEB8(Handle*, int, void*);

extern Vec fn_800F7790(void*);

extern void fn_800EE6CC(Vec, int, void*);

extern void fn_80103234(void*, int, int, void*);

extern void fn_800E5CA8(EvCmd*);

extern void fn_800E28E4(EvCmd*);

extern Vec fn_800D5C44(Handle*);

extern Vec fn_800D5B4C(Handle*);

extern void fn_800EE270(Vec, void*);

extern void fn_802549C4(char*, Vec*, f32);

extern f32 lbl_804CD930;

static inline void PlayAt(Handle* h) {
    Vec v;
    Vec w;
    v = fn_800D5B4C(h);
    w.x = v.x;
    w.y = v.y;
    w.z = v.z;
    fn_802549C4((char*)lbl_8036707C + 3, &w, lbl_804CD930);
}

extern void fn_80108CC0(void*, void*, int);

extern void fn_80114D00(void*);

extern void fn_801484B4(void*);

extern u8 lbl_803EC898[];

extern void fn_800F6604(void*, char*);

extern void fn_80102C6C(void*, char*, int, int, int);

extern EvCmd* fn_800E3A10(char*, EvProc*);

extern void fn_800E4904(EvCmd*, int, void*);

extern void fn_800E5BC0(EvCmd*, UnitObj*, UnitObj*);

static inline UnitObj* HandleObj(Handle* h) {
    return h ? h->obj : NULL;
}

static inline void EvCmd_Setup(EvCmd* a, UnitObj* u1, UnitObj* u2) {
    fn_800E4904(a, 0, u1);
    fn_800E4904(a, 1, u2);
    fn_800E5BC0(a, u1, u2);
    a->ctl->flags |= 0x400;
}

static inline EvCmd* EvProc_CreateAnim(EvProc* p) {
    EvCmd* a = fn_800E3A10(p->sub ? SubStr44(p->sub) : p->name, p);
    if (a) {
        UnitObj* u1 = HandleObj(p->h1);
        UnitObj* u2 = HandleObj(p->h2);
        EvCmd_Setup(a, u1, u2);
        return a;
    }
    return NULL;
}

/* Event-process factories: allocate a process of the given class (vtable/
 * type descriptor lbl_803843xx) under a parent and initialise it with a
 * finish callback. */
extern EvProc* fn_80081194(void* type, void* parent);

extern u8 lbl_80384300[];

extern u8 lbl_80384330[];

extern u8 lbl_80384398[];

extern u8 lbl_803843F8[];

extern u8 lbl_80384428[];

extern u8 lbl_80384488[];

extern u8 lbl_803845B0[];

extern u8 lbl_80384530[];

extern int fn_80007630(void*, char*);

extern Vec fn_800076E8(void*, int);

extern void fn_800E48C8(EvCmd*, Vec);

typedef struct UnitList {
    s32 count;
    u8 pad4[0x1204];
} UnitList;

extern UnitList lbl_803E7320;

extern void* fn_800CFD18(UnitList*, int);

extern u8* fn_800CFB0C(void*);

extern f32 lbl_804CD934;

extern f32 fn_800FB100(void*, f32, f32);

#if TARGET_PC
extern FE10_PROTO void fn_80102E10(void*, int, void *, f32, void *);
#else
extern void fn_80102E10(void*, int, int, f32, int);
#endif

extern void fn_800E5878(EvCmd*, void*);

extern u8 lbl_803846C0[];

extern void fn_800E48F0(EvCmd*, int, int);

extern u8 lbl_80384740[];

extern u8 lbl_80384778[];

extern void fn_800D6C44(int, int, int);

extern u8 lbl_803847D0[];

extern u8 lbl_80384854[];

#if TARGET_PC
extern FE10_PROTO void fn_80103CE4(void*, u16, void *, void *, void*);
#else
extern void fn_80103CE4(void*, u16, int, int, void*);
#endif

extern u8 lbl_80384898[];

extern void* fn_8013B9A8(void);

extern void* fn_80135800(void*, int, int, int, int);

extern void fn_801CB920(void*, void*, GXColor*, int);

extern const GXColor lbl_804CD940;

extern void fn_800E57B4(EvCmd*, int, int);

extern u8 lbl_80384900[];

extern void fn_800E5BB0(EvCmd*, UnitObj*);

extern void fn_800E49AC(EvCmd*, f32);

extern void fn_800E8F10(EvCmd*);

extern u8 lbl_80384980[];

static inline BOOL StateValid(Handle* h, EvProc* p) {
    if (h->unkE < 0) {
        switch (p->u78.b) {
        case 0:
        case 1:
        case 2:
            return 1;
        }
    }
    return 0;
}

static inline void EvProc_ShowState(EvProc* p) {
    Handle* h = p->h2;
    if (StateValid(h, p)) {
        void* a = HandleActor(h);
        if (a) {
            fn_800F6604(a, (char*)lbl_8036707C + 0x11);
        }
    }
    fn_800D5B20(p->h2);
}

typedef struct ShooterCfg {
    u8 pad0[0x11];
    s8 x;    /* 0x11 */
    s8 y;    /* 0x12 */
    s8 tx;   /* 0x13 */
    s8 ty;   /* 0x14 */
    u8 pad15[0x130 - 0x15];
} ShooterCfg;

extern ShooterCfg lbl_803CA870;

extern u8* fn_80135A54(void*, int, int, int, int);

extern char* fn_800D621C(void*);

extern f32 fn_80176A4C(f32, f32, f32, f32);

extern void fn_801CAD54(void*, void*, int, f32);

extern void fn_801CA2C4(void*);

#if TARGET_PC
extern FE10_PROTO void fn_801CAA24(void*, void *, int);
#else
extern void fn_801CAA24(void*, int, int);
#endif

extern void fn_800620A8(void*, f32, f32);

extern u8 lbl_803CAB38[];

extern int fn_80008C98(u32*, int);

extern void fn_8000987C(void*, GXColor*);

extern void fn_8012F5CC(void*, int);

extern void fn_8017DB90(int, int, int, int, EvCmd*);

static inline void SpawnDamageFx(char* name, void* parent, int x, int y, int dmg) {
    EvCmd* c = fn_800E3A10(name, parent);
    if (c) {
        fn_800E57B4(c, x, y);
        fn_800E49AC(c, dmg);
        c->ctl->onEvent = fn_800E28E4;
        fn_8017DB90(x, y, 0, 0, c);
    }
}

extern u8 lbl_80384A04[];

extern u8 lbl_80384AB8[];

/* Battle-sequence process (different class from EvProc). */
typedef struct BtlProc {
    u8 pad0[0x30];
    u8* unk30;   /* 0x30 */
    Handle* h1;  /* 0x34 */
    Handle* h2;  /* 0x38 */
    u8 pad3C[4];
    u8 unk40;    /* 0x40 */
    u8 unk41;    /* 0x41 */
    u8 unk42;    /* 0x42 */
    u8 pad43;
    u8 unk44;    /* 0x44 */
    u8 unk45;    /* 0x45 */
    u8 unk46;    /* 0x46 */
    u8 pad47;
    s8 unk48;    /* 0x48 */
} BtlProc;

extern void fn_800EFBCC(void);

extern void fn_801CEAD0(void*);

extern void fn_800D6724(void*);

#if TARGET_PC
extern FE10_PROTO int fn_801D080C(void*);
#else
extern void* fn_801D080C(void*);
#endif

extern u8 lbl_803672A0[];

extern int fn_801CFCE0(void*);

extern void fn_800EBB74(BtlProc*);

extern void fn_800EB988(BtlProc*);

extern void fn_800D679C(void*);

extern void fn_800D616C(Handle*);

extern void fn_800D6A44(BtlProc*);

extern void fn_800D6A64(BtlProc*);

extern void fn_800FBDF0(void*);

extern void fn_800F4B94(void*, int);

extern u8 lbl_80384B90[];

/* Text/label window process. */
typedef struct MsgProc {
    u8 pad0[0x30];
    void* font;   /* 0x30 */
    Vec pos;      /* 0x34 */
    u8 pad40[8];
    f32 offY;     /* 0x48 */
    s32 timer;    /* 0x4C */
    s32 alpha;    /* 0x50 */
    s32 width;    /* 0x54 */
    s32 unk58;    /* 0x58 */
    u8 pad5C[4];
    u8 unk60;     /* 0x60 */
} MsgProc;

typedef struct Vec2 {
    f32 x, y;
} Vec2;

#if TARGET_PC
extern FE10_PROTO void fn_80011B90(void *, Vec*, Vec*);
#else
extern void fn_80011B90(int, Vec*, Vec*);
#endif

extern void fn_8007E154(void);

extern void fn_8007E4E4(f32, f32, f32, f32);

#if TARGET_PC
extern FE10_PROTO void fn_8007E374(void*, void *, int);
#else
extern void fn_8007E374(void*, int, int);
#endif

extern void fn_8007E7DC(u8);

extern void fn_8007E164(void);

extern void fn_800800D4(int);

extern void fn_80080430(f32, f32, f32, f32, f32, f32);

extern void fn_80080578(int);

extern void fn_80080308(void);

extern void fn_8007E7F4(void);

extern f32 lbl_804CD9B8;

extern f32 lbl_804CD9BC;

extern f32 lbl_804CD9C0;

extern f32 lbl_804CD9C4;

extern f32 lbl_804CD9C8;

extern void* fn_8001D3B4(void*);

#if TARGET_PC
extern FE10_PROTO void fn_80177284(int, MsgProc*);
#else
extern void fn_80177284(void (*)(MsgProc*), MsgProc*);
#endif

extern u8 lbl_80367458[];

extern void fn_8001D424(void*);

extern f32 fn_8001EBC8(int, f32, f32, f32, f32);

extern f32 fn_8001EF30(f32, f32, f32, f32);

extern f32 lbl_804CD9D8;

extern f32 lbl_804CD9DC;

extern f32 lbl_804CD9E0;

extern f32 lbl_804CD9E4;

extern f32 lbl_804CD9E8;

extern void fn_800893E4(void*, int (*)(MsgProc*, s32*), s32*);

extern void* fn_80081050(void*, void*);

extern u8 lbl_80384E00[];

static inline void MsgProc_SetPos(MsgProc* m, Vec v) {
    m->pos.x = v.x;
    m->pos.y = v.y;
    m->pos.z = v.z;
}

extern f32 lbl_804CD9EC;

extern f32 lbl_804CD9F0;

extern f32 lbl_804CD9F4;

extern u8 lbl_80384E44[];

extern void fn_800EE324(MsgProc*);

extern f32 fn_8001EF44(int, int, f32, f32);

extern u8 lbl_80384E88[];

extern void fn_8023F1A0(void*, int);

extern void fn_8023F880(void*);

extern void fn_800EF25C(void*);

typedef struct FadeChild {
    u8 pad0[0x40];
    u8 alpha; /* 0x40 */
    u8 unk41; /* 0x41 */
    u8 unk42; /* 0x42 */
    u8 unk43; /* 0x43 */
    u8 unk44; /* 0x44 */
} FadeChild;

/* Fades two child windows in/out. */
typedef struct FadeProc {
    u8 pad0[0x31];
    u8 timer;              /* 0x31 */
    u8 pad32[0xE];
    void* font;            /* 0x40 */
    FadeChild* child[2];   /* 0x44 */
    Handle* owner[2];      /* 0x4C */
} FadeProc;

extern void fn_80081A90(void*);


extern void fn_800EF6F4(FadeProc*, Handle*, Handle*, int);

extern FadeProc* fn_80083B84(void*);

extern u8 lbl_80384EE8[];

static inline FadeChild* FadeProc_Find(FadeProc* q, Handle* h) {
    if (q->owner[0] == h && q->child[0]) {
        return q->child[0];
    }
    if (q->owner[1] == h && q->child[1]) {
        return q->child[1];
    }
    return NULL;
}

typedef struct GaugeProc {
    u8 pad0[0x30];
    Handle* h;  /* 0x30 */
    u8 pad34[0x10];
    f32 value;  /* 0x44 */
} GaugeProc;

extern void fn_800D5AF0(Handle*);

extern u8 lbl_80384F18[];

extern u8 lbl_803674B4[];

typedef struct NameEntry {
    char* name;
    u8 pad4[8];
} NameEntry;

extern u8* lbl_804CB7C0;

extern int fn_80109A2C(u8**);

extern int fn_80291188(char*, char*);

extern u8* lbl_804CB7BC;

#if TARGET_PC
FE10_PROTO extern void* fn_80076F54(void*);
#else
extern void fn_80076F54(void*);
#endif

typedef struct PidInfo {
    char* name; /* 0x00 */
} PidInfo;

/* Unit/character data entry: 0x10 -> PID info, 0x0C -> model suffix. */
typedef struct CharData {
    u8 pad0[0xC];
    char* unkC;     /* 0x0C */
    PidInfo* pid;   /* 0x10 */
} CharData;

typedef struct Entry8 {
    u8 pad0[4];
    char* name; /* 0x04 */
} Entry8;

extern int fn_80290DDC(char*, const char*, ...);

extern char lbl_803E8F98[];

extern u8* lbl_804CB7C4;

typedef struct Tbl30 {
    u8 pad0[0x10];
    u8* rows; /* 0x10: rows of 0x30 bytes */
} Tbl30;

typedef struct Flags16 {
    u8 pad0[0xA];
    u16 flags; /* 0x0A */
} Flags16;

extern void fn_800F15AC(void*, f32, f32, f32);

typedef struct FxSlot {
    u16 id;  /* 0x0 */
    s16 arg; /* 0x2 */
} FxSlot;

typedef struct FxSpec {
    u8 pad0[0x8C];
    FxSlot slot[4]; /* 0x8C */
} FxSpec;

#if TARGET_PC
extern FE10_PROTO unsigned int fn_800F173C(u16);
#else
extern char* fn_800F173C(u16);
#endif

struct SndMgr;

typedef struct SndMgrVt {
    u8 pad0[0xA8];
    void (*playA8)(struct SndMgr*, u16); /* 0xA8 */
    void (*stopAC)(struct SndMgr*);      /* 0xAC */
} SndMgrVt;

typedef struct SndMgr {
    SndMgrVt* vt;
} SndMgr;

extern SndMgr* lbl_804CB5B8;

extern u16 fn_80008CF0(u32*, int);

/* Functions defined in this region. */
void fn_800E5F60(EvProc* p);
void fn_800E5FE0(EvProc* p);
void fn_800E607C(EvProc* p);
void fn_800E6198(EvProc* p);
void fn_800E61BC(EvProc* p);
void fn_800E628C(EvProc* p);
void fn_800E6334(EvProc* p);
void fn_800E63E8(EvProc* p);
void fn_800E64D0(EvProc* p);
void fn_800E6594(EvProc* p);
void fn_800E65A8(EvCmd* c);
void fn_800E660C(EvCmd* c);
void fn_800E676C(EvCmd* c);
void fn_800E67D0(EvCmd* c);
void fn_800E6948(EvCmd* c);
void fn_800E6A10(EvCmd* c);
void fn_800E6AA4(EvCmd* c);
void fn_800E6AD4(EvCmd* c);
void fn_800E6D04(EvProc* p);
void fn_800E6E1C(EvProc* p);
void fn_800E7174(EvProc* p);
void fn_800E72A8(EvProc* p);
void fn_800E7440(EvProc* p);
void fn_800E7558(EvProc* p);
void fn_800E7790(EvProc* p);
void fn_800E7AD8(EvProc* p);
void fn_800E7B38(EvCmd* c);
void fn_800E7BD0(EvProc* p);
void fn_800E7CC4(EvProc* p);
void fn_800E7E70(EvProc* p);
void fn_800E7FC0(EvProc* p);
void fn_800E801C(EvProc* p);
void fn_800E8250(EvCmd* c);
void fn_800E8304(EvProc* p);
void fn_800E83BC(EvProc* p);
void fn_800E8658(EvProc* p);
void fn_800E871C(EvProc* p);
void fn_800E8834(EvProc* p);
void fn_800E888C(EvCmd* c);
void fn_800E89F0(EvProc* p);
void fn_800E8B70(EvProc* p);
void fn_800E8BE8(s8 a, s8 b, void* parent);
void fn_800E8C54(s8 a, s8 b, void* parent);
void fn_800E8CC0(EvCmd* c);
void fn_800E8D84(EvProc* p);
void fn_800E8EAC(s8 a, s8 b, void* parent);
void fn_800E92C8(EvProc* p);
void fn_800E99AC(EvProc* p);
void fn_800E9B28(EvProc* p);
void fn_800E9CAC(EvProc* p);
void fn_800E9D38(EvProc* p);
void fn_800E9DA4(EvCmd* c);
void fn_800EA3DC(EvProc* p);
void fn_800EA3F8(EvProc* p);
void* fn_800EA810(void* parent);
void fn_800EA848(EvCmd* c);
void fn_800EAF9C(EvProc* p);
void fn_800EAFDC(EvProc* p);
void fn_800EB3C8(EvProc* p);
void fn_800EB3D8(void* parent);
void fn_800EC204(BtlProc* b);
void fn_800EC294(BtlProc* b);
void fn_800EC2A8(BtlProc* b);
void fn_800EC320(BtlProc* b);
void fn_800EC358(BtlProc* b);
void fn_800EC3C8(BtlProc* b);
void fn_800EC460(BtlProc* b);
void fn_800ED0E0(EvCmd* c);
void fn_800ED6A0(BtlProc* b);
void fn_800ED6F4(BtlProc* b);
void fn_800ED6FC(BtlProc* b);
void fn_800ED720(BtlProc* b);
void fn_800ED744(BtlProc* b);
void fn_800ED8F8(void);
void fn_800ED908(void);
void fn_800EDA80(BtlProc* b);
void fn_800EDA94(BtlProc* b);
void fn_800EDAA8(BtlProc* b);
void fn_800EDAB4(BtlProc* b);
void* fn_800EDB70(void* parent);
int fn_800EDB98(MsgProc* m, s32* v);
void fn_800EDBB8(MsgProc* m);
void fn_800EDC80(MsgProc* m);
void fn_800EDCD8(MsgProc* m);
void fn_800EDCE0(MsgProc* m);
void fn_800EDD88(MsgProc* m);
void fn_800EDE14(Vec* pos, void* parent);
#if TARGET_PC
FE10_PROTO void fn_800EDEC8(fe10_vec3 pos, void* parent);
#else
void fn_800EDEC8(Vec* pos, void* parent);
#endif
void fn_800EDF7C(MsgProc* m);
void fn_800EE044(MsgProc* m);
void fn_800EE0A4(MsgProc* m);
void fn_800EE0AC(MsgProc* m);
void fn_800EE130(MsgProc* m);
#if TARGET_PC
FE10_PROTO void fn_800EE1BC(fe10_vec3 pos, void* parent);
#else
void fn_800EE1BC(Vec* pos, void* parent);
#endif
void fn_800EE270(Vec pos, void* parent);
void fn_800EE48C(MsgProc* m);
void fn_800EE4E8(MsgProc* m);
void fn_800EE4F0(MsgProc* m);
void fn_800EE598(MsgProc* m);
#if TARGET_PC
FE10_PROTO void fn_800EE61C(const Vec* pos, int n, void* parent);
#else
void fn_800EE61C(Vec pos, int n, void* parent);
#endif
void fn_800EE6CC(Vec pos, int n, void* parent);
void fn_800EE77C(void);
void fn_800EE78C(void);
void fn_800EF6F0(void* p);
void fn_800EF9B4(FadeProc* q);
void fn_800EFA24(FadeProc* q);
void fn_800EFAC8(FadeProc* q);
void fn_800EFB6C(Handle* a, Handle* b, void* parent, int mode);
void fn_800EFBCC(void);
BOOL fn_800EFC04(void);
void fn_800EFC38(Handle* h);
void fn_800EFCD4(Handle* h);
void fn_800EFD74(GaugeProc* g);
int fn_800EFE88(GaugeProc* g, Handle* key);
BOOL fn_800EFFE8(void);
void fn_800F001C(void);
char* fn_800F08DC(u32 type);
int fn_800F0994(char* name);
int fn_800F0A2C(int k);
NameEntry* fn_800F0AA8(int i);
u8* fn_800F0AF4(int i);
#if TARGET_PC
FE10_PROTO void* fn_800F0B04(void* p);
#else
void fn_800F0B04(void* p);
#endif
char* fn_800F0B08(CharData* c, int k);
char* fn_800F0BC8(CharData* c);
char* fn_800F0C18(CharData* c);
char* fn_800F0C68(CharData* c);
u8 fn_800F1490(Tbl30* t, int i, int j);
int fn_800F14A8(Flags16* f);
void fn_800F172C(void* a, Vec* v);
EvCmd* fn_800F1820(FxSpec* s, void* parent);
BOOL fn_800F1F88(u32* f);

#endif
