#include "game/rF_8017F400/types.h"

extern "C" {

/* file menu window (0x28 bytes, see fn_801958C0.cpp WinAnim) */
typedef struct FMWin {
    s16 flags; /* 0x0 */
    s16 id;    /* 0x2 */
    s16 x4;    /* 0x4 */
    s16 x;     /* 0x6 */
    s16 y;     /* 0x8 */
    s16 fromX; /* 0xa */
    s16 toX;   /* 0xc */
    s16 fromY; /* 0xe */
    s16 toY;   /* 0x10 */
    s16 mode;  /* 0x12 */
    s16 t;     /* 0x14 */
    s16 dur;   /* 0x16 */
    s16 a0;    /* 0x18 */
    s16 a1;    /* 0x1a */
    s16 a2;    /* 0x1c */
    s16 at;    /* 0x1e */
    s16 adur;  /* 0x20 */
    u8 pad22[2];
    char* msg; /* 0x24 */
} FMWin;

typedef struct Mover {
    s16 flags; /* 0x0 */
    u8 pad2[4];
    s16 x;     /* 0x6 */
    s16 y;     /* 0x8 */
    s16 fromX; /* 0xa */
    s16 fromY; /* 0xc */
    s16 toX;   /* 0xe */
    s16 toY;   /* 0x10 */
    s16 t;     /* 0x12 */
    s16 dur;   /* 0x14 */
} Mover;

typedef struct Fade2 {
    s16 a;     /* 0x0 */
    s16 b;     /* 0x2 */
    s16 fromA; /* 0x4 */
    s16 toA;   /* 0x6 */
    s16 fromB; /* 0x8 */
    s16 toB;   /* 0xa */
    s16 t;     /* 0xc */
    s16 dur;   /* 0xe */
} Fade2;

typedef struct MsgTable {
    const char* ids[13];
} MsgTable;

/* 0x7c-byte file menu entry */
typedef struct FMEntry {
    s16 flags; /* 0x0 */
    s16 x2;
    s16 type;  /* 0x4 */
    u8 pad6[0x14 - 0x6];
    s16 x14;
    u8 pad16[0x1A - 0x16];
    s16 a0;    /* 0x1a */
    s16 a1;    /* 0x1c */
    s16 a2;    /* 0x1e */
    s16 at;    /* 0x20 */
    s16 adur;  /* 0x22 */
    u8 pad24[2];
    s16 x26;
    int x28;
    int x2c;
    int x30;
    s16 x34;
    s16 x36;
    char name[0x40]; /* 0x38 */
    f32 x78;
} FMEntry;

typedef struct FMMarker {
    s16 flags;
    u8 pad2[0x18 - 0x2];
    void* model; /* 0x18 */
} FMMarker;

typedef struct FMGlobal {
    u8 pad[0xC];
    void* res;  /* 0xc */
    void* draw; /* 0x10 */
    u8 x14;
    u8 pad15[0x84 - 0x15];
    void* x84;  /* 0x84 */
    void* buf;  /* 0x88 */
    u8 pad8c[0x4B0 - 0x8C];
    FMMarker mark[2]; /* 0x4b0 */
    u8 pad4e8[0x4F0 - 0x4E8];
} FMGlobal;

/* owner process of the file menu */
typedef struct FMProc {
    u8 pad[0x30];
    FMGlobal* g; /* 0x30 */
} FMProc;

extern FMGlobal* lbl_804CB934;
extern void* lbl_804CB92C;
extern FMProc* lbl_804CB930;
extern int lbl_804CB928;
extern u32 lbl_804CB700;
extern u8 lbl_803887F8[0x60];
extern u8 lbl_803EC180[0x50];
extern void fn_80105EA0(void* p);
extern void* fn_80081194(void* cls, void* parent);
extern void fn_80081A90(void* proc);  /* delete process */
extern void fn_80078E24(void* p);     /* free */
extern void fn_80006A2C(void* handle); /* release resource handle */
extern void* fn_8024BC94(void);
extern int fn_802450BC(void* s);
extern int lbl_804CBFCC;
extern s16 lbl_804CC0CC;
extern const char lbl_8036C9C4[0x3C];
extern void fn_80079210(void* p); /* delete */
extern int fn_801D09F0(void);
extern void* fn_800D433C(const char* id);
extern void fn_802512C4(f32 ms);
extern void fn_80251838(f32 vol, int ch, const char* name); /* play BGM */
#if TARGET_PC
extern FE10_PROTO void fn_800D4188(const char* id, p32arg);
#else
extern void fn_800D4188(const char* id, int x);
#endif
extern void fn_800D42A0(const char* id);
extern void fn_8018569C(void);
extern void fn_80192FC8(void);
extern void fn_80083B78(void* proc);
extern void fn_80252984(f32 ms);
extern u8 lbl_80388A10[0x60];
extern u8 lbl_8041EB20[0x128];
extern void fn_8019FFE4(void* p, void* arg);

class Pad {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual u32 getTrigger(); /* vtable +0x34 */
    virtual void v38();
    virtual u32 getRepeat();  /* vtable +0x3c */
    virtual void v40();
    virtual void v44();
    virtual u32 getHeld();    /* vtable +0x48 */
};
extern Pad* lbl_804CB5B8;

class SoundChan {
public:
    virtual void v08();
    virtual void v0C();
    virtual BOOL isPlaying(); /* vtable +0x10 */
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void fadeOut(int ms); /* vtable +0x2c */
};
extern SoundChan* fn_8024F3FC(int ch);
extern const char lbl_8036C5E8[0x3D0];
extern char lbl_803889E8[9]; /* "FM_CLEAR" */
extern char lbl_803889F4[9]; /* "FM_BASES" */
extern char lbl_80388A00[9]; /* "FM_CLEAR" */
extern char* strcpy(char* d, const char* s);
extern void fn_801C6EAC(const char* a, const char* b, char* out);
extern void fn_800068EC(void* handle, const char* path, int flags);
extern void fn_80250D64(f32 a, f32 b, int ch);
#if TARGET_PC
extern FE10_PROTO void* fn_80177284(ptr32<const void>, void* arg); /* register draw callback */
#else
extern void* fn_80177284(void (*func)(void), void* arg); /* register draw callback */
#endif
extern void fn_80197BF0(void);
extern void fn_80197928(void);
extern void* fn_80078CCC(u32 size, const char* tag, int arg); /* alloc */
extern s16 lbl_804CB93A;
extern s16 lbl_804CB93E;
extern const MsgTable lbl_8036C52C;
extern void* memset(void* p, int c, u32 n);
extern char* fn_800D0864(const char* id);
extern void fn_80253EE4(f32 vol, const char* name); /* play SFX */

s16 fn_8019F0F4(void)
{
    return lbl_804CB93A;
}

void fn_8019F0FC(FMWin* w)
{
    w->flags = 0;
}


void fn_8019F1E8(FMWin* w, s16 x, s16 y, s16 t, s16 mode)
{
    w->fromX = w->x;
    w->fromY = w->y;
    w->toX = x;
    w->toY = y;
    w->dur = t;
    w->t = t;
    if (mode != -1) {
        w->mode = mode;
    }
    if (t == 0) {
        w->x = x;
        w->y = y;
    }
    w->flags |= 1;
}

void fn_8019F234(FMWin* w, int t)
{
    w->a0 = 0;
    w->a1 = 0;
    w->a2 = 0xFF;
    w->adur = t;
    w->at = t;
    if (w->at == 0) {
        w->a0 = 0xFF;
    }
}

void fn_8019F260(FMWin* w, BOOL on)
{
    if (on) {
        w->flags |= 2;
    } else {
        w->flags &= ~2;
    }
}

static inline void Mover_MoveTo(Mover* m, s16 x, s16 y, s16 t)
{
    m->fromX = m->x;
    m->fromY = m->y;
    m->toX = x;
    m->toY = y;
    m->dur = t;
    m->t = t;
    if (t == 0) {
        m->x = x;
        m->y = y;
    }
    m->flags |= 1;
}

void fn_8019F288(Mover* m, FMWin* ref, s16 t)
{
    Mover_MoveTo(m, ref->x - 0x10, ref->y + 0x1A, t);
}

s16 fn_8019F2E0(FMWin* w)
{
    return w->x;
}

s16 fn_8019F2E8(FMWin* w)
{
    return w->y;
}

s16 fn_8019F2F0(FMWin* w)
{
    return w->id;
}

void fn_8019F2F8(Fade2* f, s16 t)
{
    f->fromA = f->a;
    f->fromB = f->b;
    f->toA = -500;
    f->toB = 1;
    f->dur = t;
    f->t = t;
    if (t == 0) {
        f->a = -500;
        f->b = 1;
    }
}

void fn_8019F334(FMWin* w, int t)
{
    w->adur = t;
    w->a1 = w->a0;
    w->a2 = 0;
    w->at = t;
    if (w->at == 0) {
        w->a0 = 0;
    }
}

BOOL fn_8019F35C(FMWin* w)
{
    return (w->flags & 4) != 0;
}

s16 fn_8019F368(void)
{
    return lbl_804CB93E;
}

void fn_8019F370(FMWin* w, const char* sfx)
{
    w->flags |= 0x20;
    w->x = 0x46;
    if (sfx != NULL) {
        fn_80253EE4(0.0f, sfx);
    }
}

BOOL fn_8019F39C(FMWin* w)
{
    return (w->flags & 8) != 0;
}

void fn_8019F50C(FMEntry* e, int t)
{
    e->adur = t;
    e->a1 = e->a0;
    e->a2 = 0;
    e->at = t;
    if (e->at == 0) {
        e->a0 = 0;
    }
}

void fn_8019F534(void)
{
    char path[0x80];
    lbl_804CB934->draw = NULL;
    lbl_804CB934->res = NULL;
    fn_801C6EAC(lbl_8036C5E8 + 0x3B1 /* "window/filemenu/filemenu" */, lbl_8036C5E8 + 0x3CA /* ".cms" */, path);
    fn_800068EC(&lbl_804CB934->res, path, 0x2080);
    lbl_804CB92C = lbl_804CB934->res;
    fn_80250D64(0.5f, 500.0f, 6);
    lbl_804CB934->draw = fn_80177284(fn_80197BF0, lbl_804CB930);
    fn_80197928();
    lbl_804CB934->buf = fn_80078CCC(0x1000, lbl_8036C5E8 + 0x3CF /* "" */, 0);
}

#define FM_FREE(p) \
    {                 \
        fn_80078E24(p); \
        p = NULL;       \
    }

void fn_8019F6D8(void)
{
    int i;
    if (lbl_804CB934->draw != NULL) {
        fn_80081A90(lbl_804CB934->draw);
    }
    if (lbl_804CB934->res != NULL) {
        fn_80006A2C(&lbl_804CB934->res);
    }
    for (i = 0; i < 2; i++) {
        FMMarker* m = &lbl_804CB934->mark[i];
        m->flags = 0;
        if (m->model != NULL) {
            fn_80081A90(m->model);
        }
    }
    if (lbl_804CB934->x84 != NULL) {
        fn_80081A90(lbl_804CB934->x84);
    }
    if (lbl_804CB934->buf != NULL) {
        FM_FREE(lbl_804CB934->buf);
        lbl_804CB934->buf = NULL;
    }
    FM_FREE(lbl_804CB930->g);
    lbl_804CB930->g = NULL;
    lbl_804CB934 = NULL;
}

static inline void FM_Alloc(void* parent)
{
    lbl_804CB930 = (FMProc*)fn_80081194(lbl_803887F8, parent);
    lbl_804CB930->g = (FMGlobal*)fn_80078CCC(0x4F0, lbl_8036C5E8 + 0x3CF /* "" */, 0);
    lbl_804CB934 = lbl_804CB930->g;
    memset(lbl_804CB934, 0, 0x4F0);
}

static inline void FM_Create(void* parent, u8 mode)
{
    FM_Alloc(parent);
    lbl_804CB934->x14 = mode;
    lbl_804CB928 = 0;
}

void fn_8019F7CC(void* parent)
{
    fn_80105EA0(lbl_803EC180);
    FM_Create(parent, 0);
}


void fn_8019F85C(void* parent)
{
    if (lbl_804CB700 & 0x10) {
        FM_Create(parent, 3);
    } else if (fn_802450BC(fn_8024BC94())) {
        FM_Create(parent, 1);
    }
}

void fn_8019F964(void* parent)
{
    if (fn_802450BC(fn_8024BC94())) {
        FM_Create(parent, 2);
    }
}

void fn_8019F9FC(void* parent)
{
    SoundChan* c;
    FM_Alloc(parent);
    lbl_804CB934->x14 = 5;
    c = fn_8024F3FC(3);
    if (c != NULL && c->isPlaying()) {
        c->fadeOut(500);
    }
}

void fn_8019FABC(void)
{
    lbl_804CB928 = 0;
}

void* fn_8019FAC8(void* p, int del)
{
    if (p != NULL && del > 0) {
        fn_80079210(p);
    }
    return p;
}

int fn_8019FB08(void)
{
    return lbl_804CBFCC;
}

static inline BOOL Bits_Test(u32* p, u32 n)
{
    while (n >= 32) {
        n -= 32;
        p++;
    }
    return (*p & (1 << n)) != 0;
}

BOOL fn_8019FB10(u8* obj, u32 n)
{
    return Bits_Test((u32*)(obj + 0x20), n);
}

u8 fn_8019FBA4(u8* obj)
{
    return obj[0x36];
}

BOOL fn_8019FBAC(u8* obj, u32 n)
{
    return Bits_Test((u32*)(obj + 0x40), n);
}

u8 fn_8019FC40(u8* obj)
{
    return obj[0x34];
}

u32 fn_8019FC48(u8* obj)
{
    u32 f = *(u32*)(obj + 0x20);
    u32 r = f & 1;
    if (!r) {
        r = (f >> 1) & 1;
    }
    if (!r) {
        r = (f >> 2) & 1;
    }
    if (!r) {
        r = (f >> 3) & 1;
    }
    return r;
}

s8 fn_8019FC74(u8* sys)
{
    return sys[0x1BC9];
}

void* fn_8019FC80(u8* obj)
{
    return obj + 0x44;
}

static inline void Bits_Set(u32* p, u32 n)
{
    while (n >= 32) {
        n -= 32;
        p++;
    }
    *p |= 1 << n;
}

void fn_8019FC88(u8* obj, u32 n)
{
    Bits_Set((u32*)(obj + 0x40), n);
}

s16 fn_8019FD14(void)
{
    return lbl_804CC0CC;
}

int fn_8019FDA0(void)
{
    return 0;
}

u8 fn_8019FDA8(u8* obj)
{
    return obj[0x11];
}

u8 fn_8019FDB0(u8* obj)
{
    return obj[0x9F];
}

void fn_8019FDB8(u8* obj, u8 v)
{
    obj[0x9F] = v;
}

void fn_8019FDC0(void)
{
    fn_800D433C(fn_801D09F0() ? lbl_8036C9C4 : lbl_8036C9C4 + 0x1A);
    fn_802512C4(2000.0f);
}

static inline const char* GameOverRID(void)
{
    return fn_801D09F0() ? lbl_8036C9C4 : lbl_8036C9C4 + 0x1A;
}

void fn_8019FE04(void)
{
    fn_802512C4(0.0f);
    fn_80251838(0.0f, 0, lbl_8036C9C4 + 0x2D /* "BGM_GAMEOVER1" */);
    fn_800D4188(GameOverRID(), 0);
    fn_8018569C();
    fn_80192FC8();
}

void fn_8019FE6C(void* p)
{
    if (lbl_804CB5B8->getHeld() & 0xC00) {
        fn_80083B78(p);
        fn_80252984(2000.0f);
    }
}

void fn_8019FEC0(void)
{
    fn_800D42A0(GameOverRID());
}

void* fn_8019FEFC(void* parent)
{
    return fn_80081194(lbl_80388A10, parent);
}

void fn_8019FFD4(void* arg)
{
    fn_8019FFE4(lbl_8041EB20, arg);
}

}
